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
#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <cJSON.h>

static cJSON* cJSON_Search(cJSON const* json, char const* path);
static cJSON* cJSON_SearchFile(char const* fname, char const* path);

static int is_index(char const* s)
{
    int index = 0;
    if (s)
    {
        while (s && *s)
        {
            if (isdigit((int) *s))
            {
                index *= 10;
                index += *s - 48;
            }
            else
            {
                index = -1;
                break;
            }
            s++;
        }
    }
    else
    {
        index = -1;
    }
    return index;
}

int main(int argc, char* argv[])
{
    int c = 0;
    int ret = 0;
    char const* file = NULL;
    char const* path = NULL;
    int getlen = 0;

    cJSON* item = NULL;

    while (1)
    {
        int option_index = 0;
        static struct option long_options[] = 
        {
            {"file", required_argument, 0, 'f'},
            {"path", required_argument, 0, 'p'},
	    {"getlen", no_argument, 0, 'l'},
            {0, 0, 0, 0}
        };

        c = getopt_long(argc, argv, "f:p:l", long_options, &option_index);
        if (c == -1)
            break;

        switch (c)
        {
            case 'f':
                file = optarg;
            break;

            case 'p':
                path = optarg;
		break;

            case 'l':
                getlen = 1;
            break;
        }
    }

    if (!file)
    {
        fprintf(stderr, "file required with -f|--file=\n");
        exit(1);
    }

    if (!path)
    {
        fprintf(stderr, "path required with -p|--path=\n");
        exit(1);
    }

    item = cJSON_SearchFile(file, path);
    if (item)
    {
        if (getlen && item->type == cJSON_Array)
        {
            printf("%d\n", cJSON_GetArraySize(item));
        }
        else
        {
            char* s;
            char* t;
            ret = 0;

            s = cJSON_Print(item);
            t = NULL;
            if (s)
            {
                size_t len = strlen(s);
                if (len > 0)
                {
                    t = s;
                    if (t[len - 1] == '"')
                        t[len - 1] = '\0';
                    if (t[0] == '"')
                        t++;
                }
            }
            printf("%s\n", t);
            free(s);
        }
        cJSON_Delete(item);
    }
    else
    {
        ret = 1;
    }

    return ret;
}

static cJSON* cJSON_SearchFile(char const* fname, char const* path)
{
    int ret = 0;
    struct stat buf;
    char* text = NULL; 
    cJSON* json = NULL;
    cJSON* item = NULL;
    FILE* infile = NULL;
    size_t file_size = 0;
    size_t bytes_read = 0;

    memset(&buf, 0, sizeof(buf));

    ret = stat(fname, &buf);
    if (ret == -1)
    {
        fprintf(stderr, "failed to stat:%s. %s", fname, strerror(errno));
        return NULL;
    }

    file_size = buf.st_size;
    text = (char *) malloc(file_size + 1);
    memset(text, 0, file_size + 1);
    infile = fopen(fname, "r");
    if (infile)
    {
        bytes_read = fread(text, 1, file_size, infile);
        if (bytes_read == file_size)
        {
            json = cJSON_Parse(text);
            item = cJSON_Search(json, path);
            cJSON_Delete(json);
        }
        else
        {
            fprintf(stderr, "only read %zd of %zd from %s\n", bytes_read, file_size, fname);
        }
        fclose(infile);
    }
    else
    {
        fprintf(stderr, "failed to open:%s. %s", fname, strerror(errno));
    }

    if (text != NULL)
    {
        free(text);
        text = NULL;
    }

    return item;
}


static cJSON* cJSON_Search(cJSON const* json, char const* path)
{
    cJSON const* item = NULL;

    if (!json)
    {
        fprintf(stderr, "Input argument json is NULL\n");
        return NULL;
    }

    if (!path || strlen(path) == 0)
    {
        fprintf(stderr, "Input argument path is NULL\n");
        return NULL;
    }

    if (path[0] != '/')
    {
        item = cJSON_GetObjectItem(json, path);
    }
    else
    {
        char* str = strdup(path + 1);  
        char* token = NULL;
        char* temp = str;
        int count = 0;

        item = json;
        while ((token = strtok_r(str, "/", &str)) != NULL)
        {
            int index = -1;
            int length = 0;

            if ((index = is_index(token)) != -1)
            {
                if (item->type != cJSON_Array)
                {
                    fprintf(stderr, "previous object is not array\n");
                    exit(1);
                }

                length = cJSON_GetArraySize(item);
                if (index >= length)
                {
                    fprintf(stderr, "%d is out of range, max is %d\n", index, (length -1));
                    exit(1);
                }
                item = cJSON_GetArrayItem(item, index);
#ifdef RDM_BACKWARD_COMPATIBLE
                item = item->child;
            }
            else if (count == 1)
            {
                int array_count = cJSON_GetArraySize(item);
                int i;
                for (i = 0 ; i < array_count; i++)
                {
                    cJSON* new = cJSON_GetArrayItem(item, i);
                    char *app_name = cJSON_GetArrayItem(new, 0)->string;
                    if (strcmp (app_name, token) == 0)
                    {
                        item = cJSON_GetObjectItem(new, token);
                        break;
                    }
                }
#endif
            }
            else
            {
                item = cJSON_GetObjectItem(item, token);
            }
            count++;
        }
        free(temp);
    }
    return cJSON_Duplicate(item, 1);
}
