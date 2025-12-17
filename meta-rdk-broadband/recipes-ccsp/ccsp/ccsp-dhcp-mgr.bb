SUMMARY = "This receipe provides dhcp manager component support."
SECTION = "console/utils"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=8f98bf3e9ebc1788ad35a2e5b0b9191f"

DEPENDS = "ccsp-common-library dbus utopia ccsp-lm-lite"
DEPENDS_append = " hal-cm hal-dhcpv4c hal-ethsw hal-moca hal-mso_mgmt hal-mta hal-platform hal-vlan hal-wifi curl ccsp-misc ccsp-hotspot cjson libsyswrapper halinterface libunpriv "
require ccsp_common.inc
SRC_URI = "${RDKB_CCSP_ROOT_GIT}/DhcpManager/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=DhcpManager"
CFLAGS += " -Wall -Werror -Wextra -Wno-shift-negative-value -Wno-attribute-warning"
CFLAGS_append = " -Wno-format-truncation -Wno-incompatible-pointer-types -Wno-format-overflow -Wno-deprecated-declarations -Wno-sizeof-pointer-memaccess -Wno-memset-elt-size -Wno-maybe-uninitialized "

S = "${WORKDIR}/git"

PV = "${RDK_RELEASE}+git${SRCPV}"
SRCREV = "${AUTOREV}"
SRCREV_FORMAT = "${AUTOREV}"




inherit autotools ${@bb.utils.contains("DISTRO_FEATURES", "kirkstone", "python3native", "pythonnative", d)}
inherit systemd

ENABLE_MAPT = "--enable-maptsupport=${@bb.utils.contains('DISTRO_FEATURES', 'nat46', 'yes', 'no', d)}"
EXTRA_OECONF_append = " ${ENABLE_MAPT}"
EXTRA_OECONF_append  = " --with-ccsp-platform=bcm --with-ccsp-arch=arm "

#PACKAGECONFIG ?= "dropearly"
#PACKAGECONFIG[dropearly] = "--enable-dropearly,--disable-dropearly"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"
CFLAGS_append  = " ${@bb.utils.contains('DISTRO_FEATURES', 'dhcp_manager', '-DFEATURE_RDKB_DHCP_MANAGER', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'bci', '-DCISCO_CONFIG_TRUE_STATIC_IP -DCISCO_CONFIG_DHCPV6_PREFIX_DELEGATION -DCONFIG_CISCO_TRUE_STATIC_IP -D_BCI_FEATURE_REQ', '', d)}"

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
LDFLAGS_remove = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', '-lsafec-3.5', '', d)}"
LDFLAGS_append_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec-3.5.1 ', '', d)}"
LDFLAGS_append_kirkstone = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"
#CFLAGS_append  = " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', ' -DFEATURE_RDKB_WAN_MANAGER', '', d)}"
CFLAGS_append  = " ${@bb.utils.contains('DISTRO_FEATURES', 'ra_monitor_support', ' -DRA_MONITOR_SUPPORT', '', d)}"

#LDFLAGS_append_dunfell = " -lrt"

EXTRA_OECONF_append = " --enable-dhcp_server_support=yes "
EXTRA_OECONF_append = " --enable-dhcp_client_support=yes "

EXTRA_OECONF_append = " --enable-dhcpv4_server_support=yes "
EXTRA_OECONF_append = " --enable-dhcpv6_server_support=yes "
EXTRA_OECONF_append = " --enable-dhcpv4_client_support=yes "
EXTRA_OECONF_append = " --enable-dhcpv6_client_support=yes "
EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'bci', ' --enable-bci_support=yes ', '', d)}"

CFLAGS_append = " -DDHCPV4_SERVER_SUPPORT "
CFLAGS_append = " -DDHCPV6_SERVER_SUPPORT "
CFLAGS_append = " -DDHCPV4_CLIENT_SUPPORT "
CFLAGS_append = " -DDHCPV6_CLIENT_SUPPORT "

CFLAGS_append = " -UFEATURE_RDKB_WAN_MANAGER"
CFLAGS_append = " -DDHCPV4_CLIENT_UDHCPC "
CFLAGS_append = " -DDHCPV6_CLIENT_DIBBLER "
CFLAGS_append = " -DDUID_UUID_ENABLE "
CFLAGS_append = " -DDHCPV6C_PSM_ENABLE "
CFLAGS_append = " -DCONFIGURABLE_OPTIONS "
CFLAGS_append = " -DFEATURE_RDKB_CONFIGURABLE_WAN_INTERFACE "
CFLAGS_append = " -DUDHCPC_RUN_IN_FOREGROUND "

CFLAGS_append = " \
    -I${STAGING_INCDIR} \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -I${STAGING_INCDIR}/utapi \
    -I${STAGING_INCDIR}/wrp-c \
    -I${STAGING_INCDIR}/utctx \
    -I${STAGING_INCDIR}/ulog \
    -I${STAGING_INCDIR}/syscfg \
    -I${STAGING_INCDIR}/cjson \
    "
LDFLAGS_append = " \
    -lccsp_common \
    -ldbus-1 \
    -lutctx \
    -lutapi \
    -lulog \
    -lcjson \
    -lm \
    -lwrp-c \
    -lapi_dhcpv4c \
    -lsysevent \
    -lsecure_wrapper \
    -lprivilege \
    -lnanomsg \
    "
do_compile_prepend () {
	(${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/config/TR181-DHCPMgr.XML ${S}/source/DHCPMgrSsp/dm_pack_datamodel.c)
}

do_install_append () {
    # Config files and scripts
    install -d ${D}/usr/ccsp/dhcpmgr
    install -d ${D}/etc/ipv6rtmon/
    install -m 755 ${S}/config/notify.sh ${D}/etc/ipv6rtmon/
    install -m 644 ${S}/config/TR181-DHCPMgr.XML -t ${D}/usr/ccsp/dhcpmgr
    if ${@bb.utils.contains('DISTRO_FEATURES', 'dhcp_manager', 'true', 'false', d)}; then
        install -D -m 0644 ${S}/config/CcspDHCPMgr.service ${D}${systemd_unitdir}/system/CcspDHCPMgr.service
        if ${@bb.utils.contains('DISTRO_FEATURES', 'bci', 'true', 'false', d)}; then
            sed -i -- 's/WantedBy=.*/WantedBy=multi-user.target/g' ${D}${systemd_unitdir}/system/CcspDHCPMgr.service
        fi
    fi
}
FILES_${PN} += " \
    ${prefix}/ccsp/dhcpmgr/TR181-DHCPMgr.XML  \
    ${bindir}/* \
"

DEPENDS_append = " webconfig-framework trower-base64 msgpack-c "
RDEPENDS_${PN}_append = " trower-base64 msgpack-c "
CFLAGS_append = " \
    -I${STAGING_INCDIR}/trower-base64 \
    -I${STAGING_INCDIR}/msgpackc \
"
LDFLAGS_append = " \
    -lmsgpackc \
    -ltrower-base64 \
"
FILES_${PN}_append = "${@bb.utils.contains('DISTRO_FEATURES', 'dhcp_manager','${systemd_unitdir}/system/CcspDHCPMgr.service', '', d)}"
SYSTEMD_SERVICE_${PN} += " ${@bb.utils.contains('DISTRO_FEATURES', 'dhcp_manager', 'CcspDHCPMgr.service', '', d)}"
