FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

# for bluez support
SRC_URI_append_broadband += "file://Bluetooth_service_dependency_broadband.patch"
SRC_URI_append_broadband += " ${@bb.utils.contains('DISTRO_FEATURES', 'btr_hciadv', 'file://Bluetooth_service_beacon_dependency_broadband.patch', '', d)}"
