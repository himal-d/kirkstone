include ${@bb.utils.contains('DISTRO_FEATURES', 'systemd-profile', 'profiles/rdk-${BPN}-profile-${PV}.inc', 'profiles/generic-profile.inc', d)}

PACKAGECONFIG_remove = " pam idn quotacheck randomseed logind  hostnamed timedated localed resolve coredump tpm"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append = " file://journalctl-250.patch \
                   file://0003-Remove-MS-constants-from-missing-header-file-250.patch \
                   file://10-ubi-device-systemd.rules \
                   file://99-default.preset \
                   file://0001-cgroup-downgrade-warning-if-we-can-t-get-ID-off-cgro.patch \
"

EXTRA_OECONF += " --enable-polkit=no"
PACKAGECONFIG_remove = "pam"
PACKAGECONFIG_append = " kmod"

FILES_${PN} += "${sysconfdir}/udev/rules.d/10-ubi-device-systemd.rules"

do_install_append() {
    rm -rf ${D}${sysconfdir}/resolv.conf
    sed -i '/After=swap.target/d' ${D}${systemd_unitdir}/system/tmp.mount

    rm -rf ${D}${base_libdir}/systemd/system/ldconfig.service
    rm -rf ${D}${base_libdir}/systemd/system/sysinit.target.wants/ldconfig.service

    # disable LLMNR queries
    if [ -f  ${D}${sysconfdir}/systemd/resolved.conf ]; then
        sed -i '/LLMNR/c\LLMNR=no' ${D}${sysconfdir}/systemd/resolved.conf
    fi
}

do_install_append_client() {
    install -d ${D}${sysconfdir}/udev/rules.d
    install -m 0644 ${WORKDIR}/10-ubi-device-systemd.rules ${D}${sysconfdir}/udev/rules.d/
    rm -rf ${D}${base_libdir}/systemd/systemd-update-done
    rm -rf ${D}${base_libdir}/systemd/system/systemd-update-done.service
    rm -rf ${D}${base_libdir}/systemd/system/sysinit.target.wants/systemd-update-done.service
    sed -i -e 's/systemd-update-done.service//g' ${D}${systemd_unitdir}/system/systemd-journal-catalog-update.service
    sed -i -e 's/systemd-update-done.service//g' ${D}${systemd_unitdir}/system/systemd-hwdb-update.service || true
}

do_install_append_hybrid() {
    install -d ${D}${sysconfdir}/udev/rules.d
    install -m 0644 ${WORKDIR}/10-ubi-device-systemd.rules ${D}${sysconfdir}/udev/rules.d/
    sed -i -e 's/systemd-update-done.service//g' ${D}${systemd_unitdir}/system/systemd-hwdb-update.service || true
}

do_install_append() {
    install -Dm 0644 ${WORKDIR}/99-default.preset ${D}${systemd_unitdir}/system-preset/99-default.preset
}
