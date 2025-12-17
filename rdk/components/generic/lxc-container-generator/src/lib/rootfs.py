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
import stat
from . import dbg


################################################################################
#   class cRootfs(object):
#
#       Represents directories on rootfs,
#       implements basic functionalities to manipultae with rootfs.
#
################################################################################
class cRootfs(object):
    def __init__(self, name, rootfsPath, shareRootfs, extRootfsList):
        self.name = name
        self.rootfsPath = rootfsPath
        self.shareRootfs = shareRootfs
        self.launcherName = " "
        self.sources = dict()
        self.libs = dict()
        self.unusedList = list()
        self.libsScanned = False
        self.nameToUidMap = dict()
        self.groupToGidMap = dict()
        self.reElfRequired = re.compile(r"\(NEEDED\)\s+Shared library: \[([^\]]*)\]")
        self.reRunPath = re.compile(r"\(RUNPATH\)\s+Library runpath: \[([^\]]*)\]")
        self.libScanDirs = {"lib", "lib/systemd", "usr/lib", "usr/lib/gstreamer-1.0"}
        if extRootfsList:
            self.extRootfsList = extRootfsList
        else:
            self.extRootfsList = []

    def isRootfsShared(self):
        return self.shareRootfs

    def setShareRootfs(self, shareRootfs):
        self.shareRootfs = shareRootfs

    def setLauncherName(self, launcherName):
        self.launcherName = launcherName

    def getRootfsPath(self):
        return self.rootfsPath

    def getSandboxName(self):
        return self.name

    def getPathContainerParentDirHost(self):
        return "%s/container" % self.rootfsPath

    def getPathContainerHost(self):
        return "%s/container/%s" % (self.rootfsPath, self.name)

    def getPathRootfsTarget(self):
        return "/container/%s/rootfs" % self.name

    def getPathRootfsHost(self):
        return "%s/container/%s/rootfs" % (self.rootfsPath, self.name)

    def getPathConfFileHost(self):
        return "%s/container/%s/conf" % (self.rootfsPath, self.name)

    def getConfFileHost(self):
        return "%s/container/%s/conf/lxc.conf" % (self.rootfsPath, self.name)

    def getConfFileTarget(self):
        return "/container/%s/conf/lxc.conf" % self.name

    def getPathLauncherFileHost(self):
        return "%s/container/%s/launcher" % (self.rootfsPath, self.name)

    def getLauncherFileHost(self):
        return "%s/container/%s/launcher/%s.sh" % (self.rootfsPath, self.name, self.launcherName)

    def getPathPasswdFileHost(self):
        return "%s/etc/passwd" % (self.rootfsPath)

    def getPathPasswdFileTarget(self):
        return "%s/container/%s/rootfs/etc/passwd" % (self.rootfsPath, self.name)

    def getPathGroupFileHost(self):
        return "%s/etc/group" % (self.rootfsPath)

    def getPathGroupFileTarget(self):
        return "%s/container/%s/rootfs/etc/group" % (self.rootfsPath, self.name)

    def getPathLdSoPreloadFileTarget(self):
        return "%s/container/%s/rootfs/etc/ld.so.preload" % (self.rootfsPath, self.name)

    def makeDir(self, dirName):
        if (os.path.exists(dirName)):
            #raise Exception("The directory already exist -- nested mount bind found {%s}" % (dirName))
            self.log_warn("The directory already exist -- nested mount bind found {%s}" % (dirName))
        else:
            dbg.logTrace(3, "makeDir(): creating dir: %s" % (dirName))
            os.makedirs(dirName)

    def makeFile(self, filename):
        if os.path.exists(filename):
            dbg.logTrace(3, "makeFile(): file exists, skipping creation of: %s" % (filename))
        else:
            if not os.path.exists(os.path.dirname(filename)):
                dbg.logTrace(3, "makeFile(): create path: %s" % (os.path.dirname(filename)))
                os.makedirs(os.path.dirname(filename))
            dbg.logTrace(3, "makeFile(): creating file: %s" % (filename))
            error = os.mknod(filename, stat.S_IRUSR | stat.S_IRGRP)
            if error:
                raise Exception("program returned error code {%s}" % (error))

    def existsOnHost(self, source):
        return os.path.exists(os.path.join(self.getPathRootfsHost(), source))

    def removeFileFromHost(self, source):
        if not self.existsOnHost(source):
            raise Exception("The file does not exist in container's rootfs {%s}" % (source))
        os.remove(os.path.join(self.getPathRootfsHost(), source))

    def makeHardlink(self, source, destination):
        if not os.path.exists(os.path.dirname(destination)):
            os.makedirs(os.path.dirname(destination))

        os.link(source, destination)

    def makeSymlink(self, source, destination):
        if os.path.lexists(destination):
            dbg.logTrace(3, "makeSymlink(): link exists, skipping creation of: %s" % (destination))
        else:
            if not os.path.exists(os.path.dirname(destination)):
                dbg.logTrace(3, "makeSymlink(): create path: %s" % (os.path.dirname(destination)))
                os.makedirs(os.path.dirname(destination))

            dbg.logTrace(3, "makeSymlink(): creating symlink %s -> %s" % (destination, source))
            os.symlink(source, destination)

