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

class CcspCMAgentRbusHandlerApisTestFixture : public ::testing::Test {
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

// Unit Test for cosa_rbus_handler_apis.c file

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, getBoolHandler_ValidInput_EWanLinkStatus)
{
    rbusHandle_t handle = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusGetHandlerOptions_t opts;
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x5678);

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return(DOCSIS_LINK_STATUS_TR181));

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(1)
        .WillOnce(Return(value));

    EXPECT_CALL(*g_rbusMock, rbusValue_SetBoolean(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusProperty_SetValue(property, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusValue_Release(_))
        .Times(1);

    rbusError_t result = getBoolHandler(handle, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, getBoolHandler_ValidInput_CableModemRfSignalStatus)
{
    rbusHandle_t handle = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusGetHandlerOptions_t opts;
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x5678);

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return(CABLE_MODEM_RF_SIGNAL_STATUS));

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(1)
        .WillOnce(Return(value));

    EXPECT_CALL(*g_rbusMock, rbusValue_SetBoolean(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusProperty_SetValue(property, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusValue_Release(_))
        .Times(1);

    rbusError_t result = getBoolHandler(handle, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_SUCCESS);
}


TEST_F(CcspCMAgentRbusHandlerApisTestFixture, getBoolHandler_ValidInput_EWanLinkDown)
{
    rbusHandle_t handle = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusGetHandlerOptions_t opts;
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x5678);

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return(DOCSIS_LINKDOWN_TR181));

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(1)
        .WillOnce(Return(value));

    EXPECT_CALL(*g_rbusMock, rbusValue_SetBoolean(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusProperty_SetValue(property, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusValue_Release(_))
        .Times(1);

    rbusError_t result = getBoolHandler(handle, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, getBoolHandler_InvalidInput)
{
    rbusHandle_t handle = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusGetHandlerOptions_t opts;
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x5678);

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return("InvalidInput"));

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(1)
        .WillOnce(Return(value));

    rbusError_t result = getBoolHandler(handle, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_INVALID_INPUT);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, SetBoolHandler)
{
    rbusHandle_t handle = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusSetHandlerOptions_t opts;
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x5678);

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return(DOCSIS_LINKDOWN_TR181));

    EXPECT_CALL(*g_rbusMock, rbusValue_GetType(value))
        .Times(1)
        .WillOnce(Return(RBUS_BOOLEAN));

    EXPECT_CALL(*g_rbusMock, rbusValue_GetBoolean(value))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetValue(property))
        .Times(1)
        .WillOnce(Return(value));

    rbusError_t result = SetBoolHandler(handle, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, SetBoolHandler_Rbus_CMAgent_SetParamBoolValue_Failure)
{
    rbusHandle_t handle = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusSetHandlerOptions_t opts;
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x5678);

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return(DOCSIS_LINKDOWN_TR181));

    EXPECT_CALL(*g_rbusMock, rbusValue_GetType(value))
        .Times(1)
        .WillOnce(Return(RBUS_BOOLEAN));

    EXPECT_CALL(*g_rbusMock, rbusValue_GetBoolean(value))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetValue(property))
        .Times(1)
        .WillOnce(Return(value));

    EXPECT_EQ(Rbus_CMAgent_SetParamBoolValue(NULL, (char *)DOCSIS_LINKDOWN_TR181, true), false);

    rbusError_t result = SetBoolHandler(handle, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_BUS_ERROR);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, SetBoolHandler_InvalidInput)
{
    rbusHandle_t handle = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusSetHandlerOptions_t opts;
    rbusValue_t value = nullptr;

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return("InvalidInput"));

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetValue(property))
        .Times(1)
        .WillOnce(Return(value));

    rbusError_t result = SetBoolHandler(handle, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_BUS_ERROR);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, getuintHandler_ValidInput_DocsisLinkDownTimeout)
{
    rbusHandle_t handle = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusGetHandlerOptions_t opts;
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x5678);

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return(DOCSIS_LINKDOWNTIMEOUT_TR181));

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(1)
        .WillOnce(Return(value));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusValue_SetUInt32(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusProperty_SetValue(property, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusValue_Release(_))
        .Times(1);

    rbusError_t result = getuintHandler(handle, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, getuintHandler_InvalidInput)
{
    rbusHandle_t handle = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusGetHandlerOptions_t opts;
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x5678);

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return("InvalidInput"));

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(1)
        .WillOnce(Return(value));

    rbusError_t result = getuintHandler(handle, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_INVALID_INPUT);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, SetUintHandler)
{
    rbusHandle_t handle = nullptr;
    rbusSetHandlerOptions_t opts;

    char const* propName = DOCSIS_LINKDOWNTIMEOUT_TR181;
    const char* param = strdup(GetParamName(propName));
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x384);
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    uint uintValue = 0;

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return(DOCSIS_LINKDOWNTIMEOUT_TR181));

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetValue(property))
        .Times(1)
        .WillOnce(Return(value));

    EXPECT_CALL(*g_rbusMock, rbusValue_GetType(value))
        .Times(1)
        .WillOnce(Return(RBUS_UINT32));

    EXPECT_CALL(*g_rbusMock, rbusValue_GetUInt32(value))
        .Times(1)
        .WillOnce(Return(uintValue));

    EXPECT_EQ(Rbus_CMAgent_SetParamUintValue(NULL, (char *)param, uintValue), false);

    rbusError_t result = SetUintHandler(handle, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_BUS_ERROR);
}


