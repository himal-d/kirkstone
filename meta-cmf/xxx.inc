# disable uninative, yocto server for the uninative SDK fails intermittenly
#INHERIT_append_rpi = " uninative"

include conf/distro/include/yocto-uninative.inc
INHERIT_append_rpi = " image-buildinfo"
SDK_INCLUDE_NATIVESDK = "1"
require ${@bb.utils.contains('DISTRO_FEATURES','kirkstone','conf/distro/include/setscene_enforce_ignore_tasks.inc','conf/distro/include/setscene_enforce_whitelist.inc',d)}
