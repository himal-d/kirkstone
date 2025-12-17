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

#include "CcspAdvSecurityMock.h"

typedef void* ANSC_HANDLE;
ANSC_HANDLE bus_handle = NULL;


class CcspAdvSecurityDmlTestFixture : public ::testing::Test {
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
    }
};

TEST_F(CcspAdvSecurityDmlTestFixture, CheckDeviceFingerPrint_GetParamBoolValue_Enable) {
    BOOL resultBool;
    PCOSA_DATAMODEL_AGENT pMyObject = new COSA_DATAMODEL_AGENT;
    pMyObject->bEnable = TRUE;
    g_pAdvSecAgent = pMyObject;

    const char* ParamName = "Enable";
    int comparisonResult = 0;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    BOOL result = DeviceFingerPrint_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    delete pMyObject;
}

TEST_F(CcspAdvSecurityDmlTestFixture, CheckDeviceFingerPrint_GetParamBoolValue_Disable) {
    BOOL resultBool;
    PCOSA_DATAMODEL_AGENT pMyObject = new COSA_DATAMODEL_AGENT;
    pMyObject->bEnable = FALSE;
    g_pAdvSecAgent = pMyObject;

    const char* ParamName = "Enable";
    int comparisonResult = 0;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    BOOL result = DeviceFingerPrint_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    delete pMyObject;
}

TEST_F(CcspAdvSecurityDmlTestFixture, CheckDeviceFingerPrint_GetParamBoolValue_UnsupportedParam) {
    BOOL resultBool;
    PCOSA_DATAMODEL_AGENT pMyObject = new COSA_DATAMODEL_AGENT;
    g_pAdvSecAgent = pMyObject;

    const char* ParamName = "UnsupportedParam";
    int comparisonResult = 1;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    BOOL result = DeviceFingerPrint_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_FALSE(result);

    delete pMyObject;
}

TEST_F(CcspAdvSecurityDmlTestFixture, CheckDeviceFingerPrint_SetParamBoolValue_Enable) {

    const char *DeviceFingerPrintEnabled = "Advsecurity_DeviceFingerPrint";
    PCOSA_DATAMODEL_AGENT pMyObject = new COSA_DATAMODEL_AGENT;
    pMyObject->bEnable = FALSE;
    g_pAdvSecAgent = pMyObject;

    const char* ParamName = "Enable";
    BOOL bValue = TRUE;
    int comparisonResult = 0;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(DeviceFingerPrintEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enable &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecInit());

    BOOL result = DeviceFingerPrint_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_TRUE(pMyObject->bEnable);

    delete pMyObject;
}

TEST_F(CcspAdvSecurityDmlTestFixture, CheckDeviceFingerPrint_SetParamBoolValue_Disable) {
    const char *DeviceFingerPrintEnabled = "Advsecurity_DeviceFingerPrint";
    PCOSA_DATAMODEL_AGENT pMyObject = new COSA_DATAMODEL_AGENT;
    pMyObject->bEnable = TRUE;
    g_pAdvSecAgent = pMyObject;

    const char* ParamName = "Enable";
    BOOL bValue = FALSE;
    int comparisonResult = 0;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(DeviceFingerPrintEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disable &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecDeInit());

    BOOL result = DeviceFingerPrint_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_FALSE(pMyObject->bEnable);

    delete pMyObject;
}

TEST_F(CcspAdvSecurityDmlTestFixture, CheckDeviceFingerPrint_GetParamUlongValue_LoggingPeriod) {
    ULONG resultUlong;
    PCOSA_DATAMODEL_AGENT pMyObject = new COSA_DATAMODEL_AGENT;
    pMyObject->ulLoggingPeriod = 100;
    g_pAdvSecAgent = pMyObject;

    const char* ParamName = "LoggingPeriod";
    int comparisonResult = 0;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoggingPeriod"), strlen("LoggingPeriod"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    BOOL result = DeviceFingerPrint_GetParamUlongValue(NULL, (char*)ParamName, &resultUlong);

    EXPECT_TRUE(result);
    EXPECT_EQ(100, resultUlong);

    delete pMyObject;
}

TEST_F(CcspAdvSecurityDmlTestFixture, CheckDeviceFingerPrint_SetParamUlongValue_LoggingPeriod) {
    PCOSA_DATAMODEL_AGENT pMyObject = new COSA_DATAMODEL_AGENT;
    pMyObject->ulLoggingPeriod = 100;
    g_pAdvSecAgent = pMyObject;
    const char *DeviceFingerPrintLogginPeriod = "Advsecurity_LoggingPeriod";

    const char* ParamName = "LoggingPeriod";
    ULONG bValue = 200;
    int comparisonResult = 0;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LoggingPeriod"), strlen("LoggingPeriod"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(DeviceFingerPrintLogginPeriod), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecSetLoggingPeriod(bValue));

    BOOL result = DeviceFingerPrint_SetParamUlongValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_EQ(200, pMyObject->ulLoggingPeriod);

    delete pMyObject;
}

TEST_F(CcspAdvSecurityDmlTestFixture, CheckDeviceFingerPrint_GetParamStringValue_EndpointURL) {
    char pValue[256] = {0};
    ULONG pUlSize = 256;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "EndpointURL";
    int comparisonResult = 0;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EndpointURL"), strlen("EndpointURL"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecGetCustomURL(pValue, &pUlSize));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    returnStatus = DeviceFingerPrint_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize);

    EXPECT_EQ(ANSC_STATUS_SUCCESS, returnStatus);
}

TEST_F(CcspAdvSecurityDmlTestFixture, CheckDeviceFingerPrint_SetParamStringValue_EndpointURL) {
    char pString[256] = "\0";
    const char *AdvSecCustomEndpointURL = "Advsecurity_CustomEndpointURL";
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "EndpointURL";
    int comparisonResult = 0;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("EndpointURL"), strlen("EndpointURL"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecCustomEndpointURL), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecSetCustomURL(pString));

    returnStatus = DeviceFingerPrint_SetParamStringValue(NULL, (char*)ParamName, pString);

    EXPECT_EQ(ANSC_STATUS_SUCCESS, returnStatus);
}

