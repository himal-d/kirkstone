#
# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2019 Liberty Global B.V.
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

SUMMARY = "Cobalt (with wayland-egl backend)"
HOMEPAGE = "https://cobalt.dev/"
BUGTRACKER = "https://issuetracker.google.com/issues?q=componentid:181120%20status:open"

LICENSE = "BSD-3-Clause & BSD-2-Clause & Apache-2.0 & MIT & ISC & OpenSSL & CC0-1.0 & LGPL-2.0 & LGPL-2.1 & PD & Zlib & MPL-2.0"
LIC_FILES_CHKSUM = " \
    file://src/LICENSE;md5=0fca02217a5d49a14dfe2d11837bb34d \
    file://../depot_tools/LICENSE;md5=c2c05f9bdd5fc0b458037c2d1fb8d95e \
    file://../wayland/LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57 \
    file://../wayland/NOTICE;md5=1747492b12a6d7e65a574807f9786501 \
"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

DEPENDS = "virtual/libgles2 virtual/egl wayland gstreamer1.0 gstreamer1.0-plugins-base python-native bison-native"

inherit python3native

# (dw) We don't know when this will be certified - so we sticked to the master branch
SRC_URI += "git://cobalt.googlesource.com/depot_tools.git;protocol=https;rev=acbfb02f445b1612e08131e2a4aaca4f1a849050;destsuffix=depot_tools;name=depot_tools"
SRC_URI += "git://github.com/stagingrdkm/rpi-cobalt-wayland;protocol=https;rev=b12e884ddf6d05cd9d048fba225b84b59c9d958c;name=wayland;destsuffix=wayland"
SRC_URI += "git://cobalt.googlesource.com/cobalt;protocol=https;rev=3afedffaddc5ae13b4d21dcf2ba98dc14ca58e02;name=cobalt"
SRC_URI += "file://resolution-fix.patch"
SRC_URI += "file://0001-Do-not-use-clang-compiler.patch"
SRC_URI += "file://0001-Fix-to-cobalt-compilation-issue.patch"
SRC_URI += "file://0001-cobalt-fix-errors-due-to-gcc-9-or-higher-version-Wer.patch"

S = "${WORKDIR}/git"

PLATFORM   ?= "raspi-wayland"
BUILD_TYPE ?= "gold"

do_configure() {
    export PATH=$PATH:${S}/../depot_tools
    mkdir -p ${S}/src/third_party/starboard/raspi/
    cp -prf ${S}/../wayland ${S}/src/third_party/starboard/raspi/
    ${S}/src/cobalt/build/gyp_cobalt -C ${BUILD_TYPE} ${PLATFORM}
}

do_compile() {
    export PATH=$PATH:${S}/../depot_tools
    ninja -v -C ${S}/src/out/${PLATFORM}_${BUILD_TYPE} cobalt
}

do_install() {
    export PATH=$PATH:${S}/../depot_tools
    install -d ${D}${bindir}
    install -m 0755 ${S}/src/out/${PLATFORM}_${BUILD_TYPE}/cobalt ${D}${bindir}
    cp -prf ${S}/src/out/${PLATFORM}_${BUILD_TYPE}/content ${D}${bindir}
}

FILES_${PN}  = "${bindir}/cobalt"
FILES_${PN} += "${bindir}/content/*"
