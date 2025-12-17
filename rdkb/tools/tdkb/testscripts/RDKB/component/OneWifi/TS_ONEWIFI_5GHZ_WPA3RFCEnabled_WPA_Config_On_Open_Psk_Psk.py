##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2024 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License")
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
  <name>TS_ONEWIFI_5GHZ_WPA3RFCEnabled_WPA_Config_On_Open_Psk_Psk</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>onewifi_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>When RFC WPA3-Personal-Transition is enabled check WPA configuration on security mode transition (None-WPA3-Personal-WPA3-Personal-Transition) for 5GHZ</synopsis>
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
    <test_case_id>TC_ONEWIFI_269</test_case_id>
    <test_objective>When WPA3_Personal_Transition RFC Feature is enabled and When security mode transitions from None to WPA3-Personal to WPA3-Personal-Transition  (open-psk-psk), check if the WPA configuration (Encryption method and Preshared key) are updated for(None--> WPA3-Personal) and does not gets reset for(WPA3-Personal-->WPA3-Personal-Transition) for 5GHZ</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite><1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem 2.TDK Agent should be in running state or invoke it through StartTdk.sh script/pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.WPA3_Personal_Transition.Enable
Device.WiFi.AccessPoint.2.Security.ModeEnabled
Device.WiFi.AccessPoint.2.Security.X_CISCO_COM_EncryptionMethod
Device.WiFi.AccessPoint.2.Security.PreSharedKey
name: Device.WiFi.AccessPoint.2.Security.KeyPassphrase</input_parameters>
    <automation_approch>1. Load the module.
2. Get the initial security mode using Device.WiFi.AccessPoint.2.Security.ModeEnabled and store it.
3. Change security mode to None using Device.WiFi.AccessPoint.2.Security.ModeEnabled.
4. Check initial WPA config using Device.WiFi.AccessPoint.2.Security.X_CISCO_COM_EncryptionMethod and Device.WiFi.AccessPoint.2.Security.PreSharedKey. Both the values should be empty when security mode is "None".
5. Change the security mode to WPA3-Personal, Encryption method to AES and Preshared key to a new value.
6. Check if security mode set is reflected in get and if the WPA configuration is set to the new values.
7. Then set to the next personal mode WPA3-Personal-Transition by setting Device.WiFi.AccessPoint.2.Security.ModeEnabled.
8. Check if mode set is reflected in get and check if the WPA configuration is not reset.
9. Revert to initial security mode.
10. Unload the module</automation_approch>
    <expected_output>When security mode changes for open to psk (None to WPA3-Personal) WPA config should reset. When security mode changes from psk to psk (WPA3-Personal to WPA3-Personal-Transition) WPA config should not reset.</expected_output>
    <priority>High</priority>
    <test_stub_interface>WifiAgent</test_stub_interface>
    <test_script>TS_ONEWIFI_5GHZ_WPA3RFCEnabled_WPA_Config_On_Open_Psk_Psk</test_script>
    <skipped></skipped>
    <release_version>M129</release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
#imort statements
import tdklib
from tdkutility import *
from tdkbVariables import *
from time import sleep

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent","1")
sysobj = tdklib.TDKScriptingLibrary("sysutil", "1")


#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_ONEWIFI_5GHZ_WPA3RFCEnabled_WPA_Config_On_Open_Psk_Psk')
sysobj.configureTestCase(ip,port,'TS_ONEWIFI_5GHZ_WPA3RFCEnabled_WPA_Config_On_Open_Psk_Psk')

# Get the result of connection with test component and DUT
loadmodulestatus = obj.getLoadModuleResult()
loadmodulestatus1 = sysobj.getLoadModuleResult()
revertflag = 0
RADIUS_SECRET = "Aa12345678"
PRESHAREDKEY = "Aa12345678"

