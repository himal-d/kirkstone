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
import sys
from optparse import OptionParser

from lib import cRootfs
from lib import cLauncher
from lib import cConfig
from lib import cSanityCheck
from lib import dbg

try:
    from lib.dobby.config import cConfigDobby
    from lib.dobby.rootfs import cRootfsDobby
    from lib.dobby.launcher import cLauncherDobby
except ImportError:
    cConfigDobby = None
    cRootfsDobby = None
    cLauncherDobby = None

# per container structs to preserve container information when processing container "append" xml
# indexed by container name
containers_rootfs = dict()
containers_launchers = dict()
containers_UserNames = dict()
containers_GroupNames = dict()
containers_UserNameRootFs = dict()
containers_GroupNameRootFs = dict()

# Force python XML parser not faster C accelerators
# because we can't hook the C implementation
sys.modules['_elementtree'] = None
import xml.etree.ElementTree as ET


class LineNumberingParser(ET.XMLParser):
    def _start_list(self, *args, **kwargs):
        # Here we assume the default XML parser which is expat
        # and copy its element position attributes into output Elements
        element = super(self.__class__, self)._start_list(*args, **kwargs)
        element._start_line_number = self.parser.CurrentLineNumber
        return element

    def _end(self, *args, **kwargs):
        element = super(self.__class__, self)._end(*args, **kwargs)
        element._end_line_number = self.parser.CurrentLineNumber
        return element


def parse_xml(inputXml, rootfsPath, shareRootfs, disableCrashReporting, secure, tags, enableMountCheck, extRootfsList, swapEnabled, capsGenerationEnabled):
    if isinstance(inputXml, bytes):
        container = ET.fromstring(inputXml, parser=LineNumberingParser())  # from XMLMerger()
        inputXml = "merged-xml"
    else:
        container = ET.parse(inputXml, parser=LineNumberingParser()).getroot()  # file name

    process_xml(container, inputXml, rootfsPath, shareRootfs, disableCrashReporting, secure, tags, enableMountCheck, extRootfsList, swapEnabled, capsGenerationEnabled)
    # Find include
    incFiles = container.findall("Include")
    for incFile in incFiles:
        # Constract path to include file
        incFilePath = os.path.normpath(os.path.join(os.path.dirname(os.path.realpath(__file__)), "..", "include", incFile.text))
        if not os.path.exists(incFilePath):
            raise Exception("[!!! ERROR !!!] No such include file (%s)" % incFilePath)
        # Parse include file
        incTree = ET.parse(incFilePath, parser=LineNumberingParser())
        incContainer = incTree.getroot()
        incContainer.set("SandboxName", container.attrib["SandboxName"])
        process_xml(incContainer, incFilePath, rootfsPath, shareRootfs, disableCrashReporting, secure, tags, enableMountCheck, extRootfsList, swapEnabled, capsGenerationEnabled)


