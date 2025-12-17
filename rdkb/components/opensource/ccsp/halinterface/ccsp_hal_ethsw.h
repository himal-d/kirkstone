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

/**********************************************************************

    module: ccsp_hal_ethsw.h

        For CCSP Component:  Ccsp Provisioning & Managment

    ---------------------------------------------------------------

    description:

        This header file defines the structures and function prototypes
        for Ethernet Switch control.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Cisco

**********************************************************************/

/**
* @file ccsp_hal_ethsw.h
* @author Cisco
* @brief For CCSP Component:  Ccsp Provisioning & Managment
*
* @description This header file defines the structures and function prototypes for Ethernet Switch control.
*/

#ifndef __CCSP_HAL_ETHSW_H__
#define __CCSP_HAL_ETHSW_H__

/**
* @defgroup ETHSW_HAL  Ethernet Switch HAL
*
* @defgroup ETHSW_HAL_TYPES  Ethernet Switch HAL Data Types
* @ingroup  ETHSW_HAL
*
* @defgroup ETHSW_HAL_APIS Ethernet Switch HAL  APIs
* @ingroup  ETHSW_HAL
*
**/


/**
 * @addtogroup ETHSW_HAL_TYPES
 * @{
 */

/**********************************************************************
               CONSTANT DEFINITIONS
**********************************************************************/

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef ULLONG
#define ULLONG unsigned long long
#endif

#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef BOOLEAN
#define BOOLEAN  UCHAR
#endif

#ifndef INT
#define INT   int
#endif

#ifndef UINT
#define UINT unsigned int
#endif

#ifndef TRUE
#define TRUE     1
#endif

#ifndef FALSE
#define FALSE    0
#endif

#ifndef ENABLE
#define ENABLE   1
#endif

#ifndef RETURN_OK
#define RETURN_OK   0
#endif

#ifndef RETURN_ERR
#define RETURN_ERR   -1
#endif

#ifndef ETHWAN_DEF_INTF_NUM
/*
* ETH WAN Physical Interface Number Assignment - Should eventually move away from Compile Time
* Utilized by Auto WAN feature in provisioning Apps & CCSP Eth Agent with Ethernet WAN Feature, CcspHalExtSw_setEthWanPort()
* ETh WAN HAL is 0 based
*/
#if defined (ETH_6_PORTS)
#define ETHWAN_DEF_INTF_NUM 5
#elif defined (ETH_5_PORTS)
#if defined (_SCER11BEL_PRODUCT_REQ_)
#define ETHWAN_DEF_INTF_NUM 5
#else
#define ETHWAN_DEF_INTF_NUM 4
#endif
#elif defined (ETH_4_PORTS)
#if defined(_XB10_PRODUCT_REQ_)
#define ETHWAN_DEF_INTF_NUM 1
#else
#define ETHWAN_DEF_INTF_NUM 3
#endif
#elif defined (ETH_2_PORTS) && defined (MODEM_ONLY_SUPPORT)
#define ETHWAN_DEF_INTF_NUM 0 
#else
/* Default to Physical Port #1 for ETH WAN */
#define ETHWAN_DEF_INTF_NUM 0
#endif
#endif

#ifndef ETHWAN_INTERFACE_NAME_MAX_LENGTH
/*
* Define a MAX ETH WAN Interface Name Length for GetEthWanInterfaceName
* TO DO: GetEthWanInterfaceName HAL/API needs to be updated to pass in buffer size as well
*/
#define ETHWAN_INTERFACE_NAME_MAX_LENGTH   32
#endif

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

typedef enum
_CCSP_HAL_ETHSW_PORT
{
    CCSP_HAL_ETHSW_EthPort1  = 1,
    CCSP_HAL_ETHSW_EthPort2,
    CCSP_HAL_ETHSW_EthPort3,
    CCSP_HAL_ETHSW_EthPort4,
    CCSP_HAL_ETHSW_EthPort5,
    CCSP_HAL_ETHSW_EthPort6,
    CCSP_HAL_ETHSW_EthPort7,
    CCSP_HAL_ETHSW_EthPort8,

    CCSP_HAL_ETHSW_Moca1,
    CCSP_HAL_ETHSW_Moca2,

    CCSP_HAL_ETHSW_Wlan1,
    CCSP_HAL_ETHSW_Wlan2,
    CCSP_HAL_ETHSW_Wlan3,
    CCSP_HAL_ETHSW_Wlan4,

    CCSP_HAL_ETHSW_Processor1,
    CCSP_HAL_ETHSW_Processor2,

    CCSP_HAL_ETHSW_InterconnectPort1,
    CCSP_HAL_ETHSW_InterconnectPort2,

    CCSP_HAL_ETHSW_MgmtPort,
    CCSP_HAL_ETHSW_PortMax
}
CCSP_HAL_ETHSW_PORT, *PCCSP_HAL_ETHSW_PORT;


