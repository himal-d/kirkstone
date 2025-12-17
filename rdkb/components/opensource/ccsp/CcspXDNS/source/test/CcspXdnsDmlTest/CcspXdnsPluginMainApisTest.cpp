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

class CcspXdnsPluginMainApisTestFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
        g_syseventMock = new SyseventMock();
    }

    void TearDown() override
    {
        delete g_syseventMock;

        g_syseventMock = nullptr;
    }
};

// Unit Test for plugin_main.c file

TEST_F(CcspXdnsPluginMainApisTestFixture, CosaBackEndManagerCreate)
{
    PCOSA_BACKEND_MANAGER_OBJECT pMyObject = (PCOSA_BACKEND_MANAGER_OBJECT)AnscAllocateMemory(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(pMyObject, nullptr);

    pMyObject->Oid = COSA_DATAMODEL_XDNS_OID;
    pMyObject->Create = CosaBackEndManagerCreate;
    pMyObject->Remove = CosaBackEndManagerRemove;
    pMyObject->Initialize = CosaBackEndManagerInitialize;

    EXPECT_EQ(pMyObject->Oid, COSA_DATAMODEL_XDNS_OID);
    EXPECT_EQ(pMyObject->Create, CosaBackEndManagerCreate);
    EXPECT_EQ(pMyObject->Remove, CosaBackEndManagerRemove);
    EXPECT_EQ(pMyObject->Initialize, CosaBackEndManagerInitialize);

    EXPECT_NE(CosaBackEndManagerCreate(), (ANSC_HANDLE)pMyObject);

    free(pMyObject);
    pMyObject = NULL;
}

TEST_F(CcspXdnsPluginMainApisTestFixture, CosaBackEndManagerInitialize)
{
    PCOSA_BACKEND_MANAGER_OBJECT pMyObject = (PCOSA_BACKEND_MANAGER_OBJECT)AnscAllocateMemory(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(pMyObject, nullptr);

    pMyObject->hXdns = (ANSC_HANDLE)CosaXDNSCreate();

    webConfigFrameworkInit();

    EXPECT_EQ(CosaBackEndManagerInitialize((ANSC_HANDLE)pMyObject), ANSC_STATUS_SUCCESS);

    free(pMyObject);
    pMyObject = NULL;
}

TEST_F(CcspXdnsPluginMainApisTestFixture, CosaBackEndManagerRemove)
{
    PCOSA_BACKEND_MANAGER_OBJECT pMyObject = (PCOSA_BACKEND_MANAGER_OBJECT)AnscAllocateMemory(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(pMyObject, nullptr);

    const char *file1 = "/nvram/dnsmasq_servers.conf";
    const char *file2 = "/etc/resolv.conf";

    pMyObject->hXdns = (ANSC_HANDLE)CosaXDNSCreate();

    CosaXDNSRemove((ANSC_HANDLE)pMyObject->hXdns);

    EXPECT_EQ(CosaBackEndManagerRemove((ANSC_HANDLE)pMyObject), ANSC_STATUS_SUCCESS);

    free(pMyObject);
    pMyObject = NULL;
}

TEST_F(CcspXdnsPluginMainApisTestFixture, commonSyseventGet)
{
    char key[10] = "key";
    char value[10] = "value";
    int valLen = 10;

    EXPECT_CALL(*g_syseventMock, sysevent_get(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(0));

    int result = commonSyseventGet(key, value, valLen);

    EXPECT_EQ(result, 0);
}

TEST_F(CcspXdnsPluginMainApisTestFixture, commonSyseventClose)
{
    EXPECT_CALL(*g_syseventMock, sysevent_close(_, _))
        .Times(1)
        .WillOnce(Return(0));

    int result = commonSyseventClose();

    EXPECT_EQ(result, 0);
}