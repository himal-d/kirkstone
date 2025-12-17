/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2022 Sky
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 * Copyright 2022 RDK Management
 * Licensed under the Apache License, Version 2.0
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <experimental/filesystem>
#include "mocks/cellular_sm_mock.h"
#include "cellmgr_mock.h"
#define MOCK_CELLULAR_RBUS_EVENTS
#define MOCK_CELLULAR_API

extern "C"
{
#include "cellularmgr_sm.h"
#include "cellular_hal.h"
#include "cellularmgr_cellular_apis.h"
#include "cellular_hal_qmi_apis.h"
INT sysevent_fd;
token_t sysevent_token;
}

using namespace std;
using std::experimental::filesystem::exists;
using ::testing::_;
using ::testing::Return;
using ::testing::StrEq;

extern SMPThreadMock * g_SMPThreadMock;

CellularMgrPolicyCtrlSMStruct *gpstCellularPolicyCtrl = NULL, ctx;
extern char         g_Subsystem[32];
CellularMgrSMInputStruct  pstInput;

TEST (SMDevRemStatus_1, CellularMgrDeviceRemovedStatusCBForSM)
{

        EXPECT_EQ(RETURN_ERROR, CellularMgrDeviceRemovedStatusCBForSM(NULL, DEVICE_DETECTED));
        EXPECT_EQ(RETURN_ERROR, CellularMgrDeviceRemovedStatusCBForSM(NULL, DEVICE_REMOVED));
}


TEST_F (CellularManagerTestFixture, CellularMgrDeviceRemovedStatusCBForSM)
{
        char device_name[] = "cdc-wdm0";
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrDeviceRemovedStatusCBForSM(device_name,DEVICE_DETECTED));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enDeviceDetectionStatus, DEVICE_DETECTED);
}


TEST_F (CellularManagerTestFixture, CellularMgrDeviceRemovedStatusCBForSM2)
{
        char device_name[] = "cdc-wdm0";
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrDeviceRemovedStatusCBForSM(device_name,DEVICE_REMOVED));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enDeviceDetectionStatus, DEVICE_REMOVED);
}


TEST (SMDevSlotStatus_1, CellularMgrDeviceSlotStatusCBForSM)
{
        EXPECT_EQ(RETURN_ERROR, CellularMgrDeviceSlotStatusCBForSM(NULL,NULL,1,DEVICE_SLOT_STATUS_NOT_READY));
        EXPECT_EQ(RETURN_ERROR, CellularMgrDeviceSlotStatusCBForSM(NULL,NULL,2,DEVICE_SLOT_STATUS_NOT_READY));
        EXPECT_EQ(RETURN_ERROR, CellularMgrDeviceSlotStatusCBForSM(NULL,NULL,2,DEVICE_SLOT_STATUS_SELECTING));
        EXPECT_EQ(RETURN_ERROR, CellularMgrDeviceSlotStatusCBForSM("slot1",NULL,1,DEVICE_SLOT_STATUS_NOT_READY));
        EXPECT_EQ(RETURN_ERROR, CellularMgrDeviceSlotStatusCBForSM(NULL,"logical_slot1",1,DEVICE_SLOT_STATUS_SELECTING));
        EXPECT_EQ(RETURN_ERROR, CellularMgrDeviceSlotStatusCBForSM(NULL,"logical_slot2",1,DEVICE_SLOT_STATUS_READY));
        EXPECT_EQ(RETURN_ERROR, CellularMgrDeviceSlotStatusCBForSM("slot2",NULL,1,DEVICE_SLOT_STATUS_SELECTING));
}

TEST_F (CellularManagerTestFixture, CellularMgrDeviceSlotStatusCBForSM)
{
        char slot_name[] = "slot1";
        char slot_type[] = "logical_slot1";
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrDeviceSlotStatusCBForSM(slot_name,slot_type,1,DEVICE_SLOT_STATUS_NOT_READY));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enDeviceSlotSelectionStatus, DEVICE_SLOT_STATUS_NOT_READY);
        EXPECT_EQ(ctx.SelectedSlotNumber, 1);
}

