SUMMARY = "CCSP CcspSnmpPa component"
HOMEPAGE = "http://github.com/belvedere-yocto/CcspSnmpPa"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=2291535ca559c92189f5f6053018b3e2"

DEPENDS = "ccsp-common-library net-snmp openssl utopia"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

require ccsp_common.inc

SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/CcspSnmpPa;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=CcspSnmpPa"

CFLAGS += " -Wall -Werror -Wextra "


SRCREV_CcspSnmpPa = "${AUTOREV}"
SRCREV_FORMAT = "CcspSnmpPa"
PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

inherit autotools breakpad-logmapper
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', '-DRDK_ONEWIFI', '', d)}"

CFLAGS_append = " \
    -I=${includedir}/dbus-1.0 \
    -I=${libdir}/dbus-1.0/include \
    -I=${includedir}/ccsp \
    -I${STAGING_INCDIR}/syscfg \
    "
CFLAGS_append = "${@bb.utils.contains("DISTRO_FEATURES", "snmppa", " -DSNMP_PA_ENABLE ", " ", d)}"

LDFLAGS_append = " \
    -ldbus-1 \
    -lsyscfg \
    "

do_install_append () {
	if ${@bb.utils.contains('DISTRO_FEATURES', 'snmppa', 'true', 'false', d)}; then
		install -d ${D}/etc
		touch ${D}/etc/SNMP_PA_ENABLE
		# Config files and scripts
		install -d ${D}/usr/ccsp/snmp
		install -m 644 ${S}/config/snmpd.conf -t ${D}/usr/ccsp/snmp
		install -m 777 ${S}/scripts/run_snmpd.sh -t ${D}/usr/ccsp/snmp
		install -m 777 ${S}/scripts/run_subagent.sh -t ${D}/usr/ccsp/snmp
		install -m 644 ${S}/Mib2DmMapping/Ccsp*.xml -t ${D}/usr/ccsp/snmp
		install -m 644 ${S}/Mib2DmMapping/XOPS-DEVICE-MGMT-MIB.xml -t ${D}/usr/ccsp/snmp
		install -m 644 ${S}/Mib2DmMapping/SELFHEAL-DEVICE-MIB.xml -t ${D}/usr/ccsp/snmp
		install -m 644 ${S}/Mib2DmMapping/DEVICE-WEBPA-MIB.xml -t ${D}/usr/ccsp/snmp
	fi

}

PACKAGES += "${PN}-ccsp"

FILES_${PN}-ccsp = " \
	${@bb.utils.contains("DISTRO_FEATURES", "snmppa", "/etc/* ", " ", d)} \
	${@bb.utils.contains("DISTRO_FEATURES", "snmppa", "${prefix}/ccsp/snmp/snmpd.conf ", " ", d)} \
	${@bb.utils.contains("DISTRO_FEATURES", "snmppa", "${prefix}/ccsp/snmp/run_snmpd.sh ", " ", d)} \
	${@bb.utils.contains("DISTRO_FEATURES", "snmppa", "${prefix}/ccsp/snmp/run_subagent.sh ", " ", d)} \
	${@bb.utils.contains("DISTRO_FEATURES", "snmppa", "${prefix}/ccsp/snmp/Ccsp*.xml ", " ", d)} \
	${@bb.utils.contains("DISTRO_FEATURES", "snmppa", "${prefix}/ccsp/snmp/SELFHEAL-DEVICE-MIB.xml ", " ", d)} \
	${@bb.utils.contains("DISTRO_FEATURES", "snmppa", "${prefix}/ccsp/snmp/XOPS-DEVICE-MGMT-MIB.xml ", " ", d)} \
	${@bb.utils.contains("DISTRO_FEATURES", "snmppa", "${prefix}/ccsp/snmp/DEVICE-WEBPA-MIB.xml ", " ", d)} \
"

FILES_${PN}-dbg = " \
	${@bb.utils.contains("DISTRO_FEATURES", "snmppa", "${prefix}/ccsp/snmp/.debug ", " ", d)} \
	${@bb.utils.contains("DISTRO_FEATURES", "snmppa", "${prefix}/src/debug ", " ", d)} \
	${@bb.utils.contains("DISTRO_FEATURES", "snmppa", "${bindir}/.debug ", " ", d)} \
	${@bb.utils.contains("DISTRO_FEATURES", "snmppa", "${libdir}/.debug ", " ", d)} \
"
