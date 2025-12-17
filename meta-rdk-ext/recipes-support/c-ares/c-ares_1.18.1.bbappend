FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " file://CVE-2022-4904_1.18.1_fix.patch \
                   file://CVE-2023-31124_fix.patch \
                   file://CVE-2023-31130_fix.patch \
                   file://CVE-2023-31147_fix.patch \
                   file://CVE-2023-32067_fix.patch \ 
                 "

