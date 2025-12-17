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
#include "IpCmaNode.h"

#define DEBUG_LL_ENABLE	0

#if DEBUG_LL_ENABLE
#define	DBG_LL(x)	x
#else
#define	DBG_LL(x)
#endif

template <class T>
LinkedList<T>::~LinkedList()
{
	DBG_LL(printf("LinkedList<T>::~LinkedList B: this = %p size = %d\n", this, size));
	int _size=size;
	for (int j=0; j<_size; j++) removeFront();
	DBG_LL(printf("LinkedList<T>::~LinkedList E: this = %p size = %d\n", this, size));
}

template <class T>
void LinkedList<T>::linkFront(Node<T> *node)
{
	node->prev = 0;
	node->next = first;
	if (first)
		first->prev = node;
	else
		last = node;
	first = node;
}

template <class T>
void LinkedList<T>::linkBack(Node<T> *node)
{
	node->next = 0;
	node->prev = last;
	if (last)
		last->next = node; 
	else
		first = node;
	last = node;
}

template <class T>
void LinkedList<T>::removeFront()
{
	if (first == 0)
		return;

	Node<T> *node = first->next;
	delete first;
	first = node;
	if (first)
		first->prev = 0;
	else
		last = 0;

	--size;
}

template <class T>
void LinkedList<T>::removeBack()
{
	if (last == 0)
		return;

	Node<T> *node = last->prev;
	delete last;
	last = node;
	if (last)
		last->next = 0;
	else
		first = 0;

	--size;
}

template <class T>
bool LinkedList<T>::remove(Node<T> *node)
{
	if (node == 0) 
		return false;
	if (node->owner != this)
		return false;

	Node<T> *next = node->next;
	Node<T> *prev = node->prev;

	node->owner = 0;
	if (next)
		next->prev=prev;
	else
	{
		removeBack();
		return true;
	}
	if (prev) 
		prev->next=next;
	else
	{
		removeFront();
		return true;
	}

	delete node;
	--size;
	return true;
}

template <class T>
void LinkedList<T>::moveBack(LinkedList<T> &list)
{
	if (this == &list || list.first == 0)
		return;

	if (first == 0)
	{
		first = list.first;
		last  = list.last;
	}
	else
	{
		list.first->prev=last;
		last->next=list.first;
		last=list.last;
	}
	size+=list.size;

	LinkedListIterator<T> listEnd=end();
	for (LinkedListIterator<T> iter = begin(); iter != listEnd; ++iter)
		iter.getNode()->setOwner(this);

	list.size=0;
	list.first=0;
	list.last=0;
}

template <class T>
void* HLL<T>::addFront(T &elem, int usize)
{
	Node<T> *node = new (usize) Node<T>(this);
	node->elem  = (T*) new T (elem);
	this->linkFront(node);
	++LinkedList<T>::size;

	DBG_LL(printf("HLL<T>::addFront: umem = %p : node = %p : usize = %d\n", n2u(node), node, usize));
	return this->n2u(node);
}

template <class T>
void* HLL<T>::addBack(T &elem, int usize)
{
	Node<T> *node = new (usize) Node<T>(this);
	node->elem  = (T*) new T (elem);
	this->linkBack(node);
	++LinkedList<T>::size;

	DBG_LL(printf("HLL<T>::addBack: umem = %p : node = %p : usize = %d\n", n2u(node), node, usize));
	return this->n2u(node);
}

template <class T>
void* SLL<T>::addFront(T &elem)
{
	Node<T> *node = new Node<T>(this);
	node->elem  = (T*) new T (elem);
	this->linkFront(node);
	++LinkedList<T>::size;

	return this->n2u(node);
}

template <class T>
void* SLL<T>::addBack(T &elem)
{
	Node<T> *node = new Node<T>(this);
	node->elem  = (T*) new T (elem);
	this->linkBack(node);
	++LinkedList<T>::size;

	return this->n2u(node);
}

template class HLL<HAHeader>;
template class LinkedList<HAHeader>;
template class SLL<IpCmaNode>;
template class LinkedList<IpCmaNode>;

#ifdef TEST_LL
template class SLL<int>;
template class HLL<int>;
template class LinkedList<int>;
template class SLL<char>;
template class HLL<char>;
template class LinkedList<char>;
template class SLL<char*>;
template class HLL<char*>;
template class LinkedList<char*>;
#endif //TEST_LL
