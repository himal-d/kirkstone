INCOMPATIBLE_LICENSE = 'LGPL-3.0* GPL-3.0*'
WARN_QA:remove = 'incompatible-license'
RDEPENDS:${PN}-ptest:remove:pn-glib-2.0 = "python3-dbusmock"
DISTRO_FEATURES:remove = "ptest"
