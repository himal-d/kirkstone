SUMMARY = "parodus2ccsp client library"
SECTION = "libs"
DESCRIPTION = "C client library for parodus2ccsp"
HOMEPAGE = "https://github.com/Comcast/parodus2ccsp"

DEPENDS = "cjson msgpack-c rdk-logger dbus ccsp-common-library trower-base64 cimplog wdmp-c nanomsg wrp-c libparodus breakpad breakpad-wrapper utopia libunpriv rbus"
DEPENDS_append = "${@bb.utils.contains("DISTRO_FEATURES", "webconfig", " curl webcfg ", " ", d)}"
DEPENDS_append = "${@bb.utils.contains("DISTRO_FEATURES", "webconfig_phase1", " curl ", " ", d)}"
RDEPENDS_${PN} = "cjson msgpack-c rdk-logger trower-base64 cimplog wdmp-c nanomsg wrp-c libparodus utopia bash"
RDEPENDS_${PN}_append = "${@bb.utils.contains("DISTRO_FEATURES", "webconfig", " curl webcfg ", " ", d)}"
RDEPENDS_${PN}_append = "${@bb.utils.contains("DISTRO_FEATURES", "webconfig_phase1", " curl ", " ", d)}"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=e3fc50a88d0a364313df4b21ef20c29e"

SRCREV = "${@bb.utils.contains("DISTRO_FEATURES", "webconfig_phase1", "d26d16eb4a85348404259178a48bfcdc49830463", "4a67801a8c35b68c41c2e3b229ccd77a2b130a40" , d)}"

do_configure_prepend () {
    (${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/source/arch/intel_usg/boards/rdkb_atom/config/comcast/WebpaAgent.xml ${S}/source/broadband/dm_pack_datamodel.c)
}

BRANCH = "${@bb.utils.contains("DISTRO_FEATURES", "webconfig_phase1", "webconfig_phase1", "master", d)}"
SRC_URI = "\
    git://github.com/xmidt-org/parodus2ccsp.git;branch=${BRANCH};protocol=https  \
    file://WebPA_drop_root.patch \
    file://WebPA_getValues.patch \
    "
PV = "git+${SRCPV}"
S = "${WORKDIR}/git"
require ccsp_common.inc

# generating minidumps symbols
inherit breakpad-wrapper ${@bb.utils.contains("DISTRO_FEATURES", "kirkstone", "python3native", "pythonnative", d)} breakpad-logmapper
BREAKPAD_BIN_append = " webpa"

LDFLAGS += "-lpthread -lcjson -lmsgpackc -ltrower-base64 -lnanomsg -lcimplog -lwdmp-c -lwrp-c -llibparodus -lm -luuid -lstdc++ -lbreakpadwrapper -lsysevent -lutapi -lutctx -lsyscfg -lprivilege -lrbus -lrtMessage"
LDFLAGS_append = "${@bb.utils.contains("DISTRO_FEATURES", "webconfig", " -lcurl -lwebcfg ", " ", d)}"
LDFLAGS_append = "${@bb.utils.contains("DISTRO_FEATURES", "webconfig_phase1", " -lcurl ", " ", d)}"

ASNEEDED = ""
CFLAGS_append = " \
	-D_YOCTO_ \
	-DPLATFORM_RDKB \
	-DRDKB_BUILD \
	-DBUILD_YOCTO \
	-I${STAGING_INCDIR}/ccsp \
	-I${STAGING_INCDIR}/wdmp-c \
	-I${STAGING_INCDIR}/libparodus \
	-I${STAGING_INCDIR}/dbus-1.0 \
	-I${STAGING_LIBDIR}/dbus-1.0/include \
	-I${STAGING_INCDIR}/rbus \
	-I${STAGING_INCDIR}/rtmessage \
	-I${STAGING_INCDIR}/cimplog \
        -I${STAGING_INCDIR}/trower-base64 \
	"

CFLAGS_append = "${@bb.utils.contains("DISTRO_FEATURES", "webconfig", "-I${STAGING_INCDIR}/webcfg ", " ", d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'webconfig_bin', '-DWEBCONFIG_BIN_SUPPORT', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', '-DFEATURE_SUPPORT_ONEWIFI', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'Support_6G_Radio', '-DFEATURE_SUPPORT_6G_RADIO', '', d)}"

CFLAGS_remove = " ${@bb.utils.contains('DISTRO_FEATURES', 'webconfig_bin', ' -DFEATURE_SUPPORT_WEBCONFIG ', '', d)}"

inherit pkgconfig cmake
EXTRA_OECMAKE = "-DBUILD_TESTING=OFF -DBUILD_YOCTO=true"

EXTRA_OECMAKE += " ${@bb.utils.contains('DISTRO_FEATURES', 'webconfig', ' -DFEATURE_SUPPORT_WEBCONFIG=true ', '', d)}"
EXTRA_OECMAKE += " ${@bb.utils.contains('DISTRO_FEATURES', 'webconfig_phase1', ' -DFEATURE_SUPPORT_WEBCONFIG=true ', '', d)}"

EXTRA_OECONF_append  = " --with-ccsp-platform=bcm --with-ccsp-arch=arm "

SRC_URI_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'webconfig', 'file://Web_config_XML.patch', '', d)}"
SRC_URI_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'webconfig_phase1', 'file://Web_config_Phase1_XML.patch', '', d)}"
SRC_URI_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'webconfig_bin', 'file://Webpa_Connected_Client_Notify_XML.patch', '', d)}"
SRC_URI_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'webconfig', 'file://webconfig_metadata.json', ' ', d)}"
SRC_URI_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'webconfig', 'file://metadata_parser.py ', ' ', d)}"

# generating minidumps
PACKAGECONFIG_append = " breakpad"
do_install_append() {
    install -d ${D}/usr/ccsp/webpa

    install -d ${D}/etc

    if ${@bb.utils.contains("DISTRO_FEATURES", "webconfig", "true", "false", d)}
    then
	if ${@bb.utils.contains("DISTRO_FEATURES", "gateway_manager", "false", "true", d)}
	then
		sed -z 's/"name": "gwfailover",\n[[:blank:]]*"bitposition": 1,\n[[:blank:]]*"support": true,/"name": "gwfailover",\n"bitposition": 1,\n"support": false,/g' ${WORKDIR}/webconfig_metadata.json > ${WORKDIR}/out.txt
		mv ${WORKDIR}/out.txt ${WORKDIR}/webconfig_metadata.json
	fi
        touch ${D}/etc/WEBCONFIG_ENABLE
        (${PYTHON} ${WORKDIR}/metadata_parser.py ${WORKDIR}/webconfig_metadata.json ${D}/etc/webconfig.properties ${MACHINE})
    fi
}

FILES_${PN} += " \
    ${exec_prefix}/ccsp/webpa \
    ${bindir}/webpa \
"
# Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "webpa"
BREAKPAD_LOGMAPPER_LOGLIST = "WEBPAlog.txt.0"
