################################################################################
# If not stated otherwise in this file or this component's Licenses.txt file the
# following copyright and licenses apply:
#
# Copyright 2017 Liberty Global B.V.
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
#   class cDbus(object):
#
#       Represents info for dbus container environment
#
################################################################################
class cDbus(object):
    def __init__(self, rootfs, socketPath, confOptsDict):
        self.rootfs = rootfs
        self.enable = False
        self.socketPath = socketPath.strip("/")
        self.confOptsDict = confOptsDict

    def isEnabled(self):
        return self.enable

    def getSocketPath(self):
        return self.socketPath

    def getLibDbus(self):
        return "libdbus-1"

    def createDbusConf(self, config, dbusNode):
        entry = ""
        self.enable = False

        if dbusNode is not None:
            enable = dbusNode.attrib["enable"]
            if (enable == "true"):
                entry += "\n# LXC configuration for D-Bus\n"
                if not self.getSocketPath():
                    raise Exception("[!!! ERROR !!!] DBus option is set, but socket addr is empty. Check config.ini.")
                entry += self.confOptsDict['environment'] + " = DBUS_SESSION_BUS_ADDRESS=unix:path=/%s\n" % (self.getSocketPath())
                entry += self.confOptsDict['mount_entry'] + " = /%s %s none rw,bind,nosuid,nodev,noexec 0 0\n" % (self.getSocketPath(), self.getSocketPath())

                entry += "# Library: '%s' added with auto-found dependencies.\n" % self.getLibDbus()
                dbg.logTrace(1, "Installing libraries for D-Bus configuration")
                config.processLibBinding(self.getLibDbus())

                self.rootfs.createMountPointForFile(self.getSocketPath())
                self.enable = True
            else:
                entry = "\n# D-Bus disabled\n"

        return entry
