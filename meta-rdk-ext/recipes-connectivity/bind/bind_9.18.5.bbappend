FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = "file://CVE-2022-2795_9.18.5_fix.patch \
                  file://CVE-2022-2881_9.18.5_fix.patch \
                  file://CVE-2022-2906_9.18.5_fix.patch \
                  file://CVE-2022-3080_9.18.5_fix.patch \
                  file://CVE-2022-3094_9.18.5_fix.patch \
                  file://CVE-2022-3736_9.18.5_fix.patch \
                  file://CVE-2022-3924_9.18.5_fix.patch \
                  file://CVE-2023-2828_9.18.5_fix.patch \
                  file://CVE-2023-3341_9.18.5_fix.patch \
                  file://CVE-2023-4236_9.18.5_fix.patch \
                  file://CVE-2023-50387_9.18.5_fix.patch \
                 "

SRC_URI_remove_client = "file://CVE-2023-2828_9.18.5_fix.patch \
                        "
