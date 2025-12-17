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
#ifndef __RPL_MALLOC_H
#define __RPL_MALLOC_H

#if USE_SYSRES_MLT

#define CONCAT1(x,y)	x##y 
#define CONCAT2(x,y)	CONCAT1(x,y) 
#define FUNCTION(NAME)	CONCAT2(NAME, RETURN_ADDRESS_LEVEL)

#if USE_FILE_LINE_INFO
#define malloc(size) FUNCTION (rpl_malloc) (size, __FILE__, __LINE__)
#define realloc(ptr,size) FUNCTION (rpl_realloc) (ptr, size, __FILE__, __LINE__)
#define calloc(num, size) FUNCTION (rpl_calloc) (num, size, __FILE__, __LINE__)
#define free(ptr) FUNCTION (rpl_free) (ptr, __FILE__, __LINE__)
#define strdup(str) rpl_strdup(str, __FILE__, __LINE__)
//#define memalign(alignment, size) rpl_memalign(alignment, size, __FILE__, __LINE__)
#else
#define malloc(size) FUNCTION (rpl_malloc) (size, 0, 0)
#define realloc(ptr,size) FUNCTION (rpl_realloc) (ptr, size, 0, 0)
#define calloc(num, size) FUNCTION (rpl_calloc) (num, size, 0, 0)
#define free(ptr) FUNCTION (rpl_free) (ptr, 0, 0)
#define strdup(str) rpl_strdup(str, 0, 0)
//#define memalign(alignment, size) rpl_memalign(alignment, size, 0, 0)
#endif

#ifdef __cplusplus 
extern "C" {
#endif

void * rpl_malloc0 (unsigned int size, const char *file, int line);
void * rpl_malloc1 (unsigned int size, const char *file, int line);
void rpl_free0(void *p, const char *file, int line);
void rpl_free1(void *p, const char *file, int line);
void * rpl_realloc0 (void *p, unsigned int size, const char *file, int line);
void * rpl_realloc1 (void *p, unsigned int size, const char *file, int line);
void * rpl_calloc0 (unsigned int num, unsigned int size, const char *file, int line);
void * rpl_calloc1 (unsigned int num, unsigned int size, const char *file, int line);
char * rpl_strdup (const char *str, const char *file, int line);
//void * rpl_memalign (unsigned int alignment, unsigned int size, const char *file, int line);

#ifdef __cplusplus
}
#endif

#endif	//USE_SYSRES_MLT

#endif	//__RPL_MALLOC_H
