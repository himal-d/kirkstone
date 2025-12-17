/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
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
#include <arpa/inet.h>
#include <syscfg/syscfg.h>
#include "ansc_platform.h"
#include "cosa_xdns_apis.h"
#include "cosa_xdns_dml.h"
#include "plugin_main_apis.h"
#include "ccsp_xdnsLog_wrapper.h"
#include  "safec_lib_common.h"
#include "cosa_xdns_webconfig_api.h"
#include <trower-base64/base64.h>
#include "secure_wrapper.h"
int isValidIPv4Address(char *ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result;
}

int isValidIPv6Address(char *ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET6, ipAddress, &(sa.sin_addr));
    return result;
}

BOOL isValidMacAddress
    (
        PCHAR                       pAddress
    )
{
    ULONG                           length   = 0;
    ULONG                           i        = 0;
    char                            c        = 0;

    if( pAddress == NULL)
    {
        return TRUE; /* empty string is fine */
    }

    length = AnscSizeOfString(pAddress);

    if( length == 0)
    {
        return TRUE; /* empty string is fine */
    }

    /*
     *  Mac address such as "12:BB:AA:99:34:89" is fine, and mac adress
     *  with Mask is also OK, such as "12:BB:AA:99:34:89/FF:FF:FF:FF:FF:00".
     */
    if( length != 17 && length != 35)
    {
        return FALSE;
    }

    if( length > 17 && pAddress[17] != '/')
    {
        return FALSE;
    }

    for( i = 0; i < length ; i ++)
    {
        c = pAddress[i];

        if( i % 3 == 2)
        {
            if( i != 17 && c != ':')
            {
                return FALSE;
            }
        }
        else
        {
            if ( AnscIsHexAlphaOrDigit(c) )
            {
                continue;
            }

            return FALSE;
        }
    }

    return TRUE;
}

/***********************************************************************


************************************************************************

 APIs for Object:

    Device.DeviceInfo.

    *  XDNSDeviceInfo_GetParamBoolValue
    *  XDNSDeviceInfo_SetParamBoolValue

***********************************************************************/

BOOL
XDNSDeviceInfo_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
    errno_t                         rc                  = -1;
    int                             ind                 = -1;


   CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

    // XDNS - get XDNS Enable/Disable flag


    rc = strcmp_s("X_RDKCENTRAL-COM_EnableXDNS", strlen("X_RDKCENTRAL-COM_EnableXDNS"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
        char buf[5] = {0};
        syscfg_get( NULL, "X_RDKCENTRAL-COM_XDNS", buf, sizeof(buf));
	if(buf[0] != '\0')
	{
		int var=atoi(buf);
    		if(var)
    		{
                        *pBool = TRUE;
                        return TRUE;
                }
	}
        *pBool = FALSE;

        return TRUE;
    }

    CcspXdnsConsoleTrace(("Unsupported parameter '%s'\n", ParamName));
    return FALSE;
}

BOOL
XDNSDeviceInfo_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        bValue
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
    PCOSA_DATAMODEL_XDNS            pMyObject           = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    errno_t                         rc                  = -1;
    int                             ind                 = -1;


CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

    // XDNS -  set XDNS Enable/Disable flag
    rc = strcmp_s("X_RDKCENTRAL-COM_EnableXDNS", strlen("X_RDKCENTRAL-COM_EnableXDNS"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
        char bval[2] = {0};


        // Check if value is same as already SET one.
        char buf[5] = {0};
        syscfg_get( NULL, "X_RDKCENTRAL-COM_XDNS", buf, sizeof(buf));
	if(buf[0] != '\0')
	{
		int var=atoi(buf);
		
		if(((bValue == TRUE) && (var)) || ((bValue == FALSE) && (!var)))
		{
			fprintf(stderr, "%s X_RDKCENTRAL-COM_XDNS value is same in DB, just return\n",__FUNCTION__);
			return TRUE;
		}
	}

        if( bValue == TRUE)
        {
#ifdef WAN_FAILOVER_SUPPORTED
            token_t  token;
            int fd = sysevent_open("127.0.0.1", SE_SERVER_WELL_KNOWN_PORT, SE_VERSION, "xdns", &token);
            if (!fd)
            {
                CcspTraceError(("CcspXDNS: Failed to get sysevent fd %d\n", fd));
                return FALSE;
            }
            char currentWanIfname[32] = {0};
            if( sysevent_get(fd, token, "current_wan_ifname", currentWanIfname, sizeof(currentWanIfname)) == 0 &&
                strncmp(currentWanIfname, "erouter0", 8) == 0 )
            {
#endif
                FILE *fp1 = NULL;
                fp1 = fopen(DNSMASQ_SERVERS_CONF ,"r");
                if(fp1 == NULL)
                {
                        fprintf(stderr, "%s while Enabling XDNS DNSMASQ_SERVERS_CONF not exists\n",__FUNCTION__);
                        CreateDnsmasqServerConf(pMyObject);
                }

		/* CID-164173 fix */
		if(fp1 != NULL)
		{
		    fclose(fp1);
                    fp1 = NULL;
		}

                if(!SetXdnsConfig())
#ifdef WAN_FAILOVER_SUPPORTED
                {
                    sysevent_close(fd, token);
#endif
                    return FALSE;
#ifdef WAN_FAILOVER_SUPPORTED
                }
            }
            else
            {
                CcspTraceWarning(("CcspXDNS: Not enabled due to LTE WAN\n"));
            }
            sysevent_close(fd, token);
#endif
            bval[0] = '1';
        }
        else
        {
            if(!UnsetXdnsConfig())
                return FALSE;

            bval[0] = '0';
        }

        if (syscfg_set(NULL, "X_RDKCENTRAL-COM_XDNS", bval) != 0)
        {
                CcspXdnsConsoleTrace(("[XDNS] syscfg_set X_RDKCENTRAL-COM_XDNS failed!\n"));
        }
        else
        {
#ifdef _CBR_PRODUCT_REQ_
                if (syscfg_set(NULL, "XDNS_DNSSecEnable", bval) != 0)
                {
                        AnscTraceWarning(("[XDNS] syscfg_set XDNS_DNSSecEnable failed!\n"));
                }
                else
                {
                        fprintf(stderr, "%s [XDNS] XDNS_DNSSecEnable value is set to %s in DB\n",__FUNCTION__,bval);
                }
#endif        
                if (syscfg_commit() != 0)
                {
                        CcspXdnsConsoleTrace(("[XDNS] syscfg_commit X_RDKCENTRAL-COM_XDNS failed!\n"));
                }
                else
                {
			fprintf(stderr, "%s X_RDKCENTRAL-COM_XDNS value is set to %s in DB\n",__FUNCTION__,bval);
                        //Restart firewall to apply XDNS setting
                        commonSyseventSet("firewall-restart", "");
                }
        }

        return TRUE;
    }
    else
    {
        CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : EXIT FALSE \n", __FUNCTION__ ));
        return FALSE;
    }

    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : EXIT TRUE \n", __FUNCTION__ ));
    return TRUE;


}

/***********************************************************************

APIs for Object:

    DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.AvoidUnNecesaryXDNSretries.

    *  XDNSRefac_GetParamBoolValue
    *  XDNSRefac_SetParamBoolValue

***********************************************************************/

