PARALLEL_MAKE_append = " -l ${@int(os.sysconf(os.sysconf_names['SC_NPROCESSORS_ONLN'])) * 150/100}"

PREFERRED_VERSION_jansson = "2.7"

PREFERRED_VERSION_icu ?= "64.1"
PREFERRED_VERSION_icu-native ?= "64.1"
PREFERRED_VERSION_icu_dunfell ?= "66.1"
PREFERRED_VERSION_icu-native_dunfell ?= "66.1"
PREFERRED_VERSION_icu_kirkstone ?= "70.1"
PREFERRED_VERSION_icu-native_kirkstone ?= "70.1"

PREFERRED_VERSION_curl ?= "7.60.0"
PREFERRED_VERSION_curl-native ?= "7.60.0"
PREFERRED_VERSION_curl_dunfell ?= "7.69.1"
PREFERRED_VERSION_curl-native_dunfell ?= "7.69.1"

PREFERRED_VERSION_openssl = "1.0.2o"
PREFERRED_VERSION_openssl_dunfell = "1.1.1d"

PREFERRED_VERSION_brotli_dunfell = "1.0.7"
PREFERRED_VERSION_brotli-native_dunfell = "1.0.7"

PREFERRED_VERSION_brotli_kirkstone = "1.0.9"
PREFERRED_VERSION_brotli-native_kirkstone = "1.0.9"

PREFERRED_VERSION_libwebsockets_kirkstone = "4.2.2"

PREFERRED_VERSION_libstd-rs_kirkstone = "1.72.0"
PREFERRED_VERSION_cargo_kirkstone = "1.72.0"
PREFERRED_VERSION_cargo-native_kirkstone = "1.72.0"
PREFERRED_VERSION_rust_kirkstone = "1.72.0"
PREFERRED_VERSION_rust-native_kirkstone = "1.72.0"
PREFERRED_VERSION_rust-llvm_kirkstone = "1.72.0"
PREFERRED_VERSION_rust-llvm-native_kirkstone = "1.72.0"
PREFERRED_VERSION_rust-cross-canadian_kirkstone = "1.72.0"
PREFERRED_VERSION_rust-cross-canadian-native_kirkstone = "1.72.0"

PREFERRED_VERSION_glib-networking_kirkstone = "2.72.2"
PREFERRED_VERSION_glib-2.0_kirkstone = "2.72.3"
PREFERRED_VERSION_glib-2.0-native_kirkstone = "2.72.3"

PREFERRED_VERSION_heaptrack = "${@bb.utils.contains('DISTRO_FEATURES', 'enable_heaptrack', '1.5.0', '', d)}"
PREFERRED_VERSION_libunwind =  "${@bb.utils.contains('DISTRO_FEATURES', 'enable_heaptrack', '1.7.0', '', d)}"


# Disabling Dunfell version of breakpad for timebeing due to DELIA-48240. Till issue is fixed morty version of breakpad will be used in dunfell builds.
PREFERRED_VERSION_breakpad_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'breakpadgit', 'git', 'svn', d)}"
PREFERRED_VERSION_breakpad-native_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'breakpadgit', 'git', 'svn', d)}"

BBMASK .= "|.*recipes-ccsp|.*recipes-rdkb|.*webpabroadband"

# Build flags to control default SecAPI engine for netflix component
DISTRO_FEATURES_append = " netflix_cryptanium"

BBMASK .= "|meta-rdk-comcast-video/recipes-extended/mediaframework/emu-podserver_git.bb"
BBMASK .= "|meta-rdk-comcast-video/recipes-extended/halsnmp/halsnmp-emu_git.bb"
BBMASK .= "|.meta-rdk-comcast/recipes-common/nvm-sqlite/nvm-sqlite.bb"

# add rdkfwupgrader.bb to bbmask till such time that it supports video devices.
# BBMASK .= "|.meta-rdk-comcast/recipes-extended/rdkfwupgrader/rdkfwupgrader.bb"

# add webconfig-framework.bb to bbmask till such time that it supports Video devices.
# BBMASK .= "|.meta-rdk/recipes-common/webconfig-framework/webconfig-framework.bb"

DISTRO_FEATURES_append = " playreadycdmi_cryptanium"
DISTRO_FEATURES_append = " widevine_hardware"

DISTRO_FEATURES_append = " cgroup"

DISTRO_FEATURES_remove = "nfs"

DISTRO_FEATURES_append = " xcal_device"

DISTRO_FEATURES_append = " lxy"

# Flags to control cedm builds
DISTRO_FEATURES_remove_rpi = "fkpskdf"
DISTRO_FEATURES_append_rpi = " enable-cpg"
#DISTRO_FEATURES_append_rpi = " use-cpg-source"

DISTRO_FEATURES_append  = " cpg-ecfs"
DISTRO_FEATURES_remove_rpi = "cpg-ecfs"

DISTRO_FEATURES_append  = " bind"
DISTRO_FEATURES_append = " safec"

DISTRO_FEATURES_append = " webconfig_bin"

DISTRO_FEATURES_append = " rdm-versioning"

PREFERRED_VERSION_bluez5_dunfell ?= "5.54"
PREFERRED_VERSION_bluez5_kirkstone ?= "5.65"
DISTRO_FEATURES_append = " logendpoints"
DISTRO_FEATURES_remove_morty = " logendpoints"

DISTRO_FEATURES_append = " tigress"
# Masking recipes for CEDM multicall implementation in RDK-V
BBMASK .= "|.config-files|.config-service|.cpgu-src|.cpgu-pbt|.cpgc-src|.cpgc-pbt"


OPTIMIZE_DEFAULT = "-Os"

PREFERRED_VERSION_lighttpd = "1.4.53"

