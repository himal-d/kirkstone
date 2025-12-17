SUMMARY = "Cellular Modem HAL"
HOMEPAGE = "https://github.com/rdkcentral/rdkb-halif-cellular-modem"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

SRC_URI = "git://github.com/rdkcentral/rdkb-halif-cellular-modem.git;protocol=https;branch=main"
SRCREV = "4422ee385c5bc5109e17d10904af3bc87a39fefc"

S = "${WORKDIR}/git"

CFLAGS_append = " -I=${includedir}/ccsp "

do_install () {
   install -d ${D}/usr/include/ccsp
   install -m 0644 ${S}/include/cellular_modem_hal_api.h ${D}/usr/include/ccsp
}

FILES_${PN} = " \
/usr/include/ccsp \
"
