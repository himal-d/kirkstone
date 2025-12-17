EXTRA_OECONF_append += " --enable-broadband-support "

DEPENDS += "breakpad-wrapper ccsp-common-library ccsp-lm-lite utopia"
LDFLAGS += "-lbreakpadwrapper -lccsp_common -llmapi -lutapi -lutctx"

do_install_append() {
    install -d ${D}${systemd_unitdir}/system ${D}${sysconfdir}
    install -m 0644 ${S}/conf/broadband/systemd/xupnp.service ${D}${systemd_unitdir}/system/xupnp.service
    install -m 0644 ${S}/conf/systemd/xdiscovery.conf ${D}${sysconfdir}
    install -m 0644 ${S}/conf/systemd/xdevice.conf ${D}${sysconfdir}
    install -m 0644 ${S}/conf/systemd/xcal-device.service ${D}${systemd_unitdir}/system/xcal-device.service
    install -m 0644 ${S}/conf/systemd/xupnp-firewall.service ${D}${systemd_unitdir}/system/xupnp-firewall.service
    install -m 0644 ${S}/conf/systemd/xcal-device.path ${D}${systemd_unitdir}/system/xcal-device.path
}

SYSTEMD_SERVICE_${PN} = "xupnp.service"
SYSTEMD_SERVICE_${PN}_append = " xcal-device.service"
SYSTEMD_SERVICE_${PN}_append = " xcal-device.path"
SYSTEMD_SERVICE_${PN}_append = " xupnp-firewall.service"
FILES_${PN} += "${systemd_unitdir}/system/xupnp.service"
FILES_${PN}_append = " ${systemd_unitdir}/system/xcal-device.service"
FILES_${PN}_append = " ${systemd_unitdir}/system/xcal-device.path"
FILES_${PN}_append = " ${systemd_unitdir}/system/xupnp-firewall.service"
