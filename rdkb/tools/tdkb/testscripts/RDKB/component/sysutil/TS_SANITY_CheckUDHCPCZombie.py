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
  <version>1</version>
  <name>TS_SANITY_CheckUDHCPCZombie</name>
  <primitive_test_id/>
  <primitive_test_name>ExecuteCmd</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>To check if UDHCPC zombie process is running in the device.</synopsis>
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
    <test_case_id>TC_SYSUTIL_79</test_case_id>
    <test_objective>To check if UDHCPC zombie process is running in the device.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>ParamName: Device.DeviceInfo.UpTime</input_parameters>
    <automation_approch>1. Load the modules
2. Check the uptime using Device.DeviceInfo.UpTime
3. Check if UDHCPC zombie process is running in the DUT, if so, return failure.
4. If UDHCPC zombie process is not running in the device and the uptime of the device is greater than 5 minutes, reboot the DUT.
5. After bootup, check if UDHCPC zombie process is running in the device. If so, return failure
6. Unload the modules</automation_approch>
    <expected_output>UDHCPC zombie process should NOT be running in the device.</expected_output>
    <priority>High</priority>
    <test_stub_interface>sysutil</test_stub_interface>
    <test_script>TS_SANITY_CheckUDHCPCZombie</test_script>
    <skipped>No</skipped>
    <release_version>M117</release_version>
    <remarks/>
  </test_cases>
</xml>

'''
def udhcpczombie(obj, step):
    status = 0;
    print("\nTEST STEP %d: Check if UDHCPC zombie process is present" %step);
    print("EXPECTED RESULT %d: UDHCPC zombie process should not be present" %step);

    query="ps | grep \"\\[udhcpc\\]\"";
    print("query:%s" %query);
    tdkTestObj = obj.createTestStep('ExecuteCmd');
    actualresult, details = doSysutilExecuteCommand(tdkTestObj,query)

    if expectedresult in actualresult and details == "":
        tdkTestObj.setResultStatus("SUCCESS");
        print("ACTUAL RESULT %d : UDHCPC zombie process is not present" %(step));
        print("[TEST EXECUTION RESULT] : SUCCESS");
    else:
        status = 1;
        tdkTestObj.setResultStatus("FAILURE");
        print("ACTUAL RESULT %d: UDHCPC zombie process is present; %s" %(step, details));
        print("[TEST EXECUTION RESULT] : FAILURE");

    return status, tdkTestObj;


# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
from tdkutility import *;
from time import sleep;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("sysutil","1");
pamobj = tdklib.TDKScriptingLibrary("pam","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with corresponding DUT Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_SANITY_CheckUDHCPCZombie');
pamobj.configureTestCase(ip,port,'TS_SANITY_CheckUDHCPCZombie');

#Get the result of connection with test component and DUT
loadmodulestatus=obj.getLoadModuleResult();
loadmodulestatus1=pamobj.getLoadModuleResult();

if "SUCCESS" in loadmodulestatus.upper() and "SUCCESS" in loadmodulestatus1.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    pamobj.setLoadModuleStatus("SUCCESS");
    expectedresult="SUCCESS";

    #Get the uptime and check if it is greater than 300s(5 mins)
    tdkTestObj = pamobj.createTestStep('pam_GetParameterValues');
    tdkTestObj.addParameter("ParamName","Device.DeviceInfo.UpTime");
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();

    print("\nTEST STEP 1: Get the UpTime");
    print("EXPECTED RESULT 1: Should get the UpTime");

    if expectedresult in actualresult and details.isdigit():
        uptime = int(details);
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print("ACTUAL RESULT 1: UpTime is %d" %uptime);
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");

        #Check if UDHCPC process is in zombie state
        step = 2;
        status, tdkTestObj = udhcpczombie(obj, step);
        if status == 1:
            tdkTestObj.setResultStatus("FAILURE");
            print("UDHCPC zombie process found after an uptime of %ds" %uptime);
        else:
            tdkTestObj.setResultStatus("SUCCESS");
            print("UDHCPC zombie process NOT found after an uptime of %ds" %uptime);

        #check if UDHCPC is in zombie state after reboot if the uptime is greater than 5 mins
        if uptime >= 300 and status == 0:
            #Initiate a device reboot and check if any services are in activating state after devices comes up
            print("\n****DUT is going for a reboot and will be up after 360 seconds*****");
            pamobj.initiateReboot();
            sleep(360);
            step = 3;
            status, tdkTestObj = udhcpczombie(obj, step);
            if status == 1:
                tdkTestObj.setResultStatus("FAILURE");
                print("UDHCPC zombie process found after device boot-up");
            else:
                tdkTestObj.setResultStatus("SUCCESS");
                print("UDHCPC zombie process not found after device boot-up");
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print("ACTUAL RESULT 1: Failure in getting the UpTime. Details: %s" %details);
        print("[TEST EXECUTION RESULT] : FAILURE");

    obj.unloadModule("sysutil");
    pamobj.unloadModule("pam");
else:
    print("Failed to load the module");
    obj.setLoadModuleStatus("FAILURE");
    pamobj.setLoadModuleStatus("FAILURE");
