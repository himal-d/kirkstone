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
  <name>TS_WIFIAGENT_SetNeighboringAPPollingPeriod_HigherWithReportEnabled</name>
  <primitive_test_id/>
  <primitive_test_name>WIFIAgent_Set_Get</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>Check if setting the Neighboring AP Scan Report Polling Interval to a higher value than the current Polling Interval returns failure when Reports are enabled.</synopsis>
  <groups_id/>
  <execution_time>5</execution_time>
  <long_duration>false</long_duration>
  <advanced_script>false</advanced_script>
  <remarks/>
  <skip>false</skip>
  <box_types>
    <box_type>Broadband</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_WIFIAGENT_230</test_case_id>
    <test_objective>Check if setting the Neighboring AP Scan Report Polling Interval to a higher value than the current Polling Interval returns failure when Reports are enabled.</test_objective>
    <test_type>Negative</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>paramName: Device.X_RDKCENTRAL-COM_Report.NeighboringAP.PollingPeriod
paramValue: value from the list ["300","900","1800","3600","10800","21600","43200","86400"]
paramType: unsigned int
paramName: Device.X_RDKCENTRAL-COM_Report.NeighboringAP.Enabled
paramValue: true/false
paramType: boolean</input_parameters>
    <automation_approch>1. Load the wifiagent module
2. Get the initial values of Device.X_RDKCENTRAL-COM_Report.NeighboringAP.PollingPeriod and Device.X_RDKCENTRAL-COM_Report.NeighboringAP.Enabled
3. Check if Polling Period is from the expected list of ["300","900","1800","3600","10800","21600","43200","86400"]
4. If the Polling Period is the highest value, set to the lowest value and validate SET with GET after disabling the report enable state.
5. If report is not enabled, enable it.
6. Set the Polling Period to a value greater than the current value. The SET operation should fail.
7. Revert the polling period if required.
8. Revert the report enable if required.
9. Unload the module.</automation_approch>
    <expected_output>Setting the Neighboring AP Scan Report Polling Interval to a higher value than the current Polling Interval should return failure when Reports are enabled.</expected_output>
    <priority>High</priority>
    <test_stub_interface>wifiagent</test_stub_interface>
    <test_script>TS_WIFIAGENT_SetNeighboringAPPollingPeriod_HigherWithReportEnabled</test_script>
    <skipped>No</skipped>
    <release_version>M116</release_version>
    <remarks/>
  </test_cases>
  <script_tags/>
</xml>

