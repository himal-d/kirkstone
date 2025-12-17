SUMMARY = "Memcapture - memory reporting and analysis tool for RDK"
DESCRIPTION = "A C++ tool to capture the average memory usage of a platform including per-process memory usage and \
SoC-specific metrics and present them in a report"

LICENSE = "Apache-2.0"

LIC_FILES_CHKSUM = "file://LICENSE;md5=1b8525f92b462b86205ffaba159b4481"

SRC_URI = "git://github.com/RDKCentral/MemCapture.git;branch=main;name=src"
SRC_URI_append = " git://${RDK_GIT}/rdk/component/generic/performancetool/generic;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH};subpath=memcapture;name=script"
SRCREV_src = "0cf90e07af97b70fb1f253ebd0f71edd5a9b8225"
SRCREV_script = "${AUTOREV}"
SRCREV_FORMAT = "src_script"

S = "${WORKDIR}/git"
B = "${WORKDIR}/git/build"

DEPENDS = "breakpad-wrapper inja nlohmann-json"

inherit cmake syslog-ng-config-gen systemd
EXTRA_OECMAKE += "-DCMAKE_BUILD_TYPE=Release"

SYSLOG-NG_FILTER = "memcapture"
SYSLOG-NG_SERVICE_memcapture = "memcapture.service"
SYSLOG-NG_DESTINATION_memcapture = "memcapture.log"
SYSLOG-NG_LOGRATE_memcapture = "high"

# Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "memcapture"
BREAKPAD_LOGMAPPER_LOGLIST = "memcapture.log"

do_install () {
    install -d ${D}${bindir}
    install -d ${D}${sysconfdir}
    install -d ${D}${base_libdir}/rdk
    install -d ${D}${systemd_unitdir}/system
    install -m 4755 ${B}/MemCapture ${D}${bindir}
    # Install memcapture json config file
    install -m 0600 ${WORKDIR}/memcapture/groups-rdkv.json ${D}${sysconfdir}/groups.json
    # Install memcapture start script
    install -m 0755 ${WORKDIR}/memcapture/start_memcapture.sh ${D}${base_libdir}/rdk/start_memcapture.sh
    # Install memcapture service
    install -m 0644 ${WORKDIR}/memcapture/memcapture.service ${D}${systemd_unitdir}/system/memcapture.service
}

SYSTEMD_SERVICE_${PN} += "memcapture.service"

FILES_${PN} += "${bindir}/MemCapture \
                ${sysconfdir}/groups.json \
                ${base_libdir}/rdk/start_memcapture.sh \ 
                ${systemd_unitdir}/system/memcapture.service \
               "
