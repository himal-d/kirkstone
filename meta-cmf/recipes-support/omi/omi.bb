#
# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2021 Liberty Global B.V.
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

SUMMARY = "OCI Image Mounter"
DESCRIPTION = "Mounts and un-mounts OCI filesystem images"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

FILESEXTRAPATHS_prepend := "${THISDIR}/${@oe.utils.conditional('ONEMW_SUPPORT', '1', 'files-onemw:', 'files-rdk:', d)}"

DEPENDS = "dbus dropprivileges glib-2.0 glib-2.0-native jansson virtual/libkwk libdacjwt libmntfsimg cjose"

SRCREV = "${AUTOREV}"
SRC_URI ="${CMF_GIT_ROOT}/components/opensource/OMI;name=${BPN};protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_MASTER_BRANCH}"
S = "${WORKDIR}/git"
PV = "${RDK_RELEASE}+git${SRCPV}"

inherit ${@oe.utils.conditional('ONEMW_SUPPORT', '1', 'onemwsrc', 'coverity', d)} pkgconfig cmake systemd
ONEMW_SRC_SUBPATH = "rdk/${BPN}"

SRC_URI += "file://omi.service"
SRC_URI += "file://omi.conf"
SRC_URI += "file://99-omi.rules"

# Define kid -> certificate path mapping (see: CMakeLists.txt for details)
EXTRA_OECMAKE += "${@oe.utils.conditional('ONEMW_SUPPORT', '1', \
     '-DCERTIFICATE_PATH_FORMAT="/usr/share/ami-certificates/onemw-appmodule-authority-%s-cert.pem"', \
     '-DCERTIFICATE_PATH_FORMAT="${sysconfdir}/pki/kwk/certs/%s/bundlecrypt-cert.pem"', \
     d)}"

PACKAGECONFIG ??= "${@oe.utils.conditional('ONEMW_SUPPORT', '1', 'rdklogger', '', d)}"
PACKAGECONFIG[rdklogger] = "-DRDK_LOGGER_ENABLED=ON,-DRDK_LOGGER_ENABLED=OFF,rdk-logger,,"

SYSTEMD_SERVICE_${PN} = "omi.service"

do_install_append() {
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/omi.service ${D}${systemd_unitdir}/system/

    install -d ${D}${sysconfdir}/tmpfiles.d
    install -m 0440 ${WORKDIR}/omi.conf ${D}${sysconfdir}/tmpfiles.d/

    install -d ${D}${sysconfdir}/udev/rules.d
    install -m 0440 ${WORKDIR}/99-omi.rules ${D}${sysconfdir}/udev/rules.d/
}

PACKAGES =+ "${PN}-test"
PROVIDES += "${PN}-test"

FILES_${PN}-test = "${bindir}/omi-parser-test"
FILES_${PN} += "${sysconfdir}/tmpfiles.d/omi.conf"
FILES_${PN}-dev += "${datadir}/dbus-1/interfaces/com.lgi.onemw.omi1.xml"
