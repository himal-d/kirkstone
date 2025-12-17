/*
 * If not stated otherwise in this file or this component's LICENSE file the
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

#include <syscfg/syscfg.h>
#include "cosa_xdns_webconfig_api.h"
#include "cosa_xdns_apis.h"
#include "plugin_main_apis.h"
#include "webconfig_framework.h"
#include  "safec_lib_common.h"

xdns_cache XDNS_Data_Cache;
xdns_cache XDNS_tmp_bck;

int CheckIfIpIsValid( char *ipAddress )
{

    //CcspTraceInfo(("%s:IpAddressReceivedIs:%s\n",__FUNCTION__,ipAddress));

    struct sockaddr_in sa;
    struct sockaddr_in6 sa6;

    if ( (inet_pton(AF_INET, ipAddress, &(sa.sin_addr)) == 1 ) || (inet_pton(AF_INET6, ipAddress, &(sa6.sin6_addr)) == 1 ))
    {
        return VALID_IP;
    }

    return INVALID_IP;
}

int CheckIfMacIsValid(char* pAddress)
{
    ULONG                           length   = 0;
    ULONG                           i        = 0;
    char                            c        = 0;

    if( pAddress == NULL)
    {
        return TRUE;
    }

    length = AnscSizeOfString(pAddress);

    if( length == 0)
    {
        return INVALID_MAC; 
    }

    if( length != 17 && length != 35)
    {
        return INVALID_MAC;
    }

    if( length > 17 && pAddress[17] != '/')
    {
        return INVALID_MAC;
    }

    for( i = 0; i < length ; i ++)
    {
        c = pAddress[i];

        if( i % 3 == 2)
        {
            if( i != 17 && c != ':')
            {
                return INVALID_MAC;
            }
        }
        else
        {
            if ( AnscIsHexAlphaOrDigit(c) )
            {
                continue;
            }

            return INVALID_MAC;
        }
    }

    return 0;
}

/* API to get the subdoc version */
uint32_t getBlobVersion(char* subdoc)
{

        char subdoc_ver[64] = {0}, buf[72] = {0};
        snprintf(buf,sizeof(buf),"%s_version",subdoc);
        if ( syscfg_get( NULL, buf, subdoc_ver, sizeof(subdoc_ver)) == 0 )
        {
                int version = atoi(subdoc_ver);
                //  uint32_t version = strtoul(subdoc_ver, NULL, 10) ; 

                return (uint32_t)version;
        }
        return 0;
}

/* API to update the subdoc version */
int setBlobVersion(char* subdoc,uint32_t version)
{

        char subdoc_ver[64] = {0}, buf[72] = {0};
        snprintf(subdoc_ver,sizeof(subdoc_ver),"%u",version);
        snprintf(buf,sizeof(buf),"%s_version",subdoc);
        if(syscfg_set_commit(NULL,buf,subdoc_ver) != 0)
        {
                //CcspTraceError(("syscfg_set failed\n"));
                return -1;
        }

        return 0;

}

/* API to read device dns ip from resolve.conf */
int xdns_read_dns_ip(char *UseRDKDefaultDeviceDnsIPv4, char *UseRDKDefaultDeviceDnsIPv6)
{
        char buff[256] = {0};
        FILE *fp = NULL;
        char *tok = NULL;
        int count = 0;
        int len = 0;
        int ret = 1;
        errno_t rc1 = EOK, rc2 = EOK;

        fp = fopen(RESOLV_CONF, "r");

        if(fp == NULL)
        {
           CcspTraceError(("%d:%s !!!NO resolv.conf fileError\n", __LINE__, __FUNCTION__));
           return ret;
        }

        while(fgets(buff, sizeof(buff), fp) != NULL)
        {
            if(strstr(buff, "nameserver") )
            {
                count++ ;
                if ( ( count == 1 ) || (count == 3 ) )
                {
                     tok = strtok(buff," ");
                     tok = strtok(NULL," ");

                     if( strstr(tok, ".") )
                     {
                        rc1 = strcpy_s(UseRDKDefaultDeviceDnsIPv4, STR_SIZE, tok);
                     }
                     else if ( strstr(tok, "::") )
                     {
                        rc2 = strcpy_s(UseRDKDefaultDeviceDnsIPv6, IPV6_STR_SIZE, tok);

                        /*Handle MAP-T mode*/
                        if ( count == 1 )
                        {
                           rc1 = strcpy_s(UseRDKDefaultDeviceDnsIPv4, STR_SIZE, IPV4_LOOPBACK);
                           break;
                        }
                     }
                }
            }
        }
        fclose(fp);

        len = strlen(UseRDKDefaultDeviceDnsIPv4) - 1;
        if (UseRDKDefaultDeviceDnsIPv4[len] == '\n')
             UseRDKDefaultDeviceDnsIPv4[len] = '\0';

        len = strlen(UseRDKDefaultDeviceDnsIPv6) - 1;
        if (UseRDKDefaultDeviceDnsIPv6[len] == '\n')
             UseRDKDefaultDeviceDnsIPv6[len] = '\0';

        if((rc1 != EOK) && (rc2 != EOK))
        {
            ERR_CHK(rc1);
            ERR_CHK(rc2);
            return ret;
        }

        return 0;
}

