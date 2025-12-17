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
#include <stdio.h>
#include <string.h>

#include "eltAnalyzer.h"
#include "procInfo.h"

#define DEBUG_ELTA_ENABLE	1

#if DEBUG_ELTA_ENABLE
#define	DBG_ELTA(x)	x
#else
#define	DBG_ELTA(x)
#endif

//distrBin :	1 - 1nsec; 10 - 10nsec; 100 - 100nsec; 1000 - 1usec; 10000 - 10usec; 100000 - 1000usec.
template <class statsT, class distT>
EltAnalyzer<statsT, distT>::EltAnalyzer(int distrRange, int _distrBin, size_t bufferLength, char *filename) : SysResLogger(bufferLength, filename), distrBin(_distrBin), iteration(0), sd(distrRange)
{
	DBG_ELTA(printf("EltAnalyzer<statsT, distT>::EltAnalyzer: distrRange = %d distrBin = %d bufferLength = %d filename = %s\n", sd.getRange(), distrBin, bufferLength, filename));
}

template <class statsT, class distT>
void EltAnalyzer<statsT, distT>::SetFilename(const char *postfix, const char *ext)
{
	SysResLogger::SetFilename(postfix, ext);
}

template <class statsT, class distT>
void EltAnalyzer<statsT, distT>::Start()
{
	elapsedTime.start();
}

template <class statsT, class distT>
void EltAnalyzer<statsT, distT>::Accumulate()
{
	if (distrBin) sd.accumulate(elapsedTime.enddiffnsec()/distrBin);
}

#ifdef USE_SSTATS_FLINT
template <>
void EltAnalyzer<float, int>::Analyze()
{
	SimpleStats<float, int> sdStats = sd.getStats();

	int bufoff=0;
	if (iteration == 0)
		bufoff=sprintf(logBuffer, "distribution range = 0-%d / 0-%d usec : bin size = %d nsec\n", sd.getRange(), (sd.getRange()*distrBin)/1000, distrBin);

	bufoff+=sprintf(logBuffer+bufoff, "iteration = %4.4d : mean = %f sd = %f : min = %d max = %d : size = %d outOfRange = %d maxOut = %d\n",
		iteration, sdStats.mean, sdStats.sd, sdStats.min, sdStats.max, sdStats.size, sdStats.outOfRange, sdStats.maxOut);

	int	*sdDistr=sd.getDistribution();
	for (int i=0; i<sd.getRange(); i++) bufoff+=sprintf(logBuffer+bufoff,"%2d ", sdDistr[i]);
	bufoff+=sprintf(logBuffer+bufoff, "\n");

	bufoff+=sprintf(logBuffer+bufoff, "buffer length = %d\n", bufoff);

	Log(bufoff);

	++iteration;
}

template class EltAnalyzer<float, int>;
#endif
