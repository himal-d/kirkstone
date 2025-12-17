##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2019 RDK Management
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
  <name>TS_WIFIAGENT_Blaster_NumberOfSamples</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>WIFIAgent_Set_Get</primitive_test_name>
  <!--  -->
  <primitive_test_version>3</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To validate set operation of NumberOfSamples parameter by passing valid and invalid values</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>2</execution_time>
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
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_WIFIAGENT_239</test_case_id>
    <test_objective>Number of Samples in a blast should be successfully set to valid values and fail when set invalid values</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters> Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.Enable, Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.NumberOfSamples</input_parameters>
    <automation_approch>1. Load wifiagent module
2. Set the ActiveMeasurements Enable parameter value to true
3. Set valid values ["1", "100", "50"] to NumberOfSamples parameter and verify if set operation is successful
4. Set invalid values ["0", "101"] to NumberOfSamples parameter and verify if set operation fails
5. Unload wifiagent module</automation_approch>
    <expected_output>NumberOfSamples should set valid values and fail setting invalid values</expected_output>
    <priority>High</priority>
    <test_stub_interface>WIFIAGENT</test_stub_interface>
    <test_script>TS_WIFIAGENT_Blaster_NumberOfSamples</test_script>
    <skipped>No</skipped>
    <release_version>M116</release_version>
    <remarks>None</remarks>
  </test_cases>
  <script_tags />
