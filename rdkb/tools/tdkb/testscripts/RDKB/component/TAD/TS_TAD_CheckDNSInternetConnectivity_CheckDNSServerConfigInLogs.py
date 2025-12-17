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
  <version>5</version>
  <name>TS_TAD_CheckDNSInternetConnectivity_CheckDNSServerConfigInLogs</name>
  <primitive_test_id/>
  <primitive_test_name>TADstub_Set</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>To check if the "DnsServerCount" and "DNS_ENTRY_" logs are populated under /rdklogs/logs/DNSInternetCheck.txt.0 when Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNow is set to true after enabling the corresponding WAN Interface.</synopsis>
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
    <test_case_id>TC_TAD_100</test_case_id>
    <test_objective>To check if the "DnsServerCount" and "DNS_ENTRY_" logs are populated under /rdklogs/logs/DNSInternetCheck.txt.0 when Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNow is set to true after enabling the corresponding WAN Interface.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>ParamName : Device.Diagnostics.X_RDK_DNSInternet.Enable
ParamValue : true/false
Type : boolean
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterfaceNumberOfEntries
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable
ParamValue : true/false
Type : boolean
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNow
ParamValue : true
Type : boolean</input_parameters>
    <automation_approch>1. Load the modules
2. Get and save the initial enable state of Device.Diagnostics.X_RDK_DNSInternet.Enable.
3. If it is disabled, enable the DNS Internet using Device.Diagnostics.X_RDK_DNSInternet.Enable and cross check with get.
4. Get and save the initial WAN Interface enable with Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable.
5. If not already in enabled state, set Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable to true and validate with get.
6. Start the DNS queries by setting Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNow to true. Need not cross check this parameter with get.
7. Once DNS queries start, check if "DnsServerCount" log is found under /rdklogs/logs/DNSInternetCheck.txt.0. Get the DNS Server count value from logs.
8. Loop through the servers from 1 to the upper limit specified by the server count and get the DNS Servers by querying the logs "DNS_ENTRY_&lt;Server&gt;".
9. Check if the DNS servers are non-empty values.
10. Revert the WAN interface enable state if required using Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable.
11. Revert to the initial Device.Diagnostics.X_RDK_DNSInternet.Enabe state if required.</automation_approch>
    <expected_output>The "DnsServerCount" and "DNS_ENTRY_" logs should be populated under /rdklogs/logs/DNSInternetCheck.txt.0 when Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNow is set to true after enabling the corresponding WAN Interface.</expected_output>
    <priority>High</priority>
    <test_stub_interface>tad</test_stub_interface>
    <test_script>TS_TAD_CheckDNSInternetConnectivity_CheckDNSServerConfigInLogs</test_script>
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
obj.configureTestCase(ip,port,'TS_TAD_CheckDNSInternetConnectivity_CheckDNSServerConfigInLogs');
sysobj.configureTestCase(ip,port,'TS_TAD_CheckDNSInternetConnectivity_CheckDNSServerConfigInLogs');

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

                        #Check the DNS Server configuration from the log file
                        #Find the number of DNS servers
                        step = step + 1;
                        file = "/rdklogs/logs/DNSInternetCheck.txt.0";
                        print("\nTEST STEP %d : Get the number of DNS servers configured from %s" %(step, file));
                        print("EXPECTED RESULT %d : The number of DNS servers configured should be retrieved from %s" %(step, file));

                        tdkTestObj = sysobj.createTestStep('ExecuteCmd');
                        cmd = "grep \"DnsServerCount             : \" " + file;
                        print(cmd);
                        actualresult, details = doSysutilExecuteCommand(tdkTestObj,cmd)

                        if expectedresult in actualresult and details != "" :
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("ACTUAL RESULT %d : Details : %s" %(step, details));
                            print("TEST EXECUTION RESULT : SUCCESS");

                            serverCount = details.split(" : ")[1];
                            if serverCount.isdigit():
                                serverCount = int(serverCount);
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("SUCCESS");
                                print("Number of DNS servers : %d" %serverCount);

                                #Check if DNS entries are found for each of the DNS servers
                                serverFlag = 1;
                                for server in range(1, serverCount + 1):
                                    step = step + 1;
                                    dnsEntry = "DNS_ENTRY_" + str(server);
                                    cmd = "grep " + dnsEntry + " " + file;
                                    tdkTestObj = sysobj.createTestStep('ExecuteCmd');
                                    print(cmd);
                                    actualresult, details = doSysutilExecuteCommand(tdkTestObj,cmd);

                                    print("\nTEST STEP %d : Get the DNS Server at entry %d should be retrieved from %s" %(step, server, file));
                                    print("EXPECTED RESULT %d : The DNS server configured at entry %d should be retrieved from %s" %(step, server, file));

                                    if expectedresult in actualresult and details != "" :
                                        #Set the result status of execution
                                        tdkTestObj.setResultStatus("SUCCESS");
                                        print("ACTUAL RESULT %d : Details : %s" %(step, details));
                                        print("TEST EXECUTION RESULT : SUCCESS");

                                        #Check if DNS server is non-empty
                                        serverValue = details.split(" : ")[1];
                                        if serverValue != "":
                                            #Set the result status of execution
                                            tdkTestObj.setResultStatus("SUCCESS");
                                            print("DNS server at entry %d : %s" %(server, serverValue));
                                        else:
                                            #Set the result status of execution
                                            tdkTestObj.setResultStatus("FAILURE");
                                            print("DNS server at entry %d is empty" %(server));
                                            serverFlag = 0;
                                            break;
                                    else:
                                        #Set the result status of execution
                                        tdkTestObj.setResultStatus("FAILURE");
                                        print("ACTUAL RESULT %d : DNS Server entry logs not found" %step);
                                        print("TEST EXECUTION RESULT : FAILURE");
                                        serverFlag = 0;
                                        break;

                                #Check if DNS Server values are retrieved successfully
                                step = step + 1;
                                print("\nTEST STEP %d : Check if the DNS Servers retrieved successfully and are non-empty" %step);
                                print("EXPECTED RESULT %d : All DNS Servers hould be retrieved successfully and should be non-empty" %(step));

                                if serverFlag == 1 :
                                    #Set the result status of execution
                                    tdkTestObj.setResultStatus("SUCCESS");
                                    print("ACTUAL RESULT %d : All DNS Servers are retrieved successfully and are non-empty" %step);
                                    print("TEST EXECUTION RESULT : SUCCESS");
                                else :
                                    #Set the result status of execution
                                    tdkTestObj.setResultStatus("FAILURE");
                                    print("ACTUAL RESULT %d : All DNS Servers are not retrieved successfully or are non-empty" %step);
                                    print("TEST EXECUTION RESULT : FAILURE");
                            else:
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("FAILURE");
                                print("Number of DNS servers retrieved is NOT valid");
                        else :
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("FAILURE");
                            print("ACTUAL RESULT %d : Number of DNS Servers is not VALID" %step);
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
