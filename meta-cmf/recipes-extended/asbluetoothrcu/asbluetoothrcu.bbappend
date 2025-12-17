inherit coverity
SYSLOG-NG_FILTER = "blercudeamon"
SYSLOG-NG_SERVICE_blercudeamon = "sky-bluetoothrcu.service"
SYSLOG-NG_DESTINATION_blercudeamon = "blercudaemon.log"
SYSLOG-NG_LOGRATE_blercudeamon = "low"

# Unpin the SRCREV to build tip
SRCREV_blercudaemon = "${AUTOREV}"
