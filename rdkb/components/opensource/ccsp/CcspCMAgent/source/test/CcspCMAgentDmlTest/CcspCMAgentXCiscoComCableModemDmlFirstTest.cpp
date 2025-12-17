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

class CcspCMAgentXCiscoComCableModemDmlFirstTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        g_securewrapperMock = new SecureWrapperMock();
        g_msgpackMock = new msgpackMock();
        g_usertimeMock = new UserTimeMock();
        g_safecLibMock = new SafecLibMock();
        g_anscMemoryMock = new AnscMemoryMock();
        g_traceMock = new TraceMock();
        g_base64Mock = new base64Mock();
        g_rbusMock = new rbusMock();
        g_cmHALMock = new CmHalMock();
        g_platformHALMock = new PlatformHalMock();
        g_cjsonMock = new cjsonMock();
        g_syseventMock = new SyseventMock();
        g_webconfigFwMock = new webconfigFwMock();
        g_anscWrapperApiMock = new AnscWrapperApiMock();
        g_utilMock = new UtilMock();
        g_PtdHandlerMock = new PtdHandlerMock();
        g_fileIOMock = new FileIOMock();
    }

    void TearDown() override {
        delete g_securewrapperMock;
        delete g_msgpackMock;
        delete g_usertimeMock;
        delete g_safecLibMock;
        delete g_anscMemoryMock;
        delete g_traceMock;
        delete g_base64Mock;
        delete g_rbusMock;
        delete g_cmHALMock;
        delete g_platformHALMock;
        delete g_cjsonMock;
        delete g_syseventMock;
        delete g_webconfigFwMock;
        delete g_anscWrapperApiMock;
        delete g_utilMock;
        delete g_PtdHandlerMock;
        delete g_fileIOMock;
        g_securewrapperMock = nullptr;
        g_msgpackMock = nullptr;
        g_usertimeMock = nullptr;
        g_safecLibMock = nullptr;
        g_anscMemoryMock = nullptr;
        g_traceMock = nullptr;
        g_base64Mock = nullptr;
        g_rbusMock = nullptr;
        g_cmHALMock = nullptr;
        g_platformHALMock = nullptr;
        g_cjsonMock = nullptr;
        g_syseventMock = nullptr;
        g_webconfigFwMock = nullptr;
        g_anscWrapperApiMock = nullptr;
        g_utilMock = nullptr;
        g_PtdHandlerMock = nullptr;
        g_fileIOMock = nullptr;
    }
};

