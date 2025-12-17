do_install_append() {
        rm -f ${D}${bindir}/lsipc
        rm -f ${D}${bindir}/lslogins
        rm -f ${D}${bindir}/lsns
        rm -f ${D}${bindir}/chfn
        rm -f ${D}${bindir}/chsh
        rm -f ${D}${bindir}/uclampset
        rm -f ${D}${bindir}/lsirq
        rm -f ${D}${bindir}/irqtop

}
