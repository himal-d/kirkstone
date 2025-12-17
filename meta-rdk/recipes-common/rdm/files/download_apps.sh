#!/bin/sh
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2021 RDK Management
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
. /etc/device.properties

DOWNLOAD_APP_MODULE=$1
APPLN_HOME_PATH=/tmp
APP_MOUNT_PATH=/media/apps
SKIP_DOWNLOAD=0

if [ -n "$2" ]; then
     USB_RDM_PKG_FILE=$2
     SKIP_DOWNLOAD=1
fi

if [ "$DEVICE_TYPE" = "broadband" ]; then
     RDM_DL_INFO=/nvram/persistent/rdmDownloadInfo.txt
else
     RDM_DL_INFO=/opt/persistent/rdmDownloadInfo.txt
fi

DOWNLOAD_PKG_NAME=`/usr/bin/jsonquery -f /etc/rdm/rdm-manifest.json  --path=//packages/$DOWNLOAD_APP_MODULE/pkg_name`
DOWNLOAD_APP_SIZE=`/usr/bin/jsonquery -f /etc/rdm/rdm-manifest.json  --path=//packages/$DOWNLOAD_APP_MODULE/app_size`
DOWNLOAD_PKG_TYPE=`/usr/bin/jsonquery -f /etc/rdm/rdm-manifest.json  --path=//packages/$DOWNLOAD_APP_MODULE/pkg_type`

if [ -f /tmp/.rdm-apps-data/${DOWNLOAD_APP_MODULE}.conf ]; then
    source /tmp/.rdm-apps-data/${DOWNLOAD_APP_MODULE}.conf
fi

if [ "x$IS_VERSIONED" == "xtrue" ]; then
    RDM_DOWNLOAD_SCRIPT=/etc/rdm/downloadVersionedApps.sh
elif [ "$DOWNLOAD_PKG_TYPE" == "plugin" ]; then
    echo "Installing $DOWNLOAD_APP_MODULE via Packager"
    RDM_DOWNLOAD_SCRIPT=/etc/rdm/packagerMgr.sh
else
    RDM_DOWNLOAD_SCRIPT=/etc/rdm/downloadMgr.sh
fi

#Space reserved on app partition for firmware download(in MB)
RDM_SCRATCHPAD_MAX_FW_SIZE=80
RDM_SCRATCHPAD_FREE_MARGIN=5

# Determine App size in KB's and MB's
scale=`echo "${DOWNLOAD_APP_SIZE#"${DOWNLOAD_APP_SIZE%?}"}"`
value=`echo ${DOWNLOAD_APP_SIZE%?}`
value=${value%.*} # Truncate fractional part

if [ "x$scale" == "xK" -o "x$scale" == "xk" ]; then
    DOWNLOAD_APP_SIZE_KB=$value
    # convert into MB's
    value=$((value/1024))
    DOWNLOAD_APP_SIZE_MB=${value%.*} # Truncate fractional part
else
    DOWNLOAD_APP_SIZE_KB=$((value * 1024))
    DOWNLOAD_APP_SIZE_MB=$value
fi

echo "Downloading $DOWNLOAD_APP_MODULE..."

