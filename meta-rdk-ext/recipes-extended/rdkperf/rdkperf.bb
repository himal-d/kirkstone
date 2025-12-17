DESCRIPTION = "RDK Perf - lightweight profiling tool for real time performance metrics reporting"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

#DEPENDS = " "

#USE_RDKPERF_SERVICE = "${@bb.utils.contains('DISTRO_FEATURES', 'rdkperf_service', "true", "", d)}"

inherit systemd syslog-ng-config-gen
SYSLOG-NG_FILTER = "${@bb.utils.contains('DISTRO_FEATURES', 'rdkperf_service', "rdkperf", "", d)}"
SYSLOG-NG_SERVICE_rdkperf = "${@bb.utils.contains('DISTRO_FEATURES', 'rdkperf_service', "rdkperf.service", "", d)}"
SYSLOG-NG_DESTINATION_rdkperf = "${@bb.utils.contains('DISTRO_FEATURES', 'rdkperf_service', "rdkperf.log", "", d)}"
SYSLOG-NG_LOGRATE_rdkperf = "${@bb.utils.contains('DISTRO_FEATURES', 'rdkperf_service', "low", "", d)}"

def use_rdk_perf_service(d):
    if bb.utils.contains("DISTRO_FEATURES", "rdkperf_service", "true", "false", d) == "true":
        # SYSLOG-NG_FILTER = bb.utils.contains("DISTRO_FEATURES", 'rdkperf_service', "rdkperf", "", d)
        # SYSLOG-NG_SERVICE_rdkperf = bb.utils.contains("DISTRO_FEATURES", 'rdkperf_service', "rdkperf.service", "", d)
        # SYSLOG-NG_DESTINATION_rdkperf = bb.utils.contains("DISTRO_FEATURES", 'rdkperf_service', "rdkperf.log", "", d)
        # SYSLOG-NG_LOGRATE_rdkperf = bb.utils.contains("DISTRO_FEATURES", 'rdkperf_service', "low", "", d)
        return "true"
    else:
        return "false"

USE_RDKPERF_SERVICE = "${@use_rdk_perf_service(d)}"

# git@github.com:rdkcentral/rdkperf.git
# Testing with development branch
#SRC_URI = "git://github.com/rdkcentral/rdkperf;protocol=git;branch=development"
#SRCREV = "${AUTOREV}"

# Using the main branch
SRC_URI = "git://github.com/rdkcentral/rdkperf;protocol=git;branch=main"
SRCREV = "d802d561c4a2a4456403d572da75e73032d48d91"
#SRCREV = "${AUTOREV}"


PV = "1.0+git${SRCPV}"
S = "${WORKDIR}/git"


RDKPERF_BUILD_FLAGS += "${@bb.utils.contains('DISTRO_FEATURES', 'rdkperf_service', "ENABLE_PERF_REMOTE=1", "", d)}"

do_configure() { 
    echo "RDKPERF Configure"
    oe_runmake -C ${S} -f Makefile ${RDKPERF_BUILD_FLAGS} clean
}

do_compile () {
    oe_runmake -C ${S} -f Makefile ${RDKPERF_BUILD_FLAGS}
}

do_install() {
        install -d ${D}/usr/lib
        install -d ${D}/usr/include
        install -m 0755 ${S}/build/librdkperf.so          ${D}/usr/lib
        install -m 0755 ${S}/build/libperftool.so         ${D}/usr/lib
        install -m 0644 ${S}/rdkperf/rdk_perf.h           ${D}/usr/include
        install -m 0644 ${S}/src/*.h                      ${D}/usr/include
}

do_install_append() {
    if [ "x${USE_RDKPERF_SERVICE}" = "xtrue" ]; then
        echo "Installing RDKPerf service"
        install -d ${D}${systemd_unitdir}/system
        install -m 0644 ${S}/service/rdkperf.service ${D}${systemd_unitdir}/system/rdkperf.service

        install -d ${D}/usr/bin
        install -m 0755 ${S}/build/perfservice         ${D}/usr/bin

    fi
}


SYSTEMD_SERVICE_${PN} = "${@bb.utils.contains('DISTRO_FEATURES', 'rdkperf_service', "rdkperf.service", "", d)}"
FILES_${PN} += "${@bb.utils.contains('DISTRO_FEATURES', 'rdkperf_service', "${systemd_unitdir}/system/rdkperf.service", "", d)}"

INSANE_SKIP_${PN} = "dev-so"
FILES_SOLIBSDEV = ""
FILES_${PN} += "${libdir}/*.so" 

INSANE_SKIP_${PN} += "ldflags"


