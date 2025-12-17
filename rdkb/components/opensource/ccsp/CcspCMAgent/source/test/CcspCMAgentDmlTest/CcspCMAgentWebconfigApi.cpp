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

class CcspCMAgentWebconfigApiTestFixture : public ::testing::Test {
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

// Unit Test for cm_agent_webconfig_api.c file


TEST_F(CcspCMAgentWebconfigApiTestFixture, get_base64_decodedbuffer)
{
    char *buffer = NULL;
    char *pString = NULL;
    int size = 0;
    int decodeMsgSize = 0;
    char *decodeMsg = NULL;

    pString = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(pString, nullptr);

    decodeMsg = (char *) malloc(sizeof(char) * decodeMsgSize);
    EXPECT_NE(decodeMsg, nullptr);

    EXPECT_CALL(*g_base64Mock, b64_get_decoded_buffer_size(_))
        .Times(1)
        .WillOnce(Return(16));

    EXPECT_CALL(*g_base64Mock, b64_decode(_, _, _))
        .Times(1)
        .WillOnce(Return(16));

    EXPECT_EQ(get_base64_decodedbuffer(pString, &buffer, &size), 0);
    EXPECT_NE(buffer, nullptr);

    free(pString);
    pString = NULL;
    free(decodeMsg);
    decodeMsg = NULL;
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, get_base64_decodedbuffer_null_buffer)
{
    char *buffer = NULL;
    char *pString = NULL;
    int size = 0;
    int decodeMsgSize = 0;
    char *decodeMsg = NULL;

    decodeMsg = (char *) malloc(sizeof(char) * decodeMsgSize);
    EXPECT_NE(decodeMsg, nullptr);

    EXPECT_EQ(get_base64_decodedbuffer(pString, NULL, &size), -1);

    free(decodeMsg);
    decodeMsg = NULL;
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, get_msgpack_unpack_status_msgpack_unpack_success)
{
    char *decodedbuf = NULL;
    msgpack_zone mempool;
    msgpack_object deserialized;
    msgpack_unpack_return unpack_ret;

    decodedbuf = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(decodedbuf, nullptr);

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_init(_, _))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(MSGPACK_UNPACK_SUCCESS));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_destroy(_))
        .Times(1);

    unpack_ret = get_msgpack_unpack_status(decodedbuf, 16);
    EXPECT_EQ(unpack_ret, MSGPACK_UNPACK_SUCCESS);

    free(decodedbuf);
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, get_msgpack_unpack_status_msgpack_unpack_extra_bytes)
{
    char *decodedbuf = NULL;
    msgpack_zone mempool;
    msgpack_object deserialized;
    msgpack_unpack_return unpack_ret;

    decodedbuf = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(decodedbuf, nullptr);

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_init(_, _))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(MSGPACK_UNPACK_EXTRA_BYTES));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_destroy(_))
        .Times(1);

    unpack_ret = get_msgpack_unpack_status(decodedbuf, 16);
    EXPECT_EQ(unpack_ret, MSGPACK_UNPACK_EXTRA_BYTES);

    free(decodedbuf);
    decodedbuf = NULL;
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, get_msgpack_unpack_status_msgpack_unpack_continue)
{
    char *decodedbuf = NULL;
    msgpack_zone mempool;
    msgpack_object deserialized;
    msgpack_unpack_return unpack_ret;

    decodedbuf = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(decodedbuf, nullptr);

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_init(_, _))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(MSGPACK_UNPACK_CONTINUE));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_destroy(_))
        .Times(1);

    unpack_ret = get_msgpack_unpack_status(decodedbuf, 16);
    EXPECT_EQ(unpack_ret, MSGPACK_UNPACK_CONTINUE);

    free(decodedbuf);
    decodedbuf = NULL;
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, get_msgpack_unpack_status_msgpack_unpack_parse_error)
{
    char *decodedbuf = NULL;
    msgpack_zone mempool;
    msgpack_object deserialized;
    msgpack_unpack_return unpack_ret;

    decodedbuf = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(decodedbuf, nullptr);

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_init(_, _))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(MSGPACK_UNPACK_PARSE_ERROR));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_destroy(_))
        .Times(1);

    unpack_ret = get_msgpack_unpack_status(decodedbuf, 16);
    EXPECT_EQ(unpack_ret, MSGPACK_UNPACK_PARSE_ERROR);

    free(decodedbuf);
    decodedbuf = NULL;
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, get_msgpack_unpack_status_msgpack_unpack_nomem_error)
{
    char *decodedbuf = NULL;
    msgpack_zone mempool;
    msgpack_object deserialized;
    msgpack_unpack_return unpack_ret;

    decodedbuf = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(decodedbuf, nullptr);

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_init(_, _))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack(_, _, _, _, _))
        .Times(1)
        .WillOnce(Return(MSGPACK_UNPACK_NOMEM_ERROR));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_destroy(_))
        .Times(1);

    unpack_ret = get_msgpack_unpack_status(decodedbuf, 16);
    EXPECT_EQ(unpack_ret, MSGPACK_UNPACK_NOMEM_ERROR);

    free(decodedbuf);
    decodedbuf = NULL;
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, get_msgpack_unpack_status_null_decodedbuf)
{
    char *decodedbuf = NULL;
    msgpack_zone mempool;
    msgpack_object deserialized;
    msgpack_unpack_return unpack_ret;

    unpack_ret = get_msgpack_unpack_status(NULL, 16);
    EXPECT_EQ(unpack_ret, MSGPACK_UNPACK_NOMEM_ERROR);
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, processcmagentWebConfigRequest_blob_exec_success)
{
    pErr execRetVal = NULL;
    cmagentdoc_t *cd = NULL;

    execRetVal = (pErr) malloc (sizeof(Err));
    EXPECT_NE(execRetVal, nullptr);

    cd = (cmagentdoc_t *) malloc (sizeof(cmagentdoc_t));
    EXPECT_NE(cd, nullptr);

    memset(execRetVal, 0, sizeof(Err));

    execRetVal->ErrorCode = BLOB_EXEC_SUCCESS;

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _)) 
        .Times(1);

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

    EXPECT_CALL(*g_syseventMock, sysevent_set(_, _, _, _, _))
        .Times(1);
    
    execRetVal = processcmagentWebConfigRequest(cd);
    EXPECT_EQ(execRetVal->ErrorCode, BLOB_EXEC_SUCCESS);

    free(execRetVal);
    free(cd);
}

