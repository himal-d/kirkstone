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
import os
import re
import json
from . import dbg
from .dbus import cDbus
from .cgroup import cCgroup
from .crash_reporting import cCrashReporting
from .caps import cCaps
import xml.etree.ElementTree as ET
from .sanity_check import cSanityCheck
from .logging import cLog


################################################################################
#   class cConfig(object):
#
#       Represents container configuration,
#       implements basic functionalities to generate lxc.conf.
#
################################################################################
class cConfig(object):
    def __init__(self, sanityCheck, rootfs, privileged, crashReporting, append, prevUserName, prevGroupName, swapEnabled, capsGenerationEnabled):
        self.sanityCheck = sanityCheck
        self.rootfs = rootfs
        self.privileged = privileged
        self.crashReporting = crashReporting
        self.autodev = True
        self.isAppend = append
        self.prevUserName = prevUserName
        self.prevGroupName = prevGroupName
        self.installedLibs = set()
        self.alreadyLinked = set()
        self.librariesToAdd = []
        self.defaultMountOptions = "ro,bind,nodev,nosuid"
        self.cRObject = cCrashReporting(sanityCheck.confOptsDict)
        self.ldSoPreloadConfigured = False
        self.ldSoPreloadCrashReportingConfigured = False
        self.swapEnabled = swapEnabled
        self.capsGenerationEnabled = capsGenerationEnabled

    def processUsersAndGroups(self, lxcParamsNode, lxcConfigNode, allUserNames, allGroupNames):
        # add username and groupname for main service
        if (lxcConfigNode is not None):
            userName = lxcConfigNode.find("UserName")
            groupName = lxcConfigNode.find("GroupName")
            if (groupName is None or groupName.text is None):
                groupName = userName
            if (userName is not None and userName.text is not None):
                allUserNames["start"] = userName.text  # main launcher doesn't have a ParamName attribute, so use "start"
            if (groupName is not None and groupName.text is not None):
                allGroupNames["start"] = groupName.text

            extraUserNames = lxcConfigNode.find("ExtraUsers")
            if extraUserNames is not None:
                for userName in extraUserNames.iter("UserName"):
                    if (userName is not None and userName.text is not None):
                        allUserNames["additional-" + userName.text] = userName.text

            extraGroupNames = lxcConfigNode.find("ExtraGroups")
            if extraGroupNames is not None:
                for groupName in extraGroupNames.iter("GroupName"):
                    if (groupName is not None and groupName.text is not None):
                        allGroupNames["additional-" + groupName.text] = groupName.text

        # add usernames and groupnames for secondary services if needed
        if (lxcParamsNode is not None):
            for attachEntry in lxcParamsNode.iter('Attach'):
                paramName = attachEntry.find("ParamName").text
                userName = attachEntry.find("UserName")
                groupName = attachEntry.find("GroupName")

                # if no groupName provided, take userName as groupName
                if (groupName is None or groupName.text is None):
                    groupName = userName

                if (userName is not None and userName.text is not None):
                    allUserNames[paramName] = userName.text
                if (groupName is not None and groupName.text is not None):
                    allGroupNames[paramName] = groupName.text

        if (not self.sanityCheck.isPrivileged()):
            allUserNames["hardcoded-root"] = "root"  # assuming none of the launchers will ever have ParamName == "hardcoded-root"
            allGroupNames["hardcoded-root"] = "root"
            allUserNames["hardcoded-lxc"] = "lxc"  # assuming none of the launchers will ever have ParamName == "hardcoded-lxc"
            allGroupNames["hardcoded-lxc"] = "lxc"

        if (not self.rootfs.isRootfsShared()):
            dbg.logTrace(1, "Create /etc/passwd /etc/group entries for container")
            self.rootfs.createUserGroupEntries(allUserNames, allGroupNames)

    def createEnvConf(self, lxcConfigNode):

        entry = ""
        envNode = lxcConfigNode.find("Environment")

        if (self.sanityCheck.validateTextEntry(envNode)):
            entry += "\n# Environment Variables Configuration\n"
            preload = list()

            for variable in envNode.iter('Variable'):
                if (variable is not None and variable.text is not None):
                    parts = variable.text.split("=")
                    var_name = parts[0].strip()
                    if (var_name == "LD_PRELOAD" and len(parts) > 1):
                        # avoid duplicates
                        for solib in parts[1].split(":"):
                            if solib not in preload:
                                preload.append(solib)
                    else:
                        entry += self.sanityCheck.confOptsDict['environment'] + " = %s\n" % (variable.text)

            if preload:
                entry += self.sanityCheck.confOptsDict['environment'] + " = LD_PRELOAD=%s\n" % (":".join(preload))
                dbg.logTrace(1, "Installing libraries from LD_PRELOAD: %s" % preload)
                for preload_lib in preload:
                    self.rootfs.addLibraryRequired(preload_lib, 'LD_PRELOAD')
                    # Rootfs configuration is not created when rootfs is shared (non-secure containers - base builds).
                    # Adding libraries should be ignored in this situation.
                    if not self.rootfs.isRootfsShared():
                        self.addRequiredLibs(preload_lib, True)
        else:
            dbg.logTrace(1, "We do not need to create Environment variables")

        return entry

    def getSuffixLen(self, lib, preloadLib):
        nameIdx = lib.find(preloadLib)
        if (nameIdx != -1):
            suffixLen = len(lib) - (nameIdx + len(preloadLib))
            return suffixLen
        else:
            return -1;

    def createLdSoPreloadConf(self, lxcConfigNode):
        entry = ""
        ldSoPreloadNode = lxcConfigNode.find("LdSoPreload")

        preload = list()
        # We need to add libcrashreporting if crashreporting is enabled
        if ((self.cRObject.isEnabled() == True) and (self.crashReporting is True)):
            dbg.logTrace(1, "Crashreporting enabled, adding library to LdPreload")
            preload.append(self.cRObject.getLibCrashReporting())
            self.ldSoPreloadCrashReportingConfigured = True

        if (self.sanityCheck.validateTextEntry(ldSoPreloadNode)):
            for soLibrary in ldSoPreloadNode.iter('SoLib'):
                if (soLibrary is not None and soLibrary.text is not None):
                    solib = soLibrary.text
                    # Check if name of the lib match libcrashreporting - don't add it when crashreporting is disabled
                    if (solib.find(self.cRObject.getLibCrashReporting()) != -1):
                        if self.crashReporting is not True:
                            dbg.logTrace(1, "crashReporting disabled, skipping libcrashreporting from ldSoPreload")
                            continue
                    if solib not in preload:
                        preload.append(solib)
            self.ldSoPreloadConfigured = True
        else:
            dbg.logTrace(1, "No LdSoPreload section to process")

        dbg.logTrace(2, "self.cRObject.isEnabled():%s" % self.cRObject.isEnabled())

        preloadFullPath = list()
        if preload:
            if dbg.traceLevel >= 2:
                entry += "\n# ld.so.preload configuration\n"

            dbg.logTrace(1, "Resolving libs to full path: %s" % preload)
            for preloadLib in preload:
                if preloadLib.find('/') != -1:              # If the lib name contains slashes lets treat it as full path to the lib
                    if preloadLib not in preloadFullPath:
                        preloadFullPath.append(preloadLib)
                else:                                       # Otherwise lets find the path
                    libList = self.rootfs.findLibByName(preloadLib)
                    bestMatch = ""
                    bestMatchSuffixLen = -1
                    # We are selecting among the found paths the one that most closely match preloadLib e.g.:
                    # if preloadLib is: 'libnxpl-weston.so.1' and libList contains; ['usr/lib/libnxpl-weston.so.1.13.1', 'usr/lib/libnxpl-weston.so.1']
                    # we should choose 'usr/lib/libnxpl-weston.so.1'
                    for lib in libList:
                        suffixLen = self.getSuffixLen(lib, preloadLib)
                        if (suffixLen != -1):
                            dbg.logTrace(2, "'%s' found in '%s', suffixLen:%s" % (preloadLib, lib, suffixLen))
                            if (bestMatch == ""):
                                bestMatch = lib
                                bestMatchSuffixLen = suffixLen
                                dbg.logTrace(2, "Initial bestMatch '%s'" % (bestMatch))
                            else:
                                if (suffixLen < bestMatchSuffixLen):
                                    dbg.logTrace(2, "better match found '%s', suffixLen:%s, bestMatchSuffixLen:%s" % (lib, suffixLen, bestMatchSuffixLen))
                                    bestMatch = lib
                                    bestMatchSuffixLen = suffixLen
                                else:
                                    dbg.logTrace(2, "Not a better match '%s', suffixLen:%s, bestMatchSuffixLen:%s" % (lib, suffixLen, bestMatchSuffixLen))
                        else:
                            dbg.logTrace(2, "'%s' not found in '%s'" % (preloadLib, lib))

                    libName = "/%s" % bestMatch
                    dbg.logTrace(1, "Full lib path: %s" % libName)
                    if libName not in preloadFullPath:
                        preloadFullPath.append(libName)
            if preloadFullPath:
                dbg.logTrace(1, "Installing libraries from LdSoPreload: %s" % preloadFullPath)
                for preloadLib in preloadFullPath:
                    self.rootfs.addLibraryRequired(preloadLib, 'LdSoPreload')
                    # Rootfs configuration is not created when rootfs is shared (non-secure containers - base builds).
                    # Adding libraries should be ignored in this situation.
                    if not self.rootfs.isRootfsShared():
                        self.addRequiredLibs(preloadLib, True)
                    if dbg.traceLevel >= 2:
                        entry += "# solib: %s\n" % (preloadLib)
                    self.rootfs.appendLdSoPreload(preloadLib)
        else:
            dbg.logTrace(1, "Nothing to add in ld.preload - list is empty")

        return entry

    def createNetworkConf(self, lxcConfigNode):

        entry = ""

        for networkNode in lxcConfigNode.iter('Network'):
            if networkNode is not None:
                entry += "\n# LXC network interface configuration\n"
                type = networkNode.attrib["type"]

                if (type == "veth" or type == "macvlan"):
                    entry += self.sanityCheck.confOptsDict['net_type'] + " = %s\n" % (type)

                    name = networkNode.find("Name")
                    if (self.sanityCheck.validateTextEntry(name)):
                        entry += self.sanityCheck.confOptsDict['net_name'] + " = %s\n" % (name.text)

                    flags = networkNode.find("Flags")
                    if (self.sanityCheck.validateTextEntry(flags)):
                        entry += self.sanityCheck.confOptsDict['net_flags'] + " = %s\n" % (flags.text)

                    link = networkNode.find("Link")
                    if (self.sanityCheck.validateTextEntry(link)):
                        entry += self.sanityCheck.confOptsDict['net_link'] + " = %s\n" % (link.text)

                    pair = networkNode.find("Pair")
                    if (self.sanityCheck.validateTextEntry(pair)):
                        entry += self.sanityCheck.confOptsDict['net_veth_pair'] + " = %s\n" % (pair.text)

                    hwaddr = networkNode.find("HwAddr")
                    if (self.sanityCheck.validateTextEntry(hwaddr)):
                        entry += self.sanityCheck.confOptsDict['net_hwaddr'] + " = %s\n" % (hwaddr.text)

                    ipv4 = networkNode.find("IPV4")
                    if (self.sanityCheck.validateTextEntry(ipv4)):
                        entry += self.sanityCheck.confOptsDict['net_ipv4'] + " = %s\n" % (ipv4.text)

                    ipv4Gw = networkNode.find("IPV4gateway")
                    if (self.sanityCheck.validateTextEntry(ipv4Gw)):
                        entry += self.sanityCheck.confOptsDict['net_ipv4_gateway'] + " = %s\n" % (ipv4Gw.text)

                    ipv6 = networkNode.find("IPV6")
                    if (self.sanityCheck.validateTextEntry(ipv6)):
                        entry += self.sanityCheck.confOptsDict['net_ipv6'] + " = %s\n" % (ipv6.text)

                    ipv6Gw = networkNode.find("IPV6gateway")
                    if (self.sanityCheck.validateTextEntry(ipv6Gw)):
                        entry += self.sanityCheck.confOptsDict['net_ipv6_gateway'] + " = %s\n" % (ipv6Gw.text)

                    libs4Network = self.sanityCheck.getAutoInstallLibs(cSanityCheck.LibCategory.NETWORK)
                    dbg.logTrace(1, "Auto install libs category[%s]: %s" % (cSanityCheck.LibCategory.NETWORK.value,
                        libs4Network))

                    for lib in libs4Network:
                        # Rootfs configuration is not created when rootfs is shared
                        # (non-secure containers - base builds).
                        # Adding libraries should be ignored in this situation.
                        if not self.rootfs.isRootfsShared():
                            self.addRequiredLibs(lib, True)

                else:
                    entry += self.sanityCheck.confOptsDict['net_type'] + " = %s\n" % (type)

        return entry

    def addRequiredLibs(self, source, addSourceItself = False, indent = ""):
        deps = self.rootfs.readElfDeps(source)
        if addSourceItself:
            deps.insert(0, os.path.basename(source))  # Put a source on 'lxc.mount.entry' list (used when parsing LD_PRELOAD)
        if not deps:
            return
        if not indent:
            dbg.logTrace(1, "Adding required libs for %s" % source)
        for dep in deps:
            dbg.logTrace(2, "%s- %s" % (indent, dep))
            libList = self.rootfs.findLibByName(dep)

            outputLibSet = set()
            for li in libList:                       # Check if any library is a link and if it is, then put its target to the list and remove the link itself
                if os.path.islink(os.path.join(self.rootfs.getRootfsPath(), li)):
                    if li not in self.alreadyLinked:
                        target = os.readlink(os.path.join(self.rootfs.getRootfsPath(), li))
                        originalTarget = target
                        if not target.startswith("/"):
                            target = os.path.join(os.path.dirname(li), target)
                        dbg.logTrace(3, "%s  + %s - symbolic link to %s" % (indent, li, target))
                        targetPath = os.path.join(self.rootfs.getRootfsPath(), target)
                        if (os.path.islink(targetPath)):
                            dbg.logTrace(3, "%s  + targetPath is a symbolic link itself: %s" % (indent, targetPath))
                        else:
                            outputLibSet.add(target)
                        # cerate actual symlink on container fs
                        dbg.logTrace(3, "%s  + create link %s -> %s" % (indent, li, originalTarget))
                        self.rootfs.createSoftlinkForFile(originalTarget, li)
                        if target not in self.installedLibs:
                            self.installedLibs.add(li)
                        self.alreadyLinked.add(li)
                    else:
                        dbg.logTrace(3, "%s  + %s - symbolic link already exist." % (indent, li))
                else:                  # Append only real files to the output list
                    outputLibSet.add(li)

            del libList
            libList = list()
            libList.extend(outputLibSet)
            for li in libList:
                if li in self.installedLibs:
                    dbg.logTrace(3, "%s  + %s - already installed" % (indent, li))
                    continue
                dbg.logTrace(2, "%s  + %s" % (indent, li))
                self.installedLibs.add(li)
                if(self.sanityCheck.pathExist(li)):
                    self.librariesToAdd.append(self.sanityCheck.confOptsDict['mount_entry'] + " = /%s %s none %s 0 0\n" % (li, li, self.defaultMountOptions))
                    self.rootfs.createMountPointForFile(li)
                    self.addRequiredLibs(li, indent = indent + "    ")
                else:
                    raise Exception("[!!! ERROR !!!] Rootfs does not contain (%s) - No such file or directory" % (li))

    def scanDir(self, path):
        for root, dirs, files in os.walk(self.rootfs.getRootfsPath() + "/" + str(path)):
            for f in files:
                self.addRequiredLibs(os.path.join("/" + path, f))
            for d in dirs:
                self.scanDir(os.path.join(path, d))

    def createMountPoint(self, type, path, source):
        if (type == "dir"):
            self.rootfs.makeDir("%s/%s" % (self.rootfs.getPathRootfsHost(), path))
            self.scanDir(path)
        elif (type == "file"):
            self.rootfs.createMountPointForFile(path, source)

            # if library is added as regular file, we need to:
            # - remove previous lxc.conf entry definitions generated by RoLibs and auto-dependencies
            # - add library to installed libraries list if not there yet (to not add again from RoLibs and auto-dependencies)
            fname = os.path.basename(path)
            if re.match("(^lib.*?\.so(?:$|.\d+))", fname):
                dbg.logTrace(1, "!!! processing lib from <entry>: %s" % source)
                if path in self.installedLibs:
                    dbg.logTrace(1, "!!! %s in installedLibs" % path)
                    for line in self.librariesToAdd:
                        if (line.find(path) != -1):
                            dbg.logTrace(1, "!!! %s in librariesToAdd, remove %s" % (path, line))
                            self.librariesToAdd.remove(line)
                else:
                    dbg.logTrace(1, "!!! %s not in installedLibs" % path)
                    self.installedLibs.add(path)

            self.addRequiredLibs(source)
        elif (type == "dev"):
            if(self.autodev):
                dbg.logTrace(1, "Skipping creating entry for devices cause - autodev enabled.")
            else:
                self.rootfs.makeFile("%s/%s" % (self.rootfs.getPathRootfsHost(), path))
        else:
            raise Exception("No such type for mount point {%s}" % (type))

    def getAutodevSettings(self, lxcConfigNode):

        entry = "\n# When autodev =1 LXC mounts and populate a minimal /dev when container starts\n"
        autoDev = lxcConfigNode.find("AutoDev")

        if(self.rootfs.isRootfsShared()):
            dbg.logTrace(1, "Shared rootfs was set, overwriting autodev settings to false")
            self.autodev = False
            entry += self.sanityCheck.confOptsDict['autodev'] + " = 0\n"
        else:
            if (self.sanityCheck.validateTextEntry(autoDev)):
                entry += self.sanityCheck.confOptsDict['autodev'] + " = %s\n" % (autoDev.text)
                if (autoDev.text == "0"):
                    self.autodev = False
                else:
                    self.autodev = True
            else:
                entry += self.sanityCheck.confOptsDict['autodev'] + " = 1\n"
                self.autodev = True

        return entry

    def sortMountOptions(self, mountOptions):
        optionsList = mountOptions.split(",")
        result = []
        for i in ("defaults," + self.defaultMountOptions).split(","):
            if i in optionsList:
                result.append(i)
                optionsList.remove(i)
        result.extend(optionsList)
        resultStr = ",".join(result)
        if mountOptions != resultStr:
            dbg.logTrace(2, "Mount options have been reordered to match ordering of default options '%s' --> '%s'" % (mountOptions, resultStr))
        return resultStr

    def addMountPointIfMissing(self, mountPointNode, _type, source, destination, options):
        el_exists = False
        for mountPoint in mountPointNode.iter('Entry'):
            if (mountPoint is not None):
                el_source = mountPoint.find("Source")
                if el_source == source:
                    el_exists = True
                    break
        if not el_exists:
            entry_el = ET.SubElement(mountPointNode, 'Entry', type=_type)
            source_el = ET.SubElement(entry_el, 'Source')
            source_el.text = source
            dest_el = ET.SubElement(entry_el, 'Destination')
            dest_el.text = destination
            options_el = ET.SubElement(entry_el, 'Options')
            options_el.text = options

    def preprocessMountPoints(self, mountPointNode):
        self.addMountPointIfMissing(mountPointNode, 'file', '/etc/nsswitch.conf', 'etc/nsswitch.conf', 'ro,bind,noexec,nosuid,nodev')

    def getAutodevHookSettings(self, lxcConfigNode):

        entry = ""
        autoDevHook = lxcConfigNode.find("AutoDevHook")

        if (self.sanityCheck.validateTextEntry(autoDevHook)):
            entry += "lxc.hook.autodev = %s\n"%(autoDevHook.text)
        else:
            entry += "#No AutoDev Hook.\n"

        return entry

    def generateMountPoints(self, mountPointNode):

        entry = ""
        if (mountPointNode is not None):
            entry += "\n# Mount Points Configuration\n"
            self.preprocessMountPoints(mountPointNode)
            for mountPoint in mountPointNode.iter('Entry'):
                if(mountPoint is not None):
                    source = mountPoint.find("Source")
                    destination = mountPoint.find("Destination")
                    options = mountPoint.find("Options").text
                    type = mountPoint.attrib["type"]
                    appendix_list = [""]
                    dump = 0
                    fsck = 0
                    fsType = "none"

                    if (self.sanityCheck.validateTextEntry(mountPoint.find("Dump"))):
                        dump = mountPoint.find("Dump").text

                    if (self.sanityCheck.validateTextEntry(mountPoint.find("Fsck"))):
                        fsck = mountPoint.find("Fsck").text

                    if (self.sanityCheck.validateTextEntry(mountPoint.find("FsType"))):
                        fsType = mountPoint.find("FsType").text

                    if "range" in mountPoint.attrib and mountPoint.attrib["range"] is not None:
                        rbegin, rend = self.sanityCheck.parseRange(mountPoint.attrib["range"])
                        appendix_list = list(range(rbegin, rend + 1))

                    for i in appendix_list:
                        sourceTmpStr = source.text + str(i)
                        destinationTmpStr = destination.text + str(i)
                        if (self.sanityCheck.validateTextEntry(source) and self.sanityCheck.validateTextEntry(destination)):
                            if destinationTmpStr.startswith("/"):
                                #raise Exception("[%s] Destination mount path can't start with /", destinationTmpStr)
                                print("[%s] Destination mount path can't start with /", destinationTmpStr)
                            if (not self.sanityCheck.validateMountBind(sourceTmpStr, options)):
                                continue
                            self.sanityCheck.validateOptions(sourceTmpStr, fsType, options)
                            if(sourceTmpStr == destinationTmpStr):
                                if(not self.sanityCheck.checkNestedMountBinds(sourceTmpStr)):
                                    raise Exception("[%s] Nested mount bind found =  %s ", sourceTmpStr)

                            entry += self.sanityCheck.confOptsDict['mount_entry'] + " = %s %s %s %s %s %s\n" % (
                                sourceTmpStr,
                                destinationTmpStr,
                                fsType,
                                self.sortMountOptions(options),
                                dump,
                                fsck)

                            self.createMountPoint(type, destinationTmpStr, sourceTmpStr)
                            if (type == "dir"):
                                self.sanityCheck.addDir(sourceTmpStr)
                                for unusedEntry in mountPoint.iter('Unused'):
                                    if (self.sanityCheck.validateTextEntry(unusedEntry)):
                                        self.rootfs.unusedList.append(unusedEntry.text)
                                self.rootfs.checkElfDepsForDirectoryMountPoint(destinationTmpStr, sourceTmpStr)

                        else:
                            raise Exception("INVALID DATA MOUNT POINT")

        return entry

    def moveContent(self, moveContentNode):

        if moveContentNode is not None:
            for moveContent in moveContentNode.iter('Entry'):
                source = moveContent.find("Source")
                destination = moveContent.find("Destination")
                type = moveContent.attrib["type"]

                if (self.sanityCheck.validateTextEntry(source) and self.sanityCheck.validateTextEntry(destination)):
                    if type == "dir":
                        self.rootfs.moveDir("%s" % (self.rootfs.getRootfsPath() + source.text), "%s" % (self.rootfs.getPathRootfsHost() + destination.text))
                    elif type == "file":
                        self.rootfs.moveFile("%s" % (self.rootfs.getRootfsPath() + source.text), "%s" % (self.rootfs.getPathRootfsHost() + destination.text))
                    else:
                        dbg.logTrace(1, "No such type for mount content --> %s" % type)
        else:
            dbg.logTrace(1, "Move content entry not found, skipping")

    def processLibBinding(self, libname):
        entry = ""
        dbg.logTrace(2, "Lib entry: %s" % (libname))
        libList = self.rootfs.findLibByName(libname)
        for source in libList:
            if source in self.installedLibs:
                if dbg.traceLevel >= 2:
                    entry += "#### already installed: " + self.sanityCheck.confOptsDict['mount_entry'] + " = /%s %s none %s 0 0\n" % (source, source, self.defaultMountOptions)
                dbg.logTrace(3, "  + %s - already installed" % source)
                continue
            dbg.logTrace(2, "  + %s" % source)
            self.addRequiredLibs(source, True)
        return entry

    def generateLibMountPoints(self, libBindingsNode):
        entry = ""
        entry += "\n# Mount Binds Configuration For Libs\n"
        if self.librariesToAdd:
            entry += "# Auto-found dependencies\n"
            for libEntry in sorted(self.librariesToAdd):
                entry += libEntry
        if libBindingsNode is not None:
            self.librariesToAdd = []
            entry += "# Manually added dependencies\n"
            dbg.logTrace(1, "Manually added dependencies:")
            for libBinding in libBindingsNode.iter('Entry'):
                if (self.sanityCheck.validateTextEntry(libBinding)):
                    entry += self.processLibBinding(libBinding.text)
            if self.librariesToAdd:
                for libEntry in sorted(self.librariesToAdd):
                    entry += libEntry
        return entry

    def generateHardlinks(self, libHardlinksNode):

        if libHardlinksNode is not None:
            for libHardlink in libHardlinksNode.iter('Entry'):
                if self.sanityCheck.validateTextEntry(libHardlink):
                    libList = self.rootfs.findLibByName(libHardlink.text)
                    for source in libList:
                        if self.sanityCheck.pathExist(source):
                            if self.rootfs.existsOnHost(source):
                                if source not in self.installedLibs:
                                    # Binding could be already done by 'auto-find dependencies' functionality
                                    # and then entries from 'LibsHardlinks' try to create hard links.
                                    # If 'LibsHardlinks' is in 'appendix' for lxc-configuration, then this warning
                                    # is false-positive because 'installedLibs' variable is not shareable between
                                    # root configuration and its appendixes.
                                    dbg.logTrace(1, "*** WARNING: Removing already existing file. Needed to create hard link there: '%s' - '%s'."
                                                 % (source, os.path.join(self.rootfs.getPathRootfsHost(), source)))
                                self.rootfs.removeFileFromHost(source)
                            self.rootfs.createHardlinkForFile(source)
                        else:
                            raise Exception("[!!! ERROR !!!] Rootfs does not contain (%s) - No such file or directory" % (source))

    def generateDirsAndFiles(self, dirsAndFilesNode):
        if dirsAndFilesNode is not None:
            for DirOrFile in dirsAndFilesNode.iter('Entry'):
                if self.sanityCheck.validateTextEntry(DirOrFile):
                    type = DirOrFile.attrib["type"]
                    if (type == "file"):
                        self.rootfs.makeFile("%s/%s" % (self.rootfs.getPathRootfsHost(), DirOrFile.text))
                    elif type == "dir":
                        self.rootfs.makeDir("%s/%s" % (self.rootfs.getPathRootfsHost(), DirOrFile.text))
                    else:
                        raise Exception("[!!! ERROR !!!] Unknown type under DirsAndFiles (%s)" % (type))

    def generateSoftLinks(self, softLinksNode):
        if softLinksNode is not None:
            for linkNode in softLinksNode.iter('Entry'):
                if linkNode is not None:
                    name = linkNode.find("Name")
                    target = linkNode.find("Target")
                    if self.sanityCheck.validateTextEntry(name) and self.sanityCheck.validateTextEntry(target):
                        self.rootfs.makeSymlink(target.text, os.path.join(self.rootfs.getPathRootfsHost(), name.text))
                    else:
                        raise Exception("[!!! ERROR !!!] Invalid link data")

    def updateLibScanDirsList(self, rootfsNode):
        if rootfsNode is not None:
            libBindingsNode = rootfsNode.find("LibsRoBindMounts")
            if libBindingsNode is not None:  # All library dirs have to be set before checking dependencies
                for libsScanDir in libBindingsNode.iter('LibsScanDir'):
                    if self.sanityCheck.validateTextEntry(libsScanDir):
                        self.rootfs.addLibsScanDir(libsScanDir.text)
                    else:
                        raise Exception("[!!! ERROR !!!] Invalid <LibsScanDir> tag: Must contain a dir")

    def createRootfsConf(self, rootfsNode):

        entry = ""

        if rootfsNode is not None:
            rootfsCreate = rootfsNode.attrib["create"]
            if rootfsCreate == "yes":
                if (not self.isAppend):
                    entry += "\n# Rootfs path settings\n"
                    entry += self.sanityCheck.confOptsDict['rootfs_path'] + " = %s\n" % (self.rootfs.getPathRootfsTarget())
                    # Libs that have to be added to every container
                    essentialLibs = self.sanityCheck.getAutoInstallLibs(cSanityCheck.LibCategory.ESSENTIAL)
                    dbg.logTrace(1, "Auto install libs category[%s]: %s" % (cSanityCheck.LibCategory.ESSENTIAL.value,
                        essentialLibs))
                    for lib in essentialLibs:
                        self.addRequiredLibs(lib, True)
                entry += self.generateMountPoints(rootfsNode.find("MountPoints"))
                self.moveContent(rootfsNode.find("MoveContent"))
                entry += self.generateLibMountPoints(rootfsNode.find("LibsRoBindMounts"))
                self.generateHardlinks(rootfsNode.find("LibsHardlinks"))
                self.generateDirsAndFiles(rootfsNode.find("DirsAndFiles"))
                self.generateSoftLinks(rootfsNode.find("SoftLinks"))
            else:
                dbg.logTrace(1, "Mount namespace disabled")

        return entry

    def genereteUserSettings(self, lxcConfigNode):

        entry = ""

        if(self.privileged):
            userName = lxcConfigNode.find("UserName")
            groupName = lxcConfigNode.find("GroupName")
            if (self.sanityCheck.validateTextEntry(userName) and self.sanityCheck.validateTextEntry(groupName)):
                if (self.prevUserName != userName.text or self.prevGroupName != groupName.text):
                    uid = self.rootfs.userNameToUid(userName.text)
                    gid = self.rootfs.groupNameToGid(groupName.text)
                    entry += "\n# USER/GROUP Container Configuration\n"
                    entry += self.sanityCheck.confOptsDict['init_uid'] + " = %s\n" % (uid)
                    entry += self.sanityCheck.confOptsDict['init_gid'] + " = %s\n" % (gid)

            dbg.logTrace(1, "Non-root container created")
        else:
            dbg.logTrace(1, "Root container created")

        return entry

    def genereteConsoleSettings(self, lxcConfigNode):

        entry = ""

        pts = lxcConfigNode.find("LxcPts")
        tty = lxcConfigNode.find("LxcTty")
        if (self.sanityCheck.validateTextEntry(pts)):
            entry += self.sanityCheck.confOptsDict['pts_max'] + " = %s\n" % (pts.text)
        if (self.sanityCheck.validateTextEntry(tty)):
            entry += self.sanityCheck.confOptsDict['tty_max'] + " = %s\n" % (tty.text)

        return entry

    def generateCapsSettings(self, lxcConfigNode):

        entry = ""
        capDrop = lxcConfigNode.find("CapDrop")
        if (self.sanityCheck.validateTextEntry(capDrop)):
            capDropList = re.split(',| |\n|\t', capDrop.text)
            for capDropEntry in capDropList:
                entry += self.sanityCheck.confOptsDict['cap_drop'] + " = %s\n" % (capDropEntry)

        capKeep = lxcConfigNode.find("CapKeep")
        if (self.sanityCheck.validateTextEntry(capKeep)):
            capKeepList = re.split(',| |\n|\t', capKeep.text)
            for capKeepEntry in capKeepList:
                entry += self.sanityCheck.confOptsDict['cap_keep'] + " = %s\n" % (capKeepEntry)

        return entry

    def createSeccompConf(self, lxcConfigNode):

        entry = ""
        seccompprofile = lxcConfigNode.find("SeccompProfile");
        if (seccompprofile != None and seccompprofile.text != None):
            entry +="\n# LXC SECCOMP configuration\n"
            entry += "lxc.seccomp = %s\n"%seccompprofile.text

        return entry

    def createLxcConf(self, lxcConfigNode):

        if (os.path.exists(os.path.dirname(self.rootfs.getConfFileHost()))):
            conf_fd = open(self.rootfs.getConfFileHost(), 'a')
        else:
            raise Exception("[!!! ERROR !!!] No such directory for configuration file (%s) - "
                            "it may happen when configuration append-file is processed before main. "
                            "Check the append-file name (%s)."
                            % (os.path.dirname(self.rootfs.getConfFileHost()), self.sanityCheck.filename))

        if(self.isAppend):
            conf_fd.write("\n\n# Platform specific settings \n")
        else:
            conf_fd.write("# Container hostname settings \n")
            conf_fd.write(self.sanityCheck.confOptsDict['uts_name'] + " = %s\n" % (self.rootfs.getSandboxName()))

        if (lxcConfigNode.find("Rootfs") is None or lxcConfigNode.find("Rootfs").attrib["create"] == "no"):
            self.rootfs.setShareRootfs(True)

        dbg.logTrace(1, "Create LXC CGROUP configuration")
        cgroup = cCgroup(self.sanityCheck, self.swapEnabled)
        cgroupConfig = cgroup.createCGroupConf(lxcConfigNode.find("CGroupSettings"))
        conf_fd.write(cgroupConfig)

        consoleConfig = self.genereteConsoleSettings(lxcConfigNode)
        conf_fd.write(consoleConfig)

        capsConfig = self.generateCapsSettings(lxcConfigNode)
        conf_fd.write(capsConfig)

        userConfig = self.genereteUserSettings(lxcConfigNode)
        conf_fd.write(userConfig)

        print("[%s] Create LXC SECCOMP configuration"%(self.sanityCheck.getName()))
        seccompConfig = self.createSeccompConf(lxcConfigNode)
        conf_fd.write(seccompConfig)

        dbg.logTrace(1, "Create LXC Network configuration")
        networkConfig = self.createNetworkConf(lxcConfigNode)
        conf_fd.write(networkConfig)

        for lxcInclude in lxcConfigNode.findall("LxcInclude"):
            if (self.sanityCheck.validateTextEntry(lxcInclude)):
                conf_fd.write(self.sanityCheck.confOptsDict['include'] + " = %s\n" % (lxcInclude.text))

        dbg.logTrace(1, "Create LXC Environment configuration")
        envInfo = self.createEnvConf(lxcConfigNode)
        conf_fd.write(envInfo)

        if (not self.isAppend):
            autodevInfo = self.getAutodevSettings(lxcConfigNode)
            conf_fd.write(autodevInfo)
            if (self.autodev):
                autodevHookInfo = self.getAutodevHookSettings(lxcConfigNode)
                conf_fd.write(autodevHookInfo);

        if (not self.rootfs.isRootfsShared()):
            dbg.logTrace(1, "Create LXC D-Bus configuration")
            dbus = cDbus(self.rootfs, self.sanityCheck.dbusSocket, self.sanityCheck.confOptsDict)
            dbusConfig = dbus.createDbusConf(self, lxcConfigNode.find("Dbus"))
            conf_fd.write(dbusConfig)

            # First check if crashreporting is not explicitely disabled
            if self.crashReporting is True:
                crashReportingNode = lxcConfigNode.find("CrashReporting")
                if crashReportingNode is not None:
                    dbg.logTrace(1, "Create LXC CrashReporting configuration")
                    self.cRObject.setUp(self, self.rootfs, crashReportingNode, conf_fd)

            rootfsNode = lxcConfigNode.find("Rootfs")
            self.updateLibScanDirsList(rootfsNode)

            dbg.logTrace(1, "Create ld.so.preload configuration")
            ldSoPreloadInfo = self.createLdSoPreloadConf(lxcConfigNode)
            conf_fd.write(ldSoPreloadInfo)

            if (rootfsNode is not None and rootfsNode.text is not None):
                dbg.logTrace(1, "Create LXC Mount Points configuration")
                rootfsInfo = self.createRootfsConf(rootfsNode)
                conf_fd.write(rootfsInfo)

            for autoMount in lxcConfigNode.iter("AutoMount"):
                if (self.sanityCheck.validateAutoMount(autoMount)):
                    conf_fd.write("\n" + self.sanityCheck.confOptsDict['mount_auto'] + " = %s\n" % (autoMount.text))

            print("[%s] Create LXC logging configuration"%(self.sanityCheck.getName()))
            log = cLog(self.rootfs)
            logConfig = log.createLoggingConf(lxcConfigNode.find("Logging"), lxcConfigNode.find("UserName"))
            conf_fd.write(logConfig);
        else:
            conf_fd.write("\n" + self.sanityCheck.confOptsDict['autodev'] + " = 0\n")

        conf_fd.close()

        # Remove duplicated mount entries
        lines_seen = set()  # Holds lines already present in the file
        outputBuffer = ""

        with open(self.rootfs.getConfFileHost(), "r") as conf_fd:
            for line in conf_fd:
                if line.find(self.sanityCheck.confOptsDict['mount_entry']) == -1:   # If the line is not a mount entry so write it back.
                    outputBuffer += line
                else:
                    pattern = r'^\s*' + self.sanityCheck.confOptsDict['autodev'] + '\s*=\s*/(\S+)\s+(etc/ld.so.preload)\s+'
                    if re.match(pattern, line):   # Check if custom ld.so.preload is mounted in the container
                        match = re.search(pattern, line)
                        sourcePath = match.group(1)
                        targetPath = match.group(2)

                        # Check if both source and target paths of the mounted file are found
                        if (sourcePath and targetPath):
                            dbg.logTrace(1, "custom ld.so.preload found, sourcePath: %s" %(sourcePath))
                            if os.path.exists(self.rootfs.getPathLdSoPreloadFileTarget()):
                                dbg.logTrace(1, "Size of %s is %s" %(self.rootfs.getPathLdSoPreloadFileTarget(), os.path.getsize(self.rootfs.getPathLdSoPreloadFileTarget())))
                                # Check if the file is bigger than 0 to differentiate between mount points for custom file and generated ld.so.preload
                                if (os.path.getsize(self.rootfs.getPathLdSoPreloadFileTarget()) > 0):
                                    if self.ldSoPreloadConfigured:
                                        raise Exception("ERROR: Custom ld.so.preload found while <LdSoPreload> is configured in XML.")
                                    elif (self.ldSoPreloadCrashReportingConfigured and not self.ldSoPreloadConfigured):
                                        # When <LdSoPreload> not configured allow custom ld.so.preload if it contains libcrashreporting, throw an error if doesn't
                                        if (open(self.rootfs.getRootfsPath()+'/'+sourcePath, 'r').read().find(self.cRObject.getLibCrashReporting()) != -1):
                                            open(self.rootfs.getPathLdSoPreloadFileTarget(), 'w').close()   # Empty target file, which will be only a mountpoint
                                        else:
                                            raise Exception("ERROR: Custom /etc/ld.so.preload found but it doesn't contain libcrashreporting which is enabled.")
                                    dbg.logTrace(1, "Custom ld.so.preload %s accepted as mount bind for target: %s" %(sourcePath, targetPath))

                    if line not in lines_seen:  # If the line is the first ocurrence of a particular mount entry write it back.
                        outputBuffer += line
                        if (line.startswith("#") is False):  # Add only not commented lines, to avoid putting multiple comments if dbg.traceLevel >= 2
                            lines_seen.add(line)
                    else:                      # If it is a duplicate do not store or comment it out.
                        if dbg.traceLevel >= 2:
                            outputBuffer += "# duplicated: %s" % line

        with open(self.rootfs.getConfFileHost(), 'w') as conf_fd:
            conf_fd.write(outputBuffer)

        # Remove duplicated libs in ld.so.preload file
        if os.path.exists(self.rootfs.getPathLdSoPreloadFileTarget()):
            lines_seen = set()  # Holds lines already present in the file
            outputBuffer = ""

            with open(self.rootfs.getPathLdSoPreloadFileTarget(), "r") as ldPreload_fd:
                for line in ldPreload_fd:
                    if line not in lines_seen:  # If the line is the first ocurrence of a particular mount entry write it back.
                        outputBuffer += line
                        lines_seen.add(line)
                    else:
                        dbg.logTrace(1, "Duplicated library: %s" %(line))

            with open(self.rootfs.getPathLdSoPreloadFileTarget(), 'w') as ldPreload_fd:
                ldPreload_fd.write(outputBuffer)

        # The last step after all configurations are complete:
        # add appropriate "lxc.cap.keep = xxx" entries required by NASC 1.x.
        if self.capsGenerationEnabled:
            if self.rootfs.getSandboxName() != "NXSERVER":
                # nxserver will not work properly if lxc.cap.keep is used
                # even if all caps are listed in lxc.cap.keep
                dbg.logTrace(1, "Create CAPS configuration")
                # Get OE_VER
                oe_ver = self.sanityCheck.getPlatformSettingValue("OE_VER")
                if not oe_ver:
                    raise Exception("[!!! ERROR !!!] OE_VER is not set.")
                dbg.logTrace(1, "OE_VER = %s" % (oe_ver))
                caps = cCaps(self.sanityCheck.confOptsDict)
                capsConfig = caps.createCapsConf(self.rootfs.getRootfsPath(), self.rootfs.getConfFileHost(), oe_ver)
                if capsConfig:
                    with open(self.rootfs.getConfFileHost(), 'a') as conf_fd:
                        conf_fd.write(capsConfig)
