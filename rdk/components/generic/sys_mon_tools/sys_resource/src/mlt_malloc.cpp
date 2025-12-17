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
#if USE_SYSRES_MLT

#ifdef PLATFORM_LINUX
#elif  PLATFORM_CANMORE
#include <osal.h>
#include <osal_thread.h>
#else
#error PLATFORM MUST BE DEFINED!
#endif

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/stat.h>

#include "procInfo.h"
#include "mlt_malloc.h"
#include "radixSort.h"
#include "sysResource.h"
#include "debugRecord.h"

#include "haHeader.h"
#include "mltAnalyzer.h"
#include "dbgMLT.h"
#include "logFileDescr.h"

#if defined(USE_CMAS) || defined(USE_CMAS_IT)
#include "avlTree.h"
#include "cmastats.h"
#include "cmasAnalyzer.h"
#endif

#if USE_LNK_MALLOC
#include "lnk_malloc.h"
#include "countedFlag.h"
#endif

#if defined(USE_CMAT_SSTATS) || defined(USE_CMAS_IT)
#include "eltAnalyzer.h"
#endif

#ifdef USE_CMAS		// Caller memory allocation frequency statistics
CmasAnalyzer	cmasAnalyzer(192*1024);

#ifdef USE_CMAS_IT	// Caller memory allocation instrumentation timing statistics
EltAnalyzer<float, int>	cmasitAnalyzer(1000, 100, 8*1024);
EltAnalyzer<float, int>	cmdsitAnalyzer(1000, 100, 8*1024);
#endif //USE_CMAS_IT

#endif //USE_CMAS

#ifdef USE_CMAT_SSTATS	// Caller memory allocation timing statistics
EltAnalyzer<float, int>	cmatAnalyzer(1000, 100, 8*1024);
EltAnalyzer<float, int>	cmdtAnalyzer(1000, 100, 8*1024);
#endif //USE_CMAT_SSTATS

static unsigned long	allocsSize=0;		// Current number of active allocations
static unsigned long	allocsMaxSize=0;	// Maximum number of active allocations
static unsigned long	totalMallocCalls=0;	// Total number of malloc calls
static unsigned long	totalFreeCalls=0;	// Total number of free calls
static unsigned long	totalReallocCalls=0;	// Total number of realloc calls
static unsigned long	totalCallocCalls=0;	// Total number of calloc calls

static	MltAnalyzer	mltAnalyzer(192*1024);

#if USE_LNK_MALLOC
#define	LNK_MALLOC(x)	x
#else
#define	LNK_MALLOC(x)
#endif

static pthread_once_t   mltMutex_once = PTHREAD_ONCE_INIT;
static pthread_mutex_t 	mltMutex;

static void mltMutex_init (void)
{
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mltMutex, &attr);
	pthread_mutexattr_destroy(&attr);
}

static int lock (void)
{
	pthread_once(&mltMutex_once, mltMutex_init);
	return pthread_mutex_lock(&mltMutex);
}

static int unlock (void)
{
	return pthread_mutex_unlock(&mltMutex);
}

void mlt_analyze(unsigned long iterationN)
{
	lock();
	LNK_MALLOC(disable_mlt_malloc=true);

	static	bool initLogs=false;
	if (initLogs == false)
	{
		char command[256];
		char filenameMaps[LOG_FILENAME_LENGTH] = {0};
	  	sprintf (command, "cat /proc/%u/maps > %s", getpid(), proc_filename(LOG_FILE_DEFAULT_PATH, "Maps", ".txt", filenameMaps));
		if (fileExists(filenameMaps) == false) system(command);

		mltAnalyzer.SetFilename("MLT", "");

		CMAT_SSTATS(cmatAnalyzer.SetFilename("CMAT", ".txt"));
		CMAT_SSTATS(cmdtAnalyzer.SetFilename("CMDT", ".txt"));
#if defined(USE_CMAS)
		cmasAnalyzer.SetFilename("CMAS", "");
		USE_CMASIT(cmasitAnalyzer.SetFilename("CMASIT", ".txt"));
		USE_CMASIT(cmdsitAnalyzer.SetFilename("CMDSIT", ".txt"));
#endif
		initLogs=true;
	}

	mltAnalyzer.Analyze();

#ifdef  USE_CMAS
	cmasAnalyzer.Analyze(allocsSize, allocsMaxSize, totalMallocCalls, totalFreeCalls, totalReallocCalls, totalCallocCalls);
	USE_CMASIT(cmasitAnalyzer.Analyze());
	USE_CMASIT(cmdsitAnalyzer.Analyze());
#endif	//USE_CMAS
	CMAT_SSTATS(cmatAnalyzer.Analyze());
	CMAT_SSTATS(cmdtAnalyzer.Analyze());

	LNK_MALLOC(disable_mlt_malloc=false);
	unlock();
}