if "SUCCESS" in loadmodulestatus.upper() and "SUCCESS" in loadmodulestatus1.upper():
    # Set the load module status
    obj.setLoadModuleStatus("SUCCESS")
    sysobj.setLoadModuleStatus("SUCCESS")
    expectedresult = "SUCCESS"

    #step 1: Get the Radius and WPA config values from tdk_platform.properties
    step = 1
    config_keys = ["RADIUS_IP", "RADIUS_PORT","ENCRYPTION_MODE"]
    config_values = {}
    actualresult_all = []
    for key in config_keys:
        command = "sh %s/tdk_utility.sh parseConfigFile %s" % (TDK_PATH, key)
        tdkTestObj, actualresult, config_values[key] = get_config_values(sysobj, command)
        actualresult_all.append(actualresult)
    RADIUS_IP = config_values["RADIUS_IP"]
    RADIUS_PORT = config_values["RADIUS_PORT"]
    ENCRYPTION_MODE = config_values["ENCRYPTION_MODE"]

    print(f"\nTEST STEP {step}: Get the Radius and WPA config info from tdk_platform.properties")
    print(f"EXPECTED RESULT {step}: Should get the radius and wpa config info from tdk_platform.properties")

    if "FAILURE" not in actualresult_all:
        tdkTestObj.setResultStatus("SUCCESS")
        print(f"ACTUAL RESULT {step}: RADIUS_IP:{RADIUS_IP}, RADIUS_PORT:{RADIUS_PORT}, RADIUS_SECRET:{RADIUS_SECRET}, ENCRYPTION_METHOD:{ENCRYPTION_MODE}, PRESHAREDKEY:{PRESHAREDKEY}")
        print("[TEST EXECUTION RESULT] : SUCCESS")

        #Get the initial security mode
        step = step+1
        paramName = "Device.WiFi.AccessPoint.2.Security.ModeEnabled"
        tdkTestObj,actualresult,initialSecurityMode = wifi_GetParam(obj,paramName)

        print(f"\nTEST STEP {step}: Get the initial security mode")
        print(f"EXPECTED RESULT {step}: Should get the initial security mode")

        if expectedresult in actualresult:
            tdkTestObj.setResultStatus("SUCCESS")
            print(f"ACTUAL RESULT {step}: Initial security mode is %s" % initialSecurityMode)
            print("[TEST EXECUTION RESULT] : SUCCESS")

            if "Personal" in initialSecurityMode:
                #Get the Keypassphrase and encryption method
                paramNames = [
                        "Device.WiFi.AccessPoint.2.Security.KeyPassphrase",
                        "Device.WiFi.AccessPoint.2.Security.X_CISCO_COM_EncryptionMethod"
                        ]
                paramResults = {}
                actualresult_all = []

                for paramName in paramNames:
                    tdkTestObj, actualresult, paramValue = wifi_GetParam(obj, paramName)
                    actualresult_all.append(actualresult)
                    paramResults[paramName] = paramValue

                initialKeypassphrase = paramResults["Device.WiFi.AccessPoint.2.Security.KeyPassphrase"]
                initialencryptionMethod = paramResults["Device.WiFi.AccessPoint.2.Security.X_CISCO_COM_EncryptionMethod"]
                step = step + 1
                print(f"\nTEST STEP {step}: Get the initial Keypassphrase and encryption method")
                print(f"EXPECTED RESULT {step}: Should get the initial Keypassphrase and encryption method")

                if "FAILURE" not in actualresult_all:
                    tdkTestObj.setResultStatus("SUCCESS")
                    print(f"ACTUAL RESULT {step}: Initial keypassphrase is {initialKeypassphrase} and initial encryption method is {initialencryptionMethod} ")
                    print("[TEST EXECUTION RESULT] : SUCCESS")
                else:
                    tdkTestObj.setResultStatus("FAILURE")
                    print(f"ACTUAL RESULT {step}: Failed to get initial Keypassphrase and encryption method")
                    print("[TEST EXECUTION RESULT] : FAILURE")
            else:
                #Get Radius config and encryption mode
                paramNames = [
                        "Device.WiFi.AccessPoint.2.Security.RadiusServerIPAddr",
                        "Device.WiFi.AccessPoint.2.Security.RadiusServerPort",
                        "Device.WiFi.AccessPoint.2.Security.X_CISCO_COM_EncryptionMethod"
                        ]
                paramResults = {}
                actualresult_all = []

                for paramName in paramNames:
                    tdkTestObj, actualresult, paramValue = wifi_GetParam(obj, paramName)
                    actualresult_all.append(actualresult)
                    paramResults[paramName] = paramValue

                initialRadiusIP = paramResults["Device.WiFi.AccessPoint.2.Security.RadiusServerIPAddr"]
                initialRadiusport = paramResults["Device.WiFi.AccessPoint.2.Security.RadiusServerPort"]
                initialencryptionMethod = paramResults["Device.WiFi.AccessPoint.2.Security.X_CISCO_COM_EncryptionMethod"]
                step = step + 1
                print(f"\nTEST STEP {step}: Get the initial radius config and encryption method")
                print(f"EXPECTED RESULT {step}: Should get the initial radius config and encryption method")

                if "FAILURE" not in actualresult_all:
                    tdkTestObj.setResultStatus("SUCCESS")
                    print(f"ACTUAL RESULT {step}:Initial radiusIP is {initialRadiusIP} , initial radius port is {initialRadiusport} and initial encryption method is {initialencryptionMethod} ")
                    print("[TEST EXECUTION RESULT] : SUCCESS")
                else:
                    tdkTestObj.setResultStatus("FAILURE")
                    print(f"ACTUAL RESULT {step}: Failed to get initial radius config and encryption method")
                    print("[TEST EXECUTION RESULT] : FAILURE")

            #Check the Pre-requisites - WPA3_Personal_Transition RFC should be enabled
            step = step + 1
            pre_req_set, tdkTestObj, step, revert_flag, initial_value = CheckWPA3Pre_requiste(obj, step)

            if pre_req_set == 1:
                print("\n*************RFC Pre-requisite set for the DUT*****************")

                #Change Security Mode to None
                step = step + 1
                paramName = "Device.WiFi.AccessPoint.2.Security.ModeEnabled"
                tdkTestObj, actualresult = wifi_SetParam(obj,paramName,"None","string")
                sleep(2)
                print("TEST STEP %s: Change security mode to None" % step)
                print("EXPECTED RESULT %s: Should change security mode to None" % step)

                if expectedresult in actualresult:
                    tdkTestObj.setResultStatus("SUCCESS")
                    revertflag = 1
                    print("ACTUAL RESULT %s: Security mode changed to None" % step)
                    print("[TEST EXECUTION RESULT] : SUCCESS")

                    #Check Security Mode and initial WPA Config
                    step = step + 1
                    paramList_config = ["Device.WiFi.AccessPoint.2.Security.ModeEnabled",
                                    "Device.WiFi.AccessPoint.2.Security.X_CISCO_COM_EncryptionMethod",
                                    "Device.WiFi.AccessPoint.2.Security.PreSharedKey",
                                    "Device.WiFi.AccessPoint.2.Security.KeyPassphrase"
                                    ]
                    expected_values = ["None", "","","0.0"]
                    actual_values = []
                    actualresult_all = []

                    for param in paramList_config:
                        tdkTestObj, actualresult, value = wifi_GetParam(obj, param)
                        actualresult_all.append(actualresult)
                        actual_values.append(value)

                    print("TEST STEP %s: Check security mode and WPA configuration" % step)
                    print("EXPECTED RESULT %s: WPA configuration values should be reset when security mode is None" % step)

                    if "FAILURE" not in actualresult_all and actual_values == expected_values:
                        tdkTestObj.setResultStatus("SUCCESS")
                        print("ACTUAL RESULT %s: SecurityMode is '%s',Encryption Mode is ' %s', PresharedKey is ' %s', KeyPasspharse is ' %s'" % (step,actual_values[0],actual_values[1],actual_values[2],actual_values[3]))
                        print("[TEST EXECUTION RESULT] : SUCCESS")

                        #Change Security Mode to WPA3-Personal, Encryption Mode to AES, PreSharedKey to Aa12345678
                        step = step + 1
                        print(step)
                        tdkTestObj = obj.createTestStep("WIFIAgent_SetMultiple")
                        print(step)
                        paramList = ("Device.WiFi.AccessPoint.2.Security.ModeEnabled|WPA3-Personal|string|"
                                "Device.WiFi.AccessPoint.2.Security.X_CISCO_COM_EncryptionMethod|%s|string|"
                                "Device.WiFi.AccessPoint.2.Security.PreSharedKey|%s|string" % (ENCRYPTION_MODE,PRESHAREDKEY))
                        tdkTestObj.addParameter("paramList", paramList)
                        tdkTestObj.executeTestCase(expectedresult)
                        actualresult = tdkTestObj.getResult()
                        sleep(2)

                        print(f"TEST STEP {step}: Change security mode to WPA3-Personal, Encryption mode to {ENCRYPTION_MODE} and PresharedKey to {PRESHAREDKEY} ")
                        print("EXPECTED RESULT %s: Should set security mode to WPA3-Personal and WPA config parameters to new values" % step)

                        if expectedresult in actualresult:
                            tdkTestObj.setResultStatus("SUCCESS")
                            print("ACTUAL RESULT %s: Security mode set to WPA3-Personal, WPA config parameters are updated" % step)
                            print("[TEST EXECUTION RESULT] : SUCCESS")

                            #Check Security Mode and WPA Configuration

                            step = step + 1
                            paramList_config = ["Device.WiFi.AccessPoint.2.Security.ModeEnabled",
                                    "Device.WiFi.AccessPoint.2.Security.X_CISCO_COM_EncryptionMethod",
                                    "Device.WiFi.AccessPoint.2.Security.PreSharedKey",
                                    "Device.WiFi.AccessPoint.2.Security.KeyPassphrase"
                                    ]
                            expected_values = ["WPA3-Personal", ENCRYPTION_MODE, "", "Aa12345678"]
                            actual_values = []
                            actualresult_all = []

                            for param in paramList_config:
                                tdkTestObj, actualresult, value = wifi_GetParam(obj, param)
                                actualresult_all.append(actualresult)
                                actual_values.append(value)

                            print("TEST STEP %s: Check security mode and WPA configuration Values" % step)
                            print("EXPECTED RESULT %s: Security mode should be WPA3-Personal Encryption mode should be 'AES' and KeyPassphrase should be 'Aa12345678'" % step)
                            if "FAILURE" not in actualresult_all and actual_values == expected_values:
                                tdkTestObj.setResultStatus("SUCCESS")
                                print("ACTUAL RESULT %s: Security mode is '%s', Encryption method is '%s', PreSharedKey is ' %s', KeyPassphrase is ' %s'" % (step,actual_values[0],actual_values[1],actual_values[2],actual_values[3]))
                                print("[TEST EXECUTION RESULT] : SUCCESS")

                                #Change Security Mode WPA3-Personal-Transition

                                step = step + 1
                                paramName = "Device.WiFi.AccessPoint.2.Security.ModeEnabled"
                                tdkTestObj,actualresult = wifi_SetParam(obj,paramName,"WPA3-Personal-Transition","string")
                                sleep(2)

                                print("TEST STEP %s: Change security mode to WPA3-Personal-Transition" % step)
                                print("EXPECTED RESULT %s: Should set security mode to WPA3-Personal-Transition" % step)

                                if expectedresult in actualresult:
                                    tdkTestObj.setResultStatus("SUCCESS")
                                    print("ACTUAL RESULT %s: Security mode set to WPA3-Personal-Transition:" % step)
                                    print("[TEST EXECUTION RESULT] : SUCCESS")

                                    #Check Security Mode and WPA Configuration

                                    step = step + 1
                                    paramList_config = ["Device.WiFi.AccessPoint.2.Security.ModeEnabled",
                                                        "Device.WiFi.AccessPoint.2.Security.X_CISCO_COM_EncryptionMethod",
                                                        "Device.WiFi.AccessPoint.2.Security.PreSharedKey",
                                                        "Device.WiFi.AccessPoint.2.Security.KeyPassphrase"
                                                    ]
                                    expected_values = ["WPA3-Personal-Transition", ENCRYPTION_MODE, "", "Aa12345678"]
                                    actual_values = []
                                    actualresult_all = []

                                    for param in paramList_config:
                                        tdkTestObj, actualresult, value = wifi_GetParam(obj, param)
                                        actualresult_all.append(actualresult)
                                        actual_values.append(value)

                                    print("TEST STEP %s: Check security mode and WPA configuration Values" % step)
                                    print(f"EXPECTED RESULT {step}: Security mode should be WPA3-Personal-Transition Encryption mode should be {ENCRYPTION_MODE} and KeyPassphrase should be 'Aa12345678'")

                                    if "FAILURE" not in actualresult_all and actual_values == expected_values:
                                        tdkTestObj.setResultStatus("SUCCESS")
                                        print("ACTUAL RESULT %s: Security mode is '%s', Encryption method is '%s', PreSharedKey is ' %s', KeyPassphrase is ' %s'" % (step,actual_values[0],actual_values[1],actual_values[2],actual_values[3]))
                                        print("[TEST EXECUTION RESULT] : SUCCESS")
                                    else:
                                        tdkTestObj.setResultStatus("FAILURE")
                                        print("ACTUAL RESULT %s: Security mode is '%s', Encryption method is '%s', PreSharedKey is ' %s', KeyPassphrase is ' %s'" % (step,actual_values[0],actual_values[1],actual_values[2],actual_values[3]))
                                        print("[TEST EXECUTION RESULT] : FAILURE")
                                else:
                                    tdkTestObj.setResultStatus("FAILURE")
                                    print("ACTUAL RESULT %s: Failed to change SecurityMode to WPA3-Personal-Transition and WPA configuration parameters to new values" % step)
                                    print("[TEST EXECUTION RESULT] : FAILURE")
                            else:
                                tdkTestObj.setResultStatus("FAILURE")
                                print("ACTUAL RESULT %s: Security mode is '%s', Encryption method is '%s', PreSharedKey is ' %s', KeyPassphrase is ' %s'" % (step,actual_values[0],actual_values[1],actual_values[2],actual_values[3]))
                                print("[TEST EXECUTION RESULT] : FAILURE")
                        else:
                            tdkTestObj.setResultStatus("FAILURE")
                            print("ACTUAL RESULT %s: Failed to change SecurityMode to WPA3-Personal and WPA configuration parameters to new values" % step)
                            print("[TEST EXECUTION RESULT] : FAILURE")
                    else:
                        tdkTestObj.setResultStatus("FAILURE")
                        print("ACTUAL RESULT %s: SecurityMode is '%s',Encryption Mode is ' %s', PresharedKey is ' %s', KeyPasspharse is ' %s'" % (step,actual_values[0],actual_values[1],actual_values[2],actual_values[3]))
                        print("[TEST EXECUTION RESULT] : FAILURE")
                else:
                    tdkTestObj.setResultStatus("FAILURE")
                    print("ACTUAL RESULT %s: Failed to change SecurityMode to None" % step)
                    print("[TEST EXECUTION RESULT] : FAILURE")

                #Revert the pre-requisites set
                if revert_flag == 1:
                    step = step + 1
                    status = RevertWPA3Pre_requisite(obj, initial_value)

                    print("\nTEST STEP %d : Revert the pre-requisite to initial value" %step)
                    print("EXPECTED RESULT %d : Pre-requisites set should be reverted successfully" %step)

                    if status == 1:
                        tdkTestObj.setResultStatus("SUCCESS")
                        print("ACTUAL RESULT %d : Revert operation was success" %step)
                        print("[TEST EXECUTION RESULT] : SUCCESS")
                    else:
                        tdkTestObj.setResultStatus("FAILURE")
                        print("ACTUAL RESULT %d : Revert operation failed" %step)
                        print("[TEST EXECUTION RESULT] : FAILURE")
                else:
                    tdkTestObj.setResultStatus("FAILURE")
                    print("Reverting to pre-requisites Failed")
            else:
                print("Pre-Requisite is not set successfully")
        else:
            tdkTestObj.setResultStatus("FAILURE")
            print("ACTUAL RESULT %s: Initial security mode is %s" % (initialSecurityMode,step))
            print("[TEST EXECUTION RESULT] : FAILURE")
    else:
        tdkTestObj.setResultStatus("FAILURE")
        print("ACTUAL RESULT %s: Failed to get the Radius and WPA config info from tdk_platform.properties")
        print("[TEST EXECUTION RESULT] : FAILURE")

    if revertflag == 1:

        #Revert to initial SecurityMode
        if "Personal" in initialSecurityMode:
            paramList = ("Device.WiFi.AccessPoint.2.Security.ModeEnabled|%s|string|Device.WiFi.AccessPoint.2.Security.X_CISCO_COM_EncryptionMethod|%s|string|Device.WiFi.AccessPoint.2.Security.PreSharedKey|%s|string" %(initialSecurityMode,initialencryptionMethod,initialKeypassphrase))
            tdkTestObj = obj.createTestStep("WIFIAgent_SetMultiple")
            tdkTestObj.addParameter("paramList", paramList)
            tdkTestObj.executeTestCase(expectedresult)
            actualresult = tdkTestObj.getResult()
            sleep(2)
            step = step + 1
            print(f"\nTEST STEP {step}: Revert SecurityMode to initial SecurityMode")
            print(f"EXPECTED RESULT {step}: Should set SecurityMode to initial SecurityMode")

            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS")
                print(f"ACTUAL RESULT {step}: SecurityMode changed to initial SecurityMode '%s'" % initialSecurityMode)
                print("[TEST EXECUTION RESULT] : SUCCESS")
            else:
                tdkTestObj.setResultStatus("FAILURE")
                print(f"ACTUAL RESULT {step}: Failed to change SecurityMode to initial SecurityMode '%s'" % initialSecurityMode)
                print("[TEST EXECUTION RESULT] : FAILURE")
        else:
            paramList = ("Device.WiFi.AccessPoint.2.Security.ModeEnabled|%s|string|"
                                "Device.WiFi.AccessPoint.2.Security.X_CISCO_COM_EncryptionMethod|%s|string|"
                                "Device.WiFi.AccessPoint.2.Security.RadiusServerIPAddr|%s|string|"
                                "Device.WiFi.AccessPoint.2.Security.RadiusServerPort|%s|unsignedint|"
                                "Device.WiFi.AccessPoint.2.Security.RadiusSecret|%s|string" % (initialSecurityMode,initialencryptionMethod,initialRadiusIP,initialRadiusport,RADIUS_SECRET))
            tdkTestObj = obj.createTestStep("WIFIAgent_SetMultiple")
            tdkTestObj.addParameter("paramList", paramList)
            tdkTestObj.executeTestCase(expectedresult)
            actualresult = tdkTestObj.getResult()
            sleep(2)
            step = step + 1
            print(f"\nTEST STEP {step}: Revert SecurityMode to initial SecurityMode")
            print(f"EXPECTED RESULT {step}: Should set SecurityMode to initial SecurityMode")

            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS")
                print(f"ACTUAL RESULT {step}: SecurityMode changed to initial SecurityMode '%s'" % initialSecurityMode)
                print("[TEST EXECUTION RESULT] : SUCCESS")
            else:
                tdkTestObj.setResultStatus("FAILURE")
                print(f"ACTUAL RESULT {step}: Failed to change SecurityMode to initial SecurityMode '%s'" % initialSecurityMode)
                print("[TEST EXECUTION RESULT] : FAILURE")
    else:
        print("Reverting to prerequisites not required")

    # Unload wifiagent and sysutil module
    obj.unloadModule("wifiagent")
    sysobj.unloadModule("sysutil")
else:
    print("Failed to load wifiagent and sysutil module")
    obj.setLoadModuleStatus("FAILURE")
    sysobj.setLoadModuleStatus("FAILURE")
    print("Module loading failed")
