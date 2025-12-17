SUMMARY = "DHCP6C HAL"
HOMEPAGE = "https://github.com/rdkcentral/rdkb-halif-dhcp6c"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

SRC_URI = "git://github.com/rdkcentral/rdkb-halif-dhcp6c.git;protocol=https;branch=main"
SRCREV = "4cdc21e58e9871bd63381eaeedd0df79726b97ab"

S = "${WORKDIR}/git"

CFLAGS_append = " -I=${includedir}/ccsp "

do_install () {
   install -d ${D}/usr/include/ccsp
   install -m 0644 ${S}/include/dhcp6cApi.h ${D}/usr/include/ccsp
}

FILES_${PN} = " \
/usr/include/ccsp \
"
