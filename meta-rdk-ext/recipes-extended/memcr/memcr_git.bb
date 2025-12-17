LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=0ba16794955006770904e8293abcbee5"

HOMEPAGE = "https://github.com/LibertyGlobal/memcr"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI = "git://git@github.com/LibertyGlobal/memcr.git;branch=main;protocol=ssh"
SRC_URI += " file://memcr.service"

INSANE_SKIP_${PN} += "ldflags"

PV = "1.0+git${SRCPV}"
# Code base from 07.06.2024
SRCREV = "dfeaa806a4a95aa5f7fd0cbbe861877eb60d133a"

DEPENDS += " util-linux-native lz4 openssl"
RDEPENDS_${PN} = "libcrypto lz4"

S = "${WORKDIR}/git"

inherit systemd

SYSTEMD_SERVICE_${PN} = "memcr.service"
SYSTEMD_AUTO_ENABLE = "enable"

do_compile () {
	oe_runmake COMPRESS_LZ4=1 CHECKSUM_MD5=1 ENCRYPT=1
}

do_install () {
	install -D -m 755 ${B}/memcr  ${D}${bindir}/memcr
	install -D -m 755 ${B}/parasite.bin  ${D}${bindir}/parasite.bin
	install -D -m 755 ${B}/memcr-client  ${D}${bindir}/memcr-client
	install -d ${D}${libdir}/memcr
	install -D -m 644 ${B}/libencrypt.so ${D}${libdir}/memcr/libencrypt.so
	install -d ${D}${systemd_unitdir}/system
	install -m 0644 ${WORKDIR}/memcr.service ${D}${systemd_unitdir}/system
}

FILES_${PN} += "${systemd_unitdir}/system/memcr.service"
FILES_${PN} += "${bindir}/memcr ${bindir}/parasite.bin ${bindir}/memcr-client"
FILES_${PN} += "${libdir}/memcr/libencrypt.so"
