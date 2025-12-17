#!/bin/bash
##########################################################################
#
# Copyright 2018 Comcast Cable Communications Management, LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# SPDX-License-Identifier: Apache-2.0
##########################################################################
source $(dirname $(realpath ${0}))/advsec.sh

source /etc/utopia/service.d/log_capture_path.sh

export RUNTIME_BIN_DIR="$(dirname $(realpath ${0}))"

start_device_services()
{

if [ "$1" = "-enable" ]
then

    bridge_mode=`syscfg get bridge_mode`
    if [ "$bridge_mode" = "2" ]; then
        echo_t "Advanced Security : Device is in Bridge Mode, do not launch agent!" >> ${ADVSEC_AGENT_LOG_PATH}
        exit 0
    fi

    if [ "x$(advsec_is_agent_installed)" == "xYES" ]; then
        echo_t "Advanced Security : ${CUJO_AGENT_LOG} is installed on the device" >> ${ADVSEC_AGENT_LOG_PATH}
    else
        echo_t "Advanced Security : ${CUJO_AGENT_LOG} is not installed on the device..." >> ${ADVSEC_AGENT_LOG_PATH}
        exit 0
    fi

    if [ -f $ADVSEC_INITIALIZING ]; then
        echo_t "Advanced Security Service is already being initialized" >> ${ADVSEC_AGENT_LOG_PATH}
        exit 0
    fi

    touch $ADVSEC_INITIALIZING

    if [ -f $DAEMONS_HIBERNATING ]; then
        rm $DAEMONS_HIBERNATING
    fi

    wait_for_lanip

    start_agent_services

    touch $ADVSEC_INITIALIZED

    if [ "$DF_ENABLED" = "1" ]; then
        echo_t "Device_Finger_Printing_enabled:true"
    fi

    if [ "$ADVSEC_SB_ENABLED" = "1" ]
    then
        start_advsec_safe_browsing
    else
        echo_t "ADV_SECURITY_SAFE_BROWSING_DISABLE"
    fi
    if [ "$ADVSEC_SF_ENABLED" = "1" ]
    then
        start_advsec_softflowd
    else
        echo_t "ADV_SECURITY_SOFTFLOWD_DISABLE"
    fi

    if [ "$ADV_PC_ENABLED" = "1" ] && [ "$ADV_PC_RFC_ENABLED" = "1" ]; then
        advanced_parental_control_setup "-startAdvPC"
    fi

    if [ "$PRIVACY_PROTECTION_ENABLED" = "1" ] && [ "$PRIVACY_PROTECTION_RFC_ENABLED" = "1" ]; then
        privacy_protection_setup "-startPrivProt"
    fi

    if [ "$BOX_TYPE" != "XB3" ] && [ "$BOX_TYPE" != "XF3" ]; then
        if [ "$DF_ICMPv6_RFC_ENABLED" = "1" ]; then
            enable_icmpv6
        else
            disable_icmpv6
        fi
    fi

    if [ "$ADVSEC_WS_DISCOVERY_RFC_ENABLED" = "1" ]; then
            enable_wsdiscovery
    else
            disable_wsdiscovery
    fi

    if [ "$ADVSEC_OTM_RFC_ENABLED" = "1" ]; then
            enable_otm
    else
            disable_otm
    fi

    if [ "$ADVSEC_USERSPACE_RFC_ENABLED" = "1" ]; then
            enable_userspace
    else
            disable_userspace
    fi

    if [ "$ADVSEC_CUJOTRACER_RFC_ENABLED" = "1" ]; then
            enable_cujotracer
    else
            disable_cujotracer
    fi

    if [ "$ADVSEC_CUJOTELEMETRY_RFC_ENABLED" = "1" ]; then
            enable_cujotelemetry
    else
            disable_cujotelemetry
    fi

    if [ "$ADVSEC_RAPTR_RFC_ENABLED" = "1" ]; then
            enable_raptr
    else
            disable_raptr
    fi

    if [ "$ADVSEC_WIFIDATACOLLECTION_RFC_ENABLED" = "1" ]; then
            enable_wifidatacollection
    else
            disable_wifidatacollection
    fi

    if [ "$ADVSEC_LEVL_RFC_ENABLED" = "1" ]; then
            enable_levl
    else
            disable_levl
    fi

    if [ "$ADVSEC_AGENT_RFC_ENABLED" = "1" ]; then
            enable_agent
    else
            disable_agent
    fi

    if [ "$ADVSEC_SAFEBROWSING_RFC_ENABLED" = "1" ]; then
            enable_safebro_iprules
    else
            disable_safebro_iprules
    fi

    if [ "$ADVSEC_CUJOTELEMETRYWIFIFP_RFC_ENABLED" = "1" ]; then
            enable_cujotelemetrywififp
    else
            disable_cujotelemetrywififp
    fi

    do_firewall_restart "wait"

    if [ -f $ADVSEC_RAPTR_ENABLED_PATH ]; then
        # raptr [-q] option is broken in v2021-Q3-C release and it's been fixed in v2021-Q4-C release.
        # In worstcase scenario, if [-q] option fails in future CUJO integration,
        # To avoid flooding of logs in ConsoleLog.txt, we have re-directed stderr output
        # from 'raptr check' to /rdklogs/logs/agent.txt
        if raptr -q check 2>> ${ADVSEC_AGENT_LOG_PATH}; then
            echo_t "Rules are loaded correctly" >> ${ADVSEC_AGENT_LOG_PATH}
        else
            do_firewall_restart "wait"
        fi
    else
        if [ "$ADV_PC_ENABLED" = "1" ] && [ ! -e ${ADV_PARENTAL_CONTROL_RFC_DISABLED_PATH} ]; then
            #This is a workaround for an issue in firewall utility, where cujo related rules are not added.
            #To be removed once firewall utility issue is fixed!
            sleep 20s
            ipt4=`cat /tmp/.ipt | grep CUJO | wc -l`
            ipt6=`cat /tmp/.ipt_v6 | grep CUJO | wc -l`
            ip4=`iptables-save | grep CUJO | wc -l`
            ip6=`ip6tables-save | grep CUJO | wc -l`
            if [ ${ipt4} != ${ip4} ] || [ ${ipt6} != ${ip6} ]; then
                do_firewall_restart "wait"
            else
                echo_t "Rules are loaded correctly" >> ${ADVSEC_AGENT_LOG_PATH}
            fi
        fi
    fi

    AGENT_USER=`advsec_get_agent_group_name`
    if [ "${AGENT_USER}" = "root" ]; then
        echo_t ${AGENT_RUNNING_AS_ROOT_LOG} >> ${ADVSEC_AGENT_LOG_PATH}
    elif [ "${AGENT_USER}" = "${CUJO_AGENT_USER_NAME}" ]; then
        echo_t ${AGENT_RUNNING_AS_NON_ROOT_LOG} >> ${ADVSEC_AGENT_LOG_PATH}
    fi

    if [ -f $ADVSEC_INITIALIZING ]; then
        rm $ADVSEC_INITIALIZING
    fi

    exit 0
elif [ "$1" = "-disable" ]
then
    stop_agent_services

    if [ "$DF_ENABLED" != "1" ]; then
        echo_t "Device_Finger_Printing_enabled:false"
    fi

    if [ -f $ADVSEC_INITIALIZED ]; then
        rm $ADVSEC_INITIALIZED
    fi

    if [ -f $ADVSEC_INITIALIZING ]; then
        rm $ADVSEC_INITIALIZING
    fi

    if [ -f $SOFTFLOWD_ENABLE ]; then
        rm $SOFTFLOWD_ENABLE
    fi

    if [ -f $SAFEBRO_ENABLE ]; then
        rm $SAFEBRO_ENABLE
    fi

    if [ -f $ADVSEC_AGENT_SHUTDOWN ]; then
        rm $ADVSEC_AGENT_SHUTDOWN
    fi

    if [ "$BOX_TYPE" != "XB3" ] && [ "$BOX_TYPE" != "XF3" ]; then
        if [ -f $ADVSEC_DF_ICMPv6_ENABLED_PATH ]; then
            rm $ADVSEC_DF_ICMPv6_ENABLED_PATH
        fi
    fi

    if [ -f $ADVSEC_WS_DISCOVERY_ENABLED_PATH ]; then
        rm $ADVSEC_WS_DISCOVERY_ENABLED_PATH
    fi

    if [ -f $ADVSEC_RAPTR_ENABLED_PATH ]; then
        rm $ADVSEC_RAPTR_ENABLED_PATH
    fi

    if [ -f $ADVSEC_USERSPACE_ENABLED_PATH ]; then
        rm $ADVSEC_USERSPACE_ENABLED_PATH
    fi

    if [ -f $ADVSEC_AGENT_ENABLED_PATH ]; then
        rm $ADVSEC_AGENT_ENABLED_PATH
    fi

    if [ -f $ADVSEC_SAFEBROWSING_ENABLED_PATH ]; then
        rm $ADVSEC_SAFEBROWSING_ENABLED_PATH
    fi

    if [ -f $ADVSEC_CUJOTELEMETRYWIFIFP_ENABLED_PATH ]; then
        rm $ADVSEC_CUJOTELEMETRYWIFIFP_ENABLED_PATH
    fi

    if [ -f $ADVSEC_CUJOTRACER_ENABLED_PATH ]; then
        rm $ADVSEC_CUJOTRACER_ENABLED_PATH
    fi

    if [ -f $ADVSEC_CUJOTELEMETRY_ENABLED_PATH ]; then
        rm $ADVSEC_CUJOTELEMETRY_ENABLED_PATH
    fi

    if [ -f $ADVSEC_WIFIDATACOLLECTION_ENABLED_PATH ]; then
        rm $ADVSEC_WIFIDATACOLLECTION_ENABLED_PATH
    fi

    exit 0
fi
}

