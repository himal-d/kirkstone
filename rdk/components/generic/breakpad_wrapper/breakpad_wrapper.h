/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2017 RDK Management
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
#ifndef __BREAKPAD_WRAPPER__
#define __BREAKPAD_WRAPPER__

#include<stddef.h>
#include<stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif//__cplusplus
#define DEFAULT_VISIBILITY __attribute__((visibility("default")))
DEFAULT_VISIBILITY void breakpad_AddMappingInfo(char *name, char *identifier,
                                                size_t identifer_length, uintptr_t start_address,
                                                size_t mapping_size, size_t file_offset);
void breakpad_ExceptionHandler(void);
void breakpad_autoconstruct(void);
#ifdef __cplusplus
}
#endif//__cplusplus
#endif//__BREAKPAD_WRAPPER__
