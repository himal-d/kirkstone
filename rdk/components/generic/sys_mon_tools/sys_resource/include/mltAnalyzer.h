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
#ifndef	MLT_ANALYZER_H
#define MLT_ANALYZER_H

#include "LinkedList.h"
#include "IpCmaNode.h"
#include "cmadLogger.h"
#include "cmadHandler.h"

#if defined(USE_MLT_BACKTRACE)
#include "avlTree.h"
#include "backtrace.h"
#include "backtraceHandler.h"
#endif

class MltAnalyzer : public CmadLogger
{
public:
	MltAnalyzer(size_t bufferLength, char *filename=0);
	~MltAnalyzer() {}

	void 		SetFilename(const char *postfix, const char *ext);
	void*		Insert(void *caller, int size, char *file, int line);
	void		Remove(void *p);
	HAHeader* 	GetHAHeader(void *p);
	void		Analyze();

private:
	void		Log(int iteration, SLL<IpCmaNode> &common);

	int		iteration;
	HLL<HAHeader>	cmaHll;
	SLL<IpCmaNode>	*cmad;
	CmadHandler	cmadHandler;
#if !ANALYZE_IDLE_MLT
	HLL<HAHeader>	skippedCmaHll;
#endif
#if defined(USE_MLT_BACKTRACE)
	BacktraceHandler	mltbtHandler;
#endif
};

#endif // MLT_ANALYZER_H

