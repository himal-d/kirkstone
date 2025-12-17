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
  <version>8</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_CellularManager_GetStatistics_DEREGISTERED</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>CellularManager_DoNothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check if statistics Bytesent and ByteReceived are zero when cellular manager status is "DEREGISTERED".</synopsis>
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
    <test_case_id>TC_CellularManager_12</test_case_id>
    <test_objective>Check if statistics Bytesent and ByteReceived are zero when cellular manager status is "DEREGISTERED".</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state.
2.TDK Agent should be in running state or invoke it through StartTdk.sh script.
3. Cellular manager should be UP and status should be CONNECTED.</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>ParamName : Device.Cellular.X_RDK_Status
ParamValue : CONNECTED
Type : string
ParamName : Device.Cellular.Interface.1.Enable
ParamValue : false
Type : bool
ParamName : Device.Cellular.X_RDK_Status
ParamValue : DEREGISTERED
Type : string
ParamName : Device.Cellular.Interface.1.X_RDK_Statistics.BytesSent
ParamValue : 0
Type : int
ParamName : Device.Cellular.Interface.1.X_RDK_Statistics.BytesReceived
ParamValue : 0
Type : int</input_parameters>
    <automation_approch>1. Load tdkbtr181 the module.
2. Check if Device.Cellular.X_RDK_Status be CONNECTED.
3. Set Device.Cellular.Interface.1.Enable to false.
4. Check if Device.Cellular.X_RDK_Status be DEREGISTERED.
5. Check if Device.Cellular.Interface.1.X_RDK_Statistics.BytesSent be zero.
6. Check if Device.Cellular.Interface.1.X_RDK_Statistics.BytesReceived be zero.
7. Unload the tdkbtr181 module.</automation_approch>
    <expected_output>statistics Bytesent and ByteReceived are zero when cellular manager status is "DEREGISTERED".</expected_output>
    <priority>High</priority>
    <test_stub_interface>tdkbtr181</test_stub_interface>
    <test_script>TS_CellularManager_GetStatistics_DEREGISTERED</test_script>
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
obj.configureTestCase(ip,port,'TS_CellularManager_GetStatistics_DEREGISTERED');

#Get the result of connection with test component and DUT
result =obj.getLoadModuleResult();
print ("[LIB LOAD STATUS]  :  %s" %result);

