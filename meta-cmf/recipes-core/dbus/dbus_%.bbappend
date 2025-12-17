FILESEXTRAPATHS_prepend := "${THISDIR}/dbus:"

RDEPENDS_${PN} += " ${@bb.utils.contains('DISTRO_FEATURES', 'apparmor', 'apparmor', '', d)}"

RDEPENDS_${PN}_remove_camera = "apparmor"
RDEPENDS_${PN}_remove_broadband = "apparmor"
RDEPENDS_${PN}_remove_extender = "apparmor"
