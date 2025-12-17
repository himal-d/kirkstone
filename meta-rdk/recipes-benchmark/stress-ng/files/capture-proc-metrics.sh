#!/bin/sh
source /etc/device.properties

if [ "$DEVICE_TYPE" == "broadband" ]; then
	RW_DISK_LOCATION="/rdklogs/logs"
	LOG_PATH="/rdklogs/logs"
else
RW_DISK_LOCATION="/opt"
LOG_PATH="/opt/logs"
fi
STRESS_NG_LOG_PATH="$LOG_PATH/stress-ng_logs"
LOG_FILE="$STRESS_NG_LOG_PATH/rdk-oss-perf-stats.yaml"
STRESS_NG_WORKSPACE="$RW_DISK_LOCATION/stress-ng"_

if [ ! -z "$2" ]; then
STRESS_NG_LOG_PATH=$2
fi

setLogFile(){
   LOG_FILE="$STRESS_NG_LOG_PATH/$1_proc_stats.yaml"
   rm -f $LOG_FILE
}

getEthMac(){
    if [ "$DEVICE_TYPE" == "broadband" ]; then
       ifconfig erouter0 | grep "HWaddr" | tr -s " " | cut -d ' ' -f5
    else
       ifconfig eth0 | grep "HWaddr" | tr -s " " | cut -d ' ' -f5
    fi
}

getCpuModel(){
    grep "model name" /proc/cpuinfo | head -n1 | tr -s ' ' | cut -d ' ' -f3
}

populateSystemInfo()
{
      echo "---" >> $LOG_FILE
      echo "system-info:" >> $LOG_FILE
      echo "    imagename: `cat /version.txt | head -n 1 | cut -d ":" -f2`" >> $LOG_FILE
      echo "    ethernet_MAC: `getEthMac`" >> $LOG_FILE
      echo "    date-yyyy-mm-dd: `date +'%Y:%m:%d'`" >> $LOG_FILE
      echo "    time-hh-mm-ss: `date +'%H:%M:%S'`" >> $LOG_FILE
      echo "    epoch-secs: `date +%s`" >> $LOG_FILE
      echo "    hostname: `hostname`" >> $LOG_FILE
      echo "    release: `uname -r`" >> $LOG_FILE
      echo "    machine: `getCpuModel`" >> $LOG_FILE
      echo "    uptime: `cat /proc/uptime | cut -d " " -f1`" >> $LOG_FILE
      echo "    gcc-version : `sed -e "s/.*gcc version //g" /proc/version | cut -d " " -f1`" >> $LOG_FILE
      if [ "$DEVICE_TYPE" == "broadband" ]; then
	      OPENSSL_LOG_PATH="/rdklogs/logs/openssl_logs"
      else
	      OPENSSL_LOG_PATH="/opt/logs/openssl_logs"
      fi
      if [ -d "$OPENSSL_LOG_PATH" ]; then
      echo "    Openssl-version: `openssl version | cut -d " " -f2`" >> $LOG_FILE
      fi
      echo "" >> $LOG_FILE
      echo "metrics:" >> $LOG_FILE
}

populateSysMemInfo(){

    echo "  - class: mem" >> $LOG_FILE
    echo "    `grep 'MemTotal:' /proc/meminfo`" >> $LOG_FILE
    echo "    `grep 'MemFree:' /proc/meminfo`" >> $LOG_FILE
    echo "    `grep 'MemAvailable:' /proc/meminfo`" >> $LOG_FILE
    echo "    `grep 'Shmem:' /proc/meminfo`" >> $LOG_FILE
    echo "    `grep 'Buffers:' /proc/meminfo`" >> $LOG_FILE
    echo "    `grep 'Dirty:' /proc/meminfo`" >> $LOG_FILE
    grep -i 'cached' /proc/meminfo | awk '{print "    " $0}' >> $LOG_FILE
    grep -i 'active' /proc/meminfo | awk '{print "    " $0}' >> $LOG_FILE
    grep -i 'commit' /proc/meminfo | awk '{print "    " $0}' >> $LOG_FILE
    echo "" >> $LOG_FILE

}

populateSysCPUInfo(){

    echo "  - class: cpu" >> $LOG_FILE
    echo "    context_sitches : `grep 'ctxt' /proc/stat | tr -s " " | cut -d " " -f2`" >> $LOG_FILE
    grep "cpu" /proc/stat | tr -s " " | cut -d " " -f1,2 | sed -e "s/cpu/User_Time_cpu/g" | sed -e "s/ / : /g" | awk '{print "    " $0}' >> $LOG_FILE
    grep "cpu" /proc/stat | tr -s " " | cut -d " " -f1,4 | sed -e "s/cpu/System_Time_cpu/g" | sed -e "s/ / : /g" | awk '{print "    " $0}'  >> $LOG_FILE
    grep "cpu" /proc/stat | tr -s " " | cut -d " " -f1,5 | sed -e "s/cpu/Idle_cpu/g" | sed -e "s/ / : /g" | awk '{print "    " $0}' >> $LOG_FILE
    grep "cpu" /proc/stat | tr -s " " | cut -d " " -f1,8 | sed -e "s/cpu/Irq_cpu/g" | sed -e "s/ / : /g" | awk '{print "    " $0}' >> $LOG_FILE

}


calc_bogo_ops() {
TimeDiff=` echo $2 $1 | awk '{print $1 - $2}'`
bogoOpsPerSec_us=`echo $3 $TimeDiff | awk '{print $1 / $2}'`
echo "    NoOfIterations   : $3" >> $LOG_FILE
echo "    RealTime         : `echo $4 1000 | awk '{print $1 * $2}'`" >> $LOG_FILE
echo "    BogoOpsPerSec_us : $bogoOpsPerSec_us"
echo "    BogoOpsPerSec_us : $bogoOpsPerSec_us" >> $LOG_FILE

bogoOpsPerSec_rl=`echo $3 $4 | awk '{print $1 / $2}'`
echo "    BogoOpsPerSec_rl : $bogoOpsPerSec_rl"
echo "    BogoOpsPerSec_rl : $bogoOpsPerSec_rl" >> $LOG_FILE
}

# Start
fileNameSuffix=$1
if [ -z "${fileNameSuffix}" ]; then
    echo "Please enter a file name sufix "
    echo "${0} start"
    exit 0
fi

setLogFile $fileNameSuffix

populateSystemInfo

populateSysMemInfo

populateSysCPUInfo

noOfItr=$3
pre_Exec=$4
post_Exec=$5
real_time=$6
if [ ! -z "${noOfItr}" ]; then
calc_bogo_ops $pre_Exec $post_Exec $noOfItr $real_time
fi


echo "..." >> $LOG_FILE

