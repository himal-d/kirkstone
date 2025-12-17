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
  <version>1</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_ONEWIFI_2.4GHZ_WPA-WPA2_RADIUS_WPA_On_Open_Enterprise_Psk_SecurityModeTransition</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>onewifi_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check RADIUS and WPA configurations on security mode transition(None->WPA-WPA2-Enterprise->WPA-WPA2-Personal) for 2.4ghz</synopsis>
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
    <test_case_id>TC_ONEWIFI_255</test_case_id>
    <test_objective>To check whether RADIUS and WPA configuration will be reset or not on security mode transition(None->WPA-WPA2-Enterprise->WPA-WPA2-Personal) for 2.4ghz</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem 2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Device.WiFi.AccessPoint.1.Security.ModeEnabled
    Device.WiFi.AccessPoint.1.Security.X_CISCO_COM_EncryptionMethod
    Device.WiFi.AccessPoint.1.Security.RadiusServerIPAddr
    Device.WiFi.AccessPoint.1.Security.RadiusServerPort
    Device.WiFi.AccessPoint.1.Security.RadiusSecret
    Device.WiFi.AccessPoint.1.Security.PreSharedKey
    Device.WiFi.AccessPoint.1.Security.KeyPassphrase</input_parameters>
    <automation_approch>1. Load the module.
2. Get the security mode using Device.WiFi.AccessPoint.1.Security.ModeEnabled and store it.
3. Change security mode to None using Device.WiFi.AccessPoint.1.Security.ModeEnabled.
4. Check WPA and RADIUS config using Device.WiFi.AccessPoint.1.Security.X_CISCO_COM_EncryptionMethod Device.WiFi.AccessPoint.1.Security.PreSharedKey, Device.WiFi.AccessPoint.1.Security.RadiusServerIPAddr, Device.WiFi.AccessPoint.1.Security.RadiusServerPort and Device.WiFi.AccessPoint.1.Security.RadiusSecret. The values should be empty, empty, 0.0.0.0, 0, empty respectively.
5. Change the security mode to WPA-WPA2-Enterprise ,Encryption method to AES and Radius serverIP, Serverport, RadiusSecret to new values.
6. Check if mode set is reflected in get and if the RADIUS configuration is set to the new values.
7. Now set to the security mode WPA-WPA2-Personal encryption method to AES, Preshared key to new value.
8. Check if security mode set is reflected in get and if the WPA configuration is set to the new values.
9. Revert to initial security mode.
10. unload the module</automation_approch>
    <expected_output>When security mode changes for open to enterprise(None to WPA-WPA2-Enterprise) RADIUS config should set. When security mode changes from enterprise to psk (WPA-WPA2-Enterprise to WPA-WPA2-Personal) RADIUS config should  reset.</expected_output>
    <priority>High</priority>
    <test_stub_interface>WifiAgent</test_stub_interface>
    <test_script>TS_ONEWIFI_2.4GHZ_WPA-WPA2_RADIUS_WPA_On_Open_Enterprise_Psk_SecurityModeTransition</test_script>
    <skipped></skipped>
    <release_version>M129</release_version>
    <remarks></remarks>
  </test_cases>
