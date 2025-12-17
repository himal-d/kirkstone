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

class CcspXdnsCosaApisTestFixture : public ::testing::Test {
protected:
    void SetUp() override
    {
        g_syscfgMock = new SyscfgMock();
        g_safecLibMock = new SafecLibMock();
        g_syseventMock = new SyseventMock();
        g_rbusMock = new rbusMock();
        g_fileIOMock = new FileIOMock();
    }

    void TearDown() override
    {
        delete g_syscfgMock;
        delete g_safecLibMock;
        delete g_syseventMock;
        delete g_rbusMock;
        delete g_fileIOMock;

        g_syscfgMock = nullptr;
        g_safecLibMock = nullptr;
        g_syseventMock = nullptr;
        g_rbusMock = nullptr;
        g_fileIOMock = nullptr;
    }
};

// Unit Test for cosa_xdns_apis.c file

ACTION_TEMPLATE(SetArgNPointeeTo, HAS_1_TEMPLATE_PARAMS(unsigned, uIndex), AND_2_VALUE_PARAMS(pData, uiDataSize))
{
    memcpy(std::get<uIndex>(args), pData, uiDataSize);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_xdns_sysevent_init)
{
    errno_t rc = -1;

    EXPECT_CALL(*g_syseventMock, sysevent_open(_, _, _, StrEq("xdns"), _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_CALL(*g_syseventMock, sysevent_set_options(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syseventMock, sysevent_setnotification(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    rc = xdns_sysevent_init();
    EXPECT_EQ(SYS_EVENT_OK, rc);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_xdns_sysevent_init2)
{
    errno_t rc = -1;

    EXPECT_CALL(*g_syseventMock, sysevent_open(_, _, _, StrEq("xdns"), _))
        .Times(1)
        .WillOnce(Return(-1));

    EXPECT_CALL(*g_syseventMock, sysevent_set_options(_, _, _, _))
        .Times(1)
        .WillOnce(Return(-1));

    EXPECT_CALL(*g_syseventMock, sysevent_setnotification(_, _, _, _))
        .Times(1)
        .WillOnce(Return(-1));

    rc = xdns_sysevent_init();
    EXPECT_EQ(SYS_EVENT_ERROR, rc);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_xdns_handle_sysevent_notification)
{
    char event[] = "current_wan_ifname";
    char val[] = "erouter0";
    int comparisonResult = 0;
    char buf[] = "1";
    FILE *fp1 = NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp1));

    EXPECT_CALL(*g_syseventMock, sysevent_set(_, _, StrEq("firewall-restart"), _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, StrEq(val), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("current_wan_ifname"), strlen("current_wan_ifname"), StrEq(event), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(get_xdnsSysEvent_type_from_name(event, 0), 0);

    xdns_handle_sysevent_notification(event, val);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_xdns_handle_sysevent_notification2)
{
    char event[] = "current_wan_ifname";
    char val[] = "erouter0";
    int comparisonResult = 0;
    char buf[] = "1";
    FILE *fp1 = NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp1));

    EXPECT_CALL(*g_syseventMock, sysevent_set(_, _, StrEq("firewall-restart"), _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, StrEq(val), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("current_wan_ifname"), strlen("current_wan_ifname"), StrEq(event), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(get_xdnsSysEvent_type_from_name(event, 0), 0);

    xdns_handle_sysevent_notification(event, val);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_xdns_handle_sysevent_notification3)
{
    char event[] = "current_wan_ifname";
    char val[] = "erouter1";
    int comparisonResult = 0;
    char buf[] = "1";
    FILE *fp1 = NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp1));

    EXPECT_CALL(*g_syseventMock, sysevent_set(_, _, StrEq("firewall-restart"), _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, StrEq(val), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("current_wan_ifname"), strlen("current_wan_ifname"), StrEq(event), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(get_xdnsSysEvent_type_from_name(event, 0), 0);

    xdns_handle_sysevent_notification(event, val);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_xdns_handle_sysevent_notification4)
{
    char event[] = "current_wan_ifname";
    char val[] = "erouter1";
    int comparisonResult = 0;
    char buf[] = "1";
    FILE *fp1 = NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp1));

    EXPECT_CALL(*g_syseventMock, sysevent_set(_, _, StrEq("firewall-restart"), _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, StrEq(val), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("current_wan_ifname"), strlen("current_wan_ifname"), StrEq(event), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(get_xdnsSysEvent_type_from_name(event, 0), 0);

    xdns_handle_sysevent_notification(event, val);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_xdns_handle_sysevent_notification5)
{
    char event[] = "current_wan_ifname";
    char val[] = "erouter1";
    int comparisonResult = 0;
    char buf[] = "1";
    FILE *fp1 = NULL;

    char xdnsflag[20] = {0};

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(1)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, StrEq(val), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("current_wan_ifname"), strlen("current_wan_ifname"), StrEq(event), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(get_xdnsSysEvent_type_from_name(event, 0), 0);

    xdns_handle_sysevent_notification(event, val);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_xdns_handle_sysevent_notification6)
{
    char event[] = "current_wan_ifname";
    char val[] = "erouter1";
    int comparisonResult = 0;
    char buf[] = "0";
    FILE *fp1 = NULL;

    char xdnsflag[20] = {0};

    xdnsflag[1] = '\0';

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, StrEq(val), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("current_wan_ifname"), strlen("current_wan_ifname"), StrEq(event), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(get_xdnsSysEvent_type_from_name(event, 0), 0);

    xdns_handle_sysevent_notification(event, val);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_xdns_handle_sysevent_notification7)
{
    char event[] = "current_wan_ifname";
    char val[] = "erouter1";
    int comparisonResult = 0;
    char buf[] = "3";
    FILE *fp1 = NULL;

    char xdnsflag[20] = {0};

    xdnsflag[1] = '2';

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, StrEq(val), _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("current_wan_ifname"), strlen("current_wan_ifname"), StrEq(event), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(get_xdnsSysEvent_type_from_name(event, 0), 0);

    xdns_handle_sysevent_notification(event, val);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_xdns_sysvent_listener)
{
    int ret = SYS_EVENT_TIMEOUT;
    char name[256], val[256];
    int namelen = sizeof(name);
    int vallen = sizeof(val);
    int err = 0;
    async_id_t getnotification_asyncid;

    EXPECT_CALL(*g_syseventMock, sysevent_getnotification(_, _, _, _, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(_, _, _, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    ret = xdns_sysvent_listener();
    EXPECT_EQ(SYS_EVENT_RECEIVED, ret);

}

TEST_F(CcspXdnsCosaApisTestFixture, test_xdns_sysvent_listener2)
{
    int ret = SYS_EVENT_TIMEOUT;
    char name[256], val[256];
    int namelen = sizeof(name);
    int vallen = sizeof(val);
    int err = 0;
    async_id_t getnotification_asyncid;

    EXPECT_CALL(*g_syseventMock, sysevent_getnotification(_, _, _, _, _, _, _))
        .Times(1)
        .WillOnce(Return(1));

    ret = xdns_sysvent_listener();
    EXPECT_EQ(SYS_EVENT_TIMEOUT, ret);

}

TEST_F(CcspXdnsCosaApisTestFixture, test_xdns_sysvent_close)
{
    int ret = SYS_EVENT_OK;

    EXPECT_CALL(*g_syseventMock, sysevent_rmnotification(_, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syseventMock, sysevent_close(_, _))
        .Times(1)
        .WillOnce(Return(0));

    ret = xdns_sysvent_close();
    EXPECT_EQ(SYS_EVENT_OK, ret);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_xdns_check_sysevent_status)
{
    int fd = 0;
    token_t token = 0;
    int returnStatus = ANSC_STATUS_SUCCESS;

    returnStatus = xdns_check_sysevent_status(fd, token);
    EXPECT_EQ(ANSC_STATUS_SUCCESS, returnStatus);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_xdns_handle_sysevent_async)
{
    BOOL XDNSSysEventHandlerStarted = FALSE;
    xdns_handle_sysevent_async();
}

TEST_F(CcspXdnsCosaApisTestFixture, test_xdns_handle_sysevent_async2)
{
    BOOL XDNSSysEventHandlerStarted = TRUE;
    xdns_handle_sysevent_async();
}

TEST_F(CcspXdnsCosaApisTestFixture, test_GetDnsMasqFileEntry1)
{
    char macaddress[] = "00:00:00:00:00:00";
    char defaultEntry[MAX_BUF_SIZE][MAX_BUF_SIZE] = {0};
    int count = 3;
    char dnsmasqConfEntry[256] = {0};
    errno_t rc = -1;

    FILE *fp1 = NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp1));

    strncpy(defaultEntry[0], "dnsoverride a6:83:e7:76:52:eb 75.75.75.30 2001:558:feed::7530", MAX_BUF_SIZE - 1);
    strncpy(defaultEntry[1], "dnsoverride a4:83:e7:76:52:eb 75.75.75.30 2001:558:feed::7530", MAX_BUF_SIZE - 1);
    strncpy(defaultEntry[2], "dnsoverride 28:f1:0e:12:a1:a4 75.75.75.30 2001:558:feed::7530", MAX_BUF_SIZE - 1);

    GetDnsMasqFileEntry(macaddress, defaultEntry);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_GetDnsMasqFileEntry2)
{
    char macaddress[] = "00:00:00:00:00:00";
    char defaultEntry[MAX_BUF_SIZE][MAX_BUF_SIZE] = {0};
    int count = 3;
    char dnsmasqConfEntry[256] = {0};
    errno_t rc = -1;
    char buff[64] = {0};

    FILE *fp = (FILE *)0xffffffff;

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

    strncpy(defaultEntry[0], "dnsoverride a6:83:e7:76:52:eb 75.75.75.30 2001:558:feed::7530", MAX_BUF_SIZE - 1);
    strncpy(defaultEntry[1], "dnsoverride a4:83:e7:76:52:eb 75.75.75.30 2001:558:feed::7530", MAX_BUF_SIZE - 1);
    strncpy(defaultEntry[2], "dnsoverride 28:f1:0e:12:a1:a4 75.75.75.30 2001:558:feed::7530", MAX_BUF_SIZE - 1);

    GetDnsMasqFileEntry(macaddress, defaultEntry);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_GetDnsMasqFileEntry3)
{
    char macaddress[] = "00:00:00:00:00:00";
    char defaultEntry[MAX_BUF_SIZE][MAX_BUF_SIZE] = {0};
    int count = 3;
    char dnsmasqConfEntry[256] = {0};
    errno_t rc = -1;
    char buff[64] = {0};

    FILE *fp = (FILE *)0xffffffff;

    strcpy(dnsmasqConfEntry, "dnsoverride a6:83:e7:76:52:eb 75.75.75.30 2001:558:feed::7530");
    char *ptr = dnsmasqConfEntry;

    strncpy(defaultEntry[0], "dnsoverride a6:83:e7:76:52:eb 75.75.75.30 2001:558:feed::7530", MAX_BUF_SIZE - 1);
    strncpy(defaultEntry[1], "dnsoverride a4:83:e7:76:52:eb 75.75.75.30 2001:558:feed::7530", MAX_BUF_SIZE - 1);
    strncpy(defaultEntry[2], "dnsoverride 28:f1:0e:12:a1:a4 75.75.75.30 2001:558:feed::7530", MAX_BUF_SIZE - 1);

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

    GetDnsMasqFileEntry(macaddress, defaultEntry);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_RefreshResolvConfEntry)
{
    char xdnsflag[] = "1";
    char dnsmasqConfEntry[256] = {0};
    char resolvConfEntry[256] = {0};
    char buf[] = "1";

    FILE *fp1 = NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp1));

    EXPECT_CALL(*g_fileIOMock, unlink(_))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    RefreshResolvConfEntry();
}

TEST_F(CcspXdnsCosaApisTestFixture, test_RefreshResolvConfEntry2)
{
    char xdnsflag[] = "0";
    char dnsmasqConfEntry[256] = {0};
    char resolvConfEntry[256] = {0};
    char buf[] = "1";

    FILE *fp1 = NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp1));

    EXPECT_CALL(*g_fileIOMock, unlink(_))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    RefreshResolvConfEntry();
}

TEST_F(CcspXdnsCosaApisTestFixture, test_RefreshResolvConfEntry3)
{
    char xdnsflag[] = "0";
    char dnsmasqConfEntry[256] = {0};
    char resolvConfEntry[256] = {0};
    char buff[] = "1";

    FILE *fp = (FILE *)0xffffffff;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(5)
        .WillRepeatedly(Return(fp));

    EXPECT_CALL(*g_fileIOMock, fgets(_, _, fp))
        .Times(3);

    EXPECT_CALL(*g_fileIOMock, fclose(_))
        .Times(5)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_fileIOMock, unlink(_))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buff, buff + sizeof(buff)), Return(0)));

    RefreshResolvConfEntry();
}

