SUMMARY = "CCSP WebUI component"
HOMEPAGE = "http://github.com/ccsp-yocto/webui"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://../../LICENSE;md5=ecf4e15f1559e48fc2b54f092948be4c"

DEPENDS = "ccsp-common-library php chrpath-replacement-native ccsp-webui-csrf"

DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

require ccsp_common.inc

SRC_URI = "\
    ${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/webui;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=webui \
    ${CMF_GIT_ROOT}/rdkb/devices/rdkbemu/rdkbemu_xb3;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};destsuffix=xb3;name=xb3 \
    "

SRCREV_webui = "${AUTOREV}"
SRCREV_xb3 = "${AUTOREV}"
SRCREV_FORMAT = "webui_xb3"

PV = "${RDK_RELEASE}"

S = "${WORKDIR}/git/source/CcspPhpExtension"

inherit autotools systemd
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
LDFLAGS_remove = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', '-lsafec-3.5', '', d)}"
LDFLAGS_append_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec-3.5.1 ', '', d)}"
LDFLAGS_append_kirkstone = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"

inherit lxc
LXC_TEMPLATE = "lxc-lighttpd"
LXC_NAME = "webui"
LXC_LOG_PATH = "/rdklogs/logs"
LXC_LOG_LEVEL = "8"


CFLAGS_append = " \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -fPIC \
    "

LDFLAGS += " \
     -ldbus-1 \
     "
do_configure_prepend () {
	(cd ${S} && ${STAGING_BINDIR_CROSS}/phpize && aclocal && libtoolize --force && autoreconf)
}

EXTRA_OECONF = "--enable-cosa CCSP_COMMON_LIB=${STAGING_LIBDIR}"
EXTRA_OECONF_append  = " --with-ccsp-platform=bcm --with-ccsp-arch=arm "

EXTRANATIVEPATH += "chrpath-native"

do_configure () {
	oe_runconf
}

do_install() {
	install -d ${D}${base_libdir}/rdk
	install -d ${D}${systemd_unitdir}/system
        install -m 0644 ${S}/../../debug_scripts/cosalogs.service ${D}${systemd_unitdir}/system
        install -m 0644 ${S}/../../debug_scripts/cosalogs.sh ${D}${base_libdir}/rdk
}

do_install_append() {
    # Config files and scripts
    install -d ${D}/usr/www
    install -d ${D}/usr/www/actionHandler
    install -d ${D}/usr/www/CSRF-Protector-PHP/libs
    install -d ${D}/usr/www/CSRF-Protector-PHP/libs/csrf
    install -d ${D}/usr/www/cmn
    install -d ${D}/usr/www/cmn/css
    install -d ${D}/usr/www/cmn/css/lib
    install -d ${D}/usr/www/cmn/img
    install -d ${D}/usr/www/cmn/js
    install -d ${D}/usr/www/cmn/js/lib
    install -d ${D}/usr/www/cmn/syndication/img
    install -d ${D}/usr/www/cmn/syndication
    install -d ${D}/usr/www/cmn/syndication/device_pause_screen
    install -d ${D}/usr/www/includes
    install -d ${D}/fss/gw/usr/ccsp
    install -d ${D}${sysconfdir}
    install -m 755 ${S}/../Styles/xb3/code/status-500.html ${D}/usr/www
    install -m 755 ${S}/../Styles/xb3/code/*.php ${D}/usr/www
    install -m 755 ${S}/../Styles/xb3/code/actionHandler/*.php ${D}/usr/www/actionHandler
    install -m 755 ${S}/../Styles/xb3/code/CSRF-Protector-PHP/libs/config.php ${D}/usr/www/CSRF-Protector-PHP/libs
    install -m 755 ${S}/../Styles/xb3/code/CSRF-Protector-PHP/libs/csrf/csrfprotector_rdkb.php ${D}/usr/www/CSRF-Protector-PHP/libs/csrf
    install -m 755 ${S}/../Styles/xb3/code/cmn/css/*.css ${D}/usr/www/cmn/css
    install -m 755 ${S}/../Styles/xb3/code/cmn/css/lib/*.css ${D}/usr/www/cmn/css/lib
    install -m 755 ${S}/../Styles/xb3/code/cmn/img/* ${D}/usr/www/cmn/img
    install -m 755 ${S}/../Styles/xb3/code/cmn/js/*.js ${D}/usr/www/cmn/js
    install -m 755 ${S}/../Styles/xb3/code/cmn/js/lib/* ${D}/usr/www/cmn/js/lib
    install -m 755 ${S}/../Styles/xb3/code/cmn/syndication/img/* ${D}/usr/www/cmn/syndication/img
    install -m 755 ${S}/../Styles/xb3/code/cmn/syndication/device_pause_screen/* ${D}/usr/www/cmn/syndication/device_pause_screen
    install -m 755 ${S}/../Styles/xb3/code/includes/*.php ${D}/usr/www/includes
    install -m 755 ${S}/../Styles/xb3/code/test/OddEvenPattern.test ${D}/usr
    install -m 755 ${S}/../Styles/xb3/config/*.sh ${D}${sysconfdir}
    install ${B}/modules/cosa.so ${D}/fss/gw/usr/ccsp

    # Remove the RPATH embedded in cosa.so
    chrpath --delete ${D}/fss/gw/usr/ccsp/cosa.so
}

do_install_append_mips () {
    install -d ${D}/usr/bin
    install -m 755 ${S}/../../scripts/confPhp ${D}/usr/bin/confPhp
}

do_install_append_puma7 () {
    install -d ${D}${exec_prefix}/ccsp
    install -m 755 ${S}/../../scripts/confPhp ${D}${exec_prefix}/ccsp/confPhp
}

do_install_append_bcm3390(){
    install -d ${D}${exec_prefix}/ccsp
    install -m 755 ${S}/../../scripts/confPhp ${D}${exec_prefix}/ccsp/confPhp
}

SYSTEMD_SERVICE_${PN} = "cosalogs.service"

FILES_${PN} += "/fss/* /fss/gw/* /fss/gw/usr/* /fss/gw/usr/ccsp/* /opt/www/* ${base_libdir}/rdk/* ${libdir}"

FILES_${PN} += " \
     ${systemd_unitdir}/system/cosalogs.service \
     "
FILES_${PN} += "/usr/*"
FILES_${PN} += "/usr/www/*"
FILES_${PN} += "/usr/www/actionHandler/*"
FILES_${PN} += "/usr/www/CSRF-Protector-PHP/libs/*"
FILES_${PN} += "/usr/www/CSRF-Protector-PHP/libs/csrf/*"
FILES_${PN} += "/usr/www/cmn/*"
FILES_${PN} += "/usr/www/includes/*"
FILES_${PN} += "${exec_prefix}/ccsp/confPhp"
 
FILES_${PN}-dbg += "${libdir}/php5/extensions/*/.debug/* \
                    ${libdir}/extensions/*/.debug/* \
                    /fss/gw/usr/ccsp/.debug/*"
