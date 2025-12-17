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

#ifdef PLATFORM_LINUX
#elif  PLATFORM_CANMORE
#include <osal.h>
#include <osal_thread.h>
#else
#error PLATFORM MUST BE DEFINED!
#endif

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <malloc.h>
#include <sys/types.h>
#include <string.h>

#include "sysResource.h"
#include "procInfo.h"

#if USE_SYSRES_MLT && ANALYZE_IDLE_MLT
#include "mlt_malloc.h"
static int mlt_analyze_count=0;
#endif

static pthread_mutex_t 	srsMutex = PTHREAD_MUTEX_INITIALIZER;

#define lock()		pthread_mutex_lock(&srsMutex);
#define unlock()	pthread_mutex_unlock(&srsMutex);

#ifdef PLATFORM_LINUX
static pthread_t 	sysResourceHandle;
#else
static os_thread_t 	sysResourceHandle;
#endif
static bool 		terminateSysResourceMonitor;
static unsigned int     pollingPeriodSysResourceMonitor=SYSMON_POLLINT*60*1000*1000; //usecs
static int		uordblks=0, hblkhd=0;
static int		tduordblks=0, tdhblkhd=0;	// total sum of differences between params on iterations i and i - 1 since start up.
static char		filename[128]={0};
static FILE		*file=0;
static char		processName[16];
static char		buffer[1024];

static void *sysResourceThread(void *arg);
static int  createSysResourceInfo(pid_t processId, char *processName, struct structProcMemInfo *sProcMemInfo, char *sysResorceInfo, bool includeIterDelta);
static void closeSysResourceMonitor();

int createSysResourceMonitor()
{
	terminateSysResourceMonitor = false;
	// Create sysResourceThread: //handle  	    //func	       //arg //priority //flags //name
#ifdef PLATFORM_LINUX
	return pthread_create(&sysResourceHandle, NULL, sysResourceThread, NULL);
#else
	return os_thread_create(&sysResourceHandle, sysResourceThread, 0, 0, 0, "sysResourceThread");
#endif
}

int destroySysResourceMonitor()
{
	terminateSysResourceMonitor = true;
	closeSysResourceMonitor();
#ifdef PLATFORM_LINUX
	return pthread_join(sysResourceHandle, 0 );
#else
	return os_thread_terminate(&sysResourceHandle);
#endif
}

static void closeSysResourceMonitor()
{
	int	buffoff=0;
	time_t	timeNow;
	char	ctime_b[26]; 

	timeNow=time(NULL);
	ctime_r(&timeNow, ctime_b); ctime_b[24]='\0';
	lock();
	buffoff=sprintf(buffer, "%s [%d:%s]: end:\n", &ctime_b[4], getpid(), processName);
	if (file) fwrite ((char*)buffer, 1, buffoff, file);
	getSysResourceInfo(buffer, false);
	if (file) fwrite ((char*)buffer, 1, strlen(buffer), file);
	if (file) fclose(file);
	file = 0;
	unlock();
}

void setSysResourceMonitorPollingPeriod(unsigned int secs)
{
	time_t	timeNow;
	char	ctime_b[26];
	pid_t	processId=0;
	timeNow=time(NULL);
	ctime_r(&timeNow, ctime_b); ctime_b[24]='\0';
	processId = getpid();
	procName(processId, processName);

	lock();
	pollingPeriodSysResourceMonitor = secs * 1000000;
	sprintf(buffer, "%s [%d:%s]: new polling period = %d secs\n", &ctime_b[4], processId, processName, pollingPeriodSysResourceMonitor/1000000);
	if (file) fwrite ((char*)buffer, 1, strlen(buffer), file);
	if (file) fflush(file);
	unlock();
}

void printSysResourceInfo()
{
	char	sysResourceInfoString[1024];
	getSysResourceInfo(sysResourceInfoString, false);
	printf ("%s\n", sysResourceInfoString);
}

int getSysResourceInfo(char *sysResourceInfoString, bool includeIterDelta)
{
	struct	structProcMemInfo sProcMemInfo;
	char	processName[16];
	pid_t	processId=0;

	processId = getpid();
	procName(processId, processName);
	procMemInfo(&sProcMemInfo);

	return createSysResourceInfo(processId, processName, &sProcMemInfo, sysResourceInfoString, includeIterDelta);
}

void resetIterDelta()
{
	uordblks=hblkhd=tduordblks=tdhblkhd=0;
}