def process_xml(container, inputXml, rootfsPath, shareRootfs, disableCrashReporting, secure, tags, enableMountCheck, extRootfsList, swapEnabled, capsGenerationEnabled):
    if dbg.traceLevel >= 1:
        print("Process XML (source: {})".format(inputXml))
        ET.dump(container)

    name = container.attrib["SandboxName"]
    append = False
    dbg.setName(name)

    if ('APPEND' in container.attrib):
        append = True
        print("\n\n===================================================================")
        print("\tGENERATE %s CONTAINER APPEND FOR %s " % (name, container.attrib["APPEND"]))
        print("====================================================================")
    else:
        print("\n\n===================================================================")
        print("\tGENERATE %s CONTAINER" % (name))
        print("==================================================================")

    main_base = os.path.dirname(__file__)
    confPath = main_base + "/conf"

    sanityCheck = cSanityCheck(inputXml, secure, name, rootfsPath, confPath, tags, enableMountCheck, extRootfsList)
    sanityCheck.filter_out_inactive_tags(container)

    orig_name = name
    containerType = container.get("Type")
    if containerType == "dobby":
        if cRootfsDobby is None or cLauncherDobby is None or cConfigDobby is None:
            raise Exception("dobby generator missing")
        name = "%s_%s" % (orig_name, containerType)
        rootfs_class = cRootfsDobby
        launcher_class = cLauncherDobby
        config_class = cConfigDobby
    else:
        rootfs_class = cRootfs
        launcher_class = cLauncher
        config_class = cConfig

    if name not in containers_rootfs:
        containers_rootfs[name] = rootfs_class(orig_name, rootfsPath, shareRootfs, extRootfsList)
    rootfs = containers_rootfs[name]
    if(not append):
        rootfs.createContainerTree()

    if name not in containers_launchers:
        containers_launchers[name] = launcher_class(sanityCheck, rootfs)
    launcher = containers_launchers[name]
    lxcParamsNode = launcher.matchVersion(container, "LxcParams")
    if (lxcParamsNode is not None):
        if(append):
            launcher.appendLauncher(lxcParamsNode)
        else:
            launcher.createLauncher(lxcParamsNode)

    if name not in containers_UserNames:
        containers_UserNames[name] = dict()  # usernames are indexed by xml ParamName. For main launcher use "start"
    userNames = containers_UserNames[name]

    if name not in containers_GroupNames:
        containers_GroupNames[name] = dict()
    groupNames = containers_GroupNames[name]

    config = config_class(sanityCheck, rootfs, secure, not disableCrashReporting, append,
                     userNames.get("start"), groupNames.get("start"), swapEnabled, capsGenerationEnabled) # pass main launcher user and group from "base" XML
    lxcConfigNode = container.find("LxcConfig")
    if (lxcConfigNode is not None):
        config.createLxcConf(lxcConfigNode)

    config.processUsersAndGroups(lxcParamsNode, lxcConfigNode, userNames, groupNames)

    if (lxcConfigNode is not None):
        # now assign uid:gid to rootfs files
        userName = lxcConfigNode.find("UserNameRootFs")

        # if UserNameRootFs not provided fall back to the one given in base xml
        if (userName is None or userName.text is None):
            userName = containers_UserNameRootFs.get(name)
            # if this is a base xml or the value was not provided in base xml, try UserName
            if (userName is None or userName.text is None):
                userName = lxcConfigNode.find("UserName")
        if (userName is not None):
            dbg.logTrace(3, "userName: %s" % userName.text)

        groupName = lxcConfigNode.find("GroupNameRootFs")
        # if GroupNameRootFs not provided fall back to the one given in base xml
        if (groupName is None or groupName.text is None):
            groupName = containers_GroupNameRootFs.get(name)
            # if this is a base xml or the value was not provided in base xml, try GroupName
            if (groupName is None or groupName.text is None):
                groupName = lxcConfigNode.find("GroupName")
                # if no groupName provided, take userName as groupName
                if (groupName is None or groupName.text is None):
                    groupName = userName
        if (groupName is not None):
            dbg.logTrace(3, "groupName: %s" % groupName.text)

        if (userName is not None and userName.text is not None):
            uid = rootfs.userNameToUid(userName.text)
            gid = rootfs.groupNameToGid(groupName.text)

            rootfs.setUpContainersRights(uid, gid)

            containers_UserNameRootFs[name] = userName
            containers_GroupNameRootFs[name] = groupName
        else:
            rootfs.setUpContainersRights("0", "0")


class HashableDictionary(dict):
    def __hash__(self):
        return hash(tuple(sorted(self.items())))