BOOL
XDNSRefac_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    )
{

    UNREFERENCED_PARAMETER(hInsContext);
    errno_t                         rc                  = -1;
    int                             ind                 = -1;


   CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

    // XDNS - get AvoidUnNecesaryXDNSretries Enable/Disable flag

        rc = strcmp_s("Enable", strlen("Enable"), ParamName , &ind);
        ERR_CHK(rc);
        if((!ind) && (rc == EOK))
        {
                char buf[5] = {0};
                syscfg_get( NULL, "XDNS_RefacCodeEnable", buf, sizeof(buf));
                if( buf != NULL )
                {
                        int var=atoi(buf);
                        if(var)
                        {

                                *pBool = TRUE;
                                return TRUE;
                        }
                }

                *pBool = FALSE;

                return TRUE;
        }


    CcspXdnsConsoleTrace(("Unsupported parameter '%s'\n", ParamName));
    return FALSE;
}
BOOL
XDNSRefac_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        bValue
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
    errno_t                         rc                  = -1;
    int                             ind                 = -1;


   CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

    // XDNS - set AvoidUnNecesaryXDNSretries Enable/Disable flag


    rc = strcmp_s("Enable", strlen("Enable"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
       // Check if XDNS is Enable if not AvoidUnNecesaryXDNSretries.Enable should not be Enabled/Disabled. so, dml will return error.
                char buf[5] = {0};
                syscfg_get( NULL, "X_RDKCENTRAL-COM_XDNS", buf, sizeof(buf));
                if( buf != NULL )
                {
                        int var=atoi(buf);

                        if(!var)
                        {
                                CcspTraceError((" %s X_RDKCENTRAL-COM_XDNS value is disabled,so, AvoidUnNecesaryXDNSretries_RFC Enable/Disable NOT SUCCESSFULL!!!\n", __FUNCTION__));
                                return FALSE;
                        }
                }

                char bval[2] = {0};
                if( bValue == TRUE)
                {
                        bval[0] = '1';
                }
                else
                {
                        bval[0] = '0';
                }



                if (syscfg_set(NULL, "XDNS_RefacCodeEnable", bval) != 0)
                {

                        CcspTraceInfo(("%s syscfg_set XDNS_RefacCodeEnable failed!!!!!\n", __FUNCTION__ ));
                }
                else
                {
                        if (syscfg_commit() != 0)
                        {
                                CcspTraceInfo(("%s syscfg_commit XDNS_RefacCodeEnable failed!!!!\n", __FUNCTION__ ));
                        }
                        else
                        {
                                CcspTraceInfo(("%s syscfg_set XDNS_RefacCodeEnable value set to %s \n", __FUNCTION__,bval ));
				if(bValue){
					CcspTraceInfo(("%s AvoidUnNecesaryXDNSretries_RFC_changed_to_enabled \n", __FUNCTION__));
				}else{
					CcspTraceInfo(("%s AvoidUnNecesaryXDNSretries_RFC_changed_to_disabled \n", __FUNCTION__));
				}
                                commonSyseventSet("dhcp_server-stop", "");
                                commonSyseventSet("dhcp_server-start", "");
                        }
                }

                return TRUE;
        }

    CcspXdnsConsoleTrace(("Unsupported parameter '%s'\n", ParamName));
    return FALSE;
}

/************************************************************************

 APIs for Object:

    Device.X_RDKCENTRAL-COM_XDNS.

    *  XDNS_GetParamStringValue
    *  XDNS_SetParamStringValue
    *  XDNS_GetParamBoolValue
    *  XDNS_SetParamBoolValue
    *  XDNS_Validate
    *  XDNS_Commit
    *  XDNS_Rollback

***********************************************************************/