static int createSysResourceInfo(pid_t processId, char *processName, struct structProcMemInfo *sProcMemInfo, char *sysResorceInfo, bool includeIterDelta)
{
	time_t	timeNow;
	char	ctime_b[26];
	int	buffoff=0;

#if defined (__GLIBC__)
	struct	mallinfo sMallInfo;

	sMallInfo = mallinfo();
#else
	/* Temp solution for non-glibc builds */
	struct mallinfo {
		int arena;      /* Non-mmapped space allocated (bytes) */
		int ordblks;    /* Number of free chunks */
		int smblks;     /* Number of free fastbin blocks */
		int hblks;      /* Number of mmapped regions */
		int hblkhd;     /* Space allocated in mmapped regions (bytes) */
		int usmblks;    /* Maximum total allocated space (bytes) */
		int fsmblks;    /* Space in freed fastbin blocks (bytes) */
		int uordblks;   /* Total allocated space (bytes) */
		int fordblks;   /* Total free space (bytes) */
		int keepcost;   /* Top-most, releasable space (bytes) */
	}
	sMallInfo = { 0 };
#endif

	timeNow=time(NULL); 
	ctime_r(&timeNow, ctime_b); ctime_b[24]='\0';
	buffoff=sprintf(sysResorceInfo, "%s [%d:%10.10s]: total = %08luKB[%2.2luMB] arena = %08d[%5.5dKB][%2.2dMB] ford = %08d[%5.5dKB][%2.2dMB] uord = %08d[%5.5dKB][%2.2dMB] hblkh   = %08d[%5.5dKB][%2.2dMB]\n",
		&ctime_b[4], processId,  processName,
		sProcMemInfo->totalram,	sProcMemInfo->totalram/1024,
		sMallInfo.arena,	sMallInfo.arena/1024,	sMallInfo.arena/(1024*1024),
		sMallInfo.fordblks,	sMallInfo.fordblks/1024,sMallInfo.fordblks/(1024*1024),
		sMallInfo.uordblks,	sMallInfo.uordblks/1024,sMallInfo.uordblks/(1024*1024),
		sMallInfo.hblkhd,	sMallInfo.hblkhd/1024,	sMallInfo.hblkhd/(1024*1024)
		);

	if (includeIterDelta)
	{
		int	duordblks=0, dhblkhd=0; 	// difference between params on iterations i and i - 1.

		if (uordblks != 0)
			duordblks = sMallInfo.uordblks - uordblks;
		tduordblks += duordblks;
		if (hblkhd != 0)
			dhblkhd = sMallInfo.hblkhd - hblkhd;
		tdhblkhd += dhblkhd;

		char *puord=strstr(sysResorceInfo, "uord");
		int  off=(int)(puord-sysResorceInfo-1);
		buffoff+=sprintf(sysResorceInfo+buffoff, "%*c", off, ' ');
		buffoff+=sprintf(sysResorceInfo+buffoff, "duord = %08d[%5.5dKB][%2.2dMB] dhblkh  = %08d[%5.5dKB][%2.2dMB]\n", 
				 duordblks, duordblks/1024, duordblks/(1024*1024), dhblkhd, dhblkhd/1024, dhblkhd/(1024*1024));
		buffoff+=sprintf(sysResorceInfo+buffoff, "%*c", off-1, ' ');
		buffoff+=sprintf(sysResorceInfo+buffoff, "tduord = %08d[%5.5dKB][%2.2dMB] tdhblkh = %08d[%5.5dKB][%2.2dMB]\n",
				 tduordblks, tduordblks/1024, tduordblks/(1024*1024), tdhblkhd, tdhblkhd/1024, tdhblkhd/(1024*1024));
		uordblks=sMallInfo.uordblks; hblkhd=sMallInfo.hblkhd;
	}

	return buffoff;
}

static void *sysResourceThread(void *arg)
{
	time_t	timeNow;
	struct	structProcMemInfo sProcMemInfo;
	char	ctime_b[26];
	pid_t	processId=0;
	int 	buffoff=0;

	timeNow=time(NULL);
	ctime_r(&timeNow, ctime_b); ctime_b[24]='\0';
	processId = getpid();
	procName(processId, processName);

	char *sSysResMonEnable= (char*)getenv("SYSRESRT_ENABLE");
	if (sSysResMonEnable && strlen(sSysResMonEnable) != 0 && strcmp(sSysResMonEnable, "false") == 0)
	{
		printf("%s [%d:%s]: Sys Resource Monitor is disabled\n", &ctime_b[4], processId, processName);
		return NULL;
	}

#ifdef RDK_BROADBAND
	procFilename("/rdklogs/logs/", "MON", ".txt", filename);
#else
	procFilename("/opt/logs/", "MON", ".txt", filename);
#endif
	lock();
	file = fopen (filename, "a");
	buffoff=sprintf(buffer, "%s [%d:%s]: start: default polling period = %d secs\n", &ctime_b[4], processId, processName, pollingPeriodSysResourceMonitor/1000000);
	if (file) fwrite ((char*)buffer, 1, buffoff, file);
	if (file) fflush(file);
	unlock();

	procMemInfo(&sProcMemInfo);
	while(terminateSysResourceMonitor == false)
	{
#if USE_SYSRES_MLT && ANALYZE_IDLE_MLT
		lock();
		buffoff=sprintf(buffer, "sysResMon: mlt_analyze = %d\n", mlt_analyze_count++);
		if (file) fwrite ((char*)buffer, 1, buffoff, file);
		if (file) fflush(file);
		unlock();
		mlt_analyze(0);
#endif
		lock();
		getSysResourceInfo(buffer, false);
		if (file) fwrite ((char*)buffer, 1, strlen(buffer), file);
		if (file) fflush(file);
		unlock();

		usleep( pollingPeriodSysResourceMonitor );
	}
	return NULL;
}

