#!/bin/sh
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
if [ -f /etc/device.properties ];then
     . /etc/device.properties
fi

DHCP_CONFIG_FILE="/etc/dibbler/client.conf"
DHCP_CONFIG_FILE_RFS="/etc/dibbler/client_back.conf"
DHCP_CONFIG_FILE_RUNTIME="/tmp/dibbler/client.conf"
DHCP_CONFIG_FILE_TMP="/tmp/dibbler/client-tmp.conf"
RDK_PATH="/lib/rdk"
interface=$ARM_INTERFACE

if [ "$interface" ] && [ -f /etc/dibbler/client_back.conf ];then
     sed -i "s/RDK-ESTB-IF/${interface}/g" /etc/dibbler/client_back.conf
fi
if [ ! -f /etc/dibbler/radvd.conf ];then touch /etc/dibbler/radvd.conf; fi
if [ ! -f /etc/dibbler/radvd.conf.old ];then touch /etc/dibbler/radvd.conf.old; fi
if [ -f /etc/os-release ];then
     if [ ! -f /tmp/dibbler/radvd.conf ];then touch /tmp/dibbler/radvd.conf; fi
     if [ ! -f /tmp/dibbler/radvd.conf.old ];then touch /tmp/dibbler/radvd.conf.old; fi
fi

if [ -f "$DHCP_CONFIG_FILE_RUNTIME" ]; then
      rm -rf $DHCP_CONFIG_FILE_RUNTIME
fi
if [ -f "$DHCP_CONFIG_FILE_TMP" ]; then
    rm -rf $DHCP_CONFIG_FILE_TMP
fi
sed '$d' $DHCP_CONFIG_FILE_RFS > $DHCP_CONFIG_FILE_TMP
echo >> $DHCP_CONFIG_FILE_TMP
echo "}" >> $DHCP_CONFIG_FILE_TMP
sed -i "1i script \"/lib/rdk/client-notify.sh\"" $DHCP_CONFIG_FILE_TMP
TMP=""
if [ "$TMP" = "true" ]         
then
IPv6subPrefix=56
sed -i "8i { prefix ::/56 }" $DHCP_CONFIG_FILE_TMP               
else
IPv6subPrefix=64
sed -i "8i { prefix ::/64 }" $DHCP_CONFIG_FILE_TMP
fi

ln -s $DHCP_CONFIG_FILE_TMP $DHCP_CONFIG_FILE_RUNTIME