TEST_F(CcspXdnsCosaApisTestFixture, test_ReplaceDnsmasqConfEntry)
{
    char macaddress[] = "";
    char overrideEntry[MAX_BUF_SIZE][MAX_BUF_SIZE] = {0};
    char dnsmasqConfEntry[256] = {0};
    int count = 0;

    ReplaceDnsmasqConfEntry(macaddress, overrideEntry, count);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_ReplaceDnsmasqConfEntry2)
{
    char macaddress[] = "";
    char overrideEntry[MAX_BUF_SIZE][MAX_BUF_SIZE] = {0};
    char dnsmasqConfEntry[256] = {0};
    int count = 300;

    ReplaceDnsmasqConfEntry(macaddress, overrideEntry, count);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_ReplaceDnsmasqConfEntry3)
{
    char macaddress[] = "00:00:00:00:00:00";
    char overrideEntry[MAX_BUF_SIZE][MAX_BUF_SIZE] = {0};
    char dnsmasqConfEntry[256] = {0};
    int count = 3;
    char buf[] = "1";
    FILE *fp1 = NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(3)
        .WillRepeatedly(Return(fp1));

    EXPECT_CALL(*g_fileIOMock, unlink(_))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    ReplaceDnsmasqConfEntry(macaddress, overrideEntry, count);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_ReplaceDnsmasqConfEntry4)
{
    char macaddress[] = "00:00:00:00:00:00";
    char overrideEntry[MAX_BUF_SIZE][MAX_BUF_SIZE] = {0};
    char dnsmasqConfEntry[256] = {0};
    int count = 3;
    char buf[] = "1";
    FILE *fp = (FILE *)0xffffffff;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(7)
        .WillRepeatedly(Return(fp));

    EXPECT_CALL(*g_fileIOMock, fgets(_, _, fp))
        .Times(4);

    EXPECT_CALL(*g_fileIOMock, fclose(_))
        .Times(7)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_fileIOMock, unlink(_))
        .Times(3)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    ReplaceDnsmasqConfEntry(macaddress, overrideEntry, count);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_AppendDnsmasqConfEntry)
{
    char string1[MAX_BUF_SIZE][MAX_BUF_SIZE] = {0};
    int count = 0;

    FILE *fp2 = NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp2));

    AppendDnsmasqConfEntry(string1, count);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_AppendDnsmasqConfEntry2)
{
    char string1[MAX_BUF_SIZE][MAX_BUF_SIZE] = {0};
    int count = 3;

    FILE *fp2 = NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp2));

    AppendDnsmasqConfEntry(string1, count);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_AppendDnsmasqConfEntry3)
{
    char string1[MAX_BUF_SIZE][MAX_BUF_SIZE] = {0};
    int count = 3;

    FILE *fp = (FILE *)0xffffffff;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1);

    AppendDnsmasqConfEntry(string1, count);
}


