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

class CcspCMAgentDeviceInfoDmlTestFixture : public ::testing::Test {
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
// Unit Test for cosa_device_info_dml.c file

TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_GetParamBoolValue_FirmwareDownloadNow)
{
    BOOL pBool = FALSE;
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareDownloadNow";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = TRUE;
    
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadNow"), strlen("X_RDKCENTRAL-COM_FirmwareDownloadNow"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(DeviceInfo_GetParamBoolValue(NULL, (char*)ParamName, &pBool), TRUE);
    EXPECT_FALSE(pBool);
    EXPECT_TRUE(pMyObject->Download_Control_Flag);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_GetParamBoolValue_CableRfSignalStatus)
{
    BOOL pBool = FALSE;
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_CableRfSignalStatus";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadNow"), strlen("X_RDKCENTRAL-COM_FirmwareDownloadNow"), StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_CableRfSignalStatus"), strlen("X_RDKCENTRAL-COM_CableRfSignalStatus"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(DeviceInfo_GetParamBoolValue(NULL, (char*)ParamName, &pBool), TRUE);
    EXPECT_FALSE(pBool);
    EXPECT_TRUE(pMyObject->Download_Control_Flag);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_GetParamBoolValue_FirmwareDownloadNow_Disable)
{
    BOOL pBool = FALSE;
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareDownloadNow";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = FALSE;
    
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadNow"), strlen("X_RDKCENTRAL-COM_FirmwareDownloadNow"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(DeviceInfo_GetParamBoolValue(NULL, (char*)ParamName, &pBool), TRUE);
    EXPECT_FALSE(pBool);
    EXPECT_FALSE(pMyObject->Download_Control_Flag);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_GetParamStringValue_FirmwareDownloadStatus_InProgress)
{
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareDownloadStatus";
    char pValue[128] = {0};
    ULONG pUlSize = sizeof(pValue);

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(testing::SetArgPointee<3>(comparisonResult), testing::Return(EOK)));

    int dl_status1 = 50;
    const char *DL_Status1 = "In Progress"; 

    EXPECT_CALL(*g_cmHALMock, cm_hal_Get_HTTP_Download_Status())
        .Times(2)
        .WillRepeatedly(testing::Return(dl_status1));


    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(3)
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(CosaDmlDIGetDLStatus((ANSC_HANDLE)pMyObject, (char *)DL_Status1), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(DeviceInfo_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_GetParamStringValue_FirmwareDownloadStatus_Completed)
{
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareDownloadStatus";
    char pValue[128] = {0};
    ULONG pUlSize = sizeof(pValue);

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(testing::SetArgPointee<3>(comparisonResult), testing::Return(EOK)));

    int dl_status2 = 200;
    const char *DL_Status2 = "Completed"; 

    EXPECT_CALL(*g_cmHALMock, cm_hal_Get_HTTP_Download_Status())
        .Times(2)
        .WillRepeatedly(testing::Return(dl_status2));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(3)
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(CosaDmlDIGetDLStatus((ANSC_HANDLE)pMyObject, (char *)DL_Status2), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(DeviceInfo_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}   


TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_GetParamStringValue_FirmwareDownloadStatus_Failed)
{
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareDownloadStatus";
    char pValue[128] = {0};
    ULONG pUlSize = sizeof(pValue);

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(testing::SetArgPointee<3>(comparisonResult), testing::Return(EOK)));

    int dl_status3 = 400;
    const char *DL_Status3 = "Failed"; 

    EXPECT_CALL(*g_cmHALMock, cm_hal_Get_HTTP_Download_Status())
        .Times(2)
        .WillRepeatedly(testing::Return(dl_status3));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(3)
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(CosaDmlDIGetDLStatus((ANSC_HANDLE)pMyObject, (char *)DL_Status3), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(DeviceInfo_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}   

TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_GetParamStringValue_FirmwareDownloadStatus_NotStarted)
{
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareDownloadStatus";
    char pValue[128] = {0};
    ULONG pUlSize = sizeof(pValue);

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(testing::SetArgPointee<3>(comparisonResult), testing::Return(EOK)));

    int dl_status4 = 300;
    const char *DL_Status4 = "Not Started"; 

    EXPECT_CALL(*g_cmHALMock, cm_hal_Get_HTTP_Download_Status())
        .Times(2)
        .WillRepeatedly(testing::Return(dl_status4));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(3)
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(CosaDmlDIGetDLStatus((ANSC_HANDLE)pMyObject, (char *)DL_Status4), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(DeviceInfo_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_GetParamStringValue_FirmwareDownloadProtocol)
{
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareDownloadProtocol";
    char pValue[128] = {0};
    ULONG pUlSize = sizeof(pValue);

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadProtocol"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadProtocol"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(testing::SetArgPointee<3>(comparisonResult), testing::Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(2)
        .WillRepeatedly(testing::DoAll(
            testing::WithArgs<2>([&](char* dest) {
                strncpy(dest, "http", sizeof(pValue));
            }),
            testing::Return(0)));

    EXPECT_EQ(CosaDmlDIGetProtocol(pValue, pUlSize), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(DeviceInfo_GetParamStringValue(NULL, (char*)ParamName, pValue, &pUlSize), 0);

    EXPECT_STREQ(pValue, "http");

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_GetParamStringValue_FirmwareDownloadURL)
{
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareDownloadURL";
    char pValue[128] = {0};
    ULONG pUlSize = sizeof(pValue);

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = TRUE;

    memset(pMyObject->DownloadURL, 0, sizeof(pMyObject->DownloadURL));
    strncpy(pMyObject->DownloadURL, "https://dac15cdlserver.ae.ccp.xcal.tv/Images", sizeof(pMyObject->DownloadURL) - 1);
    pMyObject->DownloadURL[sizeof(pMyObject->DownloadURL) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadProtocol"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadProtocol"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadURL"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadURL"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(testing::SetArgPointee<3>(comparisonResult), testing::Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(
            testing::WithArgs<2>([&](char* dest) {
                strncpy(dest, "https://dac15cdlserver.ae.ccp.xcal.tv/Images", sizeof(pValue));
            }),
            testing::Return(0)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(CosaDmlDIGetURL((ANSC_HANDLE)pMyObject), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(DeviceInfo_GetParamStringValue(nullptr, (char*)ParamName, pValue, &pUlSize), 0);
    

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_GetParamStringValue_FirmwareDownloadURL_empty)
{
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareDownloadURL";
    char pValue[128] = {0};
    ULONG pUlSize = sizeof(pValue);

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = TRUE;

    memset(pMyObject->DownloadURL, 0, sizeof(pMyObject->DownloadURL));
    strncpy(pMyObject->DownloadURL, "", sizeof(pMyObject->DownloadURL) - 1);
    pMyObject->DownloadURL[sizeof(pMyObject->DownloadURL) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadProtocol"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadProtocol"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadURL"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadURL"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(testing::SetArgPointee<3>(comparisonResult), testing::Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(2)
        .WillRepeatedly(testing::DoAll(
            testing::WithArgs<2>([&](char* dest) {
                strncpy(dest, "", sizeof(pValue));
            }),
            testing::Return(0)));

    EXPECT_EQ(CosaDmlDIGetURL((ANSC_HANDLE)pMyObject), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_EQ(DeviceInfo_GetParamStringValue(nullptr, (char*)ParamName, pValue, &pUlSize), 0);
    
    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_GetParamStringValue_FirmwareToDownload)
{
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareToDownload";
    char pValue[128] = {0};
    ULONG pUlSize = sizeof(pValue);

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = TRUE;

    memset(pMyObject->Firmware_To_Download, 0, sizeof(pMyObject->Firmware_To_Download));
    strncpy(pMyObject->Firmware_To_Download, "CGA4332COM_7.6s3_DEV_sey.bin", sizeof(pMyObject->Firmware_To_Download) - 1);
    pMyObject->Firmware_To_Download[sizeof(pMyObject->Firmware_To_Download) - 1] = '\0';

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadProtocol"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadProtocol"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadURL"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadURL"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareToDownload"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareToDownload"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(testing::SetArgPointee<3>(comparisonResult), testing::Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(2);

    EXPECT_EQ(CosaDmlDIGetImage((ANSC_HANDLE)pMyObject), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(DeviceInfo_GetParamStringValue(nullptr, (char*)ParamName, pValue, &pUlSize), 0);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}


TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_GetParamStringValue_FirmwareToDownload_empty_factoryreset_case)
{
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareToDownload";
    char pValue[128] = {0};
    ULONG pUlSize = sizeof(pValue);

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = TRUE;

    memset(pMyObject->Firmware_To_Download, 0, sizeof(pMyObject->Firmware_To_Download));
    strncpy(pMyObject->Firmware_To_Download, "", sizeof(pMyObject->Firmware_To_Download) - 1);
    pMyObject->Firmware_To_Download[sizeof(pMyObject->Firmware_To_Download) - 1] = '\0';


    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadProtocol"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadProtocol"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadURL"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadURL"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareToDownload"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareToDownload"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(testing::SetArgPointee<3>(comparisonResult), testing::Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, _, _, _))
        .Times(3);

    EXPECT_EQ(CosaDmlDIGetURL((ANSC_HANDLE)pMyObject), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(1)
        .WillOnce(Return(EOK));
    

    EXPECT_EQ(DeviceInfo_GetParamStringValue(nullptr, (char*)ParamName, pValue, &pUlSize), 0);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_GetParamStringValue_FirmwareToDownload_empty_nonfactoryreset_case)
{
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareToDownload";
    char pValue[128] = {0};
    ULONG pUlSize = sizeof(pValue);

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = TRUE;

    memset(pMyObject->Firmware_To_Download, 0, sizeof(pMyObject->Firmware_To_Download));
    strncpy(pMyObject->Firmware_To_Download, "", sizeof(pMyObject->Firmware_To_Download) - 1);
    pMyObject->Firmware_To_Download[sizeof(pMyObject->Firmware_To_Download) - 1] = '\0';


    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadStatus"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadProtocol"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadProtocol"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadURL"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadURL"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1);

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareToDownload"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareToDownload"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(testing::DoAll(testing::SetArgPointee<3>(comparisonResult), testing::Return(EOK)));

    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("xconf_url"), _, _))
        .Times(1);

    char Last_reboot_reason[32] = "factory-reset";
    EXPECT_CALL(*g_syscfgMock, syscfg_get(_, StrEq("X_RDKCENTRAL-COM_LastRebootReason"), _, _))
        .Times(1)
        .WillOnce(testing::DoAll(
            testing::WithArgs<2>([&](char* dest) {
                strncpy(dest, "factory-reset", 32);
            }),
            testing::Return(0)));

    memset(pMyObject->Current_Firmware, 0, sizeof(pMyObject->Current_Firmware));
    strncpy(pMyObject->Current_Firmware, "", sizeof(pMyObject->Current_Firmware) - 1);
    pMyObject->Current_Firmware[sizeof(pMyObject->Current_Firmware) - 1] = '\0';    

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns_commit(_, _))
        .Times(1);

    EXPECT_EQ(CosaDmlDIGetURL((ANSC_HANDLE)pMyObject), ANSC_STATUS_SUCCESS);

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(EOK));

    EXPECT_EQ(DeviceInfo_GetParamStringValue(nullptr, (char*)ParamName, pValue, &pUlSize), 0);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_SetParamBoolValue_FirmwareDownloadNow_Enable_dlstatus150)
{
    BOOL bValue = TRUE;
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareDownloadNow";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadNow"), strlen("X_RDKCENTRAL-COM_FirmwareDownloadNow"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    memset(pMyObject->Firmware_To_Download, 0, sizeof(pMyObject->Firmware_To_Download));
    strncpy(pMyObject->Firmware_To_Download, "CGA4332COM_7.6s3_DEV_sey.bin", sizeof(pMyObject->Firmware_To_Download) - 1);
    pMyObject->Firmware_To_Download[sizeof(pMyObject->Firmware_To_Download) - 1] = '\0';

    memset(pMyObject->DownloadURL, 0, sizeof(pMyObject->DownloadURL));
    strncpy(pMyObject->DownloadURL, "https://dac15cdlserver.ae.ccp.xcal.tv/Images", sizeof(pMyObject->DownloadURL) - 1);
    pMyObject->DownloadURL[sizeof(pMyObject->DownloadURL) - 1] = '\0';


    EXPECT_CALL(*g_safecLibMock, _strncpy_s_chk(_, _, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(EOK));

    EXPECT_CALL(*g_safecLibMock, _strcasecmp_s_chk(_, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(EOK));

    EXPECT_CALL(*g_safecLibMock, _strcat_s_chk(_, _, _, _))
        .Times(8)
        .WillRepeatedly(Return(EOK));

    EXPECT_CALL(*g_cmHALMock, cm_hal_Set_HTTP_Download_Url(_, StrEq("CGA4332COM_7.6s3_DEV_sey.bin")))
        .Times(2)
        .WillRepeatedly(testing::Return(0));

    EXPECT_CALL(*g_cmHALMock, cm_hal_Get_HTTP_Download_Status())
        .Times(2)
        .WillRepeatedly(testing::Return(150));

    EXPECT_CALL(*g_cmHALMock, cm_hal_Set_HTTP_Download_Interface(_))
       .Times(2)
       .WillRepeatedly(testing::Return(0));

    EXPECT_CALL(*g_cmHALMock, cm_hal_HTTP_Download())
        .Times(testing::AtLeast(1))
        .WillRepeatedly(testing::Return(0));

    EXPECT_EQ(CosaDmlDIDownloadNow((ANSC_HANDLE)pMyObject), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(DeviceInfo_SetParamBoolValue(NULL, (char*)ParamName, bValue), TRUE);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_SetParamBoolValue_FirmwareDownloadNow_Enable_dlstatus200)
{
    BOOL bValue = TRUE;
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareDownloadNow";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadNow"), strlen("X_RDKCENTRAL-COM_FirmwareDownloadNow"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    memset(pMyObject->Firmware_To_Download, 0, sizeof(pMyObject->Firmware_To_Download));
    strncpy(pMyObject->Firmware_To_Download, "CGA4332COM_7.6s3_DEV_sey.bin", sizeof(pMyObject->Firmware_To_Download) - 1);
    pMyObject->Firmware_To_Download[sizeof(pMyObject->Firmware_To_Download) - 1] = '\0';

    memset(pMyObject->DownloadURL, 0, sizeof(pMyObject->DownloadURL));
    strncpy(pMyObject->DownloadURL, "https://dac15cdlserver.ae.ccp.xcal.tv/Images", sizeof(pMyObject->DownloadURL) - 1);
    pMyObject->DownloadURL[sizeof(pMyObject->DownloadURL) - 1] = '\0';


    EXPECT_CALL(*g_safecLibMock, _strncpy_s_chk(_, _, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(EOK));

    EXPECT_CALL(*g_safecLibMock, _strcasecmp_s_chk(_, _, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(EOK));

    EXPECT_CALL(*g_safecLibMock, _strcat_s_chk(_, _, _, _))
        .Times(8)
        .WillRepeatedly(Return(EOK));

    EXPECT_CALL(*g_cmHALMock, cm_hal_Set_HTTP_Download_Url(_, StrEq("CGA4332COM_7.6s3_DEV_sey.bin")))
        .Times(2)
        .WillRepeatedly(testing::Return(0));

    EXPECT_CALL(*g_cmHALMock, cm_hal_Get_HTTP_Download_Status())
        .Times(2)
        .WillRepeatedly(testing::Return(200));

    EXPECT_EQ(CosaDmlDIDownloadNow((ANSC_HANDLE)pMyObject), ANSC_STATUS_FAILURE);

    EXPECT_EQ(DeviceInfo_SetParamBoolValue(NULL, (char*)ParamName, bValue), TRUE);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_SetParamBoolValue_FirmwareDownloadNow_Disable)
{
    BOOL bValue = FALSE;
    int comparisonResult = 0;
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareDownloadNow";

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    pMyObject->Download_Control_Flag = FALSE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadNow"), strlen("X_RDKCENTRAL-COM_FirmwareDownloadNow"), StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_EQ(DeviceInfo_SetParamBoolValue(NULL, (char*)ParamName, bValue), TRUE);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}

TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_SetParamStringValue_FirmwareDownloadURL_Enable)
{
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareDownloadURL";
    const char *pString = "https://dac15cdlserver.ae.ccp.xcal.tv/Images";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;

    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pMyObject; 
    
    pMyObject->Download_Control_Flag = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadURL"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadURL"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(EOK));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns_commit(_, _))
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(_, _))
        .Times(4)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlDISetURL(hInsContext, (char *)pString), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(DeviceInfo_SetParamStringValue(hInsContext, (char*)ParamName, (char *)pString), TRUE);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}   


TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_SetParamStringValue_FirmwareToDownload_Enable)
{
    const char *ParamName = "X_RDKCENTRAL-COM_FirmwareToDownload";
    const char *pString = "CGA4332COM_7.6s3_DEV_sey.bin";
    int comparisonResult = 0;

    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;
    
    ANSC_HANDLE hInsContext = (ANSC_HANDLE)pMyObject; 

    pMyObject->Download_Control_Flag = TRUE;

    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareDownloadURL"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareDownloadURL"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1);
    EXPECT_CALL(*g_safecLibMock, _strcmp_s_chk(StrEq("X_RDKCENTRAL-COM_FirmwareToDownload"), 
                                               strlen("X_RDKCENTRAL-COM_FirmwareToDownload"), 
                                               StrEq(ParamName), _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgPointee<3>(comparisonResult), Return(EOK)));

    EXPECT_CALL(*g_safecLibMock, _strcpy_s_chk(_, _, _, _))
        .Times(2)
        .WillRepeatedly(Return(EOK));

    EXPECT_CALL(*g_syscfgMock, syscfg_set_nns(_, _))
        .Times(4)
        .WillRepeatedly(Return(0));

    EXPECT_CALL(*g_syscfgMock, syscfg_commit())
        .Times(2)
        .WillRepeatedly(Return(0));

    EXPECT_EQ(CosaDmlDISetImage(hInsContext, (char *)pString), ANSC_STATUS_SUCCESS);

    EXPECT_EQ(DeviceInfo_SetParamStringValue(hInsContext, (char*)ParamName, (char *)pString), TRUE);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}   

TEST_F(CcspCMAgentDeviceInfoDmlTestFixture, DeviceInfo_IsFileUpdateNeeded)
{
    g_pCosaBEManager = (PCOSA_BACKEND_MANAGER_OBJECT)malloc(sizeof(COSA_BACKEND_MANAGER_OBJECT));
    ASSERT_NE(g_pCosaBEManager, nullptr);

    g_pCosaBEManager->hDI = (PCOSA_DATAMODEL_DEVICEINFO)malloc(sizeof(COSA_DATAMODEL_DEVICEINFO));
    ASSERT_NE(g_pCosaBEManager->hDI, nullptr);

    PCOSA_DATAMODEL_DEVICEINFO pMyObject = (PCOSA_DATAMODEL_DEVICEINFO)g_pCosaBEManager->hDI;
    
    pMyObject->Download_Control_Flag = TRUE;

    memset(pMyObject->Firmware_To_Download, 0, sizeof(pMyObject->Firmware_To_Download));
    strncpy(pMyObject->Firmware_To_Download, "CGA4332COM_7.6s3_DEV_sey.bin", sizeof(pMyObject->Firmware_To_Download) - 1);
    pMyObject->Firmware_To_Download[sizeof(pMyObject->Firmware_To_Download) - 1] = '\0';

    memset(pMyObject->DownloadURL, 0, sizeof(pMyObject->DownloadURL));
    strncpy(pMyObject->DownloadURL, "https://dac15cdlserver.ae.ccp.xcal.tv/Images", sizeof(pMyObject->DownloadURL) - 1);
    pMyObject->DownloadURL[sizeof(pMyObject->DownloadURL) - 1] = '\0';

    EXPECT_EQ(IsFileUpdateNeeded((ANSC_HANDLE)pMyObject), TRUE);

    free(g_pCosaBEManager->hDI);
    g_pCosaBEManager->hDI = NULL;
    free(g_pCosaBEManager);
    g_pCosaBEManager = NULL;
}