################################################################################
#
#   createContainerTree():
#
#   Generate container directory:
#         /container/name
#                     |__launcher
#                     |__conf
#                     |__rootfs
#                        |__dev
#                        |__init.lxc.static
#
################################################################################
    def createContainerTree(self):
        self.makeDir(self.getPathLauncherFileHost())
        self.makeDir(self.getPathConfFileHost())
        self.makeDir(self.getPathRootfsHost())
        self.makeDir(self.getPathRootfsHost() + "/dev")
        self.makeFile("%s/init.lxc.static" % (self.getPathRootfsHost()))

    def moveFile(self, source, destination):
        if not os.path.exists(os.path.dirname(destination)):
            os.makedirs(os.path.dirname(destination))

        error = os.system("mv %s %s" % (source, destination))
        if error:
            raise Exception("program returned error code {%s}" % (error))

    def moveDir(self, source, destination):
        if not os.path.exists(destination):
            os.makedirs(destination)

        error = os.system("mv %s %s" % (source, destination))
        if error:
            raise Exception("program returned error code {%s}" % (error))

    def changeFilePermissions(self, path, mode):
        dbg.logTrace(3, "changeFilePermissions() changing permissions to:%s %s" % (oct(mode), path))
        error = os.chmod(path, mode)
        if error:
            raise Exception("program returned error code {%s}" % (error))

    def changeFileOwnership(self, uid, gid, path):
        dbg.logTrace(3, "changeFileOwnership() setting uid:%s, gid:%s %s" % (uid, gid, path))
        error = os.lchown(path, int(uid), int(gid))
        if error:
            raise Exception("chown returned error code {%s}" % (error))

    def setUpContainersRights(self, uid, gid):
        dbg.logTrace(3, "setUpContainersRights() uid: %s, gid:%s" % (uid, gid))
        if (uid != "0" and gid != "0"):
            self.changeFileOwnership(uid, gid, self.getPathRootfsHost())
            for root, dirs, files in os.walk(self.getPathRootfsHost()):
                for d in dirs:
                    self.changeFileOwnership(uid, gid, os.path.join(root, d))
                for f in files:
                    file_path = os.path.join(root, f)
                    if not (os.path.isfile(file_path) and os.stat(file_path).st_nlink > 1):
                        self.changeFileOwnership(uid, gid, file_path)
                    else:
                        dbg.logTrace(3, "Skipping chown for hardlink (%s)" % (file_path))

        # remove all "other" user file rights and all write rights for this container
        linux_cmd = "chmod o-rwx,a-w %s -R " % self.getPathContainerHost()
        dbg.logTrace(3, "setUpContainersRights() executing linux_cmd:%s" % linux_cmd)
        error = os.system(linux_cmd)
        if error:
            raise Exception("program returned error code {%s}" % (error))

        # set proper rights for container parent dir, non-recursive
        self.changeFilePermissions(self.getPathContainerParentDirHost(), stat.S_IRUSR | stat.S_IXUSR | stat.S_IRGRP | stat.S_IXGRP)

        # set proper rights for container launcher
        if (self.launcherName is not None and self.launcherName != " "):
            self.changeFilePermissions(self.getLauncherFileHost(), stat.S_IRUSR | stat.S_IXUSR | stat.S_IRGRP | stat.S_IXGRP)

        # set the proper rights for lxc.conf
        self.changeFilePermissions(self.getConfFileHost(), stat.S_IRUSR | stat.S_IRGRP)

