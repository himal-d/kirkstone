/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2021 Liberty Global B.V.
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

#include <cerrno>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <string.h>
#include <jansson.h>
#include "omi_log.hpp"

namespace omi
{
// Parse annotations in config.json
// payload    [IN]  - JSON input (null-terminated string)
// roothash   [OUT] - roothash for dm-verity (null-terminated string)
// hashoffset [OUT] - hash offset for dm-verity
// key        [OUT] - key for dm-crypt (null-terminated string)
// Returns 0 on success, -1 on error
// ATTENTION: On success roothash and key must be freed by caller using free()

int ParseConfigJson(const char* payload,
                    char** roothash,
                    uint64_t* hashoffset,
                    char** key)
{
    int rv = -1;
    json_t* root = NULL;
    json_t* annotations = NULL;
    json_t* roothash_object = NULL;
    json_t* hashoffset_object = NULL;
    json_t* key_object = NULL;
    const char* roothash_string = NULL;
    const char* hashoffset_string = NULL;
    const char* key_string = NULL;
    json_error_t error;

    if ((root = json_loads(payload, JSON_REJECT_DUPLICATES, &error)) == NULL)
    {
        Log::error("%s: Line %d, Column %d: %s", __FUNCTION__, error.line, error.column, error.text);
    }
    else if ((annotations = json_object_get(root, "annotations")) == NULL)
    {
        Log::error("%s: Couldn't get annotations object", __FUNCTION__);
    }
    else if ((roothash_object = json_object_get(annotations, "org.rdk.dac.bundle.image.roothash")) == NULL)
    {
        Log::error("%s: Couldn't get roothash object", __FUNCTION__);
    }
    else if ((roothash_string = json_string_value(roothash_object)) == NULL)
    {
        Log::error("%s: Couldn't get roothash value", __FUNCTION__);
    }
    else if ((*roothash = strdup(roothash_string)) == NULL)
    {
        Log::error("%s: Couldn't duplicate roothash", __FUNCTION__);
    }
    else if ((hashoffset_object = json_object_get(annotations, "org.rdk.dac.bundle.image.hashoffset")) == NULL)
    {
        Log::error("%s: Couldn't get hash offset object", __FUNCTION__);
    }
    else if ((hashoffset_string = json_string_value(hashoffset_object)) == NULL)
    {
        Log::error("%s: Couldn't get hash offset value", __FUNCTION__);
    }
    else if ((key_object = json_object_get(annotations, "org.rdk.dac.bundle.image.key")) == NULL)
    {
        Log::error("%s: Couldn't get key object", __FUNCTION__);
    }
    else if ((key_string = json_string_value(key_object)) == NULL)
    {
        Log::error("%s: Couldn't get roothash value", __FUNCTION__);
    }
    else if ((*key = strdup(key_string)) == NULL)
    {
        Log::error("%s: Couldn't duplicate key", __FUNCTION__);
    }
    else
    {
        errno = 0;
        char* endptr = NULL;

        if (((*hashoffset = static_cast<uint64_t>(strtoull(hashoffset_string, &endptr, 10))) == ULLONG_MAX) ||
            (errno != 0) ||
            (endptr == hashoffset_string))
        {
            Log::error("%s: Couldn't convert hash offset to integer", __FUNCTION__);
        }
        else
        {
            // Success
            rv = 0;
        }
    }

    if (root != NULL)
    {
        json_decref(root);
    }

    if (rv != 0)
    {
        free(*roothash);
        *roothash = NULL;
        free(*key);
        *key = NULL;
    }

    return rv;
}
} // namespace omi

