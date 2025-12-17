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
  <name>TS_WANMANAGER_CheckForUDHCPCZombieProcess_AfterWanMgrRestart</name>
  <primitive_test_id/>
  <primitive_test_name>wanmanager_DoNothing</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>Check if UDHCPC zombie process is running in the device after stopping RDKWanManager service and after restarting the service.</synopsis>
  <groups_id/>
  <execution_time>10</execution_time>
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
    <test_case_id>TC_WANMANAGER_118</test_case_id>
    <test_objective>Check if UDHCPC zombie process is running in the device after stopping RDKWanManager service and after restarting the service.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script
3.Wan Manager should be enabled</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>None</input_parameters>
    <automation_approch>1. Load the module
2. Check if RdkWanManager service is running in the device.
3. Stop the RdkWanManager service.
4. Check if RdkWanManager service is in dead state.
5. Check if UDHCPC zombie process is running in the device, if so, return failure.
6. Restart RdkWanManager service
7. Check if RdkWanManager service is in active state.
8. Check if UDHCPC zombie process is running in the device, if so, return failure.
9. Unload the module.</automation_approch>
    <expected_output>UDHCPC zombie process should NOT be running in the device after stopping RDKWanManager service and after restarting the service.</expected_output>
    <priority>High</priority>
    <test_stub_interface>wanmanager</test_stub_interface>
    <test_script>TS_WANMANAGER_CheckForUDHCPCZombieProcess_AfterWanMgrRestart</test_script>
    <skipped>No</skipped>
    <release_version>M117</release_version>
    <remarks/>
  </test_cases>
  <script_tags/>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
from tdkutility import *;
from time import sleep;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("sysutil","1");

#IP and Port of box, No need to change,
#This will be replaced with corresponding DUT Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WANMANAGER_CheckForUDHCPCZombieProcess_AfterWanMgrRestart');

