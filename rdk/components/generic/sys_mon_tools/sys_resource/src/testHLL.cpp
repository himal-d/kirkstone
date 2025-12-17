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

#include "LinkedList.h"
#include "haHeader.h"

int	testHLL(void)
{
	printf("testHLL: sizeof NodeLinks<HAHeader>  = %d : sizeof Node<HAHeader> = %d : sizeof HAHeader = %d\n", sizeof (NodeLinks<HAHeader>), sizeof (Node<HAHeader>), sizeof (HAHeader));

	HAHeader HAHeader_0(16, (void*)0x100000, (char*)"file1", 10);
	HAHeader HAHeader_1(26, (void*)0x200000, (char*)"file2", 20);
	void *userMemory[2]={0};

	HLL<HAHeader>	list;
	printf("list size before = %d\n", list.getSize());
	userMemory[0]=list.addBack(HAHeader_0, 16);
	userMemory[1]=list.addBack(HAHeader_1, 16);
	int size = list.getSize();
	printf("list size after  = %d\n", size);
	int i=0;
	LinkedListIterator<HAHeader> listEnd=list.end();
	for (LinkedListIterator<HAHeader> iter = list.begin(); iter != listEnd; iter++)
		printf("node[%d]       = %p elem = %p\n", i++, iter, (*iter).caller);
	printf("userMemory[0] = %p\n", userMemory[0]);
	printf("userMemory[1] = %p\n", userMemory[1]);
	for (int j=0; j<size; j++)
	{
		printf("removing   : node = %p elem = %p\n", list.begin(), list.begin().getNode()->GetDataPtr());
		HAHeader *elem=list.u2n(userMemory[j])->GetDataPtr();
		printf("u = %p n = %p elem = %p : caller = %p size = %d @ %s:%d\n", 
			userMemory[j], list.u2n(userMemory[j]), elem, elem->caller, elem->size, elem->file, elem->line);
		list.remove(userMemory[j]);
		listEnd=list.end();
		for (LinkedListIterator<HAHeader> iter = list.begin(); iter != listEnd; iter++) printf("traversing : node = %p elem = %p\n", iter, (*iter).caller);
		printf("status     : list size = %d\n\n", list.getSize());
	}

#if 0
	{
		// Forward/Reverese traverse and element removal of an empty list
		HLL<int>	list;
		printf("list size = %d\n", list.size());
		printf("Forward iteration: empty list\n");
		for (LinkedListIterator<int> iter1 = list.begin(); iter1 != list.end(); iter1++)
			printf("node = %p elem = %d\n", iter1, (*iter1));
		printf("Reverse iteration: empty list\n");
		for (LinkedListIterator<int> iter2 = list.rend(); iter2 != list.rbegin(); iter2--)
			printf("node = %p elem = %d\n", iter2, (*iter2));
		int size = list.size();
		for (int j=0; j<size; j++) list.removeBack();
		printf("list size = %d\n\n", list.size());
	}

	{
		// Forward traverse and front element removal of a list of N integers
		HLL<int>	list;
		printf("list size = %d\n", list.size());
		int	listValueS=1;
		int &listNodeV=listValueS;
		for (int i=0; i<4; i++, listNodeV++) { list.addBack(listNodeV); }
		int size = list.size();
		printf("list size = %d\n", size);
		for (LinkedListIterator<int> iter1 = list.begin(); iter1 != list.end(); iter1++)
			printf("node = %p elem = %d\n", iter1, (*iter1));
		for (int j=0; j<size; j++)
		{
			printf("removing   : node = %p elem = %d\n", list.begin(), *list.begin());
			list.removeFront();
			for (LinkedListIterator<int> iter1 = list.begin(); iter1 != list.end(); iter1++) 
				printf("traversing : node = %p elem = %d\n", iter1, (*iter1));
			printf("status     : list size = %d\n\n", list.size());
		}
	}

	{
		// Forward traverse and pointer based element removal of a list of N integers
		HLL<int>	list;
		printf("list size = %d\n", list.size());
		void *userMemory[4]={0};
		int	listValueS=1;
		int &listNodeV=listValueS;
		for (int i=0; i<4; i++, listNodeV++) { userMemory[i]=list.addBack(listNodeV); }
		int size = list.size();
		printf("list size = %d\n", size);
		for (LinkedListIterator<int> iter1 = list.begin(); iter1 != list.end(); iter1++)
			printf("node = %p elem = %d\n", iter1, (*iter1));
		for (int j=0; j<size; j++)
		{
			printf("removing   : node = %p userMemory = %p\n", list.u2n(userMemory[j]), userMemory[j]);
			list.remove(userMemory[j]);
			for (LinkedListIterator<int> iter1 = list.begin(); iter1 != list.end(); iter1++) 
				printf("traversing : node = %p elem = %d\n", iter1, (*iter1));
			printf("status     : list size = %d\n\n", list.size());
		}
	}

	{
		// Concatination of 2 lists using moveBack()
		HLL<int>	list1;
		printf("list 1: size = %d\n", list1.size());
		int	listValueS=1;
		int &listNodeV=listValueS;
		for (int i=0; i<4; i++, listNodeV++) { list1.addBack(listNodeV); }
		printf("list 1: size = %d\n", list1.size());
		printf("Forward iteration: postfix increment\n");
		for (LinkedListIterator<int> iter1 = list1.begin(); iter1 != list1.end(); iter1++)
			printf("list 1: node = %p elem = %d\n", iter1, (*iter1));

		HLL<int>	list2;
		printf("list 2: size = %d\n", list2.size());
		listValueS=20;
		for (int i=0; i<8; i++, listNodeV++) { list2.addBack(listNodeV); }
		printf("list 2: size = %d\n", list2.size());
		printf("Forward iteration: postfix increment\n");
		for (LinkedListIterator<int> iter1 = list2.begin(); iter1 != list2.end(); iter1++)
			printf("list 2: node = %p elem = %d\n", iter1, (*iter1));

		printf("cat list 1 & 2\n");
		list1.moveBack(list2);
		printf("list 1: size = %d\n", list1.size());
		printf("Forward iteration: postfix increment\n");
		for (LinkedListIterator<int> iter1 = list1.begin(); iter1 != list1.end(); iter1++)
			printf("list 1: node = %p elem = %d\n", iter1, (*iter1));
	}

	{
		// Removal of list elements using removeBack()
		HLL<int>	list;
		printf("list size = %d\n", list.size());
		int	listValueS=1;
		int &listNodeV=listValueS;
		for (int i=0; i<4; i++, listNodeV++) { list.addBack(listNodeV); }
		printf("list size = %d\n", list.size());
		printf("Forward iteration: postfix increment\n");
		for (LinkedListIterator<int> iter1 = list.begin(); iter1 != list.end(); iter1++)
			printf("node = %p elem = %d\n", iter1, (*iter1));
		printf("Reverse iteration: postfix decrement\n");
		for (LinkedListIterator<int> iter2 = list.rend(); iter2 != list.rbegin(); iter2--)
			printf("node = %p elem = %d\n", iter2, (*iter2));
		int size = list.size();
		for (int j=0; j<size; j++) list.removeBack();
		printf("list size = %d\n\n", list.size());
	}

	{
		HLL<char>	list;
		printf("list size = %d\n", list.size());
		char	listValueS=65;
		char	&listNodeV=listValueS;
		for (int i=0; i<4; i++, listNodeV++) { list.addBack(listNodeV); }
		printf("list.size = %d\n", list.size());
		printf("Forward iteration: prefix increment\n");
		for (LinkedListIterator<char> iter1 = list.begin(); iter1 != list.end(); ++iter1)
			printf("node = %p elem = %c\n", iter1, (*iter1));
		printf("Reverse iteration: prefix decrement\n");
		for (LinkedListIterator<char> iter2 = list.rend(); iter2 != list.rbegin(); --iter2)
			printf("node = %p elem = %c\n", iter2, (*iter2));
		int size = list.size();
		for (int j=0; j<size; j++) list.removeBack();
		printf("list size = %d\n\n", list.size());
	}

	{
		char *strings[] =	{
							"Hello",
							"Goodbye",
							"Computer",
							"World",
							};
		HLL<char*>	list;
		printf("list size = %d\n", list.size());
		for (int i=0; i<4; i++) list.addBack(strings[i]);
		printf("list.size = %d\n", list.size());
		printf("Forward iteration: prefix increment\n");
		for (LinkedListIterator<char*> iter1 = list.begin(); iter1 != list.end(); ++iter1)
			printf("node = %p elem = %s\n", iter1, (*iter1));
		printf("Reverse iteration: prefix decrement\n");
		for (LinkedListIterator<char*> iter2 = list.rend(); iter2 != list.rbegin(); --iter2)
			printf("node = %p elem = %s\n", iter2, (*iter2));
		int size = list.size();
		for (int j=0; j<size; j++) list.removeBack();
		printf("list size = %d\n\n", list.size());
	}
#endif
	return 0;
}
