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

int printArray(int *intArray, int arrayLength)
{
	printf("Array: [size=%d]\n", arrayLength);
	for (int i=0; i<arrayLength; i++) printf("%d ", intArray[i]); printf("\n");
	return 0;
}

int insertInArray(AVLTree<int,int> &avlTree, int *intArray, int arrayLength)
{
	printf("Inserting Array elements into the tree:\n");

	int l=0;
	int dupsCount=0;
	AVLNode<int, int>* node=0;
	AVLTreeInOrderIterator<int,int> end = avlTree.end();

	for (int i=0; i<arrayLength; i++)
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

	return 0;
}

int	sortAndPrint(AVLTree<int,int> &avlTree, int arrayLength, bool asc)
{
	// Sort tree elements in ascending order
	int *sortedArray = new int [arrayLength];
	int size=avlTree.getSize();
	avlTree.Sort(asc, sortedArray);
	printf("Sorted tree elements [size=%d] in %s order: \n", size, (asc == true ? "ascending" : "descinding"));
	for (int i=0; i<size; i++) printf("%d ", sortedArray[i]);
	printf("\n");

	delete [] sortedArray;
	return 0;
}

int traverseAndPrint(AVLTree<int,int> &avlTree, bool forward)
{
	// Traverse the tree inorder
	int size=avlTree.getSize();
	printf("Traverse tree [size=%d] inorder: forward = %s\n", size, (forward == true ? "true" : "false"));
	int i=0;
	if (forward)
	{
		AVLTreeInOrderIterator<int,int> end=avlTree.end();
		for (AVLTreeInOrderIterator<int,int> iter = avlTree.begin(); iter != end; ++i, ++iter) printf("%d ", (*iter));
	}
	else
	{
		AVLTreeInOrderIterator<int,int> end=avlTree.rbegin();
		for (AVLTreeInOrderIterator<int,int> iter = avlTree.rend(); iter != end; ++i, --iter) printf("%d ", (*iter));
	}
	printf("\n");

	printf("Number of traversed tree inorder elements = %d\n", i);
	return 0;
}

int minmaxAndPrint(AVLTree<int,int> &avlTree)
{
	int mindata=0, maxdata=0;
	int keyMin=avlTree.Min(mindata);
	int keyMax=avlTree.Max(maxdata);
	printf("min = %d(%d) : max = %d(%d)\n", keyMin, mindata, keyMax, maxdata);
	return 0;
}

int avlintTests(int testCase, AVLTree<int,int> &avlTree, int *intArray, int arrayLength)
{
	printf("Test case: %d\n", testCase);
	printArray(intArray, arrayLength);
	insertInArray(avlTree, intArray, arrayLength);
	sortAndPrint(avlTree, arrayLength, true);
	traverseAndPrint(avlTree, true);
	sortAndPrint(avlTree, arrayLength, false);
	traverseAndPrint(avlTree, false);
	minmaxAndPrint(avlTree);
	return 0;
}

int avlintTests(int testCase, AVLTree<int,int> &avlTree, int arrayLength)
{
	printf("Test case: %d\n", testCase);
	sortAndPrint(avlTree, arrayLength, true);
	traverseAndPrint(avlTree, true);
	sortAndPrint(avlTree, arrayLength, false);
	traverseAndPrint(avlTree, false);
	minmaxAndPrint(avlTree);
	return 0;
}

int testavlint2()
{
{
	// Test case #1
	int testCase=1;

	AVLTree<int,int> avlTree(false);
	const int arrayLength=8;
	int intArray[arrayLength]= {50,20,70,30,10,90,60,55};
	avlintTests(testCase, avlTree, intArray, arrayLength);

	printf("Test a clone\n");
	AVLTree<int,int> avlTreeClone(avlTree);
	avlintTests(testCase, avlTreeClone, arrayLength);
}
{
	// Test case #2
	int testCase=2;

	AVLTree<int,int> avlTree(false);
	const int arrayLength=9;
	int intArray[arrayLength]= {50,20,70,30,10,90,60,55,28};
	avlintTests(testCase, avlTree, intArray, arrayLength);

	printf("Test a clone\n");
	AVLTree<int,int> avlTreeClone(avlTree);
	avlintTests(testCase, avlTreeClone, arrayLength);
}
{
	// Test case #3
	int testCase=3;

	AVLTree<int,int> avlTree(false);
	const int arrayLength=9;
	int intArray[arrayLength]= {50,20,70,10,90,60,80,98,93};
	avlintTests(testCase, avlTree, intArray, arrayLength);

	printf("Test a clone\n");
	AVLTree<int,int> avlTreeClone(avlTree);
	avlintTests(testCase, avlTreeClone, arrayLength);
}
{
	// Test case #4
	int testCase=4;

	AVLTree<int,int> avlTree(false);
	const int arrayLength=12;
	int intArray[arrayLength]= {50,20,70,10,30,90,60,5,15,25,35,13};
	avlintTests(testCase, avlTree, intArray, arrayLength);

	printf("Test a clone\n");
	AVLTree<int,int> avlTreeClone(avlTree);
	avlintTests(testCase, avlTreeClone, arrayLength);
}
{
	// Test case #5
	int testCase=5;

	AVLTree<int,int> avlTree(false);
	const int arrayLength=12;
	int intArray[arrayLength]= {50,20,90,10,40,70,100,5,15,30,45,35};
	avlintTests(testCase, avlTree, intArray, arrayLength);

	printf("Test a clone\n");
	AVLTree<int,int> avlTreeClone(avlTree);
	avlintTests(testCase, avlTreeClone, arrayLength);
}
{
	// Test case #6
	int testCase=6;

	AVLTree<int,int> avlTree(false);
	const int arrayLength=6;
	int intArray[arrayLength]= {50,20,80,70,90,75};
	avlintTests(testCase, avlTree, intArray, arrayLength);

	printf("Test a clone\n");
	AVLTree<int,int> avlTreeClone(avlTree);
	avlintTests(testCase, avlTreeClone, arrayLength);
}

	return 0;
}
#endif //USE_AVLINT
