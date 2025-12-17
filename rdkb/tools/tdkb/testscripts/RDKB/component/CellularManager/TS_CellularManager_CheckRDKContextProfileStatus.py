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
  <name>TS_CellularManager_CheckRDKContextProfileStatus</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>CellularManager_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check whether RDKContextProfileStatus is active or inactive depending on Device.Cellular.X_RDK_Status</synopsis>
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
    <test_case_id>TC_CellularManager_14</test_case_id>
    <test_objective>Check whether RDKContextProfileStatus is active or inactive depending on Device.Cellular.X_RDK_Status</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1. TDK agent should be running in the DUT and DUT should be online in TDK test manager.
2. Cellular Manager setup should be up and running.</pre_requisite>
    <api_or_interface_used>Nil</api_or_interface_used>
    <input_parameters>Device.Cellular.X_RDK_Status
Device.Cellular.Interface.1.Enable
Device.Cellular.Interface.1.X_RDK_ContextProfile.1.Status
</input_parameters>
    <automation_approch>1. Load tdkb-tr181 module
2.Set the Device.Cellular.Interface.1.Enable as false
3.Get the Device.Cellular.X_RDK_Status
4.Get the Device.Cellular.Interface.1.X_RDK_ContextProfile.1.Status
5.Set the Device.Cellular.Interface.1.Enable as true
6.Get the Device.Cellular.X_RDK_Status
7.Get the Device.Cellular.Interface.1.X_RDK_ContextProfile.1.Status
8.Unload tdkb-tr181 module</automation_approch>
    <expected_output>Device.Cellular.Interface.1.X_RDK_ContextProfile.1.Status is active when the cellular manager status is connected</expected_output>
    <priority>High</priority>
    <test_stub_interface>CellularManager_DoNothing</test_stub_interface>
    <test_script>TS_CellularManager_CheckRDKContextProfileStatus</test_script>
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

#IP and Port of box, No need to change,
#This will be replaced with corresponding DUT Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_CellularManager_CheckRDKContextProfileStatus');

#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();
print ("[LIB LOAD STATUS]  :  %s" %loadmodulestatus);
#Prmitive test case which associated to this Script
#tdkTestObj = obj.createTestStep('CellularManager_DoNothing');

print("Loading TDKB-TR181 module")
if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");
    #Get Device.Cellular.Interface.1.Enable
    tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
    tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.Enable");
    expectedresult="SUCCESS";

    #Execute testcase in DUT
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

        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");


        # Get Device.Cellular.Interface.1.X_RDK_ContextProfile.1.Status
        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
        tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.X_RDK_ContextProfile.1.Status");
        expectedresult="SUCCESS";

        #Execute testcase in DUT
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();

        print("TEST STEP 2: Get the Device.Cellular.Interface.1.X_RDK_ContextProfile.1.Status");
        print("EXPECTED RESULT 2: Should get the Device.Cellular.Interface.1.X_RDK_ContextProfile.1.Status as INACTIVE");
        print("ACTUAL RESULT 2:Status is %s" %details);
        #Check whether Device.Cellular.Interface.1.X_RDK_ContextProfile.1.Status is INACTIVE
        if expectedresult in actualresult and details == "INACTIVE":
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

    print("TEST STEP 3: Set the Device.Cellular.Interface.1.Enable as true");
    print("EXPECTED RESULT 3: Should set the Device.Cellular.Interface.1.Enable as true");
    print("ACTUAL RESULT 3: Details : %s" %details);

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
        print("TEST STEP 4: Get the Device.Cellular.X_RDK_Status");
        print("EXPECTED RESULT 4: Should get the Device.Cellular.X_RDK_Status as CONNECTED");
        print("ACTUAL RESULT 4: Interface status is %s" %details);

        #Check if Device.Cellular.X_RDK_Status is CONNECTED
        if expectedresult in actualresult and details == "CONNECTED":
            tdkTestObj.setResultStatus("SUCCESS");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");

        # Get Device.Cellular.Interface.1.X_RDK_ContextProfile.1.Status
        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
        tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.X_RDK_ContextProfile.1.Status");
        expectedresult="SUCCESS";

        #Execute testcase in DUT
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();

        print("TEST STEP 2: Get the Device.Cellular.Interface.1.X_RDK_ContextProfile.1.Status");
        print("EXPECTED RESULT 2: Should get the Device.Cellular.Interface.1.X_RDK_ContextProfile.1.Status as ACTIVE");
        print("ACTUAL RESULT 2:Status is %s" %details);
        #Check whether Device.Cellular.Interface.1.X_RDK_ContextProfile.1.Status is ACTIVE
        if expectedresult in actualresult and details == "ACTIVE":
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
else:
    print("Failed to load module");
    obj.setLoadModuleStatus("FAILURE");