# make sure that we have a rw filesystem mounted on cdl mount path
if [ "$DEVICE_TYPE" != "broadband" ]; then
  tst_file=$APP_MOUNT_PATH/testfile
  diskcheck=1
  #Write something in the test file to ensure disk is writable.
  echo "Test write" > $tst_file
  if [ $? -eq 0 ];then
          #check we are able to remove the file as well. Sometimes, corrupted disk don't allow us to delete a file.
	  rm -f $tst_file
	  if [ $? -eq 0 ];then
		  echo "$APP_MOUNT_PATH is in working condition"
                  diskcheck=0
	  fi
  fi
  if [ $diskcheck -eq 0 ]; then
    # Verify if package already present on cdl mount path.
    pkg_present=`find $APP_MOUNT_PATH -iname $DOWNLOAD_PKG_NAME | wc -l`
    if [ $pkg_present -ne 0 ]; then
        echo "$DOWNLOAD_APP_MODULE already downloaded on secondary storage. So skip the download and validate the package."
        APPLN_HOME_PATH=$APP_MOUNT_PATH
    else
        # Expected App package version (as per rdm-manifest.json) is not present on secondary storage.
        # Download for this version will be initiated so delete any previously downlaoded version of same App.
        APPLN_APP_DL_PATH=$APP_MOUNT_PATH/rdm/downloads/$DOWNLOAD_APP_MODULE

        pkg_previous=`ls $APPLN_APP_DL_PATH | grep _$DOWNLOAD_APP_MODULE | grep tar`
        if [[ $pkg_previous = "" ]]; then
            echo "Any version of $DOWNLOAD_APP_MODULE package not available on secondary storage"
        else
            echo "Previous $DOWNLOAD_APP_MODULE App version available on secondary storage: $pkg_previous"
            echo "Upgrading to newer package version: $DOWNLOAD_PKG_NAME"
        fi

        rm -rf $APPLN_APP_DL_PATH/*
        rm -rf $APP_MOUNT_PATH/$DOWNLOAD_APP_MODULE/*

        # Verify if sufficient free space available on secondary storage for downloadable APP
        # Determine free Space in app partition in 1K-blocks
        RDM_SCRATCHPAD_FREE_SPACE=`df -k $APP_MOUNT_PATH |  grep -v File | awk '{print $4 }'`

        #Convert the available space into MB's
        RDM_SCRATCHPAD_FREE_SPACE="$(($RDM_SCRATCHPAD_FREE_SPACE / 1024))"
        echo "Free Space in $APP_MOUNT_PATH = $RDM_SCRATCHPAD_FREE_SPACE MB"

        RDM_AVAILABE_SPACE_FOR_APPS="$(($RDM_SCRATCHPAD_FREE_SPACE - $RDM_SCRATCHPAD_MAX_FW_SIZE - $RDM_SCRATCHPAD_FREE_MARGIN))"
        echo "Availabble Space in $APP_MOUNT_PATH for app Download = $RDM_AVAILABE_SPACE_FOR_APPS MB"

        if [[ "$RDM_AVAILABE_SPACE_FOR_APPS" -gt "$DOWNLOAD_APP_SIZE_MB" ]]; then
            echo "secondary storage scratchpad will be used for App download"
            APPLN_HOME_PATH=$APP_MOUNT_PATH
        else
            echo "Not enough space available for App download on $APP_MOUNT_PATH. Downloading the App on tmp dir."
        fi
    fi
  else
    echo "$APP_MOUNT_PATH is not in working condition."
  fi
fi

echo "HOME PATH for APP = $APPLN_HOME_PATH"

if [ $SKIP_DOWNLOAD -eq 1 ]; then
    # Copy app signed tarball from usb to rdm download directory
    echo "Copying $DOWNLOAD_APP_MODULE signed tarball from usb to $APPLN_APP_DL_PATH"
    mkdir -p $APPLN_APP_DL_PATH
    cp $USB_RDM_PKG_FILE $APPLN_APP_DL_PATH

    RDM_DOWNLOAD_SCRIPT="/etc/rdm/downloadMgr.sh"
fi

# Download the Package. If package already present on download path then skip the download
# and perform the signature validation

if [ "x$IS_VERSIONED" = "xtrue" ]; then
    time sh $RDM_DOWNLOAD_SCRIPT $DOWNLOAD_APP_NAME "$DOWNLOAD_PKG_VERSION"
else
    time sh $RDM_DOWNLOAD_SCRIPT $DOWNLOAD_APP_MODULE $APPLN_HOME_PATH openssl ipk "" $SKIP_DOWNLOAD
fi

RDM_STATUS=$?
if [ $RDM_STATUS -eq 3 ] && [ "$APPLN_HOME_PATH" == "$APP_MOUNT_PATH" ]; then
    #Signature validation failed. This could be due to corruption on previously downloaded pacakge.
    # Download the package again from CDL server and do the validation.
    echo "Signature validation failed on pacakge which was already present on secondary storage."
    echo "Downalod new package from server."
    time sh $RDM_DOWNLOAD_SCRIPT $DOWNLOAD_APP_MODULE $APPLN_HOME_PATH openssl ipk "" $SKIP_DOWNLOAD
    RDM_STATUS=$?
fi

# Download Status will be “SUCCESS, “FAILURE” or “DOWNLOAD NOT STARTED”
# TODO: Currently we download all the components present on rdm-manifest.json during bootup.
# So status "DOWNLOAD NOT STARTED" is not being used. It may get used in future.
if [ $RDM_STATUS -eq 0 ]; then
   RDM_DL_STATUS="SUCCESS"
else
   RDM_DL_STATUS="FAILURE"
fi

# Keeps the meta-data about the Apps in following format in /opt/persistent/rdmDownloadInfo.txt
# Meta data contains App Name, Package Name, App Home path, App Size, Download Status
if [ -f $RDM_DL_INFO ]; then
    sed -i "/^${DOWNLOAD_APP_MODULE}/d" $RDM_DL_INFO
fi
#To redirect output persistent folder should be present

if [ "$DEVICE_TYPE" = "broadband" ]; then
    if [ ! -d /nvram/persistent ];then
        mkdir -p /nvram/persistent
    fi
elif [ ! -d /opt/persistent ];then
        mkdir -p /opt/persistent
fi
echo "$DOWNLOAD_APP_MODULE $DOWNLOAD_PKG_NAME $APPLN_HOME_PATH/$DOWNLOAD_APP_MODULE/ $DOWNLOAD_APP_SIZE_KB $RDM_DL_STATUS" >> $RDM_DL_INFO
exit $RDM_STATUS
