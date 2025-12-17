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

RUN_TILL_DEATH=
WAIT_AFTER_ALLOCATION=
NUM_OF_THREADS="-n 1"
TOTAL_ALLOC_SIZE="-t 104857600" # 1024*1024*100 100MB
ALLOC_BLOCK_SIZE="-b 102400" # 100kb
SLEEP_BW_ALLOCS="-s 0" # usecs
KEEP_MEM_HOT="-k 100" # usecs 

echo "running with $RUN_TILL_DEATH $WAIT_AFTER_ALLOCATION $NUM_OF_THREADS $TOTAL_ALLOC_SIZE $ALLOC_BLOCK_SIZE $SLEEP_BW_ALLOCS $KEEP_MEM_HOT"
./memstress $RUN_TILL_DEATH $WAIT_AFTER_ALLOCATION $NUM_OF_THREADS $TOTAL_ALLOC_SIZE $ALLOC_BLOCK_SIZE $SLEEP_BW_ALLOCS $KEEP_MEM_HOT -- > ./allocate_keep_busy.txt