start_agent_services()
{
    advsec_module_load
    advsec_agent_create_ipsets
    advsec_start_agent
    advsec_wait_for_agent

    if [ ${EXIT_STATUS} -ne 0 ]; then
        echo_t "${CUJO_AGENT_LOG} is not active...exiting..." >> ${ADVSEC_AGENT_LOG_PATH}
        rm $ADVSEC_INITIALIZING
        exit 0
    fi

    if [ "$DF_ENABLED" = "1" ]; then
        advsec_agent_start_fp
    fi

    advsec_initialize_nfq_ct
}

stop_agent_services()
{
    rm -f ${ADVSEC_NFLUA_LOADED}
    stop_privacy_protection
    stop_adv_parental_control
    advsec_agent_stop_sf
    advsec_agent_stop_sb
    advsec_agent_stop_fp
    advsec_stop_agent
    if [ -f $ADVSEC_RAPTR_ENABLED_PATH ]; then
        retries=5;
        echo "Clearing Cujo iptables rules..." >> ${ADVSEC_AGENT_LOG_PATH}
        raptr clear
        while [ ${retries} -gt 0 ]; do
            if raptr -q check -N; then
                echo_t "Cujo iptables rules successfully cleared..." >> ${ADVSEC_AGENT_LOG_PATH}
                break
            fi
            sleep 1
            retries=$((retries--))
            raptr clear
        done
    else
        RETRY_CNT=5
        while [ ${RETRY_CNT} -gt 0 ]; do
            RETRY_CNT=$(expr $RETRY_CNT - 1)
            echo_t "${CUJO_AGENT_LOG} triggering firewall restart..." >> ${ADVSEC_AGENT_LOG_PATH}
            sysevent set firewall-restart
            sleep 10s
            ip4=`iptables-save | grep CUJO | wc -l`
            ip6=`ip6tables-save | grep CUJO | wc -l`
            if [ $ip4 = "0" ] && [ $ip6 = "0" ]; then
                break
            else
                echo_t "${CUJO_AGENT_LOG} rules are not removed yet! ip4 = $ip4 And ip6 = $ip6 ..Retry again" >> ${ADVSEC_AGENT_LOG_PATH}
                sleep 60s
            fi
        done
    fi
    advsec_module_unload
    advsec_agent_flush_ipsets
    advsec_cleanup_config_agent
}

