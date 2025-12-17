FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " file://CVE-2023-25155_7.0.4_fix.patch \
                   file://CVE-2023-28856_7.0.4_fix.patch \
                   file://CVE-2023-36824_7.0.4_fix.patch \
                   file://CVE-2022-24834_7.0.4_fix.patch \
                   file://CVE-2022-35951_7.0.4_fix.patch \
                 "
