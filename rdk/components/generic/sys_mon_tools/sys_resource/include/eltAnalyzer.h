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
#ifndef	ELT_ANALYZER_H
#define ELT_ANALYZER_H

#include <sys/time.h>
#include <stdlib.h>

#include "sysresLogger.h"
#include "simpleStats.h"
#include "elapsedTime.h"

template <class statsT, class distT>
class EltAnalyzer : public SysResLogger
{
public:
	EltAnalyzer(int distrRange, int distrBin, size_t bufferLength, char *filename=0);
	~EltAnalyzer() {}

	void 		SetFilename(const char *postfix, const char *ext);
	void		Start();
	void		Accumulate();
	void		Analyze();

private:
	int 				  distrBin;
	int				  iteration;
	ElapsedTime 			  elapsedTime;
	SimpleDistribution<statsT, distT> sd;
};

#endif // ELT_ANALYZER_H

