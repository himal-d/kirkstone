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
#ifndef DBG_MLT_H
#define DBG_MLT_H

#define DEBUG_MLT_ENABLE	0
#define DEBUG_BTRC_ENABLE	0

#if DEBUG_MLT_ENABLE
#define	DBG_MLT(x)	x
#define	DEBUG_MLT(x)	x
#else
#define	DBG_MLT(x)
#define	DEBUG_MLT(x)
#endif

#if DEBUG_BTRC_ENABLE
#define	DBG_BTRC(x)	x
#else
#define	DBG_BTRC(x)
#endif

#ifdef USE_CMAT_SSTATS
#define	CMAT_SSTATS(x)	x
#else
#define	CMAT_SSTATS(x)
#endif

#ifdef USE_CMAS_IT
#define	USE_CMASIT(x)	x
#else
#define	USE_CMASIT(x)
#endif

#endif //DBG_MLT_H
