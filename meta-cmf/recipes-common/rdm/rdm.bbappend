SRC_URI += "file://download_apps.sh"
SRC_URI += "file://apps_rdm.sh"
SRC_URI += "file://apps-rdm.service"
SRC_URI += "file://apps_rdm.path"
SRC_URI += "file://apps_prerdm.sh"
SRC_URI += "file://apps-prerdm.service"
SRC_URI += "file://jsonquery.c"
SRC_URI += "file://rdm_apps_rfc_check.sh"

DEPENDS += "cjson"

CFLAGS += "-I${PKG_CONFIG_SYSROOT_DIR}/usr/include/cjson -lcjson"

do_compile_append () {
    ${CC} -Wall -Wextra ${WORKDIR}/jsonquery.c $CFLAGS -o ${WORKDIR}/jsonquery 
}

do_install_append () {
    install -d ${D}${bindir}
    install -m 0755 ${WORKDIR}/jsonquery ${D}${bindir}/
}

INSANE_SKIP_${PN} = "ldflags"
