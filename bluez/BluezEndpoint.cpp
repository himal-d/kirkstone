/*
 *
 *    Copyright (c) 2020-2022 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/*
 *  Copyright (c) 2016-2019, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#include "BluezEndpoint.h"

#include <cstring>
#include <errno.h>
#include <memory>
#include <sys/socket.h>
#include <unistd.h>
#include <utility>

#include <gio/gio.h>
#include <gio/gunixfdlist.h>
#include <glib-object.h>
#include <glib.h>

#include <ble/Ble.h>
#include <lib/support/BitFlags.h>
#include <lib/support/CHIPMem.h>
#include <lib/support/CodeUtils.h>
#include <lib/support/logging/CHIPLogging.h>
#include <platform/ConfigurationManager.h>
#include <platform/ConnectivityManager.h>
#include <platform/DeviceInstanceInfoProvider.h>
#include <platform/GLibTypeDeleter.h>
#include <platform/Linux/dbus/bluez/DbusBluez.h>
#include <platform/PlatformManager.h>
#include <platform/internal/BLEManager.h>
#include <setup_payload/AdditionalDataPayloadGenerator.h>
#include <system/SystemPacketBuffer.h>

#include "BluezConnection.h"
#include "Types.h"
#include <unistd.h>

#if !GLIB_CHECK_VERSION(2, 68, 0)
#define g_memdup2(mem, size) g_memdup(mem, static_cast<unsigned int>(size))
#endif

namespace chip {
namespace DeviceLayer {
namespace Internal {

constexpr uint16_t kMaxConnectRetries = 4;

gboolean BluezEndpoint::BluezCharacteristicReadValue(BluezGattCharacteristic1 * aChar, GDBusMethodInvocation * aInvocation,
                                                     GVariant * aOptions)
{
    ChipLogDetail(DeviceLayer, "Received %s", __func__);
    GVariant * val = bluez_gatt_characteristic1_get_value(aChar);
    bluez_gatt_characteristic1_complete_read_value(aChar, aInvocation, val);
    return TRUE;
}

gboolean BluezEndpoint::BluezCharacteristicAcquireWrite(BluezGattCharacteristic1 * aChar, GDBusMethodInvocation * aInvocation,
                                                        GUnixFDList * aFDList, GVariant * aOptions)
{
    int fds[2] = { -1, -1 };
#if CHIP_ERROR_LOGGING
    char * errStr;
#endif // CHIP_ERROR_LOGGING
    BluezConnection * conn = nullptr;
    GAutoPtr<GVariant> option_mtu;
    uint16_t mtu;

    conn = GetBluezConnectionViaDevice();
    VerifyOrReturnValue(
        conn != nullptr, FALSE,
        g_dbus_method_invocation_return_dbus_error(aInvocation, "org.bluez.Error.Failed", "No CHIPoBLE connection"));

    ChipLogDetail(DeviceLayer, "BluezCharacteristicAcquireWrite is called, conn: %p", conn);

    VerifyOrReturnValue(
        g_variant_lookup(aOptions, "mtu", "q", &mtu), FALSE, ChipLogError(DeviceLayer, "FAIL: No MTU in options in %s", __func__);
        g_dbus_method_invocation_return_dbus_error(aInvocation, "org.bluez.Error.InvalidArguments", "MTU negotiation failed"));
    conn->SetMTU(mtu);

    if (socketpair(AF_UNIX, SOCK_SEQPACKET | SOCK_NONBLOCK | SOCK_CLOEXEC, 0, fds) < 0)
    {
#if CHIP_ERROR_LOGGING
        errStr = strerror(errno);
#endif // CHIP_ERROR_LOGGING
        ChipLogError(DeviceLayer, "FAIL: socketpair: %s in %s", StringOrNullMarker(errStr), __func__);
        g_dbus_method_invocation_return_dbus_error(aInvocation, "org.bluez.Error.Failed", "FD creation failed");
        return FALSE;
    }

    conn->SetupWriteHandler(fds[0]);
    bluez_gatt_characteristic1_set_write_acquired(aChar, TRUE);

    GUnixFDList * fdList = g_unix_fd_list_new_from_array(&fds[1], 1);
    bluez_gatt_characteristic1_complete_acquire_write(aChar, aInvocation, fdList, g_variant_new_handle(0), conn->GetMTU());
    g_object_unref(fdList);

    return TRUE;
}

static gboolean BluezCharacteristicAcquireWriteError(BluezGattCharacteristic1 * aChar, GDBusMethodInvocation * aInvocation,
                                                     GUnixFDList * aFDList, GVariant * aOptions)
{
    ChipLogDetail(DeviceLayer, "Received %s", __func__);
    g_dbus_method_invocation_return_dbus_error(aInvocation, "org.bluez.Error.NotSupported",
                                               "AcquireWrite for characteristic is unsupported");
    return TRUE;
}

gboolean BluezEndpoint::BluezCharacteristicAcquireNotify(BluezGattCharacteristic1 * aChar, GDBusMethodInvocation * aInvocation,
                                                         GUnixFDList * aFDList, GVariant * aOptions)
{
    int fds[2] = { -1, -1 };
#if CHIP_ERROR_LOGGING
    char * errStr;
#endif // CHIP_ERROR_LOGGING
    BluezConnection * conn       = nullptr;
    bool isAdditionalAdvertising = false;
    GAutoPtr<GVariant> option_mtu;
    uint16_t mtu;

#if CHIP_ENABLE_ADDITIONAL_DATA_ADVERTISING
    isAdditionalAdvertising = (aChar == mC3.get());
#endif

    if (bluez_gatt_characteristic1_get_notifying(aChar))
    {
        g_dbus_method_invocation_return_dbus_error(aInvocation, "org.bluez.Error.NotPermitted", "Already notifying");
        return FALSE;
    }

    conn = GetBluezConnectionViaDevice();
    VerifyOrReturnValue(
        conn != nullptr, FALSE,
        g_dbus_method_invocation_return_dbus_error(aInvocation, "org.bluez.Error.Failed", "No CHIPoBLE connection"));

    VerifyOrReturnValue(
        g_variant_lookup(aOptions, "mtu", "q", &mtu), FALSE, ChipLogError(DeviceLayer, "FAIL: No MTU in options in %s", __func__);
        g_dbus_method_invocation_return_dbus_error(aInvocation, "org.bluez.Error.InvalidArguments", "MTU negotiation failed"););
    conn->SetMTU(mtu);

    if (socketpair(AF_UNIX, SOCK_SEQPACKET | SOCK_NONBLOCK | SOCK_CLOEXEC, 0, fds) < 0)
    {
#if CHIP_ERROR_LOGGING
        errStr = strerror(errno);
#endif // CHIP_ERROR_LOGGING
        ChipLogError(DeviceLayer, "FAIL: socketpair: %s in %s", StringOrNullMarker(errStr), __func__);
        g_dbus_method_invocation_return_dbus_error(aInvocation, "org.bluez.Error.Failed", "FD creation failed");
        return FALSE;
    }

    conn->SetupNotifyHandler(fds[0], isAdditionalAdvertising);
    bluez_gatt_characteristic1_set_notify_acquired(aChar, TRUE);
    conn->SetNotifyAcquired(true);

    GUnixFDList * fdList = g_unix_fd_list_new_from_array(&fds[1], 1);
    bluez_gatt_characteristic1_complete_acquire_notify(aChar, aInvocation, fdList, g_variant_new_handle(0), conn->GetMTU());
    g_object_unref(fdList);

    BLEManagerImpl::HandleTXCharCCCDWrite(conn);

    return TRUE;
}

static gboolean BluezCharacteristicAcquireNotifyError(BluezGattCharacteristic1 * aChar, GDBusMethodInvocation * aInvocation,
                                                      GVariant * aOptions)
{
    ChipLogDetail(DeviceLayer, "Received %s", __func__);
    g_dbus_method_invocation_return_dbus_error(aInvocation, "org.bluez.Error.NotSupported",
                                               "AcquireNotify for characteristic is unsupported");
    return TRUE;
}

gboolean BluezEndpoint::BluezCharacteristicConfirm(BluezGattCharacteristic1 * aChar, GDBusMethodInvocation * aInvocation)
{
    BluezConnection * conn = GetBluezConnectionViaDevice();
    ChipLogDetail(Ble, "Indication confirmation, %p", conn);
    bluez_gatt_characteristic1_complete_confirm(aChar, aInvocation);
    BLEManagerImpl::HandleTXComplete(conn);
    return TRUE;
}

static gboolean BluezCharacteristicConfirmError(BluezGattCharacteristic1 * aChar, GDBusMethodInvocation * aInvocation)
{
    g_dbus_method_invocation_return_dbus_error(aInvocation, "org.bluez.Error.Failed", "Confirm from characteristic is unsupported");
    return TRUE;
}

BluezGattCharacteristic1 * BluezEndpoint::CreateGattCharacteristic(BluezGattService1 * aService, const char * aCharName,
                                                                   const char * aUUID, const char * const * aFlags)
{
    const char * servicePath = g_dbus_object_get_object_path(g_dbus_interface_get_object(G_DBUS_INTERFACE(aService)));
    GAutoPtr<char> charPath(g_strdup_printf("%s/%s", servicePath, aCharName));
    BluezObjectSkeleton * object;
    BluezGattCharacteristic1 * characteristic;

    ChipLogDetail(DeviceLayer, "Create characteristic object at %s", charPath.get());
    object = bluez_object_skeleton_new(charPath.get());

    characteristic = bluez_gatt_characteristic1_skeleton_new();
    bluez_gatt_characteristic1_set_uuid(characteristic, aUUID);
    bluez_gatt_characteristic1_set_flags(characteristic, aFlags);
    bluez_gatt_characteristic1_set_service(characteristic, servicePath);

    // Initialize value to empty array, so it can be read without prior write from the client side.
    auto value = g_variant_new_fixed_array(G_VARIANT_TYPE_BYTE, nullptr, 0, sizeof(uint8_t));
    bluez_gatt_characteristic1_set_value(characteristic, value);

    bluez_object_skeleton_set_gatt_characteristic1(object, characteristic);
    g_dbus_object_manager_server_export(mRoot.get(), G_DBUS_OBJECT_SKELETON(object));
    g_object_unref(object);

    return characteristic;
}

void BluezEndpoint::RegisterGattApplicationDone(GObject * aObject, GAsyncResult * aResult)
{
    GAutoPtr<GError> error;
    if (!bluez_gatt_manager1_call_register_application_finish(reinterpret_cast<BluezGattManager1 *>(aObject), aResult,
                                                              &error.GetReceiver()))
    {
        ChipLogError(DeviceLayer, "FAIL: RegisterGattApplication: %s", error->message);
        BLEManagerImpl::NotifyBLEPeripheralRegisterAppComplete(BluezCallToChipError(error.get()));
        return;
    }

    ChipLogDetail(DeviceLayer, "GATT application registered successfully");
    BLEManagerImpl::NotifyBLEPeripheralRegisterAppComplete(CHIP_NO_ERROR);
}

CHIP_ERROR BluezEndpoint::RegisterGattApplicationImpl()
{
    VerifyOrReturnError(mAdapter, CHIP_ERROR_UNINITIALIZED);

    // If the adapter configured in the Init() was unplugged, the g_dbus_interface_get_object()
    // or bluez_object_get_gatt_manager1() might return nullptr (depending on the timing, since
    // the D-Bus communication is handled on a separate thread). In such case, we should not
    // report internal error, but adapter unavailable, so the application can handle the situation
    // properly.

    GDBusObject * adapterObject = g_dbus_interface_get_object(reinterpret_cast<GDBusInterface *>(mAdapter.get()));
    VerifyOrReturnError(adapterObject != nullptr, BLE_ERROR_ADAPTER_UNAVAILABLE);
    GAutoPtr<BluezGattManager1> gattMgr(bluez_object_get_gatt_manager1(reinterpret_cast<BluezObject *>(adapterObject)));
    VerifyOrReturnError(gattMgr, BLE_ERROR_ADAPTER_UNAVAILABLE);

    GVariantBuilder optionsBuilder;
    g_variant_builder_init(&optionsBuilder, G_VARIANT_TYPE("a{sv}"));
    GVariant * options = g_variant_builder_end(&optionsBuilder);

    bluez_gatt_manager1_call_register_application(
        gattMgr.get(), mpRootPath, options, nullptr,
        +[](GObject * aObj, GAsyncResult * aResult, void * self) {
            reinterpret_cast<BluezEndpoint *>(self)->RegisterGattApplicationDone(aObj, aResult);
        },
        this);

    return CHIP_NO_ERROR;
}

/// Update the table of open BLE connections whenever a new device is spotted or its attributes have changed.
void BluezEndpoint::UpdateConnectionTable(BluezDevice1 & aDevice)
{
    const char * objectPath = g_dbus_proxy_get_object_path(reinterpret_cast<GDBusProxy *>(&aDevice));
    BluezConnection * conn  = GetBluezConnection(objectPath);

    if (conn != nullptr && !bluez_device1_get_connected(&aDevice))
    {
        ChipLogDetail(DeviceLayer, "BLE connection closed: conn=%p", conn);
        BLEManagerImpl::HandleConnectionClosed(conn);
        mConnMap.erase(objectPath);
        // TODO: the connection object should be released after BLEManagerImpl finishes cleaning up its resources
        // after the disconnection. Releasing it here doesn't cause any issues, but it's error-prone.
        chip::Platform::Delete(conn);
        return;
    }

    if (conn == nullptr)
    {
        HandleNewDevice(aDevice);
    }
}

void BluezEndpoint::HandleNewDevice(BluezDevice1 & aDevice)
{
    VerifyOrReturn(bluez_device1_get_connected(&aDevice));
    VerifyOrReturn(!mIsCentral || bluez_device1_get_services_resolved(&aDevice));
    CHIP_ERROR err;

    const char * objectPath = g_dbus_proxy_get_object_path(reinterpret_cast<GDBusProxy *>(&aDevice));
    BluezConnection * conn  = GetBluezConnection(objectPath);
    VerifyOrReturn(conn == nullptr,
                   ChipLogError(DeviceLayer, "FAIL: Connection already tracked: conn=%p device=%s path=%s", conn,
                                conn->GetPeerAddress(), objectPath));

    conn = chip::Platform::New<BluezConnection>(aDevice);
    VerifyOrExit(conn != nullptr, err = CHIP_ERROR_NO_MEMORY);
    SuccessOrExit(err = conn->Init(*this));

    mpPeerDevicePath           = g_strdup(objectPath);
    mConnMap[mpPeerDevicePath] = conn;

    ChipLogDetail(DeviceLayer, "New BLE connection: conn=%p device=%s path=%s", conn, conn->GetPeerAddress(), objectPath);

    BLEManagerImpl::HandleNewConnection(conn);
    return;

exit:
    chip::Platform::Delete(conn);
    BLEManagerImpl::HandleConnectFailed(err);
}

void BluezEndpoint::OnDeviceAdded(BluezDevice1 & device)
{
    HandleNewDevice(device);
}

void BluezEndpoint::OnDevicePropertyChanged(BluezDevice1 & device, GVariant * changedProps, const char * const * invalidatedProps)
{
    UpdateConnectionTable(device);
}

void BluezEndpoint::OnDeviceRemoved(BluezDevice1 & device)
{
    // Handling device removal is not necessary because disconnection is already handled
    // in the OnDevicePropertyChanged() - we are checking for the "Connected" property.
}

BluezGattService1 * BluezEndpoint::CreateGattService(const char * aUUID)
{
    BluezObjectSkeleton * object;
    BluezGattService1 * service;

    mpServicePath = g_strdup_printf("%s/service", mpRootPath);
    ChipLogDetail(DeviceLayer, "CREATE service object at %s", mpServicePath);
    object = bluez_object_skeleton_new(mpServicePath);

    service = bluez_gatt_service1_skeleton_new();
    bluez_gatt_service1_set_uuid(service, aUUID);
    // device is only valid for remote services
    bluez_gatt_service1_set_primary(service, TRUE);

    // includes -- unclear whether required.  Might be filled in later
    bluez_object_skeleton_set_gatt_service1(object, service);
    g_dbus_object_manager_server_export(mRoot.get(), G_DBUS_OBJECT_SKELETON(object));
    g_object_unref(object);

    return service;
}

BluezConnection * BluezEndpoint::GetBluezConnection(const char * aPath)
{
    auto it = mConnMap.find(aPath);
    return (it != mConnMap.end()) ? it->second : nullptr;
}

BluezConnection * BluezEndpoint::GetBluezConnectionViaDevice()
{
    return GetBluezConnection(mpPeerDevicePath);
}

#if CHIP_ENABLE_ADDITIONAL_DATA_ADVERTISING
static void UpdateAdditionalDataCharacteristic(BluezGattCharacteristic1 * characteristic)
{
    VerifyOrReturn(characteristic != nullptr);

    // Construct the TLV for the additional data
    GVariant * cValue = nullptr;
    gpointer data;
    CHIP_ERROR err = CHIP_NO_ERROR;
    chip::System::PacketBufferHandle bufferHandle;
    BitFlags<AdditionalDataFields> additionalDataFields;
    AdditionalDataPayloadGeneratorParams additionalDataPayloadParams;

#if CHIP_ENABLE_ROTATING_DEVICE_ID && defined(CHIP_DEVICE_CONFIG_ROTATING_DEVICE_ID_UNIQUE_ID)
    uint8_t rotatingDeviceIdUniqueId[ConfigurationManager::kRotatingDeviceIDUniqueIDLength] = {};
    MutableByteSpan rotatingDeviceIdUniqueIdSpan(rotatingDeviceIdUniqueId);

    err = GetDeviceInstanceInfoProvider()->GetRotatingDeviceIdUniqueId(rotatingDeviceIdUniqueIdSpan);
    SuccessOrExit(err);
    err = ConfigurationMgr().GetLifetimeCounter(additionalDataPayloadParams.rotatingDeviceIdLifetimeCounter);
    SuccessOrExit(err);
    additionalDataPayloadParams.rotatingDeviceIdUniqueId = rotatingDeviceIdUniqueIdSpan;
    additionalDataFields.Set(AdditionalDataFields::RotatingDeviceId);
#endif /* CHIP_ENABLE_ROTATING_DEVICE_ID && defined(CHIP_DEVICE_CONFIG_ROTATING_DEVICE_ID_UNIQUE_ID) */

    err = AdditionalDataPayloadGenerator().generateAdditionalDataPayload(additionalDataPayloadParams, bufferHandle,
                                                                         additionalDataFields);
    SuccessOrExit(err);

    data = g_memdup2(bufferHandle->Start(), bufferHandle->DataLength());

    cValue = g_variant_new_from_data(G_VARIANT_TYPE("ay"), data, bufferHandle->DataLength(), TRUE, g_free, data);
    bluez_gatt_characteristic1_set_value(characteristic, cValue);

    return;

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(DeviceLayer, "Failed to generate TLV encoded Additional Data (%s)", __func__);
    }
    return;
}
#endif

