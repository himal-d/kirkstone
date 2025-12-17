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

#ifndef OMI_PROXY_HPP_
#define OMI_PROXY_HPP_

#include <gio/gio.h>
#include <i_omi_proxy.hpp>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <unordered_map>
#include <utility>

struct _Omi1;
typedef struct _Omi1 Omi1;

namespace omi
{

class OmiProxy : public IOmiProxy
{
public:
    OmiProxy() = default;
    virtual ~OmiProxy();

    virtual bool mountCryptedBundle(const std::string& id,
                                       const std::string& rootfs_file_path,
                                       const std::string& config_json_path,
                                       std::string& bundlePath /*out parameter*/);

    virtual bool umountCryptedBundle(const std::string& id);

    virtual long unsigned registerListener(const OmiErrorListener &listener, const void* cbParams);

    virtual void unregisterListener(long unsigned tag);

private:
    long unsigned listenerCounter{1};
    std::unordered_map<long unsigned, std::pair<OmiErrorListener, const void*>> m_listeners;
    Omi1 *m_omi{nullptr};
    bool m_monitor_thread_started{false};
    std::mutex m_signal_monitor_mtx;
    std::mutex m_listeners_mtx;
    std::thread m_signal_monitor_thread;
    GMainLoop* m_main_loop{nullptr};
    std::condition_variable m_signal_monitor_cv;
    bool startSignalMonitorThread();
    void signalMonitorThread();
    static void signalHandler(GDBusProxy *proxy, gchar *sender_name, gchar *signal_name_c_str,
                              GVariant *parameters, gpointer user_data);
    void handleVerityFailed(GVariant *parameters);
    static gboolean notifyThreadStarted(gpointer user_data);
    bool init();
};

} // namespace omi

#endif // OMI_PROXY_HPP_
