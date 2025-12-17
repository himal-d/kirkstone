SUMMARY = "Image with open source components used in RDK stack"

IMAGE_FEATURES += "package-management"

LICENSE = "MIT"

inherit core-image populate_sdk rdk-image cpc-image

IMAGE_ROOTFS_SIZE = "8192"

# QT4e (wrongly?) pulls in these packages which we don't want for now.
BAD_RECOMMENDATIONS = " \
    qt4-embedded-demos \
    qt4-embedded-examples \
    qt4-embedded-demos-doc \
    qt4-embedded-tools \
    qt4-embedded-assistant \
    "

IMAGE_INSTALL += "packagegroup-rdk-oss"

PACKAGE_TYPE = "OSS"

# you can pick Qt4e or Qt5 by (un)commenting the proper line below
# they can't be both installed simulatenously
# it's generally a good idea to remove <build>/tmp when switching back 
# and forth.
# IMAGE_INSTALL += "packagegroup-rdk-qt4e"

# for now, let's add 'debug stuff' in our images, we can revisit that later
# and create release vs debug builds.

DEPENDS += " jq jq-native"

IMAGE_INSTALL +="${@bb.utils.contains("DISTRO_FEATURES", "benchmark_enable", "packagegroup-rdk-debug-extra \
                                                             network-zero-conf \
                                                             network-hotplug \
                                                             dnsmasq \
                                                             gdbm \
                                                             perf \ 
                                                             stress-ng \
                                                             binutils \
                                                             sysint-min \
                                                             ca-certificates \
                                                             lttng-modules \
                                                             lttng-tools \
                                                             lttng-ust \
                                                             babeltrace \
                                                             liburcu \
                                                             perl-modules \
                                                             ptest-runner \
                                                             make \
                                                             rdm \
                                                             rdk-ca-store","packagegroup-rdk-debug \
                                                                            packagegroup-rdk-debug-extra",d)}"

IMAGE_INSTALL +="${@bb.utils.contains("DISTRO_FEATURES","benchmark_dbg_enable","gdb\
                                                                                stress-ng-dbg\
                                                                                stress-ng-dev","",d)}"          
