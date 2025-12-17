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
#include "mlt_malloc.h"

#if USE_SYSRES_MLT

void * operator new (unsigned int size)
{
	return mlt_malloc(size, __builtin_return_address(0), 0 , 0);
}

void * operator new[](unsigned int size)
{
	return mlt_malloc(size, __builtin_return_address(0), 0, 0);
}

void * operator new (unsigned int size, const char *file, int line)
{
	return mlt_malloc(size, __builtin_return_address(0), file, line);
}

void * operator new[](unsigned int size, const char *file, int line)
{
	return mlt_malloc(size, __builtin_return_address(0), file, line);
}

void operator delete(void *p)
{
	mlt_free(p, __builtin_return_address(0), 0, 0);
}

void operator delete(void *p, const char *file, int line)
{
	mlt_free(p, __builtin_return_address(0), file, line);
}

void operator delete[](void *p)
{
	mlt_free(p, __builtin_return_address(0), 0, 0);
}

void operator delete[](void *p, const char *file, int line)
{
	mlt_free(p, __builtin_return_address(0), file, line);
}

#endif

