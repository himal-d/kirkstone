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
  <name>TS_TAD_CheckDNSInternetConnectivity_AddAndDeleteTestURL</name>
  <primitive_test_id/>
  <primitive_test_name>TADstub_Set</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>To check if adding 2 Test URL table instances, Device.Diagnostics.X_RDK_DNSInternet.TestURL.{i}.URL, using the add table operation is incrementing the value of Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries by 2 and the corresponding delete operation of the newly added instances decrement Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries to initial number of entries.</synopsis>
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
    <test_case_id>TC_TAD_91</test_case_id>
    <test_objective>To check if adding 2 Test URL table instances, Device.Diagnostics.X_RDK_DNSInternet.TestURL.{i}.URL, using the add table operation is incrementing the value of Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries by 2 and the corresponding delete operation of the newly added instances decrement Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries to initial number of entries.</test_objective>
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
ParamValue : "www.amazon.com", "www.reddit.com"
Type : string</input_parameters>
    <automation_approch>1. Load the tad and tr181 modules
2. Get and save the initial enable state of Device.Diagnostics.X_RDK_DNSInternet.Enable.
3. If it is disabled, enable the DNS Internet using Device.Diagnostics.X_RDK_DNSInternet.Enable and cross check with get.
4. Get the initial number of Test URLs configured using Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries.
5. Add two new instances for Test URL table using Device.Diagnostics.X_RDK_DNSInternet.TestURL. and configure the test URLs "www.amazon.com", "www.reddit.com". Validate the set with get.
6. Check the current Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries to see if it is incremented by 2.
7. Delete the two newly added table instances using Device.Diagnostics.X_RDK_DNSInternet.TestURL.{i}.
8. Check the current Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries to see if it is decremented by 2.
9. Revert Device.Diagnostics.X_RDK_DNSInternet.Enable if required.</automation_approch>
    <expected_output>Adding 2 Test URL table instances Device.Diagnostics.X_RDK_DNSInternet.TestURL.{i}.URL, using the add table operation should increment the value of Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries by 2 and the corresponding delete operation of the newly added instances should decrement Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries to initial number of entries.</expected_output>
    <priority>High</priority>
    <test_stub_interface>tad</test_stub_interface>
    <test_script>TS_TAD_CheckDNSInternetConnectivity_AddAndDeleteTestURL</test_script>
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
obj.configureTestCase(ip,port,'TS_TAD_CheckDNSInternetConnectivity_AddAndDeleteTestURL');
tr181obj.configureTestCase(ip,port,'TS_TAD_CheckDNSInternetConnectivity_AddAndDeleteTestURL');

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
        #Get the initial number of Test URL entries configured
        step = step + 1;
        paramName = "Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries";
        tdkTestObj, actualresult, initialEntries = getDNSParameterValue(obj, expectedresult, paramName);

        print("\nTEST STEP %d: Get the initial number of Test URLs configured using %s" %(step, paramName));
        print("EXPECTED RESULT %d: Should get the initial number of Test URLs configured using %s" %(step, paramName));

        if expectedresult in actualresult and initialEntries.isdigit():
            initialEntries = int(initialEntries);
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print("ACTUAL RESULT %d: Initial number of Test URLs configured retrieved : %d" %(step, initialEntries));
            print("TEST EXECUTION RESULT : SUCCESS");

            #Add 2 new Table instances and populate a Test URLs
            step = step + 1;
            testURLList = ["www.amazon.com", "www.reddit.com"];
            numberOfURLs = len(testURLList);
            setTestURL, newInstanceList, step = createTestURLTable(obj, tr181obj, step, expectedresult, numberOfURLs, testURLList);

            if setTestURL == 0:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print("Test URL table configured successfully");

                #Retrieve the current number of Test URL table entries
                paramName = "Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries";
                tdkTestObj, actualresult, currentEntries = getDNSParameterValue(obj, expectedresult, paramName);

                print("\nTEST STEP %d: Get the current number of Test URLs configured using %s" %(step, paramName));
                print("EXPECTED RESULT %d: Should get the current number of Test URLs configured using %s" %(step, paramName));

                if expectedresult in actualresult and currentEntries.isdigit():
                    currentEntries = int(currentEntries);
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d: Current number of Test URLs configured retrieved : %d" %(step, currentEntries));
                    print("TEST EXECUTION RESULT : SUCCESS");

                    #Check if the number of Test URL table entries is incremeneted by 2
                    step = step + 1;
                    print("\nTEST STEP %d: Check if the current number of Test URLs configured is incremeneted by 2" %(step));
                    print("EXPECTED RESULT %d: Should get the current number of Test URLs configured incremented by 2" %(step));
                    print("Initial Number of Entries : %d" %initialEntries);
                    print("Current Number of Entries : %d" %currentEntries);

                    if currentEntries == initialEntries + 2:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("ACTUAL RESULT %d: Current number of Test URLs is incremented by 2" %(step));
                        print("TEST EXECUTION RESULT : SUCCESS");

                        #Delete the new Test URLs configured
                        step = step + 1;
                        deleteStatus = deleteTestURLTable(tr181obj, step, expectedresult, newInstanceList);

                        if deleteStatus == 0:
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("Test URL table configured is deleted successfully");

                            #Get the final Test URL number of entries after deleting 2 Test URL table instances
                            step = step + 2;
                            paramName = "Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries";
                            tdkTestObj, actualresult, finalEntries = getDNSParameterValue(obj, expectedresult, paramName);

                            print("\nTEST STEP %d: Get the final number of Test URLs configured using %s" %(step, paramName));
                            print("EXPECTED RESULT %d: Should get the final number of Test URLs configured using %s" %(step, paramName));

                            if expectedresult in actualresult and finalEntries.isdigit():
                                finalEntries = int(finalEntries);
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("SUCCESS");
                                print("ACTUAL RESULT %d: Final number of Test URLs configured retrieved : %d" %(step, finalEntries));
                                print("TEST EXECUTION RESULT : SUCCESS");

                                #Check if the number of Test URL table entries is same as initial number
                                step = step + 1;
                                print("\nTEST STEP %d: Check if the final number of Test URLs configured is same as initial number of entries %d" %(step, initialEntries));
                                print("EXPECTED RESULT %d: Should get the final number of Test URLs configured as same as initial number of entries %d" %(step, initialEntries));
                                print("Initial Number of Entries : %d" %initialEntries);
                                print("Final Number of Entries : %d" %finalEntries);

                                if finalEntries == initialEntries:
                                    #Set the result status of execution
                                    tdkTestObj.setResultStatus("SUCCESS");
                                    print("ACTUAL RESULT %d: Final number of Test URLs is same as initial number of Test URL entries" %(step));
                                    print("TEST EXECUTION RESULT : SUCCESS");
                                else:
                                    #Set the result status of execution
                                    tdkTestObj.setResultStatus("FAILURE");
                                    print("ACTUAL RESULT %d: Final number of Test URLs is NOT same as initial number of Test URL entries" %(step));
                                    print("TEST EXECUTION RESULT : FAILURE");
                            else:
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("FAILURE");
                                print("ACTUAL RESULT %d: Final number of Test URLs configured retrieved : %d" %(step, finalEntries));
                                print("TEST EXECUTION RESULT : FAILURE");
                        else:
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("FAILURE");
                            print("Test URL table configured is NOT deleted successfully");
                    else:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print("ACTUAL RESULT %d: Current number of Test URLs is NOT incremented by 2" %(step));
                        print("TEST EXECUTION RESULT : FAILURE");
                else:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT %d: Current number of Test URLs configured retrieved : %d" %(step, currentEntries));
                    print("TEST EXECUTION RESULT : FAILURE");
            else:
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print("Test URL table is NOT configured successfully");
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print("ACTUAL RESULT %d: Initial number of Test URLs configured retrieved : %d" %(step, initialEntries));
            print("TEST EXECUTION RESULT : FAILURE");

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
    tr181obj.unloadModule("tdkbtr181");
else:
    print("Failed to load the module");
    obj.setLoadModuleStatus("FAILURE");
    tr181obj.setLoadModuleStatus("FAILURE");
    print("Module loading failed");
