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

#include <cassert>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cjose/base64.h>
#include <cjose/util.h>
#include "libkwk.h"
#include "mntfsimg.hpp"
#include "omi_log.hpp"
#include "omi_mount.hpp"
#include "omi_parser.hpp"
#include "omi_utils.hpp"
#include "dac_jwt_jwe.hpp"
#include "dac_jwt_jwk.hpp"
#include "dac_jwt_jws.hpp"

namespace omi
{
int GetJwsPayload(const char* plaintext,
                  const int plaintext_len,
                  char** payload)
{
    int rv = -1;
    char* jws_compact = NULL;
    char* key_id = NULL;

    assert(plaintext != NULL);
    assert(payload != NULL);

    if ((jws_compact = strndup(plaintext, plaintext_len)) == NULL)
    {
        Log::error("%s: Couldn't duplicate plaintext", __FUNCTION__);
    }
    else if (dac_jwt::GetJwsKeyId(jws_compact, &key_id) != 0)
    {
        Log::error("%s: Couldn't get JWS key ID", __FUNCTION__);
    }
    else
    {
        char* pathname = NULL;
        char* jwk = NULL;

        // Create pathname for certificate from key ID
        if (asprintf(&pathname, CERTIFICATE_PATH_FORMAT, key_id) == -1) {
            Log::error("%s: Couldn't create path for certificate", __FUNCTION__);
            pathname = NULL;
        }
        else if (dac_jwt::GetJwsJwk(pathname, &jwk) != 0)
        {
            Log::error("%s: Couldn't get JWK for JWS (certificate path: %s)", __FUNCTION__, pathname);
        }
        else if (dac_jwt::VerifyJws(jws_compact, jwk, payload) != 0)
        {
            Log::error("%s: JWS verification failed", __FUNCTION__);
        }
        else
        {
            // Success
            rv = 0;
        }

        free(jwk);
        free(pathname);
    }

    free(key_id);
    free(jws_compact);
    return rv;
}

int DoMount(mntfsimg::ImageMounter& mounter,
            const std::string& id,
            const std::string& rootfs_path,
            const std::string& config_json_path,
            std::string& container_path,
            std::string& errmsg)
{
    int rv = -1;
    struct stat statbuf;
    FILE* stream = NULL;
    char* jwe_compact = NULL;
    const kwk_cb_table_t* const cb_table = kwk_get_cb_table();

    if (stat(config_json_path.c_str(), &statbuf) != 0)
    {
        Log::error("%s: %s: stat: %s", __FUNCTION__, config_json_path.c_str(), strerror(errno));
        errmsg = "Couldn't find config";
    }
    else if ((stream = fopen(config_json_path.c_str(), "r")) == NULL)
    {
        Log::error("%s: %s: fopen: %s", __FUNCTION__, config_json_path.c_str(), strerror(errno));
        errmsg = "Couldn't open config";
    }
    else if ((jwe_compact = static_cast<char*>(malloc(statbuf.st_size + 1))) == NULL)
    {
        Log::error("%s: %s: malloc: Couldn't allocate memory", __FUNCTION__, config_json_path.c_str());
        errmsg = "Couldn't allocate memory";
    }
    else if (fgets(jwe_compact, statbuf.st_size + 1, stream) == NULL)
    {
        Log::error("%s: %s: fgets: EOF or error", __FUNCTION__, config_json_path.c_str());
        errmsg = "Couldn't read config";
    }
    else
    {
        char* plaintext = NULL;
        char* payload = NULL;
        char* roothash = NULL;
        char* key = NULL;
        uint8_t* decoded_key = NULL;
        uint64_t hashoffset = 0;
        size_t plaintext_len = 0;
        size_t decoded_keylen = 0;
        cjose_err err;
        jwe_compact[statbuf.st_size] = '\0';

        if (dac_jwt::GetJwePlaintext(jwe_compact, cb_table, &plaintext, &plaintext_len) != 0)
        {
            errmsg = "Couldn't get plaintext";
            Log::error("%s: %s: %s", __FUNCTION__, config_json_path.c_str(), errmsg.c_str());
        }
        else if (GetJwsPayload(plaintext, plaintext_len, &payload) != 0)
        {
            errmsg = "JWS verification failed";
            Log::error("%s: %s: %s", __FUNCTION__, config_json_path.c_str(), errmsg.c_str());
        }
        else if (ParseConfigJson(payload, &roothash, &hashoffset, &key) != 0)
        {
            errmsg = "Parsing config failed";
            Log::error("%s: %s", __FUNCTION__, errmsg.c_str());
        }
        else if (!cjose_base64url_decode(key, strlen(key), &decoded_key, &decoded_keylen, &err))
        {
            Log::error("%s: %s: %s", __FUNCTION__, config_json_path.c_str(), err.message);
        }
        else
        {
            std::string target = "/run/dac/rootfs/" + id;
            mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP;

            if (mkdir(target.c_str(), mode) != 0)
            {
                Log::error("%s: %s: mkdir: %s", __FUNCTION__, target.c_str(), strerror(errno));
            }
            else
            {
                std::string options = "ro,nosuid";
                std::string dm_verity_name = "vdac-dec-" + id;
                std::string dm_crypt_name = "vdac-enc-" + id;
                std::string dm_crypt_key(reinterpret_cast<char*>(decoded_key), decoded_keylen);

                mntfsimg::MntFsImgResult result = mounter.MountImage(rootfs_path,
                                                                     target,
                                                                     options,
                                                                     dm_verity_name,
                                                                     roothash,
                                                                     hashoffset,
                                                                     false,
                                                                     dm_crypt_name,
                                                                     dm_crypt_key);

                if (result != mntfsimg::MntFsImgResult::Success)
                {
                    MapMountError(result, errmsg);
                    Log::error("%s: %s", __FUNCTION__, errmsg.c_str());
                    remove(target.c_str());
                }
                else
                {
                    // Save decrypted config.json
                    std::string config_json_dir = "/run/dac/volatile/";
                    std::string config_json_subdir = config_json_dir + id;
                    std::string target_symlink = config_json_subdir + "/rootfs"; // symlink to 'target'
                    std::string config_json_pathname = config_json_subdir + "/config.json";
                    FILE* fp = NULL;
                    size_t payload_len = strlen(payload);

                    if (mkdir(config_json_subdir.c_str(), mode) != 0)
                    {
                        Log::error("%s: %s: mkdir: %s", __FUNCTION__, config_json_subdir.c_str(), strerror(errno));
                    }
                    else if (chmod(config_json_subdir.c_str(), mode) != 0)
                    {
                        Log::error("%s: %s: chmod: %s", __FUNCTION__, config_json_subdir.c_str(), strerror(errno));
                    }
                    else if (stat(config_json_dir.c_str(), &statbuf) != 0)
                    {
                        Log::error("%s: %s: stat: %s", __FUNCTION__, config_json_dir.c_str(), strerror(errno));
                    }
                    else if (chown(config_json_subdir.c_str(), statbuf.st_uid, -1) != 0)
                    {
                        Log::error("%s: %s: chown: %s", __FUNCTION__, config_json_subdir.c_str(), strerror(errno));
                    }
                    else if ((fp = fopen(config_json_pathname.c_str(), "wt")) == NULL)
                    {
                        Log::error("%s: %s: fopen: %s", __FUNCTION__, config_json_pathname.c_str(), strerror(errno));
                    }
                    else if (fwrite(payload, sizeof(char), payload_len, fp) != payload_len)
                    {
                        Log::error("%s: %s: fwrite: %s", __FUNCTION__, config_json_pathname.c_str(), strerror(errno));
                    }
                    else if (chown(config_json_pathname.c_str(), statbuf.st_uid, statbuf.st_gid) != 0)
                    {
                        Log::error("%s: %s: chown: %s", __FUNCTION__, config_json_pathname.c_str(), strerror(errno));
                    }
                    else if (chmod(config_json_pathname.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP) != 0)
                    {
                        Log::error("%s: %s: chmod: %s", __FUNCTION__, config_json_pathname.c_str(), strerror(errno));
                    }
                    else if (symlink(target.c_str(), target_symlink.c_str()))
                    {
                        Log::error("%s: %s -> %s symlink: %s", __FUNCTION__, target.c_str(), target_symlink.c_str(), strerror(errno));
                    }
                    else
                    {
                        // Success
                        container_path = config_json_subdir;
                        rv = 0;
                    }

                    if (fp != NULL)
                    {
                        fclose(fp);
                    }
                }
            }

            cjose_get_dealloc()(decoded_key);
        }

        free(roothash);
        free(key);
        free(plaintext);
        free(payload);
    }

    free(jwe_compact);

    if (stream != NULL)
    {
        fclose(stream);
    }

    return rv;
}
} // namespace omi