typedef enum
_CCSP_HAL_ETHSW_LINK_RATE
{
    CCSP_HAL_ETHSW_LINK_NULL      = 0,
    CCSP_HAL_ETHSW_LINK_10Mbps,
    CCSP_HAL_ETHSW_LINK_100Mbps,
    CCSP_HAL_ETHSW_LINK_1Gbps,
    CCSP_HAL_ETHSW_LINK_2_5Gbps,
    CCSP_HAL_ETHSW_LINK_5Gbps,
    CCSP_HAL_ETHSW_LINK_10Gbps,
    CCSP_HAL_ETHSW_LINK_Auto
}
CCSP_HAL_ETHSW_LINK_RATE, *PCCSP_HAL_ETHSW_LINK_RATE;


typedef enum
_CCSP_HAL_ETHSW_DUPLEX_MODE
{
    CCSP_HAL_ETHSW_DUPLEX_Auto    = 0,
    CCSP_HAL_ETHSW_DUPLEX_Half,
    CCSP_HAL_ETHSW_DUPLEX_Full
}
CCSP_HAL_ETHSW_DUPLEX_MODE, *PCCSP_HAL_ETHSW_DUPLEX_MODE;


typedef enum
_CCSP_HAL_ETHSW_LINK_STATUS
{
    CCSP_HAL_ETHSW_LINK_Up        = 0,
    CCSP_HAL_ETHSW_LINK_Down,
    CCSP_HAL_ETHSW_LINK_Disconnected
}
CCSP_HAL_ETHSW_LINK_STATUS, *PCCSP_HAL_ETHSW_LINK_STATUS;


typedef enum
_CCSP_HAL_ETHSW_ADMIN_STATUS
{
    CCSP_HAL_ETHSW_AdminUp        = 0,
    CCSP_HAL_ETHSW_AdminDown,
    CCSP_HAL_ETHSW_AdminTest
}
CCSP_HAL_ETHSW_ADMIN_STATUS, *PCCSP_HAL_ETHSW_ADMIN_STATUS;


typedef  struct
_CCSP_HAL_ETH_STATS
{
    ULLONG                          BytesSent;
    ULLONG                          BytesReceived;
    ULONG                           PacketsSent;
    ULONG                           PacketsReceived;
    ULONG                           ErrorsSent;
    ULONG                           ErrorsReceived;
    ULONG                           UnicastPacketsSent;
    ULONG                           UnicastPacketsReceived;
    ULONG                           DiscardPacketsSent;
    ULONG                           DiscardPacketsReceived;
    ULONG                           MulticastPacketsSent;
    ULONG                           MulticastPacketsReceived;
    ULONG                           BroadcastPacketsSent;
    ULONG                           BroadcastPacketsReceived;
    ULONG                           UnknownProtoPacketsReceived;
}
CCSP_HAL_ETH_STATS, *PCCSP_HAL_ETH_STATS;

/**
 * @}
 */


/**
 * @addtogroup ETHSW_HAL_APIS
 * @{
 */

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

