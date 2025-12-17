SUMMARY = "MTA HAL"
HOMEPAGE = "https://github.com/rdkcentral/rdkb-halif-mta"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

SRC_URI = "git://github.com/rdkcentral/rdkb-halif-mta.git;protocol=https;branch=main"
SRCREV = "8a34fd2578e7921630222a4b50a418b378af15c3"

S = "${WORKDIR}/git"

CFLAGS_append = " -I=${includedir}/ccsp "

do_install () {
   install -d ${D}/usr/include/ccsp
   install -m 0644 ${S}/include/mta_hal.h ${D}/usr/include/ccsp
}

FILES_${PN} = " \
/usr/include/ccsp \
"