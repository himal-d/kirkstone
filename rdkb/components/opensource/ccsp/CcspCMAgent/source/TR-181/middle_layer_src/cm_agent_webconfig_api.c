#include<stdio.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <msgpack.h>
#include <stdarg.h>
#include <syscfg/syscfg.h>
#include "safec_lib_common.h"
#include "webconfig_framework.h"
#include "cm_agent_webconfig_api.h"
#include "cosa_rbus_handler_apis.h"
#include "msgpack.h"
#include <trower-base64/base64.h>
#include "ansc_platform.h"
#include "secure_wrapper.h"
#include "cmagent_helpers.h"
#include "cmagent_param.h"
#include "cosa_cm_common.h"

bool LLdMarkingRules_Enable,oldval;

int  get_base64_decodedbuffer(char *pString, char **buffer, int *size)
{
    CcspTraceInfo(("entering to %s \n", __FUNCTION__));
    int decodeMsgSize = 0;
    char *decodeMsg = NULL;
    if (buffer == NULL || size == NULL || pString == NULL)
        return -1;

    decodeMsgSize = b64_get_decoded_buffer_size(strlen(pString));

    decodeMsg = (char *) malloc(sizeof(char) * decodeMsgSize);

    if (!decodeMsg)
        return -1;

    *size = b64_decode( (const uint8_t*)pString, strlen(pString), (uint8_t *)decodeMsg );
    CcspTraceWarning(("base64 decoded data contains %d bytes\n",*size));

    *buffer = decodeMsg;
    return 0;
}

msgpack_unpack_return get_msgpack_unpack_status(char *decodedbuf, int size)
{
    CcspTraceInfo(("entering to %s \n", __FUNCTION__));

    msgpack_zone mempool;
    msgpack_object deserialized;
    msgpack_unpack_return unpack_ret;

    if (decodedbuf == NULL || !size)
        return MSGPACK_UNPACK_NOMEM_ERROR;

    msgpack_zone_init(&mempool, 2048);
    unpack_ret = msgpack_unpack(decodedbuf, size, NULL, &mempool, &deserialized);

    switch(unpack_ret)
    {
    case MSGPACK_UNPACK_SUCCESS:
        CcspTraceWarning(("MSGPACK_UNPACK_SUCCESS :%d\n",unpack_ret));
        break;
    case MSGPACK_UNPACK_EXTRA_BYTES:
        CcspTraceWarning(("MSGPACK_UNPACK_EXTRA_BYTES :%d\n",unpack_ret));
        break;
    case MSGPACK_UNPACK_CONTINUE:
        CcspTraceWarning(("MSGPACK_UNPACK_CONTINUE :%d\n",unpack_ret));
        break;
    case MSGPACK_UNPACK_PARSE_ERROR:
        CcspTraceWarning(("MSGPACK_UNPACK_PARSE_ERROR :%d\n",unpack_ret));
        break;
    case MSGPACK_UNPACK_NOMEM_ERROR:
        CcspTraceWarning(("MSGPACK_UNPACK_NOMEM_ERROR :%d\n",unpack_ret));
        break;
    default:
        CcspTraceWarning(("Message Pack decode failed with error: %d\n", unpack_ret));
    }

    msgpack_zone_destroy(&mempool);
    //End of msgpack decoding

    return unpack_ret;
}

/***************************************************************************************
 @name: LldMarkingRules_Enable
 @description: Update LldMarkingRules_Enable
 @param cmagentdoc_t         *subdoc - Pointer to name of the subdoc
 @return 0 if update success, BLOB_EXEC_FAILURE otherwise
****************************************************************************************/
static int LldMarkingRules_Enable( cmagentdoc_t* gd )
{
    char LLDEnableBuf[16] = {0};
    if(gd!=NULL)
    {
        if(!syscfg_get(NULL, LLDENABLE, LLDEnableBuf, sizeof(LLDEnableBuf)))
        {
            if(strcmp(LLDEnableBuf,"true") == 0)
            { 
                oldval = true;
            }
            else
            {
                oldval = false;
            }
        }
  
        LLdMarkingRules_Enable = gd->param->enable;
        if(LLdMarkingRules_Enable != oldval)
        { 
            publishLLDEnableValueChange(LLdMarkingRules_Enable);
            commonSyseventSet("firewall-restart", " ");
        }
        CcspTraceInfo(("LLdMarkingRules_Enable doc value : %d - %s \n",LLdMarkingRules_Enable,__FUNCTION__));
        return 0;
    }
    return BLOB_EXEC_FAILURE;    
}
/***************************************************************************************
 @name: processcmagentWebConfigRequest
 @description: CallBack API to execute gwmgr Blob request 
****************************************************************************************/