class XMLMerger(object):
    # The list of XML compound elements.
    #
    # The directory structure is as follows:
    #  - key (in fact a tuple) is used to check if the element
    #    should be treated as a compound one.
    #
    #  - value is used for storing the element_key (used to.
    #    uniquely identify the XML compound element
    #    amongst others).
    #
    # Structure: ( parent_tag, tag      ): element_key
    COMPOUNDS = {('LxcConfig', 'Network'): 'Name',
                 ('LxcParams', 'Attach'): 'ParamName',
                 ('LxcParams', 'SystemdNotify'): 'PidFile',
                 ('MountPoints', 'Entry'): 'Destination',
                 ('MoveContent', 'Entry'): 'Destination'}

    def __init__(self, trees):
        self.xmlroots = [r.getroot() for r in trees]
        if self.xmlroots is not None:
            dbg.setName(self.xmlroots[0].get("SandboxName"))

    def merge(self):
        for x in self.xmlroots[1:]:
            dbg.logTrace(1, "Merging container configuration with %s.%s"
                         % (x.get("SandboxName"), x.get("APPEND")))
            self.merge_element(self.xmlroots[0], x)
        return ET.tostring(self.xmlroots[0])

    def element2key(self, element):
        return (element.tag, HashableDictionary(element.attrib))

    def merge_element(self, one, other, parent_tag=''):
        tag2element = {self.element2key(elem): elem for elem in one}

        for e2 in other:
            # The following are treated as a leaf:
            #  - element with no children,
            #  - compound XML element.
            if len(e2) == 0 or (parent_tag, e2.tag) in self.COMPOUNDS:
                found = False

                # Check if the same element already exists then:
                #  - for XML compound element merge their sub-element recursively,
                #  - for simple XML element do nothing,
                # otherwise (if the element does not exists) then simply add it.
                for e1 in one:
                    # For "the same" element comparison use element tag and list of attributes.
                    if self.element2key(e1) == self.element2key(e2):
                        try:
                            # Check if this is XML compound element
                            tag = self.COMPOUNDS[(parent_tag, e2.tag)]
                            # then try to uniquely identify it
                            if self.is_element_tag_text_equal(e1, e2, tag):
                                if parent_tag == "MountPoints":
                                    # There is something wrong with the configuration if there are
                                    # either similar or even equal entries for the same mount point.
                                    # Equal ones can be ignored, similar should be verified.
                                    entries_are_equal = self.compare_mount_points(e1, e2)
                                    if not entries_are_equal:
                                        exit(1)
                                found = True
                                # finally merge their sub-elements
                                self.merge_element(e1, e2, parent_tag='')
                                break
                        except KeyError:
                            # For simple XML elements just compare the text
                            if self.is_stripped_equal(e1.text, e2.text):
                                found = True
                                break

                # Element not found, simply append it.
                if not found:
                    tag2element[self.element2key(e2)] = e2
                    one.append(e2)
            else:
                # This is neither leaf nor XML compound element,
                # so either try to recursively merge it or append
                # depending on whether it exists on the other
                # XML tree or not respectively.
                key = self.element2key(e2)
                try:
                    e1 = tag2element[key]
                    assert e1.tag == e2.tag
                    self.merge_element(e1, e2, e1.tag)
                except KeyError:
                    tag2element[key] = e2
                    one.append(e2)

    def is_element_tag_text_equal(self, element_1, element_2, tag):
        tag_1 = element_1.find(tag)
        tag_2 = element_2.find(tag)
        if (tag_1 is None or tag_2 is None):
            return False
        return tag_1.text == tag_2.text

    def is_stripped_equal(self, text1, text2):
        if text1 == text2:
            return True
        if text1 is not None:
            text1 = text1.strip(' \t\r\n')
        if text2 is not None:
            text2 = text2.strip(' \t\r\n')
        return text1 == text2

    def el_text(self, element, tag):
        tag_e = element.find(tag)
        if tag_e is None:
            return ""
        return tag_e.text

    def compare_mount_points(self, element_1, element_2):
        dst = self.el_text(element_1, 'Destination')
        src_1 = self.el_text(element_1, 'Source')
        src_2 = self.el_text(element_2, 'Source')
        opts_1 = self.el_text(element_1, 'Options')
        opts_2 = self.el_text(element_2, 'Options')
        is_equal = (src_1 == src_2 and opts_1 == opts_2)
        if is_equal:
            dbg.logTrace(1, "*** WARNING: Found equal entries for the mountpoint '%s' ('%s', '%s')"
                         % (dst, src_1, opts_1))
        else:
            dbg.logTrace(1, "*** ERROR: Found not equal entries for the mountpoint '%s' ('%s', '%s') vs ('%s', '%s')"
                         % (dst, src_1, opts_1, src_2, opts_2))
        return is_equal

