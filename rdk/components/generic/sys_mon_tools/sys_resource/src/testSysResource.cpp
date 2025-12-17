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
#include <stdio.h>
//#include <osal.h>
//#include <osal_thread.h>

#include "sysResource.h"
#include "procInfo.h"
#include "mlt_malloc.h"
#include "rpl_new.h"
#include "debugRecord.h"

int testnew();
#ifdef USE_AVLINT
extern int testavlint();
extern int testavlint2();
#endif
#ifdef USE_AVLBT
int testavlbt();
#endif
#ifdef USE_CMAS
int testavlcmas();
#endif

#ifdef __cplusplus 
extern "C" {
#endif
int testmalloc();
int testmalloc2();
int testcalloc();
int testcalloc2();
int testmemalign();
#ifdef __cplusplus
}
#endif

#define PROC_INFO_TEST_ENABLE		0
#define MLT_MALLOC_TEST_ENABLE		1

#ifdef TEST_DEADCODESTRIP
int deadCodeFunctionExe()
{
	printf ("deadCodeFunctionExe:\n");
	return 0;
}
#endif

int main(int argc, char* argv[])
{
	printf("main:\n");

#ifdef TEST_DEADCODESTRIP
extern int deadCodeRefedInitDataFileData;
extern int deadCodeRefedNonInitDataFileData;
	printf ("main: deadCodeRefedNonInitDataFileData = %d deadCodeRefedInitDataFileData = %d\n", deadCodeRefedNonInitDataFileData, deadCodeRefedInitDataFileData);
#endif

	createSysResourceMonitor();
	//os_sleep(2000);

#if TEST_FMP
extern void testfixedSizePartition();
	testfixedSizePartition();
#endif

#if TEST_LL
void testSLL(void);
void testHLL(void);
	testSLL();
	testHLL();
#endif

#if	PROC_INFO_TEST_ENABLE
	struct structProcMemInfo pminfo;
	struct structProcStat  pstat;
	struct structProcStatm pstatm;
	int pidReceiver=-1, pidMpeos=-1;

	if ((procMemInfo(&pminfo)) == 0)
	{
		printf( "procMInf: MemTotal: %8lu kB\n",  pminfo.totalram);
	}

	if ((procStat("Receiver", &pstat)) == 0)
	{
		//        0   1   2  3  4  5  6  7  8   9  10  11  12  13  14  15  16  17  18 19 20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36 37 38 39 40   41  42  43
		printf( "procStat: %d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %d %d %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %u %u %llu %lu %ld\n",
		pstat.pid, pstat.comm, pstat.state, pstat.ppid, pstat.pgrp, pstat.session, pstat.tty_nr, pstat.tpgid, pstat.flags,
		pstat.minflt, pstat.cminflt, pstat.majflt, pstat.cmajflt, pstat.utime, pstat.stime, pstat.cutime, pstat.cstime, pstat.priority, 
		pstat.nice, pstat.num_threads, pstat.itrealvalue, pstat.starttime, pstat.vsize, pstat.rss, pstat.rsslim, pstat.startcode, pstat.endcode,
		pstat.startstack, pstat.kstkesp, pstat.kstkeip, pstat.signal, pstat.blocked, pstat.sigignore, pstat.sigcatch, pstat.wchan, pstat.nswap, 
		pstat.cnswap, pstat.exit_signal, pstat.processor, pstat.rt_priority, pstat.policy, pstat.delayacct_blkio_ticks, pstat.guest_time, pstat.cguest_time);
		pidReceiver = pstat.pid;
	}

	if ((procStat("mpeos-main", &pstat)) == 0)
	{
		//        0   1   2  3  4  5  6  7  8   9  10  11  12  13  14  15  16  17  18 19 20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36 37 38 39 40   41  42  43
		printf( "procStat: %d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %d %d %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %u %u %llu %lu %ld\n",
		pstat.pid, pstat.comm, pstat.state, pstat.ppid, pstat.pgrp, pstat.session, pstat.tty_nr, pstat.tpgid, pstat.flags,
		pstat.minflt, pstat.cminflt, pstat.majflt, pstat.cmajflt, pstat.utime, pstat.stime, pstat.cutime, pstat.cstime, pstat.priority, 
		pstat.nice, pstat.num_threads, pstat.itrealvalue, pstat.starttime, pstat.vsize, pstat.rss, pstat.rsslim, pstat.startcode, pstat.endcode,
		pstat.startstack, pstat.kstkesp, pstat.kstkeip, pstat.signal, pstat.blocked, pstat.sigignore, pstat.sigcatch, pstat.wchan, pstat.nswap, 
		pstat.cnswap, pstat.exit_signal, pstat.processor, pstat.rt_priority, pstat.policy, pstat.delayacct_blkio_ticks, pstat.guest_time, pstat.cguest_time);
		pidMpeos = pstat.pid;
	}

	if ((procStatm("Receiver", pidReceiver, &pstatm)) == 0)
	{
		printf( "procStam: %d size = %d resident = %d share = %d text = %d lib = %d data = %d dt = %d\n",  pidReceiver, pstatm.size, pstatm.resident, pstatm.share, pstatm.text, pstatm.lib, pstatm.data, pstatm.dt);
	}

	if ((procStatm("mpeos-main", pidMpeos, &pstatm)) == 0)
	{
		printf( "procStam: %d size = %d resident = %d share = %d text = %d lib = %d data = %d dt = %d\n",  pidMpeos, pstatm.size, pstatm.resident, pstatm.share, pstatm.text, pstatm.lib, pstatm.data, pstatm.dt);
	}
#endif	//PROC_INFO_TEST_ENABLE

#if MLT_MALLOC_TEST_ENABLE && USE_SYSRES_MLT
	WDR("main: testmemalign:\n");
	testmemalign();
#ifdef USE_AVLINT
	WDR("main: testavlint:\n");
	testavlint();
	WDR("main: testavlint2:\n");
	testavlint2();
#endif
#ifdef USE_AVLBT
	WDR("main: testavlbt:\n");
	testavlbt();
#endif
#ifdef USE_CMAS
	WDR("main: testavlcmas:\n");
	testavlcmas();
#endif
	WDR("main: testnew:\n");
	testnew();
	WDR("main: testmalloc:\n");
	testmalloc();
	WDR("main: testmalloc2:\n");
	testmalloc2();
	WDR("main: testcalloc:\n");
	testcalloc();
	WDR("main: testcalloc2:\n");
	testcalloc2();
	printSysResourceInfo();
#endif	//MLT_MALLOC_TEST_ENABLE

	destroySysResourceMonitor();

	return 0;
}

