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
#include <cstring>
#include <algorithm>
#include <sys/stat.h>
#include <dirent.h>
#include <fstream>

using namespace std;

static bool is_number(const char *s_str) {
    return (s_str && (strspn(s_str, "0123456789") == strlen(s_str)));
}

static std::string &trim(std::string &str) {
    auto it1 = std::find_if(str.rbegin(), str.rend(),
                            [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); });
    str.erase(it1.base(), str.end());
    return str;
}

static bool readFromFile(unsigned int pid, pidmap::proc_map_t &proc_map) {
    char state;
    unsigned int ppid;
    pidmap::proc_t proc;
    bool status = false;
    string stat_file_path(string("/proc/").append(to_string(pid)).append("/stat"));
    string cmd_line_file_path(string("/proc/").append(to_string(pid)).append("/cmdline"));

    try {
      ifstream statFile(stat_file_path);
      if (statFile) {
          unsigned int p;
          statFile >> p;
          statFile >> proc.cmdline;
          statFile >> state;
          statFile >> ppid;

          if (statFile.good()) {
              ifstream cmdlineFile(cmd_line_file_path);
              if (cmdlineFile) {
                  string cmdline;
                  char c;

                  while (!cmdlineFile.eof()) {
                      cmdlineFile >> c;
                      if (c != 0) {
                          cmdline.append(1, c);
                      } else {
                          cmdline.append(1, ' ');
                      }
                  }

                  if (!trim(cmdline).empty()) {
                      proc.cmdline = cmdline;
                  }
                  proc.pid = pid;

                  proc_map[ppid].push_back(proc);
                  status = true;
              } else {
                  //DBG("Could not open " << cmd_line_file_path);
              }
          } else {
              //DBG("Could not read from stat file");
          }
      } else {
          //DBG("Could not open " << stat_file_path);
      }
    } catch (const exception &ex) {
        // sometimes an exception happens when reading stat file
        // catch and ignore here
        //DBG("Caught and ignored rogue exception: " << ex.what());
    }

    return status;
}

bool compare(pidmap::proc_t& proc, string child_name) {
  auto match = false;
  auto wildcard_pos = child_name.find("*");
  if (wildcard_pos != std::string::npos) {
    // if wildcard then match chars only up to wildcard
    match = proc.cmdline.compare(0, wildcard_pos, child_name, 0, wildcard_pos) == 0;
  } else {
    // when no wildcard: either the cmdline matches exactly with the child_name OR
    // it starts with child_name followed by a space
    match = ((proc.cmdline.compare(child_name) == 0) ||
        (proc.cmdline.find(child_name + " ") == 0));
  }
  return match;
}

namespace pidmap {

    bool findChild(proc_map_t &proc_map, pid_t pid, string child_name, pid_t &child_pid,
                   int level) {
      //DBG_CODE(string space;)
      bool found = false;
      //DBG_CODE(space.append(level * 2, ' ');)
      if (proc_map.find(pid) != proc_map.end()) {
        for (auto proc : proc_map[pid]) {
          //DBG(space << "check [" << proc.cmdline << "][" << proc.pid << "]");
          auto match = compare(proc, child_name);
          if (match) {
            child_pid = proc.pid;
            //DBG("Child process has been found");
            found = true;
            break;
          }
          found = findChild(proc_map, proc.pid, child_name, child_pid, level + 1);
          if (found) {
            break;
          }
        }
      }
      return found;
    }

    bool findProcess(proc_map_t &proc_map, pid_t &pid, const string &name) {
      bool found = false;
      bool end = false;
      for (auto item : proc_map) { /*check also if current pid meets requiments*/
        for (auto proc : item.second) {
          if (proc.pid == pid) {
            found = compare(proc, name);
            end = true;
            break;
          }
        }
        if (end) {
          break;
        }
      }

      return found;
    }

    bool loadProcMap(proc_map_t &proc_map) {
      bool result = false;
      pid_list_t pids;
      DIR *dir_ptr = opendir("/proc");

      if (dir_ptr) {
        rewinddir(dir_ptr);
        struct dirent *ent_ptr = readdir(dir_ptr);

        while (ent_ptr) {
          if (is_number(ent_ptr->d_name)) {
            pids.push_back(strtoul(ent_ptr->d_name, NULL, 10));
          }
          ent_ptr = readdir(dir_ptr);
        }
        result = true;
        closedir(dir_ptr);
      }

      proc_map.clear();
      for (auto i : pids) {
        readFromFile(i, proc_map);
      }

      return result;
    }

}
