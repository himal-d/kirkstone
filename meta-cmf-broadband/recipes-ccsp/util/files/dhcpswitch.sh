#! /bin/sh
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2021 RDK Management
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

CRONTAB_DIR="/var/spool/cron/crontabs/"
CRONTAB_FILE=$CRONTAB_DIR"root"
CRONFILE_BK="/tmp/cron_tab$$.txt"
LOG_FILE="/rdklogs/logs/PAMlog.txt.0"

if [ -f /etc/device.properties ]
then
    source /etc/device.properties
fi


calcExecTime()
{

        # Extract maintenance window start and end time
        start_time=`dmcli eRT getv Device.DeviceInfo.X_RDKCENTRAL-COM_MaintenanceWindow.FirmwareUpgradeStartTime | grep "value:" | cut -d ":" -f 3 | tr -d ' '`
        end_time=`dmcli eRT getv Device.DeviceInfo.X_RDKCENTRAL-COM_MaintenanceWindow.FirmwareUpgradeEndTime | grep "value:" | cut -d ":" -f 3 | tr -d ' '`

        #if start_time and end_time are set it to default
        if [ "$start_time" = "$end_time" ]
        then
		echo "[dhcpswitch.sh] start_time and end_time are equal.so,setting them to default" >> $LOG_FILE
        	dmcli eRT setv Device.DeviceInfo.X_RDKCENTRAL-COM_MaintenanceWindow.FirmwareUpgradeStartTime string "3600"
                dmcli eRT setv Device.DeviceInfo.X_RDKCENTRAL-COM_MaintenanceWindow.FirmwareUpgradeEndTime string "14400"
                start_time=3600
                end_time=14400
        fi

        #Get local time off set
        time_offset=`dmcli eRT getv Device.Time.TimeOffset | grep "value:" | cut -d ":" -f 3 | tr -d ' '`


        #Maintence start and end time in local
        main_start_time=$((start_time-time_offset))
        main_end_time=$((end_time-time_offset))

        #calculate random time in sec
        rand_time_in_sec=`awk -v min=$main_start_time -v max=$main_end_time -v seed="$(date +%N)" 'BEGIN{srand(seed);print int(min+rand()*(max-min+1))}'`

	# To avoid cron to be set beyond 24 hr clock limit
	if [ $rand_time_in_sec -ge 86400 ]
	then
		rand_time_in_sec=$((rand_time_in_sec-86400))
		echo "[dhcpswitch.sh] Random time in sec exceed 24 hr limit.setting it correct limit" >> $LOG_FILE
		
	fi

        #conversion of random generated time to HH:MM:SS format
                #calculate random second
                rand_time=$rand_time_in_sec
                rand_sec=$((rand_time%60))

                #calculate random minute
                rand_time=$((rand_time/60))
                rand_min=$((rand_time%60))

                #calculate random hour
                rand_time=$((rand_time/60))
                rand_hr=$((rand_time%60))

        echo "[dhcpswitch.sh]start_time: $start_time, end_time: $end_time" >> $LOG_FILE
	echo "[dhcpswitch.sh]time_offset: $time_offset" >> $LOG_FILE
        echo "[dhcpswitch.sh]main_start_time: $main_start_time , main_end_time= $main_end_time" >> $LOG_FILE
        echo "[dhcpswitch.sh]rand_time_in_sec: $rand_time_in_sec ,rand_hr: $rand_hr ,rand_min: $rand_min ,rand_sec: $rand_sec" >> $LOG_FILE

}

ScheduleCron()                                                                                                                           
{                                                                                                                                        
        # Dump existing cron jobs to a file & add new job                                                                                
        crontab -l -c $CRONTAB_DIR > $CRONFILE_BK                                                                                        
        echo "$rand_min $rand_hr * * * /etc/dhcpswitch.sh Execute" >> $CRONFILE_BK                                                       
        crontab $CRONFILE_BK -c $CRONTAB_DIR                                                                                             
        rm -rf $CRONFILE_BK                                                                                                              
                                                                                                                                         
                                                                                                                                         
}                                                                                                                                        
                                                                                                                                         
RemoveCron()                                                                                                                             
{                                                                                                                                        
        # Dump existing cron jobs to a file & remove existing job                                                                                
        crontab -l -c $CRONTAB_DIR > $CRONFILE_BK                                                                                        
        sed -i '/dhcpswitch.sh/d' $CRONFILE_BK                                                                                           
        crontab $CRONFILE_BK -c $CRONTAB_DIR                                                                   
        rm -rf $CRONFILE_BK                                                                                    
                                                                                                               
}

wait_till_state_wan_stopped ()
{
   TRIES=1
   while [ "9" -ge "$TRIES" ] ; do
      LSTATUS=`sysevent get wan-status`
      if [ "stopped" != "$LSTATUS" ] ; then
         sleep 1
         TRIES=`expr $TRIES + 1`
      else
         return
      fi
   done
}

wait_till_state_wan_started ()
{
   TRY=0
   while [ "1" != "$TRY" ] ; do
      LSTATUS=`sysevent get wan-status`
      if [ "started" != "$LSTATUS" ] ; then
         sleep 1
      else
	TRY=1
         return
      fi
   done
}