ULONG
XDNS_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
    PCOSA_DATAMODEL_XDNS            pMyObject           = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    errno_t                         rc                  = -1;
    int                             ind                 = -1;

    rc = strcmp_s("DefaultDeviceDnsIPv4", strlen("DefaultDeviceDnsIPv4"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
        ULONG bufsize = strlen(pMyObject->DefaultDeviceDnsIPv4);
        if (bufsize < *pUlSize)
        {
            rc = strcpy_s(pValue, *pUlSize, pMyObject->DefaultDeviceDnsIPv4);
            if (rc != EOK)
            {
                ERR_CHK(rc);
                return 1;
            }
            return 0;
        }
        else
        {
            *pUlSize = bufsize + 1;
            return 1;
        }
    }

    rc = strcmp_s("DefaultDeviceDnsIPv6", strlen("DefaultDeviceDnsIPv6"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
        ULONG bufsize = strlen(pMyObject->DefaultDeviceDnsIPv6);
        if (bufsize < *pUlSize)
        {
            rc = strcpy_s(pValue, *pUlSize, pMyObject->DefaultDeviceDnsIPv6);
            if (rc != EOK)
            {
                ERR_CHK(rc);
                return 1;
            }
            return 0;
        }
        else
        {
            *pUlSize = bufsize + 1;
            return 1;
        }
    }

    rc = strcmp_s("DefaultSecondaryDeviceDnsIPv4", strlen("DefaultSecondaryDeviceDnsIPv4"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
        ULONG bufsize = strlen(pMyObject->DefaultSecondaryDeviceDnsIPv4);
        if (bufsize < *pUlSize)
        {
            rc = strcpy_s(pValue, *pUlSize, pMyObject->DefaultSecondaryDeviceDnsIPv4);
            if (rc != EOK)
            {
                ERR_CHK(rc);
                return 1;
            }
            return 0;
        }
        else
        {
            *pUlSize = bufsize + 1;
            return 1;
        }
    }

    rc = strcmp_s("DefaultSecondaryDeviceDnsIPv6", strlen("DefaultSecondaryDeviceDnsIPv6"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
        ULONG bufsize = strlen(pMyObject->DefaultSecondaryDeviceDnsIPv6);
        if (bufsize < *pUlSize)
        {
            rc = strcpy_s(pValue, *pUlSize, pMyObject->DefaultSecondaryDeviceDnsIPv6);
            if (rc != EOK)
            {
                ERR_CHK(rc);
                return 1;
            }
            return 0;
        }
        else
        {
            *pUlSize = bufsize + 1;
            return 1;
        }
    }

    rc = strcmp_s("DefaultDeviceTag", strlen("DefaultDeviceTag"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
        ULONG bufsize = strlen(pMyObject->DefaultDeviceTag);
        if (bufsize < *pUlSize)
        {
            rc = strcpy_s(pValue, *pUlSize, pMyObject->DefaultDeviceTag);
            if (rc != EOK)
            {
                ERR_CHK(rc);
                return 1;
            }
            return 0;
        }
        else
        {
            *pUlSize = bufsize + 1;
            return 1;
        }
        
    }

    rc = strcmp_s("Data", strlen("Data"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
                fprintf(stderr, "%s Data Get Not supported\n",__FUNCTION__);
                return 0;
    }

    AnscTraceWarning(("Unsupported parameter '%s'\n", ParamName));
    return -1;
}

BOOL
XDNS_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
    errno_t                         rc                  = -1;
    int                             ind                 = -1;

   CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

    rc = strcmp_s("DNSSecEnable", strlen("DNSSecEnable"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
#ifdef _CBR_PRODUCT_REQ_
        char buf[5] = {0};
        syscfg_get( NULL, "XDNS_DNSSecEnable", buf, sizeof(buf));
        if( buf != NULL )
        {
        	int var=atoi(buf);
    		if(var)
    		{

                        *pBool = TRUE;
                        return TRUE;
                }
        }

#endif
        *pBool = FALSE;

        return TRUE;
    }


	return FALSE;
}

BOOL
XDNS_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        bValue
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
    UNREFERENCED_PARAMETER(bValue);
    errno_t                         rc                  = -1;
    int                             ind                 = -1;
CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));


    rc = strcmp_s("DNSSecEnable", strlen("DNSSecEnable"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
#ifdef _CBR_PRODUCT_REQ_    
        char bval[2] = {0};
        if( bValue == TRUE)
        {
                bval[0] = '1';
        }
        else
        {
                        bval[0] = '0';
                }



        if (syscfg_set(NULL, "XDNS_DNSSecEnable", bval) != 0)
        {

               CcspXdnsConsoleTrace(("RDK_LOG_DEBUG,%s syscfg_set XDNS_DNSSecEnable failed!!!!!\n", __FUNCTION__ ));
        }
        else
        {
                if (syscfg_commit() != 0)
                {
                       CcspXdnsConsoleTrace(("RDK_LOG_DEBUG,%s syscfg_commit XDNS_DNSSecEnable failed!!!!\n", __FUNCTION__ ));
                }
                else
                {
                       fprintf(stderr, "%s syscfg_set XDNS_DNSSecEnable value set to %s \n",__FUNCTION__,bval);
                       commonSyseventSet("dhcp_server-stop", "");
                       commonSyseventSet("dhcp_server-start", "");
                }
        }

        return TRUE;
#endif
    }

	return FALSE;
}


/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL
        XDNS_SetParamStringValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                char*                       pString
            );

    description:

        This function is called to set string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pString
                The updated string value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL
XDNS_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pString
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
    PCOSA_DATAMODEL_XDNS            pMyObject           = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    errno_t                         rc                  = -1;
    int                             ind                 = -1;
    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

    rc = strcmp_s("DefaultDeviceDnsIPv4", strlen("DefaultDeviceDnsIPv4"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
        /* save update to backup */
        pMyObject->DefaultDeviceDnsIPv4Changed = TRUE;
        rc = strcpy_s(pMyObject->DefaultDeviceDnsIPv4, sizeof(pMyObject->DefaultDeviceDnsIPv4),pString  );
        if (rc != EOK)
        {
            ERR_CHK(rc);
            return FALSE;
        }
	fprintf(stderr, "%s primary ipv4 address is set to %s\n",__FUNCTION__,pMyObject->DefaultDeviceDnsIPv4);
    }
    else {
         rc = strcmp_s("DefaultDeviceDnsIPv6", strlen("DefaultDeviceDnsIPv6"), ParamName , &ind);
         ERR_CHK(rc);
         if((!ind) && (rc == EOK))
         {
             /* save update to backup */
             pMyObject->DefaultDeviceDnsIPv6Changed = TRUE;
             rc = strcpy_s(pMyObject->DefaultDeviceDnsIPv6, sizeof(pMyObject->DefaultDeviceDnsIPv6),pString);
             if (rc != EOK)
             {
                 ERR_CHK(rc);
                 return FALSE;
             }
	     fprintf(stderr, "%s primary ipv6 address is set to %s\n",__FUNCTION__,pMyObject->DefaultDeviceDnsIPv6);
          }
    else {
         rc = strcmp_s("DefaultSecondaryDeviceDnsIPv4", strlen("DefaultSecondaryDeviceDnsIPv4"), ParamName , &ind);
         ERR_CHK(rc);
         if((!ind) && (rc == EOK))
         {
             /* save update to backup */
             pMyObject->DefaultSecondaryDeviceDnsIPv4Changed = TRUE;
             rc = strcpy_s(pMyObject->DefaultSecondaryDeviceDnsIPv4, sizeof(pMyObject->DefaultSecondaryDeviceDnsIPv4),pString  );
             if (rc != EOK)
             {
                 ERR_CHK(rc);
                 return FALSE;
             }
	     fprintf(stderr, "%s secondary ipv4 address is set to %s\n",__FUNCTION__,pMyObject->DefaultSecondaryDeviceDnsIPv4);
         }
    else {
         rc = strcmp_s("DefaultSecondaryDeviceDnsIPv6", strlen("DefaultSecondaryDeviceDnsIPv6"), ParamName , &ind);
         ERR_CHK(rc);
         if((!ind) && (rc == EOK))
         {
             /* save update to backup */
             pMyObject->DefaultSecondaryDeviceDnsIPv6Changed = TRUE;
             rc = strcpy_s(pMyObject->DefaultSecondaryDeviceDnsIPv6, sizeof(pMyObject->DefaultSecondaryDeviceDnsIPv6),pString );
             if (rc != EOK)
             {
                ERR_CHK(rc);
                return FALSE;
             }
       	     fprintf(stderr, "%s secondary ipv6 address is set to %s\n",__FUNCTION__,pMyObject->DefaultSecondaryDeviceDnsIPv6);
         }
    else {
         rc = strcmp_s("DefaultDeviceTag", strlen("DefaultDeviceTag"), ParamName , &ind);
         ERR_CHK(rc);
         if((!ind) && (rc == EOK))
         {
             /* save update to backup */
             pMyObject->DefaultDeviceTagChanged = TRUE;
             rc = strcpy_s(pMyObject->DefaultDeviceTag, sizeof(pMyObject->DefaultDeviceTag),pString  );
             if (rc != EOK)
             {
                 ERR_CHK(rc);
                 return FALSE;
             }
        	fprintf(stderr, "%s DefaultDeviceTag is set to %s\n",__FUNCTION__,pMyObject->DefaultDeviceTag);
         }
    else {
         rc = strcmp_s("Data", strlen("Data"), ParamName , &ind);
         ERR_CHK(rc);
         if((!ind) && (rc == EOK))
         {
                fprintf(stderr, "%s ---------------start of b64 decode--------------\n",__FUNCTION__);

                char * decodeMsg =NULL;
                int decodeMsgSize =0;
                int size =0;
                int err;
                int i=0;


                msgpack_zone mempool;
                msgpack_object deserialized;
                msgpack_unpack_return unpack_ret;

                decodeMsgSize = b64_get_decoded_buffer_size(strlen(pString));

                decodeMsg = (char *) malloc(sizeof(char) * decodeMsgSize);

                size = b64_decode((const uint8_t *) pString, strlen(pString),(uint8_t *) decodeMsg );
                fprintf(stderr, "%s base64 decoded data contains %d bytes\n",__FUNCTION__,size);


                msgpack_zone_init(&mempool, 2048);
                unpack_ret = msgpack_unpack(decodeMsg, size, NULL, &mempool, &deserialized);

                switch(unpack_ret)
                {
                        case MSGPACK_UNPACK_SUCCESS:
                                fprintf(stderr, "%s MSGPACK_UNPACK_SUCCESS :%d\n",__FUNCTION__,unpack_ret);
                        break;
                        case MSGPACK_UNPACK_EXTRA_BYTES:
                                fprintf(stderr, "%s MSGPACK_UNPACK_EXTRA_BYTES :%d\n",__FUNCTION__,unpack_ret);
                        break;
                        case MSGPACK_UNPACK_CONTINUE:
                                fprintf(stderr, "%s MSGPACK_UNPACK_CONTINUE :%d\n",__FUNCTION__,unpack_ret);
                        break;
                        case MSGPACK_UNPACK_PARSE_ERROR:
                                fprintf(stderr, "%s MSGPACK_UNPACK_PARSE_ERROR :%d\n",__FUNCTION__,unpack_ret);
                        break;
                        case MSGPACK_UNPACK_NOMEM_ERROR:
                                fprintf(stderr, "%s MSGPACK_UNPACK_NOMEM_ERROR :%d\n",__FUNCTION__,unpack_ret);
                        break;
                        default:
                                fprintf(stderr, "%s Message Pack decode failed with error: %d\n",__FUNCTION__,unpack_ret);
                }

                msgpack_zone_destroy(&mempool);
                //End of msgpack decoding
                fprintf(stderr, "%s ---------------End of b64 decode--------------\n",__FUNCTION__);

                if(unpack_ret == MSGPACK_UNPACK_SUCCESS)
                {
                        xdnsdoc_t *xd;
                        xd = xdnsdoc_convert( decodeMsg, size+1 );
                        err = errno;
                        fprintf(stderr, "%s errno: %s\n",__FUNCTION__,xdnsdoc_strerror(err));

                        if ( decodeMsg )
                        {
                                free(decodeMsg);
                                decodeMsg = NULL;
                        }

                        if (NULL !=xd)
                        {



                                fprintf(stderr,"xd->subdoc_name is %s\n", xd->subdoc_name);
                                fprintf(stderr,"xd->version is %lu\n", (long)xd->version);
                                fprintf(stderr,"xd->transaction_id %lu\n",(long) xd->transaction_id);
                                fprintf(stderr,"xd->param->enable_xdns %s\n", (1 == xd->enable_xdns)?"true":"false");
                                fprintf(stderr,"xd->default_ipv4 %s\n",xd->default_ipv4);
                                fprintf(stderr,"xd->default_ipv6 %s\n",xd->default_ipv6);
                                fprintf(stderr,"xd->default_tag %s\n",xd->default_tag);
                                fprintf(stderr,"xd->table_param->entries_count %d\n",(int) xd->table_param->entries_count);
                                for(i =0; i< (int) xd->table_param->entries_count; i++)
                                {
                                        fprintf(stderr,"xd->table_param->entries[%d].dns_mac %s\n",i, xd->table_param->entries[i].dns_mac);
                                        fprintf(stderr,"xd->table_param->entries[%d].dns_ipv4 %s\n",i, xd->table_param->entries[i].dns_ipv4);
                                        fprintf(stderr,"xd->table_param->entries[%d].dns_ipv6 %s\n",i, xd->table_param->entries[i].dns_ipv6);
                                        fprintf(stderr,"xd->table_param->entries[%d].dns_tag %s\n",i, xd->table_param->entries[i].dns_tag);
                                }

                                execData *execDataxdns = NULL ;

                                execDataxdns = (execData*) malloc (sizeof(execData));

                                if ( execDataxdns != NULL )
                                {

                                        memset(execDataxdns, 0, sizeof(execData));

                                        execDataxdns->txid = xd->transaction_id;
                                        execDataxdns->version = xd->version;
                                        execDataxdns->numOfEntries = xd->table_param->entries_count;

                                        strncpy(execDataxdns->subdoc_name,"xdns",sizeof(execDataxdns->subdoc_name)-1);

                                        execDataxdns->user_data = (void*) xd ;
                                        execDataxdns->calcTimeout = NULL ;
                                        execDataxdns->executeBlobRequest = Process_XDNS_WebConfigRequest;
                                        execDataxdns->rollbackFunc = rollback_XDNS ;
                                        execDataxdns->freeResources = freeResources_XDNS ;

                                        PushBlobRequest(execDataxdns);

                                        fprintf(stderr, "%s PushBlobRequest complete\n",__FUNCTION__);

                                        return TRUE;

                                }
                                else
                                {
                                        fprintf(stderr, "%s execData memory allocation failed\n",__FUNCTION__);
                                        xdnsdoc_destroy( xd );

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
                        fprintf(stderr, "%s Corrupted XDNS Config value\n",__FUNCTION__);
                        return FALSE;
                }
	
	 }
    else
         {
             CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : EXIT FALSE \n", __FUNCTION__ ));
             return FALSE;
         }
	 }
         }
         }
         }
         }
    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : EXIT TRUE \n", __FUNCTION__ ));
    return TRUE;
   
}


BOOL
XDNS_Validate
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pReturnParamName,
        ULONG*                      puLength
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
    int ret = TRUE;
    PCOSA_DATAMODEL_XDNS            pMyObject           = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    errno_t                         rc                  = -1;
    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

    if(pMyObject->DefaultDeviceDnsIPv4Changed)
    {
        if(!strlen(pMyObject->DefaultDeviceDnsIPv4))
        {
            CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : IPv4 String is Empty  RET %d \n", __FUNCTION__, ret ));
            rc = strcpy_s(pReturnParamName, *puLength, "DnsIPv4 is empty" );
            if (rc != EOK)
            {
                ERR_CHK(rc);
            }
            return FALSE;
        } 
        else
        {
            ret = (isValidIPv4Address(pMyObject->DefaultDeviceDnsIPv4) == 1) ? TRUE : FALSE;
            CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s :  isValidIPv4Address RET %d \n", __FUNCTION__, ret ));
        }
    }

    if(pMyObject->DefaultDeviceDnsIPv6Changed)
    {
        if(!strlen(pMyObject->DefaultDeviceDnsIPv6))
        {
            rc = strcpy_s(pReturnParamName, *puLength, "DnsIPv6 is empty" );
            if (rc != EOK)
            {
                ERR_CHK(rc);
            }
            return FALSE;
        }
        else
        {
            ret = (isValidIPv6Address(pMyObject->DefaultDeviceDnsIPv6) == 1) ? TRUE : FALSE;
            CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s :  isValidIPv6Address RET %d \n", __FUNCTION__, ret ));
        }
    }

    if(pMyObject->DefaultSecondaryDeviceDnsIPv4Changed)
    {
        if(!strlen(pMyObject->DefaultSecondaryDeviceDnsIPv4))
        {
            CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : Secondary IPv4 String is Empty  RET %d \n", __FUNCTION__, ret ));
            rc = strcpy_s(pReturnParamName,*puLength , "SecondaryDnsIPv4 is empty" );
            if (rc != EOK)
            {
                ERR_CHK(rc);
                return FALSE;
            }
        }
        else
        {
            ret = (isValidIPv4Address(pMyObject->DefaultSecondaryDeviceDnsIPv4) == 1) ? TRUE : FALSE;
            CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s :  isValidIPv4Address for secondary server RET %d \n", __FUNCTION__, ret ));
        }
    }

    if(pMyObject->DefaultSecondaryDeviceDnsIPv6Changed)
    {
        if(!strlen(pMyObject->DefaultSecondaryDeviceDnsIPv6))
        {
            CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : Secondary IPv6 String is Empty  RET %d \n", __FUNCTION__, ret ));
            rc = strcpy_s(pReturnParamName,*puLength , "SecondaryDnsIPv6 is empty" );
            if (rc != EOK)
            {
                ERR_CHK(rc);
                return FALSE;
            }
        }
        else
        {
            ret = (isValidIPv6Address(pMyObject->DefaultSecondaryDeviceDnsIPv6) == 1) ? TRUE : FALSE;
            CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s :  isValidIPv6Address for secondary server RET %d \n", __FUNCTION__, ret ));
        }
    }

    if(pMyObject->DefaultDeviceTagChanged)
    {
        int len = strlen(pMyObject->DefaultDeviceTag);
        if(len > 255)
        {
            rc = strcpy_s(pReturnParamName,*puLength , "Tag Exceeds length" );
            if (rc != EOK)
            {
                ERR_CHK(rc);
            }
            return FALSE;
        }
    }

    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : EXIT  RET %d \n", __FUNCTION__, ret ));
    return ret;
}

ULONG
XDNS_Commit
    (
        ANSC_HANDLE                 hInsContext
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
    char dnsoverrideEntry[MAX_XDNS_SERV][MAX_BUF_SIZE] = {{0,0}};
    char* defaultMacAddress = "00:00:00:00:00:00";
    int count=0;
    char iprulebuf[256] = {0};
    PCOSA_DATAMODEL_XDNS            pMyObject           = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    errno_t rc = -1;
    
    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

    if(pMyObject->DefaultDeviceDnsIPv4Changed || pMyObject->DefaultDeviceDnsIPv6Changed || pMyObject->DefaultSecondaryDeviceDnsIPv4Changed || pMyObject->DefaultSecondaryDeviceDnsIPv6Changed || pMyObject->DefaultDeviceTagChanged)
    {
#ifndef FEATURE_IPV6
    if(strlen(pMyObject->DefaultDeviceDnsIPv4))
    {  
        rc = sprintf_s(iprulebuf, sizeof(iprulebuf), "from all to %s lookup erouter", pMyObject->DefaultDeviceDnsIPv4);
	if(rc < EOK) {
	   ERR_CHK(rc);
	} 

        if(v_secure_system("ip -4 rule show | grep '%s' | grep -v grep >/dev/null", iprulebuf) != 0)
            v_secure_system("ip -4 rule add %s", iprulebuf);

        
	snprintf(dnsoverrideEntry[0], 256, "dnsoverride %s %s %s\n", defaultMacAddress, pMyObject->DefaultDeviceDnsIPv4, pMyObject->DefaultDeviceTag);
        count++;

    if(strlen(pMyObject->DefaultSecondaryDeviceDnsIPv4))
    {
        rc = sprintf_s(iprulebuf, sizeof(iprulebuf), "from all to %s lookup erouter", pMyObject->DefaultSecondaryDeviceDnsIPv4);
	if(rc < EOK) {
	     ERR_CHK(rc);
	}

        if(v_secure_system("ip -4 rule show | grep '%s' | grep -v grep >/dev/null", iprulebuf) != 0)
            v_secure_system("ip -4 rule add %s", iprulebuf);

        snprintf(dnsoverrideEntry[1], 256, "dnsoverride %s %s %s\n", defaultMacAddress, pMyObject->DefaultSecondaryDeviceDnsIPv4, pMyObject->DefaultDeviceTag);
	count++;        
    }
    ReplaceDnsmasqConfEntry(defaultMacAddress, dnsoverrideEntry,count);
   }
#else
    if(strlen(pMyObject->DefaultDeviceDnsIPv4) && strlen(pMyObject->DefaultDeviceDnsIPv6))
    {

        rc = sprintf_s(iprulebuf, sizeof(iprulebuf), "from all to %s lookup erouter", pMyObject->DefaultDeviceDnsIPv4);
	if(rc < EOK) {
	    ERR_CHK(rc);
	}

        if(v_secure_system("ip -4 rule show | grep '%s' | grep -v grep >/dev/null", iprulebuf) != 0)
            v_secure_system("ip -4 rule add %s", iprulebuf);

        rc = sprintf_s(iprulebuf, sizeof(iprulebuf), "from all to %s lookup erouter", pMyObject->DefaultDeviceDnsIPv6);
	if(rc < EOK) {
	    ERR_CHK(rc);
	}

        if(v_secure_system("ip -6 rule show | grep '%s' | grep -v grep >/dev/null", iprulebuf) != 0)
            v_secure_system("ip -6 rule add %s", iprulebuf);

        rc = sprintf_s(dnsoverrideEntry[0], 256, "dnsoverride %s %s %s %s\n", defaultMacAddress, pMyObject->DefaultDeviceDnsIPv4, pMyObject->DefaultDeviceDnsIPv6, pMyObject->DefaultDeviceTag);
	if(rc < EOK) {
	     ERR_CHK(rc);
        }
	count++; 
    if(strlen(pMyObject->DefaultSecondaryDeviceDnsIPv4) && strlen(pMyObject->DefaultSecondaryDeviceDnsIPv6))
    {

        rc = sprintf_s(iprulebuf, sizeof(iprulebuf), "from all to %s lookup erouter", pMyObject->DefaultSecondaryDeviceDnsIPv4);
	if(rc < EOK) {
	    ERR_CHK(rc);
	}

        if(v_secure_system("ip -4 rule show | grep '%s' | grep -v grep >/dev/null", iprulebuf) != 0)
            v_secure_system("ip -4 rule add %s", iprulebuf);

        rc = sprintf_s(iprulebuf, sizeof(iprulebuf), "from all to %s lookup erouter", pMyObject->DefaultSecondaryDeviceDnsIPv6);
	if(rc < EOK) {
	    ERR_CHK(rc);
	}

        if(v_secure_system("ip -6 rule show | grep '%s' | grep -v grep >/dev/null", iprulebuf) != 0)
            v_secure_system("ip -6 rule add %s", iprulebuf);

        rc = sprintf_s(dnsoverrideEntry[1], 256, "dnsoverride %s %s %s %s\n", defaultMacAddress, pMyObject->DefaultSecondaryDeviceDnsIPv4, pMyObject->DefaultSecondaryDeviceDnsIPv6, pMyObject->DefaultDeviceTag);
	if(rc < EOK) {
	    ERR_CHK(rc);
        }
	count++; 
    }

      ReplaceDnsmasqConfEntry(defaultMacAddress, dnsoverrideEntry,count);
    }
#endif    
    else
    {
        CreateDnsmasqServerConf(pMyObject);
    }

    pMyObject->DefaultDeviceDnsIPv4Changed = FALSE;
    pMyObject->DefaultDeviceDnsIPv6Changed = FALSE;
    pMyObject->DefaultSecondaryDeviceDnsIPv4Changed = FALSE;
    pMyObject->DefaultSecondaryDeviceDnsIPv6Changed = FALSE;
    pMyObject->DefaultDeviceTagChanged = FALSE;
    
    }
    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

	return TRUE;
}

ULONG
XDNS_Rollback
    (
        ANSC_HANDLE                 hInsContext
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
    PCOSA_DATAMODEL_XDNS            pMyObject           = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

    char* primarytoken = NULL;
    char* secondarytoken = NULL;
    const char* s = " ";
    char buf[MAX_XDNS_SERV][MAX_BUF_SIZE] = {{0,0}};
    char* defaultMacAddress = "00:00:00:00:00:00";
    errno_t                         rc       = -1;

    GetDnsMasqFileEntry(defaultMacAddress,buf);

    char *ptr1 = NULL, *ptr2 = NULL;
    size_t len1 = 0, len2 =0;
    len1 = strlen( buf[0]);
    len2 = strlen(buf[1]);
    primarytoken = strtok_s(buf[0], &len1,s,&ptr1);
    secondarytoken = strtok_s(buf[1],&len2, s,&ptr2);
    if( (!primarytoken ||(!len1)) || (!secondarytoken ||(!len2)) )
    {
        return FALSE;   
    }

    primarytoken = strtok_s(NULL, &len1,s,&ptr1);
    secondarytoken = strtok_s(NULL,&len2, s,&ptr2);
    if( (!primarytoken ||(!len1)) || (!secondarytoken ||(!len2)) )
    {
        return FALSE;   
    }

    primarytoken = strtok_s(NULL, &len1,s,&ptr1);
    if(primarytoken && strstr(primarytoken, "."))
    {
	rc = strcpy_s(pMyObject->DefaultDeviceDnsIPv4, sizeof(pMyObject->DefaultDeviceDnsIPv4),primarytoken);
        if(rc != EOK)
        {
            ERR_CHK(rc);
            return FALSE;
         }
    }
    else
    {
        return FALSE;
    }

    secondarytoken = strtok_s(NULL,&len2, s,&ptr2);
    if(secondarytoken && strstr(secondarytoken, "."))
    {
	rc = strcpy_s(pMyObject->DefaultSecondaryDeviceDnsIPv4, sizeof(pMyObject->DefaultSecondaryDeviceDnsIPv4),secondarytoken);
        if(rc != EOK)
        {
            ERR_CHK(rc);
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }

#ifdef FEATURE_IPV6
    if(!len1)
    return FALSE;
    primarytoken = strtok_s(NULL, &len1,s,&ptr1);
    if((primarytoken) && strstr(primarytoken, ":"))
    {
	rc = strcpy_s(pMyObject->DefaultDeviceDnsIPv6, sizeof(pMyObject->DefaultDeviceDnsIPv6), primarytoken);
        if(rc != EOK)
        {
            ERR_CHK(rc);
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
    if(!len2)
    return FALSE;
    secondarytoken = strtok_s(NULL,&len2, s,&ptr2);
    if((secondarytoken) && strstr(secondarytoken, ":"))
    {
	rc = strcpy_s(pMyObject->DefaultSecondaryDeviceDnsIPv6, sizeof(pMyObject->DefaultSecondaryDeviceDnsIPv6),secondarytoken);
        if(rc != EOK)
        {
            ERR_CHK(rc);
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
#else
	rc = strcpy_s( pMyObject->DefaultDeviceDnsIPv6, sizeof(pMyObject->DefaultDeviceDnsIPv6),"");
        if(rc != EOK)
        {
            ERR_CHK(rc);
            return FALSE;
        }
	rc = strcpy_s( pMyObject->DefaultSecondaryDeviceDnsIPv6,sizeof(pMyObject->DefaultSecondaryDeviceDnsIPv6), "");
        if(rc != EOK)
        {
            ERR_CHK(rc);
            return FALSE;
        }

#endif
    if(!len1)
    return FALSE;
    primarytoken  = strtok_s(NULL,&len1, s,&ptr1);
    if(primarytoken)
    {     
	rc = strcpy_s(pMyObject->DefaultDeviceTag,sizeof(pMyObject->DefaultDeviceTag) , primarytoken);
	if(rc != EOK)
        {
            ERR_CHK(rc);
            return FALSE;
        }
    }
    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

	return TRUE;
}

/***********************************************************************

 APIs for Object:

    X_RDKCENTRAL-COM_XDNS.DNSMappingTable.{i}.

    *  DNSMappingTable_GetEntryCount
    *  DNSMappingTable_GetEntry
    *  DNSMappingTable_IsUpdated
    *  DNSMappingTable_Synchronize
    *  DNSMappingTable_AddEntry
    *  DNSMappingTable_DelEntry
    *  DNSMappingTable_GetParamStringValue
    *  DNSMappingTable_SetParamStringValue
    *  DNSMappingTable_Validate
    *  DNSMappingTable_Commit
    *  DNSMappingTable_Rollback

***********************************************************************/

ULONG
DNSMappingTable_GetEntryCount
    (
        ANSC_HANDLE hInsContext
    )

{
    UNREFERENCED_PARAMETER(hInsContext);
    PCOSA_DATAMODEL_XDNS            pMyObject           = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    int Qdepth = AnscSListQueryDepth( &pMyObject->XDNSDeviceList );
    return Qdepth;
}

ANSC_HANDLE
DNSMappingTable_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
    PCOSA_DATAMODEL_XDNS                   pMyObject         = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    PSINGLE_LINK_ENTRY                    pSListEntry       = NULL;
    PCOSA_CONTEXT_XDNS_LINK_OBJECT    pCxtLink          = NULL;

    pSListEntry       = AnscSListGetEntryByIndex(&pMyObject->XDNSDeviceList, nIndex);
    if ( pSListEntry )
    {
        pCxtLink      = ACCESS_COSA_CONTEXT_XDNS_LINK_OBJECT(pSListEntry);
        *pInsNumber   = pCxtLink->InstanceNumber;
    }

    return (ANSC_HANDLE)pSListEntry;
}

BOOL
DNSMappingTable_IsUpdated
    (
        ANSC_HANDLE                 hInsContext
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
    BOOL                            bIsUpdated   = TRUE;
    return bIsUpdated;
}

ULONG
DNSMappingTable_Synchronize
    (
        ANSC_HANDLE                 hInsContext
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
    /*Coverity Fix CID:72723  MISSING_RETURN */
    return ANSC_STATUS_SUCCESS;
}

ANSC_HANDLE
DNSMappingTable_AddEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG*                      pInsNumber
    )
{
    UNREFERENCED_PARAMETER(hInsContext);
	PCOSA_DATAMODEL_XDNS             pXdns              = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry = NULL;
    PCOSA_CONTEXT_XDNS_LINK_OBJECT   pXdnsCxtLink  = NULL;
    //CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

    pDnsTableEntry = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)AnscAllocateMemory(sizeof(COSA_DML_XDNS_MACDNS_MAPPING_ENTRY));
    if ( !pDnsTableEntry )
    {
		CcspTraceWarning(("%s resource allocation failed\n",__FUNCTION__));
        return NULL;
    }
 
    pXdnsCxtLink = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)AnscAllocateMemory(sizeof(COSA_CONTEXT_XDNS_LINK_OBJECT));

    if ( !pXdnsCxtLink )
    {
        goto EXIT;
    }        
	
	pXdnsCxtLink->InstanceNumber =  pXdns->ulXDNSNextInstanceNumber;
	pDnsTableEntry->InstanceNumber = pXdns->ulXDNSNextInstanceNumber;
    pXdns->ulXDNSNextInstanceNumber++;

    /* now we have this link content */
	pXdnsCxtLink->hContext = (ANSC_HANDLE)pDnsTableEntry;
	pXdns->pMappingContainer->XDNSEntryCount++;
    *pInsNumber = pXdnsCxtLink->InstanceNumber;

	CosaSListPushEntryByInsNum(&pXdns->XDNSDeviceList, (PCOSA_CONTEXT_LINK_OBJECT)pXdnsCxtLink);

    return (ANSC_HANDLE)pXdnsCxtLink;

EXIT:
    AnscFreeMemory(pDnsTableEntry);

    return NULL;

}

ULONG
DNSMappingTable_DelEntry
    (
        ANSC_HANDLE                 hInsContext,
        ANSC_HANDLE                 hInstance
    )

{
    UNREFERENCED_PARAMETER(hInsContext);
    ANSC_STATUS                          returnStatus      = ANSC_STATUS_SUCCESS;
    PCOSA_DATAMODEL_XDNS             pXdns               = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
    PCOSA_CONTEXT_XDNS_LINK_OBJECT   pXdnsCxtLink   = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)hInstance;
    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry      = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pXdnsCxtLink->hContext;
	/* Remove entery from the database */

    ReplaceDnsmasqConfEntry(pDnsTableEntry->MacAddress, NULL,1);

    if ( returnStatus == ANSC_STATUS_SUCCESS )
	{
			/* Remove entery from the Queue */
        if(AnscSListPopEntryByLink(&pXdns->XDNSDeviceList, &pXdnsCxtLink->Linkage) == TRUE)
		{
			AnscFreeMemory(pXdnsCxtLink->hContext);

			AnscFreeMemory(pXdnsCxtLink);
		}
		else
		{
			return ANSC_STATUS_FAILURE;
		}
	}


    //CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : EXIT \n", __FUNCTION__ ));


    return returnStatus;
}

ULONG
DNSMappingTable_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    )

{
    PCOSA_CONTEXT_XDNS_LINK_OBJECT   pXdnsCxtLink     = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)hInsContext;
    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry  = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pXdnsCxtLink->hContext;
    errno_t                                   rc            = -1;
    int                                       ind           = -1;
    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

    /* check the parameter name and return the corresponding value */
    rc = strcmp_s("MacAddress", strlen("MacAddress"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
        if ( AnscSizeOfString(pDnsTableEntry->MacAddress) < *pUlSize)
        {
            rc = strcpy_s(pValue, *pUlSize, pDnsTableEntry->MacAddress);
            if (rc != EOK)
            {
                ERR_CHK(rc);
                return 1;
            }
            return 0;
        }
        else
        {
            *pUlSize = AnscSizeOfString(pDnsTableEntry->MacAddress)+1;
            return 1;
        }
    }

    rc = strcmp_s("DnsIPv4", strlen("DnsIPv4"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
        if ( AnscSizeOfString(pDnsTableEntry->DnsIPv4) < *pUlSize)
        {
            rc = strcpy_s(pValue, *pUlSize, pDnsTableEntry->DnsIPv4);
            if (rc != EOK)
            {
                ERR_CHK(rc);
                return 1;
            }
            return 0;
        }
        else
        {
            *pUlSize = AnscSizeOfString(pDnsTableEntry->DnsIPv4)+1;
            return 1;
        }
    }

    rc = strcmp_s("DnsIPv6", strlen("DnsIPv6"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
        if ( AnscSizeOfString(pDnsTableEntry->DnsIPv6) < *pUlSize)
        {
            rc = strcpy_s(pValue, *pUlSize, pDnsTableEntry->DnsIPv6);
            if (rc != EOK)
            {
                ERR_CHK(rc);
                return 1;
            }
            return 0;
        }
        else
        {
            *pUlSize = AnscSizeOfString(pDnsTableEntry->DnsIPv6)+1;
            return 1;
        }
    }

    rc = strcmp_s("Tag", strlen("Tag"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK)) 
    {
        if ( AnscSizeOfString(pDnsTableEntry->Tag) < *pUlSize)
        {
            rc = strcpy_s(pValue, *pUlSize, pDnsTableEntry->Tag);
            if (rc != EOK)
            {
                ERR_CHK(rc);
                return 1;
            }
            return 0;
        }
        else
        {
            *pUlSize = AnscSizeOfString(pDnsTableEntry->Tag)+1;
            return 1;
        }
    }

    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : EXIT \n", __FUNCTION__ ));

    return -1;
}

BOOL
DNSMappingTable_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       strValue
    )

{
	PCOSA_CONTEXT_XDNS_LINK_OBJECT   pXdnsCxtLink     = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)hInsContext;
    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry  = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pXdnsCxtLink->hContext;
    BOOL ret = FALSE;
    errno_t                         rc          = -1;
    int                             ind         =  -1;
    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));
    rc = strcmp_s("MacAddress", strlen("MacAddress"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
    	// if MacAddress is already present, don't update.
        if(!strlen(pDnsTableEntry->MacAddress))
        {
        	CHAR *p = NULL;
            rc = strcpy_s(pDnsTableEntry->MacAddress, sizeof(pDnsTableEntry->MacAddress), strValue);
            if (rc != EOK)
            {
                ERR_CHK(rc);
                return FALSE;
            }            
            // convert MAC to lower case before writing to dml
            for (p = pDnsTableEntry->MacAddress; *p != '\0'; p++)
                *p = (char)tolower(*p);

            pDnsTableEntry->MacAddressChanged = TRUE;
            ret =  TRUE;            
        }
        else
        {
            ret =  FALSE;
        }

	}

    rc = strcmp_s("DnsIPv4", strlen("DnsIPv4"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
       rc = strcpy_s(pDnsTableEntry->DnsIPv4, sizeof(pDnsTableEntry->DnsIPv4), strValue);
            if (rc != EOK)
            {
                ERR_CHK(rc);
                return FALSE;
            }
        pDnsTableEntry->DnsIPv4Changed = TRUE;
        ret = TRUE;
    }

    rc = strcmp_s("DnsIPv6", strlen("DnsIPv6"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
        rc = strcpy_s(pDnsTableEntry->DnsIPv6, sizeof(pDnsTableEntry->DnsIPv6), strValue);
            if (rc != EOK)
            { 
                ERR_CHK(rc);
                return FALSE;
            }

        pDnsTableEntry->DnsIPv6Changed = TRUE;
        ret = TRUE;
    }

    rc = strcmp_s("Tag", strlen("Tag"), ParamName , &ind);
    ERR_CHK(rc);
    if((!ind) && (rc == EOK))
    {
        rc = strcpy_s(pDnsTableEntry->Tag, sizeof(pDnsTableEntry->Tag), strValue);
        if (rc != EOK)
        {
            ERR_CHK(rc);
            return FALSE;
        }
        pDnsTableEntry->TagChanged = TRUE;        
        ret = TRUE;
    }    

    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : EXIT %d \n", __FUNCTION__, ret ));

    return ret;
}

BOOL
DNSMappingTable_Validate
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pReturnParamName,
        ULONG*                      puLength
    )

{
    PCOSA_CONTEXT_XDNS_LINK_OBJECT   pXdnsCxtLink     = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)hInsContext;
    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry  = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pXdnsCxtLink->hContext;
    char* defaultMacAddress = "00:00:00:00:00:00";
    errno_t                         rc       = -1;
    int                             ind      = -1;
    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

    BOOL ret = FALSE;

    if(pDnsTableEntry->MacAddressChanged)
    {
        char buf[256] = {0};
        GetDnsMasqFileEntry(pDnsTableEntry->MacAddress, &buf);        
	rc = strcmp_s(pDnsTableEntry->MacAddress, sizeof(pDnsTableEntry->MacAddress),defaultMacAddress ,&ind);
	ERR_CHK(rc);
	if(!strlen(pDnsTableEntry->MacAddress) || ((rc == EOK) && (!ind))  || strlen(buf))
        {
            rc = strcpy_s(pReturnParamName, *puLength,"MacAddress is Invalid");
            if (rc != EOK)
            {
                ERR_CHK(rc);
                return FALSE;
            } 
            rc = strcpy_s(pDnsTableEntry->MacAddress, sizeof(pDnsTableEntry->MacAddress),"");
            if (rc != EOK)
            {
                ERR_CHK(rc);
                return FALSE;
            }
            CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : EXIT %d \n", __FUNCTION__, ret ));
            return FALSE;
        }
        else
        {
            ret = (isValidMacAddress(pDnsTableEntry->MacAddress) == TRUE) ? TRUE : FALSE;
        }
    }

    if(pDnsTableEntry->DnsIPv4Changed)
    {
        if(!strlen(pDnsTableEntry->DnsIPv4))
        {
            rc = strcpy_s(pReturnParamName, *puLength,"DnsIPv4 is empty");
            if (rc != EOK)
            {
                ERR_CHK(rc);
            }
            return FALSE;
        }
        else
        {
            ret = (isValidIPv4Address(pDnsTableEntry->DnsIPv4) == 1) ? TRUE : FALSE;
        }
    }

    if(pDnsTableEntry->DnsIPv6Changed)
    {
        if(!strlen(pDnsTableEntry->DnsIPv6))
        {
            rc = strcpy_s(pReturnParamName, *puLength,"DnsIPv6 is empty");
            if (rc != EOK)
            {
                ERR_CHK(rc);
            }
            return FALSE;
        }
        else
        {
            ret = (isValidIPv6Address(pDnsTableEntry->DnsIPv6) == 1) ? TRUE : FALSE;
        }
    }

    if(pDnsTableEntry->TagChanged)
    {
        int len = strlen(pDnsTableEntry->Tag);
        if(len > 255)
        {
            rc = strcpy_s(pReturnParamName, *puLength,"Tag Exceeds length");
            if (rc != EOK)
            {
                ERR_CHK(rc);
            }
            return FALSE;
        }
        else
            ret = TRUE;
    }

    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : EXIT %d \n", __FUNCTION__, ret ));

    return ret;
}

ULONG
DNSMappingTable_Commit
    (
        ANSC_HANDLE                 hInsContext
    )

{
    char dnsoverrideEntry[1][256] = {{0,0}};
    errno_t rc = -1;

    PCOSA_CONTEXT_XDNS_LINK_OBJECT   pXdnsCxtLink     = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)hInsContext;
    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry  = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pXdnsCxtLink->hContext;
    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

    char iprulebuf[256] = {0};
    rc = sprintf_s(iprulebuf, sizeof(iprulebuf), "from all to %s lookup erouter", pDnsTableEntry->DnsIPv4);
    if(rc < EOK) {
        ERR_CHK(rc);
    }

    if(v_secure_system("ip -4 rule show | grep '%s' | grep -v grep >/dev/null", iprulebuf) != 0)
        v_secure_system("ip -4 rule add %s", iprulebuf);

#ifdef FEATURE_IPV6
    rc = sprintf_s(iprulebuf, sizeof(iprulebuf), "from all to %s lookup erouter", pDnsTableEntry->DnsIPv6);
    if(rc < EOK) {
	ERR_CHK(rc);
    }

    if(v_secure_system("ip -6 rule show | grep '%s' | grep -v grep >/dev/null", iprulebuf) != 0)
        v_secure_system("ip -6 rule add %s", iprulebuf);

    rc = sprintf_s(dnsoverrideEntry[0], 256, "dnsoverride %s %s %s %s\n", pDnsTableEntry->MacAddress, pDnsTableEntry->DnsIPv4, pDnsTableEntry->DnsIPv6, pDnsTableEntry->Tag);
    if(rc < EOK) {
        ERR_CHK(rc);
    }
#else
    snprintf(dnsoverrideEntry[0], 256, "dnsoverride %s %s %s\n", pDnsTableEntry->MacAddress, pDnsTableEntry->DnsIPv4, pDnsTableEntry->Tag);
#endif
    ReplaceDnsmasqConfEntry(pDnsTableEntry->MacAddress, dnsoverrideEntry,1);

    pDnsTableEntry->MacAddressChanged = FALSE;
    pDnsTableEntry->DnsIPv4Changed = FALSE;
    pDnsTableEntry->DnsIPv6Changed = FALSE;
    pDnsTableEntry->TagChanged = FALSE;        

    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : EXIT  \n", __FUNCTION__ ));
  
    /*Coverity Fix CID:53942 MISSING_RETURN */
    return ANSC_STATUS_SUCCESS;
}

