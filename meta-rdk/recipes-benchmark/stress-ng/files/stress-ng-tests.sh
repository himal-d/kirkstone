#!/bin/sh

source /etc/device.properties
## Start Global variables

if [ "$DEVICE_TYPE" == "broadband" ]; then
	RW_DISK_LOCATION="/rdklogs"
	LOG_PATH="/rdklogs/logs"
else
RW_DISK_LOCATION="/opt"
LOG_PATH="/opt/logs"
fi
STRESS_NG_LOG_PATH="$LOG_PATH/stress-ng_logs"
LOG_FILE="$STRESS_NG_LOG_PATH/rdk-oss-perf-stats.log"
STRESS_NG_WORKSPACE="$RW_DISK_LOCATION/stress-ng"
ENABLE_OPTIONS="--times --metrics --perf"

TEMP_PATH="--temp-path $STRESS_NG_WORKSPACE"

TEST_COUNT=0

YAML_OPTION="--yaml $STRESS_NG_LOG_PATH/metrics_"

#Logging Arguments
upload_protocol="HTTP"
upload_httplink="https://ssr.ccp.xcal.tv/cgi-bin/S3.cgi"
tftp_server="logs.xcal.tv"

## End Global variables

boot_time=600
read -d. seconds < /proc/uptime
if [ $seconds -lt $boot_time ]; then
echo "Waiting for $(( $boot_time - $seconds )) secs to start the stress-NG testcases"
sleep $(( $boot_time - $seconds ))
fi

if [ -f /etc/stress-ng.conf ];then
     . /etc/stress-ng.conf
fi

log(){
   echo "`date` :`basename $0`: $*"    >> $LOG_FILE
}

tearDown() {
    sh /lib/rdk/capture-proc-metrics.sh end
    echo "Tear down test resources"
    rm -rf $STRESS_NG_WORKSPACE
    log "End of stress NG tests"
}

logUptime(){
    echo "UPTIME : `uptime`" >> $LOG_FILE
    echo "" >> $LOG_FILE
}

logMem() {
    echo "Memory Details:" >>$LOG_FILE
    echo "`free`" >> $LOG_FILE
    echo "" >> $LOG_FILE
}

execAndRedirectOut(){

    TEST_COUNT=$((TEST_COUNT + 1))
    command=$*
    echo "Executing Stressor:$test"
    log " ===== Start : $command  ====="
    logUptime
    logMem
    currentDir=`pwd`
    cd $STRESS_NG_WORKSPACE
    $command >> $LOG_FILE  2>&1
    cd $currentDir
    logUptime
    logMem
    log " ===== End: $command  ====="
    echo "" >> $LOG_FILE
}


cpuStressTest(){
    #Load Avg:69
    test="cpu"
    if [ "$DEVICE_NAME" == "XiOne-SCB" ]; then 
    execAndRedirectOut stress-ng --all $CPU_INSTANCE --class cpu --exclude atomic,zlib,wcs,tree,radixsort,ioport,heapsort,crypt,pkey,numa,mergesort,judy,ipsec_mb,rdrand,tsc,opcode -t $CPU_TIME  $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    elif [ "$DEVICE_NAME" == "XiOne" ]; then
    execAndRedirectOut stress-ng --all $CPU_INSTANCE --class cpu --exclude atomic,zlib,wcs,tree,radixsort,ioport,heapsort,crypt,pkey,numa,mergesort,judy,ipsec_mb,rdrand,tsc,opcode,stream,skiplist,tsearch,vcemath -t $CPU_TIME  $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    else
    execAndRedirectOut stress-ng --all $CPU_INSTANCE --class cpu --exclude atomic,zlib,wcs,tree,radixsort,ioport,heapsort,crypt,pkey,numa,mergesort,judy,opcode -t $CPU_TIME  $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    fi
    execAndRedirectOut stress-ng --opcode 0 --opcode-method inc -t $CPU_TIME  $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    sh /lib/rdk/capture-proc-metrics.sh $test
}