start_advsec_safe_browsing()
{
    advsec_agent_start_sb
    echo_t "ADV_SECURITY_SAFE_BROWSING_ENABLE"
}

stop_advsec_safe_browsing()
{
    advsec_agent_stop_sb
    echo_t "ADV_SECURITY_SAFE_BROWSING_DISABLE"
    if [ -e ${ADVSEC_LOOKUP_EXCEED_COUNT_FILE} ]; then
        rm ${ADVSEC_LOOKUP_EXCEED_COUNT_FILE}
    fi
}

start_advsec_softflowd()
{
    advsec_agent_start_sf
    echo_t "ADV_SECURITY_SOFTFLOWD_ENABLE"
}

stop_advsec_softflowd()
{
    advsec_agent_stop_sf
    echo_t "ADV_SECURITY_SOFTFLOWD_DISABLE"
}

start_advanced_security()
{
    if [ "$1" = "-start" ]
    then
            if [ "$2" = "sb" ]
            then
                start_advsec_safe_browsing
            fi
            if [ "$3" = "sf" ]
            then
                start_advsec_softflowd
            fi
    fi

    if [ "$1" = "-stop" ]
    then
            if [ "$2" = "sb" ]
            then
                stop_advsec_safe_browsing
            fi
            if [ "$3" = "sf" ]
            then
                stop_advsec_softflowd
            fi
    fi
}

