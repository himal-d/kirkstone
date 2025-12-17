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


########################### Getting Total Number of wireless Interface Count #################
wifi=`ifconfig -a | grep wlan | wc -l`

########################### Getting Total Number of Channel Count for all Interfaces #############

wifi_wlan0=`iwlist wlan0 freq | grep wlan0 | tr -s ' ' | cut -d ' ' -f2`
echo "Channel Count = $wifi_wlan0"


wifi_wlan1=`iwlist wlan1 freq | grep wlan1 | tr -s ' ' | cut -d ' ' -f2`
echo "Channel Count = $wifi_wlan1"

########################### Killing the private wifi for 5Ghz and Starting the Xfinity-wifi for 5Ghz #############

rmmod rtl8812au
sleep 1
insmod /lib/modules/3.14.4-yocto-standard/kernel/drivers/net/wireless/rtl8812au/rtl8812au.ko
sleep 2
############################### single dongle #################################################

if [ $wifi == 1 ];then
	killall hostapd
	ps -eaf | grep hostapd | grep -v grep | awk '{print $2}' | xargs kill -9
	ifconfig wlan0 down
	sleep 2
	ifconfig wlan0 up
	wifi_oldinterface=`cat /etc/hostapd_xfinity_5G.conf | grep interface | head -1`      
	echo "wireless old interface $wifi_oldinterface"                                           
	sed -i "s/$wifi_oldinterface/interface=wlan0/g" /etc/hostapd_xfinity_5G.conf            
	/usr/sbin/hostapd -B /etc/hostapd_xfinity_5G.conf -dd

#################################### Double Dongle / Virtual Interface for wlan0_0(3) ##############################################

elif [ $wifi == 3 ] || [ $wifi == 2 ] ; then
	ps -eaf | grep hostapd_5G | grep -v grep | awk '{print $2}' | xargs kill -9
	if [ $wifi_wlan0 == 36 ] ; then
		ifconfig wlan0 down
		sleep 2
		ifconfig wlan0 up
		wifi_oldinterface=`cat /etc/hostapd_xfinity_5G.conf | grep interface | head -1`
	        echo "wireless old interface $wifi_oldinterface"
        	sed -i "s/$wifi_oldinterface/interface=wlan0/g" /etc/hostapd_xfinity_5G.conf
        	/usr/sbin/hostapd -B /etc/hostapd_xfinity_5G.conf -dd
	else
		ifconfig wlan1 down                                                
                sleep 2                
                ifconfig wlan1 up  
                wifi_oldinterface=`cat /etc/hostapd_xfinity_5G.conf | grep interface | head -1`
                echo "wireless old interface $wifi_oldinterface"                               
                sed -i "s/$wifi_oldinterface/interface=wlan1/g" /etc/hostapd_xfinity_5G.conf   
                /usr/sbin/hostapd -B /etc/hostapd_xfinity_5G.conf -dd 	
	fi	

else
	echo "wireless interface doesnot exist"
fi
