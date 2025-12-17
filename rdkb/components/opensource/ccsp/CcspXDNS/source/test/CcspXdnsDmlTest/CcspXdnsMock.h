/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2024 RDK Management
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

#ifndef CCSP_XDNS_MOCK_H
#define CCSP_XDNS_MOCK_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cstdlib>
#include <experimental/filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <mocks/mock_syscfg.h>
#include <mocks/mock_syscfg.h>
#include <mocks/mock_ansc_memory.h>
#include <mocks/mock_ansc_wrapper_api.h>
#include <mocks/mock_safec_lib.h>
#include <mocks/mock_base64.h>
#include <mocks/mock_webconfigframework.h>
#include <mocks/mock_sysevent.h>
#include <mocks/mock_msgpack.h>
#include <mocks/mock_securewrapper.h>
#include <mocks/mock_usertime.h>
#include <mocks/mock_base_api.h>
#include <mocks/mock_trace.h>
#include <mocks/mock_utopia.h>
#include <mocks/mock_rbus.h>
#include <mocks/mock_file_io.h>
#include <mocks/mock_socket.h>
#include <mocks/mock_fd.h>

extern SyscfgMock * g_syscfgMock;
extern AnscMemoryMock * g_anscMemoryMock;
extern AnscWrapperApiMock * g_anscWrapperApiMock;
extern SafecLibMock* g_safecLibMock;
extern base64Mock *g_base64Mock;
extern webconfigFwMock *g_webconfigFwMock;
extern SyseventMock *g_syseventMock;
extern msgpackMock *g_msgpackMock;
extern SecureWrapperMock *g_securewrapperMock;
extern UserTimeMock *g_usertimeMock;
extern BaseAPIMock *g_baseapiMock;
extern TraceMock *g_traceMock;
extern utopiaMock *g_utopiaMock;
extern rbusMock *g_rbusMock;
extern FileIOMock *g_fileIOMock;
extern SocketMock *g_socketMock;
extern FileDescriptorMock *g_fdMock;

using namespace std;
using std::experimental::filesystem::exists;
using ::testing::_;
using ::testing::Return;
using ::testing::StrEq;
using ::testing::HasSubstr;
using ::testing::SetArgPointee;
using ::testing::DoAll;

extern "C" {
#include "ansc_platform.h"
#include "cosa_xdns_apis.h"
#include "cosa_xdns_dml.h"
#include "plugin_main_apis.h"
#include "ccsp_xdnsLog_wrapper.h"
#include "cosa_xdns_webconfig_api.h"
#include "cosa_apis_busutil.h"
#include "cosa_apis_util.h"
#include "cosa_dml_api_common.h"
#include "cosa_apis.h"
#include "plugin_main.h"
#include "xdns_comp_helpers.h"
#include "xdns_param.h"

int isValidIPv4Address(char *ipAddress);
int isValidIPv6Address(char *ipAddress);
BOOL isValidMacAddress
    (
        PCHAR                       pAddress
    );

int xdns_sysevent_init(void);
enum {SYS_EVENT_ERROR=-1, SYS_EVENT_OK, SYS_EVENT_TIMEOUT, SYS_EVENT_HANDLE_EXIT, SYS_EVENT_RECEIVED=0x10};


void xdns_handle_sysevent_notification(char *event, char *val);
enum xdnsSysEvent_e{
    SYSEVENT_CURRENT_WAN_IFNAME_EVENT,
};

int get_xdnsSysEvent_type_from_name(char *name, enum xdnsSysEvent_e *type_ptr);
int xdns_sysvent_listener(void);
int xdns_sysvent_close(void);
int xdns_check_sysevent_status(int fd, token_t token);
void xdns_handle_sysevent_async(void);
void RefreshResolvConfEntry();
void* MonitorResolvConfForChanges(void *arg);
void AppendDnsmasqConfEntry(char (*string1)[MAX_BUF_SIZE], int count);
void CreateDnsmasqServerConf(PCOSA_DATAMODEL_XDNS pMyObject);
void FillEntryInList(PCOSA_DATAMODEL_XDNS pXdns, PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY dnsTableEntry);

PCOSA_DML_MAPPING_CONTAINER
CosaDmlGetSelfHealCfg(
        ANSC_HANDLE                 hThisObject
    );

void backup_xdns_cache(xdns_cache *tmp_xdns_cache,xdns_cache *xdns_cache_bkup);
int process_dnsparams( dnsMapping_t *e, msgpack_object_map *map );

enum DeviceInterfaceType {
    ETHERNET_INTERFACE,
    IP_INTERFACE,
    USB_INTERFACE,
    HPNA_INTERFACE,
    DSL_INTERFACE,
    WIFI_INTERFACE,
    HOMEPLUG_INTERFACE,
    MOCA_INTERFACE,
    UPA_INTERFACE,
    ATM_LINK_INTERFACE,
    PTM_LINK_INTERFACE,
    ETHERNET_LINK_INTERFACE,
    ETHERNET_VLANT_INTERFACE,
    WIFI_SSID_INTERFACE,
    BRIDGING_INTERFACE,
    PPP_INTERFACE,
    DSL_CHANNEL_INTERFACE
};

int interface_type_from_name(char *name, enum DeviceInterfaceType *type_ptr);

ANSC_STATUS
CosaUtilStringToHex
    (
        char          *str,
        unsigned char *hex_str
    );

msgpack_object* __finder_comp( const char *name,
                          msgpack_object_type expect_type,
                          msgpack_object_map *map );
}

extern FILE* debugLogFile;
extern int consoleDebugEnable;
extern ANSC_HANDLE g_MessageBusHandle_Irep;
extern char g_SubSysPrefix_Irep[32];
extern char g_Subsystem[32];
extern xdns_cache XDNS_Data_Cache;
extern xdns_cache XDNS_tmp_bck;

extern PCOSA_BACKEND_MANAGER_OBJECT g_pCosaBEManager;
extern void *                       g_pDslhDmlAgent;

#endif //CCSP_XDNS_MOCK_H