PREFERRED_VERSION_cairo_daisy ?= "1.12.16"
PREFERRED_VERSION_cairo_dunfell ?= "1.16.0"
PREFERRED_VERSION_cairo_kirkstone ?= "1.16.0"
#Downgrade the cairo version since 1.16.0 is having compatibility issues in Arm devices.
PREFERRED_VERSION_cairo_dunfell_arm = "1.14.6"
#Enable cairo 1.16 just for llama (arm)
PREFERRED_VERSION_cairo_dunfell_llama = "1.16.0"

PREFERRED_VERSION_systemd_dunfell ?= "1:230%"

PREFERRED_VERSION_mosquitto_dunfell = "1.6.%"
PREFERRED_VERSION_mosquitto_kirkstone = "2.0.14"

PREFERRED_VERSION_nodejs_kirkstone = "16.14.2"
PREFERRED_VERSION_nodejs-native_kirkstone = "16.14.2"

VOLATILE_BINDS_append = "/tmp/named.conf.options /etc/bind/named.conf.options\n"
VOLATILE_BINDS_append = "/tmp/bind /var/cache/bind\n"
VOLATILE_BINDS_append = "/tmp/stunnel.conf /etc/stunnel.conf\n"

PREFERRED_VERSION_qtwebsockets = "${@bb.utils.contains('DISTRO_FEATURES', 'build_for_sky', bb.utils.contains('DISTRO_FEATURES', 'comcast_qt5', '5.1.1%', '5.12.3', d), '5.1.1%', d)}"

DISTRO_FEATURES_append  = " logbacktrace"

require conf/distro/include/rdk_backtrace_log.inc

DISTRO_FEATURES_append  = " certconfig"
DISTRO_FEATURES_remove_rpi = "certconfig"

DISTRO_FEATURES_append  = " rdkssa"
#RDKPI-429
DISTRO_FEATURES_remove_rpi = "rdkssa"

#State Red for RDK-V
DISTRO_FEATURES_append  = " redrecovery"
DISTRO_FEATURES_remove_rpi = " redrecovery"

DISTRO_FEATURES_NATIVE_append = " bpd_symbol_compression"
DISTRO_FEATURES_NATIVE_remove_daisy = " bpd_symbol_compression"

BBMASK .= "${@bb.utils.contains('DISTRO_FEATURES', 'ssl-1.1.1', '|.meta-rdk-ext/recipes-support/stunnel/stunnel_5.56.bbappend|.meta-rdk-video/recipes-support/curl/curl_7.69%.bbappend', '', d)}"
BBMASK .= "${@bb.utils.contains('DISTRO_FEATURES', 'ssl-1.1.1', '|.meta-rdk-ext/recipes-connectivity/openssl/openssl-1.0.2o_1.0.2o.bb', '', d)}"

inherit ${@bb.utils.contains('DISTRO_FEATURES', 'sbom', 'create-spdx', '', d)}


# Guarding RDK-40652 with DISTRO
DISTRO_FEATURES_append_dunfell = " systemd-journal-cache"
#remove following line while upgrading to systemd to 250
DISTRO_FEATURES_append_kirkstone = " systemd-journal-cache"

#Masking the below recipes because in kirkstone build recipes pulling older version due to layer priority
BBMASK .= "${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '|.meta-rdk-ext/recipes-support/fcgi/fcgi_2.4.0.bb', '', d)}"
BBMASK .= "${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '|.meta-rdk-ext/recipes-devtools/jsonrpc/jsonrpc_0.7.0.bb', '', d)}"
BBMASK .= "${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '|.meta-rdk-ext/recipes-devtools/jsoncpp/jsoncpp_0.6.0-rc2.bb', '', d)}"
BBMASK .= "${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '|.meta-rdk-ext/recipes-common/spawn-fcgi/spawn-fcgi_1.6.3.bb', '', d)}"
BBMASK .= "${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '|.meta-rdk-ext/recipes-support/libev/libev_4.24.bb', '', d)}"
BBMASK .= "${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '|.meta-rdk-ext/recipes-support/libtinyxml2/libtinyxml2_git.bb', '', d)}"
BBMASK .= "${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', '|.meta-rdk-ext/recipes-extended/procps/procps_3.3.12.bb', '', d)}"

#removed the Thunder R4.2 and Enabled the R4.4.1
DISTRO_FEATURES_remove = " wpe_r4"
DISTRO_FEATURES_append = " wpe_r4_4"

PREFERRED_VERSION_wpeframework = "${@bb.utils.contains('DISTRO_FEATURES', 'wpe_r4_4', '4.4%' , bb.utils.contains('DISTRO_FEATURES', 'wpe_r4', '4.2%', '2.1%', d), d)}"
PREFERRED_VERSION_wpeframework-clientlibraries = "${@bb.utils.contains('DISTRO_FEATURES', 'wpe_r4_4', '4.4%' , bb.utils.contains('DISTRO_FEATURES', 'wpe_r4', '4.2%', '2.1%', d), d)}"
PREFERRED_VERSION_wpeframework-interfaces = "${@bb.utils.contains('DISTRO_FEATURES', 'wpe_r4_4', '4.4%' , bb.utils.contains('DISTRO_FEATURES', 'wpe_r4', '4.2%', '2.1%', d), d)}"
PREFERRED_VERSION_wpeframework-tools-native = "${@bb.utils.contains('DISTRO_FEATURES', 'wpe_r4_4', '4.4%' , bb.utils.contains('DISTRO_FEATURES', 'wpe_r4', '4.2%', '2.1%', d), d)}"

# For Apparmor
DISTRO_FEATURES_append = " apparmor"

PREFERRED_VERSION_collectd ?= "5.12.0"

PREFERRED_VERSION_dnsmasq_kirkstone = "2.86"
