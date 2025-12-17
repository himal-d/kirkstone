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

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "syslog_helper.h"

inline syslog_helper::syslog_helper()
{
    gethostname(hostname, max_hostname_length) ;
    pid = getpid();
    progname = __progname;

    memset(log_buf, '\0', (max_message_length+1));
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, socket_stream_path, sizeof(client_addr.sun_path));

    soc_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (soc_fd <= 0)
    {
        fprintf(stderr, "[syslog_helper] : Error creating unix datagram socket - %s !!! \n", socket_stream_path);
    }
}

syslog_helper* syslog_helper::syslog_instance = NULL;

syslog_helper* syslog_helper::get_instance()
{
    if( !syslog_instance)
    {
        syslog_instance = new syslog_helper;
        fprintf(stdout, "[syslog_helper] : created new syslog object - %s \n", __progname);
    }

    return syslog_instance;
}

void syslog_helper::send_data(const char* data)
{
    struct timeval now;
    struct tm tm;
    char stamp[32];
    int tslen = 0;
    int len = 0;
    
    gettimeofday(&now, NULL);
    gmtime_r(&now.tv_sec, &tm);

    tslen = strftime(stamp, sizeof(stamp), "%Y-%m-%dT%H:%M:%S", &tm);
    tslen += snprintf((stamp+tslen), 7, ".%06ld", (long) now.tv_usec);

    len = snprintf(log_buf, max_message_length, "<30>%.*s %s %s[%d]: %s", tslen, stamp, hostname, __progname, pid, data);   
    if (sendto(soc_fd, log_buf , len, MSG_DONTWAIT|MSG_NOSIGNAL,(struct sockaddr *) &client_addr, sizeof(client_addr)) < 0)
    {
        perror("[syslog_helper]: ");
        fprintf(stderr, "[syslog_helper]: Failed to write data on %s !!! \n", socket_stream_path);
    }
}

syslog_helper::~syslog_helper()
{
    close(soc_fd);
}

void send_logs_to_syslog(const char* src_data)
{
    log_mutex.lock();
    syslog_helper::get_instance()->send_data(src_data);
    log_mutex.unlock();
}