if [ "$1" = "Execute" ]
then
	sysevent set wan-stop
        sleep 2
        wait_till_state_wan_stopped
	echo "[dhcpswitch.sh] WAN STOPPED" >> $LOG_FILE

	if [ "$MODEL_NUM" = "TG3482G" ]; then
		systemctl stop dropbear-atom-js.service
		echo "[dhcpswitch.sh] dropbear service stopped in Execute" >> $LOG_FILE
	fi

        if [ "1" = "`sysevent get dhcpclient_v4`" ]
        then
        	syscfg set UDHCPEnable true
                syscfg commit
		echo "[dhcpswitch.sh] UDHCPEnable flag set to true" >> $LOG_FILE
        fi
        if [ "1" = "`sysevent get dhcpclient_v6`" ]
        then
        	syscfg set dibbler_client_enable true
                syscfg commit
		echo "[dhcpswitch.sh] dibbler_client_enable flag set to true" >> $LOG_FILE
        fi

	sysevent set wan-start
	RemoveCron
	echo "[dhcpswitch.sh] WAN STARTED and Cron Removed" >> $LOG_FILE

        if [ "$MODEL_NUM" = "TG3482G" ]; then
		wait_till_state_wan_started
		systemctl start dropbear-atom-js.service
                echo "[dhcpswitch.sh] dropbear service started in Execute" >> $LOG_FILE
        fi

        if [ "1" = "`sysevent get dhcpclient_v4`" ]
        then
                sysevent set dhcpclient_v4 0
                echo "[dhcpswitch.sh] dhcpclient_v4 is set back to Null after V4 flip" >> $LOG_FILE
        fi
        if [ "1" = "`sysevent get dhcpclient_v6`" ]
        then
                sysevent set dhcpclient_v6 0
                echo "[dhcpswitch.sh] dhcpclient_v4 is set back to Null after V4 flip" >> $LOG_FILE
        fi

fi

if [ "$1" = "schedule_v4_cron" ]
then
	if [ "1" = "`sysevent get dhcpclient_v6`" ]
        then
        	sysevent set dhcpclient_v4 1
		echo "[dhcpswitch.sh] dhcpclient_v4 event set to 1" >> $LOG_FILE
        else
                sysevent set dhcpclient_v4 1
                calcExecTime
                if [ -f $CRONTAB_FILE ]
                then
			ScheduleCron
			echo "[dhcpswitch.sh] dhcpclient_v4 cron job scheduled" >> $LOG_FILE
                fi

         fi

fi

if [ "$1" = "schedule_v6_cron" ]
then

	if [ "1" = "`sysevent get dhcpclient_v4`" ]
        then
        	sysevent set dhcpclient_v6 1
		echo "[dhcpswitch.sh] dhcpclient_v6 event set to 1" >> $LOG_FILE
        else
        	sysevent set dhcpclient_v6 1
                calcExecTime
                if [ -f $CRONTAB_FILE ]
                then
			ScheduleCron
			echo "[dhcpswitch.sh] dhcpclient_v6 cron job scheduled" >> $LOG_FILE
                fi

       fi

fi

if [ "$1" = "clear_v4_cron" ]
then
  	if [ "1" = "`sysevent get dhcpclient_v6`" ]
        then
        	sysevent set dhcpclient_v4 0
		echo "[dhcpswitch.sh] dhcpclient_v4 event set to 0" >> $LOG_FILE
                else
                sysevent set dhcpclient_v4 0
                if [ -f $CRONTAB_FILE ]
                then
			RemoveCron
			echo "[dhcpswitch.sh] dhcpclient_v4 cron job removed" >> $LOG_FILE
		fi

        fi

        	sysevent set wan-stop
                sleep 2
                wait_till_state_wan_stopped

        	if [ "$MODEL_NUM" = "TG3482G" ]; then
                	systemctl stop dropbear-atom-js.service
                	echo "[dhcpswitch.sh] dropbear service stopped in clear_v4_cron" >> $LOG_FILE
        	fi
                syscfg set UDHCPEnable false
                syscfg commit
                sysevent set wan-start

        if [ "$MODEL_NUM" = "TG3482G" ]; then
                wait_till_state_wan_started
                systemctl start dropbear-atom-js.service
                echo "[dhcpswitch.sh] dropbear service started in clear_v4_cron" >> $LOG_FILE
        fi

fi

if [ "$1" = "clear_v6_cron" ]
then

	if [ "1" = "`sysevent get dhcpclient_v4`" ]
        then
        	sysevent set dhcpclient_v6 0
		echo "[dhcpswitch.sh] dhcpclient_v6 event set to 0" >> $LOG_FILE
        else
                sysevent set dhcpclient_v6 0
                if [ -f $CRONTAB_FILE ]
                then
			RemoveCron
			echo "[dhcpswitch.sh] dhcpclient_v6 cron job removed" >> $LOG_FILE
                fi
         fi

	        sysevent set wan-stop
                sleep 2
                wait_till_state_wan_stopped

                if [ "$MODEL_NUM" = "TG3482G" ]; then
                        systemctl stop dropbear-atom-js.service
                        echo "[dhcpswitch.sh] dropbear service stopped in clear_v6_cron" >> $LOG_FILE
                fi

        	syscfg set dibbler_client_enable false
                syscfg commit
                sysevent set wan-start

        if [ "$MODEL_NUM" = "TG3482G" ]; then
                wait_till_state_wan_started
                systemctl start dropbear-atom-js.service
                echo "[dhcpswitch.sh] dropbear service started in clear_v6_cron" >> $LOG_FILE
        fi

fi

if [ "$1" = "removecron" ]
then

		RemoveCron
		echo "[dhcpswitch.sh] scheduled cron job removed" >> $LOG_FILE

fi
