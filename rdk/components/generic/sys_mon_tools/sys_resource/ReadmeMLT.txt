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
System Resource Memory Leak Tracer build and Run-time Instructions (ReadmeMLT.txt file)

1.	Build Instructions:
Identical to the System Resource Monitor library [see Readme.txt file in the current folder].
To compile in memory leak tracing functionality in the libsysResource.so library, set USE_SYS_RESOURCE_MLT environment variable to “y”:
export USE_SYS_RESOURCE_MLT=y
and recompile the library.
It'll enable the following compile symbols:
-DUSE_SYSRES_MLT=1 -DUSE_FILE_LINE_INFO=1 -DRETURN_ADDRESS_LEVEL=0
where
USE_SYSRES_MLT - compiles in MLT;
USE_FILE_LINE_INFO - compiles in file and line info of a potential memory leak;
RETURN_ADDRESS_LEVEL - configures return address level, default is 0.

2.	To compile in memory leak tracing functionality in the XRE NR: 
Edit http://mach.chalybs.net:8081/svn/excalibur/application/XRE/native_receiver/trunk/build/Receiver/Receiver.pro
file to include MLT support in the Receiver build by uncommenting out the lines:
DEFINES += USE_SYSRES_MLT=1		// compiles in MLT;
DEFINES += USE_FILE_LINE_INFO=1 	// compiles in file and line info of a potential memory leak.
and rebuild the XRE NR application.

3.	To compile in memory leak tracing functionality in the OCAP-RI, set USE_SYS_RESOURCE_MLT environment variable to “y”:
export USE_SYS_RESOURCE_MLT=y
additionaly, set USE_MPEMEDIATUNE_MLT to "y" to enable memory leak analysis for channel change operations:
export USE_MPEMEDIATUNE_MLT=y 
and rebuild the OCAP-RI stack.
Note: It is also possible to enable memory leak analysis for channel change operations via an export of the USE_IDLE_MLT:
export USE_IDLE_MLT=y
to make libsysResource.so library periodic analysis of memory consumption every designated period of time.
In such case,  USE_MPEMEDIATUNE_MLT should not be used [disabled] and the libsysResource.so library should be compiled with 
the exported "USE_IDLE_MLT=y".

The default MLT build options are:
-DUSE_SYSRES_MLT=1 -DUSE_FILE_LINE_INFO=1 -DRETURN_ADDRESS_LEVEL=0
[see above for the descriptions of the symbols]
-DMPE_FEATURE_MEM_PROF - enables OCAP-RI stack support to use file and line info of a potential memory leak.

4.	To run testSysResource and/or XRE NR and/or OCAP-RI with the libsysResource.so library services:
copy the testSysResource executable and libsysResource.so library to the target’s folder /mnt/nfs/bin/ 
and set a symbolic link /mnt/nfs/env/libsysResource.so to the library itself as
ln -s /mnt/nfs/bin/libsysResource.so /mnt/nfs/env/libsysResource.so
or edit LD_LIBRARY_PATH accordingly.

5.	To analyse memory leaks between different iterations [such as channel change ops], press F8 on an attached to STB usb keyboard
after every channel change [this is for XRE NR only, there is nothing to be done for the OCAP-RI stack].

6.	Regardless of the application used, as result of memory leak analysis on every repetition cycle 2 files are produced:
/opt/logs/<Process Name>MLT.txt  - contains distribution of all not deallocated objects within a repetition cycle;
/opt/logs/<Process Name>MLT2.txt - contains distribution of all not deallocated objects within a repetition cycle whose size [in bytes] 
increased comparing to the previous cycle.