cpuLongRunTest(){

   # Run cpu stressors on all online CPUs working through all the available CPU stressors for 5m
    test="cpu"
    execAndRedirectOut stress-ng $TEMP_PATH --cpu 0 --cpu-method all -t 5m $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    sh /lib/rdk/capture-proc-metrics.sh $test
}

diskIOTests(){
    test="io"
    # start N workers continually writing with commit buffer cache to disk, reading and removing temporary
    #load avg of 30
    execAndRedirectOut stress-ng --class io --all $IO_INSTANCE --exclude aiol,io-uring,rawdev,readahead -t $IO_TIME  $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    #stress-ng --iomix 1 -t 20 -v
    sh /lib/rdk/capture-proc-metrics.sh $test
}

schedulerTests() {
    test="scheduler"
    #load average: 193.86 120.35 53.12.incase of seq execution around 12
    #In Axi6 clone forks the processes more than the limit which casues the crash
    #TBD:skyxione scheduler case causes reboot.
    if [ "$DEVICE_NAME" != "XiOne" ]; then
    execAndRedirectOut stress-ng --sequential $SCHEDULER_INSTANCE --class scheduler -t $SCHEDULER_TIME --exclude netlink-task,vforkmany,clone,sem-sysv,schedpolicy,session,hrtimers,softlockup $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    execAndRedirectOut stress-ng --vforkmany 1 --vforkmany-ops 1000 -t 20s $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    execAndRedirectOut stress-ng --vfork 1 -t 20s $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    execAndRedirectOut stress-ng --clone 1 -t 20s $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    sh /lib/rdk/capture-proc-metrics.sh $test
    fi
}
memStressTest(){
    test="memory"
    # Use mmap N bytes per vm worker. specify size as % of total available memory
    # TBD : Beware of OOM killer triggering reboot - use percentile of available memory for stress test
    # Example of test triggering reboot stress-ng --brk 0 --stack 0 --bigheap 0
    #executing memory class makes the system to reboot
    execAndRedirectOut stress-ng $TEMP_PATH --vm 1 --vm-bytes 20% -t 10s --times $YAML_OPTION$test$TEST_COUNT.yaml
    execAndRedirectOut stress-ng --hdd 1 --hdd-bytes 50% -t 5s --metrics $YAML_OPTION$test$TEST_COUNT.yaml
    execAndRedirectOut stress-ng --malloc 1 --malloc-bytes 20% -t 10s --metrics -v --perf $YAML_OPTION$test$TEST_COUNT.yaml
    execAndRedirectOut stress-ng --stack 1 -t 10s --metrics $YAML_OPTION$test$TEST_COUNT.yaml
    execAndRedirectOut stress-ng --str 1 -t 10s --metrics $YAML_OPTION$test$TEST_COUNT.yaml
    execAndRedirectOut stress-ng --memcpy 1 -t 10s --metrics $YAML_OPTION$test$TEST_COUNT.yaml
    execAndRedirectOut stress-ng --memfd 1 -t 10s --metrics $YAML_OPTION$test$TEST_COUNT.yaml
    execAndRedirectOut stress-ng --stream 1 -t 10s --metrics $YAML_OPTION$test$TEST_COUNT.yaml
#execAndRedirectOut stress-ng --sequential 1 --class memory --exclude atomic,membarrier,judy,heapsort,mergesort,numa,pipe,pipeherd,radixsort,tree,wcs,zlib -t 10s --times --metrics $YAML_OPTION$test$TEST_COUNT.yaml

    # Shared memory tests has some problems
    # execAndRedirectOut stress-ng --shm --shm-bytes 100% -v -t 5s
    sh /lib/rdk/capture-proc-metrics.sh $test
}

thermalZoneTests() {

   ##TBD - Debug this stress-ng: info:  [12561] thermal zone temperatures not available
    execAndRedirectOut stress-ng --matrix 0 --tz -t 60 --log-brief -v --times $YAML_OPTION$test$TEST_COUNT.yaml
    execAndRedirectOut stress-ng --cpu 0 --tz -t 5 --log-brief $YAML_OPTIOt$test$TEST_COUNT.yaml
}

