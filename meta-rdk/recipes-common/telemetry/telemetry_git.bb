SUMMARY = "This recipe compiles Telemetry"
SECTION = "console/utils"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

SRC_URI = "${RDK_GENERIC_ROOT_GIT}/telemetry/generic;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH}"

DEPENDS += "curl cjson glib-2.0 breakpad-wrapper rbus libsyswrapper libunpriv"
DEPENDS += "rdk-logger"

RDEPENDS_${PN} += "curl cjson glib-2.0 rbus"

PV = "${RDK_RELEASE}+git${SRCPV}"
SRCREV ?= "${AUTOREV}"
S = "${WORKDIR}/git"

CFLAGS += " -Wall -Werror -Wextra -Wno-unused-parameter -Wno-pointer-sign -Wno-sign-compare -Wno-enum-compare -Wno-type-limits -Wno-enum-conversion -Wno-format-truncation"

# Enable SE HW based cert usage
CFLAGS_append += "${@bb.utils.contains('DISTRO_FEATURES', 'ENABLE_HW_CERT_USAGE',' -DENABLE_HW_CERT_USAGE -DENABLE_CUSTOM_ENGINE ',' ',d)}"


inherit pkgconfig autotools systemd ${@bb.utils.contains("DISTRO_FEATURES", "kirkstone", "python3native", "pythonnative", d)} breakpad-logmapper

CFLAGS += " -DDROP_ROOT_PRIV "

LDFLAGS_append = " \
        -lbreakpadwrapper \
        -lpthread \
        -lstdc++ \
        -lsecure_wrapper \
        "
LDFLAGS_append = " \
        -lprivilege \
      "

CXXFLAGS += "-DINCLUDE_BREAKPAD"

do_install_append () {
    install -d ${D}/usr/include/
    install -d ${D}/lib/rdk/
    install -d ${D}${systemd_unitdir}/system
    install -m 644 ${S}/include/telemetry_busmessage_sender.h ${D}/usr/include/
    install -m 644 ${S}/include/telemetry2_0.h ${D}/usr/include/
    install -m 0755 ${S}/source/commonlib/t2Shared_api.sh ${D}/lib/rdk
    rm -fr ${D}/usr/lib/libtelemetry_msgsender.la 
}

FILES_${PN} = "\
    ${bindir}/telemetry2_0 \
    ${bindir}/t2rbusMethodSimulator \
    ${bindir}/telemetry2_0_client \
    ${systemd_unitdir}/system \
"
FILES_${PN} += "${libdir}/*.so*"
FILES_${PN} += "/lib/rdk/*"

FILES_SOLIBSDEV = ""
INSANE_SKIP_${PN} += "dev-so"

PACKAGES =+ "${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', '${PN}-gtest', '', d)}"

FILES_${PN}-gtest = "\
    ${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', '${bindir}/telemetry_gtest.bin ${bindir}/xconfclient_gtest.bin ${bindir}/t2parser_gtest.bin ${bindir}/reportgen_gtest.bin ${bindir}/scheduler_gtest.bin', '', d)} \
"

DOWNLOAD_APPS="${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', 'gtestapp-telemetry', '', d)}"
inherit comcast-package-deploy
CUSTOM_PKG_EXTNS="${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', 'gtest', '', d)}"
SKIP_MAIN_PKG="${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', 'yes', 'no', d)}"
DOWNLOAD_ON_DEMAND="${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', 'yes', 'no', d)}"

# Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "telemetry2_0"
BREAKPAD_LOGMAPPER_LOGLIST = "telemetry2_0.txt.0"
