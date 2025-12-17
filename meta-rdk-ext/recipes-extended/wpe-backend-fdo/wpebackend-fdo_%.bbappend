FILESEXTRAPATHS_append := "${THISDIR}/files:"
DEPENDS += "virtual/egl"

SRC_URI += "file://0001-Broadcom-workaroun-wayland-egl-config-check-failure.patch"

REQUIRED_DISTRO_FEATURES += "wayland"
