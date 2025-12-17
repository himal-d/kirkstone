PACKAGECONFIG_remove = "gnutls"
PACKAGECONFIG_append = " openssl"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI += "${@bb.utils.contains('PREFERRED_VERSION_wpa-supplicant', '2.10', '', 'file://openssl_no_md4.patch', d)}"
SRC_URI_append_kirkstone = " file://wpa_supplicant_makefile_bug_fix_2.10.patch"

inherit syslog-ng-config-gen breakpad-logmapper logrotate
SYSLOG-NG_FILTER = "wpa_supplicant"
SYSLOG-NG_SERVICE_wpa_supplicant = "wpa_supplicant.service"
SYSLOG-NG_DESTINATION_wpa_supplicant = "wpa_supplicant.log"
SYSLOG-NG_LOGRATE_wpa_supplicant = "high"

LOGROTATE_NAME="wpa_supplicant"
LOGROTATE_LOGNAME_wpa_supplicant="wpa_supplicant.log"
#HDD_ENABLE
LOGROTATE_SIZE_wpa_supplicant="1572864"
LOGROTATE_ROTATION_wpa_supplicant="3"
#HDD_DISABLE
LOGROTATE_SIZE_MEM_wpa_supplicant="1572864"
LOGROTATE_ROTATION_MEM_wpa_supplicant="3"

do_configure_append () {
   # Add the "-fPIC" option to CFLAGS to allow the Pace WiFi HAL module to link against wpa-supplicant
   echo "CFLAGS += -fPIC" >> wpa_supplicant/.config

   echo "CONFIG_BUILD_WPA_CLIENT_SO=y" >> wpa_supplicant/.config

   if grep -q '\bCONFIG_DEBUG_FILE\b' wpa_supplicant/.config; then
      sed -i -e '/\bCONFIG_DEBUG_FILE\b/s/.*/CONFIG_DEBUG_FILE=y/' wpa_supplicant/.config
   else
      echo "CONFIG_DEBUG_FILE=y" >> wpa_supplicant/.config
   fi

   sed -i -- 's/CONFIG_AP=y/\#CONFIG_AP=y/' wpa_supplicant/.config
   sed -i -- 's/CONFIG_DRIVER_HOSTAP=y/\#CONFIG_DRIVER_HOSTAPAP=y/' wpa_supplicant/.config

   echo "OPENSSL_NO_MD4=y" >> wpa_supplicant/.config
}

do_install_append () {
   install -d ${D}${includedir}
   install -m 0644 ${S}/src/common/wpa_ctrl.h ${D}${includedir}

   install -d ${D}${libdir}
   install -m 0644 ${S}/wpa_supplicant/libwpa_client.so ${D}${libdir}
}

FILES_SOLIBSDEV = ""
FILES_${PN} += "${libdir}/libwpa_client.so"

# Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "wpa_supplicant"
BREAKPAD_LOGMAPPER_LOGLIST = "wpa_supplicant.log"
