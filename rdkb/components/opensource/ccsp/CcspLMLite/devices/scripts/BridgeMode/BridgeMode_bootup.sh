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


sleep 20

BRIDGEMODE_ENABLE=`dmcli simu getv Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanMode | grep value | cut -f3 -d : | cut -f2 -d" "`
if [ "$BRIDGEMODE_ENABLE" = "bridge-static" ]; then
	INTERFACE_2G=`cat /nvram/hostapd0.conf | grep -w interface | head -1 | cut -d '=' -f2`
	INTERFCAE_5G=`cat /nvram/hostapd1.conf | grep -w interface | head -1 | cut -d '=' -f2`
	brctl delif brlan0 $INTERFACE_2G
	brctl delif brlan0 $INTERFCAE_5G
	ifconfig $INTERFACE_2G down
	ifconfig $INTERFCAE_5G down
	echo "0" > /tmp/Get2gssidEnable.txt
	echo "0" > /tmp/Get5gssidEnable.txt
	LAN_IP=`cat /var/dnsmasq_org.conf | grep dhcp-range | cut -d ',' -f1 | cut -d '=' -f2 | cut -d '.' -f1-3`
	ip addr add $LAN_IP.1/24 dev eth0
	ip addr add 192.168.100.1/24 dev eth0
	killall dnsmasq
#	killall CcspLMLite
else
	eth2_count=`ifconfig eth2 | grep eth2 | wc -l`
        if [ $eth2_count == 1 ]; then
                /sbin/udhcpc -ieth2 &
        fi
fi
