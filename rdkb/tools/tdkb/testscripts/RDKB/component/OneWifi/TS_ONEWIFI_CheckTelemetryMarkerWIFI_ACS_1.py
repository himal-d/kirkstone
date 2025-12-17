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
  <version>28</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_ONEWIFI_CheckTelemetryMarkerWIFI_ACS_1</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>onewifi_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To check WIFI_ACS_1 is populating correctly in wifihealth.txt</synopsis>
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
    <test_case_id>TC_ONEWIFI_249</test_case_id>
    <test_objective>To check WIFI_ACS_1 is populated correctly in wifihealth.txt</test_objective>
    <test_type></test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem 2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used></api_or_interface_used>
    <input_parameters>Device.WiFi.Radio.1.AutoChannelEnable
    Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.Telemetry.Enable
    Device.DeviceInfo.X_RDKCENTRAL-COM_WIFI_TELEMETRY.LogInterval</input_parameters>
    <automation_approch>1.Load the module.
2.Get the AutoChannelEnable by using Device.WiFi.Radio.1.AutoChannelEnable and store it
3.Check if telemetry markers are enabled ,if not enable using Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.Telemetry.Enable
4.Change the log interval to 300 sec i,e 5min using Device.DeviceInfo.X_RDKCENTRAL-COM_WIFI_TELEMETRY.LogInterval
5.Check if the log file wifihealth.txt is present under /rdklogs/logs.
6.Check if WIFI_ACS_1 is present in wifihealth.txt. If not found, check every 60s for 15 minutes to see if the log is getting populated.
7.Retrive the value of WIFI_ACS_1.
8.Compare the initially retrived AutoChannelEnable with WIFI_ACS_1.
9.Unload the module.
</automation_approch>
    <expected_output>WIFI_ACS_1 should populate in wifihealth.txt and should match with AutoChannelEnable</expected_output>
    <priority></priority>
    <test_stub_interface>WifiAgent</test_stub_interface>
    <test_script>TS_ONEWIFI_CheckTelemetryMarkerWIFI_ACS_1</test_script>
    <skipped></skipped>
    <release_version>M129</release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''

# Import statements
import tdklib
from tdkutility import *
from time import sleep

# Test component to be tested
wifiobj = tdklib.TDKScriptingLibrary("wifiagent", "1")
pamobj = tdklib.TDKScriptingLibrary("pam","1")
sysObj = tdklib.TDKScriptingLibrary("sysutil","1")

# IP and Port of box, No need to change,
# This will be replaced with corresponding Box IP and port while executing script
ip = <ipaddress>
port = <port>
wifiobj.configureTestCase(ip,port,'TS_ONEWIFI_CheckTelemetryMarkerWIFI_ACS_1')
pamobj.configureTestCase(ip,port,'TS_ONEWIFI_CheckTelemetryMarkerWIFI_ACS_1')
sysObj.configureTestCase(ip,port,'TS_ONEWIFI_CheckTelemetryMarkerWIFI_ACS_1')

#Get the result of connection with test component and DUT
wifiloadmodulestatus=wifiobj.getLoadModuleResult()
pamloadmodulestatus=pamobj.getLoadModuleResult()
sysutilloadmodulestatus=sysObj.getLoadModuleResult()

step = 0
flag = 0
revertflag = 0

