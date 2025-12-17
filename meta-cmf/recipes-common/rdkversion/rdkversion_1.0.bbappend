SRC_URI_remove = "${RDK_GENERIC_ROOT_GIT}/rdkversion/generic;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH};name=rdkversion"
SRC_URI += "${CMF_GIT_ROOT}/rdk/components/generic/rdkversion;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=rdkversion"

inherit coverity

INCLUDE_DIRS_aarch64 += " \
    -I${PKG_CONFIG_SYSROOT_DIR}/usr/include/glib-2.0 \
    -I${PKG_CONFIG_SYSROOT_DIR}/usr/lib64/glib-2.0/include \
    -I${PKG_CONFIG_SYSROOT_DIR}/usr/lib/glib-2.0/include \
    "