/* API to load device dns ip into XDNS DataModel */
int xdns_load_dns_ip(char *DnsIPv4, char *DnsIPv6, char *UseRDKDefaultDeviceDnsIPv4, char *UseRDKDefaultDeviceDnsIPv6)
{
        int ret = 1;
        errno_t rc = EOK;
        char router_mode[20]={0};
        syscfg_get(NULL, "last_erouter_mode", router_mode, sizeof(router_mode));

        if( atoi(router_mode) == erouter_mode_DualStack ) //DualStack
        {
            rc = strcpy_s(DnsIPv4, STR_SIZE, UseRDKDefaultDeviceDnsIPv4);
            if(rc != EOK)
            {
                ERR_CHK(rc);
                return ret;
            }
            rc = strcpy_s(DnsIPv6, IPV6_STR_SIZE, UseRDKDefaultDeviceDnsIPv6);
            if(rc != EOK)
            {
                ERR_CHK(rc);
                return ret;
            }
        }
        else if( atoi(router_mode) == erouter_mode_IPv6 ) //IPv6
        {
            rc = strcpy_s(DnsIPv4, STR_SIZE, IPV4_LOOPBACK);
            if(rc != EOK)
            {
                ERR_CHK(rc);
                return ret;
            }
            rc = strcpy_s(DnsIPv6, IPV6_STR_SIZE, UseRDKDefaultDeviceDnsIPv6);
            if(rc != EOK)
            {
                ERR_CHK(rc);
                return ret;
            }
        }
        else if( atoi(router_mode) == erouter_mode_IPv4 ) //IPv4
        {
            rc = strcpy_s(DnsIPv4, STR_SIZE, UseRDKDefaultDeviceDnsIPv4);
            if(rc != EOK)
            {
                ERR_CHK(rc);
                return ret;
            }
            rc = strcpy_s(DnsIPv6, IPV6_STR_SIZE, IPV6_LOOPBACK);
            if(rc != EOK)
            {
                ERR_CHK(rc);
                return ret;
            }
        }
        else
        {
            CcspTraceError(("%d:%s !!!Unable to check router mode\n", __LINE__, __FUNCTION__));
            return ret;
        }

        return 0;
}

/* API to read and load device dns ip from resolv.conf into XDNS DataModel */
int xdns_read_load_dns_ip(char *Blob_Valid_IPv4, char *Blob_Valid_IPv6, char *DnsIPv4, char *DnsIPv6)
{
        char UseRDKDefaultDeviceIPv4[STR_SIZE] = {0};
        char UseRDKDefaultDeviceIPv6[IPV6_STR_SIZE] = {0};
        int ret = 1;

        ret = xdns_read_dns_ip(UseRDKDefaultDeviceIPv4, UseRDKDefaultDeviceIPv6);
        if ( 0 != ret )
        {
             CcspTraceError(("%d:%s !!!UseRDKDefaultDeviceDnsIP: Unable to read Resolve.conf file OR resolv.conf file may not exits\n", __LINE__, __FUNCTION__));
             return ret;
        }

        if((INVALID_IP != CheckIfIpIsValid(UseRDKDefaultDeviceIPv4)) && (INVALID_IP != CheckIfIpIsValid(UseRDKDefaultDeviceIPv6)))
        {
            if((INVALID_IP != CheckIfIpIsValid(Blob_Valid_IPv4)))
            {
                 ret = xdns_load_dns_ip(DnsIPv4, DnsIPv6, Blob_Valid_IPv4, UseRDKDefaultDeviceIPv6);
                 if ( 0 != ret )
                 {
                      CcspTraceError(("%d:%s !!!Unable to load DNS IPv6 from device\n", __LINE__, __FUNCTION__));
                      return ret;
                 }
            }
            else if((INVALID_IP != CheckIfIpIsValid(Blob_Valid_IPv6)))
            {
                 ret = xdns_load_dns_ip(DnsIPv4, DnsIPv6, UseRDKDefaultDeviceIPv4, Blob_Valid_IPv6);
                 if ( 0 != ret )
                 {
                      CcspTraceError(("%d:%s !!!Unable to load DNS IPv4 from device\n", __LINE__, __FUNCTION__));
                      return ret;
                 }
            }
            else
            {
                 ret = xdns_load_dns_ip(DnsIPv4, DnsIPv6, UseRDKDefaultDeviceIPv4, UseRDKDefaultDeviceIPv6);
                 if ( 0 != ret )
                 {
                      CcspTraceError(("%d:%s !!!Unable to load DNS IPv4 and IPv6 from device\n", __LINE__, __FUNCTION__));
                      return ret;
                 }
            }
        }

        return ret;
}

