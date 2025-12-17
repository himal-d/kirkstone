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
#ifndef	COUNTEDFLAG_H
#define COUNTEDFLAG_H

#include <stdio.h>

class CountedFlag
{
private:
	CountedFlag();

public:
	CountedFlag(bool _flag) : flag(_flag), count(1) {};
	CountedFlag& operator = (const CountedFlag& rhs)
	{
		if (this == &rhs)
			return *this;

		flag == rhs.flag ? ++count : --count;
		if (!count)
		{
			flag=rhs.flag;
			count=1;
		}
		return *this;
	}
	bool operator == (const CountedFlag& rhs)
	{
		return rhs.flag == flag ? true : false;
	}
	bool operator != (const CountedFlag& rhs)
	{
		return rhs.flag != flag ? true : false;
	}
	bool get() const { return flag; }
	int counter() const { return count; }

private:
	bool	flag;
	int	count;
};

#endif // COUNTEDFLAG_H
