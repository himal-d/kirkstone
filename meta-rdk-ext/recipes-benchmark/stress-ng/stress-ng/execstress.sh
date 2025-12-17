
if [ -z "$1" ]
  then
    echo "No argument supplied"
    IT=10
  else
    IT=$1
fi

echo 0 > /proc/sys/vm/panic_on_oom ; dmesg -D ; 
python3 /usr/bin/run_sng.py $IT
