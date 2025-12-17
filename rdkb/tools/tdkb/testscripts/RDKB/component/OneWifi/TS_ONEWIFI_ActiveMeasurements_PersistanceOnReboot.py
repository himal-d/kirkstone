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
  <version>2</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_ONEWIFI_ActiveMeasurements_PersistanceOnReboot</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>onewifi_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>3</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To check Blaster ActiveMeasurement parameters persistence after reboot</synopsis>
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
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_ONEWIFI_242</test_case_id>
    <test_objective>To set Blaster ActiveMeasurements values and check persistence after reboot</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.Enable ,Device.WiFi.X_RDKCENTRAL-COM_Report.WifiClient.ActiveMeasurements.PacketSize, Device.WiFi.X_RDKCENTRAL-COM_Report.WifiClient.ActiveMeasurements.NumberOfSamples, Device.WiFi.X_RDKCENTRAL-COM_Report.WifiClient.ActiveMeasurements.SampleDuration</input_parameters>
    <automation_approch>1. Load wifiagent and tad modules
2.Get the current ActiveMeasurements values
3.Set the ActiveMeasurements values
4.Get the ActiveMeasurements values after set
5.Validate the set and get values
6.Initiate reboot
7.Check if ActiveMeasurements value persists on reboot
8.Revert the  ActiveMeasurements values
9. Unload wifiagent and tad modules</automation_approch>
    <expected_output>Set and get values of ActiveMeasurements should be the same before and after reboot</expected_output>
    <priority>High</priority>
    <test_stub_interface>ONEWIFI</test_stub_interface>
    <test_script>TS_ONEWIFI_CheckActiveMeasurement_PersistenceOnReboot</test_script>
    <skipped>No</skipped>
    <release_version>M70</release_version>
    <remarks>None</remarks>
  </test_cases>
  <script_tags />
</xml>
'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
from time import sleep;
import tdkutility
from tdkutility import *
#Test component to be tested
obj = tdklib.TDKScriptingLibrary("tad","1");
obj1 = tdklib.TDKScriptingLibrary("wifiagent","1");
#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_ONEWIFI_CheckActiveMeasurement_PersistenceOnReboot');
obj1.configureTestCase(ip,port,'TS_ONEWIFI_CheckActiveMeasurement_PersistenceOnReboot');
set_ActiveMeasurementValues = ["true", "64", "50", "2000"]
flag = 0
#Get the result of connection with test component and DUT
loadmodulestatus1=obj.getLoadModuleResult();
loadmodulestatus2=obj1.getLoadModuleResult();
if "SUCCESS" in loadmodulestatus1.upper() and loadmodulestatus2.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS")
    expectedresult="SUCCESS";
    tdkTestObj = obj.createTestStep('TADstub_Get');
    paramList=["Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.Enable" ,"Device.WiFi.X_RDKCENTRAL-COM_Report.WifiClient.ActiveMeasurements.PacketSize", "Device.WiFi.X_RDKCENTRAL-COM_Report.WifiClient.ActiveMeasurements.NumberOfSamples", "Device.WiFi.X_RDKCENTRAL-COM_Report.WifiClient.ActiveMeasurements.SampleDuration"]
    print("TEST STEP 1: Should get the ActiveMeasurements values")
    tdkTestObj,status,orgValue = getMultipleParameterValues(obj,paramList)
    expectedresult = "SUCCESS";
    print("The initial ActiveMeasurement parameters values are %s" %paramList);
    if expectedresult in status and orgValue[0] != "" and orgValue[1] != "" and orgValue[2] != "" and orgValue[3] != "":
        tdkTestObj.setResultStatus("SUCCESS");
        print("ACTUAL RESULT 1:  Enable: %s, PacketSize: %s, NumberOfSamples : %s and SampleDuration : %s" %(orgValue[0],orgValue[1],orgValue[2],orgValue[3]));
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");

        typeList = ["bool","unsignedint","unsignedint","unsignedint"]
        print("TEST STEP 2: Should set ActiveMeasurement parameters to given value");
        expectedresult = "SUCCESS";
        for param, value, dtype in zip(paramList, set_ActiveMeasurementValues, typeList):
            tdkTestObj = obj1.createTestStep("WIFIAgent_Set_Get");
            tdkTestObj.addParameter("paramName", param);
            tdkTestObj.addParameter("paramValue", value);
            tdkTestObj.addParameter("paramType", dtype);
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();
            if expectedresult in actualresult and details != "":
                flag = 1
                print("Value successfully set to %s" %value);
            else:
                print("Value %s failed to set" %value);
        if flag == 1:
            print("ACTUAL RESULT 2: %s" %details);
            tdkTestObj.setResultStatus("SUCCESS");
            print("TEST EXECUTION RESULT :SUCCESS");
            print("Device is going for reboot and so waiting for the device to come up");
            obj1.initiateReboot();
            #waiting for the device to come up after reboot
            sleep(300);
            tdkTestObj = obj.createTestStep('TADstub_Get');
            tdkTestObj,status,PostrebootValue = getMultipleParameterValues(obj,paramList)
            print("The ActiveMeasurementValues after reboot are %s" %PostrebootValue);
            print("TEST STEP 3:The values should be persistant after reboot");
            expectedresult == "SUCCESS";
            if expectedresult in status and PostrebootValue[0] != "" and PostrebootValue[1] != "" and PostrebootValue[2] != "" and PostrebootValue[3] != "" and PostrebootValue == set_ActiveMeasurementValues:
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT 3:The ActiveMeasurements values persist after reboot");
                print("TEST EXECUTION RESULT :SUCCESS");

                print("TEST STEP 4: Should revert ActiveMeasurement parameters to original value");
                for param, value, dtype in zip(paramList, org_Value, typeList):
                    tdkTestObj = obj1.createTestStep("WIFIAgent_Set_Get");
                    tdkTestObj.addParameter("paramName", param);
                    tdkTestObj.addParameter("paramValue", value);
                    tdkTestObj.addParameter("paramType", dtype);
                    expectedresult == "SUCCESS";
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails();
                    if expectedresult in actualresult:
                        flag = 0;
                        print("Value set successfully to %s" %value);
                    else:
                        flag = 1;
                        print("Set failed for %s" %value);
                if flag == 0:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT 4: %s" %details);
                    print("TEST EXECUTION RESULT :SUCCESS");
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT 4: %s" %details);
                    print("TEST EXECUTION RESULT :FAILURE");
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT 3:The ActiveMeasurements values do not persist after reboot");
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");
        else:
            print("ACTUAL RESULT 2: %s" %details);
            tdkTestObj.setResultStatus("FAILURE");
            print("TEST EXECUTION RESULT :FAILURE");
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print("ACTUAL RESULT 1:Failed to get ActiveMeasurements values ");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");
    obj.unloadModule("tad");
    obj1.unloadModule("wifiagent");
else:
    print("Failed to load module");
    obj.setLoadModuleStatus("FAILURE");
    obj1.setLoadModuleStatus("FAILURE");
    print("Module loading failed")
