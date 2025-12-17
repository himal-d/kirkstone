FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

PLUME_CORE_PATCHES := "core"
PLUME_PLATFORM_RDK_PATCHES := "platform/rdk"

OPENSYNC_CORE_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', ' file://${PLUME_CORE_PATCHES}/0001-ESW-12184-ds-len-util.patch;patchdir=../core', ' ', d)}"
OPENSYNC_CORE_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', ' file://${PLUME_CORE_PATCHES}/1100-onewifi-kconfig.patch;patchdir=../core', ' ', d)}"
OPENSYNC_CORE_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', ' file://${PLUME_CORE_PATCHES}/1101-onewifi-code.patch;patchdir=../core', ' ', d)}"
OPENSYNC_CORE_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', ' file://${PLUME_CORE_PATCHES}/1102-onewifi-bm-sm.patch;patchdir=../core', ' ', d)}"
OPENSYNC_CORE_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', ' file://${PLUME_CORE_PATCHES}/1103-onewifi-ocs-support.patch;patchdir=../core', ' ', d)}"
OPENSYNC_CORE_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', ' file://${PLUME_CORE_PATCHES}/0001-RDKB-48818-SM-APP-Change-path-for-ds_tree-headers.patch;patchdir=../core', ' ', d)}"
OPENSYNC_CORE_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', ' file://${PLUME_CORE_PATCHES}/rpi_fix_for_64bit_build_errors.patch;patchdir=../core', ' ', d)}"
OPENSYNC_CORE_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', ' file://${PLUME_CORE_PATCHES}/1103-onewifi-wifi-7.patch;patchdir=../core', ' ', d)}"
OPENSYNC_CORE_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'extender', ' file://${PLUME_CORE_PATCHES}/opensync_rpi_kirk_build_error.patch;patchdir=../core', ' ', d)}"
OPENSYNC_CORE_URI += " file://${PLUME_CORE_PATCHES}/createVersion.patch;patchdir=../core"

OPENSYNC_PLATFORM_URI += " file://${PLUME_PLATFORM_RDK_PATCHES}/opensync_compilation_errors_fix_64b.patch;patchdir=../platform/rdk"
OPENSYNC_PLATFORM_URI += " file://${PLUME_PLATFORM_RDK_PATCHES}/Added_rdkbwifi_db_creation_changes.patch;patchdir=../platform/rdk"

DEPENDS += " c-ares"
SYSROOT_DIRS += "/usr/opensync/lib"
EXTRA_OEMAKE += "INSTALL_HEADERS=y"
TARGET_CC_ARCH_append_kirkstone = "${LDFLAGS}"
do_install_append_kirkstone () {
          rm ${D}/sbin/reboot
          rm -r ${D}/sbin 
}
FILES_${PN} += "${prefix}/include/opensync/ \
                /etc \
 "

do_install_append () {
         install -d ${D}${includedir}/src
         cp ${S}/src/lib/common/src/memutil.c.h ${D}${includedir}/src
         cp ${S}/work/*/pb-inc/opensync_stats.pb-c.h  ${D}${includedir}/opensync
}
