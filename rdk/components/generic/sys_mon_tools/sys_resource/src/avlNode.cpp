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

#include "avlNode.h"
#ifdef USE_AVLBT
#include "backtrace.h"
#endif
#ifdef	USE_CMAS
#include "cmastats.h"
#endif
#include "cmaNode.h"

#include "zmalloc.h"

#define DEBUG_AVLN_ENABLE	0

#if DEBUG_AVLN_ENABLE
#define	DBG_AVLN(x)	x
#else
#define	DBG_AVLN(x)
#endif

static inline int min(int a, int b) { return  (a < b) ? a : b; }
static inline int max(int a, int b) { return  (a > b) ? a : b; }

template <class T1, class T2>
void* AVLNode<T1, T2>::operator new (size_t size)
{
	return zmalloc(size);
}

template <class T1, class T2>
void AVLNode<T1, T2>::operator delete (void *p)
{
	zfree(p);
}

template <class T1, class T2>
AVLNode<T1, T2>::AVLNode(T1 k) : key(k), parent(0), balance(0), count(1)
{
	node[LEFT] = node[RIGHT] = NULL;
}

template <class T1, class T2>
AVLNode<T1, T2>::AVLNode(T1 k, T2& v) : key(k), data(v), parent(0), balance(0), count(1)
{
	node[LEFT] = node[RIGHT] = NULL;
}

template <class T1, class T2>
AVLNode<T1, T2>::AVLNode(AVLNode<T1, T2>* left, AVLNode<T1, T2>* right, T1 k, T2& v, AVLNode<T1, T2>* parent, int b, int c) : 
	key(k),data(v), parent(0), balance(b), count(c)
{
	node[LEFT]=left; node[RIGHT]=right;
}

template <class T1, class T2>
AVLNode<T1, T2>* AVLNode<T1, T2>::Clone(AVLNode<T1, T2>* node)
{
	if (node)
	{
		AVLNode<T1, T2>* left=Clone(node->node[LEFT]);
		AVLNode<T1, T2>* right=Clone(node->node[RIGHT]);
		DBG_AVLN(printf("AVLNode<T1, T2>::Clone:       this = %p cloning  node = %p : left = %p right = %p\n", this, node, left, right));
		return new AVLNode<T1, T2>(left, right, node->key, node->data, 0, node->balance, node->count);
	}
	else
		return NULL;
}

template <class T1, class T2>
void AVLNode<T1, T2>::SetParent(AVLNode<T1, T2>* node, AVLNode<T1, T2>* parent)
{
	if (node)
	{
		SetParent(node->node[LEFT], node);
		SetParent(node->node[RIGHT], node);
		if (node != parent)
		{
			node->parent=parent;
			DBG_AVLN(printf("AVLNode<T1, T2>::SetParent:   this = %p (%d) node = %p (%d) parent = %p (%d)\n", this, key, node, node->key, parent, parent->key));
		}
	}
}

template <class T1, class T2>
AVLNode<T1, T2>::~AVLNode(void)
{
#if DEBUG_AVLN_ENABLE
	if (node[LEFT])
		printf("AVLNode<T1, T2>::~AVLNode:    this = %p deleting node=%p: data = %d\n", this, node[LEFT], node[LEFT]->data);
	else
		printf("AVLNode<T1, T2>::~AVLNode:    this = %p deleting node=%p\n", this, node[LEFT]);
#endif
	delete  node[LEFT];
	node[LEFT] = 0;
#if DEBUG_AVLN_ENABLE
	if (node[RIGHT])
		printf("AVLNode<T1, T2>::~AVLNode:    this = %p deleting node=%p: data = %d\n", this, node[RIGHT], node[RIGHT]->data);
	else
		printf("AVLNode<T1, T2>::~AVLNode:    this = %p deleting node=%p\n", this, node[LEFT]);
#endif
	delete  node[RIGHT];
	node[RIGHT] = 0;
}

template <class T1, class T2>
int AVLNode<T1, T2>::RotateOnce(AVLNode<T1, T2> *&root, dir_t dir)
{
	dir_t  oppDir = Opposite(dir);
	int  heightChange = (root->node[oppDir]->balance == 0) ? HEIGHT_NOCHANGE : HEIGHT_CHANGE;

	// setup the rotation nodes
	AVLNode<T1, T2>	*oldRoot = root;
	root = oldRoot->node[oppDir];

	// update parent links
	root->parent = oldRoot->parent;
	oldRoot->parent = root;

	if (root->node[dir] != NULL)
	root->node[dir]->parent = oldRoot;

	// do the rotation
	oldRoot->node[oppDir] = root->node[dir];
	root->node[dir] = oldRoot;

	 // update balances
	oldRoot->balance = -((dir == LEFT) ? --(root->balance) : ++(root->balance));
	return  heightChange;
}

