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

class CcspXdnsCosaApiUtilTestFixture : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        g_safecLibMock = new SafecLibMock();
        g_anscWrapperApiMock = new AnscWrapperApiMock();
        g_socketMock = new SocketMock();
        g_fdMock = new FileDescriptorMock();
    }

    void TearDown() override 
    {
        delete g_safecLibMock;
        delete g_anscWrapperApiMock;
        delete g_socketMock;
        delete g_fdMock;

        g_safecLibMock = nullptr;
        g_anscWrapperApiMock = nullptr;
        g_socketMock = nullptr;
        g_fdMock = nullptr;
    }
};

// Unit Test for cosa_apis_util.c

TEST_F(CcspXdnsCosaApiUtilTestFixture, interface_type_from_name)
{
    enum DeviceInterfaceType type;
    char *name = NULL;
    int rc = interface_type_from_name(name, &type);
    EXPECT_EQ(rc, 0);
    name = (char *)malloc(sizeof(char) * 10);
    strcpy(name, "eth0");

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(_, _, _, _, _, _))
        .Times(17)
        .WillRepeatedly(Return(0));

    rc = interface_type_from_name(name, &type);
    EXPECT_EQ(rc, 0);
    free(name);
}

TEST_F(CcspXdnsCosaApiUtilTestFixture, CosaUtilStringToHex)
{
    char *str = NULL;
    unsigned char *hex_str = NULL;
    str = (char *)malloc(sizeof(char) * 64);
    strcpy(str, "12345678");
    hex_str = (unsigned char *)malloc(sizeof(unsigned char) * 10);

    ANSC_STATUS rc = CosaUtilStringToHex(str, hex_str);
    EXPECT_EQ(rc, ANSC_STATUS_FAILURE);
    free(str);
    free(hex_str);
}

TEST_F(CcspXdnsCosaApiUtilTestFixture, CosaUtilGetIfAddr)
{
    char *netdev = NULL;
    netdev = (char *)malloc(sizeof(char) * 10);
    strcpy(netdev, "eth0");
    int fd = 0;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_socketMock, socket(_, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_fdMock, ioctl(_, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_safecLibMock, _memcpy_s_chk(_, _, _, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_socketMock, close(_))
        .Times(1)
        .WillOnce(Return(0));

    ULONG ip4_addr = CosaUtilGetIfAddr(netdev);
    EXPECT_EQ(ip4_addr, 0);
    free(netdev);
}

TEST_F(CcspXdnsCosaApiUtilTestFixture, CosaUtilGetIfAddr2)
{
    char *netdev = NULL;
    netdev = (char *)malloc(sizeof(char) * 10);
    strcpy(netdev, "eth0");
    int fd = 0;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(1));

    ULONG ip4_addr = CosaUtilGetIfAddr(netdev);
    EXPECT_EQ(ip4_addr, 0);
    free(netdev);
}

TEST_F(CcspXdnsCosaApiUtilTestFixture, CosaUtilGetIfAddr3)
{
    char *netdev = NULL;
    netdev = (char *)malloc(sizeof(char) * 10);
    strcpy(netdev, "eth0");
    int fd = 0;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_socketMock, socket(_, _, _))
        .Times(1)
        .WillOnce(Return(10));

    EXPECT_CALL(*g_fdMock, ioctl(10, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_safecLibMock, _memcpy_s_chk(_, _, _, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_socketMock, close(_))
        .Times(1)
        .WillOnce(Return(0));

    ULONG ip4_addr = CosaUtilGetIfAddr(netdev);
    EXPECT_EQ(ip4_addr, 0);
    free(netdev);
}

TEST_F(CcspXdnsCosaApiUtilTestFixture, CosaUtilGetIfAdd4)
{
    char *netdev = NULL;
    netdev = (char *)malloc(sizeof(char) * 10);
    strcpy(netdev, "eth0");
    int fd = 0;

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_socketMock, socket(_, _, _))
        .Times(1)
        .WillOnce(Return(10));

    EXPECT_CALL(*g_fdMock, ioctl(10, _, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_safecLibMock, _memcpy_s_chk(_, _, _, _, _, _))
        .Times(1)
        .WillOnce(Return(1));

    EXPECT_CALL(*g_socketMock, close(_))
        .Times(1)
        .WillOnce(Return(0));

    ULONG ip4_addr = CosaUtilGetIfAddr(netdev);
    EXPECT_EQ(ip4_addr, 0);
    free(netdev);
}

TEST_F(CcspXdnsCosaApiUtilTestFixture, CosaSListPushEntryByInsNum)
{
    PCOSA_CONTEXT_LINK_OBJECT pCosaContext = (PCOSA_CONTEXT_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_LINK_OBJECT));
    ASSERT_NE(pCosaContext, nullptr);

    PSLIST_HEADER pListHead = (PSLIST_HEADER)malloc(sizeof(SLIST_HEADER));
    ASSERT_NE(pListHead, nullptr);

    pListHead->Depth = 0;
    pCosaContext->InstanceNumber = 1;
    AnscSListInitializeHeader(pListHead);

    ANSC_STATUS result = CosaSListPushEntryByInsNum(pListHead, pCosaContext);

    EXPECT_EQ(result, ANSC_STATUS_SUCCESS);

    free(pListHead);
    free(pCosaContext);
}

TEST_F(CcspXdnsCosaApiUtilTestFixture, CosaSListPushEntryByInsNum2)
{
    PCOSA_CONTEXT_LINK_OBJECT pCosaContext = (PCOSA_CONTEXT_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_LINK_OBJECT));
    ASSERT_NE(pCosaContext, nullptr);

    PSLIST_HEADER pListHead = (PSLIST_HEADER)malloc(sizeof(SLIST_HEADER));
    ASSERT_NE(pListHead, nullptr);

    pListHead->Depth = 1;
    pCosaContext->InstanceNumber = 1;
    AnscSListInitializeHeader(pListHead);

    ANSC_STATUS result = CosaSListPushEntryByInsNum(pListHead, pCosaContext);

    EXPECT_EQ(result, ANSC_STATUS_SUCCESS);

    free(pListHead);
    free(pCosaContext);
}

