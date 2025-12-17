# Remove git protocol from Opensync github src_uri
OPENSYNC_CORE_REPO_PATH = "git://github.com/plume-design/opensync.git"
OPENSYNC_PLATFORM_REPO_PATH = "git://github.com/plume-design/opensync-platform-rdk.git"
OPENSYNC_VENDOR_REPO_PATH = "git://github.com/plume-design/opensync-vendor-rdk-template.git"
OPENSYNC_SERVICE_PROVIDER_REPO_PATH = "git://github.com/plume-design/opensync-service-provider-local.git"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
OPENSYNC_SERVICE_PROVIDER_URI += " ${@bb.utils.contains('DISTRO_FEATURES', 'extender', 'file://0001-Update-bhaul-credential.patch;patchdir=${WORKDIR}/git/service-provider/local', '', d)} "
