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
from . import dbg


################################################################################
#   class cCrashReporting(object):
#
#       Represents info for crashreporting container environment
#
################################################################################
class cCrashReporting(object):

    def __init__(self, confOptsDict):
        self.enable = False
        self.confOptsDict = confOptsDict

    def isEnabled(self):
        return self.enable

    def getLibCrashReporting(self):
        return "libcrashreporting"

    def getCrashDumpConfigPath(self):
        return "var/crashdumpconfig"

################################################################################
#
#        createCrashReportingConf(cCurrPath, crashReportingNode):
#
#                     uses information inside the <CrashReporting> element
#                     to generate lxc.conf file
#
################################################################################
    def createCrashReportingConf(self, config, rootfs, crashReportingNode):
        entry = ""
        isEnabled = False

        if (crashReportingNode is not None):
            enable = crashReportingNode.attrib["enable"]

            if enable == "true":
                # ONEM-7738 - Breakpad handler needs to follow Dump.enabled in CPE configuration file.
                entry += "\n# LXC bindings for crash config file\n"
                entry += self.confOptsDict['mount_entry'] + " = /%s %s none ro,bind,optional,nosuid,nodev 0 0\n" % (self.getCrashDumpConfigPath(), self.getCrashDumpConfigPath())
                config.createMountPoint("dir", self.getCrashDumpConfigPath(), None)

                isEnabled = True
            else:
                entry += "\n# Crash reporting disabled\n"

        self.enable = isEnabled

        return entry

    # TODO: ADD CORE DUMPS MOUNT BIND
    def setUp(self, config, rootfs, crashReportingNode, conf_fd):
        crashReportingInfo = self.createCrashReportingConf(config, rootfs, crashReportingNode)
        if crashReportingInfo is not None:
            conf_fd.write(crashReportingInfo)
