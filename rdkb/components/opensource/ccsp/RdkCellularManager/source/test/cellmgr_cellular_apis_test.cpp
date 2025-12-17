/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2022 Sky
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 * Copyright 2022 RDK Management
 * Licensed under the Apache License, Version 2.0
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <experimental/filesystem>
#include "mocks/cellular_api_mock.h"
#include "cellmgr_mock.h"
#define MOCK_CELLULAR_HAL_API_2
#define MOCK_CELLULAR_MGR_RDKBUS_2
#define MOCK_CELLULAR_MGR_SM_2
#define MOCK_CELLULAR_MGR_PTHREAD_2

extern "C"
{
#include "cellular_hal.h"
#include "cellularmgr_cellular_apis.h"
#include "cellularmgr_bus_utils.h"
#include "cellularmgr_sm.h"
#ifdef RBUS_BUILD_FLAG_ENABLE
#include <rbus/rbus.h>
#include "cellularmgr_rbus_events.h"
extern CellularMGR_rbusSubListSt gRBUSSubListSt;
#endif
}

using namespace std;
using std::experimental::filesystem::exists;
using ::testing::_;
using ::testing::Return;
using ::testing::StrEq;

rbusHandle_t gBusHandle = NULL;
CellularAPIMock * g_CellularAPIMock;

#ifdef  RBUS_BUILD_FLAG_ENABLE
TEST(CellularManagerTest, GetCellLocationSubscriptionStatus_NoSubscription)
{
    gRBUSSubListSt.stCellLocation.GlobalCellIdSubFlag = false;
    gRBUSSubListSt.stCellLocation.ServingCellIdSubFlag = false;
    gRBUSSubListSt.stCellLocation.BandInfoSubFlag = false;

    CELL_LOCATION_SUBINFO result = CellularMgr_GetCellLocationSubsciptionStatus();

    EXPECT_EQ(result, LOC_NO_SUB_HAL_VALUE);
}

TEST(CellularManagerTest, GetCellLocationSubscriptionStatus_WithSubscription)
{
    gRBUSSubListSt.stCellLocation.GlobalCellIdSubFlag = true;
    gRBUSSubListSt.stCellLocation.ServingCellIdSubFlag = false;
    gRBUSSubListSt.stCellLocation.BandInfoSubFlag = true;

    CELL_LOCATION_SUBINFO result = CellularMgr_GetCellLocationSubsciptionStatus();

    EXPECT_EQ(result, LOC_SUB_CACHE_VALUE);
}

TEST(CellularManagerTest_1, GetCellLocationSubscriptionStatus_WithSubscription)
{
    gRBUSSubListSt.stCellLocation.GlobalCellIdSubFlag = false;
    gRBUSSubListSt.stCellLocation.ServingCellIdSubFlag = true;
    gRBUSSubListSt.stCellLocation.BandInfoSubFlag = true;

    CELL_LOCATION_SUBINFO result = CellularMgr_GetCellLocationSubsciptionStatus();

    EXPECT_EQ(result, LOC_SUB_CACHE_VALUE);
}

TEST(RadioSignalTest, CellularMgr_GetRadioSignalSubsciptionStatus_NoSubscription)
{
    gRBUSSubListSt.stRadioSignal.RSSISubFlag = false;
    gRBUSSubListSt.stRadioSignal.SNRSubFlag = false;
    gRBUSSubListSt.stRadioSignal.RSRPSubFlag = false;
    gRBUSSubListSt.stRadioSignal.RSRQSubFlag = false;
    gRBUSSubListSt.stRadioSignal.TRXSubFlag = false;
    gRBUSSubListSt.stRadioSignal.RadioEnvCondSubFlag = false;

    CELLULAR_RADIO_SIGNAL_SUBINFO result = CellularMgr_GetRadioSignalSubsciptionStatus();

    EXPECT_EQ(result, SIGNAL_NO_SUB_HAL_VALUE);
}

TEST(RadioSignalTest_1, CellularMgr_GetRadioSignalSubsciptionStatus_WithSubscription)
{
    gRBUSSubListSt.stRadioSignal.RSSISubFlag = true;
    gRBUSSubListSt.stRadioSignal.SNRSubFlag = false;
    gRBUSSubListSt.stRadioSignal.RSRPSubFlag = true;
    gRBUSSubListSt.stRadioSignal.RSRQSubFlag = true;
    gRBUSSubListSt.stRadioSignal.TRXSubFlag = false;
    gRBUSSubListSt.stRadioSignal.RadioEnvCondSubFlag = false;

    CELLULAR_RADIO_SIGNAL_SUBINFO result = CellularMgr_GetRadioSignalSubsciptionStatus();

    EXPECT_EQ(result, SIGNAL_SUB_CACHE_VALUE);
}

