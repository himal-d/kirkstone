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
#ifndef	CMANODE_H
#define CMANODE_H

#include <stdio.h>
#include <stdlib.h>

#include "avlTree.h"
#include "AllocMetrics.h"
#include "zmalloc.h"

class CmaNode : public AllocMetrics
{
public:
	CmaNode() : AllocMetrics(), asizes(false), file(0), line(0) {};
	CmaNode(unsigned int asize, unsigned int scount, char *file, int line);
	CmaNode(const CmaNode& rhs); 
	~CmaNode() { zfree(file); file=0; }

	void* operator new(size_t size) { return zmalloc(size); }
	void  operator delete(void* p) { zfree(p); }
	CmaNode& operator= (const CmaNode& rhs);

	char *GetFile() const { return file; }
	int   GetLine() const { return line; }
	AVLTree<int, int>* GetSizes() { return &asizes; }

	void Insert(char *file, int line);
	void Insert(unsigned int asize, unsigned int scount);
	void Insert(unsigned int asize, unsigned int scount, char *file, int line);

	void SetTotal();

private:
	AVLTree<int, int>	asizes;
	char			*file;
	int			line;
};

#endif // CMANODE_H
