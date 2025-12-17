/*********************************************************************************
* If not stated otherwise in this file or this component's Licenses.txt file the
* following copyright and licenses apply:
*
* Copyright 2017 Liberty Global B.V.
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
*********************************************************************************/

#include "lxccpid/pidmap.h"
#include "lxccpid/lxccpiddebug.h"
#include <unistd.h>

using namespace std;

static int handleFindPid(int ppid, std::string child_name, unsigned int timeout_ms) {
    DBG("Finding child application with parent pid:" << ppid << " child_name:" << child_name << " timeout_ms:"
                                                     << timeout_ms);
    pidmap::pid_t child_pid = ppid;
    pidmap::proc_map_t proc_map;
    pidmap::loadProcMap(proc_map);
    bool found = false;
    found = pidmap::findChild(proc_map, ppid, child_name, child_pid);
    unsigned int sleep_time_ms = MIN_SLEEP_TIME_MS;
    while (!found && sleep_time_ms < timeout_ms) {
        usleep(MIN_SLEEP_TIME_MS * 1000);
        pidmap::loadProcMap(proc_map);
        found = pidmap::findChild(proc_map, ppid, child_name, child_pid);
        sleep_time_ms += MIN_SLEEP_TIME_MS;
    };
    if (found) {
        DBG("Child application pid found, ppid:" << ppid << " pid:" << child_pid);
        fprintf(stdout, "%d\n", child_pid);
    } else {
        DBG("Child application pid NOT found");
    }
    return found ? 0 : -1;
}

int main(int argc, char **argv) {
    int status = -1;

    //DBG_CODE(DBG("argc=" << argc))
    //DBG_CODE(for (int i = 0; i < argc; i++) { DBG("param:" << i << " value:[" << argv[i] << "]"); })

    if (argc > 4 && string(argv[1]) == "--ppid") {
        status = handleFindPid(atoi(argv[2]), argv[3], atoi(argv[4]));
    } else {
        DBG_CODE(cout << argv[0] << " - find process pid given parent pid and process name." << endl);
        DBG_CODE(cout << "Usage:" << endl);
        DBG_CODE(cout << argv[0] << " --ppid <parent_pid> <child_name> <timeout_ms>" << endl);
    }

    return status;
}
