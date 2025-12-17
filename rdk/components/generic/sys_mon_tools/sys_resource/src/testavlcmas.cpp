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
#include <stdlib.h>

#ifdef	USE_CMAS
#include "avlTree.h"
#include "cmastats.h"

typedef struct MLTCallerAPI
{
	int		size;
	unsigned int	caller;
	char		*file;
	int 		line;
}MLTCallerAPI;

int testavlcmas()
{
	printf("testavlcmas: start\n");
	AVLTree<int,CmaStats> maFreqStats(false);
	AVLTreeInOrderIterator<int,CmaStats> end = maFreqStats.end();

	MLTCallerAPI mltCallerAPI[5]={ {16, 0x100000, (char*)"file1", 10}, {26, 0x200000, (char*)"file2", 20}, {16, 0x100000, (char*)"file1", 10}, {26, 0x200000, (char*)"file2", 20}, {36, 0x300000, (char*)"file3", 30} };
	for (int i=0; i<5; i++)
	{
		CmaStats *cmaStats = 0;

		AVLNode<int, CmaStats>* node=0;
		printf("iter=%1d: insert:        caller = %p @ %s:%d : size = %d insert event\n", i, (void*)mltCallerAPI[i].caller, mltCallerAPI[i].file, mltCallerAPI[i].line, mltCallerAPI[i].size);
		bool success=maFreqStats.Insert(mltCallerAPI[i].caller, node);
		if (node && (cmaStats=node->GetDataPtr())) 
			cmaStats->Insert(mltCallerAPI[i].size, mltCallerAPI[i].file, mltCallerAPI[i].line);

		CmaStats *cmaStatsInsert=node->GetDataPtr();
		printf("iter=%1d: insert status: caller = %p @ %s:%d : success = %d\n", i, (void*)node->GetKey(), cmaStatsInsert->GetFile(), cmaStatsInsert->GetLine(), success);

		// Find caller and init backtrace
		node=0;
		printf("iter=%1d: find:          caller = %p find event\n", i, (void*)mltCallerAPI[i].caller);
		if (maFreqStats.Find((unsigned int)mltCallerAPI[i].caller, node) && node)
		{
			CmaStats *cmaStatsFind=node->GetDataPtr();
			printf("iter=%1d: find status:   caller = %p @ %s:%d\n", i, (void*)mltCallerAPI[i].caller, cmaStatsFind->GetFile(), cmaStatsFind->GetLine());
			AVLTree<int, int>* asizes=cmaStatsFind->GetSizes();
			AVLTreeInOrderIterator<int,int> end = asizes->end();
			printf("iter=%1d: find status:   sizes  = ", i);
			for (AVLTreeInOrderIterator<int,int> iter = asizes->begin(); iter != end; ++iter)
				printf("%3.3d:%d ", *iter, iter.getNode()->GetCount());
			printf("\n");
		}
	}

	printf("\nEnd of testavlcmas tests!\n\n");

	return 0;
}
#endif //USE_CMAS
