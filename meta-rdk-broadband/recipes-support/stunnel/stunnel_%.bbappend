DEPENDS_remove = "systemd"
SYSTEMD_SERVICE_${PN}_remove = "stunnel.service"
FILES_${PN}_remove = "/lib/systemd/system/stunnel.service"
PACKAGECONFIG_remove = "systemd"