void *mlt_malloc(unsigned int size, void *caller, const char *file, int line)
{
	lock();
#if USE_LNK_MALLOC
	if (std_malloc == NULL) std_malloc_ctor();
#endif
	DEBUG_MLT(WDR("mlt_malloc: thread = %p lockCount = %d caller = %8.8p size = %8.8d file = %s:%d strlen(file) = %d\n", pthread_self(), mltMutex.__data.__count, caller, size, file, line, file != NULL ? strlen(file)+1 : 0));
	++totalMallocCalls;
	++allocsSize;
	if (allocsMaxSize < allocsSize) allocsMaxSize = allocsSize;

	LNK_MALLOC(disable_mlt_malloc=true);
	void *p=mltAnalyzer.Insert(caller, size, (char *)file, line);
	LNK_MALLOC(disable_mlt_malloc=false);

#ifdef USE_CMAS
	USE_CMASIT(cmasitAnalyzer.Start());
	cmasAnalyzer.Insert((unsigned int)caller, size, (char*)file, line);
	USE_CMASIT(cmasitAnalyzer.Accumulate());
#endif
	DEBUG_MLT(WDR("mlt_malloc: thread = %p lockCount = %d caller = %8.8p size = %8.8d file = %s:%d strlen(file) = %d p = %p\n", pthread_self(), mltMutex.__data.__count, caller, size, file, line, file != NULL ? strlen(file)+1 : 0, p));
	unlock();

	return p;
}

void mlt_free(void *p, void *caller, const char *file, int line)
{
	lock();
#if USE_LNK_MALLOC 
	if (std_free == NULL) std_malloc_ctor();
#endif
	DEBUG_MLT(WDR("mlt_free:   thread = %p lockCount = %d caller = %8.8p file = %s:%d p = %p\n", pthread_self(), mltMutex.__data.__count, caller, file, line, p));
	//if (p) free (mlt_remove(p, caller, file, line));
	if (p) 
	{
#ifdef USE_CMAS
		HAHeader *haHeader=mltAnalyzer.GetHAHeader(p);
		if (haHeader)
		{
			//printf("mlt_free:   alloc  = %p dealloc = %p size = %d dealloc @ %s:%d\n", haHeader->caller, caller, haHeader->size, (char*)file, line);
			USE_CMASIT(cmdsitAnalyzer.Start());
			cmasAnalyzer.Insert((unsigned int)haHeader->caller, (unsigned int)caller, haHeader->size, (char*)file, line);
			USE_CMASIT(cmdsitAnalyzer.Accumulate());
		}
#endif //USE_CMAS
		LNK_MALLOC(disable_mlt_malloc=true);
		mltAnalyzer.Remove(p);
		LNK_MALLOC(disable_mlt_malloc=false);

		--allocsSize;
		++totalFreeCalls;
	}
	DEBUG_MLT(WDR("mlt_free:   thread = %p lockCount = %d caller = %8.8p file = %s:%d p = %p ...done\n", pthread_self(), mltMutex.__data.__count, caller, file, line, p));
	unlock();
}

