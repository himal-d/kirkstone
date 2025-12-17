#!/bin/sh

#script to wait till the erouter0 get the link local
WAN_INTERFACE="erouter0"
loop=1

if [ ! -d /rdklogs/logs ]; then
         mkdir -p /rdklogs/logs
fi

while [ $loop -eq 1 ] 
do
    currentAddress=`ifconfig $WAN_INTERFACE | grep -i 'fe80:'`
    if [ ! -z "$currentAddress" ]; then
        echo "Got the link local address.Starting the LAN service"
        loop=0
        exit 0
    fi
done

