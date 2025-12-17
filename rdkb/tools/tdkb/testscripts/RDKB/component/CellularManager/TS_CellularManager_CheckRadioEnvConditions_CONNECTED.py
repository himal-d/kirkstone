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
  <version>12</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_CellularManager_CheckRadioEnvConditions_CONNECTED</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>CellularManager_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check if Device.Cellular.Interface.1.X_RDK_RadioEnvConditions is EXCELLENT/GOOD/FAIR/POOR matches the expected RSRP value Device.Cellular.Interface.1.RSRP when cellular manager status Device.Cellular.X_RDK_Status is CONNECTED or REGISTERED.</synopsis>
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
    <test_case_id>TC_CellularManager_7</test_case_id>
    <test_objective>Check if Device.Cellular.Interface.1.X_RDK_RadioEnvConditions is EXCELLENT/GOOD/FAIR/POOR matches the expected RSRP value Device.Cellular.Interface.1.RSRP when cellular manager status Device.Cellular.X_RDK_Status is CONNECTED or REGISTERED.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state.
2.TDK Agent should be in running state or invoke it through StartTdk.sh script.
3. Cellular manager should be UP and status should be CONNECTED.</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>ParamName : Device.Cellular.X_RDK_Status
ParamValue : CONNECTED
Type : string
ParamName : Device.Cellular.Interface.1.X_RDK_RadioEnvConditions
ParamValue : FAIR/EXCELLENT/POOR/GOOD
Type : string
ParamName : Device.Cellular.Interface.1.RSRP
ParamValue :
EXCELLENT : ( RSRP &gt; -85 )
GOOD:   (-85  &gt;=  RSRP &gt;  -95)
FAIR:   (-95  &gt;=  RSRP &gt;  -105)
POOR:    (-105 &gt;= RSRP &gt; -115)
Type : int</input_parameters>
    <automation_approch>1. Load the module.
2. Check if Device.Cellular.X_RDK_Status be CONNECTED.
3. Check if Device.Cellular.Interface.1.X_RDK_RadioEnvConditions be FAIR/EXCELLENT/POOR/GOOD.
4.Get the RSRP value Device.Cellular.Interface.1.RSRP.
5. Check if the RSRP value matches the respective RadioEnvConditions:
EXCELLENT : ( RSRP &gt; -85 )
GOOD:   (-85  &gt;=  RSRP &gt;  -95)
FAIR:   (-95  &gt;=  RSRP &gt;  -105)
POOR:    (-105 &gt;= RSRP &gt; -115)
6. Unload the module.</automation_approch>
    <expected_output>Device.Cellular.Interface.1.X_RDK_RadioEnvConditions  should be  EXCELLENT/GOOD/FAIR/POOR and should match the expected RSRP value Device.Cellular.Interface.1.RSRP when cellular manager status Device.Cellular.X_RDK_Status is CONNECTED or REGISTERED.</expected_output>
    <priority>High</priority>
    <test_stub_interface>CellularManager_DoNothing</test_stub_interface>
    <test_script>TS_CellularManager_CheckRadioEnvConditions_CONNECTED</test_script>
    <skipped>No</skipped>
    <release_version>M128</release_version>
    <remarks>None</remarks>
  </test_cases>
  <script_tags />
</xml>
'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("tdkbtr181","1");

#IP and Port of box, No need to change,
#This will be replaced with corresponding DUT Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_CelllularManager_GetRadioEnvConditions_CONNECTED');

#Get the result of connection with test component and DUT
result =obj.getLoadModuleResult();
print ("[LIB LOAD STATUS]  :  %s" %result);

