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
<?xml version="1.0" encoding="UTF-8"?><xml>
  <id/>
  <version>1</version>
  <name>TS_PAM_DNSMasq_Lease</name>
  <primitive_test_id/>
  <primitive_test_name>pam_GetParameterValues</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>Verify dnsmasq.lease file after reboot</synopsis>
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
    <test_case_id>TC_PAM_248</test_case_id>
    <test_objective>Verify dnsmasq.lease file after reboot</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state
2.TDK Agent should be in running state or invoke it through StartTdk.sh script
3.Ensure that DUT has a LAN client connected</pre_requisite>
    <api_or_interface_used>none</api_or_interface_used>
    <input_parameters></input_parameters>
    <automation_approch>1.Load the module
2.Verify LAN client connectivity by checking Host Table entries
3.Check if there is a LAN connection by looping through connected devices
4.Get IP and MAC address of LAN client at identified index
5.Check if /nvram/dnsmasq.leases file exists and its details
6.Reboot the device
7.Verify LAN client connectivity after reboot by checking Host Table entries
8.Check if there is a LAN connection by looping through connected devices post-reboot
9.Get IP and MAC address of LAN client at identified index post-reboot
10.Check /nvram/dnsmasq.leases for LAN client details again after reboot
11.Verify if the details in the leases file are consistent with the obtained IP and MAC addresses
12.Unload the module</automation_approch>
    <expected_output>The IP and MAC address of connected clients should  reflect in  lease file before and after reboot</expected_output>
    <priority>High</priority>
    <test_stub_interface>PAM
    </test_stub_interface>
    <test_script>TS_PAM_DNSMasq_Lease</test_script>
    <skipped>No</skipped>
    <release_version>M129</release_version>
    <remarks>None</remarks>
  </test_cases>
