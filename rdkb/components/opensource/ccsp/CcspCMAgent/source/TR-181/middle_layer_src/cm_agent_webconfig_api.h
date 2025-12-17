#ifndef __CM_AGENT_WEBCONFIG_API__
#define __CM_AGENT_WEBCONFIG_API__

#include <stdint.h>
#include <stdlib.h>
#include <msgpack.h>
#include "cmagent_helpers.h"
#include "cmagent_param.h"
#include "webconfig_framework.h"
#define SUBDOC_COUNT           1

bool WebConfig_blob_handler(char *Encoded_data);
int  get_base64_decodedbuffer(char *pString, char **buffer, int *size);
void cmagentdocDestroy( cmagentdoc_t *gd );
void webConfigFrameworkInit();
msgpack_unpack_return get_msgpack_unpack_status(char *decodedbuf, int size);
pErr processcmagentWebConfigRequest(void *Data);
void freeResourcesCmagent(void *arg);
int rollbackcmagentFailureConf();
uint32_t getcmagentBlobVersion(char* subdoc);
int setcmagentBlobVersion(char* subdoc,uint32_t version);

#endif //__CM_AGENT_WEBCONFIG_API__