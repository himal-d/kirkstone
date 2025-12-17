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

########### Creating Bridge #####################################
brctl addbr brlan0
WAN_IP=`route -n | grep UG | tr -s ' ' | cut -d ' ' -f2`

########## Adding Route to WAN Interface(eth0) ####################
route del default gw $WAN_IP          
route add default gw $WAN_IP eth0


######### Killing udhcpc for eth1 and brlan0 ########################
ps -eaf | grep ieth1 | grep -v grep | awk '{print $2}' | xargs kill -9
sleep 5
ps -eaf | grep ibrlan0 | grep -v grep | awk '{print $2}' | xargs kill -9

#################### Adding two more IP Address to eth0 Interface ########

LAN_IP=`cat /var/dnsmasq_org.conf | grep dhcp-range | cut -d ',' -f1 | cut -d '=' -f2 | cut -d '.' -f1-3`
ip addr add $LAN_IP.1/24 dev eth0
ip addr add 192.168.100.1/24 dev eth0

######################## Adding physical and WAN Interfaces to Bridge #########
ifconfig eth2 0.0.0.0
brctl addif brlan0 eth2
brctl addif brlan0 eth1


####################### FORWARDING TRAFFIC to eth0 INTERFACE ##########
WAN_MAC=`ifconfig eth0|grep HWaddr|awk '{print $5}'| tr '[a-z]' '[A-Z]'`
ebtables -t nat -I PREROUTING -i eth1 -p IPv4 --ip-dst $LAN_IP.1 -j dnat --to-dst $WAN_MAC --dnat-target ACCEPT
ebtables -t nat -A PREROUTING -i eth1 -p IPv4 --ip-dst 192.168.100.1 -j dnat --to-dst $WAN_MAC --dnat-target ACCEPT

################### Getting wlan0_0 mac Address(public wifi) #############
#sh /lib/rdk/Getting_wlan0_0_mac.sh wlan0

############################ iptables-restore ########################     
iptables-restore < /etc/iptables/rules.v4 

###################### Routing Table ##################################
#sh /lib/rdk/webgui.sh

###############################CcspTR069pa#########################
touch /var/tmp/tr069paready         
cp /version.txt /fss/gw/version.txt

############################## Webpa Component ################################

brctl addbr br0
ifconfig br0 up
sleep 2
ifconfig br0 192.168.101.3 up

WEBPA_FILE="/etc/webpa_cfg.json"
if [ -f "$WEBPA_FILE" ]; then
        echo "webpa_cfg.json file exists"
        cp -fr /etc/webpa_cfg.json /nvram/webpa_cfg.json
        sed -i 's/erouter0/eth0/g'  /nvram/webpa_cfg.json
fi

DEVICE_PROPERTIES_FILE="/etc/device.properties"
if [ -f "$DEVICE_PROPERTIES_FILE" ]; then
        echo "device.properties file exists"
        WEBPA_COUNT=`cat /etc/device.properties | grep ATOM_INTERFACE | wc -l`
        if [ $WEBPA_COUNT == 0 ]; then
        echo "ATOM_INTERFACE="br0"" >> /etc/device.properties
        echo "ATOM_INTERFACE_IP=192.168.101.3" >> /etc/device.properties
        echo "PARODUS_URL=tcp://127.0.0.1:6666" >> /etc/device.properties
        fi
fi

################################ Driver Module Support for TP-Link ###############################


Driver_Count=`lsmod | grep rtl8812au | wc -l`
	if [ $Driver_Count == 0 ]; then
		modprobe rtl8812au
	fi

Driver_Count=`lsmod | grep 88x2bu | wc -l`
	if [ $Driver_Count == 0 ]; then
		modprobe 88x2bu
	fi
