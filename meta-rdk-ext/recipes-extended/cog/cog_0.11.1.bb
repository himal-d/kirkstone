require cog.inc
require cog-cmake.inc

SRC_URI_append = " file://0001-lower-webkit-version-requirement.patch"
SRC_URI_remove_skyxione-alpaca-de = " file://0001-lower-webkit-version-requirement.patch"
SRC_URI[sha256sum] = "6cbd60386e20bad62adccb26a2488c9eea0b609b12336476fac1fb71fcd26572"

PACKAGECONFIG ?= ""
