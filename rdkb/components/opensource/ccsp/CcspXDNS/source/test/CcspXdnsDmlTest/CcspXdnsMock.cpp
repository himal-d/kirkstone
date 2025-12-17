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

#include "CcspXdnsMock.h"

SyscfgMock *g_syscfgMock = NULL;
AnscMemoryMock *g_anscMemoryMock = NULL;
AnscWrapperApiMock *g_anscWrapperApiMock = NULL;
SafecLibMock *g_safecLibMock = NULL;
base64Mock *g_base64Mock = NULL;
webconfigFwMock *g_webconfigFwMock = NULL;
SyseventMock *g_syseventMock = NULL;
msgpackMock *g_msgpackMock = NULL;
SecureWrapperMock *g_securewrapperMock = NULL;
UserTimeMock *g_usertimeMock = NULL;
BaseAPIMock *g_baseapiMock = NULL;
TraceMock *g_traceMock = NULL;
utopiaMock *g_utopiaMock = NULL;
rbusMock *g_rbusMock = NULL;
FileIOMock *g_fileIOMock = NULL;
SocketMock *g_socketMock = NULL;
FileDescriptorMock *g_fdMock = NULL;

FILE* debugLogFile = NULL;
int consoleDebugEnable = 0;
ANSC_HANDLE g_MessageBusHandle_Irep = NULL;
char g_SubSysPrefix_Irep[32] = {0};
char g_Subsystem[32] = {0};

PCOSA_BACKEND_MANAGER_OBJECT g_pCosaBEManager = NULL;
void *g_pDslhDmlAgent = NULL;