void BluezEndpoint::SetupGattService()
{

    static const char * const c1_flags[] = { "write", nullptr };
    static const char * const c2_flags[] = { "indicate", nullptr };
#if CHIP_ENABLE_ADDITIONAL_DATA_ADVERTISING
    static const char * const c3_flags[] = { "read", nullptr };
#endif

    mService.reset(CreateGattService(Ble::CHIP_BLE_SERVICE_SHORT_UUID_STR));

    // C1 characteristic
    mC1.reset(CreateGattCharacteristic(mService.get(), "c1", Ble::CHIP_BLE_CHAR_1_UUID_STR, c1_flags));
    g_signal_connect(mC1.get(), "handle-read-value",
                     G_CALLBACK(+[](BluezGattCharacteristic1 * aChar, GDBusMethodInvocation * aInv, GVariant * aOpt,
                                    BluezEndpoint * self) { return self->BluezCharacteristicReadValue(aChar, aInv, aOpt); }),
                     this);
    g_signal_connect(
        mC1.get(), "handle-acquire-write",
        G_CALLBACK(+[](BluezGattCharacteristic1 * aChar, GDBusMethodInvocation * aInv, GUnixFDList * aFDList, GVariant * aOpt,
                       BluezEndpoint * self) { return self->BluezCharacteristicAcquireWrite(aChar, aInv, aFDList, aOpt); }),
        this);
    g_signal_connect(mC1.get(), "handle-acquire-notify", G_CALLBACK(BluezCharacteristicAcquireNotifyError), nullptr);
    g_signal_connect(mC1.get(), "handle-confirm", G_CALLBACK(BluezCharacteristicConfirmError), nullptr);

    // C2 characteristic
    mC2.reset(CreateGattCharacteristic(mService.get(), "c2", Ble::CHIP_BLE_CHAR_2_UUID_STR, c2_flags));
    g_signal_connect(mC2.get(), "handle-read-value",
                     G_CALLBACK(+[](BluezGattCharacteristic1 * aChar, GDBusMethodInvocation * aInv, GVariant * aOpt,
                                    BluezEndpoint * self) { return self->BluezCharacteristicReadValue(aChar, aInv, aOpt); }),
                     this);
    g_signal_connect(mC2.get(), "handle-acquire-write", G_CALLBACK(BluezCharacteristicAcquireWriteError), nullptr);
    g_signal_connect(
        mC2.get(), "handle-acquire-notify",
        G_CALLBACK(+[](BluezGattCharacteristic1 * aChar, GDBusMethodInvocation * aInv, GUnixFDList * aFDList, GVariant * aOpt,
                       BluezEndpoint * self) { return self->BluezCharacteristicAcquireNotify(aChar, aInv, aFDList, aOpt); }),
        this);
    g_signal_connect(mC2.get(), "handle-confirm",
                     G_CALLBACK(+[](BluezGattCharacteristic1 * aChar, GDBusMethodInvocation * aInv, BluezEndpoint * self) {
                         return self->BluezCharacteristicConfirm(aChar, aInv);
                     }),
                     this);

    ChipLogDetail(DeviceLayer, "CHIP BTP C1 %s", bluez_gatt_characteristic1_get_service(mC1.get()));
    ChipLogDetail(DeviceLayer, "CHIP BTP C2 %s", bluez_gatt_characteristic1_get_service(mC2.get()));

#if CHIP_ENABLE_ADDITIONAL_DATA_ADVERTISING
    ChipLogDetail(DeviceLayer, "CHIP_ENABLE_ADDITIONAL_DATA_ADVERTISING is TRUE");
    // Additional data characteristics
    mC3.reset(CreateGattCharacteristic(mService.get(), "c3", Ble::CHIP_BLE_CHAR_3_UUID_STR, c3_flags));
    g_signal_connect(mC3.get(), "handle-read-value",
                     G_CALLBACK(+[](BluezGattCharacteristic1 * aChar, GDBusMethodInvocation * aInv, GVariant * aOpt,
                                    BluezEndpoint * self) { return self->BluezCharacteristicReadValue(aChar, aInv, aOpt); }),
                     this);
    g_signal_connect(mC3.get(), "handle-acquire-write", G_CALLBACK(BluezCharacteristicAcquireWriteError), nullptr);
    g_signal_connect(
        mC3.get(), "handle-acquire-notify",
        G_CALLBACK(+[](BluezGattCharacteristic1 * aChar, GDBusMethodInvocation * aInv, GUnixFDList * aFDList, GVariant * aOpt,
                       BluezEndpoint * self) { return self->BluezCharacteristicAcquireNotify(aChar, aInv, aFDList, aOpt); }),
        this);
    g_signal_connect(mC3.get(), "handle-confirm",
                     G_CALLBACK(+[](BluezGattCharacteristic1 * aChar, GDBusMethodInvocation * aInv, BluezEndpoint * self) {
                         return self->BluezCharacteristicConfirm(aChar, aInv);
                     }),
                     this);

    // update the characteristic value
    UpdateAdditionalDataCharacteristic(mC3.get());
    ChipLogDetail(DeviceLayer, "CHIP BTP C3 %s", bluez_gatt_characteristic1_get_service(mC3.get()));
#else
    ChipLogDetail(DeviceLayer, "CHIP_ENABLE_ADDITIONAL_DATA_ADVERTISING is FALSE");
#endif
}

