SRC_URI_remove = "http://www.balabit.com/downloads/files/syslog-ng/open-source-edition/3.4.2/source/${BPN}_${PV}.tar.gz"
SRC_URI += "git://github.com/balabit/eventlog.git;protocol=https;branch=master"
SRCREV = "${AUTOREV}"
S = "${WORKDIR}/git/"
