SUMMARY = "libwebconfig_framework component"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=bc21fa26f9718980827123b8b80c0ded"

DEPENDS = "rbus"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"
DEPENDS_class-native = ""

RDEPENDS_${PN}_append = " bash"
RDEPENDS_${PN}_remove_morty = "bash"

SRC_URI = "${RDK_GENERIC_ROOT_GIT}/WebconfigFramework/generic;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH}"

SRCREV = "${AUTOREV}"
SRCREV_FORMAT = "${AUTOREV}"
PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

inherit autotools systemd pkgconfig

#skip package renaming
DEBIAN_NOAUTONAME_${PN} = "1"
DEBIAN_NOAUTONAME_${PN}-dev = "1"
DEBIAN_NOAUTONAME_${PN}-dbg = "1"

CFLAGS += " \
    -D_GNU_SOURCE -D__USE_XOPEN \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/rbus \
    -I${STAGING_INCDIR}/rtmessage \
    "

CFLAGS += " -Wall -Werror -Wextra "

CFLAGS_append = " -Wno-restrict -Wno-format-truncation -Wno-format-overflow -Wno-cast-function-type -Wno-unused-function -Wno-implicit-fallthrough "

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'webconfig_bin', '-DWEBCONFIG_BIN_SUPPORT', '', d)}"

LDFLAGS += " \
    -lrbuscore \
    -lrtMessage \
    -lrbus \
    "

do_configure_class-native () {
    echo "Configure is skipped"
}

do_compile_class-native () {
    echo "Compile is skipped"
}

do_install_append_class-target () {
    install -d ${D}/usr/include/
    install -m 644 ${S}/include/*.h ${D}/usr/include/

}

do_install_class-native () {
    echo "Compile is skipped"
}

FILES_${PN} += "${libdir}/*.so"

BBCLASSEXTEND = "native"