void clear_xdns_cache(xdns_cache *tmp_xdns_cache)
{
fprintf(stderr, "%s Entered\n",__FUNCTION__);

	//memset(tmp_xdns_cache->XdnsEnable,0,STR_SIZE);
	tmp_xdns_cache->XdnsEnable=0;
	memset(tmp_xdns_cache->DefaultDeviceDnsIPv4,0,STR_SIZE);
	memset(tmp_xdns_cache->DefaultDeviceDnsIPv6,0,IPV6_STR_SIZE);
	memset(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4,0,STR_SIZE);
	memset(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6,0,IPV6_STR_SIZE);
	memset(tmp_xdns_cache->DefaultDeviceTag,0,STR_SIZE);
	tmp_xdns_cache->Tablecount=0;
	int i;
	for(i=0;i<XDNS_CACHE_SIZE;i++)
	{
		memset(tmp_xdns_cache->XDNSTableList[i].MacAddress,0,STR_SIZE);
		memset(tmp_xdns_cache->XDNSTableList[i].DnsIPv4,0,STR_SIZE);
		memset(tmp_xdns_cache->XDNSTableList[i].DnsIPv6,0,IPV6_STR_SIZE);
		memset(tmp_xdns_cache->XDNSTableList[i].Tag,0,STR_SIZE);

	}


}

void backup_xdns_cache(xdns_cache *tmp_xdns_cache,xdns_cache *xdns_cache_bkup)
{
fprintf(stderr, "%s Entered\n",__FUNCTION__);

	xdns_cache_bkup->XdnsEnable = tmp_xdns_cache->XdnsEnable;
        errno_t                         rc                  = EOK;
        char *pDefaultDeviceDnsIPv4 = xdns_cache_bkup->DefaultDeviceDnsIPv4;
        char *pDefaultDeviceDnsIPv6 = xdns_cache_bkup->DefaultDeviceDnsIPv6;
        char *pDefaultSecondaryDeviceDnsIPv4 = xdns_cache_bkup->DefaultSecondaryDeviceDnsIPv4;
        char *pDefaultSecondaryDeviceDnsIPv6 = xdns_cache_bkup->DefaultSecondaryDeviceDnsIPv6;
        char *pDefaultDeviceTag = xdns_cache_bkup->DefaultDeviceTag;

        rc = strcpy_s(pDefaultDeviceDnsIPv4, STR_SIZE,tmp_xdns_cache->DefaultDeviceDnsIPv4 );
        if(rc != EOK)
        {
            ERR_CHK(rc);
            return;
        }
        rc = strcpy_s(pDefaultDeviceDnsIPv6, IPV6_STR_SIZE,tmp_xdns_cache->DefaultDeviceDnsIPv6 );
        if(rc != EOK)
        {
            ERR_CHK(rc);
            return;
        }
        rc = strcpy_s(pDefaultSecondaryDeviceDnsIPv4, STR_SIZE,tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4 );
        if(rc != EOK)
        {
            ERR_CHK(rc);
            return;
        }
        rc = strcpy_s(pDefaultSecondaryDeviceDnsIPv6, IPV6_STR_SIZE,tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6 );
        if(rc != EOK)
        {
            ERR_CHK(rc);
            return;
        }
        rc = strcpy_s(pDefaultDeviceTag, STR_SIZE,tmp_xdns_cache->DefaultDeviceTag );
        if(rc != EOK)
        {
            ERR_CHK(rc);
            return;
        }
        xdns_cache_bkup->Tablecount=tmp_xdns_cache->Tablecount;

        int i;
        for(i=0;i<(tmp_xdns_cache->Tablecount);i++)
       	{
            char *pMacAddress = xdns_cache_bkup->XDNSTableList[i].MacAddress;
            char *pDnsIPv4 = xdns_cache_bkup->XDNSTableList[i].DnsIPv4;
            char *pDnsIPv6 = xdns_cache_bkup->XDNSTableList[i].DnsIPv6;
            char *pTag = xdns_cache_bkup->XDNSTableList[i].Tag;

            rc = strcpy_s(pMacAddress,STR_SIZE,tmp_xdns_cache->XDNSTableList[i].MacAddress );
            if(rc != EOK)
            {
                ERR_CHK(rc);
                return;
            }
            rc = strcpy_s(pDnsIPv4,STR_SIZE,tmp_xdns_cache->XDNSTableList[i].DnsIPv4 );
            if(rc != EOK)
            {
                ERR_CHK(rc);
                return;
            }
            rc = strcpy_s(pDnsIPv6,IPV6_STR_SIZE,tmp_xdns_cache->XDNSTableList[i].DnsIPv6 );
            if(rc != EOK)
            {
                ERR_CHK(rc);
                return;
            }
            rc = strcpy_s(pTag,STR_SIZE,tmp_xdns_cache->XDNSTableList[i].Tag );
            if(rc != EOK)
            {
                ERR_CHK(rc);
                return;
            }
        }


}

