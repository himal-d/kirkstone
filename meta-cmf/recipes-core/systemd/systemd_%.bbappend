RDEPENDS_${PN} += " ${@bb.utils.contains('DISTRO_FEATURES', 'apparmor', 'apparmor', '', d)}"
RDEPENDS_${PN}-analyze += " ${@bb.utils.contains('DISTRO_FEATURES', 'apparmor', 'apparmor', '', d)}"

RDEPENDS_${PN}_remove_camera = "apparmor"
RDEPENDS_${PN}-analyze_remove_camera = "apparmor"

RDEPENDS_${PN}_remove_broadband = "apparmor"
RDEPENDS_${PN}-analyze_remove_broadband = "apparmor"

RDEPENDS_${PN}_remove_extender = "apparmor"
RDEPENDS_${PN}-analyze_remove_extender = "apparmor"

DEPENDS_remove_camera = "apparmor"
DEPENDS_remove_broadband = "apparmor"
DEPENDS_remove_extender = "apparmor"