'''
def getValues(obj, paramList):
    Values = [];
    status = 0;
    expectedresult = "SUCCESS";
    for param in paramList:
        tdkTestObj = obj.createTestStep("WIFIAgent_Get");
        tdkTestObj.addParameter("paramName",param)
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails().strip().replace("\\n", "");

        if expectedresult in actualresult and details != "":
            val = details.split("VALUE:")[1].split(" ")[0].strip();
            Values.append(val);
            print("\n%s : %s" %(param, val));

            if val != "":
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                continue;
            else:
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                status = 1;
                break;
        else :
            status = 1;
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print("%s : %s" %(param, details));
            break;

    return tdkTestObj, status, Values;

def setParameter(obj, param, setValue, type):
    expectedresult = "SUCCESS";
    status = 0;
    tdkTestObj = obj.createTestStep('WIFIAgent_Set_Get');
    tdkTestObj.addParameter("paramName",param);
    tdkTestObj.addParameter("paramValue",setValue);
    tdkTestObj.addParameter("paramType",type);
    #Execute the test case in DUT
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    return actualresult, details;

# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
from  time import sleep;
from tdkutility import *;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with corresponding DUT Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIAGENT_SetNeighboringAPPollingPeriod_HigherWithReportEnabled');

#Get the result of connection with test component and DUT
loadmodulestatus=obj.getLoadModuleResult();
print("[LIB LOAD STATUS]  :  %s" %loadmodulestatus) ;

if "SUCCESS" in loadmodulestatus.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    expectedresult="SUCCESS";

    #Get the initial values of Polling Interval and Report enable
    step = 1;
    paramList = ["Device.X_RDKCENTRAL-COM_Report.NeighboringAP.PollingPeriod", "Device.X_RDKCENTRAL-COM_Report.NeighboringAP.Enabled"];
    print("\nTEST STEP %d : Get the initial values of polling interval and report enable for the NeighboringAP Report" %step);
    print("EXPECTED RESULT %d : The initial values should be retrieved successfully" %step);

    tdkTestObj, status, initial_values = getValues(obj, paramList);

    if status == 0:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print("ACTUAL RESULT %d : The values retrieved are respectively : %s, %s" %(step, initial_values[0], initial_values[1])) ;
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : SUCCESS");

        #Polling value list
        valid_intervals = ["300","900","1800","3600","10800","21600","43200","86400"];
        print("\nThe Polling Interval should be from the list: ", valid_intervals);

        #Check if the Polling is from the expected value list
        if initial_values[0] in valid_intervals:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print("Polling interval is from the expected list of values");
            polling_index_initial = valid_intervals.index(initial_values[0]);
            #Higher polling value to be set
            polling_index_final = polling_index_initial + 1;

            #If Polling Interval is the highest value, set it to the lowest value initially and update the polling_index
            proceed_flag = 0;
            polling_revert = 0;
            if initial_values[0] == valid_intervals[-1]:
                new_polling = valid_intervals[0];
                step = step + 1;
                print("\nTEST STEP %d: Set Device.X_RDKCENTRAL-COM_Report.NeighboringAP.PollingPeriod to %s (lowest value) as initially it had the highest value" %(step, new_polling));
                print("EXPECTED RESULT %d : Device.X_RDKCENTRAL-COM_Report.NeighboringAP.PollingPeriod should be set to %s successfully" %(step, new_polling));

                actualresult, details = setParameter(obj, paramList[0], new_polling, "unsignedint");

                if expectedresult in actualresult:
                    proceed_flag = 1;
                    polling_revert = 1;
                    #Higher polling value to be set (initial_index 0 + 1)
                    polling_index_final = 1;
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d: Polling Period: %s" %(step,details));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : SUCCESS");
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT %d: Polling Period: %s" %(step,details));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");
            else:
                proceed_flag = 1;
                print("Device.X_RDKCENTRAL-COM_Report.NeighboringAP.PollingPeriod does not initially have the highest value")

            #Check if Reports are enabled if not enable it
            proceed_flag = 0;
            report_disabled = 0;
            if initial_values[1] != "true":
                step = step + 1;
                print("\nTEST STEP %d: Enable Device.X_RDKCENTRAL-COM_Report.NeighboringAP.Enabled" %(step));
                print("EXPECTED RESULT %d: Should enable Device.X_RDKCENTRAL-COM_Report.NeighboringAP.Enabled successfully" %(step));

                actualresult, details = setParameter(obj, paramList[1], "true", "boolean");

                if expectedresult in actualresult and details != "":
                    proceed_flag = 1;
                    report_disabled = 1;
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d: NeighboringAP Reports enabled; Details : %s" %(step,details));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : SUCCESS");
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT %d: NeighboringAP Reports; Details : %s" %(step,details));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");
            else:
                proceed_flag = 1;
                print("Device.X_RDKCENTRAL-COM_Report.NeighboringAP.Enabled is already enabled");

            if proceed_flag == 1:
                #Set the polling interval to higher value
                step = step + 1;
                new_polling = valid_intervals[polling_index_final];
                print("\nTEST STEP %d: Set Device.X_RDKCENTRAL-COM_Report.NeighboringAP.PollingPeriod to a higher value %s" %(step, new_polling));
                print("EXPECTED RESULT %d : Device.X_RDKCENTRAL-COM_Report.NeighboringAP.PollingPeriod should NOT be set to %s" %(step, new_polling));
                actualresult, details = setParameter(obj, paramList[0], new_polling, "unsignedint");
                expectedresult = "FAILURE";

                if expectedresult in actualresult:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d: Polling Period: %s" %(step,details));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : SUCCESS");
                else:
                    polling_revert = 1;
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT %d: Polling Period: %s" %(step,details));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print("Device.X_RDKCENTRAL-COM_Report.NeighboringAP.Enabled could not be enabled, cannot proceed...");

            #Disable report enable before reverting the polling period if required
            if polling_revert == 1:
                step = step + 1;
                print("\nTEST STEP %d: Disable Device.X_RDKCENTRAL-COM_Report.NeighboringAP.Enabled" %(step));
                print("EXPECTED RESULT %d: Should disable Device.X_RDKCENTRAL-COM_Report.NeighboringAP.Enabled successfully" %(step));

                actualresult, details = setParameter(obj, paramList[1], "false", "boolean");
                expectedresult = "SUCCESS";

                if expectedresult in actualresult and details != "":
                    tdkTestObj.setResultStatus("SUCCESS");
                    print("ACTUAL RESULT %d: NeighboringAP Reports disabled; Details : %s" %(step,details));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : SUCCESS");

                    #Revert to initial polling period
                    step = step + 1;
                    print("\nTEST STEP %d: Revert Device.X_RDKCENTRAL-COM_Report.NeighboringAP.PollingPeriod to %s" %(step, initial_values[0]));
                    print("EXPECTED RESULT %d : Device.X_RDKCENTRAL-COM_Report.NeighboringAP.PollingPeriod should be reverted to %s" %(step, initial_values[0]));
                    actualresult, details = setParameter(obj, paramList[0], initial_values[0], "unsignedint");
                    expectedresult = "SUCCESS";

                    if expectedresult in actualresult:
                        tdkTestObj.setResultStatus("SUCCESS");
                        print("ACTUAL RESULT %d: Polling Period: %s" %(step,details));
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : SUCCESS");
                    else:
                        tdkTestObj.setResultStatus("FAILURE");
                        print("ACTUAL RESULT %d: Polling Period: %s" %(step,details));
                        #Get the result of execution
                        print("[TEST EXECUTION RESULT] : FAILURE");
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print("ACTUAL RESULT %d: NeighboringAP Reports; Details : %s" %(step,details));
                    #Get the result of execution
                    print("[TEST EXECUTION RESULT] : FAILURE");
            else:
                print("Polling Period need not be reverted")
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print("Polling interval is NOT from the expected list of values");

        #Revert Report enable if required
        if initial_values[1] == "false":
            step = step + 1;
            print("\nTEST STEP %d: Revert Device.X_RDKCENTRAL-COM_Report.NeighboringAP.Enabled to false" %(step));
            print("EXPECTED RESULT %d: Should revert Device.X_RDKCENTRAL-COM_Report.NeighboringAP.Enabled to false" %(step));

            actualresult, details = setParameter(obj, paramList[1], "false", "boolean");
            expectedresult = "SUCCESS";

            if expectedresult in actualresult and details != "":
                tdkTestObj.setResultStatus("SUCCESS");
                print("ACTUAL RESULT %d: NeighboringAP Reports reverted; Details : %s" %(step,details));
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : SUCCESS");
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print("ACTUAL RESULT %d: NeighboringAP Reports; Details : %s" %(step,details));
                #Get the result of execution
                print("[TEST EXECUTION RESULT] : FAILURE");
        else:
            print("Report Enable state need not be reverted");
    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print("ACTUAL RESULT %d : The initial values are not retrieved successfully" %step);
        #Get the result of execution
        print("[TEST EXECUTION RESULT] : FAILURE");

    obj.unloadModule("wifiagent")
else:
    print("Failed to load module");
    obj.setLoadModuleStatus("FAILURE");
    print("Module loading failed");