TEST_F(CcspCMAgentRbusHandlerApisTestFixture, SetUintHandler_InvalidInput)
{
    rbusHandle_t handle = nullptr;
    rbusSetHandlerOptions_t opts;

    char const* propName = "InvalidInput";
    const char* param = strdup(GetParamName(propName));
    rbusValue_t value = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return("InvalidInput"));

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetValue(property))
        .Times(1)
        .WillOnce(Return(value));

    rbusError_t result = SetUintHandler(handle, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_BUS_ERROR);
}


TEST_F(CcspCMAgentRbusHandlerApisTestFixture, eventSubHandler_ValidInput_DocsisLinkStatus)
{
    rbusHandle_t handle = nullptr;
    rbusEventSubAction_t action = RBUS_EVENT_ACTION_SUBSCRIBE;
    const char* eventName = DOCSIS_LINK_STATUS_TR181;
    rbusFilter_t filter = reinterpret_cast<rbusFilter_t>(0x1234);
    int32_t interval = 0;
    bool autoPublish = false;

    rbusError_t result = eventSubHandler(handle, action, eventName, filter, interval, &autoPublish);

    EXPECT_EQ(result, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, eventSubHandler_ValidInput_CableModemRfSignalStatus)
{
    rbusHandle_t handle = nullptr;
    rbusEventSubAction_t action = RBUS_EVENT_ACTION_SUBSCRIBE;
    const char* eventName = CABLE_MODEM_RF_SIGNAL_STATUS;
    rbusFilter_t filter = reinterpret_cast<rbusFilter_t>(0x1234);
    int32_t interval = 0;
    bool autoPublish = false;

    rbusError_t result = eventSubHandler(handle, action, eventName, filter, interval, &autoPublish);

    EXPECT_EQ(result, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, eventSubHandler_InvalidInput)
{
    rbusHandle_t handle = nullptr;
    rbusEventSubAction_t action = RBUS_EVENT_ACTION_SUBSCRIBE;
    const char* eventName = "InvalidInput";
    rbusFilter_t filter = reinterpret_cast<rbusFilter_t>(0x1234);
    int32_t interval = 0;
    bool autoPublish = false;

    rbusError_t result = eventSubHandler(handle, action, eventName, filter, interval, &autoPublish);

    EXPECT_EQ(result, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, initLinkStatus)
{
    char pValue[128] = {0};
    CmAgent_Link_Status cmAgent_Link_Status;
    cmAgent_Link_Status.DocsisLinkStatus = false;
    cmAgent_Link_Status.DocsisLinkDown = false;

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(1);

    EXPECT_CALL(*g_cmHALMock, docsis_IsEnergyDetected(_))
        .Times(1)
        .WillOnce(Return(RETURN_OK));

    initLinkStatus();

    EXPECT_FALSE(cmAgent_Link_Status.DocsisLinkStatus);
    EXPECT_FALSE(cmAgent_Link_Status.DocsisLinkDown);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, publishDocsisLinkStatus)
{
    rbusError_t ret = RBUS_ERROR_SUCCESS;
    CmAgent_Link_Status cmAgent_Link_Status;
    bool link_status = true;
    bool oldDocsisLinkStatus = false;
    int gSubscribersCount = 1;
    const char* eventName = DOCSIS_LINK_STATUS_TR181;
    cmAgent_Link_Status.DocsisLinkStatus = link_status;

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(6)
        .WillRepeatedly(Return(reinterpret_cast<rbusValue_t>(0x5678)));

    EXPECT_CALL(*g_rbusMock, rbusObject_Init(_, _))
        .Times(2)
        .WillRepeatedly(Return(reinterpret_cast<rbusObject_t>(0x1234)));

    EXPECT_CALL(*g_rbusMock, rbusValue_SetBoolean(_, _))
        .Times(4);

    EXPECT_CALL(*g_rbusMock, rbusValue_SetString(_, _))
        .Times(2);

    EXPECT_CALL(*g_rbusMock, rbusObject_SetValue(_, _, _))
        .Times(6);

    EXPECT_CALL(*g_rbusMock, rbusEvent_Publish(_, _))
        .Times(2)
        .WillRepeatedly(Return(RBUS_ERROR_SUCCESS));

    EXPECT_CALL(*g_rbusMock, rbusValue_Release(_))
        .Times(6);

    EXPECT_CALL(*g_rbusMock, rbusObject_Release(_))
        .Times(2);

    EXPECT_EQ(sendBoolUpdateEvent(nullptr, (char *)eventName, cmAgent_Link_Status.DocsisLinkStatus, oldDocsisLinkStatus), RBUS_ERROR_SUCCESS);

    publishDocsisLinkStatus(link_status);

    EXPECT_TRUE(cmAgent_Link_Status.DocsisLinkStatus);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, Rbus_CMAgent_SetParamBoolValue)
{
    const char *pParamName = "LinkDown";
    BOOL bValue = true;
    CmAgent_Link_Status cmAgent_Link_Status;
    cmAgent_Link_Status.DocsisLinkDown = false;
    cmAgent_Link_Status.DocsisLinkDown = bValue;

    EXPECT_EQ(Rbus_CMAgent_SetParamBoolValue(nullptr, (char *)pParamName, bValue), true);

    EXPECT_TRUE(cmAgent_Link_Status.DocsisLinkDown);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, Rbus_CMAgent_SetParamBoolValue_InvalidInput)
{
    const char *pParamName = "InvalidInput";
    BOOL bValue = true;
    CmAgent_Link_Status cmAgent_Link_Status;
    cmAgent_Link_Status.DocsisLinkDown = false;
    cmAgent_Link_Status.DocsisLinkDown = bValue;

    EXPECT_EQ(Rbus_CMAgent_SetParamBoolValue(nullptr, (char *)pParamName, bValue), false);

    EXPECT_TRUE(cmAgent_Link_Status.DocsisLinkDown);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, Rbus_CMAgent_SetParamBoolValue_SameValueTrue)
{
    const char *pParamName = "LinkDown";
    BOOL bValue = true;
    CmAgent_Link_Status cmAgent_Link_Status;
    cmAgent_Link_Status.DocsisLinkDown = true;
    cmAgent_Link_Status.DocsisLinkDown = bValue;

    EXPECT_EQ(Rbus_CMAgent_SetParamBoolValue(nullptr, (char *)pParamName, bValue), false);

    EXPECT_TRUE(cmAgent_Link_Status.DocsisLinkDown);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, Rbus_CMAgent_SetParamBoolValue_SameValueFalse)
{
    const char *pParamName = "LinkDown";
    BOOL bValue = false;
    CmAgent_Link_Status cmAgent_Link_Status;
    cmAgent_Link_Status.DocsisLinkDown = false;
    cmAgent_Link_Status.DocsisLinkDown = bValue;

    EXPECT_EQ(Rbus_CMAgent_SetParamBoolValue(nullptr, (char *)pParamName, bValue), true);

    EXPECT_FALSE(cmAgent_Link_Status.DocsisLinkDown);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, SetDocsisLinkdowSignalfunc)
{
    fpDocsisLinkdownSignal CreateThreadandSendCondSignalToPthreadfunc = NULL;
    CmAgent_Link_Status cmAgent_Link_Status;
    cmAgent_Link_Status.pDocsisLinkdowSignal = NULL;

    EXPECT_EQ(SetDocsisLinkdowSignalfunc(CreateThreadandSendCondSignalToPthreadfunc), FALSE);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, SetDocsisLinkdowSignalfunc_ValidInput)
{
    fpDocsisLinkdownSignal CreateThreadandSendCondSignalToPthreadfunc = (fpDocsisLinkdownSignal)0x1234;
    CmAgent_Link_Status cmAgent_Link_Status;
    cmAgent_Link_Status.pDocsisLinkdowSignal = CreateThreadandSendCondSignalToPthreadfunc;

    EXPECT_EQ(SetDocsisLinkdowSignalfunc(CreateThreadandSendCondSignalToPthreadfunc), TRUE);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, publishCableModemRfSignalStatus)
{
    CmAgent_Link_Status cmAgent_Link_Status;

    BOOL currentRfSignalStatus = true;
    BOOL prevRfSignalStatus = false;

    EXPECT_CALL(*g_cmHALMock, docsis_IsEnergyDetected(_))
        .Times(1)
        .WillOnce(Return(RETURN_OK));

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(3)
        .WillRepeatedly(Return(reinterpret_cast<rbusValue_t>(0x5678)));

    EXPECT_CALL(*g_rbusMock, rbusObject_Init(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusValue_SetBoolean(_, _))
        .Times(2);

    EXPECT_CALL(*g_rbusMock, rbusValue_Release(_))
        .Times(3);

    EXPECT_CALL(*g_rbusMock, rbusEvent_Publish(_, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_SUCCESS));

    EXPECT_CALL(*g_rbusMock, rbusValue_SetString(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusObject_SetValue(_, _, _))
        .Times(3);

    EXPECT_CALL(*g_rbusMock, rbusObject_Release(_))
        .Times(1);

    prevRfSignalStatus = cmAgent_Link_Status.CableModemRfSignalStatus;
    cmAgent_Link_Status.CableModemRfSignalStatus = currentRfSignalStatus;

    publishCableModemRfSignalStatusValue(currentRfSignalStatus);
    publishCableModemRfSignalStatus();
    EXPECT_TRUE(cmAgent_Link_Status.CableModemRfSignalStatus);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, publishCableModemRfSignalStatusValue)
{
    rbusError_t ret = RBUS_ERROR_SUCCESS;
    CmAgent_Link_Status cmAgent_Link_Status;
    bool link_status = true;
    bool oldCableModemRfSignalStatus = false;
    int gSubscribersCount = 1;
    const char* eventName = CABLE_MODEM_RF_SIGNAL_STATUS;
    cmAgent_Link_Status.CableModemRfSignalStatus = link_status;

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(6)
        .WillRepeatedly(Return(reinterpret_cast<rbusValue_t>(0x5678)));

    EXPECT_CALL(*g_rbusMock, rbusObject_Init(_, _))
        .Times(2)
        .WillRepeatedly(Return(reinterpret_cast<rbusObject_t>(0x1234)));

    EXPECT_CALL(*g_rbusMock, rbusValue_SetBoolean(_, _))
        .Times(4);

    EXPECT_CALL(*g_rbusMock, rbusValue_SetString(_, _))
        .Times(2);

    EXPECT_CALL(*g_rbusMock, rbusObject_SetValue(_, _, _))
        .Times(6);

    EXPECT_CALL(*g_rbusMock, rbusEvent_Publish(_, _))
        .Times(2)
        .WillRepeatedly(Return(RBUS_ERROR_SUCCESS));

    EXPECT_CALL(*g_rbusMock, rbusValue_Release(_))
        .Times(6);

    EXPECT_CALL(*g_rbusMock, rbusObject_Release(_))
        .Times(2);

    EXPECT_EQ(sendBoolUpdateEvent(nullptr, (char *)eventName, cmAgent_Link_Status.CableModemRfSignalStatus, oldCableModemRfSignalStatus), RBUS_ERROR_SUCCESS);

    publishCableModemRfSignalStatusValue(link_status);

    EXPECT_TRUE(cmAgent_Link_Status.CableModemRfSignalStatus);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, cmAgentRbusInit)
{
    rbusError_t rc = RBUS_ERROR_SUCCESS;

    EXPECT_CALL(*g_rbusMock, rbus_checkStatus())
        .Times(1)
        .WillOnce(Return(RBUS_ENABLED));

    EXPECT_CALL(*g_rbusMock, rbus_open(_, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_SUCCESS));

    EXPECT_CALL(*g_rbusMock, rbus_regDataElements(_, _, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_SUCCESS));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(1);

    EXPECT_CALL(*g_cmHALMock, docsis_IsEnergyDetected(_))
        .Times(1)
        .WillOnce(Return(RETURN_OK));

    rc = cmAgentRbusInit();

    EXPECT_EQ(rc, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, cmAgentRbusInit_RbusNotEnabled)
{
    rbusError_t rc = RBUS_ERROR_SUCCESS;

    EXPECT_CALL(*g_rbusMock, rbus_checkStatus())
        .Times(1)
        .WillOnce(Return(RBUS_DISABLED));

    rc = cmAgentRbusInit();

    EXPECT_EQ(rc, RBUS_ERROR_BUS_ERROR);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, cmAgentRbusInit_RbusOpenFailed)
{
    rbusError_t rc = RBUS_ERROR_SUCCESS;

    EXPECT_CALL(*g_rbusMock, rbus_checkStatus())
        .Times(1)
        .WillOnce(Return(RBUS_ENABLED));

    EXPECT_CALL(*g_rbusMock, rbus_open(_, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_BUS_ERROR));

    rc = cmAgentRbusInit();

    EXPECT_EQ(rc, RBUS_ERROR_NOT_INITIALIZED);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, cmAgentRbusInit_RbusRegDataElementsFailed)
{
    rbusError_t rc = RBUS_ERROR_SUCCESS;

    EXPECT_CALL(*g_rbusMock, rbus_checkStatus())
        .Times(1)
        .WillOnce(Return(RBUS_ENABLED));

    EXPECT_CALL(*g_rbusMock, rbus_open(_, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_SUCCESS));

    EXPECT_CALL(*g_rbusMock, rbus_regDataElements(_, _, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_BUS_ERROR));

    EXPECT_CALL(*g_rbusMock, rbus_close(_))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_SUCCESS));

    rc = cmAgentRbusInit();

    EXPECT_EQ(rc, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, sendBoolUpdateEvent)
{
    rbusHandle_t cm_handle = nullptr;
    const char* event_name = "DOCSIS_LINK_STATUS";
    bool eventNewData = true;
    bool eventOldData = false;

    rbusEvent_t event;
    rbusObject_t data;
    rbusValue_t value;
    rbusValue_t oldVal;
    rbusValue_t byVal;
    rbusError_t ret = RBUS_ERROR_SUCCESS;

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(3)
        .WillRepeatedly(Return(reinterpret_cast<rbusValue_t>(0x5678)));

    EXPECT_CALL(*g_rbusMock, rbusObject_Init(_, _))
        .Times(1)
        .WillOnce(Return(reinterpret_cast<rbusObject_t>(0x1234)));

    EXPECT_CALL(*g_rbusMock, rbusValue_SetBoolean(_, _))
        .Times(2);

    EXPECT_CALL(*g_rbusMock, rbusValue_SetString(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusObject_SetValue(_, _, _))
        .Times(3);

    EXPECT_CALL(*g_rbusMock, rbusEvent_Publish(_, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_SUCCESS));

    EXPECT_CALL(*g_rbusMock, rbusValue_Release(_))
        .Times(3);

    EXPECT_CALL(*g_rbusMock, rbusObject_Release(_))
        .Times(1);

    ret = sendBoolUpdateEvent(cm_handle, (char *)event_name, eventNewData, eventOldData);

    EXPECT_EQ(ret, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, GetParamName_ValidInput)
{
    char const* path = "Device.DeviceInfo.X_RDKCENTRAL-COM_CableModem.DocsisLinkStatus";
    char const* result = GetParamName(path);

    EXPECT_STREQ(result, "DocsisLinkStatus");
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, GetParamName_InvalidInput)
{
    char const* path = "Device.DeviceInfo.X_RDKCENTRAL-COM_CableModem.";
    char const* result = GetParamName(path);

    EXPECT_STREQ(result, "");
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, GetParamName_EmptyInput)
{
    char const* path = "";
    char const* result = GetParamName(path);

    EXPECT_STREQ(result, "");
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, cmAgentLldRbusInit)
{
    rbusError_t rc = RBUS_ERROR_SUCCESS;

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbus_checkStatus())
        .Times(1)
        .WillOnce(Return(RBUS_ENABLED));

    EXPECT_CALL(*g_rbusMock, rbus_open(_, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_SUCCESS));

    EXPECT_CALL(*g_rbusMock, rbus_regDataElements(_, _, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_SUCCESS));

    rc = cmAgentLldRbusInit();

    EXPECT_EQ(rc, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, cmAgentLldRbusInit_RbusNotEnabled)
{
    rbusError_t rc = RBUS_ERROR_SUCCESS;

    EXPECT_CALL(*g_rbusMock, rbus_checkStatus())
        .Times(1)
        .WillOnce(Return(RBUS_DISABLED));

    rc = cmAgentLldRbusInit();

    EXPECT_EQ(rc, RBUS_ERROR_BUS_ERROR);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, cmAgentLldRbusInit_RbusOpenFailed)
{
    rbusError_t rc = RBUS_ERROR_SUCCESS;

    EXPECT_CALL(*g_rbusMock, rbus_checkStatus())
        .Times(1)
        .WillOnce(Return(RBUS_ENABLED));

    EXPECT_CALL(*g_rbusMock, rbus_open(_, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_BUS_ERROR));

    rc = cmAgentLldRbusInit();

    EXPECT_EQ(rc, RBUS_ERROR_NOT_INITIALIZED);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, cmAgentLldRbusInit_RbusRegDataElementsFailed)
{
    rbusError_t rc = RBUS_ERROR_SUCCESS;

    EXPECT_CALL(*g_rbusMock, rbus_checkStatus())
        .Times(1)
        .WillOnce(Return(RBUS_ENABLED));

    EXPECT_CALL(*g_rbusMock, rbus_open(_, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_SUCCESS));

    EXPECT_CALL(*g_rbusMock, rbus_regDataElements(_, _, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_BUS_ERROR));

    EXPECT_CALL(*g_rbusMock, rbus_close(_))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_SUCCESS));

    rc = cmAgentLldRbusInit();

    EXPECT_EQ(rc, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, initLLDEnable)
{
    char LLDEnable[16] = "true";
    cmAgent_Lld_Enable.lldenable = true;

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(1);

    initLLDEnable();

    EXPECT_FALSE(cmAgent_Lld_Enable.lldenable);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, publishLLDEnableValueChange)
{
    rbusHandle_t cm_lld_rbus_handle = nullptr;
    const char* event_name = "LLD_ENABLE";
    bool eventOldData = false;
    cmAgent_Lld_Enable.lldenable = false;
    bool eventNewData = true;
    cmAgent_Lld_Enable.lldenable = eventNewData;

    rbusEvent_t event;
    rbusObject_t data;
    rbusValue_t value;
    rbusValue_t oldVal;
    rbusValue_t byVal;
    rbusError_t ret = RBUS_ERROR_SUCCESS;

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(3)
        .WillRepeatedly(Return(reinterpret_cast<rbusValue_t>(0x5678)));

    EXPECT_CALL(*g_rbusMock, rbusObject_Init(_, _))
        .Times(1)
        .WillOnce(Return(reinterpret_cast<rbusObject_t>(0x1234)));

    EXPECT_CALL(*g_rbusMock, rbusValue_SetBoolean(_, _))
        .Times(2);

    EXPECT_CALL(*g_rbusMock, rbusValue_SetString(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusObject_SetValue(_, _, _))
        .Times(3);

    EXPECT_CALL(*g_rbusMock, rbusEvent_Publish(_, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_SUCCESS));

    EXPECT_CALL(*g_rbusMock, rbusValue_Release(_))
        .Times(3);

    EXPECT_CALL(*g_rbusMock, rbusObject_Release(_))
        .Times(1);

    ret = sendBoolUpdateEvent(cm_lld_rbus_handle, (char *)event_name, eventNewData, eventOldData);

    EXPECT_EQ(ret, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, lldEventSubHandler_Subscribe)
{
    rbusHandle_t handleLld = nullptr;
    rbusEventSubAction_t action = RBUS_EVENT_ACTION_SUBSCRIBE;
    const char* eventName = LLD_ENABLE_TR181;
    rbusFilter_t filter = reinterpret_cast<rbusFilter_t>(0x1234);
    int32_t interval = 0;
    bool autoPublishLld = false;

    rbusError_t result = lldEventSubHandler(handleLld, action, (char *)eventName, filter, interval, &autoPublishLld);

    EXPECT_EQ(result, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, lldEventSubHandler_Unsubscribe)
{
    rbusHandle_t handleLld = nullptr;
    rbusEventSubAction_t action = RBUS_EVENT_ACTION_UNSUBSCRIBE;
    const char* eventName = LLD_ENABLE_TR181;
    rbusFilter_t filter = reinterpret_cast<rbusFilter_t>(0x1234);
    int32_t interval = 0;
    bool autoPublishLld = false;

    rbusError_t result = lldEventSubHandler(handleLld, action, (char *)eventName, filter, interval, &autoPublishLld);

    EXPECT_EQ(result, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, lldEventSubHandler_InvalidInput)
{
    rbusHandle_t handleLld = nullptr;
    rbusEventSubAction_t action = RBUS_EVENT_ACTION_SUBSCRIBE;
    const char* eventName = "InvalidInput";
    rbusFilter_t filter = reinterpret_cast<rbusFilter_t>(0x1234);
    int32_t interval = 0;
    bool autoPublishLld = false;

    rbusError_t result = lldEventSubHandler(handleLld, action, (char *)eventName, filter, interval, &autoPublishLld);

    EXPECT_EQ(result, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, Rbus_LLDEnabled_SetParamBoolValue)
{
    const char *pParamName = "Enable";
    BOOL bValue = true;
    cmAgent_Lld_Enable.lldenable = false;

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(_, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(3);

    EXPECT_CALL(*g_rbusMock, rbusObject_Init(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusValue_SetBoolean(_, _))
        .Times(2);

    EXPECT_CALL(*g_rbusMock, rbusValue_SetString(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusObject_SetValue(_, _, _))
        .Times(3);

    EXPECT_CALL(*g_rbusMock, rbusEvent_Publish(_, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_SUCCESS));
    
    EXPECT_CALL(*g_rbusMock, rbusValue_Release(_))
        .Times(3);
    
    EXPECT_CALL(*g_rbusMock, rbusObject_Release(_))
        .Times(1);

    EXPECT_EQ(Rbus_LLDEnabled_SetParamBoolValue(nullptr, (char *)pParamName, bValue), TRUE);

    EXPECT_TRUE(cmAgent_Lld_Enable.lldenable);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, Rbus_LLDEnabled_SetParamBoolValue_false)
{
    const char *pParamName = "Enable";
    BOOL bValue = true;
    cmAgent_Lld_Enable.lldenable = false;

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(_, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(3);

    EXPECT_CALL(*g_rbusMock, rbusObject_Init(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusValue_SetBoolean(_, _))
        .Times(2);

    EXPECT_CALL(*g_rbusMock, rbusValue_SetString(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusObject_SetValue(_, _, _))
        .Times(3);

    EXPECT_CALL(*g_rbusMock, rbusEvent_Publish(_, _))
        .Times(1)
        .WillOnce(Return(RBUS_ERROR_SUCCESS));
    
    EXPECT_CALL(*g_rbusMock, rbusValue_Release(_))
        .Times(3);
    
    EXPECT_CALL(*g_rbusMock, rbusObject_Release(_))
        .Times(1);

    publishLLDEnableValueChange(bValue);

    EXPECT_EQ(Rbus_LLDEnabled_SetParamBoolValue(nullptr, (char *)pParamName, bValue), FALSE);

    EXPECT_TRUE(cmAgent_Lld_Enable.lldenable);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, Rbus_LLDEnabled_SetParamBoolValue_SameValueTrue)
{
    const char *pParamName = "Enable";
    BOOL bValue = true;
    cmAgent_Lld_Enable.lldenable = true;

    EXPECT_EQ(Rbus_LLDEnabled_SetParamBoolValue(nullptr, (char *)pParamName, bValue), false);

    EXPECT_TRUE(cmAgent_Lld_Enable.lldenable);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, Rbus_LLDEnabled_SetParamBoolValue_SameValueFalse)
{
    const char *pParamName = "Enable";
    BOOL bValue = false;
    cmAgent_Lld_Enable.lldenable = false;

    EXPECT_EQ(Rbus_LLDEnabled_SetParamBoolValue(nullptr, (char *)pParamName, bValue), false);

    EXPECT_FALSE(cmAgent_Lld_Enable.lldenable);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, Rbus_LLDEnabled_SetParamBoolValue_InvalidInput)
{
    const char *pParamName = "InvalidInput";
    BOOL bValue = true;
    cmAgent_Lld_Enable.lldenable = false;

    EXPECT_EQ(Rbus_LLDEnabled_SetParamBoolValue(nullptr, (char *)pParamName, bValue), false);

    EXPECT_FALSE(cmAgent_Lld_Enable.lldenable);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, getLLDBoolHandler_ValidInput_true)
{
    rbusHandle_t handleLld = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusGetHandlerOptions_t opts;
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x5678);
    char LLDEnable[16] = "true";
    cmAgent_Lld_Enable.lldenable = true;

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return(LLD_ENABLE_TR181));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(1)
        .WillOnce(Return(value));

    EXPECT_CALL(*g_rbusMock, rbusValue_SetBoolean(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusProperty_SetValue(property, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusValue_Release(_))
        .Times(1);

    rbusError_t result = getLLDBoolHandler(handleLld, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, getLLDBoolHandler_ValidInput_false)
{
    rbusHandle_t handleLld = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusGetHandlerOptions_t opts;
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x5678);
    char LLDEnable[16] = "false";
    cmAgent_Lld_Enable.lldenable = false;

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return(LLD_ENABLE_TR181));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(1)
        .WillOnce(Return(value));

    EXPECT_CALL(*g_rbusMock, rbusValue_SetBoolean(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusProperty_SetValue(property, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusValue_Release(_))
        .Times(1);

    rbusError_t result = getLLDBoolHandler(handleLld, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, getLLDBoolHandler_InvalidInput)
{
    rbusHandle_t handleLld = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusGetHandlerOptions_t opts;
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x5678);
    char LLDEnable[16] = "false";
    cmAgent_Lld_Enable.lldenable = false;

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return("InvalidInput"));

    rbusError_t result = getLLDBoolHandler(handleLld, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_INVALID_INPUT);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, setLLDEnableBoolHandler)
{
    rbusHandle_t handleLld = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusSetHandlerOptions_t opts;
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x5678);
    char LLDEnable[16] = "true";

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(_, _))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(3);

    EXPECT_CALL(*g_rbusMock, rbusValue_SetBoolean(_, _))
        .Times(2);

    EXPECT_CALL(*g_rbusMock, rbusValue_SetString(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusObject_Init(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusObject_SetValue(_, _, _))
        .Times(3);
    
    EXPECT_CALL(*g_rbusMock, rbusEvent_Publish(_, _))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return(LLD_ENABLE_TR181));

    EXPECT_CALL(*g_rbusMock, rbusValue_GetType(value))
        .Times(1)
        .WillOnce(Return(RBUS_BOOLEAN));

    EXPECT_CALL(*g_rbusMock, rbusValue_GetBoolean(value))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetValue(property))
        .Times(1)
        .WillOnce(Return(value));

    EXPECT_CALL(*g_rbusMock, rbusValue_Release(_))
        .Times(3);

    EXPECT_CALL(*g_rbusMock, rbusObject_Release(_))
        .Times(1);

    rbusError_t result = setLLDEnableBoolHandler(handleLld, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_SUCCESS);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, setLLDEnableBoolHandler_InvalidInput)
{
    rbusHandle_t handleLld = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusSetHandlerOptions_t opts;
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x5678);
    char LLDEnable[16] = "true";

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetValue(property))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return("InvalidInput"));

    rbusError_t result = setLLDEnableBoolHandler(handleLld, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_BUS_ERROR);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, setLLDEnableBoolHandler_InvalidType)
{
    rbusHandle_t handleLld = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusSetHandlerOptions_t opts;
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x5678);
    char LLDEnable[16] = "true";

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return(LLD_ENABLE_TR181));

    EXPECT_CALL(*g_rbusMock, rbusValue_GetType(value))
        .Times(1);

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetValue(property))
        .Times(1)
        .WillOnce(Return(value));

    rbusError_t result = setLLDEnableBoolHandler(handleLld, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_BUS_ERROR);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, setLLDEnableBoolHandler_NullValue)
{
    rbusHandle_t handleLld = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusSetHandlerOptions_t opts;
    rbusValue_t value = nullptr;
    char LLDEnable[16] = "true";

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return(LLD_ENABLE_TR181));

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetValue(property))
        .Times(1)
        .WillOnce(Return(value));

    rbusError_t result = setLLDEnableBoolHandler(handleLld, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_BUS_ERROR);
}

TEST_F(CcspCMAgentRbusHandlerApisTestFixture, setLLDEnableBoolHandler_SetParamBoolValueFailed)
{
    rbusHandle_t handleLld = nullptr;
    rbusProperty_t property = reinterpret_cast<rbusProperty_t>(0x1234);
    rbusSetHandlerOptions_t opts;
    rbusValue_t value = reinterpret_cast<rbusValue_t>(0x5678);
    char LLDEnable[16] = "true";

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetName(property))
        .Times(1)
        .WillOnce(Return(LLD_ENABLE_TR181));

    EXPECT_CALL(*g_rbusMock, rbusValue_GetType(value))
        .Times(1)
        .WillOnce(Return(RBUS_BOOLEAN));

    EXPECT_CALL(*g_rbusMock, rbusValue_GetBoolean(value))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(*g_rbusMock, rbusProperty_GetValue(property))
        .Times(1)
        .WillOnce(Return(value));

    rbusError_t result = setLLDEnableBoolHandler(handleLld, property, &opts);

    EXPECT_EQ(result, RBUS_ERROR_BUS_ERROR);
}