#!/bin/sh
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2021 RDK Management
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
##########################################################################
if [ -f ${PWD}/../versions.conf ]; then
        sed -i '/meta-/d' ${PWD}/../versions.conf
        sed -i '/hooks/d' ${PWD}/../versions.conf
        sed -i '/openembedded/d' ${PWD}/../versions.conf
        sed -i '/bitbake/d' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/closedcaption/generic+SRCREV_pn-closedcaption-hal-headers+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/closedcaption/generic+SRCREV_pn-closedcaption+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/ledmgr/generic+SRCREV_pn-ledmgr+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/ledmgr/generic+SRCREV_pn-ledmgr-headers+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/ledmgr/generic+SRCREV_pn-ledmgr-extended-noop+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/trm/generic+SRCREV_pn-trm-common+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/trm/generic+SRCREV_pn-qtapp+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/trm/generic+SRCREV_pn-wsproxy+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/trm/generic+SRCREV_pn-trmmgr+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/devicesettings/generic+SRCREV_pn-devicesettings+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/devicesettings/generic+SRCREV_pn-devicesettings-hal-headers+g' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/hdmicec/generic+SRCREV_pn-hdmicec+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/hdmicec/generic+SRCREV_pn-hdmicecheader+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/iarmmgrs/generic+SRCREV_pn-iarmmgrs+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/iarmmgrs/generic+SRCREV_pn-iarmmgrs-hal-headers+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/media_utils/generic+SRCREV_pn-media-utils+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/media_utils/generic+SRCREV_pn-media-utils-headers+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/thirdparty/dimark/tr69-4.4/devices/raspberrypi+SRCREV_pn-tr69hostif+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/thirdparty/dimark/tr69-4.4/devices/raspberrypi+SRCREV_pn-tr69hostif-headers+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/audioserver/generic+SRCREV_pn-audioserver+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/audioserver/generic+SRCREV_pn-audioserver-headers+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/audioserver/generic+SRCREV_pn-audioserver-sample-apps+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/rbuscore/generic+SRCREV_pn-rbus-core+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/opensource/rtmessage+SRCREV_pn-rtmessage+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/tdk/generic+SRCREV_pn-tdk+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/tdk/generic+SRCREV_pn-installtdk+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/generic+SRCREV_pn-rmfgeneric+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/generic+SRCREV_pn-rmfapp+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/generic+SRCREV_pn-rmfgenericheader+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/generic+SRCREV_pn-rmfgenericheaders+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/generic+SRCREV_pn-trh+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/generic+SRCREV_pn-rtrmfplayer+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/generic+SRCREV_pn-rmfosal+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/generic+SRCREV_pn-sectionfilter-hal-stub+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/generic+SRCREV_pn-runsnmp-emu+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/generic+SRCREV_pn-runsnmp+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/generic+SRCREV_pn-rmfpodserver+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/generic+SRCREV_pn-runpod+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/generic+SRCREV_pn-rmfpodmgrheaders+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/generic+SRCREV_pn-rmfpodmgr+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/generic+SRCREV_pn-rmfhalheaders+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/dvr/generic+SRCREV_pn-dvrgenericheaders+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/dvr/generic+SRCREV_pn-dvrmgr+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/appmanager/generic+SRCREV_pn-appmanager+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/appmanager/generic+SRCREV_pn-rdkresidentapp+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/opensource/qt5_1/generic+SRCREV_pn-qtbase+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/opensource/qt5_1/generic+SRCREV_pn-qtbase-native+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/wifi/generic+SRCREV_pn-wifi-hal-generic+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/wifi/generic+SRCREV_pn-wifi-hal-headers+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/diagnostics/generic+SRCREV_pn-diagnostics-snmp2json+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/diagnostics/generic+SRCREV_pn-rdk-diagnostics+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/xraudio/hal_ctrlm+SRCREV_pn-ctrlm-xraudio-hal+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/xraudio/hal_ctrlm+SRCREV_pn-ctrlm-xraudio-hal-headers+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/generic/systemtimemgr/generic+SRCREV_pn-systimemgrinetrface+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/generic/systemtimemgr/generic+SRCREV_pn-systimemgrfactory+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/generic/systemtimemgr/generic+SRCREV_pn-systimemgr+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-components/opensource/RDK_apps+SRCREV_pn-residentui+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-components/opensource/RDK_apps+SRCREV_pn-lxapp-diag+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-components/opensource/RDK_apps+SRCREV_pn-lxapp-bt-audio+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/devices/intel-x86-pc/rdkri+SRCREV_pn-sectionfilter-hal-noop+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/mediaframework/devices/intel-x86-pc/rdkri+SRCREV_pn-dvrmgr-hal-noop+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/thirdparty/cablelabs/chila/podManager/generic+SRCREV_pn-rmfpodmgrheaders-priv+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/thirdparty/cablelabs/chila/podManager/generic+SRCREV_pn-snmpmanager-priv+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/thirdparty/cablelabs/chila/podManager/generic+SRCREV_pn-podserver-priv+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/generic/tdk/tdk-advanced/generic+SRCREV_pn-tdksm+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/generic/tdk/tdk-advanced/generic+SRCREV_pn-tdkadvanced+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/OCDM-Widevine/generic+SRCREV_pn-wpeframework-ocdm-widevine+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/OCDM-Widevine/generic+SRCREV_pn-wpeframework-ocdm-widevine2+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/rf4ce/generic+SRCREV_pn-rf4ce+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/rf4ce/generic+SRCREV_pn-rf4ce-headers+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/vod-client/generic+SRCREV_pn-vodclient-java+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/vod-client/generic+SRCREV_pn-vodclient-app+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/lxy/generic+SRCREV_pn-lxy+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/lxy/generic+SRCREV_pn-lxyupdate+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/xreplugins/generic+SRCREV_pn-netflix-plugin+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/xreplugins/generic+SRCREV_pn-wayland-plugin-default+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/xreplugins/generic+SRCREV_pn-xre2-plugin-default+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/cpc/xre/generic+SRCREV_pn-xre-receiver-default+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/cpc/xre/generic+SRCREV_pn-xre-receiver-default-headers+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/ave/generic+SRCREV_pn-ave-crypto+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/ave/generic+SRCREV_pn-ave-filesystem+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/ave/generic+SRCREV_pn-ave-trace+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/ave/generic+SRCREV_pn-ave-ve+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/ave/generic+SRCREV_pn-ave-auditude+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/ave/generic+SRCREV_pn-ave-safe-apis+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/ave/generic+SRCREV_pn-ave-drm+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/ave/generic+SRCREV_pn-ave-psdk+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/ave/generic+SRCREV_pn-ave-psdkutils+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/ave/generic+SRCREV_pn-ave-adapter+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/ave/generic+SRCREV_pn-ave-kernel+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/ave/generic+SRCREV_pn-ave-text+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/ave/generic+SRCREV_pn-ave-xmlreader+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/ave/generic+SRCREV_pn-ave-cts+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/ave/generic+SRCREV_pn-ave-net+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/sec-client-rdk/generic+SRCREV_pn-secclient+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/sec-client-rdk/generic+SRCREV_pn-socprovapi-crypto+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/sec-client-rdk/generic+SRCREV_pn-socprovapi+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/cpc/sec-client-rdk/generic+SRCREV_pn-secclient+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/rdk-ca-store/generic+SRCREV_pn-rdk-ca-store+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/rdk-ca-store/generic+SRCREV_pn-caupdate+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/cpc/sec-apis/generic+SRCREV_pn-secapi-common-crypto+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/cpc/sec-apis/generic+SRCREV_pn-secapi-common-hw+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/cpc/sec-apis/generic+SRCREV_pn-secapi-common+' ${PWD}/../versions.conf
	sed -z -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/key_simulator/generic+SRCREV_pn-key-simulator+' ${PWD}/../versions.conf
        sed -z -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/key_simulator/generic+SRCREV_pn-sys-resource+' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/generic/crashlog/generic+SRCREV_pn-crashlog+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/gst-plugins-rdk/soc/raspberry/rpi3/playersinkbin+SRCREV_pn-gst-plugins-playersinkbin-raspberry+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/podmgr/devices/intel-x86-pc/rdkri+SRCREV_pn-podmgr+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/recorder/generic+SRCREV_pn-recorder+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/gst-plugins-rdk-dvr/generic+SRCREV_pn-gst-plugins-rdk-dvr+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/xrpSMEngine/generic+SRCREV_pn-xr-sm-engine+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/libunpriv/generic+SRCREV_pn-libunpriv+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/mem_analyser_tools/generic+SRCREV_pn-memstress+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/telemetry/generic+SRCREV_pn-telemetry+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/rtcav/generic+SRCREV_pn-rtcav+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-Comcast/littlesheens.git+SRCREV_pn-littlesheens+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/opensource/qt5_1/soc/broadcom/common+SRCREV_soc_pn-qtbase+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/storagemanager/generic+SRCREV_pn-storagemanager+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/sys_resource/generic+SRCREV_pn-sys-resource +g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/closedcaption/soc/noop/common+SRCREV_pn-closedcaption-hal-noop+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/rfc/generic+SRCREV_pn-rfc+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/control/generic+SRCREV_pn-ctrlm-headers+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-libtom/libtomcrypt.git+SRCREV_pn-libtomcrypt+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/trm/generic+SRCREV_pn-trm-common+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/power-state-monitor/generic+SRCREV_pn-power-state-monitor+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/devices/raspberrypi/devicesettings+SRCREV_pn-devicesettings-hal-raspberrypi+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/ttsengine/generic+SRCREV_pn-tts+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/opensource/qtwebsockets/generic+SRCREV_pn-qtwebsockets+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/yocto_oe/layers/iarmmgrs-hal-sample+SRCREV_pn-iarmmgrs-hal-noop+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/rmf_mediastreamer/generic+SRCREV_pn-rmfstreamer+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/crashupload/generic+SRCREV_pn-crashupload+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/xupnp/generic+SRCREV_pn-xupnp+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/dtcp/generic+SRCREV_pn-dtcpmgr-noop+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/sys_utils/generic/+SRCREV_pn-sys-utils+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/mediaframework/soc/raspberrypi/common+SRCREV_pn-rmfhalheaders+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/rdkbrowser/generic+SRCREV_pn-rdkbrowser+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sysint/devices/raspberrypi+SRCREV_soc_pn-sysint+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/hwselftest/generic+SRCREV_pn-hwselftest+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/tr69hostif/generic+SRCREV_pn-tr69hostif +g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/rdkbrowser2/generic+SRCREV_pn-rdkbrowser2+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-components/opensource/westeros+SRCREV_pn-westeros+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/cpc/socprovisioning/soc/cryptanium/common+SRCREV_soc_pn-socprovisioning-crypto+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/analyzers/scripts/host/generic+SRCREV_pn-analyzers-host+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/dcm/generic+SRCREV_pn-dcmjsonparser+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/si_cache_parser/generic+SRCREV_pn-si-cache-parser+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/rmf_tools/tenableHDCP/soc/broadcom/common+SRCREV_soc_pn-tenablehdcp+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/mfr_data/generic+SRCREV_pn-mfr-data+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/opensource/base64/generic+SRCREV_pn-base64+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/mocahal/generic+SRCREV_pn-moca-hal+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/rdklogctrl/generic+SRCREV_pn-rdklogctrl+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/dtcp/generic+SRCREV_pn-dtcpmgr-noop+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/iarmbus/generic+SRCREV_pn-iarmbus+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-nanomsg/nanomsg.git+SRCREV_pn-nanomsg+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/breakpad_wrapper/generic+SRCREV_pn-breakpad-wrapper+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/lxccpid+SRCREV_pn-lxccpid+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/iarmmgrs/generic+SRCREV_pn-iarmmgrs +g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/cpc/authservice/generic+SRCREV_authservice_pn-authservice+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/control-testapp/generic+SRCREV_pn-ctrlm-testapp+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/thirdparty/vnc/generic+SRCREV_pn-vnc+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/hdmicec/soc/raspberrypi/rpi3+SRCREV_pn-hdmicec-hal+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/cpc/xre/devices/raspberry/rpi3+SRCREV_xreplat_pn-xre-receiver-default +g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sec-apis/generic+SRCREV_pn-secapi-noop+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/dcm/generic+SRCREV_pn-dcmjsonparser+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/gstreamer-netflix-platform/generic+SRCREV_pn-rdk-gstreamer-utils+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/media_utils/generic+SRCREV_pn-media-utils+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/opensource/jquery/generic+SRCREV_pn-jquery+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sec-apis/generic+SRCREV_pn-secapi-noop+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/iarm_set_powerstate/generic+SRCREV_pn-iarm-set-powerstate+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/netmonitor/generic+SRCREV_pn-nlmonitor+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/libSyscallWrapper/generic+SRCREV_pn-libsyswrapper+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/rmf_tools/tenableHDCP/generic+SRCREV_pn-tenablehdcp+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/closedcaption/generic+SRCREV_pn-closedcaption+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/servicemanager/generic+SRCREV_pn-servicemanager+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/mfr_utils/generic+SRCREV_pn-mfr-utils+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/closedcaption/soc/noop/common+SRCREV_pn-closedcaption-hal-noop+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/rbus/generic+SRCREV_pn-rbus+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/gst_svp_ext/generic+SRCREV_pn-gst-svp-ext+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/generate_si_cache/generic+SRCREV_pn-generate-si-cache+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/aampabr+SRCREV_pn-aampabr+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/rdkversion/generic+SRCREV_pn-rdkversion+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/cpc/socprovisioning/generic+SRCREV_pn-socprovisioning-crypto+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/servicemanager/soc/raspberrypi/raspberrypi+SRCREV_svcmgrplat_pn-servicemanager+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/mediaframework/soc/raspberrypi/common+SRCREV_pn-rmfhalheaders+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/iarm_event_sender/generic+SRCREV_pn-iarm-event-sender+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/syslog_helper/generic+SRCREV_pn-syslog-helper+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/netsrvmgr/generic+SRCREV_pn-netsrvmgr+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/gst-plugins-rdk-aamp+SRCREV_pn-gst-plugins-rdk-aamp+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/injectedbundle/generic+SRCREV_pn-injectedbundle+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/sys_utils/generic+SRCREV_pn-sys-utils+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/cpc/tr69profiles/generic+SRCREV_pn-tr69profiles+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/bluetooth_leAppMgr/generic+SRCREV_pn-bluetooth-leappmgr+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/bluetooth_mgr/generic+SRCREV_pn-bluetooth-mgr+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/bluetooth/generic+SRCREV_pn-bluetooth-core+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/servicemanager/generic+SRCREV_pn-servicemanager+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/rdkmediaplayer/generic+SRCREV_pn-rdkmediaplayer+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-zserge/jsmn.git+SRCREV_pn-jsmn+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/cpc/appmanager/generic+SRCREV_cpcmgr_pn-appmanager+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/aamp+SRCREV_pn-aamp+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/rdm+SRCREV_pn-rdm+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/cpc/authservice/devices/raspberrypi+SRCREV_authdevice_pn-authservice+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/hostdataconverter/generic+SRCREV_pn-hostdataconverter+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/fonts/generic+SRCREV_pn-rdk-fonts+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/rdkapps/generic+SRCREV_rdkbrowserapps_pn-rdkbrowser+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/cpuprocanalyzer+SRCREV_pn-cpuprocanalyzer+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/dca/generic+SRCREV_pn-dca+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/cgroup_memory_utils/generic+SRCREV_pn-cgrouputils+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/audiocapturemgr/generic+SRCREV_pn-audiocapturemgr+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/rdk_logger/generic+SRCREV_pn-rdk-logger+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/cpc/sec-apis-crypto/generic+SRCREV_pn-secapi-crypto-brcm+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/gst-plugins-rdk/generic+SRCREV_pn-gst-plugins-rdk+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/iarm_query_powerstate/generic+SRCREV_pn-iarm-query-powerstate+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sys_mon_tools/analyzers/scripts/target/generic+SRCREV_pn-analyzers-target+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/yocto_oe/layers/devicesettings-hal-sample+SRCREV_pn-devicesettings-hal-noop+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/lxc-container-generator+SRCREV_pn-lxc-container-generator-native+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/control/generic+SRCREV_pn-ctrlm-main+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/sysint/generic+SRCREV_pn-sysint+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/generic/fog/generic+SRCREV_pn-fog+g' ${PWD}/../versions.conf
        sed -i 's+SRCREV_pn-rdk/components/cpc/firewall/generic+SRCREV_firewall_pn-sysint+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/playready-cdm-rdk/generic+SRCREV_pn-playready-cdm-rdk+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/rdk-OCDM-Playready/generic+SRCREV_pn-wpeframework-ocdm-playready-rdk+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/generic/rdkfwupdater+SRCREV_pn-rdkfwupgrader+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/tdk/generic+SRCREV_pn-tdk-cpc+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/config-files/generic+SRCREV_pn-config-files+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/nvm/nvm-sqlite/generic+SRCREV_pn-nvm-sqlite+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/config-libs/generic+SRCREV_pn-config-libs+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/rdkb/components/cpc/icontrolkey/generic+SRCREV_pn-icontrolkey+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/config-service/generic+SRCREV_pn-config-service+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/sec_pks_client/generic+SRCREV_pn-sec-pks-client+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/utils/cpc/sslcerts/generic+SRCREV_pn-sslcerts+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/utils/cpc/sshkeys/generic+SRCREV_pn-sshkeys+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/mount-utils/generic+SRCREV_pn-mount-utils+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/ecfs_search/generic+SRCREV_pn-ecfs-search+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/crypt_utils/generic+SRCREV_pn-crypt-utils+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/snmp/generic+SRCREV_pn-net-snmp+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/utils/cpc/snmpv3certs/generic+SRCREV_pn-snmpv3certs+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/generic/podserver/devices/intel-x86-pc/rdkemulator/emu-podserver+SRCREV_pn-emu-podserver+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/rtcast/generic+SRCREV_pn-rtcast+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/thirdparty/cox/generic+SRCREV_pn-acscerts+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/fonts/generic+SRCREV_pn-cpc-fonts+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/component/cpc/xre-automation-dac15/xre-automation/devices/intel-x86-pc/rdkemulator +SRCREV_pn-fbdump-util+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/netflix5_1/generic+SRCREV_pn-netflix+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/generic/sdvagent/generic+SRCREV_pn-sdvagent+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/rdkservices/generic+SRCREV_pn-rdkservices-comcast+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/xdial/generic+SRCREV_pn-xdial+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/component/cpc/mediaframework/devices/intel-x86-pc/halsnmp+SRCREV_pn-halsnmp-emu+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/thirdparty/rogers/generic+SRCREV_pn-rogerscerts+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/lostandfound/generic+SRCREV_pn-lostandfound+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/component/cpc/widevine-cdm-rdk/generic+SRCREV_pn-widevinecdmi+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-apps/netflix/rdkcryptoapi-netflix+SRCREV_pn-secapi-netflix+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/playready/generic+SRCREV_pn-playreadycdmi+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/playready_netflix/generic+SRCREV_pn-playready+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/thirdparty/shaw/generic+SRCREV_pn-shawcerts+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/nrdplugin/generic+SRCREV_pn-nrdplugin+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/mount-utils/generic+SRCREV_pn-mountutils+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/prototypes/rdkcef+SRCREV_pn-rdkcefapp+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/opensource/chromium2062/generic+SRCREV_pn-cef-eglfs+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/qtwebrtc_new/generic+SRCREV_pn-qtwebrtc+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/generic/ppapi_plugins/generic+SRCREV_pn-ppapi-plugins+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/OCDM-Playready/generic+SRCREV_pn-wpeframework-ocdm-playready+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/cachehelpers/generic +SRCREV_pn-cachehelpers+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/rdkssa/generic+SRCREV_pn-rdk-oss-ssa+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/generic/libledger+SRCREV_pn-libledger+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/ssa-cpc+SRCREV_pn-ssacpc+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/generic/rdkxpkiutl+SRCREV_pn-rdkxpkiutl+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/generic/ermgr+SRCREV_pn-ermgr+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/generic/gstreamer-netflix-platform/generic+SRCREV_pn-rdk-gstreamer-utils+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/generic/WebconfigFramework/generic+SRCREV_pn-webconfig-framework+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/generic/audiocapturemgr/soc/raspberrypi/common+SRCREV_soc_pn-audiocapturemgr+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/generic/bluetooth_leAppMgr/soc/raspberrypi/common+SRCREV_soc_pn-bluetooth-leappmgr+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/cpc/bluetooth_leAppMgr+SRCREV_cpc_pn-bluetooth-leappmgr+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/generic/bluetooth_mgr/soc/raspberrypi/common+SRCREV_soc_pn-bluetooth-mgr+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/generic/devicesettings/devices/raspberrypi/rpi3+SRCREV_pn-devicesettings-hal-raspberrypi+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/rdkb/components/opensource/ccsp/DSLAgent/generic+SRCREV_pn-ccsp-dslagent+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/rdkb/components/opensource/ccsp/VLANAgent/generic+SRCREV_pn-ccsp-vlanagent+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/rdkb/components/opensource/ccsp/XTMAgent/generic+SRCREV_pn-ccsp-xtmagent+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdkb/components/opensource/ccsp/RebootManager+SRCREV_pn-reboot-manager+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/components/rdkssa/generic+SRCREV_pn-rdk-oss-ssa+g' ${PWD}/../versions.conf
	sed -i 's+SRCREV_pn-rdk/yocto_oe/manifests/raspberrypi-manifest+SRCREV_pn-manifest+g' ${PWD}/../versions.conf 
        sed -i 's+SRCREV_pn-rdk/components/generic/media_interface_lib/soc/broadcom/common+SRCREV_pn-media-interface+g' ${PWD}/../versions.conf
