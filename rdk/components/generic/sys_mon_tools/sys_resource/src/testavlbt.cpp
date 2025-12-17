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

#ifdef	USE_AVLBT
#include "avlTree.h"
#include "backtrace.h"

int testavlbt()
{
	AVLTree<int,Backtrace> mlt3Backtrace;
	AVLTreeInOrderIterator<int,Backtrace> end = mlt3Backtrace.end();
	AVLNode<int, Backtrace>* node=0;

	int caller[5]={0x100000,0x200000,0x300000,0x400000,0x500000}, size=0;
	Backtrace *backtrace=0;
	for (int i=0; i<5; i++)
	{
		// Insert caller
		printf("iter=%1d: insert:       caller = %p insert event\n", i, (void*)caller[i]);
		bool success=mlt3Backtrace.Insert(caller[i], node);
		backtrace=node->GetDataPtr();
		printf("iter=%1d: after insert: caller = %p : bo = %p : success = %d\n", i, (void*)caller[i], backtrace, success);
		if (backtrace && (size=backtrace->GetSize()))
		{
			unsigned int *bt=backtrace->GetBacktrace();
			printf("iter=%1d: check bt:     caller = %p : bt = %p : size = %d\n", i, (void*)caller[i], (void*)bt, size);
			for (int i=0; i<size; i++) printf("%p\n", (void*)bt[i]);
		}

		// Find caller and init backtrace
		printf("iter=%1d: find:         caller = %p find event\n", i, (void*)caller[i]);
		if (mlt3Backtrace.Find((unsigned int)caller[i], node) && node && (backtrace=node->GetDataPtr()) && ((size=backtrace->GetSize())==0))
		{
			printf("iter=%1d: after find:   caller = %p found and backtrace init event\n", i, (void*)caller[i]);
			backtrace->Init();
			int size=backtrace->GetSize();
			unsigned int *bt=backtrace->GetBacktrace();
			printf("iter=%1d: after init bt:caller = %p : bt = %p : size = %d\n", i, (void*)caller[i], (void*)bt, size);
			for (int i=0; i<size; i++) printf("%p\n", (void*)bt[i]);
		}
	}

	printf("\nEnd of testavlbt tests!\n\n");

	return 0;
}
#endif //USE_AVLBT

