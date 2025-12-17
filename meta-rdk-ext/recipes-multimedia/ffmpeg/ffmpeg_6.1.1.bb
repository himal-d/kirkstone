SUMMARY = "A complete, cross-platform solution to record, convert and stream audio and video."
DESCRIPTION = "FFmpeg is the leading multimedia framework, able to decode, encode, transcode, \
               mux, demux, stream, filter and play pretty much anything that humans and machines \
               have created. It supports the most obscure ancient formats up to the cutting edge."
HOMEPAGE = "https://www.ffmpeg.org/"

LICENSE = "LGPLv2.1"
LICENSE_PATH += "${WORKDIR}/FFmpeg-n6.1.1/"
LIC_FILES_CHKSUM = "file://COPYING.LGPLv2.1;md5=bd7a443320af8c812e4c18d1b79df004"

SRC_URI = "https://github.com/FFmpeg/FFmpeg/archive/n6.1.1.tar.gz;name=FFmpeg \
          "
SRC_URI[FFmpeg.md5sum] = "ad40e9142ad5cd3d70c29d8ad7bc6d21"
SRC_URI[FFmpeg.sha256sum] = "7c1ebea95d815e49c1e60c7ee816410dec73a81b8ac002b276780d2f9048e598"

SRCREV_FFmpeg = "${AUTOREV}"

S="${WORKDIR}/FFmpeg-n6.1.1"

PACKAGE_STRIP = "yes"

inherit autotools pkgconfig

do_compile() {
  cd ${S}/
  make
}

do_install() {
  install -d ${D}${bindir}
  install -d ${D}${libdir}
  install -d ${D}${includedir}
  install -d ${D}${datadir}
  cd ${S}/
  # libraries install
  cp -rvf ./libavcodec/libavcodec.so.60 ${D}${libdir}
  cp -rvf ./libavformat/libavformat.so.60 ${D}${libdir}
  cp -rvf ./libavutil/libavutil.so.58 ${D}${libdir}
  cp -rvf ./libavfilter/libavfilter.so.9 ${D}${libdir}
  cp -rvf ./libavdevice/libavdevice.so.60 ${D}${libdir}
  cp -rvf ./libswresample/libswresample.so.4 ${D}${libdir}
  cp -rvf ./libswscale/libswscale.so.7 ${D}${libdir}
  # binaries install
  cp -rvf ./ffmpeg ${D}${bindir}
  cp -rvf ./ffprobe ${D}${bindir}
  # symbolic links
  ln -s ${D}${libdir}/libavcodec.so.60 ${D}${libdir}/libavcodec.so
  ln -s ${D}${libdir}/libavformat.so.60 ${D}${libdir}/libavformat.so
  ln -s ${D}${libdir}/libavutil.so.58 ${D}${libdir}/libavutil.so
  ln -s ${D}${libdir}/libavfilter.so.9 ${D}${libdir}/libavfilter.so
  ln -s ${D}${libdir}/libavdevice.so.60 ${D}${libdir}/libavdevice.so
  ln -s ${D}${libdir}/libswresample.so.4 ${D}${libdir}/libswresample.so
  ln -s ${D}${libdir}/libswscale.so.7 ${D}${libdir}/libswscale.so
}

ERROR_QA_remove_morty = "pkgconfig"

FILES_${PN} += "/usr/*"

ALLOW_EMPTY_${PN} = "1"
