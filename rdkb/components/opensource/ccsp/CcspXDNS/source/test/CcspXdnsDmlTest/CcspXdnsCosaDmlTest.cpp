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

class CcspXdnsCosaDmlTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        g_syscfgMock = new SyscfgMock();
        g_anscMemoryMock = new AnscMemoryMock();
        g_anscWrapperApiMock = new AnscWrapperApiMock();
        g_safecLibMock = new SafecLibMock();
        g_base64Mock = new base64Mock();
        g_webconfigFwMock = new webconfigFwMock();
        g_syseventMock = new SyseventMock();
        g_msgpackMock = new msgpackMock();
        g_securewrapperMock = new SecureWrapperMock();
        g_usertimeMock = new UserTimeMock();
        g_baseapiMock = new BaseAPIMock();
        g_traceMock = new TraceMock();
        g_utopiaMock = new utopiaMock();
        g_rbusMock = new rbusMock();
    }

    void TearDown() override {
        delete g_syscfgMock;
        delete g_anscMemoryMock;
        delete g_anscWrapperApiMock;
        delete g_safecLibMock;
        delete g_base64Mock;
        delete g_webconfigFwMock;
        delete g_syseventMock;
        delete g_msgpackMock;
        delete g_securewrapperMock;
        delete g_usertimeMock;
        delete g_baseapiMock;
        delete g_traceMock;
        delete g_utopiaMock;
        delete g_rbusMock;

        g_syscfgMock = nullptr;
        g_anscMemoryMock = nullptr;
        g_anscWrapperApiMock = nullptr;
        g_safecLibMock = nullptr;
        g_base64Mock = nullptr;
        g_webconfigFwMock = nullptr;
        g_syseventMock = nullptr;
        g_msgpackMock = nullptr;
        g_securewrapperMock = nullptr;
        g_usertimeMock = nullptr;
        g_baseapiMock = nullptr;
        g_traceMock = nullptr;
        g_utopiaMock = nullptr;
        g_rbusMock = nullptr;
    }
};

// Unit Test for cosa_xdns_dml.c file

TEST_F(CcspXdnsCosaDmlTestFixture, isValidIPv4Address)
{
    char ipAddr[] = "192.168.14.3";
    EXPECT_EQ(1, isValidIPv4Address(ipAddr));
}

TEST_F(CcspXdnsCosaDmlTestFixture, isValidIPv6Address)
{
    char ipAddr[] = "2001:0db8:85a3:0000:0000:8a2e:0370:7334";
    EXPECT_EQ(1, isValidIPv6Address(ipAddr));
}

TEST_F(CcspXdnsCosaDmlTestFixture, isValidMacAddress)
{
    char macAddr[] = "00:11:22:33:44:55";
    EXPECT_EQ(TRUE, isValidMacAddress(macAddr));
}

TEST_F(CcspXdnsCosaDmlTestFixture, isValidMacAddress_NULL)
{
    char macAddr[] = "";
    EXPECT_EQ(TRUE, isValidMacAddress(macAddr));
}

TEST_F(CcspXdnsCosaDmlTestFixture, isValidMacAddress_Length)
{
    char macAddr[] = "00:11:22:33:44:5";
    EXPECT_EQ(FALSE, isValidMacAddress(macAddr));
}

TEST_F(CcspXdnsCosaDmlTestFixture, isValidMacAddress_Length1)
{
    char macAddr[] = "00:11:22:33:44:55/";
    EXPECT_EQ(FALSE, isValidMacAddress(macAddr));
}

TEST_F(CcspXdnsCosaDmlTestFixture, isValidMacAddress_Length2)
{
    char macAddr[] = "00:11:22:33:44:55:";
    EXPECT_EQ(FALSE, isValidMacAddress(macAddr));
}

TEST_F(CcspXdnsCosaDmlTestFixture, isValidMacAddress_Length_NULL)
{
    char macAddr[] = "00:11:22:33:44:5";
    ULONG length  = 0;
    EXPECT_EQ(FALSE, isValidMacAddress(macAddr));
}

TEST_F(CcspXdnsCosaDmlTestFixture, isValidMacAddress_Length3)
{
    char macAddr[] = "00:11:22:33:44:55:66";
    EXPECT_EQ(FALSE, isValidMacAddress(macAddr));
}

