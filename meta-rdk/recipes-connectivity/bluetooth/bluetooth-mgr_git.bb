SUMMARY = "bluetooth-mgr"
SECTION = "console/utils"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

PV = "${RDK_RELEASE}+git${SRCPV}"

SRCREV = "${AUTOREV}"
SRCREV_FORMAT = "bluetooth-mgr"

SRC_URI = "${CMF_GIT_ROOT}/rdk/components/generic/bluetooth_mgr;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH}"
S = "${WORKDIR}/git"


DEPENDS = "bluetooth-core cjson"

RDEPENDS_${PN}  = " bluetooth-core"
RDEPENDS_${PN} += " cjson"


DEPENDS += " ${@bb.utils.contains('DISTRO_FEATURES', 'gstreamer1', 'gstreamer1.0 gstreamer1.0-plugins-base', '', d)}"
ENABLE_GST1 = "--enable-gstreamer1=${@bb.utils.contains('DISTRO_FEATURES', 'gstreamer1', 'yes', 'no', d)}"
EXTRA_OECONF = " ${ENABLE_GST1}"

# RPC-IARM Must be Enabled for Video Platforms only; Also iarmbus is dependency for Video Platforms
DEPENDS_append_client = " iarmbus netsrvmgr"
DEPENDS_append_hybrid = " iarmbus"
EXTRA_OECONF_append_client = " --enable-rpc"
EXTRA_OECONF_append_hybrid = " --enable-rpc"

DEPENDS += " fcgi"
DEPENDS += " rfc"

DEPENDS += " rdk-logger"
RDEPENDS_${PN} += " rdk-logger"


DEPENDS_append_client = " virtual/media-utils"
DEPENDS_append_client = " audiocapturemgr"
RDEPENDS_${PN}_append_client = " virtual/media-utils"
RDEPENDS_${PN}_append_client = " audiocapturemgr"

DEPENDS_append_hybrid = " virtual/media-utils"
DEPENDS_append_hybrid = " audiocapturemgr"
RDEPENDS_${PN}_append_hybrid = " virtual/media-utils"
RDEPENDS_${PN}_append_hybrid = " audiocapturemgr"


inherit autotools pkgconfig systemd coverity syslog-ng-config-gen logrotate
SYSLOG-NG_FILTER = "btmgr"
SYSLOG-NG_SERVICE_btmgr = "btmgr.service"
SYSLOG-NG_DESTINATION_btmgr = "btmgrlog.txt"
SYSLOG-NG_LOGRATE_btmgr = "very-high"

LOGROTATE_NAME    = "btmgr"
LOGROTATE_LOGNAME_btmgr = "btmgrlog.txt"
LOGROTATE_SIZE_MEM_btmgr    = "250000"
LOGROTATE_ROTATION_MEM_btmgr  = "2"
LOGROTATE_SIZE_btmgr    = "512000"
LOGROTATE_ROTATION_btmgr  = "5"


ENABLE_AC_RMF = "--enable-ac_rmf=${@bb.utils.contains('RDEPENDS_${PN}', 'virtual/${MLPREFIX}media-utils', 'yes', 'no', d)}"
ENABLE_ACM = "--enable-acm=${@bb.utils.contains('RDEPENDS_${PN}', '${MLPREFIX}audiocapturemgr', 'yes', 'no', d)}"
EXTRA_OECONF += " ${ENABLE_ACM} ${ENABLE_AC_RMF}"

CFLAGS_append =" ${@bb.utils.contains('RDEPENDS_${PN}', '${MLPREFIX}audiocapturemgr', ' -I${STAGING_INCDIR}/audiocapturemgr', " ", d)}"
CFLAGS_append =" ${@bb.utils.contains('RDEPENDS_${PN}', 'virtual/${MLPREFIX}media-utils', ' -I${STAGING_INCDIR}/media-utils -I${STAGING_INCDIR}/media-utils/audioCapture', " ", d)}"

ENABLE_RDK_LOGGER = "--enable-rdk-logger=${@bb.utils.contains('RDEPENDS_${PN}', '${MLPREFIX}rdk-logger', 'yes', 'no', d)}"
EXTRA_OECONF += " ${ENABLE_RDK_LOGGER}"

# Autoconnect feature enabled
ENABLE_AUTO_CONNECT = "--enable-autoconnectfeature=${@bb.utils.contains('DISTRO_FEATURES', 'btr_enable_auto_connect','yes','no',d)}"
EXTRA_OECONF += " ${ENABLE_AUTO_CONNECT} "

ENABLE_STREAMING_IN = "--enable-streaming-in=${@bb.utils.contains('DISTRO_FEATURES', 'btr_disable_streaming_in','no','yes',d)}"
EXTRA_OECONF += " ${ENABLE_STREAMING_IN} "

EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', '--enable-systemd-notify', '', d)}"
EXTRA_OECONF_append_client = " --enable-sys-diag"

do_install_append() {
	install -d ${D}${systemd_unitdir}/system ${D}${sysconfdir}
    install -m 0644 ${S}/conf/btmgr.service ${D}${systemd_unitdir}/system
}

SYSTEMD_SERVICE_${PN}  = "btmgr.service"

FILES_${PN} += "${systemd_unitdir}/system/btmgr.service"

