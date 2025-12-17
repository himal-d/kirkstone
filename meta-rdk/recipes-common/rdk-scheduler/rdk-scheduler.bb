SUMMARY = "librdkscheduler component"
SECTION = "libs"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=a530f32d7e55cab43d8d35cf7ec07d1f"

DEPENDS_class-native = ""

RDEPENDS_${PN}_append_dunfell = " bash"

DEPENDS = "cimplog"

SRC_URI = "${RDK_GENERIC_ROOT_GIT}/rdkscheduler/generic;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH}"

SRCREV = "${AUTOREV}"
SRCREV_FORMAT = "${AUTOREV}"
PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

inherit autotools systemd pkgconfig

CFLAGS += " \
    -D_GNU_SOURCE -D__USE_XOPEN \
    "

CFLAGS += " -Wall -Werror -Wextra "

CFLAGS_append_dunfell = " -Wno-restrict -Wno-format-truncation -Wno-format-overflow -Wno-cast-function-type -Wno-unused-function -Wno-implicit-fallthrough "

LDFLAGS += " \
    -lcimplog \
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
	install -m 644 ${S}/source/*.h ${D}/usr/include/
}

do_install_class-native () {
    echo "Compile is skipped"
}

FILES_${PN} += "${libdir}/*.so"

BBCLASSEXTEND = "native"