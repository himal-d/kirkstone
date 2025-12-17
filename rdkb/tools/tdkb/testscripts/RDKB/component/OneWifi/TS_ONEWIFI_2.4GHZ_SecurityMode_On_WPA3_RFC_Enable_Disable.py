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
  <version>4</version>
  <name>TS_ONEWIFI_2.4GHZ_SecurityMode_On_WPA3_RFC_Enable_Disable</name>
  <primitive_test_id></primitive_test_id>
  <primitive_test_name>onewifi_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Verify that the Security Mode is correctly set when the WPA3 RFC feature is disabled.</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>10</execution_time>
  <!--  -->
  <long_duration>false</long_duration>
  <!--  -->
  <advanced_script>false</advanced_script>
  <remarks></remarks>
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
    <test_case_id>TC_ONEWIFI_276</test_case_id>
    <test_objective>To check the operational mode for private_wifi_2g (AP1) when WPA3_Personal_Transition.Enable is set to true.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1. Ccsp Components in DUT should be in a running state that includes component under test Cable Modem 2. TDK Agent should be in a running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WPA3_Personal_Transition.Enable
Device.WiFi.AccessPoint.1.Security.ModeEnabled</input_parameters>
    <automation_approach>
      1. Load the module.
      2. Get enable state of WPA3 RFC using Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WPA3_Personal_Transition.Enable and set it to false.
      3. If WPA3 RFC is enabled then security mode should be WPA3-Personal-Transition
      4. Set WPA3_Personal_Transition.Enable using Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WPA3_Personal_Transition.Enable and set it to true.
      5. Get the security mode using Device.WiFi.AccessPoint.1.Security.ModeEnabled.
      6. Disable WPA3_Personal_Transition.Enable if required.
      7. Unload the module.
    </automation_approach>
    <expected_output>When WPA3_Personal_Transition.Enable is set to true, the operational mode for private_wifi_2g (AP1) should be verified correctly.</expected_output>
    <priority>High</priority>
    <test_stub_interface>WifiAgent</test_stub_interface>
    <test_script>TS_ONEWIFI_2.4GHZ_SecurityMode_On_WPA3_RFC_Enable_Disable</test_script>
    <skipped></skipped>
    <release_version>M129</release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
# Import the necessary TDK libraries
import tdklib
from tdkutility import *
from time import sleep;

# Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent", "1")

# IP and Port of box, No need to change
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_ONEWIFI_2.4GHZ_SecurityMode_On_WPA3_RFC_Enable_Disable')

