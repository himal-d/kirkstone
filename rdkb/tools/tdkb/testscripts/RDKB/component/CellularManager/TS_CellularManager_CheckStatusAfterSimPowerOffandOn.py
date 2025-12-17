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
  <version>13</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_CellularManager_CheckStatusAfterSimPowerOffandOn</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>CellularManager_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check whether the status of cellular manager is DEREGISTERED on sim power off and REGISTERED when sim is powered on</synopsis>
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
    <test_objective>Check whether the status of cellular manager is DEREGISTERED on sim power off and REGISTERED when sim is powered on</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1. TDK agent should be running in the DUT and DUT should be online in TDK test manager.
2. Cellular Manager should be up and running.
</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Param Name: Device.Cellular.X_RDK_Status
Value: DEREGISTERED/REGISTERED
Type:String
</input_parameters>
    <automation_approch>1. Load the sysutil and tdkbtr181 module.
2.Power off the sim using qmicli command
3.Get the Device.Cellular.X_RDK_Status
4.Power on the sim using qmicli command
5.Get the Device.Cellular.X_RDK_Status
6. Unload the cellular manager and tdkbtr181 module.</automation_approch>
    <expected_output>The status of cellular manager should be DEREGISTERED on sim power off and REGISTERED when sim is powered on</expected_output>
    <priority>High</priority>
    <test_stub_interface>CellularManager_DoNothing</test_stub_interface>
    <test_script>TS_CellularManager_CheckStatusAfterSimPowerOffandOn</test_script>
    <skipped>No</skipped>
    <release_version>M128</release_version>
    <remarks>None</remarks>
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
sysobj = tdklib.TDKScriptingLibrary("sysutil","1");

#IP and Port of box, No need to change,
#This will be replaced with corresponding DUT Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_CellularManager_CheckStatusAfterSimPowerOffandOn');
sysobj.configureTestCase(ip,port,'TS_CellularManager_CheckStatusAfterSimPowerOffandOn');

#load cellular manager,sysutil and tdkb-tr181 modules
loadmodulestatus_sys =sysobj.getLoadModuleResult();
loadmodulestatus =obj.getLoadModuleResult();
print ("[LIB LOAD STATUS]  :  %s" %loadmodulestatus_sys);
print ("[LIB LOAD STATUS]  :  %s" %loadmodulestatus);
#Prmitive test case which associated to this Script
#tdkTestObj = obj.createTestStep('CellularManager_DoNothing');


print("Loading sysutil and tdkb-tr181 modules");
if "SUCCESS" in loadmodulestatus.upper() and loadmodulestatus_sys.upper():
    obj.setLoadModuleStatus("SUCCESS");
    sysobj.setLoadModuleStatus("SUCCESS");

    #SIM Power off using qmicli command
    step = 1;
    tdkTestObj = sysobj.createTestStep('ExecuteCmd');
    tdkTestObj.addParameter("command", "qmicli -p -d /dev/cdc-wdm0 --uim-sim-power-off=1");
    expectedresult="SUCCESS";
    #Execute the test case in STB
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    print("TEST STEP %d: Power off the sim using qmicli command" %step);
    print("EXPECTED RESULT %d: Should successfully perform SIM power off " %step);
    print("ACTUAL RESULT %d: %s" %(step,details));

    if expectedresult in actualresult and details != "":
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");

    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");

    step = step + 1;
    sleep(5);
    # Get Device.Cellular.X_RDK_Status
    tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
    tdkTestObj.addParameter("ParamName","Device.Cellular.X_RDK_Status");
    expectedresult="SUCCESS";

    #Execute testcase in DUT
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();

    print("TEST STEP %d: Get the Device.Cellular.X_RDK_Status" %step);
    print("EXPECTED RESULT %d: Should get the Device.Cellular.X_RDK_Status as DEREGISTERED" %step);
    print("ACTUAL RESULT %d: Interface status is %s" %(step,details));
    #Check whether Device.Cellular.X_RDK_Status is DEREGISTERED
    if expectedresult in actualresult and details == "DEREGISTERED":
        tdkTestObj.setResultStatus("SUCCESS");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");

    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");

    step = step + 1;


    tdkTestObj = sysobj.createTestStep('ExecuteCmd');
    tdkTestObj.addParameter("command", "qmicli -p -d /dev/cdc-wdm0 --uim-sim-power-on=1");
    expectedresult="SUCCESS";
    #Execute the test case in STB
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    print("TEST STEP %d: Power on the sim using qmicli command" %step);
    print("EXPECTED RESULT %d: Should successfully perform SIM power on " %step);
    print("ACTUAL RESULT %d: %s" %(step,details));

    if expectedresult in actualresult and details != "":
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");

    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");

    sleep(20);
    step = step + 1;

    # Get Device.Cellular.X_RDK_Status
    tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
    tdkTestObj.addParameter("ParamName","Device.Cellular.X_RDK_Status");
    expectedresult="SUCCESS";

    #Execute testcase in DUT
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();

    print("TEST STEP %d: Get the Device.Cellular.X_RDK_Status" %step);
    print("EXPECTED RESULT %d: Should get the Device.Cellular.X_RDK_Status as REGISTERED" %step);
    print("ACTUAL RESULT %d: Interface status is %s" %(step,details));
    #Check whether Device.Cellular.X_RDK_Status is DEREGISTERED
    if expectedresult in actualresult and details == "REGISTERED":
        tdkTestObj.setResultStatus("SUCCESS");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");

    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");


    obj.unloadModule("tdkbtr181");
    sysobj.unloadModule("sysutil");
else:
    print("Failed to load module");
    obj.setLoadModuleStatus("FAILURE");
    sysobj.setLoadModuleStatus("FAILURE");

