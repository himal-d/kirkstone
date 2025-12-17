#!/bin/sh

source /etc/device.properties

if [ -d /tmp/openssl-ptest ]; then
dir_path="/tmp/openssl-ptest/usr/lib/openssl/ptest/"
elif [ -d /tmp/lib32-openssl-ptest ]; then
dir_path="/tmp/lib32-openssl-ptest/usr/lib/openssl/ptest/"
fi

if [ ! -d $dir_path ]; then
    # Need to wait for the openssl ptest package to download. Message logged in stress script
    exit
fi

# / **Global Variables **/
if [ "$DEVICE_TYPE" == "broadband" ]; then
      RW_DISK_LOCATION="/rdklogs"
      LOG_PATH="/rdklogs/logs/openssl_logs"
      perf_stat="perf stat -e branch-instructions,branch-misses,bus-cycles,cache-misses,cache-references,cpu-cycles,instructions,alignment-faults,cs,cpu-clock,cpu-migrations,major-faults,minor-faults,page-faults,task-clock,L1-dcache-load-misses,L1-dcache-store-misses,dTLB-load-misses,iTLB-load-misses,sched:sched_wakeup_new,sched:sched_wakeup,sched:sched_switch,sched:sched_move_numa"

else
      LOG_PATH="/opt/logs/openssl_logs"
      perf_stat="perf stat -e branch-instructions,branch-misses,bus-cycles,cache-misses,cache-references,cpu-cycles,instructions,alignment-faults,cs,cpu-clock,cpu-migrations,major-faults,minor-faults,page-faults,task-clock,L1-dcache-load-misses,L1-dcache-store-misses,dTLB-load-misses,iTLB-load-misses,sched:sched_wakeup_new,sched:sched_wakeup,sched:sched_switch,migrate:mm_migrate_pages,sched:sched_move_numa,kmem:mm_page_alloc,kmem:kmalloc"

fi
#Logging Arguments
upload_protocol="HTTP"
upload_httplink="https://ssr.ccp.xcal.tv/cgi-bin/S3.cgi"
tftp_server="logs.xcal.tv"

mkdir -p $LOG_PATH
rm -rf $LOG_PATH/perf_stat*.log
LOG_FILE="$LOG_PATH/openssl-stats.log"

log(){
   echo "`date` :`basename $0`: $*"    >> $LOG_FILE
}

stress_bio_function() {
test="bio_print"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/bioprinttest & > /dev/null
test="bio_memleak"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/bio_memleak_test & > /dev/null
test="bio_enc"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/bio_enc_test & > /dev/null
test="bio_cb"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/bio_callback_test & > /dev/null
}

stress_ui_function() {
test="uitest"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/uitest & > /dev/null
}

stress_ec_function() {
test="ectest"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/ectest & > /dev/null
test="ec_internal"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/ec_internal_test & > /dev/null
}

stress_engine_function() {
test="engine"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/enginetest & > /dev/null
}

stress_bn_function() {
test="bntest"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/bntest & > /dev/null
}

stress_rsa_function() {
test="rsa"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/rsa_test & > /dev/null
test="rsa_mp"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/rsa_mp_test & > /dev/null
}

stress_des_function() {
test="modes"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/modes_internal_test  & > /dev/null
test="des"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/destest  & > /dev/null
}

stress_cipher_function() {
test="cipher_name"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/ciphername_test & > /dev/null
test="cipher_list"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/cipherlist_test & > /dev/null
test="cipher_byte"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/cipherbytes_test & > /dev/null
}

stress_err_function () {
test="err"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/errtest & > /dev/null
test="fatal_err"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/fatalerrtest $dir_path/apps/server.pem $dir_path/apps/server.pem & > /dev/null
}

stress_x509_function() {
test="x509aux"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/x509aux  $dir_path/test/certs/roots.pem $dir_path/test/certs/root+anyEKU.pem $dir_pl
test="x509_time"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/x509_time_test & > /dev/null
test="x509_internal"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/x509_internal_test & > /dev/null
test="x509_dup_cert"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/x509_dup_cert_test $dir_path/test/certs/leaf.pem  & > /dev/null
test="x509_check_cert"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/x509_check_cert_pkey_test $dir_path/test/certs/servercert.pem  $dir_path/test/certsl
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/x509_check_cert_pkey_test $dir_path/test/certs/servercert.pem  $dir_path/test/certsl
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/x509_check_cert_pkey_test $dir_path/test/certs/server-dsa-cert.pem $dir_path/test/cl
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/x509_check_cert_pkey_test $dir_path/test/certs/server-ecdsa-cert.pem $dir_path/testl
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/x509_check_cert_pkey_test $dir_path/test/certs/x509-check.csr $dir_path/test/certs/l
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/x509_check_cert_pkey_test $dir_path/test/certs/x509-check.csr $dir_path/test/certs/l
}

stress_dsa_function() {
test="ecdsa"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/ecdsatest & > /dev/null
test="dsa"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/dsatest & > /dev/null
test="dsa_dig"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/dsa_no_digest_size_test & > /dev/null
}

stress_tls_function() {
test="dtls_listen"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/dtlsv1listentest & > /dev/null
test="dtls"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/dtlstest $dir_path/apps/server.pem $dir_path/apps/server.pem & > /dev/null
test="dtls_mtu"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/dtls_mtu_test & > /dev/null
test="bad_dtls"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/bad_dtls_test & > /dev/null
test="tls13secret"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/tls13secretstest & > /dev/null
test="tls13enc"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/tls13encryptiontest & > /dev/null
test="tls13ccs"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/tls13ccstest $dir_path/apps/server.pem $dir_path/apps/server.pem & > /dev/null
}

stress_dh_function() {
test="dh"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/dhtest & > /dev/null
}

stress_evp_function() {
test="evp_extra"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/evp_extra_test & > /dev/null
test="evp"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evpciph.txt & > /dev/null
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evpdigest.txt & > /dev/null
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evpencod.txt & > /dev/null
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evpkdf.txt & > /dev/null
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evpmac.txt & > /dev/null
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evppbe.txt & > /dev/null
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evppkey.txt & > /dev/null
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evppkey_ecc.txt & > /dev/null
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evpcase.txt & > /dev/null
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/evp_test  $dir_path/test/recipes/30-test_evp_data/evpccmcavs.txt & > /dev/null
}


stress_asn1_function() {
test="asn1_time"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/asn1_time_test & > /dev/null
test="asnl_str"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/asn1_string_table_test & > /dev/null
test="asn1_internal"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/asn1_internal_test & > /dev/null
test="asnl_enc"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/asn1_encode_test & > /dev/null
test="asn1_dec"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/asn1_decode_test & > /dev/null
}

stress_hmac_function() {
test="hmac"
 $perf_stat -o $LOG_PATH/perf_stat_$test.log  -r 10  $dir_path/test/hmactest & > /dev/null
}

log "Start of perf report.Perf Report will be available in $LOG_PATH/perf_stat.log"
stress_bio_function
wait
stress_ui_function
wait
stress_ec_function
wait
stress_engine_function
wait
stress_bn_function
wait
stress_rsa_function
wait
stress_des_function
wait
stress_cipher_function
wait
stress_err_function
wait
stress_x509_function
wait
stress_dsa_function
wait
stress_tls_function
wait
stress_dh_function
wait
stress_evp_function
wait
stress_asn1_function
wait
stress_hmac_function
wait

log "End of perf report"
log "End of Openssl Stress Test Suite"

/bin/sh /lib/rdk/rdk_oss_uploadSTBLogs.sh $tftp_server $upload_protocol $upload_httplink $LOG_PATH