TEST_F (CellularManagerTestFixture, CellularMgrDeviceSlotStatusCBForSM2)
{
        char slot_name[] = "slot2";
        char slot_type[] = "logical_slot2";
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrDeviceSlotStatusCBForSM(slot_name,slot_type,2,DEVICE_SLOT_STATUS_SELECTING));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enDeviceSlotSelectionStatus, DEVICE_SLOT_STATUS_SELECTING);
        EXPECT_EQ(ctx.SelectedSlotNumber, 2);
}

TEST_F (CellularManagerTestFixture, CellularMgrDeviceSlotStatusCBForSM3)
{
        char slot_name[] = "slot1";
        char slot_type[] = "logical_slot2";
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrDeviceSlotStatusCBForSM(slot_name,slot_type,2,DEVICE_SLOT_STATUS_READY));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enDeviceSlotSelectionStatus, DEVICE_SLOT_STATUS_READY);
        EXPECT_EQ(ctx.SelectedSlotNumber, 2);
}

TEST_F (CellularManagerTestFixture, CellularMgrDeviceSlotStatusCBForSM4)
{
        char slot_name[] = "slot2";
        char slot_type[] = "logical_slot1";
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrDeviceSlotStatusCBForSM(slot_name,slot_type,1,DEVICE_SLOT_STATUS_READY));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enDeviceSlotSelectionStatus, DEVICE_SLOT_STATUS_READY);
        EXPECT_EQ(ctx.SelectedSlotNumber, 1);
}


TEST (SMProfileStatus, CellularMgrProfileStatusCBForSM)
{
        EXPECT_EQ(RETURN_ERROR, CellularMgrProfileStatusCBForSM(NULL,CELLULAR_PDP_TYPE_IPV4,DEVICE_PROFILE_STATUS_NOT_READY));
        EXPECT_EQ(RETURN_ERROR, CellularMgrProfileStatusCBForSM(NULL,CELLULAR_PDP_TYPE_IPV6,DEVICE_PROFILE_STATUS_CONFIGURING));
        EXPECT_EQ(RETURN_ERROR, CellularMgrProfileStatusCBForSM(NULL,CELLULAR_PDP_TYPE_IPV4_OR_IPV6,DEVICE_PROFILE_STATUS_READY));
        EXPECT_EQ(RETURN_ERROR, CellularMgrProfileStatusCBForSM(NULL,CELLULAR_PDP_TYPE_IPV4,DEVICE_PROFILE_STATUS_READY));
        EXPECT_EQ(RETURN_ERROR, CellularMgrProfileStatusCBForSM(NULL,CELLULAR_PDP_TYPE_IPV6,DEVICE_PROFILE_STATUS_NOT_READY));
        EXPECT_EQ(RETURN_ERROR, CellularMgrProfileStatusCBForSM(NULL,CELLULAR_PDP_TYPE_PPP,DEVICE_PROFILE_STATUS_DELETED));
        EXPECT_EQ(RETURN_ERROR, CellularMgrProfileStatusCBForSM(NULL,CELLULAR_PDP_TYPE_IPV4_OR_IPV6,DEVICE_PROFILE_STATUS_DELETED));
        EXPECT_EQ(RETURN_ERROR, CellularMgrProfileStatusCBForSM(NULL,CELLULAR_PDP_TYPE_IPV4_OR_IPV6,DEVICE_PROFILE_STATUS_CONFIGURING));
}

TEST_F (CellularManagerTestFixture, CellularMgrProfileStatusCBForSM)
{
        char profile_name[] = "DefaultProfile";
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrProfileStatusCBForSM(profile_name,CELLULAR_PDP_TYPE_IPV4_OR_IPV6,DEVICE_PROFILE_STATUS_READY));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enDeviceProfileSelectionStatus, DEVICE_PROFILE_STATUS_READY);
        EXPECT_EQ(ctx.enPDPTypeForSelectedProfile, CELLULAR_PDP_TYPE_IPV4_OR_IPV6);

}

