BPN = "eglibc"

do_install_append () {
    install -m 0644 ${WORKDIR}/SUPPORTED ${D}${datadir}/i18n/
    install -d ${D}${libdir}/locale
}

FILES_${BPN}-charmap-utf-8 += "${datadir}/i18n/SUPPORTED"
FILES_${BPN}-charmap-utf-8 += "${libdir}/locale"

