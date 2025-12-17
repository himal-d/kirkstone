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
  <version>9</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_WIFIHAL_5GHzSetRadioExtChannel_BWInvalid</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>WIFIHAL_GetOrSetParamStringValue</primitive_test_name>
  <!--  -->
  <primitive_test_version>8</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>This is a negative scenario which checks if setting the extension channel to a new value for 5G radio returns failure when the current 5G radio operating channel bandwidth is invalid for the extension channel set operations.</synopsis>
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
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_WIFIHAL_115</test_case_id>
    <test_objective>This is a negative scenario which checks if setting the extension channel to a new value for 5G radio returns failure when the current 5G radio operating channel bandwidth is invalid for the extension channel set operations.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>wifi_setRadioOperatingChannelBandwidth()
wifi_getRadioOperatingChannelBandwidth()
wifi_getRadioExtChannel()
wifi_setRadioExtChannel()</api_or_interface_used>
    <input_parameters>methodName   :   setRadioOperatingChannelBandwidth
methodName   :   getChannelBandwidth
methodName   :   setRadioExtChannel
methodName   :   getRadioExtChannel
radioIndex   :   5G radio index</input_parameters>
    <automation_approch>1. Load the wifihal module
2. Get the initial radio operating channel bandwidth using wifi_getRadioOperatingChannelBandwidth().
3. Check if the initial operating channel bandwidth is not from the extension channel bandwidth list ["40MHz"]. If not, set the operating channel bandwidth using wifi_setRadioOperatingChannelBandwidth() to 20MHz which does not support extension channels.
4. Validate the SET with GET API if required.
5. Get the initial extension channel using wifi_getRadioExtChannel() and check if they are from the possible list of values ['AboveControlChannel', 'BelowControlChannel', 'Auto'].
6. Set the extension channel to a new value using wifi_setRadioExtChannel(). The SET operation is expected to return failure as extension channel set operation is not supported by operating channel bandwidths other than 40MHz and 80MHz.
7. Revert the extension channel to initial value using wifi_setRadioExtChannel() if required.
8. Revert the operating channel bandwidth to initial value using wifi_setRadioOperatingChannelBandwidth() if required.
9. Unload the module.</automation_approch>
    <expected_output>Setting the extension channel to a new value for 5G radio should return failure when the current 5G radio operating channel bandwidth is invalid for the extension channel set operations.</expected_output>
    <priority>High</priority>
    <test_stub_interface>WIFIHAL</test_stub_interface>
    <test_script>TS_WIFIHAL_5GHzSetRadioExtChannel_BWInvalid</test_script>
    <skipped>No</skipped>
    <release_version></release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
from wifiUtility import *;
radio = "5G"

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifihal","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIHAL_5GHzSetRadioExtChannel_BWInvalid');

def setExtChannel(radioIndex):
    expectedresult = "SUCCESS";
    #Get the current extension channel and check if it is from the Possible Extension channels list
    tdkTestObj = obj.createTestStep("WIFIHAL_GetOrSetParamStringValue");
    tdkTestObj.addParameter("methodName","getRadioExtChannel");
    tdkTestObj.addParameter("radioIndex", radioIndex);
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();

    possibleExtChannels = ['AboveControlChannel', 'BelowControlChannel', 'Auto'];

    print("\nTEST STEP : Check if the initial Radio Extension Channel retrieved using wifi_getRadioExtChannel() is from the list ", possibleExtChannels);
    print("EXPECTED RESULT : wifi_getRadioExtChannel should successfully return the radio extension channel from ", possibleExtChannels);

    if expectedresult in actualresult and details != "":
        initGetExtCh = details.split(":")[1].strip();

        if initGetExtCh in possibleExtChannels:
            tdkTestObj.setResultStatus("SUCCESS");
            print("ACTUAL RESULT : Ext Channel value string received: %s"%initGetExtCh);
            print("[TEST EXECUTION RESULT] : SUCCESS");

            for setExtCh in possibleExtChannels:
                if initGetExtCh == setExtCh:
                    continue;
                else:
                    expectedresult = "FAILURE";
                    tdkTestObj = obj.createTestStep("WIFIHAL_GetOrSetParamStringValue");
                    tdkTestObj.addParameter("methodName","setRadioExtChannel");
                    tdkTestObj.addParameter("radioIndex", radioIndex);
                    tdkTestObj.addParameter("param",setExtCh);
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails();

                    print("\nTEST STEP : Check if setting the radio extension channel as %s returns failure when the current channel bandwidth is not applicable for extension channels" %setExtCh);
                    print("EXPECTED RESULT : Setting the radio extension channel should return FAILURE");

                    if expectedresult in actualresult:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("ACTUAL RESULT : Set operation failed; Details : %s " %details)
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : SUCCESS");
                    else:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print("ACTUAL RESULT : Set operation success; Details : %s " %details)
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : FAILURE");

                        #Reverting the extension channel
                        expectedresult = "SUCCESS";
                        tdkTestObj = obj.createTestStep("WIFIHAL_GetOrSetParamStringValue");
                        tdkTestObj.addParameter("methodName","setRadioExtChannel");
                        tdkTestObj.addParameter("radioIndex", radioIndex);
                        tdkTestObj.addParameter("param",initGetExtCh);
                        tdkTestObj.executeTestCase(expectedresult);
                        actualresult = tdkTestObj.getResult();
                        details = tdkTestObj.getResultDetails();

                        print("\nTEST STEP : Revert the extension channel to %s" %initGetExtCh);
                        print("EXPECTED RESULT : The extension channel should be reverted to the initial state successfully");

                        if expectedresult in actualresult:
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("ACTUAL RESULT : Extension channel is successfully reverted to initial value");
                            #Get the result of execution
                            print("[TEST EXECUTION RESULT] : SUCCESS");
                        else:
                            tdkTestObj.setResultStatus("FAILURE");
                            print("Unable to revert the extension channel to initial value");
                            #Get the result of execution
                            print("[TEST EXECUTION RESULT] : FAILURE");
                    break;
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print("ACTUAL RESULT : Ext Channel value string received: %s is not from possible extension channels list" %initGetExtCh);
            print("[TEST EXECUTION RESULT] : FAILURE");
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print("ACTUAL RESULT : Failed to get the current extension channel");
        print("[TEST EXECUTION RESULT] : FAILURE");
    return;

