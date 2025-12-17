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
  <version>3</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_CellularManager_CheckIPCellularMangerLog</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>CellularManager_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check whether ip listed in cellular manager logs matches wwan0 ip</synopsis>
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
    <test_case_id>TC_CellularManager_15</test_case_id>
    <test_objective>Check whether ip listed in cellular manager logs matches wwan0 ip		</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.TDK Agent should be in running state or invoke it through StartTdk.sh script.
2. Cellular manager should be UP and status should be CONNECTED.</pre_requisite>
    <api_or_interface_used>Nil</api_or_interface_used>
    <input_parameters>Nil</input_parameters>
    <automation_approch>1. Load sysutil and tdkb-tr181 modules
2.Get the Device.Cellular.X_RDK_Status
3.Get the IP address from CellularManagerLog.txt.0 after reboot
4.Get the wwan0 IP address
5. Compare wwan0 IP and CellularManagerLog.txt.0 IP
6.Unload sysutil and tdkb-tr181 modules</automation_approch>
    <expected_output>wwan0 IP and IP obtained from cellular manager logs must be the same</expected_output>
    <priority>High</priority>
    <test_stub_interface>CellularManager_DoNothing</test_stub_interface>
    <test_script>TS_CellularManager_CheckIPCellularMangerLog</test_script>
    <skipped>No</skipped>
    <release_version>M128</release_version>
    <remarks>None</remarks>
  </test_cases>
  <script_tags />
</xml>
'''
 # use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
from time import sleep;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("tdkbtr181","1");
sysobj = tdklib.TDKScriptingLibrary("sysutil","1");

#IP and Port of box, No need to change,
#This will be replaced with corresponding DUT Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_CellularManager_CheckIPCellularMangerLog');
sysobj.configureTestCase(ip,port,'TS_CellularManager_CheckIPCellularMangerLog');

#load cellular manager,sysutil and tdkb-tr181 modules
loadmodulestatus_sys =sysobj.getLoadModuleResult();
loadmodulestatus =obj.getLoadModuleResult();
print ("[LIB LOAD STATUS]  :  %s" %loadmodulestatus_sys);
print ("[LIB LOAD STATUS]  :  %s" %loadmodulestatus);
#Prmitive test case which associated to this Script
#tdkTestObj = obj.createTestStep('CellularManager_DoNothing');


print("Loading module")
if "SUCCESS" in loadmodulestatus.upper() and loadmodulestatus_sys.upper():
    obj.setLoadModuleStatus("SUCCESS");

    #Get the Device.Cellular.X_RDK_Status
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

    #Check whether Device.Cellular.X_RDK_Status is in CONNECTED state
    if expectedresult in actualresult and details == "CONNECTED":
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");

        print("Rebooting the device... \n");
        obj.initiateReboot();
        sleep(120);
        #Fetch IP address from CellularManagerLog.txt.0
        tdkTestObj = sysobj.createTestStep('ExecuteCmd');
        tdkTestObj.addParameter("command", "cat /rdklogs/logs/CellularManagerLog.txt.0 | grep -i \"IPType\[IPv4\] Address\" | awk '{print $12}'");
        expectedresult="SUCCESS";
        #Execute the test case in STB
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
        print("TEST STEP 2: Get the IP address from CellularManagerLog.txt.0");
        print("EXPECTED RESULT 2: Should get the IP address from CellularManagerLog.txt.0");

        if expectedresult in actualresult and details != "":
            ip_cellmanagerlog = details[8:22];
            print("ACTUAL RESULT 2: IP obtained from at /rdklogs/logs/CellularManagerLog.txt.0 : %s" %ip_cellmanagerlog);

            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");

        else:
            print("ACTUAL RESULT 2:Error: Failed to obtain IP from at /rdklogs/logs/CellularManagerLog.txt.0 ")
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");
        #Fetch wwan0 IP address
        tdkTestObj = sysobj.createTestStep('ExecuteCmd');
        tdkTestObj.addParameter("command", "ifconfig wwan0 | grep 'inet addr' | cut -d ':' -f 2 | cut -d ' ' -f 1");
        expectedresult="SUCCESS";
        #Execute the test case in STB
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
        ip_wwan0 = details[:-2];

        print("TEST STEP 3: Get the wwan0 IP address");
        print("EXPECTED RESULT 3: Should get the wwan0 IP address");
        print("ACTUAL RESULT 3:wwan0 IP : %s" %ip_wwan0);

        if expectedresult in actualresult and ip_wwan0 != "":
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");

        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");

        #Compare wwan0 IP and CellularManagerLog.txt.0 IP
        print("TEST STEP 4: Compare wwan0 IP and CellularManagerLog.txt.0 IP");
        print("EXPECTED RESULT 4: Both IPs must be the same");

        if ip_cellmanagerlog == ip_wwan0:
            print("ACTUAL RESULT 4: Both IPs are the same ");
            tdkTestObj.setResultStatus("SUCCESS");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");
        else:
            print("ACTUAL RESULT 4: Both IPs are not same ");
            tdkTestObj.setResultStatus("FAILURE");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");
    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");
    #Unloading sysutil,tdkbtr181 and cellular manager modules
    sysobj.unloadModule("sysutil");
    obj.unloadModule("tdkbtr181");
else:
    print("Failed to load module");
    sysobj.setLoadModuleStatus("FAILURE");
