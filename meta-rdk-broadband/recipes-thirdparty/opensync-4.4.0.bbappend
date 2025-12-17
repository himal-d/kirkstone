DEPENDS += " ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', 'hal-wifi-generic', '', d)}"
