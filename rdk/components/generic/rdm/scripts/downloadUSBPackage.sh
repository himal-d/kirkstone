#!/bin/sh
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2018 RDK Management
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

# Logging to verify USB status
if [ -f /etc/include.properties ];then
     . /etc/include.properties
fi

if [ -f /etc/device.properties ];then
     . /etc/device.properties
fi
if [ -f /lib/rdk/t2Shared_api.sh ]; then
    source /lib/rdk/t2Shared_api.sh
fi

if [ "$LOG_PATH" ];then
     LOG_FILE="$LOG_PATH/rdm_status.log"
else
     if [ -d /var/log ];then
          if [ -f /var/log/rdm_status.log ];then
               rm -rf /var/log/rdm_status.log
          fi
          LOG_FILE=/var/log/rdm_status.log
     else
          LOG_FILE=/dev/null
     fi
fi

log_msg() {
  #get current dateandtime
  DateTime=`date "+%m%d%y-%H:%M:%S:%N"`
  STR=""
  #check if parameter non zero size
  if [ -n "$1" ];
  then
    STR="$1"
  else
    DONE=false
    until $DONE ;do
    read IN || DONE=true
    STR=$STR$IN
    done
  fi
  #print log message
  echo "[$DateTime] [pid=$$] $STR" >>$LOG_FILE
}

# Extract & validate Signed package resides at given USB 
# mount point.  
USB_MOUNT_POINT=$1
if [ ! -d $USB_MOUNT_POINT ]; then
    log_msg "Mount point $USB_MOUNT_POINT does not exists"
fi

# Check if any signed tarball present
# Loop to validate all packages resides at USB Mount point
for file in `find $USB_MOUNT_POINT -name '*-signed.tar' -type f`
do
    if [ ! -f $file ]; then
        log_msg "Packaged file $file does not exists"
        log_msg "Continue to next package"
        continue;
    fi

    #Get App name
    fileName=$(basename $file)
    pkg=$(echo "${fileName##*_}")
    appName=$(echo "${pkg%-signed*}")

    #Check whether the rdm package available in usb belongs to the currently running firmware 
    grep -q $fileName /etc/rdm/rdm-manifest.json
    if [ $? -eq 0 ]; then
        log_msg "Installing $fileName from usb"

        #Invoke download_apps.sh to skip the download and to install the package. Should pass appName and file path as arguments
        /usr/bin/download_apps.sh $appName $file
    else
        log_msg "$fileName does not belong to the currently running firmware. Hence skipping it"
        continue
    fi
done
