FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

DESCRIPTION = "Network Zero Config"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COREBASE}/../meta-rdk/licenses/Apache-2.0;md5=3b83ef96387f14655fc854ddc3c6bd57"

inherit systemd

SRC_URI += "file://iface-setup-broadband.service \
            file://default-time-setter-broadband.sh \
            file://board-access-broadband.service \
            file://board_access-broadband.sh \
           "

do_install_append() {
    install -d ${D}${systemd_unitdir}/system
    install -d ${D}${base_libdir}/rdk
    install -m 0644 ${WORKDIR}/iface-setup-broadband.service ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/board-access-broadband.service ${D}${systemd_unitdir}/system
    install -m 0755 ${WORKDIR}/board_access-broadband.sh ${D}${base_libdir}/rdk/

    # Override the default time setter script which is too dependent on configs and entries from sysint
    install -m 0755 ${WORKDIR}/default-time-setter-broadband.sh ${D}${base_libdir}/rdk/
}

SYSTEMD_SERVICE_${PN} = "board-access-broadband.service iface-setup-broadband.service" 

FILES_${PN} = " ${base_libdir}/rdk/default-time-setter-broadband.sh \
                ${base_libdir}/rdk/board_access-broadband.sh "
