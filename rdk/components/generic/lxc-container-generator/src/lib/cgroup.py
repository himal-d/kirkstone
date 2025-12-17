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
#   class DeviceCgroup(object):
#
#       Represents info for container device cgroups
#
################################################################################
class cCgroup(object):
    def __init__(self, sanityCheck, swapEnabled):
        self.sanityCheck = sanityCheck
        self.swapEnabled = swapEnabled

    def devNull(self):
        return "# /dev/null\n" + self.sanityCheck.confOptsDict['cgroup_devices_allow'] + " = c 1:3 rw\n"

    def devZero(self):
        return "# /dev/zero\n" + self.sanityCheck.confOptsDict['cgroup_devices_allow'] + " = c 1:5 rw\n"

    def devFull(self):
        return "# /dev/full\n" + self.sanityCheck.confOptsDict['cgroup_devices_allow'] + " = c 1:7 rw\n"

    def devRandom(self):
        return "# /dev/random\n" + self.sanityCheck.confOptsDict['cgroup_devices_allow'] + " = c 1:8 rw\n"

    def devURandom(self):
        return "# /dev/urandom\n" + self.sanityCheck.confOptsDict['cgroup_devices_allow'] + " = c 1:9 rw\n"

    def devTty(self):
        return "# /dev/tty\n" + self.sanityCheck.confOptsDict['cgroup_devices_allow'] + " = c 5:0 rw\n"

    def createLxcConfDevicesCGroup(self, CGroupNode):

        entry = ""
        deviceCgroup = CGroupNode.find("DeviceCgroup")
        if (deviceCgroup is not None):
            for device in deviceCgroup:
                if (device is not None and device.text is not None):
                    if ("name" in device.attrib and device.attrib["name"] is not None):
                        entry += "# %s\n" % device.attrib["name"]
                    if (device.tag == "DevicesDeny"):
                        entry += self.sanityCheck.confOptsDict['cgroup_devices_deny'] + " = %s\n" % device.text
                    elif (device.tag == "DevicesAllow"):
                        entry += self.sanityCheck.confOptsDict['cgroup_devices_allow'] + " = %s\n" % device.text
                elif (device.tag == "AllowDefaultDevices" and "enable" in device.attrib and device.attrib["enable"] == "yes"):
                    entry += "# default allowed devices\n"
                    entry += self.devNull()
                    entry += self.devZero()
                    entry += self.devFull()
                    entry += self.devRandom()
                    entry += self.devURandom()
                    entry += self.devTty()
        return entry

    def createCGroupConf(self, CGroupNode):

        entry = ""
        if CGroupNode is not None:

            entry += "\n# CGroup Container Configuration\n"

        # Directory for cgroup
