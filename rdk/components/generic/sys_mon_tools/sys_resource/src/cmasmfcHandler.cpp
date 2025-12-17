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

#include "cmasmfcHandler.h"
#include "radixSort.h"
#include "procInfo.h"
#include "zmalloc.h"

#define	BT_BUFFER_LENGTH	1024

CmasMfcHandler::CmasMfcHandler(char *filename) : groups(0), mabtHandler(BT_BUFFER_LENGTH, filename, USE_CMAS_BACKTRACE_COUNT), mdbtHandler(BT_BUFFER_LENGTH, filename)
{
}

void CmasMfcHandler::setFilename(const char *postfix, const char *ext)
{
	mabtHandler.setFilename(postfix, ext);
	mdbtHandler.setFilename(postfix, ext);
}

void CmasMfcHandler::init(AVLTree<int, CmaStats> &maStats)
{
	int size=maStats.getSize();
	if (!size) return;
	//groups = new MfcGroup [size];
	groups=(MfcGroup **)zmalloc(size * sizeof(*groups));
	for (int i=0; i<size; ++i) groups[i]=(MfcGroup *)zmalloc(sizeof(MfcGroup));

	int i=0;
	AVLTreeInOrderIterator<int,CmaStats> cmasEnd = maStats.end();
	for (AVLTreeInOrderIterator<int,CmaStats> cmasIt = maStats.begin(); cmasIt != cmasEnd; ++cmasIt, ++i)
	{
		CmaStats *cmaStats=cmasIt.getNode()->GetDataPtr();
		if (!cmaStats) continue;
		groups[i]->caller=(unsigned long)*cmasIt;
		groups[i]->fcount=(unsigned long)(cmaStats->GetCount()+cmaStats->GetCPCount());
		groups[i]->cmaStats=cmaStats;
	}
	if (size > 1)
	{
		RadixSort rsCaller = RadixSort((unsigned long **)groups, size, 1);
		rsCaller.sort();
	}
}

void CmasMfcHandler::deinit(AVLTree<int, CmaStats> &maStats)
{
	//delete [] groups;
	for (int i=0; i<maStats.getSize(); ++i) zfree (groups[i]);
	zfree(groups);
	groups=0;
}

void CmasMfcHandler::schedule_log(AVLTree<int, CmaStats> &maStats)
{
	int size=maStats.getSize();
	if (!size) return;
	mabtHandler.resetUpdate();
	for (int j=0, i=size-1; j<USE_CMAS_BACKTRACE_COUNT && i>=0; --i, ++j)
	{
		mabtHandler.schedule_log(groups[i]->caller);
		if (groups[i]->cmaStats)
		{
			AVLTree<int, int>* cparts=groups[i]->cmaStats->GetCParts();
			AVLTreeInOrderIterator<int,int> cpartsEnd = cparts->end();
			for (AVLTreeInOrderIterator<int,int> cpartsIt = cparts->begin(); cpartsIt != cpartsEnd; ++cpartsIt)
				mdbtHandler.schedule_log(*cpartsIt, groups[i]->caller);
		}
	}
}

void CmasMfcHandler::collect(unsigned int caller, bool alloc)
{
	if (alloc) mabtHandler.collect(caller);
	else       mdbtHandler.collect(caller);
}