/* CcspHalEthSwInit :  */
/**
* @description Do what needed to intialize the Eth hal.
*
* @param None
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwInit
    (
        void
    );


/* CcspHalEthSwGetPortStatus :  */
/**
* @description Retrieve the current port status - link speed, duplex mode etc.

* @param[in] PortId Port ID as defined in enum CCSP_HAL_ETHSW_PORT.
*                   \n Port ID value ranges from 1 to 20.
* <pre>
*                   Possible enum Values:
*                       CCSP_HAL_ETHSW_EthPort1             = 1
*                       CCSP_HAL_ETHSW_EthPort2             = 2
*                       CCSP_HAL_ETHSW_EthPort3             = 3
*                       CCSP_HAL_ETHSW_EthPort4             = 4
*                       CCSP_HAL_ETHSW_EthPort5             = 5
*                       CCSP_HAL_ETHSW_EthPort6             = 6
*                       CCSP_HAL_ETHSW_EthPort7             = 7
*                       CCSP_HAL_ETHSW_EthPort8             = 8
*                       CCSP_HAL_ETHSW_Moca1                = 9
*                       CCSP_HAL_ETHSW_Moca2                = 10
*                       CCSP_HAL_ETHSW_Wlan1                = 11
*                       CCSP_HAL_ETHSW_Wlan2                = 12
*                       CCSP_HAL_ETHSW_Wlan3                = 13
*                       CCSP_HAL_ETHSW_Wlan4                = 14
*                       CCSP_HAL_ETHSW_Processor1           = 15
*                       CCSP_HAL_ETHSW_Processor2           = 16
*                       CCSP_HAL_ETHSW_InterconnectPort1    = 17
*                       CCSP_HAL_ETHSW_InterconnectPort2    = 18
*                       CCSP_HAL_ETHSW_MgmtPort             = 19
*                       CCSP_HAL_ETHSW_PortMax              = 20
* </pre>
* @param[out] pLinkRate Receives the current link rate, as in enum CCSP_HAL_ETHSW_LINK_RATE.
*                       \n The value ranges from 0 to 7.
* <pre>
*                       Possible enum Values:
*                           CCSP_HAL_ETHSW_LINK_NULL        = 0
*                           CCSP_HAL_ETHSW_LINK_10Mbps      = 1
*                           CCSP_HAL_ETHSW_LINK_100Mbps     = 2
*                           CCSP_HAL_ETHSW_LINK_1Gbps       = 3
*                           CCSP_HAL_ETHSW_LINK_2_5Gbps     = 4
*                           CCSP_HAL_ETHSW_LINK_5Gbps       = 5
*                           CCSP_HAL_ETHSW_LINK_10Gbps      = 6
*                           CCSP_HAL_ETHSW_LINK_Auto        = 7
* </pre>
* @param[out] pDuplexMode Receives the current duplex mode, as in enum CCSP_HAL_ETHSW_DUPLEX_MODE.
*                         \n The value ranges from 0 to 2.
* <pre>
*                         Possible enum Values:
*                             CCSP_HAL_ETHSW_DUPLEX_Auto     = 0
*                             CCSP_HAL_ETHSW_DUPLEX_Half     = 1
*                             CCSP_HAL_ETHSW_DUPLEX_Full     = 2
* </pre>
* @param[out] pStatus Receives the current link status, as in enum CCSP_HAL_ETHSW_LINK_STATUS.
*                     \n The value ranges from 0 to 2.
* <pre>
*                     Possible enum Values:
*                         CCSP_HAL_ETHSW_LINK_Up              = 0
*                         CCSP_HAL_ETHSW_LINK_Down            = 1
*                         CCSP_HAL_ETHSW_LINK_Disconnected    = 2
* </pre>
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwGetPortStatus
    (
        CCSP_HAL_ETHSW_PORT         PortId,
        PCCSP_HAL_ETHSW_LINK_RATE   pLinkRate,
        PCCSP_HAL_ETHSW_DUPLEX_MODE pDuplexMode,
        PCCSP_HAL_ETHSW_LINK_STATUS pStatus
    );


/* CcspHalEthSwGetPortCfg :  */
/**
* @description Retrieve the current port config - link speed, duplex mode, etc.

* @param[in] PortId Port ID as defined in enum CCSP_HAL_ETHSW_PORT.
*                   \n Port ID value ranges from 1 to 20.
* <pre>
*                   Possible enum Values:
*                       CCSP_HAL_ETHSW_EthPort1             = 1
*                       CCSP_HAL_ETHSW_EthPort2             = 2
*                       CCSP_HAL_ETHSW_EthPort3             = 3
*                       CCSP_HAL_ETHSW_EthPort4             = 4
*                       CCSP_HAL_ETHSW_EthPort5             = 5
*                       CCSP_HAL_ETHSW_EthPort6             = 6
*                       CCSP_HAL_ETHSW_EthPort7             = 7
*                       CCSP_HAL_ETHSW_EthPort8             = 8
*                       CCSP_HAL_ETHSW_Moca1                = 9
*                       CCSP_HAL_ETHSW_Moca2                = 10
*                       CCSP_HAL_ETHSW_Wlan1                = 11
*                       CCSP_HAL_ETHSW_Wlan2                = 12
*                       CCSP_HAL_ETHSW_Wlan3                = 13
*                       CCSP_HAL_ETHSW_Wlan4                = 14
*                       CCSP_HAL_ETHSW_Processor1           = 15
*                       CCSP_HAL_ETHSW_Processor2           = 16
*                       CCSP_HAL_ETHSW_InterconnectPort1    = 17
*                       CCSP_HAL_ETHSW_InterconnectPort2    = 18
*                       CCSP_HAL_ETHSW_MgmtPort             = 19
*                       CCSP_HAL_ETHSW_PortMax              = 20
* </pre>
* @param[out] pLinkRate Receives the current link rate, as in enum CCSP_HAL_ETHSW_LINK_RATE.
*                       \n The value ranges from 0 to 7.
* <pre>
*                       Possible enum Values:
*                           CCSP_HAL_ETHSW_LINK_NULL        = 0
*                           CCSP_HAL_ETHSW_LINK_10Mbps      = 1
*                           CCSP_HAL_ETHSW_LINK_100Mbps     = 2
*                           CCSP_HAL_ETHSW_LINK_1Gbps       = 3
*                           CCSP_HAL_ETHSW_LINK_2_5Gbps     = 4
*                           CCSP_HAL_ETHSW_LINK_5Gbps       = 5
*                           CCSP_HAL_ETHSW_LINK_10Gbps      = 6
*                           CCSP_HAL_ETHSW_LINK_Auto        = 7
* </pre>
* @param[out] pDuplexMode Receives the current duplex mode, as in enum CCSP_HAL_ETHSW_DUPLEX_MODE.
*                         \n The value ranges from 0 to 2.
* <pre>
*                         Possible enum Values:
*                             CCSP_HAL_ETHSW_DUPLEX_Auto     = 0
*                             CCSP_HAL_ETHSW_DUPLEX_Half     = 1
*                             CCSP_HAL_ETHSW_DUPLEX_Full     = 2
* </pre>

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwGetPortCfg
    (
        CCSP_HAL_ETHSW_PORT         PortId,
        PCCSP_HAL_ETHSW_LINK_RATE   pLinkRate,
        PCCSP_HAL_ETHSW_DUPLEX_MODE pDuplexMode
    );


/* CcspHalEthSwSetPortCfg :  */
/**
* @description Set the port configuration - link speed, duplex mode.

* @param[in] PortId Port ID as defined in CCSP_HAL_ETHSW_PORT.
*                   \n Port ID value ranges from 1 to 20.
* <pre>
*                   Possible enum Values:
*                       CCSP_HAL_ETHSW_EthPort1             = 1
*                       CCSP_HAL_ETHSW_EthPort2             = 2
*                       CCSP_HAL_ETHSW_EthPort3             = 3
*                       CCSP_HAL_ETHSW_EthPort4             = 4
*                       CCSP_HAL_ETHSW_EthPort5             = 5
*                       CCSP_HAL_ETHSW_EthPort6             = 6
*                       CCSP_HAL_ETHSW_EthPort7             = 7
*                       CCSP_HAL_ETHSW_EthPort8             = 8
*                       CCSP_HAL_ETHSW_Moca1                = 9
*                       CCSP_HAL_ETHSW_Moca2                = 10
*                       CCSP_HAL_ETHSW_Wlan1                = 11
*                       CCSP_HAL_ETHSW_Wlan2                = 12
*                       CCSP_HAL_ETHSW_Wlan3                = 13
*                       CCSP_HAL_ETHSW_Wlan4                = 14
*                       CCSP_HAL_ETHSW_Processor1           = 15
*                       CCSP_HAL_ETHSW_Processor2           = 16
*                       CCSP_HAL_ETHSW_InterconnectPort1    = 17
*                       CCSP_HAL_ETHSW_InterconnectPort2    = 18
*                       CCSP_HAL_ETHSW_MgmtPort             = 19
*                       CCSP_HAL_ETHSW_PortMax              = 20
* </pre>
* @param[in] LinkRate Set the link rate, as in CCSP_HAL_ETHSW_LINK_RATE.
*                     \n The value ranges from 0 to 7.
* <pre>
*                     Possible enum Values:
*                         CCSP_HAL_ETHSW_LINK_NULL        = 0
*                         CCSP_HAL_ETHSW_LINK_10Mbps      = 1
*                         CCSP_HAL_ETHSW_LINK_100Mbps     = 2
*                         CCSP_HAL_ETHSW_LINK_1Gbps       = 3
*                         CCSP_HAL_ETHSW_LINK_2_5Gbps     = 4
*                         CCSP_HAL_ETHSW_LINK_5Gbps       = 5
*                         CCSP_HAL_ETHSW_LINK_10Gbps      = 6
*                         CCSP_HAL_ETHSW_LINK_Auto        = 7
* </pre>
* @param[in] DuplexMode Set the duplex mode, as in CCSP_HAL_ETHSW_DUPLEX_MODE.
*                       \n The value ranges from 0 to 2.
* <pre>
*                       Possible enum Values:
*                           CCSP_HAL_ETHSW_DUPLEX_Auto     = 0
*                           CCSP_HAL_ETHSW_DUPLEX_Half     = 1
*                           CCSP_HAL_ETHSW_DUPLEX_Full     = 2
* </pre>

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwSetPortCfg
    (
        CCSP_HAL_ETHSW_PORT         PortId,
        CCSP_HAL_ETHSW_LINK_RATE    LinkRate,
        CCSP_HAL_ETHSW_DUPLEX_MODE  DuplexMode
    );


/* CcspHalEthSwGetPortAdminStatus :  */
/**
* @description Retrieve the current port admin status.

* @param[in] PortId Port ID as defined in CCSP_HAL_ETHSW_PORT.
*                   \n Port ID value ranges from 1 to 20.
* <pre>
*                   Possible enum Values:
*                       CCSP_HAL_ETHSW_EthPort1             = 1
*                       CCSP_HAL_ETHSW_EthPort2             = 2
*                       CCSP_HAL_ETHSW_EthPort3             = 3
*                       CCSP_HAL_ETHSW_EthPort4             = 4
*                       CCSP_HAL_ETHSW_EthPort5             = 5
*                       CCSP_HAL_ETHSW_EthPort6             = 6
*                       CCSP_HAL_ETHSW_EthPort7             = 7
*                       CCSP_HAL_ETHSW_EthPort8             = 8
*                       CCSP_HAL_ETHSW_Moca1                = 9
*                       CCSP_HAL_ETHSW_Moca2                = 10
*                       CCSP_HAL_ETHSW_Wlan1                = 11
*                       CCSP_HAL_ETHSW_Wlan2                = 12
*                       CCSP_HAL_ETHSW_Wlan3                = 13
*                       CCSP_HAL_ETHSW_Wlan4                = 14
*                       CCSP_HAL_ETHSW_Processor1           = 15
*                       CCSP_HAL_ETHSW_Processor2           = 16
*                       CCSP_HAL_ETHSW_InterconnectPort1    = 17
*                       CCSP_HAL_ETHSW_InterconnectPort2    = 18
*                       CCSP_HAL_ETHSW_MgmtPort             = 19
*                       CCSP_HAL_ETHSW_PortMax              = 20
* </pre>
* @param[out] pAdminStatus  Receives the current admin status.
*                           \n The value ranges from 0 to 2 and is defined in CCSP_HAL_ETHSW_ADMIN_STATUS enum.
* <pre>
*                           Possible enum Values:
*                               CCSP_HAL_ETHSW_AdminUp       = 0
*                               CCSP_HAL_ETHSW_AdminDown     = 1
*                               CCSP_HAL_ETHSW_AdminTest     = 2
* </pre>
*

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwGetPortAdminStatus
    (
        CCSP_HAL_ETHSW_PORT           PortId,
        PCCSP_HAL_ETHSW_ADMIN_STATUS  pAdminStatus
    );


/* CcspHalEthSwSetPortAdminStatus :  */
/**
* @description Set the ethernet port admin status.
* @param[in] PortId Port ID as defined in enum CCSP_HAL_ETHSW_PORT.
*                   \n Port ID value ranges from 1 to 20.
* <pre>
*                   Possible enum Values:
*                       CCSP_HAL_ETHSW_EthPort1             = 1
*                       CCSP_HAL_ETHSW_EthPort2             = 2
*                       CCSP_HAL_ETHSW_EthPort3             = 3
*                       CCSP_HAL_ETHSW_EthPort4             = 4
*                       CCSP_HAL_ETHSW_EthPort5             = 5
*                       CCSP_HAL_ETHSW_EthPort6             = 6
*                       CCSP_HAL_ETHSW_EthPort7             = 7
*                       CCSP_HAL_ETHSW_EthPort8             = 8
*                       CCSP_HAL_ETHSW_Moca1                = 9
*                       CCSP_HAL_ETHSW_Moca2                = 10
*                       CCSP_HAL_ETHSW_Wlan1                = 11
*                       CCSP_HAL_ETHSW_Wlan2                = 12
*                       CCSP_HAL_ETHSW_Wlan3                = 13
*                       CCSP_HAL_ETHSW_Wlan4                = 14
*                       CCSP_HAL_ETHSW_Processor1           = 15
*                       CCSP_HAL_ETHSW_Processor2           = 16
*                       CCSP_HAL_ETHSW_InterconnectPort1    = 17
*                       CCSP_HAL_ETHSW_InterconnectPort2    = 18
*                       CCSP_HAL_ETHSW_MgmtPort             = 19
*                       CCSP_HAL_ETHSW_PortMax              = 20
* </pre>
* @param[in] AdminStatus Set the admin status, as defined in CCSP_HAL_ETHSW_ADMIN_STATUS enum.
*                        \n The values that can be set are 0 and 1.
* <pre>
*                        Possible enum Values:
*                            CCSP_HAL_ETHSW_AdminUp       = 0
*                            CCSP_HAL_ETHSW_AdminDown     = 1
*                            CCSP_HAL_ETHSW_AdminTest     = 2
* </pre>
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwSetPortAdminStatus
    (
        CCSP_HAL_ETHSW_PORT         PortId,
        CCSP_HAL_ETHSW_ADMIN_STATUS AdminStatus
    );


/* CcspHalEthSwSetAgingSpeed :  */
/**
* @description Set the ethernet port configuration - admin up/down, link speed, duplex mode.

* @param[in] PortId Port ID as defined in CCSP_HAL_ETHSW_PORT.
*                   \n Port ID value ranges from 1 to 20.
* <pre>
*                   Possible enum Values:
*                       CCSP_HAL_ETHSW_EthPort1             = 1
*                       CCSP_HAL_ETHSW_EthPort2             = 2
*                       CCSP_HAL_ETHSW_EthPort3             = 3
*                       CCSP_HAL_ETHSW_EthPort4             = 4
*                       CCSP_HAL_ETHSW_EthPort5             = 5
*                       CCSP_HAL_ETHSW_EthPort6             = 6
*                       CCSP_HAL_ETHSW_EthPort7             = 7
*                       CCSP_HAL_ETHSW_EthPort8             = 8
*                       CCSP_HAL_ETHSW_Moca1                = 9
*                       CCSP_HAL_ETHSW_Moca2                = 10
*                       CCSP_HAL_ETHSW_Wlan1                = 11
*                       CCSP_HAL_ETHSW_Wlan2                = 12
*                       CCSP_HAL_ETHSW_Wlan3                = 13
*                       CCSP_HAL_ETHSW_Wlan4                = 14
*                       CCSP_HAL_ETHSW_Processor1           = 15
*                       CCSP_HAL_ETHSW_Processor2           = 16
*                       CCSP_HAL_ETHSW_InterconnectPort1    = 17
*                       CCSP_HAL_ETHSW_InterconnectPort2    = 18
*                       CCSP_HAL_ETHSW_MgmtPort             = 19
*                       CCSP_HAL_ETHSW_PortMax              = 20
* </pre>
* @param[in] AgingSpeed  Integer value of aging speed.
*                        \n It is a vendor specific value.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwSetAgingSpeed
    (
        CCSP_HAL_ETHSW_PORT         PortId,
        INT                         AgingSpeed
    );

/* CcspHalEthSwLocatePortByMacAddress  :  */
/**
* @description Query Moca and External switch port for the given MAC address.

* @param[in] mac Pointer to character array holding the MAC address to search for. The buffer size is 6 bytes.
*                \n The format of the MAC address is given as an example: "00:1A:2B:11:B2:33".
* @param[out] port Pointer to an integer value holding the external port. The possible return values are: 0: MoCA, 1-4: Ethernet port.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected or MAC address is not found.
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwLocatePortByMacAddress
    (
        unsigned char * mac,
        INT * port
    );


//>>zqiu
//Ethernet HAL for client association/disassociation notification.

/**
 * @}
 */