if "SUCCESS" in result.upper():
    step = 1;
    flag = 0;
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

        step = step + 1 ;
        print("\nTEST STEP %d : Check if cellular manager status using Device.Cellular.X_RDK_Status is CONNECTED as per prerequisite" %step);
        print("EXPECTED RESULT %d : Should successfully get Device.Cellular.X_RDK_Status as CONNECTED" %step);
        if status != "DEREGISTERED" :
            tdkTestObj.setResultStatus("SUCCESS");
            print("ACTUAL RESULT %d : %s" %(step,status));
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");

            tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Set')
            tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.Enable");
            tdkTestObj.addParameter("ParamValue","false");
            tdkTestObj.addParameter("Type","bool");
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            interfaceEnable = tdkTestObj.getResultDetails();

            step = step + 1;
            print("\nTEST STEP %d : Set Device.Cellular.Interface.1.Enable to false" %step);
            print("EXPECTED RESULT %d : Should successfully set Device.Cellular.Interface.1.Enable to false" %step);
            if expectedresult in actualresult :
                flag = 1;
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d: Set operation success; Details : %s" %(step,interfaceEnable));
                print("TEST EXECUTION RESULT :SUCCESS");

                obj.setLoadModuleStatus("SUCCESS");
                #Prmitive test case which associated to this Script
                tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
                tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.Enable");
                expectedresult="SUCCESS";
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                enable = tdkTestObj.getResultDetails();
                step = step + 1;
                print("\nTEST STEP %d : Check if Device.Cellular.Interface.1.Enable is false" %step);
                print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.Enable as false" %step);
                if expectedresult in actualresult and enable == 'false':
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d: Get operation success; Device.Cellular.Interface.1.Enable : %s" %(step,enable));
                    print("TEST EXECUTION RESULT :SUCCESS");

                    step = step + 1;
                    obj.setLoadModuleStatus("SUCCESS");
                    #Prmitive test case which associated to this Script
                    tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
                    tdkTestObj.addParameter("ParamName","Device.Cellular.X_RDK_Status");
                    expectedresult="SUCCESS";
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();
                    newstatus = tdkTestObj.getResultDetails();
                    print("\nTEST STEP %d : Get the cellular manager status using Device.Cellular.X_RDK_Status" %step);
                    print("EXPECTED RESULT %d : Should successfully get Device.Cellular.X_RDK_Status" %step);
                    if expectedresult in actualresult and newstatus == "DEREGISTERED":
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("ACTUAL RESULT %d: Get operation success and Status is : %s" %(step,newstatus));
                        print("TEST EXECUTION RESULT :SUCCESS");

                        step = step + 1;
                        obj.setLoadModuleStatus("SUCCESS");
                        #Prmitive test case which associated to this Script
                        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
                        tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.X_RDK_Statistics.BytesSent");
                        expectedresult="SUCCESS";
                        tdkTestObj.executeTestCase(expectedresult);
                        actualresult = tdkTestObj.getResult();
                        bytesSent = tdkTestObj.getResultDetails();
                        print("\nTEST STEP %d : Get Byte sent statistics using Device.Cellular.Interface.1.X_RDK_Statistics.BytesSent" %step);
                        print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.X_RDK_Statistics.BytesSent" %step);
                        if expectedresult in actualresult:
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("ACTUAL RESULT %d: Get operation success and Details : %s" %(step,bytesSent));
                            print("TEST EXECUTION RESULT :SUCCESS");

                            step = step + 1;
                            print("\nTEST STEP %d : Check if Byte sent statistics using Device.Cellular.Interface.1.X_RDK_Statistics.BytesSent is zero" %step);
                            print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.X_RDK_Statistics.BytesSent as zero" %step);
                            if int(bytesSent) == 0 :
                                tdkTestObj.setResultStatus("SUCCESS");
                                print("ACTUAL RESULT %d: Device.Cellular.Interface.1.X_RDK_Statistics.BytesSent : %s" %(step,bytesSent));
                                print("TEST EXECUTION RESULT :SUCCESS");
                            else:
                                tdkTestObj.setResultStatus("FAILURE");
                                print("ACTUAL RESULT %d: Device.Cellular.Interface.1.X_RDK_Statistics.BytesSent : %s" %(step,bytesSent));
                                #Get the result of execution
                                print("[TEST EXECUTION RESULT] : FAILURE");
                        else:
                            tdkTestObj.setResultStatus("FAILURE");
                            print("ACTUAL RESULT %d: Get operation failed; Details : %s" %(step,bytesSent));
                            #Get the result of execution
                            print("[TEST EXECUTION RESULT] : FAILURE");

                        obj.setLoadModuleStatus("SUCCESS");
                        #Prmitive test case which associated to this Script
                        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Get');
                        tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.X_RDK_Statistics.BytesReceived");
                        expectedresult="SUCCESS";
                        tdkTestObj.executeTestCase(expectedresult);
                        actualresult = tdkTestObj.getResult();
                        bytesReceived = tdkTestObj.getResultDetails();
                        print("\nTEST STEP %d : Get Byte sent statistics using Device.Cellular.Interface.1.X_RDK_Statistics.BytesReceived" %step);
                        print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.X_RDK_Statistics.BytesReceived" %step);
                        if expectedresult in actualresult:
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("ACTUAL RESULT %d: Get operation success and Details : %s" %(step,bytesReceived));
                            print("TEST EXECUTION RESULT :SUCCESS");

                            step = step + 1;
                            print("\nTEST STEP %d : Check if Byte sent statistics using Device.Cellular.Interface.1.X_RDK_Statistics.BytesReceived is zero" %step);
                            print("EXPECTED RESULT %d : Should successfully get Device.Cellular.Interface.1.X_RDK_Statistics.BytesReceived as zero" %step);
                            if int(bytesReceived) == 0 :
                                tdkTestObj.setResultStatus("SUCCESS");
                                print("ACTUAL RESULT %d: Device.Cellular.Interface.1.X_RDK_Statistics.BytesReceived : %s" %(step,bytesReceived));
                                print("TEST EXECUTION RESULT :SUCCESS");
                            else:
                                tdkTestObj.setResultStatus("FAILURE");
                                print("ACTUAL RESULT %d: Device.Cellular.Interface.1.X_RDK_Statistics.BytesReceived : %s" %(step,bytesReceived));
                                #Get the result of execution
                                print("[TEST EXECUTION RESULT] : FAILURE");
                        else:
                            tdkTestObj.setResultStatus("FAILURE");
                            print("ACTUAL RESULT %d: Get operation failed; Details : %s" %(step,bytesReceived));
                            #Get the result of execution
                            print("[TEST EXECUTION RESULT] : FAILURE");
                    else:
                        tdkTestObj.setResultStatus("FAILURE");
                        print("ACTUAL RESULT %d: Get operation failed; Details : %s" %(step,newstatus));
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : FAILURE");
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT %d: Get operation failed; Details : %s" %(step,enable));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT %d: Set operation failed; Details : %s" %(step,interfaceEnable));
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print("ACTUAL RESULT %d : %s" %(step,status));
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");
    else :
        tdkTestObj.setResultStatus("FAILURE");
        print("ACTUAL RESULT %d: Get operation failed; Details : %s" %(step,status));
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");

    #Revert to original values
    if flag == 1 :
        step = step + 1;
        tdkTestObj = obj.createTestStep('TDKB_TR181Stub_Set')
        tdkTestObj.addParameter("ParamName","Device.Cellular.Interface.1.Enable");
        tdkTestObj.addParameter("ParamValue","true");
        tdkTestObj.addParameter("Type","bool");
        expectedresult="SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
        print("TEST STEP %d: Revert Device.Cellular.Interface.1.Enable same as previous status" %step);
        print("EXPECTED RESULT %d: Should revert Device.Cellular.Interface.1.Enable same as previous status" %step);
        if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d: Device.Cellular.Interface.1.Enable revert is success" %step);
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : SUCCESS");
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print("ACTUAL RESULT %d:Device.Cellular.Interface.1.Enable revert failed" %step);
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");
    obj.unloadModule("tdkbtr181");
else:
    print("Failed to load the module");
    obj.setLoadModuleStatus("FAILURE");