TEST_F(CcspXdnsCosaDmlTestFixture, isValidMacAddress_Length4)
{
    char macAddr[] = "00:11:22:33:44:55:66:77";
    EXPECT_EQ(FALSE, isValidMacAddress(macAddr));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNSDeviceInfo_GetParamBoolValue_TRUE)
{
    BOOL pBool = FALSE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "X_RDKCENTRAL-COM_EnableXDNS";
    int comparisonResult = 0;

    char buf[] = "1";

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_EnableXDNS"), strlen("X_RDKCENTRAL-COM_EnableXDNS"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_EQ(TRUE, XDNSDeviceInfo_GetParamBoolValue(NULL, (char *)ParamName, &pBool));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNSDeviceInfo_GetParamBoolValue_FALSE)
{
    BOOL pBool = TRUE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "X_RDKCENTRAL-COM_EnableXDNS";
    int comparisonResult = 1;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_EnableXDNS"), strlen("X_RDKCENTRAL-COM_EnableXDNS"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(FALSE, XDNSDeviceInfo_GetParamBoolValue(NULL, (char *)ParamName, &pBool));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNSDeviceInfo_GetParamBoolValue_FALSE_pBoolFalse)
{
    BOOL pBool = FALSE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "X_RDKCENTRAL-COM_EnableXDNS";
    int comparisonResult = 0;

    char buf[] = "\0";

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_EnableXDNS"), strlen("X_RDKCENTRAL-COM_EnableXDNS"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_EQ(TRUE, XDNSDeviceInfo_GetParamBoolValue(NULL, (char *)ParamName, &pBool));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNSDeviceInfo_SetParamBoolValue_bValueTrue_Buf1)
{
    BOOL bValue = TRUE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "X_RDKCENTRAL-COM_EnableXDNS";
    int comparisonResult = 0;

    char buf[] = "1";
    int var= atoi(buf);

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pXdns = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_EnableXDNS"), strlen("X_RDKCENTRAL-COM_EnableXDNS"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_EQ(TRUE, XDNSDeviceInfo_SetParamBoolValue(NULL, (char *)ParamName, bValue));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNSDeviceInfo_SetParamBoolValue_bValueTrue_Buf0)
{
    BOOL bValue = TRUE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "X_RDKCENTRAL-COM_EnableXDNS";
    int comparisonResult = 0;

    char buf[] = "0";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pXdns = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_EnableXDNS"), strlen("X_RDKCENTRAL-COM_EnableXDNS"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_CALL(*g_syseventMock, sysevent_open(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(FALSE, XDNSDeviceInfo_SetParamBoolValue(NULL, (char *)ParamName, bValue));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNSDeviceInfo_SetParamBoolValue_bValueTrue_Buf0_SyseventOpenFail)
{
    BOOL bValue = TRUE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "X_RDKCENTRAL-COM_EnableXDNS";
    int comparisonResult = 0;

    char buf[] = "0";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pXdns = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_EnableXDNS"), strlen("X_RDKCENTRAL-COM_EnableXDNS"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_CALL(*g_syseventMock, sysevent_open(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(-1));

    EXPECT_CALL(*g_syseventMock, sysevent_get(_, _, _, _, _))
        .Times(2)
        .WillOnce(Return(0))
        .WillOnce(Return(-1));

    EXPECT_EQ(SetXdnsConfig(), 0);

    EXPECT_CALL(*g_syseventMock, sysevent_close(_, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(FALSE, XDNSDeviceInfo_SetParamBoolValue(NULL, (char *)ParamName, bValue));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNSDeviceInfo_SetParamBoolValue_bValueFalse_Buf0_SyseventOpenFail)
{
    BOOL bValue = FALSE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "X_RDKCENTRAL-COM_EnableXDNS";
    int comparisonResult = 0;

    char buf[] = "0";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pXdns = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_EnableXDNS"), strlen("X_RDKCENTRAL-COM_EnableXDNS"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_EQ(TRUE, XDNSDeviceInfo_SetParamBoolValue(NULL, (char *)ParamName, bValue));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNSDeviceInfo_SetParamBoolValue_bValueFalse_Buf1)
{
    BOOL bValue = FALSE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "X_RDKCENTRAL-COM_EnableXDNS";
    int comparisonResult = 0;

    char buf[] = "1";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pXdns = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_EnableXDNS"), strlen("X_RDKCENTRAL-COM_EnableXDNS"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(_, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syseventMock, sysevent_set(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_utopiaMock, s_sysevent_connect(_))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(UnsetXdnsConfig(), 1);

    EXPECT_EQ(TRUE, XDNSDeviceInfo_SetParamBoolValue(NULL, (char *)ParamName, bValue));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNSDeviceInfo_SetParamBoolValue_bValueTrue_Buf0_SyseventOpenFail_SyseventGetFail)
{
    BOOL bValue = TRUE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "X_RDKCENTRAL-COM_EnableXDNS";
    int comparisonResult = 0;

    char buf[] = "0";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pXdns = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_EnableXDNS"), strlen("X_RDKCENTRAL-COM_EnableXDNS"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_CALL(*g_syseventMock, sysevent_get(_, _, _, _, _))
        .Times(2)
        .WillOnce(Return(0))
        .WillOnce(Return(-1));

    EXPECT_CALL(*g_syseventMock, sysevent_open(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(-1));

    EXPECT_CALL(*g_syseventMock, sysevent_close(_, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(FALSE, XDNSDeviceInfo_SetParamBoolValue(NULL, (char *)ParamName, bValue));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNSDeviceInfo_GetParamBoolValue_strcmp_s_fail)
{
    BOOL pBool = TRUE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "X_RDKCENTRAL-COM_EnableXDNS";
    int comparisonResult = 1;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_EnableXDNS"), strlen("X_RDKCENTRAL-COM_EnableXDNS"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(1)));

    EXPECT_EQ(FALSE, XDNSDeviceInfo_GetParamBoolValue(NULL, (char *)ParamName, &pBool));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNSRefac_GetParamBoolValue_pBoolFalse_buf1_TRUE)
{
    BOOL pBool = FALSE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "Enable";
    int comparisonResult = 0;

    char buf[] = "1";

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("XDNS_RefacCodeEnable"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_EQ(TRUE, XDNSRefac_GetParamBoolValue(NULL, (char *)ParamName, &pBool));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNSRefac_GetParamBoolValue_pBoolFalse_bufNull_TRUE)
{
    BOOL pBool = FALSE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "Enable";
    int comparisonResult = 0;

    char buf[] = "\0";

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("XDNS_RefacCodeEnable"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_EQ(TRUE, XDNSRefac_GetParamBoolValue(NULL, (char *)ParamName, &pBool));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNSRefac_GetParamBoolValue_FALSE)
{
    BOOL pBool = TRUE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "Enable";
    int comparisonResult = 1;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(FALSE, XDNSRefac_GetParamBoolValue(NULL, (char *)ParamName, &pBool));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNSRefac_SetParamBoolValue_bValueTrue)
{
    BOOL bValue = TRUE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "Enable";
    int comparisonResult = 0;

    char buf[] = "1";

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq("XDNS_RefacCodeEnable"), StrEq("1")))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syseventMock, sysevent_set(_, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(TRUE, XDNSRefac_SetParamBoolValue(NULL, (char *)ParamName, bValue));
}


TEST_F(CcspXdnsCosaDmlTestFixture, XDNSRefac_SetParamBoolValue_bValueFalse)
{
    BOOL bValue = FALSE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "Enable";
    int comparisonResult = 0;

    char buf[] = "1";

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq("XDNS_RefacCodeEnable"), StrEq("0")))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syseventMock, sysevent_set(_, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(TRUE, XDNSRefac_SetParamBoolValue(NULL, (char *)ParamName, bValue));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNSRefac_SetParamBoolValue_bValueTrue_X_RDKCENTRAL_COM_XDNS_NULL)
{
    BOOL bValue = TRUE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "Enable";
    int comparisonResult = 0;

    char buf[] = "\0";

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Enable"), strlen("Enable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_EQ(FALSE, XDNSRefac_SetParamBoolValue(NULL, (char *)ParamName, bValue));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_DefaultDeviceDnsIPv4)
{
    char pValue[256] = {0};
    ULONG pUlSize = 256;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultDeviceDnsIPv4";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    strcpy(pMyObject->DefaultDeviceDnsIPv4, "75.75.75.30");

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pValue), pUlSize, StrEq(pMyObject->DefaultDeviceDnsIPv4), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(0, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_DefaultDeviceDnsIPv4_strcpy_s_fail)
{
    char pValue[256] = {0};
    ULONG pUlSize = 256;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultDeviceDnsIPv4";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    strcpy(pMyObject->DefaultDeviceDnsIPv4, "75.75.75.30");

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pValue), pUlSize, StrEq(pMyObject->DefaultDeviceDnsIPv4), _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_EQ(1, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_DefaultDeviceDnsIPv4_BufSizeLess)
{
    char pValue[256] = {0};
    ULONG pUlSize = 1;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultDeviceDnsIPv4";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    strcpy(pMyObject->DefaultDeviceDnsIPv4, "75.75.75.30");

    EXPECT_EQ(1, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_DefaultDeviceDnsIPv6)
{
    char pValue[256] = {0};
    ULONG pUlSize = 256;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultDeviceDnsIPv6";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    strcpy(pMyObject->DefaultDeviceDnsIPv6, "2001:558:feed::30");

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pValue), pUlSize, StrEq(pMyObject->DefaultDeviceDnsIPv6), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(0, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_DefaultDeviceDnsIPv6_strcpy_s_fail)
{
    char pValue[256] = {0};
    ULONG pUlSize = 256;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultDeviceDnsIPv6";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    strcpy(pMyObject->DefaultDeviceDnsIPv6, "2001:558:feed::30");

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pValue), pUlSize, StrEq(pMyObject->DefaultDeviceDnsIPv6), _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_EQ(1, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_DefaultDeviceDnsIPv6_BufSizeLess)
{
    char pValue[256] = {0};
    ULONG pUlSize = 1;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultDeviceDnsIPv6";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    strcpy(pMyObject->DefaultDeviceDnsIPv6, "2001:558:feed::30");

    EXPECT_EQ(1, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_DefaultSecondaryDeviceDnsIPv4)
{
    char pValue[256] = {0};
    ULONG pUlSize = 256;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultSecondaryDeviceDnsIPv4";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv4, "75.75.75.10");

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pValue), pUlSize, StrEq(pMyObject->DefaultSecondaryDeviceDnsIPv4), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(0, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_DefaultSecondaryDeviceDnsIPv4_strcpy_s_fail)
{
    char pValue[256] = {0};
    ULONG pUlSize = 256;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultSecondaryDeviceDnsIPv4";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv4, "75.75.75.10");

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pValue), pUlSize, StrEq(pMyObject->DefaultSecondaryDeviceDnsIPv4), _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_EQ(1, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_DefaultSecondaryDeviceDnsIPv4_BufSizeLess)
{
    char pValue[256] = {0};
    ULONG pUlSize = 1;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultSecondaryDeviceDnsIPv4";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv4, "75.75.75.10");

    EXPECT_EQ(1, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_DefaultSecondaryDeviceDnsIPv6)
{
    char pValue[256] = {0};
    ULONG pUlSize = 256;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultSecondaryDeviceDnsIPv6";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv6, "2001:558:feed::10");

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pValue), pUlSize, StrEq(pMyObject->DefaultSecondaryDeviceDnsIPv6), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(0, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_DefaultSecondaryDeviceDnsIPv6_strcpy_s_fail)
{
    char pValue[256] = {0};
    ULONG pUlSize = 256;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultSecondaryDeviceDnsIPv6";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv6, "2001:558:feed::10");

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pValue), pUlSize, StrEq(pMyObject->DefaultSecondaryDeviceDnsIPv6), _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_EQ(1, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_DefaultSecondaryDeviceDnsIPv6_BufSizeLess)
{
    char pValue[256] = {0};
    ULONG pUlSize = 1;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultSecondaryDeviceDnsIPv6";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv6, "2001:558:feed::10");

    EXPECT_EQ(1, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_DefaultDeviceTag)
{
    char pValue[256] = {0};
    ULONG pUlSize = 256;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultDeviceTag";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceTag"), strlen("DefaultDeviceTag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    strcpy(pMyObject->DefaultDeviceTag, "xdnstag");

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pValue), pUlSize, StrEq(pMyObject->DefaultDeviceTag), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(0, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_DefaultDeviceTag_strcpy_s_fail)
{
    char pValue[256] = {0};
    ULONG pUlSize = 256;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultDeviceTag";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceTag"), strlen("DefaultDeviceTag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    strcpy(pMyObject->DefaultDeviceTag, "xdnstag");

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pValue), pUlSize, StrEq(pMyObject->DefaultDeviceTag), _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_EQ(1, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_DefaultDeviceTag_BufSizeLess)
{
    char pValue[256] = {0};
    ULONG pUlSize = 1;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultDeviceTag";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceTag"), strlen("DefaultDeviceTag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    strcpy(pMyObject->DefaultDeviceTag, "xdnstag");

    EXPECT_EQ(1, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamStringValue_Data)
{
    char pValue[256] = {0};
    ULONG pUlSize = 256;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "Data";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceTag"), strlen("DefaultDeviceTag"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Data"), strlen("Data"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(0, XDNS_GetParamStringValue(NULL, (char *)ParamName, pValue, &pUlSize));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamBoolValue_DNSSecEnable)
{
    BOOL pBool = TRUE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DNSSecEnable";
    int comparisonResult = 0;

    char buf[] = "1";

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DNSSecEnable"), strlen("DNSSecEnable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("XDNS_DNSSecEnable"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_EQ(TRUE, XDNS_GetParamBoolValue(NULL, (char *)ParamName, &pBool));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamBoolValue_DNSSecEnable_False)
{
    BOOL pBool = TRUE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DNSSecEnable";
    int comparisonResult = 0;

    char buf[] = "0";

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DNSSecEnable"), strlen("DNSSecEnable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("XDNS_DNSSecEnable"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_EQ(TRUE, XDNS_GetParamBoolValue(NULL, (char *)ParamName, &pBool));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamBoolValue_DNSSecEnable_BufNull)
{
    BOOL pBool = TRUE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DNSSecEnable";
    int comparisonResult = 0;

    char buf[] = "\0";

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DNSSecEnable"), strlen("DNSSecEnable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("XDNS_DNSSecEnable"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_EQ(TRUE, XDNS_GetParamBoolValue(NULL, (char *)ParamName, &pBool));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_GetParamBoolValue_DNSSecEnable_SysCfgFail)
{
    BOOL pBool = TRUE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DNSSecEnable";
    int comparisonResult = 0;

    char buf[] = "1";

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DNSSecEnable"), strlen("DNSSecEnable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("XDNS_DNSSecEnable"), _, _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_EQ(TRUE, XDNS_GetParamBoolValue(NULL, (char *)ParamName, &pBool));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamBoolValue_DNSSecEnable_True)
{
    BOOL bValue = TRUE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DNSSecEnable";
    int comparisonResult = 0;

    char bval[] = "1";

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DNSSecEnable"), strlen("DNSSecEnable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq("XDNS_DNSSecEnable"), StrEq(bval)))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syseventMock, sysevent_set(_, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(TRUE, XDNS_SetParamBoolValue(NULL, (char *)ParamName, bValue));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamBoolValue_DNSSecEnable_False)
{
    BOOL bValue = FALSE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DNSSecEnable";
    int comparisonResult = 0;

    char bval[] = "0";

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DNSSecEnable"), strlen("DNSSecEnable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq("XDNS_DNSSecEnable"), StrEq(bval)))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syseventMock, sysevent_set(_, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(TRUE, XDNS_SetParamBoolValue(NULL, (char *)ParamName, bValue));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamBoolValue_DNSSecEnable_SysCfgFail)
{
    BOOL bValue = TRUE;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DNSSecEnable";
    int comparisonResult = 0;

    char bval[] = "1";

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DNSSecEnable"), strlen("DNSSecEnable"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(StrEq("XDNS_DNSSecEnable"), StrEq(bval)))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_EQ(TRUE, XDNS_SetParamBoolValue(NULL, (char *)ParamName, bValue));
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_DefaultDeviceDnsIPv4)
{
    char pString[] = "75.75.75.30";
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultDeviceDnsIPv4";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    pMyObject->DefaultDeviceDnsIPv4Changed = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pMyObject->DefaultDeviceDnsIPv4), sizeof(pMyObject->DefaultDeviceDnsIPv4), StrEq(pString), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(TRUE, XDNS_SetParamStringValue(NULL, (char *)ParamName, pString));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_DefaultDeviceDnsIPv4_strcpy_s_fail)
{
    char pString[] = "75.75.75.30";
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultDeviceDnsIPv4";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    pMyObject->DefaultDeviceDnsIPv4Changed = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pMyObject->DefaultDeviceDnsIPv4), sizeof(pMyObject->DefaultDeviceDnsIPv4), StrEq(pString), _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_EQ(FALSE, XDNS_SetParamStringValue(NULL, (char *)ParamName, pString));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_DefaultDeviceDnsIPv6)
{
    char pString[] = "2001:558:feed::1";
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultDeviceDnsIPv6";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    pMyObject->DefaultDeviceDnsIPv6Changed = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pMyObject->DefaultDeviceDnsIPv6), sizeof(pMyObject->DefaultDeviceDnsIPv6), StrEq(pString), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(TRUE, XDNS_SetParamStringValue(NULL, (char *)ParamName, pString));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_DefaultDeviceDnsIPv6_strcpy_s_fail)
{
    char pString[] = "2001:558:feed::1";
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultDeviceDnsIPv6";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    pMyObject->DefaultDeviceDnsIPv6Changed = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pMyObject->DefaultDeviceDnsIPv6), sizeof(pMyObject->DefaultDeviceDnsIPv6), StrEq(pString), _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_EQ(FALSE, XDNS_SetParamStringValue(NULL, (char *)ParamName, pString));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_DefaultSecondaryDeviceDnsIPv4)
{
    char pString[] = "75.75.75.10";
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultSecondaryDeviceDnsIPv4";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    pMyObject->DefaultSecondaryDeviceDnsIPv4Changed = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pMyObject->DefaultSecondaryDeviceDnsIPv4), sizeof(pMyObject->DefaultSecondaryDeviceDnsIPv4), StrEq(pString), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(TRUE, XDNS_SetParamStringValue(NULL, (char *)ParamName, pString));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_DefaultSecondaryDeviceDnsIPv4_strcpy_s_fail)
{
   char pString[] = "75.75.75.10";
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultSecondaryDeviceDnsIPv4";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    pMyObject->DefaultSecondaryDeviceDnsIPv4Changed = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pMyObject->DefaultSecondaryDeviceDnsIPv4), sizeof(pMyObject->DefaultSecondaryDeviceDnsIPv4), StrEq(pString), _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_EQ(FALSE, XDNS_SetParamStringValue(NULL, (char *)ParamName, pString));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_DefaultSecondaryDeviceDnsIPv6)
{
    char pString[] = "2001:558:feed::2";
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultSecondaryDeviceDnsIPv6";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    pMyObject->DefaultSecondaryDeviceDnsIPv6Changed = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pMyObject->DefaultSecondaryDeviceDnsIPv6), sizeof(pMyObject->DefaultSecondaryDeviceDnsIPv6), StrEq(pString), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(TRUE, XDNS_SetParamStringValue(NULL, (char *)ParamName, pString));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_DefaultSecondaryDeviceDnsIPv6_strcpy_s_fail)
{
    char pString[] = "2001:558:feed::2";
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultSecondaryDeviceDnsIPv6";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    pMyObject->DefaultSecondaryDeviceDnsIPv6Changed = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pMyObject->DefaultSecondaryDeviceDnsIPv6), sizeof(pMyObject->DefaultSecondaryDeviceDnsIPv6), StrEq(pString), _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_EQ(FALSE, XDNS_SetParamStringValue(NULL, (char *)ParamName, pString));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_DefaultDeviceTag)
{
    char pString[] = "Primary";
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultDeviceTag";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceTag"), strlen("DefaultDeviceTag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    pMyObject->DefaultDeviceTagChanged = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pMyObject->DefaultDeviceTag), sizeof(pMyObject->DefaultDeviceTag), StrEq(pString), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(TRUE, XDNS_SetParamStringValue(NULL, (char *)ParamName, pString));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_DefaultDeviceTag_strcpy_s_fail)
{
    char pString[] = "Primary";
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "DefaultDeviceTag";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceTag"), strlen("DefaultDeviceTag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    pMyObject->DefaultDeviceTagChanged = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(pMyObject->DefaultDeviceTag), sizeof(pMyObject->DefaultDeviceTag), StrEq(pString), _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_EQ(FALSE, XDNS_SetParamStringValue(NULL, (char *)ParamName, pString));

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_Data_MSGPACK_UNPACK_EXTRA_BYTES)
{
    ANSC_HANDLE hInsContext = NULL;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "Data";
    int comparisonResult = 0;

    char pString[] = "c3ViamVjdD1YRG5zJnZlcnNpb249MSZ0cmFuc2FjdGlvbl9pZD0xJmRlZmF1bHRfaW52YWxpZD0xJmRlZmF1bHRfaW52YWxpZD0yJmRlZmF1bHRfdGFyZ2V0PTEwMCZkbnNfbWFjPTE5Mi4xNjguMTI1LjEwJmRuc19tYWM9MjAwMS41NTguZmVlZC4uMSZkbnNfbWFjPTIwMDEuNTU4LmZlZWQuLjI=";
    char * decodeMsg = NULL;
    int decodeMsgSize = 0;
    int size = 0;
    int err = 0;
    int i = 0;

    msgpack_zone mempool;
    msgpack_object deserialized;
    msgpack_unpack_return unpack_ret = MSGPACK_UNPACK_EXTRA_BYTES;

    xdnsdoc_t *xd = NULL;
    execData *execDataxdns = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceTag"), strlen("DefaultDeviceTag"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Data"), strlen("Data"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_base64Mock, b64_get_decoded_buffer_size(_))
        .Times(1);

    decodeMsg = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(decodeMsg, nullptr);

    EXPECT_CALL(*g_base64Mock, b64_decode(_, _, _))
        .Times(1)
        .WillOnce(Return(16));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_init(_, _))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(MSGPACK_UNPACK_EXTRA_BYTES));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_destroy(_))
        .Times(1);

    EXPECT_EQ(FALSE, XDNS_SetParamStringValue(hInsContext, (char *)ParamName, pString));

    free(decodeMsg);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_Data_MSGPACK_UNPACK_SUCCESS)
{
    ANSC_HANDLE hInsContext = NULL;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "Data";
    int comparisonResult = 0;

    char pString[] = "c3ViamVjdD1YRG5zJnZlcnNpb249MSZ0cmFuc2FjdGlvbl9pZD0xJmRlZmF1bHRfaW52YWxpZD0xJmRlZmF1bHRfaW52YWxpZD0yJmRlZmF1bHRfdGFyZ2V0PTEwMCZkbnNfbWFjPTE5Mi4xNjguMTI1LjEwJmRuc19tYWM9MjAwMS41NTguZmVlZC4uMSZkbnNfbWFjPTIwMDEuNTU4LmZlZWQuLjI=";
    char * decodeMsg = NULL;
    int decodeMsgSize = 0;
    int size = 0;
    int err = 0;
    int i = 0;

    msgpack_zone mempool;
    msgpack_object deserialized;
    msgpack_unpack_return unpack_ret = MSGPACK_UNPACK_SUCCESS;

    xdnsdoc_t *xd = NULL;
    execData *execDataxdns = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceTag"), strlen("DefaultDeviceTag"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Data"), strlen("Data"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_base64Mock, b64_get_decoded_buffer_size(_))
        .Times(1);

    decodeMsg = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(decodeMsg, nullptr);

    EXPECT_CALL(*g_base64Mock, b64_decode(_, _, _))
        .Times(1)
        .WillOnce(Return(16));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_init(_, _))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(MSGPACK_UNPACK_SUCCESS));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack_next(_, _, _, _))
        .Times(1);

    EXPECT_CALL(*g_msgpackMock, msgpack_object_print(_, _))
        .Times(1);

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_destroy(_))
        .Times(1);

    EXPECT_EQ(TRUE, XDNS_SetParamStringValue(hInsContext, (char *)ParamName, pString));

    free(decodeMsg);
    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_Data_MSGPACK_UNPACK_CONTINUE)
{
    ANSC_HANDLE hInsContext = NULL;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "Data";
    int comparisonResult = 0;

    char pString[] = "c3ViamVjdD1YRG5zJnZlcnNpb249MSZ0cmFuc2FjdGlvbl9pZD0xJmRlZmF1bHRfaW52YWxpZD0xJmRlZmF1bHRfaW52YWxpZD0yJmRlZmF1bHRfdGFyZ2V0PTEwMCZkbnNfbWFjPTE5Mi4xNjguMTI1LjEwJmRuc19tYWM9MjAwMS41NTguZmVlZC4uMSZkbnNfbWFjPTIwMDEuNTU4LmZlZWQuLjI=";
    char * decodeMsg = NULL;
    int decodeMsgSize = 0;
    int size = 0;
    int err = 0;
    int i = 0;

    msgpack_zone mempool;
    msgpack_object deserialized;
    msgpack_unpack_return unpack_ret = MSGPACK_UNPACK_CONTINUE;

    xdnsdoc_t *xd = NULL;
    execData *execDataxdns = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceTag"), strlen("DefaultDeviceTag"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Data"), strlen("Data"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_base64Mock, b64_get_decoded_buffer_size(_))
        .Times(1);

    decodeMsg = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(decodeMsg, nullptr);

    EXPECT_CALL(*g_base64Mock, b64_decode(_, _, _))
        .Times(1)
        .WillOnce(Return(16));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_init(_, _))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(MSGPACK_UNPACK_CONTINUE));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_destroy(_))
        .Times(1);

    EXPECT_EQ(FALSE, XDNS_SetParamStringValue(hInsContext, (char *)ParamName, pString));

    free(decodeMsg);
    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_Data_MSGPACK_UNPACK_PARSE_ERROR)
{
    ANSC_HANDLE hInsContext = NULL;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "Data";
    int comparisonResult = 0;

    char pString[] = "c3ViamVjdD1YRG5zJnZlcnNpb249MSZ0cmFuc2FjdGlvbl9pZD0xJmRlZmF1bHRfaW52YWxpZD0xJmRlZmF1bHRfaW52YWxpZD0yJmRlZmF1bHRfdGFyZ2V0PTEwMCZkbnNfbWFjPTE5Mi4xNjguMTI1LjEwJmRuc19tYWM9MjAwMS41NTguZmVlZC4uMSZkbnNfbWFjPTIwMDEuNTU4LmZlZWQuLjI=";
    char * decodeMsg = NULL;
    int decodeMsgSize = 0;
    int size = 0;
    int err = 0;
    int i = 0;

    msgpack_zone mempool;
    msgpack_object deserialized;
    msgpack_unpack_return unpack_ret = MSGPACK_UNPACK_PARSE_ERROR;

    xdnsdoc_t *xd = NULL;
    execData *execDataxdns = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceTag"), strlen("DefaultDeviceTag"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Data"), strlen("Data"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_base64Mock, b64_get_decoded_buffer_size(_))
        .Times(1);

    decodeMsg = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(decodeMsg, nullptr);

    EXPECT_CALL(*g_base64Mock, b64_decode(_, _, _))
        .Times(1)
        .WillOnce(Return(16));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_init(_, _))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(MSGPACK_UNPACK_PARSE_ERROR));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_destroy(_))
        .Times(1);

    EXPECT_EQ(FALSE, XDNS_SetParamStringValue(hInsContext, (char *)ParamName, pString));

    free(decodeMsg);
    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_Data_MSGPACK_UNPACK_NOMEM_ERROR)
{
    ANSC_HANDLE hInsContext = NULL;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "Data";
    int comparisonResult = 0;

    char pString[] = "c3ViamVjdD1YRG5zJnZlcnNpb249MSZ0cmFuc2FjdGlvbl9pZD0xJmRlZmF1bHRfaW52YWxpZD0xJmRlZmF1bHRfaW52YWxpZD0yJmRlZmF1bHRfdGFyZ2V0PTEwMCZkbnNfbWFjPTE5Mi4xNjguMTI1LjEwJmRuc19tYWM9MjAwMS41NTguZmVlZC4uMSZkbnNfbWFjPTIwMDEuNTU4LmZlZWQuLjI=";
    char * decodeMsg = NULL;
    int decodeMsgSize = 0;
    int size = 0;
    int err = 0;
    int i = 0;

    msgpack_zone mempool;
    msgpack_object deserialized;
    msgpack_unpack_return unpack_ret = MSGPACK_UNPACK_NOMEM_ERROR;

    xdnsdoc_t *xd = NULL;
    execData *execDataxdns = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceTag"), strlen("DefaultDeviceTag"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Data"), strlen("Data"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_base64Mock, b64_get_decoded_buffer_size(_))
        .Times(1);

    decodeMsg = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(decodeMsg, nullptr);

    EXPECT_CALL(*g_base64Mock, b64_decode(_, _, _))
        .Times(1)
        .WillOnce(Return(16));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_init(_, _))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(MSGPACK_UNPACK_NOMEM_ERROR));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_destroy(_))
        .Times(1);

    EXPECT_EQ(FALSE, XDNS_SetParamStringValue(hInsContext, (char *)ParamName, pString));

    free(decodeMsg);
    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_SetParamStringValue_Data_strcmp_s_fail)
{
    ANSC_HANDLE hInsContext = NULL;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    const char* ParamName = "Data";
    int comparisonResult = 0;

    char pString[] = "c3ViamVjdD1YRG5zJnZlcnNpb249MSZ0cmFuc2FjdGlvbl9pZD0xJmRlZmF1bHRfaW52YWxpZD0xJmRlZmF1bHRfaW52YWxpZD0yJmRlZmF1bHRfdGFyZ2V0PTEwMCZkbnNfbWFjPTE5Mi4xNjguMTI1LjEwJmRuc19tYWM9MjAwMS41NTguZmVlZC4uMSZkbnNfbWFjPTIwMDEuNTU4LmZlZWQuLjI=";
    char * decodeMsg = NULL;
    int decodeMsgSize = 0;
    int size = 0;
    int err = 0;
    int i = 0;

    msgpack_zone mempool;
    msgpack_object deserialized;
    msgpack_unpack_return unpack_ret = MSGPACK_UNPACK_NOMEM_ERROR;

    xdnsdoc_t *xd = NULL;
    execData *execDataxdns = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv4"), strlen("DefaultDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(1)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceDnsIPv6"), strlen("DefaultDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(1)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv4"), strlen("DefaultSecondaryDeviceDnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(1)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultSecondaryDeviceDnsIPv6"), strlen("DefaultSecondaryDeviceDnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(1)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DefaultDeviceTag"), strlen("DefaultDeviceTag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(1)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Data"), strlen("Data"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_base64Mock, b64_get_decoded_buffer_size(_))
        .Times(1);

    decodeMsg = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(decodeMsg, nullptr);

    EXPECT_CALL(*g_base64Mock, b64_decode(_, _, _))
        .Times(1)
        .WillOnce(Return(16));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_init(_, _))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack(_, _, _, _, _))
        .Times(1);
    EXPECT_CALL(*g_msgpackMock, msgpack_zone_destroy(_))
        .Times(1);

    EXPECT_EQ(FALSE, XDNS_SetParamStringValue(hInsContext, (char *)ParamName, pString));

    free(decodeMsg);
    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Commit)
{
    ANSC_HANDLE hInsContext = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    pMyObject->DefaultDeviceDnsIPv4Changed = TRUE;
    strcpy(pMyObject->DefaultDeviceDnsIPv4, "");

    pMyObject->DefaultDeviceDnsIPv6Changed = TRUE;
    strcpy(pMyObject->DefaultDeviceDnsIPv6, "");

    pMyObject->DefaultSecondaryDeviceDnsIPv4Changed = TRUE;
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv4, "");

    pMyObject->DefaultSecondaryDeviceDnsIPv6Changed = TRUE;
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv6, "");

    pMyObject->DefaultDeviceTagChanged = TRUE;
    strcpy(pMyObject->DefaultDeviceTag, "");

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .WillRepeatedly(Return(EOK));

    ULONG result = XDNS_Commit(hInsContext);

    EXPECT_TRUE(result);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Commit_Failure)
{
    ANSC_HANDLE hInsContext = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    pMyObject->DefaultDeviceDnsIPv4Changed = TRUE;
    strcpy(pMyObject->DefaultDeviceDnsIPv4, "192.168.1.2");

    pMyObject->DefaultDeviceDnsIPv6Changed = TRUE;
    strcpy(pMyObject->DefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");

    pMyObject->DefaultSecondaryDeviceDnsIPv4Changed = TRUE;
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv4, "192.168.1.2");

    pMyObject->DefaultSecondaryDeviceDnsIPv6Changed = TRUE;
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");

    pMyObject->DefaultDeviceTagChanged = TRUE;
    strcpy(pMyObject->DefaultDeviceTag, "TestTag");

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(6)
        .WillRepeatedly(Return(EOK));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(_, _))
        .Times(4)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    ULONG result = XDNS_Commit(hInsContext);

    EXPECT_TRUE(result);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Commit_sprintf_s_fails)
{
    ANSC_HANDLE hInsContext = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    pMyObject->DefaultDeviceDnsIPv4Changed = TRUE;
    strcpy(pMyObject->DefaultDeviceDnsIPv4, "192.168.1.2");

    pMyObject->DefaultDeviceDnsIPv6Changed = TRUE;
    strcpy(pMyObject->DefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");

    pMyObject->DefaultSecondaryDeviceDnsIPv4Changed = TRUE;
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv4, "192.168.1.2");

    pMyObject->DefaultSecondaryDeviceDnsIPv6Changed = TRUE;
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");

    pMyObject->DefaultDeviceTagChanged = TRUE;
    strcpy(pMyObject->DefaultDeviceTag, "TestTag");

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .Times(6)
        .WillRepeatedly(Return(-1));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(_, _))
        .Times(8)
        .WillRepeatedly(Return(-1));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    ULONG result = XDNS_Commit(hInsContext);

    EXPECT_TRUE(result);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Rollback)
{
    ANSC_HANDLE hInsContext = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    pMyObject->DefaultDeviceDnsIPv4Changed = TRUE;
    strcpy(pMyObject->DefaultDeviceDnsIPv4, "172.16.0.5");

    pMyObject->DefaultDeviceDnsIPv6Changed = TRUE;
    strcpy(pMyObject->DefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");

    pMyObject->DefaultSecondaryDeviceDnsIPv4Changed = TRUE;
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv4, "172.16.0.5");

    pMyObject->DefaultSecondaryDeviceDnsIPv6Changed = TRUE;
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");

    pMyObject->DefaultDeviceTagChanged = TRUE;
    strcpy(pMyObject->DefaultDeviceTag, "TestTag");

    EXPECT_CALL(*g_safecLibMock, _strtok_s_chk(_, _, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(XDNS_Rollback(hInsContext), FALSE);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Rollback2)
{
    ANSC_HANDLE hInsContext = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    pMyObject->DefaultDeviceDnsIPv4Changed = TRUE;
    strcpy(pMyObject->DefaultDeviceDnsIPv4, "172.16.0.5");

    pMyObject->DefaultDeviceDnsIPv6Changed = TRUE;
    strcpy(pMyObject->DefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");

    pMyObject->DefaultSecondaryDeviceDnsIPv4Changed = TRUE;
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv4, "172.16.0.5");

    pMyObject->DefaultSecondaryDeviceDnsIPv6Changed = TRUE;
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");

    pMyObject->DefaultDeviceTagChanged = TRUE;
    strcpy(pMyObject->DefaultDeviceTag, "TestTag");

    char* primarytoken = NULL;
    char* secondarytoken = NULL;
    const char* s = " ";
    char *ptr1 = NULL, *ptr2 = NULL;
    size_t len1 = 0, len2 =0;
    char buf[MAX_XDNS_SERV][MAX_BUF_SIZE] = {{0,0}};
    len1 = strlen(buf[0]);
    len2 = strlen(buf[1]);

    ptr1 = (char *)malloc(len1 + 1);
    ptr2 = (char *)malloc(len2 + 1);


    strcpy(ptr1, buf[0]);
    strcpy(ptr2, buf[1]);

    EXPECT_CALL(*g_safecLibMock, _strtok_s_chk(_, _, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(XDNS_Rollback(hInsContext), FALSE);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Rollback_empty)
{
    ANSC_HANDLE hInsContext = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    pMyObject->DefaultDeviceDnsIPv4Changed = TRUE;
    strcpy(pMyObject->DefaultDeviceDnsIPv4, "");

    pMyObject->DefaultDeviceDnsIPv6Changed = TRUE;
    strcpy(pMyObject->DefaultDeviceDnsIPv6, "");

    pMyObject->DefaultSecondaryDeviceDnsIPv4Changed = TRUE;
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv4, "");

    pMyObject->DefaultSecondaryDeviceDnsIPv6Changed = TRUE;
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv6, "");

    pMyObject->DefaultDeviceTagChanged = TRUE;
    strcpy(pMyObject->DefaultDeviceTag, "");

    EXPECT_CALL(*g_safecLibMock, _strtok_s_chk(_, _, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(XDNS_Rollback(hInsContext), FALSE);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_GetEntryCount)
{
    ANSC_HANDLE hInsContext = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    EXPECT_GE(DNSMappingTable_GetEntryCount(hInsContext), 0);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_GetEntry)
{
    ANSC_HANDLE hInsContext = NULL;
    ULONG nIndex = 1;
    ULONG pInsNumber = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pCxtLink1 = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pCxtLink1, nullptr);
    pCxtLink1->InstanceNumber = 1;
    AnscSListPushEntry(&pMyObject->XDNSDeviceList, &pCxtLink1->Linkage);

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pCxtLink2 = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pCxtLink2, nullptr);
    pCxtLink2->InstanceNumber = 2;
    AnscSListPushEntry(&pMyObject->XDNSDeviceList, &pCxtLink2->Linkage);

    EXPECT_CALL(*g_anscWrapperApiMock, AnscSListSearchEntryByIndex(testing::_, 1))
        .Times(1)
        .WillOnce(testing::Return(reinterpret_cast<_SINGLE_LINK_ENTRY*>(&pCxtLink2->Linkage)));

    EXPECT_EQ(DNSMappingTable_GetEntry(hInsContext, nIndex, &pInsNumber),(ANSC_HANDLE)&pCxtLink2->Linkage);
    EXPECT_EQ(pInsNumber, 2);

    free(pCxtLink1);
    pCxtLink1 = NULL;
    free(pCxtLink2);
    pCxtLink2 = NULL;
    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_IsUpdated)
{
    ANSC_HANDLE hInsContext = NULL;

    EXPECT_EQ(DNSMappingTable_IsUpdated(hInsContext), TRUE);
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_Synchronize)
{
    ANSC_HANDLE hInsContext = NULL;

    EXPECT_EQ(DNSMappingTable_Synchronize(hInsContext), ANSC_STATUS_SUCCESS);
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_AddEntry)
{
    ULONG pInsNumber = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pXdns = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    pXdns->pMappingContainer = (PCOSA_DML_MAPPING_CONTAINER)malloc(sizeof(COSA_DML_MAPPING_CONTAINER));
    ASSERT_NE(pXdns->pMappingContainer, nullptr);

    ANSC_HANDLE pXdnsCxtLink;

    pXdnsCxtLink = DNSMappingTable_AddEntry(NULL, &pInsNumber);

    EXPECT_NE(pXdnsCxtLink, nullptr);

    free(pXdns->pMappingContainer);
    pXdns->pMappingContainer = NULL;
    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_AddEntry2)
{
    ULONG pInsNumber = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pXdns = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = NULL;

    pXdns->pMappingContainer = (PCOSA_DML_MAPPING_CONTAINER)malloc(sizeof(COSA_DML_MAPPING_CONTAINER));
    ASSERT_NE(pXdns->pMappingContainer, nullptr);

    ANSC_HANDLE pXdnsCxtLink;

    pXdnsCxtLink = DNSMappingTable_AddEntry(NULL, &pInsNumber);

    EXPECT_NE(pXdnsCxtLink, nullptr);

    free(pXdns->pMappingContainer);
    pXdns->pMappingContainer = NULL;
    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_DelEntry)
{
    ANSC_HANDLE hInsContext = NULL;
    ANSC_HANDLE hInstance = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pXdns = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    AnscSListInitializeHeader(&pXdns->XDNSDeviceList);

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (ANSC_HANDLE)pDnsTableEntry;

    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    EXPECT_CALL(*g_anscWrapperApiMock, AnscSListPopEntryByLink(_, _))
        .Times(1);

    ULONG result = DNSMappingTable_DelEntry(hInsContext, (ANSC_HANDLE)pXdnsCxtLink);

    EXPECT_NE(result, returnStatus);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_DelEntry_Failure)
{
    ANSC_HANDLE hInsContext = NULL;
    ANSC_HANDLE hInstance = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pXdns = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    AnscSListInitializeHeader(&pXdns->XDNSDeviceList);

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (ANSC_HANDLE)pDnsTableEntry;

    ANSC_STATUS returnStatus = ANSC_STATUS_FAILURE;

    EXPECT_CALL(*g_anscWrapperApiMock, AnscSListPopEntryByLink(_, _))
        .Times(1);

    ULONG result = DNSMappingTable_DelEntry(hInsContext, (ANSC_HANDLE)pXdnsCxtLink);

    EXPECT_EQ(result, returnStatus);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_DelEntry_Failure2)
{
    ANSC_HANDLE hInsContext = NULL;
    ANSC_HANDLE hInstance = NULL;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pXdns = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

    AnscSListInitializeHeader(&pXdns->XDNSDeviceList);

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (ANSC_HANDLE)pDnsTableEntry;

    ANSC_STATUS returnStatus = ANSC_STATUS_FAILURE;

    EXPECT_CALL(*g_anscWrapperApiMock, AnscSListPopEntryByLink(_, _))
        .Times(1);

    ULONG result = DNSMappingTable_DelEntry(hInsContext, (ANSC_HANDLE)pXdnsCxtLink);

    EXPECT_EQ(result, returnStatus);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_GetParamStringValue_MacAddress)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "MacAddress";
    int comparisonResult = 0;
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    strcpy(pDnsTableEntry->MacAddress, "00:00:00:00:00:00");

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)pXdnsCxtLink;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(DNSMappingTable_GetParamStringValue((ANSC_HANDLE)pXdnsCxtLink, (char *)ParamName, pValue, &pUlSize), 0);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_GetParamStringValue_DnsIPv4)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "DnsIPv4";
    int comparisonResult = 0;
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    strcpy(pDnsTableEntry->DnsIPv4, "75.75.75.75");

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)pXdnsCxtLink;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(DNSMappingTable_GetParamStringValue((ANSC_HANDLE)pXdnsCxtLink, (char *)ParamName, pValue, &pUlSize), 0);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}


TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_GetParamStringValue_DnsIPv6)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "DnsIPv6";
    int comparisonResult = 0;
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    strcpy(pDnsTableEntry->DnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)pXdnsCxtLink;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv6"), strlen("DnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(DNSMappingTable_GetParamStringValue((ANSC_HANDLE)pXdnsCxtLink, (char *)ParamName, pValue, &pUlSize), 0);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_GetParamStringValue_Tag)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "Tag";
    int comparisonResult = 0;
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    strcpy(pDnsTableEntry->Tag, "TestTag");

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)pXdnsCxtLink;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv6"), strlen("DnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Tag"), strlen("Tag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(DNSMappingTable_GetParamStringValue((ANSC_HANDLE)pXdnsCxtLink, (char *)ParamName, pValue, &pUlSize), 0);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_GetParamStringValue_MacAddress_lessPUlSize)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "MacAddress";
    int comparisonResult = 0;
    char pValue[256] = {0};
    ULONG pUlSize = 2;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    strcpy(pDnsTableEntry->MacAddress, "00:00:00:00:00:00");

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)pXdnsCxtLink;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(DNSMappingTable_GetParamStringValue((ANSC_HANDLE)pXdnsCxtLink, (char *)ParamName, pValue, &pUlSize), 1);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_GetParamStringValue_DnsIPv4_lessPUlSize)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "DnsIPv4";
    int comparisonResult = 0;
    char pValue[256] = {0};
    ULONG pUlSize = 2;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    strcpy(pDnsTableEntry->DnsIPv4, "75.75.75.75");

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)pXdnsCxtLink;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(DNSMappingTable_GetParamStringValue((ANSC_HANDLE)pXdnsCxtLink, (char *)ParamName, pValue, &pUlSize), 1);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}


TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_GetParamStringValue_DnsIPv6_lessPUlSize)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "DnsIPv6";
    int comparisonResult = 0;
    char pValue[256] = {0};
    ULONG pUlSize = 2;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    strcpy(pDnsTableEntry->DnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)pXdnsCxtLink;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv6"), strlen("DnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(DNSMappingTable_GetParamStringValue((ANSC_HANDLE)pXdnsCxtLink, (char *)ParamName, pValue, &pUlSize), 1);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_GetParamStringValue_Tag_lessPUlSize)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "Tag";
    int comparisonResult = 0;
    char pValue[256] = {0};
    ULONG pUlSize = 2;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    strcpy(pDnsTableEntry->Tag, "TestTag");

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)pXdnsCxtLink;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv6"), strlen("DnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Tag"), strlen("Tag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(DNSMappingTable_GetParamStringValue((ANSC_HANDLE)pXdnsCxtLink, (char *)ParamName, pValue, &pUlSize), 1);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_GetParamStringValue_MacAddress_strcpyFailure)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "MacAddress";
    int comparisonResult = 0;
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    strcpy(pDnsTableEntry->MacAddress, "00:00:00:00:00:00");

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)pXdnsCxtLink;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .WillOnce(Return(ESNULLP));

    EXPECT_EQ(DNSMappingTable_GetParamStringValue((ANSC_HANDLE)pXdnsCxtLink, (char *)ParamName, pValue, &pUlSize), 1);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_GetParamStringValue_DnsIPv4_strcpyFailure)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "DnsIPv4";
    int comparisonResult = 0;
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    strcpy(pDnsTableEntry->DnsIPv4, "75.75.75.75");

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)pXdnsCxtLink;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(ESNULLP));

    EXPECT_EQ(DNSMappingTable_GetParamStringValue((ANSC_HANDLE)pXdnsCxtLink, (char *)ParamName, pValue, &pUlSize), 1);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}


TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_GetParamStringValue_DnsIPv6_strcpyFailure)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "DnsIPv6";
    int comparisonResult = 0;
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    strcpy(pDnsTableEntry->DnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)pXdnsCxtLink;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv6"), strlen("DnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(ESNULLP));

    EXPECT_EQ(DNSMappingTable_GetParamStringValue((ANSC_HANDLE)pXdnsCxtLink, (char *)ParamName, pValue, &pUlSize), 1);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_GetParamStringValue_Tag_strcpyFailure)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "Tag";
    int comparisonResult = 0;
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    strcpy(pDnsTableEntry->Tag, "TestTag");

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)pXdnsCxtLink;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv6"), strlen("DnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Tag"), strlen("Tag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(ESNULLP));

    EXPECT_EQ(DNSMappingTable_GetParamStringValue((ANSC_HANDLE)pXdnsCxtLink, (char *)ParamName, pValue, &pUlSize), 1);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_GetParamStringValue_Failure)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "TestParam";
    int comparisonResult = 0;
    char pValue[256] = {0};
    ULONG pUlSize = 256;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    strcpy(pDnsTableEntry->Tag, "TestTag");

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)pXdnsCxtLink;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv6"), strlen("DnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Tag"), strlen("Tag"), StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_EQ(DNSMappingTable_GetParamStringValue((ANSC_HANDLE)pXdnsCxtLink, (char *)ParamName, pValue, &pUlSize), -1);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_SetParamStringValue_MacAddressNullValue)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "MacAddress";
    const char *strValue = "";
    int comparisonResult = 0;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pDnsTableEntry->MacAddressChanged = FALSE;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);
    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (ANSC_HANDLE)pXdnsCxtLink;

    strncpy(pDnsTableEntry->MacAddress, strValue, sizeof(pDnsTableEntry->MacAddress) - 1);
    pDnsTableEntry->MacAddress[sizeof(pDnsTableEntry->MacAddress) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv6"), strlen("DnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Tag"), strlen("Tag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(DNSMappingTable_SetParamStringValue(hInsContext, (char *)ParamName, (char *)strValue), TRUE);
    EXPECT_EQ(pDnsTableEntry->MacAddressChanged, TRUE);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_SetParamStringValue_DnsIPv4NullValue)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "DnsIPv4";
    const char *strValue = "";
    int comparisonResult = 0;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pDnsTableEntry->DnsIPv4Changed = FALSE;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);
    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (ANSC_HANDLE)pXdnsCxtLink;

    strncpy(pDnsTableEntry->DnsIPv4, strValue, sizeof(pDnsTableEntry->DnsIPv4) - 1);
    pDnsTableEntry->DnsIPv4[sizeof(pDnsTableEntry->DnsIPv4) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv6"), strlen("DnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Tag"), strlen("Tag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(DNSMappingTable_SetParamStringValue(hInsContext, (char *)ParamName, (char *)strValue), TRUE);
    EXPECT_EQ(pDnsTableEntry->DnsIPv4Changed, TRUE);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_SetParamStringValue_DnsIPv6NullValue)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "DnsIPv6";
    const char *strValue = "";
    int comparisonResult = 0;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pDnsTableEntry->DnsIPv6Changed = FALSE;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);
    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (ANSC_HANDLE)pXdnsCxtLink;

    strncpy(pDnsTableEntry->DnsIPv6, strValue, sizeof(pDnsTableEntry->DnsIPv6) - 1);
    pDnsTableEntry->DnsIPv6[sizeof(pDnsTableEntry->DnsIPv6) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv6"), strlen("DnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Tag"), strlen("Tag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(DNSMappingTable_SetParamStringValue(hInsContext, (char *)ParamName, (char *)strValue), TRUE);
    EXPECT_EQ(pDnsTableEntry->DnsIPv6Changed, TRUE);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}


TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_SetParamStringValue_TagNullValue)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "Tag";
    const char *strValue = "";
    int comparisonResult = 0;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pDnsTableEntry->TagChanged = FALSE;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);
    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (ANSC_HANDLE)pXdnsCxtLink;

    strncpy(pDnsTableEntry->Tag, strValue, sizeof(pDnsTableEntry->Tag) - 1);
    pDnsTableEntry->Tag[sizeof(pDnsTableEntry->Tag) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv6"), strlen("DnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Tag"), strlen("Tag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(DNSMappingTable_SetParamStringValue(hInsContext, (char *)ParamName, (char *)strValue), TRUE);
    EXPECT_EQ(pDnsTableEntry->TagChanged, TRUE);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}


TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_SetParamStringValue_MacAddress_strcpyFailure)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "MacAddress";
    const char *strValue = "00:00:00:00:00:00";
    int comparisonResult = 0;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pDnsTableEntry->MacAddressChanged = FALSE;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);
    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (ANSC_HANDLE)pXdnsCxtLink;

    strncpy(pDnsTableEntry->MacAddress, strValue, sizeof(pDnsTableEntry->MacAddress) - 1);
    pDnsTableEntry->MacAddress[sizeof(pDnsTableEntry->MacAddress) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv6"), strlen("DnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Tag"), strlen("Tag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(ESNULLP));

    EXPECT_EQ(DNSMappingTable_SetParamStringValue(hInsContext, (char *)ParamName, (char *)strValue), FALSE);
    EXPECT_EQ(pDnsTableEntry->MacAddressChanged, FALSE);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;

}


TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_SetParamStringValue_DnsIPv4_strcpyFailure)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "DnsIPv4";
    const char *strValue = "75.75.75.75";
    int comparisonResult = 0;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pDnsTableEntry->DnsIPv4Changed = FALSE;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);
    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (ANSC_HANDLE)pXdnsCxtLink;

    strncpy(pDnsTableEntry->DnsIPv4, strValue, sizeof(pDnsTableEntry->DnsIPv4) - 1);
    pDnsTableEntry->DnsIPv4[sizeof(pDnsTableEntry->DnsIPv4) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv6"), strlen("DnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Tag"), strlen("Tag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .WillRepeatedly(Return(ESNULLP));

    EXPECT_EQ(DNSMappingTable_SetParamStringValue(hInsContext, (char *)ParamName, (char *)strValue), FALSE);
    EXPECT_EQ(pDnsTableEntry->DnsIPv4Changed, FALSE);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}


TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_SetParamStringValue_DnsIPv6_strcpyFailure)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "DnsIPv6";
    const char *strValue = "2001:0db8:85a3:0000:0000:8a2e:0370:7334";
    int comparisonResult = 0;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pDnsTableEntry->DnsIPv6Changed = FALSE;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);
    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (ANSC_HANDLE)pXdnsCxtLink;

    strncpy(pDnsTableEntry->DnsIPv6, strValue, sizeof(pDnsTableEntry->DnsIPv6) - 1);
    pDnsTableEntry->DnsIPv6[sizeof(pDnsTableEntry->DnsIPv6) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv6"), strlen("DnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Tag"), strlen("Tag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .WillRepeatedly(Return(ESNULLP));

    EXPECT_EQ(DNSMappingTable_SetParamStringValue(hInsContext, (char *)ParamName, (char *)strValue), FALSE);
    EXPECT_EQ(pDnsTableEntry->DnsIPv6Changed, FALSE);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}


TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_SetParamStringValue_Tag_strcpyFailure)
{
    ANSC_HANDLE hInsContext = NULL;
    const char *ParamName = "Tag";
    const char *strValue = "TestTag";
    int comparisonResult = 0;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pDnsTableEntry->TagChanged = FALSE;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);
    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (ANSC_HANDLE)pXdnsCxtLink;

    strncpy(pDnsTableEntry->Tag, strValue, sizeof(pDnsTableEntry->Tag) - 1);
    pDnsTableEntry->Tag[sizeof(pDnsTableEntry->Tag) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("MacAddress"), strlen("MacAddress"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv4"), strlen("DnsIPv4"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("DnsIPv6"), strlen("DnsIPv6"), StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("Tag"), strlen("Tag"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .WillRepeatedly(Return(ESNULLP));

    EXPECT_EQ(DNSMappingTable_SetParamStringValue(hInsContext, (char *)ParamName, (char *)strValue), FALSE);
    EXPECT_EQ(pDnsTableEntry->TagChanged, FALSE);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_Validate_MacAddress)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;
    int comparisonResult = 0;

    const char *MacAddress = "";
    const char *ReturnValue = "MacAddress is Invalid";

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pDnsTableEntry->TagChanged = FALSE;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);
    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (ANSC_HANDLE)pXdnsCxtLink;

    pDnsTableEntry->MacAddressChanged = TRUE;

    strcpy(pDnsTableEntry->MacAddress, MacAddress);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(_, _, _, _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_,_,_,_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(DNSMappingTable_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_Validate_DnsIPv4)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;

    const char *DnsIPv4 = "";
    const char *ReturnValue = "DnsIPv4 is empty";

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pDnsTableEntry->TagChanged = FALSE;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);
    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (ANSC_HANDLE)pXdnsCxtLink;

    pDnsTableEntry->DnsIPv4Changed = TRUE;

    strcpy(pDnsTableEntry->DnsIPv4, DnsIPv4);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(_,_,_,_,_,_))
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_,_,_,_))
        .WillRepeatedly(Return(0));

    EXPECT_EQ(DNSMappingTable_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_Validate_DnsIPv6)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;

    const char *DnsIPv6 = "";
    const char *ReturnValue = "DnsIPv6 is empty";

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pDnsTableEntry->TagChanged = FALSE;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);
    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (ANSC_HANDLE)pXdnsCxtLink;

    pDnsTableEntry->DnsIPv6Changed = TRUE;

    strcpy(pDnsTableEntry->DnsIPv6, DnsIPv6);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(_,_,_,_,_,_))
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_,_,_,_))
        .WillRepeatedly(Return(0));

    EXPECT_EQ(DNSMappingTable_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_Validate_Tag)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;

    const char *Tag = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora.";
    const char *ReturnValue = "Tag Exceeds length";

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pDnsTableEntry->TagChanged = TRUE;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);
    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (ANSC_HANDLE)pXdnsCxtLink;

    strncpy(pDnsTableEntry->Tag, Tag, sizeof(pDnsTableEntry->Tag) - 1);
    pDnsTableEntry->Tag[sizeof(pDnsTableEntry->Tag) - 1] = '\0';
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(_,_,_,_,_,_))
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_,_,_,_))
        .WillRepeatedly(Return(0));

    EXPECT_EQ(DNSMappingTable_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_Validate_MacAddress_strcpyFailure)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;
    int comparisonResult = 0;

    const char *MacAddress = "";
    const char *ReturnValue = "MacAddress is Invalid";

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pDnsTableEntry->TagChanged = FALSE;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);
    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (ANSC_HANDLE)pXdnsCxtLink;

    pDnsTableEntry->MacAddressChanged = TRUE;

    strcpy(pDnsTableEntry->MacAddress, MacAddress);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(_, _, _, _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));
    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_,_,_,_))
        .Times(1)
        .WillOnce(Return(ESNULLP));

    EXPECT_EQ(DNSMappingTable_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_Validate_DnsIPv4_strcpyFailure)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;
    int comparisonResult = 0;

    const char *DnsIPv4 = "";
    const char *ReturnValue = "DnsIPv4 is empty";

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pDnsTableEntry->TagChanged = FALSE;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);
    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (ANSC_HANDLE)pXdnsCxtLink;

    pDnsTableEntry->DnsIPv4Changed = TRUE;

    strcpy(pDnsTableEntry->DnsIPv4, DnsIPv4);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(_,_,_,_,_,_))
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_,_,_,_))
        .Times(1)
        .WillOnce(Return(ESNULLP));

    EXPECT_EQ(DNSMappingTable_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_Validate_DnsIPv6_strcpyFailure)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;
    int comparisonResult = 0;

    const char *DnsIPv6 = "";
    const char *ReturnValue = "DnsIPv6 is empty";

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pDnsTableEntry->TagChanged = FALSE;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);
    pXdnsCxtLink->hContext = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pDnsTableEntry;

    hInsContext = (ANSC_HANDLE)pXdnsCxtLink;

    pDnsTableEntry->DnsIPv6Changed = TRUE;

    strcpy(pDnsTableEntry->DnsIPv6, DnsIPv6);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(_,_,_,_,_,_))
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_,_,_,_))
        .Times(1)
        .WillOnce(Return(ESNULLP));

    EXPECT_EQ(DNSMappingTable_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_Rollback_ifcondition)
{
    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pXdnsCxtLink->hContext = (ANSC_HANDLE)pDnsTableEntry;

    pDnsTableEntry->MacAddressChanged = TRUE;
    pDnsTableEntry->DnsIPv4Changed = TRUE;
    pDnsTableEntry->DnsIPv6Changed = TRUE;
    pDnsTableEntry->TagChanged = TRUE;

    const char* ipv4 = "192.168.0.2";
    const char* ipv6 = "fe80::2";
    const char* tag = "NewTag";
    char buf[256] = "";

    strcpy(pDnsTableEntry->MacAddress, "00:11:22:33:44:55");
    strcpy(pDnsTableEntry->DnsIPv4, ipv4);
    strcpy(pDnsTableEntry->DnsIPv6, ipv6);
    strcpy(pDnsTableEntry->Tag, tag);

    GetDnsMasqFileEntry(pDnsTableEntry->MacAddress, &buf);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(ipv4), _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));
    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(ipv6), _, _, _))
        .Times(1)
        .WillOnce(Return(ESNULLP));

    ULONG result = DNSMappingTable_Rollback((ANSC_HANDLE)pXdnsCxtLink);

    EXPECT_EQ(result, 0);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_Rollback_ifcondition2)
{
    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pXdnsCxtLink->hContext = (ANSC_HANDLE)pDnsTableEntry;

    pDnsTableEntry->MacAddressChanged = TRUE;
    pDnsTableEntry->DnsIPv4Changed = TRUE;
    pDnsTableEntry->DnsIPv6Changed = TRUE;
    pDnsTableEntry->TagChanged = TRUE;

    const char* ipv4 = "192.168.0.2";
    const char* ipv6 = "fe80::2";
    const char* tag = "NewTag";
    char buf[256] = "";

    strcpy(pDnsTableEntry->MacAddress, "00:11:22:33:44:55");
    strcpy(pDnsTableEntry->DnsIPv4, ipv4);
    strcpy(pDnsTableEntry->DnsIPv6, ipv6);
    strcpy(pDnsTableEntry->Tag, tag);

    GetDnsMasqFileEntry(pDnsTableEntry->MacAddress, &buf);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(ipv4), _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));
    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(ipv6), _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));
    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(StrEq(tag), _, _, _))
        .Times(1)
        .WillOnce(Return(ESNULLP));

    ULONG result = DNSMappingTable_Rollback((ANSC_HANDLE)pXdnsCxtLink);

    EXPECT_EQ(result, 0);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_Rollback_condition)
{
    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pXdnsCxtLink->hContext = (ANSC_HANDLE)pDnsTableEntry;

    pDnsTableEntry->MacAddressChanged = TRUE;
    pDnsTableEntry->DnsIPv4Changed = TRUE;
    pDnsTableEntry->DnsIPv6Changed = TRUE;
    pDnsTableEntry->TagChanged = TRUE;

    const char* ipv4 = "192.168.0.2";
    const char* ipv6 = "fe80::2";
    const char* tag = "NewTag";
    char buf[256] = "";

    strcpy(buf, "192.168.0.2 fe80::2 NewTag");
    strcpy(pDnsTableEntry->MacAddress, "00:11:22:33:44:55");
    strcpy(pDnsTableEntry->DnsIPv4, ipv4);
    strcpy(pDnsTableEntry->DnsIPv6, ipv6);
    strcpy(pDnsTableEntry->Tag, tag);

    GetDnsMasqFileEntry(pDnsTableEntry->MacAddress, &buf);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(3)
        .WillRepeatedly(Return(EOK));

    ULONG result = DNSMappingTable_Rollback((ANSC_HANDLE)pXdnsCxtLink);

    EXPECT_EQ(result, 0);
    EXPECT_FALSE(pDnsTableEntry->DnsIPv4Changed);
    EXPECT_FALSE(pDnsTableEntry->DnsIPv6Changed);
    EXPECT_FALSE(pDnsTableEntry->TagChanged);
    EXPECT_STREQ(pDnsTableEntry->DnsIPv4, ipv4);
    EXPECT_STREQ(pDnsTableEntry->DnsIPv6, ipv6);
    EXPECT_STREQ(pDnsTableEntry->Tag, tag);

    free(pDnsTableEntry);
    free(pXdnsCxtLink);
}


TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_Commit)
{
    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pXdnsCxtLink->hContext = (ANSC_HANDLE)pDnsTableEntry;

    pDnsTableEntry->MacAddressChanged = TRUE;
    pDnsTableEntry->DnsIPv4Changed = TRUE;
    pDnsTableEntry->DnsIPv6Changed = TRUE;
    pDnsTableEntry->TagChanged = TRUE;

    const char* ipv4 = "75.75.75.30";
    const char* ipv6 = "fe80::2";
    const char* tag = "NewTag";
    char buf[256] = "";

    strcpy(pDnsTableEntry->MacAddress, "00:11:22:33:44:55");
    strcpy(pDnsTableEntry->DnsIPv4, ipv4);
    strcpy(pDnsTableEntry->DnsIPv6, ipv6);
    strcpy(pDnsTableEntry->Tag, tag);

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(_, _))
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    ULONG result = DNSMappingTable_Commit((ANSC_HANDLE)pXdnsCxtLink);

    EXPECT_EQ(result, 0);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_Commit_v_secure_system_true)
{
    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pXdnsCxtLink->hContext = (ANSC_HANDLE)pDnsTableEntry;

    pDnsTableEntry->MacAddressChanged = TRUE;
    pDnsTableEntry->DnsIPv4Changed = TRUE;
    pDnsTableEntry->DnsIPv6Changed = TRUE;
    pDnsTableEntry->TagChanged = TRUE;

    const char* ipv4 = "75.75.75.75";
    const char* ipv6 = "fe80::2";
    const char* tag = "NewTag";
    char buf[256] = "";

    strcpy(pDnsTableEntry->MacAddress, "00:11:22:33:44:55");
    strcpy(pDnsTableEntry->DnsIPv4, ipv4);
    strcpy(pDnsTableEntry->DnsIPv6, ipv6);
    strcpy(pDnsTableEntry->Tag, tag);

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(_, _))
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    ULONG result = DNSMappingTable_Commit((ANSC_HANDLE)pXdnsCxtLink);

    EXPECT_EQ(result, 0);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, DNSMappingTable_Commit_v_secure_system_true2)
{
    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);
    pXdnsCxtLink->hContext = (ANSC_HANDLE)pDnsTableEntry;

    pDnsTableEntry->MacAddressChanged = TRUE;
    pDnsTableEntry->DnsIPv4Changed = TRUE;
    pDnsTableEntry->DnsIPv6Changed = TRUE;
    pDnsTableEntry->TagChanged = TRUE;

    const char* ipv4 = "75.75.75.30";
    const char* ipv6 = "fe80::2";
    const char* tag = "NewTag";
    char buf[256] = "";

    strcpy(pDnsTableEntry->MacAddress, "00:11:22:33:44:55");
    strcpy(pDnsTableEntry->DnsIPv4, ipv4);
    strcpy(pDnsTableEntry->DnsIPv6, ipv6);
    strcpy(pDnsTableEntry->Tag, tag);

    EXPECT_CALL(*g_safecLibMock, _sprintf_s_chk(_, _, _, _))
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_securewrapperMock, v_secure_system(_, _))
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    ULONG result = DNSMappingTable_Commit((ANSC_HANDLE)pXdnsCxtLink);

    EXPECT_EQ(result, 0);

    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
    free(pXdnsCxtLink);
    pXdnsCxtLink = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Validate_DefaultDeviceDnsIPv4Changed)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->DefaultDeviceDnsIPv4Changed = TRUE;

    const char *DnsIPv4 = "";
    const char *ReturnValue = "DnsIPv4 is empty";

    strcpy(pMyObject->DefaultDeviceDnsIPv4, DnsIPv4);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(XDNS_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Validate_DefaultDeviceDnsIPv6Changed)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->DefaultDeviceDnsIPv6Changed = TRUE;

    const char *DnsIPv6 = "";
    const char *ReturnValue = "DnsIPv6 is empty";

    strcpy(pMyObject->DefaultDeviceDnsIPv6, DnsIPv6);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(XDNS_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Validate_DefaultSecondaryDeviceDnsIPv4Changed)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->DefaultSecondaryDeviceDnsIPv4Changed = TRUE;

    const char *DnsIPv4 = "";
    const char *ReturnValue = "SecondaryDnsIPv4 is empty";

    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv4, DnsIPv4);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(XDNS_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Validate_DefaultSecondaryDeviceDnsIPv6Changed)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->DefaultSecondaryDeviceDnsIPv6Changed = TRUE;

    const char *DnsIPv6 = "";
    const char *ReturnValue = "SecondaryDnsIPv6 is empty";

    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv6, DnsIPv6);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(XDNS_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


// write the GTEST test cases for XDNS_Validate with all possible strlen else conditions

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Validate_DefaultDeviceDnsIPv4Changed2_1)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->DefaultDeviceDnsIPv4Changed = TRUE;

    const char *DnsIPv4 = "75.75.75.60";
    const char *ReturnValue = "DnsIPv4 is empty";

    strcpy(pMyObject->DefaultDeviceDnsIPv4, DnsIPv4);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_EQ(isValidIPv4Address(pMyObject->DefaultDeviceDnsIPv4), 1);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(XDNS_Validate(hInsContext, (char *)pReturnParamName, &puLength), TRUE);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Validate_DefaultDeviceDnsIPv4Changed2_2)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->DefaultDeviceDnsIPv4Changed = TRUE;

    const char *DnsIPv4 = "75.75.75.60";
    const char *ReturnValue = "DnsIPv4 is empty";

    strcpy(pMyObject->DefaultDeviceDnsIPv4, DnsIPv4);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_EQ(isValidIPv4Address(pMyObject->DefaultDeviceDnsIPv4), 1);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(-1));

    EXPECT_EQ(XDNS_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Validate_DefaultDeviceDnsIPv6Changed2_1)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->DefaultDeviceDnsIPv6Changed = TRUE;

    const char *DnsIPv6 = "fe80::2";
    const char *ReturnValue = "DnsIPv6 is empty";

    strcpy(pMyObject->DefaultDeviceDnsIPv6, DnsIPv6);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_EQ(isValidIPv6Address(pMyObject->DefaultDeviceDnsIPv6), 1);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(XDNS_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Validate_DefaultDeviceDnsIPv6Changed2_2)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->DefaultDeviceDnsIPv6Changed = TRUE;

    const char *DnsIPv6 = "fe80::2";
    const char *ReturnValue = "DnsIPv6 is empty";

    strcpy(pMyObject->DefaultDeviceDnsIPv6, DnsIPv6);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_EQ(isValidIPv6Address(pMyObject->DefaultDeviceDnsIPv6), 1);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(-1));

    EXPECT_EQ(XDNS_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Validate_DefaultSecondaryDeviceDnsIPv4Changed2_1)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->DefaultSecondaryDeviceDnsIPv4Changed = TRUE;

    const char *DnsIPv4 = "75.75.75.10";
    const char *ReturnValue = "SecondaryDnsIPv4 is empty";

    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv4, DnsIPv4);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_EQ(isValidIPv4Address(pMyObject->DefaultSecondaryDeviceDnsIPv4), 1);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(XDNS_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Validate_DefaultSecondaryDeviceDnsIPv4Changed2_2)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->DefaultSecondaryDeviceDnsIPv4Changed = TRUE;

    const char *DnsIPv4 = "75.75.75.10";
    const char *ReturnValue = "SecondaryDnsIPv4 is empty";

    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv4, DnsIPv4);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_EQ(isValidIPv4Address(pMyObject->DefaultSecondaryDeviceDnsIPv4), 1);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(-1));

    EXPECT_EQ(XDNS_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Validate_DefaultSecondaryDeviceDnsIPv6Changed2_1)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->DefaultSecondaryDeviceDnsIPv6Changed = TRUE;

    const char *DnsIPv6 = "fe80::2";
    const char *ReturnValue = "SecondaryDnsIPv6 is empty";

    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv6, DnsIPv6);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_EQ(isValidIPv6Address(pMyObject->DefaultSecondaryDeviceDnsIPv6), 1);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(XDNS_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspXdnsCosaDmlTestFixture, XDNS_Validate_DefaultSecondaryDeviceDnsIPv6Changed2_2)
{
    ANSC_HANDLE hInsContext = NULL;
    char pReturnParamName[256] = {0};
    ULONG puLength = 256;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->DefaultSecondaryDeviceDnsIPv6Changed = TRUE;

    const char *DnsIPv6 = "fe80::2";
    const char *ReturnValue = "SecondaryDnsIPv6 is empty";

    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv6, DnsIPv6);
    strcpy(pReturnParamName, ReturnValue);

    EXPECT_EQ(isValidIPv6Address(pMyObject->DefaultSecondaryDeviceDnsIPv6), 1);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(-1));

    EXPECT_EQ(XDNS_Validate(hInsContext, (char *)pReturnParamName, &puLength), FALSE);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}