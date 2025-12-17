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
<?xml version='1.0' encoding='utf-8'?>
<xml>
  <id></id>
  <!-- Do not edit id. This will be auto filled while exporting. If you are adding a new script keep the id empty -->
  <version>6</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_TAD_CheckDNSInternetConnectivityNamespaces_WithDNSInternetEnabled</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>TADstub_Set</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>When Device.Diagnostics.X_RDK_DNSInternet.Enable is enabled, check if DNS Internet Connectivity DML objects/parameters below X_RDK_DNSInternet. are available.</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>2</execution_time>
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
    <test_case_id>TC_TAD_86</test_case_id>
    <test_objective>When Device.Diagnostics.X_RDK_DNSInternet.Enable is enabled, check if DNS Internet Connectivity DML objects/parameters below X_RDK_DNSInternet. are available.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>ParamName : Device.Diagnostics.X_RDK_DNSInternet.Enable
ParamValue : true/false
Type : boolean
ParamName : Device.Diagnostics.X_RDK_DNSInternet.Active
ParamName : Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterfaceNumberOfEntries</input_parameters>
    <automation_approch>1. Load the tad and tr181 modules
2. Get and save the initial enable state of Device.Diagnostics.X_RDK_DNSInternet.Enable.
3. If Device.Diagnostics.X_RDK_DNSInternet.Enable is initially disabled, enable it and validate with get.
4. Once enabled, check if DNS Internet Connectivity DML objects/parameters below X_RDK_DNSInternet. are available. To validate this, the following parameters are queried : "Device.Diagnostics.X_RDK_DNSInternet.Active", "Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries", "Device.Diagnostics.X_RDK_DNSInternet.WANInterfaceNumberOfEntries". Check if they return success when tried to query.
5. Revert Device.Diagnostics.X_RDK_DNSInternet.Enable to initial state if required.
</automation_approch>
    <expected_output>When Device.Diagnostics.X_RDK_DNSInternet.Enable is enabled, DNS Internet Connectivity DML objects/parameters below X_RDK_DNSInternet. should be available.</expected_output>
    <priority>High</priority>
    <test_stub_interface>tad</test_stub_interface>
    <test_script>TS_TAD_CheckDNSInternetConnectivityNamespaces_WithDNSInternetEnabled</test_script>
    <skipped>No</skipped>
    <release_version>M109</release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
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
obj.configureTestCase(ip,port,'TS_TAD_CheckDNSInternetConnectivityNamespaces_WithDNSInternetEnabled');

#Get the result of connection with test component and DUT
loadmodulestatus=obj.getLoadModuleResult();
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus)

if "SUCCESS" in loadmodulestatus.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    expectedresult="SUCCESS";

    #Get the initial enable state of Device.Diagnostics.X_RDK_DNSInternet.Enable
    step = 1;
    print("\nTEST STEP %d : Get the initial enable state of Device.Diagnostics.X_RDK_DNSInternet.Enable" %step);
    print("EXPECTED RESULT %d : The initial enable state of Device.Diagnostics.X_RDK_DNSInternet.Enable should be retrieved successfully" %step);
    tdkTestObj, actualresult, initialEnable = getDNSParameterValue(obj, expectedresult, "Device.Diagnostics.X_RDK_DNSInternet.Enable");

    if expectedresult in actualresult and initialEnable != "":
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print("ACTUAL RESULT %d: Device.Diagnostics.X_RDK_DNSInternet.Enable : %s" %(step, initialEnable));
        print("TEST EXECUTION RESULT : SUCCESS");

        #If initialEnable is "false", enable it
        proceedFlag = 1;
        if initialEnable == "false":
            print("DNSInternet is disabled initially");
            #Enabling Device.Diagnostics.X_RDK_DNSInternet.Enable and validating the SET
            step = step + 1;
            setEnable = "true";
            print("\nTEST STEP %d : Enable Device.Diagnostics.X_RDK_DNSInternet.Enable" %step);
            print("EXPECTED RESULT %d : Device.Diagnostics.X_RDK_DNSInternet.Enable should be enabled successfully" %step);
            tdkTestObj, actualresult, details = setDNSParameterValue(obj, expectedresult, "Device.Diagnostics.X_RDK_DNSInternet.Enable", setEnable, "boolean");

            if expectedresult in actualresult and details == "Set has been validated successfully":
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d: Device.Diagnostics.X_RDK_DNSInternet.Enable set to %s successfully" %(step, setEnable));
                print("TEST EXECUTION RESULT : SUCCESS");
            else:
                proceedFlag = 0;
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT %d: Device.Diagnostics.X_RDK_DNSInternet.Enable was NOT set to %s successfully" %(step, setEnable));
                print("TEST EXECUTION RESULT : FAILURE");
        else:
            print("Device.Diagnostics.X_RDK_DNSInternet.Enable is already in enabled state");

        #If the DNS Internet is enabled, proceed
        if proceedFlag == 1:
            #Check if the parameters Device.Diagnostics.X_RDK_DNSInternet.Active, Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries and Device.Diagnostics.X_RDK_DNSInternet.WANInterfaceNumberOfEntries are available
            step = step + 1;
            dmlFlag = 0;
            paramList = ["Device.Diagnostics.X_RDK_DNSInternet.Active", "Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries", "Device.Diagnostics.X_RDK_DNSInternet.WANInterfaceNumberOfEntries"];
            print("\nTEST STEP %d : Verify that DNS Internet Connectivity DML objects are available under Device.Diagnostics.X_RDK_DNSInternet. " %step);
            print("EXPECTED RESULT %d : DNS Internet Connectivity DML objects should be available under Device.Diagnostics.X_RDK_DNSInternet. " %step);

            for param in paramList:
                tdkTestObj, actualresult, details = getDNSParameterValue(obj, expectedresult, param);
                print("%s : %s" %(param, details));

                if expectedresult in actualresult:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("Parameter retrieved");
                else:
                    dmlFlag = 1;
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    print("Parameter NOT retrieved");
                    break;

            if dmlFlag == 0:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d: DNS Internet Connectivity DML objects are available under Device.Diagnostics.X_RDK_DNSInternet." %(step));
                print("TEST EXECUTION RESULT : SUCCESS");
            else:
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT %d: DNS Internet Connectivity DML objects are NOT available under Device.Diagnostics.X_RDK_DNSInternet." %(step));
                print("TEST EXECUTION RESULT : FAILURE");

            #Revert Device.Diagnostics.X_RDK_DNSInternet. if required
            step = step + 1;
            if initialEnable != "true":
                DNSInternetConnectivity_Revert(obj, step, initialEnable, expectedresult);
            else:
                print("Reverting Device.Diagnostics.X_RDK_DNSInternet.Enable to initial value not required");
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print("Unable to enable Device.Diagnostics.X_RDK_DNSInternet.Enable, cannot proceed further...");
    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print("ACTUAL RESULT %d: Device.Diagnostics.X_RDK_DNSInternet.Enable not retrieved" %step);
        print("TEST EXECUTION RESULT : FAILURE");

    obj.unloadModule("tad");
else:
    print("Failed to load the module");
    obj.setLoadModuleStatus("FAILURE");
    print("Module loading failed");