void print_xdns_cache(xdns_cache *tmp_xdns_cache)
{
	fprintf(stderr, "%s  tmp_xdns_cache->XdnsEnable:%s\n",__FUNCTION__,(1==tmp_xdns_cache->XdnsEnable)?"true":"false");
	fprintf(stderr, "%s  tmp_xdns_cache->DefaultDeviceDnsIPv4:%s\n",__FUNCTION__,tmp_xdns_cache->DefaultDeviceDnsIPv4);
	fprintf(stderr, "%s  tmp_xdns_cache->DefaultDeviceDnsIPv6:%s\n",__FUNCTION__,tmp_xdns_cache->DefaultDeviceDnsIPv6);
	fprintf(stderr, "%s  tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4:%s\n",__FUNCTION__,tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4);
	fprintf(stderr, "%s  tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6:%s\n",__FUNCTION__,tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6);
	fprintf(stderr, "%s  tmp_xdns_cache->DefaultDeviceTag:%s\n",__FUNCTION__,tmp_xdns_cache->DefaultDeviceTag);
	fprintf(stderr, "%s  tmp_xdns_cache->Tablecount:%d\n",__FUNCTION__,tmp_xdns_cache->Tablecount);

	int i;
        for(i=0;i<(tmp_xdns_cache->Tablecount);i++)
        {

		fprintf(stderr, "%s  tmp_xdns_cache->XDNSTableList[%d].MacAddress:%s\n",__FUNCTION__,i,tmp_xdns_cache->XDNSTableList[i].MacAddress);
		fprintf(stderr, "%s  tmp_xdns_cache->XDNSTableList[%d].DnsIPv4:%s\n",__FUNCTION__,i,tmp_xdns_cache->XDNSTableList[i].DnsIPv4);
		fprintf(stderr, "%s  tmp_xdns_cache->XDNSTableList[%d].DnsIPv6:%s\n",__FUNCTION__,i,tmp_xdns_cache->XDNSTableList[i].DnsIPv6);
		fprintf(stderr, "%s  tmp_xdns_cache->XDNSTableList[%d].Tag:%s\n",__FUNCTION__,i,tmp_xdns_cache->XDNSTableList[i].Tag);

        }



}


/* Initialize cache , this API will be called once in boot up */
void init_xdns_cache(xdns_cache *tmp_xdns_cache)
{
	PCOSA_DATAMODEL_XDNS            pMyObject           = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;
        fprintf(stderr, "%s Entered\n",__FUNCTION__);

	errno_t                         rc                  = EOK;	
	char buf[5]={0};
        int ret = 1;
	syscfg_get( NULL, "X_RDKCENTRAL-COM_XDNS",buf, 5);
	tmp_xdns_cache->XdnsEnable=atoi(buf);
	char *pDefaultSecondaryDeviceDnsIPv4 = tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4;
	char *pDefaultSecondaryDeviceDnsIPv6 = tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6;
	char *pDefaultDeviceTag = tmp_xdns_cache->DefaultDeviceTag;

        ret = xdns_load_dns_ip(tmp_xdns_cache->DefaultDeviceDnsIPv4, tmp_xdns_cache->DefaultDeviceDnsIPv6, pMyObject->DefaultDeviceDnsIPv4, pMyObject->DefaultDeviceDnsIPv6);
        if ( 0 != ret )
        {
             CcspTraceError(("%d %s: !!!Unable to load dns ip from device\n", __LINE__, __FUNCTION__));
             return;
        }

	rc = strcpy_s(pDefaultSecondaryDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4),pMyObject->DefaultSecondaryDeviceDnsIPv4 );
	if(rc != EOK)
	{
	    ERR_CHK(rc);
	    return;
	}
	rc = strcpy_s(pDefaultSecondaryDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6),pMyObject->DefaultSecondaryDeviceDnsIPv6 );
	if(rc != EOK)
	{
	    ERR_CHK(rc);
	    return;
	}
	rc = strcpy_s(pDefaultDeviceTag, sizeof(tmp_xdns_cache->DefaultDeviceTag),pMyObject->DefaultDeviceTag );
	if(rc != EOK)
	{
	    ERR_CHK(rc);
	    return;
	}
	tmp_xdns_cache->Tablecount=(pMyObject->ulXDNSNextInstanceNumber)-1;

	int i;
	for(i=0;i<(tmp_xdns_cache->Tablecount);i++)
	{
    		PSINGLE_LINK_ENTRY                    pSListEntry       = NULL;
    		PCOSA_CONTEXT_XDNS_LINK_OBJECT    pCxtLink          = NULL;
		pSListEntry       = AnscSListGetEntryByIndex(&pMyObject->XDNSDeviceList, i);
		    if ( pSListEntry )
    		     {
        			pCxtLink      = ACCESS_COSA_CONTEXT_XDNS_LINK_OBJECT(pSListEntry);
				PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY pDnsTableEntry  = (PCOSA_DML_XDNS_MACDNS_MAPPING_ENTRY)pCxtLink->hContext;
				char *pMacAddress = tmp_xdns_cache->XDNSTableList[i].MacAddress;
				char *pTag = tmp_xdns_cache->XDNSTableList[i].Tag;

				rc = strcpy_s(pMacAddress,STR_SIZE,pDnsTableEntry->MacAddress );
				if(rc != EOK)
				{
				    ERR_CHK(rc);
				    return;
				}

                                ret = xdns_load_dns_ip(tmp_xdns_cache->XDNSTableList[i].DnsIPv4, tmp_xdns_cache->XDNSTableList[i].DnsIPv6, pDnsTableEntry->DnsIPv4, pDnsTableEntry->DnsIPv6);
                                if ( 0 != ret )
                                {
                                     CcspTraceError(("%d:%s !!!Unable to load dns ip from device\n", __LINE__, __FUNCTION__));
                                     return;
                                }
				rc = strcpy_s(pTag,STR_SIZE,pDnsTableEntry->Tag );
				if(rc != EOK)
				{
				    ERR_CHK(rc);
				    return;
				}
   	 	    }
	}



}

