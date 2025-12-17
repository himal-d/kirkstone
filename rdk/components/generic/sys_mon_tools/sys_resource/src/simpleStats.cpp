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
#include <cmath>
#include <cstring>
#include <limits.h>
#include <cfloat>

#include "simpleStats.h"
#include "zmalloc.h"

#ifdef USE_SSTATS_FLINT
template <>
void SimpleDistribution<float, int>::setLimits()
{
	min = INT_MAX;
	max = maxOut = INT_MIN;
}
#endif

template <class statsT, class distT>
void* SimpleDistribution<statsT, distT>::operator new [] (size_t size)
{
	return zmalloc(size);
}

template <class statsT, class distT>
void SimpleDistribution<statsT, distT>::operator delete [] (void *p)
{
	zfree(p);
}

template <class statsT, class distT>
SimpleDistribution<statsT, distT>::SimpleDistribution(int _range) : range(_range), distribution(0), currentSamplesIn(0), currentSamplesOut(0), updateRequired(false), stopAccumulation(false)
{
	setLimits();
	distribution = new distT [range];
	memset((void *)distribution, 0, range*sizeof(distT));
}

template <class statsT, class distT>
SimpleDistribution<statsT, distT>::~SimpleDistribution()
{
	delete [] distribution;
	distribution=0;
}

template <class statsT, class distT>
void SimpleDistribution<statsT, distT>::reset()
{
	setLimits();
	currentSamplesIn = currentSamplesOut = 0;

	if (distribution)
		memset((void *)distribution, 0, range*sizeof(distT));
	
	updateRequired = false;
	stopAccumulation = false;
}

template <class statsT, class distT>
void SimpleDistribution<statsT, distT>::accumulate(distT sample)
{
	if (!distribution || stopAccumulation)
		return;

	if ((int)sample >= range)
	{
		currentSamplesOut++;		// Number of samples out of the range
		if (maxOut < (distT)sample) maxOut=(distT)sample;
		return;
	}

	if (min > (distT)sample) min=(distT)sample;
	if (max < (distT)sample) max=(distT)sample;

	distribution[(int)sample]++;		// Collect samples within the distribition range
	updateRequired = true;
	currentSamplesIn++;
}

template <class statsT, class distT>
SimpleStats<statsT, distT> SimpleDistribution<statsT, distT>::calculate()
{
	mean=sd=0;
	for (int i=1; i<range; i++)
	{
		if (distribution[i] != 0)
		{
			statsT sample=(statsT)distribution[i]*i;
			mean +=(statsT)sample;
			sd   +=(statsT)sample*i;
		}
	}

	if (currentSamplesIn)
	{
		mean=mean/currentSamplesIn;
		sd=(statsT)sqrt(sd/(double)currentSamplesIn - (double)mean*mean);
	}

	return SimpleStats<statsT, distT>(mean, sd, min, max, currentSamplesIn, currentSamplesOut, maxOut);
}

template <class statsT, class distT>
SimpleStats<statsT, distT> SimpleDistribution<statsT, distT>::getStats()
{
	if (updateRequired)
	{
		updateRequired = false;
		return calculate();
	}

	return SimpleStats<statsT, distT>(mean, sd, min, max, currentSamplesIn, currentSamplesOut, maxOut);
}

#ifdef USE_SSTATS_FLINT
template class SimpleStats<float, int>;
template class SimpleDistribution<float, int>;
#endif