################################################################################
#
#   Shared libs support:
#
#       Find libs version based on their name.
#       Check dependencies
#
################################################################################
    def addLib(self, name):
        """Add entry to self.libs"""
        if name in self.libs:
            return
        self.libs[name] = dict()
        self.libs[name]["installed"] = False
        self.libs[name]["path"] = None
        self.libs[name]["deps"] = list()
        self.libs[name]["required_by"] = list()

    def addLibsScanDir(self, dir):
        if dir in self.libScanDirs:
            dbg.logTrace(2, "LibsScanDir [%s] duplicated!. Ignoring it" % dir)
            return
        # Adding a new dir requires rescan of the libraries.
        self.libsScanned = False
        self.libScanDirs.add(str(dir))

    def scanLibsDir(self, base_dir, subdir):
        """Scan directories then add entries to dict
        :raise BadValueError: If 'base_dir' is empty.
        """

        if not base_dir:
            raise ValueError("Invalid base_dir: \"{}\"".format(base_dir))

        for root, dirs, files in os.walk(base_dir + "/" + str(subdir)):
            if (root != base_dir + "/" + subdir):
                continue
            for file in sorted(files):
                self.addLib(file)
                if self.libs[file]["path"] is None:
                    self.libs[file]["path"] = os.path.join(subdir, file)
                if os.path.islink(os.path.join(root, file)):
                    link = os.readlink(os.path.join(root, file))
                    self.libs[file]["symlinkTo"] = os.path.basename(link)

    def scanLibDirs(self):
        if not self.libsScanned:
            # Scan all directories listed in libScanDirs set
            for libDir in self.libScanDirs:
                self.scanLibsDir(self.rootfsPath, str(libDir))

                for ext_rootfs_path in self.extRootfsList:
                    self.scanLibsDir(ext_rootfs_path, str(libDir))
            self.libsScanned = True

    def findLibByName(self, libName):
        """ Find libs version based on their name"""
        self.scanLibDirs()

        lib = []
        for (file, val) in list(self.libs.items()):
            if file.startswith(libName):
                if (libName == file or libName + "." in file or libName + "-" in file):
                    # special case: skip libbusybox-devel
                    if "libbusybox-devel" in file and libName == "libbusybox":
                        continue
                    if val["path"] is not None:
                        lib.append(val["path"])

        if not lib:
            raise Exception("[!!! FIND  !!!] Rootfs does not contain (%s) - No such file or directory" % (libName))

        return lib

    # get full path of the file
    def getFullPath(self, source):
        path = os.path.join(self.rootfsPath, source)
        if not os.path.exists(path):
            for ext_rootfs_path in self.extRootfsList:
                path = os.path.join(ext_rootfs_path, source)
                if os.path.exists(path):
                    return path
        else:
            return path
        return None


