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

class CcspXdnsCosaWebconfigApiTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        g_syscfgMock = new SyscfgMock();
        g_anscMemoryMock = new AnscMemoryMock();
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
        g_fileIOMock = new FileIOMock();
    }

    void TearDown() override {
        delete g_syscfgMock;
        delete g_anscMemoryMock;
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
        delete g_fileIOMock;

        g_syscfgMock = nullptr;
        g_anscMemoryMock = nullptr;
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
        g_fileIOMock = nullptr;
    }
};

// Unit Test for cosa_xdns_webconfig_api.c

ACTION_TEMPLATE(SetArgNPointeeTo, HAS_1_TEMPLATE_PARAMS(unsigned, uIndex), AND_2_VALUE_PARAMS(pData, uiDataSize))
{
    memcpy(std::get<uIndex>(args), pData, uiDataSize);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, CheckIfIpIsValidTest)
{
    const char *ipAddress = "192.168.21.2";
    EXPECT_EQ(VALID_IP, CheckIfIpIsValid((char *)ipAddress));
    const char *ipAddress1 = "2001:0db8:85a3:0000:0000:8a2e:0370:7334";
    EXPECT_EQ(VALID_IP, CheckIfIpIsValid((char *)ipAddress1));
    const char *ipAddress2 = "1000.1000.1000.1000";
    EXPECT_EQ(INVALID_IP, CheckIfIpIsValid((char *)ipAddress2));
    const char *ipAddress3 = "charfe80:2030:31:24:1:2:3:4";
    EXPECT_EQ(INVALID_IP, CheckIfIpIsValid((char *)ipAddress3));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, CheckIfMacIsValidTest)
{
    const char *macAddress = "00:11:22:33:44:55";
    EXPECT_EQ(0, CheckIfMacIsValid((char *)macAddress));
    const char *macAddress1 = "00:11:22:33:44:55/00:11:22:33:44:55";
    EXPECT_EQ(0, CheckIfMacIsValid((char *)macAddress1));
    const char *macAddress2 = "00:11:22:33:44:55/00:11:22:33:44:55/00:11:22:33:44:55";
    EXPECT_EQ(INVALID_MAC, CheckIfMacIsValid((char *)macAddress2));
    const char *macAddress3 = "00:11:22:33:44:55/00:11:22:33:44:55/00:11:22:33:44:55/00:11:22:33:44:55";
    EXPECT_EQ(INVALID_MAC, CheckIfMacIsValid((char *)macAddress3));
    const char *macAddress4 = "00:11:22:33:44:55";
    EXPECT_EQ(0, CheckIfMacIsValid((char *)macAddress4));
    const char *macAddress5 = "00:11:22:33:44:55/00:11:22:33:44:55";
    EXPECT_EQ(0, CheckIfMacIsValid((char *)macAddress5));
    const char *macAddress6 = "00:11:22:33:44:55/00:11:22:33:44:55/00:11:22:33:44:55";
    EXPECT_EQ(INVALID_MAC, CheckIfMacIsValid((char *)macAddress6));
    const char *macAddress7 = "00:11:22:33:44:55/00:11:22:33:44:55/00:11:22:33:44:55/00:11:22:33:44:55";
    EXPECT_EQ(INVALID_MAC, CheckIfMacIsValid((char *)macAddress7));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, getBlobVersionTest)
{
    char subdoc[] = "subdoc";
    char subdoc_ver[] = "subdoc_version";
    char buf[] = "subdoc_version";
    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("subdoc_version"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));
    EXPECT_EQ(0, getBlobVersion(subdoc));
}


TEST_F(CcspXdnsCosaWebconfigApiTestFixture, getBlobVersionNegativeTest)
{
    char subdoc[] = "subdoc";
    char subdoc_ver[] = "subdoc_version";
    char buf[] = "subdoc_version";
    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("subdoc_version"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(1)));
    EXPECT_EQ(0, getBlobVersion(subdoc));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, setBlobVersionTest)
{
    char subdoc[] = "subdoc";
    char subdoc_ver[] = "1";
    char buf[] = "subdoc_version";
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns_commit(StrEq(buf), StrEq(subdoc_ver)))
        .WillOnce(Return(0));
    int version = atoi(subdoc_ver);
    EXPECT_EQ(0, setBlobVersion(subdoc, version));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, setBlobVersionNegativeTest)
{
    char subdoc[] = "subdoc";
    char subdoc_ver[] = "1";
    char buf[] = "subdoc_version";
    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns_commit(StrEq(buf), StrEq(subdoc_ver)))
        .WillOnce(Return(1));
    int version = atoi(subdoc_ver);
    EXPECT_EQ(-1, setBlobVersion(subdoc, version));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, Process_XDNS_WebConfigRequest)
{
    xdnsdoc_t *xd = (xdnsdoc_t *)malloc(sizeof(xdnsdoc_t));
    xd->default_ipv4 = (char *)malloc(256);
    xd->default_ipv6 = (char *)malloc(256);
    xd->default_tag = (char *)malloc(256);
    xd->table_param = (xdnsTable_t *)malloc(sizeof(xdnsTable_t));
    xd->table_param->entries = (dnsMapping_t *)malloc(sizeof(dnsMapping_t));
    xd->table_param->entries->dns_mac = (char *)malloc(256);
    xd->table_param->entries->dns_ipv4 = (char *)malloc(256);
    xd->table_param->entries->dns_ipv6 = (char *)malloc(256);
    xd->table_param->entries->dns_tag = (char *)malloc(256);
    xd->subdoc_name = (char *)malloc(256);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(5)
        .WillRepeatedly(Return(0));

    pErr result = Process_XDNS_WebConfigRequest(xd);

    EXPECT_TRUE(result);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, Process_XDNS_WebConfigRequest_Failure)
{
    xdnsdoc_t *xd = (xdnsdoc_t *)malloc(sizeof(xdnsdoc_t));
    xd->default_ipv4 = (char *)malloc(256);
    xd->default_ipv6 = (char *)malloc(256);
    xd->default_tag = (char *)malloc(256);
    xd->table_param = (xdnsTable_t *)malloc(sizeof(xdnsTable_t));
    xd->table_param->entries = (dnsMapping_t *)malloc(sizeof(dnsMapping_t));
    xd->table_param->entries->dns_mac = (char *)malloc(256);
    xd->table_param->entries->dns_ipv4 = (char *)malloc(256);
    xd->table_param->entries->dns_ipv6 = (char *)malloc(256);
    xd->table_param->entries->dns_tag = (char *)malloc(256);
    xd->subdoc_name = (char *)malloc(256);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(5)
        .WillRepeatedly(Return(0));

    pErr result = Process_XDNS_WebConfigRequest(xd);

    EXPECT_TRUE(result);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_read_dns_ipTest)
{
    const char *UseRDKDefaultDeviceDnsIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    FILE* fp = (FILE *)NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp));

    EXPECT_EQ(1, xdns_read_dns_ip((char *) UseRDKDefaultDeviceDnsIPv4, (char *) UseRDKDefaultDeviceDnsIPv6));

}


TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_read_dns_ipTest2)
{
    const char *UseRDKDefaultDeviceDnsIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    FILE* fp = (FILE *)0xffffffff;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp));

    EXPECT_CALL(*g_fileIOMock, fclose(_))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_fileIOMock, fgets(_, _, fp))
        .Times(1)
        .WillOnce(Return((char *)NULL));

    EXPECT_EQ(0, xdns_read_dns_ip((char *) UseRDKDefaultDeviceDnsIPv4, (char *) UseRDKDefaultDeviceDnsIPv6));

}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_read_dns_ipTest3)
{
    const char *UseRDKDefaultDeviceDnsIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    FILE* fp = (FILE *)0xffffffff;
    char buff[64] = {0};
    int count = 1;

    snprintf(buff, sizeof(buff), "nameserver %s", UseRDKDefaultDeviceDnsIPv4);

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp));

    EXPECT_CALL(*g_fileIOMock, fclose(_))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_fileIOMock, fgets(_, _, fp))
        .Times(2)
        .WillOnce(::testing::DoAll(
            SetArgNPointeeTo<0>(std::begin(buff), sizeof(buff)),
            ::testing::Return((char*)buff)
        ))
        .WillOnce(::testing::ReturnNull());

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(0, xdns_read_dns_ip((char *) UseRDKDefaultDeviceDnsIPv4, (char *) UseRDKDefaultDeviceDnsIPv6));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_read_dns_ipTest4)
{
    const char *UseRDKDefaultDeviceDnsIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    FILE* fp = (FILE *)0xfffffffe;
    char buff[64] = {0};
    int count = 1;

    snprintf(buff, sizeof(buff), "nameserver %s", UseRDKDefaultDeviceDnsIPv6);

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp));

    EXPECT_CALL(*g_fileIOMock, fclose(_))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_fileIOMock, fgets(_, _, fp))
        .Times(1)
        .WillOnce(::testing::DoAll(
            SetArgNPointeeTo<0>(std::begin(buff), sizeof(buff)),
            ::testing::Return((char*)buff)
        ));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(0, xdns_read_dns_ip((char *) UseRDKDefaultDeviceDnsIPv4, (char *) UseRDKDefaultDeviceDnsIPv6));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_read_dns_ipTest5)
{
    const char *UseRDKDefaultDeviceDnsIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    FILE* fp = (FILE *)0xfffffffe;
    char buff[64] = {0};
    int count = 1;

    snprintf(buff, sizeof(buff), "nameserver %s", UseRDKDefaultDeviceDnsIPv6);

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp));

    EXPECT_CALL(*g_fileIOMock, fclose(_))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_fileIOMock, fgets(_, _, fp))
        .Times(1)
        .WillOnce(::testing::DoAll(
            SetArgNPointeeTo<0>(std::begin(buff), sizeof(buff)),
            ::testing::Return((char*)buff)
        ));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(1));

    EXPECT_EQ(1, xdns_read_dns_ip((char *) UseRDKDefaultDeviceDnsIPv4, (char *) UseRDKDefaultDeviceDnsIPv6));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_load_dns_ipTest)
{
    const char *DnsIPv4 = "75.75.75.30";
    const char *DnsIPv6 = "2001:558:feed::1";
    const char *UseRDKDefaultDeviceDnsIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    char router_mode[] = "2";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_EQ(1, xdns_load_dns_ip((char *)DnsIPv4, (char *)DnsIPv6, (char *)UseRDKDefaultDeviceDnsIPv4, (char *)UseRDKDefaultDeviceDnsIPv6));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_load_dns_ipTest2)
{
    const char *DnsIPv4 = "75.75.75.30";
    const char *DnsIPv6 = "2001:558:feed::1";
    const char *UseRDKDefaultDeviceDnsIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    char router_mode[] = "1";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(0, xdns_load_dns_ip((char *)DnsIPv4, (char *)DnsIPv6, (char *)UseRDKDefaultDeviceDnsIPv4, (char *)UseRDKDefaultDeviceDnsIPv6));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_load_dns_ipTest2_negative)
{
    const char *DnsIPv4 = "75.75.75.30";
    const char *DnsIPv6 = "2001:558:feed::1";
    const char *UseRDKDefaultDeviceDnsIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    char router_mode[] = "1";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_EQ(1, xdns_load_dns_ip((char *)DnsIPv4, (char *)DnsIPv6, (char *)UseRDKDefaultDeviceDnsIPv4, (char *)UseRDKDefaultDeviceDnsIPv6));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_load_dns_ipTest2_negative2)
{
    const char *DnsIPv4 = "75.75.75.30";
    const char *DnsIPv6 = "2001:558:feed::1";
    const char *UseRDKDefaultDeviceDnsIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    char router_mode[] = "1";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    EXPECT_EQ(1, xdns_load_dns_ip((char *)DnsIPv4, (char *)DnsIPv6, (char *)UseRDKDefaultDeviceDnsIPv4, (char *)UseRDKDefaultDeviceDnsIPv6));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_load_dns_ipTest3)
{
    const char *DnsIPv4 = "75.75.75.30";
    const char *DnsIPv6 = "2001:558:feed::1";
    const char *UseRDKDefaultDeviceDnsIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    char router_mode[] = "0";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(0, xdns_load_dns_ip((char *)DnsIPv4, (char *)DnsIPv6, (char *)UseRDKDefaultDeviceDnsIPv4, (char *)UseRDKDefaultDeviceDnsIPv6));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_load_dns_ipTest3_negative)
{
    const char *DnsIPv4 = "75.75.75.30";
    const char *DnsIPv6 = "2001:558:feed::1";
    const char *UseRDKDefaultDeviceDnsIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    char router_mode[] = "0";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_EQ(1, xdns_load_dns_ip((char *)DnsIPv4, (char *)DnsIPv6, (char *)UseRDKDefaultDeviceDnsIPv4, (char *)UseRDKDefaultDeviceDnsIPv6));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_load_dns_ipTest3_negative2)
{
    const char *DnsIPv4 = "75.75.75.30";
    const char *DnsIPv6 = "2001:558:feed::1";
    const char *UseRDKDefaultDeviceDnsIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    char router_mode[] = "0";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    EXPECT_EQ(1, xdns_load_dns_ip((char *)DnsIPv4, (char *)DnsIPv6, (char *)UseRDKDefaultDeviceDnsIPv4, (char *)UseRDKDefaultDeviceDnsIPv6));
}


TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_load_dns_ipTest4)
{
    const char *DnsIPv4 = "75.75.75.30";
    const char *DnsIPv6 = "2001:558:feed::1";
    const char *UseRDKDefaultDeviceDnsIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    char router_mode[] = "3";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(0, xdns_load_dns_ip((char *)DnsIPv4, (char *)DnsIPv6, (char *)UseRDKDefaultDeviceDnsIPv4, (char *)UseRDKDefaultDeviceDnsIPv6));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_load_dns_ipTest4_negative)
{
    const char *DnsIPv4 = "75.75.75.30";
    const char *DnsIPv6 = "2001:558:feed::1";
    const char *UseRDKDefaultDeviceDnsIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    char router_mode[] = "3";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_EQ(1, xdns_load_dns_ip((char *)DnsIPv4, (char *)DnsIPv6, (char *)UseRDKDefaultDeviceDnsIPv4, (char *)UseRDKDefaultDeviceDnsIPv6));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_load_dns_ipTest4_negative2)
{
    const char *DnsIPv4 = "75.75.75.30";
    const char *DnsIPv6 = "2001:558:feed::1";
    const char *UseRDKDefaultDeviceDnsIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    char router_mode[] = "3";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    EXPECT_EQ(1, xdns_load_dns_ip((char *)DnsIPv4, (char *)DnsIPv6, (char *)UseRDKDefaultDeviceDnsIPv4, (char *)UseRDKDefaultDeviceDnsIPv6));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_read_load_dns_ipTest)
{
    const char *Blob_Valid_IPv4 = "75.75.75.30";
    const char *Blob_Valid_IPv6 = "2001:558:feed::1";
    const char *DnsIPv4 = "";
    const char *DnsIPv6 = "";
    int ret = 1;
    const char *UseRDKDefaultDeviceIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceIPv6 = "::1";
    FILE* fp = (FILE *)NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(2)
        .WillRepeatedly(Return(fp));

    EXPECT_EQ(xdns_read_dns_ip((char *)UseRDKDefaultDeviceIPv4, (char *)UseRDKDefaultDeviceIPv6), 1);

    EXPECT_EQ(CheckIfIpIsValid((char *)UseRDKDefaultDeviceIPv4), VALID_IP);
    EXPECT_EQ(CheckIfIpIsValid((char *)UseRDKDefaultDeviceIPv6), VALID_IP);

    EXPECT_EQ(CheckIfIpIsValid((char *)Blob_Valid_IPv4), VALID_IP);

    EXPECT_EQ(1, xdns_read_load_dns_ip((char *)Blob_Valid_IPv4, (char *)Blob_Valid_IPv6, (char *)DnsIPv4, (char *)DnsIPv6));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_read_load_dns_ipTest2)
{
    const char *Blob_Valid_IPv4 = "75.75.75.30";
    const char *Blob_Valid_IPv6 = "2001:558:feed::1";
    const char *DnsIPv4 = "";
    const char *DnsIPv6 = "";
    int ret = 1;
    const char *UseRDKDefaultDeviceIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceIPv6 = "::1";
    FILE* fp = (FILE *)0xfffffffe;
    char buff[64] = {0};
    int count = 1;

    snprintf(buff, sizeof(buff), "nameserver %s", UseRDKDefaultDeviceIPv6);

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(2)
        .WillRepeatedly(Return(fp));

    EXPECT_CALL(*g_fileIOMock, fclose(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_fileIOMock, fgets(_, _, fp))
        .Times(2)
        .WillOnce(::testing::DoAll(
            SetArgNPointeeTo<0>(std::begin(buff), sizeof(buff)),
            ::testing::Return((char*)buff)
        ))
        .WillOnce(::testing::ReturnNull());

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(1));

    EXPECT_EQ(xdns_read_dns_ip((char *)UseRDKDefaultDeviceIPv4, (char *)UseRDKDefaultDeviceIPv6), 1);

    EXPECT_EQ(CheckIfIpIsValid((char *)UseRDKDefaultDeviceIPv4), VALID_IP);
    EXPECT_EQ(CheckIfIpIsValid((char *)UseRDKDefaultDeviceIPv6), VALID_IP);

    EXPECT_EQ(CheckIfIpIsValid((char *)Blob_Valid_IPv4), VALID_IP);

    EXPECT_EQ(0, xdns_read_load_dns_ip((char *)Blob_Valid_IPv4, (char *)Blob_Valid_IPv6, (char *)DnsIPv4, (char *)DnsIPv6));
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, xdns_read_load_dns_ipTest3)
{
    const char *Blob_Valid_IPv4 = "75.75.75.30";
    const char *Blob_Valid_IPv6 = "2001:558:feed::1";
    const char *DnsIPv4 = "";
    const char *DnsIPv6 = "";
    int ret = 1;
    const char *UseRDKDefaultDeviceIPv4 = "127.0.0.1";
    const char *UseRDKDefaultDeviceIPv6 = "::1";
    FILE* fp = (FILE *)0xfffffffe;
    char buff[64] = {0};
    int count = 1;

    snprintf(buff, sizeof(buff), "nameserver %s", UseRDKDefaultDeviceIPv6);

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(2)
        .WillRepeatedly(Return(fp));

    EXPECT_CALL(*g_fileIOMock, fclose(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_fileIOMock, fgets(_, _, fp))
        .Times(2)
        .WillOnce(::testing::DoAll(
            SetArgNPointeeTo<0>(std::begin(buff), sizeof(buff)),
            ::testing::Return((char*)buff)
        ))
        .WillOnce(::testing::ReturnNull());

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(1));

    EXPECT_EQ(xdns_read_dns_ip((char *)UseRDKDefaultDeviceIPv4, (char *)UseRDKDefaultDeviceIPv6), 1);

    EXPECT_EQ(CheckIfIpIsValid((char *)UseRDKDefaultDeviceIPv4), VALID_IP);
    EXPECT_EQ(CheckIfIpIsValid((char *)UseRDKDefaultDeviceIPv6), VALID_IP);

    EXPECT_EQ(CheckIfIpIsValid((char *)Blob_Valid_IPv4), VALID_IP);

    char router_mode[] = "3";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(xdns_load_dns_ip((char *)DnsIPv4, (char *)DnsIPv6, (char *)Blob_Valid_IPv4, (char *)UseRDKDefaultDeviceIPv6), 0);

    EXPECT_EQ(0, xdns_read_load_dns_ip((char *)Blob_Valid_IPv4, (char *)Blob_Valid_IPv6, (char *)DnsIPv4, (char *)DnsIPv6));
}


