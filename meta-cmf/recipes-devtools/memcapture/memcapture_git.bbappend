SRC_URI_remove = "git://${RDK_GIT}/rdk/component/generic/performancetool/generic;protocol=${RDK_GIT_PROTOCOL};branch=${RDK_GIT_BRANCH};subpath=memcapture;name=script"

inherit coverity

do_install_prepend () {
    mkdir -p ${WORKDIR}/memcapture/
    touch ${WORKDIR}/memcapture/groups-rdkv.json
    touch ${WORKDIR}/memcapture/start_memcapture.sh
    touch ${WORKDIR}/memcapture/memcapture.service
}