</xml>
'''
# Use tdk library, which provides a wrapper for TDK test case script
import tdklib
from tdkutility import *
from time import sleep

# Test component to be tested
obj = tdklib.TDKScriptingLibrary("pam", "RDKB")
sysutil = tdklib.TDKScriptingLibrary("sysutil", "RDKB")

# IP and Port of box
ip = <ipaddress>
port = <port>

obj.configureTestCase(ip,port,'TS_PAM_DNSMasq_Lease')
sysutil.configureTestCase(ip,port,'TS_PAM_DNSMasq_Lease')

# Get the result of connection with test component
loadmodulestatus = obj.getLoadModuleResult()
sysutilmodulestatus = sysutil.getLoadModuleResult()

print(f"[LIB LOAD STATUS]  : {loadmodulestatus}")
print(f"[SYSUTIL LOAD STATUS]  : {sysutilmodulestatus}")

def pam_GetParameterValues(tdkTestObj, paramname):
    tdkTestObj.addParameter("ParamName", paramname)
    expectedresult = "SUCCESS"
    tdkTestObj.executeTestCase(expectedresult)
    actualresult = tdkTestObj.getResult()
    details = tdkTestObj.getResultDetails()
    return actualresult, details

if "SUCCESS" in loadmodulestatus.upper() and "SUCCESS" in sysutilmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS")
    sysutil.setLoadModuleStatus("SUCCESS")

    # Step 1: Verify LAN client connectivity by checking Host Table entries
    tdkTestObj = obj.createTestStep('pam_GetParameterValues')
    host_entries_result, host_entries_count = pam_GetParameterValues(tdkTestObj, "Device.Hosts.HostNumberOfEntries")

    print("TEST STEP 1: Verify LAN client connectivity by checking Host Table entries")
    print("EXPECTED RESULT 1: At least one LAN client should be connected")

    if "SUCCESS" in host_entries_result and host_entries_count.isdigit():
        print(f"ACTUAL RESULT 1: Host entries result is {host_entries_result}")
        tdkTestObj.setResultStatus("SUCCESS")
        print("[TEST EXECUTION RESULT] : SUCCESS")
        print(f"Total connected host entries: {host_entries_count}")
        host_entries_count = int(host_entries_count)
        if host_entries_count > 0:
            print("At least one device is connected.")
            print("TEST STEP 2: Check if there is a LAN connection by looping through connected devices")
            print("EXPECTED RESULT 2: Identify if any connected device is using Ethernet as the Layer1Interface")

        lan_connection_found = False  # Flag variable to track Ethernet connection
        for i in range(1, host_entries_count + 1):
            layer1_interface_param = f"Device.Hosts.Host.{i}.Layer1Interface"

            # Fetch Layer1Interface for the current host entry
            layer1_interface_result, layer1_interface_value = pam_GetParameterValues(tdkTestObj, layer1_interface_param)

            if "SUCCESS" in layer1_interface_result and layer1_interface_value:
                print(f"Checking Layer1Interface for Device.Hosts.Host.{i}: {layer1_interface_value}")

                # Check if the interface is Ethernet
                if "Ethernet" in layer1_interface_value:
                    lan_connection_found = True
                    print(f"ACTUAL RESULT 2: LAN connection found with Ethernet interface for Device.Hosts.Host.{i}")
                    tdkTestObj.setResultStatus("SUCCESS")
                    print("[TEST EXECUTION RESULT] : SUCCESS")
                    break  # Exit loop if Ethernet is found
                else:
                    print(f"Device.Hosts.Host.{i} is not using Ethernet, continuing to check other devices.")
            else:
                print(f"Failed to retrieve Layer1Interface for Device.Hosts.Host.{i}")
                tdkTestObj.setResultStatus("FAILURE")
                print("[TEST EXECUTION RESULT] : FAILURE")
        # Control flow based on the flag
        if lan_connection_found:
                    # Step 3: Get IP and MAC address of LAN client at identified index
                    ip_param = f"Device.Hosts.Host.{i}.IPAddress"
                    mac_param = f"Device.Hosts.Host.{i}.PhysAddress"
                    ip_result, ip_details = pam_GetParameterValues(tdkTestObj, ip_param)
                    mac_result, mac_details = pam_GetParameterValues(tdkTestObj, mac_param)

                    print(f"TEST STEP 3: Get IP and MAC address of LAN client at index {i}")
                    print("EXPECTED RESULT 3: Should successfully get IP and MAC address")
                    if "SUCCESS" in ip_result and "SUCCESS" in mac_result:
                        # Check if IP and MAC details are not empty
                        if ip_details and mac_details:
                            pre_reboot_ip = ip_details
                            pre_reboot_mac = mac_details
                            print(f"ACTUAL RESULT 3: IP Result = {ip_details}, MAC Result = {mac_details}")
                            print(f"Pre-Reboot IP Address: {pre_reboot_ip}")
                            print(f"Pre-Reboot MAC Address: {pre_reboot_mac}")
                            tdkTestObj.setResultStatus("SUCCESS")
                            print("[TEST EXECUTION RESULT] : SUCCESS")
                        else:
                            print("ACTUAL RESULT 3: IP address or MAC address is empty")
                            tdkTestObj.setResultStatus("FAILURE")
                            print("[TEST EXECUTION RESULT] : FAILURE")

                        # Step 4: Check if /nvram/dnsmasq.leases file exists and read the content of the file
                        tdkTestObj = sysutil.createTestStep('ExecuteCmd')
                        file_name = "/nvram/dnsmasq.leases"
                        print("TEST STEP 4: Check if /nvram/dnsmasq.leases file exists")
                        print("EXPECTED RESULT 4: /nvram/dnsmasq.leases file should exist")
                        file_exist_result = isFilePresent(tdkTestObj, file_name)

                        if "SUCCESS" in file_exist_result:
                            # Now, read the content of the file
                            print("lease file exists")
                            cmd = f"cat {file_name}"
                            leases_result, leases_details = doSysutilExecuteCommand(tdkTestObj, cmd)
                            if "SUCCESS" in leases_result:
                                print(f"ACTUAL RESULT 4: dnsmasq.leases file exists. Details: {leases_details}")
                                tdkTestObj.setResultStatus("SUCCESS")
                                print("[TEST EXECUTION RESULT] : SUCCESS")
                            else:
                                print("ACTUAL RESULT 4: Failed to read the content of /nvram/dnsmasq.leases")
                                tdkTestObj.setResultStatus("FAILURE")
                                print("[TEST EXECUTION RESULT] : FAILURE")

                            # Step 5: Reboot the device
                            print("TEST STEP 5: Reboot the device")
                            obj.initiateReboot()
                            sleep(300)

                            # Step 6: Verify LAN client connectivity after reboot by checking Host Table entries
                            tdkTestObj = obj.createTestStep('pam_GetParameterValues')
                            host_entries_result, host_entries_count = pam_GetParameterValues(tdkTestObj, "Device.Hosts.HostNumberOfEntries")
                            print("TEST STEP 6: Verify LAN client connectivity after reboot by checking Host Table entries")
                            print("EXPECTED RESULT 6: At least one LAN client should be connected after reboot")
                            print(f"Total connected host entries after reboot: {host_entries_count}")

                            if "SUCCESS" in host_entries_result and host_entries_count.isdigit():
                                print(f"ACTUAL RESULT 6: Host entries result is {host_entries_result}")
                                tdkTestObj.setResultStatus("SUCCESS")
                                print("[TEST EXECUTION RESULT] : SUCCESS")
                                host_entries_count = int(host_entries_count)
                                if host_entries_count > 0:
                                    print("At least one device is connected after reboot.")
                                    lan_connection_found_post_reboot = False  # Flag variable for post-reboot Ethernet connection
                                    print("TEST STEP 7: Check if there is a LAN connection by looping through connected devices post reboot")
                                    print("EXPECTED RESULT 7: Identify if any connected device is using Ethernet as the Layer1Interface post reboot")
                                    for i in range(1, host_entries_count + 1):
                                            layer1_interface_param = f"Device.Hosts.Host.{i}.Layer1Interface"
                                            # Fetch Layer1Interface for the current host entry
                                            layer1_interface_result, layer1_interface_value = pam_GetParameterValues(tdkTestObj, layer1_interface_param)
                                            if "SUCCESS" in layer1_interface_result and layer1_interface_value:
                                                print(f"Checking Layer1Interface for Device.Hosts.Host.{i} post-reboot: {layer1_interface_value}")
                                                # Check if the interface is Ethernet
                                                if "Ethernet" in layer1_interface_value:
                                                    lan_connection_found_post_reboot = True
                                                    print(f"ACTUAL RESULT 7: LAN connection found with Ethernet interface for Device.Hosts.Host.{i} post-reboot")
                                                    tdkTestObj.setResultStatus("SUCCESS")
                                                    print("[TEST EXECUTION RESULT] : SUCCESS")
                                                    break  # Exit loop if Ethernet is found
                                                else:
                                                    print(f"Device.Hosts.Host.{i} is not using Ethernet post-reboot, continuing to check other devices.")
                                            else:
                                                print(f"ACTUAL RESULT 7: Failed to retrieve Layer1Interface for Device.Hosts.Host.{i} post-reboot")
                                                tdkTestObj.setResultStatus("FAILURE")
                                                print("[TEST EXECUTION RESULT] : FAILURE")
                                    # Control flow based on the post-reboot flag
                                    if lan_connection_found_post_reboot:
                                            print(f"TEST STEP 8: Get IP and MAC address of LAN client at index {i} post-reboot")
                                            print("EXPECTED RESULT 8: Should successfully get IP and MAC address post-reboot")

                                            if "SUCCESS" in ip_result and "SUCCESS" in mac_result:
                                                # Check if IP and MAC details are not empty
                                                if ip_details and mac_details:
                                                    post_reboot_ip = ip_details
                                                    post_reboot_mac = mac_details
                                                    print(f"ACTUAL RESULT 8: IP Result = {ip_details}, MAC Result = {mac_details}")
                                                    print(f"Post-Reboot IP Address: {post_reboot_ip}")
                                                    print(f"Post-Reboot MAC Address: {post_reboot_mac}")
                                                    tdkTestObj.setResultStatus("SUCCESS")
                                                    print("[TEST EXECUTION RESULT] : SUCCESS")
                                                else:
                                                    print("ACTUAL RESULT 8: IP address or MAC address is empty")
                                                    tdkTestObj.setResultStatus("FAILURE")
                                                    print("[TEST EXECUTION RESULT] : FAILURE")

                                                # Step 9: Check /nvram/dnsmasq.leases for LAN client details again after reboot
                                                tdkTestObj = sysutil.createTestStep('ExecuteCmd')
                                                file_name = "/nvram/dnsmasq.leases"
                                                print("TEST STEP 9: /nvram/dnsmasq.leases file should exist post-reboot")
                                                file_exist_result = isFilePresent(tdkTestObj, file_name)
                                                print("EXPECTED RESULT 9: /nvram/dnsmasq.leases file exists post-reboot")
                                                if "SUCCESS" in file_exist_result:
                                                    print("dnsmasq.leases file exists post reboot")
                                                    # Now, read the content of the file
                                                    cmd = f"cat {file_name}"
                                                    leases_result, leases_details = doSysutilExecuteCommand(tdkTestObj, cmd)
                                                    if "SUCCESS" in leases_result:
                                                        print(f"ACTUAL RESULT 9: dnsmasq.leases file exists. Details: {leases_details}")
                                                        tdkTestObj.setResultStatus("SUCCESS")
                                                        print("[TEST EXECUTION RESULT] : SUCCESS")
                                                        # Verify if the details in the leases file are consistent with the obtained IP and MAC addresses
                                                        print("TEST STEP 10: Verify if the details in the leases file are consistent with the obtained IP and MAC addresses")
                                                        print("EXPECTED RESULT 10: Details in the lease file should be consistent with the obtained IP and MAC addresses")
                                                        if post_reboot_ip in leases_details and post_reboot_mac in leases_details:
                                                            print("ACTUAL RESULT 10: Verification successful: IP and MAC address match the details in dnsmasq.leases file")
                                                            tdkTestObj.setResultStatus("SUCCESS")
                                                            print("[TEST EXECUTION RESULT] : SUCCESS")
                                                        else:
                                                            print("ACTUAL RESULT 10: Verification failed: IP and MAC address do not match the details in dnsmasq.leases file")
                                                            tdkTestObj.setResultStatus("FAILURE")
                                                            print("[TEST EXECUTION RESULT] : FAILURE")
                                                    else:
                                                        print("ACTUAL RESULT 9: Failed to read the content of dnsmasq.leases")
                                                        tdkTestObj.setResultStatus("FAILURE")
                                                        print("[TEST EXECUTION RESULT] : FAILURE")
                                                else:
                                                    print("ACTUAL RESULT 9: Failed to read the dnsmasq.leases file after reboot")
                                                    tdkTestObj.setResultStatus("FAILURE")
                                                    print("[TEST EXECUTION RESULT] : FAILURE")
                                            else:
                                                print(f"ACTUAL RESULT 8: Device {i} is not connected via Ethernet post-reboot. Layer1Interface: {layer1_interface}")
                                                tdkTestObj.setResultStatus("FAILURE")
                                                print("[TEST EXECUTION RESULT] : FAILURE")
                                    else:
                                        print("No Lan Connection Found post reboot")
                                        tdkTestObj.setResultStatus("FAILURE")
                                        print("[TEST EXECUTION RESULT] : FAILURE")
                                else:
                                    print("ACTUAL RESULT 6: No LAN client is connected after reboot.")
                                    tdkTestObj.setResultStatus("FAILURE")
                                    print("[TEST EXECUTION RESULT] : FAILURE")
                            else:
                                print("ACTUAL RESULT 6: Failed to get number of host entries")
                                tdkTestObj.setResultStatus("FAILURE")
                                print("[TEST EXECUTION RESULT] : FAILURE")
                        else:
                            print("ACTUAL RESULT 4: dnsmasq.leases file does not exists")
                            tdkTestObj.setResultStatus("FAILURE")
                            print("[TEST EXECUTION RESULT] : FAILURE")
                    else:
                        print(f"ACTUAL RESULT 3: Failed to get IP and Maq of the LAN client")
                        tdkTestObj.setResultStatus("FAILURE")
                        print("[TEST EXECUTION RESULT] : FAILURE")
        else:
            print("No Lan Connection found")
            tdkTestObj.setResultStatus("FAILURE")
            print("[TEST EXECUTION RESULT] : FAILURE")
    else:
        print("ACTUAL RESULT 1: Failed to get the number of host entries.")
        tdkTestObj.setResultStatus("FAILURE")
        print("[TEST EXECUTION RESULT] : FAILURE")
    # Unload the module
    obj.unloadModule("pam")
    sysutil.unloadModule("sysutil")
else:
    print("Failed to load the pam or sysutil module")
    obj.setLoadModuleStatus("FAILURE")
    sysutil.setLoadModuleStatus("FAILURE")
    print("[TEST EXECUTION RESULT] : FAILURE")
