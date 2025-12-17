RDEPENDS_packagegroup-rdk-oss-broadband_remove = " libmtp"
RDEPENDS_packagegroup-rdk-oss-broadband += "${@bb.utils.contains('DISTRO_FEATURES','benchmark_enable','ntp','',d)}"