TEST_F(CcspXdnsCosaApisTestFixture, test_CreateDnsmasqServerConf)
{
    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)AnscAllocateMemory(sizeof(COSA_DATAMODEL_XDNS));
    char resolvConfEntry[256] = {0};
    char buf[256] = {0};
    char dnsmasqConfOverrideEntry[MAX_XDNS_SERV][MAX_BUF_SIZE] = {{0,0}};
    char tokenIPv4[256] = {0};
    char tokenIPv6[256] = {0};

    FILE *fp1 = NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp1));

    CreateDnsmasqServerConf(pMyObject);

    free(pMyObject);
    pMyObject = NULL;
}

TEST_F(CcspXdnsCosaApisTestFixture, test_CreateDnsmasqServerConf2)
{
    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)AnscAllocateMemory(sizeof(COSA_DATAMODEL_XDNS));
    char resolvConfEntry[256] = "nameserver 75.75.75.30\nnameserver 2001:558:feed::7530\n";
    char buff[256] = {0};
    char dnsmasqConfOverrideEntry[MAX_XDNS_SERV][MAX_BUF_SIZE] = {{0,0}};
    char tokenIPv4[256] = {0};
    char tokenIPv6[256] = {0};

    FILE *fp = (FILE *)0xffffffff;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp));

    EXPECT_CALL(*g_fileIOMock, fgets(_, _, fp))
        .Times(2)
        .WillOnce(::testing::DoAll(
            SetArgNPointeeTo<0>(std::begin(buff), sizeof(buff)),
            ::testing::Return((char*)buff)
        ))
        .WillOnce(::testing::ReturnNull());

    EXPECT_CALL(*g_fileIOMock, fclose(_))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(5)
        .WillRepeatedly(Return(0));

    CreateDnsmasqServerConf(pMyObject);

    free(pMyObject);
    pMyObject = NULL;
}


