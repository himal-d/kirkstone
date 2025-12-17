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
#ifndef __LNK_MALLOC_H
#define __LNK_MALLOC_H

#if USE_SYSRES_MLT && USE_LNK_MALLOC

#include <stdio.h>

#include "sysres_ctor.h"
#include "countedFlag.h"


typedef void* (*malloc_call)(size_t);
typedef void* (*calloc_call)(size_t, size_t);
typedef void* (*realloc_call)(void *, size_t);
typedef void  (*free_call)(void *);
typedef void* (*memalign_call)(size_t, size_t);
typedef void* (*valloc_call)(size_t);
typedef int   (*posix_memalign_call)(void **memptr, size_t alignment, size_t size);

#ifdef __cplusplus 
extern "C" {
#endif

#define USE_STD_MALLOC_ATTR_CTOR

#ifdef USE_STD_MALLOC_ATTR_CTOR
#define __std_malloc_attr  __attribute__((constructor (__STD_MALLOC_CTOR_PRIORITY)))
#else
#define __std_malloc_attr
#endif

extern void __std_malloc_attr std_malloc_ctor();

extern malloc_call		std_malloc;
extern calloc_call		std_calloc;
extern realloc_call		std_realloc;
extern free_call		std_free;
extern memalign_call		std_memalign;
extern valloc_call		std_valloc;
extern posix_memalign_call	std_posix_memalign;

extern CountedFlag 		disable_mlt_malloc;

#ifdef __cplusplus
}
#endif

#endif	//USE_SYSRES_MLT && USE_LNK_MALLOC

#endif	//__LNK_MALLOC_H
