SUMMARY = "RDK Memory manager for TinyRDK"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=e3fc50a88d0a364313df4b21ef20c29e"


SRC_URI = "${CMF_GITHUB_ROOT}/smartmon;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GITHUB_MAIN_BRANCH}"

# Modify these as desired
PV = "1.0+git${SRCPV}"
SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git"

inherit cmake pkgconfig systemd coverity

DEPENDS += "jsoncpp websocketpp systemd boost"

# Specify any options you want to pass to cmake using EXTRA_OECMAKE:
EXTRA_OECMAKE = ""
EXTRA_OECONF += " --enable-breakpad"

BREAKPAD_BIN="smartmon"

SYSTEMD_SERVICE_${PN} = "smartmon.service"
