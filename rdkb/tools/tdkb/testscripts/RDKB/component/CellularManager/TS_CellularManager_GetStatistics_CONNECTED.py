##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2024 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################
'''
<?xml version='1.0' encoding='utf-8'?>
<xml>
  <id></id>
  <!-- Do not edit id. This will be auto filled while exporting. If you are adding a new script keep the id empty -->
  <version>14</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_CellularManager_GetStatistics_CONNECTED</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>CellularManager_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>When Device.Cellular.X_RDK_Status == CONNECTED, Cellular manager will pull the Device.Cellular.Interface[i].X_RDK_Statistics every minute to provide subscription capability.</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>10</execution_time>
  <!--  -->
  <long_duration>false</long_duration>
  <!--  -->
  <advanced_script>false</advanced_script>
  <!-- execution_time is the time out time for test execution -->
  <remarks></remarks>
  <!-- Reason for skipping the tests if marked to skip -->
  <skip>false</skip>
  <!--  -->
  <box_types>
    <box_type>Broadband</box_type>
    <!--  -->
    <box_type>RPI</box_type>
    <!--  -->
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_CellularManager_11</test_case_id>
    <test_objective>When Device.Cellular.X_RDK_Status == CONNECTED, Cellular manager will pull the Device.Cellular.Interface[i].X_RDK_Statistics every minute to provide subscription capability.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>TDK agent should be running in the DUT and DUT should be online in TDK test manager.
Cellular Manager setup should be up and running.</pre_requisite>
    <api_or_interface_used>No</api_or_interface_used>
    <input_parameters>Device.Cellular.X_RDK_Status
Device.Cellular.Interface.1.X_RDK_Statistics.BytesReceived
Device.Cellular.Interface.1.X_RDK_Statistics.PacketsSent</input_parameters>
    <automation_approch>1. Load the tdkbtr181 module
2. Get Device.Cellular.X_RDK_Status
3. While  Device.Cellular.X_RDK_Status has the value CONNECTED, get Device.Cellular.Interface.1.X_RDK_Statistics.BytesReceived and Device.Cellular.Interface.1.X_RDK_Statistics.PacketsSent
4.Ensure the values of both dmls are nonzero
5.Unload the tdkbtr181 module</automation_approch>
    <expected_output>Device.Cellular.Interface.1.X_RDK_Statistics.BytesReceived and Device.Cellular.Interface.1.X_RDK_Statistics.PacketsSent are non-zero values.</expected_output>
    <priority>High</priority>
    <test_stub_interface>CellularManager_DoNothing</test_stub_interface>
    <test_script>TS_CellularManager_GetStatistics_CONNECTED</test_script>
    <skipped>No</skipped>
    <release_version>M128</release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
import time;
from time import sleep;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("tdkbtr181","1");

#IP and Port of box, No need to change,
#This will be replaced with corresponding DUT Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_CellularManager_GetStatistics_CONNECTED');

#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();
print ("[LIB LOAD STATUS]  :  %s" %loadmodulestatus);
#Prmitive test case which associated to this Script

print("Loading TDKB-TR181 module")
if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
    tdkTestObj.addParameter("ParamName","Device.Cellular.X_RDK_Status");
    expectedresult="SUCCESS";
    #Get Device.Cellular.X_RDK_Status
    #Execute testcase in DUT
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    print("TEST STEP 1: Get the Device.Cellular.X_RDK_Status");
    print("EXPECTED RESULT 1: Should get the Device.Cellular.X_RDK_Status as Connected");
    print("ACTUAL RESULT 1: Status is %s" %details);

    if expectedresult in actualresult and details == "CONNECTED":
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");

        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
        tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.X_RDK_Statistics.BytesSent");
        expectedresult="SUCCESS";
        #Execute testcase in DUT
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
        print("TEST STEP 2: Get the value Device.Cellular.Interface.1.X_RDK_Statistics.BytesSent");
        print("EXPECTED RESULT 2: Bytes sent should be non-zero value");
        print("ACTUAL RESULT 2: Bytes sent is %s" %details);

        if expectedresult in actualresult and details != 0 :
            tdkTestObj.setResultStatus("SUCCESS");
            print("[TEST EXECUTION RESULT] : SUCCESS");
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print("[TEST EXECUTION RESULT] : FAILURE");

        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
        tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.X_RDK_Statistics.BytesReceived");
        expectedresult="SUCCESS";
        #Execute testcase in DUT
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
        print("TEST STEP 2: Get the value Device.Cellular.Interface.1.X_RDK_Statistics.BytesReceived");
        print("EXPECTED RESULT 2: Bytes Received should be non-zero value");
        print("ACTUAL RESULT 2: Bytes Received is %s" %details);

        if expectedresult in actualresult and details != 0 :
            tdkTestObj.setResultStatus("SUCCESS");
            print("[TEST EXECUTION RESULT] : SUCCESS");
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print("[TEST EXECUTION RESULT] : FAILURE");

    else:
        tdkTestObj.setResultStatus("FAILURE");
        print("[TEST EXECUTION RESULT] : FAILURE");

    obj.unloadModule("tdkbtr181");
else:
    print("Failed to load module");
    obj.setLoadModuleStatus("FAILURE");
