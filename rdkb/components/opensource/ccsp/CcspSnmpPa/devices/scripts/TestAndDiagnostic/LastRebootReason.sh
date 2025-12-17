#!/bin/sh
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
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



# Checking syseventd PID
        SYSEVENT_PID=`pidof syseventd`
        if [ "$SYSEVENT_PID" == "" ]
        then
                        echo "[RDKB_PROCESS_CRASHED] : syseventd is crashed, need to reboot the device in maintanance window."
			dmcli simu setv Device.DeviceInfo.X_RDKCENTRAL-COM_LastRebootReason string Sysevent_Crashed
			sleep 5
                	rebootDeviceNeeded=1
        fi


# Checking CcspCr PID
        CCSPCR_PID=`pidof CcspCrSsp`
        if [ "$CCSPCR_PID" == "" ]
        then
                        echo "[RDKB_PROCESS_CRASHED] : CcspCR is crashed, need to reboot the device in maintanance window."  
			psmcli nosubsys set dmsb.DeviceInfo.X_RDKCENTRAL-COM_LastRebootReason CR_Crashed
			sleep 5
                        rebootDeviceNeeded=1                                                                                    
        fi    

if [ "$rebootDeviceNeeded" == 1 ]
 then

	echo  "Emulator is going to Reboot Now"
	sleep 5
	reboot
fi

