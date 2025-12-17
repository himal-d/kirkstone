FILESEXTRAPATHS_prepend := "${THISDIR}/${BPN}:"
SRC_URI += " \
   file://viconsole.cfg \
   file://rdkb.cfg \
   file://shasum.cfg \
   file://tftp.cfg \
   file://netstat.cfg \
   file://tdk-needed-tools.cfg \
   file://telnet.cfg \
   file://date.cfg \
   file://ipneighbor.cfg \
   file://top.cfg \
   file://archival.cfg \
   file://traceroute.cfg \
   file://blkid.cfg \
   ${@bb.utils.contains('DISTRO_FEATURES', 'morty', ' file://udhcp.patch file://0001-networking-add-ip-neigh-command.patch file://ip6_neigh_show_crash.patch ' , '' ,d)} \
   ${VERSION_PATCHES} \
   "

SRC_URI_append_rpi = " \
   file://nice.cfg \
   "
SRC_URI_remove_broadband += " \
   file://blkid.cfg \
   "
SRC_URI_append = " file://devmem.cfg "
SRC_URI_append_morty = " file://enable_ps_wide.cfg "
SRC_URI_append_broadband = " ${@bb.utils.contains_any('DISTRO_FEATURES', 'dunfell kirkstone', ' file://enable_ps_wide.cfg ','',d)}"
SRC_URI_append = " file://enable_ar.cfg"
SRC_URI_remove_morty = " file://devmem.cfg file://enable_ar.cfg "
VERSION_PATCHES ?= ""

PTEST_ENABLED = "${@bb.utils.contains('DISTRO_FEATURES', 'benchmark_enable', '1', '0', d)}"
inherit ptest-package-deploy
