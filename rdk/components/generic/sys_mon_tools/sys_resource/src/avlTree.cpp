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
#ifdef USE_AVLBT
#include "backtrace.h"
#endif
#ifdef	USE_CMAS
#include "cmastats.h"
#endif
#include "cmaNode.h"

#include "zmalloc.h"

#define DEBUG_AVLT_ENABLE	0

#if DEBUG_AVLT_ENABLE
#define	DBG_AVLT(x)	x
#else
#define	DBG_AVLT(x)
#endif

template <class T1, class T2>
AVLTree<T1, T2>::AVLTree(const bool _strict) : root (0), size(0), strict(_strict)
{
	DBG_AVLT(printf("AVLTree<T1, T2>::AVLTree:     this = %p strict = %d\n", this, strict));
}

template <class T1, class T2>
AVLTree<T1, T2>::~AVLTree()
{
	DBG_AVLT(printf("AVLTree<T1, T2>::~AVLTree B:  this = %p strict = %d size = %d\n", this, strict, size));
	Destroy(root);
	DBG_AVLT(printf("AVLTree<T1, T2>::~AVLTree E:  this = %p strict = %d size = %d\n", this, strict, size));
}

template <class T1, class T2>
AVLTree<T1, T2>::AVLTree(const AVLTree& rhs) : size(rhs.size), strict(rhs.strict)
{
	DBG_AVLT(printf("AVLTree<T1, T2>::AVLTreeCCB:  rhs  = %p strict = %d size = %d\n", &rhs, rhs.strict, rhs.size));
	root = rhs.root->Clone(rhs.root);
	DBG_AVLT(printf("AVLTree<T1, T2>::AVLTreeCCE:  this = %p strict = %d size = %d\n", this, strict, size));
	// Fix me:
	root->SetParent(root, root);
}

template <class T1, class T2>
AVLTree<T1, T2> &AVLTree<T1, T2>::operator= (const AVLTree<T1, T2> &rhs)
{
	DBG_AVLT(printf("AVLTree<T1, T2>::operator= B: rhs  = %p strict = %d size = %d\n", &rhs, rhs.strict, rhs.size));
	DBG_AVLT(printf("AVLTree<T1, T2>::operator= B: this = %p strict = %d size = %d\n", this, strict, size));
	if (this == &rhs)
		return *this;

	Destroy(root);

	root=rhs.root;
	size=rhs.size;

	DBG_AVLT(printf("AVLTree<T1, T2>::operator= E: this = %p strict = %d size = %d\n", this, strict, size));
	return *this;
}

template <class T1, class T2>
void AVLTree<T1, T2>::Destroy()
{
	DBG_AVLT(printf("AVLTree<T1, T2>::Destroy   B:  this = %p strict = %d size = %d\n", this, strict, size));
	Destroy(root);
	DBG_AVLT(printf("AVLTree<T1, T2>::Destroy   E:  this = %p strict = %d size = %d\n", this, strict, size));
}

template <class T1, class T2>
void AVLTree<T1, T2>::Destroy(AVLNode<T1, T2>* &node)
{
	if (node)
	{
		Destroy(node->node[LEFT]);
		Destroy(node->node[RIGHT]);
#if DEBUG_AVLT_ENABLE
		if (node)
			printf("AVLTree<T1, T2>::Destroy  B:  this = %p deleting node = %p key = %d strict = %d size = %d count = %d\n", this, node, node->GetKey(), strict, size, node->count);
		else
			printf("AVLTree<T1, T2>::Destroy  B:  this = %p deleted  node = %p strict = %d size = %d\n", this, node, strict, size);
#endif
		delete node;
		--size;
		DBG_AVLT(printf("AVLTree<T1, T2>::Destroy  E:  this = %p deleted  node = %p strict = %d size = %d\n", this, node, strict, size));
		node=0;
	}
}

template <class T1, class T2>
void* AVLTree<T1, T2>::operator new (size_t size)
{
	return zmalloc(size);
}

template <class T1, class T2>
void AVLTree<T1, T2>::operator delete (void *p)
{
	zfree(p);
}

template <class T1, class T2>
bool AVLTree<T1, T2>::Insert(T1 key)
{
	AVLNode<T1, T2>* node=0;
	return Insert(key, node);
}

template <class T1, class T2>
bool AVLTree<T1, T2>::Insert(T1 key, AVLNode<T1, T2>*& node)
{
	int	heightChange=0;
	if (root == NULL)
	{
		root = node = new AVLNode<T1, T2>(key);
		size = 1;
		return true;
	}
	else if (root->Insert(key, root, heightChange, node))
	{
		++size;
		return true;
	}
	else if (strict == false)
	{
		++node->count;
		return true;
	}

	return false;
}

