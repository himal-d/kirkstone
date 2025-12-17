EXTRA_OECMAKE += " ${@bb.utils.contains('DISTRO_FEATURES', 'webconfig_bin', '-DPLATFORM=DEVICE_GATEWAY', '', d)}"
