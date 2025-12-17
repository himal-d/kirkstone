/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2021 Liberty Global B.V.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <algorithm>
#include <functional>
#include <cstring>
#include <cerrno>
#include <string>
#include <thread>
#include <gio/gio.h>
#include <glib.h>
#include <signal.h>
#include <unistd.h>
#include <dropprivileges/dropprivileges.h>
#include "omi_dbus_api.h"
#include "omi_log.hpp"
#include "omi_mount.hpp"
#include "omi_service.hpp"
#include "omi_unmount.hpp"

namespace omi
{
gboolean OmiService::OnMount(Omi1* object,
                             GDBusMethodInvocation* invocation,
                             const gchar* arg_id,
                             const gchar* arg_rootfs_path,
                             const gchar* arg_config_json_path,
                             gpointer user_data)
{
    std::string container_path;
    std::string errmsg;
    OmiService* self = static_cast<OmiService*>(user_data);

    // If id already in use reject the Mount request

    auto id_in_use = [&arg_id](const Mount& mount){ return arg_id == mount.id; };

    auto id_search_iter = std::find_if(self->m_mounts.cbegin(),
                                       self->m_mounts.cend(),
                                       id_in_use);

    if (id_search_iter != self->m_mounts.cend())
    {
        g_dbus_method_invocation_return_dbus_error(invocation,
                                                   "com.lgi.onemw.omi1.Error.IdInUse",
                                                   "Container ID in use");

        return TRUE;
    }

    // If rootfs_path already in use reject the Mount request

    auto rootfs_path_in_use = [&arg_rootfs_path](const Mount& mount){ return arg_rootfs_path == mount.rootfs_path; };

    auto rootfs_path_search_iter = std::find_if(self->m_mounts.cbegin(),
                                                self->m_mounts.cend(),
                                                rootfs_path_in_use);

    if (rootfs_path_search_iter != self->m_mounts.cend())
    {
        g_dbus_method_invocation_return_dbus_error(invocation,
                                                   "com.lgi.onemw.omi1.Error.BundleInUse",
                                                   "Bundle rootfs in use");

        return TRUE;
    }

    int rv = DoMount(self->m_mounter,
                     arg_id,
                     arg_rootfs_path,
                     arg_config_json_path,
                     container_path,
                     errmsg);

    if (rv == 0)
    {
        // Add mount to used list
        Mount mnt = {arg_id, arg_rootfs_path};
        self->m_mounts.push_back(mnt);
        omi1_complete_mount(object, invocation, container_path.c_str());
    }
    else
    {
        g_dbus_method_invocation_return_dbus_error(invocation,
                                                   "com.lgi.onemw.omi1.Error.MountFailed",
                                                   errmsg.c_str());
    }

    return TRUE;
}

gboolean OmiService::OnUnmount(Omi1* object,
                               GDBusMethodInvocation* invocation,
                               const gchar* arg_id,
                               gpointer user_data)
{
    OmiService* self = static_cast<OmiService*>(user_data);
    std::string errmsg;

    // If id not found reject the Un-mount request

    auto id_in_use = [&arg_id](const Mount& mount){ return arg_id == mount.id; };

    auto id_search_iter = std::find_if(self->m_mounts.cbegin(),
                                       self->m_mounts.cend(),
                                       id_in_use);

    if (id_search_iter == self->m_mounts.cend())
    {
        g_dbus_method_invocation_return_dbus_error(invocation,
                                                   "com.lgi.onemw.omi1.Error.IdNotFound",
                                                   "Container ID not found");

        return TRUE;
    }

    int rv = DoUnmount(self->m_mounter, arg_id, errmsg);

    if (rv == 0)
    {
        // Remove mount from used list
        self->m_mounts.erase(id_search_iter);
        omi1_complete_umount(object, invocation);
    }
    else
    {
        g_dbus_method_invocation_return_dbus_error(invocation,
                                                   "com.lgi.onemw.omi1.Error.UnmountFailed",
                                                   errmsg.c_str());
    }

    return TRUE;
}

void OmiService::OnBusAcquired(GDBusConnection* connection,
                               const gchar* name,
                               gpointer user_data)
{
    Log::info("%s: connection: %p, name: %s, user_data: %p", __FUNCTION__, connection, name, user_data);
    OmiService* self = static_cast<OmiService*>(user_data);
    self->m_omi1_skeleton = omi1_skeleton_new();
    g_signal_connect(self->m_omi1_skeleton, "handle-mount", G_CALLBACK(OnMount), user_data);
    g_signal_connect(self->m_omi1_skeleton, "handle-umount", G_CALLBACK(OnUnmount), user_data);

    GError* error = NULL;
    gboolean status = g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(self->m_omi1_skeleton),
                                                       connection,
                                                       "/com/lgi/onemw/omi1",
                                                       &error);
    if (status == FALSE)
    {
        Log::fatal("%s: g_dbus_interface_skeleton_export: %s", __FUNCTION__, error->message);
        g_error_free(error);
        g_main_loop_quit(self->m_loop);
    }
}

