
SUMMARY = "Mesh Agent"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=175792518e4ac015ab6696d16c4f607e"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

DEPENDS = "ccsp-common-library webconfig-framework utopia dbus rdk-logger telemetry wrp-c cjson libparodus breakpad-wrapper"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

DEPENDS_append = " trower-base64"
RDEPENDS_${PN}_append = " trower-base64 bash"

LDFLAGS_remove = "-lsafec-3.5"
LDFLAGS_append = " -lsyscfg -lsysevent -lbreakpadwrapper"

LDFLAGS_append_dunfell = " -lsafec-3.5.1"
LDFLAGS_append_kirkstone = " -lsafec"

require recipes-ccsp/ccsp/ccsp_common.inc

SRC_URI = "${CMF_GIT_ROOT}/rdkb/components/opensource/ccsp/MeshAgent;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=mesh-agent"

SRCREV_mesh-agent = "${AUTOREV}"
PV = "${RDK_RELEASE}+git${SRCPV}"

SRC_URI += "\
file://enabling_dhcp_lease_resync.patch;apply=no \
file://meshagent-enable-ovs-default.patch;apply=no \
"

# we need to patch to code for mesh-agent
do_refplatform_meshagent_patches() {
    cd ${S}
    if [ ! -e patch_applied ]; then
        bbnote "Patching enabling_dhcp_lease_resync.patch"
        patch  -p1 < ${WORKDIR}/enabling_dhcp_lease_resync.patch ${S}/source/MeshAgentSsp/cosa_mesh_apis.c

        bbnote "Patching meshagent-enable-ovs-default.patch"
        patch  -p1 < ${WORKDIR}/meshagent-enable-ovs-default.patch ${S}/source/MeshAgentSsp/cosa_mesh_apis.c

        touch patch_applied
    fi
}
addtask refplatform_meshagent_patches after do_unpack before do_configure

do_compile_prepend () {
    (${PYTHON} ${STAGING_BINDIR_NATIVE}/dm_pack_code_gen.py ${S}/config/TR181-MeshAgent.xml ${S}/source/MeshAgentSsp/dm_pack_datamodel.c)
}

CFLAGS_append = " \
    -I${STAGING_INCDIR}/dbus-1.0 \
    -I${STAGING_LIBDIR}/dbus-1.0/include \
    -I${STAGING_INCDIR}/ccsp \
    -I${STAGING_INCDIR}/trower-base64 \
    -I${STAGING_INCDIR}/libsafec \
    -I${STAGING_INCDIR}/cjson \
    -I${STAGING_INCDIR}/wrp-c \
    -I${STAGING_INCDIR}/libparodus \
    -DENABLE_MESH_SOCKETS \
    "
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"

CFLAGS += " -Wall -Werror -Wextra -Wno-pointer-sign -Wno-int-to-pointer-cast -Wno-address -Wno-unused-parameter -Wno-misleading-indentation -Wno-unused-function"

LDFLAGS_append = " \
    -ldbus-1 \
    -lrdkloggers \
    -ltelemetry_msgsender \
    -lm \
    -lcjson \
    -lwrp-c \
    -llibparodus \
"
LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"

S = "${WORKDIR}/git"

inherit autotools systemd pkgconfig

EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', '--enable-gtestapp', '', d)}"
EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', ' --enable-wanfailover ', '', d)}"
EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', ' --enable-onewifi ', '', d)}"
EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'gateway_manager', ' --enable-gatewayfailoversupport ', '', d)}"
EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_extender', ' --enable-rdkb_extender ', '', d)}"
EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'rdk_ledmanager', ' --enable-rdk_ledmanager ', '', d)}"

# Enable OneWifi for this component only to fix build issues
EXTRA_OECONF_append = " --enable-onewifi "