// Unit Test for cosa_x_cisco_com_cablemodem_dml.c file

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamBoolValue_BPIState)
{
    int comparisonResult = 0;
    const char *ParamName = "BPIState";
    BOOL pBool = FALSE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    COSA_CM_DOCSIS_INFO DInfo;
    pBool = DInfo.BPIState;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BPIState"),
                                               strlen("BPIState"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamBoolValue(NULL, (char*)ParamName, &pBool), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamBoolValue_NetworkAccess)
{
    int comparisonResult = 0;
    const char *ParamName = "NetworkAccess";
    BOOL pBool = FALSE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    COSA_CM_DOCSIS_INFO DInfo;
    pBool = DInfo.NetworkAccess;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BPIState"),
                                               strlen("BPIState"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NetworkAccess"),
                                               strlen("NetworkAccess"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    pBool = DInfo.NetworkAccess;

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamBoolValue(NULL, (char*)ParamName, &pBool), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamBoolValue_LoopDiagnosticsStart)
{
    int comparisonResult = 0;
    const char *ParamName = "LoopDiagnosticsStart";
    BOOL pBool = TRUE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    COSA_CM_DOCSIS_INFO DInfo;
    pBool = DInfo.NetworkAccess;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BPIState"),
                                               strlen("BPIState"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NetworkAccess"),
                                               strlen("NetworkAccess"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(CosaDmlCMGetLoopDiagnosticsStart(NULL, &pBool), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamBoolValue(NULL, (char*)ParamName, &pBool), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamBoolValue_EnableLog)
{
    int comparisonResult = 0;
    const char *ParamName = "EnableLog";
    BOOL pBool = TRUE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    pBool = pCfg->EnableLog;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BPIState"),
                                               strlen("BPIState"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NetworkAccess"),
                                               strlen("NetworkAccess"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EnableLog"),
                                               strlen("EnableLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamBoolValue(NULL, (char*)ParamName, &pBool), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamBoolValue_CleanDocsislog)
{
    int comparisonResult = 0;
    const char *ParamName = "CleanDocsislog";
    BOOL pBool = TRUE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    pBool = pCfg->CleanDocsisLog;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BPIState"),
                                               strlen("BPIState"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NetworkAccess"),
                                               strlen("NetworkAccess"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EnableLog"),
                                               strlen("EnableLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CleanDocsislog"),
                                               strlen("CleanDocsislog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamBoolValue(NULL, (char*)ParamName, &pBool), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamBoolValue_DOCSISEnableCert)
{
    int comparisonResult = 0;
    const char *ParamName = "DOCSISEnableCert";
    BOOL pBool = TRUE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    pBool = pCfg->EnableLog;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BPIState"),
                                               strlen("BPIState"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NetworkAccess"),
                                               strlen("NetworkAccess"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EnableLog"),
                                               strlen("EnableLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CleanDocsislog"),
                                               strlen("CleanDocsislog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISEnableCert"),
                                               strlen("DOCSISEnableCert"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetCertStatus(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCmGetCMCertStatus(NULL, &pBool), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamBoolValue(NULL, (char*)ParamName, &pBool), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamBoolValue_ConfigureWan)
{
    int comparisonResult = 0;
    const char *ParamName = "ConfigureWan";
    BOOL pBool = TRUE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_WANCFG pWanCfg = &pMyObject->CmWanCfg;

    pBool = pWanCfg->ConfigureWan;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BPIState"),
                                               strlen("BPIState"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NetworkAccess"),
                                               strlen("NetworkAccess"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EnableLog"),
                                               strlen("EnableLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CleanDocsislog"),
                                               strlen("CleanDocsislog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISEnableCert"),
                                               strlen("DOCSISEnableCert"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigureWan"),
                                               strlen("ConfigureWan"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamBoolValue(NULL, (char*)ParamName, &pBool), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamBoolValue_CustomWanConfigUpdate)
{
    int comparisonResult = 0;
    const char *ParamName = "CustomWanConfigUpdate";
    BOOL pBool = TRUE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_WANCFG pWanCfg = &pMyObject->CmWanCfg;

    pBool = pWanCfg->CustomWanConfigUpdate;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BPIState"),
                                               strlen("BPIState"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NetworkAccess"),
                                               strlen("NetworkAccess"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EnableLog"),
                                               strlen("EnableLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CleanDocsislog"),
                                               strlen("CleanDocsislog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISEnableCert"),
                                               strlen("DOCSISEnableCert"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigureWan"),
                                               strlen("ConfigureWan"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CustomWanConfigUpdate"),
                                               strlen("CustomWanConfigUpdate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamBoolValue(NULL, (char*)ParamName, &pBool), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamIntValue_TimeOffset)
{
    int comparisonResult = 0;
    const char *ParamName = "TimeOffset";
    int pInt = 0;

    COSA_CM_DHCP_INFO Info;
    pInt = Info.TimeOffset;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeOffset"),
                                               strlen("TimeOffset"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetDHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDHCPInfo(NULL, &Info), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamIntValue(NULL, (char*)ParamName, &pInt), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamUlongValue_DOCSISDHCPAttempts)
{
    int comparisonResult = 0;
    const char *ParamName = "DOCSISDHCPAttempts";
    ULONG pUlong = 0;

    COSA_CM_DOCSIS_INFO DInfo;
    pUlong = DInfo.DOCSISDHCPAttempts;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}


TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamUlongValue_DOCSISTftpAttempts)
{
    int comparisonResult = 0;
    const char *ParamName = "DOCSISTftpAttempts";
    ULONG pUlong = 0;

    COSA_CM_DOCSIS_INFO DInfo;
    pUlong = DInfo.DOCSISTftpAttempts;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamUlongValue_MaxCpeAllowed)
{
    int comparisonResult = 0;
    const char *ParamName = "MaxCpeAllowed";
    ULONG pUlong = 0;

    COSA_CM_DOCSIS_INFO DInfo;
    pUlong = DInfo.MaxCpeAllowed;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamUlongValue_UpgradeServerIP)
{
    int comparisonResult = 0;
    const char *ParamName = "UpgradeServerIP";
    ULONG pUlong = 0;

    COSA_CM_DOCSIS_INFO DInfo;
    pUlong = DInfo.UpgradeServerIP.Value;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}


TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamUlongValue_IPAddress)
{
    int comparisonResult = 0;
    const char *ParamName = "IPAddress";
    ULONG pUlong = 0;

    COSA_CM_DHCP_INFO Info;
    pUlong = Info.IPAddress.Value;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetDHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDHCPInfo(NULL, &Info), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamUlongValue_SubnetMask)
{
    int comparisonResult = 0;
    const char *ParamName = "SubnetMask";
    ULONG pUlong = 0;

    COSA_CM_DHCP_INFO Info;
    pUlong = Info.SubnetMask.Value;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubnetMask"),
                                               strlen("SubnetMask"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetDHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDHCPInfo(NULL, &Info), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamUlongValue_Gateway)
{
    int comparisonResult = 0;
    const char *ParamName = "Gateway";
    ULONG pUlong = 0;

    COSA_CM_DHCP_INFO Info;
    pUlong = Info.Gateway.Value;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubnetMask"),
                                               strlen("SubnetMask"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Gateway"),
                                               strlen("Gateway"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetDHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDHCPInfo(NULL, &Info), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);

}


TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamUlongValue_TFTPServer)
{
    int comparisonResult = 0;
    const char *ParamName = "TFTPServer";
    ULONG pUlong = 0;

    COSA_CM_DHCP_INFO Info;
    pUlong = Info.TFTPServer.Value;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubnetMask"),
                                               strlen("SubnetMask"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Gateway"),
                                               strlen("Gateway"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TFTPServer"),
                                               strlen("TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetDHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDHCPInfo(NULL, &Info), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamUlongValue_TimeOffset)
{
    int comparisonResult = 0;
    const char *ParamName = "TimeOffset";
    ULONG pUlong = 0;

    COSA_CM_DHCP_INFO Info;
    pUlong = Info.TimeOffset;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubnetMask"),
                                               strlen("SubnetMask"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Gateway"),
                                               strlen("Gateway"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TFTPServer"),
                                               strlen("TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeOffset"),
                                               strlen("TimeOffset"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetDHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDHCPInfo(NULL, &Info), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamUlongValue_LeaseTimeRemaining)
{
    int comparisonResult = 0;
    const char *ParamName = "LeaseTimeRemaining";
    ULONG pUlong = 0;

    COSA_CM_DHCP_INFO Info;
    pUlong = Info.LeaseTimeRemaining;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubnetMask"),
                                               strlen("SubnetMask"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Gateway"),
                                               strlen("Gateway"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TFTPServer"),
                                               strlen("TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeOffset"),
                                               strlen("TimeOffset"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LeaseTimeRemaining"),
                                               strlen("LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetDHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDHCPInfo(NULL, &Info), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamUlongValue_IPv6LeaseTimeRemaining)
{
    int comparisonResult = 0;
    const char *ParamName = "IPv6LeaseTimeRemaining";
    ULONG pUlong = 0;

    COSA_CM_IPV6DHCP_INFO IPv6Info;
    pUlong = IPv6Info.IPv6LeaseTimeRemaining;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubnetMask"),
                                               strlen("SubnetMask"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Gateway"),
                                               strlen("Gateway"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TFTPServer"),
                                               strlen("TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeOffset"),
                                               strlen("TimeOffset"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LeaseTimeRemaining"),
                                               strlen("LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6LeaseTimeRemaining"),
                                               strlen("IPv6LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetIPv6DHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetIPv6DHCPInfo(NULL, &IPv6Info), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);

}


TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamUlongValue_IPv6RebindTimeRemaining)
{
    int comparisonResult = 0;
    const char *ParamName = "IPv6RebindTimeRemaining";
    ULONG pUlong = 0;

    COSA_CM_IPV6DHCP_INFO IPv6Info;
    pUlong = IPv6Info.IPv6RebindTimeRemaining;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubnetMask"),
                                               strlen("SubnetMask"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Gateway"),
                                               strlen("Gateway"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TFTPServer"),
                                               strlen("TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeOffset"),
                                               strlen("TimeOffset"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LeaseTimeRemaining"),
                                               strlen("LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6LeaseTimeRemaining"),
                                               strlen("IPv6LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6RebindTimeRemaining"),
                                               strlen("IPv6RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetIPv6DHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetIPv6DHCPInfo(NULL, &IPv6Info), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}


TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamUlongValue_IPv6RenewTimeRemaining)
{
    int comparisonResult = 0;
    const char *ParamName = "IPv6RenewTimeRemaining";
    ULONG pUlong = 0;

    COSA_CM_IPV6DHCP_INFO IPv6Info;
    pUlong = IPv6Info.IPv6RenewTimeRemaining;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubnetMask"),
                                               strlen("SubnetMask"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Gateway"),
                                               strlen("Gateway"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TFTPServer"),
                                               strlen("TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeOffset"),
                                               strlen("TimeOffset"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LeaseTimeRemaining"),
                                               strlen("LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6LeaseTimeRemaining"),
                                               strlen("IPv6LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6RebindTimeRemaining"),
                                               strlen("IPv6RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6RenewTimeRemaining"),
                                               strlen("IPv6RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetIPv6DHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetIPv6DHCPInfo(NULL, &IPv6Info), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}



TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamUlongValue_LockedUpstreamChID)
{
    int comparisonResult = 0;
    const char *ParamName = "LockedUpstreamChID";
    ULONG pUlong = 0;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubnetMask"),
                                               strlen("SubnetMask"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Gateway"),
                                               strlen("Gateway"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TFTPServer"),
                                               strlen("TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeOffset"),
                                               strlen("TimeOffset"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LeaseTimeRemaining"),
                                               strlen("LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6LeaseTimeRemaining"),
                                               strlen("IPv6LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6RebindTimeRemaining"),
                                               strlen("IPv6RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6RenewTimeRemaining"),
                                               strlen("IPv6RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LockedUpstreamChID"),
                                               strlen("LockedUpstreamChID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetUSChannelId())
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetLockedUpstreamChID(NULL, &pUlong), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_StartDSFrequency)
{
    int comparisonResult = 0;
    const char *ParamName = "StartDSFrequency";
    ULONG pUlong = 0;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubnetMask"),
                                               strlen("SubnetMask"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Gateway"),
                                               strlen("Gateway"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TFTPServer"),
                                               strlen("TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeOffset"),
                                               strlen("TimeOffset"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LeaseTimeRemaining"),
                                               strlen("LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6LeaseTimeRemaining"),
                                               strlen("IPv6LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6RebindTimeRemaining"),
                                               strlen("IPv6RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6RenewTimeRemaining"),
                                               strlen("IPv6RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LockedUpstreamChID"),
                                               strlen("LockedUpstreamChID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("StartDSFrequency"),
                                               strlen("StartDSFrequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDownFreq())
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetStartDSFrequency(NULL, &pUlong), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_CMResetCount)
{
    int comparisonResult = 0;
    const char *ParamName = "CMResetCount";
    ULONG pUlong = 0;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubnetMask"),
                                               strlen("SubnetMask"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Gateway"),
                                               strlen("Gateway"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TFTPServer"),
                                               strlen("TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeOffset"),
                                               strlen("TimeOffset"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LeaseTimeRemaining"),
                                               strlen("LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6LeaseTimeRemaining"),
                                               strlen("IPv6LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6RebindTimeRemaining"),
                                               strlen("IPv6RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6RenewTimeRemaining"),
                                               strlen("IPv6RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LockedUpstreamChID"),
                                               strlen("LockedUpstreamChID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("StartDSFrequency"),
                                               strlen("StartDSFrequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMResetCount"),
                                               strlen("CMResetCount"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_Get_CableModemResetCount(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetResetCount(NULL, CABLE_MODEM_RESET, &pUlong), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_LocalResetCount)
{
    int comparisonResult = 0;
    const char *ParamName = "LocalResetCount";
    ULONG pUlong = 0;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubnetMask"),
                                               strlen("SubnetMask"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Gateway"),
                                               strlen("Gateway"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TFTPServer"),
                                               strlen("TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeOffset"),
                                               strlen("TimeOffset"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LeaseTimeRemaining"),
                                               strlen("LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6LeaseTimeRemaining"),
                                               strlen("IPv6LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6RebindTimeRemaining"),
                                               strlen("IPv6RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6RenewTimeRemaining"),
                                               strlen("IPv6RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LockedUpstreamChID"),
                                               strlen("LockedUpstreamChID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("StartDSFrequency"),
                                               strlen("StartDSFrequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMResetCount"),
                                               strlen("CMResetCount"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LocalResetCount"),
                                               strlen("LocalResetCount"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_Get_LocalResetCount(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetResetCount(NULL, LOCAL_RESET, &pUlong), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_DocsisResetCount)
{
    int comparisonResult = 0;
    const char *ParamName = "DocsisResetCount";
    ULONG pUlong = 0;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubnetMask"),
                                               strlen("SubnetMask"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Gateway"),
                                               strlen("Gateway"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TFTPServer"),
                                               strlen("TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeOffset"),
                                               strlen("TimeOffset"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LeaseTimeRemaining"),
                                               strlen("LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6LeaseTimeRemaining"),
                                               strlen("IPv6LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6RebindTimeRemaining"),
                                               strlen("IPv6RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6RenewTimeRemaining"),
                                               strlen("IPv6RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LockedUpstreamChID"),
                                               strlen("LockedUpstreamChID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("StartDSFrequency"),
                                               strlen("StartDSFrequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMResetCount"),
                                               strlen("CMResetCount"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LocalResetCount"),
                                               strlen("LocalResetCount"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DocsisResetCount"),
                                               strlen("DocsisResetCount"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_Get_DocsisResetCount(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetResetCount(NULL, DOCSIS_RESET, &pUlong), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_ErouterResetCount)
{
    int comparisonResult = 0;
    const char *ParamName = "ErouterResetCount";
    ULONG pUlong = 0;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPAttempts"),
                                               strlen("DOCSISDHCPAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpAttempts"),
                                               strlen("DOCSISTftpAttempts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MaxCpeAllowed"),
                                               strlen("MaxCpeAllowed"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpgradeServerIP"),
                                               strlen("UpgradeServerIP"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubnetMask"),
                                               strlen("SubnetMask"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Gateway"),
                                               strlen("Gateway"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TFTPServer"),
                                               strlen("TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeOffset"),
                                               strlen("TimeOffset"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LeaseTimeRemaining"),
                                               strlen("LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6LeaseTimeRemaining"),
                                               strlen("IPv6LeaseTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6RebindTimeRemaining"),
                                               strlen("IPv6RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6RenewTimeRemaining"),
                                               strlen("IPv6RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LockedUpstreamChID"),
                                               strlen("LockedUpstreamChID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("StartDSFrequency"),
                                               strlen("StartDSFrequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMResetCount"),
                                               strlen("CMResetCount"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LocalResetCount"),
                                               strlen("LocalResetCount"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DocsisResetCount"),
                                               strlen("DocsisResetCount"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ErouterResetCount"),
                                               strlen("ErouterResetCount"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_Get_ErouterResetCount(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetResetCount(NULL, EROUTER_RESET, &pUlong), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamUlongValue(NULL, (char*)ParamName, &pUlong), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_MACAddress)
{
    int comparisonResult = 0;
    const char *ParamName = "MACAddress";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    strncpy(Info.MACAddress, "E0:DB:D1:37:8C:DF", sizeof(Info.MACAddress) - 1);
    Info.MACAddress[sizeof(Info.MACAddress) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetDHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDHCPInfo(NULL, &Info), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_BootFileName)
{
    int comparisonResult = 0;
    const char *ParamName = "BootFileName";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    strncpy(Info.BootFileName, "d11_v_cgm4331comims_gigabit_c02.cm", sizeof(Info.BootFileName) - 1);
    Info.BootFileName[sizeof(Info.BootFileName) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetDHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDHCPInfo(NULL, &Info), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_TimeServer)
{
    int comparisonResult = 0;
    const char *ParamName = "TimeServer";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetDHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDHCPInfo(NULL, &Info), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_RebindTimeRemaining)
{
    int comparisonResult = 0;
    const char *ParamName = "RebindTimeRemaining";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetDHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDHCPInfo(NULL, &Info), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_RenewTimeRemaining)
{
    int comparisonResult = 0;
    const char *ParamName = "RenewTimeRemaining";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetDHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDHCPInfo(NULL, &Info), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_DOCSISDHCPStatus)
{
    int comparisonResult = 0;
    const char *ParamName = "DOCSISDHCPStatus";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetDHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDHCPInfo(NULL, &Info), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_CMStatus)
{
    int comparisonResult = 0;
    const char *ParamName = "CMStatus";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_getCMStatus(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetStatus(NULL, pValue), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_DOCSISVersion)
{
    int comparisonResult = 0;
    const char *ParamName = "DOCSISVersion";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_DOCSISDownstreamScanning)
{
    int comparisonResult = 0;
    const char *ParamName = "DOCSISDownstreamScanning";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_DOCSISDownstreamRanging)
{
    int comparisonResult = 0;
    const char *ParamName = "DOCSISDownstreamRanging";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_DOCSISUpstreamScanning)
{
    int comparisonResult = 0;
    const char *ParamName = "DOCSISUpstreamScanning";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_DOCSISUpstreamRanging)
{
    int comparisonResult = 0;
    const char *ParamName = "DOCSISUpstreamRanging";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_DOCSISTftpStatus)
{
    int comparisonResult = 0;
    const char *ParamName = "DOCSISTftpStatus";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_DOCSISDataRegComplete)
{
    int comparisonResult = 0;
    const char *ParamName = "DOCSISDataRegComplete";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_CoreVersion)
{
    int comparisonResult = 0;
    const char *ParamName = "CoreVersion";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_DOCSISConfigFileName)
{
    int comparisonResult = 0;
    const char *ParamName = "DOCSISConfigFileName";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_ToDStatus)
{
    int comparisonResult = 0;
    const char *ParamName = "ToDStatus";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_UpstreamServiceFlowParams)
{
    int comparisonResult = 0;
    const char *ParamName = "UpstreamServiceFlowParams";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_DownstreamServiceFlowParams)
{
    int comparisonResult = 0;
    const char *ParamName = "DownstreamServiceFlowParams";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_DOCSISDownstreamDataRate)
{
    int comparisonResult = 0;
    const char *ParamName = "DOCSISDownstreamDataRate";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_DOCSISUpstreamDataRate)
{
    int comparisonResult = 0;
    const char *ParamName = "DOCSISUpstreamDataRate";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamDataRate"),
                                               strlen("DOCSISUpstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDOCSISInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetDOCSISInfo(NULL, &DInfo), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_LoopDiagnosticsDetails)
{
    int comparisonResult = 0;
    const char *ParamName = "LoopDiagnosticsDetails";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamDataRate"),
                                               strlen("DOCSISUpstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsDetails"),
                                               strlen("LoopDiagnosticsDetails"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(CosaDmlCMGetLoopDiagnosticsDetails(NULL, pValue), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_Market)
{
    int comparisonResult = 0;
    const char *ParamName = "Market";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamDataRate"),
                                               strlen("DOCSISUpstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsDetails"),
                                               strlen("LoopDiagnosticsDetails"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Market"),
                                               strlen("Market"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetMarket(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetMarket(NULL, pValue), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_MDDIPOverride)
{
    int comparisonResult = 0;
    const char *ParamName = "MDDIPOverride";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamDataRate"),
                                               strlen("DOCSISUpstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsDetails"),
                                               strlen("LoopDiagnosticsDetails"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Market"),
                                               strlen("Market"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetMddIpModeOverride(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetMDDIPOverride(NULL, pValue), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_IPv6Address)
{
    int comparisonResult = 0;
    const char *ParamName = "IPv6Address";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamDataRate"),
                                               strlen("DOCSISUpstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsDetails"),
                                               strlen("LoopDiagnosticsDetails"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Market"),
                                               strlen("Market"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Address"),
                                               strlen("IPv6Address"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetIPv6DHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetIPv6DHCPInfo(NULL, &IPV6Info), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_IPv6BootFileName)
{
    int comparisonResult = 0;
    const char *ParamName = "IPv6BootFileName";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamDataRate"),
                                               strlen("DOCSISUpstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsDetails"),
                                               strlen("LoopDiagnosticsDetails"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Market"),
                                               strlen("Market"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Address"),
                                               strlen("IPv6Address"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6BootFileName"),
                                               strlen("IPv6BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetIPv6DHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetIPv6DHCPInfo(NULL, &IPV6Info), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_IPv6Prefix)
{
    int comparisonResult = 0;
    const char *ParamName = "IPv6Prefix";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamDataRate"),
                                               strlen("DOCSISUpstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsDetails"),
                                               strlen("LoopDiagnosticsDetails"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Market"),
                                               strlen("Market"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Address"),
                                               strlen("IPv6Address"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6BootFileName"),
                                               strlen("IPv6BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Prefix"),
                                               strlen("IPv6Prefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetIPv6DHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetIPv6DHCPInfo(NULL, &IPV6Info), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_IPv6Router)
{
    int comparisonResult = 0;
    const char *ParamName = "IPv6Router";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamDataRate"),
                                               strlen("DOCSISUpstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsDetails"),
                                               strlen("LoopDiagnosticsDetails"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Market"),
                                               strlen("Market"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Address"),
                                               strlen("IPv6Address"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6BootFileName"),
                                               strlen("IPv6BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Prefix"),
                                               strlen("IPv6Prefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Router"),
                                               strlen("IPv6Router"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetIPv6DHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetIPv6DHCPInfo(NULL, &IPV6Info), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_IPv6TFTPServer)
{
    int comparisonResult = 0;
    const char *ParamName = "IPv6TFTPServer";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamDataRate"),
                                               strlen("DOCSISUpstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsDetails"),
                                               strlen("LoopDiagnosticsDetails"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Market"),
                                               strlen("Market"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Address"),
                                               strlen("IPv6Address"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6BootFileName"),
                                               strlen("IPv6BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Prefix"),
                                               strlen("IPv6Prefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Router"),
                                               strlen("IPv6Router"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6TFTPServer"),
                                               strlen("IPv6TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetIPv6DHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetIPv6DHCPInfo(NULL, &IPV6Info), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_IPv6TimeServer)
{
    int comparisonResult = 0;
    const char *ParamName = "IPv6TimeServer";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamDataRate"),
                                               strlen("DOCSISUpstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsDetails"),
                                               strlen("LoopDiagnosticsDetails"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Market"),
                                               strlen("Market"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Address"),
                                               strlen("IPv6Address"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6BootFileName"),
                                               strlen("IPv6BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Prefix"),
                                               strlen("IPv6Prefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Router"),
                                               strlen("IPv6Router"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6TFTPServer"),
                                               strlen("IPv6TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6TimeServer"),
                                               strlen("IPv6TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_GetIPv6DHCPInfo(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetIPv6DHCPInfo(NULL, &IPV6Info), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_TelephonyDHCPStatus)
{
    int comparisonResult = 0;
    const char *ParamName = "TelephonyDHCPStatus";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamDataRate"),
                                               strlen("DOCSISUpstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsDetails"),
                                               strlen("LoopDiagnosticsDetails"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Market"),
                                               strlen("Market"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Address"),
                                               strlen("IPv6Address"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6BootFileName"),
                                               strlen("IPv6BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Prefix"),
                                               strlen("IPv6Prefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Router"),
                                               strlen("IPv6Router"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6TFTPServer"),
                                               strlen("IPv6TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6TimeServer"),
                                               strlen("IPv6TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TelephonyDHCPStatus"),
                                               strlen("TelephonyDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(CosaDmlCMGetTelephonyDHCPStatus(NULL, pValue), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_TelephonyTftpStatus)
{
    int comparisonResult = 0;
    const char *ParamName = "TelephonyTftpStatus";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamDataRate"),
                                               strlen("DOCSISUpstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsDetails"),
                                               strlen("LoopDiagnosticsDetails"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Market"),
                                               strlen("Market"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Address"),
                                               strlen("IPv6Address"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6BootFileName"),
                                               strlen("IPv6BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Prefix"),
                                               strlen("IPv6Prefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Router"),
                                               strlen("IPv6Router"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6TFTPServer"),
                                               strlen("IPv6TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6TimeServer"),
                                               strlen("IPv6TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TelephonyDHCPStatus"),
                                               strlen("TelephonyDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TelephonyTftpStatus"),
                                               strlen("TelephonyTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(CosaDmlCMGetTelephonyTftpStatus(NULL, pValue), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_TelephonyRegistrationStatus)
{
    int comparisonResult = 0;
    const char *ParamName = "TelephonyRegistrationStatus";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamDataRate"),
                                               strlen("DOCSISUpstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsDetails"),
                                               strlen("LoopDiagnosticsDetails"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Market"),
                                               strlen("Market"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Address"),
                                               strlen("IPv6Address"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6BootFileName"),
                                               strlen("IPv6BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Prefix"),
                                               strlen("IPv6Prefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Router"),
                                               strlen("IPv6Router"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6TFTPServer"),
                                               strlen("IPv6TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6TimeServer"),
                                               strlen("IPv6TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TelephonyDHCPStatus"),
                                               strlen("TelephonyDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TelephonyTftpStatus"),
                                               strlen("TelephonyTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TelephonyRegistrationStatus"),
                                               strlen("TelephonyRegistrationStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(CosaDmlCMGetTelephonyTftpStatus(NULL, pValue), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_DOCSISCertificate)
{
    int comparisonResult = 0;
    const char *ParamName = "DOCSISCertificate";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamDataRate"),
                                               strlen("DOCSISUpstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsDetails"),
                                               strlen("LoopDiagnosticsDetails"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Market"),
                                               strlen("Market"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Address"),
                                               strlen("IPv6Address"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6BootFileName"),
                                               strlen("IPv6BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Prefix"),
                                               strlen("IPv6Prefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Router"),
                                               strlen("IPv6Router"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6TFTPServer"),
                                               strlen("IPv6TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6TimeServer"),
                                               strlen("IPv6TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TelephonyDHCPStatus"),
                                               strlen("TelephonyDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TelephonyTftpStatus"),
                                               strlen("TelephonyTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TelephonyRegistrationStatus"),
                                               strlen("TelephonyRegistrationStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISCertificate"),
                                               strlen("DOCSISCertificate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetCert(pValue))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCmGetCMCert(NULL, pValue), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_GetParamStringValue_ProvIpType)
{
    int comparisonResult = 0;
    const char *ParamName = "ProvIpType";
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    COSA_CM_DHCP_INFO               Info;
    COSA_CM_DOCSIS_INFO             DInfo;
    COSA_CM_IPV6DHCP_INFO           IPV6Info;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("BootFileName"),
                                               strlen("BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeServer"),
                                               strlen("TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RebindTimeRemaining"),
                                               strlen("RebindTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RenewTimeRemaining"),
                                               strlen("RenewTimeRemaining"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDHCPStatus"),
                                               strlen("DOCSISDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CMStatus"),
                                               strlen("CMStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISVersion"),
                                               strlen("DOCSISVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamScanning"),
                                               strlen("DOCSISDownstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamRanging"),
                                               strlen("DOCSISDownstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamScanning"),
                                               strlen("DOCSISUpstreamScanning"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamRanging"),
                                               strlen("DOCSISUpstreamRanging"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISTftpStatus"),
                                               strlen("DOCSISTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDataRegComplete"),
                                               strlen("DOCSISDataRegComplete"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CoreVersion"),
                                               strlen("CoreVersion"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISConfigFileName"),
                                               strlen("DOCSISConfigFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ToDStatus"),
                                               strlen("ToDStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamServiceFlowParams"),
                                               strlen("UpstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamServiceFlowParams"),
                                               strlen("DownstreamServiceFlowParams"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISDownstreamDataRate"),
                                               strlen("DOCSISDownstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISUpstreamDataRate"),
                                               strlen("DOCSISUpstreamDataRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsDetails"),
                                               strlen("LoopDiagnosticsDetails"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Market"),
                                               strlen("Market"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Address"),
                                               strlen("IPv6Address"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6BootFileName"),
                                               strlen("IPv6BootFileName"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Prefix"),
                                               strlen("IPv6Prefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6Router"),
                                               strlen("IPv6Router"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6TFTPServer"),
                                               strlen("IPv6TFTPServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPv6TimeServer"),
                                               strlen("IPv6TimeServer"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TelephonyDHCPStatus"),
                                               strlen("TelephonyDHCPStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TelephonyTftpStatus"),
                                               strlen("TelephonyTftpStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TelephonyRegistrationStatus"),
                                               strlen("TelephonyRegistrationStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DOCSISCertificate"),
                                               strlen("DOCSISCertificate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ProvIpType"),
                                               strlen("ProvIpType"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_GetProvIpType(pValue))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMGetProvType(NULL, pValue), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamBoolValue_LoopDiagnosticsStart_Enable)
{
    const char *ParamName = "LoopDiagnosticsStart";
    BOOL bValue = TRUE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    pMyObject->LoopDiagnosticsStart = bValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamBoolValue(NULL, (char*)ParamName, bValue), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamBoolValue_LoopDiagnosticsStart_Disable)
{
    const char *ParamName = "LoopDiagnosticsStart";
    BOOL bValue = FALSE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    pMyObject->LoopDiagnosticsStart = bValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamBoolValue(NULL, (char*)ParamName, bValue), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamBoolValue_EnableLog_Enable)
{
    const char *ParamName = "EnableLog";
    BOOL bValue = TRUE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    pCfg->EnableLog = bValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EnableLog"),
                                               strlen("EnableLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamBoolValue(NULL, (char*)ParamName, bValue), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamBoolValue_EnableLog_Disable)
{
    const char *ParamName = "EnableLog";
    BOOL bValue = FALSE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    pCfg->EnableLog = bValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EnableLog"),
                                               strlen("EnableLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamBoolValue(NULL, (char*)ParamName, bValue), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamBoolValue_CleanDocsisLog_Enable)
{
    const char *ParamName = "CleanDocsisLog";
    BOOL bValue = TRUE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    pCfg->CleanDocsisLog = bValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EnableLog"),
                                               strlen("EnableLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CleanDocsisLog"),
                                               strlen("CleanDocsisLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamBoolValue(NULL, (char*)ParamName, bValue), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamBoolValue_CleanDocsisLog_Disable)
{
    const char *ParamName = "CleanDocsisLog";
    BOOL bValue = FALSE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    pCfg->CleanDocsisLog = bValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EnableLog"),
                                               strlen("EnableLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CleanDocsisLog"),
                                               strlen("CleanDocsisLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamBoolValue(NULL, (char*)ParamName, bValue), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamBoolValue_ConfigureWan_Enable)
{
    const char *ParamName = "ConfigureWan";
    BOOL bValue = TRUE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    PCOSA_DML_CM_WANCFG pWanCfg = &pMyObject->CmWanCfg;

    pWanCfg->ConfigureWan = bValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EnableLog"),
                                               strlen("EnableLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CleanDocsisLog"),
                                               strlen("CleanDocsisLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigureWan"),
                                               strlen("ConfigureWan"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamBoolValue(NULL, (char*)ParamName, bValue), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamBoolValue_ConfigureWan_Disable)
{
    const char *ParamName = "ConfigureWan";
    BOOL bValue = FALSE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    PCOSA_DML_CM_WANCFG pWanCfg = &pMyObject->CmWanCfg;

    pWanCfg->ConfigureWan = bValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EnableLog"),
                                               strlen("EnableLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CleanDocsisLog"),
                                               strlen("CleanDocsisLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigureWan"),
                                               strlen("ConfigureWan"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamBoolValue(NULL, (char*)ParamName, bValue), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamBoolValue_CustomWanConfigUpdate_Enable)
{
    const char *ParamName = "CustomWanConfigUpdate";
    BOOL bValue = TRUE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    PCOSA_DML_CM_WANCFG pWanCfg = &pMyObject->CmWanCfg;

    pWanCfg->CustomWanConfigUpdate = bValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EnableLog"),
                                               strlen("EnableLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CleanDocsisLog"),
                                               strlen("CleanDocsisLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigureWan"),
                                               strlen("ConfigureWan"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CustomWanConfigUpdate"),
                                               strlen("CustomWanConfigUpdate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(_, _))
        .Times(12)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMWanUpdateCustomConfig(pMyObject, bValue), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamBoolValue(NULL, (char*)ParamName, bValue), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamBoolValue_CustomWanConfigUpdate_Disable)
{
    const char *ParamName = "CustomWanConfigUpdate";
    BOOL bValue = FALSE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    PCOSA_DML_CM_WANCFG pWanCfg = &pMyObject->CmWanCfg;

    pWanCfg->ConfigureWan = bValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoopDiagnosticsStart"),
                                               strlen("LoopDiagnosticsStart"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EnableLog"),
                                               strlen("EnableLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CleanDocsisLog"),
                                               strlen("CleanDocsisLog"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigureWan"),
                                               strlen("ConfigureWan"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CustomWanConfigUpdate"),
                                               strlen("CustomWanConfigUpdate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(_, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCMWanUpdateCustomConfig(pMyObject, bValue), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamBoolValue(NULL, (char*)ParamName, bValue), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamIntValue)
{
    const char *ParamName = "LoopDiagnosticsStart";
    int iValue = 1;

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamIntValue(NULL, (char*)ParamName, iValue), FALSE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamUlongValue_LockedUpstreamChID)
{
    const char *ParamName = "LockedUpstreamChID";
    ULONG uValue = 1;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LockedUpstreamChID"),
                                               strlen("LockedUpstreamChID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_SetUSChannelId((int)uValue))
        .Times(2);

    EXPECT_EQ(CosaDmlCMSetLockedUpstreamChID(NULL, uValue), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamUlongValue(NULL, (char*)ParamName, uValue), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamUlongValue_StartDSFrequency)
{
    const char *ParamName = "StartDSFrequency";
    ULONG uValue = 1;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LockedUpstreamChID"),
                                               strlen("LockedUpstreamChID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("StartDSFrequency"),
                                               strlen("StartDSFrequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, docsis_SetStartFreq(uValue))
        .Times(2);

    EXPECT_EQ(CosaDmlCMSetStartDSFrequency(NULL, uValue), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamUlongValue(NULL, (char*)ParamName, uValue), TRUE);
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamStringValue_MDDIPOverride)
{
    const char *ParamName = "MDDIPOverride";
    char pString[256] = "honorMdd";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_WANCFG pWanCfg = &pMyObject->CmWanCfg;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamStringValue(NULL, (char*)ParamName, pString), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamStringValue_RequestPhyStatus)
{
    const char *ParamName = "RequestPhyStatus";
    char pString[256] = "1";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_WANCFG pWanCfg = &pMyObject->CmWanCfg;

    pWanCfg->MonitorPhyStatusAndNotify = FALSE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RequestPhyStatus"),
                                               strlen("RequestPhyStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamStringValue(NULL, (char*)ParamName, pString), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamStringValue_RequestOperationalStatus)
{
    const char *ParamName = "RequestOperationalStatus";
    char pString[256] = "1";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_WANCFG pWanCfg = &pMyObject->CmWanCfg;

    pWanCfg->MonitorOperStatusAndNotify = FALSE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RequestPhyStatus"),
                                               strlen("RequestPhyStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RequestOperationalStatus"),
                                               strlen("RequestOperationalStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamStringValue(NULL, (char*)ParamName, pString), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_SetParamStringValue_PostCfgWanFinalize)
{
    const char *ParamName = "PostCfgWanFinalize";
    char pString[256] = "1";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_WANCFG pWanCfg = &pMyObject->CmWanCfg;

    pWanCfg->MonitorOperStatusAndNotify = FALSE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MDDIPOverride"),
                                               strlen("MDDIPOverride"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RequestPhyStatus"),
                                               strlen("RequestPhyStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RequestOperationalStatus"),
                                               strlen("RequestOperationalStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PostCfgWanFinalize"),
                                               strlen("PostCfgWanFinalize"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(X_CISCO_COM_CableModem_SetParamStringValue(NULL, (char*)ParamName, pString), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_Validate)
{
    char pReturnParamName[256] = "MDDIPOverride";
    ULONG uLength = 1;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    EXPECT_EQ(X_CISCO_COM_CableModem_Validate(NULL, pReturnParamName, &uLength), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

/*
ULONG
X_CISCO_COM_CableModem_Commit
    (
        ANSC_HANDLE                 hInsContext
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
    ANSC_STATUS                     returnStatus  = ANSC_STATUS_SUCCESS;        
    PCOSA_DATAMODEL_CABLEMODEM      pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;
    PCOSA_DML_CM_LOG                pCfg      = &pMyObject->CmLog;

    if(pCfg->CleanDocsisLog == 1)
    {
        CosaDmlCmSetLog(NULL,pCfg);
        g_DocsisLog_clean_flg = 1;
        return 0;
    }

    CosaDmlCMSetMDDIPOverride(NULL, pMyObject->MDDIPOverride);

    returnStatus = CosaDmlCMSetLoopDiagnosticsStart(NULL, pMyObject->LoopDiagnosticsStart);
    
    if ( returnStatus == ANSC_STATUS_SUCCESS )
    {
        CosaDmlCmSetLog(NULL, pCfg);

        return 0;
    }
    else
    {
        return -1;
    }    
}


*/

// write the GTEST test case for the X_CISCO_COM_CableModem_Commit

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_Commit_CleanDocsisLog)
{
    ANSC_HANDLE hInsContext = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    pCfg->CleanDocsisLog = 1;

    EXPECT_CALL(*g_cmHALMock, docsis_ClearDocsisEventLog())
        .Times(1);


    EXPECT_EQ(X_CISCO_COM_CableModem_Commit(hInsContext), 0);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;

}


TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_Commit_MDDIPOverride)
{
    ANSC_HANDLE hInsContext = NULL;
    char pString[256] = "honorMdd";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    int g_DocsisLog_clean_flg = 0;

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    strncpy(pMyObject->MDDIPOverride, pString, sizeof(pMyObject->MDDIPOverride) - 1);
    pMyObject->MDDIPOverride[sizeof(pMyObject->MDDIPOverride) - 1] = '\0'; // Ensure null-termination

    EXPECT_CALL(*g_cmHALMock, docsis_SetMddIpModeOverride(_))
        .Times(2);

    EXPECT_EQ(CosaDmlCMSetMDDIPOverride(NULL, pMyObject->MDDIPOverride), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_Commit(hInsContext), 0);

    EXPECT_EQ(g_DocsisLog_clean_flg, 0);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_Commit_CosaDmlCMSetLoopDiagnosticsStart)
{
    ANSC_HANDLE hInsContext = NULL;
    char pString[256] = "honorMdd";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;

    pCfg->CleanDocsisLog = 0;

    pMyObject->LoopDiagnosticsStart = TRUE;

    strncpy(pMyObject->MDDIPOverride, pString, sizeof(pMyObject->MDDIPOverride) - 1);
    pMyObject->MDDIPOverride[sizeof(pMyObject->MDDIPOverride) - 1] = '\0';

    EXPECT_CALL(*g_cmHALMock, docsis_SetMddIpModeOverride(_))
        .Times(1);

    EXPECT_EQ(CosaDmlCMSetLoopDiagnosticsStart(NULL, pMyObject->LoopDiagnosticsStart), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_Commit(hInsContext), 0);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_Rollback_True_CosaDmlCMGetLoopDiagnosticsStart)
{
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->LoopDiagnosticsStart = TRUE;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;
    
    EXPECT_EQ(CosaDmlCMGetLoopDiagnosticsStart(NULL, &pMyObject->LoopDiagnosticsStart), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_Rollback(NULL), 0);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlFirstTestFixture, X_CISCO_COM_CableModem_Rollback_True_CosaDmlCmGetLog)
{
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;
 
    pMyObject->LoopDiagnosticsStart = TRUE;

    PCOSA_DML_CM_LOG pCfg = &pMyObject->CmLog;
    
    EXPECT_EQ(CosaDmlCmGetLog(NULL, pCfg), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_CISCO_COM_CableModem_Rollback(NULL), 0);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}