if "SUCCESS" in wifiloadmodulestatus.upper() and "SUCCESS" in pamloadmodulestatus.upper() and "SUCCESS" in sysutilloadmodulestatus.upper():
    wifiobj.setLoadModuleStatus("SUCCESS")
    pamobj.setLoadModuleStatus("SUCCESS")
    sysObj.setLoadModuleStatus("SUCCESS")
    expectedresult = "SUCCESS"

    #Get the value of AutoChannelEnable and store it
    paramName = "Device.WiFi.Radio.1.AutoChannelEnable"
    tdkTestObj,actualresult,initial_AutoChannel = wifi_GetParam(wifiobj,paramName)
    step = step + 1
    print("TEST STEP %s: Get the AutoChannelEnable" % step)
    print("EXPECTED RESULT %s: Should get AutoChannelEnable" % step)

    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS")
        print("ACTUAL RESULT %s: AutoChannelEnable is %s " % (step,initial_AutoChannel))
        print("[TEST EXECUTION RESULT] : SUCCESS")

        #Get TelementryEnable
        tdkTestObj = pamobj.createTestStep('pam_GetParameterValues')
        tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.Telemetry.Enable")
        tdkTestObj.executeTestCase(expectedresult)
        actualresult = tdkTestObj.getResult()
        initial_TelemetrylogEnable  = tdkTestObj.getResultDetails()

        print("TEST STEP %s: Get the TelemetryEnable" % step)
        print("EXPECTED RESULT %s: Should get TelementryEnable" % step)
        step = step + 1

        if expectedresult in actualresult:
            flag = 1
            tdkTestObj.setResultStatus("SUCCESS")
            print("ACTUAL RESULT %s: TelementryEnable is %s " % (step,initial_TelemetrylogEnable))
            print("[TEST EXECUTION RESULT] : SUCCESS")

            #if TelemetryEnable is false enable it
            if initial_TelemetrylogEnable == "false":
                tdkTestObj = pamobj.createTestStep('pam_SetParameterValues')
                tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.Telemetry.Enable")
                tdkTestObj.addParameter("ParamValue","true")
                tdkTestObj.addParameter("Type","bool")
                tdkTestObj.executeTestCase(expectedresult)
                actualresult = tdkTestObj.getResult()

                print("TEST STEP %s: Set the TelemetryEnable to true" % step)
                print("EXPECTED RESULT %s: Should set the TelemetryEnable to true" % step)
                step = step + 1
                if expectedresult in actualresult:
                    flag = 1
                    revertflag = 1
                    tdkTestObj.setResultStatus("SUCCESS")
                    print("ACTUAL RESULT %s: TelemetryEnable changed successfully" % step)
                    print("[TEST EXECUTION RESULT] : SUCCESS")

                    #verfy TelementryEnable with GET
                    tdkTestObj = pamobj.createTestStep('pam_GetParameterValues')
                    tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.Telemetry.Enable")
                    tdkTestObj.executeTestCase(expectedresult)
                    actualresult = tdkTestObj.getResult()
                    TelemetrylogEnable = tdkTestObj.getResultDetails()

                    print("TEST STEP %s: Get the TelemetryEnable" % step)
                    print("EXPECTED RESULT %s: Should get TelementryEnable" % step)
                    step = step + 1

                    if expectedresult in actualresult:
                        tdkTestObj.setResultStatus("SUCCESS")
                        print("ACTUAL RESULT %s: TelementryEnable is %s " % (step,TelemetrylogEnable))
                        print("[TEST EXECUTION RESULT] : SUCCESS")
                    else:
                        tdkTestObj.setResultStatus("FAILURE")
                        print("ACTUAL RESULT %s:Failed to get TelementryEnable" % step)
                        print("[TEST EXECUTION RESULT] : FAILURE")
                else:
                    flag = 0
                    revertflag = 0
                    tdkTestObj.setResultStatus("FAILURE")
                    print("ACTUAL RESULT %s: Failed to set TelemetryEnable" % step)
                    print("[TEST EXECUTION RESULT] : FAILURE")

            #Set the loginterval to 300 seconds if Telemetry enable is true
            if flag == 1:
                #get loginterval and store it
                tdkTestObj = pamobj.createTestStep('pam_GetParameterValues')
                tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_WIFI_TELEMETRY.LogInterval")
                tdkTestObj.executeTestCase(expectedresult)
                actualresult = tdkTestObj.getResult()
                TelemetrylogInterval = tdkTestObj.getResultDetails()

                print("TEST STEP %s: Get the Telemetry LogInterval and store it" % step)
                print("EXPECTED RESULT %s: Should get the Telemetry LogInterval" % step)
                step = step+1

                if expectedresult in actualresult:
                    tdkTestObj.setResultStatus("SUCCESS")
                    print("ACTUAL RESULT %s: Telemetry LogInterval get successfull" % step)
                    print("[TEST EXECUTION RESULT] : SUCCESS")

                    tdkTestObj = pamobj.createTestStep('pam_SetParameterValues')
                    tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_WIFI_TELEMETRY.LogInterval")
                    tdkTestObj.addParameter("ParamValue","300")
                    tdkTestObj.addParameter("Type","int")
                    tdkTestObj.executeTestCase(expectedresult)
                    actualresult = tdkTestObj.getResult()

                    print("TEST STEP %s: Set the Telemetry LogInterval to 5 min" % step)
                    print("EXPECTED RESULT %s: Should set the Telemetry LogInterval to 5 min" % step)

                    step = step + 1
                    if expectedresult in actualresult:
                        tdkTestObj.setResultStatus("SUCCESS")
                        print("ACTUAL RESULT %s: Telemetry LogInterval set to 5 min" % step)
                        print("[TEST EXECUTION RESULT] : SUCCESS")

                        #Get the loginterval and verify
                        tdkTestObj = pamobj.createTestStep('pam_GetParameterValues')
                        tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_WIFI_TELEMETRY.LogInterval")
                        expectedresult="SUCCESS"
                        tdkTestObj.executeTestCase(expectedresult)
                        actualresult = tdkTestObj.getResult()
                        loginterval = tdkTestObj.getResultDetails()

                        print("TEST STEP %s: Get the Telemetry LogInterval" % step)
                        print("EXPECTED RESULT %s: Should get the Telemetry LogInterval" % step)
                        step = step + 1

                        if expectedresult in actualresult:
                            tdkTestObj.setResultStatus("SUCCESS")
                            print("ACTUAL RESULT %s: Telemetry LogInterval: %s" % (step,loginterval))
                            print("[TEST EXECUTION RESULT] : SUCCESS")

                            #Check whether the wifihealth.txt file is present or not
                            tdkTestObj = sysObj.createTestStep('ExecuteCmd')
                            cmd = "[ -f /rdklogs/logs/wifihealth.txt ] && echo \"File exist\" || echo \"File does not exist\""
                            tdkTestObj.addParameter("command",cmd)
                            expectedresult="SUCCESS"
                            tdkTestObj.executeTestCase(expectedresult)
                            actualresult = tdkTestObj.getResult()
                            details = tdkTestObj.getResultDetails().strip().replace("\\n", "")
                            print("TEST STEP %s: Check for wifihealth log file presence" % step)
                            print("EXPECTED RESULT %s:wifihealth log file should be present" % step)
                            step = step + 1

                            if details == "File exist":
                                tdkTestObj.setResultStatus("SUCCESS")
                                print("ACTUAL RESULT %s: wifihealth log file is present" % step)
                                print("[TEST EXECUTION RESULT] : SUCCESS")

                                #Check for the maraker WIFI_ACS_1
                                step = step + 1
                                tdkTestObj = sysObj.createTestStep('ExecuteCmd')
                                cmd = "grep -ire \"WIFI_ACS_1\" /rdklogs/logs/wifihealth.txt"
                                tdkTestObj.addParameter("command",cmd)
                                expectedresult="SUCCESS"

                                print("\nTEST STEP %s: Check for the presence of the marker WIFI_ACS_1 in wifihealth.txt" % step)
                                print("EXPECTED RESULT %s: WIFI_ACS_1 marker should be present in wifihealth.txt" % step)

                                markerfound = 0
                                #Giving 5 iterations of 60s each as the  value of Log Interval is 300s
                                for iteration in range(1,6):
                                    print("Waiting for the marker to get populated in wifihealth.txt....\nIteration : %s" % iteration)
                                    tdkTestObj.executeTestCase(expectedresult)
                                    actualresult = tdkTestObj.getResult()
                                    details = tdkTestObj.getResultDetails().strip().replace("\\n", "")

                                    if expectedresult in actualresult and "WIFI_ACS_1" in details:
                                        markerfound = 1
                                        break
                                    else:
                                        sleep(60)
                                        continue

                                if markerfound == 1:
                                    tdkTestObj.setResultStatus("SUCCESS")
                                    print("ACTUAL RESULT %s: WIFI_ACS_1 marker is found in wifihealth.txt : %s" %(step,details))
                                    print("[TEST EXECUTION RESULT] : SUCCESS")

                                    # Retrieve the value of WIFI_ACS_1
                                    step += 1
                                    tdkTestObj = sysObj.createTestStep('ExecuteCmd')
                                    cmd = "grep -inr 'WIFI_ACS_1' /rdklogs/logs/wifihealth.txt | tail -1 | awk -F 'WIFI_ACS_1:' '{print $2}' | awk '{print $1}'"
                                    tdkTestObj.addParameter("command", cmd)

                                    print("\nTEST STEP %s: Retrieve the value of WIFI_ACS_1" % step)
                                    print("EXPECTED RESULT %s: The value of WIFI_ACS_1 should be retrieved" % step)

                                    tdkTestObj.executeTestCase(expectedresult)
                                    actualresult = tdkTestObj.getResult()
                                    details = tdkTestObj.getResultDetails().strip().replace("\\n", "")

                                    if expectedresult in actualresult and details:
                                        tdkTestObj.setResultStatus("SUCCESS")
                                        print("ACTUAL RESULT %s: Retrieved the value of WIFI_ACS_1: %s" % (step, details))
                                        print("[TEST EXECUTION RESULT] : SUCCESS")

                                        #compare WIFI_ACS_1 with AutochannelEnable
                                        step = step + 1
                                        print("\nTEST STEP %s: Compare WIFI_ACS_1 with initially retrived AutochannelEnable" % step)
                                        print("EXPECTED RESULT %s: WIFI_ACS_1 and initially retrived AutochannelEnable should has same value" % step)

                                        if details == initial_AutoChannel:
                                            tdkTestObj.setResultStatus("SUCCESS")
                                            print("The value of AutoChannelEnable is %s" % initial_AutoChannel)
                                            print("The value of WIFI_ACS_1 in wifihealth.txt is %s" % details)
                                            print("ACTUAL RESULT %s: WIFI_ACS_1 and AutoChannelEnable is same" % step)
                                            print("[TEST EXECUTION RESULT] : SUCCESS")
                                        else:
                                            tdkTestObj.setResultStatus("FAILURE")
                                            print("The value of initial AutoChannelEnable is %s" % initial_AutoChannel)
                                            print("The value of WIFI_ACS_1 in wifihealth.txt is %s" % details)
                                            print("ACTUAL RESULT %s: WIFI_ACS_1 and AutoChannelEnable is not same" % step)
                                            print("[TEST EXECUTION RESULT] : FAILURE")
                                    else:
                                        tdkTestObj.setResultStatus("FAILURE")
                                        print("ACTUAL RESULT %s: Failed to retrieve the value of WIFI_ACS_1" % step)
                                        print("[TEST EXECUTION RESULT] : FAILURE")
                                else:
                                    tdkTestObj.setResultStatus("FAILURE")
                                    print("ACTUAL RESULT %d: WIFI_ACS_1 marker is not found Details : %s" %(step,details))
                                    print("[TEST EXECUTION RESULT] : FAILURE")
                            else:
                                tdkTestObj.setResultStatus("FAILURE")
                                print("ACTUAL RESULT %s:wifihealth log file is not present" % step)
                                print("[TEST EXECUTION RESULT] : FAILURE")
                            #Revert the LogInterval
                            tdkTestObj = pamobj.createTestStep('pam_SetParameterValues')
                            tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_WIFI_TELEMETRY.LogInterval")
                            tdkTestObj.addParameter("ParamValue",TelemetrylogInterval)
                            tdkTestObj.addParameter("Type","int")
                            tdkTestObj.executeTestCase(expectedresult)
                            actualresult = tdkTestObj.getResult()
                            step = step + 1
                            print("TEST STEP %s: Change the LogInterval to initial value" % step)
                            print("EXPECTED RESULT %s: Should change value of LogInterval to initial value" % step)

                            if expectedresult in actualresult:
                                tdkTestObj.setResultStatus("SUCCESS")
                                print("ACTUAL RESULT %s: LogInterval changed to initial value successfully " % (step))
                                print("[TEST EXECUTION RESULT] : SUCCESS")
                            else:
                                tdkTestObj.setResultStatus("FAILURE")
                                print("ACTUAL RESULT %s: Failed to change LogInterval changed to initial value" % (step))
                                print("[TEST EXECUTION RESULT] : FAILURE")
                        else:
                            tdkTestObj.setResultStatus("FAILURE")
                            print("ACTUAL RESULT %s: Failed to get Telemetry LogInterval" % step)
                            print("[TEST EXECUTION RESULT] : FAILURE")
                    else:
                        tdkTestObj.setResultStatus("FAILURE")
                        print("ACTUAL RESULT %s: Failed to set Telemetry LogInterval" % step)
                        print("[TEST EXECUTION RESULT] : FAILURE")
                else:
                    tdkTestObj.setResultStatus("FAILURE")
                    print("ACTUAL RESULT %s: Failed to get Telemetry LogInterval" % step)
                    print("[TEST EXECUTION RESULT] : FAILURE")
                #Revert TelemetryEnable
                if revertflag == 1:
                    tdkTestObj = pamobj.createTestStep('pam_SetParameterValues')
                    tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.Telemetry.Enable")
                    tdkTestObj.addParameter("ParamValue",initial_TelemetrylogEnable)
                    tdkTestObj.addParameter("Type","bool")
                    tdkTestObj.executeTestCase(expectedresult)
                    actualresult = tdkTestObj.getResult()
                    step = step + 1
                    print("TEST STEP %s: Change the TelemetryEnable to initial value" % step)
                    print("EXPECTED RESULT %s: Should change value of TelemetryEnable to initial value" % step)

                    if expectedresult in actualresult:
                        tdkTestObj.setResultStatus("SUCCESS")
                        print("ACTUAL RESULT %s: TelemetryEnable changed to initial value successfully " % (step))
                        print("[TEST EXECUTION RESULT] : SUCCESS")
                    else:
                        tdkTestObj.setResultStatus("FAILURE")
                        print("ACTUAL RESULT %s: Failed to change TelemetryEnable changed to initial value" % (step))
                        print("[TEST EXECUTION RESULT] : FAILURE")
            else:
                tdkTestObj.setResultStatus("FAILURE")
                print(" Telemetry logger was disbled and failed on enabling")
                print("[TEST EXECUTION RESULT] :FAILURE")
        else:
            tdkTestObj.setResultStatus("FAILURE")
            print("ACTUAL RESULT %s:Failed to get TelementryEnable" % step)
            print("[TEST EXECUTION RESULT] : FAILURE")
    else:
        tdkTestObj.setResultStatus("FAILURE")
        print("ACTUAL RESULT %s: Failed to get AutoChannelEnable" % step)
        print("[TEST EXECUTION RESULT] : FAILURE")

    wifiobj.unloadModule("wifiagent")
    pamobj.unloadModule("pam")
    sysObj.unloadModule("sysutil")
else:
    print("Failed to load wifi/pam/sysutil module")
    wifiobj.setLoadModuleStatus("FAILURE")
    pamobj.setLoadModuleStatus("FAILURE")
    sysObj.setLoadModuleStatus("FAILURE")
    print("Module loading failed")