/* API to register all the supported subdocs , versionGet and versionSet are callback functions to get and set the subdoc versions in db */
void webConfigFrameworkInit()
{
	fprintf(stderr, "Entered webConfigFrameworkInit\n");
        char *sub_docs[SUBDOC_COUNT+1]= {"xdns",(char *) 0 };

        blobRegInfo *blobData;

        blobData = (blobRegInfo*) malloc(SUBDOC_COUNT * sizeof(blobRegInfo));

        int i;
        memset(blobData, 0, SUBDOC_COUNT * sizeof(blobRegInfo));

        blobRegInfo *blobDataPointer = blobData;


        for (i=0 ; i < SUBDOC_COUNT ; i++ )
        {
                strncpy( blobDataPointer->subdoc_name, sub_docs[i], sizeof(blobDataPointer->subdoc_name)-1);

                blobDataPointer++;
        }

         blobDataPointer = blobData ;

        getVersion versionGet = getBlobVersion;

        setVersion versionSet = setBlobVersion;

        register_sub_docs(blobData,SUBDOC_COUNT,versionGet,versionSet);

}

/* API to apply XDNS blob requests to DB */
int apply_XDNS_cache_ToDB(xdns_cache *tmp_xdns_cache)
{
	PCOSA_DATAMODEL_XDNS            pMyObject           = (PCOSA_DATAMODEL_XDNS)g_pCosaBEManager->hXdns;

	char Entry[DATA_BLOCK_SIZE]={0};
	char* def_mac= "00:00:00:00:00:00";
	char buf[DATA_BLOCK_SIZE]={0};
	FILE *fp1 =NULL;
	int i;
	errno_t rc = -1;

	fprintf(stderr, "%s Entered !!!\n",__FUNCTION__);

	fp1 = fopen(DNSMASQ_SERVERS_CONF, "w");
	if(fp1 == NULL)
	{
		fprintf(stderr, "%s DNSMASQ_SERVERS_CONF file open error!!!\n",__FUNCTION__);
		return FILE_OPEN_ERROR;
	}

        rc = sprintf_s(Entry, sizeof(Entry), "dnsoverride %s %s %s %s\n", def_mac, tmp_xdns_cache->DefaultDeviceDnsIPv4, tmp_xdns_cache->DefaultDeviceDnsIPv6 , tmp_xdns_cache->DefaultDeviceTag);
	if(rc < EOK) {
	    ERR_CHK(rc);
	}
	fprintf(fp1, "%s", Entry);

        for(i=0;i<(tmp_xdns_cache->Tablecount);i++)
        {
		memset(Entry,0, sizeof(Entry));

        	rc = sprintf_s(Entry, sizeof(Entry), "dnsoverride %s %s %s %s\n", tmp_xdns_cache->XDNSTableList[i].MacAddress, tmp_xdns_cache->XDNSTableList[i].DnsIPv4 , tmp_xdns_cache->XDNSTableList[i].DnsIPv6, tmp_xdns_cache->XDNSTableList[i].Tag);
		if(rc < EOK) {
		     ERR_CHK(rc);
		}
	fprintf(fp1, "%s", Entry);
        }

	fclose(fp1);

	syscfg_get( NULL, "X_RDKCENTRAL-COM_XDNS", buf, sizeof(buf));
	int var=atoi(buf);
    	if( tmp_xdns_cache->XdnsEnable == var)
    	{
		fprintf(stderr, "%s blob and DB XDNS ENABLE falg are same %d !!!\n",__FUNCTION__,tmp_xdns_cache->XdnsEnable);
	}
	else
	{
		char setval[5]={0};

        	if(tmp_xdns_cache->XdnsEnable)
        	{
			SetXdnsConfig();
			setval[0]='1';

		}
		else
		{
			UnsetXdnsConfig();
			setval[0]='0';
		}

        	if (syscfg_set(NULL, "X_RDKCENTRAL-COM_XDNS", setval) != 0)
        	{
			fprintf(stderr, "%s syscfg_set X_RDKCENTRAL-COM_XDNS failed %d !!!\n",__FUNCTION__,tmp_xdns_cache->XdnsEnable);
			return SYSCFG_FAILURE;
        	}
        	else
        	{
#ifdef _CBR_PRODUCT_REQ_
                	if (syscfg_set(NULL, "XDNS_DNSSecEnable", setval) != 0)
                	{
				fprintf(stderr, "%s syscfg_set XDNS_DNSSecEnable failed %d !!!\n",__FUNCTION__,tmp_xdns_cache->XdnsEnable);
                	}
                	else
                	{
                        	fprintf(stderr, "%s XDNS_DNSSecEnable value is set to %d in DB\n",__FUNCTION__,tmp_xdns_cache->XdnsEnable);
               		}
#endif        
                	if (syscfg_commit() != 0)
                	{
				fprintf(stderr, "%s syscfg_commit X_RDKCENTRAL-COM_XDNS failed!!!\n",__FUNCTION__);
				return SYSCFG_FAILURE;
                	}
                	else
                	{
				fprintf(stderr, "%s X_RDKCENTRAL-COM_XDNS value is set to %d in DB\n",__FUNCTION__,tmp_xdns_cache->XdnsEnable);
                        	//Restart firewall to apply XDNS setting
                        	commonSyseventSet("firewall-restart", "");
                	}
        	}

	}
	CosaXDNSInitialize((ANSC_HANDLE)pMyObject);

	return 0;	
}