// write the GTEST test case for processcmagentWebConfigRequest with execRetVal == NULL

TEST_F(CcspCMAgentWebconfigApiTestFixture, processcmagentWebConfigRequest_blob_exec_null)
{
    pErr execRetVal = NULL;
    
    execRetVal = processcmagentWebConfigRequest(NULL);
    EXPECT_EQ(execRetVal->ErrorCode, BLOB_EXEC_FAILURE);
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, rollbackcmagentFailureConf)
{
    int ret = 0;
    bool oldval = 0;
    bool LLdMarkingRules_Enable = 1;

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(_, _))
        .Times(2);

    EXPECT_CALL(*g_rbusMock, rbusValue_Init(_))
        .Times(6);

    EXPECT_CALL(*g_rbusMock, rbusObject_Init(_, _))
        .Times(2);

    EXPECT_CALL(*g_rbusMock, rbusValue_SetBoolean(_, _))
        .Times(4);

    EXPECT_CALL(*g_rbusMock, rbusValue_SetString(_, _))
        .Times(2);

    EXPECT_CALL(*g_rbusMock, rbusObject_SetValue(_, _, _))
        .Times(6);

    EXPECT_CALL(*g_rbusMock, rbusEvent_Publish(_, _))
        .Times(2);
    
    EXPECT_CALL(*g_rbusMock, rbusValue_Release(_))
        .Times(6);
    
    EXPECT_CALL(*g_rbusMock, rbusObject_Release(_))
        .Times(2);

    EXPECT_CALL(*g_syseventMock, sysevent_set(_, _, _, _, _))
        .Times(1);

    publishLLDEnableValueChange(oldval);

    ret = rollbackcmagentFailureConf();
    EXPECT_EQ(ret, 0);
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, rollbackcmagentFailureConf_same_value)
{
    int ret = 0;
    bool oldval = 1;
    bool LLdMarkingRules_Enable = 1;

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

    EXPECT_CALL(*g_syseventMock, sysevent_set(_, _, _, _, _))
        .Times(1);

    ret = rollbackcmagentFailureConf();
    EXPECT_EQ(ret, 0);
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, getcmagentBlobVersion)
{
    char subdoc_ver[64] = {0}, buf[72] = {0};
    const char *subdoc = "test";
    uint32_t version = 0;

    snprintf(buf,sizeof(buf),"%s_version",subdoc);

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _)) 
        .Times(1);

    version = getcmagentBlobVersion((char *)subdoc);
    EXPECT_EQ(version, 0);
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, getcmagentBlobVersion_syscfg_get_fail)
{
    char subdoc_ver[64] = {0}, buf[72] = {0};
    const char *subdoc = "test";
    uint32_t version = 0;

    snprintf(buf,sizeof(buf),"%s_version",subdoc);

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _)) 
        .Times(1)
        .WillOnce(Return(1));

    version = getcmagentBlobVersion((char *)subdoc);
    EXPECT_EQ(version, 0);
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, setcmagentBlobVersion)
{
    char subdoc_ver[64] = {0}, buf[72] = {0};
    const char *subdoc = "test";
    uint32_t version = 1;
    int ret = 0;

    snprintf(subdoc_ver,sizeof(subdoc_ver),"%u",version);
    snprintf(buf,sizeof(buf),"%s_version",subdoc);

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns_commit(_, _)) 
        .Times(1);

    ret = setcmagentBlobVersion((char *)subdoc, version);
    EXPECT_EQ(ret, 0);
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, setcmagentBlobVersion_syscfg_set_fail)
{
    char subdoc_ver[64] = {0}, buf[72] = {0};
    const char *subdoc = "test";
    uint32_t version = 1;
    int ret = 0;

    snprintf(subdoc_ver,sizeof(subdoc_ver),"%u",version);
    snprintf(buf,sizeof(buf),"%s_version",subdoc);

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns_commit(_, _)) 
        .Times(1)
        .WillOnce(Return(1));

    ret = setcmagentBlobVersion((char *)subdoc, version);
    EXPECT_EQ(ret, -1);
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, WebConfig_blob_handler_null_Encoded_data)
{
    char *Encoded_data = NULL;
    bool ret = false;

    ret = WebConfig_blob_handler(Encoded_data);
    EXPECT_EQ(ret, false);
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, WebConfig_blob_handler_b64_decode_fail)
{
    char *decodeMsg = NULL;
    int size =0;
    int retval = 0;
    msgpack_unpack_return unpack_ret = MSGPACK_UNPACK_SUCCESS;

    char *Encoded_data = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(Encoded_data, nullptr);

    EXPECT_CALL(*g_base64Mock, b64_get_decoded_buffer_size(_))
        .Times(2)
        .WillRepeatedly(Return(16));

    EXPECT_CALL(*g_base64Mock, b64_decode(_, _, _))
        .Times(2)
        .WillRepeatedly(Return(16));

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

    EXPECT_EQ(get_base64_decodedbuffer(Encoded_data, &decodeMsg, &size), 0);

    bool ret = WebConfig_blob_handler(Encoded_data);
    EXPECT_EQ(ret, true);

    free(Encoded_data);
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, WebConfig_blob_handler_b64_decode_success)
{
    char *decodeMsg = NULL;
    cmagentdoc_t *gd = NULL;
    int size =0;
    int retval = 0;
    msgpack_unpack_return unpack_ret = MSGPACK_UNPACK_SUCCESS;

    char *Encoded_data = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(Encoded_data, nullptr);

    EXPECT_CALL(*g_base64Mock, b64_get_decoded_buffer_size(_))
        .Times(2)
        .WillRepeatedly(Return(16));

    EXPECT_CALL(*g_base64Mock, b64_decode(_, _, _))
        .Times(2)
        .WillRepeatedly(Return(16));

    EXPECT_EQ(get_base64_decodedbuffer(Encoded_data, &decodeMsg, &size), 0);

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_init(_, _))
        .Times(2)
        .WillRepeatedly(Return(true));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack(_, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(MSGPACK_UNPACK_SUCCESS));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack_next(_, _, _, _))
        .Times(2);

    EXPECT_CALL(*g_msgpackMock, msgpack_object_print(_, _))
        .Times(2);

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_destroy(_))
        .Times(2);

    EXPECT_EQ(get_msgpack_unpack_status(decodeMsg, size), MSGPACK_UNPACK_SUCCESS);

    EXPECT_EQ(cmagentdocConvert(decodeMsg, size), gd);

    execData *execDataGm = NULL ;
    execDataGm = (execData*) malloc (sizeof(execData));
    EXPECT_NE(execDataGm, nullptr);

    bool ret = WebConfig_blob_handler(Encoded_data);
    EXPECT_EQ(ret, true);

    free(Encoded_data);
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, WebConfig_blob_handler_b64_decode_null_decodeMsg)
{
    char *decodeMsg = NULL;
    int size =0;
    int retval = 0;
    msgpack_unpack_return unpack_ret = MSGPACK_UNPACK_SUCCESS;

    char *Encoded_data = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(Encoded_data, nullptr);

    EXPECT_CALL(*g_base64Mock, b64_get_decoded_buffer_size(_))
        .Times(1)
        .WillOnce(Return(16));

    EXPECT_CALL(*g_base64Mock, b64_decode(_, _, _))
        .Times(1)
        .WillOnce(Return(16));

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_init(_, _))
        .Times(1);

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack(_, _, _, _, _))
        .Times(1);

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_destroy(_))
        .Times(1);

    EXPECT_EQ(get_base64_decodedbuffer(Encoded_data, NULL, &size), -1);

    bool ret = WebConfig_blob_handler(Encoded_data);
    EXPECT_EQ(ret, false);

    free(Encoded_data);
}

