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

#ifndef OMI_SERVICE_HPP_
#define OMI_SERVICE_HPP_

#include <thread>
#include <vector>
#include <gio/gio.h>
#include <glib.h>
#include "mntfsimg.hpp"
#include "omi_dbus_api.h"

namespace omi
{
class OmiService
{
struct st_mount
{
    std::string id;
    std::string rootfs_path;
};

using Mount = struct st_mount;

public:
    OmiService();
    ~OmiService();
    OmiService(const OmiService&) = delete;
    OmiService& operator=(OmiService const&) = delete;
    OmiService(const OmiService&&) = delete;
    OmiService& operator=(OmiService const&&) = delete;
    int Run();
private:
    static gboolean OnMount(Omi1* object,
                            GDBusMethodInvocation* invocation,
                            const gchar* arg_id,
                            const gchar* arg_rootfs_path,
                            const gchar* arg_config_json_path,
                            gpointer user_data);

    static gboolean OnUnmount(Omi1* object,
                              GDBusMethodInvocation* invocation,
                              const gchar* arg_id,
                              gpointer user_data);

    static void OnBusAcquired(GDBusConnection* connection,
                              const gchar* name,
                              gpointer user_data);

    static void OnNameAcquired(GDBusConnection* connection,
                               const gchar* name,
                               gpointer user_data);

    static void OnNameLost(GDBusConnection* connection,
                           const gchar* name,
                           gpointer user_data);

    static void OnDestroyNotify(gpointer user_data);

    static void OnDmVerityError(const char* device,
                                void* user_data);

    void Shutdown();

    bool ChangeRoot();

    guint m_owner_id;
    GMainLoop* m_loop;
    Omi1* m_omi1_skeleton;
    std::thread m_shutdown_thread;
    std::vector<Mount> m_mounts;
    mntfsimg::ImageMounter m_mounter;
};
} // namespace omi

#endif // #ifdef OMI_SERVICE_HPP_

