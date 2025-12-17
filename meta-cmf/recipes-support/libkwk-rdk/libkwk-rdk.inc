#
# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2023 Liberty Global Service B.V.
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

#
# Author: Damian Wrobel <dwrobel@ertelnet.rybnik.pl>
#

SRCREV = "${AUTOREV}"
SRC_URI = "${CMF_GIT_ROOT}/components/opensource/dac-sec;name=${BPN};protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_MASTER_BRANCH}"
S = "${WORKDIR}/git/libkwk-rdk"

inherit ${@oe.utils.conditional('ONEMW_SUPPORT', '1', 'onemwsrc', 'coverity', d)} cmake
ONEMW_SRC_SUBPATH="rdk/libkwk-rdk"

PACKAGECONFIG[header]  = "-DINSTALL_HEADERS=ON,-DINSTALL_HEADERS=OFF"
PACKAGECONFIG[library] = "-DINSTALL_LIBS=ON,-DINSTALL_LIBS=OFF,openssl libkwk-rdk-header"
