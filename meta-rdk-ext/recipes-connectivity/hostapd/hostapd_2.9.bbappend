FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append_broadband = " ${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '', 'file://CVE-2022-23303-4.patch', d)} \
                           "
