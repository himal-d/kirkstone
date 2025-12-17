SUMMARY = "CCSP WebUI component"
HOMEPAGE = "http://github.com/ccsp-yocto/webui"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://../../../LICENSE;md5=ecf4e15f1559e48fc2b54f092948be4c"

DEPENDS = "ccsp-common-library chrpath-replacement-native"

require ccsp_common.inc

SRC_URI = "\
    git://${RDK_GIT}/rdk/rdkb/components/opensource/ccsp/webui/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=webui \
    git://${RDK_GIT}/rdk/rdkb/devices/rdkbemu/rdkbemu_xb3;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};destsuffix=xb3;name=xb3 \
    "

SRCREV_webui = "${AUTOREV}"
SRCREV_xb3 = "${AUTOREV}"
SRCREV_FORMAT = "webui_xb3"

PV = "${RDK_RELEASE}"

S = "${WORKDIR}/git/source/Styles/xb3"


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

EXTRA_OECONF = "CCSP_COMMON_LIB=${STAGING_LIBDIR}"
EXTRA_OECONF_append  = " --with-ccsp-platform=bcm --with-ccsp-arch=arm "

EXTRANATIVEPATH += "chrpath-native"


do_install_append() {
    # Config files and scripts
    install -d ${D}${sysconfdir}
    install -m 755 ${S}/config/*.sh ${D}${sysconfdir}
    install -d ${D}/usr/www2/locale
    install -m 755 ${S}/jst/locale/* ${D}/usr/www2/locale/
    install -d ${D}/usr/www2/actionHandler
    install -m 755 ${S}/jst/actionHandler/* ${D}/usr/www2/actionHandler/
    install -d ${D}/usr/www2/cmn/
    install -d ${D}/usr/www2/cmn/css/
    install -d ${D}/usr/www2/cmn/css/lib
    install -m 755 ${S}/cmn/css/lib/* ${D}/usr/www2/cmn/css/lib/
    install -m 755 ${S}/cmn/css/*.*  ${D}/usr/www2/cmn/css/
    install -d ${D}/usr/www2/cmn/img
    install -m 755 ${S}/cmn/img/* ${D}/usr/www2/cmn/img
    install -d ${D}/usr/www2/cmn/js
    install -d ${D}/usr/www2/cmn/js/lib
    install -m 755 ${S}/cmn/js/lib/* ${D}/usr/www2/cmn/js/lib
    install -m 755 ${S}/cmn/js/*.*  ${D}/usr/www2/cmn/js/
    install -d ${D}/usr/www2/cmn/syndication
    install -d ${D}/usr/www2/cmn/syndication/device_pause_screen
    install -d ${D}/usr/www2/cmn/syndication/img
    install -m 755 ${S}/jst/syndication/device_pause_screen/* ${D}/usr/www2/cmn/syndication/device_pause_screen
    install -m 755 ${S}/jst/syndication/img/* ${D}/usr/www2/cmn/syndication/img
    install -d ${D}/usr/www2/includes
    install -m 755 ${S}/jst/includes/* ${D}/usr/www2/includes
    install -m 755 ${S}/jst/*.* ${D}/usr/www2/
    install -d ${D}/usr/www2/test
    sed -i 's/usr\/www/usr\/www2/g' ${D}${sysconfdir}/webgui.sh
}

FILES_${PN} += "/fss/* /fss/gw/* /fss/gw/usr/*"

FILES_${PN} += "/usr/*"
FILES_${PN} += "/usr/www2/actionHandler/*"
FILES_${PN} += "/usr/www2/cgi-bin/*"
FILES_${PN} += "/usr/www2/cmn/*"
FILES_${PN} += "/usr/www2/CSRF-Protector-PHP/*"
FILES_${PN} += "/usr/www2/includes/*"
FILES_${PN} += "/usr/www2/includes/*"