TEST_F(CcspXdnsCosaApisTestFixture, test_FillEntryInList)
{
    PCOSA_DATAMODEL_XDNS pXdns = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(pXdns, nullptr);

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY dnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(dnsTableEntry, nullptr);


    PCOSA_CONTEXT_XDNS_LINK_OBJECT pXdnsCxtLink = NULL;

    pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)AnscAllocateMemory(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));
    ASSERT_NE(pXdnsCxtLink, nullptr);


    pXdnsCxtLink->InstanceNumber =  pXdns->ulXDNSNextInstanceNumber;
    dnsTableEntry->InstanceNumber =  pXdns->ulXDNSNextInstanceNumber;

    pXdns->ulXDNSNextInstanceNumber++;

    pXdnsCxtLink->hContext = (ANSC_HANDLE)dnsTableEntry;

    FillEntryInList(pXdns, dnsTableEntry);

    free(pXdns);
    pXdns = NULL;
    free(dnsTableEntry);
    dnsTableEntry = NULL;
}

TEST_F(CcspXdnsCosaApisTestFixture, test_CosaDmlGetSelfHealCfg)
{
    char buf[256] = {0};
    FILE *fp_dnsmasq_conf = NULL;
    int ret = 0;
    int index = 0;
    errno_t rc = -1;
    ANSC_HANDLE hThisObject = NULL;
    int Secondaryipv4count=0;
    int Secondaryipv6count=0;

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)hThisObject;
    pMyObject = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(pMyObject, nullptr);

    strcpy(pMyObject->DefaultDeviceDnsIPv4, "192.168.1.2");
    strcpy(pMyObject->DefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv4, "192.168.1.2");
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");
    strcpy(pMyObject->DefaultDeviceTag, "TestTag");


    PCOSA_DML_MAPPING_CONTAINER pMappingContainer = NULL;
    pMappingContainer = (PCOSA_DML_MAPPING_CONTAINER)malloc(sizeof(COSA_DML_MAPPING_CONTAINER));
    ASSERT_NE(pMappingContainer, nullptr);

    pMappingContainer->XDNSEntryCount = 0;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = NULL;
    pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    strcpy(pDnsTableEntry->MacAddress, "00:00:00:00:00:00");
    strcpy(pDnsTableEntry->DnsIPv4, "75.75.75.30");
    strcpy(pDnsTableEntry->DnsIPv6, "2001:558:feed::1");
    strcpy(pDnsTableEntry->Tag, "TestTag");

    EXPECT_CALL(*g_fileIOMock, fopen(_,_))
        .Times(2)
        .WillRepeatedly(Return(fp_dnsmasq_conf));

    EXPECT_NE(CosaDmlGetSelfHealCfg(hThisObject), nullptr);

    free(pMyObject);
    pMyObject = NULL;
    free(pMappingContainer);
    pMappingContainer = NULL;
    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
}

