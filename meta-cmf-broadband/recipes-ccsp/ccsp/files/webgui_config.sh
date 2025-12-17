#! /bin/sh
##########################################################################
# If not stated otherwise in this file or this component's LICENSE
# file the following copyright and licenses apply:
#
# Copyright 2015 RDK Management
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
#######################################################################
#   Copyright [2014] [Cisco Systems, Inc.]
#
#   Licensed under the Apache License, Version 2.0 (the \"License\");

source /etc/device.properties

HTTP_ADMIN_PORT=`syscfg get http_admin_port`
HTTP_PORT=`syscfg get mgmt_wan_httpport`
HTTP_PORT_ERT=`syscfg get mgmt_wan_httpport_ert`
HTTPS_PORT=`syscfg get mgmt_wan_httpsport`
BRIDGE_MODE=`syscfg get bridge_mode`
LAN_IPADDR=`syscfg get lan_ipaddr`
LOCAL_DOMAIN=`syscfg get SecureWebUI_LocalFqdn`
SECUREWEBUI_ENABLE=`syscfg get SecureWebUI_Enable`
NAMESERVERENCHK=`syscfg get dhcp_nameserver_enabled`
ethWanEnabled=`syscfg get eth_wan_enabled`

if [ "$BRIDGE_MODE" != "0" ]; then
    INTERFACE="lan0"
else
    INTERFACE="brlan0"
    LAN_IPADDR_V6=`sysevent get lan_ipaddr_v6`
fi

if [ "$BOX_TYPE" == "HUB4" ]; then
    echo "setenv.add-environment = (\"LANG\" => \"$LOCALE\")"
fi
HTTP_SECURITY_HEADER_ENABLE=`syscfg get HTTPSecurityHeaderEnable`

if [ "$HTTP_SECURITY_HEADER_ENABLE" = "true" ]; then
    echo "setenv.add-response-header = (" 
    echo "    \"X-Frame-Options\" => \"deny\"," 
    echo "    \"X-XSS-Protection\" => \"1; mode=block\"," 
    echo "    \"X-Content-Type-Options\" => \"nosniff\"," 
    echo "    \"Strict-Transport-Security\" => \"max-age=15768000; includeSubdomains\","
    echo "    \"Pragma\" => \"no-cache\","
    echo "    \"Cache-Control\" => \"no-store, no-cache, must-revalidate\","
    echo "    \"Content-Security-Policy\" => \"default-src 'self' 'unsafe-inline' 'unsafe-eval'; style-src 'self' 'unsafe-inline' 'unsafe-eval'; frame-src 'self' 'unsafe-inline' 'unsafe-eval'; font-src 'self' 'unsafe-inline' 'unsafe-eval'; form-action 'self' 'unsafe-inline' 'unsafe-eval'; script-src 'self' 'unsafe-inline' 'unsafe-eval'; img-src 'self'; connect-src 'self'; object-src 'none'; media-src 'none'; script-nonce 'none'; plugin-types 'none'; reflected-xss 'none'; report-uri 'none';\"," 
    echo ")" 
    echo "#sandbox 'allow-same-origin allow-scripts allow-popups allow-forms';" 
fi

echo "server.port = $HTTP_ADMIN_PORT "
echo "server.bind = \"$INTERFACE\""

if [ "$SECUREWEBUI_ENABLE" = "true" ]
    then
        if [ "$BRIDGE_MODE" = "0" ]; then
            #syscfg set dhcp_nameserver_enabled 1
            #syscfg set dhcpv6spool00::X_RDKCENTRAL_COM_DNSServersEnabled 1
            #syscfg commit
            echo -e "\$SERVER[\"socket\"] == \"$INTERFACE:80\" {\n     server.use-ipv6 = \"enable\"\n     \$HTTP[\"host\"] =~ \"$LAN_IPADDR\" {\n        url.redirect = (\".*\" => \"https://$LOCAL_DOMAIN/\$1\")\n        url.redirect-code = \"307\"\n  }\n      \$HTTP[\"host\"] =~ \"$LOCAL_DOMAIN\" {\n        url.redirect = (\".*\" => \"https://$LOCAL_DOMAIN/\$1\")\n        url.redirect-code = \"307\"\n  }\n}"
        fi
fi

