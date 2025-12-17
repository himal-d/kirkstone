FILESEXTRAPATHS_prepend:="${THISDIR}/${PN}:"

SRC_URI_append = " file://CVE-2022-4304_openssl_3.0.5_fix.patch \
                   file://CVE-2023-0464_openssl_3.0.5_fix.patch \
                   file://CVE-2023-0465_openssl_3.0.5_fix.patch \
                   file://CVE-2023-0466_openssl_3.0.5_fix.patch \
                   file://CVE-2023-5678_openssl_3.0.5_fix.patch \
                   file://CVE-2023-5363_openssl_3.0.5_fix.patch \
                   file://CVE-2022-3358_openssl_3.0.5_fix.patch \
                   file://CVE-2022-3602_openssl_3.0.5_fix.patch \
                   file://CVE-2022-3786_openssl_3.0.5_fix.patch \
                   file://CVE-2022-3996_openssl_3.0.5_fix.patch \
                   file://CVE-2022-4203_openssl_3.0.5_fix.patch \
                   file://CVE-2023-0216_openssl_3.0.5_fix.patch \
                   file://CVE-2023-0217_openssl_3.0.5_fix.patch \
                   file://CVE-2023-0401_openssl_3.0.5_fix.patch \
                   file://CVE-2024-0727_openssl_3.0.5_fix.patch \
                   file://CVE-2023-6129_openssl_3.0.5_fix.patch \
                   file://CVE-2023-0286_openssl_3.0.5_fix.patch \
                   file://CVE-2023-0215_openssl_3.0.5_fix.patch \
                   file://CVE-2022-4450_openssl_3.0.5_fix.patch \
                   file://CVE-2023-1255_openssl_3.0.5_fix.patch \
                   file://CVE-2023-2650_openssl_3.0.5_fix.patch \
                   file://CVE-2023-2975_openssl_3.0.5_fix.patch \
                   file://CVE-2023-3817_openssl_3.0.5_fix.patch \
                   file://CVE-2023-4807_openssl_3.0.5_fix.patch \
                 "
SRC_URI += " file://openssl-c_rehash.sh \
           "

PTEST_ENABLED = "${@bb.utils.contains('DISTRO_FEATURES', 'benchmark_enable', '1', '0', d)}"

#Disable unapproved cipher algorithms
EXTRA_OECONF += "no-camellia"
EXTRA_OECONF += "no-seed"
EXTRA_OECONF += "no-rc5"
EXTRA_OECONF += "no-md2"
#EXTRA_OECONF += "no-md4"
EXTRA_OECONF += "no-mdc2"
EXTRA_OECONF += "no-ssl2"
EXTRA_OECONF += "no-ssl3"
EXTRA_OECONF += "no-err"
EXTRA_OECONF += "no-hw"
#EXTRA_OECONF += "no-srp"
EXTRA_OECONF += "no-idea"
EXTRA_OECONF += "no-rc4"
EXTRA_OECONF += "no-aria"
EXTRA_OECONF += "no-sm4"
EXTRA_OECONF += "no-sm2"


do_install_append () {
        # Install a custom version of c_rehash that can handle sysroots properly.
        # This version is used for example when installing ca-certificates during
        # image creation.
        install -Dm 0755 ${WORKDIR}/openssl-c_rehash.sh ${D}${bindir}/c_rehash
        sed -i -e 's,/etc/openssl,${sysconfdir}/ssl,g' ${D}${bindir}/c_rehash
}

inherit ptest-package-deploy
FILES_${PN} =+ " ${bindir}/c_rehash"
