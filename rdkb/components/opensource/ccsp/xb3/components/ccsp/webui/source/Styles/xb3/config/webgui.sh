#! /bin/sh
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

#WEBGUI_SRC=/fss/gw/usr/www/html.tar.bz2
#WEBGUI_DEST=/var/www

#if test -f "$WEBGUI_SRC"
#then
#	if [ ! -d "$WEBGUI_DEST" ]; then
#		/bin/mkdir -p $WEBGUI_DEST
#	fi
#	/bin/tar xjf $WEBGUI_SRC -C $WEBGUI_DEST
#else
#	echo "WEBGUI SRC does not exist!"
#fi

# start lighttpd
LIGHTTPD_PID=`pidof lighttpd`
if [ "$LIGHTTPD_PID" != "" ]; then
	/bin/kill $LIGHTTPD_PID
fi

HTTP_ADMIN_PORT=`syscfg get http_admin_port`
HTTP_PORT=`syscfg get mgmt_wan_httpport`
HTTP_PORT_ERT=`syscfg get mgmt_wan_httpport_ert`
HTTPS_PORT=`syscfg get mgmt_wan_httpsport`
BRIDGE_MODE=`syscfg get bridge_mode`

if [ "$BRIDGE_MODE" != "0" ]; then
    INTERFACE="lan0"
else
    INTERFACE="brlan0"
fi


cp /etc/lighttpd.conf /var
#sed -i "s/^server.port.*/server.port = $HTTP_PORT/" /var/lighttpd.conf
#sed -i "s#^\$SERVER\[.*\].*#\$SERVER[\"socket\"] == \":$HTTPS_PORT\" {#" /var/lighttpd.conf

HTTP_SECURITY_HEADER_ENABLE=`syscfg get HTTPSecurityHeaderEnable`

if [ "$HTTP_SECURITY_HEADER_ENABLE" = "true" ]; then
        echo "setenv.add-response-header = (\"X-Frame-Options\" => \"deny\",\"X-XSS-Protection\" => \"1; mode=block\",\"X-Content-Type-Options\" => \"nosniff\",\"Content-Security-Policy\" => \"img-src 'self'; font-src 'self'; form-action 'self';\")"  >> /var/lighttpd.conf
fi

echo "server.port = $HTTP_ADMIN_PORT" >> /var/lighttpd.conf
echo "server.bind = \"$INTERFACE\"" >> /var/lighttpd.conf
echo "\$SERVER[\"socket\"] == \"wan0:80\" { server.use-ipv6 = \"enable\" }" >> /var/lighttpd.conf

if [ "x$HTTP_PORT_ERT" != "x" ];then
    echo "\$SERVER[\"socket\"] == \"erouter0:$HTTP_PORT_ERT\" { server.use-ipv6 = \"enable\" }" >> /var/lighttpd.conf
else
    echo "\$SERVER[\"socket\"] == \"erouter0:$HTTP_PORT\" { server.use-ipv6 = \"enable\" }" >> /var/lighttpd.conf
fi

echo "\$SERVER[\"socket\"] == \"$INTERFACE:443\" { server.use-ipv6 = \"enable\" ssl.engine = \"enable\" ssl.pemfile = \"/etc/server.pem\" }" >> /var/lighttpd.conf
echo "\$SERVER[\"socket\"] == \"wan0:443\" { server.use-ipv6 = \"enable\" ssl.engine = \"enable\" ssl.pemfile = \"/etc/server.pem\" }" >> /var/lighttpd.conf
if [ $HTTPS_PORT -ne 0 ]
then
    echo "\$SERVER[\"socket\"] == \"erouter0:$HTTPS_PORT\" { server.use-ipv6 = \"enable\" ssl.engine = \"enable\" ssl.pemfile = \"/etc/server.pem\" }" >> /var/lighttpd.conf
else
    # When the httpsport is set to NULL. Always put default value into database.
    syscfg set mgmt_wan_httpsport 8081
    syscfg commit
    HTTPS_PORT=`syscfg get mgmt_wan_httpsport`
    echo "\$SERVER[\"socket\"] == \"erouter0:$HTTPS_PORT\" { server.use-ipv6 = \"enable\" ssl.engine = \"enable\" ssl.pemfile = \"/etc/server.pem\" }" >> /var/lighttpd.conf
fi

SSID1_DEF=`cat /nvram/bbhm_cur_cfg.xml | grep Device.WiFi.Radio.SSID.1.SSID | cut -d">" -f 2 | cut -d "<" -f 1`
SSID2_DEF=`cat /nvram/bbhm_cur_cfg.xml | grep Device.WiFi.Radio.SSID.2.SSID | cut -d">" -f 2 | cut -d "<" -f 1`

PASSPHRASE1_DEF=`cat /nvram/bbhm_cur_cfg.xml | grep Device.WiFi.Radio.SSID.1.Passphrase | cut -d">" -f 2 | cut -d "<" -f 1`
PASSPHRASE2_DEF=`cat /nvram/bbhm_cur_cfg.xml | grep Device.WiFi.Radio.SSID.2.Passphrase | cut -d">" -f 2 | cut -d "<" -f 1`

SSID1_CUR=`dmcli eRT getv Device.WiFi.SSID.1.SSID | grep string, | awk '{print $5}'`
SSID2_CUR=`dmcli eRT getv Device.WiFi.SSID.2.SSID | grep string, | awk '{print $5}'`

PASSPHRASE1_CUR=`dmcli eRT getv Device.WiFi.AccessPoint.1.Security.X_CISCO_COM_KeyPassphrase | grep string, | awk '{print $5}'`
PASSPHRASE2_CUR=`dmcli eRT getv Device.WiFi.AccessPoint.2.Security.X_CISCO_COM_KeyPassphrase | grep string, | awk '{print $5}'`

 
WIFIUNCONFIGURED=`syscfg get redirection_flag`

if [ "$WIFIUNCONFIGURED" = "true" ]
then
	CONFIGFILEAVAIL=`ls /tmp/*walledgarden*`
	if [ "$CONFIGFILEAVAIL" = "" ]
	then
		if [ "$SSID1_DEF" == "$SSID1_CUR" ] ||  [ "$SSID2_DEF" == "$SSID2_CUR" ] 
		then
			dmcli eRT setvalues Device.DeviceInfo.X_RDKCENTRAL-COM_ConfigureWiFi bool TRUE
		elif [ "$PASSPHRASE1_DEF" == "$PASSPHRASE1_CUR" ] || [ "$PASSPHRASE2_DEF" == "$PASSPHRASE2_CUR" ]
		then
			dmcli eRT setvalues Device.DeviceInfo.X_RDKCENTRAL-COM_ConfigureWiFi bool TRUE
		else
			echo "WiFi is already configured"
		fi
	fi
fi		


echo "\$SERVER[\"socket\"] == \"$INTERFACE:10443\" { server.use-ipv6 = \"enable\" ssl.engine = \"enable\" ssl.pemfile = \"/etc/server.pem\" server.document-root = \"/fss/gw/usr/walled_garden/parcon/siteblk\" server.error-handler-404 = \"/index.php\" }" >> /var/lighttpd.conf
echo "\$SERVER[\"socket\"] == \"$INTERFACE:18080\" { server.use-ipv6 = \"enable\"  server.document-root = \"/fss/gw/usr/walled_garden/parcon/siteblk\" server.error-handler-404 = \"/index.php\" }" >> /var/lighttpd.conf

LD_LIBRARY_PATH=/fss/gw/usr/ccsp:$LD_LIBRARY_PATH lighttpd -f /var/lighttpd.conf