/**
 * @addtogroup ETHSW_HAL_TYPES
 * @{
 */

typedef struct _eth_device {
    UCHAR eth_devMacAddress[6];
    INT  eth_port;      //!< which external port the device attached to. index start from 0
    INT  eth_vlanid;    //!< what vlan ID the the port tagged.
    INT  eth_devTxRate;     // optional
    INT  eth_devRxRate;     // optional
    BOOLEAN eth_Active;     //device is online/offline
} eth_device_t;
/**
 * @}
 */


/**
 * @addtogroup ETHSW_HAL_APIS
 * @{
 */

/* CcspHalExtSw_getAssociatedDevice  :  */
/**
* @description The HAL need to allocate array and return the array size by output_array_size.

* @param[out] output_array_size Pointer to unsigned long integer holding the output array size to be returned.
*                              \n The range of acceptable values is 0 to 4,294,967,296.
* @param[out] output_struct Pointer to an array of structures of type eth_device_t.
*                           \n The structure members are defined as below:
* <pre>
*    eth_devMacAddress[6]    - It is a 6 bytes unsigned character array that represents the MAC Address.
*                              The format of the MAC address is given as an example: "00:1A:2B:11:B2:33".
*    eth_port                - Which external port the device attached to. It is an integer value.
*                              \n The valid range of eth_Port is from 0 to MaxEthPort-1, where MaxEthPort is platform specific.
*                              It is a vendor specific value.
*    eth_vlanid              - It is an integer value which represents What vlan ID the port is tagged.
*                              The valid VLAN IDs range from 1 to 4094.It is a vendor specific value.
*    eth_devTxRate           - Tx Speed. It is an unsigned integer value. It is a vendor specific value.
*    eth_devRxRate           - Rx Speed. IT is an unsigned integer value. It is a vendor specific value.
*    eth_Active;             - It is a boolean value which represents whether the device is online/offline. Possible values: TRUE or FALSE.
* </pre>
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected or MAC address is not found.
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT CcspHalExtSw_getAssociatedDevice(ULONG *output_array_size, eth_device_t **output_struct);

/* CcspHalExtSw_ethAssociatedDevice_callback  :  */
/**
* @description This call back will be invoked when new Ethernet client come to associate to AP, or existing Ethernet client left.
* @param[out] eth_dev Pointer to an array of structures of type eth_device_t.
*                     \n The structure members are defined as below:
* <pre>
*    eth_devMacAddress[6]    - It is a 6 bytes unsigned character array that represents the MAC Address.
*                              The format of the MAC address is given as an example: "00:1A:2B:11:B2:33".
*    eth_port                - Which external port the device attached to. It is an integer value.
*                              \n The valid range of eth_Port is from 0 to MaxEthPort-1, where MaxEthPort is platform specific.
*                              It is a vendor specific value.
*    eth_vlanid              - It is an integer value which represents What vlan ID the port is tagged.
*                              The valid VLAN IDs range from 1 to 4094.It is a vendor specific value.
*    eth_devTxRate           - Tx Speed. It is an unsigned integer value. It is a vendor specific value.
*    eth_devRxRate           - Rx Speed. IT is an unsigned integer value. It is a vendor specific value.
*    eth_Active;             - It is a boolean value which represents whether the device is online/offline. Possible values: TRUE or FALSE.
* </pre>
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected or MAC address is not found.
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
typedef INT ( * CcspHalExtSw_ethAssociatedDevice_callback)(eth_device_t *eth_dev);

/* CcspHalExtSw_ethAssociatedDevice_callback_register  :  */
/**
* @description Callback registration function.

* @param[in] callback_proc Callback prototype.
*            \n The parameters are defined below:
*            \n eth_dev - Output parameter which is a pointer to an array of structures of type eth_device_t.
*            \n The structure members are defined as below:
* <pre>
*    eth_devMacAddress[6]    - It is a 6 bytes unsigned character array that represents the MAC Address.
*                              The format of the MAC address is given as an example: "00:1A:2B:11:B2:33".
*    eth_port                - Which external port the device attached to. It is an integer value.
*                              \n The valid range of eth_Port is from 0 to MaxEthPort-1, where MaxEthPort is platform specific.
*                              It is a vendor specific value.
*    eth_vlanid              - It is an integer value which represents What vlan ID the port is tagged.
*                              The valid VLAN IDs range from 1 to 4094.It is a vendor specific value.
*    eth_devTxRate           - Tx Speed. It is an unsigned integer value. It is a vendor specific value.
*    eth_devRxRate           - Rx Speed. IT is an unsigned integer value. It is a vendor specific value.
*    eth_Active;             - It is a boolean value which represents whether the device is online/offline. Possible values: TRUE or FALSE.
* </pre>
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected or MAC address is not found.
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
void CcspHalExtSw_ethAssociatedDevice_callback_register(CcspHalExtSw_ethAssociatedDevice_callback callback_proc); //!< Callback registration function.

#ifdef FEATURE_RDKB_WAN_MANAGER
#ifdef FEATURE_RDKB_AUTO_PORT_SWITCH

/* CcspHalExtSw_ethPortConfigure  :  */
/**
* @description Configure Ethernet port.

* @param[in] ifname A pointer to the character array that will hold the interface name.
*                   \n The possible values are: eth0, eth1, eth2, eth3.
*                   \n The buffer size should be atleast 32 bytes.
* @param[in] WanMode Boolean value to hold the EthernetWAN enable status. The possible values are: True, False.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected or MAC address is not found.
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
int CcspHalExtSw_ethPortConfigure(char *ifname, BOOLEAN WanMode);

#endif  //FEATURE_RDKB_AUTO_PORT_SWITCH
#endif
//<<

/* CcspHalExtSw_getEthWanEnable() function */
/**
* @description Get EthernetWAN enable status.
*
* @param[out] pFlag Pointer to BOOLEAN to store current EthernetWAN enable value which is returned.
*                   \n Values: 1- Enabled, 0- Disabled.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @sideeffect None
*/
INT
CcspHalExtSw_getEthWanEnable
  (
    BOOLEAN * pFlag
  );

