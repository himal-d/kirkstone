SRCREV = "${AUTOREV}"
SRC_URI = "git://github.com/deniskropp/linux-fusion.git;protocol=https;branch=master \
           file://user_msghdr.patch \
      "
S = "${WORKDIR}/git"
