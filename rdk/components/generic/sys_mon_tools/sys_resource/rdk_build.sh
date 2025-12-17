#!/bin/bash
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################

#######################################
#
# Build Framework standard script for
#
# MLT component

# use -e to fail on any shell issue
# -e is the requirement from Build Framework
set -e


# default PATHs - use `man readlink` for more info
# the path to combined build
export RDK_PROJECT_ROOT_PATH=${RDK_PROJECT_ROOT_PATH-`readlink -m ../..`}
export COMBINED_ROOT=$RDK_PROJECT_ROOT_PATH

# path to build script (this script)
export RDK_SCRIPTS_PATH=${RDK_SCRIPTS_PATH-`readlink -m $0 | xargs dirname`}

# path to components sources and target
export RDK_SOURCE_PATH=${RDK_SOURCE_PATH-$RDK_SCRIPTS_PATH}
export RDK_TARGET_PATH=${RDK_TARGET_PATH-$RDK_SOURCE_PATH}

# fsroot and toolchain (valid for all devices)
export RDK_FSROOT_PATH=${RDK_FSROOT_PATH-`readlink -m $RDK_PROJECT_ROOT_PATH/sdk/fsroot/ramdisk`}
export RDK_TOOLCHAIN_PATH=${RDK_TOOLCHAIN_PATH-`readlink -m $RDK_PROJECT_ROOT_PATH/sdk/toolchain/staging_dir`}


# default component name
export RDK_COMPONENT_NAME=${RDK_COMPONENT_NAME-mlt}


# parse arguments
INITIAL_ARGS=$@
CC_DEVICE=$RDK_PLATFORM_DEVICE

function usage()
{
    set +x
    echo "Usage: `basename $0` [-h|--help] [-v|--verbose] [action]"
    echo "    -h    --help                  : this help"
    echo "    -v    --verbose               : verbose output"
    echo "    -m                            : enable RI MLT configuration"
    echo
    echo "Supported actions:"
    echo "      configure, clean, build (DEFAULT), rebuild, install"
}

# options may be followed by one colon to indicate they have a required argument
if ! GETOPT=$(getopt -o hvm -l help,verbose -- "$@")
then
    usage
    exit 1
fi

eval set -- "$GETOPT"

while true; do
  case "$1" in
    -h | --help ) usage; exit 0 ;;
    -v | --verbose ) set -x ;;
    --platform-device ) CC_DEVICE="$2" ; shift ;;
    -m ) RIMLT=1 ;;
    -- ) shift; break;;
    * ) break;;
  esac
  shift
done

ARGS=$@

if [ -z "$CC_DEVICE" ]; then
    echo "--platform-device option is required to build this component"
    exit 1
fi

# component-specific vars
#multicore build support
JOBS_NUM=$((`grep -c ^processor /proc/cpuinfo` + 1))

export BUILDS_DIR=$RDK_PROJECT_ROOT_PATH
export DEBUG=n
export WORK_DIR=$RDK_PROJECT_ROOT_PATH/work${CC_DEVICE^^}

if [ ${RDK_PLATFORM_DEVICE} = "xi3" ]; then
    source ${RDK_PROJECT_ROOT_PATH}/build_scripts/setBCMenv.sh
elif [ ${RDK_PLATFORM_DEVICE} = "rng150" ];then

	# check to support both Trunk and 13.2 builds
	if [ -f  $WORK_DIR/../sdk/scripts/setBCMenv.sh ]; then
		source  $WORK_DIR/../sdk/scripts/setBCMenv.sh
	fi
	
	if [ -f $WORK_DIR/../sdk/scripts/setBcmEnv.sh ]; then
		 source $WORK_DIR/../sdk/scripts/setBcmEnv.sh
	fi
else
  source $WORK_DIR/../sdk/scripts/setBcmEnv.sh
fi

export USE_SYSRES_PLATFORM=BROADCOM

if [[ $RIMLT -eq 1 ]];then
    export USE_SYS_RESOURCE_MLT=y
    export USE_IDLE_MLT=y
    export USE_MPEMEDIATUNE_MLT="n"
    export USE_SYS_RESOURCE_MON="y"
    export USE_SYSRES_PLATFORM="BROADCOM"

fi


# functional modules

function configure()
{
    true #use this function to perform any pre-build configuration
}

function clean()
{
    true
}

function build()
{
    cd ${RDK_SOURCE_PATH}
    
    if [[ $VLCLEAN == 1 ]]; then
	make clean
    fi
    
    make -j $JOBS_NUM all
#HACK Also need to make ledCtrl
    
    ledPath=$COMBINED_ROOT/sys_mon_tools/ledCtrl
    
    if [ -d $ledPath ]; then
	cd $ledPath
	if [[ $VLCLEAN == 1 ]]; then
	    make clean
	fi
	
        make -j $JOBS_NUM all
    fi


}

function rebuild()
{
    VLCLEAN=1
    build
}

function install()
{
    RAMDISK_TARGET=${RDK_FSROOT_PATH}/mnt/nfs/bin
    mkdir -p ${RAMDISK_TARGET}

    SDK_PATH=${RDK_PROJECT_ROOT_PATH}/sdk
    FSROOT_TOP_PATH=${SDK_PATH}/fsroot
    TOOLCHAIN_TOP_PATH=${SDK_PATH}/toolchain
    SYSAPPS_PATHLED=${RDK_PROJECT_ROOT_PATH}/sys_mon_tools/ledCtrl
    INSTALL_DIR=${SYSAPPS_PATHLED}/bin/rel/broadcom

    cp $RDK_TARGET_PATH/lib/platform/broadcom/libsysResource.so ${RAMDISK_TARGET}
    cp $RDK_TARGET_PATH/lib/platform/broadcom/libsysResource.so ${RDK_FSROOT_PATH}/usr/lib
    if [ ${RDK_PLATFORM_DEVICE} != "xi3" ]; then
        cp $INSTALL_DIR/ledCtrl ${RDK_PROJECT_ROOT_PATH}/sdk/fsroot/ramdisk/usr/local/bin/ledCtrl
    fi

    ENV_PATH=${RAMDISK_TARGET}/../env
    mkdir -p ${ENV_PATH}
    cd ${ENV_PATH}

    ln -sf ../bin/libsysResource.so libsysResource.so
}


# run the logic

#these args are what left untouched after parse_args
HIT=false

for i in "$ARGS"; do
    case $i in
        configure)  HIT=true; configure ;;
        clean)      HIT=true; clean ;;
        build)      HIT=true; build ;;
        rebuild)    HIT=true; rebuild ;;
        install)    HIT=true; install ;;
        *)
            #skip unknown
        ;;
    esac
done

# if not HIT do build by default
if ! $HIT; then
  build
fi
