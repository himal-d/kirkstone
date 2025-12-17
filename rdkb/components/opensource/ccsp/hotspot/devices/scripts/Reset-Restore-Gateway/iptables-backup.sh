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


################################## SAVING & RESTORING IPTABLES RULES ###########################################
sleep 20


if [[ ! -f /nvram/captivemode_enabled  && ! -f /nvram/updated_captiveportal_redirectionrules ]] ; then
	iptables -t nat -D PREROUTING -i brlan0 -p udp --dport 53 -j DNAT --to 10.0.0.1
	iptables -t nat -D PREROUTING -i brlan0 -p tcp --dport 53 -j DNAT --to 10.0.0.1
fi

while true
do
################# SAVING MANGLE TABLE & HOTSPOT #############################

	iptables-save -c -t mangle > /etc/iptables/mangle_tables_rules.v4
	iptables -t mangle -F
	iptables -t nat -D POSTROUTING -o eth0 -j MASQUERADE
	iptables -D FORWARD -i eth0 -o brlan0 -m state --state RELATED,ESTABLISHED -j ACCEPT
	iptables -D FORWARD -i brlan0 -o eth0 -j ACCEPT
	iptables -t nat -D prerouting_redirect -p tcp --dport 80 -j DNAT --to-destination 0.0.0.0:21515
	iptables -t nat -D prerouting_redirect -p tcp --dport 443 -j DNAT --to-destination 0.0.0.0:21515
	iptables -t nat -D prerouting_redirect -p tcp  -j DNAT --to-destination 0.0.0.0:21515
	iptables -t nat -D prerouting_redirect -p udp ! --dport 53 -j DNAT --to-destination 0.0.0.0:21515
	iptables -t nat -D PREROUTING  -j prerouting_mgmt_override
    TRPORT=`dmcli simu getv Device.ManagementServer.X_CISCO_COM_ConnectionRequestURLPort | grep value | cut -f3 -d : | cut -f2 -d" "`
	iptables -t nat -D prerouting_mgmt_override -p tcp -m multiport --dports ${TRPORT},22 -j ACCEPT

HOTSPOT_ENABLE=`dmcli simu getv Device.DeviceInfo.X_COMCAST_COM_xfinitywifiEnable | grep value | cut -f3 -d : | cut -f2 -d " "`
	if [ "$HOTSPOT_ENABLE" = "true" ]; then 
	iptables -D FORWARD -j general_forward                                         
	iptables -D OUTPUT -j general_output                                            
	iptables -D general_forward -o brlan1 -p udp --dport=67:68 -j NFQUEUE --queue-bypass --queue-num 1                                   
	iptables -D general_forward -o brlan2 -p udp --dport=67:68 -j NFQUEUE --queue-bypass --queue-num 2
	iptables -D general_output -o eth0 -p icmp --icmp-type 3 -j NFQUEUE --queue-bypass --queue-num 0

	iptables -D FORWARD -j general_forward
        iptables -D OUTPUT -j general_output
        iptables -D general_forward -o brlan1 -p udp --dport=67:68 -j NFQUEUE --queue-bypass --queue-num 1
        iptables -D general_forward -o brlan2 -p udp --dport=67:68 -j NFQUEUE --queue-bypass --queue-num 2
        iptables -D general_output -o eth0 -p icmp --icmp-type 3 -j NFQUEUE --queue-bypass --queue-num 0
	fi

###################### SAVING WHOLE IPTBALES RULES ######################################

	iptables-save -c > /etc/iptables/rules.v4

######################## RESTORING MANGLE TABLE RULES AND ROUTING RULES #########################

	iptables-restore -c  < /etc/iptables/mangle_tables_rules.v4
	iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
	iptables -A FORWARD -i eth0 -o brlan0 -m state --state RELATED,ESTABLISHED -j ACCEPT
	iptables -A FORWARD -i brlan0 -o eth0 -j ACCEPT
	iptables -t nat -A prerouting_redirect -p tcp --dport 80 -j DNAT --to-destination 0.0.0.0:21515
	iptables -t nat -A prerouting_redirect -p tcp --dport 443 -j DNAT --to-destination 0.0.0.0:21515
	iptables -t nat -A prerouting_redirect -p tcp  -j DNAT --to-destination 0.0.0.0:21515
	iptables -t nat -A prerouting_redirect -p udp ! --dport 53 -j DNAT --to-destination 0.0.0.0:21515
	iptables -t nat -I PREROUTING 1 -j prerouting_mgmt_override
	TRPORT=`dmcli simu getv Device.ManagementServer.X_CISCO_COM_ConnectionRequestURLPort | grep value | cut -f3 -d : | cut -f2 -d" "`
	iptables -t nat -A prerouting_mgmt_override -p tcp -m multiport --dports ${TRPORT},22 -j ACCEPT

HOTSPOT_ENABLE=`dmcli simu getv Device.DeviceInfo.X_COMCAST_COM_xfinitywifiEnable | grep value | cut -f3 -d : | cut -f2 -d" "`
        if [ "$HOTSPOT_ENABLE" = "true" ]; then
        iptables -I FORWARD -j general_forward
        iptables -I OUTPUT -j general_output
        iptables -I general_forward -o brlan1 -p udp --dport=67:68 -j NFQUEUE --queue-bypass --queue-num 1
        iptables -A general_forward -o brlan2 -p udp --dport=67:68 -j NFQUEUE --queue-bypass --queue-num 2
        iptables -A general_output -o eth0 -p icmp --icmp-type 3 -j NFQUEUE --queue-bypass --queue-num 0
        fi

	sleep 3
done
