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

#include "CcspCMAgentMock.h"

SyscfgMock *g_syscfgMock = NULL;
SecureWrapperMock *g_securewrapperMock = NULL;
msgpackMock *g_msgpackMock = NULL;
UserTimeMock *g_usertimeMock = NULL;
SafecLibMock *g_safecLibMock = NULL;
AnscMemoryMock *g_anscMemoryMock = NULL;
BaseAPIMock *g_baseapiMock = NULL;
TraceMock *g_traceMock = NULL;
base64Mock *g_base64Mock = NULL;
rbusMock *g_rbusMock = NULL;
CmHalMock *g_cmHALMock = NULL;
PlatformHalMock *g_platformHALMock = NULL;
cjsonMock *g_cjsonMock = NULL;
SyseventMock *g_syseventMock = NULL;
webconfigFwMock *g_webconfigFwMock = NULL;
AnscWrapperApiMock *g_anscWrapperApiMock = NULL;
UtilMock *g_utilMock = NULL;
PtdHandlerMock *g_PtdHandlerMock = NULL;
FileIOMock *g_fileIOMock = NULL;
utopiaMock *g_utopiaMock = NULL;

ANSC_HANDLE g_MessageBusHandle_Irep = NULL;
char  g_SubSysPrefix_Irep[32] = {0};
ANSC_HANDLE bus_handle = NULL;