fi

if [ -f ${PWD}/../versions.conf ]; then
     cat ${PWD}/../versions.conf >> ${PWD}/../auto.conf
fi

if [ -f ${PWD}/../auto.conf ]; then
     sed -i 's/externalsrc//g' ${PWD}/../auto.conf
     sed -i '/EXTERNALSRC_pn/d' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-audioserver-sample-apps/SRCREV_audioserversampleapps_pn-audioserver-sample-apps/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-audioserver-headers/SRCREV_audioserverheaders_pn-audioserver-headers/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-audioserver /SRCREV_audioserver_pn-audioserver /g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-rdm/SRCREV_rdmgeneric_pn-rdm/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-tdk/SRCREV_tdk_pn-tdk/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-jsmn/SRCREV_jsmn_pn-jsmn/g'  ${PWD}/../auto.conf  
     sed -i 's/SRCREV_pn-aampabr/SRCREV_aamp-abr_pn-aampabr/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-gst-plugins-rdk-aamp/SRCREV_gstplug-rdk-aamp_pn-gst-plugins-rdk-aamp/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-installtdk/SRCREV_tdk_pn-installtdk/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-ctrlm-headers/SRCREV_ctrlm-headers_pn-ctrlm-headers/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-rbus-core/SRCREV_base_pn-rbus-core/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-hwselftest/SRCREV_hwselftest_pn-hwselftest/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-rtmessage/SRCREV_rtmessage_pn-rtmessage/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-libsyswrapper/SRCREV_libsyswrapper_pn-libsyswrapper/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-servicemanagerfunctionaltest/SRCREV_generic_pn-servicemanagerfunctionaltest/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-appmanager/SRCREV_generic_pn-appmanager/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-audiocapturemgr/SRCREV_audiocapturemgr_pn-audiocapturemgr/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-breakpad-wrapper/SRCREV_breakpad_wrapper_pn-breakpad-wrapper/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-ctrlm-testapp/SRCREV_ctrlm-testapp_pn-ctrlm-testapp/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-ctrlm-main/SRCREV_ctrlm-main_pn-ctrlm-main/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-hdmicec /SRCREV_hdmicec_pn-hdmicec /g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-iarmbus/SRCREV_iarmbus_pn-iarmbus/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-iarmmgrs /SRCREV_iarmmgrs_pn-iarmmgrs /g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-rmfgeneric /SRCREV_rmfgeneric_pn-rmfgeneric /g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-nlmonitor/SRCREV_netmonitor_pn-nlmonitor/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-netsrvmgr/SRCREV_netsrvmgr_pn-netsrvmgr/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-rdkbrowser /SRCREV_default_pn-rdkbrowser/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-rfc/SRCREV_rfc_pn-rfc/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-rmfstreamer/SRCREV_rmfmediastreamergeneric_pn-rmfstreamer/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-mfr-utils/SRCREV_mfr-utils_pn-mfr-utils/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-sysint/SRCREV_sysintgeneric_pn-sysint/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-tr69hostif /SRCREV_tr69hostif_pn-tr69hostif /g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-wsproxy/SRCREV_wsproxy_pn-wsproxy/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-xupnp/SRCREV_xupnp_pn-xupnp/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-servicemanager/SRCREV_servicemanager_pn-servicemanager/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-gst-svp-ext/SRCREV_gst_pn-gst-svp-ext/g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-ledmgr /SRCREV_generic_pn-ledmgr /g'  ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-crashlog/SRCREV_crashlog_pn-crashlog/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-dvrmgr /SRCREV_dvrmgr_pn-dvrmgr/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-gst-plugins-rdk-dvr/SRCREV_dvr-plugins_pn-gst-plugins-rdk-dvr/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-audioserver-gstplugin-generic/SRCREV_plugin_pn-audioserver-gstplugin-generic/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-xr-sm-engine/SRCREV_xrpSMEngine_pn-xr-sm-engine/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-libunpriv/SRCREV_libunpriv_pn-libunpriv/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-rdkresidentapp/SRCREV_generic_pn-rdkresidentapp/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-ctrlm-xraudio-hal /SRCREV_ctrlm-xraudio-hal_pn-ctrlm-xraudio-hal/g' ${PWD}/../auto.conf     
     sed -i 's/SRCREV_pn-ctrlm-xraudio-hal-headers/SRCREV_ctrlm-xraudio-hal-headers_pn-SRCREV_ctrlm-xraudio-hal-headers/g' ${PWD}/../auto.conf 
     sed -i 's/SRCREV_pn-tdk-cpc/SRCREV_tdk_tdkcpc_pn-tdk-cpc/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-config-files/SRCREV_cpgc_pn-config-files/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-systimemgrinetrface/SRCREV_systemtimemgrifc_pn-systimemgrinetrface/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-systimemgr /SRCREV_systemtimemgr_pn-systimemgr/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-systimemgrfactory/SRCREV_systemtimemgrfactory_pn-systimemgrfactory/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-nvm-sqlite/SRCREV_nvm-sqlite_pn-nvm-sqlite/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-rdkversion/SRCREV_rdkversion_pn-rdkversion/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-config-libs/SRCREV_cpg-libs_pn-config-libs/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-config-service/SRCREV_cpgu_pn-config-service/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-ecfs-search/SRCREV_ecfsgeneric_pn-ecfs-search/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-caupdate/SRCREV_caupdate_pn-caupdate/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-rdk-ca-store/SRCREV_rdk-ca-store_pn-rdk-ca-store/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-tdksm/SRCREV_tdkadvanced_pn-tdksm/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-tdkadvanced/SRCREV_tdkadvanced_pn-tdkadvanced/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-mfr-data/SRCREV_mfr-data_pn-mfr-data/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-ctrlm-main/SRCREV_ctrlm-main-cpc_pn-ctrlm-main/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-lostandfound/SRCREV_lafgeneric_pn-lostandfound/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-widevinecdmi/SRCREV_widevine-cdm-rdk_pn-widevinecdmi/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-playreadycdmi/SRCREV_playready_pn-playreadycdmi/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-secclient/SRCREV_secclient_pn-secclient/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-socprovapi-crypto/SRCREV_socprovapi-crypto_pn-socprovapi-crypto/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-socprovapi /SRCREV_socprovapi_pn-socprovapi/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-hwselftest/SRCREV_hwselftest_pn-hwselftest/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-mountutils/SRCREV_generic_pn-mountutils/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-libledger/SRCREV_libledger_pn-libledger/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-rdkssa/SRCREV_rdkssa_pn-rdkssa/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-lxy /SRCREV_lxy_pn-lxy/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-lxyupdate/SRCREV_lxy_pn-lxyupdate/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-wayland-plugin-default/SRCREV_xreplgs_pn-wayland-plugin-default/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-cef-eglfs/SRCREV_rdkcef_chromium_pn-cef-eglfs/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-socprovisioning/SRCREV_socprovisioning_pn-socprovisioning/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-qtwebrtc/SRCREV_qtwebrtc_pn-qtwebrtc/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-xre-receiver-default /SRCREV_xre_default_xreplat_servicemanager_svcmgrplat_pn-xre-receiver-default/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-xre-receiver-default-headers/SRCREV_xrereceiverdefaultheaders_pn-xre-receiver-default-headers/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-authservice/SRCREV_authservice_pn-authservice/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-sdvagent/SRCREV_sdvagent_pn-sdvagent/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-rdk-oss-ssa/SRCREV_rdk-oss-ssa_pn-rdk-oss-ssa/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-ssacpc/SRCREV_ssacpc_pn-ssacpc/g' ${PWD}/../auto.conf
     sed -i 's/SRCREV_pn-rdkxpkiutl/SRCREV_rdkxpkiutl_pn-rdkxpkiutl/g' ${PWD}/../auto.conf
fi     

