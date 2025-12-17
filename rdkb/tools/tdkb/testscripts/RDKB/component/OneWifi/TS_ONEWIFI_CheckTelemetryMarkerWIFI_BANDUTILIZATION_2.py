##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2021 RDK Management
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
<?xml version="1.0" encoding="UTF-8"?><xml>
  <id/>
  <version>2</version>
  <name>TS_ONEWIFI_CheckTelemetryMarkerWIFI_BANDUTILIZATION_2</name>
  <primitive_test_id/>
  <primitive_test_name>onewifi_DoNothing</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>Check if WIFI_BANDUTILIZATION_2 is populated in wifihealth.txt</synopsis>
  <groups_id/>
  <execution_time>20</execution_time>
  <long_duration>false</long_duration>
  <advanced_script>false</advanced_script>
  <remarks/>
  <skip>false</skip>
  <box_types>
    <box_type>Broadband</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_ONEWIFI_246</test_case_id>
    <test_objective>Check if WIFI_BANDUTILIZATION_2 is populated in wifihealth.txt</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>None</input_parameters>
    <automation_approch>1. Load the modules
2.Check if telemetry markers are enabled ,if not enable using Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.Telemetry.Enable
3.Change the log interval to 300 sec i,e 5min using Device.DeviceInfo.X_RDKCENTRAL-COM_WIFI_TELEMETRY.LogInterval
4.Check if the log file wifihealth.txt is present under /rdklogs/logs.
5.Check if the WIFI_BANDUTILIZATION_2 is present in wifihealth.txt. If not found, check every 60s for 5 minutes to see if the log is getting populated.
6.Retrive the value of WIFI_BANDUTILIZATION_2
7. Revert the TELEMETRY LogInterval to previous
8. Revert the Telemetry Enable status to previous
9. Unload the modules.</automation_approch>
    <expected_output>The WIFI_BANDUTILIZATION_2 marker should present in wifihealth.txt</expected_output>
    <priority>High</priority>
    <test_stub_interface>wifiagent</test_stub_interface>
    <test_script>TS_ONEWIFI_CheckTelemetryMarkerWIFI_BANDUTILIZATION_2</test_script>
    <skipped>No</skipped>
    <release_version>M129</release_version>
    <remarks/>
  </test_cases>
  <script_tags/>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
