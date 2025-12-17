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
  <version>9</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_CellularManager_CheckRadioEnvConditions_DEREGISTERED</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>CellularManager_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To check whether Device.Cellular.Interface.1.X_RDK_RadioEnvConditions is UNAVAILABLE when Device.Cellular.X_RDK_Status is DEREGISTERED.</synopsis>
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
    <test_case_id>TC_CellularManager_8</test_case_id>
    <test_objective>To check whether Device.Cellular.Interface.1.X_RDK_RadioEnvConditions is UNAVAILABLE when Device.Cellular.X_RDK_Status is DEREGISTERED.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1. TDK agent should be running in the DUT and DUT should be online in TDK test manager.
2. Cellular Manager setup should be up and running.</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Param Name: Device.Cellular.Interface.1.Enable
Value: false
Type: bool
Param Name: Device.Cellular.X_RDK_Status
Value: DEREGISTERED
Type: string
Param Name: Device.Cellular.Interface.1.X_RDK_RadioEnvConditions
Value: UNAVAILABLE
Type: string</input_parameters>
    <automation_approch>1. Load the tdkbtr181 module
2. Check Device.Cellular.Interface.1.Enable and ensure it as false. If it is true, set the value to false.
3. Check if Device.Cellular.X_RDK_Status returns value as DEREGISTERED.
4. Check if Device.Cellular.Interface.1.X_RDK_RadioEnvConditions returns expected the value UNAVAILABLE.
5. Unload the tdkbtr181 module.</automation_approch>
    <expected_output>Device.Cellular.Interface.1.X_RDK_RadioEnvConditions must return the value UNAVAILABLE.</expected_output>
    <priority>High</priority>
    <test_stub_interface>CellularManager_DoNothing</test_stub_interface>
    <test_script>TS_CellularManager_CheckRadioEnvConditions_DEREGISTERED</test_script>
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
obj.configureTestCase(ip,port,'TS_CellularManager_CheckRadioEnvConditions_DEREGISTERED');
#Get the result of connection with test component and DUT
#Loading cellular manager and tdkb tr181 modules
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
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    #Ensure Device.Cellular.Interface.1.Enable is false
    if details == "true":
            flag = 1
            setVal = "false"
            tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Set');
            tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.Enable");
            tdkTestObj.addParameter("ParamValue",setVal);
            tdkTestObj.addParameter("Type","bool");

            #Execute testcase in DUT
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details=tdkTestObj.getResultDetails();

    print("TEST STEP 1: Get the Device.Cellular.Interface.1.Enable");
    print("EXPECTED RESULT 1: Should get the Device.Cellular.Interface.1.Enable as false");
    print("ACTUAL RESULT 1: Interface status is %s" %details);

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
        # Check if Device.Cellular.X_RDK_Status returns DEREGISTERED
        if expectedresult in actualresult and details == "DEREGISTERED":
            tdkTestObj.setResultStatus("SUCCESS");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");
            #Get Device.Cellular.Interface.1.X_RDK_RadioEnvConditions
            tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
            tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.X_RDK_RadioEnvConditions");
            expectedresult="SUCCESS";

            #Execute testcase in DUT
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();

            print("TEST STEP 3: Get the Device.Cellular.Interface.1.X_RDK_RadioEnvConditions");
            print("EXPECTED RESULT 3: Should get the Device.Cellular.Interface.1.X_RDK_RadioEnvConditions as UNAVAILABLE");
            print("ACTUAL RESULT 3: Interface status is %s" %details);
            #Check whether Device.Cellular.Interface.1.X_RDK_RadioEnvConditions returns UNAVAILABLE
            if expectedresult in actualresult and details == "UNAVAILABLE":
                tdkTestObj.setResultStatus("SUCCESS");
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : SUCCESS");
            else:
                tdkTestObj.setResultStatus("FALSE");
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FALSE");
        else:
            tdkTestObj.setResultStatus("FALSE");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FALSE");
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
    #Unload tdkbtr181 and cellular manager modules
    obj.unloadModule("tdkbtr181");
else:
    print("Failed to load module");
    obj.setLoadModuleStatus("FAILURE");
