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
#ifndef  __MLT_MALLOC_H__
#define  __MLT_MALLOC_H__

#ifdef __cplusplus 
extern "C" {
#endif

#if USE_SYSRES_MLT

void *mlt_malloc(unsigned int size, void *caller, const char *file, int line);
void mlt_free(void *p, void *caller, const char *file, int line);
void *mlt_realloc(void *p, unsigned int size, void *caller, const char *file, int line);
void *mlt_calloc(unsigned int num, unsigned int size, void *caller, const char *file, int line);
char *mlt_strdup(const char *str, void *caller, const char *file, int line);
//void *mlt_memalign(unsigned int alignment, unsigned int size, void *caller, const char *file, int line);
void mlt_analyze(unsigned long iter);
void mlt_reset();

#endif

#ifdef __cplusplus
}
#endif

#endif	//__MLT_MALLOC_H__
