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

#ifndef OMI_LOG_HPP_
#define OMI_LOG_HPP_

#ifdef __GNUC__
#define CHECK_PRINTF_LIKE_ARGUMENTS __attribute__((format (printf, 1, 2)))
#else
#define CHECK_PRINTF_LIKE_ARGUMENTS
#endif

#ifdef USE_RDK_LOGGER

#include <utility>
#include "rdk_debug.h"

namespace omi
{
    class Log
    {
    public:
        static constexpr auto RDK_LOG_MODULE_NAME = "LOG.RDK.OMI";

        static void init()
        {
            (void)rdk_logger_init("/etc/debug.ini");
        }

        template <typename ... TArgs>
        static void fatal(const char* format, TArgs&&... args)
        {
            RDK_LOG(RDK_LOG_FATAL, RDK_LOG_MODULE_NAME, format, std::forward<TArgs>(args)...);
        }

        template <typename ... TArgs>
        static void error(const char* format, TArgs&&... args)
        {
            RDK_LOG(RDK_LOG_ERROR, RDK_LOG_MODULE_NAME, format, std::forward<TArgs>(args)...);
        }

        template <typename ... TArgs>
        static void warning(const char* format, TArgs&&... args)
        {
            RDK_LOG(RDK_LOG_WARN, RDK_LOG_MODULE_NAME, format, std::forward<TArgs>(args)...);
        }

        template <typename ... TArgs>
        static void notice(const char* format, TArgs&&... args)
        {
            RDK_LOG(RDK_LOG_NOTICE, RDK_LOG_MODULE_NAME, format, std::forward<TArgs>(args)...);
        }

        template <typename ... TArgs>
        static void info(const char* format, TArgs&&... args)
        {
            RDK_LOG(RDK_LOG_INFO, RDK_LOG_MODULE_NAME, format, std::forward<TArgs>(args)...);
        }

        template <typename ... TArgs>
        static void debug(const char* format, TArgs&&... args)
        {
            RDK_LOG(RDK_LOG_DEBUG, RDK_LOG_MODULE_NAME, format, std::forward<TArgs>(args)...);
        }

        template <typename ... TArgs>
        static void trace(const char* format, TArgs&&... args)
        {
            RDK_LOG(RDK_LOG_TRACE1, RDK_LOG_MODULE_NAME, format, std::forward<TArgs>(args)...);
        }

    private:
    };
} // namespace omi

#else // ifdef USE_RDK_LOGGER

#include <cstdio>
#include <cstdarg>

namespace omi
{
class Log
{
public:
    static void init() {}

    template<typename ... TArgs>
    static void CHECK_PRINTF_LIKE_ARGUMENTS fatal(const char* format, ...)
    {
        va_list ap;
        va_start(ap, format);
        printMessage("FATAL", format, ap);
        va_end(ap);
    }

    static void CHECK_PRINTF_LIKE_ARGUMENTS error(const char* format, ...)
    {
        va_list ap;
        va_start(ap, format);
        printMessage("ERROR", format, ap);
        va_end(ap);
    }

    static void CHECK_PRINTF_LIKE_ARGUMENTS warning(const char* format, ...)
    {
        va_list ap;
        va_start(ap, format);
        printMessage("WARN.", format, ap);
        va_end(ap);
    }

    static void CHECK_PRINTF_LIKE_ARGUMENTS notice(const char* format, ...)
    {
        va_list ap;
        va_start(ap, format);
        printMessage("NOTIC", format, ap);
        va_end(ap);
    }

    static void CHECK_PRINTF_LIKE_ARGUMENTS info(const char* format, ...)
    {
        va_list ap;
        va_start(ap, format);
        printMessage("INFO.", format, ap);
        va_end(ap);
    }

    static void CHECK_PRINTF_LIKE_ARGUMENTS debug(const char* format, ...)
    {
        va_list ap;
        va_start(ap, format);
        printMessage("DEBUG", format, ap);
        va_end(ap);
    }

private:
    static void printMessage(const char* levelString,
                             const char* format,
                             va_list args)
    {
        static char buffer[1024];

        vsnprintf(buffer, sizeof(buffer) - 1, format, args);
        buffer[sizeof(buffer) - 1] = 0;

        printf("%s: %s\n", levelString, buffer);
        fflush(stdout);
    }
};

} // namespace omi

#endif // ifdef USE_RDK_LOGGER

#endif // #ifdef OMI_LOG_HPP_

