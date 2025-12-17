SUMMARY = "LPA HAL"
HOMEPAGE = "https://github.com/rdkcentral/rdkb-halif-lpa"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

SRC_URI = "git://github.com/rdkcentral/rdkb-halif-lpa.git;protocol=https;branch=main"
SRCREV = "de8397d3ebb98084cc33e89e39aa4d320098aef7"

S = "${WORKDIR}/git"

CFLAGS_append = " -I=${includedir}/ccsp "

do_install () {
   install -d ${D}/usr/include/ccsp
   install -m 0644 ${S}/include/lpa_hal.h ${D}/usr/include/ccsp
}

FILES_${PN} = " \
/usr/include/ccsp \
"
