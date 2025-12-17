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

class CcspAdvSecurityInternalTestFixture : public ::testing::Test {
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

TEST_F(CcspAdvSecurityInternalTestFixture, ccsp_advsec_start_features_sb) {
    const advsec_feature_type type = ADVSEC_SAFEBROWSING;
    const char *AdvSecuritySBEnabled = "Advsecurity_SafeBrowsing";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSafeBrows = (COSA_DATAMODEL_SB *)malloc(sizeof(COSA_DATAMODEL_SB));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSafeBrows, nullptr);

    g_pAdvSecAgent->pAdvSec->pSafeBrows->bEnable = FALSE;
    g_pAdvSecAgent->bEnable = TRUE;

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

    if ((file = fopen(fname, "r"))) {
        fclose(file);
    } else {
        file = fopen(fname, "w");
        fclose(file);
        val = 1;
    }

    ANSC_STATUS status = CosaAdvSecStartFeatures(type);

    if (val == 1) {
        int ret = remove(fname);
        if(ret != 0) {
            printf("Error deleting file %s", fname);
        }
    }

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, ccsp_advsec_start_features_sf) {
    const advsec_feature_type type = ADVSEC_SOFTFLOWD;
    const char *AdvSecuritySFEnabled = "Advsecurity_Softflowd";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSoftFlowd = (COSA_DATAMODEL_SOFTFLOWD *)malloc(sizeof(COSA_DATAMODEL_SOFTFLOWD));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSoftFlowd, nullptr);

    g_pAdvSecAgent->pAdvSec->pSoftFlowd->bEnable = FALSE;
    g_pAdvSecAgent->bEnable = TRUE;

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

    if ((file = fopen(fname, "r"))) {
        fclose(file);
    } else {
        file = fopen(fname, "w");
        fclose(file);
        val = 1;
    }

    ANSC_STATUS status = CosaAdvSecStartFeatures(type);

    if (val == 1) {
        int ret = remove(fname);
        if(ret != 0) {
            printf("Error deleting file %s", fname);
        }
    }

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);

    free(g_pAdvSecAgent->pAdvSec->pSoftFlowd);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, ccsp_advsec_start_features_sb_sf) {
    const advsec_feature_type type = ADVSEC_ALL;
    const char *AdvSecuritySBEnabled = "Advsecurity_SafeBrowsing";
    const char *AdvSecuritySFEnabled = "Advsecurity_Softflowd";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSoftFlowd = (COSA_DATAMODEL_SOFTFLOWD *)malloc(sizeof(COSA_DATAMODEL_SOFTFLOWD));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSoftFlowd, nullptr);
    g_pAdvSecAgent->pAdvSec->pSafeBrows = (COSA_DATAMODEL_SB *)malloc(sizeof(COSA_DATAMODEL_SB));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSafeBrows, nullptr);

    g_pAdvSecAgent->pAdvSec->pSafeBrows->bEnable = FALSE;
    g_pAdvSecAgent->pAdvSec->pSoftFlowd->bEnable = FALSE;
    g_pAdvSecAgent->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecuritySBEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecuritySFEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(2)
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -start sb sf &"), _))
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

    ANSC_STATUS status = CosaAdvSecStartFeatures(type);
    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);

    if (val == 1)
    {
        int ret = remove(fname);
        if(ret != 0)
        {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec->pSoftFlowd);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, ccsp_advsec_stop_features_sb) {
    const advsec_feature_type type = ADVSEC_SAFEBROWSING;
    const char *AdvSecuritySBEnabled = "Advsecurity_SafeBrowsing";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSafeBrows = (COSA_DATAMODEL_SB *)malloc(sizeof(COSA_DATAMODEL_SB));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSafeBrows, nullptr);

    g_pAdvSecAgent->pAdvSec->pSafeBrows->bEnable = TRUE;
    g_pAdvSecAgent->bEnable = TRUE;

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

    ANSC_STATUS status = CosaAdvSecStopFeatures(type);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pAdvSec->pSafeBrows->bEnable);

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

