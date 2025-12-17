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

#include "IpCmaNode.h"
#include "LinkedList.h"

#define	TEST_BASIC_TYPES
#define	TEST_IPCMANODE

int	testSLL(void)
{
#ifdef TEST_IPCMANODE
#define	IP_NODES_SIZE	4
#define	IP_NODE_SIZES	3

	SLL<IpCmaNode>	list;
	int				size=0;
	void *userMemory[IP_NODES_SIZE]={0};

	printf("sizeof sizeof NodeLinks<IpCmaNode>  = %d : sizeof Node<IpCmaNode> = %d : sizeof IpCmaNode = %d\n", 
		sizeof (NodeLinks<IpCmaNode>), sizeof (Node<IpCmaNode>), sizeof (IpCmaNode));

	{
		IpCmaNode*	ipCmaNodes[IP_NODES_SIZE]={0};
		int		address=0x100000;
		char		file[10]={0};
		int		line=10;
		int		size=12, scount=1, fileind=0;
		sprintf(file, "file.0");
		for (int i=0; i<IP_NODES_SIZE; i++, scount++)
		{
			ipCmaNodes[i]= new IpCmaNode(address, file, line);
			for (int j=0; j<IP_NODE_SIZES; j++, size+=8)
				ipCmaNodes[i]->Insert(size, scount);
			address+=0x100000;
			sprintf(file, "file.%d", ++fileind);
			line+=10; 
		}

		printf("list size before = %d\n", list.getSize());
		for (int i=0; i<IP_NODES_SIZE; i++)
			userMemory[i]=list.addBack(*ipCmaNodes[i]);
		printf("list size after  = %d\n", list.getSize());

		for (int i=0; i<IP_NODES_SIZE; i++)
			delete ipCmaNodes[i];
	}

	int i=0;
	LinkedListIterator<IpCmaNode> iter1End=list.end();
	for (LinkedListIterator<IpCmaNode> iter1 = list.begin(); iter1 != iter1End; iter1++)
	{
		IpCmaNode *ipCmaNode=iter1.getNode()->GetDataPtr();
		AVLTree<int, int>* sizes=ipCmaNode->GetSizes();
		printf("node[%d]       = %p elem = %p\n", i++, iter1, iter1.getNode()->GetDataPtr()->GetCaller());
		AVLTreeInOrderIterator<int,int> sizesEnd = sizes->end();
		for (AVLTreeInOrderIterator<int,int> sizesIt = sizes->begin(); sizesIt != sizesEnd; ++sizesIt)
		{
			printf("%6.6d(%4.4d) ", *sizesIt, *(sizesIt.getNode()->GetDataPtr()));
		}
		printf("\n");
	}
	for (i=0; i<IP_NODES_SIZE; i++)
		printf("userMemory[%d] = %p\n", i, userMemory[i]);

	size=list.getSize();
	for (int j=0; j<size; j++)
	{
		printf("removing   : node = %p elem = %p\n", list.begin(), list.begin().getNode()->GetDataPtr()->GetCaller());
		list.remove(userMemory[j]);
		for (LinkedListIterator<IpCmaNode> iter1 = list.begin(); iter1 != iter1End; iter1++) printf("traversing : node = %p elem = %p\n", 
			iter1, iter1.getNode()->GetDataPtr()->GetCaller());
		printf("status     : list size = %d\n\n", list.getSize());
	}
#endif

#ifdef TEST_BASIC_TYPES
	printf("sizeof NodeLinks<int>  = %d : sizeof Node<int> = %d sizeof SLL<int> = %d sizeof HLL<int> = %d\n", 
		sizeof (NodeLinks<int>), sizeof (Node<int>), sizeof (SLL<int>), sizeof (HLL<int>));

	{
		// Forward/Reverese traverse and element removal of an empty list
		SLL<int>	list;
		printf("list size = %d\n", list.getSize());
		printf("Forward iteration: empty list\n");
		LinkedListIterator<int> iter1End=list.end();
		for (LinkedListIterator<int> iter1 = list.begin(); iter1 != iter1End; iter1++)
			printf("node = %p elem = %d\n", iter1, (*iter1));
		printf("Reverse iteration: empty list\n");
		LinkedListIterator<int> iter2End=list.rbegin();
		for (LinkedListIterator<int> iter2 = list.rend(); iter2 != iter2End; iter2--)
			printf("node = %p elem = %d\n", iter2, (*iter2));
		int size = list.getSize();
		for (int j=0; j<size; j++) list.removeBack();
		printf("list size = %d\n\n", list.getSize());
	}

	{
		// Forward traverse and front element removal of a list of N integers
		SLL<int>	list;
		printf("list size = %d\n", list.getSize());
		int	listValueS=1;
		int &listNodeV=listValueS;
		for (int i=0; i<4; i++, listNodeV++) { list.addBack(listNodeV); }
		int size = list.getSize();
		printf("list size = %d\n", size);
		LinkedListIterator<int> iter1End=list.end();
		for (LinkedListIterator<int> iter1 = list.begin(); iter1 != iter1End; iter1++)
			printf("node = %p elem = %d\n", iter1, (*iter1));
		for (int j=0; j<size; j++)
		{
			printf("removing   : node = %p elem = %d\n", list.begin(), *list.begin());
			list.removeFront();
			for (LinkedListIterator<int> iter1 = list.begin(); iter1 != iter1End; iter1++) 
				printf("traversing : node = %p elem = %d\n", iter1, (*iter1));
			printf("status     : list size = %d\n\n", list.getSize());
		}
	}

	{
		// Forward traverse and pointer based element removal of a list of N integers
		SLL<int>	list;
		printf("list size = %d\n", list.getSize());
		void *userMemory[4]={0};
		int	listValueS=1;
		int &listNodeV=listValueS;
		for (int i=0; i<4; i++, listNodeV++) { userMemory[i]=list.addBack(listNodeV); }
		int size = list.getSize();
		printf("list size = %d\n", size);
		LinkedListIterator<int> iter1End=list.end();
		for (LinkedListIterator<int> iter1 = list.begin(); iter1 != iter1End; iter1++)
			printf("node = %p elem = %d\n", iter1, (*iter1));
		for (int j=0; j<size; j++)
		{
			printf("removing   : node = %p userMemory = %p\n", list.u2n(userMemory[j]), userMemory[j]);
			list.remove(userMemory[j]);
			for (LinkedListIterator<int> iter1 = list.begin(); iter1 != iter1End; iter1++) 
				printf("traversing : node = %p elem = %d\n", iter1, (*iter1));
			printf("status     : list size = %d\n\n", list.getSize());
		}
	}

	{
		// Concatination of 2 lists using moveBack()
		SLL<int>	list1;
		printf("list 1: size = %d\n", list1.getSize());
		int	listValueS=1;
		int &listNodeV=listValueS;
		for (int i=0; i<4; i++, listNodeV++) { list1.addBack(listNodeV); }
		printf("list 1: size = %d\n", list1.getSize());
		printf("Forward iteration: postfix increment\n");
		LinkedListIterator<int> iter1End=list1.end();
		for (LinkedListIterator<int> iter1 = list1.begin(); iter1 != iter1End; iter1++)
			printf("list 1: node = %p elem = %d\n", iter1, (*iter1));

		SLL<int>	list2;
		printf("list 2: size = %d\n", list2.getSize());
		listValueS=20;
		for (int i=0; i<8; i++, listNodeV++) { list2.addBack(listNodeV); }
		printf("list 2: size = %d\n", list2.getSize());
		printf("Forward iteration: postfix increment\n");
		LinkedListIterator<int> iter2End=list2.end();
		for (LinkedListIterator<int> iter1 = list2.begin(); iter1 != iter2End; iter1++)
			printf("list 2: node = %p elem = %d\n", iter1, (*iter1));

		printf("cat list 1 & 2\n");
		list1.moveBack(list2);
		printf("list 1: size = %d\n", list1.getSize());
		printf("Forward iteration: postfix increment\n");
		for (LinkedListIterator<int> iter1 = list1.begin(); iter1 != iter1End; iter1++)
			printf("list 1: node = %p elem = %d\n", iter1, (*iter1));
	}

	{
		// Removal of list elements using removeBack()
		SLL<int>	list;
		printf("list size = %d\n", list.getSize());
		int	listValueS=1;
		int &listNodeV=listValueS;
		for (int i=0; i<4; i++, listNodeV++) { list.addBack(listNodeV); }
		printf("list size = %d\n", list.getSize());
		printf("Forward iteration: postfix increment\n");
		LinkedListIterator<int> iter1End=list.end();
		for (LinkedListIterator<int> iter1 = list.begin(); iter1 != iter1End; iter1++)
			printf("node = %p elem = %d\n", iter1, (*iter1));
		printf("Reverse iteration: postfix decrement\n");
		LinkedListIterator<int> iter2End=list.rbegin();
		for (LinkedListIterator<int> iter2 = list.rend(); iter2 != iter2End; iter2--)
			printf("node = %p elem = %d\n", iter2, (*iter2));
		int size = list.getSize();
		for (int j=0; j<size; j++) list.removeBack();
		printf("list size = %d\n\n", list.getSize());
	}

	{
		SLL<char>	list;
		printf("list size = %d\n", list.getSize());
		char	listValueS=65;
		char	&listNodeV=listValueS;
		for (int i=0; i<4; i++, listNodeV++) { list.addBack(listNodeV); }
		printf("list.getSize = %d\n", list.getSize());
		printf("Forward iteration: prefix increment\n");
		LinkedListIterator<char> iter1End=list.end();
		for (LinkedListIterator<char> iter1 = list.begin(); iter1 != iter1End; ++iter1)
			printf("node = %p elem = %c\n", iter1, (*iter1));
		printf("Reverse iteration: prefix decrement\n");
		LinkedListIterator<char> iter2End=list.rbegin();
		for (LinkedListIterator<char> iter2 = list.rend(); iter2 != iter2End; --iter2)
			printf("node = %p elem = %c\n", iter2, (*iter2));
		int size = list.getSize();
		for (int j=0; j<size; j++) list.removeBack();
		printf("list size = %d\n\n", list.getSize());
	}

	{
		char *strings[] = {
					(char*)"Hello",
					(char*)"Goodbye",
					(char*)"Computer",
					(char*)"World",
				 };
		SLL<char*>	list;
		printf("list size = %d\n", list.getSize());
		for (int i=0; i<4; i++) list.addBack(strings[i]);
		printf("list.getSize = %d\n", list.getSize());
		printf("Forward iteration: prefix increment\n");
		LinkedListIterator<char*> iter1End=list.end();
		for (LinkedListIterator<char*> iter1 = list.begin(); iter1 != iter1End; ++iter1)
			printf("node = %p elem = %s\n", iter1, (*iter1));
		printf("Reverse iteration: prefix decrement\n");
		LinkedListIterator<char*> iter2End=list.rbegin();
		for (LinkedListIterator<char*> iter2 = list.rend(); iter2 != iter2End; --iter2)
			printf("node = %p elem = %s\n", iter2, (*iter2));
		int size = list.getSize();
		for (int j=0; j<size; j++) list.removeBack();
		printf("list size = %d\n\n", list.getSize());
	}
#endif

	return 0;
}

