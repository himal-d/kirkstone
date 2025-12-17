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

# this script uses the memstress program to alloate a certain amount of memory
# memset it to const number and exit once it is done
# the total block size should be set to about 30MB less than max number that you got from
# oom size finder script as last 30 or so MB will be extremely slow. It is better to find 
# /proc/sys/vm/min_free_kbytes and reduce that from maximum from speedtest to get the best 
# results.


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
TOTAL_ALLOC_SIZE="-t 280742400" #
ALLOC_BLOCK_SIZE="-b 102400" # 100kb
#ALLOC_BLOCK_SIZE="-b 1048576" # 1MB
#ALLOC_BLOCK_SIZE="-b 2097152" # 2MB
SLEEP_BW_ALLOCS="-s 0" #don't sleep
KEEP_MEM_HOT="-k 0" #don't keep it hot
WRITE_RANDOM_INTS="-a 0" # default is 1 which would mean write random ints, here we want const written memory

vmstat -n 1 > $VMSTAT_LOG_FILE &
./cpu_loadavg.sh > $LOADAVG_LOG_FILE &
./memstress $RUN_TILL_DEATH $WAIT_AFTER_ALLOCATION $NUM_OF_THREADS $TOTAL_ALLOC_SIZE $ALLOC_BLOCK_SIZE $SLEEP_BW_ALLOCS $KEEP_MEM_HOT $WRITE_RANDOM_INTS -- > $MEMSTRESS_LOG_FILE
pkill vmstat
pkill cpu_loadavg.sh

