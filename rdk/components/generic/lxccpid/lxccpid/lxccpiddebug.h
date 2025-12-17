/*********************************************************************************
* If not stated otherwise in this file or this component's Licenses.txt file the
* following copyright and licenses apply:
*
* Copyright 2017 Liberty Global B.V.
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
*********************************************************************************/

#define LXCCPID_DEBUGS

#ifdef LXCCPID_DEBUGS
#include <iostream>
#include <sstream>
#include <libgen.h>

#define SD_DEBUG(s...)                          ({ fprintf(stderr,ERROR_MARKER); fprintf(stderr,s); fprintf(stderr,CLEAR_MARKER); })
//#define SD_DEBUG(s...)                          swsyslog_log( LOG_DEBUG, s )

//#define __DBG_BEGIN { std::cerr <<"[" << __FILE__ << "][" << __LINE__ << "][" << __FUNCTION__ << "] "
//#define __DBG_END std::endl; }

#define __DBG_BEGIN { std::stringstream ss; ss <<"[" << basename((char*)__FILE__) << "][" << __LINE__ << "][" << __FUNCTION__ << "] "
#define __DBG_END std::endl; std::cerr << ss.str();}

#define DBG_IN() __DBG_BEGIN << "++" << __DBG_END
#define DBG_IN_S( x... ) __DBG_BEGIN << "++" << "(" << x << ")" << __DBG_END
#define DBG_OUT() __DBG_BEGIN << "--" << __DBG_END
#define DBG_OUT_S( x... ) __DBG_BEGIN << "--" << "(" << x << ")" << __DBG_END
#define DBG( x... ) __DBG_BEGIN << x << __DBG_END
#define DBG_CODE( x... ) x
#else
#define SD_DEBUG(s...)
#define DBG_IN()
#define DBG_IN_S( x... )
#define DBG_OUT()
#define DBG_OUT_S( x... )
#define DBG( x... )
#define DBG_CODE( x... )
#endif