#Get the result of connection with test component and DUT
loadmodulestatus=obj.getLoadModuleResult();

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");
    expectedresult="SUCCESS";

    #Check the status of RDKWanManagerand service
    step = 1;
    print("\nTEST STEP %d: Check if RdkWanManager.service is in active state" %step);
    print("EXPECTED RESULT %d: RdkWanManager.service should be in active state" %step);
    tdkTestObj = obj.createTestStep('ExecuteCmd');
    query="systemctl status RdkWanManager.service | grep -i running";
    print("query:%s" %query)
    actualresult, details = doSysutilExecuteCommand(tdkTestObj,query)

    if expectedresult in actualresult and "running" in details:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print("ACTUAL RESULT %d : RdkWanManager.service is running in the device : %s" %(step, details));
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");

        #Stop RdkWanManager.service
        step = step + 1;
        print("\nTEST STEP %d: Stop RdkWanManager.service" %step);
        print("EXPECTED RESULT %d: Stop RdkWanManager.service" %step);
        tdkTestObj = obj.createTestStep('ExecuteCmd');
        query="systemctl stop RdkWanManager.service";
        print("query:%s" %query)
        actualresult, details = doSysutilExecuteCommand(tdkTestObj,query)

        if expectedresult in actualresult and details == "":
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print("ACTUAL RESULT %d : RdkWanManager.service is stopped" %(step));
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");

            #Check if RdkWanManager.service is in dead state
            step = step + 1;
            print("\nTEST STEP %d: Check if RdkWanManager.service is in dead state after stopping the service" %step);
            print("EXPECTED RESULT %d: RdkWanManager.service should be in dead state after stopping the service" %step);
            tdkTestObj = obj.createTestStep('ExecuteCmd');
            query="systemctl status RdkWanManager.service | grep -i dead";
            print("query:%s" %query)
            actualresult, details = doSysutilExecuteCommand(tdkTestObj,query)

            if expectedresult in actualresult and "dead" in details:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d : RdkWanManager.service is in dead state: %s" %(step, details));
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : SUCCESS");

                #Check if UDHCPC zombie process is present in DUT
                step = step + 1;
                print("\nTEST STEP %d: Check if UDHCPC is in zombie state when RdkWanManager.service is stopped" %step);
                print("EXPECTED RESULT %d: UDHCPC should not be in zombie state when RdkWanManager.service is stopped" %step);
                tdkTestObj = obj.createTestStep('ExecuteCmd');
                query="ps | grep \"\\[udhcpc\\]\"";
                print("query:%s" %query)
                actualresult, details = doSysutilExecuteCommand(tdkTestObj,query)

                if expectedresult in actualresult and details == "":
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d : UDHCPC not found in zombie state when RdkWanManager.service is stopped" %(step));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : SUCCESS");

                    #Restart RdkWanManager.service
                    step = step + 1;
                    print("\nTEST STEP %d: Restart RdkWanManager.service" %step);
                    print("EXPECTED RESULT %d: Restart RdkWanManager.service" %step);
                    tdkTestObj = obj.createTestStep('ExecuteCmd');
                    query="systemctl start RdkWanManager.service";
                    print("query:%s" %query)
                    actualresult, details = doSysutilExecuteCommand(tdkTestObj,query)

                    if expectedresult in actualresult and details == "":
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("ACTUAL RESULT %d : RdkWanManager.service is restarted" %(step));
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : SUCCESS");

                        #Check if RdkWanManager.service is in running state
                        step = step + 1;
                        print("\nTEST STEP %d: Check if RdkWanManager.service is in running state after restarting the service" %step);
                        print("EXPECTED RESULT %d: RdkWanManager.service should be in running state after restarting the service" %step);
                        tdkTestObj = obj.createTestStep('ExecuteCmd');
                        query="systemctl status RdkWanManager.service | grep -i running";
                        print("query:%s" %query)
                        actualresult, details = doSysutilExecuteCommand(tdkTestObj,query)

                        if expectedresult in actualresult and "running" in details:
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("ACTUAL RESULT %d : RdkWanManager.service is in running state: %s" %(step, details));
                            #Get the result of execution
                            print("[TEST EXECUTION RESULT] : SUCCESS");

                            #Check if UDHCPC zombie process is present in DUT post 5 seconds
                            sleep(5);
                            step = step + 1;
                            print("\nTEST STEP %d: Check if UDHCPC is in zombie state when RdkWanManager.service is restarted" %step);
                            print("EXPECTED RESULT %d: UDHCPC should not be in zombie state when RdkWanManager.service is restarted" %step);
                            tdkTestObj = obj.createTestStep('ExecuteCmd');
                            query="ps | grep \"\\[udhcpc\\]\"";
                            print("query:%s" %query)
                            actualresult, details = doSysutilExecuteCommand(tdkTestObj,query)

                            if expectedresult in actualresult and details == "":
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("SUCCESS");
                                print("ACTUAL RESULT %d : UDHCPC not found in zombie state when RdkWanManager.service is restarted" %(step));
                                #Get the result of execution
                                print("[TEST EXECUTION RESULT] : SUCCESS");
                            else:
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("FAILURE");
                                print("ACTUAL RESULT %d : Process found in zombie state when RdkWanManager.service is restarted : %s" %(step, details));
                                #Get the result of execution
                                print("[TEST EXECUTION RESULT] : FAILURE");
                        else:
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("FAILURE");
                            print("ACTUAL RESULT %d : RdkWanManager.service is NOT in running state: %s" %(step, details));
                            #Get the result of execution
                            print("[TEST EXECUTION RESULT] : FAILURE");
                    else:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print("ACTUAL RESULT %d : RdkWanManager.service is NOT restarted; %s" %(step, details));
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : FAILURE");
                else:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d : Process found in zombie state when RdkWanManager.service is stopped; %s" %(step, details));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : SUCCESS");
            else:
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT %d : RdkWanManager.service is NOT in dead state: %s" %(step, details));
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print("ACTUAL RESULT %d : RdkWanManager.service is NOT stopped" %(step));
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");
    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print("ACTUAL RESULT %d : RdkWanManager.service is NOT running in the device : %s" %(step, details));
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");

    obj.unloadModule("sysutil");
else:
    print("Failed to load the module");
    obj.setLoadModuleStatus("FAILURE");
