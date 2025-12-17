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
#ifndef	IPCMANODE_H
#define IPCMANODE_H

#include <stdio.h>

#include "cmaNode.h"
#include "avlTree.h"
#include "zmalloc.h"

class IpCmaNode
{
public:
	IpCmaNode() : caller(0) {};
	IpCmaNode(int _caller) : caller(_caller) {};
	IpCmaNode(int _caller, char *file, int line) : caller(_caller)
	{
		cmaNode.Insert(file, line);
	}
	IpCmaNode(const IpCmaNode& rhs) : caller(rhs.caller), cmaNode(rhs.cmaNode) {}
	~IpCmaNode() { }

	void* operator new(size_t size) { return zmalloc(size); }
	void  operator delete(void* p) { zfree(p); }

	int	  GetCaller() const { return caller; }
	AVLTree<int, int>* GetSizes() { return cmaNode.GetSizes(); }
	char *GetFile() const { return cmaNode.GetFile(); }
	int   GetLine() const { return cmaNode.GetLine(); }

	void Insert(char *file, int line) { cmaNode.Insert(file, line); }
	void Insert(unsigned int asize, unsigned int scount) { cmaNode.Insert(asize, scount); }
	void Insert(unsigned int asize, unsigned int scount, char *file, int line) { cmaNode.Insert(asize, scount, file, line); }

	void SetTotal() { cmaNode.SetTotal(); }

	CmaNode*	getCmaNode() { return &cmaNode; }
private:
	int		caller;
	CmaNode		cmaNode;
};

#endif // IPCMANODE_H
