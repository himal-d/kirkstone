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

class CcspCMAgentDeviceInfoInternalTestFixture : public ::testing::Test {
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

// Unit Test for cosa_device_info_internal.c file

TEST_F(CcspCMAgentDeviceInfoInternalTestFixture, CosaDeviceInfoCreate)
{
    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(pMyObject, nullptr);

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(4)
        .WillRepeatedly(Return(0));
    
    EXPECT_CALL(*g_rbusMock, rbus_checkStatus())
        .Times(1)
        .WillOnce(Return(RBUS_ENABLED));
    
    EXPECT_CALL(*g_rbusMock, rbus_open(_,_))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_SUCCESS));

    EXPECT_CALL(*g_rbusMock, rbus_regDataElements(_, _, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_SUCCESS));

    EXPECT_CALL(*g_webconfigFwMock, register_sub_docs(_, _, _, _))
        .Times(1)
        .WillOnce(Return());

    ANSC_HANDLE createdObject = CosaDeviceInfoCreate();
    EXPECT_NE(createdObject, nullptr);
    
    free(pMyObject);
    pMyObject = NULL;
}

TEST_F(CcspCMAgentDeviceInfoInternalTestFixture, CosaDeviceInfoInitialize)
{
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(pMyObject, nullptr);

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(5)
        .WillRepeatedly(Return(0));
    
    EXPECT_CALL(*g_rbusMock, rbus_checkStatus())
        .Times(2)
        .WillRepeatedly(Return(RBUS_ENABLED));
    
    EXPECT_CALL(*g_rbusMock, rbus_open(_,_))
        .Times(2)
        .WillRepeatedly(Return(RBUS_ERROR_SUCCESS));

    EXPECT_CALL(*g_rbusMock, rbus_regDataElements(_, _, _))
        .Times(2)
        .WillRepeatedly(Return(RBUS_ERROR_SUCCESS));

    EXPECT_EQ(cmAgentLldRbusInit(), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_webconfigFwMock, register_sub_docs(_, _, _, _))
        .Times(1)
        .WillOnce(Return());
    
    EXPECT_EQ(CosaDeviceInfoInitialize((ANSC_HANDLE)pMyObject), returnStatus);

    free(pMyObject);
    pMyObject = NULL;
}

TEST_F(CcspCMAgentDeviceInfoInternalTestFixture, CosaDeviceInfoRemove)
{
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(pMyObject, nullptr);

    EXPECT_CALL(*g_anscMemoryMock, AnscFreeMemoryOrig(_))
        .Times(1);
    
    EXPECT_EQ(CosaDeviceInfoRemove((ANSC_HANDLE)pMyObject), returnStatus);

    free(pMyObject);
    pMyObject = NULL;
}

TEST_F(CcspCMAgentDeviceInfoInternalTestFixture, CosaDmlDIGetFWVersion)
{
    ANSC_STATUS returnStatus = ANSC_STATUS_SUCCESS;

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(pMyObject, nullptr);
    
    strncpy(pMyObject->Current_Firmware, "CGA4332COM_7.6s3_DEV_sey.bin", sizeof(pMyObject->Current_Firmware));

    EXPECT_EQ(CosaDmlDIGetFWVersion((ANSC_HANDLE)pMyObject), ANSC_STATUS_FAILURE);

    free(pMyObject);
    pMyObject = NULL;
}