pageFaultTests(){
    test="os"
        #load average:  46.79 18.09 14.62
    if [ "$DEVICE_NAME" == "XiOne" ]; then 
    #in Xione, 1) TBD: we see Loop Testcase cause uninterruptible sleep state.Multiple instances of loop TC will stuck in removing the loop device
    #          2) seccomp Testcase is not supported
    execAndRedirectOut stress-ng --fault $OS_INSTANCE --switch $OS_INSTANCE  --klog $OS_INSTANCE  --ptrace $OS_INSTANCE --pty $OS_INSTANCE  --sendfile $OS_INSTANCE  --resources $OS_INSTANCE --revio $OS_INSTANCE --rmap $OS_INSTANCE  -t $OS_TIME $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    execAndRedirectOut stress-ng --loop 1 -t 30s $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    else
    execAndRedirectOut stress-ng --fault $OS_INSTANCE --switch $OS_INSTANCE --loop $OS_INSTANCE --klog $OS_INSTANCE  --ptrace $OS_INSTANCE --pty $OS_INSTANCE  --sendfile $OS_INSTANCE --seccomp $OS_INSTANCE --resources $OS_INSTANCE --revio $OS_INSTANCE --rmap $OS_INSTANCE  -t $OS_TIME $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    fi
    sh /lib/rdk/capture-proc-metrics.sh $test
}

timerTests(){
    test="timer"
    #load average: 13.72 16.99 27.67
    execAndRedirectOut stress-ng --timer $TIMER_INSTANCE --timer-freq $TIMER_FREQ --rtc $TIMER_INSTANCE --clock $TIMER_INSTANCE --itimer $TIMER_INSTANCE  --timerfd $TIMER_INSTANCE  -t $TIMER_TIME $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    sh /lib/rdk/capture-proc-metrics.sh $test
}

networkTests(){
    test="network"
    #sock testcase has some issue
    execAndRedirectOut stress-ng --sequential $NETWORK_INSTANCE --class network --exclude dccp,sctp,sock,sockpair -t $NETWORK_TIME $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    sh /lib/rdk/capture-proc-metrics.sh $test
}

runAllTests(){
   # run 4 simultaneous instances of all the stressors sequentially one by one, each for 6 minutes and summaries with performance metrics at the end
   # --pathological  Go for it !!! Destructive tests 
    stress-ng $TEMP_PATH --sequential 4 --timeout 6m --pathological --metrics $YAML_OPTION$TEST_COUNT.yaml
}

# This test can be used to check for applications that doesn't handle OOM gracefully
memoryPressureTest() {
    test="memory"
   #load average: 31.05 26.55 18.00
   execAndRedirectOut stress-ng --brk 30 --brk-notouch --verbose --metrics -t 30s –-times $YAML_OPTION$test$TEST_COUNT.yaml
   sleep 5
   #load average: 
   execAndRedirectOut stress-ng --shm 10 --shm-objs 4 --shm-bytes 5% --times --metrics -t 30s $YAML_OPTION$test$TEST_COUNT.yaml
   sleep 5
   #load average: 5.26 5.97 3.34
   execAndRedirectOut stress-ng --bigheap 1 --bigheap-growth 4K -t 4s --times $YAML_OPTION$test$TEST_COUNT.yaml
   sleep 5
   #stress-ng --brk 2 --stack 2 --bigheap 2
   sh /lib/rdk/capture-proc-metrics.sh $test
}

pipeTests() {
   test="pipe"
   #load avg of 139
   execAndRedirectOut stress-ng --class pipe --all $PIPE_INSTANCE -t $PIPE_TIME $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
   sh /lib/rdk/capture-proc-metrics.sh $test
}

