do_install_append () {
	if [ "${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'systemd', '', d)}" = "systemd" ]; then
		echo "export SYSTEMD_PAGER=/bin/cat" >> ${D}${sysconfdir}/profile
	fi
	if [ -e ${D}${sysconfdir}/fstab ]; then
		sed -i -e '/^\/dev\/root/ s/\([[:space:]]*[[:digit:]]\)\([[:space:]]*\)[[:digit:]]$/\1\20/' ${D}${sysconfdir}/fstab
	fi
}

do_install_append_kirkstone(){
	if [ "${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'systemd', '', d)}" = "systemd" ]; then
		#SYSTEMD_PAGER will be ignored if SYSTEMD_PAGERSECURE is not set. cat doesn't have any secure mode. Only less have secure mode as of now. Since we are using cat as our pager, disabling the pagersecure. 
                echo "export SYSTEMD_PAGERSECURE=0" >> ${D}${sysconfdir}/profile
        fi
}
