SUMMARY = "A safec wrapper definition header file"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI = "file://safec_lib.h"

do_install() {
 install -d ${D}${includedir}
 install -m 0755 ${WORKDIR}/safec_lib.h ${D}${includedir}/
}

#SDK generation fails if there is no default package
ALLOW_EMPTY_${PN} = "1"
