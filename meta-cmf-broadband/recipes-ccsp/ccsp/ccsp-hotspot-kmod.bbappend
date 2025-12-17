SRC_URI_remove = "${CMF_GIT_ROOT}/rdkb/components/cpc/mtu_modifier;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=hotspot-kmod"
SRC_URI += "${CMF_GIT_ROOT}/rdkb/components/generic/mtu_modifier;protocol=${CMF_GIT_PROTOCOL};branch=${CMF_GIT_BRANCH};name=hotspot-kmod"

inherit coverity
