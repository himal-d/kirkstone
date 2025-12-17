##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2024 RDK Management
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
  <version>18</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_CellularManager_X_RDK_Enable_PersistenceOnReboot</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>CellularManager_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check "Device.Cellular.X_RDK_Enable" persistence across reboot.</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>10</execution_time>
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
    <test_case_id>TC_CellularManager_17</test_case_id>
    <test_objective>Check "Device.Cellular.X_RDK_Enable" persistence across reboot.
</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1. TDK agent should be running in the DUT and DUT should be online in TDK test manager.
2. Cellular Manager setup should be up and running.</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Device.Cellular.Interface.1.Enable
</input_parameters>
    <automation_approch>.</automation_approch>
    <expected_output>.</expected_output>
    <priority>High</priority>
    <test_stub_interface>.</test_stub_interface>
    <test_script>TS_CellularManager_X_RDK_EnablePersistenceOnReboot</test_script>
    <skipped>No</skipped>
    <release_version>M128</release_version>
    <remarks>None</remarks>
  </test_cases>
  <script_tags />
</xml>
'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
import time;
from time import sleep;

#Test component to be tested
sysobj = tdklib.TDKScriptingLibrary("sysutil","1");
obj = tdklib.TDKScriptingLibrary("tdkbtr181","1");

#IP and Port of box, No need to change,
#This will be replaced with corresponding DUT Ip and port while executing script
ip = <ipaddress>
port = <port>
sysobj.configureTestCase(ip,port,'TS_CellularManager_X_RDK_EnablePersistenceOnReboot');
obj.configureTestCase(ip,port,'TS_CellularManager_X_RDK_EnablePersistenceOnReboot');

#Get the result of connection with test component and DUT
loadmodulestatus_sys =sysobj.getLoadModuleResult();
loadmodulestatus =obj.getLoadModuleResult();
print ("[LIB LOAD STATUS]  :  %s" %loadmodulestatus_sys);
print ("[LIB LOAD STATUS]  :  %s" %loadmodulestatus);

print("Loading Cellular Manager module")
if "SUCCESS" in loadmodulestatus.upper() and loadmodulestatus_sys.upper():
    sysobj.setLoadModuleStatus("SUCCESS");
    obj.setLoadModuleStatus("SUCCESS");

    step = 1;
    tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
    tdkTestObj.addParameter("ParamName","Device.Cellular.X_RDK_Enable");
    expectedresult="SUCCESS";

    #Execute testcase in DUT
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    initialvalue = tdkTestObj.getResultDetails();
    print("TEST STEP %d: Get the Device.Cellular.X_RDK_Enable" %step);
    print("EXPECTED RESULT %d: Should get the Device.Cellular.X_RDK_Enable" %step);
    print("ACTUAL RESULT %d: Value is %s" %(step,initialvalue));

    if expectedresult in actualresult and initialvalue != "":
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");


        step = step + 1;
        setVal = "false";
        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Set');
        tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.Enable");
        tdkTestObj.addParameter("ParamValue",setVal);
        tdkTestObj.addParameter("Type","bool");
        expectedresult="SUCCESS";

        #Execute testcase in DUT
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        setvalue = tdkTestObj.getResultDetails();

        print("TEST STEP %d: Set the Device.Cellular.X_RDK_Enable" %step);
        print("EXPECTED RESULT %d: Should set the Device.Cellular.X_RDK_Enable as %s" %(step,setVal));
        print("ACTUAL RESULT %d: Value is %s" %(step,setvalue));

        if expectedresult in actualresult:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");

            #rebooting the device
            sysobj.initiateReboot();
            sleep(60);

            tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
            tdkTestObj.addParameter("ParamName","Device.Cellular.X_RDK_Enable");
            expectedresult="SUCCESS";

            step = step + 1;
            #Execute testcase in DUT
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            newvalue = tdkTestObj.getResultDetails();
            print("TEST STEP %d: Get the Device.Cellular.X_RDK_Enable after Reboot" %step);
            print("EXPECTED RESULT %d:  Should get the  Device.Cellular.X_RDK_Enable value " %step);
            print("ACTUAL RESULT %d: Value is %s" %(step,newvalue));

            if expectedresult in actualresult and newvalue != "":
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : SUCCESS");

                print("TEST STEP %d: Check persistence of Device.Cellular.X_RDK_Enable value after Reboot"%step);
                print("EXPECTED RESULT %d:  The value of Device.Cellular.X_RDK_Enable should persist after reboot"%step);
                print("ACTUAL RESULT %d: Value is %s" %(step,newvalue));

                #Check if the value persists after reboot
                if newvalue == setvalue :
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : SUCCESS");
                else:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");
            else:
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");
            #Reverting the value of Device.Cellular.X_RDK_Enable to initial one
            tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Set');
            tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.Enable");
            tdkTestObj.addParameter("ParamValue",initialvalue);
            tdkTestObj.addParameter("Type","bool");
            expectedresult="SUCCESS";

            #Execute testcase in DUT
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            setvalue = tdkTestObj.getResultDetails();
            print("Reverted the value of Device.Cellular.X_RDK_Enable to initial value");

        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");
    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");
    obj.unloadModule("tdkbtr181");
    sysobj.unloadModule("sysutil");
else:
    print("Failed to load module");
    sysobj.setLoadModuleStatus("FAILURE");
    obj.setLoadModuleStatus("FAILURE");
