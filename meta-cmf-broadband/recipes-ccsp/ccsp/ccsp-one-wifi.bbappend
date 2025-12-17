inherit coverity

DEPENDS_append = " protobuf-c"
RDEPENDS_${PN}_append = " openvswitch"
LDFLAGS_remove = " -ldpp"