from  time import sleep;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("pam","RDKB");
sysObj = tdklib.TDKScriptingLibrary("sysutil","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with corresponding DUT Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_ONEWIFI_CheckTelemetryMarkerWIFI_BANDUTILIZATION_2');
sysObj.configureTestCase(ip,port,'TS_ONEWIFI_CheckTelemetryMarkerWIFI_BANDUTILIZATION_2');

#Get the result of connection with test component and DUT
loadmodulestatus=obj.getLoadModuleResult();
sysutilloadmodulestatus=sysObj.getLoadModuleResult();
revertflag = 0;
flag =1;
if "SUCCESS" in loadmodulestatus.upper() and "SUCCESS" in sysutilloadmodulestatus.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    sysObj.setLoadModuleStatus("SUCCESS");

    tdkTestObj = obj.createTestStep('pam_GetParameterValues');
    tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.Telemetry.Enable");
    expectedresult="SUCCESS";
    #Execute the test case in DUT
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    logEnable  = tdkTestObj.getResultDetails();
    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS");
        print("TEST STEP 1: Get the Telemetry Enable state ");
        print("EXPECTED RESULT 1: Should get the TELEMETRY Enable state");
        print("ACTUAL RESULT 1: TELEMETRY Enable state :",logEnable);
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");

        if logEnable == "false":
            tdkTestObj = obj.createTestStep('pam_SetParameterValues');
            tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.Telemetry.Enable");
            tdkTestObj.addParameter("ParamValue","true");
            tdkTestObj.addParameter("Type","bool");
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();
            if expectedresult in actualresult:
                flag =1;
                revertflag =1;
                tdkTestObj.setResultStatus("SUCCESS");
                print("TEST STEP 2: Set the Telemetry Enable state to true");
                print("EXPECTED RESULT 2: Should set the TELEMETRY Enable state to true");
                print("ACTUAL RESULT 2: TELEMETRY Enable state :",details);
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : SUCCESS");
            else:
                flag =0;
                revertflag =0;
                tdkTestObj.setResultStatus("FAILURE");
                print("TEST STEP 2: Set the Telemetry Enable state to true");
                print("EXPECTED RESULT 2: Should set the TELEMETRY Enable state to true");
                print("ACTUAL RESULT 2: TELEMETRY Enable state :",details);
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");

        if flag == 1:
            tdkTestObj = obj.createTestStep('pam_GetParameterValues');
            tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_WIFI_TELEMETRY.LogInterval");
            expectedresult="SUCCESS";
            #Execute the test case in DUT
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            DeflogInt = tdkTestObj.getResultDetails();
            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS");
                print("TEST STEP 2: Get the TELEMETRY LogInterval");
                print("EXPECTED RESULT 2: Should get the TELEMETRY LogInterval");
                print("ACTUAL RESULT 2: TELEMETRY LogInterval:",DeflogInt);
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : SUCCESS");

                tdkTestObj = obj.createTestStep('pam_SetParameterValues');
                tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_WIFI_TELEMETRY.LogInterval");
                tdkTestObj.addParameter("ParamValue","300");
                tdkTestObj.addParameter("Type","int");
                expectedresult="SUCCESS";
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                details = tdkTestObj.getResultDetails();
                if expectedresult in actualresult:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("TEST STEP 3: Set the TELEMETRY LogInterval to 5 min");
                    print("EXPECTED RESULT 3: Should set the TELEMETRY LogInterval to 5 min");
                    print("ACTUAL RESULT 3: TELEMETRY LogInterval:",details);
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : SUCCESS");

                    #Check whether the wifihealth.txt file is present or not
                    tdkTestObj = sysObj.createTestStep('ExecuteCmd');
                    cmd = "[ -f /rdklogs/logs/wifihealth.txt ] && echo \"File exist\" || echo \"File does not exist\"";
                    tdkTestObj.addParameter("command",cmd);
                    expectedresult="SUCCESS";
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails().strip().replace("\\n", "");

                    if details == "File exist":
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("TEST STEP 4: Check for wifihealth log file presence");
                        print("EXPECTED RESULT 4:wifihealth log file should be present");
                        print("ACTUAL RESULT 4:wifihealth log file is present");
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : SUCCESS");


                        #Check for the maraker WIFI_BANDUTILIZATION_2
                        step = 5;
                        tdkTestObj = sysObj.createTestStep('ExecuteCmd');
                        cmd = "grep -ire \"WIFI_BANDUTILIZATION_2\" /rdklogs/logs/wifihealth.txt";
                        tdkTestObj.addParameter("command",cmd);
                        expectedresult="SUCCESS";

                        print("\nTEST STEP %d: Check for the presence of the marker WIFI_BANDUTILIZATION_2" %step);
                        print("EXPECTED RESULT %d: WIFI_BANDUTILIZATION_2 marker should be present" %step);

                        markerfound = 0;
                        #check every 60s for 5 minutes to see if the log is getting populated.
                        for iteration in range(1,6):
                            print("Waiting for the marker to get populated in wifihealth.txt....\nIteration : %d" %iteration);
                            tdkTestObj.executeTestCase(expectedresult);
                            actualresult = tdkTestObj.getResult();
                            details = tdkTestObj.getResultDetails().strip().replace("\\n", "");

                            if expectedresult in actualresult and "WIFI_BANDUTILIZATION_2" in details:
                                markerfound = 1;
                                break;
                            else:
                                sleep(60);
                                continue;

                        if markerfound == 1:
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("ACTUAL RESULT %d: WIFI_BANDUTILIZATION_2 marker is found; Details : %s" %(step,details));
                            #Get the result of execution
                            print("[TEST EXECUTION RESULT] : SUCCESS");

                            # Retrieve the value of WIFI_BANDUTILIZATION_2
                            step += 1;
                            tdkTestObj = sysObj.createTestStep('ExecuteCmd')
                            cmd = "grep -ire 'WIFI_BANDUTILIZATION_2' /rdklogs/logs/wifihealth.txt | awk -F 'WIFI_BANDUTILIZATION_2:' '{print $2}' | awk '{print $1}'"
                            tdkTestObj.addParameter("command", cmd)
                            expectedresult = "SUCCESS"

                            print("\nTEST STEP %d: Retrieve the value of WIFI_BANDUTILIZATION_2" % step)
                            print("EXPECTED RESULT %d: The value of WIFI_BANDUTILIZATION_2 should be retrieved" % step)

                            tdkTestObj.executeTestCase(expectedresult)
                            actualresult = tdkTestObj.getResult()
                            details = tdkTestObj.getResultDetails().strip().replace("\\n", "")

                            if expectedresult in actualresult and details:
                                tdkTestObj.setResultStatus("SUCCESS")
                                print("ACTUAL RESULT %d: Retrieved the value of WIFI_BANDUTILIZATION_2; Details : %s" % (step, details))
                                print("[TEST EXECUTION RESULT] : SUCCESS")
                            else:
                                tdkTestObj.setResultStatus("FAILURE")
                                print("ACTUAL RESULT %d: Failed to retrieve the value of WIFI_BANDUTILIZATION_2; Details : %s" % (step, details))
                                print("[TEST EXECUTION RESULT] : FAILURE")
                        else:
                            tdkTestObj.setResultStatus("FAILURE");
                            print("ACTUAL RESULT %d: WIFI_BANDUTILIZATION_2 marker is not found; Details : %s" %(step,details));
                            #Get the result of execution
                            print("[TEST EXECUTION RESULT] : FAILURE");
                    else:
                        tdkTestObj.setResultStatus("FAILURE");
                        print("TEST STEP 4: Check for wifihealth log file presence");
                        print("EXPECTED RESULT 4:wifihealth log file should be present");
                        print("ACTUAL RESULT 4:wifihealth log file is not present");
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : FAILURE");
                    #Revert the Value
                    tdkTestObj = obj.createTestStep('pam_SetParameterValues');
                    tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_WIFI_TELEMETRY.LogInterval");
                    tdkTestObj.addParameter("ParamValue",DeflogInt);
                    tdkTestObj.addParameter("Type","int");
                    expectedresult="SUCCESS";
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails();
                    if expectedresult in actualresult:
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("TEST STEP 7: Revert the TELEMETRY LogInterval to previous");
                        print("EXPECTED RESULT 7: Should revert the TELEMETRY LogInterval to previous");
                        print("ACTUAL RESULT 7: Revert successfull");
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : SUCCESS");
                    else:
                        tdkTestObj.setResultStatus("FAILURE");
                        print("TEST STEP 7: Revert the TELEMETRY LogInterval to previous");
                        print("EXPECTED RESULT 7: Should revert the TELEMETRY LogInterval to previous");
                        print("ACTUAL RESULT 7: Revertion failed");
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : FAILURE");
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print("TEST STEP 3: Set the TELEMETRY LogInterval to 5 min");
                    print("EXPECTED RESULT 3: Should set the TELEMETRY LogInterval to 5 min");
                    print("ACTUAL RESULT 3: TELEMETRY LogInterval:",details);
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print("TEST STEP 2: Get the TELEMETRY LogInterval");
                print("EXPECTED RESULT 2: Should get the TELEMETRY LogInterval");
                print("ACTUAL RESULT 2: TELEMETRY LogInterval:",DeflogInt);
                #Get the result of execution
                print("[TEST EXECUTION RESULT] :FAILURE");
            if revertflag == 1:
                #Revert the value
                tdkTestObj = obj.createTestStep('pam_SetParameterValues');
                tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.Telemetry.Enable");
                tdkTestObj.addParameter("ParamValue",logEnable);
                tdkTestObj.addParameter("Type","bool");
                expectedresult="SUCCESS";
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                details = tdkTestObj.getResultDetails();
                if expectedresult in actualresult:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("TEST STEP 8: Revert the Telemetry Enable status to previous");
                    print("EXPECTED RESULT 8: Should revert the Telemetry Enable status to previous");
                    print("ACTUAL RESULT 8: Revert successfull");
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : SUCCESS");
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print("TEST STEP 8: Revert the Telemetry Enable status to previous");
                    print("EXPECTED RESULT 8: Should revert the Telemetry Enable status to previous");
                    print("ACTUAL RESULT 8: Revertion failed");
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");
        else:
            print(" Telemetry logger was disbled and failed on enabling")
            tdkTestObj.setResultStatus("FAILURE");
            print("[TEST EXECUTION RESULT] :FAILURE");
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print("TEST STEP 1: Get the Telemetry Enable state ");
        print("EXPECTED RESULT 1: Should get the TELEMETRY Enable state");
        print("ACTUAL RESULT 1: TELEMETRY Enable state :",logEnable);
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");
    obj.unloadModule("pam")
    sysObj.unloadModule("sysutil");
else:
    print("Failed to load pam/sysutil module");
    obj.setLoadModuleStatus("FAILURE");
    print("Module loading failed");

