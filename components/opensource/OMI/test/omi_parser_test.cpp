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

#include <cstdint>
#include <cstring>
#include <iostream>
#include "omi_log.hpp"
#include "omi_parser.hpp"

using namespace omi;

static const char roothash_reference[] = "176cf91ace5bcf5d7025c37a0e3aa6e6c67555317173cf1b37576b3ec22c6cb5";
static const char key_reference[] = "D8Poky2xz+l/pr0CuCNARhPZJigxZ/N2G11guxsigvs=";
static const uint64_t hashoffset_reference = 2101248;

static void happy_path()
{
    const char payload[] =
        "{\"annotations\": {"
        "\"org.rdk.dac.bundle.image.roothash\": \"176cf91ace5bcf5d7025c37a0e3aa6e6c67555317173cf1b37576b3ec22c6cb5\","
        "\"org.rdk.dac.bundle.image.salt\": \"14541abf5f0699eca1d9b92e9df1958f1a73ea52400c4770ad8d9925cf870e8c\","
        "\"org.rdk.dac.bundle.image.hashoffset\": \"2101248\","
        "\"org.rdk.dac.bundle.image.key\": \"D8Poky2xz+l/pr0CuCNARhPZJigxZ/N2G11guxsigvs=\"}}";

    char* roothash = NULL;
    char* key = NULL;
    uint64_t hashoffset = 0;
    int roothash_chk = -1;
    int key_chk = -1;
    bool hashoffset_chk = false;

    int rv = ParseConfigJson(payload, &roothash, &hashoffset, &key);

    if (rv == 0)
    {
        roothash_chk = strncmp(roothash, roothash_reference, strlen(roothash_reference));
        key_chk = strncmp(key, key_reference, strlen(key_reference));
        hashoffset_chk = (hashoffset == hashoffset_reference);
    }

    if ((rv == 0) && (roothash_chk == 0) && (key_chk == 0) && hashoffset_chk)
    {
        std::cout << "happy_path: PASS" << std::endl;
    }
    else
    {
        std::cout << "happy_path: FAIL" << std::endl;
    }
} 

static void negative_test(const char* payload, const char* name)
{
    char* roothash = NULL;
    char* key = NULL;
    uint64_t hashoffset = 0;
    int rv = ParseConfigJson(payload, &roothash, &hashoffset, &key);

    if (rv == -1)
    {
        std::cout << name << ": PASS" << std::endl;
    }
    else
    {
        std::cout << name << ": FAIL" << std::endl;
    }
}

static void missing_annotations()
{
    const char payload[] = "{}";
    negative_test(payload, __FUNCTION__);
}

static void missing_roothash()
{
    const char payload[] =
        "{\"annotations\": {"
        "\"org.rdk.dac.bundle.image.salt\": \"14541abf5f0699eca1d9b92e9df1958f1a73ea52400c4770ad8d9925cf870e8c\","
        "\"org.rdk.dac.bundle.image.hashoffset\": \"2101248\","
        "\"org.rdk.dac.bundle.image.key\": \"D8Poky2xz+l/pr0CuCNARhPZJigxZ/N2G11guxsigvs=\"}}";

    negative_test(payload, __FUNCTION__);
}

static void missing_hashoffset()
{
    const char payload[] =
        "{\"annotations\": {"
        "\"org.rdk.dac.bundle.image.roothash\": \"176cf91ace5bcf5d7025c37a0e3aa6e6c67555317173cf1b37576b3ec22c6cb5\","
        "\"org.rdk.dac.bundle.image.salt\": \"14541abf5f0699eca1d9b92e9df1958f1a73ea52400c4770ad8d9925cf870e8c\","
        "\"org.rdk.dac.bundle.image.key\": \"D8Poky2xz+l/pr0CuCNARhPZJigxZ/N2G11guxsigvs=\"}}";

    negative_test(payload, __FUNCTION__);
}

static void missing_key()
{
    const char payload[] =
        "{\"annotations\": {"
        "\"org.rdk.dac.bundle.image.roothash\": \"176cf91ace5bcf5d7025c37a0e3aa6e6c67555317173cf1b37576b3ec22c6cb5\","
        "\"org.rdk.dac.bundle.image.salt\": \"14541abf5f0699eca1d9b92e9df1958f1a73ea52400c4770ad8d9925cf870e8c\","
        "\"org.rdk.dac.bundle.image.hashoffset\": \"2101248\"}}";

    negative_test(payload, __FUNCTION__);
}

int main()
{
    Log::init();
    happy_path();
    missing_annotations();
    missing_roothash();
    missing_hashoffset();
    missing_key();
    return 0;
}

