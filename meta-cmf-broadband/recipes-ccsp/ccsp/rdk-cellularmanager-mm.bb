SUMMARY = "RDK Cellular Manager MM component"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

DEPENDS = "ccsp-common-library rdk-logger utopia libunpriv halinterface glib-2.0 libqmi webconfig-framework curl trower-base64 msgpack-c libgudev rbus"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

DEPENDS_append += "modemmanager"

SRC_URI ="${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/RdkCellularManager-MM;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=CellularManager-mm"

SRCREV_CellularManager-mm = "${AUTOREV}"
SRCREV_FORMAT = "CellularManager-mm"

PV = "${RDK_RELEASE}+git${SRCPV}"

S = "${WORKDIR}/git"

inherit coverity

require recipes-ccsp/ccsp/ccsp_common.inc

inherit autotools pkgconfig systemd ${@bb.utils.contains("DISTRO_FEATURES", "kirkstone", "python3native", "pythonnative", d)}

CFLAGS_append = " \
    -I${STAGING_INCDIR} \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -I${STAGING_INCDIR}/libsafec \
    -I${STAGING_INCDIR}/glib-2.0 \
    -I${STAGING_LIBDIR}/glib-2.0/include \
    -I${STAGING_INCDIR}/libqmi-glib \
    -I${STAGING_INCDIR}/trower-base64 \
    -I${STAGING_INCDIR}/msgpackc \
    "
LDFLAGS += " -lprivilege"
LDFLAGS_append = " -ldbus-1"
LDFLAGS_remove_morty = " -ldbus-1"
LDFLAGS += " -lgobject-2.0 -lgio-2.0 -lglib-2.0 -lgudev-1.0 -lqmi-glib"

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"
LDFLAGS_append_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec-3.5.1 ', '', d)}"
LDFLAGS_append_kirkstone = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"

CFLAGS += "-I${STAGING_INCDIR}/libmm-glib/"
CFLAGS += "-I${STAGING_INCDIR}/ModemManager/"
CFLAGS += "-DMM_SUPPORT"
#CFLAGS += "-DQMI_SUPPORT"

LDFLAGS += "-lmm-glib"

PACKAGES += "${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', '${PN}-gtest', '', d)}"

SYSTEMD_SERVICE_${PN} = "RdkCellularManager.service"

do_compile_prepend () {
    if ${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', 'true', 'false', d)}; then
    sed -i '2i <?define RBUS_BUILD_FLAG_ENABLE=True?>' ${S}/config/RdkCellularManager.xml
    fi

    if ${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', 'true', 'false', d)}; then
        (${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/config/RdkCellularManager.xml ${S}/source/CellularManager/dm_pack_datamodel.c)
    fi
}

do_install_append () {
    # Config files and scripts
    install -d ${D}${exec_prefix}/rdk/cellularmanager
    ln -sf ${bindir}/cellularmanager ${D}${exec_prefix}/rdk/cellularmanager/cellularmanager
    install -m 644 ${S}/config/RdkCellularManager.xml ${D}${exec_prefix}/rdk/cellularmanager/
    
    #Install systemd unit.
    install -d ${D}${systemd_unitdir}/system
    install -D -m 0644 ${S}/systemd_units/RdkCellularManager.service ${D}${systemd_unitdir}/system/RdkCellularManager.service
}

FILES_${PN} = " \
   ${bindir}/* \
   ${exec_prefix}/rdk/cellularmanager/* \
   ${systemd_unitdir}/system/RdkCellularManager.service \
"

FILES_${PN}-dbg = " \
    ${exec_prefix}/rdk/rdkcellularmanager/.debug \
    /usr/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"

FILES_${PN}-gtest = "\
    ${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', '${bindir}/RdkCellularManager_gtest.bin', '', d)} \
"

DOWNLOAD_APPS="${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', 'gtestapp-RdkCellularManager', '', d)}"
inherit comcast-package-deploy
CUSTOM_PKG_EXTNS="${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', 'gtest', '', d)}"
SKIP_MAIN_PKG="${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', 'yes', 'no', d)}"
DOWNLOAD_ON_DEMAND="${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', 'yes', 'no', d)}"

EXTRA_OECONF_append  = " --with-ccsp-platform=bcm --with-ccsp-arch=arm "
