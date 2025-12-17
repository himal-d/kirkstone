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

class CcspAdvSecurityWebconfigTestFixture : public ::testing::Test {
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

// cosa_adv_security_webconfig.c file test cases

TEST_F(CcspAdvSecurityWebconfigTestFixture, advsec_webconfig_get_blobversion_success) {
    const char subdoc_ver[] = "1";
    char subdoc[] = "test";

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .WillOnce(DoAll(
            SetArgPointee<2>(*subdoc_ver),
            Return(0)
        ));

    uint32_t result = advsec_webconfig_get_blobversion(subdoc);

    EXPECT_EQ(1, result);
}

TEST_F(CcspAdvSecurityWebconfigTestFixture, advsec_webconfig_get_blobversion_failure) {
    const char buf[] = "test_version";
    const char subdoc_ver[] = "1";
    char subdoc[] = "test";

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .WillOnce(DoAll(
            SetArgPointee<2>(*subdoc_ver),
            Return(1)
        ));

    uint32_t result = advsec_webconfig_get_blobversion(subdoc);

    EXPECT_EQ(0, result);
}

TEST_F(CcspAdvSecurityWebconfigTestFixture, advsec_webconfig_set_blobversion_success) {
    const char subdoc_ver[] = "1";
    char subdoc[] = "test";
    uint32_t version = 1;
    const char buf[] = "test_version";

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(_, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    int result = advsec_webconfig_set_blobversion(subdoc, version);

    EXPECT_EQ(0, result);
}

TEST_F(CcspAdvSecurityWebconfigTestFixture, advsec_webconfig_set_blobversion_failure) {
    const char subdoc_ver[] = "1";
    char subdoc[] = "test";
    uint32_t version = 1;
    const char buf[] = "test_version";

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(_, _))
        .Times(1)
        .WillOnce(Return(1));

    int result = advsec_webconfig_set_blobversion(subdoc, version);

    EXPECT_EQ(-1, result);
}

TEST_F(CcspAdvSecurityWebconfigTestFixture, advsec_webconfig_init) {
    const char sub_docs[] = "ADVSEC_WEBCONFIG_SUBDOC_NAME";
    blobRegInfo *blobData;

    EXPECT_CALL(*g_safecLibMock, _memset_s_chk(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_webconfigFwMock, register_sub_docs(_, _, _, _))
        .Times(1);

    EXPECT_TRUE(advsec_webconfig_get_blobversion);
    EXPECT_TRUE(advsec_webconfig_set_blobversion);

    advsec_webconfig_init();
}

TEST_F(CcspAdvSecurityWebconfigTestFixture, advsec_webconfig_process_request_success) {
    
    advsecurityparam_t feature;
    advsecuritydoc_t advsec;
    advsec.param = &feature;
    advsec.subdoc_name = strdup("advsecurity");
    advsec.param->fingerprint_enable = true;
    advsec.param->softflowd_enable = true;
    advsec.param->safebrowsing_enable = true;
    advsec.param->parental_control_activate = true;
    advsec.param->privacy_protection_activate = true;

    int comparisonResult = 1;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSoftFlowd = (COSA_DATAMODEL_SOFTFLOWD *)malloc(sizeof(COSA_DATAMODEL_SOFTFLOWD));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSoftFlowd, nullptr);
    g_pAdvSecAgent->pAdvSec->pSafeBrows = (COSA_DATAMODEL_SB *)malloc(sizeof(COSA_DATAMODEL_SB));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSafeBrows, nullptr);
    g_pAdvSecAgent->pAdvPC = (COSA_DATAMODEL_ADVPARENTALCONTROL *)malloc(sizeof(COSA_DATAMODEL_ADVPARENTALCONTROL));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC, nullptr);
    g_pAdvSecAgent->pPrivProt = (COSA_DATAMODEL_PRIVACYPROTECTION *)malloc(sizeof(COSA_DATAMODEL_PRIVACYPROTECTION));
    ASSERT_NE(g_pAdvSecAgent->pPrivProt, nullptr);

    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvSec->pSafeBrows->bEnable = TRUE;
    g_pAdvSecAgent->pAdvSec->pSoftFlowd->bEnable = TRUE;
    g_pAdvSecAgent->pAdvPC->bEnable = TRUE;
    g_pAdvSecAgent->pPrivProt->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _memset_s_chk(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(_, _, _, _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -configure_features &"),_))
        .Times(1)
        .WillOnce(Return(0));

    int result = advsec_webconfig_handle_blob(advsec.param);
    EXPECT_EQ(result, BLOB_EXEC_SUCCESS);

    pErr result2 = advsec_webconfig_process_request(&advsec);
    EXPECT_EQ(result2->ErrorCode, SUBDOC_NOT_SUPPORTED);

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec->pSoftFlowd);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent->pAdvPC);
    free(g_pAdvSecAgent->pPrivProt);
    free(g_pAdvSecAgent);
    free(advsec.subdoc_name);
}

