FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append_broadband = " ${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '', 'file://CVE-2022-29824_fix.patch', d)} \
                           "
