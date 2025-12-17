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

#include "logFileDescr.h"
#include "mltAnalyzer.h"
#include "procInfo.h"
#include "debugRecord.h"

MltAnalyzer::MltAnalyzer(size_t bufferLength, char *filename) : CmadLogger(MLT_INCREASE_THRESHOLD, bufferLength, filename), iteration(0), cmad(0), cmadHandler(bufferLength, filename)
#if defined(USE_MLT_BACKTRACE)
	, mltbtHandler(1024)
#endif
{
}

void MltAnalyzer::SetFilename(const char *postfix, const char *ext)
{
	char	file[LOG_FILENAME_LENGTH]={0};

	DEBUG_MLT(WDR("MltAnalyzer::SetFilename: postfix = %s ext = %s\n", postfix, ext));

	strcpy(file, postfix);
	strcat(file, "3");
	DEBUG_MLT(WDR("MltAnalyzer::SetFilename: file    = %s ext = %s\n", file, ext));
	SysResLogger::SetFilename(file, ext);

	cmadHandler.SetFilename(postfix, ext);
#if defined(USE_MLT_BACKTRACE)
	mltbtHandler.setFilename("MLTBTRC", "");
#endif
}

void *MltAnalyzer::Insert(void* caller, int usize, char *file, int line)
{
	DEBUG_MLT(WDR("MltAnalyzer::Insert:  caller = %p size = %d @ %s:%d\n", caller, usize, file, line));
#ifdef USE_MLT_BACKTRACE
	mltbtHandler.collect((unsigned int)caller);
#endif
	HAHeader haHeader(usize, caller, (char *)file, line);
	return cmaHll.addBack(haHeader, usize);
}

void MltAnalyzer::Remove(void *p)
{
#if DEBUG_MLT_ENABLE
	//HAHeader *haHeader=GetHAHeader(p);
	//DEBUG_MLT(WDR("MltAnalyzer::Remove:  caller = %p size = %d @ %s:%d\n", haHeader->caller, haHeader->size, haHeader->file, haHeader->line));
#endif
	if (cmaHll.remove(p) == true)
		return;
#if !ANALYZE_IDLE_MLT
	else if (skippedCmaHll.remove(p) == true)
		return;
#endif
	else
	{
		DEBUG_MLT(WDR("MltAnalyzer::Remove: p = %p likely just mlt mismatch / less likely memory corruption\n", p));
		zfree(p);
		//*(int*)(0)=1;
	}
}

HAHeader* MltAnalyzer::GetHAHeader(void *p)
{
	return cmaHll.u2n(p)->GetDataPtr();
}

void MltAnalyzer::Analyze()
{
	DEBUG_MLT(WDR ("MltAnalyzer::Analyze:  iter = %d\n", iteration));
#if !ANALYZE_IDLE_MLT
	static SLL<IpCmaNode>	*skippedCmad=0;
	if (iteration < MLT_SKIP_ITERATIONS)
	{
		DEBUG_MLT(WDR ("MltAnalyzer::Analyze:  iter  = %d is skipped\n", iteration));
		skippedCmaHll.moveBack(cmaHll);

		// Build current distribution from skipped calls
		SLL<IpCmaNode> *skippedCmacd = cmadHandler.Build(skippedCmaHll);
		// Compare the distributions from skipped calls if more than one.
		SLL<IpCmaNode> skippedCommon;
		cmadHandler.Compare(skippedCmad, skippedCommon);
		// Log the complete output of skipped calls distribution
		cmadHandler.Log(iteration);

		DEBUG_MLT(WDR ("MltAnalyzer::Analyze: siter = %d: delete skippedCmad = %p\n", iteration, skippedCmad));
		delete skippedCmad;
		// Store the current skipped distribution
		skippedCmad=skippedCmacd;

		++iteration;
		return;
	}
	else if (skippedCmad)
	{
		DEBUG_MLT(WDR ("MltAnalyzer::Analyze:  iter = %d: delete skippedCmad = %p\n", iteration, skippedCmad));
		delete skippedCmad;
		skippedCmad=0;
	}
#endif
	// Build current distribution
	SLL<IpCmaNode> *cmacd = cmadHandler.Build(cmaHll);
	// Compare the distributions
	SLL<IpCmaNode> common;
	cmadHandler.Compare(cmad, common);
	// Log the complete output
	cmadHandler.Log(iteration);
	// Log the common allocation's output
	Log(iteration, common);
#ifdef USE_MLT_BACKTRACE
	LinkedListIterator<IpCmaNode> commonEnd = common.end();
	for (LinkedListIterator<IpCmaNode> commonIt = common.begin(); commonIt != commonEnd; ++commonIt)
	{
		if (commonIt.getNode()->GetDataPtr()->getCmaNode()->GetMaxIncr() >= MLT_INCREASE_THRESHOLD)
		{
			DEBUG_MLT(WDR("MltAnalyzer::Analyze: caller = %p @ %s:%d\n", 
			commonIt.getNode()->GetDataPtr()->GetCaller(), commonIt.getNode()->GetDataPtr()->getCmaNode()->GetFile(), commonIt.getNode()->GetDataPtr()->getCmaNode()->GetLine()));
			mltbtHandler.schedule_log(commonIt.getNode()->GetDataPtr()->GetCaller());
		}
	}
#endif
	// Delete the previous distribution
	DEBUG_MLT(WDR ("MltAnalyzer::Analyze:  delete cmad = %p\n", cmad));
	delete cmad;
	// Store the current distribution
	cmad=cmacd;
	DEBUG_MLT(WDR ("MltAnalyzer::Analyze:  iter = %d ...done\n", iteration));
	++iteration;
}

void MltAnalyzer::Log(int iteration, SLL<IpCmaNode> &common)
{
	int bufoff=sprintf(logBuffer, "CMA: iteration = %4.4d: List of not deallocated objects with maxIncr equal or exceeding threshold = %d:\n", iteration, MLT_INCREASE_THRESHOLD);
	CmadLogger::Log(bufoff, common);
}

