FILESEXTRAPATHS_prepend := "${THISDIR}/ccsp-webui-bci:"
SRC_URI += "file://logo_rdk.png"
PV_kirkstone = "${RDK_RELEASE}+git${SRCPV}"

# we need to patch to code for RPi webui_bci
do_webui_bci_patches() {
    cd ${S}/../..
    if [ ! -e patch_applied ]; then
        patch -p1 < ${WORKDIR}/bci_maintenance_window.patch
        touch patch_applied
    fi
}
addtask webui_bci_patches after do_unpack before do_compile

do_install_append () {
if [ "${@bb.utils.contains("DISTRO_FEATURES", "referencepltfm", "yes", "no", d)}" = "yes" ]; then
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
fi
}

FILES_${PN} += "/usr/www/cmn/syndication/img/* \
"