TEST_F(CcspAdvSecurityDmlTestFixture, SetParamStringValue_Success) {
    const char* ParamName = "Data";
    const char* pString = "encodedData";
    int comparisonResult = 0;
    char *decodeMsg = NULL;
    int size = 128;


    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Data"), strlen("Data"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_base64Mock, b64_get_decoded_buffer_size(strlen(pString)))
        .Times(1)
        .WillOnce(Return(128));

    EXPECT_CALL(*g_base64Mock, b64_decode(reinterpret_cast<const uint8_t*>(pString), strlen(pString), testing::_))
        .Times(1)
        .WillOnce(Return(64));

    msgpack_unpack_return unpack_ret = MSGPACK_UNPACK_SUCCESS;
    EXPECT_CALL(*g_msgpackMock, msgpack_zone_init(testing::_, 2048))
        .Times(1);
    EXPECT_CALL(*g_msgpackMock, msgpack_unpack(testing::_, 64, testing::_, testing::_, testing::_))
        .Times(1)
        .WillOnce(Return(unpack_ret));
    EXPECT_CALL(*g_msgpackMock, msgpack_unpack_next(testing::_, testing::_, testing::_, testing::_))
        .Times(1)
        .WillOnce(Return(unpack_ret));
    EXPECT_CALL(*g_msgpackMock, msgpack_object_print(testing::_, testing::_))
        .Times(1);
    EXPECT_CALL(*g_msgpackMock, msgpack_zone_destroy(testing::_))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _memset_s_chk(_, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_TRUE(advsecuritydoc_convert(decodeMsg, size));

    EXPECT_CALL(*g_anscMemoryMock, AnscFreeMemoryOrig(testing::_))
        .Times(3);

    BOOL result = AdvancedSecurity_SetParamStringValue(NULL, (char*)ParamName, (char*)pString);

    EXPECT_TRUE(result);
}

TEST_F(CcspAdvSecurityDmlTestFixture, SafeBrowsing_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Enable";
    int comparisonResult = 0;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSafeBrows = (COSA_DATAMODEL_SB *)malloc(sizeof(COSA_DATAMODEL_SB));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSafeBrows, nullptr);

    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvSec->pSafeBrows->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    BOOL result = SafeBrowsing_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, SafeBrowsing_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Enable";
    int comparisonResult = 0;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSafeBrows = (COSA_DATAMODEL_SB *)malloc(sizeof(COSA_DATAMODEL_SB));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSafeBrows, nullptr);

    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvSec->pSafeBrows->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    BOOL result = SafeBrowsing_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, SafeBrowsing_SetParamBoolValue_Enable) {
    const char *ParamName = "Enable";
    const char *AdvSecuritySBEnabled = "Advsecurity_SafeBrowsing";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;
    BOOL bValue = TRUE;
    int comparisonResult = 0;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSafeBrows = (COSA_DATAMODEL_SB *)malloc(sizeof(COSA_DATAMODEL_SB));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSafeBrows, nullptr);
    g_pAdvSecAgent->pAdvSec->pSafeBrows->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecuritySBEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -start sb null &"), _))
        .Times(1)
        .WillOnce(Return(0));

    if ((file = fopen(fname, "r")))
    {
        fclose(file);
    }
    else
    {
        file = fopen(fname, "w");
        fclose(file);
        val = 1;
    }

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecStartFeatures(ADVSEC_SAFEBROWSING));

    BOOL result = SafeBrowsing_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_TRUE(g_pAdvSecAgent->pAdvSec->pSafeBrows->bEnable);

    if (val == 1)
    {
        int ret = remove(fname);
        if(ret != 0)
        {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, SafeBrowsing_SetParamBoolValue_Disable) {
    const char *ParamName = "Enable";
    const char *AdvSecuritySBEnabled = "Advsecurity_SafeBrowsing";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;
    BOOL bValue = FALSE;
    int comparisonResult = 0;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSafeBrows = (COSA_DATAMODEL_SB *)malloc(sizeof(COSA_DATAMODEL_SB));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSafeBrows, nullptr);

    g_pAdvSecAgent->pAdvSec->pSafeBrows->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecuritySBEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -stop sb null &"), _))
        .Times(1)
        .WillOnce(Return(0));

    if ((file = fopen(fname, "r")))
    {
        fclose(file);
    }
    else
    {
        file = fopen(fname, "w");
        fclose(file);
        val = 1;
    }

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecStopFeatures(ADVSEC_SAFEBROWSING));

    BOOL result = SafeBrowsing_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_FALSE(g_pAdvSecAgent->pAdvSec->pSafeBrows->bEnable);

    if (val == 1) {
        int ret = remove(fname);
        if(ret != 0) {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, SafeBrowsing_GetParamUlongValue_LookupTimeout) {
    ULONG resultUlong;
    const char* ParamName = "LookupTimeout";
    int comparisonResult = 0;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSafeBrows = (COSA_DATAMODEL_SB *)malloc(sizeof(COSA_DATAMODEL_SB));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSafeBrows, nullptr);

    g_pAdvSecAgent->pAdvSec->pSafeBrows->ulLookupTimeout = 100;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LookupTimeout"), strlen("LookupTimeout"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    BOOL result = SafeBrowsing_GetParamUlongValue(NULL, (char*)ParamName, &resultUlong);

    EXPECT_TRUE(result);
    EXPECT_EQ(100, resultUlong);

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, SafeBrowsing_SetParamUlongValue_LookupTimeout) {
    const char *ParamName = "LookupTimeout";
    ULONG bValue = 100;
    int comparisonResult = 0;
    const char *AdvSecuritySBLookupTimeout = "Advsecurity_LookupTimeout";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSafeBrows = (COSA_DATAMODEL_SB *)malloc(sizeof(COSA_DATAMODEL_SB));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSafeBrows, nullptr);

    g_pAdvSecAgent->pAdvSec->pSafeBrows->ulLookupTimeout = 100;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("LookupTimeout"), strlen("LookupTimeout"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecuritySBLookupTimeout), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecSetLookupTimeout(bValue));

    BOOL result = SafeBrowsing_SetParamUlongValue(NULL, (char*)ParamName, bValue);

    EXPECT_FALSE(result);
    EXPECT_EQ(100, bValue);

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, SafeBrowsing_Validate) {
    const char *pReturnParamName = "ReturnParamName";
    ULONG puLength = 100;

    BOOL result = SafeBrowsing_Validate(NULL, (char*)pReturnParamName, &puLength);

    EXPECT_TRUE(result);
}


TEST_F(CcspAdvSecurityDmlTestFixture, SafeBrowsing_Commit) {
    ULONG result = SafeBrowsing_Commit(NULL);

    EXPECT_EQ(0, result);
}

TEST_F(CcspAdvSecurityDmlTestFixture, SafeBrowsing_Rollback) {
    ULONG result = SafeBrowsing_Rollback(NULL);

    EXPECT_EQ(0, result);
}

