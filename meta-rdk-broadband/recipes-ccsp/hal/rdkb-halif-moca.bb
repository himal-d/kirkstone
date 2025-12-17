SUMMARY = "Moca HAL"
HOMEPAGE = "https://github.com/rdkcentral/rdkb-halif-moca"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

SRC_URI = "git://github.com/rdkcentral/rdkb-halif-moca.git;protocol=https;branch=main"
SRCREV = "48ff5d73312cf8fcc0e246c5e527d790035d8317"

S = "${WORKDIR}/git"

CFLAGS_append = " -I=${includedir}/ccsp "

do_install () {
   install -d ${D}/usr/include/ccsp
   install -m 0644 ${S}/include/moca_hal.h ${D}/usr/include/ccsp
}

FILES_${PN} = " \
/usr/include/ccsp \
"
