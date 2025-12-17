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
  <version>12</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_CellularManager_CheckParametersValue_CONNECTED</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>CellularManager_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check if  parameters Device.Cellular.X_RDK_Enable be true, Device.Cellular.Interface.1.Enable be true, Device.Cellular.Interface.1.X_RDK_RadioEnvConditions be FAIR/EXCELLENT/POOR/GOOD , Device.Cellular.Interface.1.X_RDK_Identification.Imei be not empty, Device.Cellular.Interface.1.Status be UP when cellular manager status is CONNECTED.</synopsis>
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
    <test_case_id>TC_CellularManager_6</test_case_id>
    <test_objective>Check if  parameters Device.Cellular.X_RDK_Enable be true, Device.Cellular.Interface.1.Enable be true, Device.Cellular.Interface.1.X_RDK_RadioEnvConditions be FAIR/EXCELLENT/POOR/GOOD , Device.Cellular.Interface.1.X_RDK_Identification.Imei be not empty, Device.Cellular.Interface.1.Status be UP when cellular manager status is CONNECTED.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state.
2.TDK Agent should be in running state or invoke it through StartTdk.sh script.
3. Cellular manager should be UP and status should be CONNECTED.</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>ParamName : Device.Cellular.X_RDK_Status
ParamValue : CONNECTED
Type : string
ParamName : Device.Cellular.X_RDK_Enable
ParamValue : true
Type : bool
ParamName : Device.Cellular.Interface.1.Enable
ParamValue : true
Type : bool
ParamName : Device.Cellular.Interface.1.X_RDK_RadioEnvConditions
ParamValue : FAIR/EXCELLENT/POOR/GOOD
Type : string
ParamName : Device.Cellular.Interface.1.X_RDK_Identification.Imei
ParamValue : not empty
Type : string
ParamName : Device.Cellular.Interface.1.Status
ParamValue : UP
Type : string</input_parameters>
    <automation_approch>1. Load the modules.
2. Check if Device.Cellular.X_RDK_Status be CONNECTED.
3. Check if Device.Cellular.X_RDK_Enable be true.
4. Check if Device.Cellular.Interface.1.Enable be true.
5. Check if Device.Cellular.Interface.1.X_RDK_RadioEnvConditions be FAIR/EXCELLENT/POOR/GOOD.
6. Check if Device.Cellular.Interface.1.X_RDK_Identification.Imei be not empty.
7. Check if Device.Cellular.Interface.1.Status be UP.
8. Unload the modules.
</automation_approch>
    <expected_output>Parameters Device.Cellular.X_RDK_Enable be true, Device.Cellular.Interface.1.Enable be true, Device.Cellular.Interface.1.X_RDK_RadioEnvConditions be FAIR/EXCELLENT/POOR/GOOD , Device.Cellular.Interface.1.X_RDK_Identification.Imei be not empty, Device.Cellular.Interface.1.Status be UP when cellular manager status is CONNECTED.</expected_output>
    <priority>High</priority>
    <test_stub_interface>tdkbtr181</test_stub_interface>
    <test_script>TS_CellularManager_CheckParametersValue_CONNECTED</test_script>
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
obj.configureTestCase(ip,port,'TS_CellularManager_CheckParametersValue_CONNECTED');

#Get the result of connection with test component and DUT
result =obj.getLoadModuleResult();
print ("[LIB LOAD STATUS]  :  %s" %result);

