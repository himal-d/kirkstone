/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2021 RDK Management
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
#include <stdlib.h>
#include <string.h>

#include <fwupgrade_hal.h>

int fwupgrade_hal_set_download_url (char *pUrl, char *pfilename)
{
    return RETURN_ERR;
}

int fwupgrade_hal_get_download_url (char *pUrl, char *pfilename)
{
    return RETURN_ERR;
}

int fwupgrade_hal_set_download_interface (unsigned int interface)
{
    return RETURN_ERR;
}

int fwupgrade_hal_get_download_interface (unsigned int *pinterface)
{
    return RETURN_ERR;
}

int fwupgrade_hal_download (void)
{
    return RETURN_ERR;
}

int fwupgrade_hal_get_download_status (void)
{
    return RETURN_ERR;
}

int fwupgrade_hal_reboot_ready (unsigned long *pValue)
{
    return RETURN_ERR;
}

int fwupgrade_hal_download_reboot_now (void)
{
    return RETURN_ERR;
}

int fwupgrade_hal_update_and_factoryreset (void)
{
    return RETURN_ERR;
}

int fwupgrade_hal_download_install (const char *url)
{
    return RETURN_ERR;
}
