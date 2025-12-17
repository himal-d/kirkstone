FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append_broadband = " file://0024-glibc-2.31-ignore-truncated-dns-response.patch"
SRC_URI_append = " file://0001-glibc-2.31-mips-clone-stack-alignment.patch"
SRC_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'enable_heaptrack','file://size.patch','', d)}"

SRC_URI_append_hybrid = " ${@bb.utils.contains('MACHINE_IMAGE_NAME','AX014AN','','file://CVE-2022-23219_fix.patch',d)} "
SRC_URI_append_client = " file://CVE-2022-23219_fix.patch "
SRC_URI_append_broadband = " file://CVE-2022-23219_fix.patch "

SRC_URI_append_hybrid = " ${@bb.utils.contains('MACHINE_IMAGE_NAME','AX014AN','','file://CVE-2021-38604_fix.patch',d)} "
SRC_URI_append_client = " file://CVE-2021-38604_fix.patch "
SRC_URI_append_broadband = " file://CVE-2021-38604_fix.patch "

SRC_URI_append_hybrid = " ${@bb.utils.contains('DISTRO_FEATURES', 'yocto-3.1.15', '', 'file://CVE-2020-29562_fix.patch \
                                                                                       file://Add_the___sockaddr_un_set_function.patch \
                                                                                       file://CVE-2022-23218_fix.patch', d)} "

SRC_URI_append_client = " file://CVE-2020-29562_fix.patch \
                          file://Add_the___sockaddr_un_set_function.patch \
                          file://CVE-2022-23218_fix.patch \
                        "

SRC_URI_append = " file://CVE-2023-0687_fix.patch"

SRC_URI_append_broadband = " file://CVE-2020-29562_fix.patch \
                             file://Add_the___sockaddr_un_set_function.patch \
                             file://CVE-2022-23218_fix.patch \
                             file://CVE-2020-1752_fix.patch "

SRC_URI_remove_puma7 = " file://Add_the___sockaddr_un_set_function.patch "

SRC_URI_remove_class-nativesdk = " file://Add_the___sockaddr_un_set_function.patch "

SRC_URI_append_broadband = " file://CVE-2023-4813_fix.patch "

SRC_URI += " ${@bb.utils.contains('MACHINE_IMAGE_NAME','AX014AN','','file://CVE-2020-27618_fix.patch',d)} "

SRC_URI += " ${@bb.utils.contains('MACHINE_IMAGE_NAME','AX014AN','','file://CVE-2021-33574_fix.patch',d)} "

