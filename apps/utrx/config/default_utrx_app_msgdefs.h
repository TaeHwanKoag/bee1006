/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2020 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/**
 * @file
 *   Specification for the UTRX_APP command and telemetry
 *   message constant definitions.
 *
 *  For UTRX_APP this is only the function/command code definitions
 */
#ifndef UTRX_APP_MSGDEFS_H
#define UTRX_APP_MSGDEFS_H

#include "common_types.h"
#include "utrx_app_fcncodes.h"

typedef struct UTRX_APP_DisplayParam_Payload
{
    uint32 ValU32;                            /**< 32 bit unsigned integer value */
    int16  ValI16;                            /**< 16 bit signed integer value */
    char   ValStr[UTRX_APP_STRING_VAL_LEN]; /**< An example string */
} UTRX_APP_DisplayParam_Payload_t;

/*************************************************************************/
/*
** Type definition (Utrx App housekeeping)
*/

// typedef struct UTRX_APP_HkTlm_Payload
// {
//     uint8 CommandErrorCounter;
//     uint8 CommandCounter;
//     uint8 spare[2];
// } UTRX_APP_HkTlm_Payload_t;


typedef struct
{
    int16 TempBrd;
    int16 LastRssi;
    int16 LastRferr;
    uint8 ActiveConf;
    uint16 BootCount;
    uint32 BootCause;
    uint32 LastContact;
    uint32 TotTxBytes;
    uint32 TotRxBytes;
} UTRX_HK_t;



typedef struct
{   
    uint32 rx_baudrate; //0x0004
    int16 LastRssi; // 0x0004
    uint8 ActiveConf; //0x0018
    uint16 BootCount; //0x0020
    uint32 BootCause; //0x0024
    uint32 TotRxBytes; //0x003C
    uint32 tx_baudrate; //0x0004
    
} UTRX_BCN_t;

typedef struct RPT_Report {
    uint16_t MsgID;
    uint8_t CommandCode;

    /**
     * `enum RPT_ReturnType_t`
     */
    uint8_t ReturnType;
    int32_t ReturnCode;

    /**
     * This member can be used to 2 types
     * 1. Get CMD -> earned value
     * 2. HW's Error packet -> HW error value
     */
    uint16_t ReturnDataSize;
    uint8_t ReturnValue[256]; /* `RPT_RET_VALUE_BUF_SIZE` == 60 */
} RPT_Report_t;



typedef struct UTRX_AppCount
{
    uint16 AppCmdCounter;
    uint16 AppErrCounter;
    uint16 DeviceCmdCounter;
    uint16 DeviceErrCounter;
} UTRX_AppCount_t;




#endif
