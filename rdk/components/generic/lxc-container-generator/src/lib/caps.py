################################################################################
# If not stated otherwise in this file or this component's Licenses.txt file the
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
################################################################################
import re
import subprocess
from . import dbg

################################################################################
#   class cCaps(object):
#
#       Represents info for CAPS container environment
#
################################################################################
class cCaps(object):
    def __init__(self, confOptsDict):
        self.enable = False
        self.confOptsDict = confOptsDict

    def isEnabled(self):
        return self.enable

    def isCapAlreadySet(self, confFile):
        isCapSet = False
        with open(confFile, "r") as conf_fd:
            for line in conf_fd:
                if line.find('lxc.cap.') == 0:
                    # let's honour caps difined by <CapDrop> and <CapKeep> in .xml
                    isCapSet = True
                    break
        conf_fd.close()
        return isCapSet

    def getCommonCaps(self):
        """Returns the string with common "lxc.cap.keep" entries.

        "dac_override setuid setgid sys_admin" are always kept too
        because they are needed to properly setup the container. Why?
        - dac_override: mount files inside container regardless of directory mode
        - setuid/setgid: drop to non-root UID/GID
        - sys_admin: mount filesystems inside in some containers, e.g.:
           - /proc in PINFO
           - tmpfs /dev/shm in DEVUPDATEPROXY, OEM_PLATFORM, PLATFORMCONTROL, POWER
           - tmpfs /var/run/irmgr_sockets in PLATFORMCONTROL
        """
        return "\n# ---- CAPS: auto-detected capabilities needed by this container ----\n" \
               "# clear the keep-list first with \"= none\"\n" \
               + self.confOptsDict['cap_keep'] + " = none\n" \
               "# always keep caps necessary to setup the container\n" \
               + self.confOptsDict['cap_keep'] + " = dac_override setuid setgid sys_admin\n" \
               "# list of caps for specific files follows (may be empty)\n"

    def getNonRootExecutableFilesList(self, confFile):
        capFiles = []
        with open(confFile, "r") as conf_fd:
            for line in conf_fd:
                if line.find('lxc.mount') != -1:
                    lexemes = line.split()
                    # find mount points without 'noexec' && 'nosuid'
                    if (lexemes[0].find(self.confOptsDict['mount_entry']) == 0 and
                        lexemes[5].find('noexec') == -1 and
                        lexemes[5].find('nosuid') == -1):
                        capFiles.append(lexemes[2])
        conf_fd.close()
        return capFiles

    def getXtablesMulti(self, oe_ver):
        XTABLES_MULTI = {
            '2.1': "/usr/sbin/xtables-multi",
            '2.2': "/usr/sbin/xtables-multi",
            '3.1': "/usr/sbin/xtables-legacy-multi",
        }
        try:
            ret = XTABLES_MULTI[oe_ver]
        except KeyError as e:
            raise Exception("[!!! ERROR !!!] unknown OE_VER: %s" % (oe_ver))
        return ret

    def runProcess(self, args, mode=None):
        try:
            if mode == "shell":
                result = subprocess.check_output(args, stderr=subprocess.PIPE, shell=True)
            else:
                result = subprocess.check_output(args, stderr=subprocess.PIPE)
        except subprocess.CalledProcessError as e:
            print(e.output)
            print(e)
            raise Exception("[!!! ERROR !!!] Subprocess call failed: cmd = \"%s\"" % (args))
        return result.decode().rstrip()

    def createCapsConf(self, rootfsPath, confFile, oe_ver):
        entry = ""
        self.enable = False

        if self.isCapAlreadySet(confFile) is False:
            entry += self.getCommonCaps()
            filesNeedCaps = self.getNonRootExecutableFilesList(confFile)
            if filesNeedCaps is not None:
                for filename in filesNeedCaps:
                    # /usr/bin/netflix is a directory containing /usr/bin/netflix/bin/netflix
                    if filename == "/usr/bin/netflix":
                        filename = "/usr/bin/netflix/bin/netflix"
                    # iptables-restore is a symbolic link to xtables-multi
                    if filename == "/usr/sbin/iptables-restore":
                        filename = self.getXtablesMulti(oe_ver)
                    # ip6tables-restore - same as above
                    if filename == "/usr/sbin/ip6tables-restore":
                        continue
                    # iptables-lxc-exec.sh is a wrapper for both above which must not introduce intermediate constraints for any caps
                    if filename == "/usr/sbin/iptables-lxc-exec.sh":
                        continue

                    dbg.logTrace(1, "Processing file: %s" % (filename))
                    fullPath = rootfsPath + filename
                    # get caps
                    cmd = "getcap \"" + fullPath + "\""
                    fileCapsRaw = self.runProcess(cmd, "shell")
                    if not fileCapsRaw:
                        raise Exception("[!!! ERROR !!!] File-capabilities are empty")
                    dbg.logTrace(1, "Capabilities: %s" % (fileCapsRaw))

                    # get only caps
                    cmd = "echo \"" + fileCapsRaw + "\" | sed -e 's/^[^=]*= //;'"
                    fileCapsWithSuffix = self.runProcess(cmd, "shell")
                    if not fileCapsWithSuffix:
                        raise Exception("[!!! ERROR !!!] Failed to extract capabilities from the string: %s" % (fileCapsRaw))
                    entry += "# " + filename + " = " + fileCapsWithSuffix + "\n"

                    # strip data
                    cmd = "echo \"" + fileCapsWithSuffix + "\" | sed 's/\<cap_//g; s/,/ /g; s/+.*//'"
                    shortNameCaps = self.runProcess(cmd, "shell")
                    if not shortNameCaps:
                        raise Exception("[!!! ERROR !!!] Failed to strip capabilities: %s " % (shortNameCaps))
                    entry += self.confOptsDict['cap_keep'] + " = " + shortNameCaps + "\n"
                self.enable = True
        else:
            dbg.logTrace(1, "CAPS are already set in container configuration")

        return entry
