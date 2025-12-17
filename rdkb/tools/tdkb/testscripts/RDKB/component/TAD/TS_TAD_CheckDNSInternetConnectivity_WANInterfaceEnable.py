##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2023 RDK Management
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
  <version>3</version>
  <name>TS_TAD_CheckDNSInternetConnectivity_WANInterfaceEnable</name>
  <primitive_test_id/>
  <primitive_test_name>TADstub_Set</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>Check if Internet connectivity checking for each detected WAN interface is enabled when X_RDK_DNSInternet.WANInterface.{i}.Enable is set to TRUE and disabled when X_RDK_DNSInternet.WANInterface.{i}.Enable is set to FALSE. Also check if the required WAN connectivity check toggle status is getting logged under /rdklogs/logs/DNSInternetCheck.txt.0.</synopsis>
  <groups_id/>
  <execution_time>2</execution_time>
  <long_duration>false</long_duration>
  <advanced_script>false</advanced_script>
  <remarks/>
  <skip>false</skip>
  <box_types>
    <box_type>Broadband</box_type>
    <box_type>RPI</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_TAD_88</test_case_id>
    <test_objective>Check if Internet connectivity checking for each detected WAN interface is enabled when X_RDK_DNSInternet.WANInterface.{i}.Enable is set to TRUE and disabled when X_RDK_DNSInternet.WANInterface.{i}.Enable is set to FALSE. Also check if the required WAN connectivity check toggle status is getting logged under /rdklogs/logs/DNSInternetCheck.txt.0.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>ParamName : Device.Diagnostics.X_RDK_DNSInternet.Enable
ParamValue : true/false
Type : boolean
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterfaceNumberOfEntries
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable where the range of i [1, WANInterfaceNumberOfEntries]
ParamValue : true/false
Type : boolean</input_parameters>
    <automation_approch>1. Load the tad and tr181 modules
2. Get and save the initial enable state of Device.Diagnostics.X_RDK_DNSInternet.Enable.
3. If Device.Diagnostics.X_RDK_DNSInternet.Enable is initially disabled, enable it and validate with get.
4. Get the available WAN interfaces using Device.Diagnostics.X_RDK_DNSInternet.WANInterfaceNumberOfEntries.
5. For each of the available interfaces, query the enable state using  Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable and save it.
6. If initially false, check the initial number of log lines "wanconnectivity_chk Interface status changed 0-&gt;1" under /rdklogs/logs/DNSInternetCheck.txt.0 and if initially true, check for "wanconnectivity_chk Interface status changed 1-&gt;0".
7. Toggle to the opposite enable state and check if the toggling is success with get.
8. Then check the final number of logs lines "wanconnectivity_chk Interface status changed 0-&gt;1" under /rdklogs/logs/DNSInternetCheck.txt.0 and if initially true, check for "wanconnectivity_chk Interface status changed 1-&gt;0" if toggled to true and false respectively.
9. Check the number of log lines are incremented by 1.
10. Revert Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable to the initial state and check if it is success with a get.
11. Check if there is a corresponding increment in the number of required log lines.
12. Revert Device.Diagnostics.X_RDK_DNSInternet.Enable if required.
</automation_approch>
    <expected_output>Internet connectivity checking for each detected WAN interface should be enabled when X_RDK_DNSInternet.WANInterface.{i}.Enable is set to TRUE and disabled when X_RDK_DNSInternet.WANInterface.{i}.Enable is set to FALSE. The required WAN connectivity check toggle status should be logged properly under /rdklogs/logs/DNSInternetCheck.txt.0.</expected_output>
    <priority>High</priority>
    <test_stub_interface>tad</test_stub_interface>
    <test_script>TS_TAD_CheckDNSInternetConnectivity_WANInterfaceEnable</test_script>
    <skipped>No</skipped>
    <release_version>M109</release_version>
    <remarks/>
  </test_cases>
  <script_tags/>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
from tdkbVariables import *
from tdkutility import *;
from time import sleep;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("tad","RDKB");
sysobj = tdklib.TDKScriptingLibrary("sysutil","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_TAD_CheckDNSInternetConnectivity_WANInterfaceEnable');
sysobj.configureTestCase(ip,port,'TS_TAD_CheckDNSInternetConnectivity_WANInterfaceEnable');

#Get the result of connection with test component and DUT
loadmodulestatus=obj.getLoadModuleResult();
loadmodulestatus1=sysobj.getLoadModuleResult();
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus)
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus1)

