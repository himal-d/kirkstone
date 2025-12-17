# meta-rdk-matter/recipes-connectivity/bluez5/bluez5_5.66.bbappend

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

# Dependencies required for feature detection
DEPENDS += "json-c ell readline"
RDEPENDS:${PN} += "json-c"

inherit autotools pkgconfig systemd

# Enable desired BlueZ features
PACKAGECONFIG:append = " client mesh obex systemd udev tools experimental"

# Use only valid configure options — no legacy or Meson args
EXTRA_OECONF += " \
    --enable-datafiles \
    --enable-library \
    --enable-test \
    --enable-client \
    --enable-mesh \
    --enable-obex \
    --enable-tools \
    --enable-systemd \
    --enable-udev \
    --enable-experimental \
    --enable-shared \
    --libdir=${libdir} \
"

# Include your local configuration and service files
SRC_URI += " \
    file://default-bluetooth.conf \
    file://enable-hci.sh \
    file://bluetooth.service \
"

# Systemd integration
SYSTEMD_SERVICE:${PN} = "bluetooth.service"
SYSTEMD_AUTO_ENABLE = "enable"

do_install:append() {
    install -Dm644 ${WORKDIR}/default-bluetooth.conf ${D}${sysconfdir}/bluetooth/main.conf
    install -Dm755 ${WORKDIR}/enable-hci.sh ${D}${sbindir}/enable-hci.sh
    install -Dm644 ${WORKDIR}/bluetooth.service ${D}${systemd_system_unitdir}/bluetooth.service
}

# Include plugin paths — plugins get built into ${libdir}/bluetooth/
FILES:${PN} += " \
    ${sysconfdir}/bluetooth/main.conf \
    ${sbindir}/enable-hci.sh \
    ${systemd_system_unitdir}/bluetooth.service \
    ${libdir}/bluetooth/ \
"