void BluezEndpoint::SetupGattServer(GDBusConnection * aConn)
{
    VerifyOrReturn(!mIsCentral);

    mpRootPath = g_strdup_printf("/chipoble/%04x", getpid() & 0xffff);
    mRoot.reset(g_dbus_object_manager_server_new(mpRootPath));

    SetupGattService();

    // Set connection after the service is set up in order to reduce the number
    // of signals sent on the bus.
    g_dbus_object_manager_server_set_connection(mRoot.get(), aConn);
}

CHIP_ERROR BluezEndpoint::SetupEndpointBindings()
{
    SetupGattServer(mObjectManager.GetConnection());
    return CHIP_NO_ERROR;
}

CHIP_ERROR BluezEndpoint::RegisterGattApplication()
{
    return PlatformMgrImpl().GLibMatterContextInvokeSync(
        +[](BluezEndpoint * self) { return self->RegisterGattApplicationImpl(); }, this);
}

CHIP_ERROR BluezEndpoint::Init(BluezAdapter1 * apAdapter, bool aIsCentral)
{
    VerifyOrReturnError(!mIsInitialized, CHIP_ERROR_INCORRECT_STATE);
    VerifyOrReturnError(apAdapter != nullptr, CHIP_ERROR_INVALID_ARGUMENT);

    mAdapter.reset(reinterpret_cast<BluezAdapter1 *>(g_object_ref(apAdapter)));
    mIsCentral = aIsCentral;

    CHIP_ERROR err = mObjectManager.SubscribeDeviceNotifications(mAdapter.get(), this);
    VerifyOrReturnError(err == CHIP_NO_ERROR, err,
                        ChipLogError(DeviceLayer, "Failed to subscribe for notifications: %" CHIP_ERROR_FORMAT, err.Format()));

    err = PlatformMgrImpl().GLibMatterContextInvokeSync(
        +[](BluezEndpoint * self) { return self->SetupEndpointBindings(); }, this);
    VerifyOrReturnError(err == CHIP_NO_ERROR, err,
                        ChipLogError(DeviceLayer, "Failed to schedule endpoint initialization: %" CHIP_ERROR_FORMAT, err.Format()));

    mIsInitialized = true;

    return CHIP_NO_ERROR;
}