TEST_F(CcspCMAgentWebconfigApiTestFixture, WebConfig_blob_handler_gd_not_null)
{
    char *decodeMsg = NULL;
    cmagentdoc_t *gd = NULL;
    int size =0;
    int retval = 0;
    msgpack_unpack_return unpack_ret = MSGPACK_UNPACK_SUCCESS;

    char *Encoded_data = (char *) malloc(sizeof(char) * 16);
    EXPECT_NE(Encoded_data, nullptr);

    EXPECT_CALL(*g_base64Mock, b64_get_decoded_buffer_size(_))
        .Times(2)
        .WillRepeatedly(Return(16));

    EXPECT_CALL(*g_base64Mock, b64_decode(_, _, _))
        .Times(2)
        .WillRepeatedly(Return(16));

    EXPECT_EQ(get_base64_decodedbuffer(Encoded_data, &decodeMsg, &size), 0);

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_init(_, _))
        .Times(2)
        .WillRepeatedly(Return(true));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack(_, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(MSGPACK_UNPACK_SUCCESS));

    EXPECT_CALL(*g_msgpackMock, msgpack_unpack_next(_, _, _, _))
        .Times(2);

    EXPECT_CALL(*g_msgpackMock, msgpack_object_print(_, _))
        .Times(2);

    EXPECT_CALL(*g_msgpackMock, msgpack_zone_destroy(_))
        .Times(2);

    EXPECT_EQ(get_msgpack_unpack_status(decodeMsg, size), MSGPACK_UNPACK_SUCCESS);

    EXPECT_EQ(cmagentdocConvert(decodeMsg, size), gd);

    gd = (cmagentdoc_t *) malloc (sizeof(cmagentdoc_t));
    EXPECT_NE(gd, nullptr);

    execData *execDataGm = NULL ;
    execDataGm = (execData*) malloc (sizeof(execData));
    EXPECT_NE(execDataGm, nullptr);

    bool ret = WebConfig_blob_handler(Encoded_data);
    EXPECT_EQ(ret, true);

    free(Encoded_data);
}