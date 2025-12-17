SRC_URI_remove = "git://anongit.freedesktop.org/gstreamer/gst-plugins-ugly;branch=1.8;name=base"
SRC_URI += "git://anongit.freedesktop.org/git/gstreamer/gst-plugins-ugly.git;protocol=${CMF_GIT_PROTOCOL};branch=1.8;name=base"

SRC_URI_remove = "git://anongit.freedesktop.org/gstreamer/common;destsuffix=git/common;name=common"
SRC_URI += "git://gitlab.freedesktop.org/gstreamer/common.git;protocol=${CMF_GIT_PROTOCOL};destsuffix=git/common;name=common"