TEST_F(CcspXdnsCosaWebconfigApiTestFixture, clear_xdns_cacheTest)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));
    tmp_xdns_cache->XdnsEnable = 1;
    tmp_xdns_cache->Tablecount = 1;

    char *tmpMacAddress = (char *)malloc(256);
    char *tmpDnsIPv4 = (char *)malloc(256);
    char *tmpDnsIPv6 = (char *)malloc(256);
    char *tmpTag = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultDeviceTag = (char *)malloc(256);

    strncpy(tmpMacAddress, "00:00:00:00:00:00", 256);
    strncpy(tmpDnsIPv4, "75.75.75.30", 256);
    strncpy(tmpDnsIPv6, "2001:558:feed::1", 256);
    strncpy(tmpTag, "TestTag", 256);
    strncpy(tmpDefaultDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultDeviceTag, "TestTag", 256);

    strncpy(tmp_xdns_cache->XDNSTableList[0].MacAddress, tmpMacAddress, sizeof(tmp_xdns_cache->XDNSTableList[0].MacAddress));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv4, tmpDnsIPv4, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv4));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv6, tmpDnsIPv6, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv6));
    strncpy(tmp_xdns_cache->XDNSTableList[0].Tag, tmpTag, sizeof(tmp_xdns_cache->XDNSTableList[0].Tag));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmpDefaultDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv6, tmpDefaultDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4, tmpDefaultSecondaryDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6, tmpDefaultSecondaryDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultDeviceTag, tmpDefaultDeviceTag, sizeof(tmp_xdns_cache->DefaultDeviceTag));

    free(tmpMacAddress);
    free(tmpDnsIPv4);
    free(tmpDnsIPv6);
    free(tmpTag);
    free(tmpDefaultDeviceDnsIPv4);
    free(tmpDefaultDeviceDnsIPv6);
    free(tmpDefaultSecondaryDeviceDnsIPv4);
    free(tmpDefaultSecondaryDeviceDnsIPv6);
    free(tmpDefaultDeviceTag);

    clear_xdns_cache(tmp_xdns_cache);

    EXPECT_EQ(0, tmp_xdns_cache->XdnsEnable);
    EXPECT_EQ(0, tmp_xdns_cache->Tablecount);
    EXPECT_EQ(0, strlen(tmp_xdns_cache->DefaultDeviceDnsIPv4));
    EXPECT_EQ(0, strlen(tmp_xdns_cache->DefaultDeviceDnsIPv6));
    EXPECT_EQ(0, strlen(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4));
    EXPECT_EQ(0, strlen(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6));
    EXPECT_EQ(0, strlen(tmp_xdns_cache->DefaultDeviceTag));
    EXPECT_EQ(0, strlen(tmp_xdns_cache->XDNSTableList[0].MacAddress));
    EXPECT_EQ(0, strlen(tmp_xdns_cache->XDNSTableList[0].DnsIPv4));
    EXPECT_EQ(0, strlen(tmp_xdns_cache->XDNSTableList[0].DnsIPv6));
    EXPECT_EQ(0, strlen(tmp_xdns_cache->XDNSTableList[0].Tag));

    free(tmp_xdns_cache);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, backup_xdns_cacheTest)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));
    xdns_cache *xdns_cache_bkup = (xdns_cache *)malloc(sizeof(xdns_cache));

    char *tmpMacAddress = (char *)malloc(256);
    char *tmpDnsIPv4 = (char *)malloc(256);
    char *tmpDnsIPv6 = (char *)malloc(256);
    char *tmpTag = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultDeviceTag = (char *)malloc(256);

    tmp_xdns_cache->XdnsEnable = 1;
    tmp_xdns_cache->Tablecount = 1;
    strncpy(tmpMacAddress, "00:00:00:00:00:00", 256);
    strncpy(tmpDnsIPv4, "75.75.75.30", 256);
    strncpy(tmpDnsIPv6, "2001:558:feed::1", 256);
    strncpy(tmpTag, "TestTag", 256);
    strncpy(tmpDefaultDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultDeviceTag, "TestTag", 256);

    strncpy(tmp_xdns_cache->XDNSTableList[0].MacAddress, tmpMacAddress, sizeof(tmp_xdns_cache->XDNSTableList[0].MacAddress));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv4, tmpDnsIPv4, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv4));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv6, tmpDnsIPv6, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv6));
    strncpy(tmp_xdns_cache->XDNSTableList[0].Tag, tmpTag, sizeof(tmp_xdns_cache->XDNSTableList[0].Tag));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmpDefaultDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv6, tmpDefaultDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4, tmpDefaultSecondaryDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6, tmpDefaultSecondaryDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultDeviceTag, tmpDefaultDeviceTag, sizeof(tmp_xdns_cache->DefaultDeviceTag));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(9)
        .WillRepeatedly(Return(0));

    xdns_cache_bkup->XdnsEnable = tmp_xdns_cache->XdnsEnable;
    xdns_cache_bkup->Tablecount = tmp_xdns_cache->Tablecount;

    backup_xdns_cache(tmp_xdns_cache, xdns_cache_bkup);

    EXPECT_EQ(1, xdns_cache_bkup->XdnsEnable);
    EXPECT_EQ(1, xdns_cache_bkup->Tablecount);

    free(tmpMacAddress);
    free(tmpDnsIPv4);
    free(tmpDnsIPv6);
    free(tmpTag);
    free(tmpDefaultDeviceDnsIPv4);
    free(tmpDefaultDeviceDnsIPv6);
    free(tmpDefaultSecondaryDeviceDnsIPv4);
    free(tmpDefaultSecondaryDeviceDnsIPv6);
    free(tmpDefaultDeviceTag);
    free(tmp_xdns_cache);
    free(xdns_cache_bkup);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, backup_xdns_cacheTest2)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));
    xdns_cache *xdns_cache_bkup = (xdns_cache *)malloc(sizeof(xdns_cache));

    tmp_xdns_cache->XdnsEnable = 1;
    tmp_xdns_cache->Tablecount = 1;
    char *tmpMacAddress = (char *)malloc(256);
    char *tmpDnsIPv4 = (char *)malloc(256);
    char *tmpDnsIPv6 = (char *)malloc(256);
    char *tmpTag = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultDeviceTag = (char *)malloc(256);

    strncpy(tmpMacAddress, "00:00:00:00:00:00", 256);
    strncpy(tmpDnsIPv4, "75.75.75.30", 256);
    strncpy(tmpDnsIPv6, "2001:558:feed::1", 256);
    strncpy(tmpTag, "TestTag", 256);
    strncpy(tmpDefaultDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultDeviceTag, "TestTag", 256);

    strncpy(tmp_xdns_cache->XDNSTableList[0].MacAddress, tmpMacAddress, sizeof(tmp_xdns_cache->XDNSTableList[0].MacAddress));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv4, tmpDnsIPv4, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv4));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv6, tmpDnsIPv6, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv6));
    strncpy(tmp_xdns_cache->XDNSTableList[0].Tag, tmpTag, sizeof(tmp_xdns_cache->XDNSTableList[0].Tag));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmpDefaultDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv6, tmpDefaultDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4, tmpDefaultSecondaryDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6, tmpDefaultSecondaryDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultDeviceTag, tmpDefaultDeviceTag, sizeof(tmp_xdns_cache->DefaultDeviceTag));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    xdns_cache_bkup->XdnsEnable = tmp_xdns_cache->XdnsEnable;
    xdns_cache_bkup->Tablecount = tmp_xdns_cache->Tablecount;

    backup_xdns_cache(tmp_xdns_cache, xdns_cache_bkup);

    EXPECT_EQ(1, xdns_cache_bkup->XdnsEnable);
    EXPECT_EQ(1, xdns_cache_bkup->Tablecount);

    free(tmpMacAddress);
    free(tmpDnsIPv4);
    free(tmpDnsIPv6);
    free(tmpTag);
    free(tmpDefaultDeviceDnsIPv4);
    free(tmpDefaultDeviceDnsIPv6);
    free(tmpDefaultSecondaryDeviceDnsIPv4);
    free(tmpDefaultSecondaryDeviceDnsIPv6);
    free(tmpDefaultDeviceTag);
    free(tmp_xdns_cache);
    free(xdns_cache_bkup);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, backup_xdns_cacheTest3)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));
    xdns_cache *xdns_cache_bkup = (xdns_cache *)malloc(sizeof(xdns_cache));

    tmp_xdns_cache->XdnsEnable = 1;
    tmp_xdns_cache->Tablecount = 1;
    char *tmpMacAddress = (char *)malloc(256);
    char *tmpDnsIPv4 = (char *)malloc(256);
    char *tmpDnsIPv6 = (char *)malloc(256);
    char *tmpTag = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultDeviceTag = (char *)malloc(256);

    strncpy(tmpMacAddress, "00:00:00:00:00:00", 256);
    strncpy(tmpDnsIPv4, "75.75.75.30", 256);
    strncpy(tmpDnsIPv6, "2001:558:feed::1", 256);
    strncpy(tmpTag, "TestTag", 256);
    strncpy(tmpDefaultDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultDeviceTag, "TestTag", 256);

    strncpy(tmp_xdns_cache->XDNSTableList[0].MacAddress, tmpMacAddress, sizeof(tmp_xdns_cache->XDNSTableList[0].MacAddress));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv4, tmpDnsIPv4, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv4));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv6, tmpDnsIPv6, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv6));
    strncpy(tmp_xdns_cache->XDNSTableList[0].Tag, tmpTag, sizeof(tmp_xdns_cache->XDNSTableList[0].Tag));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmpDefaultDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv6, tmpDefaultDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4, tmpDefaultSecondaryDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6, tmpDefaultSecondaryDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultDeviceTag, tmpDefaultDeviceTag, sizeof(tmp_xdns_cache->DefaultDeviceTag));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(3)
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    xdns_cache_bkup->XdnsEnable = tmp_xdns_cache->XdnsEnable;
    xdns_cache_bkup->Tablecount = tmp_xdns_cache->Tablecount;

    backup_xdns_cache(tmp_xdns_cache, xdns_cache_bkup);

    EXPECT_EQ(1, xdns_cache_bkup->XdnsEnable);
    EXPECT_EQ(1, xdns_cache_bkup->Tablecount);

    free(tmpMacAddress);
    free(tmpDnsIPv4);
    free(tmpDnsIPv6);
    free(tmpTag);
    free(tmpDefaultDeviceDnsIPv4);
    free(tmpDefaultDeviceDnsIPv6);
    free(tmpDefaultSecondaryDeviceDnsIPv4);
    free(tmpDefaultSecondaryDeviceDnsIPv6);
    free(tmpDefaultDeviceTag);
    free(tmp_xdns_cache);
    free(xdns_cache_bkup);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, backup_xdns_cacheTest4)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));
    xdns_cache *xdns_cache_bkup = (xdns_cache *)malloc(sizeof(xdns_cache));

    tmp_xdns_cache->XdnsEnable = 1;
    tmp_xdns_cache->Tablecount = 1;
    char *tmpMacAddress = (char *)malloc(256);
    char *tmpDnsIPv4 = (char *)malloc(256);
    char *tmpDnsIPv6 = (char *)malloc(256);
    char *tmpTag = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultDeviceTag = (char *)malloc(256);

    strncpy(tmpMacAddress, "00:00:00:00:00:00", 256);
    strncpy(tmpDnsIPv4, "75.75.75.30", 256);
    strncpy(tmpDnsIPv6, "2001:558:feed::1", 256);
    strncpy(tmpTag, "TestTag", 256);
    strncpy(tmpDefaultDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultDeviceTag, "TestTag", 256);

    strncpy(tmp_xdns_cache->XDNSTableList[0].MacAddress, tmpMacAddress, sizeof(tmp_xdns_cache->XDNSTableList[0].MacAddress));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv4, tmpDnsIPv4, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv4));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv6, tmpDnsIPv6, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv6));
    strncpy(tmp_xdns_cache->XDNSTableList[0].Tag, tmpTag, sizeof(tmp_xdns_cache->XDNSTableList[0].Tag));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmpDefaultDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv6, tmpDefaultDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4, tmpDefaultSecondaryDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6, tmpDefaultSecondaryDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultDeviceTag, tmpDefaultDeviceTag, sizeof(tmp_xdns_cache->DefaultDeviceTag));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(4)
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    xdns_cache_bkup->XdnsEnable = tmp_xdns_cache->XdnsEnable;
    xdns_cache_bkup->Tablecount = tmp_xdns_cache->Tablecount;

    backup_xdns_cache(tmp_xdns_cache, xdns_cache_bkup);

    EXPECT_EQ(1, xdns_cache_bkup->XdnsEnable);
    EXPECT_EQ(1, xdns_cache_bkup->Tablecount);

    free(tmpMacAddress);
    free(tmpDnsIPv4);
    free(tmpDnsIPv6);
    free(tmpTag);
    free(tmpDefaultDeviceDnsIPv4);
    free(tmpDefaultDeviceDnsIPv6);
    free(tmpDefaultSecondaryDeviceDnsIPv4);
    free(tmpDefaultSecondaryDeviceDnsIPv6);
    free(tmpDefaultDeviceTag);
    free(tmp_xdns_cache);
    free(xdns_cache_bkup);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, backup_xdns_cacheTest5)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));
    xdns_cache *xdns_cache_bkup = (xdns_cache *)malloc(sizeof(xdns_cache));

    char *tmpMacAddress = (char *)malloc(256);
    char *tmpDnsIPv4 = (char *)malloc(256);
    char *tmpDnsIPv6 = (char *)malloc(256);
    char *tmpTag = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultDeviceTag = (char *)malloc(256);

    tmp_xdns_cache->XdnsEnable = 1;
    tmp_xdns_cache->Tablecount = 1;
    strncpy(tmpMacAddress, "00:00:00:00:00:00", 256);
    strncpy(tmpDnsIPv4, "75.75.75.30", 256);
    strncpy(tmpDnsIPv6, "2001:558:feed::1", 256);
    strncpy(tmpTag, "TestTag", 256);
    strncpy(tmpDefaultDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultDeviceTag, "TestTag", 256);

    strncpy(tmp_xdns_cache->XDNSTableList[0].MacAddress, tmpMacAddress, sizeof(tmp_xdns_cache->XDNSTableList[0].MacAddress));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv4, tmpDnsIPv4, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv4));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv6, tmpDnsIPv6, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv6));
    strncpy(tmp_xdns_cache->XDNSTableList[0].Tag, tmpTag, sizeof(tmp_xdns_cache->XDNSTableList[0].Tag));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmpDefaultDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv6, tmpDefaultDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4, tmpDefaultSecondaryDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6, tmpDefaultSecondaryDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultDeviceTag, tmpDefaultDeviceTag, sizeof(tmp_xdns_cache->DefaultDeviceTag));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(5)
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    xdns_cache_bkup->XdnsEnable = tmp_xdns_cache->XdnsEnable;
    xdns_cache_bkup->Tablecount = tmp_xdns_cache->Tablecount;

    backup_xdns_cache(tmp_xdns_cache, xdns_cache_bkup);

    EXPECT_EQ(1, xdns_cache_bkup->XdnsEnable);
    EXPECT_EQ(1, xdns_cache_bkup->Tablecount);

    free(tmpMacAddress);
    free(tmpDnsIPv4);
    free(tmpDnsIPv6);
    free(tmpTag);
    free(tmpDefaultDeviceDnsIPv4);
    free(tmpDefaultDeviceDnsIPv6);
    free(tmpDefaultSecondaryDeviceDnsIPv4);
    free(tmpDefaultSecondaryDeviceDnsIPv6);
    free(tmpDefaultDeviceTag);
    free(tmp_xdns_cache);
    free(xdns_cache_bkup);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, backup_xdns_cacheTest6)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));
    xdns_cache *xdns_cache_bkup = (xdns_cache *)malloc(sizeof(xdns_cache));

    tmp_xdns_cache->XdnsEnable = 1;
    tmp_xdns_cache->Tablecount = 1;
    char *tmpMacAddress = (char *)malloc(256);
    char *tmpDnsIPv4 = (char *)malloc(256);
    char *tmpDnsIPv6 = (char *)malloc(256);
    char *tmpTag = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultDeviceTag = (char *)malloc(256);

    strncpy(tmpMacAddress, "00:00:00:00:00:00", 256);
    strncpy(tmpDnsIPv4, "75.75.75.30", 256);
    strncpy(tmpDnsIPv6, "2001:558:feed::1", 256);
    strncpy(tmpTag, "TestTag", 256);
    strncpy(tmpDefaultDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultDeviceTag, "TestTag", 256);

    strncpy(tmp_xdns_cache->XDNSTableList[0].MacAddress, tmpMacAddress, sizeof(tmp_xdns_cache->XDNSTableList[0].MacAddress));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv4, tmpDnsIPv4, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv4));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv6, tmpDnsIPv6, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv6));
    strncpy(tmp_xdns_cache->XDNSTableList[0].Tag, tmpTag, sizeof(tmp_xdns_cache->XDNSTableList[0].Tag));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmpDefaultDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv6, tmpDefaultDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4, tmpDefaultSecondaryDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6, tmpDefaultSecondaryDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultDeviceTag, tmpDefaultDeviceTag, sizeof(tmp_xdns_cache->DefaultDeviceTag));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(6)
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    xdns_cache_bkup->XdnsEnable = tmp_xdns_cache->XdnsEnable;
    xdns_cache_bkup->Tablecount = tmp_xdns_cache->Tablecount;

    backup_xdns_cache(tmp_xdns_cache, xdns_cache_bkup);

    EXPECT_EQ(1, xdns_cache_bkup->XdnsEnable);
    EXPECT_EQ(1, xdns_cache_bkup->Tablecount);

    free(tmpMacAddress);
    free(tmpDnsIPv4);
    free(tmpDnsIPv6);
    free(tmpTag);
    free(tmpDefaultDeviceDnsIPv4);
    free(tmpDefaultDeviceDnsIPv6);
    free(tmpDefaultSecondaryDeviceDnsIPv4);
    free(tmpDefaultSecondaryDeviceDnsIPv6);
    free(tmpDefaultDeviceTag);
    free(tmp_xdns_cache);
    free(xdns_cache_bkup);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, backup_xdns_cacheTest7)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));
    xdns_cache *xdns_cache_bkup = (xdns_cache *)malloc(sizeof(xdns_cache));

    char *tmpMacAddress = (char *)malloc(256);
    char *tmpDnsIPv4 = (char *)malloc(256);
    char *tmpDnsIPv6 = (char *)malloc(256);
    char *tmpTag = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultDeviceTag = (char *)malloc(256);

    tmp_xdns_cache->XdnsEnable = 1;
    tmp_xdns_cache->Tablecount = 1;
    strncpy(tmpMacAddress, "00:00:00:00:00:00", 256);
    strncpy(tmpDnsIPv4, "75.75.75.30", 256);
    strncpy(tmpDnsIPv6, "2001:558:feed::1", 256);
    strncpy(tmpTag, "TestTag", 256);
    strncpy(tmpDefaultDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultDeviceTag, "TestTag", 256);

    strncpy(tmp_xdns_cache->XDNSTableList[0].MacAddress, tmpMacAddress, sizeof(tmp_xdns_cache->XDNSTableList[0].MacAddress));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv4, tmpDnsIPv4, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv4));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv6, tmpDnsIPv6, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv6));
    strncpy(tmp_xdns_cache->XDNSTableList[0].Tag, tmpTag, sizeof(tmp_xdns_cache->XDNSTableList[0].Tag));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmpDefaultDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv6, tmpDefaultDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4, tmpDefaultSecondaryDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6, tmpDefaultSecondaryDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultDeviceTag, tmpDefaultDeviceTag, sizeof(tmp_xdns_cache->DefaultDeviceTag));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(7)
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    xdns_cache_bkup->XdnsEnable = tmp_xdns_cache->XdnsEnable;
    xdns_cache_bkup->Tablecount = tmp_xdns_cache->Tablecount;

    backup_xdns_cache(tmp_xdns_cache, xdns_cache_bkup);

    EXPECT_EQ(1, xdns_cache_bkup->XdnsEnable);
    EXPECT_EQ(1, xdns_cache_bkup->Tablecount);

    free(tmpMacAddress);
    free(tmpDnsIPv4);
    free(tmpDnsIPv6);
    free(tmpTag);
    free(tmpDefaultDeviceDnsIPv4);
    free(tmpDefaultDeviceDnsIPv6);
    free(tmpDefaultSecondaryDeviceDnsIPv4);
    free(tmpDefaultSecondaryDeviceDnsIPv6);
    free(tmpDefaultDeviceTag);
    free(tmp_xdns_cache);
    free(xdns_cache_bkup);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, backup_xdns_cacheTest8)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));
    xdns_cache *xdns_cache_bkup = (xdns_cache *)malloc(sizeof(xdns_cache));

    char *tmpMacAddress = (char *)malloc(256);
    char *tmpDnsIPv4 = (char *)malloc(256);
    char *tmpDnsIPv6 = (char *)malloc(256);
    char *tmpTag = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultDeviceTag = (char *)malloc(256);

    tmp_xdns_cache->XdnsEnable = 1;
    tmp_xdns_cache->Tablecount = 1;
    strncpy(tmpMacAddress, "00:00:00:00:00:00", 256);
    strncpy(tmpDnsIPv4, "75.75.75.30", 256);
    strncpy(tmpDnsIPv6, "2001:558:feed::1", 256);
    strncpy(tmpTag, "TestTag", 256);
    strncpy(tmpDefaultDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultDeviceTag, "TestTag", 256);

    strncpy(tmp_xdns_cache->XDNSTableList[0].MacAddress, tmpMacAddress, sizeof(tmp_xdns_cache->XDNSTableList[0].MacAddress));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv4, tmpDnsIPv4, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv4));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv6, tmpDnsIPv6, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv6));
    strncpy(tmp_xdns_cache->XDNSTableList[0].Tag, tmpTag, sizeof(tmp_xdns_cache->XDNSTableList[0].Tag));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmpDefaultDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv6, tmpDefaultDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4, tmpDefaultSecondaryDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6, tmpDefaultSecondaryDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultDeviceTag, tmpDefaultDeviceTag, sizeof(tmp_xdns_cache->DefaultDeviceTag));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(8)
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    xdns_cache_bkup->XdnsEnable = tmp_xdns_cache->XdnsEnable;
    xdns_cache_bkup->Tablecount = tmp_xdns_cache->Tablecount;

    backup_xdns_cache(tmp_xdns_cache, xdns_cache_bkup);

    EXPECT_EQ(1, xdns_cache_bkup->XdnsEnable);
    EXPECT_EQ(1, xdns_cache_bkup->Tablecount);

    free(tmpMacAddress);
    free(tmpDnsIPv4);
    free(tmpDnsIPv6);
    free(tmpTag);
    free(tmpDefaultDeviceDnsIPv4);
    free(tmpDefaultDeviceDnsIPv6);
    free(tmpDefaultSecondaryDeviceDnsIPv4);
    free(tmpDefaultSecondaryDeviceDnsIPv6);
    free(tmpDefaultDeviceTag);
    free(tmp_xdns_cache);
    free(xdns_cache_bkup);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, backup_xdns_cacheTest9)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));
    xdns_cache *xdns_cache_bkup = (xdns_cache *)malloc(sizeof(xdns_cache));


    char *tmpMacAddress = (char *)malloc(256);
    char *tmpDnsIPv4 = (char *)malloc(256);
    char *tmpDnsIPv6 = (char *)malloc(256);
    char *tmpTag = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultDeviceTag = (char *)malloc(256);

    strncpy(tmpMacAddress, "00:00:00:00:00:00", 256);
    strncpy(tmpDnsIPv4, "75.75.75.30", 256);
    strncpy(tmpDnsIPv6, "2001:558:feed::1", 256);
    strncpy(tmpTag, "TestTag", 256);
    strncpy(tmpDefaultDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultDeviceTag, "TestTag", 256);

    strncpy(tmp_xdns_cache->XDNSTableList[0].MacAddress, tmpMacAddress, sizeof(tmp_xdns_cache->XDNSTableList[0].MacAddress));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv4, tmpDnsIPv4, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv4));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv6, tmpDnsIPv6, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv6));
    strncpy(tmp_xdns_cache->XDNSTableList[0].Tag, tmpTag, sizeof(tmp_xdns_cache->XDNSTableList[0].Tag));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmpDefaultDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv6, tmpDefaultDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4, tmpDefaultSecondaryDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6, tmpDefaultSecondaryDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultDeviceTag, tmpDefaultDeviceTag, sizeof(tmp_xdns_cache->DefaultDeviceTag));

    tmp_xdns_cache->XdnsEnable = 1;
    tmp_xdns_cache->Tablecount = 1;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(9)
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    xdns_cache_bkup->XdnsEnable = tmp_xdns_cache->XdnsEnable;
    xdns_cache_bkup->Tablecount = tmp_xdns_cache->Tablecount;

    backup_xdns_cache(tmp_xdns_cache, xdns_cache_bkup);

    EXPECT_EQ(1, xdns_cache_bkup->XdnsEnable);
    EXPECT_EQ(1, xdns_cache_bkup->Tablecount);

    free(tmpMacAddress);
    free(tmpDnsIPv4);
    free(tmpDnsIPv6);
    free(tmpTag);
    free(tmpDefaultDeviceDnsIPv4);
    free(tmpDefaultDeviceDnsIPv6);
    free(tmpDefaultSecondaryDeviceDnsIPv4);
    free(tmpDefaultSecondaryDeviceDnsIPv6);
    free(tmpDefaultDeviceTag);
    free(tmp_xdns_cache);
    free(xdns_cache_bkup);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, print_xdns_cacheTest)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));
    tmp_xdns_cache->XdnsEnable = 1;
    tmp_xdns_cache->Tablecount = 1;

    char *tmpMacAddress = (char *)malloc(256);
    char *tmpDnsIPv4 = (char *)malloc(256);
    char *tmpDnsIPv6 = (char *)malloc(256);
    char *tmpTag = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultDeviceTag = (char *)malloc(256);

    strncpy(tmpMacAddress, "00:00:00:00:00:00", 256);
    strncpy(tmpDnsIPv4, "75.75.75.30", 256);
    strncpy(tmpDnsIPv6, "2001:558:feed::1", 256);
    strncpy(tmpTag, "TestTag", 256);
    strncpy(tmpDefaultDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultDeviceTag, "TestTag", 256);

    strncpy(tmp_xdns_cache->XDNSTableList[0].MacAddress, tmpMacAddress, sizeof(tmp_xdns_cache->XDNSTableList[0].MacAddress));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv4, tmpDnsIPv4, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv4));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv6, tmpDnsIPv6, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv6));
    strncpy(tmp_xdns_cache->XDNSTableList[0].Tag, tmpTag, sizeof(tmp_xdns_cache->XDNSTableList[0].Tag));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmpDefaultDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv6, tmpDefaultDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4, tmpDefaultSecondaryDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6, tmpDefaultSecondaryDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultDeviceTag, tmpDefaultDeviceTag, sizeof(tmp_xdns_cache->DefaultDeviceTag));

    print_xdns_cache(tmp_xdns_cache);

    free(tmpMacAddress);
    free(tmpDnsIPv4);
    free(tmpDnsIPv6);
    free(tmpTag);
    free(tmpDefaultDeviceDnsIPv4);
    free(tmpDefaultDeviceDnsIPv6);
    free(tmpDefaultSecondaryDeviceDnsIPv4);
    free(tmpDefaultSecondaryDeviceDnsIPv6);
    free(tmpDefaultDeviceTag);
    free(tmp_xdns_cache);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, init_xdns_cacheTest)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->ulXDNSNextInstanceNumber = 2;

    char buf[5] = {0};
    char *pDefaultSecondaryDeviceDnsIPv4 = tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4;
    char *pDefaultSecondaryDeviceDnsIPv6 = tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6;
    char *pDefaultDeviceTag = tmp_xdns_cache->DefaultDeviceTag;
    int ret = 1;
    const char *DnsIPv4 = "75.75.75.30";
    const char *DnsIPv6 = "2001:558:feed::1";
    const char *UseRDKDefaultDeviceDnsIPv4 = "1270.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    const char *MacAddress = "00:00:00:00:00:00";
    const char *Tag = "TestTag";

    char router_mode[] = "3";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(xdns_load_dns_ip(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmp_xdns_cache->DefaultDeviceDnsIPv6, pMyObject->DefaultDeviceDnsIPv4, pMyObject->DefaultDeviceDnsIPv6), 0);

    int i = 0;
    PSINGLE_LINK_ENTRY pSListEntry = NULL;
    PCOSA_CONTEXT_XDNS_LINK_OBJECT pCxtLink = NULL;
    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));

    strncpy(pDnsTableEntry->MacAddress, MacAddress, sizeof(pDnsTableEntry->MacAddress));
    strncpy(pDnsTableEntry->DnsIPv4, DnsIPv4, sizeof(pDnsTableEntry->DnsIPv4));
    strncpy(pDnsTableEntry->DnsIPv6, DnsIPv6, sizeof(pDnsTableEntry->DnsIPv6));
    strncpy(pDnsTableEntry->Tag, Tag, sizeof(pDnsTableEntry->Tag));

    pSListEntry = (PSINGLE_LINK_ENTRY)malloc(sizeof(SINGLE_LINK_ENTRY));
    ASSERT_NE(pSListEntry, nullptr);

    pCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pCxtLink, nullptr);

    pCxtLink->hContext = pDnsTableEntry;
    AnscSListPushEntryByIndex(&pMyObject->XDNSDeviceList, pSListEntry, i);

    pSListEntry = AnscSListGetEntryByIndex(&pMyObject->XDNSDeviceList, i);
    char *pMacAddress = tmp_xdns_cache->XDNSTableList[i].MacAddress;
    char *pTag = tmp_xdns_cache->XDNSTableList[i].Tag;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(5)
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(2)
        .WillOnce(Return(0))
        .WillOnce(Return(0));

    init_xdns_cache(tmp_xdns_cache);

    EXPECT_EQ(0, tmp_xdns_cache->XdnsEnable);

    free(pDnsTableEntry);
    free(pSListEntry);
    free(pCxtLink);
    free(g_pCosaBEManager->hXdns);
    free(g_pCosaBEManager);
    free(tmp_xdns_cache);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, init_xdns_cacheTest2)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->ulXDNSNextInstanceNumber = 2;

    char buf[5] = {0};
    char *pDefaultSecondaryDeviceDnsIPv4 = tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4;
    char *pDefaultSecondaryDeviceDnsIPv6 = tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6;
    char *pDefaultDeviceTag = tmp_xdns_cache->DefaultDeviceTag;
    int ret = 1;
    const char *DnsIPv4 = "75.75.75.30";
    const char *DnsIPv6 = "2001:558:feed::1";
    const char *UseRDKDefaultDeviceDnsIPv4 = "1270.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    const char *MacAddress = "00:00:00:00:00:00";
    const char *Tag = "TestTag";

    char router_mode[] = "3";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(xdns_load_dns_ip(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmp_xdns_cache->DefaultDeviceDnsIPv6, pMyObject->DefaultDeviceDnsIPv4, pMyObject->DefaultDeviceDnsIPv6), 0);

    int i = 0;
    PSINGLE_LINK_ENTRY pSListEntry = NULL;
    PCOSA_CONTEXT_XDNS_LINK_OBJECT pCxtLink = NULL;
    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));

    strncpy(pDnsTableEntry->MacAddress, MacAddress, sizeof(pDnsTableEntry->MacAddress));
    strncpy(pDnsTableEntry->DnsIPv4, DnsIPv4, sizeof(pDnsTableEntry->DnsIPv4));
    strncpy(pDnsTableEntry->DnsIPv6, DnsIPv6, sizeof(pDnsTableEntry->DnsIPv6));
    strncpy(pDnsTableEntry->Tag, Tag, sizeof(pDnsTableEntry->Tag));

    pSListEntry = (PSINGLE_LINK_ENTRY)malloc(sizeof(SINGLE_LINK_ENTRY));
    ASSERT_NE(pSListEntry, nullptr);

    pCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pCxtLink, nullptr);

    pCxtLink->hContext = pDnsTableEntry;
    AnscSListPushEntryByIndex(&pMyObject->XDNSDeviceList, pSListEntry, i);

    pSListEntry = AnscSListGetEntryByIndex(&pMyObject->XDNSDeviceList, i);
    char *pMacAddress = tmp_xdns_cache->XDNSTableList[i].MacAddress;
    char *pTag = tmp_xdns_cache->XDNSTableList[i].Tag;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(2)
        .WillOnce(Return(0))
        .WillOnce(Return(0));

    init_xdns_cache(tmp_xdns_cache);

    EXPECT_EQ(0, tmp_xdns_cache->XdnsEnable);

    free(pDnsTableEntry);
    free(pSListEntry);
    free(pCxtLink);
    free(g_pCosaBEManager->hXdns);
    free(g_pCosaBEManager);
    free(tmp_xdns_cache);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, init_xdns_cacheTest3)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->ulXDNSNextInstanceNumber = 2;

    char buf[5] = {0};
    char *pDefaultSecondaryDeviceDnsIPv4 = tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4;
    char *pDefaultSecondaryDeviceDnsIPv6 = tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6;
    char *pDefaultDeviceTag = tmp_xdns_cache->DefaultDeviceTag;
    int ret = 1;
    const char *DnsIPv4 = "75.75.75.30";
    const char *DnsIPv6 = "2001:558:feed::1";
    const char *UseRDKDefaultDeviceDnsIPv4 = "1270.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    const char *MacAddress = "00:00:00:00:00:00";
    const char *Tag = "TestTag";

    char router_mode[] = "3";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(xdns_load_dns_ip(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmp_xdns_cache->DefaultDeviceDnsIPv6, pMyObject->DefaultDeviceDnsIPv4, pMyObject->DefaultDeviceDnsIPv6), 0);

    int i = 0;
    PSINGLE_LINK_ENTRY pSListEntry = NULL;
    PCOSA_CONTEXT_XDNS_LINK_OBJECT pCxtLink = NULL;
    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));

    strncpy(pDnsTableEntry->MacAddress, MacAddress, sizeof(pDnsTableEntry->MacAddress));
    strncpy(pDnsTableEntry->DnsIPv4, DnsIPv4, sizeof(pDnsTableEntry->DnsIPv4));
    strncpy(pDnsTableEntry->DnsIPv6, DnsIPv6, sizeof(pDnsTableEntry->DnsIPv6));
    strncpy(pDnsTableEntry->Tag, Tag, sizeof(pDnsTableEntry->Tag));

    pSListEntry = (PSINGLE_LINK_ENTRY)malloc(sizeof(SINGLE_LINK_ENTRY));
    ASSERT_NE(pSListEntry, nullptr);

    pCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pCxtLink, nullptr);

    pCxtLink->hContext = pDnsTableEntry;
    AnscSListPushEntryByIndex(&pMyObject->XDNSDeviceList, pSListEntry, i);

    pSListEntry = AnscSListGetEntryByIndex(&pMyObject->XDNSDeviceList, i);
    char *pMacAddress = tmp_xdns_cache->XDNSTableList[i].MacAddress;
    char *pTag = tmp_xdns_cache->XDNSTableList[i].Tag;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(3)
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(2)
        .WillOnce(Return(0))
        .WillOnce(Return(0));

    init_xdns_cache(tmp_xdns_cache);

    EXPECT_EQ(0, tmp_xdns_cache->XdnsEnable);

    free(pDnsTableEntry);
    free(pSListEntry);
    free(pCxtLink);
    free(g_pCosaBEManager->hXdns);
    free(g_pCosaBEManager);
    free(tmp_xdns_cache);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, init_xdns_cacheTest4)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->ulXDNSNextInstanceNumber = 2;

    char buf[5] = {0};
    char *pDefaultSecondaryDeviceDnsIPv4 = tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4;
    char *pDefaultSecondaryDeviceDnsIPv6 = tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6;
    char *pDefaultDeviceTag = tmp_xdns_cache->DefaultDeviceTag;
    int ret = 1;
    const char *DnsIPv4 = "75.75.75.30";
    const char *DnsIPv6 = "2001:558:feed::1";
    const char *UseRDKDefaultDeviceDnsIPv4 = "1270.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    const char *MacAddress = "00:00:00:00:00:00";
    const char *Tag = "TestTag";

    char router_mode[] = "3";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(xdns_load_dns_ip(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmp_xdns_cache->DefaultDeviceDnsIPv6, pMyObject->DefaultDeviceDnsIPv4, pMyObject->DefaultDeviceDnsIPv6), 0);

    int i = 0;
    PSINGLE_LINK_ENTRY pSListEntry = NULL;
    PCOSA_CONTEXT_XDNS_LINK_OBJECT pCxtLink = NULL;
    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));

    strncpy(pDnsTableEntry->MacAddress, MacAddress, sizeof(pDnsTableEntry->MacAddress));
    strncpy(pDnsTableEntry->DnsIPv4, DnsIPv4, sizeof(pDnsTableEntry->DnsIPv4));
    strncpy(pDnsTableEntry->DnsIPv6, DnsIPv6, sizeof(pDnsTableEntry->DnsIPv6));
    strncpy(pDnsTableEntry->Tag, Tag, sizeof(pDnsTableEntry->Tag));

    pSListEntry = (PSINGLE_LINK_ENTRY)malloc(sizeof(SINGLE_LINK_ENTRY));
    ASSERT_NE(pSListEntry, nullptr);

    pCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pCxtLink, nullptr);

    pCxtLink->hContext = pDnsTableEntry;
    AnscSListPushEntryByIndex(&pMyObject->XDNSDeviceList, pSListEntry, i);

    pSListEntry = AnscSListGetEntryByIndex(&pMyObject->XDNSDeviceList, i);
    char *pMacAddress = tmp_xdns_cache->XDNSTableList[i].MacAddress;
    char *pTag = tmp_xdns_cache->XDNSTableList[i].Tag;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(4)
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(2)
        .WillOnce(Return(0))
        .WillOnce(Return(0));

    init_xdns_cache(tmp_xdns_cache);

    EXPECT_EQ(0, tmp_xdns_cache->XdnsEnable);

    free(pDnsTableEntry);
    free(pSListEntry);
    free(pCxtLink);
    free(g_pCosaBEManager->hXdns);
    free(g_pCosaBEManager);
    free(tmp_xdns_cache);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, init_xdns_cacheTest5)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->ulXDNSNextInstanceNumber = 2;

    char buf[5] = {0};
    char *pDefaultSecondaryDeviceDnsIPv4 = tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4;
    char *pDefaultSecondaryDeviceDnsIPv6 = tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6;
    char *pDefaultDeviceTag = tmp_xdns_cache->DefaultDeviceTag;
    int ret = 1;
    const char *DnsIPv4 = "75.75.75.30";
    const char *DnsIPv6 = "2001:558:feed::1";
    const char *UseRDKDefaultDeviceDnsIPv4 = "1270.0.0.1";
    const char *UseRDKDefaultDeviceDnsIPv6 = "::1";
    const char *MacAddress = "00:00:00:00:00:00";
    const char *Tag = "TestTag";

    char router_mode[] = "3";

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("last_erouter_mode"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(router_mode, router_mode + sizeof(router_mode)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(xdns_load_dns_ip(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmp_xdns_cache->DefaultDeviceDnsIPv6, pMyObject->DefaultDeviceDnsIPv4, pMyObject->DefaultDeviceDnsIPv6), 0);

    int i = 0;
    PSINGLE_LINK_ENTRY pSListEntry = NULL;
    PCOSA_CONTEXT_XDNS_LINK_OBJECT pCxtLink = NULL;
    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));

    strncpy(pDnsTableEntry->MacAddress, MacAddress, sizeof(pDnsTableEntry->MacAddress));
    strncpy(pDnsTableEntry->DnsIPv4, DnsIPv4, sizeof(pDnsTableEntry->DnsIPv4));
    strncpy(pDnsTableEntry->DnsIPv6, DnsIPv6, sizeof(pDnsTableEntry->DnsIPv6));
    strncpy(pDnsTableEntry->Tag, Tag, sizeof(pDnsTableEntry->Tag));

    pSListEntry = (PSINGLE_LINK_ENTRY)malloc(sizeof(SINGLE_LINK_ENTRY));
    ASSERT_NE(pSListEntry, nullptr);

    pCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pCxtLink, nullptr);

    pCxtLink->hContext = pDnsTableEntry;
    AnscSListPushEntryByIndex(&pMyObject->XDNSDeviceList, pSListEntry, i);

    pSListEntry = AnscSListGetEntryByIndex(&pMyObject->XDNSDeviceList, i);
    char *pMacAddress = tmp_xdns_cache->XDNSTableList[i].MacAddress;
    char *pTag = tmp_xdns_cache->XDNSTableList[i].Tag;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(5)
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(2)
        .WillOnce(Return(0))
        .WillOnce(Return(0));


    init_xdns_cache(tmp_xdns_cache);

    EXPECT_EQ(0, tmp_xdns_cache->XdnsEnable);

    free(pDnsTableEntry);
    free(pSListEntry);
    free(pCxtLink);
    free(g_pCosaBEManager->hXdns);
    free(g_pCosaBEManager);
    free(tmp_xdns_cache);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, webConfigFrameworkInitTest)
{
    char *sub_docs[SUBDOC_COUNT + 1] = {(char *)"xdns", (char *)0};

    blobRegInfo *blobData;

    blobData = (blobRegInfo *)malloc(SUBDOC_COUNT * sizeof(blobRegInfo));
    ASSERT_NE(blobData, nullptr);

    EXPECT_CALL(*g_webconfigFwMock, register_sub_docs(_, _, _, _))
        .Times(1);

    webConfigFrameworkInit();

    free(blobData);
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, apply_XDNS_cache_ToDBTest)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));
    ASSERT_NE(tmp_xdns_cache, nullptr);

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->ulXDNSNextInstanceNumber = 2;

    char *tmpMacAddress = (char *)malloc(256);
    char *tmpDnsIPv4 = (char *)malloc(256);
    char *tmpDnsIPv6 = (char *)malloc(256);
    char *tmpTag = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultDeviceTag = (char *)malloc(256);

    strncpy(tmpMacAddress, "00:00:00:00:00:00", 256);
    strncpy(tmpDnsIPv4, "75.75.75.30", 256);
    strncpy(tmpDnsIPv6, "2001:558:feed::1", 256);
    strncpy(tmpTag, "TestTag", 256);
    strncpy(tmpDefaultDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultDeviceTag, "TestTag", 256);

    strncpy(tmp_xdns_cache->XDNSTableList[0].MacAddress, tmpMacAddress, sizeof(tmp_xdns_cache->XDNSTableList[0].MacAddress));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv4, tmpDnsIPv4, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv4));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv6, tmpDnsIPv6, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv6));
    strncpy(tmp_xdns_cache->XDNSTableList[0].Tag, tmpTag, sizeof(tmp_xdns_cache->XDNSTableList[0].Tag));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmpDefaultDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv6, tmpDefaultDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4, tmpDefaultSecondaryDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6, tmpDefaultSecondaryDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultDeviceTag, tmpDefaultDeviceTag, sizeof(tmp_xdns_cache->DefaultDeviceTag));

    FILE* fp = NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp));

    EXPECT_NE(apply_XDNS_cache_ToDB(tmp_xdns_cache), 0);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
    free(tmp_xdns_cache);
    tmp_xdns_cache = NULL;
}

