# Use Bluez 5.48 for ControlMgr and BLE Voice support.
PREFERRED_VERSION_bluez5 = "${@bb.utils.contains('DISTRO_FEATURES', 'enable-rdkv-bt-voice', '5.48', '', d)}"
#BBMASK .= "${@bb.utils.contains('DISTRO_FEATURES', 'enable-rdkv-bt-voice', '', '|meta-rdk-ext/recipes-connectivity/bluez/bluez5_5.48.bb', d)}"
PREFERRED_VERSION_binutils = "2.27"
BBMASK .= "${@bb.utils.contains('VIDEO_CAMERA', '1', '|./recipes-multimedia/pipewire/', '', d)}"
BBMASK .= "${@bb.utils.contains('VIDEO_CAMERA', '1', '|./recipes-multimedia/wireplumber/', '', d)}"