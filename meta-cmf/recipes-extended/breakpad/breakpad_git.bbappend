SRC_URI_remove = "git://github.com/protocolbuffers/protobuf.git;destsuffix=git/src/third_party/protobuf/protobuf;name=protobuf;branch=master;protocol=https"
SRC_URI += "git://github.com/protocolbuffers/protobuf.git;destsuffix=git/src/third_party/protobuf/protobuf;name=protobuf;branch=main;protocol=https"

# Fix problems with "Fatal error: can't create src/processor/stackwalk_common.o: No such file or directory"
do_compile_prepend () {
    mkdir -p ${B}/src/processor
}
