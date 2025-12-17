/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
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

#include "cosa_apis.h"
#include "dslh_definitions_tr143.h"

#define RESOLV_CONF "/etc/resolv.conf"
#define DNSMASQ_SERVERS_CONF "/nvram/dnsmasq_servers.conf"
#define DNSMASQ_SERVERS_BAK "/nvram/dnsmasq_servers.bak"

#define MAX_BUF_SIZE 256
#define MAX_XDNS_SERV 2
//mandate Dual stack by turning on this
#define FEATURE_IPV6 1

#ifdef FEATURE_IPV6
#define XDNS_ENTRY_FORMAT  "%63s %63s %63s %63s %63s"
#else
#define XDNS_ENTRY_FORMAT  "%63s %63s %63s %63s"
#endif

#define  COSA_CONTEXT_XDNS_LINK_CLASS_CONTENT                                  \
        COSA_CONTEXT_LINK_CLASS_CONTENT                                            \
        BOOL                            bFound;                                    \


/***********************************
    Actual definition declaration
************************************/
#define  COSA_IREP_FOLDER_NAME_XDNS                       "Xdns"
#define  COSA_DML_RR_NAME_NATNextInsNumber               "NextInstanceNumber"
#define  COSA_DML_RR_NAME_NATAlias                       "Alias"
#define  COSA_DML_RR_NAME_NATbNew                        "bNew"

/*
typedef enum _PingServerType
{
	PingServerType_IPv4 = 0,
	PingServerType_IPv6
} PingServerType;
*/

typedef  struct
_COSA_CONTEXT_XDNS_LINK_OBJECT
{
    COSA_CONTEXT_XDNS_LINK_CLASS_CONTENT
}
COSA_CONTEXT_XDNS_LINK_OBJECT,  *PCOSA_CONTEXT_XDNS_LINK_OBJECT;

typedef  struct
_COSA_DML_XDNS_MACDNS_MAPPING_ENTRY
{
    ULONG                           InstanceNumber;
    CHAR                            MacAddress[256];  /* MacAddress string address */
    BOOL                            MacAddressChanged;
    CHAR                            DnsIPv4[256];  /* IPv4 or IPv4 string address */
    BOOL                            DnsIPv4Changed;
    CHAR                            DnsIPv6[256];  /* IPv6 or IPv6 string address */
    BOOL                            DnsIPv6Changed;
    CHAR                            Tag[256];  /* Tag string address */
    BOOL                            TagChanged;
}
COSA_DML_XDNS_MACDNS_MAPPING_ENTRY,  *PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY;

typedef  struct
_PCOSA_DML_MAPPING_CONTAINER
{
    ULONG                      	    XDNSEntryCount;
    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY    pXDNSTable;
}
COSA_DML_MAPPING_CONTAINER,  *PCOSA_DML_MAPPING_CONTAINER;

#define  COSA_DATAMODEL_XDNS_CLASS_CONTENT                                                  \
    /* duplication of the base object class content */                                      \
    COSA_BASE_CONTENT                                                                       \
	ULONG                       MaxInstanceNumber;                                    \
	ULONG                       ulXDNSNextInstanceNumber;                                    \
    CHAR                        DefaultDeviceDnsIPv4[256];                                         \
    BOOL                        DefaultDeviceDnsIPv4Changed;                                         \
    CHAR                        DefaultDeviceDnsIPv6[256];                                         \
    BOOL                        DefaultDeviceDnsIPv6Changed;                                         \
    CHAR                        DefaultSecondaryDeviceDnsIPv4[256];                                         \
    BOOL                        DefaultSecondaryDeviceDnsIPv4Changed;                                         \
    CHAR                        DefaultSecondaryDeviceDnsIPv6[256];                                         \
    BOOL                        DefaultSecondaryDeviceDnsIPv6Changed;                                         \
    CHAR                        DefaultDeviceTag[256];                                            \
    BOOL                        DefaultDeviceTagChanged;                                         \
    SLIST_HEADER                XDNSDeviceList;                                        \
    PCOSA_DML_MAPPING_CONTAINER    pMappingContainer;                                        \
	ANSC_HANDLE                     hIrepFolderXdns;                                         \
    ANSC_HANDLE                     hIrepFolderXdnsMapCont;                                       \
    /* end of Diagnostic object class content */                                                    \


typedef  struct
_COSA_DATAMODEL_XDNS
{
    COSA_DATAMODEL_XDNS_CLASS_CONTENT
}
COSA_DATAMODEL_XDNS,  *PCOSA_DATAMODEL_XDNS;

#define  ACCESS_COSA_CONTEXT_XDNS_LINK_OBJECT(p)              \
         ACCESS_CONTAINER(p, COSA_CONTEXT_XDNS_LINK_OBJECT, Linkage)

/**********************************
    Standard function declaration
***********************************/
ANSC_HANDLE
CosaXDNSCreate
    (
        VOID
    );

ANSC_STATUS
CosaXDNSInitialize
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
CosaXDNSRemove
    (
        ANSC_HANDLE                 hThisObject
    );

void GetDnsMasqFileEntry(char* macaddress, char (*defaultEntry)[MAX_BUF_SIZE]);
void CreateDnsmasqServerConf(PCOSA_DATAMODEL_XDNS pMyObject);
void ReplaceDnsmasqConfEntry(char* macaddress, char (*overrideEntry)[MAX_BUF_SIZE], int count);
void ResetDnsmasqConfFile();
void AppendDnsmasqConfEntry(char (*string1)[MAX_BUF_SIZE], int count);
int SetXdnsConfig();
int UnsetXdnsConfig();
int isValidIPv4Address(char *ipAddress);
int isValidIPv6Address(char *ipAddress);
