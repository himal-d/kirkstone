SUMMARY = "RDK-WiFi-LIBHOSTAP for RDK CcspWiFiAgent components"
SUMMARY = "This recipe compiles and installs the Opensource hostapd as a dynamic library for RDK hostap authenticator"
SECTION = "base"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://source/hostap-2.10/README;md5=e3d2f6c2948991e37c1ca4960de84747"

FILESEXTRAPATHS_prepend:="${THISDIR}/files:"
PROVIDES = "rdk-wifi-libhostap"
RPROVIDES_${PN} = "rdk-wifi-libhostap"
DEPENDS += "libnl openssl"

inherit autotools pkgconfig

SRC_URI = "${RDKB_CCSP_ROOT_GIT}/rdk-wifi-libhostap;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH};name=rdk-wifi-libhostap"
SRCREV_rdk-wifi-libhostap = "${AUTOREV}"
SRCREV_FORMAT = "rdk-wifi-libhostap"
def getowe_defined(d):
    if d.getVar('MACHINE_IMAGE_NAME', True) in [ 'CGM4981COM' ]:
        return '-DCONFIG_OWE'
    else:
        return ''

def get_hostapd_pv(d):
    ret_val = '2.9' #HOSTAPD=DEFAULT
    distro_features = d.getVar('DISTRO_FEATURES', True)
    if distro_features:
        val = distro_features.split('HOSTAPD_')
        if len(val) > 1:
            ret_val = val[1].split()[0].replace('_','.')
    return ret_val

HOSTAPD_PV = "${@get_hostapd_pv(d)}"
#true for 2.9 and 2.10
PRIOR_BUILD = "${@'true' if d.getVar('HOSTAPD_PV', True) == '2.9' or d.getVar('HOSTAPD_PV', True) == '2.10' else 'false'}"

EXTRA_OEMAKE_append = " \
    'BUILDDIR=${B}' \
    'PN=rdk-wifi-libhostap' \
    'MACHINE_IMAGE_NAME=${MACHINE_IMAGE_NAME}' \
    ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', 'ONE_WIFI=y', '', d)} \
"
CFLAGS_append = " \
    -fcommon \
"

SRC_URI += " \
    file://.config \
    file://libhostap.mk \
    ${@bb.utils.contains('PRIOR_BUILD', 'false', ' \
        file://${HOSTAPD_PV}/ \
        file://${HOSTAPD_PV}/onewifi_lib.patch \
        file://${HOSTAPD_PV}/RDKB-53254_Telemetry_2.11.patch \
        file://${HOSTAPD_PV}/wps_term_session.patch \
        file://${HOSTAPD_PV}/cmxb7_dfs.patch \
        file://${HOSTAPD_PV}/cohosted_bss_param_211.patch \
        file://${HOSTAPD_PV}/ht_rifs_211.patch \
        file://${HOSTAPD_PV}/rem_dup_beacon_tags_211.patch \
        file://${HOSTAPD_PV}/vht_oper_basic_mcs_set_211.patch \
        file://${HOSTAPD_PV}/tx_pwr_envelope_211.patch \
        file://${HOSTAPD_PV}/pwr_constraint_211.patch \
        file://${HOSTAPD_PV}/supported_op_classes_211.patch \
        file://${HOSTAPD_PV}/he_2ghz_40mghz_bw_211.patch \
        file://${HOSTAPD_PV}/rnr_col_211.patch \
    ','', d)} \
"