TEST_F(CcspXdnsCosaApiUtilTestFixture, CosaSListPushEntryByInsNum_Failure)
{
    PCOSA_CONTEXT_LINK_OBJECT pCosaContext = (PCOSA_CONTEXT_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_LINK_OBJECT));
    ASSERT_NE(pCosaContext, nullptr);

    PSLIST_HEADER pListHead = (PSLIST_HEADER)malloc(sizeof(SLIST_HEADER));
    ASSERT_NE(pListHead, nullptr);

    pListHead->Depth = 0;
    pCosaContext->InstanceNumber = 1;
    AnscSListInitializeHeader(pListHead);

    ANSC_STATUS result = CosaSListPushEntryByInsNum(pListHead, pCosaContext);

    EXPECT_EQ(result, ANSC_STATUS_SUCCESS);

    free(pListHead);
    free(pCosaContext);
}

TEST_F(CcspXdnsCosaApiUtilTestFixture, CosaSListGetEntryByInsNum)
{
    PCOSA_CONTEXT_LINK_OBJECT pCosaContext = (PCOSA_CONTEXT_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_LINK_OBJECT));
    ASSERT_NE(pCosaContext, nullptr);

    PSLIST_HEADER pListHead = (PSLIST_HEADER)malloc(sizeof(SLIST_HEADER));
    ASSERT_NE(pListHead, nullptr);

    pListHead->Depth = 1;
    pCosaContext->InstanceNumber = 1;
    AnscSListInitializeHeader(pListHead);
    AnscSListPushEntry(pListHead, &pCosaContext->Linkage);

    PCOSA_CONTEXT_LINK_OBJECT result = CosaSListGetEntryByInsNum(pListHead, 1);

    EXPECT_EQ(result->InstanceNumber, 1);

    free(pListHead);
    free(pCosaContext);
}

TEST_F(CcspXdnsCosaApiUtilTestFixture, CosaSListGetEntryByInsNum_Failure)
{
    PCOSA_CONTEXT_LINK_OBJECT nullObj = NULL;
    PCOSA_CONTEXT_LINK_OBJECT pCosaContext = (PCOSA_CONTEXT_LINK_OBJECT)malloc(sizeof(COSA_CONTEXT_LINK_OBJECT));
    ASSERT_NE(pCosaContext, nullptr);

    PSLIST_HEADER pListHead = (PSLIST_HEADER)malloc(sizeof(SLIST_HEADER));
    ASSERT_NE(pListHead, nullptr);

    pListHead->Depth = 1;
    pCosaContext->InstanceNumber = 1;
    AnscSListInitializeHeader(pListHead);
    AnscSListPushEntry(pListHead, &pCosaContext->Linkage);

    PCOSA_CONTEXT_LINK_OBJECT result = CosaSListGetEntryByInsNum(pListHead, 2);

    EXPECT_EQ(result, nullObj);

    free(pListHead);
    free(pCosaContext);
}

TEST_F(CcspXdnsCosaApiUtilTestFixture, CosaUtilGetStaticRouteTable)
{
    UINT count = 0;
    StaticRoute *out_sroute = NULL;

    ANSC_STATUS result = CosaUtilGetStaticRouteTable(&count, &out_sroute);

    EXPECT_EQ(result, ANSC_STATUS_SUCCESS);
}

