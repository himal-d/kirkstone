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
  <version>4</version>
  <name>TS_TAD_CheckDNSInternetConnectivity_QueryResultTransitionFromBusy</name>
  <primitive_test_id/>
  <primitive_test_name>TADstub_Set</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>Check if an on-demand Internet connectivity check is triggered by enabling the parameter X_RDK_DNSInternet.WANInterface.{i}.QueryNow when Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable is enabled and Device.Diagnostics.X_RDK_DNSInternet.TestURL.{i}.URL is set to a invalid URL. Also check if the DNS query result retrieved using Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNowResult immediately after starting the DNS query result status is "BUSY" (state = 3) and then transitions to "DISCONNECTED" state (state = 2).</synopsis>
  <groups_id/>
  <execution_time>5</execution_time>
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
    <test_case_id>TC_TAD_90</test_case_id>
    <test_objective>Check if an on-demand Internet connectivity check is triggered by enabling the parameter X_RDK_DNSInternet.WANInterface.{i}.QueryNow when Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable is enabled and Device.Diagnostics.X_RDK_DNSInternet.TestURL.{i}.URL is set to an invalid URL. Also check if the DNS query result retrieved using Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNowResult immediately after starting the DNS query result status is "BUSY" (state = 3) and then transitions to "DISCONNECTED" state (state = 2).</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>ParamName : Device.Diagnostics.X_RDK_DNSInternet.Enable
ParamValue : true/false
Type : boolean
ParamName : Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries
ParamName : Device.Diagnostics.X_RDK_DNSInternet.TestURL.
ParamName : Device.Diagnostics.X_RDK_DNSInternet.TestURL.{i}.URL, where i is an integer
ParamValue : invalidurl.abc
Type : string
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterfaceNumberOfEntries
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable
ParamValue : true/false
Type : boolean
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNow
ParamValue : true
Type : boolean
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNowResult</input_parameters>
    <automation_approch>1. Load the tad and tr181 modules
2. Get and save the initial enable state of Device.Diagnostics.X_RDK_DNSInternet.Enable.
3. If it is disabled, enable the DNS Internet using Device.Diagnostics.X_RDK_DNSInternet.Enable and cross check with get.
4. Get the initial number of Test URLs configured using Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries.
5. To identify the upper limit of the table instance, create a new table instance using Device.Diagnostics.X_RDK_DNSInternet.TestURL. add table operation and fetch the instance number. We can assume that the number of URL entries are spread across the range 1 to the new instance number returned.
6. Loop through each Test URLs in the range using Device.Diagnostics.X_RDK_DNSInternet.TestURL.{i}.URL. For each available instance check if it holds a non-empty URL, if so copy it to a list and store it. Then delete that particular instance.
7. Then, iterate to the next URL. In case a particular instance is not present, continue to the next iteration.
8. Once all non-empty URLs are saved and available instances deleted, query Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries and check if it is 0.
9. If number of Test URL entries are 0, then the URL pre-requisite is completed and can proceed to the next step. Else, the test fails at this point.
10. Now set a new Test URL "invalidurl.abc"  after creating a table instance Device.Diagnostics.X_RDK_DNSInternet.TestURL. and validate with get.
11. Get and save the initial WAN Interface enable with Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable.
12. If not already in enabled state, set Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable to true and validate with get.
13. Start the DNS queries by setting Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNow to true. Need not cross check this parameter with get.
14. Immediately query Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNowResult and check if the value returned is 3 (for BUSY). Else return failure.
15. Sleep for 5 seconds before checking the DNS Query result status.
16. Get Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNowResult and check if the value returned is 2 (for DISCONNECTED). Else return failure.
17. Revert the WAN interface enable state if required using Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable.
18. Revert to the initial Test URL configuration if required.
19. Revert to the initial Device.Diagnostics.X_RDK_DNSInternet.Enable state if required.</automation_approch>
    <expected_output>On-demand Internet connectivity check should be triggered by enabling the parameter Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNow when Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable is enabled and Device.Diagnostics.X_RDK_DNSInternet.TestURL.{i}.URL is set to an invalid URL. Also the DNS query result retrieved using Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNowResult should be in "BUSY" state (state = 3) immediately after DNS queries are started and then transition to "DISCONNECTED" state (state = 2).</expected_output>
    <priority>High</priority>
    <test_stub_interface>tad</test_stub_interface>
    <test_script>TS_TAD_CheckDNSInternetConnectivity_QueryResultTransitionFromBusy</test_script>
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
tr181obj = tdklib.TDKScriptingLibrary("tdkbtr181","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_TAD_CheckDNSInternetConnectivity_QueryResultTransitionFromBusy');
tr181obj.configureTestCase(ip,port,'TS_TAD_CheckDNSInternetConnectivity_QueryResultTransitionFromBusy');

#Get the result of connection with test component and DUT
loadmodulestatus=obj.getLoadModuleResult();
loadmodulestatus1=tr181obj.getLoadModuleResult();
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus)
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus1)

