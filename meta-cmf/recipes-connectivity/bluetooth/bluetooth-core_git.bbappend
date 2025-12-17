FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

ENABLE_SAFEC = "--enable-safec=${@bb.utils.contains('DISTRO_FEATURES', 'safec','yes', 'no', d)}"
EXTRA_OECONF += " ${ENABLE_SAFEC}"

SRC_URI += " ${@bb.utils.contains('DISTRO_FEATURES', 'auth-ack-bt', ' \
    file://btrCore_BTAgentRequestAuthorization.patch \
    ', '', d)} \
        "
