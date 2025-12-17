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
  <version>6</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_CellularManager_CheckInterfaceParamsWithinRange</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>CellularManager_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>When Device.Cellular.X_RDK_Status == CONNECTED, the range of the following parameters are:
"Device.Cellular.Interface.{i}.RSSI" :  -117 dBm to -25 dBm
"Device.Cellular.Interface.{i}.X_RDK_SNR" : 0 dB to 20 dB
"Device.Cellular.Interface.{i}.RSRP" : -155 dBm to -44 dBm
"Device.Cellular.Interface.{i}.RSRQ" : -43 dB to 20 dB</synopsis>
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
    <test_case_id>TC_CellularManager_2</test_case_id>
    <test_objective>When Device.Cellular.X_RDK_Status == CONNECTED, the range of the following parameters are:
"Device.Cellular.Interface.{i}.RSSI" :  -117 dBm to -25 dBm
"Device.Cellular.Interface.{i}.X_RDK_SNR" : 0 dB to 20 dB 
"Device.Cellular.Interface.{i}.RSRP" : -155 dBm to -44 dBm
"Device.Cellular.Interface.{i}.RSRQ" : -43 dB to 20 dB			</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>TDK agent should be running in the DUT and DUT should be online in TDK test manager.
Cellular Manager setup should be up and running.</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Param Name: Device.Cellular.X_RDK_Status
Value: CONNECTED
Type: string
Param name: Device.Cellular.Interface.1.RSSI
Type:int
value: -117 dBm to -25 dBm
Param name: Device.Cellular.Interface.1.X_RDK_SNR
Type:int
value: 0 dB to 20 dB
Param name: Device.Cellular.Interface.1.RSRP
Type:int
value: -155 dBm to -44 dBm
Param name: Device.Cellular.Interface.1.RSRQ
Type:int
value:-43 dB to 20 dB
</input_parameters>
    <automation_approch>1.Load tdkbtr181 module.
2. Get the Device.Cellular.X_RDK_Status. It should be in the CONNECTED state to proceed.
3. Get each of the DMS mentioned below and check if they are returning the correspoding walues with the ranges given:
"Device.Cellular.Interface.{i}.RSSI" :  -117 dBm to -25 dBm
"Device.Cellular.Interface.{i}.X_RDK_SNR" : 0 dB to 20 dB
"Device.Cellular.Interface.{i}.RSRP" : -155 dBm to -44 dBm
"Device.Cellular.Interface.{i}.RSRQ" : -43 dB to 20 dB
4.Unload the tdkbtr181 module.</automation_approch>
    <expected_output>All the values returned are within expected range.</expected_output>
    <priority>High</priority>
    <test_stub_interface>CellularManager_DoNothing</test_stub_interface>
    <test_script>TS_CellularManager_CheckInterfaceParamsWithinRange</test_script>
    <skipped>No</skipped>
    <release_version>M128</release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;

#Test component to be tested

obj = tdklib.TDKScriptingLibrary("tdkbtr181","1");

#IP and Port of box, No need to change,
#This will be replaced with corresponding DUT Ip and port while executing script
ip = <ipaddress>
port = <port>

obj.configureTestCase(ip,port,'TS_CellularManager_CheckInterfaceParamsWithinRange');
#load cellular manager and tdkbtr181 modules
loadmodulestatus =obj.getLoadModuleResult();
print ("[LIB LOAD STATUS]  :  %s" %loadmodulestatus);
#Prmitive test case which associated to this Script
#tdkTestObj = obj.createTestStep('CellularManager_DoNothing');

print("Loading TDKB-TR181 module")
if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    #Get Device.Cellular.X_RDK_Status
    tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
    tdkTestObj.addParameter("ParamName","Device.Cellular.X_RDK_Status");
    expectedresult="SUCCESS";

    #Execute testcase in DUT
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    print("TEST STEP 1: Get the Device.Cellular.X_RDK_Status");
    print("EXPECTED RESULT 1: Should get the Device.Cellular.X_RDK_Status as Connected");
    print("ACTUAL RESULT 1: Status is %s" %details);
    #Check whether Device.Cellular.X_RDK_Status is CONNECTED
    if expectedresult in actualresult and details == "CONNECTED":
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");

        #Get Device.Cellular.Interface.1.RSSI
        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
        tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.RSSI");
        expectedresult="SUCCESS";

        #Execute testcase in DUT
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        rssi_value= tdkTestObj.getResultDetails();

        print("TEST STEP 2: Get the value of Device.Cellular.Interface.1.RSSI");
        print("EXPECTED RESULT 2: Value should be within range of -117 dBm to -25 dBm");
        print("ACTUAL RESULT 2: Value is %s" %rssi_value);
        #Check if Device.Cellular.Interface.1.RSSI is within the valid value range
        if expectedresult in actualresult and (-117 < int(rssi_value) < -25):
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");

        #Get Device.Cellular.Interface.1.X_RDK_SNR
        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
        tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.X_RDK_SNR");
        expectedresult="SUCCESS";

        #Execute testcase in DUT
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        snr_value= tdkTestObj.getResultDetails();

        print("TEST STEP 3: Get the value of Device.Cellular.Interface.1.X_RDK_SNR");
        print("EXPECTED RESULT 3: Value should be within range of 0 dB to 20 dB");
        print("ACTUAL RESULT 3: Value is %s" %snr_value);
        # Check whether Device.Cellular.Interface.1.X_RDK_SNR is in valid value range
        if expectedresult in actualresult and (0 < int(snr_value) < 20):
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");

        #Get Device.Cellular.Interface.1.RSRP
        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
        tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.RSRP");
        expectedresult="SUCCESS";

        #Execute testcase in DUT
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        rsrp_value= tdkTestObj.getResultDetails();

        print("TEST STEP 4: Get the value of Device.Cellular.Interface.1.RSRP");
        print("EXPECTED RESULT 4: Value should be within range of -155 dBm to -44 dBm");
        print("ACTUAL RESULT 4: Value is %s" %rsrp_value);
        #Check whether Device.Cellular.Interface.1.RSRP is within valid value range
        if expectedresult in actualresult and (-155 < int(rsrp_value) < -44):
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");

        #Get Device.Cellular.Interface.1.RSRQ
        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
        tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.RSRQ");
        expectedresult="SUCCESS";

        #Execute testcase in DUT
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        rsrq_value= tdkTestObj.getResultDetails();

        print("TEST STEP 4: Get the value of Device.Cellular.Interface.1.RSRQ");
        print("EXPECTED RESULT 4: Value should be within range of -43 dB to 20 dB");
        print("ACTUAL RESULT 4: Value is %s" %rsrq_value);
        #Check Device.Cellular.Interface.1.RSRQ is within valid value range
        if expectedresult in actualresult and (-43 < int(rsrq_value) < 20):
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");

    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");
    #Unload tdkbtr181 and cellular manager modules
    obj.unloadModule("tdkbtr181");
else:
    print("Failed to load module");
    obj.setLoadModuleStatus("FAILURE");
