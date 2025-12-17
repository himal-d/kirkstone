EXTRA_OECONF_append = " --enable-cmdlib=no --enable-dmeventd=no "

SYSTEMD_SERVICE:${PN}:remove = "lvm2-monitor.service dm-event.socket dm-event.service lvm2-lvmetad.socket lvm2-pvscan@.service blk-availability.service"

do_install_append(){
        rm -rf ${D}${base_libdir}/udev/rules.d/10-dm.rules
}

INSANE_SKIP_${PN} = "installed-vs-shipped"