TEST_F(CcspAdvSecurityWebconfigTestFixture, advsec_webconfig_process_request_failure) {
    
    advsecurityparam_t feature;
    advsecuritydoc_t advsec;
    advsec.param = &feature;
    advsec.subdoc_name = strdup("advsecurity");
    advsec.param->fingerprint_enable = false;
    advsec.param->softflowd_enable = false;
    advsec.param->safebrowsing_enable = false;
    advsec.param->parental_control_activate = false;
    advsec.param->privacy_protection_activate = false;

    int comparisonResult = 1;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSoftFlowd = (COSA_DATAMODEL_SOFTFLOWD *)malloc(sizeof(COSA_DATAMODEL_SOFTFLOWD));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSoftFlowd, nullptr);
    g_pAdvSecAgent->pAdvSec->pSafeBrows = (COSA_DATAMODEL_SB *)malloc(sizeof(COSA_DATAMODEL_SB));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSafeBrows, nullptr);
    g_pAdvSecAgent->pAdvPC = (COSA_DATAMODEL_ADVPARENTALCONTROL *)malloc(sizeof(COSA_DATAMODEL_ADVPARENTALCONTROL));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC, nullptr);
    g_pAdvSecAgent->pPrivProt = (COSA_DATAMODEL_PRIVACYPROTECTION *)malloc(sizeof(COSA_DATAMODEL_PRIVACYPROTECTION));
    ASSERT_NE(g_pAdvSecAgent->pPrivProt, nullptr);

    g_pAdvSecAgent->bEnable = TRUE;
    g_pAdvSecAgent->pAdvSec->pSafeBrows->bEnable = TRUE;
    g_pAdvSecAgent->pAdvSec->pSoftFlowd->bEnable = TRUE;
    g_pAdvSecAgent->pAdvPC->bEnable = TRUE;
    g_pAdvSecAgent->pPrivProt->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _memset_s_chk(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(_, _, _, _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disable &"),_))
        .Times(1)
        .WillOnce(Return(0));
    
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(_, _))
        .Times(5)
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(5)
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(5)
        .WillRepeatedly(Return(0));

    int result = advsec_webconfig_handle_blob(advsec.param);
    EXPECT_EQ(result, BLOB_EXEC_SUCCESS);

    pErr result2 = advsec_webconfig_process_request(&advsec);
    EXPECT_EQ(result2->ErrorCode, SUBDOC_NOT_SUPPORTED);

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec->pSoftFlowd);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent->pAdvPC);
    free(g_pAdvSecAgent->pPrivProt);
    free(g_pAdvSecAgent);
    free(advsec.subdoc_name);
}

TEST_F(CcspAdvSecurityWebconfigTestFixture, advsec_webconfig_free_resources) 
{
    execData *blob_exec_data = (execData*)malloc(sizeof(execData));
    ASSERT_NE(blob_exec_data, nullptr);
    advsecuritydoc_t *ad = (advsecuritydoc_t *)malloc(sizeof(advsecuritydoc_t));
    ASSERT_NE(ad, nullptr);
    blob_exec_data->user_data = ad;

    EXPECT_CALL(*g_anscMemoryMock, AnscFreeMemory(_))
        .Times(3);

    advsec_webconfig_free_resources(blob_exec_data);
    blob_exec_data = NULL;
    EXPECT_EQ(blob_exec_data, nullptr);

    free(ad);
}