template <class T1, class T2>
int AVLNode<T1, T2>::RotateTwice(AVLNode<T1, T2> *&root, dir_t dir)
{
	dir_t  oppDir = Opposite(dir);
	AVLNode<T1, T2> *oldRoot = root;
	AVLNode<T1, T2> *oldRootOppDirNode = root->node[oppDir];

	 // new root
	root = oldRootOppDirNode->node[dir];
	 // new root direction exchange with its grandparent's direction
	oldRoot->node[oppDir] = root->node[dir];
	root->node[dir] = oldRoot;

	 // new root opposite direction exchange with its parent's opposite direction
	oldRootOppDirNode->node[dir] = root->node[oppDir];
	root->node[oppDir] = oldRootOppDirNode;

	// update parent links
	root->parent = oldRoot->parent;
	oldRoot->parent = oldRootOppDirNode->parent = root;

	if (oldRootOppDirNode->node[dir]) oldRootOppDirNode->node[dir]->parent=root->node[oppDir];
	if (root->node[dir]->node[oppDir]) root->node[dir]->node[oppDir]->parent=root->node[dir];

	 // update balances
	root->node[LEFT]->balance  = -max(root->balance, 0);
	root->node[RIGHT]->balance = -min(root->balance, 0);
	root->balance = 0;

	return  HEIGHT_CHANGE;
}

template <class T1, class T2>
int AVLNode<T1, T2>::ReBalance(AVLNode<T1, T2> *&root) 
{
	int  heightChange = HEIGHT_NOCHANGE;

	if (RightHeavy(root->balance)) 
	{
		// Left rotation:
		if (root->node[RIGHT]->balance  ==  LEFT_HEAVY) 
		{
			// Perform double left rotation
			heightChange = RotateTwice(root, LEFT);
		} 
		else 
		{
			// Perform single left rotation
			heightChange = RotateOnce(root, LEFT);
		}
	}
	else if (LeftHeavy(root->balance)) 
	{
		// Right rotation:
		if (root->node[LEFT]->balance  ==  RIGHT_HEAVY) 
		{
			// Perform double right rotation
			heightChange = RotateTwice(root, RIGHT);
		} 
		else 
		{
			// Perform single right rotation
			heightChange = RotateOnce(root, RIGHT);
		}
	} 

	return  heightChange;
}

template <class T1, class T2>
bool AVLNode<T1, T2>::Insert(T1 key, AVLNode<T1, T2> *&root, int &heightChange, AVLNode<T1, T2> *&node)
{
	// Insert new node
	if (root == NULL) 
	{
		root = node = new AVLNode<T1, T2>(key);
		heightChange =  HEIGHT_CHANGE;
		return  true;
	}

	// Compare data and determine which direction to insert
	if (key == root->key)
	{
		node = root;
		return  false;
	}

	dir_t dir = key < root->key ? LEFT : RIGHT;
	if (Insert(key, root->node[dir], heightChange, node) == false)
		return  false;

	root->balance += dir == LEFT ? -heightChange : heightChange;
	root->node[dir]->parent = root;

	// Rebalance the tree and update the heightChange
	heightChange = (heightChange && root->balance) ? (1 - ReBalance(root)) : HEIGHT_NOCHANGE;

	return  true;
}

template <class T1, class T2>
bool AVLNode<T1, T2>::Insert(T1 key, T2& data, AVLNode<T1, T2> *&root, int &heightChange, AVLNode<T1, T2> *&node)
{
	// Insert new node
	if (root == NULL) 
	{
		root = node = new AVLNode<T1, T2>(key, data);
		heightChange =  HEIGHT_CHANGE;
		return  true;
	}

	// Compare data and determine which direction to insert
	if (key == root->key)
	{
		node = root;
		return  false;
	}

	dir_t dir = key < root->key ? LEFT : RIGHT;
	if (Insert(key, data, root->node[dir], heightChange, node) == false)  
		return  false;

	root->balance += dir == LEFT ? -heightChange : heightChange;
	root->node[dir]->parent = root;

	// Rebalance the tree and update the heightChange
	heightChange = (heightChange && root->balance) ? (1 - ReBalance(root)) : HEIGHT_NOCHANGE;

	return  true;
}

template <class T1, class T2>
bool AVLNode<T1, T2>::Found(T1 key, avl_find_mode_t mode) const
{
	switch (mode)
	{
		case EQUAL:
			return  key == this->key ? true : false;
		case MINIMUM:
			return  (node[LEFT] == NULL) ? true : false;
		case MAXIMUM:
			return  (node[RIGHT] == NULL) ? true : false;
	}

	return false;
}