if "SUCCESS" in loadmodulestatus.upper()and "SUCCESS" in loadmodulestatus1.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    sysobj.setLoadModuleStatus("SUCCESS");
    expectedresult="SUCCESS";

    #As Pre-requisite enable Device.Diagnostics.X_RDK_DNSInternet.Enable if not already enabled
    step = 1;
    tdkTestObj, preReqStatus, revertStatus, step = DNSInternetConnectivity_PreReq(obj, step, expectedresult);

    #If Pre-Requisites set successfully
    if preReqStatus == 0:
        #Check the number of WAN Interfaces for DNS Internet Connectivity Check
        step = step + 1;
        numberOfInterfaces = getWanInterfaceEntries(obj, expectedresult, step);

        #Number of WAN interfaces should be greater than or equal to 1
        if numberOfInterfaces >= 1:
            for wanInterface in range(1, numberOfInterfaces + 1):
                #Get the initial eable state of the WAN interface
                step = step + 1;
                paramName = "Device.Diagnostics.X_RDK_DNSInternet.WANInterface." + str(wanInterface) + ".Enable"
                tdkTestObj, actualresult, initialEnable = getWANInterface(obj, step, paramName, expectedresult);

                if expectedresult in actualresult:
                    #If initially WAN interface is enabled, set to false and revert back and also check the required log lines
                    if initialEnable == "true":
                        setEnable = "false";
                        wanStatusToggleString = "wanconnectivity_chk Interface status changed 1->0";
                        wanStatusRevertString = "wanconnectivity_chk Interface status changed 0->1";
                    #If initially WAN interface is disabled, set to true and revert back and also check the required log lines
                    else:
                        setEnable = "true";
                        wanStatusToggleString = "wanconnectivity_chk Interface status changed 0->1";
                        wanStatusRevertString = "wanconnectivity_chk Interface status changed 1->0";

                    print("WAN interface is initially in enable %s state" %initialEnable);

                    #Find the initial number of log lines indicating WAN interface enable toggling
                    step = step + 1;
                    tdkTestObj = sysobj.createTestStep('ExecuteCmd');
                    print("\nGet the initial number of log lines of " + wanStatusToggleString);
                    file = "/rdklogs/logs/DNSInternetCheck.txt.0";
                    count_initial = getLogFileTotalLinesCount(tdkTestObj, file, wanStatusToggleString, step);

                    #Now toggle the WAN interafce enable
                    step = step + 1;
                    tdkTestObj, actualresult, details = setWANInterface(obj, step, paramName, setEnable, expectedresult);

                    if expectedresult in actualresult:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("WAN Interface toggled to %s successfully" %setEnable);

                        #Find the final number of log lines indicating WAN interface toggling
                        sleep(2);
                        step = step + 1;
                        tdkTestObj = sysobj.createTestStep('ExecuteCmd');
                        print("\nGet the final number of log lines of " + wanStatusToggleString);
                        count_final = getLogFileTotalLinesCount(tdkTestObj, file, wanStatusToggleString, step);

                        #Check if the log line difference is 1
                        step = step + 1;
                        print("\nTEST STEP %d : Check if the WAN interface status change log - %s are populated under %s after toggling" %(step, wanStatusToggleString, file));
                        print("EXPECTED RESULT %d : WAN interface status change log should be present under %s after toggling" %(step, file));

                        print("Number of initial log lines of %s : %d" %(wanStatusToggleString, count_initial));
                        print("Number of final log lines of %s : %d" %(wanStatusToggleString, count_final));

                        if count_final == (count_initial + 1):
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("ACTUAL RESULT %d : The required log lines are found under %s after toggling" %(step, file));
                            #Get the result of execution
                            print("[TEST EXECUTION RESULT] : SUCCESS");
                        else:
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("FAILURE");
                            print("ACTUAL RESULT %d : The required log lines are NOT found under %s after toggling" %(step, file));
                            #Get the result of execution
                            print("[TEST EXECUTION RESULT] : FAILURE");

                        #Revert to initial state and check the logs
                        #Find the initial number of log lines indicating WAN interface enable revert
                        step = step + 1;
                        tdkTestObj = sysobj.createTestStep('ExecuteCmd');
                        print("\nGet the initial number of log lines of " + wanStatusRevertString);
                        count_initial = getLogFileTotalLinesCount(tdkTestObj, file, wanStatusRevertString, step);

                        #Now revert the WAN interafce enable
                        step = step + 1;
                        tdkTestObj, actualresult, details = setWANInterface(obj, step, paramName, initialEnable, expectedresult);

                        if expectedresult in actualresult:
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("WAN Interface reverted to %s successfully" %initialEnable);

                            #Find the final number of log lines indicating WAN interface revert
                            sleep(2);
                            step = step + 1;
                            tdkTestObj = sysobj.createTestStep('ExecuteCmd');
                            print("\nGet the final number of log lines of " + wanStatusRevertString);
                            count_final = getLogFileTotalLinesCount(tdkTestObj, file, wanStatusRevertString, step);

                            #Check if the log line difference is 1
                            step = step + 1;
                            print("\nTEST STEP %d : Check if the WAN interface status change log - %s are populated under %s after reverting" %(step, wanStatusRevertString, file));
                            print("EXPECTED RESULT %d : WAN interface status change log should be present under %s after reverting" %(step, file));

                            print("Number of initial log lines of %s : %d" %(wanStatusRevertString, count_initial));
                            print("Number of final log lines of %s : %d" %(wanStatusRevertString, count_final));

                            if count_final == (count_initial + 1):
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("SUCCESS");
                                print("ACTUAL RESULT %d : The required log lines are found under %s after reverting" %(step, file));
                                #Get the result of execution
                                print("[TEST EXECUTION RESULT] : SUCCESS");
                            else:
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("FAILURE");
                                print("ACTUAL RESULT %d : The required log lines are NOT found under %s after reverting" %(step, file));
                                #Get the result of execution
                                print("[TEST EXECUTION RESULT] : FAILURE");
                        else:
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("FAILURE");
                            print("WAN Interface NOT reverted to %s successfully" %initialEnable);
                    else:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print("WAN Interface NOT toggled to %s successfully" %setEnable);
                else:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    print("WAN Interface enable status is NOT retrieved successfully");
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print("Number of WAN Interface entries NOT retrieved successfully");

        #Revert operation
        setEnable = "false";
        step = step + 1;
        if revertStatus == 1:
            DNSInternetConnectivity_Revert(obj, step, setEnable, expectedresult);
        else:
            print("Reverting Device.Diagnostics.X_RDK_DNSInternet.Enable to initial value not required");
    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print("Pre-Requisites are not set successfully");

    obj.unloadModule("tad");
    sysobj.unloadModule("sysutil");
else:
    print("Failed to load the module");
    obj.setLoadModuleStatus("FAILURE");
    sysobj.setLoadModuleStatus("FAILURE");
    print("Module loading failed");
