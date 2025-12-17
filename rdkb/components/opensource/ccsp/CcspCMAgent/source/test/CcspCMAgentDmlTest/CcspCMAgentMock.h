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

#ifndef CCSP_CMAGENT_MOCK_H
#define CCSP_CMAGENT_MOCK_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cstdlib>
#include <experimental/filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <mocks/mock_usertime.h>
#include <mocks/mock_ansc_wrapper_api.h>
#include <mocks/mock_syscfg.h>
#include <mocks/mock_securewrapper.h>
#include <mocks/mock_trace.h>
#include <mocks/mock_msgpack.h>
#include <mocks/mock_safec_lib.h>
#include <mocks/mock_ansc_memory.h>
#include <mocks/mock_base_api.h>
#include <mocks/mock_base64.h>
#include <mocks/mock_rbus.h>
#include <mocks/mock_cm_hal.h>
#include <mocks/mock_platform_hal.h>
#include <mocks/mock_cJSON.h>
#include <mocks/mock_sysevent.h>
#include <mocks/mock_webconfigframework.h>
#include <mocks/mock_util.h>
#include <mocks/mock_pthread.h>
#include <mocks/mock_file_io.h>
#include <mocks/mock_utopia.h>

extern SyscfgMock *g_syscfgMock;
extern SecureWrapperMock *g_securewrapperMock;
extern msgpackMock *g_msgpackMock;
extern UserTimeMock *g_usertimeMock;
extern SafecLibMock *g_safecLibMock;
extern AnscMemoryMock *g_anscMemoryMock;
extern BaseAPIMock *g_baseapiMock;
extern TraceMock *g_traceMock;
extern base64Mock *g_base64Mock;
extern rbusMock *g_rbusMock;
extern CmHalMock *g_cmHALMock;
extern PlatformHalMock *g_platformHALMock;
extern cjsonMock *g_cjsonMock;
extern SyseventMock *g_syseventMock;
extern webconfigFwMock *g_webconfigFwMock;
extern AnscWrapperApiMock *g_anscWrapperApiMock;
extern UtilMock *g_utilMock;
extern PtdHandlerMock *g_PtdHandlerMock;
extern FileIOMock *g_fileIOMock;
extern utopiaMock *g_utopiaMock;

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
#include "plugin_main_apis.h"
#include "cosa_device_info_apis.h"
#include "cosa_device_info_dml.h"
#include "cosa_device_info_internal.h"
#include "cosa_apis.h"
#include "cosa_x_cisco_com_cablemodem_dml.h"
#include "cosa_x_cisco_com_cablemodem_internal.h"
#include "cosa_x_rdkcentral_com_cablemodem_apis.h"
#include "cosa_x_rdkcentral_com_cablemodem_dml.h"
#include "cosa_x_rdkcentral_com_cablemodem_internal.h"
#include "safec_lib_common.h"
#include "cosa_cm_common.h"
#include "cm_agent_webconfig_api.h"
#include "ccsp_trace.h"
#include "cosa_rbus_handler_apis.h"
#include "cm_agent_webconfig_api.h"

BOOL
Rbus_CMAgent_SetParamUintValue
    (
       void*                 hInsContext,
       char*                       pParamName,
       uint                        uValue
    );
BOOL
Rbus_CMAgent_SetParamBoolValue
    (
        void*                 hInsContext,
        char*                       pParamName,
        BOOL                        bValue
    );

BOOL
Rbus_LLDEnabled_SetParamBoolValue
    (
        void*                 hInsContext,
        char*                 pParamName,
        BOOL                  bValue
    );

}


extern CmAgent_LLDEnable cmAgent_Lld_Enable;
extern PCOSA_BACKEND_MANAGER_OBJECT g_pCosaBEManager;

extern ANSC_HANDLE g_MessageBusHandle_Irep;
extern char  g_SubSysPrefix_Irep[32];
extern ANSC_HANDLE bus_handle;

#endif //CCSP_CMAGENT_MOCK_H 