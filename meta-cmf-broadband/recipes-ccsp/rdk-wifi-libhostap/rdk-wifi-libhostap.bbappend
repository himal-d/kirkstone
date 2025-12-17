SRC_URI_remove += "${RDKB_CCSP_ROOT_GIT}/rdk-wifi-libhostap;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH};name=rdk-wifi-libhostap"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

S = "${WORKDIR}/git"

SRC_URI += "git://w1.fi/hostap.git;protocol=https;branch=main;destsuffix=${S}/source/hostap-2.10"
SRCREV = "9d07b9447e76059a2ddef2a879c57d0934634188"

SRC_URI += "https://w1.fi/releases/hostapd-2.9.tar.gz"
SRC_URI[sha256sum] = "881d7d6a90b2428479288d64233151448f8990ab4958e0ecaca7eeb3c9db2bd7"

do_dir_align() {
    mv ${WORKDIR}/hostapd-2.9 ${S}/source/hostap-2.9
}
addtask dir_align after do_unpack before do_patch

SRC_URI_append = " \
${@bb.utils.contains('DISTRO_FEATURES', 'HOSTAPD_2_10', '\
file://002_RDKB_35187_One_Wifi_Dev_Task.patch \
file://003_RDKB_37345_Fix_compile_error.patch \
file://004_RDKB_45650_TCXB7_5403_Added_more_validation_check_on_OneWifi_code.patch \
file://005_RDKB_40014_Integrate_hostapd_2_10.patch \
file://006_RDKB_45281_Added_Wi-Fi_WPS_event_notify_callback_handling.patch \
file://007_RDKB_45694_Libhostap_changes_to_support_Onewifi_Sharman.patch \
file://008_TCXB7_5608_Observing_onewifi_crash_with_signature_wpa_receive.patch \
file://009-RDKB-44454-Store-assoc-request-in-sta-struct.patch ',\
' ', d)}"
