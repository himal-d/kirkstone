FILESEXTRAPATHS_prepend := "${THISDIR}/${BPN}:"
SRC_URI += " file://openssl-c_rehash.sh \
           "

do_install_append () {
        # Install a custom version of c_rehash that can handle sysroots properly.
        # This version is used for example when installing ca-certificates during
        # image creation.
        install -Dm 0755 ${WORKDIR}/openssl-c_rehash.sh ${D}${bindir}/c_rehash
        sed -i -e 's,/etc/openssl,${sysconfdir}/ssl,g' ${D}${bindir}/c_rehash
}
FILES_${PN} =+ " ${bindir}/c_rehash"

SRC_URI_append = " file://CVE-2022-4304_1.1.1l_fix.patch \
                   file://CVE-2023-0464_1.1.1l_fix.patch \
                   file://CVE-2023-0465_1.1.1l_fix.patch \
                   file://CVE-2023-0466_1.1.1l_fix.patch \
                   file://CVE-2024-0727_openssl_1.1.1l_fix.patch \
                 "

SRC_URI_append_broadband = " file://CVE-2023-2650_1.1.1l_fix.patch \
                             file://CVE-2023-3817_1.1.1l_fix.patch \
                             file://CVE-2023-4807_1.1.1l_fix.patch \
                           "
