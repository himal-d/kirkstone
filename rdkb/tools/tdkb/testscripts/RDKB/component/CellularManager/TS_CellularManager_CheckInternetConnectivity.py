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
  <version>5</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_CellularManager_CheckInternetConnectivity</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>CellularManager_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check internet connectivity by doing ping operation</synopsis>
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
    <test_case_id>TC_CellularManager_3</test_case_id>
    <test_objective>Check internet connectivity by doing ping operation</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1. TDK agent should be running in the DUT and DUT should be online in TDK test manager.
2. Cellular Manager setup should be up and running.</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>None</input_parameters>
    <automation_approch>1. Load the sysutil and tdkbtr181 module.
2.Check wwan0 IP
3. Do ping operation to check internet connectivity
4. Unload the sysutil and tdkbtr181 module.</automation_approch>
    <expected_output>Check internet connectivity by doing ping operation</expected_output>
    <priority>High</priority>
    <test_stub_interface>CellularManager_DoNothing</test_stub_interface>
    <test_script>TS_CellularManager_CheckInternetConnectivity</test_script>
    <skipped>No</skipped>
    <release_version>M128</release_version>
    <remarks>None</remarks>
  </test_cases>
  <script_tags />
</xml>
'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
#Test component to be tested
sysobj = tdklib.TDKScriptingLibrary("sysutil","1");
#IP and Port of box, No need to change,
#This will be replaced with corresponding DUT Ip and port while executing script
ip = <ipaddress>
port = <port>
sysobj.configureTestCase(ip,port,'TS_CellularManager_CheckInternetConnectivity');

#load sysutil and tdkb-tr181 modules
loadmodulestatus_sys =sysobj.getLoadModuleResult();
print ("[LIB LOAD STATUS]  :  %s" %loadmodulestatus_sys);
#Prmitive test case which associated to this Script
#tdkTestObj = obj.createTestStep('CellularManager_DoNothing');


print("Loading module");
if "SUCCESS" in  loadmodulestatus_sys.upper():
    sysobj.setLoadModuleStatus("SUCCESS");

    tdkTestObj = sysobj.createTestStep('ExecuteCmd');
    tdkTestObj.addParameter("command", "ifconfig wwan0 | grep 'inet addr' | cut -d ':' -f 2 | cut -d ' ' -f 1");
    expectedresult="SUCCESS";
    #Execute the test case in STB
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    ip_wwan0 = details[:-2];

    print("TEST STEP 1: Get the wwan0 IP address");
    print("EXPECTED RESULT 1: Should obtain the wwan0 IP address");

    if expectedresult in actualresult and ip_wwan0 != "":
        tdkTestObj.setResultStatus("SUCCESS");
        #Get the result of execution
        print("ACTUAL RESULT 1: Successfully obtained wwan0 IP : %s" %ip_wwan0);
        print("[TEST EXECUTION RESULT] : SUCCESS");

        tdkTestObj = sysobj.createTestStep('ExecuteCmd');
        #Check internet connectivity
        query ="ping -c 2 google.com |  grep -i \"0% packet loss\"";
        print("query:%s" %query);
        tdkTestObj.addParameter("command",query);
        expectedresult="SUCCESS";

        #Execute the test case in DUT
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();

        print("TEST STEP 2: Do a ping operation and check for internet connectivity");
        print("EXPECTED RESULT 2: Ping operation should be success with 0% packet loss");
        print("ACTUAL RESULT 2: Ping operation is success with active internet connectivity");

        if expectedresult in actualresult and details != "":
            print("ACTUAL RESULT 2: Ping operation is success with active internet connectivity");
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");
        else:
            print("ACTUAL RESULT 2: Ping operation failed with no internet connectivity");
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");
    else:
        #Set the result status of execution
        print("ACTUAL RESULT 1:Failed to obtain wwan0 ip");
        tdkTestObj.setResultStatus("FAILURE");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");
    sysobj.unloadModule("sysutil");
else:
    print("Failed to load module");
    sysobj.setLoadModuleStatus("FAILURE");
