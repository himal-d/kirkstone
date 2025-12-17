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
#include <cstring>
#include <stdlib.h>

#include "cmaNode.h"
#include "dbgMLT.h"
#include "zmalloc.h"

CmaNode::CmaNode(unsigned int asize, unsigned int scount, char *_file, int _line) : AllocMetrics(), asizes(false), file(_file), line(_line)
{
	Insert(asize, scount, file, line);
}

CmaNode::CmaNode(const CmaNode& rhs) : AllocMetrics(rhs.curAllocs, rhs.curAllocsSize, rhs.curIncr), asizes(rhs.asizes), file(0), line(rhs.line) 
{
	if (rhs.file)
	{
		file=(char*)zmalloc(strlen(rhs.file)+1);
		strcpy(file, rhs.file);
	}
}

CmaNode &CmaNode::operator= (const CmaNode &rhs)
{
	if (this == &rhs)
		return *this;

	zfree(file);
	file=rhs.file;
	line=rhs.line;
	asizes=rhs.asizes;
	return *this;
}

void CmaNode::Insert(char *file, int line)
{
	if (file && !this->file)
	{
		int len = strlen(file)+1;
		this->file = (char*)zmalloc(len);
		strncpy(this->file, file, len);
	}
	this->line=line;
}

void CmaNode::Insert(unsigned int asize, unsigned int scount)
{
	int *count=0;
	AVLNode<int, int>* cmaNode=0;
	asizes.Insert(asize, cmaNode);
	if (cmaNode && (count=cmaNode->GetDataPtr()))
		*count=scount;
}

void CmaNode::SetTotal()
{
	//DBG_MLT(int i=0;);
	AVLTreeInOrderIterator<int,int> sizesEnd = asizes.end();
	for (AVLTreeInOrderIterator<int,int> sizesIt = asizes.begin(); sizesIt != sizesEnd; ++sizesIt)
	{
		curAllocs+=*(sizesIt.getNode()->GetDataPtr());
		curAllocsSize+= (*sizesIt) * (*(sizesIt.getNode()->GetDataPtr()));
		//DBG_MLT(printf("CmaNode::SetTotal: %2.2d curAllocs = %d curAllocsSize = %d\n", i, curAllocs, curAllocsSize));
	}
	maxAllocs=curAllocs;
	maxAllocsSize=curAllocsSize;
	//DBG_MLT(printf("CmaNode::SetTotal: this = %p node size = %d : cur/max size = %d/%d cur/max alloc = %d/%d \n", 
	//	this, asizes.getSize(), curAllocsSize, maxAllocsSize, curAllocs, maxAllocs));
}

void CmaNode::Insert(unsigned int asize, unsigned int scount, char *file, int line)
{
	Insert(asize, scount);
	Insert(file, line);
}

