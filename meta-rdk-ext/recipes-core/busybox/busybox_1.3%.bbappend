SRC_URI_append = " file://0001-add-ENABLE_FEATURE_SYSTEMD-and-use-it-in-syslogd.patch"
SRC_URI_append = " file://busybox-1.31-ping-mdev-support.patch"
SRC_URI_append_dunfell = " ${@bb.utils.contains('DISTRO_FEATURES', 'yocto-3.1.15', '', 'file://CVE-2018-1000500.patch', d)}"

VERSION_PATCHES_append_client = " ${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', ' file://busybox-1.35-udhcp-trigger-milestones.patch', ' file://busybox-1.31-udhcp-trigger-milestones.patch', d)}"

