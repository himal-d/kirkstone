do_install_append() {
    # Remove unwanted binaries
    rm -rf ${D}${bindir}
}

FILES_${PN}-consolefonts_remove = "${datadir}/consolefonts"
FILES_${PN}-keymaps_remove = "${datadir}/keymaps"
