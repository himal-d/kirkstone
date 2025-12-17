DESCRIPTION = "CoreNetLib"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=da3321fa688dcb066faa5080b7d1b009"

SRC_URI = "${RDKB_CCSP_CPC_ROOT_GIT}/CoreNetLib/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=CoreNetLib"
SRCREV_CoreNetLib = "${AUTOREV}"
SRCREV_FORMAT = "CoreNetLib"
S = "${WORKDIR}/git"

DEPENDS = " libnl ccsp-common-library "

inherit autotools pkgconfig

do_install_append() {
        install -d ${D}/usr/include/ccsp
	install -m 0644 ${S}/source/libnet.h ${D}/usr/include/ccsp
}

DEPENDS_remove_class-native = " safec-native"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"
CFLAGS_append = " -I${STAGING_INCDIR}/ -I${STAGING_INCDIR}/ccsp  -I${STAGING_INCDIR}/libsafec "
LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"

CPPFLAGS_append = " -I${STAGING_INCDIR}/ -I${STAGING_INCDIR}/ccsp  -I${STAGING_INCDIR}/libsafec "
CPPFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"
CPPFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"