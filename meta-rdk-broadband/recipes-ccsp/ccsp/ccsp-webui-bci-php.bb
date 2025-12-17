SUMMARY = "CCSP WebUI component"
HOMEPAGE = "http://github.com/ccsp-yocto/webui"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://../../LICENSE;md5=0ef5cb68a38cd4d4c9f9d350c50f68f8"

DEPENDS = "ccsp-common-library php ccsp-webui-csrf"
require ccsp_common.inc
SRC_URI = "\
    ${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/webui-bwg;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH} \
    ${CMF_GIT_ROOT}/rdkb/devices/rdkbemu/rdkbemu_xb3;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};destsuffix=xb3;name=xb3 \
    "

FILESEXTRAPATHS_prepend := "${THISDIR}/ccsp-webui-bci:"

SRC_URI_append = " \
                 file://cosalogs.service \
                 file://cosalogs.sh \
                 file://ajax_maintenance_window_conf.php \
                 file://bci_maintenance_window.patch;apply=no \
                 "

SRCREV = "${AUTOREV}"
SRCREV_xb3 = "${AUTOREV}"
SRCREV_FORMAT = "default_xb3"

PV = "${RDK_RELEASE}"

S = "${WORKDIR}/git/source/CcspPhpExtension"

inherit autotools systemd

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

do_configure () {
	oe_runconf
}

do_install() {
	install -d ${D}${base_libdir}/rdk
	install -d ${D}${systemd_unitdir}/system
	install -m 0644 ${WORKDIR}/cosalogs.service ${D}${systemd_unitdir}/system
	install -m 0644 ${WORKDIR}/cosalogs.sh ${D}${base_libdir}/rdk
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
    install -m 755 ${S}/../Styles/xb3/code/includes/*.php ${D}/usr/www/includes
    install -m 755 ${S}/../Styles/xb3/config/*.sh ${D}${sysconfdir}
    install ${B}/modules/cosa.so ${D}/fss/gw//usr/ccsp
    install -m 0755 ${WORKDIR}/ajax_maintenance_window_conf.php ${D}/usr/www/actionHandler/
}

do_install_append_mips () {
    install -d ${D}/usr/bin
    install -m 755 ${S}/../../scripts/confPhp ${D}/usr/bin/confPhp
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
