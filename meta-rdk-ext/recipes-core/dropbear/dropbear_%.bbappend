FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

do_install_append() {
    	if [ "${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'systemd', '', d)}" = "systemd" ]; then
		sed -i -- '/EnvironmentFile=.*/a BindToDevice=${ESTB_INTERFACE}' ${D}${systemd_unitdir}/system/dropbear@.service
		sed -i -- '/EnvironmentFile=.*/a EnvironmentFile=/etc/device.properties' ${D}${systemd_unitdir}/system/dropbear@.service
	fi
}