/* Read blob entries into a cache */
int set_xdns_conf(xdnsdoc_t *xd, xdns_cache *tmp_xdns_cache)
{
        fprintf(stderr, "%s Entered\n",__FUNCTION__);
        errno_t                         rc                  = EOK;
	tmp_xdns_cache->XdnsEnable = xd->enable_xdns;
        int ret = 1;
        char *pDefaultDeviceDnsIPv4 = tmp_xdns_cache->DefaultDeviceDnsIPv4;
        char *pDefaultDeviceDnsIPv6 = tmp_xdns_cache->DefaultDeviceDnsIPv6;
	if((INVALID_IP != CheckIfIpIsValid(xd->default_ipv4)) && (INVALID_IP != CheckIfIpIsValid(xd->default_ipv6)))
	{
            rc = strcpy_s(pDefaultDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv4),xd->default_ipv4 );
            if(rc != EOK)
            {
                ERR_CHK(rc);
                return 1;
            }
            rc = strcpy_s(pDefaultDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultDeviceDnsIPv6),xd->default_ipv6 );
            if(rc != EOK)
            {
                ERR_CHK(rc);
                return 1;
            }
	}
#if !defined(_COSA_FOR_BCI_)
        else if( ( !strncmp(xd->default_ipv4, USE_RDK_DEFAULT_STRING, sizeof(USE_RDK_DEFAULT_STRING) ) && ( INVALID_IP != CheckIfIpIsValid(xd->default_ipv6)) ) ||
                 ( (INVALID_IP != CheckIfIpIsValid(xd->default_ipv4)) && (!strncmp(xd->default_ipv6, USE_RDK_DEFAULT_STRING, sizeof(USE_RDK_DEFAULT_STRING))) ) ||
                 ( (!strncmp(xd->default_ipv4, USE_RDK_DEFAULT_STRING, sizeof(USE_RDK_DEFAULT_STRING))) && (!strncmp(xd->default_ipv6, USE_RDK_DEFAULT_STRING, sizeof(USE_RDK_DEFAULT_STRING))) )
               )
        {
                ret = xdns_read_load_dns_ip(xd->default_ipv4, xd->default_ipv6, tmp_xdns_cache->DefaultDeviceDnsIPv4, tmp_xdns_cache->DefaultDeviceDnsIPv6);
                if ( 0 != ret )
                {
                    CcspTraceError(("%d:%s !!!Unable to check router mode and get the device primary dns ip address from resolv.conf\n", __LINE__, __FUNCTION__));
                    return ret;
                }
        }
