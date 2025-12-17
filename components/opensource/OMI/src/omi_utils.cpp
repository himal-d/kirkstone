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

#include <string>
#include "mntfsimg.hpp"
#include "omi_utils.hpp"

namespace omi
{
void MapMountError(mntfsimg::MntFsImgResult result,
                   std::string& errmsg)
{
    if (result == mntfsimg::MntFsImgResult::SourceUndetermined)
    {
        errmsg = "Couldn't determine if source attached to target";
    }
    else if (result == mntfsimg::MntFsImgResult::SourceAttached)
    {
        errmsg = "File or device attached to target";
    }
    else if (result == mntfsimg::MntFsImgResult::TargetNotFound)
    {
        errmsg = "No file or device attached to target";
    }
    else if (result == mntfsimg::MntFsImgResult::LoopDeviceError)
    {
        errmsg = "Loop device could not be associated";
    }
    else if (result == mntfsimg::MntFsImgResult::DmVerityError)
    {
        errmsg = "dm-verity error";
    }
    else if (result == mntfsimg::MntFsImgResult::DmCryptError)
    {
        errmsg = "dm-crypt error";
    }
    else if (result == mntfsimg::MntFsImgResult::MountError)
    {
        errmsg = "mount system call failed";
    }
    else if (result == mntfsimg::MntFsImgResult::UnmountError)
    {
        errmsg = "umount system call failed";
    }
}
} // namespace omi