TEST_F(CcspAdvSecurityInternalTestFixture, ccsp_advsec_stop_features_sf) {
    const advsec_feature_type type = ADVSEC_SOFTFLOWD;
    const char *AdvSecuritySFEnabled = "Advsecurity_Softflowd";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSoftFlowd = (COSA_DATAMODEL_SOFTFLOWD *)malloc(sizeof(COSA_DATAMODEL_SOFTFLOWD));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSoftFlowd, nullptr);

    g_pAdvSecAgent->pAdvSec->pSoftFlowd->bEnable = TRUE;
    g_pAdvSecAgent->bEnable = TRUE;

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

    ANSC_STATUS status = CosaAdvSecStopFeatures(type);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pAdvSec->pSoftFlowd->bEnable);

    free(g_pAdvSecAgent->pAdvSec->pSoftFlowd);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, ccsp_advsec_stop_features_sb_sf) {
    const advsec_feature_type type = ADVSEC_ALL;
    const char *AdvSecuritySBEnabled = "Advsecurity_SafeBrowsing";
    const char *AdvSecuritySFEnabled = "Advsecurity_Softflowd";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSoftFlowd = (COSA_DATAMODEL_SOFTFLOWD *)malloc(sizeof(COSA_DATAMODEL_SOFTFLOWD));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSoftFlowd, nullptr);
    g_pAdvSecAgent->pAdvSec->pSafeBrows = (COSA_DATAMODEL_SB *)malloc(sizeof(COSA_DATAMODEL_SB));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSafeBrows, nullptr);

    g_pAdvSecAgent->pAdvSec->pSafeBrows->bEnable = TRUE;
    g_pAdvSecAgent->pAdvSec->pSoftFlowd->bEnable = TRUE;
    g_pAdvSecAgent->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecuritySBEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecuritySFEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(2)
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -stop sb sf &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecStopFeatures(type);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pAdvSec->pSafeBrows->bEnable);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pAdvSec->pSoftFlowd->bEnable);

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec->pSoftFlowd);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, Cosa_AdvSec_Agent_Raptr_Init) {
    const char *RaptrEnabled = "Adv_RaptrRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pRaptr_RFC = (COSA_DATAMODEL_RAPTR_RFC *)malloc(sizeof(COSA_DATAMODEL_RAPTR_RFC));
    ASSERT_NE(g_pAdvSecAgent->pRaptr_RFC, nullptr);

    g_pAdvSecAgent->pRaptr_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(RaptrEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableRaptr &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecAgentRaptrInit(g_pAdvSecAgent->pRaptr_RFC);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(TRUE, g_pAdvSecAgent->pRaptr_RFC->bEnable);

    free(g_pAdvSecAgent->pRaptr_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, Cosa_AdvSec_Agent_Raptr_DeInit) {
    const char *RaptrEnabled = "Adv_RaptrRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pRaptr_RFC = (COSA_DATAMODEL_RAPTR_RFC *)malloc(sizeof(COSA_DATAMODEL_RAPTR_RFC));
    ASSERT_NE(g_pAdvSecAgent->pRaptr_RFC, nullptr);

    g_pAdvSecAgent->pRaptr_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(RaptrEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableRaptr &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecAgentRaptrDeInit(g_pAdvSecAgent->pRaptr_RFC);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pRaptr_RFC->bEnable);

    free(g_pAdvSecAgent->pRaptr_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, ccsp_start_privacy_protection) {
    BOOL update_status = TRUE;
    const char *PrivacyProtectionEnabled = "Adv_PPActivate";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pPrivProt = (COSA_DATAMODEL_PRIVACYPROTECTION *)malloc(sizeof(COSA_DATAMODEL_PRIVACYPROTECTION));
    ASSERT_NE(g_pAdvSecAgent->pPrivProt, nullptr);

    g_pAdvSecAgent->pPrivProt->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(PrivacyProtectionEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -startPrivProt &"), _))
        .Times(1)
        .WillOnce(Return(0));

    if ((file = fopen(fname, "r"))) {
        fclose(file);
    } else {
        file = fopen(fname, "w");
        fclose(file);
        val = 1;
    }

    ANSC_STATUS status = CosaStartPrivacyProtection(update_status);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(TRUE, g_pAdvSecAgent->pPrivProt->bEnable);

    if (val == 1) {
        int ret = remove(fname);
        if(ret != 0) {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pPrivProt);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, ccsp_stop_privacy_protection) {
    BOOL update_status = TRUE;
    const char *PrivacyProtectionEnabled = "Adv_PPActivate";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pPrivProt = (COSA_DATAMODEL_PRIVACYPROTECTION *)malloc(sizeof(COSA_DATAMODEL_PRIVACYPROTECTION));
    ASSERT_NE(g_pAdvSecAgent->pPrivProt, nullptr);

    g_pAdvSecAgent->pPrivProt->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(PrivacyProtectionEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -stopPrivProt &"), _))
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

    ANSC_STATUS status = CosaStopPrivacyProtection(update_status);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pPrivProt->bEnable);

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

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecInit_Success)
{
    const char *DeviceFingerPrintEnabled = "Advsecurity_DeviceFingerPrint";
    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->bEnable = TRUE;

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enable &"), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(DeviceFingerPrintEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));


    ANSC_STATUS status = CosaAdvSecInit();
    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(g_pAdvSecAgent->bEnable, TRUE);

    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecDeInit_Success)
{
    const char *DeviceFingerPrintEnabled = "Advsecurity_DeviceFingerPrint";
    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);

    g_pAdvSecAgent->bEnable = FALSE;

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disable &"), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(DeviceFingerPrintEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecDeInit();
    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(g_pAdvSecAgent->bEnable, FALSE);

    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaStartAdvParentalControl_Success)
{
    const char *AdvParentalControl = "Adv_PCActivate";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvPC = (COSA_DATAMODEL_ADVPARENTALCONTROL *)malloc(sizeof(COSA_DATAMODEL_ADVPARENTALCONTROL));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC, nullptr);

    g_pAdvSecAgent->pAdvPC->bEnable = TRUE;

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -startAdvPC &"), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvParentalControl), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
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

    ANSC_STATUS status = CosaStartAdvParentalControl(TRUE);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(TRUE, g_pAdvSecAgent->pAdvPC->bEnable);

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

TEST_F(CcspAdvSecurityInternalTestFixture, CosaStopAdvParentalControl_Success)
{
    const char *AdvParentalControl = "Adv_PCActivate";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvPC = (COSA_DATAMODEL_ADVPARENTALCONTROL *)malloc(sizeof(COSA_DATAMODEL_ADVPARENTALCONTROL));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC, nullptr);

    g_pAdvSecAgent->pAdvPC->bEnable = FALSE;

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -stopAdvPC &"), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvParentalControl), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
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

    ANSC_STATUS status = CosaStopAdvParentalControl(TRUE);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pAdvPC->bEnable);

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

TEST_F(CcspAdvSecurityInternalTestFixture, advsec_webconfig_handle_blob_fingerprint_enable)
{
    const char *AdvSecuritySBEnabled = "Advsecurity_SafeBrowsing";
    const char *AdvSecuritySFEnabled = "Advsecurity_Softflowd";
    const char *AdvSecurityPCEnabled = "Advsecurity_ParentalControl";
    const char *AdvSecurityPPEnabled = "Advsecurity_PrivacyProtection";

    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    advsecurityparam_t feature;
    feature.safebrowsing_enable = false;
    feature.softflowd_enable = false;
    feature.parental_control_activate = false;
    feature.privacy_protection_activate = false;

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

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enable &"),_))
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

    int result = advsec_webconfig_handle_blob(&feature);
    EXPECT_EQ(result, BLOB_EXEC_SUCCESS);

    if (val == 1)
    {
        int ret = remove(fname);
        if(ret != 0)
        {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec->pSoftFlowd);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent->pAdvPC);
    free(g_pAdvSecAgent->pPrivProt);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, advsec_webconfig_handle_blob_fingerprint_disable)
{
    const char *AdvSecuritySBEnabled = "Advsecurity_SafeBrowsing";
    const char *AdvSecuritySFEnabled = "Advsecurity_Softflowd";
    const char *AdvSecurityPCEnabled = "Advsecurity_ParentalControl";
    const char *AdvSecurityPPEnabled = "Advsecurity_PrivacyProtection";

    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    advsecurityparam_t feature;
    feature.fingerprint_enable = false;
    feature.safebrowsing_enable = false;
    feature.softflowd_enable = false;
    feature.parental_control_activate = false;
    feature.privacy_protection_activate = false;

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

    int result = advsec_webconfig_handle_blob(&feature);
    EXPECT_EQ(result, BLOB_EXEC_SUCCESS);

    if (val == 1)
    {
        int ret = remove(fname);
        if(ret != 0)
        {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec->pSoftFlowd);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent->pAdvPC);
    free(g_pAdvSecAgent->pPrivProt);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, advsec_webconfig_handle_blob_configure_feature)
{
    const char *AdvSecuritySBEnabled = "Advsecurity_SafeBrowsing";
    const char *AdvSecuritySFEnabled = "Advsecurity_Softflowd";
    const char *AdvSecurityPCEnabled = "Advsecurity_ParentalControl";
    const char *AdvSecurityPPEnabled = "Advsecurity_PrivacyProtection";

    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    advsecurityparam_t feature;
    feature.fingerprint_enable = true;
    feature.safebrowsing_enable = false;
    feature.softflowd_enable = false;
    feature.parental_control_activate = false;
    feature.privacy_protection_activate = false;

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

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -configure_features &"),_))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(_, _))
        .Times(4)
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(4)
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(4)
        .WillRepeatedly(Return(0));

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

    int result = advsec_webconfig_handle_blob(&feature);
    EXPECT_EQ(result, BLOB_EXEC_SUCCESS);

    if (val == 1)
    {
        int ret = remove(fname);
        if(ret != 0)
        {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec->pSoftFlowd);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent->pAdvPC);
    free(g_pAdvSecAgent->pPrivProt);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecGetLoggingPeriod)
{
    const char *DeviceFingerPrintLogginPeriod = "Advsecurity_LoggingPeriod";
    const char LoggingPeriod[] = "1440";
    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq(DeviceFingerPrintLogginPeriod), _, _))
        .WillOnce(DoAll(
            SetArgPointee<2>(*LoggingPeriod),
            Return(0)
        ));

    ANSC_STATUS status = CosaAdvSecGetLoggingPeriod();

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(g_pAdvSecAgent->ulLoggingPeriod, 1);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecSetLoggingPeriod)
{
    const char *DeviceFingerPrintLogginPeriod = "Advsecurity_LoggingPeriod";
    ULONG value = ADVSEC_DEFAULT_LOG_TIMEOUT;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(DeviceFingerPrintLogginPeriod), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecSetLoggingPeriod(value);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(g_pAdvSecAgent->ulLoggingPeriod, value);
}

TEST_F(CcspAdvSecurityInternalTestFixture, GetLogLevelSuccess)
{
    const char *DeviceFingerPrintLogLevel = "Advsecurity_LogLevel";
    const char logLevel[] = "2";
    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq(DeviceFingerPrintLogLevel), _, _))
        .WillOnce(DoAll(
            SetArgPointee<2>(*logLevel),
            Return(0)
        ));

    ANSC_STATUS status = CosaAdvSecGetLogLevel();

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(g_pAdvSecAgent->ulLogLevel, 2);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecSetLogLevel)
{
    const char *DeviceFingerPrintLogLevel = "Advsecurity_LogLevel";
    ULONG value = 2;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(DeviceFingerPrintLogLevel), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -agentloglevel 2 &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecSetLogLevel(value);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(g_pAdvSecAgent->ulLogLevel, value);
}


TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecGetLookupTimeout)
{
    const char *AdvSecurityLookupTimeout = "Advsecurity_LookupTimeout";
    const char LookupTimeout[] = "350";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSafeBrows = (COSA_DATAMODEL_SB *)malloc(sizeof(COSA_DATAMODEL_SB));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSafeBrows, nullptr);

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq(AdvSecurityLookupTimeout), _, _))
        .WillOnce(DoAll(
            SetArgPointee<2>(*LookupTimeout),
            Return(0)
        ));

    ANSC_STATUS status = CosaAdvSecGetLookupTimeout();

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(g_pAdvSecAgent->pAdvSec->pSafeBrows->ulLookupTimeout, 3);

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecSetLookupTimeout)
{
    const char *AdvSecurityLookupTimeout = "Advsecurity_LookupTimeout";
    ULONG value = 3;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSec = (COSA_DATAMODEL_ADVSEC *)malloc(sizeof(COSA_DATAMODEL_ADVSEC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec, nullptr);
    g_pAdvSecAgent->pAdvSec->pSafeBrows = (COSA_DATAMODEL_SB *)malloc(sizeof(COSA_DATAMODEL_SB));
    ASSERT_NE(g_pAdvSecAgent->pAdvSec->pSafeBrows, nullptr);

    g_pAdvSecAgent->pAdvSec->pSafeBrows->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecurityLookupTimeout), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -start sb null &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecSetLookupTimeout(value);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(g_pAdvSecAgent->pAdvSec->pSafeBrows->ulLookupTimeout, value);

    free(g_pAdvSecAgent->pAdvSec->pSafeBrows);
    free(g_pAdvSecAgent->pAdvSec);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecSetCustomURL)
{
    const char *AdvSecCustomEndpointURL = "Advsecurity_CustomEndpointURL";
    char pString[] = "https://www.google.com";

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecCustomEndpointURL), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecSetCustomURL(pString);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecGetCustomURL)
{
    const char *AdvSecCustomEndpointURL = "Advsecurity_CustomEndpointURL";
    char pValue[] = "https://www.google.com";
    ULONG ulSize = 20;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq(AdvSecCustomEndpointURL), _, _))
        .WillOnce(DoAll(
            SetArgPointee<2>(*pValue),
            Return(0)
        ));

    ANSC_STATUS status = CosaAdvSecGetCustomURL(pValue, &ulSize);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_STREQ(pValue, "https://www.google.com");
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecGetLookupTimeoutExceededCount)
{
    ULONG lcount = 0;
    EXPECT_EQ(CosaAdvSecGetLookupTimeoutExceededCount(), lcount);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaRabidSetMemoryLimit)
{
    const char *RabidMemoryLimit = "Advsecurity_RabidMemoryLimit";
    ULONG value = 100;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(RabidMemoryLimit), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaRabidSetMemoryLimit(NULL, value);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaRabidSetMacCacheSize)
{
    const char *RabidMacCacheSize = "Advsecurity_RabidMacCacheSize";
    ULONG value = 100;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(RabidMacCacheSize), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaRabidSetMacCacheSize(NULL, value);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaRabidSetDNSCacheSize)
{
    const char *RabidDNSCacheSize = "Advsecurity_RabidDNSCacheSize";
    ULONG value = 100;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(RabidDNSCacheSize), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaRabidSetDNSCacheSize(NULL, value);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvPCInit)
{
    const char *AdvParentalControlRFCEnabled = "Adv_PCRFCEnable";
    const char *AdvParentalControlActivate = "Adv_PCActivate";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvPC_RFC = (COSA_DATAMODEL_ADVPC_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVPC_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC_RFC, nullptr);
    g_pAdvSecAgent->pAdvPC_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvParentalControlRFCEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
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

    g_pAdvSecAgent->pAdvPC = (COSA_DATAMODEL_ADVPARENTALCONTROL *)malloc(sizeof(COSA_DATAMODEL_ADVPARENTALCONTROL));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC, nullptr);

    g_pAdvSecAgent->pAdvPC->bEnable = TRUE;

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -startAdvPC &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status1 = CosaStartAdvParentalControl(FALSE);

    EXPECT_EQ(status1, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(TRUE, g_pAdvSecAgent->pAdvPC->bEnable);

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -startAdvPC &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status2 = CosaAdvPCInit(NULL);

    EXPECT_EQ(status2, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(TRUE, g_pAdvSecAgent->pAdvPC_RFC->bEnable);

    if (val == 1)
    {
        int ret = remove(fname);
        if(ret != 0)
        {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pAdvPC_RFC);
    free(g_pAdvSecAgent->pAdvPC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvPCDeInit)
{
    const char *AdvParentalControlRFCEnabled = "Adv_PCRFCEnable";
    const char *AdvParentalControlActivate = "Adv_PCActivate";
    const char *fname = "/tmp/advsec_initialized";
    int val = 0;
    FILE* file = NULL;

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->bEnable = TRUE;

    g_pAdvSecAgent->pAdvPC_RFC = (COSA_DATAMODEL_ADVPC_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVPC_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC_RFC, nullptr);
    g_pAdvSecAgent->pAdvPC_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvParentalControlRFCEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
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

    g_pAdvSecAgent->pAdvPC = (COSA_DATAMODEL_ADVPARENTALCONTROL *)malloc(sizeof(COSA_DATAMODEL_ADVPARENTALCONTROL));
    ASSERT_NE(g_pAdvSecAgent->pAdvPC, nullptr);

    g_pAdvSecAgent->pAdvPC->bEnable = FALSE;

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -stopAdvPC &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status1 = CosaStopAdvParentalControl(FALSE);

    EXPECT_EQ(status1, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pAdvPC->bEnable);


    ANSC_STATUS status2 = CosaAdvPCDeInit(NULL);

    EXPECT_EQ(status2, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pAdvPC_RFC->bEnable);

    if (val == 1)
    {
        int ret = remove(fname);
        if(ret != 0)
        {
            printf("Error deleting file %s", fname);
        }
    }

    free(g_pAdvSecAgent->pAdvPC_RFC);
    free(g_pAdvSecAgent->pAdvPC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvDFIcmpv6Init)
{
    const char *DeviceFingerPrintICMPv6Enabled = "Adv_DFICMPv6RFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pDFIcmpv6_RFC = (COSA_DATAMODEL_DEVICEFINGERPRINTICMPv6_RFC *)malloc(sizeof(COSA_DATAMODEL_DEVICEFINGERPRINTICMPv6_RFC));
    ASSERT_NE(g_pAdvSecAgent->pDFIcmpv6_RFC, nullptr);

    g_pAdvSecAgent->pDFIcmpv6_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(DeviceFingerPrintICMPv6Enabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableICMP6 &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvDFIcmpv6Init(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(TRUE, g_pAdvSecAgent->pDFIcmpv6_RFC->bEnable);

    free(g_pAdvSecAgent->pDFIcmpv6_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvDFIcmpv6DeInit)
{
    const char *DeviceFingerPrintICMPv6Enabled = "Adv_DFICMPv6RFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pDFIcmpv6_RFC = (COSA_DATAMODEL_DEVICEFINGERPRINTICMPv6_RFC *)malloc(sizeof(COSA_DATAMODEL_DEVICEFINGERPRINTICMPv6_RFC));
    ASSERT_NE(g_pAdvSecAgent->pDFIcmpv6_RFC, nullptr);

    g_pAdvSecAgent->pDFIcmpv6_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(DeviceFingerPrintICMPv6Enabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableICMP6 &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvDFIcmpv6DeInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pDFIcmpv6_RFC->bEnable);

    free(g_pAdvSecAgent->pDFIcmpv6_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaWSDisInit)
{
    const char *WSDiscoveryAnalysisEnabled = "Adv_WSDisAnaRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC = (COSA_DATAMODEL_WSDISCOVERYANALYSIS_RFC *)malloc(sizeof(COSA_DATAMODEL_WSDISCOVERYANALYSIS_RFC));
    ASSERT_NE(g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC, nullptr);

    g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(WSDiscoveryAnalysisEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableWSDiscovery &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaWSDisInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(TRUE, g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC->bEnable);

    free(g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaWSDisDeInit)
{
    const char *WSDiscoveryAnalysisEnabled = "Adv_WSDisAnaRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC = (COSA_DATAMODEL_WSDISCOVERYANALYSIS_RFC *)malloc(sizeof(COSA_DATAMODEL_WSDISCOVERYANALYSIS_RFC));
    ASSERT_NE(g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC, nullptr);

    g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(WSDiscoveryAnalysisEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableWSDiscovery &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaWSDisDeInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC->bEnable);

    free(g_pAdvSecAgent->pWSDiscoveryAnalysis_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecOTMInit)
{
    const char *AdvSecOTMEnabled = "Adv_AdvSecOTMRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSecOTM_RFC = (COSA_DATAMODEL_ADVSECOTM_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECOTM_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecOTM_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecOTM_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecOTMEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableOTM &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecOTMInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(TRUE, g_pAdvSecAgent->pAdvSecOTM_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecOTM_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecOTMDeInit)
{
    const char *AdvSecOTMEnabled = "Adv_AdvSecOTMRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSecOTM_RFC = (COSA_DATAMODEL_ADVSECOTM_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECOTM_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecOTM_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecOTM_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecOTMEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableOTM &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecOTMDeInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pAdvSecOTM_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecOTM_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecUserSpaceInit)
{
    const char *AdvSecUserSpaceEnabled = "Adv_AdvSecUserSpaceRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSecUserSpace_RFC = (COSA_DATAMODEL_ADVSECUSERSPACE_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECUSERSPACE_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecUserSpace_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecUserSpace_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecUserSpaceEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableUS &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecUserSpaceInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(TRUE, g_pAdvSecAgent->pAdvSecUserSpace_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecUserSpace_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecUserSpaceDeInit)
{
    const char *AdvSecUserSpaceEnabled = "Adv_AdvSecUserSpaceRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSecUserSpace_RFC = (COSA_DATAMODEL_ADVSECUSERSPACE_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECUSERSPACE_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecUserSpace_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecUserSpace_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecUserSpaceEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableUS &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecUserSpaceDeInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pAdvSecUserSpace_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecUserSpace_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecAgentInit)
{
    const char *AdvSecAgentEnabled = "Adv_AdvSecAgentRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSecAgent_RFC = (COSA_DATAMODEL_ADVSECAGENT_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECAGENT_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecAgent_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecAgent_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecAgentEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableAGT &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecAgentInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(TRUE, g_pAdvSecAgent->pAdvSecAgent_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecAgent_RFC);
    free(g_pAdvSecAgent);
}


TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecAgentDeInit)
{
    const char *AdvSecAgentEnabled = "Adv_AdvSecAgentRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSecAgent_RFC = (COSA_DATAMODEL_ADVSECAGENT_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECAGENT_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecAgent_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecAgent_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecAgentEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableAGT &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecAgentDeInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pAdvSecAgent_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecAgent_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecSafeBrowsingInit)
{
    const char *AdvSecSafeBrowsingEnabled = "Adv_AdvSecSafeBrowsingRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC = (COSA_DATAMODEL_ADVSECSAFEBROWSING_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECSAFEBROWSING_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecSafeBrowsingEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableSBRule &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecSafeBrowsingInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(TRUE, g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecSafeBrowsingDeInit)
{
    const char *AdvSecSafeBrowsingEnabled = "Adv_AdvSecSafeBrowsingRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC = (COSA_DATAMODEL_ADVSECSAFEBROWSING_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECSAFEBROWSING_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecSafeBrowsingEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableSBRule &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecSafeBrowsingDeInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecSafeBrowsing_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecCujoTelemetryWiFiFPInit)
{
    const char *AdvSecCujoTelemetryWiFiFPEnabled = "Adv_AdvSecCujoTelemetryWiFiFPRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC = (COSA_DATAMODEL_ADVSECCUJOTELEMETRYWIFIFP_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTELEMETRYWIFIFP_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecCujoTelemetryWiFiFPEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableCTW &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecCujoTelemetryWiFiFPInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(TRUE, g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecCujoTelemetryWiFiFPDeInit)
{
    const char *AdvSecCujoTelemetryWiFiFPEnabled = "Adv_AdvSecCujoTelemetryWiFiFPRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC = (COSA_DATAMODEL_ADVSECCUJOTELEMETRYWIFIFP_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTELEMETRYWIFIFP_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecCujoTelemetryWiFiFPEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableCTW &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecCujoTelemetryWiFiFPDeInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecCujoTelemetryWiFiFP_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecCujoTracerInit)
{
    const char *AdvSecCujoTracerEnabled = "Adv_AdvSecCujoTracerRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTracer_RFC = (COSA_DATAMODEL_ADVSECCUJOTRACER_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTRACER_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTracer_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecCujoTracer_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecCujoTracerEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableCT &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecCujoTracerInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(TRUE, g_pAdvSecAgent->pAdvSecCujoTracer_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecCujoTracer_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecCujoTracerDeInit)
{
    const char *AdvSecCujoTracerEnabled = "Adv_AdvSecCujoTracerRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTracer_RFC = (COSA_DATAMODEL_ADVSECCUJOTRACER_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTRACER_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTracer_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecCujoTracer_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecCujoTracerEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableCT &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecCujoTracerDeInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pAdvSecCujoTracer_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecCujoTracer_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecCujoTelemetryInit)
{
    const char *AdvSecCujoTelemetryEnabled = "Adv_AdvSecCujoTelemetryRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC = (COSA_DATAMODEL_ADVSECCUJOTELEMETRY_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTELEMETRY_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecCujoTelemetryEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableCTD &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecCujoTelemetryInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(TRUE, g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecCujoTelemetryDeInit)
{
    const char *AdvSecCujoTelemetryEnabled = "Adv_AdvSecCujoTelemetryRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC = (COSA_DATAMODEL_ADVSECCUJOTELEMETRY_RFC *)malloc(sizeof(COSA_DATAMODEL_ADVSECCUJOTELEMETRY_RFC));
    ASSERT_NE(g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC, nullptr);

    g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(AdvSecCujoTelemetryEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableCTD &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecCujoTelemetryDeInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC->bEnable);

    free(g_pAdvSecAgent->pAdvSecCujoTelemetry_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecAgentRaptrInit)
{
    const char *RaptrEnabled = "Adv_RaptrRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pRaptr_RFC = (COSA_DATAMODEL_RAPTR_RFC *)malloc(sizeof(COSA_DATAMODEL_RAPTR_RFC));
    ASSERT_NE(g_pAdvSecAgent->pRaptr_RFC, nullptr);

    g_pAdvSecAgent->pRaptr_RFC->bEnable = TRUE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(RaptrEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -enableRaptr &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecAgentRaptrInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(TRUE, g_pAdvSecAgent->pRaptr_RFC->bEnable);

    free(g_pAdvSecAgent->pRaptr_RFC);
    free(g_pAdvSecAgent);
}

TEST_F(CcspAdvSecurityInternalTestFixture, CosaAdvSecAgentRaptrDeInit)
{
    const char *RaptrEnabled = "Adv_RaptrRFCEnable";

    g_pAdvSecAgent = (COSA_DATAMODEL_AGENT *)malloc(sizeof(COSA_DATAMODEL_AGENT));
    ASSERT_NE(g_pAdvSecAgent, nullptr);
    g_pAdvSecAgent->pRaptr_RFC = (COSA_DATAMODEL_RAPTR_RFC *)malloc(sizeof(COSA_DATAMODEL_RAPTR_RFC));
    ASSERT_NE(g_pAdvSecAgent->pRaptr_RFC, nullptr);

    g_pAdvSecAgent->pRaptr_RFC->bEnable = FALSE;

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq(RaptrEnabled), _))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(*g_securewrapperMock, v_secure_system(HasSubstr("/usr/ccsp/advsec/start_adv_security.sh -disableRaptr &"), _))
        .Times(1)
        .WillOnce(Return(0));

    ANSC_STATUS status = CosaAdvSecAgentRaptrDeInit(NULL);

    EXPECT_EQ(status, ANSC_STATUS_SUCCESS);
    EXPECT_EQ(FALSE, g_pAdvSecAgent->pRaptr_RFC->bEnable);

    free(g_pAdvSecAgent->pRaptr_RFC);
    free(g_pAdvSecAgent);
}
