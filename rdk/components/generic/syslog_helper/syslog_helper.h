/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2018 RDK Management
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


#ifndef _SYSLOG_HELPER_H_
#define __SYSLOG_HELPER_H_

#include <iostream>
#include <mutex>
#include <string>
#include "syslog_helper_ifc.h"

using namespace std;

const int  max_message_length = 4096;
const int  max_hostname_length = 32;
const char* socket_stream_path = "/run/systemd/journal/syslog";
extern const char *__progname;
mutex log_mutex;

class syslog_helper
{
private:
    char log_buf[max_message_length+1];
    static syslog_helper *syslog_instance;
    int soc_fd;
    struct sockaddr_un client_addr;
    char hostname[max_hostname_length+1];
    string progname;
    int pid;
    
    syslog_helper();

public:
    static syslog_helper* get_instance();
    void send_data(const char* data);
    virtual ~syslog_helper();
};

#endif// __SYSLOG_HELPER_H_
