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

dmcli simu psmsetv Device.DeviceInfo.X_RDKCENTRAL-COM_ConfigureWiFi string true

#################### Updated lighttpd configuration to support captivemode enabling ###################
CAPTIVEMODE=`cat /etc/lighttpd.conf | grep captiveportal.php | wc -l`
if [ $CAPTIVEMODE == 0 ] ; then                                      
echo "\$HTTP[\"host\"] !~ \":8080\" {  \$HTTP[\"url\"] !~ \"captiveportal.php\" {  \$HTTP[\"referer\"] == \"\" { url.redirect = ( \".*\" => \"http://10.0.0.1/captiveportal.php\" ) url.redirect-code = 303 }" >> /etc/lighttpd.conf
echo "}" >> /etc/lighttpd.conf
echo "}" >> /etc/lighttpd.conf
fi
                                                                                                         
if [ ! -f /nvram/captivemode_enabled ]; then
touch /nvram/captivemode_enabled                               
fi               

################### Updated dnsmasq configuration to support captiveMode ################

CAPTIVEMODE=`cat /etc/dnsmasq.conf | grep address | wc -l`                                                                           
if [ $CAPTIVEMODE == 0 ]; then                                                                              
        router_ip_address=`cat /etc/dnsmasq.conf | grep -w dhcp-range | cut -d ',' -f2 | cut -d '.' -f1-3`   
        sed -i "/interface/a address=/#/$router_ip_address.1" /etc/dnsmasq.conf                           
fi                                                                                                       

###################  Redirection rules for CaptiveMode Support ###############
iptables -t nat -I PREROUTING -i brlan0 -p udp --dport 53 -j DNAT --to 10.0.0.1
sleep 1
iptables -t nat -I PREROUTING -i brlan0 -p tcp --dport 53 -j DNAT --to 10.0.0.1

touch /nvram/updated_captiveportal_redirectionrules
touch /nvram/captivemode_enabled

##################### Restarting the lighttpd and dnsmasq process ############

killall lighttpd
killall dnsmasq
sleep 2
/usr/bin/dnsmasq &
                                                                                                                                  
