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
#ifndef SIMPLESTATS_H
#define SIMPLESTATS_H

#include <stdio.h>

template <class statsT, class distT> class SimpleDistribution;

template <class statsT, class distT>
class SimpleStats
{
	friend class SimpleDistribution<statsT, distT>;

	SimpleStats(statsT _mean, statsT _sd, distT _min, distT _max, int _size, int _outOfRange, distT _maxOut) : 
			mean(_mean), sd(_sd), min(_min), max(_max), maxOut(_maxOut), size(_size), outOfRange(_outOfRange) {}
	public:
		statsT		mean;
		statsT		sd;
		distT		min;
		distT		max;
		distT		maxOut;
		int		size;
		int		outOfRange;
};

template <class statsT, class distT>
class SimpleDistribution
{
	private:
		int		range;					// distribution range;
		distT		*distribution;				// distribution 

		statsT		mean;
		statsT		sd;
		distT		min;
		distT		max;
		distT		maxOut;
		int		currentSamplesIn;			// number of samples accumulated within the distribution range
		int		currentSamplesOut;			// number of samples accumulated outside of the the distribution range

		bool		updateRequired;				// flag to notify if distribution changed
		bool		stopAccumulation;			// stop accumulating samples

		void		setLimits();

	public:
		SimpleDistribution(int range=1000);
		~SimpleDistribution();

		void* operator new [] (size_t size);
		void  operator delete [] (void *p);

		void		reset();
		void		accumulate(distT sample);
		SimpleStats<statsT, distT> calculate();

		int		getRange() const { return range; }
		int		getSamplesInSize() const { return currentSamplesIn; }
		int		getSamplesOutSize() const { return currentSamplesOut; }
		distT		*getDistribution() const { return distribution; }
		SimpleStats<statsT, distT>	getStats();
		void		stopAccumulate() { stopAccumulation=true; }
};

#endif //SIMPLESTATS_H

