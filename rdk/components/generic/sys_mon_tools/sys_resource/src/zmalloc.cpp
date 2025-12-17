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
#include <assert.h>
#include <pthread.h>

#include "dbgMLT.h"
#include "debugRecord.h"

#if USE_LNK_MALLOC
#include "std_malloc.h"
#include "lnk_malloc.h"
#include "countedFlag.h"
#else
#include <malloc.h>
#endif

#define	PRINT_MEMG_ENABLE	0
#define	PRINT_MEME_ENABLE	0

#if PRINT_MEMG_ENABLE
#define	PRINT_MEM(x)	x
#else
#define	PRINT_MEM(x)
#endif
#if PRINT_MEME_ENABLE
#define	PRINT_MEME(x)	x
#else
#define	PRINT_MEME(x)
#endif

#if defined(USE_CMAT_SSTATS)
#include "eltAnalyzer.h"
#endif

#ifdef USE_CMAT_SSTATS
extern EltAnalyzer<float, int>	cmatAnalyzer;
extern EltAnalyzer<float, int>	cmdtAnalyzer;
#endif //USE_CMAT_SSTATS

#define		BYTES_PER_ROW		32	
#define		MLT_RECORD_LENGTH	1024

#if PRINT_MEMG_ENABLE || PRINT_MEME_ENABLE
static void mlt_print_memory_raw(void *p, size_t size)
{
	int i=0;
	int msize=size;
	unsigned int  *ip=(unsigned int *)p;
	unsigned char *cp=(unsigned char *)p;
	while (msize > 0)
	{
		WDR("%p: ", ip);
		for (i=0; i<BYTES_PER_ROW/4; i++) 
		{
			if (i<msize/4) WDR("%8.8x ", *ip++);
			else           WDR("         ");
		}
		for (i=0; i<BYTES_PER_ROW && i<msize; i++) 
		{
			if (isprint(*cp) !=0 ) WDR("%c", *cp++);
			else		       WDR(" ",  *cp++);
		}
		WDR("\n");
		msize -= BYTES_PER_ROW;
	}
}

static void mlt_print_memory(void *p, size_t size)
{
	PRINT_MEME(WDR("mlt_print_memory: p = %p size = %d\n",p, size));
	PRINT_MEME(mlt_print_memory_raw((unsigned char *)p - BYTES_PER_ROW, BYTES_PER_ROW));
	size = size > 1024 ? BYTES_PER_ROW : size;
	PRINT_MEME(mlt_print_memory_raw(p, size));
	//size = (size % BYTES_PER_ROW) ? ((size / BYTES_PER_ROW) + 1)*BYTES_PER_ROW : size;
	//PRINT_MEME(mlt_print_memory_raw((unsigned char *)p + size, BYTES_PER_ROW));
	//PRINT_MEME(WDR("\n"));
}
#endif

void* zmalloc(size_t size)
{
#if USE_LNK_MALLOC
	DEBUG_MLT(WDR("zmalloc:    thread = %p size = %8.8d disable_mlt_malloc = %d/%d __builtin_return_address(0) = %p\n", pthread_self(), size, disable_mlt_malloc.get(), disable_mlt_malloc.counter(), __builtin_return_address(0)));
#else
	DEBUG_MLT(WDR("zmalloc:    thread = %p size = %8.8d __builtin_return_address(0) = %p\n", pthread_self(), size, __builtin_return_address(0)));
#endif
	CMAT_SSTATS(cmatAnalyzer.Start());
	void *p=malloc(size);
	CMAT_SSTATS(cmatAnalyzer.Accumulate());
#if USE_LNK_MALLOC
	DEBUG_MLT(WDR("zmalloc:    thread = %p size = %8.8d disable_mlt_malloc = %d/%d __builtin_return_address(0) = %p p = %p\n", pthread_self(), size, disable_mlt_malloc.get(), disable_mlt_malloc.counter(), __builtin_return_address(0), p));
#else
	DEBUG_MLT(WDR("zmalloc:    thread = %p size = %8.8d __builtin_return_address(0) = %p p = %p\n", pthread_self(), size, __builtin_return_address(0), p));
#endif
	if (!p)
	{
		printf("zmalloc: Memory Allocation Failure: thread = %p size = %8.8d\n", (void*)pthread_self(), size);
		assert(false);
	}
	return p;
}

void zfree(void *p)
{
#if USE_LNK_MALLOC
	DEBUG_MLT(WDR("zfree:      thread = %p p = %p disable_mlt_malloc = %d/%d __builtin_return_address(0) = %p\n", pthread_self(), p, disable_mlt_malloc.get(), disable_mlt_malloc.counter(), __builtin_return_address(0)));
#else
	DEBUG_MLT(WDR("zfree:      thread = %p p = %p __builtin_return_address(0) = %p\n", pthread_self(), p, __builtin_return_address(0)));
#endif
	CMAT_SSTATS(cmdtAnalyzer.Start());
	free (p);
	CMAT_SSTATS(cmdtAnalyzer.Accumulate());
#if USE_LNK_MALLOC
	DEBUG_MLT(WDR("zfree:      thread = %p p = %p disable_mlt_malloc = %d/%d __builtin_return_address(0) = %p ...done\n", pthread_self(), p, disable_mlt_malloc.get(), disable_mlt_malloc.counter(), __builtin_return_address(0)));
#else
	DEBUG_MLT(WDR("zfree:      thread = %p p = %p __builtin_return_address(0) = %p ...done\n", pthread_self(), p, __builtin_return_address(0)));
#endif
}

