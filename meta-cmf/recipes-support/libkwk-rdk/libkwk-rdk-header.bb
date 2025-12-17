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

SUMMARY = "Serialization package KWK library (interface part)"
DESCRIPTION = "Library to store and retrieve KWKs for in-field provisioned serialization packages"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://../LICENSE;md5=c495cafb5b230274448aaee58055c71d"
PV="1.4.1"

PACKAGECONFIG = "header"

include libkwk-rdk.inc
