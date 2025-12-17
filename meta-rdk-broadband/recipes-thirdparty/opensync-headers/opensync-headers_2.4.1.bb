SUMMARY = "OpenSync schema headers"
LICENSE = "BSD-3-Clause"
#LIC_FILES_CHKSUM = "file://LICENSE;md5=df3f42ef5870da613e959ac4ecaa1cb8"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

inherit python3native
OS_CORE_VERSION="${@bb.utils.contains('DISTRO_FEATURES','Opensync_4.4.0','4.4.0','2.4.2',d)}"

OS_CORE_GIT_2.4.1="${RDK_COMPONENTS_ROOT_GIT}/generic/opensync-core/${OS_CORE_VERSION}/generic;protocol=${RDK_GIT_PROTOCOL};name=opensync-headers;branch=${RDK_GIT_BRANCH};destsuffix=git/os-headers"
OS_CORE_GIT_4.4.0="${RDK_COMPONENTS_ROOT_GIT}/generic/opensync-core/generic;protocol=${RDK_GIT_PROTOCOL};name=opensync-headers;branch=osync_4.4.0;destsuffix=git/os-headers"
SRC_URI += " ${@bb.utils.contains('DISTRO_FEATURES','Opensync_4.4.0', '${OS_CORE_GIT_4.4.0}', '${OS_CORE_GIT_2.4.1}', d)}"

PV = "${RDK_RELEASE}+git${SRCPV}"
S = "${WORKDIR}/git/os-headers"

SRCREV_FORMAT = "opensync-headers"
SRCREV_opensync-headers = "${AUTOREV}"

do_compile[noexec] = "1"
do_populate_lic[noexec] = "1"

do_configure() {
  ${S}/src/lib/schema/schema.py ${S}/interfaces/opensync.ovsschema > ${STAGING_INCDIR}/schema_gen.h
}

do_install () {
  install -d ${D}/usr/include/opensync_headers
  install -m 644 ${STAGING_INCDIR}/schema_gen.h ${D}/usr/include/opensync_headers
}
