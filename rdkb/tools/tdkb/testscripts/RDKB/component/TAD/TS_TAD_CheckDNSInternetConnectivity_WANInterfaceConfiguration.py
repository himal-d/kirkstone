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
  <version>14</version>
  <name>TS_TAD_CheckDNSInternetConnectivity_WANInterfaceConfiguration</name>
  <primitive_test_id/>
  <primitive_test_name>TADstub_Set</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>When X_RDK_DNSInternet.Enable = TRUE, check the value of Device.Diagnostics.X_RDK_DNSInternet.WANInterfaceNumberOfEntries and make sure that the Alias for the WAN Interfaces are retrieved successfully using Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Alias and they are [i = 1 : "Primary", i = 2 : "Backup"] respectively.</synopsis>
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
    <test_case_id>TC_TAD_86</test_case_id>
    <test_objective>When X_RDK_DNSInternet.Enable = TRUE, check the value of Device.Diagnostics.X_RDK_DNSInternet.WANInterfaceNumberOfEntries and make sure that the Alias for the available WAN Interfaces are retrieved successfully using Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Alias and they are [i = 1 : "Primary", i = 2 : "Backup"] respectively.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>ParamName : Device.Diagnostics.X_RDK_DNSInternet.Enable
ParamValue : true/false
Type : boolean
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterfaceNumberOfEntries
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Alias where the range of i [1, WANInterfaceNumberOfEntries]</input_parameters>
    <automation_approch>1. Load the tad and tr181 modules
2. Get and save the initial enable state of Device.Diagnostics.X_RDK_DNSInternet.Enable.
3. If Device.Diagnostics.X_RDK_DNSInternet.Enable is initially disabled, enable it and validate with get.
4. Get the available WAN interfaces using Device.Diagnostics.X_RDK_DNSInternet.WANInterfaceNumberOfEntries.
5. For each of the available interfaces, query the Alias using Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Alias.
6. Check if [i = 1 : "Primary", i = 2 : "Backup"]
7. Revert Device.Diagnostics.X_RDK_DNSInternet.Enable to initial state if required.</automation_approch>
    <expected_output>When X_RDK_DNSInternet.Enable = TRUE, the Alias for the available WAN Interfaces should be retrieved successfully using Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Alias and they should be [i = 1 : "Primary", i = 2 : "Backup"] respectively.</expected_output>
    <priority>High</priority>
    <test_stub_interface>tad</test_stub_interface>
    <test_script>TS_TAD_CheckDNSInternetConnectivity_WANInterfaceConfiguration</test_script>
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

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_TAD_CheckDNSInternetConnectivity_WANInterfaceConfiguration');

#Get the result of connection with test component and DUT
loadmodulestatus=obj.getLoadModuleResult();
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus)

if "SUCCESS" in loadmodulestatus.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
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
            #Check if the WAN Interface Alias is retrieved as expected
            step = step + 1;
            aliasExpected = ["Primary", "Backup"];

            for wanInterface in range(1, numberOfInterfaces + 1):
                paramName = "Device.Diagnostics.X_RDK_DNSInternet.WANInterface." + str(wanInterface) + ".Alias"
                print("\nTEST STEP %d : Check if %s is retrieved as %s" %(step, paramName, aliasExpected[wanInterface - 1]));
                print("EXPECTED RESULT %d : %s should be retrieved as expected" %(step, paramName));
                tdkTestObj, actualresult, alias = getDNSParameterValue(obj, expectedresult, paramName);

                if expectedresult in actualresult:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("Alias expected for WAN Interface %d as : %s" %(wanInterface, aliasExpected[wanInterface - 1]));
                    print("Alias retrieved for WAN Interface %d as : %s" %(wanInterface, alias));

                    if alias == aliasExpected[wanInterface - 1]:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("ACTUAL RESULT %d : Alias retrieved for WAN Interface %d is as expected" %(step, wanInterface));
                        print("TEST EXECUTION RESULT : SUCCESS");
                    else:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print("ACTUAL RESULT %d : Alias retrieved for WAN Interface %d is NOT as expected" %(step, wanInterface));
                        print("TEST EXECUTION RESULT : FAILURE");
                else:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT %d : Alias NOT retrieved for WAN Interface %d" %(step, wanInterface));
                    print("TEST EXECUTION RESULT : FAILURE");
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print("As Number of WAN Interfaces is not valid, cannot proceed further...");

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
else:
    print("Failed to load the module");
    obj.setLoadModuleStatus("FAILURE");
    print("Module loading failed");
