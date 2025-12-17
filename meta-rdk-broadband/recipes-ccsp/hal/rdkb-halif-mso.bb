SUMMARY = "MSO Mgmt HAL"
HOMEPAGE = "https://github.com/rdkcentral/rdkb-halif-mso"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

SRC_URI = "git://github.com/rdkcentral/rdkb-halif-mso.git;protocol=https;branch=main"
SRCREV = "e907b9323408fd6a6596208e162f3033060579fb"

S = "${WORKDIR}/git"

CFLAGS_append = " -I=${includedir}/ccsp "

do_install () {
   install -d ${D}/usr/include/ccsp
   install -m 0644 ${S}/include/mso_mgmt_hal.h ${D}/usr/include/ccsp
}

FILES_${PN} = " \
/usr/include/ccsp \
"
