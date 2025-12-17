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
#ifndef HAHEADER_H
#define HAHEADER_H

#include <string.h>
#include "zmalloc.h"

class HAHeader
{
public:
	HAHeader() : caller(0), size(0), file(0), line(0) {}
	HAHeader(size_t _size, void *_caller, char *_file, int _line) : caller(_caller), size(_size), file(0), line(_line) 
	{
		if (_file)
		{
			int len = strlen(_file)+1;
			file = (char*)zmalloc(len);
			strncpy(file, _file, len);
		}
	}

	HAHeader(const HAHeader& rhs) : caller(rhs.caller), size(rhs.size), file(0), line(rhs.line) 
	{
		if (rhs.file)
		{
			int len = strlen(rhs.file)+1;
			file=(char*)zmalloc(len);
			strncpy(file, rhs.file, len);
		}
	}

	~HAHeader() { if (file) { zfree(file); file=0; } }

	void* operator new(size_t size) { return zmalloc(size); }
	void  operator delete(void* p) { zfree(p); }

	HAHeader& operator= (const HAHeader &rhs)
	{
		if (this == &rhs)
			return *this;
		if (file) zfree(file);
		caller=rhs.caller;
		size=rhs.size;
		file=rhs.file;
		line=rhs.line;
		return *this;
	}

	void		*caller;
	size_t		size;
	char		*file;
	int 		line;
};

#endif //HAHEADER_H
