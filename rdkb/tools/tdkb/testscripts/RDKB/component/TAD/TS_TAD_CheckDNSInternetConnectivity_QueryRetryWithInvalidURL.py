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
  <version>14</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_TAD_CheckDNSInternetConnectivity_QueryRetryWithInvalidURL</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>TADstub_Set</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check if X_RDK_DNSInternet.WANInterface.{i}.QueryRetry when set  to a value greater than 0, any failure of a DNS query is resulting in an immediate re-attempt, up to and not exceeding a number of re-attempts specified by the value of X_RDK_DNSInternet.WANInterface{i}.QueryRetry.</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>5</execution_time>
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
    <test_case_id>TC_TAD_97</test_case_id>
    <test_objective>Check if X_RDK_DNSInternet.WANInterface.{i}.QueryRetry when set to a value greater than 0, any failure of a DNS query is resulting in an immediate re-attempt, up to and not exceeding a number of re-attempts specified by the value of X_RDK_DNSInternet.WANInterface{i}.QueryRetry.</test_objective>
    <test_type>Negative</test_type>
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
ParamValue : "www.invalidurl.com"
Type : string
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterfaceNumberOfEntries
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable
ParamValue : true/false
Type : boolean
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNow
ParamValue : true
Type : boolean
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNowResult
ParamName : Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryRetry
ParamValue : dynamically assigned
Type : unsigned integer
ParamName: Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryTimeout</input_parameters>
    <automation_approch>1. Load the tad and tr181 modules
2. Get and save the initial enable state of Device.Diagnostics.X_RDK_DNSInternet.Enable.
3. If it is disabled, enable the DNS Internet using Device.Diagnostics.X_RDK_DNSInternet.Enable and cross check with get.
4. Get the initial number of Test URLs configured using Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries.
5. To identify the upper limit of the table instance, create a new table instance using Device.Diagnostics.X_RDK_DNSInternet.TestURL. add table operation and fetch the instance number. We can assume that the number of URL entries are spread across the range 1 to the new instance number returned.
6. Loop through each Test URLs in the range using Device.Diagnostics.X_RDK_DNSInternet.TestURL.{i}.URL. For each available instance check if it holds a non-empty URL, if so copy it to a list and store it. Then delete that particular instance.
7. Then, iterate to the next URL. In case a particular instance is not present, continue to the next iteration.
8. Once all non-empty URLs are saved and available instances deleted, query Device.Diagnostics.X_RDK_DNSInternet.TestURLNumberOfEntries and check if it is 0.
9. If number of Test URL entries are 0, then the URL pre-requisite is completed and can proceed to the next step. Else, the test fails at this point.
10. Now set a new Test URL "www.invalidurl.com" after creating a table instance Device.Diagnostics.X_RDK_DNSInternet.TestURL. and validate with get.
11. Get and save the initial WAN Interface enable with Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable.
12. If not already in enabled state, set Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable to true and validate with get.
13. Get the value of Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryRetry and store it.
14. Set Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryRetry to a new value. Validate with get.
15. Get the timeout configured in milliseconds using Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryTimeout.
16. Get the DNS Server type using the parameter Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.ServerType and check if the value is from ["IPv4", "IPv6", "IPv4*IPv6", "IPv4+IPv6"]
17. Get the maximum number of DNS Servers from the platform properties file.
18. Loop through the DNS Servers using Device.DNS.Client.Server.{i}.Type and get the number of valid DNS Servers for DHCPv4/dhcpV6 server types.
19. Multiply the total number of DNS servers that will send the queries as per the parameter Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.ServerType with the Query Time out value SET.  This value will be the maximum duration for 1 query retry to be completed.
20. Start the DNS queries by setting Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNow to true. Need not cross check this parameter with get.
21. Sleep for (retry * maxOneRetryTime )/1000 seconds before checking the DNS Query result status.
22. Get Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNowResult and check if the value returned is 2 (for DISCONNECTED). Else return failure.
23. Revert  Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryRetry  to initial value.
24. Revert the WAN interface enable state if required using Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.Enable.
25. Revert to the initial Test URL configuration if required.
26. Revert to the initial Device.Diagnostics.X_RDK_DNSInternet.Enable state if required.</automation_approch>
    <expected_output>If X_RDK_DNSInternet.WANInterface.{i}.QueryRetry is set to a value greater than 0, any failure of a DNS query should result in an immediate re-attempt, up to and not exceeding a number of re-attempts specified by the value of X_RDK_DNSInternet.WANInterface{i}.QueryRetry.</expected_output>
    <priority>High</priority>
    <test_stub_interface>tad</test_stub_interface>
    <test_script>TS_TAD_CheckDNSInternetConnectivity_QueryRetryWithInvalidURL</test_script>
    <skipped>No</skipped>
    <release_version>M109</release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
