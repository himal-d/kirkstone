require dwarf.inc

ASLR = "${@bb.utils.contains('DISTRO_FEATURES', 'aslr', '1', '0', d)}"

EXTRA_OECONF += "${@ASLR == "1" and "--enable-shared --disable-static" or ""}"

do_install() {
    install -d ${D}${libdir} ${D}${includedir}/libdwarf

    if [ "${ASLR}" = "1" ]; then
        install -m 0755 ${B}/libdwarf/.libs/libdwarf.so.1.0.0 ${D}${libdir}
	ln -sfr ${D}${libdir}/libdwarf.so.1.0.0 ${D}${libdir}/libdwarf.so.1
	ln -sfr ${D}${libdir}/libdwarf.so.1.0.0 ${D}${libdir}/libdwarf.so
    else
	install -m 0755 ${B}/libdwarf/.libs/libdwarf.a ${D}${libdir}
    fi

    install -m 0644 ${S}/libdwarf/dwarf.h ${S}/libdwarf/libdwarf.h ${D}${includedir}/libdwarf
}

ALLOW_EMPTY_${PN} = "1"

BBCLASSEXTEND = "native"

FILES_SOLIBSDEV = ""

INSANE_SKIP_${PN} += "dev-so"
FILES_${PN} += "${libdir}/libdwarf.so*"
