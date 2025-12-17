FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"


SRC_URI_append_dunfell = " file://CVE-2021-42374_fix.patch "
SRC_URI_append_dunfell = " file://CVE-2021-42376_fix.patch "
SRC_URI_append_dunfell = " file://CVE-2021-423xx-awk.patch "
SRC_URI_append_dunfell = " file://CVE-2022-48174_fix.patch "
SRC_URI_append_dunfell = " file://CVE-2022-28391_fix.patch "


SRC_URI_remove_hybrid = " \
			file://CVE-2021-42374_fix.patch \
			file://CVE-2021-42376_fix.patch \
			file://CVE-2021-423xx-awk.patch \
			file://CVE-2022-48174_fix.patch \
			file://CVE-2022-28391_fix.patch \
        		"
