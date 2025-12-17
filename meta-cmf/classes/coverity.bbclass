# Run after recipe parsing and give make override global scope.
python __anonymous() {
    coverity_dir=d.getVar('COVERITY_DIR', True)
    component=d.getVar('PN', True)
    if d.getVar('COVERITY_REQUIRED', True) == "1":
        if d.getVar('COVERITY_COMPONENT_NAME', True) == component:
            d.setVar('MAKE', '${COVERITY_PATH}/cov-build --config ${COVERITY_CONFIG} --dir ${TOPDIR}/../build-images/${COVERITY_COMPONENT_NAME} make')
}

do_compile_prepend () {
    COVERITY_REQUIRED="${@d.getVar('COVERITY_REQUIRED', True)}"
    if [ "${COVERITY_REQUIRED}" = "1" ] ;then
        bbnote "Coverity configure start ${COVERITY_COMPONENT_NAME} ${PN}"

        COVERITY_COMPONENT_NAME="${@d.getVar('COVERITY_COMPONENT_NAME', True)}"
        if [ "${COVERITY_COMPONENT_NAME}" = "${PN}" ]; then
            bbnote "Coverity configure run ${COVERITY_COMPONENT_NAME}"

            COVERITY_CONFIG="${@d.getVar('COVERITY_CONFIG', True)}"
            COVERITY_PATH="${@d.getVar('COVERITY_PATH', True)}"
            compiler_value=`echo ${CC} | cut -f1 -d " "`
            ${COVERITY_PATH}/cov-configure --template --compiler $compiler_value
            export MAKE='${COVERITY_PATH}/cov-build --config ${COVERITY_CONFIG} --dir ${TOPDIR}/../build-images/${COVERITY_COMPONENT_NAME} make'
        fi
    fi
}

do_compile_append () {
    COVERITY_REQUIRED="${@d.getVar('COVERITY_REQUIRED', True)}"
    if [ "${COVERITY_REQUIRED}" = "1" ] ;then
        bbnote "Coverity build start ${COVERITY_COMPONENT_NAME} ${PN}"

        COVERITY_COMPONENT_NAME="${@d.getVar('COVERITY_COMPONENT_NAME', True)}"
        if [ "${COVERITY_COMPONENT_NAME}" = "${PN}" ]; then
            bbnote "Coverity build run1 ${COVERITY_COMPONENT_NAME}"

            # Check that the previous build did not generate the Coverity data
            if [ ! -d ${TOPDIR}/../build-images/${COVERITY_COMPONENT_NAME} ]; then
                bbnote "Coverity build run2 ${COVERITY_COMPONENT_NAME}"

                # Check that the build is a cmake build
                if [ -f ${S}/CMakeLists.txt ]; then
                    bbnote "Coverity rebuild cmake"

                    COVERITY_CONFIG="${@d.getVar('COVERITY_CONFIG', True)}"
                    COVERITY_PATH="${@d.getVar('COVERITY_PATH', True)}"
                    ${COVERITY_PATH}/cov-build --config ${COVERITY_CONFIG} --dir ${TOPDIR}/../build-images/${COVERITY_COMPONENT_NAME} cmake --build '${B}' --clean-first --target all
                fi
            fi
        fi
    fi
}
