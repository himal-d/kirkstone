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

class CcspCMAgentRdkCentralCableModemInternalTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        g_syscfgMock = new SyscfgMock();
        g_securewrapperMock = new SecureWrapperMock();
        g_msgpackMock = new msgpackMock();
        g_usertimeMock = new UserTimeMock();
        g_safecLibMock = new SafecLibMock();
        g_baseapiMock = new BaseAPIMock();
        g_traceMock = new TraceMock();
        g_base64Mock = new base64Mock();
        g_rbusMock = new rbusMock();
        g_cmHALMock = new CmHalMock();
        g_platformHALMock = new PlatformHalMock();
        g_cjsonMock = new cjsonMock();
        g_webconfigFwMock = new webconfigFwMock();
        g_anscWrapperApiMock = new AnscWrapperApiMock();
        g_utilMock = new UtilMock();
        g_PtdHandlerMock = new PtdHandlerMock();
        g_fileIOMock = new FileIOMock();
    }

    void TearDown() override {
        delete g_syscfgMock;
        delete g_securewrapperMock;
        delete g_msgpackMock;
        delete g_usertimeMock;
        delete g_safecLibMock;
        delete g_baseapiMock;
        delete g_traceMock;
        delete g_base64Mock;
        delete g_rbusMock;
        delete g_cmHALMock;
        delete g_platformHALMock;
        delete g_cjsonMock;
        delete g_webconfigFwMock;
        delete g_anscWrapperApiMock;
        delete g_utilMock;
        delete g_PtdHandlerMock;
        delete g_fileIOMock;
        g_syscfgMock = nullptr;
        g_securewrapperMock = nullptr;
        g_msgpackMock = nullptr;
        g_usertimeMock = nullptr;
        g_safecLibMock = nullptr;
        g_baseapiMock = nullptr;
        g_traceMock = nullptr;
        g_base64Mock = nullptr;
        g_rbusMock = nullptr;
        g_cmHALMock = nullptr;
        g_platformHALMock = nullptr;
        g_cjsonMock = nullptr;
        g_webconfigFwMock = nullptr;
        g_anscWrapperApiMock = nullptr;
        g_utilMock = nullptr;
        g_PtdHandlerMock = nullptr;
        g_fileIOMock = nullptr;
    }
};

// Unit Test for cosa_x_rdkcentral_com_cablemodem_internal.c file

TEST_F(CcspCMAgentRdkCentralCableModemInternalTestFixture, CosaRDKCentralComCableModemCreate)
{
    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)NULL;

    pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));

    ANSC_HANDLE hThisObject = (ANSC_HANDLE)pMyObject;

    pMyObject->Oid = COSA_DATAMODEL_RDKCENTRAL_CM_OID;
    pMyObject->Create = CosaRDKCentralComCableModemCreate;
    pMyObject->Remove = CosaRDKCentralComCableModemRemove;
    pMyObject->Initialize = CosaRDKCentralComCableModemInitialize;

    pMyObject->Initialize(hThisObject);

    EXPECT_NE(CosaRDKCentralComCableModemCreate(), nullptr);
    EXPECT_NE(pMyObject, nullptr);
}

TEST_F(CcspCMAgentRdkCentralCableModemInternalTestFixture, CosaRDKCentralComCableModemInitialize)
{
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;
    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ANSC_HANDLE hThisObject = (ANSC_HANDLE)pMyObject;

    EXPECT_EQ(CosaDmlRDKCentralCMInit(NULL, (PANSC_HANDLE)pMyObject), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(CosaDmlRDKCMInit(NULL, (PANSC_HANDLE)pMyObject), ANSC_STATUS_SUCCESS);

    returnStatus = CosaRDKCentralComCableModemInitialize(hThisObject);
    EXPECT_EQ(returnStatus, ANSC_STATUS_SUCCESS);
    EXPECT_NE(pMyObject, nullptr);
}

TEST_F(CcspCMAgentRdkCentralCableModemInternalTestFixture, CosaRDKCentralComCableModemRemove)
{
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;
    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ANSC_HANDLE hThisObject = (ANSC_HANDLE)pMyObject;

    returnStatus = CosaRDKCentralComCableModemRemove(hThisObject);
    EXPECT_EQ(returnStatus, ANSC_STATUS_SUCCESS);
    EXPECT_NE(pMyObject, nullptr);
}