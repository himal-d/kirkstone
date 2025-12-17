SUMMARY = "RFC helper applications"
SECTION = "console/utils"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

PACKAGECONFIG ??= "rfctool"
PACKAGECONFIG[rfctool] = "--enable-rfctool=yes"

SRC_URI = "${CMF_GIT_ROOT}/rdk/components/generic/rfc;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=rfc"

S = "${WORKDIR}/git"
PV = "${RDK_RELEASE}+git${SRCPV}"
SRCREV_rfc = "${AUTOREV}"
SRCREV_FORMAT = "rfc"

export cjson_CFLAGS = "-I$(PKG_CONFIG_SYSROOT_DIR)${includedir}/cjson"
export cjson_LIBS = "-lcjson"

DEPENDS="cjson curl rdk-logger"
EXTRA_OEMAKE += "-e MAKEFLAGS="

inherit autotools pkgconfig coverity

CFLAGS += " -Wall -Werror -Wextra "

do_install_append () {
	install -d ${D}${base_libdir}/rdk
        install -d ${D}${sysconfdir}

        install -m 0755 ${S}/RFCbase.sh ${D}${base_libdir}/rdk
        install -m 0755 ${S}/rfcInit.sh ${D}${base_libdir}/rdk
        install -m 0755 ${S}/RFCpostprocess.sh ${D}${base_libdir}/rdk
        install -m 0644 ${S}/rfc.properties ${D}${sysconfdir}
	install -m 0755 ${S}/RFC_Reboot.sh ${D}${sysconfdir}/RFC_Reboot.sh
}

RDEPENDS_${PN} += "busybox"

DEPENDS += "${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', ' gtest gmock', '', d)}"
PACKAGES =+ "${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', '${PN}-gtest', '', d)}"

FILES_${PN}-gtest = "\
    ${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', '${bindir}/rfc_gtest.bin', '', d)} \
"
FILES_${PN} += "${bindir}/rfctool"
FILES_${PN} += "${base_libdir}/*"
FILES_${PN} += "${sysconfdir}/*"

DOWNLOAD_APPS="${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', 'gtestapp-rfc', '', d)}"
inherit comcast-package-deploy
CUSTOM_PKG_EXTNS="${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', 'gtest', '', d)}"
SKIP_MAIN_PKG="${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', 'yes', 'no', d)}"
DOWNLOAD_ON_DEMAND="${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', 'yes', 'no', d)}"
