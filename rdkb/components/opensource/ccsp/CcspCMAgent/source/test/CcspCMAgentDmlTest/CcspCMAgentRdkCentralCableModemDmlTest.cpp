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

class CcspCMAgentRdkCentralCableModemDmlTestFixture : public ::testing::Test {
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

// Unit Test for cosa_x_rdkcentral_com_cablemodem_dml.c

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_IsUpdated) 
{
    ANSC_HANDLE hInsContext = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;
    
    pMyObject->DsOfdmChannelUpdateTime = 0;

    EXPECT_CALL(*g_usertimeMock, UserGetTickInSeconds2())
        .Times(1)
        .WillOnce(Return(0));
    
    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_IsUpdated(hInsContext), 1);

    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_Synchronize) 
{
    ANSC_HANDLE hInsContext = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;
    pMyObject->pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pMyObject->pDsOfdmChannel, nullptr);

    pMyObject->DsOfdmChannelTotalNumbers = 0;

    EXPECT_CALL(*g_anscMemoryMock, AnscFreeMemoryOrig(_))
        .Times(1);

    EXPECT_EQ(CosaDmlRDKCentralCmGetDownstreamChannel(NULL, &pMyObject->DsOfdmChannelTotalNumbers, &pMyObject->pDsOfdmChannel), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_Synchronize(hInsContext), 0);

    free(pMyObject->pDsOfdmChannel);
    pMyObject->pDsOfdmChannel = NULL;
    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetEntryCount) 
{
    ANSC_HANDLE hInsContext = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;
    pMyObject->DsOfdmChannelTotalNumbers = 10;

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetEntryCount(hInsContext), 10);

    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetEntry) 
{
    ANSC_HANDLE hInsContext = NULL;
    ULONG nIndex = 0;
    ULONG pInsNumber = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;
    pMyObject->pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pMyObject->pDsOfdmChannel, nullptr);

    pMyObject->DsOfdmChannelTotalNumbers = 10;

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetEntry(hInsContext, nIndex, &pInsNumber), &pMyObject->pDsOfdmChannel[nIndex]);

    free(pMyObject->pDsOfdmChannel);
    pMyObject->pDsOfdmChannel = NULL;
    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_ChannelID) 
{
    const char *ParamName = "ChannelID";
    ULONG puLong = 10;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;

    pDsOfdmChannel->ChannelId = puLong;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_ChanIndicator) 
{
    const char *ParamName = "ChanIndicator";
    ULONG puLong = 10;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;

    pDsOfdmChannel->ChanIndicator = puLong;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChanIndicator"),
                                               strlen("ChanIndicator"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}


TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_SubcarrierZeroFreq) 
{
    const char *ParamName = "SubcarrierZeroFreq";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;

    pDsOfdmChannel->SubcarrierZeroFreq = puLong;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChanIndicator"),
                                               strlen("ChanIndicator"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}


TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_FirstActiveSubcarrierNum) 
{
    const char *ParamName = "FirstActiveSubcarrierNum";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;

    pDsOfdmChannel->FirstActiveSubcarrierNum = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChanIndicator"),
                                               strlen("ChanIndicator"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_LastActiveSubcarrierNum) 
{
    const char *ParamName = "LastActiveSubcarrierNum";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;
    
    pDsOfdmChannel->LastActiveSubcarrierNum = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChanIndicator"),
                                               strlen("ChanIndicator"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_NumActiveSubcarriers) 
{
    const char *ParamName = "NumActiveSubcarriers";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;
    
    pDsOfdmChannel->NumActiveSubcarriers = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChanIndicator"),
                                               strlen("ChanIndicator"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_SubcarrierSpacing) 
{
    const char *ParamName = "SubcarrierSpacing";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;
    
    pDsOfdmChannel->SubcarrierSpacing = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChanIndicator"),
                                               strlen("ChanIndicator"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierSpacing"),
                                               strlen("SubcarrierSpacing"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_CyclicPrefix) 
{
    const char *ParamName = "CyclicPrefix";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;

    pDsOfdmChannel->CyclicPrefix = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChanIndicator"),
                                               strlen("ChanIndicator"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierSpacing"),
                                               strlen("SubcarrierSpacing"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CyclicPrefix"),
                                               strlen("CyclicPrefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_RollOffPeriod) 
{
    const char *ParamName = "RollOffPeriod";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;
    
    pDsOfdmChannel->RollOffPeriod = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChanIndicator"),
                                               strlen("ChanIndicator"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierSpacing"),
                                               strlen("SubcarrierSpacing"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CyclicPrefix"),
                                               strlen("CyclicPrefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RollOffPeriod"),
                                               strlen("RollOffPeriod"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_PlcFreq) 
{
    const char *ParamName = "PlcFreq";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;

    pDsOfdmChannel->PlcFreq = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChanIndicator"),
                                               strlen("ChanIndicator"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierSpacing"),
                                               strlen("SubcarrierSpacing"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CyclicPrefix"),
                                               strlen("CyclicPrefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RollOffPeriod"),
                                               strlen("RollOffPeriod"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PlcFreq"),
                                               strlen("PlcFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_NumPilots) 
{
    const char *ParamName = "NumPilots";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;
    
    pDsOfdmChannel->NumPilots = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChanIndicator"),
                                               strlen("ChanIndicator"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierSpacing"),
                                               strlen("SubcarrierSpacing"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CyclicPrefix"),
                                               strlen("CyclicPrefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RollOffPeriod"),
                                               strlen("RollOffPeriod"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PlcFreq"),
                                               strlen("PlcFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumPilots"),
                                               strlen("NumPilots"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_TimeInterleaverDepth) 
{
    const char *ParamName = "TimeInterleaverDepth";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;

    pDsOfdmChannel->TimeInterleaverDepth = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChanIndicator"),
                                               strlen("ChanIndicator"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierSpacing"),
                                               strlen("SubcarrierSpacing"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CyclicPrefix"),
                                               strlen("CyclicPrefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RollOffPeriod"),
                                               strlen("RollOffPeriod"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PlcFreq"),
                                               strlen("PlcFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumPilots"),
                                               strlen("NumPilots"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeInterleaverDepth"),
                                               strlen("TimeInterleaverDepth"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_PlcTotalCodewords) 
{
    const char *ParamName = "PlcTotalCodewords";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;

    pDsOfdmChannel->PlcTotalCodewords = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChanIndicator"),
                                               strlen("ChanIndicator"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierSpacing"),
                                               strlen("SubcarrierSpacing"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CyclicPrefix"),
                                               strlen("CyclicPrefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RollOffPeriod"),
                                               strlen("RollOffPeriod"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PlcFreq"),
                                               strlen("PlcFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumPilots"),
                                               strlen("NumPilots"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeInterleaverDepth"),
                                               strlen("TimeInterleaverDepth"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PlcTotalCodewords"),
                                               strlen("PlcTotalCodewords"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_PlcUnreliableCodewords) 
{
    const char *ParamName = "PlcUnreliableCodewords";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;

    pDsOfdmChannel->PlcUnreliableCodewords = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChanIndicator"),
                                               strlen("ChanIndicator"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierSpacing"),
                                               strlen("SubcarrierSpacing"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CyclicPrefix"),
                                               strlen("CyclicPrefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RollOffPeriod"),
                                               strlen("RollOffPeriod"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PlcFreq"),
                                               strlen("PlcFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumPilots"),
                                               strlen("NumPilots"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeInterleaverDepth"),
                                               strlen("TimeInterleaverDepth"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PlcTotalCodewords"),
                                               strlen("PlcTotalCodewords"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PlcUnreliableCodewords"),
                                               strlen("PlcUnreliableCodewords"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_NcpTotalFields) 
{
    const char *ParamName = "NcpTotalFields";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;
    
    pDsOfdmChannel->NcpTotalFields = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChanIndicator"),
                                               strlen("ChanIndicator"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierSpacing"),
                                               strlen("SubcarrierSpacing"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CyclicPrefix"),
                                               strlen("CyclicPrefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RollOffPeriod"),
                                               strlen("RollOffPeriod"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PlcFreq"),
                                               strlen("PlcFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumPilots"),
                                               strlen("NumPilots"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeInterleaverDepth"),
                                               strlen("TimeInterleaverDepth"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PlcTotalCodewords"),
                                               strlen("PlcTotalCodewords"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PlcUnreliableCodewords"),
                                               strlen("PlcUnreliableCodewords"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NcpTotalFields"),
                                               strlen("NcpTotalFields"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)    
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue_NcpFieldCrcFailures) 
{
    const char *ParamName = "NcpFieldCrcFailures";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;
    
    pDsOfdmChannel->NcpFieldCrcFailures = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelID"),
                                               strlen("ChannelID"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChanIndicator"),
                                               strlen("ChanIndicator"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierSpacing"),
                                               strlen("SubcarrierSpacing"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CyclicPrefix"),
                                               strlen("CyclicPrefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RollOffPeriod"),
                                               strlen("RollOffPeriod"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PlcFreq"),
                                               strlen("PlcFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumPilots"),
                                               strlen("NumPilots"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TimeInterleaverDepth"),
                                               strlen("TimeInterleaverDepth"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PlcTotalCodewords"),
                                               strlen("PlcTotalCodewords"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PlcUnreliableCodewords"),
                                               strlen("PlcUnreliableCodewords"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NcpTotalFields"),
                                               strlen("NcpTotalFields"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NcpFieldCrcFailures"),
                                               strlen("NcpFieldCrcFailures"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)   
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamStringValue_PowerLevel) 
{
    const char *ParamName = "PowerLevel";
    char pValue[256] = "10";
    ULONG pUlSize = 256;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;

    strncpy(pDsOfdmChannel->PowerLevel, pValue, sizeof(pDsOfdmChannel->PowerLevel) - 1);
    pDsOfdmChannel->PowerLevel[sizeof(pDsOfdmChannel->PowerLevel) - 1] = '\0';

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamStringValue(hInsContext, (char *)ParamName, pValue, &pUlSize), 0);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamStringValue_SNRLevel) 
{
    const char *ParamName = "SNRLevel";
    char pValue[256] = "10";
    ULONG pUlSize = 256;

    PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN pDsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_DS_OFDM_CHAN));
    ASSERT_NE(pDsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pDsOfdmChannel;

    strncpy(pDsOfdmChannel->averageSNR, pValue, sizeof(pDsOfdmChannel->averageSNR) - 1);
    pDsOfdmChannel->averageSNR[sizeof(pDsOfdmChannel->averageSNR) - 1] = '\0';

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_DsOfdmChan_GetParamStringValue(hInsContext, (char *)ParamName, pValue, &pUlSize), 0);

    free(pDsOfdmChannel);
    pDsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_IsUpdated_TimeZero)
{
    ANSC_HANDLE hInsContext = NULL;
    ULONG uValue = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;

    pMyObject->UsOfdmChannelUpdateTime = uValue;

    EXPECT_CALL(*g_usertimeMock, UserGetTickInSeconds2())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_IsUpdated(hInsContext), TRUE);

    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_IsUpdated_TimeGreaterThenZero)
{
    ANSC_HANDLE hInsContext = NULL;
    ULONG uValue = 700;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;

    pMyObject->UsOfdmChannelUpdateTime = uValue;

    EXPECT_CALL(*g_usertimeMock, UserGetTickInSeconds2())
        .Times(3)
        .WillRepeatedly(Return(1000));
        
    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_IsUpdated(hInsContext), TRUE);

    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_Synchronize)
{
    ANSC_HANDLE hInsContext = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;
    pMyObject->pUsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN));
    ASSERT_NE(pMyObject->pUsOfdmChannel, nullptr);
 
    pMyObject->UsOfdmChannelTotalNumbers = 10;
    
    EXPECT_CALL(*g_anscMemoryMock, AnscFreeMemoryOrig(_))
        .Times(1);

    EXPECT_EQ(CosaDmlRDKCentralCmGetUpstreamChannel(NULL, &pMyObject->UsOfdmChannelTotalNumbers, &pMyObject->pUsOfdmChannel), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_Synchronize(hInsContext), 0);

    free(pMyObject->pUsOfdmChannel);
    pMyObject->pUsOfdmChannel = NULL;
    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetEntryCount)
{
    ANSC_HANDLE hInsContext = NULL;
    ULONG uValue = 10;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;
    pMyObject->UsOfdmChannelTotalNumbers = uValue;

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetEntryCount(hInsContext), uValue);

    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetEntry)
{
    ANSC_HANDLE hInsContext = NULL;
    ULONG nIndex = 0;
    ULONG pInsNumber = 0;
    ULONG uValue = 10;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;
    pMyObject->UsOfdmChannelTotalNumbers = uValue;
    pMyObject->pUsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN));
    ASSERT_NE(pMyObject->pUsOfdmChannel, nullptr);

    EXPECT_CALL(*g_anscMemoryMock, AnscFreeMemoryOrig(_))
        .Times(1);

    EXPECT_EQ(CosaDmlRDKCentralCmGetUpstreamChannel(NULL, &pMyObject->UsOfdmChannelTotalNumbers, &pMyObject->pUsOfdmChannel), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetEntry(hInsContext, nIndex, &pInsNumber), &pMyObject->pUsOfdmChannel[nIndex]);

    free(pMyObject->pUsOfdmChannel);
    pMyObject->pUsOfdmChannel = NULL;
    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamBoolValue_PreEqEnabled) 
{
    const char *ParamName = "PreEqEnabled";
    BOOL pBool = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN pUsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN));
    ASSERT_NE(pUsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pUsOfdmChannel;

    pUsOfdmChannel->PreEqEnabled = 1;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("PreEqEnabled"),
                                               strlen("PreEqEnabled"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamBoolValue(hInsContext, (char *)ParamName, &pBool), 1);

    free(pUsOfdmChannel);
    pUsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue_ChannelId) 
{
    const char *ParamName = "ChannelId";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN pUsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN));
    ASSERT_NE(pUsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pUsOfdmChannel;

    pUsOfdmChannel->ChannelId = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pUsOfdmChannel);
    pUsOfdmChannel = NULL;
}


TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue_ConfigChangeCt) 
{
    const char *ParamName = "ConfigChangeCt";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN pUsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN));
    ASSERT_NE(pUsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pUsOfdmChannel;

    pUsOfdmChannel->ConfigChangeCt = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigChangeCt"),
                                               strlen("ConfigChangeCt"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pUsOfdmChannel);
    pUsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue_SubcarrierZeroFreq) 
{
    const char *ParamName = "SubcarrierZeroFreq";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN pUsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN));
    ASSERT_NE(pUsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pUsOfdmChannel;

    pUsOfdmChannel->SubcarrierZeroFreq = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigChangeCt"),
                                               strlen("ConfigChangeCt"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pUsOfdmChannel);
    pUsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue_FirstActiveSubcarrierNum) 
{
    const char *ParamName = "FirstActiveSubcarrierNum";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN pUsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN));
    ASSERT_NE(pUsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pUsOfdmChannel;

    pUsOfdmChannel->FirstActiveSubcarrierNum = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigChangeCt"),
                                               strlen("ConfigChangeCt"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pUsOfdmChannel);
    pUsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue_LastActiveSubcarrierNum) 
{
    const char *ParamName = "LastActiveSubcarrierNum";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN pUsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN));
    ASSERT_NE(pUsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pUsOfdmChannel;

    pUsOfdmChannel->LastActiveSubcarrierNum = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigChangeCt"),
                                               strlen("ConfigChangeCt"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pUsOfdmChannel);
    pUsOfdmChannel = NULL;
}


TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue_NumActiveSubcarriers) 
{
    const char *ParamName = "NumActiveSubcarriers";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN pUsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN));
    ASSERT_NE(pUsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pUsOfdmChannel;

    pUsOfdmChannel->NumActiveSubcarriers = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigChangeCt"),
                                               strlen("ConfigChangeCt"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)    
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pUsOfdmChannel);
    pUsOfdmChannel = NULL;
}


TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue_SubcarrierSpacing) 
{
    const char *ParamName = "SubcarrierSpacing";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN pUsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN));
    ASSERT_NE(pUsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pUsOfdmChannel;

    pUsOfdmChannel->SubcarrierSpacing = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigChangeCt"),
                                               strlen("ConfigChangeCt"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierSpacing"),
                                               strlen("SubcarrierSpacing"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pUsOfdmChannel);
    pUsOfdmChannel = NULL;
}


TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue_CyclicPrefix) 
{
    const char *ParamName = "CyclicPrefix";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN pUsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN));
    ASSERT_NE(pUsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pUsOfdmChannel;

    pUsOfdmChannel->CyclicPrefix = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigChangeCt"),
                                               strlen("ConfigChangeCt"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierSpacing"),
                                               strlen("SubcarrierSpacing"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CyclicPrefix"),
                                               strlen("CyclicPrefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pUsOfdmChannel);
    pUsOfdmChannel = NULL;
}


TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue_RollOffPeriod) 
{
    const char *ParamName = "RollOffPeriod";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN pUsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN));
    ASSERT_NE(pUsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pUsOfdmChannel;

    pUsOfdmChannel->RollOffPeriod = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigChangeCt"),
                                               strlen("ConfigChangeCt"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierSpacing"),
                                               strlen("SubcarrierSpacing"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CyclicPrefix"),
                                               strlen("CyclicPrefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RollOffPeriod"),
                                               strlen("RollOffPeriod"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pUsOfdmChannel);
    pUsOfdmChannel = NULL;
}


TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue_NumSymbolsPerFrame) 
{
    const char *ParamName = "NumSymbolsPerFrame";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN pUsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN));
    ASSERT_NE(pUsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pUsOfdmChannel;

    pUsOfdmChannel->NumSymbolsPerFrame = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigChangeCt"),
                                               strlen("ConfigChangeCt"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierSpacing"),
                                               strlen("SubcarrierSpacing"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CyclicPrefix"),
                                               strlen("CyclicPrefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RollOffPeriod"),
                                               strlen("RollOffPeriod"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumSymbolsPerFrame"),
                                               strlen("NumSymbolsPerFrame"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pUsOfdmChannel);
    pUsOfdmChannel = NULL;
}


TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue_TxPower) 
{
    const char *ParamName = "TxPower";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN pUsOfdmChannel = (PCOSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CM_US_OFDMA_CHAN));
    ASSERT_NE(pUsOfdmChannel, nullptr);

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pUsOfdmChannel;

    pUsOfdmChannel->TxPower = 10;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ConfigChangeCt"),
                                               strlen("ConfigChangeCt"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierZeroFreq"),
                                               strlen("SubcarrierZeroFreq"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("FirstActiveSubcarrierNum"),
                                               strlen("FirstActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LastActiveSubcarrierNum"),
                                               strlen("LastActiveSubcarrierNum"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumActiveSubcarriers"),
                                               strlen("NumActiveSubcarriers"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("SubcarrierSpacing"),
                                               strlen("SubcarrierSpacing"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("CyclicPrefix"),
                                               strlen("CyclicPrefix"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RollOffPeriod"),
                                               strlen("RollOffPeriod"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("NumSymbolsPerFrame"),
                                               strlen("NumSymbolsPerFrame"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("TxPower"),
                                               strlen("TxPower"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_UsOfdmaChan_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pUsOfdmChannel);
    pUsOfdmChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_StatusOfdma_IsUpdated_TimeZero)
{
    ANSC_HANDLE hInsContext = NULL;
    ULONG uValue = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;

    pMyObject->CMStatusofUsChannelUpdateTime = uValue;

    EXPECT_CALL(*g_usertimeMock, UserGetTickInSeconds2())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_StatusOfdma_IsUpdated(hInsContext), TRUE);

    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_StatusOfdma_IsUpdated_TimeGreaterThenZero)
{
    ANSC_HANDLE hInsContext = NULL;
    ULONG uValue = 700;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;

    pMyObject->CMStatusofUsChannelUpdateTime = uValue;

    EXPECT_CALL(*g_usertimeMock, UserGetTickInSeconds2())
        .Times(3)
        .WillRepeatedly(Return(1000));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_StatusOfdma_IsUpdated(hInsContext), TRUE);

    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_StatusOfdma_Synchronize)
{
    ANSC_HANDLE hInsContext = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;
    pMyObject->pCMStatusofUsChannel = (PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US));
    ASSERT_NE(pMyObject->pCMStatusofUsChannel, nullptr);

    pMyObject->CMStatusofUsChannelTotalNumbers = 0;

    EXPECT_CALL(*g_anscMemoryMock, AnscFreeMemoryOrig(_))
        .Times(1);

    EXPECT_EQ(CosaDmlRDKCentralCmGetCMStatusofUpstreamChannel(NULL, &pMyObject->CMStatusofUsChannelTotalNumbers, &pMyObject->pCMStatusofUsChannel), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_StatusOfdma_Synchronize(hInsContext), 0);

    free(pMyObject->pCMStatusofUsChannel);
    pMyObject->pCMStatusofUsChannel = NULL;
    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetEntryCount)
{
    ANSC_HANDLE hInsContext = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;
    pMyObject->CMStatusofUsChannelTotalNumbers = 10;

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetEntryCount(hInsContext), 10);

    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetEntry)
{
    ANSC_HANDLE hInsContext = NULL;
    ULONG nIndex = 0;
    ULONG pInsNumber = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;
    pMyObject->pCMStatusofUsChannel = (PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US));
    ASSERT_NE(pMyObject->pCMStatusofUsChannel, nullptr);

    pMyObject->CMStatusofUsChannelTotalNumbers = 10;

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetEntry(hInsContext, nIndex, &pInsNumber), &pMyObject->pCMStatusofUsChannel[nIndex]);

    free(pMyObject->pCMStatusofUsChannel);
    pMyObject->pCMStatusofUsChannel = NULL;
    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetParamBoolValue_IsMuted) 
{
    const char *ParamName = "IsMuted";
    BOOL pBool = FALSE;

    PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US pCMStatusofUsChannel = (PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US));
    ASSERT_NE(pCMStatusofUsChannel, nullptr);

    pCMStatusofUsChannel->IsMuted = TRUE;

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pCMStatusofUsChannel;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("IsMuted"),
                                               strlen("IsMuted"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetParamBoolValue(hInsContext, (char *)ParamName, &pBool), 1);

    free(pCMStatusofUsChannel);
    pCMStatusofUsChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetParamUlongValue_ChannelId) 
{
    const char *ParamName = "ChannelId";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US pCMStatusofUsChannel = (PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US));
    ASSERT_NE(pCMStatusofUsChannel, nullptr);

    pCMStatusofUsChannel->ChannelId = 10;

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pCMStatusofUsChannel;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pCMStatusofUsChannel);
    pCMStatusofUsChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetParamUlongValue_T3Timeouts) 
{
    const char *ParamName = "T3Timeouts";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US pCMStatusofUsChannel = (PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US));
    ASSERT_NE(pCMStatusofUsChannel, nullptr);

    pCMStatusofUsChannel->T3Timeouts = 10;

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pCMStatusofUsChannel;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("T3Timeouts"),
                                               strlen("T3Timeouts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pCMStatusofUsChannel);
    pCMStatusofUsChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetParamUlongValue_T4Timeouts) 
{
    const char *ParamName = "T4Timeouts";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US pCMStatusofUsChannel = (PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US));
    ASSERT_NE(pCMStatusofUsChannel, nullptr);

    pCMStatusofUsChannel->T4Timeouts = 10;

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pCMStatusofUsChannel;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("T3Timeouts"),
                                               strlen("T3Timeouts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("T4Timeouts"),
                                               strlen("T4Timeouts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pCMStatusofUsChannel);
    pCMStatusofUsChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetParamUlongValue_RangingAborteds) 
{
    const char *ParamName = "RangingAborteds";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US pCMStatusofUsChannel = (PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US));
    ASSERT_NE(pCMStatusofUsChannel, nullptr);

    pCMStatusofUsChannel->RangingAborteds = 10;

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pCMStatusofUsChannel;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("T3Timeouts"),
                                               strlen("T3Timeouts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("T4Timeouts"),
                                               strlen("T4Timeouts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RangingAborteds"),
                                               strlen("RangingAborteds"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pCMStatusofUsChannel);
    pCMStatusofUsChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetParamUlongValue_T3Exceededs) 
{
    const char *ParamName = "T3Exceededs";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US pCMStatusofUsChannel = (PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US));
    ASSERT_NE(pCMStatusofUsChannel, nullptr);

    pCMStatusofUsChannel->T3Exceededs = 10;

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pCMStatusofUsChannel;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("T3Timeouts"),
                                               strlen("T3Timeouts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("T4Timeouts"),
                                               strlen("T4Timeouts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RangingAborteds"),
                                               strlen("RangingAborteds"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("T3Exceededs"),
                                               strlen("T3Exceededs"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pCMStatusofUsChannel);
    pCMStatusofUsChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetParamUlongValue_RangingStatus) 
{
    const char *ParamName = "RangingStatus";
    ULONG puLong = 0;

    PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US pCMStatusofUsChannel = (PCOSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US)malloc(sizeof(COSA_X_RDKCENTRAL_COM_CMSTATUSOFDMA_US));
    ASSERT_NE(pCMStatusofUsChannel, nullptr);

    pCMStatusofUsChannel->RangingStatus = 10;

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pCMStatusofUsChannel;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("ChannelId"),
                                               strlen("ChannelId"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("T3Timeouts"),
                                               strlen("T3Timeouts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("T4Timeouts"),
                                               strlen("T4Timeouts"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RangingAborteds"),
                                               strlen("RangingAborteds"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("T3Exceededs"),
                                               strlen("T3Exceededs"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("RangingStatus"),
                                               strlen("RangingStatus"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_StatusOfdma_GetParamUlongValue(hInsContext, (char *)ParamName, &puLong), 1);

    free(pCMStatusofUsChannel);
    pCMStatusofUsChannel = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDK_CableModem_GetParamUlongValue_DownstreamDiplexerSetting) 
{
    const char *ParamName = "DownstreamDiplexerSetting";
    ULONG puLong = 0;
    unsigned int uiUSValue = 10, uiDSValue = 20;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamDiplexerSetting"),
                                               strlen("DownstreamDiplexerSetting"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_get_DiplexerSettings(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlRDKCmGetDiplexerSettings(&uiUSValue, &uiDSValue), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_RDK_CableModem_GetParamUlongValue(NULL, (char *)ParamName, &puLong), 1);
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDK_CableModem_GetParamUlongValue_UpstreamDiplexerSetting) 
{
    const char *ParamName = "UpstreamDiplexerSetting";
    ULONG puLong = 0;
    unsigned int uiUSValue = 10, uiDSValue = 20;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DownstreamDiplexerSetting"),
                                               strlen("DownstreamDiplexerSetting"),
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("UpstreamDiplexerSetting"),
                                               strlen("UpstreamDiplexerSetting"),
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(0), Return(EOK)));

    EXPECT_CALL(*g_cmHALMock, cm_hal_get_DiplexerSettings(_))
        .Times(2)
        .WillRepeatedly(Return(0));
    
    EXPECT_EQ(CosaDmlRDKCmGetDiplexerSettings(&uiUSValue, &uiDSValue), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(X_RDK_CableModem_GetParamUlongValue(NULL, (char *)ParamName, &puLong), 1);
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_GetParamBoolValue_LLD_Active_pBoolTrue) 
{
    const char *ParamName = "LLD_Active";
    BOOL pBool = TRUE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;

    char result_buf[32] = "true";

    pMyObject->LLDActiveStatus = pBool;

    EXPECT_CALL(*g_syseventMock, sysevent_get(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_GetParamBoolValue(NULL, (char *)ParamName, &pBool), 1);

    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, X_RDKCENTRAL_COM_CableModem_GetParamBoolValue_LLD_Active_pBoolFalse) 
{
    const char *ParamName = "LLD_Active";
    BOOL pBool = FALSE;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hRDKCM = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)malloc(sizeof(COSA_DATAMODEL_RDKCENTRAL_CABLEMODEM));
    ASSERT_NE(g_pCosaBEManager->hRDKCM, nullptr);

    PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM pMyObject = (PCOSA_DATAMODEL_RDKCENTRAL_CABLEMODEM)g_pCosaBEManager->hRDKCM;

    char result_buf[32] = "false";

    pMyObject->LLDActiveStatus = pBool;

    EXPECT_CALL(*g_syseventMock, sysevent_get(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(X_RDKCENTRAL_COM_CableModem_GetParamBoolValue(NULL, (char *)ParamName, &pBool), 1);

    free(g_pCosaBEManager->hRDKCM);
    g_pCosaBEManager->hRDKCM = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, LldMarkingRules_SetParamStringValue_Data) 
{
    const char *ParamName = "Data";
    const char *pValue = "test";

    EXPECT_CALL(*g_base64Mock, b64_get_decoded_buffer_size(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_base64Mock, b64_decode(_, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(WebConfig_blob_handler((char *)pValue), FALSE);

    EXPECT_EQ(LldMarkingRules_SetParamStringValue(NULL, (char *)ParamName, (char *)pValue), TRUE);
}

TEST_F(CcspCMAgentRdkCentralCableModemDmlTestFixture, LldMarkingRules_GetParamStringValue_Data) 
{
    const char *ParamName = "Data";
    const char *pValue = "test";

    EXPECT_EQ(LldMarkingRules_GetParamStringValue(NULL, (char *)ParamName, (char *)pValue), TRUE);
}