template <class T1, class T2>
bool AVLTree<T1, T2>::Insert(T1 key, T2 &data, AVLNode<T1, T2>*& node)
{
	int	heightChange=0;
	if (root == NULL)
	{
		root = node = new AVLNode<T1, T2>(key, data);
		size = 1;
		return true;
	}
	else if (root->Insert(key, data, root, heightChange, node))
	{
		++size;
		return true;
	}
	else if (strict == false)
	{
		++node->count;
		return true;
	}

	return false;
}

template <class T1, class T2>
bool AVLTree<T1, T2>::Delete(T1 key)
{
	int	heightChange=0;
	T1	removedNode=0;

	if (root == NULL)
		return false;
	else if (root->Delete(key, root, heightChange, removedNode))
	{
		--size;
		return true;
	}
	return false;
}

template <class T1, class T2>
bool AVLTree<T1, T2>::Delete(bool maximum)
{
	int	heightChange=0;
	T1	removedNode=0, key=0;

	if (root == NULL)
		return false;
	else if (root->Delete(key, root, heightChange, removedNode, (maximum == true ? MAXIMUM : MINIMUM)))
	{
		--size;
		return true;
	}
	return false;
}

template <class T1, class T2>
bool AVLTree<T1, T2>::Sort(bool asc, T1 *sortedArray)
{
	if (root == NULL)
		return false;

	int	   index=0;
	return root->Sort(asc, sortedArray, index);
}

template <class T1, class T2>
bool AVLTree<T1, T2>::Find(T1 key) const
{
	if (root == NULL)
		return false;

	const AVLNode<T1, T2>* node=0;
	return root->Find(key, node);
}

template <class T1, class T2>
bool AVLTree<T1, T2>::Find(T1 key, AVLNode<T1, T2>*& node)
{
	if (root == NULL)
		return false;

	return root->Find(key, node);
}
#if 0
template <class T1, class T2>
void AVLTree<T1, T2>::Intersect(AVLTree<T1,T2> &other, AVLTree<T1,T2> &result)
{
	AVLTreeInOrderIterator<T1,T2> thisIter = begin();
	AVLTreeInOrderIterator<T1,T2> thisEnd = end();
	AVLTreeInOrderIterator<T1,T2> otherIter = other.begin();
	AVLTreeInOrderIterator<T1,T2> otherEnd = other.end();
	AVLTreeInOrderIterator<T1,T2> resultIter = result.begin();
	T1 prev;
	while (thisIter != thisEnd && otherIter != otherEnd)
	{
		if (*thisIter == *otherIter)
		{
			if (resultIter == result.begin() || *thisIter != prev)
			{
				prev=*thisIter;
				AVLNode<T1, T2>* node=0;
				T2 data = thisIter.getNode()->GetData() - otherIter.getNode()->GetData();
				result.Insert(*thisIter, data, node);
				++resultIter;
			}
			++thisIter;
			++otherIter;
		}
		else if (*thisIter > *otherIter)
		{
			++otherIter;
		}
		else
		{
			++thisIter;
		}
	}
}
#endif
template <class T1, class T2>
T1 AVLTree<T1, T2>::Min(T2& data) const
{
	if (root == NULL)
		throw "AVLTree is empty";

	const AVLNode<T1, T2>* node=0;
	root->Find(LEFT, node);
	data=node->GetData();
	return node->GetKey();
}

template <class T1, class T2>
T1 AVLTree<T1, T2>::Max(T2& data) const
{
	if (root == NULL)
		throw "AVLTree is empty";

	const AVLNode<T1, T2>* node=0;
	root->Find(RIGHT, node);
	data=node->GetData();
	return node->GetKey();
}

#ifdef	USE_AVLINT
template class AVLTree<int, int>;
#if 0
template <>
void AVLTree<int,int>::Intersect(AVLTree<int,int> &other, AVLTree<int,int> &result)
{
	AVLTreeInOrderIterator<int,int> thisIter = begin();
	AVLTreeInOrderIterator<int,int> thisEnd = end();
	AVLTreeInOrderIterator<int,int> otherIter = other.begin();
	AVLTreeInOrderIterator<int,int> otherEnd = other.end();
	AVLTreeInOrderIterator<int,int> resultIter = result.begin();
	int prev;
	while (thisIter != thisEnd && otherIter != otherEnd)
	{
		if (*thisIter == *otherIter)
		{
			if ((resultIter == result.begin()) || (*thisIter != prev))
			{
				prev=*thisIter;
				AVLNode<int,int>* node=0;
				int data = thisIter.getNode()->GetData() - otherIter.getNode()->GetData();
				result.Insert(*thisIter, data, node);
				++resultIter;
			}
			++thisIter;
			++otherIter;
		}
		else if (*thisIter > *otherIter)
		{
			++otherIter;
		}
		else
		{
			++thisIter;
		}
	}
}
#endif
#endif

#ifdef USE_AVLBT
template class AVLTree<int, Backtrace>;
#endif

#ifdef	USE_CMAS
template class AVLTree<int, CmaStats>;
#endif

template class AVLTree<int, CmaNode>;

