
# Disable PHP features not required for RDK-B

PACKAGECONFIG_remove = "mysql"
PACKAGECONFIG_remove = "sqlite3"
PACKAGECONFIG_remove = "imap"

EXTRA_OECONF += " \
    --with-curl=${STAGING_LIBDIR}/.. \
    --with-openssl=${STAGING_INCDIR}/.. \
"
DEPENDS_append = " openssl curl"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append = " file://md4-remove.patch"
SRC_URI_remove_kirkstone = "file://md4-remove.patch"
SRC_URI_append_kirkstone = " file://md4-remove_kirkstone.patch"


CACHED_CONFIGUREVARS_remove = "${@bb.utils.contains_any('DISTRO_FEATURES','dunfell kirkstone',' ac_cv_func_dlopen=no','',d)}"
CFLAGS_append = "${@bb.utils.contains_any('DISTRO_FEATURES','dunfell kirkstone',' -DHAVE_LIBDL','',d)} "
LDFLAGS_append = "${@bb.utils.contains_any('DISTRO_FEATURES','dunfell kirkstone','  -ldl','',d)} "
