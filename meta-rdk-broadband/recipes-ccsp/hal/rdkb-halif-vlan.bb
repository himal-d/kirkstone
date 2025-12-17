SUMMARY = "Vlan HAL"
HOMEPAGE = "https://github.com/rdkcentral/rdkb-halif-vlan"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

SRC_URI = "git://github.com/rdkcentral/rdkb-halif-vlan.git;protocol=https;branch=main"
SRCREV = "fc61170fd89ef245f4fed02d957ff2431fedc2ec"

S = "${WORKDIR}/git"

CFLAGS_append = " -I=${includedir}/ccsp "

do_install () {
   install -d ${D}/usr/include/ccsp
   install -m 0644 ${S}/include/vlan_hal.h ${D}/usr/include/ccsp
}

FILES_${PN} = " \
/usr/include/ccsp \
"
