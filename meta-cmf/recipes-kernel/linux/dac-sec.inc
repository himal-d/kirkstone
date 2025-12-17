# Provides a generic configuration for
# Linux kernel needed for OMI service.
#
# This approach allows us to keep the configuration
# in one single location and avoids adding .bbappend
# files to individual meta layers for every supported
# platform for every possible kernel package name.
#
# Unfortunately, Yocto does not allow us to easily
# prepare a single .bbappend for a package which
# provides a "virtual/kernel" without knowing upfront
# its name.
#
# If your platform contains a linux kernel package
# (the one which PROVIDES="virtual/kernel")
# with a name not existing in this directory,
# please consider adding a new one here to let
# OMI working on it.

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

# By default OMI functionality (in RDK) is controlled
# by DAC-sec distro feature see: rdkservices_git.bb
# for more details.
SRC_URI += "${@bb.utils.contains('DISTRO_FEATURES', 'DAC-sec', 'file://dac-sec.cfg', '', d)}"
