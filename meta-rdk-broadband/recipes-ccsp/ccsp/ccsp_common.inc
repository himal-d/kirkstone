SUMMARY = "common inc for ccsp modules."

DEPENDS += "rdk-logger ccsp-common-library-native"
CFLAGS += "-DFEATURE_SUPPORT_RDKLOG"
LDFLAGS += "-lrdkloggers"

inherit coverity pkgconfig

CFLAGS_append += " -D_COSA_HAL_ -U_COSA_SIM_ -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-strict-aliasing \ 
           -DCONFIG_SYSTEM_MOCA -D_ANSC_LINUX -D_ANSC_USER -D_ANSC_LITTLE_ENDIAN_ -D_CCSP_CWMP_TCP_CONNREQ_HANDLER \ 
           -D_DSLH_STUN_ -D_NO_PKI_KB5_SUPPORT -D_BBHM_SSE_FILE_IO -D_ANSC_USE_OPENSSL_ -DENABLE_SA_KEY \ 
           -D_ANSC_AES_USED_ -D_COSA_INTEL_USG_ARM_ -D_COSA_FOR_COMCAST_ -D_NO_EXECINFO_H_ -DFEATURE_SUPPORT_SYSLOG \ 
           -DBUILD_WEB -D_NO_ANSC_ZLIB_ -D_DEBUG -U_ANSC_IPV6_COMPATIBLE_ -DINCLUDE_BREAKPAD -DUSE_NOTIFY_COMPONENT -DNTPD_ENABLE \
	   -DUTC_ENABLE -DXDNS_ENABLE -DMOCA_HOME_ISOLATION -DCCSP_SUPPORT_ENABLED \
	   "


CFLAGS_append_qemux86 += "-D_COSA_SIM_"

include recipes-ccsp/ccsp/ccsp_soc.inc
include recipes-ccsp/ccsp/ccsp_oem.inc

# Define _COSA_FOR_BCI_ for BCI builds
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'bci', '-D_COSA_FOR_BCI_', '', d)}"

# Add flags to support mesh wifi if the feature is available.
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'meshwifi', '-DFEATURE_SUPPORT_MESH', '', d)}"

# Add flags to support webconfig if the feature is available.
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'webconfig', '-DFEATURE_SUPPORT_WEBCONFIG', '', d)}"
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'webconfig_bin', '-DFEATURE_SUPPORT_WEBCONFIG', '', d)}"

# Add flags to support Interworking and passpoint if the feature is available.
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'interworking', '-DFEATURE_SUPPORT_INTERWORKING', '', d)}"
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'passpoint', '-DFEATURE_SUPPORT_PASSPOINT', '', d)}"

# Add flags to support pausing wifistats while speedtest running if the feature is available.
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'wifiStatsDisable', '-DWIFI_STATS_DISABLE_SPEEDTEST_RUNNING', '', d)}"

#Add flags to support RadiusGreyList  if the feature is available.
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'RadiusGreyList', '-DFEATURE_SUPPORT_RADIUSGREYLIST', '', d)}"

#Add flags to support ACL_SELFHEAL  if the feature is available.
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'ACL_SELFHEAL', '-DFEATURE_SUPPORT_ACL_SELFHEAL', '', d)}"

# Add flags to support DFS if the feature is available.
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'dfs', '-DCONFIG_DFS', '', d)}"

# Add flags to support CSI if the feature is available.
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'csi', '-DFEATURE_CSI', '', d)}"

CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'bci', '', '-DFEATURE_SUPPORT_ONBOARD_LOGGING',d)}"

# To have a common macro for reference platform
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'referencepltfm', '-D_RDK_REF_PLATFORM_', '', d)}"

# Add flags to support DSLite Feature
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'dslite', '-DDSLITE_FEATURE_SUPPORT', '', d)}"

# Add flags to support the DDNS standard based on  Broadband forum - RDKBDEV-73
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'ddns_broadband', '-DDDNS_BROADBANDFORUM', '', d)}"

# Add flags to support the Device Gateway association using Manageable Device feature - RDKBDEV-83
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'device_gateway_association', '-DDEVICE_GATEWAY_ASSOCIATION_FEATURE', '', d)}"

# Adding flag for wan_manager
CFLAGS_append  += " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', ' -DFEATURE_RDKB_WAN_MANAGER', '', d)}"

# Add flags to support FwupgradeManager
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'fwupgrade_manager', '-DFEATURE_FWUPGRADE_MANAGER', '', d)}"

