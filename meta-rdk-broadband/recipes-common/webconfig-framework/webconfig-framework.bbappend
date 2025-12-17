DEPENDS += " ccsp-common-library"

CFLAGS += " -DCCSP_SUPPORT_ENABLED -DWBCFG_MULTI_COMP_SUPPORT"
                   
require recipes-ccsp/ccsp/ccsp_common.inc

do_install_append () {
    install -d ${D}/usr/include/ccsp
    install -m 644 ${S}/include/*.h ${D}/usr/include/ccsp/
}

EXTRA_OECONF += " --enable-ccspsupport"
