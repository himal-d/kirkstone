# Class to inherit when you want to build against Breakpad.
# Apart from inheriting this class, you need to set BREAKPAD_BIN in
# your recipe, and make sure that you link against libbreakpad_client.a.

DEPENDS += "breakpad-native"

CFLAGS += "-I${STAGING_INCDIR_NATIVE}/breakpad "
CXXFLAGS += "-I${STAGING_INCDIR_NATIVE}/breakpad "

BREAKPAD_BIN ?= "*.so*"

python () {
    breakpad_bin = d.getVar("BREAKPAD_BIN", True)

    if not breakpad_bin:
       PN = d.getVar("PN", True)
       FILE = os.path.basename(d.getVar("FILE", True))
       bb.error("To build %s, see comcast-breakpad.bbclass for instructions on \
                 setting up your Breakpad configuration" % PN)
       raise ValueError('BREAKPAD_BIN not defined in %s' % PN)
}

# Add creation of symbols here
PACKAGE_PREPROCESS_FUNCS += "breakpad_package_preprocess"
breakpad_package_preprocess () {
    
    machine_dir="${@d.getVar('MACHINE', True)}"
    mkdir -p ${TMPDIR}/deploy/breakpad_symbols/$machine_dir

    for pattern in ${BREAKPAD_BIN}; do
        find ${D} -name $pattern -type f -print | while read symlink; do
            binary="$(readlink -m "$symlink")"
            bbnote "Dumping symbols from $binary"
            dump_syms "${binary}" > "${TMPDIR}/deploy/breakpad_symbols/$machine_dir/$(basename "$binary").sym" || echo "dump_syms finished with errorlevel $?"
        done
    done
}
