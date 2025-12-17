FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " file://dropbear_2019-ssh_log.patch"
SRC_URI_append = " file://ssh_telemetry_2019_uninit_init_add.patch"

SRC_URI_append_dunfell = " file://dropbear_2019-verbose.patch \
                           file://dropbear_2019-revsshipv6.patch \
                           file://dropbear_2019-Fixed-Race-Conditions-Observed-when-using-port-forwa.patch \
                           ${@bb.utils.contains('DISTRO_FEATURES', 'yocto-3.1.15', '', 'file://dropbear_2019-CVE-2020-36254.patch', d)} \
"

SRC_URI_append = " file://CVE-2021-36369_fix.patch"

CFLAGS_append_broadband = " -DRDK_BROADBAND"

do_install_append() {
        if [ "${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'systemd', '', d)}" = "systemd" ]; then
                sed -i -- '/EnvironmentFile=.*/a BindToDevice=${ESTB_INTERFACE}' ${D}${systemd_unitdir}/system/dropbear@.service
                sed -i -- '/EnvironmentFile=.*/a EnvironmentFile=/etc/device.properties' ${D}${systemd_unitdir}/system/dropbear@.service
        fi
}
