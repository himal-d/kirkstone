FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append_video = " file://CVE-2019-12973_fix.patch \
                         file://CVE-2020-15389_fix.patch \
                         file://CVE-2020-27814_fix.patch \
                         file://CVE-2020-27823_fix.patch \
                         file://CVE-2020-27824_fix.patch \
                         file://CVE-2020-27841_fix.patch \
                         file://CVE-2020-27842_fix.patch \
                         file://CVE-2020-27843_fix.patch \
                       "
