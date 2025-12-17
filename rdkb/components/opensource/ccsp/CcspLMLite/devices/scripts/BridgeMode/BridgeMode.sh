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
################# Hide the Private SSID Names in Bridge Mode set-up
sed -i "s/ignore_broadcast_ssid=0/ignore_broadcast_ssid=1/g" /nvram/hostapd0.conf
sed -i "s/ignore_broadcast_ssid=0/ignore_broadcast_ssid=1/g" /nvram/hostapd1.conf
#sh /lib/rdk/start_hostapd.sh

INTERFACE_2G=`cat /nvram/hostapd0.conf | grep -w interface | head -1 | cut -d '=' -f2`
INTERFACE_5G=`cat /nvram/hostapd1.conf | grep -w interface | head -1 | cut -d '=' -f2`

hostapd_cli -i $INTERFACE_2G SET ignore_broadcast_ssid 1
hostapd_cli -i $INTERFACE_5G SET ignore_broadcast_ssid 1

hostapd_cli -i  $INTERFACE_2G DISABLE
hostapd_cli -i  $INTERFACE_2G ENABLE
hostapd_cli -i  $INTERFACE_5G DISABLE
hostapd_cli -i  $INTERFACE_5G ENABLE


ifconfig $INTERFACE_2G down
ifconfig $INTERFACE_5G down

############ Adding two more IP Address to eth0 Interface ##########

LAN_IP=`cat /var/dnsmasq_org.conf | grep -w dhcp-range | cut -d ',' -f2 | cut -d '.' -f1-3`
ip addr add $LAN_IP.1/24 dev eth0
ip addr add 192.168.100.1/24 dev eth0

######### Adding default WebUI Access IP in lighttpd Webserver #############

LIGHTTPD_IP=`cat /etc/lighttpd.conf | grep server.bind | grep -v ^# | cut -d '=' -f2`
router_ip_address=`cat /var/dnsmasq_org.conf | grep -w dhcp-range | cut -d ',' -f2 | cut -d '.' -f1-3`
sed -i  "s/server.bind =$LIGHTTPD_IP/server.bind = \"$router_ip_address.1\"/g" /etc/lighttpd.conf

############## Deleting Wlan0 from Bridge and Killing udhcpc for brlan0 and eth1 #############
brctl delif brlan0 $INTERFACE_2G
brctl delif brlan0 $INTERFACE_5G
ps -eaf | grep ibrlan0 | grep -v grep | awk '{print $2}' | xargs kill -9
ps -eaf | grep ieth1 | grep -v grep | awk '{print $2}' | xargs kill -9

################# Killing dnsmasq and adding WAN interface to Bridge ##############
ps -eaf | grep ieth2 | grep -v grep | awk '{print $2}' | xargs kill -9
ifconfig eth2 0.0.0.0
brctl addif brlan0 eth2
ifconfig brlan0 0.0.0.0
killall dnsmasq


######### Adding default WebUI Access LAN IP in lighttpd Webserver #############
echo "\$SERVER[\"socket\"] == \"192.168.100.1:8081\"  { }" >> /etc/lighttpd.conf


############## TURN OFF the Private Wifi for Dual Bands ########################
#PRIVATE_SSID_OFF=`cat /etc/hostapd.conf | grep ^ssid | head -1`
#sed -i "28 s/^/#/" /etc/hostapd.conf
ifconfig $INTERFACE_2G down
ifconfig $INTERFACE_5G down

########################## FORWARDING TRAFFIC TO eth0 Interface ##################
WAN_MAC=`ifconfig eth0|grep HWaddr|awk '{print $5}'| tr '[a-z]' '[A-Z]'`
ebtables -t nat -I PREROUTING -i eth1 -p IPv4 --ip-dst $LAN_IP.1 -j dnat --to-dst $WAN_MAC --dnat-target ACCEPT
ebtables -t nat -A PREROUTING -i eth1 -p IPv4 --ip-dst 192.168.100.1 -j dnat --to-dst $WAN_MAC --dnat-target ACCEPT

############### Copying BridgeMode Set-up to default Emulator Set-up ###########
cp /usr/bin/setup_bridgemode.sh /usr/bin/setup.sh

############### Restarting Hostapd and lighttd webserver #########
#killall CcspLMLite
#Restart_Hostapd
brctl delif brlan0 $INTERFACE_2G

killall lighttpd
