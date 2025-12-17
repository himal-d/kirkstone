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

# this file enables swap, take one parameter that is swap size eg bytes, 10M, 1G etc 
# eg. ./enable_swap.sh 419430400 will be about 400MB

if [ ! $# -eq 1 ]
then
	echo "Usage: need one parameter, amount of swap to create"
	exit 1 
fi
echo "creating swap of size $1"

fallocate -l $1 /media/tsb/swapfile
sleep 2 #make sure that the file done
mkswap /media/tsb/swapfile
chmod 600 /media/tsb/swapfile
swapon /media/tsb/swapfile
