##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
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
System Resource Monitor Build and Run-time Instructions (Readme.txt file)

1.	Build Instructions:
1.1.	Set CANMORE_SDK environment variable to point to Intel SDK toolchain;
1.2.	Change directory to the root directory of the SysResource utility:
http://mach.chalybs.net:8081/svn/vendor/ParkerSI/trunk/SysApps/SysResource
1.3.	Build the libsysResource.so library:
make clean
make
The library is output in the http://mach.chalybs.net:8081/svn/vendor/ParkerSI/trunk/SysApps/SysResource/lib
1.4.	Set ParkerSI_ROOT environment variable to point to the root directory of the SysResource utility:
[as for example:  export ParkerSI_ROOT=/media/linuxData/Codebase/svn/vendor/ParkerSI/trunk]
to be used with applications such as XRE NR and/or OCAP-RI to monitor system resource usage.
1.5.	SysResource utility can be used to make periodic analysis of memory consumption every designated period of time
regardless of operations performed. In this case, USE_IDLE_MLT environment variable should be exported:
export USE_IDLE_MLT=y
and the libsysResource.so library should be re-compiled.
Note:	Usage of the USE_IDLE_MLT in the libsysResource.so & USE_MPEMEDIATUNE_MLT in the OCAP-RI stack is mutually 
exclusive for memory leak tracing.

2.	To include the libsysResource.so library in the XRE NR: 
Edit http://mach.chalybs.net:8081/svn/excalibur/application/XRE/native_receiver/trunk/build/Receiver/Receiver.pro
file to include the library in the Receiver build by uncommenting out the line:
DEFINES += SYS_RESOURCE_MONITOR
and rebuild the XRE NR application.

3.	To include the libsysResource.so library in the OCAP-RI set USE_SYS_RESOURCE_MON environment variable to the “y”:
export USE_SYS_RESOURCE_MON=y
and rebuild the OCAP-RI stack.

4.	To run XRE NR and/or OCAP-RI with the libsysResource.so library services:
copy the libsysResource.so library to the target’s folder /mnt/nfs/bin/ 
and set a symbolic link /mnt/nfs/env/libsysResource.so to the library itself as
ln -s /mnt/nfs/bin/libsysResource.so /mnt/nfs/env/libsysResource.so
or edit LD_LIBRARY_PATH accordingly.

5.	If libsysResource.so library properly built and set, 
the OCAP-RI/XRE NR apps produce output similar to below:
Jun 17 16:54:36 2010 [1969:mpeos-main]: total = 00644188KB[629MB] arena = 03055616[02984KB][02MB] 
ford = 00244656[00238KB][00MB] uord = 02810960[02745KB][02MB] hblkh= 78479360[76640KB][74MB] 
Jun 17 16:57:53 2010 [2198:Receiver]: total = 00644188KB[629MB] arena = 00135168[00132KB][00MB] 
ford = 00032736[00031KB][00MB] uord = 00102432[00100KB][00MB] hblkh= 00000000[00000KB][00MB]

