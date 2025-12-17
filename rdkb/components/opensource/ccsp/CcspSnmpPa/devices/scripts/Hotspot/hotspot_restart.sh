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




Restart_Hostapd () {


        ifconfig mon.wlan0 down
        ps -eaf | grep hostapd0 | grep -v grep | awk '{print $2}' | xargs kill -9
        ifconfig wlan0 down
        ifconfig wlan0_0 down

        ifconfig wlan0 up
        hostapd -B /nvram/hostapd0.conf
        ifconfig mon.wlan0 up
        ifconfig wlan0_0 up

        ps -eaf | grep hostapd0 | grep -v grep | awk '{print $2}' | xargs kill -9
        ifconfig wlan0 up
        hostapd -B /nvram/hostapd0.conf
        ifconfig mon.wlan0 up
        ifconfig wlan0_0 up
}

Hostapd_Restart () {
	
        ps -eaf | grep hostapd0 | grep -v grep | awk '{print $2}' | xargs kill -9
        ifconfig wlan0 up
        hostapd -B /nvram/hostapd0.conf
        ifconfig mon.wlan0 up
        ifconfig wlan0_0 up

}

HOTSPOT_ENABLE=`dmcli simu getv Device.DeviceInfo.X_COMCAST_COM_xfinitywifiEnable | grep value | cut -f3 -d : | cut -f2 -d" "`
echo "HOTSPOT_ENABLE = $HOTSPOT_ENABLE"
if [ "$HOTSPOT_ENABLE" = "true" ]; then
echo "CCSP-HOTSPOT-RESTART"
#Restart_Hostapd

################# Checking the Hostapd Status Again(due to wlan0_0 getting failure status) #########################

PUBLIC_INTERFACE_2G=`cat /nvram/hostapd4.conf | grep -w interface | head -1 | cut -d '=' -f2`
PUBLIC_INTERFACE_5G=`cat /nvram/hostapd5.conf | grep -w interface | head -1 | cut -d '=' -f2`
VIRTUAL_INTERFACE_2G=`cat /nvram/hostapd0.conf | grep -w bss | head -1 | cut -d '=' -f2`
DONGLE_INDENTIFICATION=`cat /nvram/hostapd0.conf | grep bss= | cut -c1`


/lib/rdk/handle_emu_gre.sh create
echo "CCSP-HOTSPOT IS SUCCESSFULLY RUNNING"
else
if [ "$DONGLE_INDENTIFICATION" == "#" ] ; then
	ifconfig $VIRTUAL_INTERFACE_2G down
	ifconfig $PUBLIC_INTERFACE_5G down
else
	ifconfig $PUBLIC_INTERFACE_2G down
	ifconfig $PUBLIC_INTERFACE_5G down
fi
fi

