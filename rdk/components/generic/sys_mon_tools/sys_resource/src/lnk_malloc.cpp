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
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <dlfcn.h> 
#include <unistd.h>

#if USE_SYSRES_MLT && USE_LNK_MALLOC

#include "mlt_malloc.h"
#include "lnk_malloc.h"
#include "debugRecord.h"
#include "logFileDescr.h"
#include "procInfo.h"
#include "countedFlag.h"

#define	DEBUG_LNKM_ENABLE	0

#if DEBUG_LNKM_ENABLE
#define	DEBUG_LNKM(x)	x
#else
#define	DEBUG_LNKM(x)
#endif

CountedFlag disable_mlt_malloc = false;

extern pthread_mutex_t 	mltMutex;
#define lock()		pthread_mutex_lock(&mltMutex);
#define unlock()	pthread_mutex_unlock(&mltMutex);

malloc_call		std_malloc;
calloc_call		std_calloc;
realloc_call		std_realloc;
free_call		std_free;
memalign_call		std_memalign;
valloc_call		std_valloc;
posix_memalign_call	std_posix_memalign;

static unsigned int	std_memalign_end=0;
static const unsigned int std_memalign_size=592;

void __std_malloc_attr std_malloc_ctor() 
{
	DEBUG_LNKM(WDR("std_malloc_ctor: std_malloc = %p std_calloc = %p std_realloc = %p std_free = %p std_memalign = %p std_valloc = %p std_posix_memalign = %p\n", 
		std_malloc, std_calloc, std_realloc, std_free, std_memalign, std_valloc, std_posix_memalign));
	if (std_malloc != NULL)
	{
		printf("std_malloc_ctor: Already initialized! Return.\n");
		return;
	}

	std_malloc         = (malloc_call) dlsym(RTLD_NEXT, "malloc");
	std_calloc         = (calloc_call)dlsym(RTLD_NEXT, "calloc");
	std_realloc        = (realloc_call)dlsym(RTLD_NEXT, "realloc");
	std_free           = (free_call)dlsym(RTLD_NEXT, "free");
	std_memalign       = (memalign_call)dlsym(RTLD_NEXT, "memalign");
	std_valloc         = (valloc_call)dlsym(RTLD_NEXT, "valloc");
	std_posix_memalign = (posix_memalign_call)dlsym(RTLD_NEXT, "posix_memalign");
	
	std_memalign_end   = (unsigned int)std_memalign + std_memalign_size;

	DEBUG_LNKM(WDR("std_malloc_ctor: std_malloc = %p std_calloc = %p std_realloc = %p std_free = %p std_memalign = %p std_valloc = %p std_posix_memalign = %p\n", 
		std_malloc, std_calloc, std_realloc, std_free, std_memalign, std_valloc, std_posix_memalign));
	DEBUG_LNKM(WDR("RTLD_DEFAULT   : std_malloc = %p std_calloc = %p std_realloc = %p std_free = %p std_memalign = %p std_valloc = %p std_posix_memalign = %p\n", 
		dlsym(RTLD_DEFAULT, "malloc"), dlsym(RTLD_DEFAULT, "calloc"), dlsym(RTLD_DEFAULT, "realloc"), dlsym(RTLD_DEFAULT, "free"), dlsym(RTLD_DEFAULT, "memalign"), dlsym(RTLD_DEFAULT, "valloc"), dlsym(RTLD_DEFAULT, "posix_memalign")));

	char command[256];
	char filenameMaps[LOG_FILENAME_LENGTH] = {0};
  	sprintf (command, "cat /proc/%u/maps > %s", getpid(), proc_filename(LOG_FILE_DEFAULT_PATH, "Maps", ".txt", filenameMaps));
	if (fileExists(filenameMaps) == false) system(command);

	if (!std_malloc || !std_calloc || !std_realloc || !std_free || !std_memalign || !std_valloc || !std_posix_memalign)
	{
		fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
		exit(1);
	}
}

