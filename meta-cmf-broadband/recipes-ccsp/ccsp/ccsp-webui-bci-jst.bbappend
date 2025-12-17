do_compile[noexec] = "1"

PV_kirkstone = "${RDK_RELEASE}+git${SRCPV}"
FILESEXTRAPATHS_prepend := "${THISDIR}/ccsp-webui-bci:"
SRC_URI += "file://logo_rdk.png"

# we need to patch to code for RPi webui_bci
do_webui_bci_patches() {
    cd ${S}/../../..
    if [ ! -e patch_applied ]; then
        patch -p1 < ${WORKDIR}/bci_maintenance_window_jst.patch
        touch patch_applied
    fi
}
addtask webui_bci_patches after do_unpack before do_compile

do_install_append() {
        rm -rf ${D}${base_libdir}
}
