FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://0001-Fix-race-issue-with-tools-directory.patch \
            file://CVE-2019-8922.patch \
            file://CVE-2020-27153.patch \
            file://CVE-2022-0204.patch \
            file://CVE-2020-0556.patch \
            file://0002-Fixing-connection-failure-due-to-CVE-2020-0556.patch \
            file://CVE-2018-10910.patch \
            file://CVE-2018-10910_I.patch \
            file://bluez_enable_security.patch \
            file://CVE-2019-8921.patch \
            file://CVE-2022-39176_5.48_fix.patch \
            file://CVE-2022-39177_5.48_fix.patch \
            file://CVE-2023-45866.patch \
            file://0003-Fix-input-hog-connection-with-slow-pairing-devices.patch \
"
