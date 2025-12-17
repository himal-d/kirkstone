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

#ifndef OMI_PARSER_HPP_
#define OMI_PARSER_HPP_

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
                    char** key);
} // namespace omi

#endif // #ifndef OMI_PARSER_HPP_

