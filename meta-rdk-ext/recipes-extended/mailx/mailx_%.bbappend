do_install_append() {
    if ${@bb.utils.contains('DISTRO_FEATURES', 'morty', 'false', 'true', d)}; then
        rm ${D}${bindir}/mailx
    fi
}