advanced_parental_control_setup()
{
    if [ "$1" = "-startAdvPC" ]
    then
        start_adv_parental_control
        echo_t ${ADV_PARENTAL_CONTROL_ACTIVATED_LOG} >> ${ADVSEC_AGENT_LOG_PATH}
    fi

    if [ "$1" = "-stopAdvPC" ]
    then
        stop_adv_parental_control
        echo_t ${ADV_PARENTAL_CONTROL_DEACTIVATED_LOG} >> ${ADVSEC_AGENT_LOG_PATH}
    fi
}

privacy_protection_setup()
{
    if [ "$1" = "-startPrivProt" ]
    then
        start_privacy_protection
        echo_t ${PRIVACY_PROTECTION_ACTIVATED_LOG} >> ${ADVSEC_AGENT_LOG_PATH}
    fi

    if [ "$1" = "-stopPrivProt" ]
    then
        stop_privacy_protection
        echo_t ${PRIVACY_PROTECTION_DEACTIVATED_LOG} >> ${ADVSEC_AGENT_LOG_PATH}
    fi
}

enable_icmpv6()
{
    touch $ADVSEC_DF_ICMPv6_ENABLED_PATH
    echo_t ${DF_ICMPv6_RFC_ENABLED_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "FR" ]; then
        do_firewall_restart
    fi
}

disable_icmpv6()
{
    rm -f $ADVSEC_DF_ICMPv6_ENABLED_PATH
    echo_t ${DF_ICMPv6_RFC_DISABLED_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "FR" ]; then
        do_firewall_restart
    fi
}

enable_wsdiscovery()
{
    touch $ADVSEC_WS_DISCOVERY_ENABLED_PATH
    echo_t ${ADV_WS_DISCOVERY_RFC_ENABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "FR" ]; then
        do_firewall_restart
    fi
}

disable_wsdiscovery()
{
    rm -f $ADVSEC_WS_DISCOVERY_ENABLED_PATH
    echo_t ${ADV_WS_DISCOVERY_RFC_DISABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "FR" ]; then
        do_firewall_restart
    fi
}

enable_otm()
{
   echo_t ${ADV_OTM_RFC_ENABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}
   if [ "$1" = "RR" ]; then
       advsec_restart_agent "OTM_RFC_Enabled"
   fi
}

