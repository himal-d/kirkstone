# Headless disable graphical splash
SPLASH = ""

DISTRO_FEATURES_append_dunfell = " virtualization"

PREFERRED_VERSION_lighttpd = "1.4.53"
PREFERRED_VERSION_libupnp = "1.6.22"
PREFERRED_VERSION_jansson = "2.7"
PREFERRED_VERSION_libnetfilter-conntrack_daisy = "1.0.2"

# Preferred gtest version/provider
PREFERRED_VERSION_googletest = "1.10.0"
PREFERRED_PROVIDER_gtest = "googletest"
PREFERRED_PROVIDER_gmock = "googletest"

DISTRO_FEATURES_append = " bluetooth"
DISTRO_FEATURES_append = " bluez5"
PREFERRED_VERSION_bluez5_dunfell ?= "5.66"
PREFERRED_VERSION_bluez5_kirkstone ?= "5.66"

PREFERRED_VERSION_php ?= "7.2.%"
PREFERRED_VERSION_php-native ?= "7.2.%"
PREFERRED_VERSION_php_dunfell ?= "7.4.%"
PREFERRED_VERSION_php-native_dunfell ?= "7.4.%"

PREFERRED_VERSION_glib-networking_kirkstone = "2.74.0"
PREFERRED_VERSION_glib-2.0_kirkstone = "2.74.6"
PREFERRED_VERSION_glib-2.0-native_kirkstone = "2.74.6"

PREFERRED_VERSION_log4c = "1.2.3"
PREFERRED_VERSION_net-snmp = "5.8"
PREFERRED_VERSION_avro-c = "1.8.1"
PREFERRED_VERSION_avro-c_kirkstone = "1.11.0"

#PREFERRED_VERSION_icu ?= "64.2"
#PREFERRED_VERSION_icu-native ?= "64.2"
PREFERRED_VERSION_icu ?= "64.%"
PREFERRED_VERSION_icu-native ?= "64.%"
PREFERRED_VERSION_icu_dunfell ?= "66.1"
PREFERRED_VERSION_icu-native_dunfell ?= "66.1"

PREFERRED_VERSION_gupnp ?= "1.2.%"
PREFERRED_VERSION_openssl_dunfell = "1.0.2o"
PREFERRED_VERSION_openssl_morty = "1.0.2o"

# Adding PREFERRED_VERSION for smcroute
PREFERRED_VERSION_smcroute ?= "2.0.0"

PREFERRED_PROVIDER_hal-cm ?= "hal-cm-generic"
PREFERRED_PROVIDER_hal-dhcpv4c ?= "hal-dhcpv4c-generic"
PREFERRED_PROVIDER_hal-ethsw ?= "hal-ethsw-generic"
PREFERRED_PROVIDER_hal-moca ?= "hal-moca-generic"
PREFERRED_PROVIDER_hal-mso_mgmt ?= "hal-mso-mgmt-generic"
PREFERRED_PROVIDER_hal-mta ?= "hal-mta-generic"
PREFERRED_PROVIDER_hal-platform ?= "hal-platform-generic"
PREFERRED_PROVIDER_hal-vlan ?= "hal-vlan-generic"
PREFERRED_PROVIDER_hal-wifi ?= "hal-wifi-generic"
PREFERRED_PROVIDER_hal-epon ?= "hal-epon-generic"
PREFERRED_PROVIDER_hal-firewall ?= "hal-firewall-generic"

PREFERRED_VERSION_libmtp = "1.1.5"
PREFERRED_VERSION_mosquitto_dunfell = "1.6.%"
PREFERRED_VERSION_mosquitto_kirkstone = "2.0.14"
PREFERRED_VERSION_gnupg_dunfell = "1.4.7"
DISTRO_FEATURES_append_dunfell = " logendpoints"

DISTRO_FEATURES_append = " tigress"
#Masking cedm multicall implementation in RDK-B
BBMASK .= "|.cpgu-src|.cpgu-pbt|.cpgc-src|.cpgc-pbt"

PREFERRED_VERSION_cjson_kirkstone = "1.7.15"
PREFERRED_PROVIDER_xfhome ?= "zilker"

