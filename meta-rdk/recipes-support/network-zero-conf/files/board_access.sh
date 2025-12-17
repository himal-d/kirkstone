#File needed to start the apps-rdm service
if [ -f /opt/ptestDnldLocation ]; then
    url=$(cat /opt/ptTestDnldLocation)
    if [ ! -z "$url" ]; then
         echo "$url" > /tmp/.xconfssrdownloadurl
    else
         echo "https://dac15cdlserver.ae.ccp.xcal.tv/Images" > /tmp/.xconfssrdownloadurl
    fi
else	
    echo "https://dac15cdlserver.ae.ccp.xcal.tv/Images" > /tmp/.xconfssrdownloadurl
fi

# Add public dns servers to /etc/resolv.dnsmasq [ Ideally this would be set by DHCP clients ]
RESOLV_CONF_FILE="/etc/resolv.dnsmasq"
# Add google dns servers to the list
echo "nameserver 2001:4860:4860::8888" >> $RESOLV_CONF_FILE
echo "nameserver 2001:4860:4860::8844" >> $RESOLV_CONF_FILE
echo "nameserver 8.8.8.8" >> $RESOLV_CONF_FILE    
echo "nameserver 8.8.4.4" >> $RESOLV_CONF_FILE 

# Start dropbear with read-write mount of /et/dropbear and listen on all interfaces
mount-copybind /tmp/dropbear /etc/dropbear/

dropbear -v -R -B -p :22