TEST_F (CellularManagerTestFixture, CellularMgrProfileStatusCBForSM2)
{
        char profile_name[] = "DefaultProfile";
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrProfileStatusCBForSM(profile_name,CELLULAR_PDP_TYPE_IPV4,DEVICE_PROFILE_STATUS_NOT_READY));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enDeviceProfileSelectionStatus, DEVICE_PROFILE_STATUS_NOT_READY);
        EXPECT_EQ(ctx.enPDPTypeForSelectedProfile, CELLULAR_PDP_TYPE_IPV4);
}
TEST_F (CellularManagerTestFixture, CellularMgrProfileStatusCBForSM3)
{
        char profile_name[] = "DefaultProfile";
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrProfileStatusCBForSM(profile_name,CELLULAR_PDP_TYPE_IPV4,DEVICE_PROFILE_STATUS_CONFIGURING));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enDeviceProfileSelectionStatus, DEVICE_PROFILE_STATUS_CONFIGURING);
        EXPECT_EQ(ctx.enPDPTypeForSelectedProfile, CELLULAR_PDP_TYPE_IPV4);
}

TEST (SMGetNetReg, CellularMgrGetNetworkRegisteredService)
{
        EXPECT_EQ(RETURN_ERROR, CellularMgrGetNetworkRegisteredService(NULL));

}


TEST_F (CellularManagerTestFixture, CellularMgrGetNetworkRegisteredService)
{
        CELLULAR_INTERFACE_REGISTERED_SERVICE_TYPE penRegisteredService;
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrGetNetworkRegisteredService(&penRegisteredService));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enRegisteredService, penRegisteredService);
}

TEST_F (CellularManagerTestFixture, CellularMgrPacketServiceStatusCBForSM)
{
        char device_name[] = "cdc-wdm0";
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrPacketServiceStatusCBForSM(device_name,CELLULAR_NETWORK_IP_FAMILY_IPV4,DEVICE_NETWORK_STATUS_DISCONNECTED));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enNetworkIPv4PacketServiceStatus, DEVICE_NETWORK_STATUS_DISCONNECTED);
        EXPECT_EQ(ctx.bIPv4NetworkStartInProgress, FALSE);
        EXPECT_EQ(ctx.bIPv4WaitingForPacketStatus, FALSE);
}

TEST_F (CellularManagerTestFixture, CellularMgrPacketServiceStatusCBForSM3)
{
        char device_name[] = "cdc-wdm0";
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrPacketServiceStatusCBForSM(device_name,CELLULAR_NETWORK_IP_FAMILY_IPV6,DEVICE_NETWORK_STATUS_DISCONNECTED));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enNetworkIPv6PacketServiceStatus, DEVICE_NETWORK_STATUS_DISCONNECTED);
        EXPECT_EQ(ctx.bIPv4NetworkStartInProgress, FALSE);
        EXPECT_EQ(ctx.bIPv4WaitingForPacketStatus, FALSE);
}


TEST_F (CellularManagerTestFixture, CellularMgrDeviceRegistrationStatusCBForSM)
{
        CellularDeviceNASStatus_t device_registration_status = DEVICE_NAS_STATUS_NOT_REGISTERED;
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrDeviceRegistrationStatusCBForSM(device_registration_status,DEVICE_NAS_STATUS_ROAMING_ON,CELLULAR_MODEM_REGISTERED_SERVICE_PS));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enDeviceNASRegisterStatus, DEVICE_NAS_STATUS_NOT_REGISTERED);
}