# Add flags to support GPON Feature
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_gpon_manager', '-DFEATURE_RDKB_GPON_MANAGER', '', d)}"

# Add flags to support XDSL And PPP Feature
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_xdsl_ppp_manager', '-DFEATURE_RDKB_XDSL_PPP_MANAGER', '', d)}"

#Add flags to support WiFi PSM DB
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'wifi-psm-db', '-DFEATURE_SUPPORT_WIFIDB', '', d)}"

#Add flags to support Off Channel Scan for 5G Radio
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'offchannel_scan_5g', '-DFEATURE_OFF_CHANNEL_SCAN_5G', '', d)}"

#Add flags to support Rx-Tx feature for XB6
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'rxtx_bytes_xb6', '-DFEATURE_RXTX_XB6', '', d)}"

#Add flags to support Off Channel Scan for XB6 5G Radio
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'offchannel_scan_5g_xb6', '-DFEATURE_OFF_CHANNEL_SCAN_5G_XB6', '', d)}"

# Add flag to support HIGH split 
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'highsplit', '-D_CM_HIGHSPLIT_SUPPORTED_', '', d)}"

# Adding flag for cellular manager
CFLAGS_append  += " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_cellular_manager', ' -DFEATURE_RDKB_CELLULAR_MANAGER', '', d)}"

# Adding flag for inter-device manager
CFLAGS_append  += " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_inter_device_manager', '-DFEATURE_RDKB_INTER_DEVICE_MANAGER', '', d)}"

# Add flags to support MAP-T NAT46 Feature
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'nat46', '-DFEATURE_SUPPORT_MAPT_NAT46', '', d)}"

# Adding flag for wan failover
CFLAGS_append  += " ${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', ' -DWAN_FAILOVER_SUPPORTED -DRBUS_BUILD_FLAG_ENABLE', '', d)}"

# Adding flag for EasyMesh Controller
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'easymesh-controller', '-DFEATURE_SUPPORT_EASYMESH_CONTROLLER', '', d)}"

# Adding flag for Rbus Build Flag
CFLAGS_append  += " ${@bb.utils.contains('DISTRO_FEATURES', 'RbusBuildFlagEnable', ' -DRBUS_BUILD_FLAG_ENABLE', '', d)}"

# Adding Flag for support extender + secondary wan.
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_extender', '-DRDKB_EXTENDER_ENABLED', '', d)}"

CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', '-DRDK_ONEWIFI', '', d)}"

# Adding flag for DHCP Manager
CFLAGS_append  += " ${@bb.utils.contains('DISTRO_FEATURES', 'dhcp_manager', '-DFEATURE_RDKB_DHCP_MANAGER', '', d)}"
# Adding flag for gateway fail over
CFLAGS_append  += " ${@bb.utils.contains('DISTRO_FEATURES', 'gateway_manager', ' -DGATEWAY_FAILOVER_SUPPORTED ', '', d)}"

# Adding flag for Configurable wan Interface
CFLAGS_append  += " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_configurable_wan_interface', '-DFEATURE_RDKB_CONFIGURABLE_WAN_INTERFACE', '', d)}"

# Adding flag for vendor_class_id
CFLAGS_append  += " ${@bb.utils.contains('DISTRO_FEATURES', 'vendor_class_id_feature', ' -DVENDOR_CLASS_ID ', '', d)}"

# Adding flag for Wan Manager Unification 
CFLAGS_append  += " ${@bb.utils.contains('DISTRO_FEATURES', 'WanManagerUnificationEnable', '-DWAN_MANAGER_UNIFICATION_ENABLED', '', d)}"

# Adding flag for WiFi Manange
CFLAGS_append  += " ${@bb.utils.contains('DISTRO_FEATURES', 'ManagedWiFiSupportEnable', ' -DWIFI_MANAGE_SUPPORTED', '', d)}"

# Adding flag for ovs support enable
CFLAGS_append  += " ${@bb.utils.contains('DISTRO_FEATURES', 'uselinux_bridge', ' -DUSE_LINUX_BRIDGE ', '', d)}"

# Add flags to support the partner default ext RDKBDEV-694
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'partner_default_ext', '-DPARTNER_DEFAULT_EXT', '', d)}"

# Adding flag for SpeedBoostSupport 
CFLAGS_append  += " ${@bb.utils.contains('DISTRO_FEATURES', 'SpeedBoostSupportEnable', ' -DSPEED_BOOST_SUPPORTED', '', d)}"

FILES_${PN} += "${libdir}/*.so"
FILES_SOLIBSDEV = ""
INSANE_SKIP_${PN} += "dev-so"