TEST_F(CcspXdnsCosaWebconfigApiTestFixture, apply_XDNS_cache_ToDBTest2)
{
    xdns_cache *tmp_xdns_cache = (xdns_cache *)malloc(sizeof(xdns_cache));
    ASSERT_NE(tmp_xdns_cache, nullptr);

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(g_pCosaBEManager->hXdns, nullptr);

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    pMyObject->ulXDNSNextInstanceNumber = 2;

    char *tmpMacAddress = (char *)malloc(256);
    char *tmpDnsIPv4 = (char *)malloc(256);
    char *tmpDnsIPv6 = (char *)malloc(256);
    char *tmpTag = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv4 = (char *)malloc(256);
    char *tmpDefaultSecondaryDeviceDnsIPv6 = (char *)malloc(256);
    char *tmpDefaultDeviceTag = (char *)malloc(256);

    strncpy(tmpMacAddress, "00:00:00:00:00:00", 256);
    strncpy(tmpDnsIPv4, "75.75.75.30", 256);
    strncpy(tmpDnsIPv6, "2001:558:feed::1", 256);
    strncpy(tmpTag, "TestTag", 256);
    strncpy(tmpDefaultDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv4, "192.168.1.2", 256);
    strncpy(tmpDefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", 256);
    strncpy(tmpDefaultDeviceTag, "TestTag", 256);

    strncpy(tmp_xdns_cache->XDNSTableList[0].MacAddress, tmpMacAddress, sizeof(tmp_xdns_cache->XDNSTableList[0].MacAddress));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv4, tmpDnsIPv4, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv4));
    strncpy(tmp_xdns_cache->XDNSTableList[0].DnsIPv6, tmpDnsIPv6, sizeof(tmp_xdns_cache->XDNSTableList[0].DnsIPv6));
    strncpy(tmp_xdns_cache->XDNSTableList[0].Tag, tmpTag, sizeof(tmp_xdns_cache->XDNSTableList[0].Tag));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmpDefaultDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultDeviceDnsIPv6, tmpDefaultDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4, tmpDefaultSecondaryDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4));
    strncpy(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6, tmpDefaultSecondaryDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6));
    strncpy(tmp_xdns_cache->DefaultDeviceTag, tmpDefaultDeviceTag, sizeof(tmp_xdns_cache->DefaultDeviceTag));

    FILE* fp = (FILE *)0xffffffff;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1);

    EXPECT_NE(apply_XDNS_cache_ToDB(tmp_xdns_cache), 0);

    free(g_pCosaBEManager->hXdns);
    g_pCosaBEManager->hXdns = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
    free(tmp_xdns_cache);
    tmp_xdns_cache = NULL;
}