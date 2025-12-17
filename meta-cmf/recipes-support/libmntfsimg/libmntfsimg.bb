#
# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2021 Liberty Global Service B.V.
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

SUMMARY = "Library to mount and un-mount filesystem images"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://../LICENSE;md5=c495cafb5b230274448aaee58055c71d"

DEPENDS = "glib-2.0 cryptsetup libgudev lvm2"

# libmngfsimg invokes internally:
#  - /bin/echo (from busybox)
#  - /usr/bin/gencert (only when 'ami' is enabled)
#  - /usr/sbin/{crypt,verity}setup
RDEPENDS_${PN} += "busybox cryptsetup lvm2-udevrules"

SRCREV = "${AUTOREV}"
SRC_URI ="${CMF_GIT_ROOT}/components/opensource/dac-sec;name=${BPN};protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_MASTER_BRANCH}"
S = "${WORKDIR}/git/${BPN}"

inherit ${@oe.utils.conditional('ONEMW_SUPPORT', '1', 'onemwsrc', 'coverity', d)} pkgconfig cmake
ONEMW_SRC_SUBPATH = "rdk/${BPN}"
BBCLASSEXTEND = "native"

PACKAGECONFIG ??= "${@oe.utils.conditional('ONEMW_SUPPORT', '1', 'rdklogger ami', '', d)}"
PACKAGECONFIG[rdklogger] = "-DRDK_LOGGER_ENABLED=ON,-DRDK_LOGGER_ENABLED=OFF,rdk-logger,,"
PACKAGECONFIG[ami]       = "-DAMI_ENABLED=ON,,,gencert"

PACKAGES =+ "${PN}-test"
PROVIDES += "${PN}-test"

FILES_${PN}-test = "${bindir}/mntfsimg_test"
