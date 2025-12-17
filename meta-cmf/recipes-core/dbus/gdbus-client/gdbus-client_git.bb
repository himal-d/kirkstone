#
# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2018 Liberty Global B.V.
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


SUMMARY = "Simplifies definition of D-Bus calls and conversion of input and output parameters of the calls from and to STL-backed containers"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57 \
                    file://NOTICE;md5=46cc0e7d1095fb2cb3f068c78a0aae76"

DEPENDS = "glib-2.0 rdk-logger"

PV = "${RDK_RELEASE}+git${SRCPV}" 
SRCREV = "${AUTOREV}"

SRC_URI ="${CMF_GIT_ROOT}/components/opensource/gdbus-client;name=gdbus-client;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_MASTER_BRANCH}"

S = "${WORKDIR}/git"

inherit pkgconfig cmake coverity

# Use RDK logger for logging
EXTRA_OECMAKE += "-DRDK_LOGGER_ENABLED=ON"

FILES_${PN}     = "${libdir}/*.so.*"
FILES_${PN}-dev = "${libdir}/*.so ${includedir}/ ${libdir}/pkgconfig/"
