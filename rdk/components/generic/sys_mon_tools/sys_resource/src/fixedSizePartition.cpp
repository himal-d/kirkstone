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
#include <assert.h> 
#include <stdio.h>

#include "fixedSizePartition.h"
#include "zmalloc.h"

FixedSizePartition::FixedSizePartition(size_t _bcount, size_t _bsize) : bcount(_bcount), bsize(_bsize), acount(_bcount), size((sizeof(FPNode) + _bsize) * _bcount)
{
	assert(_bcount != 0 && _bsize != 0);
	
	base=zmalloc(size);

	size_t offs=bsize+sizeof(FPNode);
	head=(FPNode*)((unsigned int)base+bsize);

	FPNode* curNode=(FPNode*)((unsigned int)head+offs);
	FPNode* prvNode=head;
	for (int i=1; i<bcount; i++)
	{
		prvNode->next=curNode;
		prvNode=curNode;
		curNode=(FPNode*)((unsigned int)curNode+offs);
	}

	tail=prvNode;
	tail->next=0;

	curNode=head;
	//DEBUG_FMP(printf("Partition: base address = %p : size = %d : blocks = %d : block size = %d : nodes =\n", base, size, bcount, bsize));
	//for (int i=0; i<bcount; i++, curNode=curNode->next) { DEBUG_FMP(printf("%p ", curNode)); }
	//DEBUG_FMP(printf("\n"));
}

FixedSizePartition::~FixedSizePartition()
{
	zfree(base);
}

void* FixedSizePartition::allocate(size_t _bsize)
{
	if (bsize >= _bsize)
	{
		FPNode*	node=head;
		if (head)
		{
			if ((head=head->next) == 0)
				tail=0;
			--acount;
			return (void*)((unsigned int)node-bsize);
		}
	}
	else
	{
		DEBUG_FMP(printf("FixedSizePartition::allocate: attempt to allocate a memory block larger than instantiated : inst size = %d : requested size = %d\n", bsize, _bsize));
		assert(false);
	}
	return 0;
}

void FixedSizePartition::deallocate(void *p)
{
	if ((unsigned int)base <= (unsigned int)p && (unsigned int)p < (unsigned int)base + size)
	{
		p=(void*)((unsigned int)p+bsize);
		((FPNode*)p)->next=0;
		if (head == 0)
			head=(FPNode*)p;
		if (tail)
			tail->next=(FPNode*)p;
		tail=(FPNode*)p;
		++acount;
	}
	else if (p)
	{
		DEBUG_FMP(printf("FixedSizePartition::deallocate: attempt to deallocate out of partition range address: p = %p : base = %p : size = %d\n", p, base, size));
		assert(false);
	}
}