void* malloc(size_t size) 
{
	void *p=0;
	lock();
	if (std_malloc == NULL)
		std_malloc_ctor();
	unsigned int caller = (unsigned int)__builtin_return_address(0);
	bool std_memalign_call = caller >= (unsigned int)std_memalign && caller <= (unsigned int)std_memalign_end;
	if (disable_mlt_malloc == false && std_memalign_call == false)
	{
		DEBUG_LNKM(WDR("lnk_malloc: -> mlt_malloc: thread = %p lockCount = %d caller = %8.8p size = %8.8d mac = %d dlmac = %d\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), size, std_memalign_call));
		disable_mlt_malloc=true;
		p=mlt_malloc(size, __builtin_return_address(0), NULL, 0);
		disable_mlt_malloc=false;
		DEBUG_LNKM(WDR("lnk_malloc: -> mlt_malloc: thread = %p lockCount = %d caller = %8.8p size = %8.8d mac = %d dlmac = %d : p = %p\n\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), size, std_memalign_call, p));
	}
	else
	{
		DEBUG_LNKM(WDR("lnk_malloc: thread = %p lockCount = %d caller = %8.8p size = %8.8d mac = %d\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), size, std_memalign_call));
		p=std_malloc(size);
		DEBUG_LNKM(WDR("lnk_malloc: thread = %p lockCount = %d caller = %8.8p size = %8.8d mac = %d : p = %p\n\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), size, std_memalign_call, p));
	}
	unlock();
	return p;
}

void free(void *p) 
{
	lock();
	if (std_malloc == NULL)
		std_malloc_ctor();
	unsigned int caller = (unsigned int)__builtin_return_address(0);
	bool std_memalign_call = caller >= (unsigned int)std_memalign && caller <= (unsigned int)std_memalign_end;
	if (disable_mlt_malloc == false && std_memalign_call == false)
	{
		DEBUG_LNKM(WDR("lnk_free: -> mlt_free: thread = %p lockCount = %d caller = %8.8p mac = %d p = %p\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), std_memalign_call, p));
		disable_mlt_malloc=true;
		mlt_free(p, __builtin_return_address(0), NULL, 0);
		disable_mlt_malloc=false;
		DEBUG_LNKM(WDR("lnk_free: -> mlt_free: thread = %p lockCount = %d caller = %8.8p mac = %d p = %p ...done\n\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), std_memalign_call, p));
	}
	else
	{
		DEBUG_LNKM(WDR("lnk_free: thread = %p lockCount = %d caller = %8.8p mac = %d p = %p\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), std_memalign_call, p));
		std_free(p);
		DEBUG_LNKM(WDR("lnk_free: thread = %p lockCount = %d caller = %8.8p mac = %d p = %p...done\n\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), std_memalign_call, p));
	}
	unlock();
} 

void* calloc(size_t num, size_t size) 
{
	void *p=0;
	lock();
	if (std_malloc == NULL)
		std_malloc_ctor();
	if (disable_mlt_malloc == false)
	{
		DEBUG_LNKM(WDR("lnk_calloc: -> mlt_calloc: thread = %p lockCount = %d caller = %8.8p num = %d size = %8.8d\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), num, size));
		disable_mlt_malloc=true;
		p=mlt_calloc(num, size, __builtin_return_address(0), NULL, 0);
		disable_mlt_malloc=false;
		DEBUG_LNKM(WDR("lnk_calloc: -> mlt_calloc: thread = %p lockCount = %d caller = %8.8p num = %d size = %8.8d ...done\n\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), num, size));
	}
	else
	{
		DEBUG_LNKM(WDR("lnk_calloc: thread = %p lockCount = %d caller = %8.8p num = %d size = %8.8d\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), num, size));
		p=std_calloc(num, size);
		DEBUG_LNKM(WDR("lnk_calloc: thread = %p lockCount = %d caller = %8.8p num = %d size = %8.8d : p = %p\n\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), num, size, p));
	}
	unlock();
	return p;
}

void* realloc(void *p, size_t size) 
{
	void *l=0;
	lock();
	if (std_malloc == NULL)
		std_malloc_ctor();
	if (disable_mlt_malloc == false)
	{
		DEBUG_LNKM(WDR("lnk_realloc: -> mlt_realloc: thread = %p lockCount = %d caller = %8.8p size = %8.8d p = %p\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), size, p));
		disable_mlt_malloc=true;
		l=mlt_realloc(p, size, __builtin_return_address(0), NULL, 0);
		disable_mlt_malloc=false;
		DEBUG_LNKM(WDR("lnk_realloc: -> mlt_realloc: thread = %p lockCount = %d caller = %8.8p size = %8.8d p = %p ...done\n\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), size, p));
	}
	else
	{
		DEBUG_LNKM(WDR("lnk_realloc: thread = %p lockCount = %d caller = %8.8p size = %8.8d p = %p\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), size, p));
		l=std_realloc(p, size);
		DEBUG_LNKM(WDR("lnk_realloc: thread = %p lockCount = %d caller = %8.8p size = %8.8d p = %p l = %p\n\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), size, p, l));
	}
	unlock();
	return l;
}

void* memalign(size_t alignment, size_t size) 
{
	void *p=0;
	lock();
	DEBUG_LNKM(WDR("lnk_malign: thread = %p lockCount = %d caller = %8.8p size = %8.8d alignment = %d\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), size, alignment));
	disable_mlt_malloc=true;
	p=std_memalign(alignment, size);
	disable_mlt_malloc=false;
	DEBUG_LNKM(WDR("lnk_malign: thread = %p lockCount = %d caller = %8.8p size = %8.8d alignment = %d p = %p\n\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), size, alignment, p));
	unlock();
	return p;
}

void* valloc(size_t size) 
{
	void *p=0;
	lock();
	DEBUG_LNKM(WDR("lnk_valloc: thread = %p lockCount = %d caller = %8.8p size = %8.8d\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), size));
	disable_mlt_malloc=true;
	p=std_valloc(size);
	disable_mlt_malloc=false;
	DEBUG_LNKM(WDR("lnk_valloc: thread = %p lockCount = %d caller = %8.8p size = %8.8d : p = %p\n\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), size, p));
	unlock();
	return p;
}

int posix_memalign(void **memptr, size_t alignment, size_t size) 
{
	int err=0;
	lock();
	DEBUG_LNKM(WDR("lnk_palign: thread = %p lockCount = %d caller = %8.8p size = %8.8d alignment = %d\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), size, alignment));
	disable_mlt_malloc=true;
	err=std_posix_memalign(memptr, alignment, size);
	disable_mlt_malloc=false;
	DEBUG_LNKM(WDR("lnk_palign: thread = %p lockCount = %d caller = %8.8p size = %8.8d alignment = %d p = %p err = %d\n\n", pthread_self(), mltMutex.__data.__count, __builtin_return_address(0), size, alignment, *memptr, err));
	unlock();
	return err;
}

#endif	//USE_SYSRES_MLT && USE_LNK_MALLOC

