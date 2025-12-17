FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

FULL_OPTIMIZATION_remove = "-Os"
FULL_OPTIMIZATION_append = "-O2"

SRC_URI_append = " file://CVE-2023-0687_2.35_fix.patch \
                   file://CVE-2023-4813_2.35_fix.patch \
                   file://CVE-2023-4911_2.35_fix.patch \
                 "
