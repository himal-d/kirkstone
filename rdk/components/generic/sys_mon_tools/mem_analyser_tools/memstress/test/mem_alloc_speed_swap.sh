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

vmstat -n 300 > mem_alloc_speed_swap_vmstat.txt & 
./cpu_loadavg.sh > mem_alloc_speed_swap_laodavg.txt &
./memstress $RUN_TILL_DEATH $WAIT_AFTER_ALLOCATION $NUM_OF_THREADS $TOTAL_ALLOC_SIZE $ALLOC_BLOCK_SIZE $SLEEP_BW_ALLOCS $KEEP_MEM_HOT -- > mem_alloc_speed_swap_hot.txt &
./memstress $RUN_TILL_DEATH $WAIT_AFTER_ALLOCATION $NUM_OF_THREADS $TOTAL_ALLOC_SIZE $ALLOC_BLOCK_SIZE $SLEEP_BW_ALLOCS $KEEP_MEM_HOT2 -- > mem_alloc_speed_swapped_hot.txt &

echo "press any key when you think you are done\n"
read nothing

killall memstress
pkill vmstat
pkill cpu_loadavg.sh