void OmiService::OnNameAcquired(GDBusConnection* connection,
                                const gchar* name,
                                gpointer user_data)
{
    Log::info("%s: connection: %p, name: %s, user_data: %p", __FUNCTION__, connection, name, user_data);
}

void OmiService::OnNameLost(GDBusConnection* connection,
                            const gchar* name,
                            gpointer user_data)
{
    Log::info("%s: connection: %p, name: %s, user_data: %p", __FUNCTION__, connection, name, user_data);
}

void OmiService::OnDestroyNotify(gpointer user_data)
{
    Log::info("%s: user_data: %p", __FUNCTION__, user_data);
    OmiService* self = static_cast<OmiService*>(user_data);
    g_main_loop_quit(self->m_loop);
}

void OmiService::OnDmVerityError(const char* device,
                                 void* user_data)
{
    Log::error("%s: %s failed", __FUNCTION__, device);
    OmiService* self = static_cast<OmiService*>(user_data);
    char prefix[] = "vdac-dec-";

    // Extract container ID from device name
    if (strncmp(device, prefix, sizeof prefix - 1) != 0)
    {
        Log::warning("%s: Invalid device name", __FUNCTION__);
    }
    else
    {
        std::string id(&device[9]);
        auto id_in_use = [&id](const Mount& mount){ return id == mount.id; };

        auto id_search_iter = std::find_if(self->m_mounts.cbegin(),
                                           self->m_mounts.cend(),
                                           id_in_use);

        if (id_search_iter != self->m_mounts.cend())
        {
            omi1_emit_verity_failed(self->m_omi1_skeleton, id.c_str());
        }
        else
        {
            Log::warning("%s: Unused container ID in device name", __FUNCTION__);
        }
    }

}

OmiService::OmiService():
    m_owner_id(0),
    m_loop(NULL),
    m_omi1_skeleton(NULL),
    m_mounter(OnDmVerityError, this)
{
    Log::info("%s: user_data: %p", __FUNCTION__, this);
}

OmiService::~OmiService()
{
    Log::info("%s: user_data: %p", __FUNCTION__, this);
}

void OmiService::Shutdown()
{
    int signum;
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGTERM);
    Log::info("%s: Waiting for SIGTERM", __FUNCTION__);
    sigwait(&sigset, &signum);
    Log::info("%s: signum: %d", __FUNCTION__, signum);

    // When processing D-Bus traffic is complete
    // OnNotifyDestroy will quit the main loop
    g_bus_unown_name(m_owner_id);
}

bool OmiService::ChangeRoot()
{
    const char* omi_user = getenv("OMI_USER");
    if (!omi_user)
    {
        Log::error("%s: Failed to obtain omi user from OMI_USER", __FUNCTION__);
        return false;
    }

    const char* sandbox_path = getenv("OMI_SANDBOX_PATH");
    if (!sandbox_path)
    {
        Log::error("%s: Failed to obtain new chroot from OMI_SANDBOX_PATH", __FUNCTION__);
        return false;
    }

    Log::info("%s: Changing root to '%s'", __FUNCTION__, sandbox_path);
    int rv = chroot(sandbox_path);
    if (rv != 0) {
        Log::error("%s: Failed to change root: %s", __FUNCTION__, strerror(errno));
        return false;
    }

    Log::info("%s: Changing user to '%s' and droping root privileges", __FUNCTION__, omi_user);
    cap_value_t caps[] = {CAP_SYS_ADMIN};
    rv = drop_root_privileges(omi_user, caps, sizeof(caps)/sizeof(caps[0]));
    if (rv < 0)
    {
        Log::error("%s: Failed to drop privileges: %d", __FUNCTION__, rv);
        return false;
    }

    return true;
}

int OmiService::Run()
{
    Log::info("%s: user_data: %p", __FUNCTION__, this);

    if (!ChangeRoot())
    {
        return -1;
    }

    m_loop = g_main_loop_new(NULL, FALSE);

    m_owner_id = g_bus_own_name(G_BUS_TYPE_SESSION,
                                "com.lgi.onemw.omi1",
                                G_BUS_NAME_OWNER_FLAGS_NONE,
                                OnBusAcquired,
                                OnNameAcquired,
                                OnNameLost,
                                this,
                                OnDestroyNotify);

    m_shutdown_thread = std::thread(std::bind(&OmiService::Shutdown, this));
    m_shutdown_thread.detach();

    Log::info("%s: Starting main event loop", __FUNCTION__);
    g_main_loop_run(m_loop);
    g_main_loop_unref(m_loop);
    return 0;
}
} // namespace omi

