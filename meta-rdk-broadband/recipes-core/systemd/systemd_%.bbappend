FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

# Remove unwanted systemd services
PACKAGECONFIG_remove += "${@bb.utils.contains("MACHINE_OEM_NAME", "pace", " ", " timesyncd ", d)}"

SRC_URI += " \
            file://50-reservlocalport.conf \
           "

do_install_append() {
        install -m 644 ${WORKDIR}/50-reservlocalport.conf ${D}${sysconfdir}/sysctl.d
}

FILES_${PN} += "${sysconfdir}/sysctl.d/50-reservlocalport.conf \
               "
