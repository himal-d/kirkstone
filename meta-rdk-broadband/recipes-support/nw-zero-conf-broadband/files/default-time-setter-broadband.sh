#!/bin/sh

NTP_CONF_FILE=/tmp/ntp.conf

echo "server time.google.com true" >> ${NTP_CONF_FILE} 
echo "server time1.xfinity.com true" >> ${NTP_CONF_FILE}
echo "interface listen 127.0.0.1" >> ${NTP_CONF_FILE}
echo "interface listen erouter0"  >> ${NTP_CONF_FILE}
mount-copybind /tmp/dropbear /etc/dropbear/

#added a delay to start the dropbear
sleep 20
#systemctl start ntpd

# Start dropbear with read-write mount of /et/dropbear and listen on all interfaces

dropbear -v -R -B -p :22

#rdm service to be started once the device has network and Time is updated
# -q otion in ntpd : Exit the ntpd just after the first time the clock is set.

/usr/sbin/ntpd -u ntp:ntp -p /run/ntpd.pid -l /rdklogs/logs/ntpLog.log -c /tmp/ntp.conf -g -q

#File needed to start the apps-rdm service
if [ -f /nvram/ptestDnldLocation ]; then
	url=$(cat /nvram/ptTestDnldLocation)
	if [ ! -z "$url" ]; then
	    echo "$url" > /tmp/.xconfssrdownloadurl
	else
	    echo "https://dac15cdlserver.ae.ccp.xcal.tv/Images" > /tmp/.xconfssrdownloadurl
	fi
else
       echo "https://dac15cdlserver.ae.ccp.xcal.tv/Images" > /tmp/.xconfssrdownloadurl
fi

