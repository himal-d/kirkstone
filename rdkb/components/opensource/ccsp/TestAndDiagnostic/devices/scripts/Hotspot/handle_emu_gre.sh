#!/bin/sh
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2015 RDK Management
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

#######################################################################
#   Copyright [2014] [Cisco Systems, Inc.]
#
#   Licensed under the Apache License, Version 2.0 (the \"License\");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an \"AS IS\" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#######################################################################

#------------------------------------------------------------------
# ENTRY
#------------------------------------------------------------------

GRE_IFNAME="gretap0"
GRE_IFNAME_DUMMY="gretap_0"

GRE_PSM_BASE=dmsb.cisco.gre
HS_PSM_BASE=dmsb.hotspot.tunnel
GRE_PSM_NAME=name
#format for below is comma delimited FQDM
GRE_PSM_BRIDGES=AssociatedBridges
GRE_PSM_KAINT=RemoteEndpointHealthCheckPingInterval
GRE_PSM_KARECON=ReconnectToPrimaryRemoteEndpoint
GRE_PSM_KATHRESH=RemoteEndpointHealthCheckPingFailThreshold
GRE_PSM_KAPOLICY=KeepAlivePolicy
GRE_PSM_PRIENDPOINTS=PrimaryRemoteEndpoint
GRE_PSM_SECENDPOINTS=SecondaryRemoteEndpoint
GRE_PSM_ENDPOINT=endpoint
GRE_PSM_KACOUNT=RemoteEndpointHealthCheckPingCount
GRE_PSM_SNOOPCIRC=EnableCircuitID
GRE_PSM_SNOOPREM=EnableRemoteID
GRE_PSM_ENABLE=enable
HS_PSM_ENABLE=Enable
GRE_PSM_LOCALIFS=LocalInterfaces
WIFI_PSM_PREFIX=eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.SSID
WIFI_RADIO_INDEX=RadioIndex

HOTSPOT_COMP=CcspHotspot
GRE_ARP_PROC=hotspot_arpd
ARP_NFQUEUE=0

WAN_IF=eth0

BASEQUEUE=1

DONGLE_INDENTIFICATION=`cat /nvram/hostapd0.conf | grep bss= | cut -c1`
if [ "$DONGLE_INDENTIFICATION" == "#" ] ; then
echo "TP-link"
INTERFACE_2G=`cat /nvram/hostapd4.conf | grep -w interface | head -1 | cut -d '=' -f2`
else
echo "tenda"
INTERFACE_2G=`cat /nvram/hostapd0.conf | grep -w bss | head -1 | cut -d '=' -f2`
fi
INTERFACE_5G=`cat /nvram/hostapd5.conf | grep -w interface | head -1 | cut -d '=' -f2`

###################### ENABLING SNOOPER LOGS ################################

init_snooper_sysevents () {

        sysevent set snooper-circuit-enable 1
	sysevent set snooper-remote-enable 1
}

######################## RETRIVING VALUES FROM PSM DATABASE ##################

read_init_params () {

	 inst=1
	 eval `psmcli nosubsys get -e PRIMARY $HS_PSM_BASE.${inst}.$GRE_PSM_PRIENDPOINTS SECONDARY $HS_PSM_BASE.${inst}.$GRE_PSM_SECENDPOINTS BRIDGE_INST_1 $HS_PSM_BASE.${inst}.interface.1.$GRE_PSM_BRIDGES BRIDGE_INST_2 $HS_PSM_BASE.${inst}.interface.2.$GRE_PSM_BRIDGES KA_INTERVAL $HS_PSM_BASE.${inst}.$GRE_PSM_KAINT KA_FAIL_INTERVAL $HS_PSM_BASE.${inst}.$GRE_PSM_KAFINT KA_POLICY $HS_PSM_BASE.${inst}.$GRE_PSM_KAPOLICY KA_THRESH $HS_PSM_BASE.${inst}.$GRE_PSM_KATHRESH KA_COUNT $HS_PSM_BASE.${inst}.$GRE_PSM_KACOUNT KA_RECON_PRIM $HS_PSM_BASE.${inst}.$GRE_PSM_KARECON SNOOP_CIRCUIT $HS_PSM_BASE.${inst}.$GRE_PSM_SNOOPCIRC SNOOP_REMOTE $HS_PSM_BASE.${inst}.$GRE_PSM_SNOOPREM WECB_BRIDGES dmsb.wecb.hhs_extra_bridges`
}


####################### CREATING GRE TUNNEL ###################################

create_tunnel () {

	ip link set dev $GRE_IFNAME name $GRE_IFNAME_DUMMY
	ip link add gretap0 type gretap remote `sysevent get hotspotfd-tunnelEP` local "`ifconfig -a eth0 | grep inet | grep -v inet6 | tr -s " " | cut -d ":" -f2 | cut -d " " -f1`" ttl 255 dev $WAN_IF

	brctl addbr brlan1
	brctl addbr brlan2

	sleep 2

        ifconfig gretap0 up
	#ps -eaf | grep ibrlan1 | grep -v grep | awk '{print $2}' | xargs kill -9
	#ps -eaf | grep ibrlan2 | grep -v grep | awk '{print $2}' | xargs kill -9

	vconfig add gretap0 100
	vconfig add gretap0 101
	ifconfig gretap0.100 up
	ifconfig gretap0.101 up

	#sleep 1
	
		
	#ps -eaf | grep igretap0.100 | grep -v grep | awk '{print $2}' | xargs kill -9
	#ps -eaf | grep igretap0.101 | grep -v grep | awk '{print $2}' | xargs kill -9
	
	sleep 3
	
        brctl addif brlan1 $INTERFACE_2G
	brctl addif brlan1 gretap0.100
	brctl addif brlan2 $INTERFACE_5G
	brctl addif brlan2 gretap0.101
}

########################## UPDATING SYSEVENT DAEMON ############################

init_keepalive_sysevents () {

	keepalive_args="-n eth0"
        sysevent set hotspotfd-primary $PRIMARY
        sysevent set hotspotfd-secondary $SECONDARY
        sysevent set hotspotfd-threshold $KA_THRESH
        sysevent set hotspotfd-keep-alive $KA_INTERVAL
        sysevent set hotspotfd-max-secondary $KA_RECON_PRIM
        sysevent set hotspotfd-policy $KA_POLICY
        sysevent set hotspotfd-count $KA_COUNT
        sysevent set hotspotfd-dead-interval $KA_FAIL_INTERVAL
        sysevent set hotspotfd-enable 1
        keepalive_args="$keepalive_args -e 1"
    	sysevent set hotspotfd-log-enable 1

}

######### NFQUEUE filter rules ################

update_bridge_config () {

iptables -I FORWARD -j general_forward
iptables -I OUTPUT -j general_output
iptables -I general_forward -o brlan1 -p udp --dport=67:68 -j NFQUEUE --queue-bypass --queue-num 1
iptables -A general_forward -o brlan2 -p udp --dport=67:68 -j NFQUEUE --queue-bypass --queue-num 2
iptables -A general_output -o eth0 -p icmp --icmp-type 3 -j NFQUEUE --queue-bypass --queue-num 0

}

case "$1" in

create)

	read_init_params
	init_keepalive_sysevents
	init_snooper_sysevents
	$HOTSPOT_COMP $keepalive_args &
	$GRE_ARP_PROC -q $ARP_NFQUEUE  &
	sleep 5
	create_tunnel 
	update_bridge_config
esac
	