TEST_F(CcspXdnsCosaApisTestFixture, test_CosaDmlGetSelfHealCfg2)
{
    char buf[256] = {0};
    FILE *fp_dnsmasq_conf = (FILE *)0xffffffff;
    int ret = 0;
    int index = 0;
    errno_t rc = -1;
    ANSC_HANDLE hThisObject = NULL;
    int Secondaryipv4count=0;
    int Secondaryipv6count=0;

    PCOSA_DATAMODEL_XDNS pMyObject = (PCOSA_DATAMODEL_XDNS)hThisObject;
    pMyObject = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(pMyObject, nullptr);

    strcpy(pMyObject->DefaultDeviceDnsIPv4, "192.168.1.2");
    strcpy(pMyObject->DefaultDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv4, "192.168.1.2");
    strcpy(pMyObject->DefaultSecondaryDeviceDnsIPv6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");
    strcpy(pMyObject->DefaultDeviceTag, "TestTag");


    PCOSA_DML_MAPPING_CONTAINER pMappingContainer = NULL;
    pMappingContainer = (PCOSA_DML_MAPPING_CONTAINER)malloc(sizeof(COSA_DML_MAPPING_CONTAINER));
    ASSERT_NE(pMappingContainer, nullptr);

    pMappingContainer->XDNSEntryCount = 0;

    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = NULL;
    pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)malloc(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    ASSERT_NE(pDnsTableEntry, nullptr);

    strcpy(pDnsTableEntry->MacAddress, "00:00:00:00:00:00");
    strcpy(pDnsTableEntry->DnsIPv4, "75.75.75.30");
    strcpy(pDnsTableEntry->DnsIPv6, "2001:558:feed::1");
    strcpy(pDnsTableEntry->Tag, "TestTag");

    EXPECT_CALL(*g_fileIOMock, fopen(_,_))
        .Times(1)
        .WillOnce(Return(fp_dnsmasq_conf));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_XDNS"), _, _))
        .Times(1)
        .WillOnce(DoAll(testing::SetArrayArgument<2>(buf, buf + sizeof(buf)), Return(0)));

    EXPECT_CALL(*g_fileIOMock, fgets(_, _, fp_dnsmasq_conf))
        .Times(1);

    EXPECT_CALL(*g_fileIOMock, fclose(_))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_NE(CosaDmlGetSelfHealCfg(hThisObject), nullptr);

    free(pMyObject);
    pMyObject = NULL;
    free(pMappingContainer);
    pMappingContainer = NULL;
    free(pDnsTableEntry);
    pDnsTableEntry = NULL;
}

TEST_F(CcspXdnsCosaApisTestFixture, test_CosaXDNSInitialize)
{
    FILE *fp1 = NULL;
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;
    PCOSA_DATAMODEL_XDNS pMyObject = NULL;
    pMyObject = (PCOSA_DATAMODEL_XDNS)malloc(sizeof(COSA_DATAMODEL_XDNS));
    ASSERT_NE(pMyObject, nullptr);

    AnscSListInitializeHeader( &pMyObject->XDNSDeviceList );
    pMyObject->MaxInstanceNumber = 0;
    pMyObject->ulXDNSNextInstanceNumber = 1;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(2)
        .WillRepeatedly(Return(fp1));

    EXPECT_CALL(*g_syscfgMock, syscfg_init())
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_rbusMock, rbus_open(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusEvent_Subscribe(_, _, _, _, _))
        .Times(1);

    EXPECT_EQ(CosaXDNSInitialize((ANSC_HANDLE)pMyObject), ANSC_STATUS_SUCCESS);

    free(pMyObject);
    pMyObject = NULL;
}

TEST_F(CcspXdnsCosaApisTestFixture, test_SetXdnsConfig)
{
    char confEntry[256] = {0};
    char tempEntry[256] = {0};
    char buf[256] = {0};
    int founddefault = 0;
    FILE *fp1 = NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp1));

    EXPECT_EQ(SetXdnsConfig(), 0);

}