TEST(RadioSignalTest_2, CellularMgr_GetRadioSignalSubsciptionStatus_WithSubscription)
{
    gRBUSSubListSt.stRadioSignal.RSSISubFlag = false;
    gRBUSSubListSt.stRadioSignal.SNRSubFlag = false;
    gRBUSSubListSt.stRadioSignal.RSRPSubFlag = true;
    gRBUSSubListSt.stRadioSignal.RSRQSubFlag = true;
    gRBUSSubListSt.stRadioSignal.TRXSubFlag = false;
    gRBUSSubListSt.stRadioSignal.RadioEnvCondSubFlag = true;

    CELLULAR_RADIO_SIGNAL_SUBINFO result = CellularMgr_GetRadioSignalSubsciptionStatus();

    EXPECT_EQ(result, SIGNAL_SUB_CACHE_VALUE);
}

TEST(RadioSignalTest_3, CellularMgr_GetRadioSignalSubsciptionStatus_WithSubscription)
{
    gRBUSSubListSt.stRadioSignal.RSSISubFlag = false;
    gRBUSSubListSt.stRadioSignal.SNRSubFlag = false;
    gRBUSSubListSt.stRadioSignal.RSRPSubFlag = false;
    gRBUSSubListSt.stRadioSignal.RSRQSubFlag = true;
    gRBUSSubListSt.stRadioSignal.TRXSubFlag = false;
    gRBUSSubListSt.stRadioSignal.RadioEnvCondSubFlag = false;

    CELLULAR_RADIO_SIGNAL_SUBINFO result = CellularMgr_GetRadioSignalSubsciptionStatus();

    EXPECT_EQ(result, SIGNAL_SUB_CACHE_VALUE);
}
#endif

/*
TEST_F(CellularManagerTestFixture, GetModemControlInterfaceStatus_Success)
{
     ON_CALL(*g_CellularAPIMock, cellular_hal_IsModemControlInterfaceOpened())
     .WillByDefault(Return(TRUE));
     printf("Entered\n");
     CELLULAR_CONTROL_INTERFACE_STATUS status = CONTROL_STATUS_OPENED;
     CELLULAR_CONTROL_INTERFACE_STATUS res = CellularMgr_GetModemControlInterfaceStatus();
     printf("Value:%d\n", res);
     EXPECT_EQ(res, status);
}

TEST_F(CellularManagerTestFixture, GetModemControlInterfaceStatus_Failure)
{
     ON_CALL(*g_CellularAPIMock, cellular_hal_IsModemControlInterfaceOpened())
     .WillByDefault(Return(0));

     CELLULAR_CONTROL_INTERFACE_STATUS status = CONTROL_STATUS_CLOSED;
     CELLULAR_CONTROL_INTERFACE_STATUS res = CellularMgr_GetModemControlInterfaceStatus();
     printf("Value:%d\n", res);
     EXPECT_EQ(res, status);
}

CellularMgrPolicyCtrlSMStruct *gpstCellularPolicyCtrl = NULL, ctx;
CELLULAR_INTERFACE_INFO interfaceInfo;

static CellLocationInfoStruct cellLocInfo = { 0 };

ACTION_P(SavePsmValueArg0GUint, value) {
    *value = *static_cast<CellLocationInfoStruct*>(arg0);
}

TEST_F (CellularManagerTestFixture, CellularMgr_CellLocationInfo_Test1)
{
        CELL_LOCATION_SUBINFO loc = LOC_NO_SUB_HAL_VALUE;
        Cellular_get_sm_ctx(&ctx);

        ON_CALL(*g_CellularAPIMock, cellular_hal_get_cell_location_info(_))
        .WillByDefault(::testing::DoAll(
        SavePsmValueArg0GUint(&cellLocInfo),
        ::testing::Return(RETURN_OK)
        ));

        EXPECT_EQ(RETURN_OK, CellularMgr_CellLocationInfo(&interfaceInfo,LOC_NO_SUB_HAL_VALUE));

        printf("Global cell id: %u\n", cellLocInfo.globalCellId);

        interfaceInfo.Global_cell_id = cellLocInfo.globalCellId;
        interfaceInfo.BandInfo = cellLocInfo.bandInfo;
        interfaceInfo.Serving_cell_id = cellLocInfo.servingCellId;

        EXPECT_EQ(cellLocInfo.globalCellId, interfaceInfo.Global_cell_id);
        EXPECT_EQ(cellLocInfo.bandInfo, interfaceInfo.BandInfo);
        EXPECT_EQ(cellLocInfo.servingCellId, interfaceInfo.Serving_cell_id);
}
*/
