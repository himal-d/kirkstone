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
  <version>7</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_CellularManager_GetCurrentAccessTechnology</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>CellularManager_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check if current Access Technology Device.Cellular.Interface.1.CurrentAccessTechnology is within supported access Technologies Device.Cellular.Interface.1.SupportedAccessTechnologies.</synopsis>
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
    <test_case_id>TC_CellularManager_17</test_case_id>
    <test_objective>Check if current Access Technology Device.Cellular.Interface.1.CurrentAccessTechnology is within supported access Technologies Device.Cellular.Interface.1.SupportedAccessTechnologies.</test_objective>
    <test_type>Positive</test_type>
    <test_setup> Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state.
2.TDK Agent should be in running state or invoke it through StartTdk.sh script.
3. Cellular manager should be UP and status should be CONNECTED .</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>ParamName : Device.Cellular.Interface.1.SupportedAccessTechnologies
ParamValue : not empty
Type : string
ParamName : Device.Cellular.Interface.1.CurrentAccessTechnology
ParamValue : not empty
Type : string</input_parameters>
    <automation_approch>1. Load the modules.
2. Get the Device.Cellular.Interface.1.SupportedAccessTechnologies.
3.Get the Device.Cellular.Interface.1.CurrentAccessTechnology.
4. Check if current technology is within Supported access technology.
5. Unload the modules.</automation_approch>
    <expected_output>current Access Technology Device.Cellular.Interface.1.CurrentAccessTechnology should be within supported access Technologies Device.Cellular.Interface.1.SupportedAccessTechnologies.</expected_output>
    <priority>High</priority>
    <test_stub_interface>CellularManager_DoNothing</test_stub_interface>
    <test_script>TS_CellularManager_GetCurrentAccessTechnology</test_script>
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
obj = tdklib.TDKScriptingLibrary("tdkbtr181","1");

#IP and Port of box, No need to change,
#This will be replaced with corresponding DUT Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_CellularManager_GetCurrentAccessTechnology');

#Get the result of connection with test component and DUT
result =obj.getLoadModuleResult();
print ("[LIB LOAD STATUS]  :  %s" %result);

if "SUCCESS" in result.upper():
    step = 1;
    obj.setLoadModuleStatus("SUCCESS");
    #Prmitive test case which associated to this Script
    tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
    tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.SupportedAccessTechnologies");
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    print("\nTEST STEP %d : Get the supported Access Technologies using Device.Cellular.Interface.1.SupportedAccessTechnologies" %step);
    print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.SupportedAccessTechnologies" %step);
    if expectedresult in actualresult:
        supported_technologies = details.split(",");
        tdkTestObj.setResultStatus("SUCCESS");
        print("ACTUAL RESULT %d: Get operation success; Details : %s" %(step,supported_technologies));
        print("TEST EXECUTION RESULT :SUCCESS");

        step = step + 1;
        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
        tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.CurrentAccessTechnology");
        expectedresult="SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        accessTechnology = tdkTestObj.getResultDetails();
        print("\nTEST STEP %d : Get the current Access Technology using Device.Cellular.Interface.1.CurrentAccessTechnology" %step);
        print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.CurrentAccessTechnology" %step);
        if expectedresult in actualresult:
            tdkTestObj.setResultStatus("SUCCESS");
            print("ACTUAL RESULT %d: Get operation success; Details : %s" %(step,accessTechnology));
            print("TEST EXECUTION RESULT :SUCCESS");

            step = step + 1;
            print("\nTEST STEP %d : Check if current access Technology is within the supported access technologies" %step);
            print("EXPECTED RESULT %d : Current access Technology should be within the supported access technologies" %step);
            if accessTechnology in supported_technologies :
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d: Current access Technology is within the supported access technologies" %step);
                print("TEST EXECUTION RESULT :SUCCESS");

            else:
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT %d: Current access Technology is not within the supported access technologies" %step);
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");

        else:
            tdkTestObj.setResultStatus("FAILURE");
            print("ACTUAL RESULT %d: Get operation failed; Details : %s" %(step,accessTechnology));
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print("ACTUAL RESULT %d: Get operation failed; Details : %s" %(step,supported_technologies));
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");

    obj.unloadModule("tdkbtr181");
else:
    print("Failed to load the module");
    obj.setLoadModuleStatus("FAILURE");
