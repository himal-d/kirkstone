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
################################################################################
#            class cRootfs(object):
#
#                    Represents directories for container environment
#
################################################################################
class cLauncher(object):
    DEFAULT_LXCCPID_TIMEOUT = 3000
    DEFAULT_LXCCPID_TIMEOUT_PIDFILE = 30000

    class FunctionList(object):
        def __init__(self, launcherCommand, commandLine, pidFile, processName, shouldNotifySystemd, lxccpidTimeout, lxccpidTimeout_withPidFile, isProcessForking=False):
            self.launcherCommand = launcherCommand
            self.commandLine = commandLine
            self.pidFile = pidFile
            self.processName = processName
            self.shouldNotifySystemd = shouldNotifySystemd
            self.lxccpidTimeout = lxccpidTimeout
            self.lxccpidTimeout_withPidFile = lxccpidTimeout_withPidFile
            self.isProcessForking = isProcessForking

    def __init__(self, sanityCheck, rootfs):
        self.sanityCheck = sanityCheck
        self.rootfs = rootfs
        self.luncherName = ""
        self.execName = ""
        self.logFileOpt = ""
        self.logPriorityOpt = ""
        # dict is unordered, use list for names so that start, stop and other launchers items are in the right order
        self.functionNames = []
        self.functions = dict()
        self.uidAttach = ""
        self.gidAttach = ""
        self.containerName = ""
        self.lxccpidTimeout = cLauncher.DEFAULT_LXCCPID_TIMEOUT
        self.lxccpidTimeout_withPidFile = cLauncher.DEFAULT_LXCCPID_TIMEOUT_PIDFILE

    def matchVersion(self, parentNode, nodeName):
        node = None
        for childNode in parentNode.iter(nodeName):
            node = childNode
        return node

    def getContainerName(self, lxcParams):
        containerName = lxcParams.find("ContainerName")
        if (containerName is not None and containerName.text is not None):
            self.containerName = containerName.text
        else:
            self.containerName = self.rootfs.getSandboxName()

    def getLauncherParams(self, lxcParams):
        self.luncherName = lxcParams.find("LauncherName").text
        self.execName = lxcParams.find("ExecName").text
        execParams = lxcParams.find("ExecParams")
        if (execParams is not None and execParams.text is not None):
            self.execName += " " + execParams.text
        if execParams is not None and execParams.attrib.get("lxccpid_timeout"):
            self.lxccpidTimeout = execParams.attrib.get("lxccpid_timeout")
            self.lxccpidTimeout_withPidFile = self.lxccpidTimeout

        output = lxcParams.find("Output")
        if (output is not None and output.attrib["enable"] == "true"):
            logFileName = output.find("LogFile")
            if (logFileName is not None and logFileName.text is not None):
                self.logFileOpt = "-o " + logFileName.text
            logPriority = output.find("LogPriority")
            if (logPriority is not None and logPriority.text is not None):
                self.logPriorityOpt = "-l " + logPriority.text

    def verifyContainerName(self, lxcParams):
        containerName = lxcParams.find("ContainerName")
        if (containerName is not None and containerName.text is not None):
            containerName = containerName.text
        else:
            containerName = self.rootfs.getSandboxName()

        if (self.containerName != containerName):
            raise AttributeError("ContainerName doesn't match. base: %s, append: %s" % (self.containerName, containerName))

    def verifyLauncherName(self, lxcParams):
        # LauncherName doesn't need to exist in append container. If it does exist, it needs to be the same
        launcherName = lxcParams.find("LauncherName")
        if (launcherName is None):
            return

        if (self.luncherName != launcherName.text):
            raise AttributeError("LauncherName doesn't match. base: %s, append: %s" % (self.luncherName, launcherName.text))

    def genAttachParams(self, attachEntry):
        self.funcName = attachEntry.find("ParamName").text
        self.execAttach = attachEntry.find("ExecName").text
        paramAttach = attachEntry.find("ExecParams")
        if (paramAttach is not None and paramAttach.text is not None):
            self.execAttach += " " + paramAttach.text
        if paramAttach is not None and paramAttach.attrib.get("lxccpid_timeout"):
            self.lxccpidTimeoutAttach = paramAttach.attrib.get("lxccpid_timeout")
            self.lxccpidTimeoutAttach_withPidFile = self.lxccpidTimeoutAttach
        else:
            self.lxccpidTimeoutAttach = cLauncher.DEFAULT_LXCCPID_TIMEOUT
            self.lxccpidTimeoutAttach_withPidFile = cLauncher.DEFAULT_LXCCPID_TIMEOUT_PIDFILE

        userName = attachEntry.find("UserName")
        groupName = attachEntry.find("GroupName")
        # if no groupName provided, take userName as groupName
        if(groupName is None or groupName.text is None):
            groupName = userName

        if (self.sanityCheck.isPrivileged() and userName is not None and userName.text is not None and groupName is not None and groupName.text is not None):
            self.uidAttach = "-u " + self.rootfs.userNameToUid(userName.text)
            self.gidAttach = "-g " + self.rootfs.groupNameToGid(groupName.text)
        else:  # no uid and gid clean up class variables
            self.uidAttach = ""
            self.gidAttach = ""

    def appendFunctionList(self, functionName, function):
        self.functions[functionName] = function
        if (functionName not in self.functionNames):
            self.functionNames.append(functionName)
            self.functionNames.append("stop")  # make sure "stop" is always last
            self.functionNames.remove("stop")

    def generateSystemdNotify(self, node, command, isExec):
        FORKING_TAG = "forking"
        shouldNotifySystemd = False
        isProcessForking = False
        processName = ""
        pidfile = ""
        systemdNotify = node.find("SystemdNotify")
        if (systemdNotify is not None):
            if systemdNotify.attrib.get(FORKING_TAG, '') == "yes":
                isProcessForking = True
            if systemdNotify.attrib["create"] is not None and systemdNotify.attrib["create"] == "yes":
                shouldNotifySystemd = True
                if systemdNotify.find("PidFile") is not None:
                    pidfile = systemdNotify.find("PidFile").text
                if systemdNotify.find("ProcessName") is not None:
                    processName = systemdNotify.find("ProcessName").text
                else:
                    processName = node.find("ExecName").text.split()[0]

        launcherCommand = "start" if isExec else node.find("ParamName").text
        lxccpidTimeout = self.lxccpidTimeout if isExec else self.lxccpidTimeoutAttach
        lxccpidTimeout_withPidFile = self.lxccpidTimeout_withPidFile if isExec else self.lxccpidTimeoutAttach_withPidFile
        self.appendFunctionList(launcherCommand, self.FunctionList(launcherCommand, command, pidfile, processName, shouldNotifySystemd, lxccpidTimeout, lxccpidTimeout_withPidFile, isProcessForking))

    def createScript(self):

        fd = open(self.rootfs.getLauncherFileHost(), 'w')
        fd.write("#!/bin/sh\n\n")

        if (self.logPriorityOpt == ""):
            fd.write('. /usr/bin/lxc_log_level.inc\n\n')

        fd.write("case "'$1'" in\n")

        for name in self.functionNames:
            item = self.functions[name]

            fd.write("\t" + item.launcherCommand + ")\n")
            if (item.pidFile is not None and item.pidFile != ""):
                fd.write("\t\techo \"r " + item.pidFile + "\" | /bin/systemd-tmpfiles --remove /dev/stdin\n")
            fd.write("\t\t" + item.commandLine + (" &" if item.shouldNotifySystemd else "") + "\n")

            if (item.shouldNotifySystemd):
                if item.isProcessForking is True:
                    self.generateScriptToFindPidOfForkingProcess(fd, item.processName, item.pidFile, item.lxccpidTimeout, item.lxccpidTimeout_withPidFile)
                elif (item.pidFile is not None and item.pidFile != ""):
                    fd.write('\t\tCHILD_PID=$(/usr/bin/lxccpid --ppid $! "{processName}" {lxccpidTimeout} "{pidFile}")\n'.format(processName=item.processName, lxccpidTimeout=item.lxccpidTimeout_withPidFile, pidFile=item.pidFile))
                else:
                    fd.write('\t\tCHILD_PID=$(/usr/bin/lxccpid --ppid $! "{processName}" {lxccpidTimeout})\n'.format(processName=item.processName, lxccpidTimeout=item.lxccpidTimeout))
                fd.write("\t\tif [ -z $CHILD_PID ]; then\n")
                fd.write('\t\t\techo "CHILD_PID=$CHILD_PID for {processName}"\n'.format(processName=item.processName))
                fd.write("\t\t\texit 1\n")
                fd.write("\t\telse\n")
                fd.write("\t\t\t/bin/systemd-notify --ready MAINPID=$CHILD_PID\n")
                fd.write("\t\tfi\n")
            fd.write("\t;;\n")
        fd.write("\t*)\n\t\texit 1\n")
        fd.write("esac\n")

    def generateScriptToFindPidOfForkingProcess(self, fd, processName, pidFile, lxccpidTimeout, lxccpidTimeout_withPidFile):
        fd.write("\n\t\t#Find lxc-execute of the container\n")
        fd.write('\t\tE_PID=$(/usr/bin/lxccpid --ppid 1 "/usr/bin/lxc-execute -n {containerName}" {timeout})\n'.format(containerName=self.containerName, timeout=cLauncher.DEFAULT_LXCCPID_TIMEOUT))
        fd.write("\n\t\t#Find lxc-static of the container\n")
        fd.write('\t\tI_PID=$(/usr/bin/lxccpid --ppid $E_PID "/init.lxc.static" {timeout})\n'.format(timeout=cLauncher.DEFAULT_LXCCPID_TIMEOUT))
        fd.write("\n\t\t#Find the forking process to be started inside the container\n")
        if (pidFile is not None and pidFile != ""):
            fd.write('\t\tCHILD_PID=$(/usr/bin/lxccpid --ppid $I_PID "{processName}" {timeout} "{pidFile}")\n'.format(processName=processName, timeout=lxccpidTimeout_withPidFile, pidFile=pidFile))
        else:
            fd.write('\t\tCHILD_PID=$(/usr/bin/lxccpid --ppid $I_PID "{processName}" {timeout})\n'.format(processName=processName, timeout=lxccpidTimeout_withPidFile))

    def getLogFileOpt(self):
        if (self.logFileOpt == ""):
            return "-o none "
        else:
            return self.logFileOpt

    def getLogPriorityOpt(self):
        if (self.logPriorityOpt == ""):
            return "-l ${LXC_LOG_LEVEL}"
        else:
            return self.logPriorityOpt

    def createLauncher(self, lxcParams):

        self.getLauncherParams(lxcParams)
        self.getContainerName(lxcParams)
        self.rootfs.setLauncherName(self.luncherName)

        command = "/usr/bin/lxc-execute -n %s  %s %s -f %s -- %s" % (self.containerName,
                                                                     self.getLogFileOpt(),
                                                                     self.getLogPriorityOpt(),
                                                                     self.rootfs.getConfFileTarget(),
                                                                     self.execName)

        self.generateSystemdNotify(lxcParams, command, True)

        self.createAttached(lxcParams)

    def createAttached(self, lxcParams):
        for attachEntry in lxcParams.iter('Attach'):

            self.genAttachParams(attachEntry)
            Attachcommand = "/usr/bin/lxc-attach -n %s  %s %s -f %s %s %s -- %s" % (self.containerName,
                                                                                    self.getLogFileOpt(),
                                                                                    self.getLogPriorityOpt(),
                                                                                    self.rootfs.getConfFileTarget(),
                                                                                    self.uidAttach,
                                                                                    self.gidAttach,
                                                                                    self.execAttach)

            self.generateSystemdNotify(attachEntry, Attachcommand, False)

        stopFunction = lxcParams.find("StopFunction")
        if (stopFunction is not None):
            if stopFunction.attrib["enable"] == "true":
                stop_options = ""
                try:
                  if stopFunction.attrib["kill"] == "true":
                    stop_options = "-k"
                except KeyError:
                  pass
                StopCommand = "/usr/bin/lxc-stop %s -n %s  %s %s" % (stop_options,
                                                                  self.containerName,
                                                                  self.getLogFileOpt(),
                                                                  self.getLogPriorityOpt())
                self.appendFunctionList("stop", self.FunctionList("stop", StopCommand, "", "", 0, 0, False))

        self.createScript()

    def appendLauncher(self, lxcParams):
        self.verifyContainerName(lxcParams)
        self.verifyLauncherName(lxcParams)
        try:
            self.getLauncherParams(lxcParams)
            command = "/usr/bin/lxc-execute -n %s  %s %s -f %s -- %s" % (self.containerName,
                                                                         self.getLogFileOpt(),
                                                                         self.getLogPriorityOpt(),
                                                                         self.rootfs.getConfFileTarget(),
                                                                         self.execName)

            self.generateSystemdNotify(lxcParams, command, True)
        except Exception:
            pass  # appending xml doesn't need to contain the main launcher

        self.createAttached(lxcParams)
