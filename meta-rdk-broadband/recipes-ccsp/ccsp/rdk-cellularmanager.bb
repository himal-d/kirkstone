SUMMARY = "RDK Cellular Manager component"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

DEPENDS = "ccsp-common-library rdk-logger utopia libunpriv halinterface glib-2.0 webconfig-framework curl trower-base64 msgpack-c libgudev rbus"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'cellular_libqmi_support', 'libqmi', '', d)}"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

SRC_URI ="${RDKB_CCSP_ROOT_GIT}/RdkCellularManager/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=CellularManager"

SRCREV_CellularManager = "${AUTOREV}"
SRCREV_FORMAT = "CellularManager"

PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

require ccsp_common.inc

inherit autotools pkgconfig systemd ${@bb.utils.contains("DISTRO_FEATURES", "kirkstone", "python3native", "pythonnative", d)} 

CFLAGS_append = " \
    -I${STAGING_INCDIR} \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -I${STAGING_INCDIR}/libsafec \
    -I${STAGING_INCDIR}/glib-2.0 \
    -I${STAGING_LIBDIR}/glib-2.0/include \
    ${@bb.utils.contains('DISTRO_FEATURES', 'cellular_libqmi_support', ' -I${STAGING_INCDIR}/libqmi-glib', '', d)} \
    -I${STAGING_INCDIR}/trower-base64 \
    -I${STAGING_INCDIR}/msgpackc \
    "


LDFLAGS += " -lprivilege"
LDFLAGS_append = " -ldbus-1"
LDFLAGS_remove_morty = " -ldbus-1"
LDFLAGS += " -lgobject-2.0 -lgio-2.0 -lglib-2.0 -lgudev-1.0"
LDFLAGS += " ${@bb.utils.contains('DISTRO_FEATURES', 'cellular_libqmi_support', '-lqmi-glib', '', d)}"

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'cellular_mgr_lite', '-DCELLULAR_MGR_LITE ', '', d)}"
LDFLAGS_append_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec-3.5.1 ', '', d)}"
LDFLAGS_append_kirkstone = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"

do_compile_prepend () {
    if ${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', 'true', 'false', d)}; then
    sed -i '2i <?define RBUS_BUILD_FLAG_ENABLE=True?>' ${S}/config/RdkCellularManager.xml
    fi

    if ${@bb.utils.contains('DISTRO_FEATURES', 'WanManagerUnificationEnable', 'true', 'false', d)}; then
    sed -i '2i <?define WAN_MANAGER_UNIFICATION_ENABLED=True?>' ${S}/config/RdkCellularManager.xml
    fi

    if ${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', 'true', 'false', d)}; then
        (${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/config/RdkCellularManager.xml ${S}/source/CellularManager/dm_pack_datamodel.c)
    fi
}

V_BINARY_FILE = "cellularmanager"
V_SERVICE_FILE = "RdkCellularManager"

V_BINARY_FILE .= "${@bb.utils.contains('DISTRO_FEATURES', 'cellular_mgr_lite', 'lite', '', d)}"
V_SERVICE_FILE .= "${@bb.utils.contains('DISTRO_FEATURES', 'cellular_mgr_lite', 'Lite', '', d)}"

SYSTEMD_SERVICE_${PN} = "${V_SERVICE_FILE}.service"

do_install_append () {
    # Config files and scripts
    install -d ${D}${exec_prefix}/rdk/cellularmanager

    ln -sf ${bindir}/${V_BINARY_FILE} ${D}${exec_prefix}/rdk/cellularmanager/${V_BINARY_FILE}
    install -m 644 ${S}/config/RdkCellularManager.xml ${D}${exec_prefix}/rdk/cellularmanager/
    
    #Install systemd unit.
    install -d ${D}${systemd_unitdir}/system
    install -D -m 0644 ${S}/systemd_units/${V_SERVICE_FILE}.service ${D}${systemd_unitdir}/system/${V_SERVICE_FILE}.service
}

FILES_${PN} = " \
   ${bindir}/* \
   ${exec_prefix}/rdk/cellularmanager/* \
   ${systemd_unitdir}/system/${V_SERVICE_FILE}.service \
"

FILES_${PN}-dbg = " \
    ${exec_prefix}/rdk/rdkcellularmanager/.debug \
    /usr/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"

ENABLE_CELLULAR_MGR_LITE = "--enable-cellularmgrlite=${@bb.utils.contains('DISTRO_FEATURES', 'cellular_mgr_lite', 'yes', 'no', d)}"
EXTRA_OECONF_append  = " ${ENABLE_CELLULAR_MGR_LITE}"
EXTRA_OECONF_append  = " --with-ccsp-platform=bcm --with-ccsp-arch=arm "

ENABLE_CELLULAR_MGR_LTE_USB = "--enable-lteusbsupport=${@bb.utils.contains('DISTRO_FEATURES', 'lte_usb_support', 'yes', 'no', d)}"
EXTRA_OECONF_append  = " ${ENABLE_CELLULAR_MGR_LTE_USB}"
