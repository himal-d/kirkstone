#!/bin/sh
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2017 RDK Management
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

. /etc/device.properties

if [ ! -d $CORE_PATH ]; then     
     mkdir -p $CORE_PATH
fi

echo "$1 crash and uploading the cores" >> $LOG_PATH/core_log.txt

echo "Dump Created" >> $LOG_PATH/core_log.txt
gzip -f > /mnt/memory/corefiles/$3_core.prog_$1.signal_$2.gz
touch /tmp/.core_dump

       

