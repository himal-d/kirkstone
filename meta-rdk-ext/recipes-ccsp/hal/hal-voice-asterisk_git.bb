SUMMARY = "Voice HAL for Asterisk IP PBX"
SECTION = "net"
LICENSE = "Apache-2.0"

LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

PV = "1.0.0+git${SRCPV}"

SRCREV = "${AUTOREV}"

SRC_URI = "git://github.com/rdkcentral/hal-voice-asterisk.git;branch=main;protocol=https \
    file://hal-voice-asterisk.service \
"

DEPENDS += "json-c json-hal-lib"
RDEPENDS_${PN} += "asterisk"

S = "${WORKDIR}/git"

inherit autotools systemd

do_install_append () {
    install -d ${D}${systemd_unitdir}/system
    install -D -m 0644 ${WORKDIR}/hal-voice-asterisk.service ${D}${systemd_unitdir}/system/hal-voice-asterisk.service
}

SYSTEMD_SERVICE_${PN} += "hal-voice-asterisk.service"
SYSTEMD_AUTO_ENABLE = "enable"

FILES_${PN} += " \
    /usr/bin/* \
    ${systemd_unitdir}/system/hal-voice-asterisk.service \
"
