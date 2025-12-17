FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " file://CVE-2020-27153_5.54.patch \
                   file://CVE-2022-39176_5.54_fix.patch \
                   file://CVE-2022-39177_5.54_fix.patch \
                   file://CVE-2023-45866-5.54.patch \
                 "