/* CcspHalExtSw_setEthWanEnable() function */
/**
* @description Enable/Disable EthernetWAN functionality.
*
* @param[in] Flag   Boolean variable holding the EthernetWAN enable value.
*                   \n Possible values: 1- Enable, 0- Disable.

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @sideeffect None
*/
INT
CcspHalExtSw_setEthWanEnable
  (
    BOOLEAN Flag
  );

#ifdef FEATURE_RDKB_AUTO_PORT_SWITCH
/* CcspHalExtSw_getCurrentWanHWConf() function */
/**
* @description Returns running HW configuration.
*
* @param None
*
* @return Returns running HW configuration.
* @retval TRUE if WAN is enabled.
* @retval FALSE IF LAN is enabled.
*
* @sideeffect None
*/
BOOLEAN CcspHalExtSw_getCurrentWanHWConf();
#endif

/* CcspHalExtSw_getEthWanPort() function */
/**
* @description Get EthernetWAN port number value.
*
* @param[out] pPort Pointer to unsigned integer value to store current EthernetWAN port number setting, to be returned.
*                   \n It is an unsigned integer value. It is a vendor specific value.
*                   \n The valid range of pPort is from 0 to MaxEthPort-1, where MaxEthPort is platform specific.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @sideeffect None
*/
INT
CcspHalExtSw_getEthWanPort
  (
    UINT * pPort
  );

