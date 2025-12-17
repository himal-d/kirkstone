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
#include "cmadLogger.h"

#define		sizesMaxLength		1024

CmadLogger::CmadLogger(int _threshold, size_t bufferLength, char *filename) : SysResLogger(bufferLength, filename), threshold(_threshold)
{
}

void CmadLogger::Build(size_t &bufoff, SLL<IpCmaNode> &cmad)
{
	int i=1;
	LinkedListIterator<IpCmaNode> cmadEnd = cmad.end();
	for (LinkedListIterator<IpCmaNode> cmadIt = cmad.begin(); cmadIt != cmadEnd && bufoff < bufferLength-sizesMaxLength; ++cmadIt, ++i)
	{
		IpCmaNode *ipCmaNode=cmadIt.getNode()->GetDataPtr();

		CmaNode *cmaNode=ipCmaNode->getCmaNode();
		if (cmaNode->GetMaxIncr() >= threshold)
		{
			bufoff+=sprintf (logBuffer+bufoff, "CMA: #%4.4d: caller = %8.8p cur/max size = %8.8d/%8.8d cur/max incr = %4.4d/%4.4d cur/max alloc = %4.4d/%4.4d @ %s:%d", 
				i, (void*)ipCmaNode->GetCaller(), 
				cmaNode->GetCurAllocSize(), cmaNode->GetMaxAllocSize(), cmaNode->GetCurIncr(), cmaNode->GetMaxIncr(), cmaNode->GetCurAllocs(), cmaNode->GetMaxAllocs(),
				ipCmaNode->GetFile(), ipCmaNode->GetLine());

			AVLTree<int, int>* sizes=ipCmaNode->GetSizes();
			AVLTreeInOrderIterator<int,int> sizesEnd = sizes->end();
			int sizesLength=0;
			for (AVLTreeInOrderIterator<int,int> sizesIt = sizes->begin(); sizesIt != sizesEnd && sizesLength < sizesMaxLength-16; ++sizesIt)
				sizesLength+=sprintf(logBuffer+bufoff+sizesLength, " %6.6d(%4.4d)", *sizesIt, *(sizesIt.getNode()->GetDataPtr()));
			if (sizesLength >= sizesMaxLength-16)
				sizesLength+=sprintf(logBuffer+bufoff+sizesLength, " ***");
			sizesLength+=sprintf(logBuffer+bufoff+sizesLength, "\n");
			bufoff+=sizesLength;
		}
	}
	if (bufoff >= bufferLength-sizesMaxLength)
		bufoff+=sprintf(logBuffer+bufoff, "***\n");
	bufoff+=sprintf(logBuffer+bufoff, "buflen = %d\n", bufoff);
	bufoff+=sprintf(logBuffer+bufoff, "\n");
}

void CmadLogger::Log(size_t bufoff, SLL<IpCmaNode> &cmad)
{
	Build(bufoff, cmad);
	SysResLogger::Log(bufoff);
}

