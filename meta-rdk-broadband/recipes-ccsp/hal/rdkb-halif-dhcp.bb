SUMMARY = "DHCP HAL"
HOMEPAGE = "https://github.com/rdkcentral/rdkb-halif-dhcp"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

SRC_URI = "git://github.com/rdkcentral/rdkb-halif-dhcp.git;protocol=https;branch=main"
SRCREV = "053d714fb8ddcb1d04c55808111fd032f355350b"

S = "${WORKDIR}/git"

CFLAGS_append = " -I=${includedir}/ccsp "

do_install () {
   install -d ${D}/usr/include/ccsp
   install -m 0644 ${S}/include/dhcp4cApi.h ${D}/usr/include/ccsp
   install -m 0644 ${S}/include/dhcpv4c_api.h ${D}/usr/include/ccsp
}

FILES_${PN} = " \
/usr/include/ccsp \
"
