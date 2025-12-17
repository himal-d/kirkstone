#!/bin/sh
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
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
##########################################################################


execute_component() {
	
case $2 in
	"ccsp-commonlib")
		git clone https://$1@gerrit.teamccp.com/a/rdk/rdkb/components/opensource/ccsp/CcspCommonLibrary/generic ccsp-commonlib
		cd ccsp-commonlib
		autoreconf -i
		./configure --build=i686-linux --host=i586-rdk-linux --target=i586-rdk-linux --prefix=/build-qemux86broadband/source/ccsp-commonlib/image/usr --exec_prefix=/build-qemux86broadband/source/ccsp-commonlib/image/usr --bindir=/build-qemux86broadband/source/ccsp-commonlib/image/usr/bin --sbindir=/build-qemux86broadband/source/ccsp-commonlib/image/usr/sbin --libexecdir=/build-qemux86broadband/source/ccsp-commonlib/image/usr/lib/ccsp-common-library --datadir=/build-qemux86broadband/source/ccsp-commonlib/image/usr/share --sysconfdir=/build-qemux86broadband/source/ccsp-commonlib/image/etc --sharedstatedir=/build-qemux86broadband/source/ccsp-commonlib/image/com --localstatedir=/build-qemux86broadband/source/ccsp-commonlib/image/var --libdir=/build-qemux86broadband/source/ccsp-commonlib/image/usr/lib --includedir=/build-qemux86broadband/source/ccsp-commonlib/image/usr/include --oldincludedir=/build-qemux86broadband/source/ccsp-commonlib/image/usr/include --infodir=/build-qemux86broadband/source/ccsp-commonlib/image/usr/share/info --mandir=/build-qemux86broadband/source/ccsp-commonlib/image/usr/share/man --disable-silent-rules --disable-dependency-tracking
		make CFLAGS="-I /usr/include/dbus-1.0 -I /usr/lib/dbus-1.0/include"
		make install
	 ;;
	"ccsp-cr")
		git clone https://$1@gerrit.teamccp.com/a/rdk/rdkb/components/opensource/ccsp/CcspCr/generic ccsp-cr
		cd ccsp-cr
		autoreconf -i
		./configure --build=i686-linux --host=i586-rdk-linux --target=i586-rdk-linux --prefix=/build-qemux86broadband/source/ccsp-cr/image/usr --exec_prefix=/build-qemux86broadband/source/ccsp-cr/image/usr --bindir=/build-qemux86broadband/source/ccsp-cr/image/usr/bin --sbindir=/build-qemux86broadband/source/ccsp-cr/image/usr/sbin --libexecdir=/build-qemux86broadband/source/ccsp-cr/image/usr/lib/ccsp-common-library --datadir=/build-qemux86broadband/source/ccsp-cr/image/usr/share --sysconfdir=/build-qemux86broadband/source/ccsp-cr/image/etc --sharedstatedir=/build-qemux86broadband/source/ccsp-cr/image/com --localstatedir=/build-qemux86broadband/source/ccsp-cr/image/var --libdir=/build-qemux86broadband/source/ccsp-cr/image/usr/lib --includedir=/build-qemux86broadband/source/ccsp-cr/image/usr/include --oldincludedir=/build-qemux86broadband/source/ccsp-cr/image/usr/include --infodir=/build-qemux86broadband/source/ccsp-cr/image/usr/share/info --mandir=/build-qemux86broadband/source/ccsp-cr/image/usr/share/man --disable-silent-rules --disable-dependency-tracking
		make CFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types -DFEATURE_SUPPORT_RDKLOG -I=/usr/include/breakpad   -D_COSA_HAL_ -U_COSA_SIM_ -fno-exceptions -ffunctio""n-sections -fdata-sections -fomit-frame-pointer -fno-strict-aliasing            -DCONFIG_SYSTEM_MOCA -D_ANSC_LINUX -D_ANSC_USER -D_ANSC_LITTLE_ENDIA""N_ -D_CCSP_CWMP_TCP_CONNREQ_HANDLER            -D_DSLH_STUN_ -D_NO_PKI_KB5_SUPPORT -D_BBHM_SSE_FILE_IO -D_ANSC_USE_OPENSSL_ -DENABLE_SA_KEY         ""   -D_ANSC_AES_USED_ -D_COSA_INTEL_USG_ATOM_ -D_COSA_FOR_COMCAST_ -D_NO_EXECINFO_H_ -DFEATURE_SUPPORT_SYSLOG            -DBUILD_WEB -D_NO_ANSC_ZLIB_"" -D_DEBUG -U_ANSC_IPV6_COMPATIBLE_ -D_ENABLE_BAND_STEERING_ -DUSE_NOTIFY_COMPONENT -D_BEACONRATE_SUPPORT            -DDUAL_CORE_XB3 -DINCLUDE_BREAKPAD -DUTC_ENABLE_ATOM -D_ATM_SUPPORT -D_COSA_SIM_         -I=/usr/include/dbus-1.0     -I=/usr/lib/dbus-1.0/include     -I=/usr/include/ccsp     " LDFLAGS="-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -lrdkloggers -lbreakpadwrapper -lpthread -ldl -lstdc++" 
		make install
	;;
	"ccsp-psm")
		git clone https://$1@gerrit.teamccp.com/a/rdk/rdkb/components/opensource/ccsp/CcspPsm/generic ccsp-psm
		cd ccsp-psm
		autoreconf -i
		./configure --build=i686-linux --host=i586-rdk-linux --target=i586-rdk-linux --prefix=/build-qemux86broadband/source/ccsp-psm/image/usr --exec_prefix=/build-qemux86broadband/source/ccsp-psm/image/usr --bindir=/build-qemux86broadband/source/ccsp-psm/image/usr/bin --sbindir=/build-qemux86broadband/source/ccsp-psm/image/usr/sbin --libexecdir=/build-qemux86broadband/source/ccsp-psm/image/usr/lib/ccsp-common-library --datadir=/build-qemux86broadband/source/ccsp-psm/image/usr/share --sysconfdir=/build-qemux86broadband/source/ccsp-psm/image/etc --sharedstatedir=/build-qemux86broadband/source/ccsp-psm/image/com --localstatedir=/build-qemux86broadband/source/ccsp-psm/image/var --libdir=/build-qemux86broadband/source/ccsp-psm/image/usr/lib --includedir=/build-qemux86broadband/source/ccsp-psm/image/usr/include --oldincludedir=/build-qemux86broadband/source/ccsp-psm/image/usr/include --infodir=/build-qemux86broadband/source/ccsp-psm/image/usr/share/info --mandir=/build-qemux86broadband/source/ccsp-psm/image/usr/share/man --disable-silent-rules --disable-dependency-tracking
		cp -fr source-pc/ssp_HAL_apis.c source/Ssp/psm_hal_apis.c
		make CFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types -DFEATURE_SUPPORT_RDKLOG -I=/usr/include/breakpad   -D_COSA_HAL_ -U_COSA_SIM_ -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-strict-aliasing            -DCONFIG_SYSTEM_MOCA -D_ANSC_LINUX -D_ANSC_USER -D_ANSC_LITTLE_ENDIAN_ -D_CCSP_CWMP_TCP_CONNREQ_HANDLER            -D_DSLH_STUN_ -D_NO_PKI_KB5_SUPPORT -D_BBHM_SSE_FILE_IO -D_ANSC_USE_OPENSSL_ -DENABLE_SA_KEY            -D_ANSC_AES_USED_ -D_COSA_INTEL_USG_ATOM_ -D_COSA_FOR_COMCAST_ -D_NO_EXECINFO_H_ -DFEATURE_SUPPORT_SYSLOG            -DBUILD_WEB -D_NO_ANSC_ZLIB_ -D_DEBUG -U_ANSC_IPV6_COMPATIBLE_ -D_ENABLE_BAND_STEERING_ -DUSE_NOTIFY_COMPONENT -D_BEACONRATE_SUPPORT            -DDUAL_CORE_XB3 -DINCLUDE_BREAKPAD -DUTC_ENABLE_ATOM -D_ATM_SUPPORT -D_COSA_SIM_         -I=/usr/include/dbus-1.0     -I=/usr/lib/dbus-1.0/include     -I=/usr/include/ccsp     " LDFLAGS="-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -lrdkloggers -lbreakpadwrapper -lpthread -lstdc++     -ldbus-1   -ldl  " 
		make install
	;;
	"ccsp-p-and-m")
		git clone https://$1@gerrit.teamccp.com/a/rdk/rdkb/components/opensource/ccsp/CcspPandM/generic ccsp-p-and-m
		cd ccsp-p-and-m
		autoreconf -i
		./configure --build=i686-linux --host=i586-rdk-linux --target=i586-rdk-linux --prefix=/build-qemux86broadband/source/ccsp-p-n-m/image/usr --exec_prefix=/build-qemux86broadband/source/ccsp-p-n-m/image/usr --bindir=/build-qemux86broadband/source/ccsp-p-n-m/image/usr/bin --sbindir=/build-qemux86broadband/source/ccsp-p-n-m/image/usr/sbin --libexecdir=/build-qemux86broadband/source/ccsp-p-n-m/image/usr/lib/ccsp-common-library --datadir=/build-qemux86broadband/source/ccsp-p-n-m/image/usr/share --sysconfdir=/build-qemux86broadband/source/ccsp-p-n-m/image/etc --sharedstatedir=/build-qemux86broadband/source/ccsp-p-n-m/image/com --localstatedir=/build-qemux86broadband/source/ccsp-p-n-m/image/var --libdir=/build-qemux86broadband/source/ccsp-p-n-m/image/usr/lib --includedir=/build-qemux86broadband/source/ccsp-p-n-m/image/usr/include --oldincludedir=/build-qemux86broadband/source/ccsp-p-n-m/image/usr/include --infodir=/build-qemux86broadband/source/ccsp-p-n-m/image/usr/share/info --mandir=/build-qemux86broadband/source/ccsp-p-n-m/image/usr/share/man --disable-silent-rules --disable-dependency-tracking --with-ccsp-platform=pc --with-ccsp-arch=pc
		make CFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types -DFEATURE_SUPPORT_RDKLOG -I=/usr/include/breakpad   -D_COSA_HAL_ -U_COSA_SIM_ -fno-exceptions -ffunctio""n-sections -fdata-sections -fomit-frame-pointer -fno-strict-aliasing            -DCONFIG_SYSTEM_MOCA -D_ANSC_LINUX -D_ANSC_USER -D_ANSC_LITTLE_ENDIA""N_ -D_CCSP_CWMP_TCP_CONNREQ_HANDLER            -D_DSLH_STUN_ -D_NO_PKI_KB5_SUPPORT -D_BBHM_SSE_FILE_IO -D_ANSC_USE_OPENSSL_ -DENABLE_SA_KEY         ""   -D_ANSC_AES_USED_ -D_COSA_INTEL_USG_ATOM_ -D_COSA_FOR_COMCAST_ -D_NO_EXECINFO_H_ -DFEATURE_SUPPORT_SYSLOG            -DBUILD_WEB -D_NO_ANSC_ZLIB_"" -D_DEBUG -U_ANSC_IPV6_COMPATIBLE_ -D_ENABLE_BAND_STEERING_ -DUSE_NOTIFY_COMPONENT -D_BEACONRATE_SUPPORT            -DDUAL_CORE_XB3 -DINCLUDE_BREAKPAD -DUTC_ENABLE_ATOM -D_ATM_SUPPORT -D_COSA_SIM_  -DCONFIG_VENDOR_CUSTOMER_COMCAST -DCONFIG_INTERNET2.0 -DCONFIG_CISCO_HOTSPOT -I=/usr/include/dbus-1.0     -I=/usr/lib/dbus-1.0/include -I=/usr/include/ccsp -I/usr/include/utctx -I/usr/include/utapi -I/usr/include/syscfg " LDFLAGS="-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -lrdkloggers -lbreakpadwrapper -lpthread -lstdc++     -ldbus-1     -lutctx     -lutapi          -lhal_m""somgmt     -lapi_dhcpv4c     -lfirewall_hal     -lhal_vlan     -lsyscfg     -lhal_platform  -llmapi -ldl -ltr181   "
		make install
	 ;;
	"ccsp-wifi-agent")
		git clone https://$1@gerrit.teamccp.com/a/rdk/rdkb/components/opensource/ccsp/CcspWifiAgent/generic ccsp-wifi-agent
		cd ccsp-wifi-agent
		autoreconf -i
		./configure --build=i686-linux --host=i586-rdk-linux --target=i586-rdk-linux --prefix=/build-qemux86broadband/source/ccsp-wifi-agent/image/usr --exec_prefix=/build-qemux86broadband/source/ccsp-wifi-agent/image/usr --bindir=/build-qemux86broadband/source/ccsp-wifi-agent/image/usr/bin --sbindir=/build-qemux86broadband/source/ccsp-wifi-agent/image/usr/sbin --libexecdir=/build-qemux86broadband/source/ccsp-wifi-agent/image/usr/lib/ccsp-common-library --datadir=/build-qemux86broadband/source/ccsp-wifi-agent/image/usr/share --sysconfdir=/build-qemux86broadband/source/ccsp-wifi-agent/image/etc --sharedstatedir=/build-qemux86broadband/source/ccsp-wifi-agent/image/com --localstatedir=/build-qemux86broadband/source/ccsp-wifi-agent/image/var --libdir=/build-qemux86broadband/source/ccsp-wifi-agent/image/usr/lib --includedir=/build-qemux86broadband/source/ccsp-wifi-agent/image/usr/include --oldincludedir=/build-qemux86broadband/source/ccsp-wifi-agent/image/usr/include --infodir=/build-qemux86broadband/source/ccsp-wifi-agent/image/usr/share/info --mandir=/build-qemux86broadband/source/ccsp-wifi-agent/image/usr/share/man --disable-silent-rules --disable-dependency-tracking --with-ccsp-platform=pc --with-ccsp-arch=pc
		make CFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types -DFEATURE_SUPPORT_RDKLOG -I=/usr/include/breakpad   -D_COSA_HAL_ -U_COSA_SIM_ -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-strict-aliasing            -DCONFIG_SYSTEM_MOCA -D_ANSC_LINUX -D_ANSC_USER -D_ANSC_LITTLE_ENDIAN_ -D_CCSP_CWMP_TCP_CONNREQ_HANDLER            -D_DSLH_STUN_ -D_NO_PKI_KB5_SUPPORT -D_BBHM_SSE_FILE_IO -D_ANSC_USE_OPENSSL_ -DENABLE_SA_KEY            -D_ANSC_AES_USED_ -D_COSA_INTEL_USG_ATOM_ -D_COSA_FOR_COMCAST_ -D_NO_EXECINFO_H_ -DFEATURE_SUPPORT_SYSLOG            -DBUILD_WEB -D_NO_ANSC_ZLIB_ -D_DEBUG -U_ANSC_IPV6_COMPATIBLE_ -D_ENABLE_BAND_STEERING_ -DUSE_NOTIFY_COMPONENT -D_BEACONRATE_SUPPORT            -DDUAL_CORE_XB3 -DINCLUDE_BREAKPAD -DUTC_ENABLE_ATOM -D_ATM_SUPPORT -D_COSA_SIM_         -I/usr/include/dbus-1.0     -I/usr/lib/dbus-1.0/include     -I/usr/include/ccsp      " LDFLAGS="-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -lrdkloggers -lbreakpadwrapper -lpthread -lstdc++     -ldbus-1          -lhal_wifi   -ldl  "
		make install
	 ;;
	"ccsp-lm-lite")
		git clone https://$1@gerrit.teamccp.com/a/rdk/rdkb/components/opensource/ccsp/CcspLMLite/generic ccsp-lm-lite
		cd ccsp-lm-lite
		autoreconf -i
		./configure --build=i686-linux --host=i586-rdk-linux --target=i586-rdk-linux --prefix=/build-qemux86broadband/source/ccsp-lm-lite/image/usr --exec_prefix=/build-qemux86broadband/source/ccsp-lm-lite/image/usr --bindir=/build-qemux86broadband/source/ccsp-lm-lite/image/usr/bin --sbindir=/build-qemux86broadband/source/ccsp-lm-lite/image/usr/sbin --libexecdir=/build-qemux86broadband/source/ccsp-lm-lite/image/usr/lib/ccsp-common-library --datadir=/build-qemux86broadband/source/ccsp-lm-lite/image/usr/share --sysconfdir=/build-qemux86broadband/source/ccsp-lm-lite/image/etc --sharedstatedir=/build-qemux86broadband/source/ccsp-lm-lite/image/com --localstatedir=/build-qemux86broadband/source/ccsp-lm-lite/image/var --libdir=/build-qemux86broadband/source/ccsp-lm-lite/image/usr/lib --includedir=/build-qemux86broadband/source/ccsp-lm-lite/image/usr/include --oldincludedir=/build-qemux86broadband/source/ccsp-lm-lite/image/usr/include --infodir=/build-qemux86broadband/source/ccsp-lm-lite/image/usr/share/info --mandir=/build-qemux86broadband/source/ccsp-lm-lite/image/usr/share/man --disable-silent-rules --disable-dependency-tracking --with-ccsp-platform=pc --with-ccsp-arch=pc
		make CFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types -DFEATURE_SUPPORT_RDKLOG      -I/usr/include/idbus-1.0     -I/usr/include/libxml2     -I/usr/lib/dbus-1.0/include     -I/usr/include/ccsp     -I/usr/include/mlt      -I=/usr/include/breakpad   -D_COSA_HAL_ -U_COSA_SIM_ -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-strict-aliasing            -D_ANSC_LINUX -D_ANSC_USER -D_ANSC_LITTLE_ENDIAN_ -D_CCSP_CWMP_TCP_CONNREQ_HANDLER            -D_DSLH_STUN_ -D_NO_PKI_KB5_SUPPORT -D_BBHM_SSE_FILE_IO -D_ANSC_USE_OPENSSL_ -DENABLE_SA_KEY            -D_ANSC_AES_USED_ -D_COSA_INTEL_USG_ATOM_ -D_COSA_FOR_COMCAST_ -D_NO_EXECINFO_H_ -DFEATURE_SUPPORT_SYSLOG            -DBUILD_WEB -D_NO_ANSC_ZLIB_ -D_DEBUG -U_ANSC_IPV6_COMPATIBLE_ -D_ENABLE_BAND_STEERING_ -DUSE_NOTIFY_COMPONENT -D_BEACONRATE_SUPPORT            -DDUAL_CORE_XB3 -DINCLUDE_BREAKPAD -DUTC_ENABLE_ATOM -D_ATM_SUPPORT -D_COSA_SIM_            "  LDFLAGS="-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -lrdkloggers -lbreakpadwrapper -lpthread -lstdc++     -lcurl     -lxml2 -ldl"
		make install
	;;
	"ccsp-hotspot")
		git clone https://$1@gerrit.teamccp.com/a/rdk/rdkb/components/opensource/ccsp/hotspot/generic ccsp-hotspot
		cd ccsp-hotspot
		autoreconf -i
		./configure --build=i686-linux --host=i586-rdk-linux --target=i586-rdk-linux --prefix=/build-qemux86broadband/source/ccsp-hotspot/image/usr --exec_prefix=/build-qemux86broadband/source/ccsp-hotspot/image/usr --bindir=/build-qemux86broadband/source/ccsp-hotspot/image/usr/bin --sbindir=/build-qemux86broadband/source/ccsp-hotspot/image/usr/sbin --libexecdir=/build-qemux86broadband/source/ccsp-hotspot/image/usr/lib/ccsp-common-library --datadir=/build-qemux86broadband/source/ccsp-hotspot/image/usr/share --sysconfdir=/build-qemux86broadband/source/ccsp-hotspot/image/etc --sharedstatedir=/build-qemux86broadband/source/ccsp-hotspot/image/com --localstatedir=/build-qemux86broadband/source/ccsp-hotspot/image/var --libdir=/build-qemux86broadband/source/ccsp-hotspot/image/usr/lib --includedir=/build-qemux86broadband/source/ccsp-hotspot/image/usr/include --oldincludedir=/build-qemux86broadband/source/ccsp-hotspot/image/usr/include --infodir=/build-qemux86broadband/source/ccsp-hotspot/image/usr/share/info --mandir=/build-qemux86broadband/source/ccsp-hotspot/image/usr/share/man --disable-silent-rules --disable-dependency-tracking --with-ccsp-platform=pc --with-ccsp-arch=pc
		make CFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types -DFEATURE_SUPPORT_RDKLOG     -I/usr/include/dbus-1.0    -I/usr/lib/dbus-1.0/include    -I/usr/include/ccsp      -D_COSA_HAL_ -U_COSA_SIM_ -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-strict-aliasing            -DCONFIG_SYSTEM_MOCA -D_ANSC_LINUX -D_ANSC_USER -D_ANSC_LITTLE_ENDIAN_ -D_CCSP_CWMP_TCP_CONNREQ_HANDLER            -D_DSLH_STUN_ -D_NO_PKI_KB5_SUPPORT -D_BBHM_SSE_FILE_IO -D_ANSC_USE_OPENSSL_ -DENABLE_SA_KEY            -D_ANSC_AES_USED_ -D_COSA_INTEL_USG_ATOM_ -D_COSA_FOR_COMCAST_ -D_NO_EXECINFO_H_ -DFEATURE_SUPPORT_SYSLOG            -DBUILD_WEB -D_NO_ANSC_ZLIB_ -D_DEBUG -U_ANSC_IPV6_COMPATIBLE_ -D_ENABLE_BAND_STEERING_ -DUSE_NOTIFY_COMPONENT -D_BEACONRATE_SUPPORT            -DDUAL_CORE_XB3 -DINCLUDE_BREAKPAD -DUTC_ENABLE_ATOM -D_ATM_SUPPORT -D_COSA_SIM_    "  LDFLAGS="-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -lrdkloggers -ldl"
		make install
	;;
	"ccsp-snmp-pa")
		git clone https://$1@gerrit.teamccp.com/a/rdk/rdkb/components/opensource/ccsp/CcspSnmpPa/generic ccsp-snmp-pa
		cd ccsp-snmp-pa
		autoreconf -i
		./configure --build=i686-linux --host=i586-rdk-linux --target=i586-rdk-linux --prefix=/build-qemux86broadband/source/ccsp-snmp-pa/image/usr --exec_prefix=/build-qemux86broadband/source/ccsp-snmp-pa/image/usr --bindir=/build-qemux86broadband/source/ccsp-snmp-pa/image/usr/bin --sbindir=/build-qemux86broadband/source/ccsp-snmp-pa/image/usr/sbin --libexecdir=/build-qemux86broadband/source/ccsp-snmp-pa/image/usr/lib/ccsp-common-library --datadir=/build-qemux86broadband/source/ccsp-snmp-pa/image/usr/share --sysconfdir=/build-qemux86broadband/source/ccsp-snmp-pa/image/etc --sharedstatedir=/build-qemux86broadband/source/ccsp-snmp-pa/image/com --localstatedir=/build-qemux86broadband/source/ccsp-snmp-pa/image/var --libdir=/build-qemux86broadband/source/ccsp-snmp-pa/image/usr/lib --includedir=/build-qemux86broadband/source/ccsp-snmp-pa/image/usr/include --oldincludedir=/build-qemux86broadband/source/ccsp-snmp-pa/image/usr/include --infodir=/build-qemux86broadband/source/ccsp-snmp-pa/image/usr/share/info --mandir=/build-qemux86broadband/source/ccsp-snmp-pa/image/usr/share/man --disable-silent-rules --disable-dependency-tracking 
		make CFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types -DFEATURE_SUPPORT_RDKLOG  -D_COSA_HAL_ -U_COSA_SIM_ -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-strict-aliasing            -DCONFIG_SYSTEM_MOCA -D_ANSC_LINUX -D_ANSC_USER -D_ANSC_LITTLE_ENDIAN_ -D_CCSP_CWMP_TCP_CONNREQ_HANDLER            -D_DSLH_STUN_ -D_NO_PKI_KB5_SUPPORT -D_BBHM_SSE_FILE_IO -D_ANSC_USE_OPENSSL_ -DENABLE_SA_KEY            -D_ANSC_AES_USED_ -D_COSA_INTEL_USG_ATOM_ -D_COSA_FOR_COMCAST_ -D_NO_EXECINFO_H_ -DFEATURE_SUPPORT_SYSLOG            -DBUILD_WEB -D_NO_ANSC_ZLIB_ -D_DEBUG -U_ANSC_IPV6_COMPATIBLE_ -D_ENABLE_BAND_STEERING_ -DUSE_NOTIFY_COMPONENT -D_BEACONRATE_SUPPORT            -DDUAL_CORE_XB3 -DINCLUDE_BREAKPAD -DUTC_ENABLE_ATOM -D_ATM_SUPPORT -D_COSA_SIM_         -I=/usr/include/dbus-1.0     -I=/usr/lib/dbus-1.0/include     -I=/usr/include/ccsp     " LDFLAGS="-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -lrdkloggers     -ldbus-1  -lbreakpadwrapper  -ldl  "
		make install
	;;
	"ccsp-tr069-pa")
		git clone https://$1@gerrit.teamccp.com/a/rdk/rdkb/components/opensource/ccsp/CcspTr069Pa/generic ccsp-tr069-pa
		cd ccsp-tr069-pa
		autoreconf -i
		./configure --build=i686-linux --host=i586-rdk-linux --target=i586-rdk-linux --prefix=/build-qemux86broadband/source/ccsp-tr069-pa/image/usr --exec_prefix=/build-qemux86broadband/source/ccsp-tr069-pa/image/usr --bindir=/build-qemux86broadband/source/ccsp-tr069-pa/image/usr/bin --sbindir=/build-qemux86broadband/source/ccsp-tr069-pa/image/usr/sbin --libexecdir=/build-qemux86broadband/source/ccsp-tr069-pa/image/usr/lib/ccsp-common-library --datadir=/build-qemux86broadband/source/ccsp-tr069-pa/image/usr/share --sysconfdir=/build-qemux86broadband/source/ccsp-tr069-pa/image/etc --sharedstatedir=/build-qemux86broadband/source/ccsp-tr069-pa/image/com --localstatedir=/build-qemux86broadband/source/ccsp-tr069-pa/image/var --libdir=/build-qemux86broadband/source/ccsp-tr069-pa/image/usr/lib --includedir=/build-qemux86broadband/source/ccsp-tr069-pa/image/usr/include --oldincludedir=/build-qemux86broadband/source/ccsp-tr069-pa/image/usr/include --infodir=/build-qemux86broadband/source/ccsp-tr069-pa/image/usr/share/info --mandir=/build-qemux86broadband/source/ccsp-tr069-pa/image/usr/share/man --disable-silent-rules --disable-dependency-tracking --with-ccsp-arch=pc
		make CFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types -DFEATURE_SUPPORT_RDKLOG -I=/usr/include/breakpad   -D_COSA_HAL_ -U_COSA_SIM_ -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-strict-aliasing            -DCONFIG_SYSTEM_MOCA -D_ANSC_LINUX -D_ANSC_USER -D_ANSC_LITTLE_ENDIAN_ -D_CCSP_CWMP_TCP_CONNREQ_HANDLER            -D_DSLH_STUN_ -D_NO_PKI_KB5_SUPPORT -D_BBHM_SSE_FILE_IO -D_ANSC_USE_OPENSSL_ -DENABLE_SA_KEY            -D_ANSC_AES_USED_ -D_COSA_INTEL_USG_ATOM_ -D_COSA_FOR_COMCAST_ -D_NO_EXECINFO_H_ -DFEATURE_SUPPORT_SYSLOG            -DBUILD_WEB -D_NO_ANSC_ZLIB_ -D_DEBUG -U_ANSC_IPV6_COMPATIBLE_ -D_ENABLE_BAND_STEERING_ -DUSE_NOTIFY_COMPONENT -D_BEACONRATE_SUPPORT            -DDUAL_CORE_XB3 -DINCLUDE_BREAKPAD -DUTC_ENABLE_ATOM -D_ATM_SUPPORT -D_COSA_SIM_         -I=/usr/include/dbus-1.0     -I=/usr/lib/dbus-1.0/include     -I=/usr/include/ccsp     -I=/usr/include/syscfg     " LDFLAGS="-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -lrdkloggers -lbreakpadwrapper -lpthread -lstdc++     -ldbus-1    -ldl "
		make install
	;;
	"hal")
		git clone https://$1@gerrit.teamccp.com/a/rdk/rdkb/components/opensource/ccsp/hal/generic hal
		cd hal
		autoreconf -i
		./configure --build=i686-linux --host=i586-rdk-linux --target=i586-rdk-linux --prefix=/build-qemux86broadband/source/hal/image/usr --exec_prefix=/build-qemux86broadband/source/hal/image/usr --bindir=/build-qemux86broadband/source/hal/image/usr/bin --sbindir=/build-qemux86broadband/source/hal/image/usr/sbin --libexecdir=/build-qemux86broadband/source/hal/image/usr/lib/ccsp-common-library --datadir=/build-qemux86broadband/source/hal/image/usr/share --sysconfdir=/build-qemux86broadband/source/hal/image/etc --sharedstatedir=/build-qemux86broadband/source/hal/image/com --localstatedir=/build-qemux86broadband/source/hal/image/var --libdir=/build-qemux86broadband/source/hal/image/usr/lib --includedir=/build-qemux86broadband/source/hal/image/usr/include --oldincludedir=/build-qemux86broadband/source/hal/image/usr/include --infodir=/build-qemux86broadband/source/hal/image/usr/share/info --mandir=/build-qemux86broadband/source/hal/image/usr/share/man --disable-silent-rules --disable-dependency-tracking --with-ccsp-arch=pc
		make CFLAGS="-I/include -O2 -pipe -g -feliminate-unused-debug-types        -I/usr/include/ccsp          " LDFLAGS="-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed"
		make install
	;;
	"utopia")
		git clone https://$1@gerrit.teamccp.com/a/rdk/rdkb/components/opensource/ccsp/Utopia/generic utopia
		cd utopia
		autoreconf -i
		./configure --build=i686-linux --host=i586-rdk-linux --target=i586-rdk-linux --prefix=/build-qemux86broadband/source/utopia/image/usr --exec_prefix=/build-qemux86broadband/source/utopia/image/usr --bindir=/build-qemux86broadband/source/utopia/image/usr/bin --sbindir=/build-qemux86broadband/source/utopia/image/usr/sbin --libexecdir=/build-qemux86broadband/source/utopia/image/usr/lib/ccsp-common-library --datadir=/build-qemux86broadband/source/utopia/image/usr/share --sysconfdir=/build-qemux86broadband/source/utopia/image/etc --sharedstatedir=/build-qemux86broadband/source/utopia/image/com --localstatedir=/build-qemux86broadband/source/utopia/image/var --libdir=/build-qemux86broadband/source/utopia/image/usr/lib --includedir=/build-qemux86broadband/source/utopia/image/usr/include --oldincludedir=/build-qemux86broadband/source/utopia/image/usr/include --infodir=/build-qemux86broadband/source/utopia/image/usr/share/info --mandir=/build-qemux86broadband/source/utopia/image/usr/share/man --disable-silent-rules --disable-dependency-tracking 
		make CFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types -DFEATURE_SUPPORT_RDKLOG      -I/usr/include/ccsp     -DCONFIG_BUILD_TRIGGER      -I=/usr/include/breakpad   -D_COSA_HAL_ -U_COSA_SIM_ -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-strict-aliasing            -DCONFIG_SYSTEM_MOCA -D_ANSC_LINUX -D_ANSC_USER -D_ANSC_LITTLE_ENDIAN_ -D_CCSP_CWMP_TCP_CONNREQ_HANDLER            -D_DSLH_STUN_ -D_NO_PKI_KB5_SUPPORT -D_BBHM_SSE_FILE_IO -D_ANSC_USE_OPENSSL_ -DENABLE_SA_KEY            -D_ANSC_AES_USED_ -D_COSA_INTEL_USG_ATOM_ -D_COSA_FOR_COMCAST_ -D_NO_EXECINFO_H_ -DFEATURE_SUPPORT_SYSLOG            -DBUILD_WEB -D_NO_ANSC_ZLIB_ -D_DEBUG -U_ANSC_IPV6_COMPATIBLE_ -D_ENABLE_BAND_STEERING_ -DUSE_NOTIFY_COMPONENT -D_BEACONRATE_SUPPORT            -DDUAL_CORE_XB3 -DINCLUDE_BREAKPAD -DUTC_ENABLE_ATOM -D_ATM_SUPPORT -D_COSA_SIM_      "  LDFLAGS="-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -lrdkloggers -lbreakpadwrapper -lpthread -lstdc++ -ldl"
		make install
	;;
	"ccsp-webui")
		git clone https://$1@gerrit.teamccp.com/rdk/rdkb/components/opensource/ccsp/webui/generic ccsp-webui
		cd ccsp-webui/source/CcspPhpExtension
		phpize
		./configure --build=i686-linux --host=i586-rdk-linux --target=i586-rdk-linux --prefix=/build-qemux86broadband/source/ccsp-webui/image/usr --exec_prefix=/build-qemux86broadband/source/ccsp-webui/image/usr --bindir=/build-qemux86broadband/source/ccsp-webui/image/usr/bin --sbindir=/build-qemux86broadband/source/ccsp-webui/image/usr/sbin --libexecdir=/build-qemux86broadband/source/ccsp-webui/image/usr/lib/ccsp-common-library --datadir=/build-qemux86broadband/source/ccsp-webui/image/usr/share --sysconfdir=/build-qemux86broadband/source/ccsp-webui/image/etc --sharedstatedir=/build-qemux86broadband/source/ccsp-webui/image/com --localstatedir=/build-qemux86broadband/source/ccsp-webui/image/var --libdir=/build-qemux86broadband/source/ccsp-webui/image/usr/lib --includedir=/build-qemux86broadband/source/ccsp-webui/image/usr/include --oldincludedir=/build-qemux86broadband/source/ccsp-webui/image/usr/include --infodir=/build-qemux86broadband/source/ccsp-webui/image/usr/share/info --mandir=/build-qemux86broadband/source/ccsp-webui/image/usr/share/man --disable-silent-rules --disable-dependency-tracking --enable-cosa CCSP_COMMON_LIB=/usr/lib
		make CFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types -DFEATURE_SUPPORT_RDKLOG      -I/usr/include/dbus-1.0     -I/usr/lib/dbus-1.0/include     -I/usr/include/ccsp     -fPIC       -D_COSA_HAL_ -U_COSA_SIM_ -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-strict-aliasing            -DCONFIG_SYSTEM_MOCA -D_ANSC_LINUX -D_ANSC_USER -D_ANSC_LITTLE_ENDIAN_ -D_CCSP_CWMP_TCP_CONNREQ_HANDLER            -D_DSLH_STUN_ -D_NO_PKI_KB5_SUPPORT -D_BBHM_SSE_FILE_IO -D_ANSC_USE_OPENSSL_ -DENABLE_SA_KEY            -D_ANSC_AES_USED_ -D_COSA_INTEL_USG_ATOM_ -D_COSA_FOR_COMCAST_ -D_NO_EXECINFO_H_ -DFEATURE_SUPPORT_SYSLOG            -DBUILD_WEB -D_NO_ANSC_ZLIB_ -D_DEBUG -U_ANSC_IPV6_COMPATIBLE_ -D_ENABLE_BAND_STEERING_ -DUSE_NOTIFY_COMPONENT -D_BEACONRATE_SUPPORT            -DDUAL_CORE_XB3 -DINCLUDE_BREAKPAD -DUTC_ENABLE_ATOM -D_ATM_SUPPORT -D_COSA_SIM_    " LDFLAGS="-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -lrdkloggers       -ldbus-1      -ldl"
		make install
	;;
	"parodus")
		mkdir build_parodus
		cd build_parodus
		git clone git://github.com/Comcast/parodus.git parodus
		cd parodus
		cp -fr CMakeLists.txt src tests ../
		cd ..
		sed -i 's/Werror/Wno-error/' CMakeLists.txt
		cd parodus
		cmake ..
		make
	;;
	"ccsp-webpa-adapter")
		git clone https://$1@gerrit.teamccp.com/a/rdk/rdkb/components/opensource/ccsp/CcspWebpaAdapter/generic ccsp-webpa-adapter
		cd ccsp-webpa-adapter
		autoreconf -i
		./configure --build=i686-linux --host=i586-rdk-linux --target=i586-rdk-linux --prefix=/build-qemux86broadband/source/webpa/image/usr --exec_prefix=/build-qemux86broadband/source/webpa/image/usr --bindir=/build-qemux86broadband/source/webpa/image/usr/bin --sbindir=/build-qemux86broadband/source/webpa/image/usr/sbin --libexecdir=/build-qemux86broadband/source/webpa/image/usr/lib/ccsp-common-library --datadir=/build-qemux86broadband/source/webpa/image/usr/share --sysconfdir=/build-qemux86broadband/source/webpa/image/etc --sharedstatedir=/build-qemux86broadband/source/webpa/image/com --localstatedir=/build-qemux86broadband/source/webpa/image/var --libdir=/build-qemux86broadband/source/webpa/image/usr/lib --includedir=/build-qemux86broadband/source/webpa/image/usr/include --oldincludedir=/build-qemux86broadband/source/webpa/image/usr/include --infodir=/build-qemux86broadband/source/webpa/image/usr/share/info --mandir=/build-qemux86broadband/source/webpa/image/usr/share/man --disable-silent-rules --disable-dependency-tracking --with-ccsp-arch=pc
		make CFLAGS=" -pipe -g -feliminate-unused-debug-types -Os -pipe  -DFEATURE_SUPPORT_RDKLOG  -I=/usr/include/breakpad   -D_COSA_HAL_ -U_COSA_SIM_ -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-strict-aliasing            -DCONFIG_SYSTEM_MOCA -D_ANSC_LINUX -D_ANSC_USER -D_ANSC_LITTLE_ENDIAN_ -D_CCSP_CWMP_TCP_CONNREQ_HANDLER            -D_DSLH_STUN_ -D_NO_PKI_KB5_SUPPORT -D_BBHM_SSE_FILE_IO -D_ANSC_USE_OPENSSL_ -DENABLE_SA_KEY            -D_ANSC_AES_USED_ -D_COSA_INTEL_USG_ATOM_ -D_COSA_FOR_COMCAST_ -D_NO_EXECINFO_H_ -DFEATURE_SUPPORT_SYSLOG            -DBUILD_WEB -D_NO_ANSC_ZLIB_ -D_DEBUG -U_ANSC_IPV6_COMPATIBLE_ -D_ENABLE_BAND_STEERING_ -DUSE_NOTIFY_COMPONENT -D_BEACONRATE_SUPPORT            -DDUAL_CORE_XB3 -DINCLUDE_BREAKPAD -DUTC_ENABLE_ATOM -D_ATM_SUPPORT -D_COSA_SIM_            -D_YOCTO_       -DPLATFORM_RDKB         -I/usr/include/ccsp  -I/usr/include/wdmp-c        -I/usr/include/libparodus" LDFLAGS="-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -lrdkloggers -lcjson -lmsgpackc -ltrower-base64 -lnanomsg -lcimplog -lwrp-c -lwdmp-c -llibparodus -lm -lpthread -lstdc++ -lbreakpadwrapper -ldl"
		make install
	;;
	"TestandDiagnostic")
		git clone https://$1@gerrit.teamccp.com/a/rdk/rdkb/components/opensource/ccsp/TestAndDiagnostic/generic TestAndDiagnostic
		cd TestAndDiagnostic
		autoreconf -i
		./configure --build=i686-linux --host=i586-rdk-linux --target=i586-rdk-linux --prefix=/build-qemux86broadband/source/TestAndDiagnostic/image/usr --exec_prefix=/build-qemux86broadband/source/TestAndDiagnostic/image/usr --bindir=/build-qemux86broadband/source/TestAndDiagnostic/image/usr/bin --sbindir=/build-qemux86broadband/source/TestAndDiagnostic/image/usr/sbin --libexecdir=/build-qemux86broadband/source/TestAndDiagnostic/image/usr/lib/ccsp-common-library --datadir=/build-qemux86broadband/source/TestAndDiagnostic/image/usr/share --sysconfdir=/build-qemux86broadband/source/TestAndDiagnostic/image/etc --sharedstatedir=/build-qemux86broadband/source/TestAndDiagnostic/image/com --localstatedir=/build-qemux86broadband/source/TestAndDiagnostic/image/var --libdir=/build-qemux86broadband/source/TestAndDiagnostic/image/usr/lib --includedir=/build-qemux86broadband/source/TestAndDiagnostic/image/usr/include --oldincludedir=/build-qemux86broadband/source/TestAndDiagnostic/image/usr/include --infodir=/build-qemux86broadband/source/TestAndDiagnostic/image/usr/share/info --mandir=/build-qemux86broadband/source/TestAndDiagnostic/image/usr/share/man --disable-silent-rules --disable-dependency-tracking --with-ccsp-arch=pc
		make CFLAGS="-pipe -g -feliminate-unused-debug-types -Os -pipe  -DFEATURE_SUPPORT_RDKLOG  -I=/usr/include/breakpad   -D_COSA_HAL_ -U_COSA_SIM_ -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-strict-aliasing            -DCONFIG_SYSTEM_MOCA -D_ANSC_LINUX -D_ANSC_USER -D_ANSC_LITTLE_ENDIAN_ -D_CCSP_CWMP_TCP_CONNREQ_HANDLER            -D_DSLH_STUN_ -D_NO_PKI_KB5_SUPPORT -D_BBHM_SSE_FILE_IO -D_ANSC_USE_OPENSSL_ -DENABLE_SA_KEY            -D_ANSC_AES_USED_ -D_COSA_INTEL_USG_ATOM_ -D_COSA_FOR_COMCAST_ -D_NO_EXECINFO_H_ -DFEATURE_SUPPORT_SYSLOG            -DBUILD_WEB -D_NO_ANSC_ZLIB_ -D_DEBUG -U_ANSC_IPV6_COMPATIBLE_ -D_ENABLE_BAND_STEERING_ -DUSE_NOTIFY_COMPONENT -D_BEACONRATE_SUPPORT            -DDUAL_CORE_XB3 -DINCLUDE_BREAKPAD -DUTC_ENABLE_ATOM -D_ATM_SUPPORT -D_COSA_SIM_         -I/usr/include     -I/usr/include/dbus-1.0     -I/usr/lib/dbus-1.0/include     -I/usr/include/ccsp     -I/usr/include/utapi     -I/usr/include/utctx     -I/usr/include/ulog     -I/usr/include/syscfg" LDFLAGS="-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -lrdkloggers -lbreakpadwrapper -lpthread -lstdc++     -ldbus-1 -ldl"
		make install
	;;
esac 	
}
echo "====================================================="
echo "********* List of ccsp-components are ***************"
echo "             1.ccsp-commonlib                        "
echo "             2.ccsp-cr                               "
echo "             3.ccsp-psm                              "
echo "             4.ccsp-p-and-m                          "               
echo "             5.ccsp-wifi-agent                       "
echo "             6.ccsp-lm-lite                          "
echo "             7.ccsp-hotspot                          "
echo "             8.ccsp-snmp-pa                          "
echo "             9.ccsp-tr069-pa                         "
echo "             10.hal                                  "
echo "             11.utopia                               "
echo "             12.ccsp-webui                           "
echo "             13.parodus                              "
echo "             14.ccsp-webap-adapter                   "
echo "             15.TestandDiagnostic                    "
echo "====================================================="

echo "====================================================="
echo " usage:sh bulid_ccsp_devscript.sh UserName CCSP_Component_Name"
echo "====================================================="


workspace_location="/build-qemux86broadband/source/"
mkdir -p $workspace_location
cd $workspace_location

execute_component $1 $2