if "SUCCESS" in result.upper():
    step = 1;
    obj.setLoadModuleStatus("SUCCESS");
    #Prmitive test case which associated to this Script
    tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
    tdkTestObj.addParameter("ParamName","Device.Cellular.X_RDK_Status");
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    status = tdkTestObj.getResultDetails();
    print("\nTEST STEP %d : Get the cellular manager status using Device.Cellular.X_RDK_Status" %step);
    print("EXPECTED RESULT %d : Should successfully get Device.Cellular.X_RDK_Status" %step);
    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS");
        print("ACTUAL RESULT %d: Get operation success; Details : %s" %(step,status));
        print("TEST EXECUTION RESULT :SUCCESS");

        step = step + 1;
        print("\nTEST STEP %d : Check if the cellular manager status as CONNECTED or REGISTERED" %step);
        print("EXPECTED RESULT %d : Should get the cellular manager status as CONNECTED or REGISTERED " %step);
        if status == "CONNECTED" or status == "REGISTERED":
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print("ACTUAL RESULT %d : %s" %(step,status));
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");

            #get the current Radio conditions and save it
            valid_conditions = {'EXCELLENT', 'GOOD', 'FAIR', 'POOR'};
            tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
            tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.X_RDK_RadioEnvConditions");
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            RadioEnvCondition = tdkTestObj.getResultDetails();

            step = step + 1;
            print("\nTEST STEP %d : Get the RadioEnvCondition using Device.Cellular.Interface.1.X_RDK_RadioEnvConditions" %step);
            print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.X_RDK_RadioEnvConditions" %step);
            if expectedresult in actualresult :
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d: Get operation success; Details : %s" %(step,RadioEnvCondition));
                print("TEST EXECUTION RESULT :SUCCESS");

                step = step + 1;
                print("TEST STEP %d: Get the valid RadioEnvConditions for CONNECTED or REGISTERED cellular manager status" %step);
                print("EXPECTED RESULT %d: Should get the valid RadioEnvConditions for CONNECTED or REGISTERED cellular manager status " %step);
                if RadioEnvCondition in valid_conditions:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d : %s" %(step,RadioEnvCondition));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : SUCCESS" );

                    tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
                    tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.RSRP");
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();
                    RSRP = tdkTestObj.getResultDetails();

                    step = step + 1;
                    print("TEST STEP %d: Get the RSRP value using Device.Cellular.Interface.1.RSRP" %step);
                    print("EXPECTED RESULT %d: Should get the RSRP value using Device.Cellular.Interface.1.RSRP" %step);
                    if expectedresult in actualresult :
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("ACTUAL RESULT %d: Get operation success; Details : %s" %(step,RSRP));
                        print("TEST EXECUTION RESULT :SUCCESS");

                        print("TEST STEP %d: Check if the RSRP value matches the respective RadioEnvConditions" %step);
                        print("EXPECTED RESULT %d: Should get the RSRP value that matches the respective RadioEnvConditions " %step);
                        if RadioEnvCondition == "EXCELLENT" and (int(RSRP) > -85) :
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("ACTUAL RESULT %d: RadioEnvConditions: %s matches RSRP : %s" %(step,RadioEnvCondition,RSRP));
                            print("TEST EXECUTION RESULT :SUCCESS");

                        elif RadioEnvCondition == "GOOD" and (-85  >=  int(RSRP) >  -95) :
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("ACTUAL RESULT %d: RadioEnvConditions: %s matches RSRP : %s" %(step,RadioEnvCondition,RSRP));
                            print("TEST EXECUTION RESULT :SUCCESS");

                        elif RadioEnvCondition == "FAIR" and (-95  >=  int(RSRP) >  -105) :
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("ACTUAL RESULT %d: RadioEnvConditions: %s matches RSRP : %s" %(step,RadioEnvCondition,RSRP));
                            print("TEST EXECUTION RESULT :SUCCESS");

                        elif RadioEnvCondition == "POOR" and (-105 >= int(RSRP) > -115) :
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("ACTUAL RESULT %d: RadioEnvConditions: %s matches RSRP : %s" %(step,RadioEnvCondition,RSRP));
                            print("TEST EXECUTION RESULT :SUCCESS");

                        else:
                            tdkTestObj.setResultStatus("FAILURE");
                            print("ACTUAL RESULT %d: RadioEnvConditions: %s is not matching expected RSRP range : %s" %(step,RadioEnvCondition,RSRP));
                            print("TEST EXECUTION RESULT :FAILURE");
                    else:
                        tdkTestObj.setResultStatus("FAILURE");
                        print("ACTUAL RESULT %d: Get operation failed; Details : %s" %(step,RSRP));
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : FAILURE")
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT %d:  %s " %(step,RadioEnvCondition));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT %d: Get operation failed; Details : %s" %(step,RadioEnvCondition));
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print("ACTUAL RESULT %d:  %s " %(step,status));
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print("ACTUAL RESULT %d: Get operation failed; Details : %s" %(step,status));
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");

    obj.unloadModule("tdkbtr181");
else:
    print("Failed to load the module");
    obj.setLoadModuleStatus("FAILURE");
    print("Module loading failed");
