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
  <name>TS_ONEWIFI_FR_CheckActiveMeasurementsvalues</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>onewifi_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>3</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check if ActiveMeasurements default values are restored after factory reset</synopsis>
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
    <test_case_id>TC_ONEWIFI_241</test_case_id>
    <test_objective>Check if ActiveMeasurements default values are restored after factory reset</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Device.WiFi.X_RDKCENTRAL-COM_ActiveMeasurements.Enable
Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.PacketSize
Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.SampleDuration
Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.NumberOfSamples</input_parameters>
    <automation_approch>1. Load wifiagent, tad and sysutil modules
2. Do a factory reset and get the ActiveMeasurements values
3. Check if it is restored to default value
4. Unload wifiagent, tad and sysutil modules</automation_approch>
    <expected_output>After factory reset,ActiveMeasurements should be restored to default values</expected_output>
    <priority>High</priority>
    <test_stub_interface>ONEWIFI/obj1</test_stub_interface>
    <test_script>TS_ONEWIFI_FR_CheckActiveMeasurementsvalues</test_script>
    <skipped>No</skipped>
    <release_version>M116</release_version>
    <remarks>None</remarks>
  </test_cases>
  <script_tags />
</xml>
'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
import time;
import tdkutility;
from tdkutility import *
from tdkbVariables import *
#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent","1");
obj1 = tdklib.TDKScriptingLibrary("tad","1");
obj2 = tdklib.TDKScriptingLibrary("sysutil","1");
#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_ONEWIFI_FR_CheckActiveMeasurementsvalues');
obj1.configureTestCase(ip,port,'TS_ONEWIFI_FR_CheckActiveMeasurementsvalues');
obj2.configureTestCase(ip,port,'TS_ONEWIFI_FR_CheckActiveMeasurementsvalues');
#Get the result of connection with test component and STB
loadmodulestatus1 = obj.getLoadModuleResult();
loadmodulestatus2 = obj1.getLoadModuleResult();
loadmodulestatus3 = obj2.getLoadModuleResult();
if "SUCCESS" in loadmodulestatus1.upper() and "SUCCESS" in loadmodulestatus2.upper() and "SUCCESS" and loadmodulestatus3.upper() :
    obj.setLoadModuleStatus("SUCCESS");
    expectedresult = "SUCCESS"
    obj.saveCurrentState();
    #Initiate Factory reset before checking the default value
    tdkTestObj = obj.createTestStep('WIFIAgent_Set');
    tdkTestObj.addParameter("paramName","Device.X_CISCO_COM_DeviceControl.FactoryReset");
    tdkTestObj.addParameter("paramValue","Router,Wifi,VoIP,Dect,MoCA");
    tdkTestObj.addParameter("paramType","string");
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print("TEST STEP 1: Initiate factory reset ");
        print("ACTUAL RESULT 1: %s" %details);
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");
        #Restore the device state saved before reboot
        obj.restorePreviousStateAfterReboot();
        time.sleep(180);

        print("TEST STEP 2: Get the ActiveMeasurement parameters value after factory reset");
        paramList=["Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WifiClient.ActiveMeasurements.Enable", "Device.WiFi.X_RDKCENTRAL-COM_Report.WifiClient.ActiveMeasurements.PacketSize", "Device.WiFi.X_RDKCENTRAL-COM_Report.WifiClient.ActiveMeasurements.SampleDuration","Device.WiFi.X_RDKCENTRAL-COM_Report.WifiClient.ActiveMeasurements.NumberOfSamples"]
        tdkTestObj = obj1.createTestStep('TADstub_Get');
        tdkTestObj,status,orgValue = getMultipleParameterValues(obj1,paramList)
        expectedresult = "SUCCESS";
        ActiveMeasurementsEnable = orgValue[0]
        ActiveMeasurementsPacketSize = orgValue[1]
        ActiveMeasurementsSampleDuration = orgValue[2]
        ActiveMeasurementsNumberOfSamples = orgValue[3]
        if expectedresult in status and ActiveMeasurementsEnable != "" and ActiveMeasurementsPacketSize != "" and ActiveMeasurementsSampleDuration != "" and ActiveMeasurementsNumberOfSamples != "":
            tdkTestObj.setResultStatus("SUCCESS");
            print("ACTUAL RESULT 2: ActiveMeasurements Enable status: %s, ActiveMeasurementsPacketSize : %s ,ActiveMeasurementsSampleDuration :  %s ,ActiveMeasurementsNumberOfSamples :%s" %(ActiveMeasurementsEnable,ActiveMeasurementsPacketSize,ActiveMeasurementsSampleDuration,ActiveMeasurementsNumberOfSamples));
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");

            print("TEST STEP 3: Get the expected ActiveMeasurementsValues from the properties file")
            print("EXPECTED RESULT 3: Should be able to retrieve expected ActiveMeasurementsValues from the properties file")
            tdkTestObj = obj2.createTestStep('ExecuteCmd');
            ActiveMeasurementsValues= "sh %s/tdk_utility.sh parseConfigFile DEFAULT_ActiveMeasurements_VALUES" %TDK_PATH;
            expectedresult="SUCCESS";
            tdkTestObj.addParameter("command", ActiveMeasurementsValues);
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            ActiveMeasurementsValuesList = tdkTestObj.getResultDetails().strip().replace("\\n", "");
            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT 3:Active Measurements value from properties file:%s" %ActiveMeasurementsValuesList);
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : SUCCESS");
                details=[]
                def Convert(string):
                    li = list(string.split("],"))
                    c=li
                    return li
                c=Convert(ActiveMeasurementsValuesList)
                for x in range(len(c)):
                    if '[' in c[x]:
                        if ']' in c[x]:
                            e=c[x].strip('[')
                            details.append(e.strip(']'))
                        else:
                            details.append(c[x].strip('['))
                print("The ActiveMeasurements values after factory reset are %s" %details);
                print("TEST STEP 4: Should get default ActiveMeasurements values after factory reset");
                if orgValue == details:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT 4:Restored to default ActiveMeasurements values after factory reset");
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : SUCCESS");
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT 4:Failed to restore to default ActiveMeasurements values after factory reset");
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT 3:Failed to get value from properties file ");
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print("ACTUAL RESULT 2:Failed to get ActiveMeasurements values after factory reset");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");
    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print("TEST STEP 1: Initiate factory reset ");
        print("ACTUAL RESULT 1: %s" %details);
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");
    obj.unloadModule("wifiagent");
    obj1.unloadModule("tad");
    obj2.unloadModule("sysutil");
else:
    print("Failed to load the module");
    obj.setLoadModuleStatus("FAILURE");
    obj1.setLoadModuleStatus("FAILURE");
    obj2.setLoadModuleStatus("FAILURE");
    print("Module loading failed");
