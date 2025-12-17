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

if [ -f /etc/rdm/rdmBundleUtils.sh ]; then
    source /etc/rdm/rdmBundleUtils.sh
fi

if [ -f /etc/rdm/rdmIarmEvents.sh ]; then
        source /etc/rdm/rdmIarmEvents.sh
fi

if [ ! -f /etc/os-release ]; then
    IARM_EVENT_BINARY_LOCATION=/usr/local/bin
else
    IARM_EVENT_BINARY_LOCATION=/usr/bin
fi

if [ "$DEVICE_TYPE" = "broadband" ]; then
     RDM_DL_INFO=/nvram/persistent/rdmDownloadInfo.txt
else
     RDM_DL_INFO=/opt/persistent/rdmDownloadInfo.txt
fi
RDM_APP_PATH="/media/apps"
APP_DL_STATUS=0
RDM_MANIFEST="/etc/rdm/rdm-manifest.json"

#Verify apps downloaded in /media/apps
checkAppDownload()
{
    ret=1
    APP_DIR=$RDM_APP_PATH/$APP
    APP_MANIFEST=$RDM_APP_PATH/$APP/${APP}_cpemanifest
    APP_DATA=`ls -A $APP_DIR | grep -v httpcode`

    if [ -f "$APP_MANIFEST" ] && [ ! -z "$APP_DATA" ];then
        echo "$APP app data and manifest $APP_MANIFEST file are available"
        ret=0
    else
        echo "$APP manifest and data is missing..."
    fi
    return $ret
}

# To send notification about change in RDM application download status
sendNotification()
{
    eventStatus=$1
    if [ -f $IARM_EVENT_BINARY_LOCATION/IARM_event_sender ]; then
        echo "Sending IARM AppDownloadEvent to indicate that RDM application download status has been changed"
        $IARM_EVENT_BINARY_LOCATION/IARM_event_sender AppDownloadEvent $eventStatus
    else
        echo "Missing the binary $IARM_EVENT_BINARY_LOCATION/IARM_event_sender"
    fi
}

if [ -n "$RDM_CLOUD_MANIFEST" -a "$RDM_CLOUD_MANIFEST" = "true" ]; then
    source /etc/rdm/rdmCatalogueMgr.sh
fi

if [ "$#" -eq  "0" ]; then
    # To download all the apps mentioned in rdm-manifest.json file
    idx=0
    packageList=""
    rfc_disabled_apps=""
    while :
    do

        JQ_CMD="/usr/bin/jsonquery -f $RDM_MANIFEST --path=//packages/$idx"
        DOWNLOAD_APP_NAME=`$JQ_CMD/app_name`
        if [ $? -eq 0 ]; then
                packageList="$DOWNLOAD_APP_NAME $packageList"
		DOWNLOAD_APP_ONDEMAND=`$JQ_CMD/dwld_on_demand`
		if [ "x$DOWNLOAD_APP_ONDEMAND" = "xyes" ]; then
			echo "dwld_on_demand set to yes!!! Check RFC value of the APP to be downloaded"
			DOWNLOAD_METHOD_CONTROLLER=`$JQ_CMD/dwld_method_controller`
            		if [ "x$DOWNLOAD_METHOD_CONTROLLER" = "xRFC" ]; then
	        		/usr/bin/rdm_apps_rfc_check.sh $DOWNLOAD_APP_NAME
				APP_RFC_STATUS=$?
				echo "APP_RFC_STATUS:$APP_RFC_STATUS"
            			if [ $APP_RFC_STATUS -ne 0 ]; then
		    			echo "APP RFC is not enabled, skipping the download for:App:$idx=>$DOWNLOAD_APP_ONDEMAND=>$DOWNLOAD_APP_NAME"
                                        rfc_disabled_apps="$DOWNLOAD_APP_NAME $rfc_disabled_apps"
		    			idx=`expr $idx + 1`
		    			continue;
	    			fi
			fi
		fi
			
            echo "Start the download of App: $DOWNLOAD_APP_NAME"
            /usr/bin/download_apps.sh $DOWNLOAD_APP_NAME
            APP_DL_STATUS=$?
            if [ $APP_DL_STATUS -ne 0 ]; then
                break;
            fi
        else
            break
        fi
        idx=`expr $idx + 1`
    done
    echo "Download of all Apps completed with status=$APP_DL_STATUS"
else
    APP=$1
    # To retry download the missing downloadable app in /media/apps.
    checkAppDownload $APP
    ret=$?
    if [ $ret -eq 0 ]; then
        echo "$APP application already downloaded"
    else
        echo "Retrying download for $APP application..."
        /usr/bin/download_apps.sh $APP
        APP_DL_STATUS=$?
        echo "Download of $APP App completed with status=$APP_DL_STATUS"
    fi
    exit $APP_DL_STATUS
fi

updatePkgStatus()
{
        APP_INST_STATUS="$1"
        APP_VERSION=""
        APP_HOME_DIR=""
        pkg_info="pkg_name:$pkg\npkg_version:$APP_VERSION\npkg_inst_status:$APP_INST_STATUS\npkg_inst_path:$APP_HOME_DIR"
        broadcastRDMPkgStatus "$pkg_info"
}

uninstallPackages()
{
    echo "Uninstall the old packages that are not listed in current manifest"
    pkg_manifest=$(echo $packageList | xargs)
    echo "Packages listed in manifest: $pkg_manifest"

    # Uninstall the packages that were not listed in manifest
    installedPkgs=$(getInstalledPackages)
    echo "Installed packages in cpe: $installedPkgs"
    for package in $pkg_manifest; do
        if [[ $rfc_disabled_apps != *"$package"* ]]; then
            installedPkgs=${installedPkgs//${package}/}
        fi
    done

    uninstall_pkg_list=$(echo $installedPkgs | xargs)

    if [ ! -z "$uninstall_pkg_list" -a "$uninstall_pkg_list" != " " ]; then
        echo "Packages to be uninstalled: [$uninstall_pkg_list]"

        for pkg in $uninstall_pkg_list; do
            rm -rf "$RDM_APP_PATH/$pkg"
            if [ $? -eq 0 ]; then
                echo "Uninstalled ${pkg} from $RDM_APP_PATH"
                updatePkgStatus "$RDM_PKG_UNINSTALL"
            fi
        done
    else
        echo "CPE contains only the packages that are listed in manifest. No old packages were found to uninstall"
    fi
}

# Send notification about download status as 1 for success and 0 for failure of all the components present on rdm-manifest.json
if [ -s $RDM_DL_INFO ]; then
    if [ "$APP_DL_STATUS" -eq 0 ]; then 
        echo "App download success, sending status as $APP_DL_STATUS"
        uninstallPackages
    else
        echo "App download failed, sending status as $APP_DL_STATUS"
    fi
    sendNotification $APP_DL_STATUS
else
    echo "File $RDM_DL_INFO doesn't exist or empty."
fi

exit $APP_DL_STATUS