TEST_F(CcspAdvSecurityDmlTestFixture, Softflowd_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Enable";
    int comparisonResult = 0;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSoftFlowd = (COSA_DATAMODEL_SOFTFLOWD *)malloc(sizeof(COSA_DATAMODEL_SOFTFLOWD));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSoftFlowd, nullptr);

    g_pAdvSecAgent->pAdvSec->pSoftFlowd->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    BOOL result = Softflowd_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pAdvSec->pSoftFlowd);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, Softflowd_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Enable";
    int comparisonResult = 0;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSoftFlowd = (COSA_DATAMODEL_SOFTFLOWD *)malloc(sizeof(COSA_DATAMODEL_SOFTFLOWD));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSoftFlowd, nullptr);

    g_pAdvSecAgent->pAdvSec->pSoftFlowd->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    BOOL result = Softflowd_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pAdvSec->pSoftFlowd);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, Softflowd_SetParamBoolValue_Enable) {
    const char *ParamName = "Enable";
    BOOL bValue = TRUE;
    const char *AdvSecuritySFEnabled = "Advsecurity_Softflowd";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;
    int comparisonResult = 0;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSoftFlowd = (COSA_DATAMODEL_SOFTFLOWD *)malloc(sizeof(COSA_DATAMODEL_SOFTFLOWD));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSoftFlowd, nullptr);

    g_pAdvSecAgent->pAdvSec->pSoftFlowd->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecuritySFEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -start null sf &"), _))
        .Times(1)
        .WillOnce(Return(0));

    if ((file = fopen(fname, "r")))
    {
        fclose(file);
    }
    else
    {
        file = fopen(fname, "w");
        fclose(file);
        val = 1;
    }

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecStartFeatures(ADVSEC_SOFTFLOWD));

    BOOL result = Softflowd_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_TRUE(g_pAdvSecAgent->pAdvSec->pSoftFlowd->bEnable);

    if (val == 1)
    {
        int ret = remove(fname);
        if(ret != 0)
        {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pAdvSec->pSoftFlowd);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, Softflowd_SetParamBoolValue_Disable) {
    const char *ParamName = "Enable";
    BOOL bValue = FALSE;
    const char *AdvSecuritySFEnabled = "Advsecurity_Softflowd";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;
    int comparisonResult = 0;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSoftFlowd = (COSA_DATAMODEL_SOFTFLOWD *)malloc(sizeof(COSA_DATAMODEL_SOFTFLOWD));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSoftFlowd, nullptr);

    g_pAdvSecAgent->pAdvSec->pSoftFlowd->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecuritySFEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -stop null sf &"), _))
        .Times(1)
        .WillOnce(Return(0));

    if ((file = fopen(fname, "r")))
    {
        fclose(file);
    }
    else
    {
        file = fopen(fname, "w");
        fclose(file);
        val = 1;
    }

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecStopFeatures(ADVSEC_SOFTFLOWD));

    BOOL result = Softflowd_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_FALSE(g_pAdvSecAgent->pAdvSec->pSoftFlowd->bEnable);

    if (val == 1)
    {
        int ret = remove(fname);
        if(ret != 0)
        {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pAdvSec->pSoftFlowd);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, Softflowd_Validate) {
    const char *pReturnParamName = "Softflowd";
    ULONG puLength = 10;

    BOOL result = Softflowd_Validate(NULL, (char*)pReturnParamName, &puLength);

    EXPECT_TRUE(result);
}

TEST_F(CcspAdvSecurityDmlTestFixture, Softflowd_Commit) {
    ULONG result = Softflowd_Commit(NULL);

    EXPECT_EQ(0, result);
}

TEST_F(CcspAdvSecurityDmlTestFixture, Softflowd_Rollback) {
    ULONG result = Softflowd_Rollback(NULL);

    EXPECT_EQ(0, result);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvancedParentalControl_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Activate";
    int comparisonResult = 0;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvPC = (COSA_DATAMODEL_ADVPARENTALCONTROL *)malloc(sizeof(COSA_DATAMODEL_ADVPARENTALCONTROL));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC, nullptr);

    g_pAdvSecAgent->pAdvPC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Activate"), strlen("Activate"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    BOOL result = AdvancedParentalControl_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pAdvPC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvancedParentalControl_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Activate";
    int comparisonResult = 0;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvPC = (COSA_DATAMODEL_ADVPARENTALCONTROL *)malloc(sizeof(COSA_DATAMODEL_ADVPARENTALCONTROL));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC, nullptr);

    g_pAdvSecAgent->pAdvPC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Activate"), strlen("Activate"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    BOOL result = AdvancedParentalControl_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pAdvPC);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, AdvancedParentalControl_SetParamBoolValue_Enable) {
    const char *ParamName = "Activate";
    BOOL bValue = TRUE;
    int comparisonResult = 0;
    const char *AdvSecurityAPCEnabled = "Adv_PCActivate";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvPC = (COSA_DATAMODEL_ADVPARENTALCONTROL *)malloc(sizeof(COSA_DATAMODEL_ADVPARENTALCONTROL));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC, nullptr);

    g_pAdvSecAgent->pAdvPC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Activate"), strlen("Activate"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityAPCEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -startAdvPC &"), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    if ((file = fopen(fname, "r")))
    {
        fclose(file);
    }
    else
    {
        file = fopen(fname, "w");
        fclose(file);
        val = 1;
    }

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaStartAdvParentalControl(TRUE));

    BOOL result = AdvancedParentalControl_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);

    if (val == 1)
    {
        int ret = remove(fname);
        if(ret != 0)
        {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pAdvPC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvancedParentalControl_SetParamBoolValue_Disable) {
    const char *ParamName = "Activate";
    BOOL bValue = FALSE;
    int comparisonResult = 0;
    const char *AdvSecurityAPCEnabled = "Adv_PCActivate";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvPC = (COSA_DATAMODEL_ADVPARENTALCONTROL *)malloc(sizeof(COSA_DATAMODEL_ADVPARENTALCONTROL));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC, nullptr);

    g_pAdvSecAgent->pAdvPC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Activate"), strlen("Activate"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityAPCEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -stopAdvPC &"), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    if ((file = fopen(fname, "r")))
    {
        fclose(file);
    }
    else
    {
        file = fopen(fname, "w");
        fclose(file);
        val = 1;
    }

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaStopAdvParentalControl(TRUE));

    BOOL result = AdvancedParentalControl_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);

    if (val == 1)
    {
        int ret = remove(fname);
        if(ret != 0)
        {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pAdvPC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvancedParentalControl_Validate) {
    const char *pReturnParamName = "AdvancedParentalControl";
    ULONG puLength = 10;

    BOOL result = AdvancedParentalControl_Validate(NULL, (char*)pReturnParamName, &puLength);

    EXPECT_TRUE(result);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvancedParentalControl_Commit) {
    ULONG result = AdvancedParentalControl_Commit(NULL);

    EXPECT_EQ(0, result);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvancedParentalControl_Rollback) {
    ULONG result = AdvancedParentalControl_Rollback(NULL);

    EXPECT_EQ(0, result);
}

TEST_F(CcspAdvSecurityDmlTestFixture, PrivacyProtection_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Activate";
    int comparisonResult = 0;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pPrivProt = (COSA_DATAMODEL_PRIVACYPROTECTION *)malloc(sizeof(COSA_DATAMODEL_PRIVACYPROTECTION));
    ASSERT_NE(g_pAdvSecAgent->pPrivProt, nullptr);

    g_pAdvSecAgent->pPrivProt->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Activate"), strlen("Activate"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    BOOL result = PrivacyProtection_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pPrivProt);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, PrivacyProtection_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Activate";
    int comparisonResult = 0;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pPrivProt = (COSA_DATAMODEL_PRIVACYPROTECTION *)malloc(sizeof(COSA_DATAMODEL_PRIVACYPROTECTION));
    ASSERT_NE(g_pAdvSecAgent->pPrivProt, nullptr);

    g_pAdvSecAgent->pPrivProt->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Activate"), strlen("Activate"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    BOOL result = PrivacyProtection_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pPrivProt);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, PrivacyProtection_SetParamBoolValue_Enable) {
    const char *ParamName = "Activate";
    BOOL bValue = TRUE;
    const char *AdvSecurityPPEnabled = "Adv_PPActivate";
    int comparisonResult = 0;
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pPrivProt = (COSA_DATAMODEL_PRIVACYPROTECTION *)malloc(sizeof(COSA_DATAMODEL_PRIVACYPROTECTION));
    ASSERT_NE(g_pAdvSecAgent->pPrivProt, nullptr);
    g_pAdvSecAgent->pPrivProt->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Activate"), strlen("Activate"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityPPEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -startPrivProt &"), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    if ((file = fopen(fname, "r")))
    {
        fclose(file);
    }
    else
    {
        file = fopen(fname, "w");
        fclose(file);
        val = 1;
    }

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaStartPrivacyProtection(TRUE));

    BOOL result = PrivacyProtection_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);

    if (val == 1)
    {
        int ret = remove(fname);
        if(ret != 0)
        {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pPrivProt);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, PrivacyProtection_SetParamBoolValue_Disable) {
    const char *ParamName = "Activate";
    BOOL bValue = FALSE;
    const char *AdvSecurityPPEnabled = "Adv_PPActivate";
    int comparisonResult = 0;
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pPrivProt = (COSA_DATAMODEL_PRIVACYPROTECTION *)malloc(sizeof(COSA_DATAMODEL_PRIVACYPROTECTION));
    ASSERT_NE(g_pAdvSecAgent->pPrivProt, nullptr);
    g_pAdvSecAgent->pPrivProt->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Activate"), strlen("Activate"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityPPEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -stopPrivProt &"), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    if ((file = fopen(fname, "r")))
    {
        fclose(file);
    }
    else
    {
        file = fopen(fname, "w");
        fclose(file);
        val = 1;
    }

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaStopPrivacyProtection(TRUE));

    BOOL result = PrivacyProtection_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);

    if (val == 1)
    {
        int ret = remove(fname);
        if(ret != 0)
        {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pPrivProt);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, PrivacyProtection_Validate) {
    const char *pReturnParamName = "PrivacyProtection";
    ULONG puLength = 10;

    BOOL result = PrivacyProtection_Validate(NULL, (char*)pReturnParamName, &puLength);

    EXPECT_TRUE(result);
}