void BluezEndpoint::Shutdown()
{
    VerifyOrReturn(mIsInitialized);

    // Run endpoint cleanup on the CHIPoBluez thread. This is necessary because the
    // cleanup function releases the D-Bus manager client object, which handles D-Bus
    // signals. Otherwise, we will face race condition when the D-Bus signal is in
    // the middle of being processed when the cleanup function is called.
    PlatformMgrImpl().GLibMatterContextInvokeSync(
        +[](BluezEndpoint * self) {
            self->mAdapter.reset();
            self->mRoot.reset();
            self->mService.reset();
            self->mC1.reset();
            self->mC2.reset();
#if CHIP_ENABLE_ADDITIONAL_DATA_ADVERTISING
            self->mC3.reset();
#endif
            return CHIP_NO_ERROR;
        },
        this);

    g_free(mpRootPath);
    g_free(mpServicePath);
    g_free(mpPeerDevicePath);

    mIsInitialized = false;
}

CHIP_ERROR BluezEndpoint::VerifyAdapterReadiness()
{
    VerifyOrReturnError(mAdapter != nullptr, CHIP_ERROR_INTERNAL);

    // Check if adapter is powered
    gboolean powered = bluez_adapter1_get_powered(mAdapter.get());    

    // Adapter is ready if powered
    if (powered)	    
    {
        ChipLogDetail(DeviceLayer, "Adapter is ready (powered: %d)", powered);	    
        return CHIP_NO_ERROR;
    }

    // Wait for adapter to become ready (with timeout)
    constexpr uint32_t kAdapterReadinessTimeoutMs = 2000;
    constexpr uint32_t kAdapterReadinessPollMs    = 100;
    uint32_t waitTime                             = 0;

    while (waitTime < kAdapterReadinessTimeoutMs)
    {
        usleep(kAdapterReadinessPollMs * 1000);
        waitTime += kAdapterReadinessPollMs;

        // Re-check adapter state
        powered = bluez_adapter1_get_powered(mAdapter.get());

        if (powered)
        {
            ChipLogDetail(DeviceLayer, "Adapter is ready after %u ms (powered: %d)", waitTime, powered);
            return CHIP_NO_ERROR;
        }
    }
    ChipLogError(DeviceLayer, "Adapter readiness timeout: powered=%d", powered);
    return CHIP_ERROR_TIMEOUT;
}

