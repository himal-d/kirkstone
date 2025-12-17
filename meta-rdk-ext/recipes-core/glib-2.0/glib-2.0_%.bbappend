FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

PTEST_ENABLED = "${@bb.utils.contains('DISTRO_FEATURES', 'benchmark_enable', '1', '0', d)}"
inherit ptest-package-deploy
PKG_glib-2.0="libglib-2.0"

RDEPENDS_${PN}-utils_append_kirkstone = " libelf"