</xml>
'''
import tdklib;
import time;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent","RDKB");
#IP and Port of box, No need to change,
#This will be replaced with corresponding Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIAGENT_Blaster_NumberOfSamples');
#Get the result of connection with test component
loadmodulestatus = obj.getLoadModuleResult();
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus);
if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");
    expectedresult = "SUCCESS";
    tdkTestObj = obj.createTestStep("WIFIAgent_Get");
    tdkTestObj.addParameter("paramName","Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.Enable");
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    initial_enable = tdkTestObj.getResultDetails().strip();
    details = tdkTestObj.getResultDetails();
    step = 1;
    print("\nTEST STEP %d: Get the initial value of Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.Enable" %step);
    print("EXPECTED RESULT %d: Should get the initial Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.Enable value successfuly" %step);
    if expectedresult in actualresult and details!="":
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        initial_enable = initial_enable.split("VALUE:")[1].split(" ")[0].strip();
        print("ACTUAL RESULT %d: GET operation success; ActiveMeasurements Enable is : %s" %(step, initial_enable));
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");
        #Set to false if initially the enable status is not false
        revert_flag = 0;
        if initial_enable == "false":
            step = step + 1;
            setValue = "true";
            #Change the ActiveMeasurements Enable status
            tdkTestObj = obj.createTestStep('WIFIAgent_Set_Get');
            tdkTestObj.addParameter("paramName","Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.Enable");
            tdkTestObj.addParameter("paramValue",setValue);
            tdkTestObj.addParameter("paramType","boolean");
            #Execute the test case in DUT
            print("\nTEST STEP %d: Set ActiveMeasurements Enable to true" %step);
            print("EXPECTED RESULT %d: Should set ActiveMeasurements Enable to true" %step);
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();
            if expectedresult in actualresult:
                revert_flag = 1;
                proceed_flag = 1;
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d: Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.Enable set successfully; Details : %s" %(step, details));
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : SUCCESS");
            else:
                proceed_flag = 0;
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT %d: Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.Enable set failed; Details : %s" %(step, details));
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");
        else :
            #Set the result status of execution
            proceed_flag = 1;
            tdkTestObj.setResultStatus("SUCCESS");
            print("ActiveMeasurements Enable is already true initially");

        if proceed_flag == 1:
            tdkTestObj = obj.createTestStep('WIFIAgent_Get');
            tdkTestObj.addParameter("paramName","Device.WiFi.X_RDKCENTRAL-COM_Report.WifiClient.ActiveMeasurements.NumberOfSamples")
            tdkTestObj.executeTestCase("expectedresult");
            actualresult = tdkTestObj.getResult();
            initial_NumberOfSamples = tdkTestObj.getResultDetails();
            step = step + 1;
            print("TEST STEP %d: Get the current NumberOfSamples value" %step);
            print("EXPECTED RESULT %d: Should get current NumberOfSamples value" %step);
            if expectedresult in actualresult:
                initial_NumberOfSamples = initial_NumberOfSamples.split("VALUE:")[1].split(" ")[0].strip();
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d: current NumberOfSamples value is %s" %(step, initial_NumberOfSamples));
                print("[TEST EXECUTION RESULT] : SUCCESS");
                valid_list = ["1", "100", "50"];
                all_success  = [1, 1, 1]
                set_success = [];
                step = step + 1;
                print("TEST STEP %d: Set the NumberOfSamples to each of the values in the valid list" %step);
                print("EXPECTED RESULT %d: Should Set the NumberOfSamples to each of the values in the valid list" %step);
                for number in valid_list:
                    #### Set and Get Values ####
                    tdkTestObj = obj.createTestStep("WIFIAgent_Set_Get");
                    tdkTestObj.addParameter("paramName","Device.WiFi.X_RDKCENTRAL-COM_Report.WifiClient.ActiveMeasurements.NumberOfSamples");
                    tdkTestObj.addParameter("paramValue",number);
                    tdkTestObj.addParameter("paramType","unsignedint");
                    tdkTestObj.executeTestCase(expectedresult);
                    details = tdkTestObj.getResultDetails();
                    actualresult = tdkTestObj.getResult();
                    if expectedresult in actualresult:
                        set_success.append(1);
                        print("NumberOfSamples successfully set to %s" %number);
                    else:
                        set_success.append(0);
                        print("NumberOfSamples failed to set %s" %number);
                if all_success == set_success:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d: NumberOfSamples successfully set for all the valid values" %step);
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : %s" %actualresult);
                else:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT %d: NumberOfSamples set failed for some of the valid values" %step);
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : %s" %actualresult);
                step = step + 1;
                all_failure = [1,1]
                invalid_list = ["0", "101"]
                set_failure = [];
                print("TEST STEP %d: Set the NumberOfSamples to each of the values in the invalid list" %step);
                print("EXPECTED RESULT %d: Should Fail to set the NumberOfSamples in the invalid list" %step);
                for invalid_number in invalid_list:
                    #### Set and Get Values ####
                    tdkTestObj = obj.createTestStep("WIFIAgent_Set_Get");
                    tdkTestObj.addParameter("paramName","Device.WiFi.X_RDKCENTRAL-COM_Report.WifiClient.ActiveMeasurements.NumberOfSamples");
                    tdkTestObj.addParameter("paramValue", invalid_number);
                    tdkTestObj.addParameter("paramType","unsignedint");
                    expectedresult = "FAILURE";
                    tdkTestObj.executeTestCase(expectedresult);
                    details = tdkTestObj.getResultDetails();
                    actualresult = tdkTestObj.getResult();
                    if expectedresult in actualresult:
                        set_failure.append(1);
                        print("NumberOfSamples failed to set  %s" %invalid_number);
                    else:
                        set_failure.append(0);
                        print("NumberOfSamples successfully set for the value %s" %invalid_number);
                if all_failure == set_failure:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d: NumberOfSamples failed to set all the invalid values" %step);
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : %s" %actualresult);
                else:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT %d: NumberOfSamples set was successful for some of the invalid values" %step);
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : %s" %actualresult);

                if (set_success == all_success) and (set_failure != [0,0]):
                    print("TEST STEP %d: Revert NumberOfSamples value to the initial value" %step);
                    print("EXPECTED RESULT %d: Should revert the NumberOfSamples value to the initial value" %step);
                    tdkTestObj = obj.createTestStep("WIFIAgent_Set_Get");
                    tdkTestObj.addParameter("paramName","Device.WiFi.X_RDKCENTRAL-COM_Report.WifiClient.ActiveMeasurements.NumberOfSamples");
                    tdkTestObj.addParameter("paramValue",str(initial_NumberOfSamples));
                    tdkTestObj.addParameter("paramType","unsignedint");
                    step = step + 1;
                    tdkTestObj.executeTestCase(expectedresult);
                    expectedresult = "SUCCESS";
                    actualresult = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails();
                    if expectedresult in actualresult:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("ACTUAL RESULT %d: %s" %(step,details));
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : %s" %actualresult);
                    else:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print("ACTUAL RESULT %d: %s" %(step,details));
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : %s" %actualresult);
                else:
                    print("Revert operation not required for Device.WiFi.X_RDKCENTRAL-COM_Report.WifiClient.ActiveMeasurements.NumberOfSamples");

                if revert_flag == 1:
                    step = step + 1;
                    #Change the ActiveMeasurements Enable status
                    tdkTestObj = obj.createTestStep('WIFIAgent_Set_Get');
                    tdkTestObj.addParameter("paramName","Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.Enable");
                    tdkTestObj.addParameter("paramValue",initial_enable);
                    tdkTestObj.addParameter("paramType","boolean");
                    #Execute the test case in DUT
                    print("TEST STEP %d: Revert ActiveMeasurements Enable to initial value" %step);
                    print("EXPECTED RESULT %d: Should revert ActiveMeasurements Enable to initial value" %step)
                    tdkTestObj.executeTestCase(expectedresult);
                    expectedresult = "SUCCESS";
                    actualresult = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails();
                    if expectedresult in actualresult:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("ACTUAL RESULT %d: Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.Enable reverted successfully; Details : %s" %(step, details));
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : SUCCESS");
                    else:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print("ACTUAL RESULT %d: Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.Enable revert failed; Details : %s" %(step, details));
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : FAILURE");
                else:
                    print("Revert operation not required for Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.Enable");
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print("Device.Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.Enable could not be enabled");
    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print("ACTUAL RESULT %d: GET operation failed; ActiveMeasurements Enable is : %s" %(step, details));
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");
    obj.unloadModule("wifiagent");
else:
    print("FAILURE to load wifiagent module");
    obj.setLoadModuleStatus("FAILURE");
    print("Module loading FAILURE");