if [ "x$HTTP_PORT_ERT" != "x" ] && [ $HTTP_PORT_ERT -ne 0 ] && [ "$HTTP_PORT_ERT" -ge 1025 ] && [ "$HTTP_PORT_ERT" -le 65535 ];then
    echo "\$SERVER[\"socket\"] == \"erouter0:$HTTP_PORT_ERT\" { server.use-ipv6 = \"enable\" }"
else
    echo "\$SERVER[\"socket\"] == \"erouter0:$HTTP_PORT\" { server.use-ipv6 = \"enable\" }"
fi

if [ "$SECUREWEBUI_ENABLE" = "true" ] && [ "$BRIDGE_MODE" = "0" ]
then
    echo -e "\$SERVER[\"socket\"] == \"$INTERFACE:443\" {\n    server.use-ipv6 = \"enable\"\n    ssl.engine = \"enable\"\n    ssl.pemfile = \"/etc/server.pem\"\n    ssl.ca-file = \"/etc/server.pem\"\n    \$HTTP[\"host\"] =~ \"$LAN_IPADDR\" {\n        url.redirect = (\".*\" => \"https://$LOCAL_DOMAIN/\$1\")\n        url.redirect-code = \"307\"\n  }\n}" 
else
    echo "\$SERVER[\"socket\"] == \"$INTERFACE:443\" { server.use-ipv6 = \"enable\" ssl.engine = \"enable\" ssl.pemfile = \"/etc/server.pem\" }"
fi

#If video analytics test is enabled in device.properties file and XI is connected, open 58081 securely.
if [ "$BRIDGE_MODE" == "0" ] && [ "$VIDEO_ANALYTICS" = "enabled" ] && [ "x$LAN_IPADDR_V6" != "x" ] && grep -q "\"recvDevType\":\"mediaclient\"" /nvram/output.json
then
    echo "\$SERVER[\"socket\"] == \"[$LAN_IPADDR_V6]:58081\" { server.use-ipv6 = \"enable\" server.document-root = \"/usr/video_analytics\" ssl.engine = \"enable\" ssl.verifyclient.activate = \"enable\" ssl.ca-file = \"/etc/webui/certs/comcast-rdk-ca-chain.cert.pem\" ssl.pemfile = \"/tmp/.webui/rdkb-video.pem\" }"
    echo "\$SERVER[\"socket\"] == \"$LAN_IPADDR:58081\" { server.document-root = \"/usr/video_analytics\" ssl.engine = \"enable\" ssl.verifyclient.activate = \"enable\" ssl.ca-file = \"/etc/webui/certs/comcast-rdk-ca-chain.cert.pem\" ssl.pemfile = \"/tmp/.webui/rdkb-video.pem\" }"
    touch /tmp/videoanalytic_started
fi

if [ "x$ethWanEnabled" = "xtrue" ] && [ "$BOX_TYPE" != "HUB4" ];then
    echo "\$SERVER[\"socket\"] == \"erouter0:80\" { server.use-ipv6 = \"enable\" }" 
    echo "\$SERVER[\"socket\"] == \"erouter0:443\" { server.use-ipv6 = \"enable\" ssl.engine = \"enable\" ssl.pemfile = \"/etc/server.pem\" }" 

fi

if [ $HTTPS_PORT -ne 0 ] && [ "$HTTPS_PORT" -ge 1025 ] && [ "$HTTPS_PORT" -le 65535 ]
then
  echo "\$SERVER[\"socket\"] == \"erouter0:$HTTPS_PORT\" { server.use-ipv6 = \"enable\" ssl.engine = \"enable\" ssl.pemfile = \"/etc/server.pem\" }"
else
    # When the httpsport is set to NULL. Always put default value into database.
    syscfg set mgmt_wan_httpsport 8181
    syscfg commit
    HTTPS_PORT=`syscfg get mgmt_wan_httpsport`
    echo "\$SERVER[\"socket\"] == \"erouter0:$HTTPS_PORT\" { server.use-ipv6 = \"enable\" ssl.engine = \"enable\" ssl.pemfile = \"/etc/server.pem\" }"
fi

echo "\$SERVER[\"socket\"] == \"$INTERFACE:21515\" { server.use-ipv6 = \"enable\" server.document-root = \"/tmp/pcontrol/\" url.rewrite-if-not-file = (\"^/(.*)$\" => \"/index.html?fwd=$1\") url.access-deny =(\".inc\" )  }"