#endif
	else
	{
		fprintf(stderr,"%s INVALID_IP XDNS Default IP\n",__FUNCTION__);
		return INVALID_IP ;
	}
        char *pDefaultSecondaryDeviceDnsIPv4 = tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4;
        char *pDefaultSecondaryDeviceDnsIPv6 = tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6;
        char *pDefaultDeviceTag = tmp_xdns_cache->DefaultDeviceTag;

        rc = strcpy_s(pDefaultSecondaryDeviceDnsIPv4, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv4),"" );
        if(rc != EOK)
        {
            ERR_CHK(rc);
            return 1;
        }
        rc = strcpy_s(pDefaultSecondaryDeviceDnsIPv6, sizeof(tmp_xdns_cache->DefaultSecondaryDeviceDnsIPv6),"" );
        if(rc != EOK)
        {
            ERR_CHK(rc);
            return 1;
        }
        rc = strcpy_s(pDefaultDeviceTag, sizeof(tmp_xdns_cache->DefaultDeviceTag),xd->default_tag );
        if(rc != EOK)
        {
            ERR_CHK(rc);
            return 1;
        }
        tmp_xdns_cache->Tablecount=xd->table_param->entries_count;


        int i;
        for(i=0;i<(int)(xd->table_param->entries_count);i++)
        {
		if(INVALID_MAC != CheckIfMacIsValid(xd->table_param->entries[i].dns_mac))
		{
			char *pMacAddress = tmp_xdns_cache->XDNSTableList[i].MacAddress;

			rc = strcpy_s(pMacAddress,STR_SIZE,xd->table_param->entries[i].dns_mac );
			if(rc != EOK)
			{
			    ERR_CHK(rc);
			    return 1;
			}
		}
		else
		{
                	fprintf(stderr,"%s INVALID_MAC for index %d\n",__FUNCTION__,i);
                	return INVALID_MAC ;
		}

                char *pDnsIPv4 = tmp_xdns_cache->XDNSTableList[i].DnsIPv4;
                char *pDnsIPv6 = tmp_xdns_cache->XDNSTableList[i].DnsIPv6;
                if((INVALID_IP != CheckIfIpIsValid(xd->table_param->entries[i].dns_ipv4)) && (INVALID_IP != CheckIfIpIsValid(xd->table_param->entries[i].dns_ipv6)))
                {
                rc = strcpy_s(pDnsIPv4,STR_SIZE,xd->table_param->entries[i].dns_ipv4 );
                if(rc != EOK)
                {
                    ERR_CHK(rc);
                    return 1;
                }
                rc = strcpy_s(pDnsIPv6,IPV6_STR_SIZE,xd->table_param->entries[i].dns_ipv6 );
                if(rc != EOK)
                {
                    ERR_CHK(rc);
                    return 1;
                }
        	}
#if defined(_COSA_FOR_BCI_)
                else if( ( !strncmp(xd->table_param->entries[i].dns_ipv4, USE_RDK_DEFAULT_STRING, sizeof(USE_RDK_DEFAULT_STRING) ) && ( INVALID_IP != CheckIfIpIsValid(xd->table_param->entries[i].dns_ipv6)) ) ||
                         ( (INVALID_IP != CheckIfIpIsValid(xd->table_param->entries[i].dns_ipv4)) && (!strncmp(xd->table_param->entries[i].dns_ipv6, USE_RDK_DEFAULT_STRING, sizeof(USE_RDK_DEFAULT_STRING))) ) ||
                         ( (!strncmp(xd->table_param->entries[i].dns_ipv4, USE_RDK_DEFAULT_STRING, sizeof(USE_RDK_DEFAULT_STRING))) && (!strncmp(xd->table_param->entries[i].dns_ipv6, USE_RDK_DEFAULT_STRING, sizeof(USE_RDK_DEFAULT_STRING))) )
                       )
                {
                      ret = xdns_read_load_dns_ip(xd->table_param->entries[i].dns_ipv4, xd->table_param->entries[i].dns_ipv6, tmp_xdns_cache->XDNSTableList[i].DnsIPv4, tmp_xdns_cache->XDNSTableList[i].DnsIPv6);
                      if ( 0 != ret )
                      {
                          CcspTraceError(("%d:%s !!!Unable to check router mode and get the client dns ip address from resolv.conf\n", __LINE__, __FUNCTION__));
                          return ret;
                      }
                }
#endif
        	else
        	{
                	fprintf(stderr,"%s INVALID_IP XDNS Default IP\n",__FUNCTION__);
                	return INVALID_IP ;
        	}
            char *pTag = tmp_xdns_cache->XDNSTableList[i].Tag;
            rc = strcpy_s(pTag,STR_SIZE,xd->table_param->entries[i].dns_tag );
            if(rc != EOK)
            {
                ERR_CHK(rc);
                return 1;
            }
        }

	return 0;

}