###########################PRIOR_BUILD#####################
CFLAGS_prepend += " \
    ${@bb.utils.contains('PRIOR_BUILD', 'true', ' \
        -I${PKG_CONFIG_SYSROOT_DIR}/usr/include/libnl3 \
        -I${PKG_CONFIG_SYSROOT_DIR}/usr/include/ \
    ','', d)} \
"
CFLAGS_append = "${@' \
        -DCONFIG_LIBNL32 \
        -DCONFIG_LIBNL20 \
        -DCONFIG_DRIVER_NL80211 \
        -DCONFIG_HS20 \
        -DCONFIG_INTERWORKING \
        -DCONFIG_ACS \
        -DFEATURE_SUPPORT_RADIUSGREYLIST \
        -DCONFIG_WNM_AP \
        -DCONFIG_IPV6 \
    ' + getowe_defined(d) \
    + bb.utils.contains('DISTRO_FEATURES', 'OneWifi', ' -DRDK_ONEWIFI', '', d) \
    if d.getVar('PRIOR_BUILD', True) == 'true' else ''} \
"
#Lib hostap compilation changes for compiling libhostap.so
#!!This has to be first patch!!
SRC_URI += " ${@bb.utils.contains('DISTRO_FEATURES', 'HOSTAPD_2_10','file://2.10/oneWifiLib.patch file://2.10/greylist.patch file://2.10/broadcom.patch file://2.10/one_wifi_radius_greylist.patch file://2.10/RDKB-48455-hostap-2.10-crash.patch file://2.10/owe_radius_auth_vlan_32.patch file://2.10/RDKB_47882_VLAN_2_10.patch file://2.10/onewifi_cac.patch file://2.10/mbr.patch file://2.10/wpa_auth_vlogger_crash.patch file://2.10/connected_building_avp_2_10.patch file://2.10/enable-wnm-flag-2-10.patch file://2.10/Supported_Rates_Per_Vap_CAC.patch file://2.10/greylist_connectivity_openvap_2.10.patch file://2.10/wps_pin_led.patch file://2.10/wps_indication_deinit.patch file://2.10/RDKB-53254_Telemetry_2.10.patch file://2.10/wps_term_session.patch file://2.10/CMXB7-5998.patch file://2.10/cmxb7_dfs.patch file://2.10/cohosted_bss_param_210.patch file://2.10/ht_rifs_210.patch file://2.10/rem_dup_beacon_tags_210.patch file://2.10/vht_oper_basic_mcs_set_210.patch file://2.10/tx_pwr_envelope_210.patch file://2.10/pwr_constraint_210.patch file://2.10/supported_op_classes_210.patch file://2.10/he_2ghz_40mghz_bw_210.patch file://2.10/rnr_col_210.patch ',\
              'file://2.9/hostapd-lib-build-modify.patch file://2.9/hostapd-logger-module-changes.patch file://2.9/RDKB-48455-hostap-2.9-crash.patch file://2.9/lib-hostap-changes-xb7.diff \
              file://2.9/wps.patch file://2.9/eloop_rfc_switch.patch file://2.9/greylist.patch file://2.9/one_wifi.patch file://2.9/one_wifi_bss_transition.patch file://2.9/one_wifi_radius_greylist.patch file://2.9/owe_radius_auth_vlan_32_2_9.patch file://2.9/RDKB_47882_VLAN_2_9.patch file://2.9/onewifi_cac.patch file://2.9/connected_building_avp_2_9.patch file://2.9/enable-wnm-flag.patch file://2.9/Supported_Rates_Per_Vap_CAC.patch file://2.9/RDKB-52761-change-deauth-reason-code.patch file://2.9/wps_pin_led.patch file://2.9/wps_indication_deinit.patch file://2.9/RDKB-53254_Telemetry_2.9.patch file://2.9/wps_term_session.patch ', d) \
             if d.getVar('PRIOR_BUILD', True) == 'true' else ''}"

#use below format for adding new distro features
#SRC_URI += " ${@bb.utils.contains('DISTRO_FEATURES', 'wifi-emulator', ' file://2.9/no_ack.patch', '', d) if d.getVar('PRIOR_BUILD', True) == 'true' else ''}"
###########################PRIOR_BUILD#####################

S = "${WORKDIR}/git/"

FILES_${PN} = " \
        ${libdir}/libhostap.so* \
"

do_hostapd_patch () {
    if ! ${PRIOR_BUILD}; then
        install -m 0644 ${WORKDIR}/.config ${WORKDIR}/libhostap.mk ${S}/source/hostap-${HOSTAPD_PV}/hostapd/
        echo "include libhostap.mk" >> ${S}/source/hostap-${HOSTAPD_PV}/hostapd/Makefile
    fi
}

addtask hostapd_patch after do_patch before do_configure

do_configure_append () {
    if ! ${PRIOR_BUILD}; then
        oe_runmake -C ${S}/source/hostap-${HOSTAPD_PV}/hostapd clean_libhostap
    fi
}

do_compile () {
    if ${PRIOR_BUILD}; then
        oe_runmake V=1
    else
        oe_runmake -C ${S}/source/hostap-${HOSTAPD_PV}/hostapd libhostap V=1
    fi
}

do_install () {
    if ${PRIOR_BUILD}; then
        autotools_do_install
        install -d ${D}${includedir}/rdk-wifi-libhostap/
        install -d ${D}${includedir}/rdk-wifi-libhostap/src/
        install -d ${D}${includedir}/rdk-wifi-libhostap/src/hostapd/
        cd ${S}/source/hostap-${HOSTAPD_PV}/src && find . -type f -name "*.h" -exec install -D -m 0755 "{}" ${D}${includedir}/rdk-wifi-libhostap/src/"{}" \;
        install -m 0755 ${S}/source/hostap-${HOSTAPD_PV}/hostapd/ctrl_iface.h ${D}${includedir}/rdk-wifi-libhostap/src/hostapd/
        if ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', 'true', 'false', d)}; then
            install -m 0755 ${S}/source/hostap-${HOSTAPD_PV}/hostapd/eap_register.h ${D}${includedir}/rdk-wifi-libhostap/src/hostapd/
        fi
        install -m 0755 ${S}/source/hostap-${HOSTAPD_PV}/hostapd/config_file.h ${D}${includedir}/rdk-wifi-libhostap/src/hostapd/
    else
        oe_runmake -C ${S}/source/hostap-${HOSTAPD_PV}/hostapd 'DESTDIR=${D}' install_libhostap
    fi
}
