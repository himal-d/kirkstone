FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " file://ocsp_request_to_CA_Directly_curl_7.69.1.patch \
                   file://CVE-2020-8231.patch \
                   file://CVE-2020-8285.patch \
                   file://CVE-2020-8286.patch \
"
SRC_URI_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'yocto-3.1.15', '', 'file://CVE-2020-8284_fix.patch \
                                                                                file://CVE-2021-22876_fix.patch \
                                                                                file://CVE-2021-22890_fix.patch \
                                                                                file://CVE-2021-22898_fix.patch \
                                                                                file://CVE-2021-22924_fix.patch \
                                                                                file://CVE-2021-22925_fix.patch \
                                                                                file://CVE-2021-22946-pre1_fix.patch \
                                                                                file://CVE-2021-22946_fix.patch \
                                                                                file://CVE-2021-22947_fix.patch', d)} \
                 "
SRC_URI_append = " file://CVE-2022-22576_fix.patch \
                   file://CVE-2022-27782_fix.patch \
                   file://CVE-2022-32206_fix.patch \
                   file://CVE-2022-32208_fix.patch \
                   file://CVE-2022-32221_fix.patch \
                   file://CVE-2022-35252_fix.patch \
                   file://CVE-2022-43552_fix.patch \
                   file://CVE-2023-46218_fix.patch \
                   file://CVE-2023-27534_fix.patch \
                   file://CVE-2023-27538_fix.patch \
                   file://CVE-2023-28320_fix.patch \
                   file://CVE-2023-28319_fix.patch \
                   file://CVE-2022-27776_fix.patch \
                   file://CVE-2022-32207_fix.patch \
                   file://CVE-2023-38545_fix.patch \
                   file://CVE-2023-38546_fix.patch \
                   file://CVE-2023-28322_fix.patch \ 
                 "

CURLGNUTLS = "--without-gnutls --with-ssl"
DEPENDS += " openssl"

# Latest curl recipe 7.50.1 version comes with Yocto 2.2 is changed to use PACKAGECONFIG
PACKAGECONFIG_remove_class-target = "gnutls"
PACKAGECONFIG_append_class-target = " ssl"

# see https://lists.yoctoproject.org/pipermail/poky/2013-December/009435.html
# We should ideally drop ac_cv_sizeof_off_t from site files but until then
EXTRA_OECONF += "${@bb.utils.contains('DISTRO_FEATURES', 'largefile', 'ac_cv_sizeof_off_t=8', '', d)}"

PACKAGECONFIG_append = " ipv6 "
PACKAGECONFIG[ipv6] = "--enable-ipv6,--disable-ipv6,"
