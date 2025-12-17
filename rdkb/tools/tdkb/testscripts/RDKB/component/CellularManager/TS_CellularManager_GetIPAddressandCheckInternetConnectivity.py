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
  <version>23</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_CellularManager_GetIPAddressandCheckInternetConnectivity</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>CellularManager_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Verify the wwan0 interface state changes and internet connectivity based on the value of Device.Cellular.Interface.1.Enable.</synopsis>
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
    <test_case_id>TC_CellularManager_10</test_case_id>
    <test_objective>Verify the wwan0 interface state changes and internet connectivity based on the value of Device.Cellular.Interface.1.Enable.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1. TDK agent should be running in the DUT and DUT should be online in TDK test manager.
2. Cellular Manager setup should be up and running.</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Param Name: Device.Cellular.Interface.1.Enable
Value: false,true
Type: bool
Param Name: Device.Cellular.X_RDK_Status
Value: DEREGISTERED,CONNECTED
Type: string</input_parameters>
    <automation_approch>1. Load the sysutil and tdkbtr181 module
2. Check Device.Cellular.Interface.1.Enable and ensure it as false. If it is true, set the value to false.
3. Check if Device.Cellular.X_RDK_Status returns value as DEREGISTERED.
4. Check internet connectivity. It will not work
5. Toggle Device.Cellular.Interface.1.Enable to true
6.Check if Device.Cellular.X_RDK_Status returns value as CONNECTED.
7. Once again, check for internet connectivity and wwan0 IP. Both should work.
8. Revert enable value to initial one.
9. Unload the sysutil and tdkbtr181 module.</automation_approch>
    <expected_output>Ping attempts succeed only after the interface is enabled, registered, and connected.
</expected_output>
    <priority>High</priority>
    <test_stub_interface>CellularManager_DoNothing</test_stub_interface>
    <test_script>TS_CellularManager_GetIPAddressandCheckInternetConnectivity</test_script>
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
sysobj = tdklib.TDKScriptingLibrary("sysutil","1");
obj = tdklib.TDKScriptingLibrary("tdkbtr181","1");

#IP and Port of box, No need to change,
#This will be replaced with corresponding DUT Ip and port while executing script
ip = <ipaddress>
port = <port>
sysobj.configureTestCase(ip,port,'TS_CellularManager_GetIPAddressandCheckInternetConnectivity');
obj.configureTestCase(ip,port,'TS_CellularManager_GetIPAddressandCheckInternetConnectivity');

#Get the result of connection with test component and DUT
#Load cellular manager, tdkbtr181 and sysutil modules
loadmodulestatus2 =sysobj.getLoadModuleResult();
loadmodulestatus =obj.getLoadModuleResult();
print ("[LIB LOAD STATUS]  :  %s" %loadmodulestatus2);
print ("[LIB LOAD STATUS]  :  %s" %loadmodulestatus);

#Prmitive test case which associated to this Script
#tdkTestObj = obj.createTestStep('CellularManager_DoNothing');