# Non-touchstone builds of xfhome may build iksemel that is hosted on
# rdkgerrithub.stb.r53.xcal.tv, which is not internet accessible at the time
# of this writing. Prefer iksemel PV 1.4% for touchstone, which does not depend on this host.
# This may be optionally removed once rdkgerrithub.stb.r53.xcal.tv is internet accesssible.
# meta-rdk-ext/recipes-support/iksemel at 1.5 is not compatible with xfhome.
PREFERRED_VERSION_iksemel ?= '${@oe.utils.conditional("PREFERRED_PROVIDER_xfhome", "touchstone", "1.4%", "", d)}'

VOLATILE_BINDS_append = "/usr/ccsp/ccsp_msg.cfg /ccsp_msg.cfg\n"

BBMASK .= "|.meta-rdk/recipes-core/images/rdk-oss-image.bb|meta-rdk/recipes-core/images/rdk-generic-image.bb"
BBMASK .= "|.*recipes-extended/mediaframework|.*recipes-qt"
BBMASK .= "|.meta-rdk-comcast/recipes-support/crypt-utils/*|.meta-rdk-comcast/recipes-extended/whitebox|.meta-rdk/recipes-oem/mfrlib"
BBMASK .= "|.meta-rdk-comcast/recipes-common/sec-pks-client/sec-pks-client.bb"
BBMASK .= "|.meta-rdk-comcast/recipes-common/tdk-cpc"
BBMASK .= "|.meta-rdk/recipes-extended/wifi-hal-headers|.meta-rdk-comcast/recipes-extended/acscerts"
BBMASK .= "|.meta-rdk/recipes-common/nlmonitor"
BBMASK .= "|.meta-rdk-comcast/recipes-common/cgrouputils"
BBMASK .= "|.meta-rdk-ext/recipes-extended/(?!pam)|.meta-rdk-ext/recipes-multimedia|.meta-rdk-ext/recipes-graphics|.meta-rdk-ext/recipes-utils"
BBMASK .= "|.meta-rdk-comcast/recipes-common/nvm-sqlite/nvm-sqlite.bb|.meta-rdk-comcast/recipes-common/rdkversion/rdkversion_1.0.bb"
BBMASK .= "|.meta-rdk-soc-intel-gw/meta-intelce-arm/recipes-gateway/miniupnpd/miniupnpd.bb"
BBMASK .= "|.meta-rdk/recipes-core/packagegroups/packagegroup-rdk-qt5.bb"
VOIP_MASK ?= "|.meta-rdk-broadband/recipes-ccsp/ccsp/ccsp-telcovoip-agent.bb"
BBMASK .= "${VOIP_MASK}"
WAN_MASK ?= "|.meta-rdk-broadband/recipes-ccsp/ccsp/ccsp-wanagent.bb"
BBMASK .= "${WAN_MASK}"
DSL_MASK ?= "|.meta-rdk-broadband/recipes-ccsp/ccsp/ccsp-dslagent.bb|.meta-rdk-broadband/recipes-ccsp/ccsp/ccsp-xtmagent.bb"
BBMASK .= "${DSL_MASK}"
VLAN_MASK ?= "|.meta-rdk-broadband/recipes-ccsp/ccsp/ccsp-vlanagent.bb"
BBMASK .= "${VLAN_MASK}"