template <class T1, class T2>
bool AVLNode<T1, T2>::Delete(T1 key, AVLNode<T1, T2> *&root, int &heightChange, T1& removedNode, avl_find_mode_t mode)
{
	 // Check if the root is empty
	if (root == NULL) 
	{	// Data not found
		heightChange = HEIGHT_NOCHANGE;
		return false;
	}

	int heightDecrease=0;
	// Compare data and determine which direction to search
	if (root->Found(key, mode) == false)
	{
		dir_t dir = mode == EQUAL ? ((key < root->key ? LEFT : RIGHT)) : (mode == MAXIMUM ? RIGHT : LEFT);
		if (Delete(key, root->node[dir], heightChange, removedNode, mode) == false)  
			return  false;						// not found

		heightDecrease = dir == LEFT ? -heightChange : heightChange; 	// decrease balance factor
	}
	else
	{   	// This node data
		if (--root->count > 0)
		{
			heightChange = HEIGHT_NOCHANGE;
			return true;
		}

		removedNode = root->key;
		if ((root->node[LEFT] == NULL) && (root->node[RIGHT] == NULL)) 
		{	// Delete leaf node
			delete  root;
			root = NULL;
			heightChange = HEIGHT_CHANGE;
			return true;
		} 
		else if ((root->node[LEFT] == NULL) || (root->node[RIGHT] == NULL)) 
		{	// Node has the only child
			AVLNode<T1, T2> * nodeToDelete = root;
			root = root->node[(root->node[RIGHT]) ? RIGHT : LEFT];
			root->parent=nodeToDelete->parent;
			nodeToDelete->node[LEFT] = nodeToDelete->node[RIGHT] = parent = NULL;
			delete  nodeToDelete;
			heightChange = HEIGHT_CHANGE;
			return true;
		} 
		else 
		{	// Node has 2 children: 
			// Replace the node to be removed w/ its successor [maximum on the leftmost side] on the right.
			Delete(key, root->node[RIGHT], heightDecrease, removedNode, MINIMUM);
			// Replace the node to be removed w/ its predecessor [minimum on the rightmost side] on the left
			//Delete(data, root->node[LEFT], heightDecrease, removedNode, MAXIMUM);
			root->key = removedNode;
		}
	}

	// Adjust the balances
	root->balance -= heightDecrease;		// update balance factor 
	if (heightDecrease)
	{
		if (root->balance) 
			heightChange = ReBalance(root);	// rebalance and see if height changed
		else 
			heightChange = HEIGHT_CHANGE;	// balanced because subtree decreased
	} 
	else 
	{
		heightChange = HEIGHT_NOCHANGE;
	}

	return true;
}

template <class T1, class T2>
bool AVLNode<T1, T2>::Find(T1 key, const AVLNode<T1, T2> *&root) const
{
	if (key == this->key)
	{
		root = this;
		return true;
	}
	else
	{
		dir_t dir = key < this->key ? LEFT : RIGHT;
		if (node[dir] != NULL)
			return node[dir]->Find(key, root);
		else
			return false;
	}
}

template <class T1, class T2>
bool AVLNode<T1, T2>::Find(T1 key, AVLNode<T1, T2> *&root)
{
	if (key == this->key)
	{
		root = this;
		return true;
	}
	else
	{
		dir_t dir = key < this->key ? LEFT : RIGHT;
		if (node[dir] != NULL)
			return node[dir]->Find(key, root);
		else
			return false;
	}
}

template <class T1, class T2>
bool AVLNode<T1, T2>::Find(dir_t dir, const AVLNode<T1, T2> *&root) const
{
	if (node[dir] == NULL)
	{
		root = this;
		return true;
	}
	else
		return node[dir]->Find(dir, root);
}

template <class T1, class T2>
AVLNode<T1, T2>* AVLNode<T1, T2>::Find(dir_t dir)
{
	AVLNode<T1, T2>* node = this;
	while (node->node[dir] != NULL)
		node = node->node[dir];
	return node;
}

template <class T1, class T2>
AVLNode<T1, T2>* AVLNode<T1, T2>::Find(dir_t dir, AVLNode<T1, T2>* root)
{
	if (root == NULL)
		return NULL;

	if (root->node[1-dir] != NULL)
	{
		root = root->node[1-dir];
		while (root->node[dir] != NULL)
			root = root->node[dir];
	}
	else
	{
		AVLNode<T1, T2>* node=NULL;
		do {
			node = root;
			root = root->parent;
		} while (root != NULL && node != root->node[dir]);
	}

	return root;
}

template <class T1, class T2>
bool AVLNode<T1, T2>::Sort(bool asc, T1 *sortedArray, int &index) const
{
	dir_t dir = asc == true ? LEFT : RIGHT;
	if (node[dir] != NULL)
		node[dir]->Sort(asc, sortedArray, index);

	sortedArray[index++] = key;

	dir = (dir_t)(1 - dir);
	if (node[dir] != NULL)
		node[dir]->Sort(asc, sortedArray, index);

	return true;
}

#ifdef USE_AVLINT
template <>
AVLNode<int, int>::AVLNode(int k) : key(k), data(0), parent(0), balance(0), count(1)
{
	node[LEFT] = node[RIGHT] = NULL;
}

template class AVLNode<int, int>;
#endif

#ifdef USE_AVLBT
template class AVLNode<int, Backtrace>;
#endif

#ifdef	USE_CMAS
template class AVLNode<int, CmaStats>;
#endif

template class AVLNode<int, CmaNode>;

