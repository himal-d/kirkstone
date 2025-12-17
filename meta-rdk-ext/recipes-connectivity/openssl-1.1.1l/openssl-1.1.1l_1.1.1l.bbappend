FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " file://CVE-2021-4160_fix.patch \
                   file://CVE-2022-2097_fix.patch \
                   file://CVE-2022-0778_fix.patch \
                   file://CVE-2022-1292_fix.patch \
                   file://CVE-2022-2068_fix.patch \
                   file://CVE-2022-4304_1.1.1l_fix.patch \
                   file://CVE-2022-4450_fix_openssl1.1.1l.patch \
                   file://CVE-2023-0215_fix_openssl1.1.1l.patch \
                   file://CVE-2023-0286_fix_openssl1.1.1l.patch \
                   file://CVE-2023-0464_1.1.1l_fix.patch \
                   file://CVE-2023-0465_1.1.1l_fix.patch \
                   file://CVE-2023-0466_1.1.1l_fix.patch \
                   file://CVE-2024-0727_openssl_1.1.1l_fix.patch \
                   file://CVE-2023-2650_1.1.1l_fix.patch \
                   file://CVE-2023-3817_1.1.1l_fix.patch \
                   file://CVE-2023-4807_1.1.1l_fix.patch \
                  "
