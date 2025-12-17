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

# this script is written to test SWAP and ZSWAP use cases.  
# it will run forever if left standalone and there is enough ram, press any key to exit 
# this starts two different instancs and trying to keep both hot at a different rate
# script is mostly useless in testing as we can never know what values of hotenes will
# actually simulate a practical scnearion. 


# calculate output file names
SCRIPT_NAME=`basename "$0" | cut -d "." -f1`
VMSTAT_LOG_SUFFIX="_vmstat.txt"
LOADAVG_LOG_SUFFIX="_loadavg.txt"
MEMSTRESS_LOG_SUFFIX="_stress.txt"
VMSTAT_LOG_FILE=$SCRIPT_NAME$VMSTAT_LOG_SUFFIX
LOADAVG_LOG_FILE=$SCRIPT_NAME$LOADAVG_LOG_SUFFIX
MEMSTRESS_LOG_FILE=$SCRIPT_NAME$MEMSTRESS_LOG_SUFFIX

RUN_TILL_DEATH=""
WAIT_AFTER_ALLOCATION=""
NUM_OF_THREADS="-n 1"
TOTAL_ALLOC_SIZE="-t 180229440" #170MB
ALLOC_BLOCK_SIZE="-b 102400" # 100kb
#ALLOC_BLOCK_SIZE="-b 1048576" # 1MB
#ALLOC_BLOCK_SIZE="-b 2097152" # 2MB
SLEEP_BW_ALLOCS="-s 20000" # ms sleep
KEEP_MEM_HOT="-k 50000" # keep it hot every 50ms for every 100kb block
KEEP_MEM_HOT2="-k 400000" 

vmstat -n 1 > $VMSTAT_LOG_FILE &
./cpu_loadavg.sh > $LOADAVG_LOG_FILE &
./memstress $RUN_TILL_DEATH $WAIT_AFTER_ALLOCATION $NUM_OF_THREADS $TOTAL_ALLOC_SIZE $ALLOC_BLOCK_SIZE $SLEEP_BW_ALLOCS $KEEP_MEM_HOT -- > $MEMSTRESS_LOG_FILE_1 &
./memstress $RUN_TILL_DEATH $WAIT_AFTER_ALLOCATION $NUM_OF_THREADS $TOTAL_ALLOC_SIZE $ALLOC_BLOCK_SIZE $SLEEP_BW_ALLOCS $KEEP_MEM_HOT2 -- > $MEMSTRESS_LOG_FILE_2 &

echo "press any key when you think you are done\n"
read nothing

killall memstress
pkill vmstat
pkill cpu_loadavg.sh

