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

#ifndef __LXCCPID_PIDMAP_H__
#define __LXCCPID_PIDMAP_H__

#include <string>
#include <list>
#include <map>

#define MIN_SLEEP_TIME_MS 100

using namespace std;

namespace pidmap {

    typedef unsigned int pid_t;

    typedef struct {
        pid_t pid;
        string cmdline;
    } proc_t;

    typedef map<pid_t, list<proc_t> > proc_map_t;
    typedef list<pid_t> pid_list_t;

    bool findChild(proc_map_t &proc_map, pid_t pid, string child_name, pid_t &child_pid,
                   int level = 0);

    bool findProcess(proc_map_t &proc_map, pid_t &pid, const string &name);

    bool loadProcMap(proc_map_t &proc_map);
}

#endif /* __LXCCPID_PIDMAP_H__ */
