SUMMARY = "DPP HAL for RDK CCSP components"
HOMEPAGE = "http://github.com/belvedere-yocto/hal"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://../LICENSE;md5=5d50b1d1fb741ca457897f9e370bc747"

PROVIDES = "rdk-wifi-hal"
RPROVIDES_${PN} = "rdk-wifi-hal"

DEPENDS += " openssl halinterface rdk-wifi-util cjson libpcap pkgconfig-native hal-platform mountutils"
DEPENDS += " ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', ' rdk-wifi-libhostap libnl ', '', d)} "

SRC_URI = "${RDKB_CCSP_ROOT_GIT}/hal/rdk-wifi-hal;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=rdk-wifi-hal"

ONEWIFI_CFLAGS = " -I${PKG_CONFIG_SYSROOT_DIR}/usr/include/rdk-wifi-libhostap/src \
                  -I${PKG_CONFIG_SYSROOT_DIR}/usr/include/libnl3 \
                  -I${PKG_CONFIG_SYSROOT_DIR}/usr/include/ \
                "

CFLAGS_prepend += " ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', '${ONEWIFI_CFLAGS}', '', d)}"

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'HOSTAPD_2_10', '-DHOSTAPD_2_10', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'HOSTAPD_2_10', '-DCONFIG_WEP', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'onewifi_integration', '-DNEWPLATFORM_PORT', '', d)}"

LDFLAGS_append = " -lhal_platform "

SRCREV_rdk-wifi-hal = "${AUTOREV}"
SRCREV_FORMAT = "rdk-wifi-hal"

EXTRA_OECONF += " ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', 'ONE_WIFIBUILD=true', '', d)}"
EXTRA_OECONF += " ${@bb.utils.contains('DISTRO_FEATURES', 'hal-ipc', 'HAL_IPC=true', '', d)}"

PV = "${RDK_RELEASE}+git${SRCPV}"
S = "${WORKDIR}/git/src"

CFLAGS_append = " -I=${includedir}/ccsp "
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'passpoint', '-DFEATURE_SUPPORT_PASSPOINT', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'hostapauthenticator', '-DFEATURE_HOSTAP_AUTHENTICATOR', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'hal-ipc', '-DHAL_IPC -DHAL_IPC_SERVER', '', d)}"
CFLAGS_append_kirkstone = " -Wno-deprecated-declarations "

###########################LEGACY#####################
#This should be removed after you implement the propagation of additional definitions via pkg-config
#for the ALL transitive targets for the ALL platform
ONEWIFI_CONFIG_FLAGS = " \
    -DCONFIG_LIBNL32 \
    -DCONFIG_DRIVER_NL80211 \
    -DFEATURE_SUPPORT_RADIUSGREYLIST \
    -DCONFIG_IAPP \
    -DCONFIG_RSN_PREAUTH \
    -DCONFIG_IEEE80211W \
    -DCONFIG_DRIVER_HOSTAP \
    -DCONFIG_DRIVER_NL80211 \
    -DCONFIG_WMM \
    -DCONFIG_EAP \
    -DCONFIG_ERP \
    -DCONFIG_EAP_MD5 \
    -DCONFIG_EAP_TLS \
    -DCONFIG_EAP_MSCHAPV2 \
    -DCONFIG_EAP_PEAP \
    -DCONFIG_EAP_GTC \
    -DCONFIG_EAP_TTLS \
    -DCONFIG_HS20 \
    -DCONFIG_INTERWORKING \
    -DNEED_AP_MLME \
    -DCONFIG_IEEE80211R_AP \
    -DCONFIG_ETH_P_OUI \
    -DCONFIG_IEEE80211R \
    -DCONFIG_SAE \
    -DCONFIG_SUITE \
    -DCONFIG_SUITEB \
    -DCONFIG_SUITEB192 \
    -DCONFIG_WPS \
    -DLINUX_PORT \
    -DRDK_PORT \
    -DEAP_SERVER_IDENTITY \
    -DEAP_SERVER_TLS \
    -DEAP_SERVER_PEAP \
    -DEAP_SERVER_TTLS \
    -DEAP_SERVER_MD5 \
    -DEAP_SERVER_MSCHAPV2 \
    -DEAP_SERVER_GTC \
    -DEAP_SERVER_PSK \
    -DEAP_SERVER_PAX \
    -DEAP_SERVER_SAKE \
    -DEAP_SERVER_GPSK \
    -DEAP_SERVER_GPSK_SHA256 \
    -DEAP_SERVER_PWD \
    -DEAP_SERVER_TNC \
    -DEAP_SERVER_IKEV2 \
    -DEAP_SERVER_WSC \
    -DEAP_SERVER_TEAP \
    -DEAP_SERVER_FAST \
    -DEAP_SERVER_AKA_PRIME \
    -DEAP_SERVER_AKA \
    -DEAP_SERVER_SIM \
    -DEAP_SERVER_TLV \
    -DEAP_SERVER_UNAUTH_TLS \
    -DIEEE8021X_EAPOL \
    -DEAP_SERVER \
    -DCONFIG_INTERNAL_LIBTOMMATH \
    -DCONFIG_CRYPTO_INTERNAL \
    -DCONFIG_TLSV11 \
    -DCONFIG_TLSV12 \
    -DCONFIG_ECC \
    -DCONFIG_DEBUG_FILE \
    -DCONFIG_DEBUG_LINUX_TRACING \
    -DHOSTAPD \
    -DWIFI_HAL_VERSION_3 \
    -DRDK_ONEWIFI \
    -DCONFIG_IEEE80211AX \
    -DCONFIG_ACS \
    -DCONFIG_IPV6 \
"
###########################LEGACY#####################

#!FIXME!
#Ensure proper propagation of CFLAGS and LIBS through the build system.
#configure.ac:
#PKG_CHECK_MODULES([LIBHOSTAP], [libhostap >= 2.9])
#
#Makefile.am:
#target_name_CFLAGS += ${LIBHOSTAP_CFLAGS}
#target_name_LDFLAGS += ${LIBHOSTAP_LIBS}
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', ' `pkg-config --exists libhostap && pkg-config --cflags libhostap`', '', d)}"

CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', '${ONEWIFI_CONFIG_FLAGS}', '', d)}"

inherit autotools

