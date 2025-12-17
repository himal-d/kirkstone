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
#include <cstdio>
#include <cstring>
#include <string>
#include <filesystem>
#include "mntfsimg.hpp"
#include "omi_log.hpp"
#include "omi_unmount.hpp"
#include "omi_utils.hpp"

namespace omi
{

static int remove_directory(const std::string &dirname)
{
    int rv = -1;

    for (const auto &e: std::filesystem::directory_iterator(dirname)) {
        if (e.is_directory()) {
            rv = remove_directory(e.path());
        } else {
            rv = remove(e.path().c_str());
        }

        if (rv != 0) {
            Log::error("%s: could not remove \"%s\", error: %s", __FUNCTION__, e.path().c_str(), strerror(errno));
            break;
        }
    }

    if (rv == 0) {
        rv = remove(dirname.c_str());

        if (rv != 0)
            Log::error("%s: could not remove \"%s\", error: %s", __FUNCTION__, dirname.c_str(), strerror(errno));
    }

    return rv;
}

int DoUnmount(mntfsimg::ImageMounter& mounter,
              const std::string& id,
              std::string& errmsg)
{
    int rv = 0;
    std::string target = "/run/dac/rootfs/" + id;
    std::string dm_verity_name = "vdac-dec-" + id;
    std::string dm_crypt_name = "vdac-enc-" + id;

    mntfsimg::MntFsImgResult result = mounter.UnmountImage(target, dm_verity_name, dm_crypt_name);

    if (result != mntfsimg::MntFsImgResult::Success)
    {
        MapMountError(result, errmsg);
        Log::error("%s: %s: %s", __FUNCTION__, id.c_str(), errmsg.c_str());
        rv = -1;
    }
    else
    {
        // Clean up directories and config.json
        std::string config_json_subdir = "/run/dac/volatile/" + id;

        if (remove(target.c_str()) != 0)
        {
            Log::error("%s: %s: remove: %s", __FUNCTION__, target.c_str(), strerror(errno));
            errmsg = "Couldn't remove target";
            rv = -1;
        }

        if (remove_directory(config_json_subdir) != 0)
        {
            Log::error("%s: %s: remove: %s", __FUNCTION__, config_json_subdir.c_str(), strerror(errno));
            errmsg = "Couldn't remove config directory";
            rv = -1;
        }
    }

    return rv;
}
} // namespace omi

