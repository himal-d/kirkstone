FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI += "file://CVE-2018-16301.patch \
            ${@bb.utils.contains('DISTRO_FEATURES', 'yocto-3.1.15', '', 'file://CVE-2020-8037.patch', d)} \
"