/* CcspHalExtSw_setEthWanPort() function */
/**
* @description Set EthernetWAN interface/port number.
*
* @param[in] Port Unsigned integer value to set the EthernetWAN interface/port number.
*                   \n It is an unsigned integer value. It is a vendor specific value.
*                   \n The valid range of Port is from 0 to MaxEthPort-1, where MaxEthPort is platform specific.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @sideeffect None
*/
INT
CcspHalExtSw_setEthWanPort
  (
    UINT Port
  );

/* CcspHalEthSwGetEthPortStats :  */
/**
* Description: Retrieve the current port's statistics.

* @param[in] PortId Port ID as defined in CCSP_HAL_ETHSW_PORT.
*                   \n Port ID value ranges from 1 to 20.
* <pre>
*                   Possible enum Values:
*                       CCSP_HAL_ETHSW_EthPort1             = 1
*                       CCSP_HAL_ETHSW_EthPort2             = 2
*                       CCSP_HAL_ETHSW_EthPort3             = 3
*                       CCSP_HAL_ETHSW_EthPort4             = 4
*                       CCSP_HAL_ETHSW_EthPort5             = 5
*                       CCSP_HAL_ETHSW_EthPort6             = 6
*                       CCSP_HAL_ETHSW_EthPort7             = 7
*                       CCSP_HAL_ETHSW_EthPort8             = 8
*                       CCSP_HAL_ETHSW_Moca1                = 9
*                       CCSP_HAL_ETHSW_Moca2                = 10
*                       CCSP_HAL_ETHSW_Wlan1                = 11
*                       CCSP_HAL_ETHSW_Wlan2                = 12
*                       CCSP_HAL_ETHSW_Wlan3                = 13
*                       CCSP_HAL_ETHSW_Wlan4                = 14
*                       CCSP_HAL_ETHSW_Processor1           = 15
*                       CCSP_HAL_ETHSW_Processor2           = 16
*                       CCSP_HAL_ETHSW_InterconnectPort1    = 17
*                       CCSP_HAL_ETHSW_InterconnectPort2    = 18
*                       CCSP_HAL_ETHSW_MgmtPort             = 19
*                       CCSP_HAL_ETHSW_PortMax              = 20
* </pre>
* @param[out] pStats Pointer to structure of type PCCSP_HAL_ETH_STATS to receive the current port statistics to be returned.
* <pre>
*   The structure members are defined as below:
*       BytesSent                       - Unsigned long long value that represents the number of bytes sent. It is a vendor specific value.
*       BytesReceived                   - Unsigned long long value that represents the number of bytes received. It is a vendor specific value.
*       PacketsSent                     - Unsigned long value that represents the number of packets sent. It is a vendor specific value.
*       PacketsReceived                 - Unsigned long value that represents the number of packets received. It is a vendor specific value.
*       ErrorsSent                      - Unsigned long value that represents the number of errors sent. It is a vendor specific value.
*       ErrorsReceived                  - Unsigned long value that represents the number of errors received. It is a vendor specific value.
*       UnicastPacketsSent              - Unsigned long value that represents the number of unicast packets sent. It is a vendor specific value.
*       UnicastPacketsReceived          - Unsigned long value that represents the number of unicast packets received. It is a vendor specific value.
*       DiscardPacketsSent              - Unsigned long value that represents the number of discard packets sent. It is a vendor specific value.
*       DiscardPacketsReceived          - Unsigned long value that represents the number of discard packets received. It is a vendor specific value.
*       MulticastPacketsSent            - Unsigned long value that represents the number of multicast packets sent. It is a vendor specific value.
*       MulticastPacketsReceived        - Unsigned long value that represents the number of multicast packets received. It is a vendor specific value.
*       BroadcastPacketsSent            - Unsigned long value that represents the number of broadcast packets sent. It is a vendor specific value.
*       BroadcastPacketsReceived        - Unsigned long value that represents the number of broadcast packets received. It is a vendor specific value.
*       UnknownProtoPacketsReceived     - Unsigned long value that represents the number of unknown proto packets received. It is a vendor specific value.
* </pre>

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwGetEthPortStats
 (
    CCSP_HAL_ETHSW_PORT           PortId,
    PCCSP_HAL_ETH_STATS           pStats
 );
/**
 * @}
 */


