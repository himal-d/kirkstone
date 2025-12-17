#!/bin/sh

#### To generate the server.pem by using openssl
#### For support HTTPS port in Remote Management

#Check that file exists and is empty
if [ ! -s /etc/server.pem ]; then
openssl req -newkey rsa:2048 -new -nodes -x509 -days 3650 -subj /C=IN/ST=TN/L=Bangalore/O=Example_Org/CN=*.example.org -keyout /tmp/key.pem -out /tmp/cert.pem
cat /tmp/key.pem > /etc/server.pem
cat /tmp/cert.pem >> /etc/server.pem
rm /tmp/key.pem /tmp/cert.pem
fi

##### set the value of eth_wan_mac #####
WAN_INTERFACE=`ifconfig erouter0 | grep erouter0 | wc -l`
if [ "x$WAN_INTERFACE" -eq "x1" ]; then
MACADDRESS=`ifconfig erouter0 | grep HWaddr | cut -d ' ' -f7`
sysevent set eth_wan_mac $MACADDRESS
fi
