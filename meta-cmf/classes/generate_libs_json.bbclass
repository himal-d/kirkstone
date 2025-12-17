# If not stated otherwise in this file or this component's license file the
# following copyright and licenses apply:
#
# Copyright 2020 Liberty Global B.V.
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

## This bbclass generates a $MACHINE_libs.json file for use with
## BundleGenerator inside $DEPLOY_DIR_IMAGE
## This file helps BundleGenerator to choose between:
## 1. using a specific .so from inside an OCI image OR
## 2. mount binding that .so from the host instead
## For this it looks at what API versions the .so libs in this
## image provides.
## It also contains the shared library dependencies for each lib
## under node "deps".
##
## Excerpt of the generated json:
##{
##    "libs": [
##        {
##            "apiversions": [
##                "UUID_1.0",
##                "UUID_2.20",
##                "UUIDD_PRIVATE"
##            ],
##            "name": "lib/libuuid.so.1"
##            "deps": [
##                "libc.so.6",
##                "ld-linux-armhf.so.3"
##            ]
##        },
##        {
##            "apiversions": [
##                "GLIBC_2.4",
##                "GLIBC_2.5",
##                "GLIBC_2.6",
##                "GLIBC_2.7",
##                .....
##                "GLIBC_2.24",
##                "GLIBC_PRIVATE"
##            ],
##            "name": "lib/libc.so.6"
##            "deps": [
##                "ld-linux-armhf.so.3"
##            ]
##        }
##    ]
##}

ROOTFS_POSTPROCESS_COMMAND_append = "generate_libs_json ;"

def run_process_and_return_output(command):
    import subprocess, shlex
    """Runs the process with the specified command
    Will return the stdout of the process
    Args:
        command (string): Command with args to run
    Returns:
        int: Return code from the process
        string: stdout from the process
    """
    # Run the process
    process = subprocess.Popen(shlex.split(
        command), shell=False, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    out, err = process.communicate()

    # Process has finished, clean up and get the return code
    process.stdout.close()
    return_code = process.wait()
    return return_code, out.decode()

def retrieve_apiversions(libfullpath):
    """Retrieve version definitions from .so library
       using readelf binary

    Args:
        libfullpath (string): fullpath to .so library

    Returns:
        array[String]: version definitions. Empty [] when no result. None
                       when error (no ELF binary)
    """
    import os, re

    if not os.path.exists(libfullpath):
        return []

    apiversions = []
    command = "readelf -V {}".format(libfullpath)
    success, output = run_process_and_return_output(command)
    if success == 0:
        if "Not an ELF file" in output:
            return None
        in_version_definition_section = False
        for line in output.splitlines():
            if (in_version_definition_section):
                if ("Version needs section" in line):
                    in_version_definition_section = False
                else:
                    ## parses something like below to get out 'GLIBC_2.6' :
                    ## 0x005c: Rev: 1  Flags: none  Index: 4  Cnt: 2  Name: GLIBC_2.6
                    m = re.match(r"  0x.+Name: ([\w\d\.]+)", line)
                    if (m):
                        apiversions.append(m.groups()[0])
            elif ("Version definition section" in line):
                in_version_definition_section = True
    else:
        return None
    return apiversions

def retrieve_shared_libs_needed(libfullpath):
    """Retrieve needed shared libs from .so library
       using readelf binary

    Args:
        libfullpath (string): fullpath to .so library

    Returns:
        array[String]: needed shared libs. Empty [] when no result. None
                       when error (no ELF binary)
    """
    import os, re

    if not os.path.exists(libfullpath):
        return []

    sharedlibs = []
    command = "readelf -d {}".format(libfullpath)
    success, output = run_process_and_return_output(command)
    if success == 0:
        if "Not an ELF file" in output:
            return None
        ## parses something like below:
        ## 0x00000001 (NEEDED)                     Shared library: [libdvrmgr.so.0]
        for line in output.splitlines():
            m = re.match(r".*\(NEEDED\).+\[(\S+\.so\S*)\]", line)
            if (m):
                sharedlibs.append(m.groups()[0])
    else:
        return None

    return sharedlibs

python generate_libs_json() {
    import os.path
    import glob
    import re
    import json
    
    result = []
    libs_to_watch = [
        "/lib",
        "/usr/lib",
        ]
    rootfs = d.getVar('IMAGE_ROOTFS', 1)
    for dir_to_watch in libs_to_watch:
        for dir in glob.iglob(rootfs + dir_to_watch):
            for root, dirs, files in os.walk(dir):
                for file in files:
                    m = re.match(r"^\S+\.so\S*$", file)
                    if m:
                        fullpath = os.path.join(root, file)
                        ap = retrieve_apiversions(fullpath)
                        if ap is None:
                            continue
                        sharedlibs = retrieve_shared_libs_needed(fullpath)
                        if sharedlibs is None:
                            continue
                        fixed_sharedlibs = []
                        for lib in sharedlibs:
                            for possible_dir in libs_to_watch:
                                lib_with_path = possible_dir + '/' + lib
                                lib_fullpath = rootfs + lib_with_path
                                if (os.path.exists(lib_fullpath)):
                                    fixed_sharedlibs.append(lib_with_path)
                                    break
                        fixed_sharedlibs.sort()
                        result.append({ 'name': fullpath.replace(rootfs,''), 'apiversions' : ap, 'deps' : fixed_sharedlibs})
    
    result.sort(key=lambda x: x['name'])
    json_file = open(d.getVar('DEPLOY_DIR_IMAGE', 1) + "/" + d.getVar('MACHINE', 1) + "_libs.json", "w")
    json_file.write(json.dumps({ 'libs' : result}, indent=4, sort_keys=True))
    json_file.close()
}
