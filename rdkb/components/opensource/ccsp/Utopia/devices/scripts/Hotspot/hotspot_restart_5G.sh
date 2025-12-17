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



INTERFACE_5G=`cat /nvram/hostapd1.conf | grep -w interface | head -1 | cut -d '=' -f2`

Restart_Hostapd () {

	ps -eaf | grep hostapd5 | grep -v grep | awk '{print $2}' | xargs kill -9
	sleep 2
	ps -eaf | grep hostapd1 | grep -v grep | awk '{print $2}' | xargs kill -9
	rmmod rtl8812au 88x2bu
	sleep 1
	modprobe rtl8812au
	sleep 1
	modprobe 88x2bu
	sleep 2 
        ifconfig $INTERFACE_5G down
        sleep 3
        ifconfig $INTERFACE_5G up
        hostapd -B /nvram/hostapd5.conf
	sleep 2
        hostapd -B /nvram/hostapd1.conf 

}

HOTSPOT_ENABLE=`dmcli simu getv Device.DeviceInfo.X_COMCAST_COM_xfinitywifiEnable | grep value | cut -f3 -d : | cut -f2 -d" "`

echo "HOTSPOT_ENABLE_5G = $HOTSPOT_ENABLE"

PUBLIC_INTERFACE_2G=`cat /nvram/hostapd4.conf | grep -w interface | head -1 | cut -d '=' -f2`
PUBLIC_INTERFACE_5G=`cat /nvram/hostapd5.conf | grep -w interface | head -1 | cut -d '=' -f2`
VIRTUAL_INTERFACE_2G=`cat /nvram/hostapd0.conf | grep -w bss | head -1 | cut -d '=' -f2`
DONGLE_INDENTIFICATION=`cat /nvram/hostapd0.conf | grep bss= | cut -c1`

if [ "$HOTSPOT_ENABLE" = "true" ]; then

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

