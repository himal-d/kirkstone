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

#include "avlTree.h"

#ifdef	USE_AVLINT
int testavlint()
{
	int i=0, dupsCount=0;
	AVLTree<int,int> avlTree(false);
	AVLTreeInOrderIterator<int,int> end = avlTree.end();
	AVLNode<int, int>* node=0;

	//srand(time(0));
	//const int arrayLength=166;
	//int intArray[arrayLength]= {0,1,2,5,7,10,13,15,16,19,21,22,23,24,25,26,27,28,30,31,33,35,36,37,39,42,43,44,47,48,49,51,52,53,54,57,58,59,60,63,64,65,66,69,70,71,72,73,74,75,77,79,81,82,83,85,86,87,88,92,93,95,97,98,99,102,104,105,106,107,108,109,111,113,116,117,118,119,121,122,123,124,125,127,130,134,135,136,137,139,140,142,143,144,146,147,152,154,155,158,162,164,165,166,167,172,173,175,177,178,179,181,184,185,188,189,190,191,193,194,195,196,197,198,199,200,203,204,205,206,207,208,209,211,212,213,217,218,219,220,221,222,223,224,226,227,229,230,232,233,234,235,236,238,239,242,243,244,245,246,247,248,250,252,253,255};
	//srand(0);
	bool success=0;
	const int arrayLength=64;
	int intArray[arrayLength]= {38,39,246,133,151,21,173,29,210,148,221,196,118,25,57,49,241,173,181,88,240,147,151,50,25,43,209,192,253,22,142,78,72,155,11,245,59,73,168,99,93,222,63,223,109,104,180,135,154,170,205,220,247,193,68,129,41,8,27,64,98,56,48,78 };
	//int intArray[arrayLength]={0};
	//for (i=0; i<arrayLength; i++)
	//	intArray[i]=rand() % 256;
#if 0
	const int arrayLength=2;
	int intArray[arrayLength]={0,1};
	printf("Inserting duplicate elements test into the tree:\n");
	for (i=0; i<arrayLength; i++)
	{
		printf("key=%d insertion\n", intArray[i]);
		success=avlTree.Insert(intArray[i], node);
		printf("key=%d insertion status = %d : dataPtr = %p data = %d\n", intArray[i], success, node->GetDataPtr(), node->GetData());
		success=avlTree.Find(intArray[i], node);
		printf("key=%d lookup    status = %d : dataPtr = %p data = %d\n", intArray[i], success, node->GetDataPtr(), node->GetData());

		printf("key=%d insertion again\n", intArray[i]);
		success=avlTree.Insert(intArray[i], node);
		printf("key=%d insertion status = %d : dataPtr = %p data = %d\n", intArray[i], success, node->GetDataPtr(), node->GetData());
		success=avlTree.Find(intArray[i], node);
		printf("key=%d lookup    status = %d : dataPtr = %p data = %d\n", intArray[i], success, node->GetDataPtr(), node->GetData());
		printf("\n");
	}
#endif
	printf("Array: [size=%d]\n", arrayLength);
	for (i=0; i<arrayLength; i++)
		printf("%d ", intArray[i]);
	printf("\n");

	printf("Inserting Array elements into the tree:\n");
	int l=0;
	for (i=0; i<arrayLength; i++)
	{
		printf ("%d", intArray[i]);
		if (avlTree.Insert(intArray[i], intArray[i], node) == false) { printf("-"); ++l; } else { printf (" "); }

		int j=0;
		for (AVLTreeInOrderIterator<int,int> iter = avlTree.begin(); iter != end; ++j, ++iter);
		if (j - 1 != i - l && avlTree.isStrict() == true)
			printf("\ninsert error: iter = %d(%d) intArray[%d] = %d\n", j, i-l+1, i, intArray[i]);
	}
	int size=avlTree.getSize();
	if (l == 0)
	{
		if (avlTree.isStrict() == false)
		{
			int j=0;
			dupsCount=0;
			for (AVLTreeInOrderIterator<int,int> iter = avlTree.begin(); iter != end; ++j, ++iter)
				dupsCount+=iter.getNode()->GetCount()-1;
			printf("\nAll %d(+%d dups) elements have been inserted in the tree successfully!\n\n", size, dupsCount);
		}
		else
			printf("\nAll %d elements have been inserted in the tree successfully!\n\n", size);
	}
	else
		printf("\nThere were %d errors inserting elements in the tree of size = %d!\n\n", l, size);

	// Sort tree elements in ascending order
	int sortedArray[arrayLength];
	avlTree.Sort(true, sortedArray);
	printf("Sorted tree elements [size=%d] in ascending order: \n", size);
	for (i=0; i<size; i++)
		printf("%d ", sortedArray[i]);
	printf("\n");

	// Traverse the tree inorder
	printf("Traverse tree [size=%d] inorder: \n", size);
	i=0;
	end = avlTree.end();
	for (AVLTreeInOrderIterator<int,int> iter = avlTree.begin(); iter != end; ++i, ++iter)
		printf("%d ", (*iter));
	printf("\n");
	int mindata=0, maxdata=0;
	int keyMin=avlTree.Min(mindata);
	int keyMax=avlTree.Max(maxdata);
	printf("Number of traversed tree inorder elements = %d : min = %d(%d) : max = %d(%d)\n\n", i, keyMin, mindata, keyMax, maxdata);

	// Sort tree elements in descending order
	avlTree.Sort(false, sortedArray);
	printf("Sorted tree elements [size=%d] in descending order: \n", size);
	for (i=0; i<size; i++)
		printf("%d ", sortedArray[i]);
	printf("\n");

	// Traverse the tree inorder reverse 
	printf("Traverse tree [size=%d] reverse inorder: \n", size);
	i=0;
	end = avlTree.rbegin();
	for (AVLTreeInOrderIterator<int,int> iter = avlTree.rend(); iter != end; ++i, --iter)
		printf("%d ", (*iter));
	printf("\n");
	printf("Number of traversed tree inorder elements in reverse = %d : min = %d(%d) : max = %d(%d)\n\n", i, avlTree.Min(mindata), mindata, avlTree.Max(maxdata), maxdata);

	// Find all intArray[] elements
	int j=0;
	dupsCount=0;
	for (i=0; i<arrayLength; i++)
		if (avlTree.Find(intArray[i], node) == false) 
			j++;
		else
			dupsCount+=node->GetCount()-1;
	printf("Found %d elements including %d dups in the tree of size = %d\n\n", arrayLength-j, dupsCount/2, avlTree.getSize());

	// Find an intArray[arrayLength/2] element
	int key=intArray[1];
	printf("Finding an intArray[1]=%d element in the tree:\n", intArray[1]);
	if (avlTree.Find(intArray[1], node) == true)
		printf("Found key=%d with value = %d in the tree\n\n", key, node->GetData());
	else
		printf("Cannot find key=%d in the tree\n\n", key);

	printf("Inserting duplicate elements into the tree:\n");
	for (i=0; i<2; i++)
	{
		printf("key=%d insertion\n", intArray[i]);
		success=avlTree.Insert(intArray[i], node);
		printf("key=%d insertion status = %d : dataPtr = %p data = %d count = %d\n", intArray[i], success, node->GetDataPtr(), node->GetData(), node->GetCount());
		success=avlTree.Find(intArray[i], node);
		printf("key=%d lookup    status = %d : dataPtr = %p data = %d count = %d\n", intArray[i], success, node->GetDataPtr(), node->GetData(), node->GetCount());

		printf("key=%d insertion again\n", intArray[i]);
		success=avlTree.Insert(intArray[i], node);
		printf("key=%d insertion status = %d : dataPtr = %p data = %d count = %d\n", intArray[i], success, node->GetDataPtr(), node->GetData(), node->GetCount());
		success=avlTree.Find(intArray[i], node);
		printf("key=%d lookup    status = %d : dataPtr = %p data = %d count = %d\n", intArray[i], success, node->GetDataPtr(), node->GetData(), node->GetCount());
		printf("\n");
	}

	printf("Deleting  duplicate elements from the tree:\n");
	for (i=0; i<2; i++)
	{
		printf("key=%d deletion\n", intArray[i]);
		success=avlTree.Delete(intArray[i]);
		printf("key=%d deletion status = %d\n", intArray[i], success);
		success=avlTree.Find(intArray[i], node);
		printf("key=%d lookup   status = %d : dataPtr = %p data = %d count = %d\n", intArray[i], success, node->GetDataPtr(), node->GetData(), node->GetCount());

		printf("key=%d deletion again\n", intArray[i]);
		success=avlTree.Delete(intArray[i]);
		printf("key=%d deletion status = %d\n", intArray[i], success);
		success=avlTree.Find(intArray[i], node);
		printf("key=%d lookup   status = %d : dataPtr = %p data = %d count = %d\n", intArray[i], success, node->GetDataPtr(), node->GetData(), node->GetCount());
		printf("\n");
	}

	// Delete first array1Length/2 elemenets of Array1 from the tree
	printf("Delete 1st %d Array elements from the tree [size=%d] via Delete(element):\n", arrayLength/2, avlTree.getSize());
	for (i=0; i<arrayLength/2; i++) avlTree.Delete(intArray[i]);
	// Sort the result in ascending order
	avlTree.Sort(true, sortedArray);
	size=avlTree.getSize();
	printf("Sorted tree elements [size=%d] in ascending order: \n", size);
	for (i=0; i<size; i++) printf("%d ", sortedArray[i]);
	printf("\n");
	// Traverse the tree inorder
	printf("Traverse tree [size=%d] inorder: \n", size);
	i=0;
	end = avlTree.end();
	for (AVLTreeInOrderIterator<int,int> iter = avlTree.begin(); iter != end; ++i, ++iter)
		printf("%d ", (*iter));
	printf("\n");
	printf("Number of traversed tree inorder elements = %d : min = %d(%d) : max = %d(%d)\n\n", i, avlTree.Min(mindata), mindata, avlTree.Max(maxdata), maxdata);

	try {
		printf("tree: min = %d\n", avlTree.Min(mindata));
		printf("tree: max = %d\n", avlTree.Max(maxdata));
	}
	catch (char *message) {
		printf("tree.MinMax exception: %s: Min/Max cannot be determined\n", message);
	}

	printf("\nEnd of testavl tests!\n\n");

	return 0;
}
#endif //USE_AVLINT

