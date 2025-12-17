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
#ifndef FIXED_SIZE_PARTITION_H
#define FIXED_SIZE_PARTITION_H

#include	"IMemoryPartition.h"

#if	DEBUG
#define	DEBUG_FMP(x)	x
#else
#define	DEBUG_FMP(x)
#endif

class FPNode
{
	friend class FixedSizePartition;
	FPNode*	next;
	FPNode() : next(0) {}
};

class FixedSizePartition : IMemoryPartition
{
public:
	FixedSizePartition(size_t bcount, size_t bsize);
	~FixedSizePartition();

	virtual void*	allocate(size_t size);
	virtual void	deallocate(void *);
	const int	blockSize() { return bsize; }
	const int	blockCount() { return bcount; }
	int		blocksAvailable() { return acount; }

private:
	FixedSizePartition() : bcount(0), bsize(0), size(0) {};

	void*		base;		// partition base address
	const size_t	size;		// partition size
	const int	bcount;		// block count
	const size_t	bsize;		// block size count

	int		acount;		// available block count
	FPNode*		head;		// free block head
	FPNode*		tail;		// free block tail
};

#endif //FIXED_SIZE_PARTITION_H
