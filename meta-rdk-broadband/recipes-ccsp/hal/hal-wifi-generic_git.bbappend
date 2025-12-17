FILESEXTRAPATHS_prepend := " ${@bb.utils.contains('DISTRO_FEATURES', 'hal-ipc', "${THISDIR}/files:", "", d)}"

SRC_URI_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'hal-ipc', " file://cmxb7-onewifi-hal-ipc.patch", "", d)}"