TEST_F (CellularManagerTestFixture, CellularMgrDeviceRegistrationStatusCBForSM2)
{
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK,CellularMgrDeviceRegistrationStatusCBForSM(DEVICE_NAS_STATUS_REGISTERED,DEVICE_NAS_STATUS_ROAMING_ON,CELLULAR_MODEM_REGISTERED_SERVICE_PS));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enDeviceNASRegisterStatus, DEVICE_NAS_STATUS_REGISTERED);
        EXPECT_EQ(ctx.enDeviceNASRoamingStatus, DEVICE_NAS_STATUS_ROAMING_ON);
        EXPECT_EQ(ctx.enRegisteredService, CELLULAR_MODEM_REGISTERED_SERVICE_PS);

}

TEST_F (CellularManagerTestFixture, CellularMgrDeviceRegistrationStatusCBForSM3)
{
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK,CellularMgrDeviceRegistrationStatusCBForSM(DEVICE_NAS_STATUS_REGISTERED,DEVICE_NAS_STATUS_ROAMING_OFF,CELLULAR_MODEM_REGISTERED_SERVICE_CS));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enDeviceNASRegisterStatus, DEVICE_NAS_STATUS_REGISTERED);
        EXPECT_EQ(ctx.enDeviceNASRoamingStatus, DEVICE_NAS_STATUS_ROAMING_OFF);
        EXPECT_EQ(ctx.enRegisteredService, CELLULAR_MODEM_REGISTERED_SERVICE_CS);

}

TEST_F (CellularManagerTestFixture, CellularMgrDeviceRegistrationStatusCBForSM4)
{
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK,CellularMgrDeviceRegistrationStatusCBForSM(DEVICE_NAS_STATUS_REGISTERED,DEVICE_NAS_STATUS_ROAMING_OFF,CELLULAR_MODEM_REGISTERED_SERVICE_CS_PS));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(ctx.enDeviceNASRegisterStatus, DEVICE_NAS_STATUS_REGISTERED);
        EXPECT_EQ(ctx.enDeviceNASRoamingStatus, DEVICE_NAS_STATUS_ROAMING_OFF);
        EXPECT_EQ(ctx.enRegisteredService, CELLULAR_MODEM_REGISTERED_SERVICE_CS_PS);

}

TEST_F (CellularManagerTestFixture, CellularMgrDeviceRegistrationStatusCBForSM5)
{
        CellularDeviceNASStatus_t device_registration_status = DEVICE_NAS_STATUS_NOT_REGISTERED;
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrDeviceRegistrationStatusCBForSM(device_registration_status,DEVICE_NAS_STATUS_ROAMING_ON,CELLULAR_MODEM_REGISTERED_SERVICE_PS));
        Cellular_get_sm_ctx(&ctx);
        ctx.enDeviceNASRegisterStatus=DEVICE_NAS_STATUS_REGISTERED;
        EXPECT_EQ(ctx.enDeviceNASRegisterStatus, DEVICE_NAS_STATUS_REGISTERED);
        EXPECT_EQ(device_registration_status, DEVICE_NAS_STATUS_NOT_REGISTERED);
        ctx.enDeviceNASRegisterStatus = DEVICE_NAS_STATUS_REGISTERING;
        EXPECT_EQ(ctx.enDeviceNASRegisterStatus, DEVICE_NAS_STATUS_REGISTERING);
}

TEST (SMGetCurrentPDPCon, CellularMgrGetCurrentPDPContextStatusInformation)
{
        EXPECT_EQ(RETURN_ERROR, CellularMgrGetCurrentPDPContextStatusInformation(NULL));
}

TEST_F (CellularManagerTestFixture, CellularMgrGetCurrentPDPContextStatusInformation)
{
        CELLULAR_INTERFACE_CONTEXTPROFILE_INFO  pstContextProfileInfo;
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrGetCurrentPDPContextStatusInformation(&pstContextProfileInfo));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(pstContextProfileInfo.Type, CONTEXTPROFILE_TYPE_DEFAULT);
        EXPECT_EQ(pstContextProfileInfo.Status, CONTEXTPROFILE_STATUS_INACTIVE);
        EXPECT_EQ(pstContextProfileInfo.IpAddressFamily, INTERFACE_PROFILE_FAMILY_IPV4_IPV6);
}

