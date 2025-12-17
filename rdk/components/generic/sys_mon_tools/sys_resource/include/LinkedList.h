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
#ifndef LL_H
#define LL_H

#include <assert.h>
#include <stdlib.h>

#include "zmalloc.h"

#ifndef NULL
#define	NULL				0
#endif

template <class T> class LinkedListIterator;
template <class T> class LinkedList;
template <class T> class Node;
template <class T> class HLL;
template <class T> class SLL;

template <class T>
class NodeLinks
{
protected:
	Node<T>*	next;
	Node<T>*	prev;
	NodeLinks() : next(0), prev(0) {}
};

template <class T>
class Node : public NodeLinks<T>
{
	friend class LinkedListIterator<T>;
	friend class LinkedList<T>;
	friend class HLL<T>;
	friend class SLL<T>;

	LinkedList<T>	*owner;
	T				*elem;

	Node(LinkedList<T>* _owner) : owner(_owner), elem(0) {}
	Node(const Node &obj) : owner(obj.owner)
	{
		elem = new T (obj);
	}
	~Node() { delete elem; }
	void setOwner(LinkedList<T>* owner) { this->owner=owner; }

public:
	void* operator new (size_t sizeNode, size_t usize) { return zmalloc(sizeNode+usize); }
	void* operator new (size_t size) { return zmalloc(size); }
	void  operator delete (void *p, size_t ) { zfree (p); }	// dummy placement delete to avoid compiler warning
	void  operator delete (void *p) { zfree (p); }

	T* GetDataPtr() { return elem; }
};

template <class T>
class LinkedListIterator 
{
	friend class LinkedList<T>;

public:
	bool hasNext() const { if (mNode) return mNode->next != 0; else return false; }
	bool operator== (LinkedListIterator<T> &iter) const { return mNode == iter.mNode; }
	bool operator!= (LinkedListIterator<T> &iter) const { return mNode != iter.mNode; }
	LinkedListIterator& operator++ () { if (mNode) mNode = mNode->next; return *this; }		// prefix
	LinkedListIterator& operator-- () { if (mNode) mNode = mNode->prev; return *this; }		// prefix
	const LinkedListIterator  operator++ (int) { LinkedListIterator<T> iter = *this; *this=++*this; return iter; }	// postfix
	const LinkedListIterator  operator-- (int) { LinkedListIterator<T> iter = *this; *this=--*this; return iter; }	// postfix
	T& operator* () { assert(mNode); return *mNode->elem; }
	Node<T>* getNode() { return mNode; }

private:
	LinkedListIterator(Node<T> *p) : mNode(p) { }
	Node<T>*	mNode;
};

template <class T>
class LinkedList 
{
protected:
	LinkedList() : size(0), first(0), last(0) {}
	void* operator new (size_t size) { return zmalloc(size); }
	void  operator delete (void *p) { zfree (p); }
public:
	~LinkedList();
	void removeFront();
	void removeBack();
	void moveBack(LinkedList<T> &list);
	bool remove(void *umem) { return remove((Node<T> *)u2n(umem)); }

	static Node<T>* u2n(void *umem) { return (Node<T>*)((char*)umem - sizeof(Node<T>)); }
	static void* n2u(Node<T>* node) { return (void *)((char*)node + sizeof(Node<T>)); }

	int getSize(void) const { return size; }
	LinkedListIterator<T> begin()  { return LinkedListIterator<T>(first); }
	LinkedListIterator<T> end()    { return LinkedListIterator<T>(0);  }
	LinkedListIterator<T> rbegin() { return LinkedListIterator<T>(0);  }
	LinkedListIterator<T> rend()   { return LinkedListIterator<T>(last);  }

protected:
	bool		remove(Node<T> *node);
	void		linkFront(Node<T> *node);
	void		linkBack(Node<T> *node);

	int		size;
	Node<T>*	first;
	Node<T>*	last;
};

template <class T>
class HLL : public LinkedList<T>
{
public:
	HLL() : LinkedList<T>() {}
	~HLL() {}
	void* operator new (size_t size) { return zmalloc(size); }
	void  operator delete (void *p) { zfree (p); }

	void *addFront(T &elem, int usize);
	void *addBack(T &elem, int usize);
};

template <class T>
class SLL : public LinkedList<T>
{
public:
	SLL() : LinkedList<T>() {}
	~SLL() {}
	void* operator new (size_t size) { return zmalloc(size); }
	void  operator delete (void *p) { zfree (p); }

	void *addFront(T &elem);
	void *addBack(T &elem);
};

#endif //LL_H