if "SUCCESS" in loadmodulestatus.upper()and "SUCCESS" in loadmodulestatus1.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    tr181obj.setLoadModuleStatus("SUCCESS");
    expectedresult="SUCCESS";

    #As Pre-requisite enable Device.Diagnostics.X_RDK_DNSInternet.Enable if not already enabled
    step = 1;
    tdkTestObj, preReqStatus, revertStatus, step = DNSInternetConnectivity_PreReq(obj, step, expectedresult);

    #If Pre-Requisites set successfully
    if preReqStatus == 0:
        #Save and clear the existing Test URL table
        step = step + 1;
        testURLPreReq, testURLStore, step = saveAndClearTestURLTable(obj, tr181obj, step, expectedresult);

        if testURLPreReq == 0:
            #Set the Test URL to "invalidurl.abc" to a newly created Test URL table instance
            step = step + 1;
            testURLList = ["invalidurl.abc"];
            numberOfURLs = len(testURLList);
            setTestURL, newInstanceList, step = createTestURLTable(obj, tr181obj, step, expectedresult, numberOfURLs, testURLList);

            if setTestURL == 0:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print("Test URL table configured successfully");

                #Check the number of WAN Interfaces for DNS Internet Connectivity Check
                numberOfInterfaces = getWanInterfaceEntries(obj, expectedresult, step);

                #Number of WAN interfaces should be greater than or equal to 1
                if numberOfInterfaces >= 1:
                    for wanInterface in range(1, numberOfInterfaces + 1):
                        #Get the initial enable state of the WAN interface
                        step = step + 1;
                        paramName = "Device.Diagnostics.X_RDK_DNSInternet.WANInterface." + str(wanInterface) + ".Enable"
                        tdkTestObj, actualresult, initialEnable = getWANInterface(obj, step, paramName, expectedresult);

                        #If avaiable WAN interface is not enabled, set it to TRUE
                        proceedFlag = 1;
                        if initialEnable == "false":
                            step = step + 1;
                            setEnable = "true";
                            tdkTestObj, actualresult, details = setWANInterface(obj, step, paramName, setEnable, expectedresult);

                            if expectedresult in actualresult:
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("SUCCESS");
                                print("WAN Interface set to %s successfully" %setEnable);
                            else:
                                proceedFlag = 0;
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("FAILURE");
                                print("WAN Interface NOT set to %s successfully" %setEnable);
                        else:
                            "WAN Interface is enabled already...";

                        if proceedFlag == 1:
                            #Start the DNS queries by setting Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNow to true
                            step = step + 1;
                            paramName = "Device.Diagnostics.X_RDK_DNSInternet.WANInterface." + str(wanInterface) + ".QueryNow";
                            tdkTestObj, actualresult, details = setQueryNow(obj, step, paramName, "true", expectedresult);

                            if expectedresult in actualresult:
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("SUCCESS");
                                print("DNS queries started successfully");

                                #Check the DNS query result status immediately
                                step = step + 1;
                                paramName = "Device.Diagnostics.X_RDK_DNSInternet.WANInterface." + str(wanInterface) + ".QueryNowResult";
                                tdkTestObj, actualresult, details = getQueryNowResult(obj, step, paramName, expectedresult);

                                #DNS query result status is expected to be "BUSY"
                                step = step + 1;
                                print("\nTEST STEP %d : Check if the DNS query result status is BUSY" %step);
                                print("EXPECTED RESULT %d : The DNS query result status should be BUSY" %step);

                                if expectedresult in actualresult and details == "BUSY":
                                    #Set the result status of execution
                                    tdkTestObj.setResultStatus("SUCCESS");
                                    print("ACTUAL RESULT %d : DNS query result is retrieved as %s" %(step, details));
                                    print("TEST EXECUTION RESULT : SUCCESS");

                                    #Check the final DNS Query result status
                                    print("Sleeping 5s before querying the final DNS result status");
                                    sleep(5);
                                    step = step + 1;
                                    paramName = "Device.Diagnostics.X_RDK_DNSInternet.WANInterface." + str(wanInterface) + ".QueryNowResult";
                                    tdkTestObj, actualresult, details = getQueryNowResult(obj, step, paramName, expectedresult);

                                    #DNS query result status is expected to be "DISCONNECTED"
                                    step = step + 1;
                                    print("\nTEST STEP %d : Check if the DNS query result status is DISCONNECTED" %step);
                                    print("EXPECTED RESULT %d : The DNS query result status should be DISCONNECTED" %step);

                                    if expectedresult in actualresult and details == "DISCONNECTED":
                                        #Set the result status of execution
                                        tdkTestObj.setResultStatus("SUCCESS");
                                        print("ACTUAL RESULT %d : DNS query result is retrieved as %s" %(step, details));
                                        print("TEST EXECUTION RESULT : SUCCESS");
                                    else:
                                        #Set the result status of execution
                                        tdkTestObj.setResultStatus("FAILURE");
                                        print("ACTUAL RESULT %d : DNS query result is retrieved as %s which is not expected" %(step, details));
                                        print("TEST EXECUTION RESULT : FAILURE");
                                else:
                                    #Set the result status of execution
                                    tdkTestObj.setResultStatus("FAILURE");
                                    print("ACTUAL RESULT %d : DNS query result is retrieved as %s which is not expected" %(step, details));
                                    print("TEST EXECUTION RESULT : FAILURE");
                            else:
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("FAILURE");
                                print("DNS queries NOT started successfully");

                            #Revert the WAN interface enable if required
                            if initialEnable == "false":
                                step = step + 1;
                                paramName = "Device.Diagnostics.X_RDK_DNSInternet.WANInterface." + str(wanInterface) + ".Enable"
                                tdkTestObj, actualresult, details = setWANInterface(obj, step, paramName, initialEnable, expectedresult);

                                if expectedresult in actualresult:
                                    #Set the result status of execution
                                    tdkTestObj.setResultStatus("SUCCESS");
                                    print("WAN Interface enable reverted successfully");
                                else:
                                    #Set the result status of execution
                                    tdkTestObj.setResultStatus("FAILURE");
                                    print("WAN Interface enable NOT reverted successfully");
                            else:
                                "%s revert operation not required" %paramName;
                        else:
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("FAILURE");
                            print("WAN Interface is not enabled, cannot proceed further...");
                else:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    print("Number of WAN Interface entries NOT retrieved successfully");

                #Delete the Test URL table config
                step = step + 1;
                deleteStatus = deleteTestURLTable(tr181obj, step, expectedresult, newInstanceList);

                if deleteStatus == 0:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("Test URL table configured is deleted successfully");
                else:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    print("Test URL table configured is NOT deleted successfully");
            else:
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print("Test URL table NOT configured successfully");

            #Revert to initial table state
            print("\n****Revert to initial Test URL Configuration Start****");
            step = step + 1;
            setTestURL, newInstanceList, step = createTestURLTable(obj, tr181obj, step, expectedresult, len(testURLStore), testURLStore);

            if setTestURL == 0:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print("Test URL table reverted to initial state");
            else:
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print("Test URL table NOT reverted to initial state");
            print("\n****Revert to initial Test URL Configuration Complete****");
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print("Test URL table Pre-requisites NOT set successfully");

        #Revert operation
        setEnable = "false";
        if revertStatus == 1:
            DNSInternetConnectivity_Revert(obj, step, setEnable, expectedresult);
        else:
            print("Reverting Device.Diagnostics.X_RDK_DNSInternet.Enable to initial value not required");
    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print("Pre-Requisites are not set successfully");

    obj.unloadModule("tad");
    tr181obj.unloadModule("tdkbtr181");
else:
    print("Failed to load the module");
    obj.setLoadModuleStatus("FAILURE");
    tr181obj.setLoadModuleStatus("FAILURE");
    print("Module loading failed");
