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

#ifndef OMI_MOUNT_HPP_
#define OMI_MOUNT_HPP_

#include <string>
#include "mntfsimg.hpp"

namespace omi
{
// Mount rootfs
// mounter          [IN]  - Image mounter object
// id               [IN]  - Container ID in reverse domain name notation
// rootfs_path      [IN]  - Absolute pathname for filesystem image
// config_json_path [IN]  - Absolute pathname for config.json.jwt
// container_path   [OUT] - Absolure pathname for decrypted config.json payload
// errmsg           [OUT] - Error message
// Returns 0 on success, -1 on error
int DoMount(mntfsimg::ImageMounter& mounter,
            const std::string& id,
            const std::string& rootfs_path,
            const std::string& config_json_path,
            std::string& container_path,
            std::string& errmsg);
} // namespace omi

#endif // #ifndef OMI_MOUNT_HPP_

