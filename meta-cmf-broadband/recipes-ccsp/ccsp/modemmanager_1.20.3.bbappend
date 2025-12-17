CFLAGS += "-DENABLE_PLUGIN_SIMTECH"

do_install_append() {
   install ${WORKDIR}/build/plugins/libmm-plugin-simtech.so ${D}/usr/lib/ModemManager/.
}