pErr processcmagentWebConfigRequest(void *Data)
{
    pErr execRetVal = NULL;

    execRetVal = (pErr) malloc (sizeof(Err));
    if (execRetVal == NULL )
    {
        CcspTraceError(("%s : malloc failed\n",__FUNCTION__));
        return execRetVal;
    }

    memset(execRetVal,0,sizeof(Err));

    execRetVal->ErrorCode = BLOB_EXEC_SUCCESS;

    cmagentdoc_t *cd = (cmagentdoc_t *) Data ;

    CcspTraceInfo(("%s :  lldqoscontrol configurartion recieved\n",__FUNCTION__));

    int ret1  = LldMarkingRules_Enable( cd ); //TODO: Need add logic in this function
    if ( 0 != ret1 )
    {
        if ( BLOB_EXEC_FAILURE == ret1 )
        {
            execRetVal->ErrorCode = BLOB_EXEC_FAILURE;
            strncpy(execRetVal->ErrorMsg,"BLOB_EXEC_FAILURE while apply",sizeof(execRetVal->ErrorMsg)-1);

        }
        return execRetVal;
    }
    return execRetVal;
}
/***************************************************************************************
 @name: rollbackcmagentFailureConf
 @description: rollback the previous cm agent Failure config
 @return 0 if rollback success, 1 otherwise
****************************************************************************************/
int rollbackcmagentFailureConf( )
{
    if(LLdMarkingRules_Enable != oldval)
    { 
        publishLLDEnableValueChange(oldval);
        commonSyseventSet("firewall-restart", " ");
    }
    else
    {
        CcspTraceWarning(("Both are Same: %s- line - %d\n",__FUNCTION__,__LINE__));
    }
    return 0;    
}

/***************************************************************************************
 @name: freeResourcesCmagent
 @description: API to free the allocated memory
****************************************************************************************/

void freeResourcesCmagent(void *arg)
{
    execData *blob_exec_data  = (execData*) arg;

    if (blob_exec_data == NULL)
    {
    	CcspTraceWarning(("blob_exec_data is NULL"));
            return;
    }
  
    cmagentdoc_t *gd = (cmagentdoc_t *) blob_exec_data->user_data ;
    if ( gd != NULL )
    {
        cmagentdocDestroy( gd );
        gd = NULL;
    }
    free(blob_exec_data);
    blob_exec_data = NULL ;
}


/****************************************helpers*******************************/

/***************************************************************************************
 @name: getcmagentBlobVersion
 @description: API to get Blob version
 @param char         *subdoc - Pointer to name of the subdoc
 @return version number if present, 0 otherwise.
****************************************************************************************/

uint32_t getcmagentBlobVersion(char* subdoc)
{
    char subdoc_ver[64] = {0}, buf[72] = {0};
    snprintf(buf,sizeof(buf),"%s_version",subdoc);
    if ( syscfg_get( NULL, buf, subdoc_ver, sizeof(subdoc_ver)) == 0 )
    {
        int version = atoi(subdoc_ver);
        return (uint32_t)version;
    }
    return 0;
}

/***************************************************************************************
 @name: setGwMgrBlobVersion
 @description: API to set Blob version in Utopia db
 @param char         *subdoc - Pointer to name of the subdoc
 @param unsigned int version  - Version number
 @return 0 on success, error otherwise.
****************************************************************************************/

int setcmagentBlobVersion(char* subdoc,uint32_t version)
{
    char subdoc_ver[64] = {0}, buf[72] = {0};
    snprintf(subdoc_ver,sizeof(subdoc_ver),"%u",version);
    snprintf(buf,sizeof(buf),"%s_version",subdoc);
    if(syscfg_set_commit(NULL,buf,subdoc_ver) != 0)
    {
        CcspTraceError(("syscfg_set failed\n"));
        return -1;
    }
    return 0;
}

/***************************************************************************************
 @name: webConfigFrameworkInit
 @description: API to register all the supported subdocs , versionGet 
               and versionSet are callback functions to get and set the subdoc 
               versions in db 
****************************************************************************************/

