FILESEXTRAPATHS_prepend := "${THISDIR}/${BP}:"
CACHED_CONFIGUREVARS = "ac_cv_lib_crypto_EVP_md5=yes ac_cv_lib_crypto_AES_cfb128_encrypt=no"
CACHED_CONFIGUREVARS_append = " ac_cv_file__etc_printcap=no"
RDEPENDS_${PN}_append = "${@bb.utils.contains('DISTRO_FEATURES', 'ssl-1.1.1', ' openssl', '', d)}"

SRC_URI += "file://rdk_enhancement.patch"

SRC_URI_append = " file://systemd-support.patch \
                   file://sd-deamon_h.patch \
                   file://agent_registry.patch \
                 "

SRC_URI_append_broadband = " \
            file://rdkb_snmp.patch \
"

SRC_URI_append_dunfell = " file://CVE-2022-44792_fix.patch \
                         "

SRC_URI_append_kirkstone = " file://CVE-2022-44792_net-snmp_5.9.1_fix.patch \
                             file://CVE-2022-24805_5.9.1_fix.patch \
                           "
