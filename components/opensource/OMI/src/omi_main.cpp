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

#include <signal.h>
#include "omi_log.hpp"
#include "omi_service.hpp"

using namespace omi;

int main()
{
    Log::init();
    Log::info("OMI Entry");

    // To gracefully handle SIGTERM (on e.g. systemctl stop)
    // the signal is blocked on all threads except a dedicated
    // thread which waits for the signal and initiates shutdown
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGTERM);
    sigprocmask(SIG_BLOCK, &set, NULL);

    OmiService service;
    service.Run();
    Log::info("OMI Exit");
    return 0;
}

