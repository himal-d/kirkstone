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
#ifndef	AVLNODE_H
#define AVLNODE_H

#include <assert.h>

enum  avl_find_mode_t 
{
	EQUAL	= 0,
	MINIMUM	= 1,
	MAXIMUM	= 2
};

enum	dir_t		{ LEFT = 0, RIGHT = 1 };
enum	height_change_t { HEIGHT_NOCHANGE = 0, HEIGHT_CHANGE = 1 };
enum	balance_t	{ LEFT_HEAVY = -1, BALANCED = 0, RIGHT_HEAVY = 1 };


template <class T1, class T2> class AVLTree;
template <class T1, class T2> class AVLTreeInOrderIterator;

template <class T1, class T2>
class AVLNode 
{
	friend class AVLTree<T1, T2>;
	friend class AVLTreeInOrderIterator<T1, T2>;

public:
	void* operator new(size_t);
	void  operator delete(void*);

	T1		GetKey() const { return key; }
	T2		GetData() const { return data; }
	T2*		GetDataPtr() { return &data; }
	int		GetCount() const { return count; }

private:
	AVLNode(T1 key);
	AVLNode(T1 key, T2 &data);
	AVLNode(AVLNode<T1, T2>* left, AVLNode<T1, T2>* right, T1 k, T2& v, AVLNode<T1, T2>* parent, int b, int c);
	~AVLNode();

	AVLNode<T1, T2>*	Clone(AVLNode<T1, T2>* node);
	void				SetParent(AVLNode<T1, T2>* node, AVLNode<T1, T2>* parent);
	bool		Insert(T1 key, AVLNode<T1, T2> *&root, int &heightChange, AVLNode<T1, T2> *&node);
	bool		Insert(T1 key, T2& data, AVLNode<T1, T2> *&root, int &heightChange, AVLNode<T1, T2> *&node);
	bool		Delete(T1 key, AVLNode<T1, T2> *&root, int &heightChange, T1& removedNode, avl_find_mode_t mode=EQUAL);
	bool		Sort (bool asc, T1 *sortedArray, int &index) const;
	bool		Find(dir_t dir, const AVLNode<T1, T2> *&node) const;
	bool		Find(T1 key, const AVLNode<T1, T2> *&node) const;
	bool		Find(T1 key, AVLNode<T1, T2> *&node);
	AVLNode<T1, T2>* Find(dir_t dir);
	AVLNode<T1, T2>* Find(dir_t dir, AVLNode<T1, T2>* node);

	// Helper methods
	dir_t		Opposite(dir_t dir) { return dir_t(1 - int(dir)); }
	bool		LeftHeavy (int balance) { return (balance < LEFT_HEAVY);  }
	bool		RightHeavy(int balance) { return (balance > RIGHT_HEAVY); }
	int		RotateOnce (AVLNode<T1, T2> *&root, dir_t dir);
	int		RotateTwice(AVLNode<T1, T2> *&root, dir_t dir);
	int		ReBalance  (AVLNode<T1, T2> *&root);
	bool		Found(T1 key, avl_find_mode_t mode) const;

	// Data
	T1					key;
	T2					data;				// Node data
	AVLNode<T1, T2>*	node[2];			// Node pointers
	AVLNode<T1, T2>*	parent;				// Node parent
	int					balance;			// Node balance factor
	int					count;				// Node count
};

#endif // AVLNODE_H

