#!/bin/sh
##############################################################################
# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2020 RDK Management
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
##############################################################################
. /etc/include.properties
. /etc/device.properties


uploadLog() {
    echo "`/bin/date`: $0: $*" >> $DCM_LOG_FILE
}

logTLSError ()
 {
     TLSRet=$1
     server=$2
     case $TLSRet in
         35|51|53|54|58|59|60|64|66|77|80|82|83|90|91)
             tlsLog "HTTPS $TLS failed to connect to $server server with curl error code $TLSRet"
             ;;
     esac
 }

# assign the input arguments
TFTP_SERVER=$1
UploadProtocol=$2
UploadHttpLink=$3
NUM_UPLOAD_ATTEMPTS=3
OPENSSL_LOG_PATH=$4

# initialize the variables
if [ $DEVICE_TYPE == "broadband" ]; then
	 MAC=`ifconfig erouter0 | grep HWaddr | cut -d " " -f7 | sed 's/://g'`
else
MAC=`ifconfig eth0 | grep eth0 | tr -s ' ' | cut -d ' ' -f5`
fi

DT=`date "+%m-%d-%y-%I-%M%p"`
LOG_FILE=$MAC"_Logs_$DT.tgz"
if [ "$DEVICE_TYPE" == "broadband" ]; then
	LOG_PATH="/rdklogs/logs"
fi
STRESS_NG_LOG_PATH="$LOG_PATH/stress-ng_logs"

# working folders
HTTP_CODE=/tmp/logupload_curl_httpcode
TLS=""
if [ -f /etc/os-release ]; then
    TLS="--tlsv1.2"
fi
CLOUD_URL=""
CURL_TLS_TIMEOUT=30
CURL_TIMEOUT=10
useXpkiMtlsLogupload=false
# we limit the attempt to 1 when called
# as a part of logupload before deepsleep
DCM_LOG_FILE="$LOG_PATH/dcmscript.log"


uploadLog "Build Type: $BUILD_TYPE Log file: $LOG_FILE UploadProtocol: $UploadProtocol UploadHttpLink: $UploadHttpLink"

upload_flag="true"


if [ ! -d $LOG_PATH ]; then
    uploadLog "The /opt/logs folder is missing"
    exit 0
fi

sendTLSSSRRequest()
{
    TLSRet=1
    uploadLog "Attempting $TLS connection to SSR server"
    uploadLog "Connecting without authentication"
    CURL_CMD="curl  -w '%{http_code}\n' -d \"filename=$1\" -o \"$FILENAME\" \"$CLOUD_URL\" --connect-timeout $CURL_TLS_TIMEOUT -m 10"
    uploadLog "sendTLSSSRRequest: Connect with URL_CMD: `echo "$CURL_CMD"`"
    eval $CURL_CMD > $HTTP_CODE
    TLSRet=$?

    logTLSError $TLSRet "SSR"
    uploadLog "Connect with Curl return code : $TLSRet"
}


