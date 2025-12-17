SYSTEMD_PACKAGES_remove = "${PN} ${PN}-bgpd ${PN}-isisd ${PN}-ospf6d ${PN}-ospfd ${PN}-ripd ${PN}-ripngd"
SYSTEMD_SERVICE_${PN}-bgpd_remove = "bgpd.service"
SYSTEMD_SERVICE_${PN}-isisd_remove = "isisd.service"
SYSTEMD_SERVICE_${PN}-ospf6d_remove = "ospf6d.service"
SYSTEMD_SERVICE_${PN}-ospfd_remove = "ospfd.service"
SYSTEMD_SERVICE_${PN}-ripd_remove = "ripd.service"
SYSTEMD_SERVICE_${PN}-ripngd_remove = "ripngd.service"
SYSTEMD_SERVICE_${PN}_remove = "zebra.service"

RDEPENDS_${PN}_remove = "${PN}-bgpd ${PN}-isisd ${PN}-ospf6d ${PN}-ospfd ${PN}-ripd ${PN}-ripngd"

do_install_append() {
    rm -rf ${D}${base_libdir}
    rm -r ${D}${sysconfdir}/quagga/*.conf.sample
}

