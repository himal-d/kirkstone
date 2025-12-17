/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#ifndef PROCINFO_H
#define PROCINFO_H

#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

// /proc/[pid]/stat
//  0  1  2  3  4  5  6  7  8   9  10  11  12  13  14  15  16  17  18 19 20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36 37 38 39 40   41  42  43
//"%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %d 0 %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %u %u %llu %lu %ld"
typedef struct structProcStat
{
	int           pid;                      // 0.  The process id. 
	char          comm[_POSIX_PATH_MAX];    // 1.  The filename of the executable, in parentheses 
	char          state;                    // 2.  RSDZTW: R - running, S - sleeping, D - sleeping in an uninterruptible wait, Z - zombie, T - traced/stopped, W - paging 
	int           ppid;                     // 3.  The pid of the parent. 
	int           pgrp;                     // 4.  The process group ID of the process. 
	int           session;                  // 5.  The session id of the process. 
	int           tty_nr;                   // 6.  The controlling terminal of the process 
	int           tpgid;                    // 7.  The ID of the foreground process group of the controlling terminal of the process 
	unsigned int  flags;                    // 8.  The kernel flags word of the process. 
	unsigned long minflt;                   // 9.  The number of minor faults the process has made which have not required loading a memory page from disk 
	unsigned long cminflt;                  // 10. The number of major faults that the process's waited-for children have made. 
	unsigned long majflt;                   // 11. The number of major faults the process has made which have required loading a memory page from disk. 
	unsigned long cmajflt;                  // 12. The number of major faults that the process's waited-for children have made 
	unsigned long utime;                    // 13. Amount of time that this process has been scheduled in user mode 
	unsigned long stime;                    // 14. Amount of time that this process has been scheduled in kernel mode 
	long	      cutime;                   // 15. Amount of time that this process's waited-for children have been scheduled in user mode 
	long          cstime;                   // 16. Amount of time that this process's waited-for children have been scheduled in kernel mode 
	long          priority;                 // 17. 
	long          nice;                     // 18. The nice value (see setpriority(2)), a value in the range 19 (low priority) to -20 (high priority). 
	int           num_threads;              // 19. Number of threads in this process (since Linux 2.6). 
	int           itrealvalue;              // 20. The time in jiffies before the next SIGALRM is sent to the process due to an interval timer. 
	unsigned long long starttime; 		// 21. The time in jiffies the process started after system boot. 
	unsigned long vsize;                    // 22. Virtual memory size in bytes. 
	long          rss;                      // 23. Resident Set Size: number of pages the process has in real memory. 
	unsigned long rsslim;                   // 24. Current soft limit in bytes on the rss of the process; see the description of RLIMIT_RSS in getpriority(2). 
	unsigned long startcode;                // 25. The address above which program text can run. 
	unsigned long endcode;                  // 26. The address below which program text can run. 
	unsigned long startstack;               // 27. The address of the start (i.e., bottom) of the stack 
	unsigned long kstkesp;                  // 28. The current value of ESP (stack pointer), as found in the kernel stack page for the process 
	unsigned long kstkeip;                  // 29. The current EIP (instruction pointer). 
	unsigned long signal;                   // 30. The bitmap of pending signals, displayed as a decimal number.  Obsolete, because it does not provide information on real-time signals; use /proc/[pid]/status instead. 
	unsigned long blocked; 			// 31. The bitmap of blocked signals, displayed as a decimal number.  Obsolete, because it does not provide information on real-time signals; use /proc/[pid]/status instead. 
	unsigned long sigignore;                // 32. The bitmap of ignored signals, displayed as a decimal number.  Obsolete, because it does not provide information on real-time signals; use /proc/[pid]/status instead. 
	unsigned long sigcatch;                 // 33. The bitmap of caught signals,  displayed as a decimal number.  Obsolete, because it does not provide information on real-time signals; use /proc/[pid]/status instead. 
	unsigned long wchan;  			// 34. This is the "channel" in which the process is waiting. It is the address of a system call, and can be looked up in a namelist if you need a textual name. 
	unsigned long nswap;  			// 35. Number of pages swapped (not maintained). 
	unsigned long cnswap;  			// 36. Cumulative nswap for child processes (not maintained). 
	int           exit_signal;              // 37. Signal to be sent to parent when we die. 
	int           processor;                // 38. CPU number last executed on. 
	unsigned int  rt_priority;              // 39. Real-time scheduling priority, a number in the range 1 to 99 for processes scheduled under a real-time policy, or 0, for non-real-time processes (see sched_setscheduler(2)). 
	unsigned int  policy;                   // 40. Scheduling policy (see sched_setscheduler(2)). Decode using the SCHED_* constants in linux/sched.h. 
	unsigned long long delayacct_blkio_ticks;    // 41. Aggregated block I/O delays, measured in clock ticks (centiseconds). 
	unsigned long guest_time;    		// 42. Guest time of the process (time spent running a virtual CPU for a guest operating system). 
	long cguest_time;    			// 43. Guest time of the process's children, measured in clock ticks. 

} ProcStat;


// /proc/[pid]/statm
typedef struct structProcStatm
{
	int	size;				// 0. total program size (same as VmSize in /proc/[pid]/status)
	int	resident;			// 1. resident set size  (same as VmRSS in /proc/[pid]/status)
	int	share;				// 2. shared pages (from shared mappings)
	int	text;				// 3. text (code)
	int	lib;				// 4. library (unused in Linux 2.6)
	int	data;				// 5. data + stack
	int	dt;				// 6. dirty pages (unused in Linux 2.6)
} ProcStatm;

// /proc/meminfo
typedef struct structProcMemInfo
{
	unsigned long totalram;  		// Total usable main memory size
	//unsigned long freeram;   		// Available memory size
	//unsigned long bufferram; 		// Memory used by buffers
} ProcMemInfo;


#ifdef __cplusplus 
extern "C" {
#endif

void procFilename(const char *directory, const char *postfix, const char *ext, char *filename);
int procStat (char *procName, struct structProcStat  *pstat);
int procStatm(char *procName, int pid, struct structProcStatm *pstatm);
int procPid  (char *procName, int *pid);
int procName (int   pid, char *procName);
int procMemInfo(struct structProcMemInfo *pminfo);
int fileExists(char *name);
char *proc_filename(const char *directory, const char *postfix, const char *ext, char *filename);

#ifdef __cplusplus
}
#endif

#endif  //PROCINFO_H
