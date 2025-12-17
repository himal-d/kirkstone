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
#ifndef	CMAS_ANALYZER_H
#define CMAS_ANALYZER_H

#include "sysresLogger.h"
#include "avlTree.h"
#include "cmastats.h"

#if defined(USE_CMAS_BACKTRACE)
#include "cmasmfcHandler.h"
#endif

class CmasAnalyzer : public SysResLogger
{
public:
	CmasAnalyzer(size_t bufferLength, char *filename=0);
	~CmasAnalyzer() {}

	void 		SetFilename(const char *postfix, const char *ext);
	void		Insert(unsigned int allocator, int size, char *file, int line);
	void		Insert(unsigned int allocator, unsigned int deallocator, int size, char *file, int line);
	void		Analyze(int allocsSize, int allocsMaxSize, int totalMallocCalls, int totalFreeCalls, int totalReallocCalls, int totalCallocCalls);

private:
	void 		LogCMAS(int iteration, int allocsSize, int allocsMaxSize, int totalMallocCalls, int totalFreeCalls, int totalReallocCalls, int totalCallocCalls);

	int 			iteration;
	AVLTree<int, CmaStats>	maStats;
	AVLTree<int, CmaStats>	mdStats;

#if defined(USE_CMAS_BACKTRACE)
	CmasMfcHandler		mfcHandler;
#endif
};

#endif // CMAS_ANALYZER_H

