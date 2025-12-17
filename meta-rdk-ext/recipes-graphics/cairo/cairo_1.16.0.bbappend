FILESEXTRAPATHS_prepend := "${THISDIR}/${BP}:"
# Add egl/gles to config
PACKAGECONFIG_append_class-target = " egl"
PACKAGECONFIG_append_class-target = " ${@bb.utils.contains('DISTRO_FEATURES', 'x11', '', 'glesv2', d)}"
PACKAGECONFIG_remove = "directfb"

SRC_URI += "file://0006-add-egl-device-create.patch"
SRC_URI += "file://0009-error-check-just-in-debug.patch"

SRC_URI += "file://0001-add-noaa-compositor-for-v1.16.patch"
SRC_URI += "file://0010-Fix-performance-and-memory-consumption-issue.patch"
SRC_URI += "file://cairo_scaled_font_destroy_Assertion.patch"
SRC_URI += "file://0011-fix-device-errors-for-glesv2-contexts.patch"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI += " ${@bb.utils.contains('DISTRO_FEATURES', 'kirkstone', 'file://CVE-2020-35492_cairo_1.16.0_fix_kirkstone.patch', 'file://CVE-2020-35492_cairo_1.16.0_fix.patch', d)}"
