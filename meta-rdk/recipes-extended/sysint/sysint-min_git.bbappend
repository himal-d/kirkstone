BENCHMARK_ENABLED = "${@bb.utils.contains('DISTRO_FEATURES', 'benchmark_enable','true', 'false',d)}"

do_install_append() {
    install -d ${D}${sysconfdir}
    install -m 0644 ${S}/etc/*.properties ${D}${sysconfdir}
     if [ "${BENCHMARK_ENABLED}" = "true" ]; then
       echo "IMAGE_TYPE=OSS" >> ${D}${sysconfdir}/device.properties
    fi
}