if "SUCCESS" in result.upper():
    step = 1;
    obj.setLoadModuleStatus("SUCCESS");
    #Prmitive test case which associated to this Script
    tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
    tdkTestObj.addParameter("ParamName","Device.Cellular.X_RDK_Status");
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    status = tdkTestObj.getResultDetails();
    print("\nTEST STEP %d : Get the  cellular manager status using Device.Cellular.X_RDK_Status" %step);
    print("EXPECTED RESULT %d : Should successfully get Device.Cellular.X_RDK_Status" %step);
    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS");
        print("ACTUAL RESULT %d: Get operation success; Details : %s" %(step,status));
        print("TEST EXECUTION RESULT :SUCCESS");

        step = step + 1;
        print("\nTEST STEP %d : Check if the cellular manager status as CONNECTED" %step);
        print("EXPECTED RESULT %d : Should get the cellular manager status as CONNECTED  " %step);
        if status == "CONNECTED" :
            tdkTestObj.setResultStatus("SUCCESS");
            print("ACTUAL RESULT %d : %s" %(step,status));
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");

            obj.setLoadModuleStatus("SUCCESS");
            #Prmitive test case which associated to this Script
            tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
            tdkTestObj.addParameter("ParamName","Device.Cellular.X_RDK_Enable");
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            enable = tdkTestObj.getResultDetails();

            step = step + 1;
            print("\nTEST STEP %d : Get Device.Cellular.X_RDK_Enable" %step);
            print("EXPECTED RESULT %d : Should successfully get Device.Cellular.X_RDK_Enable " %step);
            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d: Get operation success; Details : %s" %(step,enable));
                print("TEST EXECUTION RESULT :SUCCESS");

                step = step + 1;
                print("\nTEST STEP %d : Check if Device.Cellular.X_RDK_Enable is true" %step);
                print("EXPECTED RESULT %d : Should successfully get Device.Cellular.X_RDK_Enable be true " %step);
                if enable == 'true':
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d: The value of Device.Cellular.X_RDK_Enable is %s" %(step,enable));
                    print("TEST EXECUTION RESULT :SUCCESS");
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT %d: The value of Device.Cellular.X_RDK_Enable is %s" %(step,enable));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT %d: Get operation failed; Details : %s" %(step,enable));
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");

            obj.setLoadModuleStatus("SUCCESS");
            #Prmitive test case which associated to this Script
            tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
            tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.Enable");
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            interfaceEnable = tdkTestObj.getResultDetails();

            step = step + 1;
            print("\nTEST STEP %d : Get Device.Cellular.Interface.1.Enable" %step);
            print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.Enable" %step);
            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d: Get operation success; Details : %s" %(step,interfaceEnable));
                print("TEST EXECUTION RESULT :SUCCESS");

                step = step + 1;
                print("\nTEST STEP %d : Check if Device.Cellular.Interface.1.Enable is true" %step);
                print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.Enable be true " %step);
                if interfaceEnable == 'true':
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d: The value of Device.Cellular.Interface.1.Enable  is %s" %(step,interfaceEnable));
                    print("TEST EXECUTION RESULT :SUCCESS");
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT %d: The value of Device.Cellular.Interface.1.Enable is %s" %(step,interfaceEnable));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT %d: Get operation failed; Details : %s" %(step,interfaceEnable));
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");

            obj.setLoadModuleStatus("SUCCESS");
            valid_conditions = {'EXCELLENT', 'GOOD', 'FAIR', 'POOR'};
            #Prmitive test case which associated to this Script
            tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
            tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.X_RDK_RadioEnvConditions");
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            RadioEnvCondition = tdkTestObj.getResultDetails();

            step = step + 1;
            print("\nTEST STEP %d : Get Device.Cellular.Interface.1.X_RDK_RadioEnvConditions" %step);
            print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.X_RDK_RadioEnvConditions" %step);
            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d: Get operation success; Details : %s" %(step,RadioEnvCondition));
                print("TEST EXECUTION RESULT :SUCCESS");

                step = step + 1;
                print("\nTEST STEP %d : Check if Device.Cellular.Interface.1.X_RDK_RadioEnvConditions is FAIR/EXCELLENT/POOR/GOOD" %step);
                print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.X_RDK_RadioEnvConditions be FAIR/EXCELLENT/POOR/GOOD " %step);
                if RadioEnvCondition in valid_conditions:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d: The value of Device.Cellular.Interface.1.X_RDK_RadioEnvConditions  is %s" %(step,RadioEnvCondition));
                    print("TEST EXECUTION RESULT :SUCCESS");
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT %d: The value of Device.Cellular.Interface.1.X_RDK_RadioEnvConditions is %s" %(step,RadioEnvCondition));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT %d: Get operation failed; Details : %s" %(step,RadioEnvCondition));
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");

            obj.setLoadModuleStatus("SUCCESS");
            #Prmitive test case which associated to this Script
            tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
            tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.X_RDK_Identification.Imei");
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            Imei = tdkTestObj.getResultDetails();

            step = step + 1;
            print("\nTEST STEP %d : Get Device.Cellular.Interface.1.X_RDK_Identification.Imei" %step);
            print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.X_RDK_Identification.Imei" %step);
            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d: Get operation success; Details : %s" %(step,Imei));
                print("TEST EXECUTION RESULT :SUCCESS");

                step = step + 1;
                print("\nTEST STEP %d : Check if Device.Cellular.Interface.1.X_RDK_Identification.Imei should be non-empty" %step);
                print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.Enable be non-empty" %step);
                if Imei:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d: The value of Device.Cellular.Interface.1.X_RDK_Identification.Imei  is %s" %(step,Imei));
                    print("TEST EXECUTION RESULT :SUCCESS");
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT %d: The value of Device.Cellular.Interface.1.X_RDK_Identification.Imei is %s" %(step,Imei));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT %d: Get operation failed; Details : %s" %(step,Imei));
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");

            obj.setLoadModuleStatus("SUCCESS");
            #Prmitive test case which associated to this Script
            tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
            tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.Status");
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            interfaceStatus = tdkTestObj.getResultDetails();

            step = step + 1;
            print("\nTEST STEP %d : Get Device.Cellular.Interface.1.Status" %step);
            print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.Status" %step);
            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d: Get operation success; Details : %s" %(step,interfaceStatus));
                print("TEST EXECUTION RESULT :SUCCESS");

                step = step + 1;
                print("\nTEST STEP %d : Check if Device.Cellular.Interface.1.Status" %step);
                print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.Status be UP " %step);
                if interfaceStatus == 'Up':
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d: The value of Device.Cellular.Interface.1.Status  is %s" %(step,interfaceStatus));
                    print("TEST EXECUTION RESULT :SUCCESS");
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT %d: The value of Device.Cellular.Interface.1.Status is %s" %(step,interfaceStatus));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print("ACTUAL RESULT %d : %s" %(step,status));
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print("ACTUAL RESULT %d: Get operation failed; Details : %s" %(step,status));
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");
    obj.unloadModule("tdkbtr181");
else:
    print("Failed to load the module");
    obj.setLoadModuleStatus("FAILURE");
