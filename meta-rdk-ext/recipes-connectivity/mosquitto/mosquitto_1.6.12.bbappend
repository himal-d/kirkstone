FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append_broadband = " ${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '', 'file://CVE-2021-41039_fix.patch \
                                                                                  file://CVE-2021-34432_fix.patch', d)} \
                           "
