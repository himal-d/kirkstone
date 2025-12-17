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
#ifndef	ALLOCMETRICS_H
#define ALLOCMETRICS_H

#include <stdio.h>

class AllocMetrics
{
public:
	AllocMetrics() : curAllocs(0), maxAllocs(0), curAllocsSize(0), maxAllocsSize(0), curIncr(0), maxIncr(0) {};
	AllocMetrics(int _curAllocs, int _curAllocsSize, int _curIncr) : 
		curAllocs(_curAllocs), maxAllocs(_curAllocs), curAllocsSize(_curAllocsSize), maxAllocsSize(_curAllocsSize), curIncr(_curIncr), maxIncr(_curIncr) {};

	void Compare(const AllocMetrics &other)
	{
		curIncr=other.curIncr;
		if (curAllocsSize > other.curAllocsSize) ++curIncr;
		else if (curAllocsSize < other.curAllocsSize) --curIncr;
		
		curIncr > other.maxIncr ? maxIncr=other.maxIncr+1 : maxIncr=other.maxIncr;
		curAllocsSize > other.maxAllocsSize ? maxAllocsSize=curAllocsSize : maxAllocsSize=other.maxAllocsSize;
		curAllocs > other.maxAllocs ? maxAllocs=curAllocs : maxAllocs=other.maxAllocs;
	}

	int GetCurAllocs () const { return curAllocs; }
	int GetMaxAllocs () const { return maxAllocs; }
	int GetCurAllocSize () const { return curAllocsSize; }
	int GetMaxAllocSize () const { return maxAllocsSize; }
	int GetCurIncr () const { return curIncr; }
	int GetMaxIncr () const { return maxIncr; }

protected:
	int	curAllocs;
	int	maxAllocs;
	int	curAllocsSize;
	int	maxAllocsSize;
	int	curIncr;
	int	maxIncr;
};

#endif // ALLOCMETRICS_H