loadmodulestatus =obj.getLoadModuleResult();
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus)

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");
    expectedresult = "SUCCESS";
    #Get the radio Index
    tdkTestObjTemp, radioIndex = getIndex(obj, radio);

    ## Check if a invalid index is returned
    if radioIndex == -1:
        print("Failed to get radio index for radio %s\n" %radio);
        tdkTestObjTemp.setResultStatus("FAILURE");
    else:
        #Calling the method to execute wifi_getRadioOperatingChannelBandwidth() inorder to get the initial channel bandwidth
        tdkTestObj = obj.createTestStep("WIFIHAL_GetOrSetParamStringValue");
        tdkTestObj.addParameter("methodName","getChannelBandwidth");
        tdkTestObj.addParameter("radioIndex", radioIndex);
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();

        print("\nTEST STEP : Get the initial operating channel bandwidth")
        print("EXPECTED RESULT : Should successfully get the initial channel bandwidth")

        if expectedresult in actualresult and details != "":
            initBandwidth = details.split(":")[1].strip()
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print("ACTUAL RESULT : Initial channel bandwidth is: %s " %initBandwidth);
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : SUCCESS");

            #if channel bandwidth is from ["40MHz"], set the BW as 20MHz (which is invalid for extension channels) and then do the set extension channel
            if initBandwidth in ["40MHz"]:
                tdkTestObj = obj.createTestStep("WIFIHAL_GetOrSetParamStringValue");
                tdkTestObj.addParameter("methodName","setRadioOperatingChannelBandwidth");
                tdkTestObj.addParameter("radioIndex", radioIndex);
                tdkTestObj.addParameter("param","20MHz");
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                details = tdkTestObj.getResultDetails();

                print("\nTEST STEP : Set the operating channel bandwidth to 20MHz which is an invalid extension channel bandwidth")
                print("EXPECTED RESULT : Should successfully set the channel bandwidth to 20MHz")

                if expectedresult in actualresult :
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT : Set operation success; Details : %s " %details)
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : SUCCESS");

                    #Cross check SET with GET
                    tdkTestObj = obj.createTestStep("WIFIHAL_GetOrSetParamStringValue");
                    tdkTestObj.addParameter("methodName","getChannelBandwidth");
                    tdkTestObj.addParameter("radioIndex", radioIndex);
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails();

                    print("\nTEST STEP : Check if the current operating channel bandwidth is 20MHz")
                    print("EXPECTED RESULT : The current channel bandwidth should be retrieved as 20MHz")

                    if expectedresult in actualresult and details != "":
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("ACTUAL RESULT : Current channel bandwidth is: %s " %details)
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : SUCCESS");

                        bandWidth = details.split(":")[1].strip();
                        if bandWidth == "20MHz":
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("SUCCESS");
                            print("Channel Bandwidth is successfully set to 20MHz");

                            #Call the function to set extension channel
                            setExtChannel(radioIndex);

                            #Revert to initial channel bandwidth
                            tdkTestObj = obj.createTestStep("WIFIHAL_GetOrSetParamStringValue");
                            tdkTestObj.addParameter("methodName","setRadioOperatingChannelBandwidth");
                            tdkTestObj.addParameter("radioIndex", radioIndex);
                            tdkTestObj.addParameter("param",initBandwidth);
                            tdkTestObj.executeTestCase(expectedresult);
                            actualresult = tdkTestObj.getResult();
                            details = tdkTestObj.getResultDetails();

                            print("\nTEST STEP : Revert the operating channel bandwidth to ", initBandwidth);
                            print("EXPECTED RESULT : Should successfully revert the channel bandwidth to ", initBandwidth);

                            if expectedresult in actualresult :
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("SUCCESS");
                                print("ACTUAL RESULT : Revert operation success; Details: %s " %details)
                                #Get the result of execution
                                print("[TEST EXECUTION RESULT] : SUCCESS");
                            else :
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("FAILURE");
                                print("ACTUAL RESULT : Revert operation failed; Details: %s " %details)
                                #Get the result of execution
                                print("[TEST EXECUTION RESULT] : FAILURE");
                        else:
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("FAILURE");
                            print("Channel Bandwidth is NOT successfully set to 20MHz");
                    else:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print("ACTUAL RESULT : Current channel bandwidth is: %s " %details)
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : FAILURE");
                else:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT : Set operation failed; Details : %s " %details)
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");

            #if channel bandwidth is not from ["40MHz"], do the set extension channel directly
            else:
                setExtChannel(radioIndex);
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print("ACTUAL RESULT : Initial channel bandwidth is: %s " %details)
            #Get the result of execution
            print("[TEST EXECUTION RESULT] : FAILURE");

    obj.unloadModule("wifihal");
else:
    print("Failed to load wifi module");
    obj.setLoadModuleStatus("FAILURE");
