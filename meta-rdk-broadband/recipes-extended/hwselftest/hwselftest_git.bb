SUMMARY = "Hardware Self test"
DESCRIPTION = "Hardware-Selftest and Diagnostic Tool"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"
PV = "${RDK_RELEASE}+git${SRCPV}"

SRCREV_hwselftest = "${AUTOREV}"
SRCREV_FORMAT = "hwselftest"

require recipes-ccsp/ccsp/ccsp_common.inc

SRC_URI = "${RDK_GENERIC_ROOT_GIT}/hwselftest-rdkb/generic;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH};name=hwselftest"
S = "${WORKDIR}/git"

CFLAGS += " -I=${includedir}/dbus-1.0 -I=${libdir}/dbus-1.0/include -I=${includedir}/ccsp -I=${includedir}/syscfg"

LDFLAGS_append = " -ldbus-1 -lpthread -lhal_platform"

EXTRA_OECONF += "--enable-agent-build --enable-client-build --enable-hwselftesttrigger-build"
EXTRA_OECONF += " --with-diag-emmc --with-diag-moca --with-diag-wan --with-diag-bluetooth --with-diag-dram --with-diag-wifi --with-diag-mta --with-diag-xhs --with-diag-lan --with-diag-zigbee"

DEPENDS = "jansson breakpad breakpad-wrapper xupnp ccsp-common-library dbus hal-platform"
RDEPENDS_${PN}_append = "bash"
RDEPENDS_${PN}_remove_morty = "bash"

inherit autotools pkgconfig systemd

do_install_append() {
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${S}/agent/rootfs/lib/systemd/system/hwselftest.service ${D}${systemd_unitdir}/system
    install -m 0644 ${S}/agent/rootfs/usr/bin/hwst_log.sh ${D}${bindir}
    install -d ${D}${includedir}
    install -d ${D}${bindir}
    install -d ${D}${libdir}
    install -m 0644 ${S}/hwselftesttrigger/hwselftesttrigger.h ${D}${includedir}
    install -m 0755 ${S}/agent/rootfs/usr/bin/hwst_agent_start.sh ${D}${bindir}
    install -m 0755 ${S}/agent/rootfs/usr/bin/hwselftest_run.sh ${D}${bindir}
    install -m 0755 ${S}/agent/rootfs/usr/bin/hwselftest_check_free_cpu.sh ${D}${bindir}
    install -m 0755 ${S}/agent/rootfs/usr/bin/hwselftest_check_free_dram.sh ${D}${bindir}
    install -m 0755 ${S}/agent/rootfs/usr/bin/hwselftest_cronjobscheduler.sh ${D}${bindir}
    install -m 0755 ${S}/agent/rootfs/usr/bin/hwselftest_runptr.sh ${D}${bindir}
}

FILES_${PN} += "/usr/www2/*"
FILES_${PN} += "${systemd_unitdir}/system/hwselftest.service"

SYSTEMD_SERVICE_${PN} = "hwselftest.service"
