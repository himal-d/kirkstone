#!/bin/sh

source /etc/device.properties 

run() {
    number=$1
    shift
    for ((n=0;n<=$number;n++))
    do
      $@  &> /dev/null
    done
}
if [ -d /tmp/openssl-ptest ]; then
dir_path="/tmp/openssl-ptest/usr/lib/openssl/ptest/"
elif [ -d /tmp/lib32-openssl-ptest ]; then
dir_path="/tmp/lib32-openssl-ptest/usr/lib/openssl/ptest/"
fi
if [ ! -d $dir_path ]; then
    echo "Please wait for the openssl ptest package to download"
    exit
fi

if [ "$DEVICE_TYPE" == "broadband" ]; then
     RW_DISK_LOCATION="/rdklogs"
     LOG_PATH="/rdklogs/logs/openssl_logs"
else
     LOG_PATH="/opt/logs/openssl_logs"
fi
mkdir -p $LOG_PATH
LOG_FILE="$LOG_PATH/openssl-stats.log"
log(){
   echo "`date` :`basename $0`: $*"    >> $LOG_FILE
}
stress_bio_function() {
$dir_path/test/bioprinttest
$dir_path/test/bio_memleak_test
$dir_path/test/bio_enc_test
$dir_path/test/bio_callback_test
}
stress_ui_function() {
$dir_path/test/uitest
}
stress_ec_function() {
$dir_path/test/ectest
$dir_path/test/ec_internal_test
}
stress_engine_function() {
$dir_path/test/enginetest
}
stress_bn_function() {
$dir_path/test/bntest
}
stress_rsa_function() {
$dir_path/test/rsa_test
$dir_path/test/rsa_mp_test
}
stress_des_function() {
$dir_path/test/modes_internal_test
$dir_path/test/destest
}
stress_cipher_function() {
$dir_path/test/ciphername_test
$dir_path/test/cipherlist_test
$dir_path/test/cipherbytes_test
}
stress_err_function () {
$dir_path/test/errtest
$dir_path/test/fatalerrtest $dir_path/apps/server.pem $dir_path/apps/server.pem
}
stress_x509_function() {
$dir_path/test/x509aux  $dir_path/test/certs/roots.pem $dir_path/test/certs/root+anyEKU.pem $dir_path/test/certs/root-anyEKU.pem $dir_path/test/certs/root-cert.pem $dir_path/test/certs/invalid-cert.pem
$dir_path/test/x509_time_test
$dir_path/test/x509_internal_test
$dir_path/test/x509_dup_cert_test $dir_path/test/certs/leaf.pem
$dir_path/test/x509_check_cert_pkey_test $dir_path/test/certs/servercert.pem  $dir_path/test/certs/serverkey.pem cert ok
$dir_path/test/x509_check_cert_pkey_test $dir_path/test/certs/servercert.pem  $dir_path/test/certs/wrongkey.pem cert failed
/tmp/openssl-ptest/usr/lib/openssl/ptest/test/x509_check_cert_pkey_test $dir_path/test/certs/server-dsa-cert.pem $dir_path/test/certs/server-dsa-key.pem cert ok
$dir_path/test/x509_check_cert_pkey_test $dir_path/test/certs/server-ecdsa-cert.pem $dir_path/test/certs/server-ecdsa-key.pem cert ok
$dir_path/test/x509_check_cert_pkey_test $dir_path/test/certs/x509-check.csr $dir_path/test/certs/x509-check-key.pem req ok
/tmp/openssl-ptest/usr/lib/openssl/ptest/test/x509_check_cert_pkey_test $dir_path/test/certs/x509-check.csr $dir_path/test/certs/wrongkey.pem req failed
}
stress_dsa_function() {
$dir_path/test/ecdsatest
$dir_path/test/dsatest
$dir_path/test/dsa_no_digest_size_test
}
stress_tls_function() {
$dir_path/test/dtlsv1listentest
$dir_path/test/dtlstest $dir_path/apps/server.pem $dir_path/apps/server.pem
$dir_path/test/dtls_mtu_test
$dir_path/test/bad_dtls_test
$dir_path/test/tls13secretstest
$dir_path/test/tls13encryptiontest
$dir_path/test/tls13ccstest $dir_path/apps/server.pem $dir_path/apps/server.pem
}
stress_dh_function() {
$dir_path/test/dhtest
}
stress_evp_function() {
$dir_path/test/evp_extra_test
$dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evpciph.txt
$dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evpdigest.txt
$dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evpencod.txt
$dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evpkdf.txt
$dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evpmac.txt
$dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evppbe.txt
$dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evppkey.txt
$dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evppkey_ecc.txt
$dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evpcase.txt
$dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evpccmcavs.txt
}
stress_cipher_function() {
$dir_path/test/ciphername_test
$dir_path/test/cipherlist_test
$dir_path/test/cipherbytes_test
}
stress_asn1_function() {
$dir_path/test/asn1_time_test
$dir_path/test/asn1_string_table_test
$dir_path/test/asn1_internal_test
$dir_path/test/asn1_encode_test
$dir_path/test/asn1_decode_test
}
stress_hmac_function() {
$dir_path/test/hmactest
}
execute_ui_test() {
start=$(date +%s.%N)
# *** CPU reaches around 20 % ***
for ((i=1;i<=15;i++))
do
run 200 stress_ui_function &
done
wait
test="ui"
sys_time2=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time2=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total2=`echo $sys_time2 $usr_time2 | awk '{print $1 + $2}'`
t2=`echo $Total2 | awk '{print $1 / 100 }'`
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 200 $t1 $t2 $rl
echo "Time Taken for $test Test Execution: $rl seconds"
}
execute_bio_test() {
start=$(date +%s.%N)
# *** CPU reaches around 75 % ***
for ((i=1;i<=3;i++))
do
run 50 stress_bio_function &
done
wait
test="bio"
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t1=`echo $Total1 | awk '{print $1 / 100 }'`
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 50 $t2 $t1 $rl
echo "Time taken for $test Test execution : $rl seconds"
}
execute_dsa_test() {
start=$(date +%s.%N)
# ***CPU reaches around 65% ***
for ((i=1;i<=3;i++))
do
run 1 stress_dsa_function &
done
wait
test="dsa"
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t2=`echo $Total1 | awk '{print $1 / 100 }'`
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 1 $t1 $t2 $rl
echo "Time taken for $test Test execution: $rl seconds"
}
execute_tls_test() {
start=$(date +%s.%N)
# ** CPU Goes till 8 % **
for ((i=1;i<=3;i++))
do
run 1 stress_tls_function &
done
wait
test="tls"
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t1=`echo $Total1 | awk '{print $1 / 100 }'`
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 1 $t2 $t1 $rl
echo "Time Taken for $test Test Execution: $rl seconds"
}
execute_cipher_test() {
start=$(date +%s.%N)
# ** CPu reaches around 30% ***
for ((i=1;i<=5;i++))
do
run 200 stress_cipher_function &
done
wait
test="cipher"
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t2=`echo $Total1 | awk '{print $1 / 100 }'`
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 200 $t1 $t2 $rl
echo "Time Taken for $test Test Execution: $rl seconds"
}
execute_asn1_test() {
start=$(date +%s.%N)
# *** CPU not crossing above 5%  even with 200 iteration in 5 loops***
for ((i=1;i<=3;i++))
do
run 25 stress_asn1_function &
done
wait
test="asn1"
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t1=`echo $Total1 | awk '{print $1 / 100 }'`
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 25 $t2 $t1 $rl
echo "Time Taken for $test Test Execution: $rl seconds"
}
execute_dh_test() {
start=$(date +%s.%N)
# *** CPu exceeds above 75 % ****
for ((i=1;i<=3;i++))
do
run 15 stress_dh_function &
done
wait
test="dh"
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t2=`echo $Total1 | awk '{print $1 / 100 }'`
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 15 $t1 $t2 $rl
echo "Time Taken for $test Test Execution: $rl seconds"
}
execute_hmac_test() {
start=$(date +%s.%N)
# *** CPU exceeds 2% only****
for ((i=1;i<=5;i++))
do
run 300 stress_hmac_function &
done
wait
test="hmac"
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t1=`echo $Total1 | awk '{print $1 / 100 }'`
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 300 $t2 $t1 $rl
echo "Time Taken for $test Test Execution: $rl seconds"
}
execute_evp_test() {
start=$(date +%s.%N)
# *** CPU exceeds 50% ****
for ((i=1;i<=2;i++))
do
run 1 stress_evp_function &
done
wait
test="evp"
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t2=`echo $Total1 | awk '{print $1 / 100 }'`
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 1 $t1 $t2 $rl 
echo "Time Taken for $test Test Execution: $rl seconds"
}
execute_x509_test() {
start=$(date +%s.%N)
# *** CPU Goes 8% ****
for ((i=1;i<=5;i++))
do
run 25 stress_x509_function &
done
wait
test="x509"
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t1=`echo $Total1 | awk '{print $1 / 100 }'`
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 25 $t2 $t1 $rl
echo "Time Taken for $test Test Execution: $rl seconds"
}
execute_ec_test() {
start=$(date +%s.%N)
# *** CPu exceeds 75% ****
for ((i=1;i<=3;i++))
do
run 1 stress_ec_function &
done
wait
test="ec"
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t2=`echo $Total1 | awk '{print $1 / 100 }'`
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 1 $t1 $t2 $rl 
echo "Time Taken for $test Test Execution: $rl seconds"
}
execute_bn_test() {
start=$(date +%s.%N)
# *** CPu exceeds 75% ****
for ((i=1;i<=3;i++))
do
run 1 stress_bn_function &
done
wait
test="bn"
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t1=`echo $Total1 | awk '{print $1 / 100 }'`
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 1 $t2 $t1 $rl
echo "Time Taken for $test Test Execution: $rl seconds"
}
execute_rsa_test() {
start=$(date +%s.%N)
# *** CPu exceeds 75% ****
for ((i=1;i<=3;i++))
do
run 30  stress_rsa_function &
done
wait
test="rsa"
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t2=`echo $Total1 | awk '{print $1 / 100 }'`
wait
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 30 $t1 $t2 $rl
echo "Time Taken for $test Test Execution: $rl seconds"
}
execute_des_test() {
start=$(date +%s.%N)
# *** CPu Not hogging ****
for ((i=1;i<=10;i++))
do
run 20  stress_des_function &
done
wait
test="des"
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t1=`echo $Total1 | awk '{print $1 / 100 }'`
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 10 $t2 $t1 $rl
echo "Time Taken for $test Test Execution: $rl seconds"
}
execute_engine_test() {
start=$(date +%s.%N)
# *** CPu goes 50% ****
for ((i=1;i<=10;i++))
do
run 50  stress_engine_function &
done
wait
test="engine"
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t2=`echo $Total1 | awk '{print $1 / 100 }'`
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 50 $t1 $t2 $rl
echo "Time Taken for $test Test Execution: $rl seconds"
sleep 60
}
execute_err_test() {
start=$(date +%s.%N)
# *** CPu goes 10% ****
for ((i=1;i<=10;i++))
do
run 150  stress_err_function &
done
wait
test="err"
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t1=`echo $Total1 | awk '{print $1 / 100 }'`
end=$(date +%s.%N)
rl=`echo $end  $start | awk '{print $1 - $2}'`
sh /lib/rdk/capture-proc-metrics.sh openssl_$test $LOG_PATH 150 $t2 $t1 $rl
echo "Time Taken for $test Test Execution: $rl seconds"
}
init() {
echo '' > $LOG_FILE
log "Start of Openssl Stress Test Suite"
##starting system param capture ##
exec_start=$(date +%s.%N)
sh /lib/rdk/capture-proc-metrics.sh start $LOG_PATH 
sleep 60
sys_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f4`
usr_time1=`grep "cpu"  /proc/stat | head -n 1 | tr -s " " | cut -d " " -f2`
Total1=`echo $sys_time1 $usr_time1 | awk '{print $1 + $2}'`
t1=`echo $Total1 | awk '{print $1 / 100 }'`
log "Starting UI Test"
time execute_ui_test
sleep 60
log "Starting BIO Test"
time execute_bio_test
sleep 60
log "Starting DSA Test"
time execute_dsa_test
sleep 60
log "Starting TLS Test"
time execute_tls_test
sleep 60
log "Starting CIPHER Test"
time execute_cipher_test
sleep 60
log "Starting ASN1 Test"
time execute_asn1_test
sleep 60
log "Starting DH Test"
time execute_dh_test
sleep 60
log "Starting HMAC Test"
time execute_hmac_test
sleep 60
log "Starting EVP Test"
time execute_evp_test
sleep 60
log "Starting X509 Test"
time execute_x509_test
sleep 60
log "Starting EC Test"
time execute_ec_test
sleep 60
log "Starting BN Test"
time execute_bn_test
sleep 60
log "Starting RSA Test"
time execute_rsa_test
sleep 60
log "Starting DES Test"
time execute_des_test
sleep 60
log "Starting ENGINE Test"
time execute_engine_test
sleep 60
log "Starting ERR Test"
time execute_err_test
exec_end=$(date +%s.%N)
total_time=`echo $exec_end $exec_start | awk '{print $1 - $2}'`
echo "Time Taken for Total Test Execution: $total_time seconds"
log "Time Taken for Total Test Execution: $total_time seconds"

}
init
