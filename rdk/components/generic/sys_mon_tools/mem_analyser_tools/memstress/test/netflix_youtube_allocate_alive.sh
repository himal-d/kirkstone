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

# this script logs loadavg and vmstat and at the same time keeps 50MB of memory allocated and hot
# by using the memstress program. 

date
echo "sleep for 5 minutes to settle after reboot\n"
sleep 300

echo "sleeping done, press any key to start logging, you must start youtube and netflix activity immediately after logging starts\n"
echo "both these applications have to repeatedly cycled and cold start as well as resume time has to be noted\n"
read nothing
echo "staring logging"
date

# calculate output file names
SCRIPT_NAME=`basename "$0" | cut -d "." -f1`
VMSTAT_LOG_SUFFIX="_vmstat.txt"
LOADAVG_LOG_SUFFIX="_loadavg.txt"
MEMSTRESS_LOG_SUFFIX="_stress.txt"
VMSTAT_LOG_FILE=$SCRIPT_NAME$VMSTAT_LOG_SUFFIX
LOADAVG_LOG_FILE=$SCRIPT_NAME$LOADAVG_LOG_SUFFIX
MEMSTRESS_LOG_FILE=$SCRIPT_NAME$MEMSTRESS_LOG_SUFFIX

#memstress config
RUN_TILL_DEATH=""
WAIT_AFTER_ALLOCATION=""
NUM_OF_THREADS="-n 1"
#TOTAL_ALLOC_SIZE="-t 41943040" #40MB
TOTAL_ALLOC_SIZE="-t 52428800" #50MB
#TOTAL_ALLOC_SIZE="-t 104857600" #100MB
ALLOC_BLOCK_SIZE="-b 10240" # 10kb
SLEEP_BW_ALLOCS="-s 2000" # us sleep
KEEP_MEM_HOT="-k 500000" # keep it hot every 500ms for every 10kb block
WRITE_RANDOM_INTS="-a 1" # default is 1 which would mean write random ints

vmstat -n 1 > $VMSTAT_LOG_FILE & 
./cpu_loadavg.sh > $LOADAVG_LOG_FILE &
./memstress $RUN_TILL_DEATH $WAIT_AFTER_ALLOCATION $NUM_OF_THREADS $TOTAL_ALLOC_SIZE $ALLOC_BLOCK_SIZE $SLEEP_BW_ALLOCS $KEEP_MEM_HOT $WRITE_RANDOM_INTS -- > $MEMSTRESS_LOG_FILE &

echo "press any key when you think you are done\n"
read nothing

killall memstress
pkill vmstat
pkill cpu_loadavg.sh