HttpLogUpload()
{
    result=1
    FILENAME='/tmp/httpresult.txt'
    CLOUD_URL=`echo $UploadHttpLink | sed "s/http:/https:/g"`
    domainName=`echo $CLOUD_URL | awk -F/ '{print $3}'`
    UploadHttpParams=`echo $CLOUD_URL | sed -e "s|.*$domainName||g"`
    http_code="000"
    retries=0
    cbretries=0

     uploadLog "HttpLogUpload: Attempt to upload the logs using direct connection"
            while [ "$retries" -lt $NUM_UPLOAD_ATTEMPTS ]
            do
                uploadLog "HttpLogUpload: Attempting direct log upload"
                sendTLSSSRRequest $1
                ret=$TLSRet
                http_code=$(awk -F\" '{print $1}' $HTTP_CODE)
                if [ "$http_code" = "200" ];then       # anything other than success causes retries
                    uploadLog "HttpLogUpload: Direct log upload Success: httpcode=$http_code"
                    break
                elif [ "$http_code" = "404" ]; then
                    uploadLog "HttpLogUpload: Received 404 response for Direct log upload, Retry logic not needed"
                    break
                fi
                retries=`expr $retries + 1`
                 uploadLog "HttpLogUpload: Direct log upload attempt return: retry=$retries, httpcode=$http_code"
                                 sleep 60
            done

    if [ "$http_code" != "200" ] && [ "$http_code" != "404" ] || ["$http_code" == "000" ]; then
         uploadLog "HttpLogUpload: Direct log upload failed: httpcode=$http_code"
    fi

    if [ "$http_code" = "200" ];then
        uploadLog "S3 upload query success. Got new S3 url to upload log"
        #Get the url from FILENAME
        NewUrl=\"$(awk -F\" '{print $1}' $FILENAME)\"

        NewUrl=`echo $NewUrl | sed "s/http:/https:/g"`
        uploadLog "Attempting $TLS connection for Uploading Logs to S3 Amazon server"

        CURL_CMD="curl $TLS -w '%{http_code}\n' -T \"$1\" -o \"$FILENAME\" $NewUrl --connect-timeout 60 -m 120 -v"

        # RDK-20447 --- https://ccp.sys.comcast.net/browse/RDK-20447
        #Modified the NewUrl value to remove the signature parameter & its value from loggging in to a decmscript.log file
        RemSignature=`echo $NewUrl | sed "s/AWSAccessKeyId=.*Signature=.*&//g;s/.*https/https/g"`

        LogCurlCmd="curl $TLS -w '%{http_code}\n' -T \"$1\" -o \"$FILENAME\" \"$RemSignature\" --connect-timeout 60 -m 120 -v"

        uploadLog "CURL_CMD: $LogCurlCmd"
        #RDK-20447 --End

        eval $CURL_CMD > $HTTP_CODE
        ret=$?
        logTLSError $ret "S3"
        http_code=$(awk -F\" '{print $1}' $HTTP_CODE)
        rm $FILENAME
        # Curl ret and http_code
        uploadLog "ret = $ret http_code: $http_code"

        if [ "$http_code" = "200" ];then
            result=0
            uploadLog "Successfully uploaded Logs to S3 Amazon server"
        else
                uploadLog "Failed Uploading Logs through - HTTP"
        fi
    else
        uploadLog "S3 upload query Failed"
    fi
   echo $result
}


uploadLogOnReboot()
{
    uploadLog=$1
    ret=`ls $LOG_PATH/*.txt`
    if [ ! $ret ]; then
         ret=`ls $LOG_PATH/*.log`
         if [ ! $ret ]; then
               uploadLog "Log directory empty, skipping log upload"
               exit 0
         fi
    fi
    uploadLog "Sleeping for seven minutes"
        sleep 330
    uploadLog "Done sleeping"
    if [ ! -z $OPENSSL_LOG_PATH ]; then
        cd  $OPENSSL_LOG_PATH 
    else
        cd $STRESS_NG_LOG_PATH  
    fi

   if [ $uploadLog == "true" ]; then
        uploadLog "Uploading Logs with DCM"
        tar -zcvf $LOG_FILE * >> $LOG_PATH/dcmscript.log  2>&1
        sleep 60
        if [ "$UploadProtocol" == "HTTP" ];then
            retval=$(HttpLogUpload $LOG_FILE)
            if [ $retval -ne 0 ];then
                uploadLog "HTTP log upload failed"
		exit 0
            fi
        fi
    else
        uploadLog "Not Uploading Logs with DCM"
    fi
    sleep 5
    if [ ! -z $OPENSSL_LOG_PATH ]; then
        uploadLog "Deleting from $OPENSSL_LOG_PATH  Folder "
        rm -rf $OPENSSL_LOG_PATH
    else
        uploadLog " Deleting from $STRESS_NG_LOG_PATH Folder"
        rm -rf $STRESS_NG_LOG_PATH
    fi
}


     uploadLog "Uploading Without DCM"
     uploadLogOnReboot true