def timeForOneRetry(obj, sysobj, step, wanInterface, queryTimeOut):
    expectedresult = "SUCCESS";
    serversForIPv4 = 0;
    serversForIPv6 = 0;
    serversForIPv4AndIPv6 = 0;
    serversForIPv4OrIPv6 = 0;
    totalServers = -1;
    maxOneRetry = -1;
    possibleDNSServerTypeList = ["IPv4", "IPv6", "IPv4*IPv6", "IPv4+IPv6"];

    paramName = "Device.Diagnostics.X_RDK_DNSInternet.WANInterface." + str(wanInterface) + ".ServerType";
    print("\nTEST STEP %d : Get the initial value of %s" %(step, paramName));
    print("EXPECTED RESULT %d : The initial value of %s should be retrieved successfully" %(step, paramName));
    tdkTestObj, actualresult, DNSserverType = getDNSParameterValue(obj, expectedresult, paramName);

    if expectedresult in actualresult and DNSserverType != "":
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print("ACTUAL RESULT %d: %s : %s" %(step, paramName, DNSserverType));
        print("TEST EXECUTION RESULT : SUCCESS");

        if DNSserverType in possibleDNSServerTypeList:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print("DNS Server Type is Valid");

            #Get the maximum number of DNS servers from platform properties
            proceedFlag = 1;
            step = step + 1;
            print("\nTEST STEP %d : Get the maximum number of DNS Servers from platform properties" %step);
            print("EXPECTED RESULT %d : Should get the maximum number of DNS Servers from platform properties" %step);
            cmd = "sh %s/tdk_utility.sh parseConfigFile MAX_DNS_SERVERS" %TDK_PATH;
            tdkTestObj = sysobj.createTestStep('ExecuteCmd');
            print(cmd);
            actualresult, details = doSysutilExecuteCommand(tdkTestObj, cmd);

            if expectedresult in actualresult and details.isdigit():
                maxServers = int(details);
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT : Maximum Number of DNS Servers is : %d" %maxServers);
                print("TEST EXECUTION RESULT : SUCCESS");

                print("\n*****Finding maximum time taken for one retry*****");
                for index in range(1, maxServers + 1):
                    step = step + 1;
                    paramName = "Device.DNS.Client.Server." + str(index) + ".Type";
                    print("\nTEST STEP %d : Get the value of %s" %(step, paramName));
                    print("EXPECTED RESULT %d : The value of %s should be retrieved successfully" %(step, paramName));
                    tdkTestObj, actualresult, type = getDNSParameterValue(obj, expectedresult, paramName);

                    if expectedresult in actualresult and type != "":
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("ACTUAL RESULT %d: %s : %s" %(step, paramName, type));
                        print("TEST EXECUTION RESULT : SUCCESS");

                        #Ensure that DNS Server value is not empty
                        step = step + 1;
                        paramName = "Device.DNS.Client.Server." + str(index) + ".DNSServer";
                        print("\nTEST STEP %d : Get the value of %s" %(step, paramName));
                        print("EXPECTED RESULT %d : The value of %s should be retrieved successfully" %(step, paramName));
                        tdkTestObj, actualresult, details = getDNSParameterValue(obj, expectedresult, paramName);

                        if expectedresult in actualresult and details != "":
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("ACTUAL RESULT %d: %s : %s" %(step, paramName, details));
                            print("TEST EXECUTION RESULT : SUCCESS");

                            if type == "DHCPv4" :
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("SUCCESS");
                                serversForIPv4 = serversForIPv4 + 1;
                                serversForIPv4AndIPv6 = serversForIPv4AndIPv6 + 1;
                                serversForIPv4OrIPv6 = serversForIPv4OrIPv6 + 1;
                            elif type == "DHCPv6":
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("SUCCESS");
                                serversForIPv6 = serversForIPv6 + 1;
                                serversForIPv4AndIPv6 = serversForIPv4AndIPv6 + 1;
                                serversForIPv4OrIPv6 = serversForIPv4OrIPv6 + 1;
                            else:
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("FAILURE");
                                print("DNS Server Type NOT Valid");
                                proceedFlag = 0;
                                break;
                        else:
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("FAILURE");
                            print("ACTUAL RESULT %d: %s : %s" %(step, paramName, details));
                            print("TEST EXECUTION RESULT : FAILURE");
                            proceedFlag = 0;
                            break;
                    else:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print("ACTUAL RESULT %d: %s : %s" %(step, paramName, type));
                        print("TEST EXECUTION RESULT : FAILURE");
                        proceedFlag = 0;
                        break;
            else:
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT : Maximum Number of DNS Servers is : %s" %details);
                print("TEST EXECUTION RESULT : FAILURE");
                proceedFlag = 0;

            #Determine the total number of DNS servers to be considered
            if proceedFlag == 1:
                if DNSserverType == "IPv4":
                    totalServers = serversForIPv4;
                elif DNSserverType == "IPv6":
                    totalServers = serversForIPv6;
                elif DNSserverType == "IPv4*IPv6":
                    totalServers = serversForIPv4AndIPv6;
                elif DNSserverType == "IPv4+IPv6":
                    totalServers = serversForIPv4OrIPv6;
                else:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    print("DNS Server Type NOT Valid");
                    proceedFlag = 0;

            #Determine the maximum time taken for one retry
            if proceedFlag == 1:
                #Sleep time in msec
                maxOneRetry = totalServers * queryTimeOut;
                print("Time for 1 retry is equal to total DNS servers %d multiplied by Query time out %d : %d milliseconds" %(totalServers, queryTimeOut, maxOneRetry));
                print("\n*****Maximum time taken for one retry determined*****");
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print("DNS Server Type is NOT Valid");
    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print("ACTUAL RESULT %d: %s : %s" %(step, paramName, DNSserverType));
        print("TEST EXECUTION RESULT : FAILURE");

    return maxOneRetry, step;

# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
from tdkbVariables import *
from tdkutility import *;
from time import sleep;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("tad","RDKB");
tr181obj = tdklib.TDKScriptingLibrary("tdkbtr181","RDKB");
sysobj = tdklib.TDKScriptingLibrary("sysutil","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_TAD_CheckDNSInternetConnectivity_QueryRetryWithInvalidURL');
tr181obj.configureTestCase(ip,port,'TS_TAD_CheckDNSInternetConnectivity_QueryRetryWithInvalidURL');
sysobj.configureTestCase(ip,port,'TS_TAD_CheckDNSInternetConnectivity_QueryRetryWithInvalidURL');

#Get the result of connection with test component and DUT
loadmodulestatus=obj.getLoadModuleResult();
loadmodulestatus1=tr181obj.getLoadModuleResult();
loadmodulestatus2=sysobj.getLoadModuleResult();
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus)
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus1)
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus2)

if "SUCCESS" in loadmodulestatus.upper()and "SUCCESS" in loadmodulestatus1.upper() and "SUCCESS" in loadmodulestatus2.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    tr181obj.setLoadModuleStatus("SUCCESS");
    sysobj.setLoadModuleStatus("SUCCESS");
    expectedresult="SUCCESS";

    #Set Pre-Requisites for DNS Internet Connectivity Check
    step = 1;
    tdkTestObj, preReqStatus, revertStatus, step = DNSInternetConnectivity_PreReq(obj, step, expectedresult);

    #If Pre-Requisites set successfully
    if preReqStatus == 0:
        #Save and clear the existing Test URL table
        step = step + 1;
        testURLPreReq, testURLStore, step = saveAndClearTestURLTable(obj, tr181obj, step, expectedresult);

        if testURLPreReq == 0:
            #Set the Test URL to "www.invalidurl.com" to a newly created Test URL table instance
            step = step + 1;
            testURLList = ["www.invalidurl.com"];
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
                            #Get the initial value of Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryRetry
                            step = step + 1;
                            paramName = "Device.Diagnostics.X_RDK_DNSInternet.WANInterface." + str(wanInterface) + ".QueryRetry";

                            print("\nTEST STEP %d : Get the initial value of %s" %(step, paramName));
                            print("EXPECTED RESULT %d : The initial value of %s should be retrieved successfully" %(step, paramName));
                            tdkTestObj, actualresult, details = getDNSParameterValue(obj, expectedresult, paramName);

                            if expectedresult in actualresult and details != "":
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("SUCCESS");
                                print("ACTUAL RESULT %d: %s : %s" %(step, paramName, details));
                                print("TEST EXECUTION RESULT : SUCCESS");

                                if details.isdigit():
                                    initialRetry = int(details);
                                    #Set the result status of execution
                                    tdkTestObj.setResultStatus("SUCCESS");
                                    print("Initial retry count is valid");

                                    #Set Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryRetry to retry DNS quries
                                    if initialRetry != 10:
                                        setRetry = 10;
                                    else:
                                        setRetry = 15;

                                    step = step + 1;
                                    print("\nTEST STEP %d : Set %s to %d" %(step, paramName, setRetry));
                                    print("EXPECTED RESULT %d : Setting %s to %d should be success" %(step, paramName, setRetry));
                                    tdkTestObj, actualresult, details = setDNSParameterValue(obj, expectedresult, paramName, str(setRetry), "unsignedint");

                                    if expectedresult in actualresult and details != "":
                                        #Set the result status of execution
                                        tdkTestObj.setResultStatus("SUCCESS");
                                        print("ACTUAL RESULT %d: %s set successfully" %(step, paramName));
                                        print("TEST EXECUTION RESULT : SUCCESS");

                                        #Get the value of Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryTimeout
                                        step = step + 1;
                                        paramName = "Device.Diagnostics.X_RDK_DNSInternet.WANInterface." + str(wanInterface) + ".QueryTimeout";

                                        print("\nTEST STEP %d : Get the value of %s" %(step, paramName));
                                        print("EXPECTED RESULT %d : The initial value of %s should be retrieved successfully" %(step, paramName));
                                        tdkTestObj, actualresult, details = getDNSParameterValue(obj, expectedresult, paramName);

                                        if expectedresult in actualresult and details != "":
                                            #Set the result status of execution
                                            tdkTestObj.setResultStatus("SUCCESS");
                                            print("ACTUAL RESULT %d: %s : %s" %(step, paramName, details));
                                            print("TEST EXECUTION RESULT : SUCCESS");

                                            if details.isdigit():
                                                #The timeout is given in msec
                                                timeout = int(details);
                                                #Set the result status of execution
                                                tdkTestObj.setResultStatus("SUCCESS");
                                                print("Timeout in milliseconds is : %d" %timeout);

                                                #Calculate the maximum time taken for 1 retry
                                                step = step + 1;
                                                maxOneRetryTime, step = timeForOneRetry(obj, sysobj, step, wanInterface, timeout);

                                                if maxOneRetryTime > 0:
                                                    #Start the DNS queries by setting Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryNow to true
                                                    step = step + 1;
                                                    paramName = "Device.Diagnostics.X_RDK_DNSInternet.WANInterface." + str(wanInterface) + ".QueryNow";
                                                    tdkTestObj, actualresult, details = setQueryNow(obj, step, paramName, "true", expectedresult);

                                                    if expectedresult in actualresult:
                                                        #Set the result status of execution
                                                        tdkTestObj.setResultStatus("SUCCESS");
                                                        print("DNS queries started successfully");

                                                        #Check the DNS Query result status after waiting for the retries to be completed
                                                        sleepTime = float(setRetry * maxOneRetryTime)/1000;
                                                        print("Sleeping %ds before querying the DNS result status" %sleepTime);
                                                        sleep(sleepTime);
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
                                                        print("DNS queries NOT started successfully");
                                                else:
                                                    #Set the result status of execution
                                                    tdkTestObj.setResultStatus("SUCCESS");
                                                    print("Timeout is not valid");
                                            else:
                                                #Set the result status of execution
                                                tdkTestObj.setResultStatus("FAILURE");
                                                print("ACTUAL RESULT %d: %s : %s" %(step, paramName, details));
                                                print("TEST EXECUTION RESULT : FAILURE");
                                        else:
                                            #Set the result status of execution
                                            tdkTestObj.setResultStatus("FAILURE");
                                            print("Maximum duration for one query retry attempt could not be determined successfully, cannot proceed further...");

                                        #Revert Device.Diagnostics.X_RDK_DNSInternet.WANInterface.{i}.QueryRetry to initial value
                                        step = step + 1;
                                        paramName = "Device.Diagnostics.X_RDK_DNSInternet.WANInterface." + str(wanInterface) + ".QueryRetry";
                                        print("\nTEST STEP %d : Revert %s to %d" %(step, paramName, initialRetry));
                                        print("EXPECTED RESULT %d : Reverting %s to %d should be success" %(step, paramName, initialRetry));
                                        tdkTestObj, actualresult, details = setDNSParameterValue(obj, expectedresult, paramName, str(initialRetry), "unsignedint");

                                        if expectedresult in actualresult and details != "":
                                            #Set the result status of execution
                                            tdkTestObj.setResultStatus("SUCCESS");
                                            print("ACTUAL RESULT %d: %s reverted successfully" %(step, paramName));
                                            print("TEST EXECUTION RESULT : SUCCESS");
                                        else:
                                            #Set the result status of execution
                                            tdkTestObj.setResultStatus("FAILURE");
                                            print("ACTUAL RESULT %d: %s NOT reverted successfully" %(step, paramName));
                                            print("TEST EXECUTION RESULT : FAILURE");
                                    else:
                                        #Set the result status of execution
                                        tdkTestObj.setResultStatus("FAILURE");
                                        print("ACTUAL RESULT %d: %s NOT set successfully" %(step, paramName));
                                        print("TEST EXECUTION RESULT : FAILURE");
                                else:
                                    #Set the result status of execution
                                    tdkTestObj.setResultStatus("FAILURE");
                                    print("Initial retry count is NOT valid");
                            else:
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("FAILURE");
                                print("ACTUAL RESULT %d: %s : %s" %(step, paramName, details));
                                print("TEST EXECUTION RESULT : FAILURE");

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
    sysobj.unloadModule("sysutil");
else:
    print("Failed to load the module");
    obj.setLoadModuleStatus("FAILURE");
    tr181obj.setLoadModuleStatus("FAILURE");
    sysobj.setLoadModuleStatus("FAILURE");
    print("Module loading failed");