# Get the result of connection with test component and DUT
loadmodulestatus = obj.getLoadModuleResult()
print("[LIB LOAD STATUS]  :  %s" % loadmodulestatus)

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS")
    expectedresult = "SUCCESS"
    step = 1

    # Step 1: Get the value of WPA3_Personal_Transition.Enable to verify it is false
    paramName = "Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WPA3_Personal_Transition.Enable"
    tdkTestObj,actualresult,initial_rfc_wpa3 = wifi_GetParam(obj,paramName)

    print("\nTEST STEP %s : Get the initial value of WPA3_Personal_Transition.Enable" % step)
    print("EXPECTED RESULT %s : Should get the initial value of WPA3_Personal_Transition.Enable as false" % step)

    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS")
        print("ACTUAL RESULT %s: The value of initial WPA3_Personal_Transition.Enable is :%s" % (step,initial_rfc_wpa3))
        print("TEST EXECUTION RESULT :SUCCESS")
    else:
        tdkTestObj.setResultStatus("FAILURE")
        print("ACTUAL RESULT %s: The value of initial WPA3_Personal_Transition.Enable is  : %s" % (step,initial_rfc_wpa3))
        print("TEST EXECUTION RESULT :FAILURE")
    step +=step
    # Step 2: Set WPA3_Personal_Transition.Enable to false
    paramName = "Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WPA3_Personal_Transition.Enable"
    tdkTestObj,actualresult = wifi_SetParam(obj,paramName,"false","boolean")
    sleep(1)

    print("\nTEST STEP %s : Set WPA3_Personal_Transition.Enable to false" % step)
    print("EXPECTED RESULT %s : Should successfully set WPA3_Personal_Transition.Enable to false" % step)

    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS")
        print("ACTUAL RESULT %s: RFC WPA3-Personal-Transition.Enable is set to false" % (step))
        print("TEST EXECUTION RESULT :SUCCESS")
    else:
        tdkTestObj.setResultStatus("FAILURE")
        print("ACTUAL RESULT %s: Failed to set RFC WPA3-Personal-Transition.Enable to false" % (step))
        print("TEST EXECUTION RESULT :FAILURE")

    step += 1

    # Step 3: Get the value of WPA3_Personal_Transition.Enable to verify it is false
    paramName = "Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WPA3_Personal_Transition.Enable"
    tdkTestObj,actualresult,rfc_wpa3 = wifi_GetParam(obj,paramName)

    print("\nTEST STEP %s : Get the value of WPA3_Personal_Transition.Enable" % step)
    print("EXPECTED RESULT %s : Should get the value of WPA3_Personal_Transition.Enable as false" % step)

    if expectedresult in actualresult and rfc_wpa3 == "false":
        tdkTestObj.setResultStatus("SUCCESS")
        print("ACTUAL RESULT %s: The value of WPA3_Personal_Transition.Enable is :%s" % (step,rfc_wpa3))
        print("TEST EXECUTION RESULT :SUCCESS")
    else:
        tdkTestObj.setResultStatus("FAILURE")
        print("ACTUAL RESULT %s: The value of WPA3_Personal_Transition.Enable is  : %s" % (step,rfc_wpa3))
        print("TEST EXECUTION RESULT :FAILURE")

    step += 1

    # Step 4: Get the current security mode
    paramName = "Device.WiFi.AccessPoint.1.Security.ModeEnabled"
    tdkTestObj,actualresult,securityMode = wifi_GetParam(obj,paramName)

    print("\nTEST STEP %s : Check the SecurityMode" % step)
    print("EXPECTED RESULT %s : SecurityMode should be WPA2-Personal when WPA3_Personal_Transition.Enable is false  " % step)

    if expectedresult in actualresult and securityMode == "WPA2-Personal":
        tdkTestObj.setResultStatus("SUCCESS")
        print("ACTUAL RESULT %s: SecurityMode is : %s" % (step, securityMode))
        print("TEST EXECUTION RESULT :SUCCESS")
    else:
        tdkTestObj.setResultStatus("FAILURE")
        print("ACTUAL RESULT %s: SecurityMode is  : %s" % (step, securityMode))
        print("TEST EXECUTION RESULT :FAILURE")

    step += 1

    # Step 5: Set WPA3_Personal_Transition.Enable to true
    paramName = "Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WPA3_Personal_Transition.Enable"
    tdkTestObj,actualresult = wifi_SetParam(obj,paramName,"true","boolean")
    sleep(1)

    print("\nTEST STEP %s : Set WPA3_Personal_Transition.Enable to true" % step)
    print("EXPECTED RESULT %s : Should successfully set WPA3_Personal_Transition.Enable to true" % step)

    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS")
        print("ACTUAL RESULT %s: The value of WPA3_Personal_Transition.Enable is set to true " % (step))
        print("TEST EXECUTION RESULT :SUCCESS")
    else:
        tdkTestObj.setResultStatus("FAILURE")
        print("ACTUAL RESULT %s: Failed to set value of WPA3_Personal_Transition.Enable to true %s" % (step, rfc_wpa3))
        print("TEST EXECUTION RESULT :FAILURE")

    step += 1

    # Step 6: Get the value of WPA3_Personal_Transition.Enable to verify it is true
    paramName = "Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WPA3_Personal_Transition.Enable"
    tdkTestObj,actualresult,rfc_wpa3 = wifi_GetParam(obj,paramName)

    print("\nTEST STEP %s : Get the value of WPA3_Personal_Transition.Enable" % step)
    print("EXPECTED RESULT %s : Should get the value of WPA3_Personal_Transition.Enable as true" % step)

    if expectedresult in actualresult and rfc_wpa3 == "true":
        tdkTestObj.setResultStatus("SUCCESS")
        print("ACTUAL RESULT %s: The value of WPA3_Personal_Transition.Enable is: %s" % (step, rfc_wpa3))
        print("TEST EXECUTION RESULT :SUCCESS")
    else:
        tdkTestObj.setResultStatus("FAILURE")
        print("ACTUAL RESULT %s: The value of WPA3_Personal_Transition.Enable is : %s" % (step, rfc_wpa3))
        print("TEST EXECUTION RESULT :FAILURE")

    step += 1

    # Step 7: Get the security mode again to verify it has changed
    paramName = "Device.WiFi.AccessPoint.1.Security.ModeEnabled"
    tdkTestObj,actualresult,newSecurityMode = wifi_GetParam(obj,paramName)

    print("\nTEST STEP %d : Check security mode after enabling RFC WPA3_Personal_Transition" % step)
    print("EXPECTED RESULT %d : Security mode should be WPA3-Personal-Transition after enabling RFC WPA3_Personal_Transition " % step)

    if expectedresult in actualresult and newSecurityMode == "WPA3-Personal-Transition":
        tdkTestObj.setResultStatus("SUCCESS")
        print("ACTUAL RESULT %d: Security Mode after enabling RFC WPA3_Personal_Transition %s" % (step, newSecurityMode))
        print("TEST EXECUTION RESULT :SUCCESS")
    else:
        tdkTestObj.setResultStatus("FAILURE")
        print("ACTUAL RESULT %d: Security Mode after enabling RFC WPA3_Personal_Transition %s" % (step, newSecurityMode))
        print("TEST EXECUTION RESULT :FAILURE")

    step += 1
    # Step 8: Revert WPA3_Personal_Transition.Enable back to initial value
    paramName = "Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WPA3_Personal_Transition.Enable"
    tdkTestObj,actualresult = wifi_SetParam(obj,paramName,initial_rfc_wpa3,"boolean")

    print("\nTEST STEP %d : Set WPA3_Personal_Transition.Enable back to initial value" % step)
    print("EXPECTED RESULT %d : Should successfully set WPA3_Personal_Transition.Enable back to initial value" % step)

    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS")
        print("ACTUAL RESULT %d: The value of WPA3_Personal_Transition.Enable is set to: %s" % (step,initial_rfc_wpa3))
        print("TEST EXECUTION RESULT :SUCCESS")
    else:
        tdkTestObj.setResultStatus("FAILURE")
        print("ACTUAL RESULT %d: Failed to set the value of WPA3_Personal_Transition.Enable to initial value: %s" % (step))
        print("TEST EXECUTION RESULT :FAILURE")

    obj.unloadModule("wifiagent")
else:
    print("Failed to load the module")
    obj.setLoadModuleStatus("FAILURE")
    print("Module loading failed")
