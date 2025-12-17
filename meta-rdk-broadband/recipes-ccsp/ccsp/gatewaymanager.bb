#
# If not stated otherwise in this file or this component's Licenses.txt file the
# following copyright and licenses apply:
#
# Copyright 2017 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
SUMMARY = "This receipe provides gateway manager support."
SECTION = "console/utils"
LICENSE = "CLOSED"

DEPENDS = "ccsp-common-library dbus rdk-logger hal-platform util-linux utopia libunpriv jansson rbus webconfig-framework curl trower-base64 msgpack-c telemetry"
DEPENDS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' safec', " ", d)}"

require recipes-ccsp/ccsp/ccsp_common.inc

SRC_URI ="${RDKB_CCSP_ROOT_GIT}/GatewayManager/generic;protocol=${RDK_GIT_PROTOCOL};branch=${CCSP_GIT_BRANCH};name=GatewayManager"

SRCREV_GatewayManager = "${AUTOREV}"
SRCREV_FORMAT = "GatewayManager"
PV = "${RDK_RELEASE}+git${SRCPV}"
S = "${WORKDIR}/git"

inherit autotools systemd breakpad-logmapper

CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec`', '-fPIC', d)}"

CFLAGS_append = " -Wno-restrict -Wno-format-overflow -Wno-deprecated-declarations -Wno-cast-function-type "
CFLAGS_append_kirkstone = " -fcommon"


LDFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec`', '', d)}"
LDFLAGS_remove = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', '-lsafec-3.5', '', d)}"
LDFLAGS_append_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec-3.5.1 ', '', d)}"
LDFLAGS_append_kirkstone = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"
CFLAGS_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'safec', '', ' -DSAFEC_DUMMY_API', d)}"
CFLAGS_append =  "${@bb.utils.contains('DISTRO_FEATURES', 'local_restore_support', ' -DENABLE_LOCAL_RESTORE ', '', d)}"

EXTRA_OECONF_append = " --enable-rbus_only_gwmgr"

# Breakpad processname and logfile mapping
BREAKPAD_LOGMAPPER_PROCLIST = "gateway_manager"
BREAKPAD_LOGMAPPER_LOGLIST = "GatewayManagerLog.txt.0"


CFLAGS_append = " \
    -I=${includedir}/dbus-1.0 \
    -I=${libdir}/dbus-1.0/include \
    -I=${includedir}/ccsp \
    -I=${includedir}/syscfg \
    -I${STAGING_INCDIR}/syscfg \
    -DFEATURE_SUPPORT_RDKLOG \
    -I=${includedir}/rbus \
    -I${STAGING_INCDIR}/trower-base64 \
    -I${STAGING_INCDIR}/msgpackc \
    "
LDFLAGS_append = " \
    -ldbus-1 \
    -lccsp_common \
    -lsyscfg \
    -lprivilege \
    -lrbus \
    -lrt \
    -lpthread \
    -lbreakpadwrapper \
    -ltelemetry_msgsender \
    "
do_install_append () {
    # Config files and scripts
    install -d ${D}${exec_prefix}/ccsp/gatewaymanager
    install -m 644 ${S}/config/GatewayManager.xml ${D}${exec_prefix}/ccsp/gatewaymanager/GatewayManager.xml
    install -m 775 ${S}/script/precheck.sh ${D}${exec_prefix}/bin/precheck.sh
    install -d ${D}${systemd_unitdir}/system
    install -D -m 0644 ${S}/config/GatewayManager.service ${D}${systemd_unitdir}/system/GatewayManager.service
}
SYSTEMD_SERVICE_${PN} = "GatewayManager.service"
FILES_${PN} += " \
    ${exec_prefix}/ccsp/gatewaymanager \
    /usr/bin/* \
        ${systemd_unitdir}/system/GatewayManager.service \
    ${exec_prefix}/bin/precheck.sh \
"

FILES_${PN}-diag = "\
/${bindir}/gfo_diag \
"