do_install_append () {
    # Config files and scripts
    install -d ${D}/usr/ccsp/mesh
    install -d ${D}/usr/include/mesh
    install -m 644 ${S}/source/include/*.h ${D}/usr/include/mesh
    install -m 644 ${S}/config/TR181-MeshAgent.xml -t ${D}/usr/ccsp/mesh
    install -m 755 ${S}/scripts/active_host_filter.sh -t ${D}/usr/ccsp/mesh
    ln -sf /usr/bin/meshAgent ${D}/usr/ccsp/mesh/meshAgent

    install -d ${D}${systemd_unitdir}/system

    #CCSP Initialization Targets
    install -D -m 0644 ${S}/systemd_units/meshAgent.path ${D}${systemd_unitdir}/system/meshAgent.path
    install -D -m 0644 ${S}/systemd_units/meshwifi.service ${D}${systemd_unitdir}/system/meshwifi.service
    if ${@bb.utils.contains('DISTRO_FEATURES', 'meshwifi', 'true', 'false', d)}; then
        install -D -m 0644 ${S}/systemd_units/meshAgent.service ${D}${systemd_unitdir}/system/meshAgent.service
    fi


    install -m 775 ${S}/config/MeshAgent.cfg -t ${D}/usr/ccsp/mesh
    install -m 775 ${S}/config/MeshAgentDM.cfg -t ${D}/usr/ccsp/mesh

    #Add OneWifi flag for enabling OVS and Opensync
    if ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', 'true', 'false', d)}; then
        install -d ${D}/etc
        touch ${D}/etc/onewifi_enabled
    fi

    if ${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', 'true', 'false', d)}; then
        install -d ${D}/etc
        touch ${D}/etc/WFO_enabled
    fi
    install -d ${D}${sbindir}
    install -m 777 ${S}/scripts/led_control_script.sh ${D}${sbindir}/led_control_script.sh
}

PACKAGES += "${PN}-ccsp"
PACKAGES =+ "${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', '${PN}-gtest', '', d)}"

FILES_${PN}-gtest = "\
    ${@bb.utils.contains('DISTRO_FEATURES', 'gtestapp', '${bindir}/MeshAgent_gtest.bin', '', d)} \
"

# IMPORTANT! Do not add meshwifi.service to the SYSTEMD_SERVICE define below. We don't want it automatically
# started.
SYSTEMD_SERVICE_${PN} = " ${@bb.utils.contains('DISTRO_FEATURES', 'meshwifi', 'meshAgent.path meshAgent.service', '', d)}"

FILES_${PN}-ccsp = " \
    /fss/gw/usr/ccsp/* \
    ${prefix}/ccsp/mesh/* \
    ${prefix}/ccsp/* \
"

FILES_${PN} = " \
    /usr/bin/meshAgent \
    /usr/bin/xmesh_diagnostics \
    ${prefix}/ccsp/mesh/meshAgent \
    ${prefix}/ccsp/mesh/MeshAgent.cfg \
    ${prefix}/ccsp/mesh/MeshAgentDM.cfg \
    ${prefix}/ccsp/mesh/TR181-MeshAgent.xml \
    ${prefix}/ccsp/mesh/active_host_filter.sh \
    ${systemd_unitdir}/system/meshAgent.path \
    ${systemd_unitdir}/system/meshwifi.service \
    ${libdir}/libMeshAgentSsp.so* \
    ${libdir}/libXmeshDiags.so* \
    ${sbindir}/led_control_script.sh \
"
FILES_${PN} += " ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', '/etc/onewifi_enabled', '', d)} "
FILES_${PN} += " ${@bb.utils.contains('DISTRO_FEATURES', 'WanFailOverSupportEnable', '/etc/WFO_enabled', '', d)} "
FILES_${PN} += " ${@bb.utils.contains('DISTRO_FEATURES', 'meshwifi', ' ${systemd_unitdir}/system/meshAgent.service', '', d)} "

FILES_${PN}-dbg = " \
    ${prefix}/ccsp/mesh/.debug \
    ${prefix}/src/debug \
    ${bindir}/.debug \
    ${libdir}/.debug \
"