################################################################################
#
#   Handle file addition:
#
#       Mark libs as installed, handle dependencies
################################################################################

    def readElfDeps(self, source):
        try:
            if source.startswith("/"):
                source = source[1:]
            if source not in self.sources:
                self.sources[source] = dict()
            elif "deps" in self.sources[source]:
                return self.sources[source]["deps"]
            self.sources[source]["deps"] = list()
            # check if file is elf
            fullPath = self.getFullPath(source)
            file = open(fullPath, "rb")
            header = file.read(4)
            file.close()
            if header != b"\x7fELF":
                # Not a ELF
                return self.sources[source]["deps"]
            file = os.popen("readelf -d " + fullPath)
            for lines in file:
                m = self.reElfRequired.search(lines)
                if m is not None:
                    if m.group(1) not in self.sources[source]["deps"]:
                        self.sources[source]["deps"].append(m.group(1))

                m = self.reRunPath.search(lines)
                if m is not None:
                    dirList = m.group(1).split(":")
                    for dir in dirList:
                        if dir.startswith("/"):
                            dir = dir[1:]

                        sourceDir = os.path.dirname(source)
                        dir = dir.replace("$ORIGIN", sourceDir)
                        dir = dir.replace("${ORIGIN}", sourceDir)
                        libDir = os.path.join(self.rootfsPath, dir)

                        if os.path.exists(libDir):
                            self.addLibsScanDir(dir)
                        else:
                            self.log_warn("readElfDeps: {}: Skipping adding non existing RUNPATH: {} directory".format(source, dir))
            file.close()
        except Exception:
            pass
        return self.sources[source]["deps"]

    # Add shared lib dependency
    def addLibraryRequired(self, lib, source):
        lib = os.path.basename(lib)
        self.addLib(lib)
        if source not in self.libs[lib]["required_by"]:
            self.libs[lib]["required_by"].append(source)
        # Special handling for symlinks
        if "symlinkTo" in self.libs[lib]:
            ldep = self.libs[lib]["symlinkTo"]
            self.addLib(ldep)
            if source not in self.libs[ldep]["required_by"]:
                self.libs[ldep]["required_by"].append(source)

    # Hanle file mounted both directly and as part of subdir
    def handleAddedFile(self, destination, source):
        dbg.logTrace(3, "handleAddedFile(): destination: %s, source: %s" % (destination, source))
        relpath = source
        # handle absolute symlinks
        if os.path.islink(os.path.join(self.rootfsPath, source)):
            link = os.readlink(os.path.join(self.rootfsPath, source))
            if link.startswith("/"):
                relpath = link[1:]

        deps = self.readElfDeps(relpath)
        fname = os.path.basename(destination)
        if fname in self.libs:
            if self.libs[fname]["path"] == destination:
                self.libs[fname]["installed"] = True
                self.libs[fname]["deps"] = deps
                if "symlinkTo" in self.libs[fname]:
                    link = self.libs[fname]["symlinkTo"]
                    if link in self.libs:
                        self.libs[link]["installedSymlink"] = True
        if source in self.unusedList:
            return
        for dep in deps:
            self.addLibraryRequired(dep, source)

    # Create a mount point for regular file in rootfs
    # File could either <Entry type="file>, or shared library
    # Handle shared lib dependencies for ELF files
    def createMountPointForFile(self, path, source=None):
        self.scanLibDirs()
        if source is None:
            source = path
        source = source.lstrip("/")
        self.makeFile("%s/%s" % (self.getPathRootfsHost(), path))
        self.handleAddedFile(path, source)

    def createHardlinkForFile(self, source):
        self.scanLibDirs()
        if source is None:
            return
        source = source.lstrip("/")
        self.makeHardlink("%s/%s" % (self.getRootfsPath(), source), "%s/%s" % (self.getPathRootfsHost(), source))
        self.handleAddedFile(source, source)

    def createSoftlinkForFile(self, source, destination):
        self.scanLibDirs()
        if source is None:
            return
        source = source.lstrip("/")
        self.makeSymlink(source, "%s/%s" % (self.getPathRootfsHost(), destination))
        self.handleAddedFile(destination, destination)

    def checkElfDepsForDirectoryMountPoint(self, destinationpath, sourcepath):
        self.scanLibDirs()
        # Walk directory for ELF files and check dependencies
        for root, dirs, files in os.walk(self.rootfsPath + sourcepath):
            for file in sorted(files):
                fullpath = os.path.join(root, file)
                dstpath = os.path.join(destinationpath, file)
                self.handleAddedFile(dstpath, fullpath[len(self.rootfsPath) + 1:])

    def log_warn(self, msg):
        dbg.logTrace(1, "*** WARNING: %s" % msg)

    def log_err(self, msg):
        dbg.logTrace(1, "*** ERROR:   %s" % msg)

    def checkLibraryDeps(self):
        wasError = False
        libnames = sorted(self.libs.keys())
        for name in libnames:
            lib = self.libs[name]
            if lib["installed"]:
                if len(lib["required_by"]) == 0:
                    # libnss_ dynamically loaded by libc, don't warning
                    if lib["path"].startswith("lib/libnss_"):
                        continue
                    self.log_warn("%s seems to be unused" % (str(lib["path"])))
        # Don't mix errors and warnings
        for name in libnames:
            lib = self.libs[name]
            if not lib["installed"] and "installedSymlink" not in lib:
                if len(lib["required_by"]) != 0:
                    if lib["path"] is None and " ".join(lib["required_by"]) == "LD_PRELOAD":
                        # Library doen't exists in rootfs but referenced by LD_PRELOAD
                        self.log_warn("%s library doesn't exists. required for: %s" % (name, " ".join(lib["required_by"])))
                    else:
                        self.log_err("%s library missing. required for: %s" % (name, " ".join(lib["required_by"])))
                        wasError = True
        return wasError


