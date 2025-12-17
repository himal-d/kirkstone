SUMMARY = "CCSP PandMSsp component"
HOMEPAGE = "http://github.com/belvedere-yocto/CcspPandM"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

RPROVIDES_${PN} = "ccsp-p-and-m"

DEPENDS = "ccsp-common-library webconfig-framework ccsp-lm-lite telemetry ccsp-hotspot mountutils"
DEPENDS_append = " utopia hal-cm hal-dhcpv4c hal-ethsw hal-moca hal-mso_mgmt hal-mta hal-platform hal-vlan hal-wifi curl ccsp-misc ccsp-hotspot cjson libsyswrapper cjson trower-base64 msgpack-c nanomsg wrp-c libparodus rbus"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'systemd', '', d)}"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'enable_rdkscheduler', 'rdk-scheduler', " ", d)}"

DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'fwupgrade_manager', ' hal-fwupgrade', '',d)}"
 
RDEPENDS_${PN}_append = " cjson trower-base64 msgpack-c nanomsg wrp-c libparodus "

RDEPENDS_${PN}-ccsp_append = " bash"
RDEPENDS_${PN}-ccsp_remove_morty = "bash"

require ccsp_common.inc

CFLAGS += " -Wall -Werror -Wextra -Wno-shift-negative-value"

CFLAGS_append = " -Wno-deprecated-declarations -Wno-stringop-overflow -Wno-format-truncation -Wno-enum-conversion -Wno-array-bounds -Wno-misleading-indentation"

SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/CcspPandM;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=CcspPandM"

#SRC_URI_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', 'file://0001-disable-fwupgrade-dm.patch', '', d)}"

#SRC_URI_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', 'file://0002-disable-dhcp-clients-tr181-dml-in-PandM.patch', '', d)}"
#SRC_URI_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', 'file://0003-disable-ppp-tr181-dml-in-PandM.patch', '', d)}"

SRCREV_CcspPandM = "${AUTOREV}"
SRCREV_FORMAT = "CcspPandM"
PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

inherit autotools ${@bb.utils.contains("DISTRO_FEATURES", "kirkstone", "python3native", "pythonnative", d)} breakpad-logmapper

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
LDFLAGS_remove = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', '-lsafec-3.5', '', d)}"
LDFLAGS_append_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec-3.5.1 ', '', d)}"
LDFLAGS_append_kirkstone = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'wbCfgTestApp', '-DWEBCFG_TEST_SIM', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'ethstats', '-DETH_STATS_ENABLED', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'wifimotion', '-DFEATURE_COGNITIVE_WIFIMOTION', '', d)}"
LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', '-lnanomsg', '', d)}"
LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'fwupgrade_manager', '-lfw_upgrade', '', d)}"
LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'enable_rdkscheduler', '-lrdk_scheduler', " ", d)}"

CFLAGS_append = " \
    -I${STAGING_INCDIR} \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -I${STAGING_INCDIR}/utapi \
    -I${STAGING_INCDIR}/utctx \
    -I${STAGING_INCDIR}/ulog \
    -I${STAGING_INCDIR}/syscfg \
    -I${STAGING_INCDIR}/wrp-c \
    -I${STAGING_INCDIR}/nanomsg \
    -I${STAGING_INCDIR}/trower-base64 \
    -I${STAGING_INCDIR}/msgpackc \
    -I${STAGING_INCDIR}/libparodus \
    -I${STAGING_INCDIR}/cjson \
    -I${STAGING_INCDIR}/rbus \
    "

EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', '--enable-notify', '', d)}"

ENABLE_MAPT = "--enable-maptsupport=${@bb.utils.contains('DISTRO_FEATURES', 'nat46', 'yes', 'no', d)}"
EXTRA_OECONF_append = " ${ENABLE_MAPT}"

ENABLE_WIFI_MANAGE = "--enable-wifimanagesupport=${@bb.utils.contains('DISTRO_FEATURES', 'ManagedWiFiSupportEnable', 'yes', 'no', d)}"
EXTRA_OECONF_append = " ${ENABLE_WIFI_MANAGE}"

EXTRA_OECONF_append += "${@bb.utils.contains("DISTRO_FEATURES", "SpeedBoostSupportEnable", "--enable-speedboost=yes", " ", d)}"