TEST_F(CcspXdnsCosaApisTestFixture, test_SetXdnsConfig2)
{
    char confEntry[256] = {0};
    char tempEntry[256] = {0};
    char buf[256] = {0};
    int founddefault = 0;
    FILE *fp = (FILE *)0xffffffff;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(5)
        .WillRepeatedly(Return(fp));

    EXPECT_CALL(*g_fileIOMock, fgets(_, _, fp))
        .Times(3);

    EXPECT_CALL(*g_fileIOMock, fclose(_))
        .Times(5)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_syseventMock, sysevent_set(_, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_fileIOMock, unlink(_))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(SetXdnsConfig(), 0);

}

TEST_F(CcspXdnsCosaApisTestFixture, test_UnsetXdnsConfig)
{
    char confEntry[256] = {0};
    FILE *fp = NULL;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(1)
        .WillOnce(Return(fp));

    EXPECT_EQ(UnsetXdnsConfig(), 1);
}

TEST_F(CcspXdnsCosaApisTestFixture, test_UnsetXdnsConfig2)
{
    char confEntry[256] = {0};
    FILE *fp = (FILE *)0xffffffff;

    EXPECT_CALL(*g_fileIOMock, fopen(_, _))
        .Times(4)
        .WillRepeatedly(Return(fp));

    EXPECT_CALL(*g_fileIOMock, fgets(_, _, fp))
        .Times(2);

    EXPECT_CALL(*g_fileIOMock, fclose(_))
        .Times(4)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_syseventMock, sysevent_set(_, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_fileIOMock, unlink(_))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_EQ(UnsetXdnsConfig(), 1);
}