do_install_append () {
   # remove expired certs
   rm -f ${D}/usr/share/grpc/roots.pem
}

FILES_${PN}_remove += "/usr/share/grpc/roots.pem"