void webConfigFrameworkInit()
{
    char *sub_docs[SUBDOC_COUNT+1]= {LLD_SUBDOC};
    int i;
    blobRegInfo *blobData;

    blobData = (blobRegInfo*) malloc(SUBDOC_COUNT * sizeof(blobRegInfo));

    memset(blobData, 0, SUBDOC_COUNT * sizeof(blobRegInfo));

    blobRegInfo *blobDataPointer = blobData;

    for (i=0 ; i < SUBDOC_COUNT ; i++ )
    {
        strncpy( blobDataPointer->subdoc_name, sub_docs[i], sizeof(blobDataPointer->subdoc_name)-1);
        blobDataPointer++;
    }

    blobDataPointer = blobData ;

    getVersion versionGet = getcmagentBlobVersion;

    setVersion versionSet = setcmagentBlobVersion;
    CcspTraceInfo(("registering subdocs %s-%d\n",__FUNCTION__,__LINE__));
    register_sub_docs(blobData,SUBDOC_COUNT,versionGet,versionSet);
}
/*****************************************decoding start**************************/
bool WebConfig_blob_handler(char *Encoded_data)
{
    cmagentdoc_t *gd = NULL;
    int err;
    AnscTraceWarning(("%s enter  - Encoded_data - %s \n", __FUNCTION__,Encoded_data));
    CcspTraceWarning(("---------------start of b64 decode--------------\n"));
    if(Encoded_data==NULL)
    {
        CcspTraceWarning(("%s Entering  - Encoded_data - is NULL \n", __FUNCTION__));
        return false;
    }
    char * decodeMsg =NULL;
    int size =0;
    int retval = 0;
    msgpack_unpack_return unpack_ret = MSGPACK_UNPACK_SUCCESS;
    retval = get_base64_decodedbuffer(Encoded_data, &decodeMsg, &size);
    if (retval == 0)
    {
        unpack_ret = get_msgpack_unpack_status(decodeMsg,size);
    }
    else
    {
        if (decodeMsg)
        {
            free(decodeMsg);
            decodeMsg = NULL;
        }
        CcspTraceWarning(("decodeMsg allocation failed\n"));
        return FALSE;		
    }
    CcspTraceWarning(("---------------End of b64 decode--------------\n"));
    if(unpack_ret == MSGPACK_UNPACK_SUCCESS)
    {
        gd = cmagentdocConvert(decodeMsg, size);//used to process the incoming msgobject
        err = errno;
        CcspTraceWarning(( "errno: %s\n", cmagentdocStrerror(err) ));
        if( decodeMsg )
        {
	    free(decodeMsg);
	    decodeMsg = NULL;
        } 
				
        if(gd != NULL)
        {
            CcspTraceInfo(("gd->subdoc_name is %s\n", gd->subdoc_name));
            CcspTraceInfo(("gd->version is %lu\n", (long)gd->version));
            CcspTraceInfo(("gd->transaction_id %lu\n",(long) gd->transaction_id));
            CcspTraceInfo(("gd->enable %s\n", (1 == gd->param->enable)?"true":"false"));
            execData *execDataGm = NULL ;
            execDataGm = (execData*) malloc (sizeof(execData));
					
            if ( execDataGm != NULL )
            {
                memset(execDataGm, 0, sizeof(execData));
                execDataGm->txid = gd->transaction_id; 
                execDataGm->version = gd->version; 
                execDataGm->numOfEntries = 0; 
                            
                strncpy(execDataGm->subdoc_name,LLD_SUBDOC,sizeof(execDataGm->subdoc_name)-1);
                            
                execDataGm->user_data = (void*) gd ;
                execDataGm->calcTimeout = NULL ;
                execDataGm->executeBlobRequest = processcmagentWebConfigRequest;
                execDataGm->rollbackFunc = rollbackcmagentFailureConf;
                execDataGm->freeResources = freeResourcesCmagent ;
                PushBlobRequest(execDataGm);
                CcspTraceWarning(("PushBlobRequest complete\n"));
                return TRUE;
            }	
            else 
            {
                CcspTraceWarning(("execData memory allocation failed\n"));
                cmagentdocDestroy(gd);
                return FALSE;
            }
        }
        return TRUE;
    }
    else
    {
        if ( decodeMsg )
        {
            free(decodeMsg);
            decodeMsg = NULL;
        }
        CcspTraceWarning(("Corrupted lldqoscontrol enable msgpack value\n"));
        return FALSE;
    }
}