// Helper to safely remove and rediscover device after invalidation
BluezDevice1 * BluezEndpoint::RediscoverDeviceByAddress(const char * deviceAddress)
{
    if (deviceAddress == nullptr || mAdapter == nullptr)
    {
        return nullptr;
    }

    ChipLogDetail(DeviceLayer, "Attempting to rediscover device at address: %s", deviceAddress);

    // Step 1: Safely find device path first (before any modifications)
    const char * devicePathToRemove = nullptr;
    {
        BluezObjectList objects = mObjectManager.GetObjects();
        for (BluezObject & object : objects)
        {
            GAutoPtr<BluezDevice1> device(bluez_object_get_device1(&object));
            if (device != nullptr)
            {
                const char * devAddress = bluez_device1_get_address(device.get());
                if (devAddress != nullptr && strcmp(devAddress, deviceAddress) == 0)
                {
                    devicePathToRemove = g_dbus_proxy_get_object_path(reinterpret_cast<GDBusProxy *>(device.get()));
                    if (devicePathToRemove != nullptr)
                    {
                        devicePathToRemove = g_strdup(devicePathToRemove);  // Make a copy for safety
                    }
                    break;
                }
            }
        }
    }

    // Step 2: Remove device from cache (using the saved path, avoiding iteration during removal)
    if (devicePathToRemove != nullptr)
    {
        ChipLogDetail(DeviceLayer, "Removing device %s (path: %s) from cache to force re-discovery", deviceAddress, devicePathToRemove);
        
        GAutoPtr<GError> error;
        bluez_adapter1_call_remove_device_sync(mAdapter.get(), devicePathToRemove, nullptr, &error.GetReceiver());
        if (error != nullptr && !g_error_matches(error.get(), G_DBUS_ERROR, G_DBUS_ERROR_UNKNOWN_OBJECT))
        {
            ChipLogDetail(DeviceLayer, "Device removal note: %s", error->message);
        }
        g_free(const_cast<char *>(devicePathToRemove));
    }
    else
    {
        ChipLogDetail(DeviceLayer, "Device %s not found in cache, may already be removed", deviceAddress);
    }

    // Step 3: Ensure discovery is active (required for re-discovery)
    // Attempt to start discovery - if already active, BlueZ will return an error we can ignore
    ChipLogDetail(DeviceLayer, "Ensuring discovery is active for re-discovery");
    GAutoPtr<GError> discError;
    if (!bluez_adapter1_call_start_discovery_sync(mAdapter.get(), nullptr, &discError.GetReceiver()))
    {
        if (discError != nullptr)
        {
            // Ignore "Already discovering" errors - check error message for BlueZ-specific errors
            // BlueZ returns "Already discovering" or similar when discovery is already active
            const char * errorMsg = discError->message;
            bool isAlreadyDiscovering = (errorMsg != nullptr && 
                                        (strstr(errorMsg, "Already") != nullptr ||
                                         strstr(errorMsg, "already") != nullptr ||
                                         strstr(errorMsg, "in progress") != nullptr));
            
            if (!isAlreadyDiscovering)
            {
                ChipLogDetail(DeviceLayer, "Discovery start note: %s", errorMsg);
            }
        }
    }

    // Step 4: Non-blocking wait for device re-discovery using GLib event processing
    // Process pending GLib events to allow OnDeviceAdded signals to be delivered
    constexpr uint32_t kRediscoveryWaitMs = 3000;
    constexpr uint32_t kRediscoveryPollMs = 100;  // Smaller poll interval for better responsiveness
    constexpr uint32_t kMaxIterations = (kRediscoveryWaitMs / kRediscoveryPollMs);
    
    GMainContext * context = g_main_context_get_thread_default();
    if (context == nullptr)
    {
        context = g_main_context_default();
    }

    ChipLogDetail(DeviceLayer, "Waiting up to %u ms for device re-discovery (non-blocking)...", kRediscoveryWaitMs);

    for (uint32_t iteration = 0; iteration < kMaxIterations; iteration++)
    {
        // Process pending GLib events without blocking (allows OnDeviceAdded to fire)
        while (g_main_context_iteration(context, FALSE))
        {
            // Process all pending events
        }

        // Search for the rediscovered device by address
        BluezObjectList objects = mObjectManager.GetObjects();
        for (BluezObject & object : objects)
        {
            GAutoPtr<BluezDevice1> device(bluez_object_get_device1(&object));
            if (device != nullptr)
            {
                const char * devAddress = bluez_device1_get_address(device.get());
                if (devAddress != nullptr && strcmp(devAddress, deviceAddress) == 0)
                {
                    // Found the device - return a new reference (caller must unref)
                    uint32_t elapsedMs = iteration * kRediscoveryPollMs;
                    ChipLogDetail(DeviceLayer, "Device rediscovered after %u ms", elapsedMs);
                    return reinterpret_cast<BluezDevice1 *>(g_object_ref(device.get()));
                }
            }
        }

        // Small delay using GLib's time source (non-blocking for event loop)
        // Use g_usleep which yields to the event loop on some systems, but we're already
        // processing events above, so a minimal delay is acceptable here
        g_usleep(kRediscoveryPollMs * 1000);
    }

    ChipLogError(DeviceLayer, "Device %s not rediscovered after %u ms", deviceAddress, kRediscoveryWaitMs);
    return nullptr;
}

