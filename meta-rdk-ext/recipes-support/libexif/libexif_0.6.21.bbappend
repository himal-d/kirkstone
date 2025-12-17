FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append_video = " file://CVE-2020-0093_fix.patch \
                         file://CVE-2020-0181_fix.patch \
                         file://CVE-2020-0198_fix.patch \
                         file://CVE-2020-12767_fix.patch \
                   	 file://CVE-2020-13112_fix.patch \
                   	 file://CVE-2020-13113_fix.patch \
                       "
