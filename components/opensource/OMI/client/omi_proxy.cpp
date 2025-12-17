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

#include <omi_proxy.hpp>
#include <omi_dbus_api.h>


namespace omi
{


OmiProxy::~OmiProxy()
{
    if (m_main_loop && g_main_loop_is_running(m_main_loop))
    {
        g_main_loop_quit(m_main_loop);
    }
    if (m_signal_monitor_thread.joinable())
    {
        m_signal_monitor_thread.join();
    }
    if (m_omi)
    {
        g_object_unref(m_omi);
        m_omi = nullptr;
    }
}

bool OmiProxy::mountCryptedBundle(const std::string& id,
                           const std::string& rootfs_file_path,
                           const std::string& config_json_path,
                           std::string& bundlePath /*out parameter*/)
{

    if (!init())
    {
        return false;
    }

    gchar *containerPath;

    gboolean res = omi1_call_mount_sync(m_omi,
                                        id.c_str(),
                                        rootfs_file_path.c_str(),
                                        config_json_path.c_str(),
                                        &containerPath,
                                        nullptr,
                                        nullptr);

    if (!res)
    {
        return false;
    }

    bundlePath = std::string(containerPath);

    return true;
}

bool OmiProxy::umountCryptedBundle(const std::string& id)
{
    if (!init())
    {
        return false;
    }

    return omi1_call_umount_sync(m_omi,
                                 id.c_str(),
                                 nullptr,
                                 nullptr);

}

long unsigned OmiProxy::registerListener(const OmiErrorListener &listener, const void* cbParams)
{
    if (!init())
    {
        return 0;
    }

    std::unique_lock<std::mutex> lock(m_listeners_mtx);
    m_listeners[listenerCounter] = std::make_pair(listener, cbParams);

    return listenerCounter++;
}

void OmiProxy::unregisterListener(long unsigned tag)
{
    std::unique_lock<std::mutex> lock(m_listeners_mtx);
    auto it = m_listeners.find(tag);
    if (it != m_listeners.end())
    {
        m_listeners.erase(it);
    }
}

// Private methods
bool OmiProxy::init()
{
    if (m_omi)
    {
        return true;
    }

    m_omi = omi1_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM, G_DBUS_PROXY_FLAGS_NONE,
                                        "com.lgi.onemw.omi1", "/com/lgi/onemw/omi1",
                                        nullptr, nullptr);
    if (!m_omi)
    {
        return false;
    }

    // Start monitor for incoming omi signals
    if (!startSignalMonitorThread())
    {
        return false;
    }

    return true;
}

bool OmiProxy::startSignalMonitorThread()
{
    if (m_monitor_thread_started)
    {
        return true;
    }

    std::chrono::seconds timeout{5};
    std::unique_lock<std::mutex> lock(m_signal_monitor_mtx);

    m_signal_monitor_thread = std::thread(std::bind(&OmiProxy::signalMonitorThread, this));
    m_signal_monitor_cv.wait_for(lock, timeout);
    return m_monitor_thread_started;
}

void OmiProxy::signalMonitorThread()
{
    m_main_loop = g_main_loop_new(nullptr, FALSE);

    if (!m_main_loop)
    {
        m_signal_monitor_cv.notify_one();
        return;
    }

    gulong handler_id = g_signal_connect(m_omi, "g-signal", G_CALLBACK(signalHandler), this);
    if (handler_id == 0)
    {
        m_signal_monitor_cv.notify_one();
        g_main_loop_unref(m_main_loop);
        return;
    }

    g_idle_add(notifyThreadStarted, this);

    g_main_loop_run(m_main_loop);

    {
        std::unique_lock<std::mutex> lock(m_signal_monitor_mtx);
        m_monitor_thread_started = false;
    }

    g_signal_handler_disconnect(m_omi, handler_id);
    g_main_loop_unref(m_main_loop);
}

void OmiProxy::signalHandler(GDBusProxy *proxy, gchar *sender_name, gchar *signal_name_c_str,
                             GVariant *parameters, gpointer user_data)
{
    std::string signal_name = signal_name_c_str;
    OmiProxy *self = static_cast<OmiProxy *>(user_data);

    if ("VerityFailed" == signal_name)
    {
        self->handleVerityFailed(parameters);
    }

}

void OmiProxy::handleVerityFailed(GVariant *parameters)
{
    gchar *id_c_str;

    g_variant_get(parameters, "(&s)", &id_c_str);
    std::string id{id_c_str};

    std::unique_lock<std::mutex> lock(m_listeners_mtx);
    for (const auto& el : m_listeners)
    {
        const OmiErrorListener& callback = el.second.first;
        const void* cbParams = el.second.second;
        if (callback)
        {
            callback(id, ErrorType::verityFailed, cbParams);
        }
    }
}

gboolean OmiProxy::notifyThreadStarted(gpointer user_data)
{
    OmiProxy *self = static_cast<OmiProxy *>(user_data);

    {
        std::unique_lock<std::mutex> lock(self->m_signal_monitor_mtx);
        self->m_monitor_thread_started = true;
    }

    self->m_signal_monitor_cv.notify_one();
    return FALSE;
}

} // namespace omi
