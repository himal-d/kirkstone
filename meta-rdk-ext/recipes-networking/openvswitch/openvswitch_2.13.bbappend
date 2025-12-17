FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append_broadband = " ${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '', 'file://CVE-2021-3905_fix.patch', d)}"