################################################################################
#
#   createUsersEntries(userNames, groupNames):
#
#   Create container-specific ld.so.preload file
#
################################################################################
    def appendLdSoPreload(self, libraryName):
        if (not libraryName):
            dbg.logTrace(2, "Skipping appending ls.so.preload, libraryName empty.")
            return

        self.makeFile(self.getPathLdSoPreloadFileTarget())
        with open(self.getPathLdSoPreloadFileTarget(), 'a') as fd:
            fd.write("%s\n" % libraryName)

################################################################################
#
#   createUsersEntries(userNames, groupNames):
#
#   Parse /etc/passwd and /etc/group on host rootfs and generate /etc/passwd
#   and /etc/group in container rootfs with minimum of information.
#   (Only container users amd groups).
#
################################################################################
    def createUserGroupEntries(self, userNames, groupNames):

        if (not userNames and not groupNames):
            dbg.logTrace(2, "Skipping passwd and group generation")
            return

        self.makeFile(self.getPathPasswdFileTarget())
        fd = open(self.getPathPasswdFileTarget(), 'w')
        with open(self.getPathPasswdFileHost(), "r") as file:
            for lines in file:
                for userName in list(userNames.values()):
                    if lines.startswith(userName + ":"):
                        fd.write(lines)
                        break
        file.close()
        fd.close()

        self.makeFile(self.getPathGroupFileTarget())
        fd = open(self.getPathGroupFileTarget(), 'w')
        with open(self.getPathGroupFileHost(), "r") as file:
            for lines in file:
                parts = lines.split(":")
                if (len(parts) > 3):
                    # include main groups of users
                    isMainGroup = False
                    for groupName in list(groupNames.values()):
                        if (parts[0] == groupName):
                            isMainGroup = True
                            break
                    # include any groups they are member of
                    members = parts[3].strip().split(",")
                    builtMembersString = ""
                    for member in members:
                        for userName in list(userNames.values()):
                            if (member == userName):
                                builtMembersString += "," + userName
                                break
                    if (isMainGroup or builtMembersString):
                        fd.write("%s:%s:%s:%s\n" % (parts[0], parts[1], parts[2], builtMembersString[1:]))
        file.close()
        fd.close()

################################################################################
#   userNameToUid(cCurrPath,userName):
#       Convert user name to UID
################################################################################
    def userNameToUid(self, userName):
        if len(self.nameToUidMap) == 0:
            with open(self.getPathPasswdFileHost(), "r") as file:
                for lines in file:
                    self.nameToUidMap[lines.split(":")[0]] = lines.split(":")[2]
                file.close()
        if userName not in self.nameToUidMap:
            raise Exception("No such user! [Name = %s]" % (userName))

        return self.nameToUidMap[userName]

################################################################################
#   groupNameToGid(cCurrPath,groupName):
#       Convert group name to GID
################################################################################
    def groupNameToGid(self, groupName):
        if len(self.groupToGidMap) == 0:
            with open(self.getPathGroupFileHost(), "r") as file:
                for lines in file:
                    self.groupToGidMap[lines.split(":")[0]] = lines.split(":")[2]
                file.close()
        if groupName not in self.groupToGidMap:
            raise Exception("No such group! [Name = %s]" % (groupName))
        return self.groupToGidMap[groupName]
