#
# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2017 Liberty Global B.V.
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

SUMMARY = "Drop Privileges"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI += "file://dropprivileges.pc"
SRC_URI += "file://dropprivileges.h"

S = "${WORKDIR}"

do_install_append() {
    install -p -m 0644 -D ${WORKDIR}/dropprivileges.h  ${D}${includedir}/dropprivileges/dropprivileges.h
    install -p -m 0644 -D ${WORKDIR}/dropprivileges.pc ${D}${libdir}/pkgconfig/dropprivileges.pc
}