TEST_F (CellularManagerTestFixture, CellularMgrGetCurrentPDPContextStatusInformation2)
{
        CELLULAR_INTERFACE_CONTEXTPROFILE_INFO  pstContextProfileInfo;
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrGetCurrentPDPContextStatusInformation(&pstContextProfileInfo));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(pstContextProfileInfo.Type, CONTEXTPROFILE_TYPE_DEFAULT);
        ctx.enCurrentSMState = CELLULAR_STATE_CONNECTED;
        pstContextProfileInfo.Status = CONTEXTPROFILE_STATUS_ACTIVE;
        EXPECT_EQ(pstContextProfileInfo.Status, CONTEXTPROFILE_STATUS_ACTIVE);
        ctx.enPDPTypeForSelectedProfile = CELLULAR_PDP_TYPE_IPV4;
        pstContextProfileInfo.IpAddressFamily = INTERFACE_PROFILE_FAMILY_IPV4;
        EXPECT_EQ(pstContextProfileInfo.IpAddressFamily, INTERFACE_PROFILE_FAMILY_IPV4);
}

TEST_F (CellularManagerTestFixture, CellularMgrGetCurrentPDPContextStatusInformation3)
{
        CELLULAR_INTERFACE_CONTEXTPROFILE_INFO  pstContextProfileInfo;
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrGetCurrentPDPContextStatusInformation(&pstContextProfileInfo));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(pstContextProfileInfo.Type, CONTEXTPROFILE_TYPE_DEFAULT);
        ctx.enCurrentSMState = CELLULAR_STATE_CONNECTED;
        pstContextProfileInfo.Status = CONTEXTPROFILE_STATUS_ACTIVE;
        EXPECT_EQ(pstContextProfileInfo.Status, CONTEXTPROFILE_STATUS_ACTIVE);
        ctx.enPDPTypeForSelectedProfile = CELLULAR_PDP_TYPE_IPV6;
        pstContextProfileInfo.IpAddressFamily = INTERFACE_PROFILE_FAMILY_IPV6;
        EXPECT_EQ(pstContextProfileInfo.IpAddressFamily, INTERFACE_PROFILE_FAMILY_IPV6);
}

TEST_F (CellularManagerTestFixture, CellularMgrGetCurrentPDPContextStatusInformation4)
{
        CELLULAR_INTERFACE_CONTEXTPROFILE_INFO  pstContextProfileInfo;
        EXPECT_CALL(*g_SMPThreadMock, pthread_create(_,_,_,_))
                .Times(1)
                .WillOnce(::testing::Return(0));
        CellularMgr_Start_State_Machine(&pstInput);
        EXPECT_EQ(RETURN_OK, CellularMgrGetCurrentPDPContextStatusInformation(&pstContextProfileInfo));
        Cellular_get_sm_ctx(&ctx);
        EXPECT_EQ(pstContextProfileInfo.Type, CONTEXTPROFILE_TYPE_DEFAULT);
        ctx.enCurrentSMState = CELLULAR_STATE_CONNECTED;
        pstContextProfileInfo.Status = CONTEXTPROFILE_STATUS_ACTIVE;
        EXPECT_EQ(pstContextProfileInfo.Status, CONTEXTPROFILE_STATUS_ACTIVE);
        ctx.enPDPTypeForSelectedProfile = CELLULAR_PDP_TYPE_IPV4_OR_IPV6;
        EXPECT_EQ(pstContextProfileInfo.IpAddressFamily, INTERFACE_PROFILE_FAMILY_IPV4_IPV6);
}

TEST (SMStartSM, CellularMgr_Start_State_Machine)
{
        EXPECT_EQ(RETURN_ERROR, CellularMgr_Start_State_Machine(NULL));
}
