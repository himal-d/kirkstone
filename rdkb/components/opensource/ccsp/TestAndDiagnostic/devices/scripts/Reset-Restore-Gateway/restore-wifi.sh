#!/bin/sh
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
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


############################## Restoring Wifi values for Private wifi and Xfinity-wifi 2.4Ghz  ######################

echo " *************** Entering into default wifi settings script *********** "

########################### Getting wireless interface names from hostapd configuration files ######

wifi_priv_2g=`grep interface= /nvram/hostapd0.conf | cut -d '=' -f2 | head -n1`
wifi_priv_5g=`grep interface= /nvram/hostapd1.conf | cut -d '=' -f2 | head -n1`
wifi_pub_2g=`grep interface= /nvram/hostapd4.conf | cut -d '=' -f2 | head -n1`
wifi_pub_5g=`grep interface= /nvram/hostapd5.conf | cut -d '=' -f2 | head -n1`

############# Restore default ssid ########################################
SSID=`cat /nvram/hostapd0.conf | grep ssid | head -1 | cut -d "=" -f2`
sed -i "29 s/ssid=$SSID/ssid=RDKB-EMU-2.4G/g" /nvram/hostapd0.conf
hostapd_cli -i $wifi_priv_2g SET ssid RDKB-EMU-2.4G

#XFINITY_SSID=`cat /nvram/hostapd0.conf | grep ssid | tail -1 | cut -d "=" -f2`
#sed -i "59 s/ssid=$XFINITY_SSID/ssid=Xfinity-Wifi-2.4G/g" /nvram/hostapd0.conf

XFINITY_SSID=`cat /nvram/hostapd4.conf | grep ssid | head -1 | cut -d "=" -f2`
sed -i "28 s/ssid=$XFINITY_SSID/ssid=Xfinity-Wifi-2.4G/g" /nvram/hostapd4.conf
hostapd_cli -i $wifi_pub_2g SET ssid Xfinity-Wifi-2.4G

################# Restore default password ################################
PASSWORD=`cat /nvram/hostapd0.conf | grep wpa_passphrase | cut -d "=" -f2`
sed -i  "s/wpa_passphrase=$PASSWORD/wpa_passphrase=2g-password/g" /nvram/hostapd0.conf    
hostapd_cli -i $wifi_priv_2g SET  wpa_passphrase 2g-password

#################### Restore default Channel ##################################
CHANNEL=`cat /nvram/hostapd0.conf | grep channel | cut -d "=" -f2`
sed -i  "s/channel=$CHANNEL/channel=6/g" /nvram/hostapd0.conf
hostapd_cli -i $wifi_priv_2g SET channel 6


########################## Reset Wifi  default values into PSM configuration files #########
dmcli simu psmsetv eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.SSID.1.HideSSID string 1
dmcli simu psmsetv eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.SSID.1.SSID string RDKB-EMU-2.4G
dmcli simu psmsetv eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.SSID.1.Passphrase string 2g-password
dmcli simu psmsetv eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.1.Channel uint 6


sleep 5
############################## Restoring Wifi values for Private wifi 5Ghz  ######################

############# Restore default ssid ########################################
SSID=`cat /nvram/hostapd1.conf | grep ssid | head -1 | cut -d "=" -f2`
sed -i "29 s/ssid=$SSID/ssid=RDKB-EMU-5G/g" /nvram/hostapd1.conf
hostapd_cli -i $wifi_priv_5g SET ssid RDKB-EMU-5G

################# Restore default password ################################
PASSWORD=`cat /nvram/hostapd1.conf | grep wpa_passphrase | cut -d "=" -f2`
sed -i  "s/wpa_passphrase=$PASSWORD/wpa_passphrase=5g-password/g" /nvram/hostapd1.conf
hostapd_cli -i $wifi_priv_5g SET wpa_passphrase 5g-password

#################### Restore default Channel ##################################
CHANNEL=`cat /nvram/hostapd1.conf | grep channel | cut -d "=" -f2`
sed -i  "s/channel=$CHANNEL/channel=36/g" /nvram/hostapd1.conf
hostapd_cli -i $wifi_priv_5g SET channel 36


########################## Reset Wifi  default values into PSM configuration files #########
dmcli simu psmsetv eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.SSID.2.HideSSID string 1
dmcli simu psmsetv eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.SSID.2.SSID string RDKB-EMU-5G
dmcli simu psmsetv eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.SSID.2.Passphrase string 5g-password
dmcli simu psmsetv eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.2.Channel uint 36


############################## Xfinity wifi for dual bands #####################################
dmcli simu psmsetv eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.SSID.5.HideSSID string 1
dmcli simu psmsetv eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.5.Channel uint 6
dmcli simu psmsetv eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.SSID.6.HideSSID string 1
dmcli simu psmsetv eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.SSID.5.SSID string Xfinity-Wifi-2.4G
dmcli simu psmsetv eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.SSID.6.SSID string Xfinity-Wifi-5G
dmcli simu psmsetv eRT.com.cisco.spvtg.ccsp.Device.WiFi.Radio.6.Channel uint 36

################################### Xfinity Wifi ############################################
SSID=`cat /nvram/hostapd5.conf | grep ssid | head -1 | cut -d "=" -f2`
sed -i "28 s/ssid=$SSID/ssid=Xfinity-Wifi-5G/g" /nvram/hostapd5.conf
hostapd_cli -i $wifi_pub_5g SET ssid Xfinity-Wifi-5G

CHANNEL=`cat /nvram/hostapd5.conf | grep channel | cut -d "=" -f2`
sed -i  "s/channel=$CHANNEL/channel=36/g" /nvram/hostapd5.conf
hostapd_cli -i $wifi_pub_5g SET channel 36

CHANNEL=`cat /nvram/hostapd4.conf | grep channel | cut -d "=" -f2`
sed -i  "s/channel=$CHANNEL/channel=6/g" /nvram/hostapd4.conf
hostapd_cli -i $wifi_pub_2g SET channel 6


# Disabling all the hostapd's

hostapd_cli -i $wifi_priv_2g DISABLE
hostapd_cli -i $wifi_priv_5g DISABLE
hostapd_cli -i $wifi_pub_2g DISABLE
hostapd_cli -i $wifi_pub_5g DISABLE

sleep 10
