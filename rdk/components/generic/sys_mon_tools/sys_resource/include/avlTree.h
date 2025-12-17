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
#ifndef	AVLTREE_H
#define AVLTREE_H

#include "avlNode.h"

template <class T1, class T2>
class AVLTreeInOrderIterator 
{
	friend class AVLTree<T1, T2>;

public:
	bool operator == (AVLTreeInOrderIterator<T1, T2> &iter) const { return mNode == iter.mNode; }
	bool operator != (AVLTreeInOrderIterator<T1, T2> &iter) const { return mNode != iter.mNode; }
	AVLTreeInOrderIterator& operator++ () { if (mNode) mNode = mNode->Find(LEFT,  mNode); return *this; }				// prefix
	AVLTreeInOrderIterator& operator-- () { if (mNode) mNode = mNode->Find(RIGHT, mNode); return *this; }				// prefix
	const AVLTreeInOrderIterator operator++ (int) { AVLTreeInOrderIterator<T1, T2> iter = *this; *this=++*this; return iter; }	// postfix
	const AVLTreeInOrderIterator operator-- (int) { AVLTreeInOrderIterator<T1, T2> iter = *this; *this=--*this; return iter; }	// postfix
	T1 operator* () { assert(mNode); return mNode->GetKey(); }
	AVLNode<T1, T2>* getNode() { return mNode; }

private:
	AVLTreeInOrderIterator(AVLNode<T1, T2> *p) : mNode(p) { }
	AVLNode<T1, T2>*	mNode;
};

template <class T1, class T2>
class AVLTree
{
private:
	AVLNode<T1, T2>*	root;
	int			size;
	const bool		strict;

	AVLNode<T1, T2>*	Clone(AVLNode<T1, T2>* node);
	void	Destroy(AVLNode<T1, T2>* &node);

public:
	AVLTree(const bool strict=true);
	AVLTree(const AVLTree& rhs);
	~AVLTree();
	AVLTree& operator= (const AVLTree& rhs);

	void*	operator new(size_t);
	void	operator delete(void*);

	bool	isStrict() const { return strict; }
	int  	getSize() const { return size; }
	bool	Insert(T1 key);
	bool	Insert(T1 key, AVLNode<T1, T2>*& node);
	bool	Insert(T1 key, T2 &data, AVLNode<T1, T2>*& node);
	bool 	Delete(T1 key);
	bool 	Delete(bool maximum);
	void	Destroy();
	bool 	Sort(bool asc, T1* sortedArray);
	bool 	Find(T1 key) const;
	bool	Find(T1 key, AVLNode<T1, T2>*& node);
	//void	Intersect(AVLTree<T1,T2> &other, AVLTree<T1,T2> &result);
	T1	Min(T2& data) const;
	T1	Max(T2& data) const;

	AVLTreeInOrderIterator<T1, T2> begin()  { return AVLTreeInOrderIterator<T1, T2>( root == 0 ? 0 : root->Find(LEFT));  }
	AVLTreeInOrderIterator<T1, T2> end()    { return AVLTreeInOrderIterator<T1, T2>(0);  }
	AVLTreeInOrderIterator<T1, T2> rbegin() { return AVLTreeInOrderIterator<T1, T2>(0);  }
	AVLTreeInOrderIterator<T1, T2> rend()   { return AVLTreeInOrderIterator<T1, T2>( root == 0 ? 0 : root->Find(RIGHT)); }
};

#endif //AVLTREE_H