disable_otm()
{
   echo_t ${ADV_OTM_RFC_DISABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}
   if [ "$1" = "RR" ]; then
       advsec_restart_agent "OTM_RFC_Disabled"
   fi
}

enable_userspace()
{
   touch $ADVSEC_USERSPACE_ENABLED_PATH
   echo_t ${ADV_USERSPACE_RFC_ENABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

   if [ "$1" = "RR" ]; then
       advsec_restart_agent "AgentUserSpace_RFC_Enabled"
   fi
   if [ "$2" = "FR" ]; then
       do_firewall_restart
   fi
}

disable_userspace()
{
   rm -f $ADVSEC_USERSPACE_ENABLED_PATH
   echo_t ${ADV_USERSPACE_RFC_DISABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "RR" ]; then
       advsec_restart_agent "AgentUserSpace_RFC_Disabled"
    fi
    if [ "$2" = "FR" ]; then
       do_firewall_restart
    fi
}

enable_agent()
{
   touch $ADVSEC_AGENT_ENABLED_PATH
   echo_t ${ADV_AGENT_RFC_ENABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "RR" ]; then
       advsec_restart_agent "AdvSecAgent_RFC_Enabled"
   fi
}

disable_agent()
{
   rm -f $ADVSEC_AGENT_ENABLED_PATH
   echo_t ${ADV_AGENT_RFC_DISABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "RR" ]; then
       advsec_restart_agent "AdvSecAgent_RFC_Disabled"
   fi
}

enable_safebro_iprules()
{
   touch $ADVSEC_SAFEBROWSING_ENABLED_PATH
   echo_t ${ADV_SAFEBROWSING_RFC_ENABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "RR" ]; then
       advsec_restart_agent "AgentSafeBrowsing_RFC_Enabled"
   fi
   if [ "$2" = "FR" ]; then
       do_firewall_restart
   fi
}

disable_safebro_iprules()
{
   rm -f $ADVSEC_SAFEBROWSING_ENABLED_PATH
   echo_t ${ADV_SAFEBROWSING_RFC_DISABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "RR" ]; then
       advsec_restart_agent "AgentSafeBrowsing_RFC_Disabled"
   fi
   if [ "$2" = "FR" ]; then
       do_firewall_restart
   fi
}

enable_cujotelemetrywififp()
{
   touch $ADVSEC_CUJOTELEMETRYWIFIFP_ENABLED_PATH
   echo_t ${ADV_CUJOTELEMETRYWIFIFP_RFC_ENABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "RR" ]; then
       advsec_restart_agent "AgentCujoTelemetryWiFiFP_RFC_Enabled"
   fi
}

disable_cujotelemetrywififp()
{
   rm -f $ADVSEC_CUJOTELEMETRYWIFIFP_ENABLED_PATH
   echo_t ${ADV_CUJOTELEMETRYWIFIFP_RFC_DISABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "RR" ]; then
       advsec_restart_agent "AgentCujoTelemetryWiFiFP_RFC_Disabled"
   fi
}

enable_cujotracer()
{
   touch $ADVSEC_CUJOTRACER_ENABLED_PATH
   echo_t ${ADV_CUJOTRACER_RFC_ENABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "RR" ]; then
       advsec_restart_agent "AgentCujoTracer_RFC_Enabled"
   fi
}

disable_cujotracer()
{
   rm -f $ADVSEC_CUJOTRACER_ENABLED_PATH
   echo_t ${ADV_CUJOTRACER_RFC_DISABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "RR" ]; then
       advsec_restart_agent "AgentCujoTracer_RFC_Disabled"
   fi
}

enable_cujotelemetry()
{
   touch $ADVSEC_CUJOTELEMETRY_ENABLED_PATH
   echo_t ${ADV_CUJOTELEMETRY_RFC_ENABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "RR" ]; then
       advsec_restart_agent "AgentCujoTelemetry_RFC_Enabled"
   fi
}

disable_cujotelemetry()
{
   rm -f $ADVSEC_CUJOTELEMETRY_ENABLED_PATH
   echo_t ${ADV_CUJOTELEMETRY_RFC_DISABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "RR" ]; then
       advsec_restart_agent "AgentCujoTelemetry_RFC_Disabled"
   fi
}

enable_wifidatacollection()
{
    if [ -f $ADVSEC_WIFIDCL_INIT_PATH ]; then
        touch $ADVSEC_WIFIDATACOLLECTION_ENABLED_PATH
        echo_t ${ADV_WIFIDATACOLLECTION_RFC_ENABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

        if [ "$1" = "RR" ]; then
            advsec_restart_agent "AgentWifiDataCollection_RFC_Enabled"
        fi
    fi
}

disable_wifidatacollection()
{
   rm -rf $ADVSEC_WIFIDATACOLLECTION_ENABLED_PATH
   echo_t ${ADV_WIFIDATACOLLECTION_RFC_DISABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "RR" ]; then
       advsec_restart_agent "AgentWifiDataCollection_RFC_Disabled"
   fi
}

enable_levl()
{
    if [ -f $ADVSEC_WIFIDCL_INIT_PATH ]; then
        touch $ADVSEC_LEVL_ENABLED_PATH
        echo_t ${ADV_LEVL_RFC_ENABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

        if [ "$1" = "RR" ]; then
            advsec_restart_agent "Levl_RFC_Enabled"
        fi
        if [ "$2" = "FR" ]; then
            enable_userspace
            do_firewall_restart
        fi
    fi
}

disable_levl()
{
    rm -rf $ADVSEC_LEVL_ENABLED_PATH
    echo_t ${ADV_LEVL_RFC_DISABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "RR" ]; then
        advsec_restart_agent "Levl_RFC_Disabled"
    fi
}

enable_raptr()
{
    touch $ADVSEC_RAPTR_ENABLED_PATH
    echo_t ${ADV_RAPTR_RFC_ENABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "FR" ]; then
        do_firewall_restart
    fi
}

disable_raptr()
{
    rm -f $ADVSEC_RAPTR_ENABLED_PATH
    echo_t ${ADV_RAPTR_RFC_DISABLE_LOG} >> ${ADVSEC_AGENT_LOG_PATH}

    if [ "$1" = "FR" ]; then
        do_firewall_restart
    fi
}

do_firewall_restart()
{
    if [ -f $ADVSEC_RAPTR_ENABLED_PATH ]; then
        raptr -n -4 set | grep -v \'ipset\' > $CUJO_AGENT_RULES_V4_PATH
        raptr -n -6 set | grep -v \'ipset\' > $CUJO_AGENT_RULES_V6_PATH
    else
        if [ -f $CUJO_AGENT_RULES_V4_PATH ]; then
            rm $CUJO_AGENT_RULES_V4_PATH
        fi
        if [ -f $CUJO_AGENT_RULES_V6_PATH ]; then
            rm $CUJO_AGENT_RULES_V6_PATH
        fi
    fi
    echo_t "${CUJO_AGENT_LOG} triggering firewall restart..." >> ${ADVSEC_AGENT_LOG_PATH}
    sysevent set firewall-restart

    if [ "$1" = "wait" ]; then
        fw_retries=10
        while [ ${fw_retries} -gt 0 ]; do
            fw_stat=`sysevent get firewall-status`
            if [ "${fw_stat}" = "starting" ]; then
                echo_t "starting firewall" >> ${ADVSEC_AGENT_LOG_PATH}
                break
            else
                usleep 100000
                fw_retries=$((fw_retries--))
            fi
        done

        fw_retries=20
        while [ ${fw_retries} -gt 0 ]; do
            fw_stat=`sysevent get firewall-status`
            if [ "${fw_stat}" = "started" ]; then
                break
            else
                usleep 100000
                fw_retries=$((fw_retries--))
            fi
        done
        if [ "${fw_stat}" = "started" ]; then
            echo_t "firewall restart success" >> ${ADVSEC_AGENT_LOG_PATH}
        else
            echo_t "firewall-status: ${fw_stat} firewall restart failed" >> ${ADVSEC_AGENT_LOG_PATH}
        fi
    fi
}

if [ "$1" = "-enable" ] || [ "$1" = "-disable" ]
then
    start_device_services $1 $2 $3
fi

if [ "$1" = "-start" ] || [ "$1" = "-stop" ]
then
    start_advanced_security $1 $2 $3
    if [ "$BOX_TYPE" == "XB3" ] || [ "$BOX_TYPE" == "XF3" ]; then
        echo_t "${CUJO_AGENT_LOG} triggering firewall restart..." >> ${ADVSEC_AGENT_LOG_PATH}
        sysevent set firewall-restart
    fi
fi

if [ "$1" = "-startAdvPC" ] || [ "$1" = "-stopAdvPC" ]
then
    if [ "$1" = "-startAdvPC" ] && [ "$ADV_PC_RFC_ENABLED" = "0" ]; then
        echo_t "${CUJO_AGENT_LOG} cannot activate AdvParentalControl feature due to RFC is disabled" >> ${ADVSEC_AGENT_LOG_PATH}
    else
        advanced_parental_control_setup $1
        if [ "$BOX_TYPE" == "XB3" ] || [ "$BOX_TYPE" == "XF3" ]; then
            echo_t "${CUJO_AGENT_LOG} triggering firewall restart..." >> ${ADVSEC_AGENT_LOG_PATH}
            sysevent set firewall-restart
        fi
    fi
fi

if [ "$1" = "-startPrivProt" ] || [ "$1" = "-stopPrivProt" ]
then
    if [ "$1" = "-startPrivProt" ] && [ "$PRIVACY_PROTECTION_RFC_ENABLED" = "0" ]; then
        echo_t "${CUJO_AGENT_LOG} cannot activate PrivacyProtection feature due to RFC is disabled" >> ${ADVSEC_AGENT_LOG_PATH}
    else
        privacy_protection_setup $1
        if [ "$BOX_TYPE" == "XB3" ] || [ "$BOX_TYPE" == "XF3" ]; then
            echo_t "${CUJO_AGENT_LOG} triggering firewall restart..." >> ${ADVSEC_AGENT_LOG_PATH}
            sysevent set firewall-restart
        fi
    fi
fi

if [ "$1" = "-configure_features" ]
then
    if [ "${ADVSEC_SB_ENABLED}" = "1" ]; then
        if [ ! -e ${SAFEBRO_ENABLE} ]; then
            start_advsec_safe_browsing
        fi
    else
        if [ -e ${SAFEBRO_ENABLE} ]; then
            stop_advsec_safe_browsing
        fi
    fi

    if [ "${ADVSEC_SF_ENABLED}" = "1" ]; then
        if [ ! -e ${SOFTFLOWD_ENABLE} ]; then
            start_advsec_softflowd
        fi
    else
        if [ -e ${SOFTFLOWD_ENABLE} ]; then
            stop_advsec_softflowd
        fi
    fi

    if [ "${ADV_PC_ENABLED}" = "1" ]; then
        if [ ! -e ${ADV_PARENTAL_CONTROL_PATH} ]; then
            if [ "$ADV_PC_RFC_ENABLED" = "0" ]; then
                echo_t "${CUJO_AGENT_LOG} cannot activate AdvParentalControl feature due to RFC is disabled" >> ${ADVSEC_AGENT_LOG_PATH}
            else
                advanced_parental_control_setup "-startAdvPC"
            fi
        fi
    else
        if [ -e ${ADV_PARENTAL_CONTROL_PATH} ]; then
            advanced_parental_control_setup "-stopAdvPC"
        fi
    fi

    if [ "${PRIVACY_PROTECTION_ENABLED}" = "1" ]; then
        if [ ! -e ${PRIVACY_PROTECTION_PATH} ]; then
            if [ "$PRIVACY_PROTECTION_RFC_ENABLED" = "0" ]; then
                 echo_t "${CUJO_AGENT_LOG} cannot activate PrivacyProtection feature due to RFC is disabled" >> ${ADVSEC_AGENT_LOG_PATH}
            else
                privacy_protection_setup "-startPrivProt"
            fi
        fi
    else
        if [ -e ${PRIVACY_PROTECTION_PATH} ]; then
            privacy_protection_setup "-stopPrivProt"
        fi
    fi

    if [ "$BOX_TYPE" == "XB3" ] || [ "$BOX_TYPE" == "XF3" ]; then
        echo_t "${CUJO_AGENT_LOG} triggering firewall restart..." >> ${ADVSEC_AGENT_LOG_PATH}
        sysevent set firewall-restart
    fi

fi

if [ "$1" = "-enableICMP6" ]; then
   enable_icmpv6 "FR"
fi

if [ "$1" = "-disableICMP6" ]; then
   disable_icmpv6 "FR"
fi

if [ "$1" = "-enableOTM" ]; then
    enable_otm "RR"
fi

if [ "$1" = "-disableOTM" ]; then
    disable_otm "RR"
fi

if [ "$1" = "-enableUS" ]; then
    # To remove kernel module dependent firewall rules
    do_firewall_restart
    # To unload / load required kernel modules during cujo-agent restart
    rm -f ${ADVSEC_NFLUA_LOADED}
    enable_userspace "RR" "FR"
fi

if [ "$1" = "-disableUS" ]; then
    # To unload / load required kernel modules during cujo-agent restart
    rm -f ${ADVSEC_NFLUA_LOADED}
    disable_userspace "RR" "FR"
fi

if [ "$1" = "-enableWifiDCL" ]; then
    enable_wifidatacollection "RR"
fi

if [ "$1" = "-disableWifiDCL" ]; then
    disable_wifidatacollection "RR"
fi

if [ "$1" = "-enableLEVL" ]; then
    enable_wifidatacollection
    enable_levl "RR"
fi

if [ "$1" = "-enableLEVLwithUS" ]; then
    enable_userspace
    enable_wifidatacollection
    enable_levl "RR" "FR"
fi

if [ "$1" = "-disableLEVL" ]; then
    disable_levl
fi

if [ "$1" = "-enableAGT" ]; then
    enable_agent "RR"
fi

if [ "$1" = "-disableAGT" ]; then
    disable_agent "RR"
fi

if [ "$1" = "-enableSBRule" ]; then
    enable_safebro_iprules "RR" "FR"
fi

if [ "$1" = "-disableSBRule" ]; then
    disable_safebro_iprules "RR" "FR"
fi

if [ "$1" = "-enableCTW" ]; then
    enable_cujotelemetrywififp "RR"
fi

if [ "$1" = "-disableCTW" ]; then
    disable_cujotelemetrywififp "RR"
fi

if [ "$1" = "-enableCT" ]; then
    enable_cujotracer "RR"
fi

if [ "$1" = "-disableCT" ]; then
    disable_cujotracer "RR"
fi

if [ "$1" = "-enableCTD" ]; then
    enable_cujotelemetry "RR"
fi

if [ "$1" = "-disableCTD" ]; then
    disable_cujotelemetry "RR"
fi

if [ "$1" = "-enableWSDiscovery" ]; then
   enable_wsdiscovery "FR"
fi

if [ "$1" = "-disableWSDiscovery" ]; then
   disable_wsdiscovery "FR"
fi

if [ "$1" = "-enableRaptr" ]; then
   enable_raptr "FR"
fi

if [ "$1" = "-disableRaptr" ]; then
   disable_raptr "FR"
fi

if [ "$1" = "-restartAgent" ] && [ -e ${ADVSEC_DF_ENABLED_PATH} ]
then
    advsec_restart_agent $2
    do_firewall_restart "wait"
fi

if [ "$1" = "-agentloglevel" ]; then
   advsec_agent_loglevel $2
fi

if [ "$1" = "-getSafebroConfig" ]; then
   advsec_agent_get_safebro_config
fi
