FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
PV_kirkstone = "${RDK_RELEASE}+git${SRCPV}"

SRC_URI_remove = "git://${RDK_GIT}/rdk/rdkb/components/opensource/ccsp/webui/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=webui"
SRC_URI += "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/webui;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=webui"

SRC_URI_remove = "git://${RDK_GIT}/rdk/rdkb/devices/rdkbemu/rdkbemu_xb3;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};destsuffix=xb3;name=xb3"
SRC_URI += "${CMF_GIT_ROOT}/rdkb/devices/rdkbemu/rdkbemu_xb3;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};destsuffix=xb3;name=xb3"

SRC_URI += "file://logo_rdk.png"

#REFPLTB-1802
SRC_URI += "file://webgui_config.sh"

do_install_append () {
       #For RDKM Logo
       install -d ${D}/usr/www2/cmn/syndication/img
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www2/cmn/syndication/img
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www2/cmn/syndication/img/captiveportal_videotron_logo.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www2/cmn/syndication/img/logo_videotron.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www2/cmn/syndication/img/Sky_Wifi.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www2/cmn/syndication/img/cox_color_logo.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www2/cmn/syndication/img/cox_white_logo.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www2/cmn/syndication/img/captiveportal_rogers_logo.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www2/cmn/syndication/img/logo_rogers.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www2/cmn/syndication/img/captiveportal_shaw_logo.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www2/cmn/syndication/img/logo_shaw.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www2/cmn/syndication/img/captiveportal_arris_logo.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www2/cmn/syndication/img/logo_arris.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www2/cmn/syndication/img/logo-generic.png

       install -m 755 ${WORKDIR}/webgui_config.sh ${D}/${sysconfdir}/webgui_config.sh
}

FILES_${PN} += "/usr/www2/cmn/syndication/img/* \
"
