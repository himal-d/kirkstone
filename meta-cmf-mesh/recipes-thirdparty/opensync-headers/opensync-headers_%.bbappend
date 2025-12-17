SRC_URI_remove = " ${RDK_COMPONENTS_ROOT_GIT}/generic/opensync-core/${OS_CORE_VERSION}/generic;protocol=${RDK_GIT_PROTOCOL};name=opensync-headers;branch=${RDK_GIT_BRANCH};destsuffix=git/os-headers"

SRCREV_core ?= "${AUTOREV}"

OPENSYNC_DEFAULT_PROTOCOL ?= "https"
OPENSYNC_DEFAULT_BRANCH ?= "osync_4.4.0"

OPENSYNC_CORE_REPO_PATH ?= "git://github.com/plume-design/opensync.git"
OPENSYNC_CORE_REPO_PROTOCOL ?= "${OPENSYNC_DEFAULT_PROTOCOL}"
OPENSYNC_CORE_BRANCH ?= "${OPENSYNC_DEFAULT_BRANCH}"

OPENSYNC_CORE_URI ?= "${OPENSYNC_CORE_REPO_PATH};protocol=${OPENSYNC_CORE_REPO_PROTOCOL};branch=${OPENSYNC_CORE_BRANCH};name=core;destsuffix=git/core"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI += "${OPENSYNC_CORE_URI}"

SRC_URI += "file://adding_structures_for_blaster.patch"

S = "${WORKDIR}/git/core"

PROVIDES = "opensync-headers"
