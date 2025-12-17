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
#if defined(USE_CMAS)
#include <stdio.h>
#include <string.h>

#include "logFileDescr.h"
#include "cmasAnalyzer.h"
#include "procInfo.h"

#define		bufSizesLength		(2*1024)

#define DEBUG_CMASA_ENABLE	0

#if DEBUG_CMASA_ENABLE
#define	DBG_CMASA(x)	x
#else
#define	DBG_CMASA(x)
#endif

CmasAnalyzer::CmasAnalyzer(size_t bufferLength, char *filename) : SysResLogger(bufferLength, filename), iteration(0), maStats(false), mdStats(false)
{
}

void CmasAnalyzer::SetFilename(const char *postfix, const char *ext)
{
	SysResLogger::SetFilename(postfix, ext);
#if defined(USE_CMAS_BACKTRACE)
	char	file[LOG_FILENAME_LENGTH]={0};
	strcpy(file, postfix);
	strcat(file, "BTRC");
	DBG_CMASA(printf("CmasAnalyzer::SetFilename: file = %s ext = %s\n", file, ext));
	mfcHandler.setFilename(file, ext);
#endif
}

void CmasAnalyzer::Insert(unsigned int allocator, int size, char *file, int line)
{
	CmaStats *cmaStats=0;
	AVLNode<int, CmaStats>* cmaNode=0;
	maStats.Insert((unsigned int)allocator, cmaNode);
	if (cmaNode && (cmaStats=cmaNode->GetDataPtr()))
		cmaStats->Insert(size, (char *)file, line);

#if defined(USE_CMAS_BACKTRACE)
	mfcHandler.collect(allocator, true);
#endif
}

void CmasAnalyzer::Insert(unsigned int allocator, unsigned int deallocator, int size, char *file, int line)
{
	CmaStats *cmaStats=0;
	AVLNode<int, CmaStats>* cmaNode=0;
	mdStats.Insert((unsigned int)deallocator, cmaNode);
	if (cmaNode && (cmaStats=cmaNode->GetDataPtr()))
	{
		cmaStats->Insert(size, (char *)file, line);
#ifdef USE_CMAS_CP
		// Init allocator ip
		cmaStats->Insert(allocator);
#endif
	}
#ifdef USE_CMAS_CP
	// Find allocator's node and init deallocator ip
	maStats.Find(allocator, cmaNode);
	if (cmaNode && (cmaStats=cmaNode->GetDataPtr()))
		cmaStats->Insert((unsigned int)deallocator);
#endif

#if defined(USE_CMAS_BACKTRACE)
	mfcHandler.collect(deallocator, false);
#endif
}

void CmasAnalyzer::Analyze(int allocsSize, int allocsMaxSize, int totalMallocCalls, int totalFreeCalls, int totalReallocCalls, int totalCallocCalls)
{
	LogCMAS(iteration, allocsSize, allocsMaxSize, totalMallocCalls, totalFreeCalls, totalReallocCalls, totalCallocCalls);
#if  defined(USE_CMAS_BACKTRACE)
	mfcHandler.init(maStats);
	mfcHandler.schedule_log(maStats);
	mfcHandler.deinit(maStats);
#endif
	++iteration;
}