FEATURE_WANMANAGER_DSL_MASK ?= "|.meta-rdk-wan/recipes-ccsp/ccsp/rdkxdslmanager.bb"
BBMASK .= "${FEATURE_WANMANAGER_DSL_MASK}"
FEATURE_WANMANAGER_WAN_MASK ?= "|.meta-rdk-wan/recipes-ccsp/ccsp/rdk-wanmanager.bb"
BBMASK .= "${FEATURE_WANMANAGER_WAN_MASK}"
FEATURE_WANMANAGER_VLAN_MASK ?= "|.meta-rdk-wan/recipes-ccsp/ccsp/rdk-vlanmanager.bb"
BBMASK .= "${FEATURE_WANMANAGER_VLAN_MASK}"
FEATURE_WANMANAGER_GPON_MASK ?= "|.meta-rdk-wan/recipes-ccsp/ccsp/rdkgponmanager.bb"
BBMASK .= "${FEATURE_WANMANAGER_GPON_MASK}"
FEATURE_WANMANAGER_PPP_MASK ?= "|.meta-rdk-wan/recipes-ccsp/ccsp/rdk-ppp-manager.bb"
BBMASK .= "${FEATURE_WANMANAGER_PPP_MASK}"
FEATURE_WANMANAGER_FWUPGRADE_MASK ?= "|.meta-rdk-broadband/recipes-ccsp/ccsp/rdk-fwupgrade-manager.bb"
BBMASK .= "${FEATURE_WANMANAGER_FWUPGRADE_MASK}"
FEATURE_WANMANAGER_VOICEMGR_MASK ?= "|.meta-rdk-broadband/recipes-ccsp/ccsp/rdktelcovoicemanager.bb"
BBMASK .= "${FEATURE_WANMANAGER_VOICEMGR_MASK}"
FEATURE_WANMANAGER_IPOE_MASK ?= "|.meta-rdk-wan/recipes-support/ipoe-health-check/ipoe-health-check.bb"
BBMASK .= "${FEATURE_WANMANAGER_IPOE_MASK}"
FEATURE_WANMANAGER_JSONHAL_MASK ?= "|.meta-rdk-broadband/recipes-support/json-hal/json-hal-lib.bb"
BBMASK .= "${FEATURE_WANMANAGER_JSONHAL_MASK}"
FEATURE_RDKB_LED_MANAGER ?= "|.meta-rdk-broadband/recipes-ccsp/ccsp/rdk-ledmanager.bb"
BBMASK .= "${FEATURE_RDKB_LED_MANAGER}"
FEATURE_CELLULAR_MANAGER_MASK ?= "|.meta-rdk-broadband/recipes-ccsp/ccsp/rdk-cellularmanager.bb"
BBMASK .= "${FEATURE_CELLULAR_MANAGER_MASK}"
FEATURE_RDKB_INTER_DEVICE_MANAGER ?= "|.meta-rdk-broadband/recipes-ccsp/ccsp/rdk-interdevicemanager.bb"
BBMASK .= "${FEATURE_RDKB_INTER_DEVICE_MANAGER}"
FEATURE_RDKB_LAN_MANAGER ?= "|.meta-rdk-broadband/recipes-ccsp/ccsp/lanmanager.bb"
BBMASK .= "${FEATURE_RDKB_LAN_MANAGER}"
FEATURE_RDKB_PLATFORM_MANAGER ?= "|.meta-rdk-broadband/recipes-ccsp/ccsp/platformmanager.bb"
BBMASK .= "${FEATURE_RDKB_PLATFORM_MANAGER}"

HUBLINUX_MASK ?= "|.meta-rdk-soc-broadcom-broadband/meta-brcm-broadband/recipes-kernel/linux/bcalinux_4.19.bb"
BBMASK .= "${HUBLINUX_MASK}"

# add rdkversion_1.0.bb is not supported for broadband devices.
BBMASK .= "|./meta-rdk/recipes-common/rdkversion/"

DISTRO_FEATURES_append = " rdm-versioning"
DISTRO_FEATURES_append = " telemetry2_0"
DISTRO_FEATURES_append = " snmppa"

# add new breakpad framework for RDKB
DISTRO_FEATURES_append  = " logbacktrace"
require conf/distro/include/rdkb_backtrace_log.inc

DISTRO_FEATURES_append = " heaptrack"
DISTRO_FEATURES_remove_morty = " heaptrack"
PREFERRED_VERSION_heaptrack_kirkstone = "1.2.%"

DISTRO_FEATURES_remove = "alsa"
DISTRO_FEATURES_remove = "ext2"
DISTRO_FEATURES_remove = "zeroconf"
DISTRO_FEATURES_remove = "nfs"
DISTRO_FEATURES_append = " safec"
#DISTRO_FEATURES_append = " webui_php"
DISTRO_FEATURES_append = " webui_jst"
#DISTRO_FEATURES_append = " gtestapp"
DISTRO_FEATURES_append = " redrecovery"
# For Apparmor
DISTRO_FEATURES_append = " apparmor"
OPTIMIZE_DEFAULT = "-Os"

#Masking the below recipes because in kirkstone build recipes pulling older version due to layer priority
BBMASK .= "${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '|.meta-rdk-ext/recipes-devtools/jsonrpc/jsonrpc_0.7.0.bb', '', d)}"
BBMASK .= "${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '|.meta-rdk-ext/recipes-devtools/jsoncpp/jsoncpp_1.8.4.bb', '', d)}"
BBMASK .= "${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '|.meta-rdk-ext/recipes-devtools/jsoncpp/jsoncpp_0.6.0-rc2.bb', '', d)}"

