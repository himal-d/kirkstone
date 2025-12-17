/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2015 RDK Management
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

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/
#include <stdio.h>
#include <string.h>
#include "sysevent/sysevent.h"
#include "utapi/utapi.h"
#include "utapi/utapi_util.h"
#include "cosa_cm_common.h"

int commonSyseventFd = -1;
token_t commonSyseventToken;

static int openCommonSyseventConnection() {
    if (commonSyseventFd == -1) {
        commonSyseventFd = s_sysevent_connect(&commonSyseventToken);
    }
    return 0;
}

int commonSyseventSet(char* key, char* value){
    if(commonSyseventFd == -1) {
        openCommonSyseventConnection();
    }
    return sysevent_set(commonSyseventFd, commonSyseventToken, key, value, 0);
}

int commonSyseventGet(char* key, char* value, int valLen){
    if(commonSyseventFd == -1) {
        openCommonSyseventConnection();
    }
    return sysevent_get(commonSyseventFd, commonSyseventToken, key, value, valLen);
}

int commonSyseventClose() {
    int retval;

    if(commonSyseventFd == -1) {
        return 0;
    }

    retval = sysevent_close(commonSyseventFd, commonSyseventToken);
    commonSyseventFd = -1;
    return retval;
}

