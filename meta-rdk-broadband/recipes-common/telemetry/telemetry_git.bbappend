DEPENDS += " ccsp-common-library webconfig-framework libunpriv dbus mountutils libsyswrapper"

LDFLAGS_append = " \
        -lprivilege \
        -ldbus-1 \
       "

CFLAGS += " -DCCSP_SUPPORT_ENABLED \
            -DENABLE_RDKB_SUPPORT \
            -DFEATURE_SUPPORT_WEBCONFIG \
            -DDROP_ROOT_PRIV \
          "
                   
require recipes-ccsp/ccsp/ccsp_common.inc

do_compile_prepend () {
    (${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/config/TR181-T2-USGv2.XML ${S}/source/t2ssp/dm_pack_datamodel.c)
}

do_install_append () {
    install -d ${D}/usr/ccsp/telemetry
    install -d ${D}${sysconfdir}
    install -m 644 ${S}/config/T2Agent.cfg ${D}/usr/ccsp/telemetry
    install -m 644 ${S}/config/CcspDmLib.cfg ${D}/usr/ccsp/telemetry
    install -m 755 ${S}/source/interChipHelper/scripts/interChipUtils.sh ${D}/lib/rdk/
    install -m 755 ${S}/config/Default_T2_ReportProfile.json ${D}${sysconfdir}/Default_T2_ReportProfile.json
}

FILES_${PN}_append = " \
    ${prefix}/ccsp/telemetry/T2Agent.cfg \
    ${prefix}/ccsp/telemetry/CcspDmLib.cfg \
    ${sysconfdir}/Default_T2_ReportProfile.json \
"

EXTRA_OECONF += " --enable-ccspsupport --enable-libsyswrapper"
EXTRA_OECONF += " --enable-mountutils"
