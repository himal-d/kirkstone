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
  <version>2</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_ONEWIFI_PreferPrivate_After_FactoryReset</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>onewifi_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To check whether PreferPrivate is populating with default value after Factory Reset</synopsis>
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
    <test_case_id>TC_ONEWIFI_251</test_case_id>
    <test_objective>To check whether PreferPrivate is populating with default value after Factory Reset</test_objective>
    <test_type></test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem 2.TDK Agent should be in running state or invoke it through StartTdk.sh script
</pre_requisite>
    <api_or_interface_used></api_or_interface_used>
    <input_parameters>Device.WiFi.X_RDKCENTRAL-COM_PreferPrivate</input_parameters>
    <automation_approch>1.Load the module.
2.Get the value of Prefer Private using Device.WiFi.X_RDKCENTRAL-COM_PreferPrivate and store it.
3.Change the value of prefer private to true using Device.WiFi.X_RDKCENTRAL-COM_PreferPrivate.
4.Perform Factory Reset.
5.Get the value of Prefer Private after Factory Reset .
6.Unload the module</automation_approch>
    <expected_output>PreferPrivate should populate with default value after factory reset</expected_output>
    <priority></priority>
    <test_stub_interface>WifiAgent</test_stub_interface>
    <test_script>TS_ONEWIFI_PreferPrivate_After_FactoryReset</test_script>
    <skipped></skipped>
    <release_version>M129</release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
#import statements
import tdklib
from tdkutility import *
from time import sleep
#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent","1")
#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_ONEWIFI_PreferPrivate_After_FactoryReset')

#Get the result of connection with test component
loadmodulestatus =obj.getLoadModuleResult()
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus)

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS")
    expectedresult = "SUCCESS"
    # Step 1: Get the initial Prefer Private and store it
    paramName = "Device.WiFi.X_RDKCENTRAL-COM_PreferPrivate"
    tdkTestObj,actualresult,initialPreferPrivate = wifi_GetParam(obj,paramName)
    print("TEST STEP 1: Get the initial PreferPrivate")
    print("EXPECTED RESULT 1: Should get the initial PreferPrivate")

    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS")
        print("ACTUAL RESULT 1: Initial PreferPrivate is %s" % initialPreferPrivate)
        print("[TEST EXECUTION RESULT] : SUCCESS")

        # Step 2: Toggle the prefer private before Factory Reset
        toggle_pp = str(not (initialPreferPrivate.lower() == "true")).lower()
        tdkTestObj,actualresult = wifi_SetParam(obj,paramName,toggle_pp, "bool")

        print("TEST STEP 2: Toggle the PreferPrivate ")
        print("EXPECTED RESULT 2: Should toggle the PreferPrivate")

        if expectedresult in actualresult:
            tdkTestObj.setResultStatus("SUCCESS")
            print("ACTUAL RESULT 2: PreferPrivate toggled successfully")
            print("[TEST EXECUTION RESULT] : SUCCESS")

            #Step 3: Get the value and verify
            tdkTestObj,actualresult,PreferPrivate = wifi_GetParam(obj,paramName)

            print("TEST STEP 3: Get the PreferPrivate  value")
            print("EXPECTED RESULT 3: Should get the PreferPrivate value")

            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS")
                print("ACTUAL RESULT 3: PreferPrivate value after toggling is %s" % PreferPrivate)
                print("[TEST EXECUTION RESULT] : SUCCESS")

                # Save the current state before going to reboot
                obj.saveCurrentState()
                #Step 4: Initiate Factory reset before checking the default value
                paramName_FR = "Device.X_CISCO_COM_DeviceControl.FactoryReset"
                tdkTestObj,actualresult = wifi_SetParam(obj,paramName_FR,"Router,Wifi,VoIP,Dect,MoCA","string")

                print("TEST STEP 4: Initiate factory reset ")
                print("EXPECTED RESULT 4: Should initiate factory reset")

                if expectedresult in actualresult:
                    tdkTestObj.setResultStatus("SUCCESS")
                    print("ACTUAL RESULT 4: Factory Reset successfull")
                    print("[TEST EXECUTION RESULT] : SUCCESS")

                    #Restore the device state saved before reboot
                    obj.restorePreviousStateAfterReboot()
                    #Wait for the WiFi namespace to come up upto 3 minutes (6 iterations of 30s)
                    found, tdkTestObj = wait_for_namespace(obj, 6, 30, "Device.WiFi.", expectedresult)
                    #Step 5: Get the default value of PreferPrivate after FactoryReset

                    if found == 1:
                        tdkTestObj,actualresult,PreferPrivate = wifi_GetParam(obj,paramName)

                        print("TEST STEP 5: Get the PreferPrivate after factory reset ")
                        print("EXPECTED RESULT 5: Should get the PreferPrivate after Factory Reset")

                        if expectedresult in actualresult:
                            tdkTestObj.setResultStatus("SUCCESS")
                            print("ACTUAL RESULT 5: PreferPrivate after Factory Reset is %s" % PreferPrivate)
                            print("[TEST EXECUTION RESULT] : SUCCESS")

                            #Step 6 verify the PreferPrivate value is populating with default value
                            print("TEST STEP 6: verify whether PreferPrivate is populating with default value")
                            print("EXPECTED RESULT 6: PreferPrivate should populate with default value")

                            if PreferPrivate == "false":
                                tdkTestObj.setResultStatus("SUCCESS")
                                print("ACTUAL RESULT 6: PreferPrivate is populating with default value")
                                print("[TEST EXECUTION RESULT] : SUCCESS")
                            else:
                                tdkTestObj.setResultStatus("FAILURE")
                                print("ACTUAL RESULT 6: PreferPrivate is not populating with default value")
                                print("[TEST EXECUTION RESULT] : FAILURE")
                        else:
                            tdkTestObj.setResultStatus("FAILURE")
                            print("ACTUAL RESULT 5: Failed to get PreferPrivate after Factory Reset.")
                            print("[TEST EXECUTION RESULT] : FAILURE")
                    else:
                        tdkTestObj.setResultStatus("FAILURE")
                        print("Device.WiFi. namespace not available after Factory Reset")
                else:
                    tdkTestObj.setResultStatus("FALURE")
                    print("ACTUAL RESULT 4: Failed to initiate factory reset")
                    print("[TEST EXECUTION RESULT] : FALURE")
            else:
                tdkTestObj.setResultStatus("FAILURE")
                print("ACTUAL RESULT 3: PreferPrivate value after toggling is %s" % PreferPrivate)
                print("[TEST EXECUTION RESULT] : FAILURE")
        else:
            tdkTestObj.setResultStatus("FAILURE")
            print("ACTUAL RESULT 2: Failed to toggle PreferPrivate")
            print("[TEST EXECUTION RESULT] : FAILURE")
    else:
        tdkTestObj.setResultStatus("FAILURE")
        print("ACTUAL RESULT 1: Failed to get initial PreferPrivate")
        print("[TEST EXECUTION RESULT] : FAILURE")

    # Unload wifiagent module
    obj.unloadModule("wifiagent")
else:
    print("Failed to load wifiagent module")
    obj.setLoadModuleStatus("FAILURE")
    print("Module loading failed")