fileTests() {
   test="file"
   #load avg of 150
   if [ "$DEVICE_NAME" == "XiOne" ]; then 
   #xione does not support copy-file and fanotify stressor
   execAndRedirectOut stress-ng --sequential $FILE_INSTANCE --class filesystem --exclude binderfs,chattr,fiemap,xattr,iomix,copy-file,fanotify,procfs -t $FILE_TIME $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
   else
   execAndRedirectOut stress-ng --sequential $FILE_INSTANCE --class filesystem --exclude binderfs,chattr,fiemap,xattr,iomix,procfs -t $FILE_TIME $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
   fi
   sh /lib/rdk/capture-proc-metrics.sh $test
}
ipcTests() {
    test="ipc"
    #ipcTests already covered in Scheculer Testcase
    execAndRedirectOut stress-ng --mq $IPC_INSTANCE --shm $IPC_INSTANCE --sem $IPC_INSTANCE -t $IPC_TIME $ENABLE_PERF $YAML_OPTION$test$TEST_COUNT.yaml
    sh /lib/rdk/capture-proc-metrics.sh $test
}
signalTests() {
    test="signal"
#load average: 70.21, 21.60, 14.11
#sigabrt causing coredump
    execAndRedirectOut stress-ng --sigfd $SIGNAL_INSTANCE --sigfpe $SIGNAL_INSTANCE --sigchld $SIGNAL_INSTANCE --sigio $SIGNAL_INSTANCE --sigpending $SIGNAL_INSTANCE --sigsegv $SIGNAL_INSTANCE --sigsuspend $SIGNAL_INSTANCE --sigq $SIGNAL_INSTANCE  --sigtrap $SIGNAL_INSTANCE -t $SIGNAL_TIME $ENABLE_OPTIONS $YAML_OPTION$test$TEST_COUNT.yaml
    sh /lib/rdk/capture-proc-metrics.sh $test
}
systemcallTests() {
    test="syscall"
    #exercise process creation/Termination
        # load average: 23.45 14.50 12.89
    execAndRedirectOut stress-ng --fork $SYSCALL_INSTANCE --open $SYSCALL_INSTANCE --close $SYSCALL_INSTANCE --seek $SYSCALL_INSTANCE --wait $SYSCALL_INSTANCE --kill $SYSCALL_INSTANCE -t $SYSCALL_TIME $ENABLE_OPTIONS  $YAML_OPTION$test$TEST_COUNT.yaml
    sh /lib/rdk/capture-proc-metrics.sh $test
}

getStressExeSize() {
    log "SIZE OF THE STRESS-NG EXE:"
    echo "`size /usr/bin/stress-ng`" >> $LOG_FILE
}

init(){
   rm -rf $LOG_PATH/*  
   if [ "$DEVICE_TYPE" == "broadband" ]; then
	   mkdir -p /rdklogs/stress-ng
   else
   mkdir -p /opt/stress-ng
   fi
   mkdir -p $LOG_PATH/stress-ng_logs
   echo '' > $LOG_FILE
   rm -f $STRESS_NG_LOG_PATH/metrics_*
   getStressExeSize
   log "Start of stress NG tests"
   sh /lib/rdk/capture-proc-metrics.sh start

   memStressTest
   #memoryPressureTest  bigheap causing reboot
   sleep 60

   cpuLongRunTest
   cpuStressTest
   sleep 60

   #test="thermal"
   #thermalZoneTests

   pageFaultTests
   sleep 60

   networkTests
   sleep 60

   timerTests
   sleep 60

   ipcTests
   sleep 60

   signalTests
   sleep 60

   systemcallTests
   sleep 60

   fileTests
   sleep 60

   pipeTests
   sleep 60

   schedulerTests
   sleep 60

   diskIOTests
   sleep 60
}



# main starts here

init

# Test categories should be as below :
#CPU compute
#drive stress
#I/O syncs
#Pipe I/O
#cache thrashing
#VM stress
#socket stressing
#process creation and termination
#context switching properties

#cpuStressTest

#diskIOTest

#memStressTest

#cpuLongRunTest

#thermalZoneTests

#pageFaultTests

#networkTests


# Do not run all test atleast on XI6 - kernel crashes and OOM reboot kicks in  
# runAllTests

tearDown

/bin/sh /lib/rdk/rdk_oss_uploadSTBLogs.sh $tftp_server $upload_protocol $upload_httplink





