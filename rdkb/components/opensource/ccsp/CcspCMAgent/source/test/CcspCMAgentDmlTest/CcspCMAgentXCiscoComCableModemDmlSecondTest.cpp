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

class CcspCMAgentXCiscoComCableModemDmlTestSecondFixture : public ::testing::Test {
protected:
    void SetUp() override {
        g_syscfgMock = new SyscfgMock();
        g_securewrapperMock = new SecureWrapperMock();
        g_msgpackMock = new msgpackMock();
        g_usertimeMock = new UserTimeMock();
        g_safecLibMock = new SafecLibMock();
        g_anscMemoryMock = new AnscMemoryMock();
        g_baseapiMock = new BaseAPIMock();
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
        delete g_syscfgMock;
        delete g_securewrapperMock;
        delete g_msgpackMock;
        delete g_usertimeMock;
        delete g_safecLibMock;
        delete g_anscMemoryMock;
        delete g_baseapiMock;
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
        g_syscfgMock = nullptr;
        g_securewrapperMock = nullptr;
        g_msgpackMock = nullptr;
        g_usertimeMock = nullptr;
        g_safecLibMock = nullptr;
        g_anscMemoryMock = nullptr;
        g_baseapiMock = nullptr;
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

// Unit Test for cosa_x_cisco_com_cablemodem_dml.c 2 file


TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, CMErrorCodewords_GetEntryCount)
{
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    ULONG actualValue = CMErrorCodewords_GetEntryCount(NULL);
    std::cout << "CMErrorCodewords_GetEntryCount returned: " << actualValue << std::endl; // Print the value
    EXPECT_GE(actualValue, 0);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, CMErrorCodewords_IsUpdated_TimeZero)
{
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->CMErrorCodewordsUpdateTime = 0;

    EXPECT_CALL(*g_usertimeMock, UserGetTickInSeconds2())
        .Times(1)
        .WillOnce(Return(0));

    BOOL actualValue = CMErrorCodewords_IsUpdated(NULL);
    printf("CMErrorCodewords_IsUpdated returned: %d\n", actualValue); // Print the value
    EXPECT_EQ(actualValue, TRUE);
    
    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, CMErrorCodewords_Synchronize)
{
    ANSC_HANDLE hInsContext = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->pCMErrorCodewords = (PCOSA_DML_CMERRORCODEWORDS_FULL)malloc(sizeof(COSA_DML_CMERRORCODEWORDS_FULL));
    ASSERT_NE(pMyObject->pCMErrorCodewords, nullptr);
    
    pMyObject->CMErrorCodewordsNumber = 30;

    EXPECT_CALL(*g_cmHALMock, docsis_GetNumOfActiveRxChannels(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_cmHALMock, docsis_GetErrorCodewords(_))
        .Times(1)
        .WillOnce(Return(0));
    
    EXPECT_CALL(*g_anscMemoryMock, AnscFreeMemoryOrig(_))
        .Times(1);

    EXPECT_EQ(CosaDmlCmGetCMErrorCodewords(NULL, &pMyObject->CMErrorCodewordsNumber, &pMyObject->pCMErrorCodewords), ANSC_STATUS_SUCCESS);

    ULONG status = CMErrorCodewords_Synchronize(NULL);
    printf("CMErrorCodewords_Synchronize returned: %lu\n", status); // Print the value
    EXPECT_EQ(status, 0);

    free(pMyObject->pCMErrorCodewords);
    pMyObject->pCMErrorCodewords = NULL;
    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, CMErrorCodewords_GetParamUlongValue_UnerroredCodewords)
{
    const char ParamName[256] = "UnerroredCodewords";
    ULONG uValue = 602032005;

    PCOSA_DML_CMERRORCODEWORDS_FULL pConf = (PCOSA_DML_CMERRORCODEWORDS_FULL)malloc(sizeof(COSA_DML_CMERRORCODEWORDS_FULL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    pConf->UnerroredCodewords = uValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UnerroredCodewords"),
                                               strlen("UnerroredCodewords"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    BOOL result = CMErrorCodewords_GetParamUlongValue(hInsContext, (char*)ParamName, &uValue);
    printf("CMErrorCodewords_GetParamUlongValue for UnerroredCodewords returned: %d, uValue: %lu\n", result, uValue);
    EXPECT_EQ(result, TRUE);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, CMErrorCodewords_GetParamUlongValue_CorrectableCodewords)
{
    const char ParamName[256] = "CorrectableCodewords";
    ULONG uValue = 1;

    PCOSA_DML_CMERRORCODEWORDS_FULL pConf = (PCOSA_DML_CMERRORCODEWORDS_FULL)malloc(sizeof(COSA_DML_CMERRORCODEWORDS_FULL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    pConf->CorrectableCodewords = uValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UnerroredCodewords"),
                                               strlen("UnerroredCodewords"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CorrectableCodewords"),
                                               strlen("CorrectableCodewords"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    BOOL result = CMErrorCodewords_GetParamUlongValue(hInsContext, (char*)ParamName, &uValue);
    printf("CMErrorCodewords_GetParamUlongValue for CorrectableCodewords returned: %d, uValue: %lu\n", result, uValue);
    EXPECT_EQ(result, TRUE);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, CMErrorCodewords_GetParamUlongValue_UncorrectableCodewords)
{
    const char ParamName[256] = "UncorrectableCodewords";
    ULONG uValue = 1;

    PCOSA_DML_CMERRORCODEWORDS_FULL pConf = (PCOSA_DML_CMERRORCODEWORDS_FULL)malloc(sizeof(COSA_DML_CMERRORCODEWORDS_FULL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    pConf->UncorrectableCodewords = uValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UnerroredCodewords"),
                                               strlen("UnerroredCodewords"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CorrectableCodewords"),
                                               strlen("CorrectableCodewords"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UncorrectableCodewords"),
                                               strlen("UncorrectableCodewords"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    BOOL result = CMErrorCodewords_GetParamUlongValue(hInsContext, (char*)ParamName, &uValue);
    printf("CMErrorCodewords_GetParamUlongValue for UncorrectableCodewords returned: %d, uValue: %lu\n", result, uValue);
    EXPECT_EQ(result, TRUE);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, CMErrorCodewords_GetParamStringValue)
{
    const char ParamName[256] = "UnerroredCodewords";
    char pValue[256] = "UnerroredCodewords";
    ULONG uSize = 256;

    PCOSA_DML_CMERRORCODEWORDS_FULL pConf = (PCOSA_DML_CMERRORCODEWORDS_FULL)malloc(sizeof(COSA_DML_CMERRORCODEWORDS_FULL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    ULONG result = CMErrorCodewords_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize);
    printf("CMErrorCodewords_GetParamStringValue for UnerroredCodewords returned: %lu, pValue: %s, uSize: %lu\n", result, pValue, uSize);
    EXPECT_GE(result, 0);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DocsisLog_GetEntryCount)
{
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->DocsisLogNumber = 10;
    ULONG expectedValue = pMyObject->DocsisLogNumber;

    ULONG actualValue = DocsisLog_GetEntryCount(NULL);
    EXPECT_EQ(actualValue, expectedValue);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DocsisLog_GetEntry)
{
    ULONG nIndex = 1;
    ULONG pInsNumber = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->pDocsisLog = (PCOSA_DML_DOCSISLOG_FULL)malloc(sizeof(COSA_DML_DOCSISLOG_FULL));
    ASSERT_NE(pMyObject->pDocsisLog, nullptr);

    ANSC_HANDLE status = DocsisLog_GetEntry(NULL, nIndex, &pInsNumber);
    EXPECT_NE(status, nullptr);

    free(pMyObject->pDocsisLog);
    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DocsisLog_IsUpdated_TimeZero)
{
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->DocsisLogUpdateTime = 0;
    int g_DocsisLog_clean_flg = 1;

    EXPECT_CALL(*g_usertimeMock, UserGetTickInSeconds2())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(DocsisLog_IsUpdated(NULL), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DocsisLog_IsUpdated_TimeGreaterThenZero)
{
    ULONG uValue = 700;
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->DocsisLogUpdateTime = uValue;

    EXPECT_CALL(*g_usertimeMock, UserGetTickInSeconds2())
        .Times(3)
        .WillRepeatedly(Return(1000));

    EXPECT_EQ(DocsisLog_IsUpdated(NULL), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DocsisLog_Synchronize)
{
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->pDocsisLog = (PCOSA_DML_DOCSISLOG_FULL)malloc(sizeof(COSA_DML_DOCSISLOG_FULL));
    ASSERT_NE(pMyObject->pDocsisLog, nullptr);
    
    pMyObject->DocsisLogNumber = 0;
    
    EXPECT_CALL(*g_cmHALMock, docsis_GetDocsisEventLogItems(_,_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlCmGetDocsisLog(NULL, &pMyObject->DocsisLogNumber, &pMyObject->pDocsisLog), ANSC_STATUS_SUCCESS);
    
    pMyObject->pDocsisLog = NULL;

    ULONG status = DocsisLog_Synchronize(NULL);
    EXPECT_EQ(status, 0);

    free(pMyObject->pDocsisLog);
    pMyObject->pDocsisLog = NULL;
    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DocsisLog_GetParamUlongValue_Index)
{
    const char ParamName[256] = "Index";
    ULONG uValue = 1;

    PCOSA_DML_DOCSISLOG_FULL pConf = (PCOSA_DML_DOCSISLOG_FULL)malloc(sizeof(COSA_DML_DOCSISLOG_FULL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    pConf->Index = uValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Index"),
                                               strlen("Index"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(DocsisLog_GetParamUlongValue(hInsContext, (char*)ParamName, &uValue), TRUE);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DocsisLog_GetParamUlongValue_EventID)
{
    const char ParamName[256] = "EventID";
    ULONG uValue = 1;

    PCOSA_DML_DOCSISLOG_FULL pConf = (PCOSA_DML_DOCSISLOG_FULL)malloc(sizeof(COSA_DML_DOCSISLOG_FULL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    pConf->EventID = uValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Index"),
                                               strlen("Index"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EventID"),
                                               strlen("EventID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(DocsisLog_GetParamUlongValue(hInsContext, (char*)ParamName, &uValue), TRUE);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DocsisLog_GetParamUlongValue_EventLevel)
{
    const char ParamName[256] = "EventLevel";
    ULONG uValue = 1;

    PCOSA_DML_DOCSISLOG_FULL pConf = (PCOSA_DML_DOCSISLOG_FULL)malloc(sizeof(COSA_DML_DOCSISLOG_FULL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    pConf->EventLevel = uValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Index"),
                                               strlen("Index"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EventID"),
                                               strlen("EventID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EventLevel"),
                                               strlen("EventLevel"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(DocsisLog_GetParamUlongValue(hInsContext, (char*)ParamName, &uValue), TRUE);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DocsisLog_GetParamStringValue_Description)
{
    const char ParamName[256] = "Description";
    char pValue[256] = "CM-STATUS message sent. Event Type Code: 5; Chan ID: 28 29 30; DSID: N/A; MAC Addr: N/A; OFDM/OFDMA Profile ID: N/A.;CM-MAC=1c:9e:cc:21:7c:84;CMTS-MAC=00:01:5c:8f:9e:46;CM-QOS=1.1;CM-VER=3.1;";
    ULONG uSize = 256;

    PCOSA_DML_DOCSISLOG_FULL pConf = (PCOSA_DML_DOCSISLOG_FULL)malloc(sizeof(COSA_DML_DOCSISLOG_FULL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    strncpy(pConf->Description, pValue, sizeof(pConf->Description) - 1);
    pConf->Description[sizeof(pConf->Description) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Description"),
                                               strlen("Description"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(DocsisLog_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize), 0);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DocsisLog_GetParamStringValue_Time)
{
    const char ParamName[256] = "Time";
    char pValue[256] = "Thu Aug 22 21:13:28 2024";
    ULONG uSize = 256;

    PCOSA_DML_DOCSISLOG_FULL pConf = (PCOSA_DML_DOCSISLOG_FULL)malloc(sizeof(COSA_DML_DOCSISLOG_FULL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    strncpy(pConf->Time, pValue, sizeof(pConf->Time) - 1);
    pConf->Time[sizeof(pConf->Time) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Description"),
                                               strlen("Description"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Time"),
                                               strlen("Time"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));
    EXPECT_EQ(DocsisLog_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize), 0);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DownstreamChannel_GetEntryCount)
{
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->DownstreamChannelNumber = 10;
    ULONG expectedValue = pMyObject->DownstreamChannelNumber;

    ULONG actualValue = DownstreamChannel_GetEntryCount(NULL);
    EXPECT_EQ(actualValue, expectedValue);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DownstreamChannel_GetEntry)
{
    ULONG nIndex = 1;
    ULONG pInsNumber = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->pDownstreamChannel = (PCOSA_CM_DS_CHANNEL)malloc(sizeof(COSA_CM_DS_CHANNEL));
    ASSERT_NE(pMyObject->pDownstreamChannel, nullptr);

    pMyObject->DownstreamChannelNumber = 10;

    ANSC_HANDLE status = DownstreamChannel_GetEntry(NULL, nIndex, &pInsNumber);
    EXPECT_NE(status, nullptr);

    free(pMyObject->pDownstreamChannel);
    pMyObject->pDownstreamChannel = NULL;
    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DownstreamChannel_IsUpdated_TimeZero)
{
    ULONG uValue = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->DownstreamChannelUpdateTime = uValue;

    EXPECT_CALL(*g_usertimeMock, UserGetTickInSeconds2())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(DownstreamChannel_IsUpdated(NULL), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DownstreamChannel_IsUpdated_TimeGreaterThenZero)
{
    ULONG uValue = 700;
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->DocsisLogUpdateTime = uValue;

    EXPECT_CALL(*g_usertimeMock, UserGetTickInSeconds2())
        .Times(1)
        .WillOnce(Return(1000));

    EXPECT_EQ(DownstreamChannel_IsUpdated(NULL), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DownstreamChannel_Synchronize)
{
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->pDownstreamChannel = (PCOSA_CM_DS_CHANNEL)malloc(sizeof(COSA_CM_DS_CHANNEL));
    ASSERT_NE(pMyObject->pDownstreamChannel, nullptr);
    
    pMyObject->DownstreamChannelNumber = 10;
    
    EXPECT_CALL(*g_cmHALMock, docsis_GetNumOfActiveRxChannels(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_cmHALMock, docsis_GetDSChannel(_))
        .Times(1)
        .WillOnce(Return(0));
    
    EXPECT_EQ(CosaDmlCmGetDownstreamChannel(NULL, &pMyObject->DownstreamChannelNumber, &pMyObject->pDownstreamChannel), ANSC_STATUS_SUCCESS);

    pMyObject->pDownstreamChannel = NULL;

    ULONG status = DownstreamChannel_Synchronize(NULL);
    EXPECT_EQ(status, 0);

    free(pMyObject->pDownstreamChannel);
    pMyObject->pDownstreamChannel = NULL;
    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DownstreamChannel_GetParamUlongValue_ChannelID)
{
    const char ParamName[256] = "ChannelID";
    ULONG uValue = 1;

    PCOSA_CM_DS_CHANNEL pConf = (PCOSA_CM_DS_CHANNEL)malloc(sizeof(COSA_CM_DS_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    pConf->ChannelID = uValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(DownstreamChannel_GetParamUlongValue(hInsContext, (char*)ParamName, &uValue), TRUE);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DownstreamChannel_GetParamUlongValue_Octets)
{
    const char ParamName[256] = "Octets";
    ULONG uValue = 1;

    PCOSA_CM_DS_CHANNEL pConf = (PCOSA_CM_DS_CHANNEL)malloc(sizeof(COSA_CM_DS_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    pConf->Octets = uValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Octets"),
                                               strlen("Octets"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(DownstreamChannel_GetParamUlongValue(hInsContext, (char*)ParamName, &uValue), TRUE);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DownstreamChannel_GetParamUlongValue_Correcteds)
{
    const char ParamName[256] = "Correcteds";
    ULONG uValue = 1;

    PCOSA_CM_DS_CHANNEL pConf = (PCOSA_CM_DS_CHANNEL)malloc(sizeof(COSA_CM_DS_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    pConf->Correcteds = uValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Octets"),
                                               strlen("Octets"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Correcteds"),
                                               strlen("Correcteds"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(DownstreamChannel_GetParamUlongValue(hInsContext, (char*)ParamName, &uValue), TRUE);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DownstreamChannel_GetParamUlongValue_Uncorrectables)
{
    const char ParamName[256] = "Uncorrectables";
    ULONG uValue = 1;

    PCOSA_CM_DS_CHANNEL pConf = (PCOSA_CM_DS_CHANNEL)malloc(sizeof(COSA_CM_DS_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    pConf->Uncorrectables = uValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Octets"),
                                               strlen("Octets"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Correcteds"),
                                               strlen("Correcteds"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Uncorrectables"),
                                               strlen("Uncorrectables"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(DownstreamChannel_GetParamUlongValue(hInsContext, (char*)ParamName, &uValue), TRUE);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DownstreamChannel_GetParamStringValue_Frequency)
{
    const char ParamName[256] = "Frequency";
    char pValue[256] = "591000000";
    ULONG uSize = 256;

    PCOSA_CM_DS_CHANNEL pConf = (PCOSA_CM_DS_CHANNEL)malloc(sizeof(COSA_CM_DS_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    strncpy(pConf->Frequency, pValue, sizeof(pConf->Frequency) - 1);
    pConf->Frequency[sizeof(pConf->Frequency) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Frequency"),
                                               strlen("Frequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(DownstreamChannel_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize), 0);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DownstreamChannel_GetParamStringValue_PowerLevel)
{
    const char ParamName[256] = "PowerLevel";
    char pValue[256] = "1.0";
    ULONG uSize = 256;

    PCOSA_CM_DS_CHANNEL pConf = (PCOSA_CM_DS_CHANNEL)malloc(sizeof(COSA_CM_DS_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    strncpy(pConf->PowerLevel, pValue, sizeof(pConf->PowerLevel) - 1);
    pConf->PowerLevel[sizeof(pConf->PowerLevel) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Frequency"),
                                               strlen("Frequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PowerLevel"),
                                               strlen("PowerLevel"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));
    EXPECT_EQ(DownstreamChannel_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize), 0);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DownstreamChannel_GetParamStringValue_SNRLevel)
{
    const char ParamName[256] = "SNRLevel";
    char pValue[256] = "40.0";
    ULONG uSize = 256;

    PCOSA_CM_DS_CHANNEL pConf = (PCOSA_CM_DS_CHANNEL)malloc(sizeof(COSA_CM_DS_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    strncpy(pConf->SNRLevel, pValue, sizeof(pConf->SNRLevel) - 1);
    pConf->SNRLevel[sizeof(pConf->SNRLevel) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Frequency"),
                                               strlen("Frequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PowerLevel"),
                                               strlen("PowerLevel"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SNRLevel"),
                                               strlen("SNRLevel"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));
    EXPECT_EQ(DownstreamChannel_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize), 0);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DownstreamChannel_GetParamStringValue_Modulation)
{
    const char ParamName[256] = "Modulation";
    char pValue[256] = "QAM256";
    ULONG uSize = 256;

    PCOSA_CM_DS_CHANNEL pConf = (PCOSA_CM_DS_CHANNEL)malloc(sizeof(COSA_CM_DS_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    strncpy(pConf->Modulation, pValue, sizeof(pConf->Modulation) - 1);
    pConf->Modulation[sizeof(pConf->Modulation) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Frequency"),
                                               strlen("Frequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PowerLevel"),
                                               strlen("PowerLevel"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SNRLevel"),
                                               strlen("SNRLevel"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Modulation"),
                                               strlen("Modulation"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));
    EXPECT_EQ(DownstreamChannel_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize), 0);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, DownstreamChannel_GetParamStringValue_LockStatus)
{
    const char ParamName[256] = "LockStatus";
    char pValue[256] = "Locked";
    ULONG uSize = 256;

    PCOSA_CM_DS_CHANNEL pConf = (PCOSA_CM_DS_CHANNEL)malloc(sizeof(COSA_CM_DS_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    strncpy(pConf->LockStatus, pValue, sizeof(pConf->LockStatus) - 1);
    pConf->LockStatus[sizeof(pConf->LockStatus) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Frequency"),
                                               strlen("Frequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PowerLevel"),
                                               strlen("PowerLevel"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SNRLevel"),
                                               strlen("SNRLevel"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Modulation"),
                                               strlen("Modulation"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LockStatus"),
                                               strlen("LockStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));
    EXPECT_EQ(DownstreamChannel_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize), 0);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, UpstreamChannel_GetEntryCount)
{
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->UpstreamChannelNumber = 10;
    ULONG expectedValue = pMyObject->UpstreamChannelNumber;

    ULONG actualValue = UpstreamChannel_GetEntryCount(NULL);
    EXPECT_EQ(actualValue, expectedValue);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, UpstreamChannel_GetEntry)
{
    ULONG nIndex = 1;
    ULONG pInsNumber = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->pUpstreamChannel = (PCOSA_CM_US_CHANNEL)malloc(sizeof(COSA_CM_US_CHANNEL));
    ASSERT_NE(pMyObject->pUpstreamChannel, nullptr);

    pMyObject->UpstreamChannelNumber = 10;

    ANSC_HANDLE status = UpstreamChannel_GetEntry(NULL, nIndex, &pInsNumber);
    EXPECT_NE(status, nullptr);

    free(pMyObject->pUpstreamChannel);
    pMyObject->pUpstreamChannel = NULL;
    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, UpstreamChannel_IsUpdated_TimeZero)
{
    ULONG uValue = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->UpstreamChannelUpdateTime = uValue;

    EXPECT_CALL(*g_usertimeMock, UserGetTickInSeconds2())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(UpstreamChannel_IsUpdated(NULL), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, UpstreamChannel_IsUpdated_TimeGreaterThenZero)
{
    ULONG uValue = 700;
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->UpstreamChannelUpdateTime = uValue;

    EXPECT_CALL(*g_usertimeMock, UserGetTickInSeconds2())
        .Times(3)
        .WillRepeatedly(Return(1000));

    EXPECT_EQ(UpstreamChannel_IsUpdated(NULL), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, UpstreamChannel_Synchronize)
{
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->pUpstreamChannel = (PCOSA_CM_US_CHANNEL)malloc(sizeof(COSA_CM_US_CHANNEL));
    ASSERT_NE(pMyObject->pUpstreamChannel, nullptr);
    
    pMyObject->UpstreamChannelNumber = 10;
    
    EXPECT_CALL(*g_cmHALMock, docsis_GetNumOfActiveTxChannels(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_cmHALMock, docsis_GetUSChannel(_))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(CosaDmlCmGetUpstreamChannel(NULL, &pMyObject->UpstreamChannelNumber, &pMyObject->pUpstreamChannel), ANSC_STATUS_SUCCESS);

    pMyObject->pUpstreamChannel = NULL;

    ULONG status = UpstreamChannel_Synchronize(NULL);
    EXPECT_EQ(status, 0);
    
    free(pMyObject->pUpstreamChannel);
    pMyObject->pUpstreamChannel = NULL;
    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, UpstreamChannel_GetParamUlongValue_ChannelID)
{
    const char ParamName[256] = "ChannelID";
    ULONG uValue = 1;

    PCOSA_CM_US_CHANNEL pConf = (PCOSA_CM_US_CHANNEL)malloc(sizeof(COSA_CM_US_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    pConf->ChannelID = uValue;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(UpstreamChannel_GetParamUlongValue(hInsContext, (char*)ParamName, &uValue), TRUE);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, UpstreamChannel_GetParamStringValue_Frequency)
{
    const char ParamName[256] = "Frequency";
    char pValue[256] = "22  MHz";
    ULONG uSize = 256;

    PCOSA_CM_US_CHANNEL pConf = (PCOSA_CM_US_CHANNEL)malloc(sizeof(COSA_CM_US_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    strncpy(pConf->Frequency, pValue, sizeof(pConf->Frequency) - 1);
    pConf->Frequency[sizeof(pConf->Frequency) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Frequency"),
                                               strlen("Frequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(UpstreamChannel_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize), 0);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, UpstreamChannel_GetParamStringValue_PowerLevel)
{
    const char ParamName[256] = "PowerLevel";
    char pValue[256] = "51.8 dBmV";
    ULONG uSize = 256;

    PCOSA_CM_US_CHANNEL pConf = (PCOSA_CM_US_CHANNEL)malloc(sizeof(COSA_CM_US_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    strncpy(pConf->PowerLevel, pValue, sizeof(pConf->PowerLevel) - 1);
    pConf->PowerLevel[sizeof(pConf->PowerLevel) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Frequency"),
                                               strlen("Frequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PowerLevel"),
                                               strlen("PowerLevel"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));
    EXPECT_EQ(UpstreamChannel_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize), 0);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, UpstreamChannel_GetParamStringValue_ChannelType)
{
    const char ParamName[256] = "ChannelType";
    char pValue[256] = "ATDMA";
    ULONG uSize = 256;

    PCOSA_CM_US_CHANNEL pConf = (PCOSA_CM_US_CHANNEL)malloc(sizeof(COSA_CM_US_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    strncpy(pConf->ChannelType, pValue, sizeof(pConf->ChannelType) - 1);
    pConf->ChannelType[sizeof(pConf->ChannelType) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Frequency"),
                                               strlen("Frequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PowerLevel"),
                                               strlen("PowerLevel"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelType"),
                                               strlen("ChannelType"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));
    EXPECT_EQ(UpstreamChannel_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize), 0);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, UpstreamChannel_GetParamStringValue_SymbolRate)
{
    const char ParamName[256] = "SymbolRate";
    char pValue[256] = "5120";
    ULONG uSize = 256;

    PCOSA_CM_US_CHANNEL pConf = (PCOSA_CM_US_CHANNEL)malloc(sizeof(COSA_CM_US_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    strncpy(pConf->SymbolRate, pValue, sizeof(pConf->SymbolRate) - 1);
    pConf->SymbolRate[sizeof(pConf->SymbolRate) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Frequency"),
                                               strlen("Frequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PowerLevel"),
                                               strlen("PowerLevel"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelType"),
                                               strlen("ChannelType"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SymbolRate"),
                                               strlen("SymbolRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));
    EXPECT_EQ(UpstreamChannel_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize), 0);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, UpstreamChannel_GetParamStringValue_Modulation)
{
    const char ParamName[256] = "Modulation";
    char pValue[256] = "QAM";
    ULONG uSize = 256;

    PCOSA_CM_US_CHANNEL pConf = (PCOSA_CM_US_CHANNEL)malloc(sizeof(COSA_CM_US_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    strncpy(pConf->Modulation, pValue, sizeof(pConf->Modulation) - 1);
    pConf->Modulation[sizeof(pConf->Modulation) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Frequency"),
                                               strlen("Frequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PowerLevel"),
                                               strlen("PowerLevel"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelType"),
                                               strlen("ChannelType"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SymbolRate"),
                                               strlen("SymbolRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Modulation"),
                                               strlen("Modulation"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));
    EXPECT_EQ(UpstreamChannel_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize), 0);

    free(pConf);
    pConf = NULL;
}


TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, UpstreamChannel_GetParamStringValue_LockStatus)
{
    const char ParamName[256] = "LockStatus";
    char pValue[256] = "Locked";
    ULONG uSize = 256;

    PCOSA_CM_US_CHANNEL pConf = (PCOSA_CM_US_CHANNEL)malloc(sizeof(COSA_CM_US_CHANNEL));
    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    strncpy(pConf->LockStatus, pValue, sizeof(pConf->LockStatus) - 1);
    pConf->LockStatus[sizeof(pConf->LockStatus) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Frequency"),
                                               strlen("Frequency"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PowerLevel"),
                                               strlen("PowerLevel"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelType"),
                                               strlen("ChannelType"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SymbolRate"),
                                               strlen("SymbolRate"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Modulation"),
                                               strlen("Modulation"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LockStatus"),
                                               strlen("LockStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));
    EXPECT_EQ(UpstreamChannel_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize), 0);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, CPEList_GetEntryCount)
{
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->CPEListNumber = 10;
    ULONG expectedValue = pMyObject->CPEListNumber;

    ULONG actualValue = CPEList_GetEntryCount(NULL);
    EXPECT_EQ(actualValue, expectedValue);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, CPEList_GetEntry)
{
    ULONG nIndex = 1;
    ULONG pInsNumber = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->pCPEList = (PCOSA_DML_CPE_LIST)malloc(sizeof(COSA_DML_CPE_LIST));
    ASSERT_NE(pMyObject->pCPEList, nullptr);

    pMyObject->CPEListNumber = 10;

    ANSC_HANDLE status = CPEList_GetEntry(NULL, nIndex, &pInsNumber);
    EXPECT_NE(status, nullptr);

    free(pMyObject->pCPEList);
    pMyObject->pCPEList = NULL;
    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, CPEList_IsUpdated_TimeZero)
{
    ULONG uValue = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->CPEListUpdateTime = uValue;

    EXPECT_CALL(*g_usertimeMock, UserGetTickInSeconds2())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(CPEList_IsUpdated(NULL), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, CPEList_IsUpdated_TimeGreaterThenZero)
{
    ULONG uValue = 700;
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hCM = (PCOSA_DATAMODEL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hCM, nullptr);

    PCOSA_DATAMODEL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_CABLEMODEM)g_pCosaBEManager->hCM;

    pMyObject->CPEListUpdateTime = uValue;

    EXPECT_CALL(*g_usertimeMock, UserGetTickInSeconds2())
        .Times(3)
        .WillRepeatedly(Return(1000));

    EXPECT_EQ(CPEList_IsUpdated(NULL), TRUE);

    free(g_pCosaBEManager->hCM);
    g_pCosaBEManager->hCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, CPEList_GetParamStringValue_IPAddress)
{
    const char ParamName[256] = "IPAddress";
    char pValue[256] = "192.168.0.12";

    ULONG uSize = 256;

    PCOSA_DML_CPE_LIST pConf = (PCOSA_DML_CPE_LIST)malloc(sizeof(COSA_DML_CPE_LIST));

    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    strncpy(pConf->IPAddress, pValue, sizeof(pConf->IPAddress) - 1);
    pConf->IPAddress[sizeof(pConf->IPAddress) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(CPEList_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize), 0);

    free(pConf);
    pConf = NULL;
}

TEST_F(CcspCMAgentXCiscoComCableModemDmlTestSecondFixture, CPEList_GetParamStringValue_MACAddress)
{
    const char ParamName[256] = "MACAddress";
    char pValue[256] = "00:11:22:33:44:55";

    ULONG uSize = 256;

    PCOSA_DML_CPE_LIST pConf = (PCOSA_DML_CPE_LIST)malloc(sizeof(COSA_DML_CPE_LIST));

    ASSERT_NE(pConf, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pConf;

    strncpy(pConf->MACAddress, pValue, sizeof(pConf->MACAddress) - 1);
    pConf->MACAddress[sizeof(pConf->MACAddress) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IPAddress"),
                                               strlen("IPAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MACAddress"),
                                               strlen("MACAddress"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(CPEList_GetParamStringValue(hInsContext, (char*)ParamName, pValue, &uSize), 0);

    free(pConf);
    pConf = NULL;
}