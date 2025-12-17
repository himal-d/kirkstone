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
  <name>TS_WANMANAGER_CheckCPEInterfaceNameAndDisplayName</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>wanmanager_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To check the Wan Manager CPE Interfaces name and Display Name have the expected values</synopsis>
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
    <test_case_id>TC_WANMANAGER_03</test_case_id>
    <test_objective>This test case is to check the Wan Manager CPE Interfaces name and Display Name have the expected values</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script
3.Wan Manager should be enabled</pre_requisite>
    <api_or_interface_used>TDKB_TR181Stub</api_or_interface_used>
    <input_parameters>Device.X_RDK_WanManager.CPEInterfaceNumberOfEntries
Device.X_RDK_WanManager.CPEInterface.{i}.Name
Device.X_RDK_WanManager.CPEInterface.{i}.DisplayName
Device.X_RDK_WanManager.Interface.{i}.Name
Device.X_RDK_WanManager.Interface.{i}.DisplayName
</input_parameters>
    <automation_approch>1]Load the module
2] Get the number of CPE interfaces
3] Get the expected interface names and display names from utility file
4] Get the CPE interface Name and Display Name using TR181 parameters (V1/V2 DMLs whichever applicable) and check if the values retrieved are as expected
intrName - dsl0, eth3, veip0
disName  -  DSL,WANOE,GPON
4]Unload the module</automation_approch>
    <expected_output>CPE interface Name and Display Name should be associated with names as expected</expected_output>
    <priority>High</priority>
    <test_stub_interface>WAN_MANAGER</test_stub_interface>
    <test_script>TS_WANMANAGER_CheckCPEInterfaceNameAndDisplayName</test_script>
    <skipped>No</skipped>
    <release_version>M87</release_version>
    <remarks>None</remarks>
  </test_cases>
  <script_tags />
</xml>
'''

# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
from WanManager_Utility import *;
obj = tdklib.TDKScriptingLibrary("tdkbtr181","RDKB");
sysobj =tdklib.TDKScriptingLibrary("sysutil","RDKB");
#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WANMANAGER_CheckCPEInterfaceNameAndDisplayName');
sysobj.configureTestCase(ip,port,'TS_WANMANAGER_CheckCPEInterfaceNameAndDisplayName');

#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();
loadmodulestatus1 =sysobj.getLoadModuleResult();
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus) ;
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus1) ;
if "SUCCESS" in (loadmodulestatus.upper() and loadmodulestatus1.upper()) :
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    sysobj.setLoadModuleStatus("SUCCESS");

    expectedresult="SUCCESS";
    tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
    tdkTestObj.addParameter("ParamName","Device.X_RDK_WanManager.CPEInterfaceNumberOfEntries");
    #Execute the test case in DUT
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    if expectedresult in actualresult:
        noOfEntries = int(details);
        tdkTestObj.setResultStatus("SUCCESS");
        print("TEST STEP 1 :Get the number of CPE Interfaces");
        print("EXPECTED RESULT 1: Should get the no of CPE Interfaces");
        print("ACTUAL RESULT 1: The value received is :",noOfEntries);
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");

        tdkTestObj = sysobj.createTestStep('ExecuteCmd');
        command= "sh %s/tdk_utility.sh parseConfigFile DEVICETYPE" %TDK_PATH;
        expectedresult="SUCCESS";
        tdkTestObj.addParameter("command", command);
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        devicetype = tdkTestObj.getResultDetails().strip().replace("\\n","");

        if expectedresult in actualresult and devicetype != "":
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print("TEST STEP 2: Get the DEVICE TYPE")
            print("EXPECTED RESULT 2: Should get the device type");
            print("ACTUAL RESULT 2:Device type  %s" %devicetype);
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");

            if devicetype == "RPI":
                interName=intrName;
                dispName=disName
            else:
                interName=interfaceName;
                dispName=displayName;

            #Get the parameter name in line with the Wan Manager DML version enabled
            tdkTestObj = sysobj.createTestStep('ExecuteCmd');
            command= "sh %s/tdk_utility.sh parseConfigFile WANMANAGER_UNIFICATION_ENABLE" %TDK_PATH;
            expectedresult="SUCCESS";
            tdkTestObj.addParameter("command", command);
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            enableFlag = tdkTestObj.getResultDetails().strip().replace("\\n","");

            print("TEST STEP 3: Get the WANMANAGER_UNIFICATION_ENABLE from platform properties")
            print("EXPECTED RESULT 3: Should get the enable state of WANMANAGER_UNIFICATION_ENABLE");

            if expectedresult in actualresult and enableFlag != "":
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT 3: WANMANAGER_UNIFICATION_ENABLE : %s" %enableFlag);
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : SUCCESS");

                if enableFlag == "TRUE":
                    ParamNamePrefix = "Device.X_RDK_WanManager.Interface.";
                else:
                    ParamNamePrefix = "Device.X_RDK_WanManager.CPEInterface.";

                print("TEST STEP 4:Check if CPE interface name and display name are as expected");
                print("Expected CPE interface names is %s" %interName);
                print("Expected CPE display names is %s" %dispName);

                #Flag to check if retrieved values are as expected
                flag = 0;

                for interface in range(1, noOfEntries+1):
                    expectedresult="SUCCESS";
                    tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
                    ParamName = ParamNamePrefix + str(interface) + ".Name";
                    tdkTestObj.addParameter("ParamName", ParamName);
                    #Execute the test case in DUT
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails();

                    if expectedresult in actualresult and details == interName[interface - 1]:
                        flag =1;
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("%s is %s" %(ParamName,details));

                        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
                        ParamName = ParamNamePrefix + str(interface) + ".DisplayName";
                        tdkTestObj.addParameter("ParamName", ParamName);
                        #Execute the test case in DUT
                        tdkTestObj.executeTestCase(expectedresult);
                        actualresult = tdkTestObj.getResult();
                        details = tdkTestObj.getResultDetails();

                        if expectedresult in actualresult and details == dispName[interface - 1]:
                            flag = 1;
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("%s is %s which is the expected value" %(ParamName,details));
                        else:
                            flag = 0;
                            tdkTestObj.setResultStatus("FAILURE");
                            print("%s is NOT %s which is the expected value" %(ParamName,details));
                    else:
                        flag = 0;
                        tdkTestObj.setResultStatus("FAILURE");
                        print("The CPE interface name is %s which is not among the listed interface name" %details);

                # setting the script status
                if flag == 1:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT 4: Listed CPE interfaces have expected Display name and interafce name");
                    print("[TEST EXECUTION RESULT] : SUCCESS");
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT 4: Listed CPE interfaces does not have expected Display name and interafce name");
                    print("[TEST EXECUTION RESULT] : FAILURE");
            else:
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT 3: WANMANAGER_UNIFICATION_ENABLE not retrieved from platform properties");
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print("TEST STEP 2: Get the DEVICE TYPE")
            print("EXPECTED RESULT 2: Should get the device type");
            print("ACTUAL RESULT 2:Device type  %s" %devicetype);
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print("TEST STEP 1 :Get the number of CPE Interfaces");
        print("EXPECTED RESULT 1: Should get the no of CPE Interfaces");
        print("ACTUAL RESULT 1: The value received is :",noOfEntries);
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");

    obj.unloadModule("tdkbtr181");
    sysobj.unloadModule("sysutil");
else:
    print("Failed to load module");
    obj.setLoadModuleStatus("FAILURE");
    sysobj.setLoadModuleStatus("FAILURE");
