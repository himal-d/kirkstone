do_install_append() {
    if ${@bb.utils.contains_any('DISTRO_FEATURES', 'dunfell kirkstone', 'true', 'false', d)}; then
        # Create symlink to support meta-rdk components which expect cJSON.h to
        # be found in the toplevel sysroot ${includedir} rather than within the
        # cjson subdirectory. Fixme: The real solution would be to fix those
        # recipes and then remove this symlink.
        ln -s cjson/cJSON.h ${D}${includedir}/cJSON.h
    fi
}