def group_xml_files(files):
    """Groups XML files.

     Return dictionary where:
        object - is a list of element trees (returned from ET.parse) constructed in a way that APPEND files
                 are added to the end of the list while non-APPEND files are inserted into index 0,
        key - is the value of the "SandboxName" attribute of the XML document.

    Args:
        files - a list of XML filenames to be parsed
    """
    containers = {}
    global_appends = {}

    for file in files:
        tree = ET.parse(file, parser=LineNumberingParser())
        container = tree.getroot()
        try:
            sandbox_name = container.attrib["SandboxName"]
        except KeyError:
            sandbox_name = None

        append = False
        if ('APPEND' in container.attrib):
            append = True

        if sandbox_name is None and append is False:
            raise Exception("File {} does not have SandboxName nor APPEND.".format(file))

        if sandbox_name is None and append is True:
            global_appends[file] = tree  # Global APPEND file
            continue

        if sandbox_name not in containers:
            containers[sandbox_name] = [tree]
        else:
            if not append:
                containers[sandbox_name].insert(0, tree)
            else:
                containers[sandbox_name].append(tree)

    for sandbox in containers:  # Add global APPEND file to every sandbox
        for appends in global_appends:
            containers[sandbox].append(global_appends[appends])

    return containers


def main():

    parser = OptionParser()

    parser.usage = """
genContainer.py [options] [files]

Example:
genContainer.py -r ~/user/rdk/some_path_to_rootfs -R ro -s lxc_conf_DIBBLER.xml
    will generate secure DIBBLER container at given rootfs for debug version with architecture arm_16.4 and OE 2.1
    Note: Several input files can be provided in one command line
          It is recommended to pass all .xml files related to one container in one run to handle
          dependencies correctly
"""

    parser.add_option("-r", "--rootfs", dest = "rootfs",
                                        action = "store", type = "string",
                                        help = "rootfs directory where container dir and its files will be generated")

    parser.add_option("-s", "--secure",
                                        dest = "secure", action = "store_true",
                                        help = "Create unprivileged container")

    parser.add_option("-t", "--tags",
                                        dest = "tags", action = "store", type = "string",
                                        help = "tags")

    parser.add_option("-e", "--sharedRootfs",
                                        dest = "sharedRootfs", action = "store_true",
                                        help = "Containers share rootfs with host")

    parser.add_option("-c", "--crashReporting",
                                        dest = "disableCrashReporting", action = "store_true",
                                        help = "Disable crashreporting for container, regardless of XML config")

    parser.add_option("-S", "--sanity",
                                        dest = "enableMountCheck", action = "store_true",
                                        help = "Enable sanity check")

    parser.add_option("-x", "--extRootfsList",
                                        dest = "extRootfsList", action = "store", type = "string",
                                        help = "Optional list of additonal rootfs'es")

    parser.add_option("--swap",
                                        dest = "swapEnabled", action = "store_true",
                                        help = "Enable swap support")

    parser.add_option("-k", "--capKeep",
                                        dest = "capsGenerationEnabled", action = "store_true",
                                        help = "Add appropriate lxc.cap.keep entries")

    (options, args) = parser.parse_args()

    rootfsPath = options.rootfs

    secure = False if options.secure is None else options.secure

    sharedRootfs = False if options.sharedRootfs is None else options.sharedRootfs

    disableCrashReporting = False if options.disableCrashReporting is None else options.disableCrashReporting

    enableMountCheck = False if options.enableMountCheck is None else options.enableMountCheck

    tags = options.tags

    swapEnabled = False if options.swapEnabled is None else options.swapEnabled

    capsGenerationEnabled = False if options.capsGenerationEnabled is None else options.capsGenerationEnabled

    extRootfsList = []
    if options.extRootfsList:
        extRootfsList = options.extRootfsList.split(",")

    if not (rootfsPath) or len(args) == 0:
        print(parser.print_help())
        exit(1)

    containers = group_xml_files(args)

    for key in containers:
        trees = containers[key]
        merged_tree = XMLMerger(trees).merge()
        parse_xml(merged_tree, rootfsPath, sharedRootfs, disableCrashReporting, secure, tags, enableMountCheck, extRootfsList, swapEnabled, capsGenerationEnabled)

    wasError = False
    for rootfs in containers_rootfs.values():
        if rootfs.checkLibraryDeps():
            wasError = True

    if wasError:
        sys.exit(1)


if __name__ == "__main__":
    main()
