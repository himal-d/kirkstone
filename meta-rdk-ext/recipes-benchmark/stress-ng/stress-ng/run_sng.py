#!/usr/bin/python3
#
# Run with something like: 
# echo 0 > /proc/sys/vm/panic_on_oom ; dmesg -D ; python3 ./run_sng.py
#
#
#

import sys
import time
import subprocess
import re
import getopt

def report(msg):
   t_mono = time.clock_gettime(time.CLOCK_MONOTONIC_RAW)
   print ("Time " + str(t_mono) + " " + str(msg))


def collect_stressors():
   return subprocess.check_output(["/usr/bin/stress-ng", "--stressors"]).decode('utf-8').strip()

def collect_schedulers():
   try: 
      scheds = subprocess.check_output(["/usr/bin/stress-ng",  "--sched", "which"], stderr=subprocess.STDOUT).decode('utf-8').strip()
   except subprocess.CalledProcessError as e:
      scheds = e.output.decode('utf-8').strip()

   return scheds


def getBogoOps(stressor, output):
   matcher = re.compile('stress-ng\: info:\s+\[\d+\]\D+(?P<bogoops>\d+)\s+(?P<realtime>\d+.\d+)\s+(?P<utime>\d+.\d+)\s+(?P<stime>\d+.\d+)\s+(?P<bogoopsrt>\d+.\d+)\s+(?P<bogoopsst>\d+.\d+).*')
   for rl in output.splitlines():
      result = matcher.match(rl)
      if result != None and result.group('bogoops') != None and result.group('bogoopsrt') != None :
         #print(str(result.group('bogoops')))
         #print(str(result.group('realtime')))
         #print(str(result.group('utime')))
         #print(str(result.group('stime')))
         #print(str(result.group('bogoopsrt')))
         #print(str(result.group('bogoopsst')))
         return str(result.group('bogoopsrt'))
   return None


#
# A single run here is about 35 minutes with 10 seconds per test.
#


# Note - execution time is fixed, so that doesn't get you anything useful
# The result field is filled with the bogoop/s 
def execute_stressor(name, ident, cpucount, runtime):
   
   exline = "--"+name
   
   # argarray=["/usr/bin/stress-ng",exline, str(cpucount),"-t", str(runtime), "--pathological", "--timestamp", "--tz", "--no-rand-seed", "--times", "--metrics", "-v"]
   
   argarray=["/usr/bin/stress-ng",exline, str(cpucount),"-t", str(runtime), "--pathological", "--tz", "--no-rand-seed", "--times", "--metrics", "-v"]
   t_start = time.clock_gettime(time.CLOCK_MONOTONIC_RAW)
   passing  = True
   try: 
      output = subprocess.check_output(argarray, stderr=subprocess.STDOUT).decode('utf-8').strip()
   except subprocess.CalledProcessError as e:
      passing  = False
      output = e.output.decode()

   t_stop = time.clock_gettime(time.CLOCK_MONOTONIC_RAW)
   
   print(output)
   
   exetime = (t_stop - t_start) * 1000
   
   rv = getBogoOps(name, output)
      
   if rv == None:
      passing  = False
      

   result = "<LAVA_SIGNAL_TESTCASE TEST_CASE_ID=" + ident
   if passing:
      result = result + " RESULT=pass MEASUREMENT="+str(rv)+" UNITS=bgops>"
   else:
      result = result + " RESULT=fail MEASUREMENT="+str(rv)+" UNITS=bgops>"
      
   report(result)

list_skip = ["resources", "sysfs", "zombie", "aiol", "apparmor", 
   "atomic", "binderfs", "cap", "crypt", "dccp","fiemap", "heapsort", 
   "ioport", "io-uring", "judy", "key", "memhotplug", "mergesort", 
   "pkey", "quota", "radixsort", "rawdev", "sctp", "spawn", "swap", 
   "tree", "userfaultfd", "wcs", "x86syscall", "xattr", "zlib", 
   "sysinval", "hrtimers", "aio", "bad-altstack"]

list_single = ["fork", "clone", "vfork"]
      
def do_single_run(which):
   stresslist =  collect_stressors()
   report (stresslist)
   
   schedlist = collect_schedulers()
   report (schedlist)
   
   parts = str.split(str(stresslist), ' ')
   
   for stressor in parts:
      if stressor in list_skip:
         report("Skip the test " + stressor)
      else:
         stressor_id = str(which) + "_ITERATION_"+ stressor
         report("<LAVA_SIGNAL_STARTTC "+str(stressor_id)+">")
         if stressor in list_single:
            execute_stressor(stressor, stressor_id, 1, 5)
         else:
            execute_stressor(stressor, stressor_id, 4, 5)
         report("<LAVA_SIGNAL_ENDTC "+str(stressor_id)+">")

def main(arg):
   iterations = 10
   
   if arg != None:
      iterations = int(arg)

   print("Running iterations " + str(iterations))

   report ("<LAVA_SIGNAL_TESTSET START LTP>")

   count = list(range(1,1+iterations,1))
   for n in count:
      do_single_run(n)
      
   report ("<LAVA_SIGNAL_TESTSET STOP LTP>")


if __name__ == "__main__":
   if len(sys.argv) < 2:
      main(None)
   else:
      main(sys.argv[1])



