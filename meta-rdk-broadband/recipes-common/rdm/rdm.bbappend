DEPENDS += "mountutils ccsp-common-library"
DEPENDS_remove_class-nativesdk = "mountutils ccsp-common-library"

CFLAGS_append = "${@bb.utils.contains('DISTRO_FEATURES', 'safec',  ' `pkg-config --cflags libsafec` ', ' -fPIC -DSAFEC_DUMMY_API ', d)}"

LDFLAGS_append = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' `pkg-config --libs libsafec` ', '', d)}"
LDFLAGS_append_dunfell = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec-3.5.1 ', '', d)}"
LDFLAGS_append_kirkstone = "${@bb.utils.contains('DISTRO_FEATURES', 'safec', ' -lsafec ', '', d)}"

EXTRA_OECONF += "--enable-mountutils"