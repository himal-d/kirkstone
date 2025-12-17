SUMMARY = "WAN HAL"
HOMEPAGE = "https://github.com/rdkcentral/rdkb-halif-wan"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

SRC_URI = "git://github.com/rdkcentral/rdkb-halif-wan.git;protocol=https;branch=main"
SRCREV = "8ea2a3e51bcf1ce922925c2c15091731f034cbeb"

S = "${WORKDIR}/git"

CFLAGS_append = " -I=${includedir}/ccsp "

do_install () {
   install -d ${D}/usr/include/ccsp
   install -m 0644 ${S}/include/wan_hal.h ${D}/usr/include/ccsp
}

FILES_${PN} = " \
/usr/include/ccsp \
"