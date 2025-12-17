FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " file://CVE-2020-8619_fix.patch \
   		   file://CVE-2020-8622_fix.patch \
                   file://CVE-2020-8623_fix.patch \
                   file://CVE-2020-8624_fix.patch \
                   file://CVE-2020-8625_fix.patch \
                   file://CVE-2022-2795_fix.patch \
                   file://CVE-2022-38177_fix.patch \
                   file://CVE-2022-38178_fix.patch \
                   file://CVE-2023-2828_fix.patch \
                   file://CVE-2023-3341_fix.patch \
                 "

SRC_URI_remove_broadband  = "file://CVE-2022-38178_fix.patch \
                            "
SRC_URI_remove_client = "file://CVE-2023-2828_fix.patch \
                        "