void CmasAnalyzer::LogCMAS(int iteration, int allocsSize, int allocsMaxSize, int totalMallocCalls, int totalFreeCalls, int totalReallocCalls, int totalCallocCalls)
{
	size_t	bufoff=0;
	static int totalAllCallsLast=0;
	int totalAllCalls=totalMallocCalls+totalFreeCalls+totalReallocCalls+totalCallocCalls;
	bufoff=sprintf(logBuffer, "MAFS: iteration = %4.4d: cur/max allocs = %d/%d: malloc/free/realloc/calloc/all calls = %d/%d/%d/%d/%d: all calls delta = %d: callers = %d",
		iteration, allocsSize, allocsMaxSize, totalMallocCalls, totalFreeCalls, totalReallocCalls, totalCallocCalls, totalAllCalls, totalAllCalls - totalAllCallsLast,
		maStats.getSize() + mdStats.getSize());
#if	ANALYZE_IDLE_MLT
	if (iteration)
		bufoff+=sprintf(logBuffer+bufoff, ": avg/since last call rate = %d/%d\n", totalAllCalls/(60*SYSMON_POLLINT*iteration), (totalAllCalls - totalAllCallsLast)/(60*SYSMON_POLLINT));
	else
		bufoff+=sprintf(logBuffer+bufoff, ": avg/since last call rate = -/%d\n", (totalAllCalls - totalAllCallsLast)/(60*SYSMON_POLLINT));
#else
	bufoff+=sprintf(logBuffer+bufoff, "\n");
#endif	//ANALYZE_IDLE_MLT
	totalAllCallsLast=totalAllCalls;

	int i=0;
	int curTreeAllocs=0, treeAllocs=0, treeDeAllocs=0;
	AVLTreeInOrderIterator<int,CmaStats> cmasEnd = maStats.end();
	for (AVLTreeInOrderIterator<int,CmaStats> cmasIt = maStats.begin(); cmasIt != cmasEnd && bufoff < bufferLength-bufSizesLength; ++cmasIt)
	{
		CmaStats *cmaStats=cmasIt.getNode()->GetDataPtr();
		if (cmaStats)
		{
			bufoff+=sprintf(logBuffer+bufoff, "%4.4d: +%8.8p", ++i, (void*)*cmasIt);

			AVLTree<int, int>* sizes=cmaStats->GetSizes();
			AVLTreeInOrderIterator<int,int> sizesEnd = sizes->end();
			int  bufSizesOff=0;
			char bufSizes[bufSizesLength];
			for (AVLTreeInOrderIterator<int,int> sizesIt = sizes->begin(); sizesIt != sizesEnd && bufSizesOff < bufSizesLength-16; ++sizesIt)
				bufSizesOff+=sprintf(bufSizes+bufSizesOff, " %6.6d(%4.4d)", *sizesIt, sizesIt.getNode()->GetCount());
			if (bufSizesOff >= bufSizesLength-16)
				bufSizesOff+=sprintf(bufSizes+bufSizesOff, " ***");
			treeAllocs+=cmaStats->GetCount();

			bufoff+=sprintf(logBuffer+bufoff, ":%4.4d @ %s:%d", cmaStats->GetCount(), cmaStats->GetFile(), cmaStats->GetLine());
			memcpy(logBuffer+bufoff, bufSizes, bufSizesOff);
			bufoff+=bufSizesOff;
			bufoff+=sprintf(logBuffer+bufoff, "\n");
#ifdef USE_CMAS_CP
			AVLTree<int, int>* cparts=cmaStats->GetCParts();
			AVLTreeInOrderIterator<int,int> cpartsEnd = cparts->end();
			for (AVLTreeInOrderIterator<int,int> cpartsIt = cparts->begin(); cpartsIt != cpartsEnd && bufoff < bufferLength-24; ++cpartsIt)
				bufoff+=sprintf(logBuffer+bufoff, "%5c -%8.8p:%4.4d\n", ' ', (void*)*cpartsIt, cpartsIt.getNode()->GetCount());
			if (bufoff < bufferLength-40)
				bufoff+=sprintf(logBuffer+bufoff, "_____ +1:%d/-%d:%d/%d/%d/%d\n", cmaStats->GetCount(), cparts->getSize(), cmaStats->GetCPCount(), cmaStats->GetCount()+cmaStats->GetCPCount(), cmaStats->GetCount()-cmaStats->GetCPCount(), cmaStats->GetMaxDiff());
			treeDeAllocs+=cmaStats->GetCPCount();
			curTreeAllocs+=cmaStats->GetCount()-cmaStats->GetCPCount();
#endif	//USE_CMAS_CP
		}
	}
	if (bufoff >= bufferLength-bufSizesLength)
		bufoff+=sprintf(logBuffer+bufoff, "***\n");
#ifdef USE_CMAS_CP
	bufoff+=sprintf(logBuffer+bufoff, "buflen = %d : tree allocs/deallocs/all delta = %d/%d/%d\n", 
		bufoff, totalMallocCalls+totalCallocCalls-treeAllocs, totalFreeCalls-treeDeAllocs, allocsSize-curTreeAllocs);
#else
	bufoff+=sprintf(logBuffer+bufoff, "buflen = %d\n", bufoff);
#endif	//USE_CMAS_CP
	bufoff+=sprintf(logBuffer+bufoff, "\n");

	Log(bufoff);
}

#endif //defined(USE_CMAS)