</xml>
'''
# Import statement
import tdklib
from tdkutility import *
from tdkbVariables import *
from time import sleep

# Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent", "1")
sysobj = tdklib.TDKScriptingLibrary("sysutil", "1")

# IP and Port of box, No need to change,
# This will be replaced with corresponding Box IP and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_ONEWIFI_2.4GHZ_WPA-WPA2_RADIUS_WPA_On_Open_Enterprise_Psk_SecurityModeTransition')
sysobj.configureTestCase(ip,port,'TS_ONEWIFI_2.4GHZ_WPA-WPA2_RADIUS_WPA_On_Open_Enterprise_Psk_SecurityModeTransition')

# Get the result of connection with test component and DUT
loadmodulestatus = obj.getLoadModuleResult()
loadmodulestatus1  = sysobj.getLoadModuleResult()
revertflag = 0
RADIUS_SECRET = "Aa12345678"
PRESHAREDKEY = "Aa12345678"

if "SUCCESS" in loadmodulestatus.upper() and "SUCCESS" in loadmodulestatus1.upper():
    # Set the load module status
    obj.setLoadModuleStatus("SUCCESS")
    sysobj.setLoadModuleStatus("SUCCESS")
    expectedresult = "SUCCESS"

    #Get the Radius and WPA config values from tdk_platform.properties

    config_keys = ["RADIUS_IP", "RADIUS_PORT", "ENCRYPTION_MODE"]
    config_values = {}
    actualresult_all = []
    for key in config_keys:
        command = "sh %s/tdk_utility.sh parseConfigFile %s" % (TDK_PATH, key)
        tdkTestObj, actualresult, config_values[key] = get_config_values(sysobj, command)
        actualresult_all.append(actualresult)
    RADIUS_IP = config_values["RADIUS_IP"]
    RADIUS_PORT = config_values["RADIUS_PORT"]
    ENCRYPTION_MODE = config_values["ENCRYPTION_MODE"]

    print("\nTEST STEP 1: Get the Radius and WPA config info from tdk_platform.properties")
    print("EXPECTED RESULT 1: Should get the radius and wpa config info from tdk_platform.properties")

    if "FAILURE" not in actualresult_all:
        tdkTestObj.setResultStatus("SUCCESS")
        print(f"ACTUAL RESULT 1: RADIUS_IP:{RADIUS_IP}, RADIUS_PORT:{RADIUS_PORT}, RADIUS_SECRET:{RADIUS_SECRET}, ENCRYPTION_METHOD:{ENCRYPTION_MODE}, PRESHAREDKEY:{PRESHAREDKEY}")
        print("[TEST EXECUTION RESULT] : SUCCESS")

        #Get the initial security mode
        paramName = "Device.WiFi.AccessPoint.1.Security.ModeEnabled"
        tdkTestObj,actualresult,initialSecurityMode = wifi_GetParam(obj,paramName)

        print("\nTEST STEP 2: Get the initial security mode")
        print("EXPECTED RESULT 2: Should get the initial security mode")

        if expectedresult in actualresult:
            tdkTestObj.setResultStatus("SUCCESS")
            print("ACTUAL RESULT 2: Initial security mode is %s" % initialSecurityMode)
            print("[TEST EXECUTION RESULT] : SUCCESS")

            if "Personal" in initialSecurityMode:
                #Get the Keypassphrase and encryption method
                paramNames = [
                        "Device.WiFi.AccessPoint.1.Security.KeyPassphrase",
                        "Device.WiFi.AccessPoint.1.Security.X_CISCO_COM_EncryptionMethod"
                        ]
                paramResults = {}
                actualresult_all = []

                for paramName in paramNames:
                    tdkTestObj, actualresult, paramValue = wifi_GetParam(obj, paramName)
                    actualresult_all.append(actualresult)
                    paramResults[paramName] = paramValue

                initialKeypassphrase = paramResults["Device.WiFi.AccessPoint.1.Security.KeyPassphrase"]
                initialencryptionMethod = paramResults["Device.WiFi.AccessPoint.1.Security.X_CISCO_COM_EncryptionMethod"]

                print("\nTEST STEP 3: Get the initial Keypassphrase and encryption method")
                print("EXPECTED RESULT 3: Should get the initial Keypassphrase and encryption method")

                if "FAILURE" not in actualresult_all:
                    tdkTestObj.setResultStatus("SUCCESS")
                    print(f"ACTUAL RESULT 3 Initial keypassphrase is {initialKeypassphrase} and initial encryption method is {initialencryptionMethod} ")
                    print("[TEST EXECUTION RESULT] : SUCCESS")
                else:
                    tdkTestObj.setResultStatus("FAILURE")
                    print("ACTUAL RESULT 3: Failed to get initial Keypassphrase and encryption method")
                    print("[TEST EXECUTION RESULT] : FAILURE")
            else:
                #Get Radius config and encryption mode
                paramNames = [
                        "Device.WiFi.AccessPoint.1.Security.RadiusServerIPAddr",
                        "Device.WiFi.AccessPoint.1.Security.RadiusServerPort",
                        "Device.WiFi.AccessPoint.1.Security.X_CISCO_COM_EncryptionMethod"
                        ]
                paramResults = {}
                actualresult_all = []

                for paramName in paramNames:
                    tdkTestObj, actualresult, paramValue = wifi_GetParam(obj, paramName)
                    actualresult_all.append(actualresult)
                    paramResults[paramName] = paramValue

                initialRadiusIP = paramResults["Device.WiFi.AccessPoint.1.Security.RadiusServerIPAddr"]
                initialRadiusport = paramResults["Device.WiFi.AccessPoint.1.Security.RadiusServerPort"]
                initialencryptionMethod = paramResults["Device.WiFi.AccessPoint.1.Security.X_CISCO_COM_EncryptionMethod"]

                print("\nTEST STEP 3: Get the initial radius config and encryption method")
                print("EXPECTED RESULT 3: Should get the initial radius config and encryption method")

                if "FAILURE" not in actualresult_all:
                    tdkTestObj.setResultStatus("SUCCESS")
                    print(f"ACTUAL RESULT 3 Initial radiusIP is {initialRadiusIP} , initial radius port is {initialRadiusport} and initial encryption method is {initialencryptionMethod} ")
                    print("[TEST EXECUTION RESULT] : SUCCESS")
                else:
                    tdkTestObj.setResultStatus("FAILURE")
                    print("ACTUAL RESULT 3: Failed to get initial radius config and encryption method")
                    print("[TEST EXECUTION RESULT] : FAILURE")

            #Change security mode to None
            paramName = "Device.WiFi.AccessPoint.1.Security.ModeEnabled"
            tdkTestObj, actualresult = wifi_SetParam(obj,paramName,"None","string")
            sleep(2)

            print("\nTEST STEP 4: Change security mode to None")
            print("EXPECTED RESULT 4: Should change security mode to None")

            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS")
                revertflag = 1
                print("ACTUAL RESULT 4: Security mode changed to None")
                print("[TEST EXECUTION RESULT] : SUCCESS")

                #Check SecurityMode RADIUS and WPA config

                paramList_config = ["Device.WiFi.AccessPoint.1.Security.ModeEnabled",
                                    "Device.WiFi.AccessPoint.1.Security.X_CISCO_COM_EncryptionMethod",
                                    "Device.WiFi.AccessPoint.1.Security.RadiusServerIPAddr",
                                    "Device.WiFi.AccessPoint.1.Security.RadiusServerPort",
                                    "Device.WiFi.AccessPoint.1.Security.RadiusSecret",
                                    "Device.WiFi.AccessPoint.1.Security.PreSharedKey",
                                    "Device.WiFi.AccessPoint.1.Security.KeyPassphrase"
                                    ]
                expected_values = ["None", "", "0.0.0.0", "0", "","","0.0"]
                actual_values = []
                actualresult_all = []

                for param in paramList_config:
                    tdkTestObj, actualresult, value = wifi_GetParam(obj, param)
                    actualresult_all.append(actualresult)
                    actual_values.append(value)

                print("\nTEST STEP 5: Check security mode RADIUS and WPA configuration")
                print("EXPECTED RESULT 5: RADIUS and WPA configuration values should be reset when security mode is None")

                if "FAILURE" not in actualresult_all and expected_values == actual_values:
                    tdkTestObj.setResultStatus("SUCCESS")
                    print("ACTUAL RESULT 5: SecurityMode is '%s',Encryption Mode is ' %s', PresharedKey is ' %s', KeyPasspharse is ' %s', RADIUS IP is ' %s', RADIUS ServerPort is ' %s', RADIUS Secret is ' %s'" % (actual_values[0],actual_values[1],actual_values[5],actual_values[6],actual_values[2],actual_values[3],actual_values[4]))
                    print("[TEST EXECUTION RESULT] : SUCCESS")

                    #Change security mode to WPA-WPA2-Enterprise, Encryption mode to AES and radius config parameters to new values

                    tdkTestObj = obj.createTestStep("WIFIAgent_SetMultiple")
                    paramList = ("Device.WiFi.AccessPoint.1.Security.ModeEnabled|WPA-WPA2-Enterprise|string|"
                                "Device.WiFi.AccessPoint.1.Security.X_CISCO_COM_EncryptionMethod|%s|string|"
                                "Device.WiFi.AccessPoint.1.Security.RadiusServerIPAddr|%s|string|"
                                "Device.WiFi.AccessPoint.1.Security.RadiusServerPort|%s|unsignedint|"
                                "Device.WiFi.AccessPoint.1.Security.RadiusSecret|%s|string" % (ENCRYPTION_MODE,RADIUS_IP,RADIUS_PORT,RADIUS_SECRET))
                    tdkTestObj.addParameter("paramList", paramList)
                    tdkTestObj.executeTestCase(expectedresult)
                    actualresult = tdkTestObj.getResult()
                    sleep(2)

                    print("TEST STEP 6: Set security mode to WPA-WPA2-Enterprise and RADIUS configuration to new values")
                    print(f"EXPECTED RESULT 6: Should set security mode to WPA-WPA2-Enterprise Encryption mode to {ENCRYPTION_MODE}, RADIUSserverIP to {RADIUS_IP}, RADIUSserverPort to {RADIUS_PORT} and RADIUSsecret to {RADIUS_SECRET}")

                    if expectedresult in actualresult:
                        tdkTestObj.setResultStatus("SUCCESS")
                        print("ACTUAL RESULT 6: Security mode set to WPA-WPA2-Enterprise and RADIUS configuration with new values")
                        print("[TEST EXECUTION RESULT] : SUCCESS")

                        #Check SecurityMode and RADIUS Config

                        paramList_config = ["Device.WiFi.AccessPoint.1.Security.ModeEnabled",
                                    "Device.WiFi.AccessPoint.1.Security.X_CISCO_COM_EncryptionMethod",
                                    "Device.WiFi.AccessPoint.1.Security.RadiusServerIPAddr",
                                    "Device.WiFi.AccessPoint.1.Security.RadiusServerPort",
                                    "Device.WiFi.AccessPoint.1.Security.RadiusSecret",
                                    ]
                        expected_values = ["WPA-WPA2-Enterprise", ENCRYPTION_MODE, RADIUS_IP, RADIUS_PORT, ""]
                        actual_values = []
                        actualresult_all = []

                        for param in paramList_config:
                            tdkTestObj, actualresult, value = wifi_GetParam(obj, param)
                            actualresult_all.append(actualresult)
                            actual_values.append(value)

                        print("TEST STEP 7: Check security mode and RADIUS configuration Values")
                        print("EXPECTED RESULT 7: Security mode should be WPA-WPA2-Enterprise, RADIUS config parameters with new values")

                        if "FAILURE" not in actualresult_all and actual_values == expected_values:
                            tdkTestObj.setResultStatus("SUCCESS")
                            print("ACTUAL RESULT 7: Security mode is '%s',  Encryption method is ' %s', RADIUS IP is ' %s', RADIUS ServerPort is ' %s', RADIUSSecret is ' %s'" % (actual_values[0],actual_values[1],actual_values[2],actual_values[3],actual_values[4]))
                            print("[TEST EXECUTION RESULT] : SUCCESS")

                            #Set security mode to WPA-WPA2-Personal and WPA config parameters to new values

                            tdkTestObj = obj.createTestStep("WIFIAgent_SetMultiple")
                            paramList = ("Device.WiFi.AccessPoint.1.Security.ModeEnabled|WPA-WPA2-Personal|string|"
                                "Device.WiFi.AccessPoint.1.Security.X_CISCO_COM_EncryptionMethod|%s|string|"
                                "Device.WiFi.AccessPoint.1.Security.PreSharedKey|Aa12345678|string" % (ENCRYPTION_MODE))
                            tdkTestObj.addParameter("paramList", paramList)
                            tdkTestObj.executeTestCase(expectedresult)
                            actualresult = tdkTestObj.getResult()
                            sleep(2)
                            print("TEST STEP 8: Set security mode to WPA-WPA2-Personal and WPA configuration to new values")
                            print(f"EXPECTED RESULT 8: Should set security mode to WPA-WPA2-Personal Encryption mode to {ENCRYPTION_MODE}  and PreSharedKey to'Aa12345678'")

                            if expectedresult in actualresult:
                                tdkTestObj.setResultStatus("SUCCESS")
                                print("ACTUAL RESULT 8: Security mode set to WPA-WPA2-Personal and WPA configuration with new values")
                                print("[TEST EXECUTION RESULT] : SUCCESS")

                                #Check SecurityMode and WPA Config

                                paramList_config = ["Device.WiFi.AccessPoint.1.Security.ModeEnabled",
                                    "Device.WiFi.AccessPoint.1.Security.X_CISCO_COM_EncryptionMethod",
                                    "Device.WiFi.AccessPoint.1.Security.PreSharedKey",
                                    "Device.WiFi.AccessPoint.1.Security.KeyPassphrase"
                                    ]
                                expected_values = ["WPA-WPA2-Personal", ENCRYPTION_MODE, "", "Aa12345678"]
                                actual_values = []
                                actualresult_all = []

                                for param in paramList_config:
                                    tdkTestObj, actualresult, value = wifi_GetParam(obj, param)
                                    actualresult_all.append(actualresult)
                                    actual_values.append(value)

                                print("TEST STEP 9: Check SecurityMode and WPA Config Paremeters")
                                print("EXPECTED RESULT 9: Security mode should be WPA-WPA2-Personal, WPA config parameters with new values")

                                if "FAILURE" not in actualresult_all and actual_values == expected_values:
                                    tdkTestObj.setResultStatus("SUCCESS")
                                    print("ACTUAL RESULT 9: Security mode is '%s',  Encryption method is ' %s', PreSharedKey is ' %s', KeyPassphrase is ' %s'" % (actual_values[0],actual_values[1],actual_values[2],actual_values[3]))
                                    print("[TEST EXECUTION RESULT] : SUCCESS")
                                else:
                                    tdkTestObj.setResultStatus("FAILURE")
                                    print("ACTUAL RESULT 9: Security mode is '%s',  Encryption method is ' %s', PreSharedKey is ' %s', KeyPassphrase is ' %s'" % (actual_values[0],actual_values[1],actual_values[2],actual_values[3]))
                                    print("[TEST EXECUTION RESULT] : FAILURE")
                            else:
                                tdkTestObj.setResultStatus("FAILURE")
                                print("ACTUAL RESULT 8: Security mode set to WPA-WPA2-Personal and WPA configuration with new values")
                                print("[TEST EXECUTION RESULT] : FAILURE")
                        else:
                            tdkTestObj.setResultStatus("FAILURE")
                            print("ACTUAL RESULT 7: Security mode is '%s',  Encryption method is ' %s', RADIUS IP is ' %s', RADIUS ServerPort is ' %s', RADIUSSecret is ' %s'" % (actual_values[0],actual_values[1],actual_values[2],actual_values[3],actual_values[4]))
                            print("[TEST EXECUTION RESULT] : FAILURE")
                    else:
                        tdkTestObj.setResultStatus("FAILURE")
                        print("ACTUAL RESULT 6: Security mode set to WPA-WPA2-Enterprise and RADIUS configuration with new values")
                        print("[TEST EXECUTION RESULT] : FAILURE")
                else:
                    tdkTestObj.setResultStatus("FAILURE")
                    print("ACTUAL RESULT 5: SecurityMode is '%s',Encryption Mode is ' %s', PresharedKey is ' %s', KeyPasspharse is ' %s', RADIUS IP is ' %s', RADIUS ServerPort is ' %s', RADIUS Secret is ' %s'" % (actual_values[0],actual_values[1],actual_values[5],actual_values[6],actual_values[2],actual_values[3],actual_values[4]))
                    print("[TEST EXECUTION RESULT] : FAILURE")
            else:
                tdkTestObj.setResultStatus("FAILURE")
                print("ACTUAL RESULT 4: Failed to change security mode to None")
                print("[TEST EXECUTION RESULT] : FAILURE")
        else:
            tdkTestObj.setResultStatus("FAILURE")
            print("ACTUAL RESULT 2: Failed to get the initial security mode")
            print("[TEST EXECUTION RESULT] : FAILURE")
    else:
        tdkTestObj.setResultStatus("FAILURE")
        print("ACTUAL RESULT 1: Failed to get the radius and wpa config info from tdk_platform.properties")
        print("[TEST EXECUTION RESULT] : FAILURE")

    if revertflag == 1:
        #Revert to initial SecurityMode
        if "Personal" in initialSecurityMode:
            paramList = ("Device.WiFi.AccessPoint.1.Security.ModeEnabled|%s|string|Device.WiFi.AccessPoint.1.Security.X_CISCO_COM_EncryptionMethod|%s|string|Device.WiFi.AccessPoint.1.Security.PreSharedKey|%s|string" %(initialSecurityMode,initialencryptionMethod,initialKeypassphrase))
            tdkTestObj = obj.createTestStep("WIFIAgent_SetMultiple")
            tdkTestObj.addParameter("paramList", paramList)
            tdkTestObj.executeTestCase(expectedresult)
            actualresult = tdkTestObj.getResult()
            sleep(2)
            print("\nTEST STEP 10: Revert SecurityMode to initial SecurityMode")
            print("EXPECTED RESULT 10: Should set SecurityMode to initial SecurityMode")

            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS")
                print("ACTUAL RESULT 10: SecurityMode changed to initial SecurityMode '%s'" % initialSecurityMode)
                print("[TEST EXECUTION RESULT] : SUCCESS")
            else:
                tdkTestObj.setResultStatus("FAILURE")
                print("ACTUAL RESULT 10: Failed to change SecurityMode to initial SecurityMode '%s'" % initialSecurityMode)
                print("[TEST EXECUTION RESULT] : FAILURE")
        else:
            paramList = ("Device.WiFi.AccessPoint.1.Security.ModeEnabled|%s|string|"
                                "Device.WiFi.AccessPoint.1.Security.X_CISCO_COM_EncryptionMethod|%s|string|"
                                "Device.WiFi.AccessPoint.1.Security.RadiusServerIPAddr|%s|string|"
                                "Device.WiFi.AccessPoint.1.Security.RadiusServerPort|%s|unsignedint|"
                                "Device.WiFi.AccessPoint.1.Security.RadiusSecret|%s|string" % (initialSecurityMode,initialencryptionMethod,initialRadiusIP,initialRadiusport,RADIUS_SECRET))
            tdkTestObj = obj.createTestStep("WIFIAgent_SetMultiple")
            tdkTestObj.addParameter("paramList", paramList)
            tdkTestObj.executeTestCase(expectedresult)
            actualresult = tdkTestObj.getResult()
            sleep(2)
            print("\nTEST STEP 10: Revert SecurityMode to initial SecurityMode")
            print("EXPECTED RESULT 10: Should set SecurityMode to initial SecurityMode")

            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS")
                print("ACTUAL RESULT 10: SecurityMode changed to initial SecurityMode '%s'" % initialSecurityMode)
                print("[TEST EXECUTION RESULT] : SUCCESS")
            else:
                tdkTestObj.setResultStatus("FAILURE")
                print("ACTUAL RESULT 10: Failed to change SecurityMode to initial SecurityMode '%s'" % initialSecurityMode)
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
