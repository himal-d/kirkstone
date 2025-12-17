FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " file://fix_pollfd_dispatch.patch \
                   file://CVE-2021-3800_fix.patch \
                   file://CVE-2023-32665_fix.patch \
                 "

SRC_URI_append_broadband = " file://CVE-2020-35457_fix.patch \
                             file://CVE-2020-6750_fix.patch \
                             file://CVE-2021-27218_pre_fix.patch \
                             file://CVE-2021-27218_fix.patch \
                           "