CFLAGS_append = " -DCONFIG_VENDOR_CUSTOMER_COMCAST -DCONFIG_INTERNET2P0 -DCONFIG_CISCO_HOTSPOT"

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'bci', '-DCISCO_CONFIG_TRUE_STATIC_IP -DCISCO_CONFIG_DHCPV6_PREFIX_DELEGATION -DCONFIG_CISCO_TRUE_STATIC_IP -D_BCI_FEATURE_REQ', '', d)}"

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'meshwifi', '-DENABLE_FEATURE_MESHWIFI', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'dslite', '-DDSLITE_FEATURE_SUPPORT', '', d)}" 
LDFLAGS_append = " \
    -ldbus-1 \
    -lutctx \
    -lutapi \
    -lm \
    -lcjson \
    -llibparodus \
    -lnanomsg \
    -lwrp-c \
    -lmsgpackc \
    -ltrower-base64 \
    -lm \
    -lpthread \
    -lrt \
    -lsysevent \
    -ltelemetry_msgsender \
    -lrbus \
"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'custom_ula', '-DCUSTOM_ULA', '', d)}"

LDFLAGS_append = " -lsyscfg"
LDFLAGS_remove_morty = " -lsyscfg"

do_compile_prepend () {

    if ${@bb.utils.contains('DISTRO_FEATURES', 'interworking', 'true', 'false', d)}; then
    sed -i '2i <?define FEATURE_SUPPORT_INTERWORKING=True?>' ${S}/config-arm/TR181-USGv2.XML
    fi
    if ${@bb.utils.contains('DISTRO_FEATURES', 'dslite', 'true', 'false', d)}; then
    sed -i '2i <?define DSLITE_FEATURE_SUPPORT=True?>' ${S}/config-arm/TR181-USGv2.XML
    fi
    if ${@bb.utils.contains('DISTRO_FEATURES', 'passpoint', 'true', 'false', d)}; then
    sed -i '2i <?define FEATURE_SUPPORT_PASSPOINT=True?>' ${S}/config-arm/TR181-USGv2.XML
    fi
    if ${@bb.utils.contains('DISTRO_FEATURES', 'offchannel_scan_5g', 'true', 'false', d)}; then
    sed -i '2i <?define FEATURE_OFF_CHANNEL_SCAN_5G=True?>' ${S}/config-arm/TR181-USGv2.XML
    fi
    if ${@bb.utils.contains('DISTRO_FEATURES', 'fwupgrade_manager', 'true', 'false', d)}; then
    sed -i '2i <?define FEATURE_FWUPGRADE_MANAGER=True?>' ${S}/config-arm/TR181-USGv2.XML
    fi
    if ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_xdsl_ppp_manager', 'true', 'false', d)}; then
    sed -i '2i <?define FEATURE_RDKB_XDSL_PPP_MANAGER=True?>' ${S}/config-arm/TR181-USGv2.XML
    fi
    if ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', 'true', 'false', d)}; then
    sed -i '2i <?define FEATURE_RDKB_WAN_MANAGER=True?>' ${S}/config-arm/TR181-USGv2.XML
    fi
    if ${@bb.utils.contains('DISTRO_FEATURES', 'RadiusGreyList', 'true', 'false', d)}; then
    sed -i '2i <?define FEATURE_SUPPORT_RADIUSGREYLIST=True?>' ${S}/config-arm/TR181-USGv2.XML
    fi
    if ${@bb.utils.contains('DISTRO_FEATURES', 'wifimotion', 'true', 'false', d)}; then
    sed -i '2i <?define FEATURE_COGNITIVE_WIFIMOTION=True?>' ${S}/config-arm/TR181-USGv2.XML
    fi
    sed -i '2i <?define CONFIG_INTERNET2P0=True?>' ${S}/config-arm/TR181-USGv2.XML
    sed -i '2i <?define CONFIG_VENDOR_CUSTOMER_COMCAST=True?>' ${S}/config-arm/TR181-USGv2.XML
    sed -i '2i <?define CONFIG_CISCO_HOTSPOT=True?>' ${S}/config-arm/TR181-USGv2.XML
    

	if ${@bb.utils.contains('DISTRO_FEATURES', 'bci', 'true', 'false', d)}; then
		sed -i '2i <?define BCI=True?>' ${S}/config-arm/TR181-USGv2.XML
        sed -i '2i <?define COSA_FOR_BCI=True?>' ${S}/config-arm/TR181-USGv2.XML
        sed -i '2i <?define CONFIG_CISCO_TRUE_STATIC_IP=True?>' ${S}/config-arm/TR181-USGv2.XML
        sed -i '2i <?define CONFIG_CISCO_FILE_TRANSFER=True?>' ${S}/config-arm/TR181-USGv2.XML
        
	else
        sed -i '2i <?define FEATURE_SUPPORT_ONBOARD_LOGGING=True?>' ${S}/config-arm/TR181-USGv2.XML
        sed -i '2i <?define MOCA_HOME_ISOLATION=True?>' ${S}/config-arm/TR181-USGv2.XML

        if ${@bb.utils.contains('DISTRO_FEATURES', 'ddns_broadband', 'true', 'false', d)}; then
        sed -i '2i <?define DDNS_BROADBANDFORUM=True?>' ${S}/config-arm/TR181-USGv2.XML
        fi
	fi
        if ${@bb.utils.contains('DISTRO_FEATURES', 'custom_ula', 'true', 'false', d)}; then
        sed -i '2i <?define CUSTOM_ULA=True?>' ${S}/config-arm/TR181-USGv2.XML
        fi
        if ${@bb.utils.contains('DISTRO_FEATURES', 'ManagedWiFiSupportEnable', 'true', 'false', d)}; then
            sed -i '2i <?define WIFI_MANAGE_SUPPORTED=True?>' ${S}/config-arm/TR181-USGv2.XML
        fi
        if ${@bb.utils.contains('DISTRO_FEATURES', 'dhcp_manager', 'true', 'false', d)}; then
            sed -i '2i <?define FEATURE_RDKB_DHCP_MANAGER=True?>' ${S}/config-arm/TR181-USGv2.XML
        fi
    (${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/config-arm/TR181-USGv2.XML ${S}/source/PandMSsp/dm_pack_datamodel.c)
}
do_install_append () {
    # Config files and scripts
    install -d ${D}/usr/ccsp/pam
    install -d ${D}${sysconfdir}
    install -m 755 ${S}/scripts/unique_telemetry_id.sh ${D}/usr/ccsp/pam/unique_telemetry_id.sh
    install -m 755 ${S}/scripts/launch_tr69.sh ${D}/usr/ccsp/pam/launch_tr69.sh
    install -d ${D}/usr/include/ccsp
    install -d ${D}/usr/include/middle_layer_src
    install -d ${D}/usr/include/middle_layer_src/pam
    install -m 644 ${S}/source/TR-181/include/*.h ${D}/usr/include/ccsp
    install -m 644 ${S}/source/TR-181/middle_layer_src/*.h ${D}/usr/include/middle_layer_src/pam
    install -m 755 ${S}/arch/intel_usg/boards/arm_shared/scripts/partners_defaults.json ${D}/etc/partners_defaults.json
    install -m 755 ${S}/arch/intel_usg/boards/arm_shared/scripts/ScheduleAutoReboot.sh ${D}/etc/ScheduleAutoReboot.sh
    install -m 755 ${S}/arch/intel_usg/boards/arm_shared/scripts/restart_services.sh ${D}/etc/restart_services.sh
    install -m 755 ${S}/arch/intel_usg/boards/arm_shared/scripts/AutoReboot.sh ${D}/etc/AutoReboot.sh
    install -m 755 ${S}/arch/intel_usg/boards/arm_shared/scripts/RebootCondition.sh ${D}/etc/RebootCondition.sh
}

#do_install_append_qemux86 () {
#   #Config files and scripts
#    install -m 644 ${S}/config-pc/COSAXcalibur.XML -t ${D}/usr/ccsp/pam
#}

PACKAGES += "${PN}-ccsp"

FILES_${PN}-ccsp = " \
    ${prefix}/ccsp/pam/CcspDmLib.cfg  \
    ${prefix}/ccsp/pam/CcspPam.cfg  \
    ${prefix}/ccsp/pam/email_notification_monitor.sh  \
    ${prefix}/ccsp/pam/unique_telemetry_id.sh  \
    ${prefix}/ccsp/pam/calc_random_time_to_reboot_dev.sh  \
    ${prefix}/ccsp/pam/network_response.sh  \
    ${prefix}/ccsp/pam/redirect_url.sh \
    ${prefix}/ccsp/pam/revert_redirect.sh \
    ${prefix}/ccsp/pam/whitelist.sh \
    ${prefix}/ccsp/pam/restart_services.sh \
    ${prefix}/ccsp/pam/moca_status.sh \
    ${prefix}/ccsp/pam/erouter0_ip_sync.sh \
    ${prefix}/ccsp/pam/launch_tr69.sh \
    ${prefix}/ccsp/pam/ScheduleAutoReboot.sh \
    ${prefix}/ccsp/pam/AutoReboot.sh \
    ${prefix}/ccsp/pam/RebootCondition.sh \
    /fss/gw/usr/sbin/ip \
    /fss/gw/usr/ccsp/pam/mapping.txt \
"

FILES_${PN}-dbg = " \
    ${prefix}/ccsp/pam/.debug \
    ${prefix}/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"
#FILES_${PN}-ccsp_append_qemux86 = " \
#    ${prefix}/ccsp/pam/COSAXcalibur.XML \
#"

# Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "CcspPandMSsp"
BREAKPAD_LOGMAPPER_LOGLIST = "PAMlog.txt.0"
