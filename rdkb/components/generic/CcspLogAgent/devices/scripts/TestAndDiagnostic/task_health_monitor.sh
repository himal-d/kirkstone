#! /bin/sh
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



################ PSM Module #############################

	PSM_PID=`pidof PsmSsp`
        if [ "$PSM_PID" = "" ]; then
		echo "RDKB_PROCESS_CRASHED : PSM_process is not running, need restart"
                /usr/bin/PsmSsp &
        fi

################### CcspPandM Module ######################

	PAM_PID=`pidof CcspPandMSsp`
        if [ "$PAM_PID" = "" ]; then
                # Remove the P&M initialized flag
                rm -rf /tmp/pam_initialized
                echo "RDKB_PROCESS_CRASHED : PAM_process is not running, need restart"
                /usr/bin/CcspPandMSsp &
        fi

#################### CcspTr069pa Module ######################

	TR69_PID=`pidof CcspTr069PaSsp`
        if [ "$TR69_PID" = "" ]; then
		echo "RDKB_PROCESS_CRASHED : TR69_process is not running, need restart"
                /usr/bin/CcspTr069PaSsp &
        fi

##################### Test And Diagnostics Module ################
	
	TandD_PID=`pidof CcspTandDSsp`
        if [ "$TandD_PID" = "" ]; then
                echo "RDKB_PROCESS_CRASHED : TandD_process is not running, need restart"
                /usr/bin/CcspTandDSsp &
        fi

##################### CcspLmLite Module ############################

        LM_PID=`pidof CcspLMLite`
        if [ "$LM_PID" = "" ]; then
                echo "RDKB_PROCESS_CRASHED : LanManager_process is not running, need restart"
		BRIDGEMODE_ENABLE=`dmcli simu getv Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanMode | grep value | cut -f3 -d : | cut -f2 -d" "`
		if [ "$BRIDGEMODE_ENABLE" = "router" ]; then
			/usr/bin/CcspLMLite &	
		fi	
        fi

####################### Snmp_SubAgent Module #########################

	SNMP_PID=`pidof snmp_subagent`
        if [ "$SNMP_PID" = "" ]; then
                echo "RDKB_PROCESS_CRASHED : snmp process is not running, need restart"
                /usr/bin/snmp_subagent &
        fi

####################### Ccsp Hotspot ###################################
	
	HOTSPOT_ENABLE=`dmcli simu getv Device.DeviceInfo.X_COMCAST_COM_xfinitywifiEnable | grep value | cut -f3 -d : | cut -f2 -d" "`
        if [ "$HOTSPOT_ENABLE" = "true" ]
        then

                DHCP_ARP_PID=`pidof CcspHotspot`
                if [ "$DHCP_ARP_PID" = "" ] ; then
                     echo "RDKB_PROCESS_CRASHED : DhcpArp_process is not running, need restart"
                     sh /lib/rdk/handle_emu_gre.sh create
                fi
	fi

############################ Sysevent ########################################

	SYSEVENT_PID=`pidof syseventd`
        if [ "$SYSEVENT_PID" == "" ]
        then
                echo "RDKB_PROCESS_CRASHED : syseventd is not running, restarting it"
		syseventd &
        fi

############################# Lighttpd ###########################################

	LIGHTTPD_PID=`pidof lighttpd`
        if [ "$LIGHTTPD_PID" = "" ]; then
                echo "RDKB_PROCESS_CRASHED : lighttpd is not running, restarting it"
                #/usr/sbin/lighttpd -D -f /etc/lighttpd.conf &
        fi



################################## CcspCr Module #####################################

	CCSPCR_PID=`pidof CcspCrSsp`
	if [ "$CCSPCR_PID" = "" ]; then                                                        
                echo "RDKB_PROCESS_CRASHED : ccspcr is not running, Image Needs to reboot now"                   
		reboot         
        fi  

################################## CcspWifiAgent Module ################################

	CCSPWIFIAGENT_PID=`pidof CcspWifiSsp`
	if [ "$CCSPWIFIAGENT_PID" = "" ]; then                                                        
                echo "RDKB_PROCESS_CRASHED : CcspWifiAgent is not running, restarting it"           
                /usr/bin/CcspWifiSsp &                                            
        fi     




