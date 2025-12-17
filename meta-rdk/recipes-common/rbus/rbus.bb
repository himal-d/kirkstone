SUMMARY = "rbus library component"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=ed63516ecab9f06e324238dd2b259549"

SRC_URI = "git://github.com/rdkcentral/rbus.git;branch=rbus-2.0;protocol=https"
SRC_URI_append = " file://gtest_libraries_check.patch"

SRCREV = "v2.0.13"
SRCREV_FORMAT = "base"

PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

inherit cmake systemd pkgconfig coverity syslog-ng-config-gen logrotate
DEPENDS = "cjson msgpack-c rdk-logger linenoise"


#RDK Specific Enablements
EXTRA_OECMAKE += " -DCMAKE_BUILD_TYPE=Release "
EXTRA_OECMAKE += " -DMSG_ROUNDTRIP_TIME=ON -DENABLE_RDKLOGGER=ON"

#Gtest Specific Enablements
EXTRA_OECMAKE += " ${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', '-DENABLE_UNIT_TESTING=ON', '', d)}"
EXTRA_OECMAKE += " ${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', '-DBUILD_RBUS_BENCHMARK_TEST=ON -DBUILD_RBUS_UNIT_TEST=ON -DBUILD_RBUS_SAMPLE_APPS=ON', '-DBUILD_RBUS_SAMPLE_APPS=OFF', d)}"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', ' gtest benchmark ', ' ', d)}"

#Dunfell Specific CFlags
CFLAGS_append = " -Wno-format-truncation "
CXXFLAGS_append = " -Wno-format-truncation "

SYSLOG-NG_FILTER = "rbus"
SYSLOG-NG_SERVICE_rbus = "rbus.service"
SYSLOG-NG_DESTINATION_rbus = "rtrouted.log"
SYSLOG-NG_LOGRATE_rbus = "medium"

LOGROTATE_NAME="rbus"
LOGROTATE_LOGNAME_rbus="rtrouted.log"
LOGROTATE_SIZE_rbus="1572864"
LOGROTATE_ROTATION_rbus="3"
LOGROTATE_SIZE_MEM_rbus="1572864"
LOGROTATE_ROTATION_MEM_rbus="3"

do_install_append() {
   install -d ${D}${systemd_unitdir}/system
   install -m 0644 ${S}/conf/rbus.service ${D}${systemd_unitdir}/system
   install -m 0644 ${S}/conf/rbus_session_mgr.service ${D}${systemd_unitdir}/system
}

do_install_append_broadband() {
   install -m 0755 ${S}/conf/rbus_log_capture.sh ${D}${bindir}/
   install -m 0644 ${S}/conf/rbus_log.service ${D}${systemd_unitdir}/system
   install -m 0644 ${S}/conf/rbus_monitor.path ${D}${systemd_unitdir}/system
   sed -i 's/PathExists/PathChanged/g' ${D}${systemd_unitdir}/system/rbus_monitor.path
   install -m 0644 ${S}/conf/rbus_monitor.service ${D}${systemd_unitdir}/system
}

do_install_append_hybrid() {
   install -D -m 0644 ${S}/conf/rbus_rdkv.conf ${D}${systemd_unitdir}/system/rbus.service.d/rbus_rdkv.conf
}

do_install_append_client() {
   install -D -m 0644 ${S}/conf/rbus_rdkv.conf ${D}${systemd_unitdir}/system/rbus.service.d/rbus_rdkv.conf
}

PACKAGES =+ "${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', '${PN}-gtest', '', d)}"

FILES_${PN}-gtest += "\
    ${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', '${bindir}/rbus_gtest.bin', '', d)} \
"

FILES_${PN} += "${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', '${bindir}/rbus_src_gcno.tar', '', d)}"


FILES_${PN} += "${systemd_unitdir}/system/*"
SYSTEMD_SERVICE_${PN} = "rbus.service"
SYSTEMD_SERVICE_${PN}_append = " rbus_session_mgr.service "
SYSTEMD_SERVICE_${PN}_append_broadband  = " rbus_monitor.service "
SYSTEMD_SERVICE_${PN}_append_broadband  = " rbus_monitor.path "
SYSTEMD_SERVICE_${PN}_append_broadband  = " rbus_log.service "

DOWNLOAD_APPS="${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', 'gtestapp-rbus', '', d)}"
inherit comcast-package-deploy
CUSTOM_PKG_EXTNS="gtest"
SKIP_MAIN_PKG="yes"
DOWNLOAD_ON_DEMAND="yes"

