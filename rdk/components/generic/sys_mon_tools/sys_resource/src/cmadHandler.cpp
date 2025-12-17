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
#include "procInfo.h"
#include "radixSort.h"
#include "cmadHandler.h"
#include "sysResource.h"
#include "zmalloc.h"

CmadHandler::CmadHandler(size_t bufferLength, char *filename) : CmadLogger(0, bufferLength, filename), allocsLength(0), allocsMaxLength(0), cmad(0)
{
}

void CmadHandler::SetFilename(const char *postfix, const char *ext)
{
	DBG_MLT(printf("CmadHandler::SetFilename: postfix = %s ext = %s\n", postfix, ext));
	SysResLogger::SetFilename(postfix, ext);
}

SLL<IpCmaNode>* CmadHandler::Build(HLL<HAHeader> &cmaHll)
{
	cmad = new SLL<IpCmaNode>;

	DBG_MLT(printf("CmadHandler::Build: new cmad    = %p\n", cmad));

	allocsLength=cmaHll.getSize();
	if (allocsLength > allocsMaxLength) allocsMaxLength=allocsLength;
	DBG_MLT(printf("CmadHandler::Build: allocsLength = %d\n", allocsLength));
	if (!allocsLength)
		return cmad;
	HAHeader **haHeaders=(HAHeader **)zmalloc(allocsLength * sizeof(HAHeader *));

	int i=0;
	LinkedListIterator<HAHeader> cmaHllEnd=cmaHll.end();
	for (LinkedListIterator<HAHeader> iter = cmaHll.begin(); iter != cmaHllEnd; iter++, i++) haHeaders[i]=&(*iter);
	if (allocsLength > 1)
	{
		RadixSort rsCaller = RadixSort((unsigned long **)haHeaders, allocsLength, 0);
		rsCaller.sort();
	}

	// Collect memory allocation metrics
	i=0;
	while (i<allocsLength)
	{
		int iS=i;
		// Find caller's statistics
		unsigned int caller=(unsigned int)haHeaders[i]->caller;
		while (i<allocsLength && caller == (unsigned int)haHeaders[i]->caller) i++;
		if (i - iS > 1)
		{
			RadixSort rsSizer = RadixSort((unsigned long **)&haHeaders[iS], i - iS, 1);
			rsSizer.sort();
		}
		// collect caller's file, line
		//printf("CmadHandler::Build: caller = %p file = %s line = %d\n", caller, haHeaders[iS]->file, haHeaders[iS]->line);
		IpCmaNode ipCmaNode((unsigned int)caller, haHeaders[iS]->file, haHeaders[iS]->line);
		//printf("CmadHandler::Build: caller = %p file = %s line = %d\n", ipCmaNode.GetCaller(), ipCmaNode.GetFile(), ipCmaNode.GetLine());

		// Find and collect caller's sizes:
		for (int j=iS; j<i; j++)
		{
			int jS=j;
			size_t size=haHeaders[j]->size;
			while (j<i && size == haHeaders[j]->size) j++;
			ipCmaNode.Insert(size, j - jS);
		}
		ipCmaNode.SetTotal();
		cmad->addBack(ipCmaNode);
	}

	DBG_MLT(printf("CmadHandler::Build:     cmad = %p size = %d\n", cmad, cmad->getSize()));

	return cmad;
}

void CmadHandler::Compare(SLL<IpCmaNode> *cmapd, SLL<IpCmaNode> &common)
{
	SLL<IpCmaNode>	empty;
	LinkedListIterator<IpCmaNode> cmadIter=empty.begin(), cmapdIter=empty.begin(), cmadEnd=empty.end(), cmapdEnd=empty.end();

	if (cmapd)
		cmapdIter=cmapd->begin();
	if (cmad)
		cmadIter=cmad->begin();

	LinkedListIterator<IpCmaNode> commonBegin = common.begin();
	LinkedListIterator<IpCmaNode> commonIter = commonBegin;
	int prev=0;
	while (cmadIter != cmadEnd && cmapdIter != cmapdEnd)
	{
		IpCmaNode *ipCmaNode=cmadIter.getNode()->GetDataPtr();
		IpCmaNode *ipCmaNodeP=cmapdIter.getNode()->GetDataPtr();
		if (ipCmaNode->GetCaller() == ipCmaNodeP->GetCaller())
		{
			if (commonIter == commonBegin || ipCmaNode->GetCaller() != prev)
			{
				prev=ipCmaNode->GetCaller();
				CmaNode *cmaNode=ipCmaNode->getCmaNode();
				CmaNode *cmaNodeP=ipCmaNodeP->getCmaNode();

				cmaNode->Compare(*cmaNodeP);
				common.addBack(*ipCmaNode);
				++commonIter;
			}
			++cmadIter;
			++cmapdIter;
		}
		else if (ipCmaNode->GetCaller() > ipCmaNodeP->GetCaller())
			++cmapdIter;
		else
			++cmadIter;
	}
	DBG_MLT(printf("CmadHandler::Compare: all    = %p size = %d\n", cmad, cmad->getSize()));
	DBG_MLT(Print(cmad));
	DBG_MLT(printf("CmadHandler::Compare: common = %p size = %d\n", &common, common.getSize()));
	DBG_MLT(Print(&common));
}

void CmadHandler::Log(int iteration)
{
	int bufoff=sprintf(logBuffer, "CMA: iteration = %4.4d: cur/max allocs = %d/%d entries = %d : List of not deallocated objects:\n", iteration, allocsLength, allocsMaxLength, cmad->getSize());
	CmadLogger::Log(bufoff, *cmad);
	bufoff=getSysResourceInfo(logBuffer, true);
	strcat(logBuffer,"\n");
	++bufoff;
	SysResLogger::Log(bufoff);
}

#if DEBUG_MLT_ENABLE
void CmadHandler::Print(SLL<IpCmaNode> *cmad)
{
	int	bufoff=0;
	CmadLogger::Build(bufoff, *cmad);
	printf("%s", SysResLogger::logBuffer);
}
#endif //DEBUG_MLT_ENABLE

