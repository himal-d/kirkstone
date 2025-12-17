#!/bin/sh

##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2018 RDK Management
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

dmcli simu psmsetv Device.DeviceInfo.X_RDKCENTRAL-COM_ConfigureWiFi string false
sleep 1

####################### Lighttpd Changes ##########################                                                                                                      
CAPTIVEMODE=`cat /etc/lighttpd.conf | grep captiveportal.php | wc -l`                                   

if [ $CAPTIVEMODE == 1 ] ; then                                                                         
                sed -i '$d' /etc/lighttpd.conf  ############ delete the last line in lighttpd configuration file
                sed -i '$d' /etc/lighttpd.conf                                       
                sed -i '$d' /etc/lighttpd.conf                             
fi     

###################### dnsmasq Changes #############################
CAPTIVEMODE=`cat /etc/dnsmasq.conf | grep address | wc -l`                                                                           

if [ $CAPTIVEMODE == 1 ]; then                                             
                cat /etc/dnsmasq.conf | grep address | sed -i "/address=/d" /etc/dnsmasq.conf
fi 

###################  Reverting the redirection rules ###############
iptables -t nat -D PREROUTING -i brlan0 -p udp --dport 53 -j DNAT --to 10.0.0.1
sleep 1
iptables -t nat -D PREROUTING -i brlan0 -p tcp --dport 53 -j DNAT --to 10.0.0.1

rm /nvram/updated_captiveportal_redirectionrules
rm /nvram/captivemode_enabled
##################### Restarting the lighttpd and dnsmasq process ############

killall lighttpd
killall dnsmasq
sleep 2
/usr/bin/dnsmasq &