TEST_F(CcspAdvSecurityDmlTestFixture, PrivacyProtection_Commit) {
    ULONG result = PrivacyProtection_Commit(NULL);

    EXPECT_EQ(0, result);
}

TEST_F(CcspAdvSecurityDmlTestFixture, PrivacyProtection_Rollback) {
    ULONG result = PrivacyProtection_Rollback(NULL);

    EXPECT_EQ(0, result);
}

TEST_F(CcspAdvSecurityDmlTestFixture, RabidFramework_GetParamUlongValue_MemoryLimit) {
    ULONG resultUlong;
    const char* ParamName = "MemoryLimit";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->pRabid = (COSA_DATAMODEL_RABID *)malloc(sizeof(COSA_DATAMODEL_RABID));
    ASSERT_NE(g_pAdvSecAgent->pRabid, nullptr);

    g_pAdvSecAgent->pRabid->uMemoryLimit = 100;

    BOOL result = RabidFramework_GetParamUlongValue(NULL, (char*)ParamName, &resultUlong);

    EXPECT_TRUE(result);
    EXPECT_EQ(100, resultUlong);

    free(g_pAdvSecAgent->pRabid);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, RabidFramework_GetParamUlongValue_MacCacheSize) {
    ULONG resultUlong;
    const char* ParamName = "MacCacheSize";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->pRabid = (COSA_DATAMODEL_RABID *)malloc(sizeof(COSA_DATAMODEL_RABID));
    ASSERT_NE(g_pAdvSecAgent->pRabid, nullptr);

    g_pAdvSecAgent->pRabid->uMacCacheSize = 100;

    BOOL result = RabidFramework_GetParamUlongValue(NULL, (char*)ParamName, &resultUlong);

    EXPECT_TRUE(result);
    EXPECT_EQ(100, resultUlong);

    free(g_pAdvSecAgent->pRabid);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, RabidFramework_GetParamUlongValue_DNSCacheSize) {
    ULONG resultUlong;
    const char* ParamName = "DNSCacheSize";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->pRabid = (COSA_DATAMODEL_RABID *)malloc(sizeof(COSA_DATAMODEL_RABID));
    ASSERT_NE(g_pAdvSecAgent->pRabid, nullptr);

    g_pAdvSecAgent->pRabid->uDNSCacheSize = 100;

    BOOL result = RabidFramework_GetParamUlongValue(NULL, (char*)ParamName, &resultUlong);

    EXPECT_TRUE(result);
    EXPECT_EQ(100, resultUlong);

    free(g_pAdvSecAgent->pRabid);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, RabidFramework_SetParamUlongValue_MemoryLimit) {
    const char *ParamName = "MemoryLimit";
    ULONG bValue = 100;
    int comparisonResult = 0;
    const char *AdvSecurityRabidMemoryLimit = "Advsecurity_RabidMemoryLimit";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->pRabid = (COSA_DATAMODEL_RABID *)malloc(sizeof(COSA_DATAMODEL_RABID));
    ASSERT_NE(g_pAdvSecAgent->pRabid, nullptr);

    g_pAdvSecAgent->pRabid->uMemoryLimit = 100;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityRabidMemoryLimit), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaRabidSetMemoryLimit(NULL, bValue));

    BOOL result = RabidFramework_SetParamUlongValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_EQ(100, bValue);

    free(g_pAdvSecAgent->pRabid);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, RabidFramework_SetParamUlongValue_MacCacheSize) {
    const char *ParamName = "MacCacheSize";
    ULONG bValue = 100;
    int comparisonResult = 0;
    const char *AdvSecurityRabidMacCacheSize = "Advsecurity_RabidMacCacheSize";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->pRabid = (COSA_DATAMODEL_RABID *)malloc(sizeof(COSA_DATAMODEL_RABID));
    ASSERT_NE(g_pAdvSecAgent->pRabid, nullptr);

    g_pAdvSecAgent->pRabid->uMacCacheSize = 100;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityRabidMacCacheSize), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaRabidSetMacCacheSize(NULL, bValue));

    BOOL result = RabidFramework_SetParamUlongValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_EQ(100, bValue);

    free(g_pAdvSecAgent->pRabid);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, RabidFramework_SetParamUlongValue_DNSCacheSize) {
    const char *ParamName = "DNSCacheSize";
    ULONG bValue = 100;
    int comparisonResult = 0;
    const char *AdvSecurityRabidDNSCacheSize = "Advsecurity_RabidDNSCacheSize";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->pRabid = (COSA_DATAMODEL_RABID *)malloc(sizeof(COSA_DATAMODEL_RABID));
    ASSERT_NE(g_pAdvSecAgent->pRabid, nullptr);

    g_pAdvSecAgent->pRabid->uDNSCacheSize = 100;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityRabidDNSCacheSize), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaRabidSetDNSCacheSize(NULL, bValue));

    BOOL result = RabidFramework_SetParamUlongValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_EQ(100, bValue);

    free(g_pAdvSecAgent->pRabid);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvancedParentalControl_RFC_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->pAdvPC_RFC = (COSA_DATAMODEL_ADVPC_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVPC_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC_RFC, nullptr);

    g_pAdvSecAgent->pAdvPC_RFC->bEnable = TRUE;

    BOOL result = AdvancedParentalControl_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pAdvPC_RFC);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, AdvancedParentalControl_RFC_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->pAdvPC_RFC = (COSA_DATAMODEL_ADVPC_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVPC_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC_RFC, nullptr);

    g_pAdvSecAgent->pAdvPC_RFC->bEnable = FALSE;

    BOOL result = AdvancedParentalControl_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pAdvPC_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvancedParentalControl_RFC_SetParamBoolValue_Enable) {
    const char *ParamName = "Enable";
    BOOL bValue = TRUE;
    const char *AdvSecurityAPCRFCEnabled = "Adv_PCRFCEnable";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvPC_RFC = (COSA_DATAMODEL_ADVPC_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVPC_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC_RFC, nullptr);
    g_pAdvSecAgent->pAdvPC_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityAPCRFCEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -startAdvPC &"), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    if ((file = fopen(fname, "r")))
    {
        fclose(file);
    }
    else
    {
        file = fopen(fname, "w");
        fclose(file);
        val = 1;
    }

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvPCInit(NULL));

    BOOL result = AdvancedParentalControl_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_TRUE(g_pAdvSecAgent->pAdvPC_RFC->bEnable);

    if (val == 1)
    {
        int ret = remove(fname);
        if(ret != 0)
        {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pAdvPC_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvancedParentalControl_RFC_SetParamBoolValue_Disable) {
    const char *ParamName = "Enable";
    BOOL bValue = FALSE;
    const char *AdvSecurityAPCRFCEnabled = "Adv_PCRFCEnable";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvPC_RFC = (COSA_DATAMODEL_ADVPC_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVPC_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC_RFC, nullptr);
    g_pAdvSecAgent->pAdvPC_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityAPCRFCEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -stopAdvPC &"), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    if ((file = fopen(fname, "r")))
    {
        fclose(file);
    }
    else
    {
        file = fopen(fname, "w");
        fclose(file);
        val = 1;
    }

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvPCDeInit(NULL));

    BOOL result = AdvancedParentalControl_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_FALSE(g_pAdvSecAgent->pAdvPC_RFC->bEnable);

    if (val == 1)
    {
        int ret = remove(fname);
        if(ret != 0)
        {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pAdvPC_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, PrivacyProtection_RFC_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->pPrivProt_RFC = (COSA_DATAMODEL_PRIVACYPROTECTION_RFC *)malloc(sizeof(COSA_DATAMODEL_PRIVACYPROTECTION_RFC));
    ASSERT_NE(g_pAdvSecAgent->pPrivProt_RFC, nullptr);

    g_pAdvSecAgent->pPrivProt_RFC->bEnable = TRUE;

    BOOL result = PrivacyProtection_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pPrivProt_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, PrivacyProtection_RFC_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->pPrivProt_RFC = (COSA_DATAMODEL_PRIVACYPROTECTION_RFC *)malloc(sizeof(COSA_DATAMODEL_PRIVACYPROTECTION_RFC));
    ASSERT_NE(g_pAdvSecAgent->pPrivProt_RFC, nullptr);

    g_pAdvSecAgent->pPrivProt_RFC->bEnable = FALSE;

    BOOL result = PrivacyProtection_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pPrivProt_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, PrivacyProtection_RFC_SetParamBoolValue_Enable) {
    const char *ParamName = "Enable";
    BOOL bValue = TRUE;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pPrivProt_RFC = (COSA_DATAMODEL_PRIVACYPROTECTION_RFC *)malloc(sizeof(COSA_DATAMODEL_PRIVACYPROTECTION_RFC));
    ASSERT_NE(g_pAdvSecAgent->pPrivProt_RFC, nullptr);

    g_pAdvSecAgent->pPrivProt_RFC->bEnable = TRUE;

    BOOL result = PrivacyProtection_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_TRUE(g_pAdvSecAgent->pPrivProt_RFC->bEnable);

    free(g_pAdvSecAgent->pPrivProt_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, PrivacyProtection_RFC_SetParamBoolValue_Disable) {
    const char *ParamName = "Enable";
    BOOL bValue = FALSE;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pPrivProt_RFC = (COSA_DATAMODEL_PRIVACYPROTECTION_RFC *)malloc(sizeof(COSA_DATAMODEL_PRIVACYPROTECTION_RFC));
    ASSERT_NE(g_pAdvSecAgent->pPrivProt_RFC, nullptr);

    g_pAdvSecAgent->pPrivProt_RFC->bEnable = FALSE;


    BOOL result = PrivacyProtection_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_FALSE(g_pAdvSecAgent->pPrivProt_RFC->bEnable);

    free(g_pAdvSecAgent->pPrivProt_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, DeviceFingerPrintICMPv6_RFC_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pDFIcmpv6_RFC = (COSA_DATAMODEL_DEVICEFINGERPRINTICMPv6_RFC *)malloc(sizeof(COSA_DATAMODEL_DEVICEFINGERPRINTICMPv6_RFC));
    ASSERT_NE(g_pAdvSecAgent->pDFIcmpv6_RFC, nullptr);

    g_pAdvSecAgent->pDFIcmpv6_RFC->bEnable = TRUE;

    BOOL result = DeviceFingerPrintICMPv6_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pDFIcmpv6_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, DeviceFingerPrintICMPv6_RFC_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pDFIcmpv6_RFC = (COSA_DATAMODEL_DEVICEFINGERPRINTICMPv6_RFC *)malloc(sizeof(COSA_DATAMODEL_DEVICEFINGERPRINTICMPv6_RFC));
    ASSERT_NE(g_pAdvSecAgent->pDFIcmpv6_RFC, nullptr);

    g_pAdvSecAgent->pDFIcmpv6_RFC->bEnable = FALSE;

    BOOL result = DeviceFingerPrintICMPv6_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pDFIcmpv6_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, DeviceFingerPrintICMPv6_RFC_SetParamBoolValue_Enable) {
    const char *ParamName = "Enable";
    BOOL bValue = TRUE;
    const char *AdvSecurityDFICMPv6Enable = "Adv_DFICMPv6RFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pDFIcmpv6_RFC = (COSA_DATAMODEL_DEVICEFINGERPRINTICMPv6_RFC *)malloc(sizeof(COSA_DATAMODEL_DEVICEFINGERPRINTICMPv6_RFC));
    ASSERT_NE(g_pAdvSecAgent->pDFIcmpv6_RFC, nullptr);

    g_pAdvSecAgent->pDFIcmpv6_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityDFICMPv6Enable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableICMP6 &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvDFIcmpv6Init(NULL));

    BOOL result = DeviceFingerPrintICMPv6_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_TRUE(g_pAdvSecAgent->pDFIcmpv6_RFC->bEnable);

    free(g_pAdvSecAgent->pDFIcmpv6_RFC);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, DeviceFingerPrintICMPv6_RFC_SetParamBoolValue_Disable) {
    const char *ParamName = "Enable";
    BOOL bValue = FALSE;
    const char *AdvSecurityDFICMPv6Enable = "Adv_DFICMPv6RFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pDFIcmpv6_RFC = (COSA_DATAMODEL_DEVICEFINGERPRINTICMPv6_RFC *)malloc(sizeof(COSA_DATAMODEL_DEVICEFINGERPRINTICMPv6_RFC));
    ASSERT_NE(g_pAdvSecAgent->pDFIcmpv6_RFC, nullptr);

    g_pAdvSecAgent->pDFIcmpv6_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityDFICMPv6Enable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableICMP6 &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvDFIcmpv6DeInit(NULL));

    BOOL result = DeviceFingerPrintICMPv6_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_FALSE(g_pAdvSecAgent->pDFIcmpv6_RFC->bEnable);

    free(g_pAdvSecAgent->pDFIcmpv6_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, WS_Discovery_Analysis_RFC_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC = (COSA_DATAMODEL_WSDISCOVERYANALYSIS_RFC *)malloc(sizeof(COSA_DATAMODEL_WSDISCOVERYANALYSIS_RFC));
    ASSERT_NE(g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC, nullptr);

    g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC->bEnable = TRUE;

    BOOL result = WS_Discovery_Analysis_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, WS_Discovery_Analysis_RFC_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC = (COSA_DATAMODEL_WSDISCOVERYANALYSIS_RFC *)malloc(sizeof(COSA_DATAMODEL_WSDISCOVERYANALYSIS_RFC));
    ASSERT_NE(g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC, nullptr);

    g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC->bEnable = FALSE;

    BOOL result = WS_Discovery_Analysis_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, WS_Discovery_Analysis_RFC_SetParamBoolValue_Enable) {
    const char *ParamName = "Enable";
    BOOL bValue = TRUE;
    const char *AdvSecurityWSDisEnable = "Adv_WSDisAnaRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC = (COSA_DATAMODEL_WSDISCOVERYANALYSIS_RFC *)malloc(sizeof(COSA_DATAMODEL_WSDISCOVERYANALYSIS_RFC));
    ASSERT_NE(g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC, nullptr);

    g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityWSDisEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableWSDiscovery &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaWSDisInit(NULL));

    BOOL result = WS_Discovery_Analysis_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_TRUE(g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC->bEnable);

    free(g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, WS_Discovery_Analysis_RFC_SetParamBoolValue_Disable) {
    const char *ParamName = "Enable";
    BOOL bValue = FALSE;
    const char *AdvSecurityWSDisEnable = "Adv_WSDisAnaRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC = (COSA_DATAMODEL_WSDISCOVERYANALYSIS_RFC *)malloc(sizeof(COSA_DATAMODEL_WSDISCOVERYANALYSIS_RFC));
    ASSERT_NE(g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC, nullptr);

    g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityWSDisEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableWSDiscovery &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaWSDisDeInit(NULL));

    BOOL result = WS_Discovery_Analysis_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_FALSE(g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC->bEnable);

    free(g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvancedSecurityOTM_RFC_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvSecOTM_RFC = (COSA_DATAMODEL_ADVSECOTM_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECOTM_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecOTM_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecOTM_RFC->bEnable = TRUE;

    BOOL result = AdvancedSecurityOTM_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pAdvSecOTM_RFC);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, AdvancedSecurityOTM_RFC_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvSecOTM_RFC = (COSA_DATAMODEL_ADVSECOTM_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECOTM_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecOTM_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecOTM_RFC->bEnable = FALSE;

    BOOL result = AdvancedSecurityOTM_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pAdvSecOTM_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvancedSecurityOTM_RFC_SetParamBoolValue_Enable) {
    const char *ParamName = "Enable";
    BOOL bValue = TRUE;
    const char *AdvSecurityOTMEnable = "Adv_AdvSecOTMRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvSecOTM_RFC = (COSA_DATAMODEL_ADVSECOTM_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECOTM_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecOTM_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecOTM_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityOTMEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableOTM &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecOTMInit(NULL));

    BOOL result = AdvancedSecurityOTM_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_TRUE(g_pAdvSecAgent->pAdvSecOTM_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecOTM_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvancedSecurityOTM_RFC_SetParamBoolValue_Disable) {
    const char *ParamName = "Enable";
    BOOL bValue = FALSE;
    const char *AdvSecurityOTMEnable = "Adv_AdvSecOTMRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvSecOTM_RFC = (COSA_DATAMODEL_ADVSECOTM_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECOTM_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecOTM_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecOTM_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityOTMEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableOTM &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecOTMDeInit(NULL));

    BOOL result = AdvancedSecurityOTM_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_FALSE(g_pAdvSecAgent->pAdvSecOTM_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecOTM_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecAgentRaptr_RFC_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pRaptr_RFC = (COSA_DATAMODEL_RAPTR_RFC *)malloc(sizeof(COSA_DATAMODEL_RAPTR_RFC));
    ASSERT_NE(g_pAdvSecAgent->pRaptr_RFC, nullptr);

    g_pAdvSecAgent->pRaptr_RFC->bEnable = TRUE;

    BOOL result = AdvSecAgentRaptr_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pRaptr_RFC);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecAgentRaptr_RFC_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pRaptr_RFC = (COSA_DATAMODEL_RAPTR_RFC *)malloc(sizeof(COSA_DATAMODEL_RAPTR_RFC));
    ASSERT_NE(g_pAdvSecAgent->pRaptr_RFC, nullptr);

    g_pAdvSecAgent->pRaptr_RFC->bEnable = FALSE;

    BOOL result = AdvSecAgentRaptr_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pRaptr_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecAgentRaptr_RFC_SetParamBoolValue_Enable) {
    const char *ParamName = "Enable";
    BOOL bValue = TRUE;
    const char *AdvSecurityRaptrEnable = "Adv_RaptrRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pRaptr_RFC = (COSA_DATAMODEL_RAPTR_RFC *)malloc(sizeof(COSA_DATAMODEL_RAPTR_RFC));
    ASSERT_NE(g_pAdvSecAgent->pRaptr_RFC, nullptr);

    g_pAdvSecAgent->pRaptr_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityRaptrEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableRaptr &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecAgentRaptrInit(NULL));

    BOOL result = AdvSecAgentRaptr_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_TRUE(g_pAdvSecAgent->pRaptr_RFC->bEnable);

    free(g_pAdvSecAgent->pRaptr_RFC);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecAgentRaptr_RFC_SetParamBoolValue_Disable) {
    const char *ParamName = "Enable";
    BOOL bValue = FALSE;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pRaptr_RFC = (COSA_DATAMODEL_RAPTR_RFC *)malloc(sizeof(COSA_DATAMODEL_RAPTR_RFC));
    ASSERT_NE(g_pAdvSecAgent->pRaptr_RFC, nullptr);

    g_pAdvSecAgent->pRaptr_RFC->bEnable = FALSE;

    BOOL result = AdvSecAgentRaptr_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_FALSE(g_pAdvSecAgent->pRaptr_RFC->bEnable);

    free(g_pAdvSecAgent->pRaptr_RFC);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, AdvanceSecurityUserSpace_RFC_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->pAdvSecUserSpace_RFC = (COSA_DATAMODEL_ADVSECUSERSPACE_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECUSERSPACE_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecUserSpace_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecUserSpace_RFC->bEnable = TRUE;

    BOOL result = AdvanceSecurityUserSpace_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pAdvSecUserSpace_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvanceSecurityUserSpace_RFC_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->pAdvSecUserSpace_RFC = (COSA_DATAMODEL_ADVSECUSERSPACE_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECUSERSPACE_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecUserSpace_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecUserSpace_RFC->bEnable = FALSE;

    BOOL result = AdvanceSecurityUserSpace_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pAdvSecUserSpace_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvanceSecurityUserSpace_RFC_SetParamBoolValue_Enable) {
    const char *ParamName = "Enable";
    BOOL bValue = TRUE;
    const char *AdvSecurityUserSpaceEnable = "Adv_AdvSecUserSpaceRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecUserSpace_RFC = (COSA_DATAMODEL_ADVSECUSERSPACE_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECUSERSPACE_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecUserSpace_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecUserSpace_RFC->bEnable = TRUE;

    g_pAdvSecAgent->pAdvWifiDataCollection_RFC = (COSA_DATAMODEL_ADVSECWIFIDATACOLLECTION_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECWIFIDATACOLLECTION_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvWifiDataCollection_RFC, nullptr);
    g_pAdvSecAgent->pAdvWifiDataCollection_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityUserSpaceEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableUS &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecUserSpaceInit(NULL));

    BOOL result = AdvanceSecurityUserSpace_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_TRUE(g_pAdvSecAgent->pAdvSecUserSpace_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecUserSpace_RFC);
    free(g_pAdvSecAgent->pAdvWifiDataCollection_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvanceSecurityUserSpace_RFC_SetParamBoolValue_Disable) {
    const char *ParamName = "Enable";
    BOOL bValue = FALSE;
    const char *AdvSecurityUserSpaceEnable = "Adv_AdvSecUserSpaceRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecUserSpace_RFC = (COSA_DATAMODEL_ADVSECUSERSPACE_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECUSERSPACE_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecUserSpace_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecUserSpace_RFC->bEnable = FALSE;

    g_pAdvSecAgent->pAdvWifiDataCollection_RFC = (COSA_DATAMODEL_ADVSECWIFIDATACOLLECTION_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECWIFIDATACOLLECTION_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvWifiDataCollection_RFC, nullptr);
    g_pAdvSecAgent->pAdvWifiDataCollection_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityUserSpaceEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableUS &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecUserSpaceDeInit(NULL));

    BOOL result = AdvanceSecurityUserSpace_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_FALSE(g_pAdvSecAgent->pAdvSecUserSpace_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecUserSpace_RFC);
    free(g_pAdvSecAgent->pAdvWifiDataCollection_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecAgent_RFC_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->pAdvSecAgent_RFC = (COSA_DATAMODEL_ADVSECAGENT_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECAGENT_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecAgent_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecAgent_RFC->bEnable = TRUE;

    BOOL result = AdvSecAgent_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pAdvSecAgent_RFC);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecAgent_RFC_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->pAdvSecAgent_RFC = (COSA_DATAMODEL_ADVSECAGENT_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECAGENT_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecAgent_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecAgent_RFC->bEnable = FALSE;

    BOOL result = AdvSecAgent_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pAdvSecAgent_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecAgent_RFC_SetParamBoolValue_Enable) {
    const char *ParamName = "Enable";
    BOOL bValue = TRUE;
    const char *AdvSecurityAgentEnable = "Adv_AdvSecAgentRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecAgent_RFC = (COSA_DATAMODEL_ADVSECAGENT_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECAGENT_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecAgent_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecAgent_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityAgentEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableAGT &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecAgentInit(NULL));

    BOOL result = AdvSecAgent_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_TRUE(g_pAdvSecAgent->pAdvSecAgent_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecAgent_RFC);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecAgent_RFC_SetParamBoolValue_Disable) {
    const char *ParamName = "Enable";
    BOOL bValue = FALSE;
    const char *AdvSecurityAgentEnable = "Adv_AdvSecAgentRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecAgent_RFC = (COSA_DATAMODEL_ADVSECAGENT_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECAGENT_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecAgent_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecAgent_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityAgentEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableAGT &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecAgentDeInit(NULL));

    BOOL result = AdvSecAgent_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_FALSE(g_pAdvSecAgent->pAdvSecAgent_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecAgent_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecSafeBrowsing_RFC_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC = (COSA_DATAMODEL_ADVSECSAFEBROWSING_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECSAFEBROWSING_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC->bEnable = TRUE;

    BOOL result = AdvSecSafeBrowsing_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecSafeBrowsing_RFC_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC = (COSA_DATAMODEL_ADVSECSAFEBROWSING_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECSAFEBROWSING_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC->bEnable = FALSE;

    BOOL result = AdvSecSafeBrowsing_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecSafeBrowsing_RFC_SetParamBoolValue_Enable) {
    const char *ParamName = "Enable";
    BOOL bValue = TRUE;
    const char *AdvSecuritySafeBrowsingEnable = "Adv_AdvSecSafeBrowsingRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC = (COSA_DATAMODEL_ADVSECSAFEBROWSING_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECSAFEBROWSING_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecUserSpace_RFC = (COSA_DATAMODEL_ADVSECUSERSPACE_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECUSERSPACE_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecUserSpace_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecUserSpace_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecuritySafeBrowsingEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableSBRule &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecSafeBrowsingInit(NULL));

    BOOL result = AdvSecSafeBrowsing_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_TRUE(g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC);
    free(g_pAdvSecAgent->pAdvSecUserSpace_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecSafeBrowsing_RFC_SetParamBoolValue_Disable) {
    const char *ParamName = "Enable";
    BOOL bValue = FALSE;
    const char *AdvSecuritySafeBrowsingEnable = "Adv_AdvSecSafeBrowsingRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC = (COSA_DATAMODEL_ADVSECSAFEBROWSING_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECSAFEBROWSING_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC->bEnable = FALSE;

    g_pAdvSecAgent->pAdvSecUserSpace_RFC = (COSA_DATAMODEL_ADVSECUSERSPACE_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECUSERSPACE_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecUserSpace_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecUserSpace_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecuritySafeBrowsingEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableSBRule &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecSafeBrowsingDeInit(NULL));

    BOOL result = AdvSecSafeBrowsing_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_FALSE(g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC);
    free(g_pAdvSecAgent->pAdvSecUserSpace_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecCujoTelemetryWiFiFP_RFC_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC = (COSA_DATAMODEL_ADVSECCUJOTELEMETRYWIFIFP_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTELEMETRYWIFIFP_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC->bEnable = TRUE;

    BOOL result = AdvSecCujoTelemetryWiFiFP_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecCujoTelemetryWiFiFP_RFC_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC = (COSA_DATAMODEL_ADVSECCUJOTELEMETRYWIFIFP_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTELEMETRYWIFIFP_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC->bEnable = FALSE;

    BOOL result = AdvSecCujoTelemetryWiFiFP_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecCujoTelemetryWiFiFP_RFC_SetParamBoolValue_Enable) {
    const char *ParamName = "Enable";
    BOOL bValue = TRUE;
    const char *AdvSecurityCujoTelemetryWiFiFPEnable = "Adv_AdvSecCujoTelemetryWiFiFPRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC = (COSA_DATAMODEL_ADVSECCUJOTELEMETRYWIFIFP_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTELEMETRYWIFIFP_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecUserSpace_RFC = (COSA_DATAMODEL_ADVSECUSERSPACE_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECUSERSPACE_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecUserSpace_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecUserSpace_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityCujoTelemetryWiFiFPEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableCTW &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecCujoTelemetryWiFiFPInit(NULL));

    BOOL result = AdvSecCujoTelemetryWiFiFP_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_TRUE(g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC);
    free(g_pAdvSecAgent->pAdvSecUserSpace_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvSecCujoTelemetryWiFiFP_RFC_SetParamBoolValue_Disable) {
    const char *ParamName = "Enable";
    BOOL bValue = FALSE;
    const char *AdvSecurityCujoTelemetryWiFiFPEnable = "Adv_AdvSecCujoTelemetryWiFiFPRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC = (COSA_DATAMODEL_ADVSECCUJOTELEMETRYWIFIFP_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTELEMETRYWIFIFP_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC->bEnable = FALSE;

    g_pAdvSecAgent->pAdvSecUserSpace_RFC = (COSA_DATAMODEL_ADVSECUSERSPACE_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECUSERSPACE_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecUserSpace_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecUserSpace_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityCujoTelemetryWiFiFPEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableCTW &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecCujoTelemetryWiFiFPDeInit(NULL));

    BOOL result = AdvSecCujoTelemetryWiFiFP_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_FALSE(g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC);
    free(g_pAdvSecAgent->pAdvSecUserSpace_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvanceSecurityCujoTracer_RFC_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecCujoTracer_RFC = (COSA_DATAMODEL_ADVSECCUJOTRACER_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTRACER_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTracer_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTracer_RFC->bEnable = TRUE;

    BOOL result = AdvanceSecurityCujoTracer_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pAdvSecCujoTracer_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvanceSecurityCujoTracer_RFC_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecCujoTracer_RFC = (COSA_DATAMODEL_ADVSECCUJOTRACER_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTRACER_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTracer_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTracer_RFC->bEnable = FALSE;

    BOOL result = AdvanceSecurityCujoTracer_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pAdvSecCujoTracer_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvanceSecurityCujoTracer_RFC_SetParamBoolValue_Enable) {
    const char *ParamName = "Enable";
    BOOL bValue = TRUE;
    const char *AdvSecurityCujoTracerEnable = "Adv_AdvSecCujoTracerRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecCujoTracer_RFC = (COSA_DATAMODEL_ADVSECCUJOTRACER_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTRACER_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTracer_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTracer_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityCujoTracerEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableCT &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecCujoTracerInit(NULL));

    BOOL result = AdvanceSecurityCujoTracer_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_TRUE(g_pAdvSecAgent->pAdvSecCujoTracer_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecCujoTracer_RFC);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, AdvanceSecurityCujoTracer_RFC_SetParamBoolValue_Disable) {
    const char *ParamName = "Enable";
    BOOL bValue = FALSE;
    const char *AdvSecurityCujoTracerEnable = "Adv_AdvSecCujoTracerRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecCujoTracer_RFC = (COSA_DATAMODEL_ADVSECCUJOTRACER_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTRACER_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTracer_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTracer_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityCujoTracerEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableCT &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecCujoTracerDeInit(NULL));

    BOOL result = AdvanceSecurityCujoTracer_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_FALSE(g_pAdvSecAgent->pAdvSecCujoTracer_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecCujoTracer_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvanceSecurityCujoTelemetry_RFC_GetParamBoolValue_Enable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC = (COSA_DATAMODEL_ADVSECCUJOTELEMETRY_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTELEMETRY_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC->bEnable = TRUE;

    BOOL result = AdvanceSecurityCujoTelemetry_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_TRUE(resultBool);

    free(g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvanceSecurityCujoTelemetry_RFC_GetParamBoolValue_Disable) {
    BOOL resultBool;
    const char* ParamName = "Enable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC = (COSA_DATAMODEL_ADVSECCUJOTELEMETRY_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTELEMETRY_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC->bEnable = FALSE;

    BOOL result = AdvanceSecurityCujoTelemetry_RFC_GetParamBoolValue(NULL, (char*)ParamName, &resultBool);

    EXPECT_TRUE(result);
    EXPECT_FALSE(resultBool);

    free(g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityDmlTestFixture, AdvanceSecurityCujoTelemetry_RFC_SetParamBoolValue_Enable) {
    const char *ParamName = "Enable";
    BOOL bValue = TRUE;
    const char *AdvSecurityCujoTelemetryEnable = "Adv_AdvSecCujoTelemetryRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC = (COSA_DATAMODEL_ADVSECCUJOTELEMETRY_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTELEMETRY_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityCujoTelemetryEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableCTD &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecCujoTelemetryInit(NULL));

    BOOL result = AdvanceSecurityCujoTelemetry_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_TRUE(g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityDmlTestFixture, AdvanceSecurityCujoTelemetry_RFC_SetParamBoolValue_Disable) {
    const char *ParamName = "Enable";
    BOOL bValue = FALSE;
    const char *AdvSecurityCujoTelemetryEnable = "Adv_AdvSecCujoTelemetryRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC = (COSA_DATAMODEL_ADVSECCUJOTELEMETRY_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTELEMETRY_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityCujoTelemetryEnable), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableCTD &"), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(ANSC_STATUS_SUCCESS, CosaAdvSecCujoTelemetryDeInit(NULL));

    BOOL result = AdvanceSecurityCujoTelemetry_RFC_SetParamBoolValue(NULL, (char*)ParamName, bValue);

    EXPECT_TRUE(result);
    EXPECT_FALSE(g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC);
    free(g_pAdvSecAgent);
}