FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " file://CVE-2023-2603_2.65_fix.patch \
                 "
