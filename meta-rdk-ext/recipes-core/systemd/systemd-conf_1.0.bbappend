
#Disable default journal conf settings.
do_install_append() {
     rm -rf ${D}${systemd_unitdir}/journald.conf.d
}
FILES:${PN}_remove = "${systemd_unitdir}/journald.conf.d/"

