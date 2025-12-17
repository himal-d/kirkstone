do_install_append () {
    install -m 644 ${S}/source/hotspotfd/include/debug.h ${D}/usr/include/ccsp
    install -m 644 ${S}/source/hotspotfd/include/dhcp.h ${D}/usr/include/ccsp
}
