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
#include	<assert.h> 

#include	"IMemoryPartition.h"

void * operator new (size_t size, IMemoryPartition *partition) throw()
{
	assert(partition);
	if (partition) return partition->allocate(size);
	return 0;
}

void operator delete (void *p, IMemoryPartition *partition)
{
	assert(partition);
	if (partition) partition->deallocate(p);
}

template<class T> T* create(IMemoryPartition *partition)
{
#if USE_CUSTOM_MM
	assert(partition);
	if (partition) return new (partition) T();
	return 0;
#else
	return new T();
#endif
}

template<class T> void destroy(T* p, IMemoryPartition *partition)
{
#if USE_CUSTOM_MM
	if (p)
	{
		p->~T();
		assert(partition);
		if (partition) partition->deallocate(p);
	}
#else
	delete p;
#endif
}
