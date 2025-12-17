SUMMARY = "eMMC HAL"
HOMEPAGE = "https://github.com/rdkcentral/rdkb-halif-emmc"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

SRC_URI = "git://github.com/rdkcentral/rdkb-halif-emmc.git;protocol=https;branch=main"
SRCREV = "5c2cdc21e8f3e8ffc87d50f9cd1aef0c06cc7e3f"

S = "${WORKDIR}/git"

CFLAGS_append = " -I=${includedir}/ccsp "

do_install () {
   install -d ${D}/usr/include/ccsp
   install -m 0644 ${S}/include/ccsp_hal_emmc.h ${D}/usr/include/ccsp
}

FILES_${PN} = " \
/usr/include/ccsp \
"