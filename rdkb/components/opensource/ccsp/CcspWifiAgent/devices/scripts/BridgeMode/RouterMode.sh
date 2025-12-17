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

INTERFACE_2G=`cat /nvram/hostapd0.conf | grep -w interface | head -1 | cut -d '=' -f2`
VIRTUAL_INTERFACE_2G=`cat /nvram/hostapd0.conf | grep -w bss | head -1 | cut -d '=' -f2`
INTERFACE_5G=`cat /nvram/hostapd1.conf | grep -w interface | head -1 | cut -d '=' -f2`

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

                                                                             
Restart_Hostapd_5G () {
	rmmod rtl8812au 88x2bu
	sleep 1
	modprobe rtl8812au
	sleep 1
	modprobe 88x2bu
	sleep 1                                                                                                    
        hostapd -B /nvram/hostapd1.conf                                                                                 
	sleep 1
        hostapd -B /nvram/hostapd5.conf                                                                                 
}
                                                             
Hostapd_Restart () {                                                         
                                                                             
        ps -eaf | grep hostapd0 | grep -v grep | awk '{print $2}' | xargs kill -9
        ifconfig wlan0 up                                                    
        hostapd -B /nvram/hostapd0.conf                                         
        ifconfig mon.wlan0 up                                                
        ifconfig wlan0_0 up                                                  
                                                                             
}          

sed -i "s/ignore_broadcast_ssid=1/ignore_broadcast_ssid=0/g" /nvram/hostapd0.conf
sed -i "s/ignore_broadcast_ssid=1/ignore_broadcast_ssid=0/g" /nvram/hostapd1.conf

hostapd_cli -i $INTERFACE_2G SET ignore_broadcast_ssid 0
hostapd_cli -i $INTERFACE_5G SET ignore_broadcast_ssid 0

ROUTER=`cat /etc/dnsmasq.conf | grep -w dhcp-range | cut -d ',' -f2 | cut -d '.' -f1-3`
SUBNETMASK=`cat /etc/dnsmasq.conf | grep -w dhcp-range | cut -d ',' -f3`
psmcli nosubsys set dmsb.dhcpv4.server.pool.0.IPRouters $ROUTER.1
psmcli nosubsys set dmsb.dhcpv4.server.pool.0.SubnetMask $SUBNETMASK

############ Deleting BridgeMode Interface and Adding Wireless Interface to Bridge ########
brctl delif brlan0 eth2

#brctl addif brlan0 $INTERFACE_2G 
#brctl addif brlan0 $INTERFACE_5G 

hostapd_cli -i $INTERFACE_2G DISABLE
hostapd_cli -i $INTERFACE_2G ENABLE
hostapd_cli -i $INTERFACE_5G DISABLE
hostapd_cli -i $INTERFACE_5G ENABLE

################### Getting Current Router IP Address ##########
dnsmasq_conf_file=/etc/dnsmasq.conf                                          
KEYWORD=dhcp-range 
router_ip_address=`grep $KEYWORD $dnsmasq_conf_file | cut -d ',' -f1 | cut -d '=' -f2 | cut -d '.' -f1-3`
ifconfig brlan0 $router_ip_address.1 

######## Remove Additional IP Address from eth0 #############
ip addr del $router_ip_address.1/24 dev eth0
ip addr del 192.168.100.1/24 dev eth0


################## TURN ON the Private SSID for Dual Bands ###############
#PRIVATE_SSID_ON=`cat /etc/hostapd.conf | grep ^#ssid`
#sed -i "/$PRIVATE_SSID_ON/ s/^#*//" /etc/hostapd.conf
sed -i "29 s/^#*//" /nvram/hostapd0.conf
sed -i "29 s/^#*//" /nvram/hostapd1.conf

############# Setting Default WebUI access IP in Lighttpd Webserver ########
LIGHTTPD_IP=`cat /etc/lighttpd.conf | grep server.bind | grep -v ^# | cut -d '=' -f2`
sed -i  "s/server.bind =$LIGHTTPD_IP/server.bind = \"$router_ip_address.1\"/g" /etc/lighttpd.conf

######### Remove the Additional IP Address of eth0 Interface ######
sed -i '$d' /etc/lighttpd.conf 

############### Remove ebtables rules ##################
WAN_MAC=`ifconfig eth0|grep HWaddr|awk '{print $5}'| tr '[a-z]' '[A-Z]'`
echo "$WAN_MAC"
sleep 1
ebtables -t nat -D PREROUTING -i eth1 -p IPv4 --ip-dst $router_ip_address.1 -j dnat --to-dst $WAN_MAC --dnat-target ACCEPT
ebtables -t nat -D PREROUTING -i eth1 -p IPv4 --ip-dst 192.168.100.1 -j dnat --to-dst $WAN_MAC --dnat-target ACCEPT


############### Copying RouterMode Set-up to default Emulator Set-up #######
cp /usr/bin/setup_routermode.sh /usr/bin/setup.sh

################# starting The Lighttpd Webserver and Dnsmasq ##############
#udhcpd -f /etc/udhcpd.conf &
#/usr/bin/CcspLMLite &
killall dnsmasq
/usr/bin/dnsmasq &

#Restart_Hostapd                                                              
#ps -eaf | grep hostapd0 | grep -v grep | awk '{print $2}' | xargs kill -9
#killall hostapd
#ifconfig $INTERFACE_2G down
#sleep 1
#ifconfig $VIRTUAL_INTERFACE_2G down
#sh /lib/rdk/start_hostapd.sh
#DONGLE_IDENTIFIACTION=`cat /nvram/hostapd0.conf | grep bss= | cut -c1`
#if [ "$DONGLE_IDENTIFIACTION" == "#" ] ; then
#echo "tp-link"
#else
#echo "tenda"
#Restart_Hostapd_5G                                                              
#fi

echo "1" > /tmp/Get2gssidEnable.txt
echo "1" > /tmp/Get5gssidEnable.txt

                                                                             
################# Checking the Hostapd Status Again(due to wlan0 getting failure status) #########################
                                                                                                                              
#HOTSPOT_RESTART=`ifconfig wlan0 | grep RUNNING | tr -s ' ' | cut -d " " -f4`                                                
#while [ "$HOTSPOT_RESTART" != "RUNNING" ]                                                                                     
#do                                                                                                                            
#Hostapd_Restart                                                                                                               
#HOTSPOT_RESTART=`ifconfig wlan0 | grep RUNNING | tr -s ' ' | cut -d " " -f4`                                                
#done    

###################### To support WAN0 Interface for DMZ #######################
sleep 1
/sbin/udhcpc -ieth2 &

killall lighttpd
