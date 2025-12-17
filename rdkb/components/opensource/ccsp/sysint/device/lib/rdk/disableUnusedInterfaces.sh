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

if [ "$DEVICE_TYPE" = "hybrid" ];then

    if [ "$PODNET_INTERFACE" != "" ]; then
        interface=`ls /sys/class/net | grep $PODNET_INTERFACE`
        if [ "$interface" != "" ]; then
            #Bringing down podnet0 interface
            ifconfig $PODNET_INTERFACE down
        fi
    fi
fi

if [ "$ETHERNET_INTERFACE" != "" ]; then
    interface=`ls /sys/class/net | grep $ETHERNET_INTERFACE`
    if [ "$interface" != "" ] && [ "$BUILD_TYPE" = "prod" ]; then   
        #bringing down eth0 interface for production images
        ifconfig $ETHERNET_INTERFACE down
    fi
fi