/**
 * @addtogroup ETHSW_HAL_TYPES
 * @{
 */

/*
* @brief Define callback function pointers which needs to be called
* from provisioning abstraction layer when any provisioning
* event occurs.
*/
typedef void ( *fpEthWanLink_Up ) ( ) ;    /**< RDKB expects this callback once EthWan link is UP */
typedef void ( *fpEthWanLink_Down ) ( ) ;  /**< RDKB expects this callback once EthWan link is Down */

/*! \var typedef struct __appCallBack
*       \brief struct of pointers to the function pointers of callback functions.
*/

typedef struct __appCallBack
{
        fpEthWanLink_Up                    pGWP_act_EthWanLinkUP;
        fpEthWanLink_Down          pGWP_act_EthWanLinkDown;
}appCallBack;

/**
 * @}
 */

/**
 * @addtogroup ETHSW_HAL_APIS
 * @{
 */

/* GWP_RegisterEthWan_Callback */
/**
* @description This function will get used to register RDKB functions to the callback pointers.
*
* @param[in] obj struct of pointers to the function pointers.
* <pre>
*                The structure members are defined as below:
*                    pGWP_act_EthWanLinkUP   - RDKB expects this callback once EthWan link is UP.
*                    pGWP_act_EthWanLinkDown - RDKB expects this callback once EthWan link is Down.
* </pre>
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @sideeffect None
*/
void GWP_RegisterEthWan_Callback(appCallBack *obj);

/* GWP_GetEthWanLinkStatus :  */
/**
* @description Get the Ethwan Link status.
*
* @param None
*
* @return The status of Ethwan.
* @retval 1 if active(Link Up).
* @retval 0 if inactive(Link Down).
* @retval Less than 0 if failure, errno.
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT GWP_GetEthWanLinkStatus();

/* GWP_GetEthWanInterfaceName :  */
/**
* @description This function will get used to retrieve the ETHWAN interface name.
*
* @param[out] Interface Pointer to character array holding the interface name.  It is a vendor specific value.
*             \n The buffer size should be at least 64 bytes long.
* @param[in] maxSize Unsigned long integer which represents the maximum size.
*                    \n The range of maxsize is 11 to 262.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
GWP_GetEthWanInterfaceName
    (
        unsigned char * Interface,
        ULONG maxSize
    );


#define UP "up"
#define DOWN "down"

#endif /* __CCSP_HAL_ETHSW_H__ */

/**
 * @}
 */