ULONG
DNSMappingTable_Rollback
    (
        ANSC_HANDLE                 hInsContext
    )

{
    PCOSA_CONTEXT_XDNS_LINK_OBJECT   pXdnsCxtLink     = (PCOSA_CONTEXT_XDNS_LINK_OBJECT)hInsContext;
    PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry  = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pXdnsCxtLink->hContext;
    char buf[256] = {0};
    char* token = NULL;
    const char* s = " ";
    errno_t                         rc       = -1;

    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : ENTER \n", __FUNCTION__ ));

    GetDnsMasqFileEntry(pDnsTableEntry->MacAddress, &buf);

    if(!strlen(buf))
    {
        char *pBuf = buf;
        if(pDnsTableEntry->DnsIPv4Changed)
        {
	    rc = strcpy_s(pDnsTableEntry->DnsIPv4,sizeof(pDnsTableEntry->DnsIPv4) ,pBuf);
            if(rc != EOK)
            {
            ERR_CHK(rc);
            return FALSE;
	    }
        }
        if(pDnsTableEntry->DnsIPv6Changed)
        {
	    rc = strcpy_s(pDnsTableEntry->DnsIPv6,sizeof(pDnsTableEntry->DnsIPv6) ,pBuf);
            if(rc != EOK)
            {
            ERR_CHK(rc);
            return FALSE;
            }
        }
        if(pDnsTableEntry->TagChanged)
        {
	    rc = strcpy_s(pDnsTableEntry->Tag,sizeof(pDnsTableEntry->Tag) ,pBuf);
            if(rc != EOK)
            {
            ERR_CHK(rc);
            return FALSE;
            }
        }
    }
    else
    {
        size_t len = 0;
        len = strlen(buf);
        char *ptr = NULL;
        token = strtok_s(buf,&len, s,&ptr);
        if((!token) ||(!len))
        {
            return FALSE;   
        }

        token = strtok_s(NULL,&len, s,&ptr);
        if((!token)||(!len))
        {
            return FALSE;   
        }

        token = strtok_s(NULL,&len, s,&ptr);
        if(token && strstr(token, "."))
        {
            if(pDnsTableEntry->DnsIPv4Changed)
            {
		rc = strcpy_s(pDnsTableEntry->DnsIPv4,sizeof(pDnsTableEntry->DnsIPv4) ,token);
                if(rc != EOK)
                {
                    ERR_CHK(rc);
                    return FALSE;
                }
            }
        }
        else
        {
            return FALSE;
        }

#ifdef FEATURE_IPV6
        if(!len)
        return FALSE;
        token = strtok_s(NULL,&len, s,&ptr);
        if(token && strstr(token, ":"))
        {
	    rc = strcpy_s(pDnsTableEntry->DnsIPv6,sizeof(pDnsTableEntry->DnsIPv6) ,token);
            if(rc != EOK)
            {
                ERR_CHK(rc);
                return FALSE;
            }
        }
        else
        {
            return FALSE;
        }
#else
        if(pDnsTableEntry->DnsIPv6Changed)
	{
	    rc = strcpy_s(pDnsTableEntry->DnsIPv6, sizeof(pDnsTableEntry->DnsIPv6),"");
            if(rc != EOK)
            {
                ERR_CHK(rc);
                return FALSE;
            }
        }

#endif
        if(!len)
        return FALSE;
        token = strtok_s(NULL,&len ,s,&ptr);
        if(token)
            {
                if(pDnsTableEntry->TagChanged)
	        {
		    rc = strcpy_s(pDnsTableEntry->Tag, sizeof(pDnsTableEntry->Tag), token);
                    if(rc != EOK)
                    {
                        ERR_CHK(rc);
                        return FALSE;
                    }
	        }
            }
    }


    pDnsTableEntry->MacAddressChanged = FALSE;
    pDnsTableEntry->DnsIPv4Changed = FALSE;
    pDnsTableEntry->DnsIPv6Changed = FALSE;
    pDnsTableEntry->TagChanged = FALSE;      

    CcspXdnsConsoleTrace(("RDK_LOG_DEBUG, Xdns %s : EXIT \n", __FUNCTION__ ));

    /*Coverity Fix CID:69558  MISSING_RETURN */
    return ANSC_STATUS_SUCCESS;
}

