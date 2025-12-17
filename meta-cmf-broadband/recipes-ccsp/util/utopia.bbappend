FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

PV_kirkstone = "${RDK_RELEASE}+git${SRCPV}"
SRC_URI += "file://udhcpc.script"
SRC_URI += "file://udhcpc.vendor_specific"
SRC_URI += "file://dhcpswitch.sh"

SRC_URI  += " ${@bb.utils.contains('DISTRO_FEATURES', 'device_gateway_association', 'file://Device_Gateway_Association.patch;apply=no', '', d)}"

SRC_URI_append += "${@bb.utils.contains('DISTRO_FEATURES','WanFailOverSupportEnable','file://udhcpc_backupwan.script','',d)}"
IsRdkbWanFailOverSupported = "${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', 'true', 'false', d)}"

DEPENDS += " nanomsg"

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', '-D_WAN_MANAGER_ENABLED_', '', d)}"
CFLAGS_remove_dunfell = "-Wno-enum-conversion"

LDFLAGS += " -lpthread -lhal_platform -lccsp_common"

#RDKBDEV-83 -Patch code based on distro
do_utopia_patches() {
if [ "${@bb.utils.contains("DISTRO_FEATURES", "device_gateway_association", "yes", "no", d)}" = "yes" ]; then    
    cd ${S} 
    if [ ! -e patch_applied ]; then
        patch -p1 < ${WORKDIR}/Device_Gateway_Association.patch
        touch patch_applied
    fi
fi
}
addtask utopia_patches after do_unpack before do_compile

do_install_append () {
    if [ "${IsRdkbWanFailOverSupported}" = "true" ]; then
        install -d ${D}${sysconfdir}/
        install -m 755 ${WORKDIR}/udhcpc_backupwan.script ${D}${sysconfdir}/
    fi
}

FILES_${PN} += "${@bb.utils.contains('DISTRO_FEATURES','WanFailOverSupportEnable','${sysconfdir}/udhcpc_backupwan.script','',d)}"

