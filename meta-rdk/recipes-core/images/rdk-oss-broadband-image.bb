SUMMARY = "Image with open source components used in RDK stack"

IMAGE_FEATURES += "package-management"

LICENSE = "MIT"

inherit core-image rdk-image cpc-image

IMAGE_ROOTFS_SIZE = "8192"

PACKAGE_TYPE = "OSS"

IMAGE_INSTALL += "${@bb.utils.contains("DISTRO_FEATURES", "benchmark_enable","packagegroup-rdk-oss-broadband \
                                                                              broadcom-lattice-cli \
                                                                              nw-zero-conf-broadband \
                                                                              rbus \
                                                                              ca-certificates \
									      rdk-ca-store \
							                      stress-ng \
									      perf \
                                                                              rdm \
                                                                              perl-modules\
                                                                              make \
                                                                              ","",d)}"
                                                                              
                                                                              
IMAGE_INSTALL_remove = "${@bb.utils.contains("DISTRO_FEATURES", "benchmark_enable","packagegroup-meshwifi","",d)}"