/* CallBack API to execute XDNS Blob request */
pErr Process_XDNS_WebConfigRequest(void *Data)
{

        pErr execRetVal = NULL;

        execRetVal = (pErr) malloc (sizeof(Err));
        if (execRetVal == NULL )
        {
		fprintf(stderr, "%s : malloc failed\n",__FUNCTION__);
                return execRetVal;
        }

        memset(execRetVal,0,sizeof(Err));

        execRetVal->ErrorCode = BLOB_EXEC_SUCCESS;

        xdnsdoc_t *xd = (xdnsdoc_t *) Data ;


	fprintf(stderr, "%s : xd->table_param->entries_count is %ld\n",__FUNCTION__,(long int)xd->table_param->entries_count);
	fprintf(stderr, "XDNS configurartion recieved\n");

	/*clean Backup cache and take back of orginal cache*/
	clear_xdns_cache(&XDNS_tmp_bck);
	backup_xdns_cache(&XDNS_Data_Cache,&XDNS_tmp_bck);
	
	/*clean orginal cache and set XDNS config*/
	clear_xdns_cache(&XDNS_Data_Cache);

        int ret  = set_xdns_conf(xd, &XDNS_Data_Cache) ;
        if ( 0 != ret )
        {
            if ( INVALID_IP == ret )
            {
		fprintf(stderr, "%s : Invalid IP\n",__FUNCTION__);
                execRetVal->ErrorCode = INVALID_IP;

                strncpy(execRetVal->ErrorMsg,"Invalid IP",sizeof(execRetVal->ErrorMsg)-1);

            }
            else if ( INVALID_MAC == ret )
            {
		fprintf(stderr, "%s : Invalid MAC\n",__FUNCTION__);
                execRetVal->ErrorCode = INVALID_MAC;

                strncpy(execRetVal->ErrorMsg,"Invalid MAC",sizeof(execRetVal->ErrorMsg)-1);

            }

            //xdnsdoc_destroy( xd );

            return execRetVal;
        }
	//fprintf(stderr, "printing config needed to be applied.\n");
	//print_xdns_cache(&XDNS_Data_Cache);

        int ret1  = apply_XDNS_cache_ToDB(&XDNS_Data_Cache) ;
        if ( 0 != ret1 )
        {
            if ( FILE_OPEN_ERROR == ret1 )
            {
                fprintf(stderr, "%s : FILE_OPEN_ERROR\n",__FUNCTION__);
                execRetVal->ErrorCode = FILE_OPEN_ERROR;

                strncpy(execRetVal->ErrorMsg,"FILE_OPEN_ERROR while apply",sizeof(execRetVal->ErrorMsg)-1);

            }
            else if ( SYSCFG_FAILURE == ret1 )
            {
                fprintf(stderr, "%s : SYSCFG_FAILURE\n",__FUNCTION__);
                execRetVal->ErrorCode = INVALID_MAC;

                strncpy(execRetVal->ErrorMsg,"SYSCFG_FAILURE while apply",sizeof(execRetVal->ErrorMsg)-1);

            }

            //xdnsdoc_destroy( xd );

            return execRetVal;
        }

	fprintf(stderr, "%s :XDNS configurartion applied\n",__FUNCTION__);

	fprintf(stderr, "xd->enable_xdns %s\n", xd->enable_xdns?"true":"false");
	fprintf(stderr, "xd->default_ipv4 %s\n", xd->default_ipv4);
	fprintf(stderr, "xd->default_ipv6 %s\n", xd->default_ipv6);
	fprintf(stderr, "xd->default_tag %s\n", xd->default_tag);
	fprintf(stderr, "xd->table_param->entries_count %zu\n", xd->table_param->entries_count);
        int i;
        for(i = 0; i < (int)xd->table_param->entries_count ; i++)
        {

		fprintf(stderr, "xd->table_param->entries[%d].dns_mac %s\n",i, xd->table_param->entries[i].dns_mac);
		fprintf(stderr, "xd->table_param->entries[%d].dns_ipv4 %s\n",i, xd->table_param->entries[i].dns_ipv4);
		fprintf(stderr, "xd->table_param->entries[%d].dns_ipv6 %s\n",i, xd->table_param->entries[i].dns_ipv6);
		fprintf(stderr, "xd->table_param->entries[%d].dns_tag %s\n",i, xd->table_param->entries[i].dns_tag);

        }

        //xdnsdoc_destroy( xd );

        return execRetVal;

}

/* Callback function to rollback when XDNS blob execution fails */
int rollback_XDNS()
{
	// return 0 to notify framework when rollback is success
	fprintf(stderr, "%s Entered \n",__FUNCTION__);

  	int ret = 0;
    	ret = apply_XDNS_cache_ToDB(&XDNS_tmp_bck);;

    	backup_xdns_cache(&XDNS_tmp_bck,&XDNS_Data_Cache);

    return ret ;
}

void freeResources_XDNS(void *arg)
{

	fprintf(stderr, "%s Entered \n",__FUNCTION__);    
    
	execData *blob_exec_data  = (execData*) arg;

	if(blob_exec_data != NULL)
	{
		xdnsdoc_t *xd = (xdnsdoc_t *) blob_exec_data->user_data ;
		if ( xd != NULL )
		{
		xdnsdoc_destroy( xd );
		xd = NULL;
		}
		free(blob_exec_data);
		blob_exec_data = NULL ;
	}
}