print("Loading sysutil and TDKB-TR181 module")
if "SUCCESS" in loadmodulestatus2.upper() and loadmodulestatus.upper():
    sysobj.setLoadModuleStatus("SUCCESS");
    obj.setLoadModuleStatus("SUCCESS");

    #Get Device.Cellular.Interface.1.Enable
    tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
    tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.Enable");
    expectedresult="SUCCESS";

    #Execute testcase in DUT
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    flag=0;
    #Ensure Device.Cellular.Interface.1.Enable is false
    if details == "true":
        flag = 1;
        setVal = "false";
        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Set');
        tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.Enable");
        tdkTestObj.addParameter("ParamValue",setVal);
        tdkTestObj.addParameter("Type","bool");

        #Execute testcase in DUT
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details=tdkTestObj.getResultDetails();

    print("TEST STEP 1: Set the Device.Cellular.Interface.1.Enable as false");
    print("EXPECTED RESULT 1: Should set the Device.Cellular.Interface.1.Enable as false");
    print("ACTUAL RESULT 1: Details : %s" %details);

    if expectedresult in actualresult and details != "":
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");

        # Get Device.Cellular.X_RDK_Status
        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
        tdkTestObj.addParameter("ParamName","Device.Cellular.X_RDK_Status");
        expectedresult="SUCCESS";

        #Execute testcase in DUT
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();

        print("TEST STEP 2: Get the Device.Cellular.X_RDK_Status");
        print("EXPECTED RESULT 2: Should get the Device.Cellular.X_RDK_Status as DEREGISTERED");
        print("ACTUAL RESULT 2: Interface status is %s" %details);
        #Check whether Device.Cellular.X_RDK_Status is DEREGISTERED
        if expectedresult in actualresult and details == "DEREGISTERED":
            tdkTestObj.setResultStatus("SUCCESS");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");

            tdkTestObj = sysobj.createTestStep('ExecuteCmd');
            #Check if there is internet connectivity by pinging google.com
            query ="ping -c 2 google.com |  grep -i \"0% packet loss\"";
            print("query:%s" %query);
            tdkTestObj.addParameter("command",query);
            expectedresult="SUCCESS";
            #Execute the test case in DUT
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails().strip();

            print("TEST STEP 3: Do a ping operation and check for internet connectivity");
            print("EXPECTED RESULT 3: Ping operation should not work and result in 100% packet loss");

            if expectedresult in actualresult and details == "":
                print("ACTUAL RESULT 3: Ping operation failed with no internet connectivity");
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : SUCCESS");
            else:
                print("ACTUAL RESULT 3: Ping operation is success with active internet connectivity");
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");
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

    #Set the Device.Cellular.Interface.1.Enable as true
    setVal = "true";
    tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Set');
    tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.Enable");
    tdkTestObj.addParameter("ParamValue",setVal);
    tdkTestObj.addParameter("Type","bool");

    #Execute testcase in DUT
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details=tdkTestObj.getResultDetails();

    print("TEST STEP 4: Set the Device.Cellular.Interface.1.Enable as true");
    print("EXPECTED RESULT 4: Should set the Device.Cellular.Interface.1.Enable as true");
    print("ACTUAL RESULT 4: Details : %s" %details);

    if expectedresult in actualresult and details != "":
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");
        sleep(10);

        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
        tdkTestObj.addParameter("ParamName","Device.Cellular.X_RDK_Status");
        expectedresult="SUCCESS";

        #Execute testcase in DUT
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
        #Get the Device.Cellular.X_RDK_Status
        print("TEST STEP 5: Get the Device.Cellular.X_RDK_Status");
        print("EXPECTED RESULT 5: Should get the Device.Cellular.X_RDK_Status as CONNECTED");
        print("ACTUAL RESULT 5: Interface status is %s" %details);

        #Check if Device.Cellular.X_RDK_Status is CONNECTED
        if expectedresult in actualresult and details == "CONNECTED":
            tdkTestObj.setResultStatus("SUCCESS");
            #Get the result of execution
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
            details = tdkTestObj.getResultDetails().strip();

            print("TEST STEP 6: Do a ping operation and check for internet connectivity");
            print("EXPECTED RESULT 6: Ping operation should be success with 0% packet loss");
            print("ACTUAL RESULT 6: Ping operation is success with active internet connectivity");

            if expectedresult in actualresult and details != "":
                print("ACTUAL RESULT 6: Ping operation is success with active internet connectivity");
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : SUCCESS");

            else:
                print("ACTUAL RESULT 6: Ping operation failed with no internet connectivity");
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");

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
    #Get wwan0 IP Address
    tdkTestObj = sysobj.createTestStep('ExecuteCmd');
    tdkTestObj.addParameter("command", "ifconfig wwan0 | grep 'inet addr' | cut -d ':' -f 2 | cut -d ' ' -f 1");
    expectedresult="SUCCESS";
    #Execute the test case in STB
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    ip_wwan0 = tdkTestObj.getResultDetails();

    print("TEST STEP 7: Get the wwan0 IP address");
    print("EXPECTED RESULT 7: Should get the wwan0 IP address");

    if expectedresult in actualresult and ip_wwan0 != "":
        ip_wwan0 = ip_wwan0[0:-2];
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");
        print(" wwan0 IP: %s" %ip_wwan0);
    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");
        print("Error: Failed to obtain wwan0 IP");

    #Revert to original values
    if flag == 1:
        setVal = "false"
        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Set');
        tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.Enable");
        tdkTestObj.addParameter("ParamValue",setVal);
        tdkTestObj.addParameter("Type","bool");

        #Execute testcase in DUT
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details=tdkTestObj.getResultDetails();
        print("Reverted Device.Cellular.Interface.1.Enable to initial value");
    obj.unloadModule("tdkbtr181");
    sysobj.unloadModule("sysutil");
else:
    print("Failed to load module");
    obj.setLoadModuleStatus("FAILURE");
    sysobj.setLoadModuleStatus("FAILURE");