#            if 'cgroup_dir' in self.sanityCheck.confOptsDict:
#                entry += self.sanityCheck.confOptsDict['cgroup_dir'] + " = lxc\n"
            if 'cgroup_relative' in self.sanityCheck.confOptsDict:
                entry += self.sanityCheck.confOptsDict['cgroup_relative'] + " = 1\n"

        # MEMORY
            memoryLimit = CGroupNode.find("MemoryLimit")
            if (memoryLimit is not None and memoryLimit.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_memory_limit'] + " = %s\n" % memoryLimit.text

            if (self.swapEnabled == True):
                memoryMemSwapLimit = CGroupNode.find("MemoryMemSwapLimit")
                if (memoryMemSwapLimit is None):
                    memoryMemSwapLimit = memoryLimit
                if (memoryMemSwapLimit is not None and memoryMemSwapLimit.text is not None):
                    entry += self.sanityCheck.confOptsDict['cgroup_memory_memsw_limit'] + " = %s\n" % memoryMemSwapLimit.text

            SoftMemoryLimit = CGroupNode.find("SoftMemoryLimit")
            if (SoftMemoryLimit is not None and SoftMemoryLimit.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_memory_soft_limit'] + " = %s\n" % SoftMemoryLimit.text

            OOMControl = CGroupNode.find("OOMControl")
            if (OOMControl is not None and OOMControl.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_memory_oom_control'] + " = %s\n" % OOMControl.text

        # CPU
            CpuShares = CGroupNode.find("CpuShares")
            if (CpuShares is not None and CpuShares.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_cpu_shares'] + " = %s\n" % CpuShares.text

            CpuRtRuntimeUS = CGroupNode.find("CpuRtRuntimeUS")
            if (CpuRtRuntimeUS is not None and CpuRtRuntimeUS.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_cpu_rt_runtime_us'] + " = %s\n" % CpuRtRuntimeUS.text

            CpuRtRuntimePeriod = CGroupNode.find("CpuRtRuntimePeriod")
            if (CpuRtRuntimePeriod is not None and CpuRtRuntimePeriod.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_cpu_rt_period_us'] + " = %s\n" % CpuRtRuntimePeriod.text

        # CPUSET
            CpusetCpus = CGroupNode.find("CpusetCpus")
            if (CpusetCpus is not None and CpusetCpus.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_cpuset_cpus'] + " = %s\n" % CpusetCpus.text

            CpusetCpuExlusive = CGroupNode.find("CpusetCpuExlusive")
            if (CpusetCpuExlusive is not None and CpusetCpuExlusive.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_cpuset_cpu_exclusive'] + " = %s\n" % CpusetCpuExlusive.text

            CpusetMems = CGroupNode.find("CpusetMems")
            if (CpusetMems is not None and CpusetMems.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_cpuset_mems'] + " = %s\n" % CpusetMems.text

            CpusetMemExclusive = CGroupNode.find("CpusetMemExclusive")
            if (CpusetMemExclusive is not None and CpusetMemExclusive.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_cpuset_mem_exclusive'] + " = %s\n" % CpusetMemExclusive.text

            CpusetMemHardwall = CGroupNode.find("CpusetMemHardwall")
            if (CpusetMemHardwall is not None and CpusetMemHardwall.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_cpuset_mem_hardwall'] + " = %s\n" % CpusetMemHardwall.text

            CpusetMemoryMigrate = CGroupNode.find("CpusetMemoryMigrate")
            if (CpusetMemoryMigrate is not None and CpusetMemoryMigrate.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_cpuset_memory_migrate'] + " = %s\n" % CpusetMemoryMigrate.text

            CpusetMemoryPreasureEnabled = CGroupNode.find("CpusetMemoryPreasureEnabled")
            if (CpusetMemoryPreasureEnabled is not None and CpusetMemoryPreasureEnabled.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_cpuset_memory_pressure_enabled'] + " = %s\n" % CpusetMemoryPreasureEnabled.text

            CpusetMemoryPreasure = CGroupNode.find("CpusetMemoryPreasure")
            if (CpusetMemoryPreasure is not None and CpusetMemoryPreasure.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_cpuset_cpuset_memory_pressure'] + " = %s\n" % CpusetMemoryPreasure.text

            CpusetMemorySpreadPage = CGroupNode.find("CpusetMemorySpreadPage")
            if (CpusetMemorySpreadPage is not None and CpusetMemorySpreadPage.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_cpuset_cpuset_memory_spread_page'] + " = %s\n" % CpusetMemorySpreadPage.text

            CpusetMemorySpreadSlab = CGroupNode.find("CpusetMemorySpreadSlab")
            if (CpusetMemorySpreadSlab is not None and CpusetMemorySpreadSlab.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_cpuset_cpuset_memory_spread_slab'] + " = %s\n" % CpusetMemorySpreadSlab.text

            CpusetSchedLoadBalance = CGroupNode.find("CpusetSchedLoadBalance")
            if (CpusetSchedLoadBalance is not None and CpusetSchedLoadBalance.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_cpuset_cpuset_sched_load_balance'] + " = %s\n" % CpusetSchedLoadBalance.text

            CpusetSchedDomainLevel = CGroupNode.find("CpusetSchedDomainLevel")
            if (CpusetSchedDomainLevel is not None and CpusetSchedDomainLevel.text is not None):
                entry += self.sanityCheck.confOptsDict['cgroup_cpuset_cpuset_sched_relax_domain_level'] + " = %s\n" % CpusetSchedDomainLevel.text

            entry += "\n# CGroup Device Configuration\n"
            entry += self.createLxcConfDevicesCGroup(CGroupNode)

        return entry
