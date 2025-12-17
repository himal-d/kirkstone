/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2015 RDK Management
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

#ifndef  _COSA_XDNS_WEBCONFIG_API_H
#define  _COSA_XDNS_WEBCONFIG_API_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

#include "webconfig_framework.h"
#include "xdns_param.h"

#define SUBDOC_COUNT 1
#define STR_SIZE 64
#define IPV6_STR_SIZE 129
#define DATA_BLOCK_SIZE 256
#define XDNS_CACHE_SIZE 256

#define IPV4_LOOPBACK "127.0.0.1"
#define IPV6_LOOPBACK "::1"
#define USE_RDK_DEFAULT_STRING "USE_RDK_DEFAULT"

typedef enum _erouter_mode {
    erouter_mode_IPv4 = 0,
    erouter_mode_IPv6 = 1,
    erouter_mode_DualStack = 3
} erouter_mode;

typedef struct {
    char MacAddress[STR_SIZE];
    char DnsIPv4[STR_SIZE];
    char DnsIPv6[IPV6_STR_SIZE];
    char Tag[STR_SIZE];

} xdns_table;


typedef struct {
    int  Tablecount;
    bool XdnsEnable;
    char DefaultDeviceDnsIPv4[STR_SIZE];
    char DefaultDeviceDnsIPv6[IPV6_STR_SIZE];
    char DefaultSecondaryDeviceDnsIPv4[STR_SIZE];
    char DefaultSecondaryDeviceDnsIPv6[IPV6_STR_SIZE];
    char DefaultDeviceTag[STR_SIZE];
    xdns_table XDNSTableList[XDNS_CACHE_SIZE];
    
} xdns_cache;


extern xdns_cache XDNS_Data_Cache;
extern xdns_cache XDNS_tmp_bck;


void init_xdns_cache(xdns_cache *tmp_xdns_cache);
void print_xdns_cache(xdns_cache *tmp_xdns_cache);
void clear_xdns_cache(xdns_cache *tmp_xdns_cache);
uint32_t getBlobVersion(char* subdoc);
int setBlobVersion(char* subdoc,uint32_t version);
int xdns_read_dns_ip(char *UseRDKDefaultDeviceDnsIPv4, char *UseRDKDefaultDeviceDnsIPv6);
int xdns_load_dns_ip(char *DnsIPv4, char *DnsIPv6, char *UseRDKDefaultDeviceDnsIPv4, char *UseRDKDefaultDeviceDnsIPv6);
int xdns_read_load_dns_ip(char *Blob_Valid_IPv4, char *Blob_Valid_IPv6, char *DnsIPv4, char *DnsIPv6);
void webConfigFrameworkInit() ;
pErr Process_XDNS_WebConfigRequest(void *Data);
int set_xdns_conf(xdnsdoc_t *xd, xdns_cache *tmp_xdns_cache);
int CheckIfIpIsValid( char *ipAddress );
int CheckIfMacIsValid(char* pAddress);
int apply_XDNS_cache_ToDB(xdns_cache *tmp_xdns_cache);
int rollback_XDNS();
void freeResources_XDNS(void *arg);

#endif

