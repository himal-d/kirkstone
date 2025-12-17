FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

do_install_append() {
    ( cd ${D}${libdir}/pkgconfig && ln -sf wpe-1.0.pc wpe-0.2.pc )
}
