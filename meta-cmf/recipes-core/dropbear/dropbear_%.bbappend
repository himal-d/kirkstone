
# Adding telemetry to video, broadband, and camera.
# excluding extender
DEPENDS += "telemetry"
DEPENDS_remove_extender = "telemetry"

do_configure_prepend () {
  if ${@bb.utils.contains('DISTRO_FEATURES', 'extender', 'false', 'true', d)}; then
    export LIBS="${LIBS} -ltelemetry_msgsender"
  fi
}

SRC_URI_remove_extender  = " file://ssh_telemetry_2017_uninit_init_add.patch"
SRC_URI_remove_extender = " file://ssh_telemetry_2019_uninit_init_add.patch"
