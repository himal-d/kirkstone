FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI += "file://logo_rdk.png"
PV_kirkstone = "${RDK_RELEASE}+git${SRCPV}"

do_install_prepend() {
    install -d ${S}/../Styles/xb3/code/CSRF-Protector-PHP
    install -d ${S}/../Styles/xb3/code/CSRF-Protector-PHP/js
    install -d ${S}/../Styles/xb3/code/CSRF-Protector-PHP/libs
    install -d ${S}/../Styles/xb3/code/CSRF-Protector-PHP/libs/csrf
    install -d ${S}/../Styles/xb3/code/cmn/syndication/img

    touch ${S}/../Styles/xb3/code/CSRF-Protector-PHP/TODO
    touch ${S}/../Styles/xb3/code/CSRF-Protector-PHP/js/TODO
    touch ${S}/../Styles/xb3/code/CSRF-Protector-PHP/libs/TODO.php
    touch ${S}/../Styles/xb3/code/CSRF-Protector-PHP/libs/csrf/TODO.php
    touch ${S}/../Styles/xb3/code/cmn/syndication/img/TODO
}

do_install_append () {
       #For RDKM Logo
       install -d ${D}/usr/www/cmn/syndication/img
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www/cmn/syndication/img
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www/cmn/syndication/img/captiveportal_videotron_logo.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www/cmn/syndication/img/logo_videotron.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www/cmn/syndication/img/Sky_Wifi.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www/cmn/syndication/img/cox_color_logo.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www/cmn/syndication/img/cox_white_logo.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www/cmn/syndication/img/captiveportal_rogers_logo.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www/cmn/syndication/img/logo_rogers.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www/cmn/syndication/img/captiveportal_shaw_logo.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www/cmn/syndication/img/logo_shaw.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www/cmn/syndication/img/captiveportal_arris_logo.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www/cmn/syndication/img/logo_arris.png
       install -m 644 ${WORKDIR}/logo_rdk.png ${D}/usr/www/cmn/syndication/img/logo-generic.png
}

FILES_${PN} += "/usr/www/cmn/syndication/img/* \
"
