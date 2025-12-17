SUMMARY = "This receipe compiles rmfcore code base. This has interface clasess that would be necessary for all the mediaplayers"
SECTION = "console/utils"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"
PV = "${RDK_RELEASE}+git${SRCPV}"

SRCREV = "${AUTOREV}"
SRCREV_FORMAT = "rdklogger"

PV = "${RDK_RELEASE}+gitr${SRCPV}"

SRC_URI = "${CMF_GIT_ROOT}/rdk/components/generic/rdk_logger;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=rdklogger"

S = "${WORKDIR}/git"

DEPENDS = "log4c glib-2.0"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"
DEPENDS += "${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'systemd syslog-helper', '', d)}"

PACKAGECONFIG[systemd-syslog-helper] = "--enable-systemd-syslog-helper,,"

#Milestone Support
EXTRA_OECONF += " --enable-milestone"
PROVIDES = "getClockUptime"
CFLAGS_append_hybrid += " -DLOGMILESTONE"
CFLAGS_append_client += " -DLOGMILESTONE"

inherit autotools pkgconfig coverity pkgconfig

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"
LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"

do_configure_append_broadband () {
		#Use the RDKB Versions of the Files
		install -m 644 ${S}/rdkb_debug.ini ${S}/debug.ini
		install -m 644 ${S}/rdkb_log4crc ${S}/log4crc
}

do_install_append () {
    install -d ${D}${base_libdir}/rdk/
    install -m 0755 ${S}/scripts/logMilestone.sh ${D}${base_libdir}/rdk

    # Create a symbolic link in / as the current automation team testing scripts
    # expect binaries to be present in root
    ln -sf ${bindir}/rdklogctrl ${D}/rdklogctrl
}

FILES_${PN} += "${base_libdir}/rdk/logMilestone.sh \
                /rdkLogMileStone \
                /rdklogctrl \
                ${base_libdir} \
                ${base_libdir}/rdk"
