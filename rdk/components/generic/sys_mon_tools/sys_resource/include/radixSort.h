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
#ifndef RADIX_SORT_H
#define RADIX_SORT_H

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "zmalloc.h"

class RadixSort
{
private:
	unsigned long	hist[256];
	unsigned long	indx[256];
	unsigned long	**mSource;
	unsigned long	**mTemp;
	unsigned long	mLength;
	int		mElem;

	void radix (unsigned long **source, unsigned long **dest, unsigned long bitShift)
	{
		unsigned long i=0;
		memset (hist, 0, sizeof (hist));
		for (i=0; i<mLength; i++ )
			hist[(source[i][mElem] >> bitShift) & 0xff]++;

		indx[0]=0;
		for (i=1; i<256; i++) 
			indx[i] = indx[i-1] + hist[i-1];

		for (i=0; i<mLength; i++)
			dest[indx[(source[i][mElem] >> bitShift) & 0xff]++] = source[i];
	}

public:
	RadixSort(unsigned long **source, unsigned long length, int elem) : mSource(source), mLength(length), mElem(elem)
	{
		mTemp = (unsigned long **)zmalloc(mLength * sizeof(unsigned long *));
	}
	~RadixSort()
	{
		zfree(mTemp);
	}
	void sort ()
	{
		radix (mSource, mTemp, 0);
		radix (mTemp, mSource, 8);
		radix (mSource, mTemp, 16);
		radix (mTemp, mSource, 24);
	}
};


#endif //RADIX_SORT_H

