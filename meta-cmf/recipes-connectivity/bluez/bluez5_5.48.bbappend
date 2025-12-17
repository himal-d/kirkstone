FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += " ${@bb.utils.contains('DISTRO_FEATURES', 'auth-ack-bt', ' \
    file://Modify-Request-authorization-for-bt-connection.patch \
    ', '', d)} \
        "
