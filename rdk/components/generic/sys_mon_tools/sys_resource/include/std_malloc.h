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
#ifndef __STD_MALLOC_H
#define __STD_MALLOC_H

#if USE_SYSRES_MLT && USE_LNK_MALLOC

#define malloc(size) std_malloc(size)
#define realloc(ptr,size) std_realloc(ptr, size)
#define calloc(num, size) std_calloc(num, size)
#define free(ptr) std_free(ptr)
#define memalign(alignment, size) std_memalign(alignment, size)
#define valloc(size) std_valloc(size)

#endif	//USE_SYSRES_MLT && USE_LNK_MALLOC

#endif	//__STD_MALLOC_H