TEST_F(CcspXdnsCosaApiUtilTestFixture, CosaUtilGetLowerLayers)
{
    PUCHAR pTableName = NULL;
    PUCHAR pKeyword = NULL;

    PUCHAR result = CosaUtilGetLowerLayers(pTableName, pKeyword);

    EXPECT_EQ(result, nullptr);
}

TEST_F(CcspXdnsCosaApiUtilTestFixture, CosaUtilGetLowerLayers2)
{
    PUCHAR pTableName = (PUCHAR)malloc(sizeof(char) * 10);
    strcpy((char *)pTableName, "eth0");
    PUCHAR pKeyword = (PUCHAR)malloc(sizeof(char) * 10);
    strcpy((char *)pKeyword, "eth0");

    DeviceInterfaceType type = ETHERNET_INTERFACE;

    PANSC_TOKEN_CHAIN pTableListTokenChain = (PANSC_TOKEN_CHAIN)NULL;
    pTableListTokenChain = (PANSC_TOKEN_CHAIN)malloc(sizeof(ANSC_TOKEN_CHAIN));

    PANSC_STRING_TOKEN pTableStringToken = (PANSC_STRING_TOKEN)NULL;
    pTableStringToken = (PANSC_STRING_TOKEN)malloc(sizeof(ANSC_STRING_TOKEN));
    strcpy(pTableStringToken->Name, "eth0");

    EXPECT_CALL(*g_anscWrapperApiMock, AnscTcAllocate(_, _))
        .Times(1)
        .WillOnce(Return((ANSC_HANDLE)pTableListTokenChain));

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(_, _, _, _, _, _))
        .Times(17)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_anscWrapperApiMock, AnscTcPopToken(_))
        .Times(1)
        .WillOnce(Return((ANSC_HANDLE)NULL));

    EXPECT_CALL(*g_anscWrapperApiMock, AnscTcFree(_))
        .Times(1);

    EXPECT_EQ(interface_type_from_name((char *)pTableStringToken->Name, &type), 0);

    PUCHAR result = CosaUtilGetLowerLayers(pTableName, pKeyword);

    EXPECT_EQ(result, nullptr);
    free(pTableName);
    free(pKeyword);
}

TEST_F(CcspXdnsCosaApiUtilTestFixture, CosaUtilGetFullPathNameByKeyword)
{
    PUCHAR pTableName = NULL;
    PUCHAR pParameterName = NULL;
    PUCHAR pKeyword = NULL;

    PUCHAR result = CosaUtilGetFullPathNameByKeyword(pTableName, pParameterName, pKeyword);

    EXPECT_EQ(result, nullptr);
}

TEST_F(CcspXdnsCosaApiUtilTestFixture, CosaUtilGetFullPathNameByKeyword2)
{
    PUCHAR pTableName = (PUCHAR)malloc(sizeof(char) * 10);
    strcpy((char *)pTableName, "eth0");
    PUCHAR pParameterName = (PUCHAR)malloc(sizeof(char) * 10);
    strcpy((char *)pParameterName, "eth0");
    PUCHAR pKeyword = (PUCHAR)malloc(sizeof(char) * 10);
    strcpy((char *)pKeyword, "eth0");

    PANSC_TOKEN_CHAIN pTableListTokenChain = (PANSC_TOKEN_CHAIN)NULL;
    pTableListTokenChain = (PANSC_TOKEN_CHAIN)malloc(sizeof(ANSC_TOKEN_CHAIN));

    PANSC_STRING_TOKEN pTableStringToken = (PANSC_STRING_TOKEN)NULL;
    pTableStringToken = (PANSC_STRING_TOKEN)malloc(sizeof(ANSC_STRING_TOKEN));
    strcpy(pTableStringToken->Name, "eth0");

    EXPECT_CALL(*g_anscWrapperApiMock, AnscTcAllocate(_, _))
        .Times(1)
        .WillOnce(Return((ANSC_HANDLE)pTableListTokenChain));

    EXPECT_CALL(*g_anscWrapperApiMock, AnscTcPopToken(_))
        .Times(1)
        .WillOnce(Return((ANSC_HANDLE)NULL));

    EXPECT_CALL(*g_anscWrapperApiMock, AnscTcFree(_))
        .Times(1);

    PUCHAR result = CosaUtilGetFullPathNameByKeyword(pTableName, pParameterName, pKeyword);

    EXPECT_EQ(result, nullptr);
    free(pTableName);
    free(pParameterName);
    free(pKeyword);
}