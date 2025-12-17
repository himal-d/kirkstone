SUMMARY = "TELCO VOICE Manager component"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

DEPENDS = "ccsp-common-library dbus rdk-logger utopia libparodus wrp-c trower-base64 nanomsg libunpriv avro-c"
require ccsp_common.inc

SRC_URI ="${RDKB_CCSP_ROOT_GIT}/RdkTelcoVoiceManager/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=TelcoVOICEManager"

SRCREV_TelcoVOICEManager = "${AUTOREV}"
SRCREV_FORMAT = "TelcoVOICEManager"

PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

EXTRA_OECONF_append  = " ${@bb.utils.contains('DISTRO_FEATURES','kirkstone','','--with-ccsp-platform=bcm --with-ccsp-arch=arm',d)} "

inherit autotools pkgconfig

export ISRDKB_VOICE_DM_TR104_V2 = "${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_voice_manager_dmltr104_v2','true','false', d)}"

CFLAGS_append = " \
    -I${STAGING_INCDIR} \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -I${STAGING_INCDIR}/utapi \
    -I${STAGING_INCDIR}/utctx \
    -I${STAGING_INCDIR}/ulog \
    -I${STAGING_INCDIR}/syscfg \
    -I${STAGING_INCDIR}/sysevent \
    -I${STAGING_INCDIR}/cjson \
    -I${STAGING_INCDIR}/public/include \
    -I${STAGING_INCDIR}/private/include \
    -I${STAGING_INCDIR}/public/include/linux \
    -I${STAGING_INCDIR}/libparodus \
    "

CFLAGS_append = "${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_voice_manager_dmltr104_v2','-DFEATURE_RDKB_VOICE_DM_TR104_V2=ON','', d)}"
CFLAGS_append  = " ${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', '-DRBUS_BUILD_FLAG_ENABLE', '', d)}"
CFLAGS_append += " ${@bb.utils.contains('DISTRO_FEATURES', 'telco_voice_feature_enable_persist', '-DTELCO_VOICE_FEATURE_ENABLE_PERSIST', '', d)}"

DATAMODEL_XML = "config/${@bb.utils.contains('DISTRO_FEATURES','rdkb_voice_manager_dmltr104_v2','RdkTelcoVoiceManager_v2.xml','RdkTelcoVoiceManager_v1.xml',d)}"

do_compile_prepend () {
    (${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/${DATAMODEL_XML} ${S}/source/TelcoVoiceManager/dm_pack_datamodel.c)
}

LDFLAGS_append = " \
    -ldbus-1 \
    -lutctx \
    -lutapi \
    -lm \
    -lcjson \
    -llibparodus \
    -lnanomsg \
    -lwrp-c \
    -lmsgpackc \
    -ltrower-base64 \
    -lm \
    -lcimplog \
    -lpthread \
    -lrt \
    -lsysevent \
    -lcjson \
    -lprivilege \
"

do_install_append () {
    # Config files and scripts
    install -d ${D}${exec_prefix}/rdk/voicemanager
    install -d ${D}${exec_prefix}/ccsp/harvester/
    install -d ${D}${sysconfdir}/rdk/conf
    #JSON schema file
    install -d ${D}/${sysconfdir}/rdk/schemas
    ln -sf ${bindir}/telcovoice_manager ${D}${exec_prefix}/rdk/voicemanager/telcovoice_manager
if [ ${ISRDKB_VOICE_DM_TR104_V2} = "true" ]; then
    install -m 644 ${S}/source/TR-181/integration_src.shared/VoiceDiagnostics_V2.avsc ${D}/usr/ccsp/harvester/VoiceDiagnostics.avsc
    install -m 644 ${S}/config/RdkTelcoVoiceManager_v2.xml ${D}/usr/rdk/voicemanager/RdkTelcoVoiceManager.xml
    install -m 644 ${S}/hal_schema/telcovoice_hal_schema_v2.json ${D}/${sysconfdir}/rdk/schemas/telcovoice_hal_schema.json
    install -m 644 ${S}/config/telcovoice_config_default_v2.json ${D}/usr/rdk/voicemanager/telcovoice_config_default.json
    if ${@bb.utils.contains('DISTRO_FEATURES', 'telco_voice_feature_enable_persist', 'true', 'false', d)}; then
        sed -i '/VOICESERVICE1/a \\t\t"X_RDK_Enable\": \"0\",' ${D}/usr/rdk/voicemanager/telcovoice_config_default.json
    fi

else
    install -m 644 ${S}/source/TR-181/integration_src.shared/VoiceDiagnostics.avsc ${D}/usr/ccsp/harvester/
    install -m 644 ${S}/config/RdkTelcoVoiceManager_v1.xml ${D}/usr/rdk/voicemanager/RdkTelcoVoiceManager.xml
    install -m 644 ${S}/hal_schema/telcovoice_hal_schema_v1.json ${D}/${sysconfdir}/rdk/schemas/telcovoice_hal_schema.json
    install -m 644 ${S}/config/telcovoice_config_default.json ${D}/usr/rdk/voicemanager/telcovoice_config_default.json
    if ${@bb.utils.contains('DISTRO_FEATURES', 'telco_voice_feature_enable_persist', 'true', 'false', d)}; then
        sed -i '/VoiceServiceIndex/a \\t\t"X_RDK_Enable\": \"0\",' ${D}/usr/rdk/voicemanager/telcovoice_config_default.json
    fi
fi
    install -m 644 ${S}/config/telcovoice_manager_conf.json ${D}${sysconfdir}/rdk/conf/
}


FILES_${PN} = " \
   ${exec_prefix}/rdk/voicemanager/telcovoice_manager \
   ${exec_prefix}/rdk/voicemanager/RdkTelcoVoiceManager.xml \
   ${exec_prefix}/ccsp/harvester/VoiceDiagnostics.avsc \
   ${exec_prefix}/rdk/voicemanager/telcovoice_config_default.json \
   ${sysconfdir}/rdk/conf/telcovoice_manager_conf.json \
   ${sysconfdir}/rdk/schemas/telcovoice_hal_schema.json \
   ${bindir}/* \
"

FILES_${PN}-dbg = " \
    ${exec_prefix}/rdk/voicemanager/.debug \
    /usr/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"
