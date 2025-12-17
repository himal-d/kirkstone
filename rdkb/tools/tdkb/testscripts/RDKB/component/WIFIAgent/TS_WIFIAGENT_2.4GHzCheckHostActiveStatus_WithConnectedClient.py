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
  <name>TS_WIFIAGENT_2.4GHzCheckHostActiveStatus_WithConnectedClient</name>
  <primitive_test_id/>
  <primitive_test_name>WIFIAgent_Get</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>Check if the Host Active status Device.Hosts.Host.{i}.Active is "true" for 2.4G connected client.</synopsis>
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
    <test_case_id>TC_WIFIAGENT_228</test_case_id>
    <test_objective>Check if the Host Active status Device.Hosts.Host.{i}.Active is "true" for 2.4G connected client.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script
3. Connect a 2.4G wifi client</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>ParamName : Device.Hosts.HostNumberOfEntries
ParamName : Device.Hosts.Host.{i}.Layer1Interface
ParamName : Device.Hosts.Host.{i}.Active</input_parameters>
    <automation_approch>1. Load the module
2. Get the number of Host entries using Device.Hosts.HostNumberOfEntries
3. Iterate through the Host Table and query the Device.Hosts.Host.{i}.Layer1Interface for each of the host entries.
4. Find the Host Table entry for wifi client by checking if Device.Hosts.Host.{i}.Layer1Interface is equal to Device.WiFi.SSID.1.
5. For the Host Entry of wifi client, query Device.Hosts.Host.{i}.Active and check if it is Active. Else, return failure.
6. If none of the host entry's layer 1 interface gives "Device.WiFi.SSID.1", return failure.
</automation_approch>
    <expected_output>The Host Active status Device.Hosts.Host.{i}.Active should be "true" for 2.4G connected client.</expected_output>
    <priority>High</priority>
    <test_stub_interface>wifiagent</test_stub_interface>
    <test_script>TS_WIFIAGENT_2.4GHzCheckHostActiveStatus_WithConnectedClient</test_script>
    <skipped>No</skipped>
    <release_version>M109</release_version>
    <remarks/>
  </test_cases>
  <script_tags/>
</xml>

'''
#use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
from tdkbVariables import *
from tdkutility import *;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIAGENT_2.4GHzCheckHostActiveStatus_WithConnectedClient');

#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus) ;

if "SUCCESS" in loadmodulestatus.upper():
    #Set the load module status
    obj.setLoadModuleStatus("SUCCESS");
    expectedresult="SUCCESS";

    #Get the number of host table entries
    step = 1;
    tdkTestObj = obj.createTestStep('WIFIAgent_Get');
    tdkTestObj.addParameter("paramName","Device.Hosts.HostNumberOfEntries");
    #Execute the test case in DUT
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    value = tdkTestObj.getResultDetails();
    hostEntries = value.split("VALUE:")[1].split(' ')[0];

    print("\nTEST STEP %d : Get the number of Host entries using Device.Hosts.HostNumberOfEntries" %step);
    print("EXPECTED RESULT %d : Should successfully retrieve Device.Hosts.HostNumberOfEntries" %step);

    if expectedresult in actualresult and hostEntries.isdigit():
        hostEntries = int(hostEntries);
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print("ACTUAL RESULT %d : Device.Hosts.HostNumberOfEntries : %d" %(step, hostEntries));
        print("[TEST EXECUTION RESULT] : SUCCESS");

        #Iterate through the host table and find the index for which Layer1Interface is Device.WiFi.SSID.1
        clientDetected = 0;
        for index in range(1, hostEntries + 1):
            print("\n**********For Host Table Entry %d**********" %index);
            #Get the value of Device.Hosts.Host.{i}.Layer1Interface
            step = step + 1;
            paramName = "Device.Hosts.Host." + str(index) + ".Layer1Interface"
            tdkTestObj.addParameter("paramName",paramName);
            #Execute the test case in DUT
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            value = tdkTestObj.getResultDetails();
            layer1Interface = value.split("VALUE:")[1].split(' ')[0];

            print("\nTEST STEP %d : Get the value of %s and check if it is Device.WiFi.SSID.1" %(step, paramName));
            print("EXPECTED RESULT %d : Should successfully retrieve %s" %(step, paramName));

            if expectedresult in actualresult and layer1Interface != "":
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d : %s : %s" %(step, paramName, layer1Interface));
                print("[TEST EXECUTION RESULT] : SUCCESS");

                if layer1Interface == "Device.WiFi.SSID.1":
                    clientDetected = 1;
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("Identified the Host Table Entry for connected client as : %d" %index);

                    #Check if the connected client is shown as active using Device.Hosts.Host.{i}.Active
                    step = step + 1;
                    paramName = "Device.Hosts.Host." + str(index) + ".Active"
                    tdkTestObj.addParameter("paramName",paramName);
                    #Execute the test case in DUT
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();
                    value = tdkTestObj.getResultDetails();
                    activeStatus = value.split("VALUE:")[1].split(' ')[0];

                    print("\nTEST STEP %d : Get the value of %s and check if it is true" %(step, paramName));
                    print("EXPECTED RESULT %d : Should successfully retrieve %s and it should be true" %(step, paramName));

                    if expectedresult in actualresult and activeStatus != "":
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("ACTUAL RESULT %d : %s : %s" %(step, paramName, activeStatus));
                        print("[TEST EXECUTION RESULT] : SUCCESS");

                        if activeStatus == "true":
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("Host is Active");
                            break;
                        else:
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("FAILURE");
                            print("Host is NOT Active");
                            break;
                    else:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print("ACTUAL RESULT %d : %s : %s" %(step, paramName, activeStatus));
                        print("[TEST EXECUTION RESULT] : FAILURE");
                        break;
                else:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("Host Table Entry for connected client is not %d" %index);
                    continue;
            else:
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT %d : %s : %s" %(step, paramName, layer1Interface));
                print("[TEST EXECUTION RESULT] : FAILURE");
                break;

        #Check if client connection is proper or not
        if clientDetected != 1:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print("\nNone of the Host Table entries show Device.WiFi.SSID.1 as Layer 1 Interface");
    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print("ACTUAL RESULT %d : Device.Hosts.HostNumberOfEntries : %d" %(step, hostEntries));
        print("[TEST EXECUTION RESULT] : FAILURE");

    obj.unloadModule("wifiagent");
else:
    print("Failed to load wifi agent module");
    obj.setLoadModuleStatus("FAILURE");
    print("Module loading failed");
