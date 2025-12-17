SUMMARY = "Static Multicast Routing Daemon v2.4.4"
DESCRIPTION = "SMCRoute is a daemon and command line tool to manipulate the multicast routing table in the UNIX kernel."
HOMEPAGE = "http://troglobit.github.io/smcroute.html"
SECTION = "console/network"
LICENSE = "GPLv2+"

LIC_FILES_CHKSUM = "file://COPYING;md5=751419260aa954499f7abaabaa882bbe"
SRCREV = "a8e5847e5f7e411be424f9b52a6cdf9d2ed4aeb5"
SRC_URI = "git://github.com/troglobit/smcroute.git;branch=master;protocol=git"
DEPENDS += " systemd"

S = "${WORKDIR}/git"
inherit autotools systemd

do_configure_prepend() {
    export PKG_CONFIG=${STAGING_DIR_NATIVE}${bindir}/pkg-config
}

do_compile_prepend() {
    install -d ${B}/lib
}

SYSTEMD_SERVICE_${PN} += "smcroute.service"
