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

syscfg_create -f /nvram/syscfg.db

calcRandom=1
WAN_INTERFACE="eth0"

getCorrectiveActionState() {                                                                                      
    Corrective_Action=`syscfg get ConnTest_CorrectiveAction`                                                      
    echo "$Corrective_Action"                                                                                     
}  

calcRandTimetoStartPing()          
{                                 
                                                            
    rand_min=0                                       
    rand_sec=0                         
                                       
    # Calculate random min         
    rand_min=`awk -v min=0 -v max=59 -v seed="$(date +%N)" 'BEGIN{srand(seed);print int(min+rand()*(max-min+1))}'`
                                                            
    # Calculate random second                 
    rand_sec=`awk -v min=0 -v max=59 -v seed="$(date +%N)" 'BEGIN{srand(seed);print int(min+rand()*(max-min+1))}'`
                                                            
    sec_to_sleep=$(($rand_min*60 + $rand_sec))      
    sleep $sec_to_sleep;                                                                                         
                                      
}   

resetRouter()
{
	sleep 5
	dmcli simu setv Device.X_CISCO_COM_DeviceControl.RebootDevice string Router
}
resetNeeded()                                        
{
	folderName=$1                                         
        ProcessName=$2
	if [ "$ProcessName" == "PING" ]                              
                        then                                                           
                                echo "Before ResetNeeded"                              
                                resetRouter 
	fi 
}
runDNSPingTest()
{
	DNS_PING_TEST_STATUS=`syscfg get selfheal_dns_pingtest_enable`

        if [ "$DNS_PING_TEST_STATUS" = "true" ]
        then
                urlToVerify=`syscfg get selfheal_dns_pingtest_url`

                if [ -z "$urlToVerify" ]
                then
                        echo_t "DNS Response: DNS PING Test URL is empty"
                        return
                fi

                DNS_PING_TEST_URL=`removehttp $urlToVerify`

                if [ "$DNS_PING_TEST_URL" = "" ]
                then
                        echo_t "DNS Response: DNS PING Test URL is empty"
                        return
                fi

         nslookup $DNS_PING_TEST_URL > /dev/null 2>&1
         RESPONSE=$?

	echo "Response : $RESPONSE"
	if [ $RESPONSE -eq 0 ]                                                                            
                then                                                                                              
                        echo "DNS Response: Got success response for this URL $DNS_PING_TEST_URL"                 
                else                                                                                              
                        echo "DNS Response: fail to resolve this URL $DNS_PING_TEST_URL"                          
                                                                                                                  
                        if [ `getCorrectiveActionState` = "true" ]                                                
                        then                                                                                      
                                echo "RDKB_SELFHEAL : Taking corrective action"                                   
				dmcli simu setv Device.DeviceInfo.X_RDKCENTRAL-COM_LastRebootReason string DNS_Resolving_Failed
				sleep 5
                                resetNeeded "" PING                                                               
                        fi                                                                                        
         fi         
       fi
}
runPingTest()                                                          
{
		DEFAULT_GW_ROUTER=`route -n | grep UG | tr -s ' ' | cut -d ' ' -f2`
		sleep 2
		sysevent set default_router $DEFAULT_GW_ROUTER
		sleep 2
		
		PING_PACKET_SIZE=`syscfg get selfheal_ping_DataBlockSize`
	        PINGCOUNT=`syscfg get ConnTest_NumPingsPerServer`

	        if [ "$PINGCOUNT" = "" ]
        	then
                	PINGCOUNT=3
        	fi

	        RESWAITTIME=`syscfg get ConnTest_PingRespWaitTime`

	        if [ "$RESWAITTIME" = "" ]
        	then
                	RESWAITTIME=1000
        	fi
	        RESWAITTIME=$(($RESWAITTIME/1000))

	        RESWAITTIME=$(($RESWAITTIME*$PINGCOUNT))


        	IPv4_Gateway_addr=`sysevent get default_router`

		#PING_OUTPUT=`ping -I eth0 -c 3 -w 3 -s 50 192.168.2.1`
		PING_OUTPUT=`ping -I $WAN_INTERFACE -c $PINGCOUNT -w $RESWAITTIME -s $PING_PACKET_SIZE $IPv4_Gateway_addr`
                output_ipv4=`echo $?`                                                                             
                CHECK_PACKET_RECEIVED=`echo $PING_OUTPUT | grep "packet loss" | cut -d"%" -f1 | awk '{print $NF}'`
                                                                  
		echo "ping output : $PING_OUTPUT check_packet_recieved  $CHECK_PACKET_RECEIVED"           
                if [ "$CHECK_PACKET_RECEIVED" != "" ]                                                             
                then                                                                             
                        if [ "$CHECK_PACKET_RECEIVED" -ne 100 ]                                                           
                        then    
				echo "ping success"                                                                                  
                                ping4_success=1                                                                   
                        else                       
				echo "ping failure"               
                                ping4_failed=1                                                                    
                        fi                                                                       
                else         
			echo "ping faliure"                                                                                             
                        ping4_failed=1                                                                            
                fi            
		if [ "$ping4_failed" == 1 ]
		then
			dmcli simu setv Device.DeviceInfo.X_RDKCENTRAL-COM_LastRebootReason string IPv4_Pinging_failed
			sleep 5
			resetNeeded "" PING
		fi
}


SELFHEAL_ENABLE=`syscfg get selfheal_enable`

while [ "$SELFHEAL_ENABLE" = "true" ]
do                                        
                             
        if [ "$calcRandom" -eq 1 ]
        then                                               
                                       
                calcRandTimetoStartPing
                calcRandom=0       
        else                      
                INTERVAL=`syscfg get ConnTest_PingInterval`
                                              
                if [ "$INTERVAL" = "" ]
                then                                        
                        INTERVAL=60                 
                fi                            
                INTERVAL=$(($INTERVAL*60))
                sleep $INTERVAL
        fi
                                                    
        runPingTest
        runDNSPingTest                                                                                            
 
        SELFHEAL_ENABLE=`syscfg get selfheal_enable`
done   