void *mlt_realloc(void *p, unsigned int size, void *caller, const char *file, int line)
{
	lock();
	DEBUG_MLT(WDR("mlt_realloc:thread = %p lockCount = %d caller = %8.8p size = %8.8d file = %s:%d p = %p\n", pthread_self(), mltMutex.__data.__count, caller, size, file, line, p));
	++totalReallocCalls;
        // ANSI: realloc(NULL, size) is equivalent to malloc(size)
	if (!p)
	{
		--totalMallocCalls;
		unlock();
		DEBUG_MLT(WDR("mlt_realloc:thread = %p lockCount = %d -> mlt_malloc\n", pthread_self(), mltMutex.__data.__count));
		return mlt_malloc(size, caller, file, line);
	}

	// ANSI: realloc(p, 0) is equivalent to free(p) except that NULL is returned
	if (!size)
	{
		mlt_free(p, caller, file, line);
		--totalFreeCalls;
		DEBUG_MLT(WDR("mlt_realloc:thread = %p lockCount = %d caller = %8.8p size = %8.8d file = %s:%d p = %p ...done 1\n", 
			pthread_self(), mltMutex.__data.__count, caller, size, file, line, p));
		unlock();
		DEBUG_MLT(WDR("mlt_realloc:thread = %p lockCount = %d ...done 1\n", pthread_self(), mltMutex.__data.__count));
		return NULL;
	}

	//unsigned int oldSize= (*(unsigned int*) ((unsigned char*)p - sizeof(MLTHeader) - sizeof(size_t))) & ~0x1;
	//mlt_print_memory((unsigned char*)p - sizeof(MLTHeader), oldSize + sizeof(MLTHeader));
	void *m=mlt_malloc(size, caller, file, line);
	--totalMallocCalls;
	if (!m)
	{
#if defined (__GLIBC__)
		WDR("mlt_realloc: Memory Allocation Failure: thread = %p lockCount = %d caller = %8.8p size = %8.8d file = %s:%d p = %p\n", 
			(void*)pthread_self(), mltMutex.__data.__count, caller, size, file, line, p);
#else
		WDR("mlt_realloc: Memory Allocation Failure: thread = %p lockCount = UNKNOWN caller = %8.8p size = %8.8d file = %s:%d p = %p\n", 
			(void*)pthread_self(), caller, size, file, line, p);
#endif
		unlock();
		DEBUG_MLT(WDR("mlt_realloc:thread = %p lockCount = %d Memory Allocation Failure: ...done\n", pthread_self(), mltMutex.__data.__count));
		return m;
	}

	HAHeader *haHeader=mltAnalyzer.GetHAHeader(p);
	if (haHeader)
	{
		memcpy(m, p, size > haHeader->size ? haHeader->size : size);
	}

	mlt_free(p, caller, file, line);
	--totalFreeCalls;

	DEBUG_MLT(WDR("mlt_realloc:thread = %p lockCount = %d caller = %8.8p size = %8.8d file = %s:%d p = %p ...done 2\n", pthread_self(), mltMutex.__data.__count, caller, size, file, line, p));
	unlock();
	return m;
}

void *mlt_calloc(size_t num, size_t size, void *caller, const char *file, int line)
{
	lock();
	DEBUG_MLT(WDR("mlt_calloc: thread = %p lockCount = %d caller = %8.8p num = %d size = %8.8d file = %s:%d\n", pthread_self(), mltMutex.__data.__count, caller, num, size, file, line));
	++totalCallocCalls;
	void *p=mlt_malloc(num*size, caller, file, line);
	--totalMallocCalls;
	//mlt_print_memory((unsigned char*)p - sizeof(MLTHeader), num*size + sizeof(MLTHeader));
	if (p) memset(p, 0, num*size);
	//mlt_print_memory((unsigned char*)p - sizeof(MLTHeader), num*size + sizeof(MLTHeader));

	DEBUG_MLT(WDR("mlt_calloc: thread = %p lockCount = %d caller = %8.8p num = %d size = %8.8d file = %s:%d : p = %p\n", pthread_self(), mltMutex.__data.__count, caller, num, size, file, line, p));
	unlock();
	return p;
}

char *mlt_strdup(const char *str, void *caller, const char *file, int line)
{
	if (str == NULL) return NULL;

	lock();
	size_t size=strlen(str)+1;
	DEBUG_MLT(WDR("mlt_strdup: thread = %p lockCount = %d caller = %8.8p size = %8.8d file = %s:%d\n", pthread_self(), mltMutex.__data.__count, caller, size, file, line));
	void *p=mlt_malloc(size, caller, file, line);

	DEBUG_MLT(WDR("mlt_strdup: thread = %p lockCount = %d caller = %8.8p size = %8.8d file = %s:%d : return\n", pthread_self(), mltMutex.__data.__count, caller, size, file, line));
	//return p ? (char *)memcpy(p, str, size) : NULL;
	if (p) memcpy(p, str, size);
	unlock();

	return (char *)p;
}

#endif //USE_SYSRES_MLT
