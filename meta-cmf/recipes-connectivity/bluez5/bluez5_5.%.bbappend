SRC_URI_remove_broadband = "file://Bluetooth_service_dependency_broadband.patch"

PACKAGES =+ "${PN}-bluetoothd ${PN}-mpris-proxy"

FILES_${PN}-bluetoothd = "${libdir}/bluez5/bluetooth/bluetoothd"
FILES_${PN}-mpris-proxy = "${bindir}/mpris-proxy"