// ConnectDevice callbacks

CHIP_ERROR BluezEndpoint::ConnectDeviceImpl(BluezDevice1 & aDevice)
{
    constexpr uint32_t kRetryDelayMs = 1000;  // Increased delay for better stability
    constexpr uint16_t kError36RediscoveryThreshold = 2;  // After 2 error 36s, try rediscovery
	
    // Due to radio interferences or Wi-Fi coexistence, sometimes the BLE connection may not be
    // established (e.g. Connection Indication Packet is missed by BLE peripheral). In such case,
    // BlueZ returns "Software caused connection abort error", and we should make a connection retry.
    // It's important to make sure that the connection is correctly ceased, by calling `Disconnect()`
    // D-Bus method, or else `Connect()` returns immediately without any effect.

    // Verify adapter readiness before connection attempt
    CHIP_ERROR err = VerifyAdapterReadiness();
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(DeviceLayer, "Adapter not ready: %" CHIP_ERROR_FORMAT, err.Format());
        return err;
    }

    // Get device address early for potential rediscovery
    const char * deviceAddress = bluez_device1_get_address(&aDevice);
    BluezDevice1 * currentDevice = &aDevice;  // Start with the provided device
    GAutoPtr<BluezDevice1> rediscoveredDevice;  // Will hold rediscovered device if needed
    uint16_t error36Count = 0;

    for (uint16_t i = 0; i < kMaxConnectRetries; i++)
    {
        GAutoPtr<GError> error;
        if (bluez_device1_call_connect_sync(currentDevice, mConnectCancellable.get(), &error.GetReceiver()))
        {
            ChipLogDetail(DeviceLayer, "ConnectDevice complete");
            return CHIP_NO_ERROR;
        }

        ChipLogError(DeviceLayer, "FAIL: ConnectDevice: %s (%d)", error->message, error->code);
        
        // Check if device object became invalid (UnknownObject error)
        bool isUnknownObject = g_error_matches(error.get(), G_DBUS_ERROR, G_DBUS_ERROR_UNKNOWN_OBJECT);
        
        // Check for error 36 (le-connection-abort-by-local) using proper error matching
        // Error 36 comes as org.bluez.Error.Failed with message "le-connection-abort-by-local (36)"
        bool isError36 = false;
        if (g_error_matches(error.get(), G_IO_ERROR, G_IO_ERROR_DBUS_ERROR))
        {
            // Verify it's a D-Bus error
            if (error->domain == g_dbus_error_quark())
            {
                // Error 36 is uniquely identified by the error code "(36)" in the message
                // This is the most reliable way to detect it across BlueZ versions
                if (error->message != nullptr)
                {
                    const char * msg = error->message;
                    // Check for the error code pattern: "(36)" - this is BlueZ's way of reporting HCI error 36
                    if (strstr(msg, "(36)") != nullptr)
                    {
                        isError36 = true;
                    }
                }
            }
        }
        
        if (isError36)
        {
            error36Count++;
        }
        
        // Handle device invalidation: rediscover device
        // Trigger rediscovery on UnknownObject or after persistent error 36
        if (isUnknownObject || (isError36 && error36Count >= kError36RediscoveryThreshold && i >= kError36RediscoveryThreshold))
        {
            ChipLogError(DeviceLayer, "Device object invalidated or persistent error 36 (count: %u) - attempting rediscovery", error36Count);
            
            if (deviceAddress != nullptr)
            {
                // Try to rediscover the device (non-blocking, uses GLib event processing)
                BluezDevice1 * newDevice = RediscoverDeviceByAddress(deviceAddress);
                if (newDevice != nullptr)
                {
                    ChipLogDetail(DeviceLayer, "Device rediscovered, retrying connection with new device object");
                    // Store rediscovered device (takes ownership of the reference)
                    rediscoveredDevice.reset(newDevice);
                    currentDevice = rediscoveredDevice.get();
                    // Continue retry loop with new device object
                    continue;
                }
                else
                {
                    ChipLogError(DeviceLayer, "Failed to rediscover device %s", deviceAddress);
                    break;
                }
            }
            else
            {
                ChipLogError(DeviceLayer, "Cannot rediscover device - address unknown");
                break;
            }
        }
        
        if (!g_error_matches(error.get(), G_IO_ERROR, G_IO_ERROR_DBUS_ERROR))
        {
            // Non-DBUS error, break
            break;
        }

        ChipLogProgress(DeviceLayer, "ConnectDevice retry: %u out of %u", i + 1, kMaxConnectRetries);
        
        // Ensure device is disconnected before retry attempt
        // This clears any stale connection state
        bluez_device1_call_disconnect_sync(currentDevice, nullptr, nullptr);
        
        if (i > 0)
        {
            // Re-verify adapter readiness before retry
            err = VerifyAdapterReadiness();
            if (err != CHIP_NO_ERROR)
            {
                ChipLogError(DeviceLayer, "Adapter not ready before retry: %" CHIP_ERROR_FORMAT, err.Format());
                // Continue retry loop, may succeed on next attempt
            }
		
            // For error 36, use longer delay to allow BlueZ to fully stabilize
            // This is critical for error 36 (le-connection-abort-by-local) recovery
            uint32_t delayMs = isError36 ? (kRetryDelayMs * 2) : kRetryDelayMs;
            ChipLogDetail(DeviceLayer, "Waiting %u ms before retry to allow BlueZ to stabilize", delayMs);
            usleep(delayMs * 1000);		
        }
    }

    BLEManagerImpl::HandleConnectFailed(CHIP_ERROR_INTERNAL);
    return CHIP_ERROR_INTERNAL;
}

CHIP_ERROR BluezEndpoint::ConnectDevice(BluezDevice1 & aDevice)
{
    // Add delay after device discovery to allow BlueZ to stabilize
    // This mitigates error 36 (le-connection-abort-by-local) that occurs
    // when connecting immediately after device discovery
    constexpr uint32_t kPostDiscoveryConnectDelayMs = 300;  // Increased from 200ms for better stability
    ChipLogDetail(DeviceLayer, "Waiting %u ms after device discovery before connecting", kPostDiscoveryConnectDelayMs);
    usleep(kPostDiscoveryConnectDelayMs * 1000);
	
    auto params = std::make_pair(this, &aDevice);
    mConnectCancellable.reset(g_cancellable_new());
    return PlatformMgrImpl().GLibMatterContextInvokeSync(
        +[](decltype(params) * aParams) { return aParams->first->ConnectDeviceImpl(*aParams->second); }, &params);
}

void BluezEndpoint::CancelConnect()
{
    g_cancellable_cancel(mConnectCancellable.get());
    mConnectCancellable.reset();
}

} // namespace Internal
} // namespace DeviceLayer
} // namespace chip
