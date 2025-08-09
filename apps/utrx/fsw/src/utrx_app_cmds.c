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
 * \file
 *   This file contains the source code for the Utrx App Ground Command-handling functions
 */

/*
** Include Files:
*/
#include "utrx_app.h"
#include "utrx_app_cmds.h"
#include "utrx_app_msgids.h"
#include "utrx_app_eventids.h"
#include "utrx_app_version.h"
#include "utrx_app_tbl.h"
#include "utrx_app_utils.h"
#include "utrx_app_msg.h"
#include "utrx_app_dispatch.h"

/* The utrx_lib module provides the UTRX_Function() prototype */
#include "sample_lib.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
CFE_Status_t UTRX_APP_SendHkCmd(const CFE_SB_Buffer_t *SBBufPtr)
{
    int i;

    /*
    ** Get command execution counters...
    */
    // UTRX_APP_Data.HkTlm.Payload.CommandErrorCounter = UTRX_APP_Data.ErrCounter;
    // UTRX_APP_Data.HkTlm.Payload.CommandCounter      = UTRX_APP_Data.CmdCounter;

    CFE_MSG_FcnCode_t CommandCode = 0;

    if (CFE_MSG_GetFcnCode(&SBBufPtr->Msg, &CommandCode) != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(UTRX_APP_GETFCN_ERR_EID, CFE_EVS_EventType_ERROR,
                          "UTRX: Failed to get function code from message");
        return CFE_STATUS_WRONG_MSG_LENGTH;
    }


    if (CommandCode == UTRX_SEND_HK_CC)
    {
    UTRX_ReportHousekeeping();
   }   
   else
   {
    CFE_EVS_SendEvent(UTRX_APP_CC_ERR_EID, CFE_EVS_EventType_ERROR,
                      "UTRX App: Invalid command code %d", CommandCode);
    return CFE_STATUS_BAD_COMMAND_CODE;
  }
    

    // ** Send housekeeping telemetry packet...

    // CFE_SB_TimeStampMsg((CFE_MSG_Message_t *)&UTRX_APP_Data.ExecReportMsg);
    // CFE_SB_TransmitMsg((CFE_MSG_Message_t *)&UTRX_APP_Data.ExecReportMsg,true);

    return CFE_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* UTRX NOOP commands                                                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
CFE_Status_t UTRX_APP_NoopCmd(const UTRX_APP_NoopCmd_t *Msg)
{
    UTRX_APP_Data.CmdCounter++;

    CFE_EVS_SendEvent(UTRX_APP_NOOP_INF_EID, CFE_EVS_EventType_INFORMATION, "UTRX: NOOP command %s",
                      UTRX_APP_VERSION);

    return CFE_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function resets all the global counter variables that are     */
/*         part of the task telemetry.                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
CFE_Status_t UTRX_APP_ResetCountersCmd(const UTRX_APP_ResetCountersCmd_t *Msg)
{
    UTRX_APP_Data.CmdCounter = 0;
    UTRX_APP_Data.ErrCounter = 0;

    CFE_EVS_SendEvent(UTRX_APP_RESET_INF_EID, CFE_EVS_EventType_INFORMATION, "UTRX: RESET command");

    return CFE_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function Process Ground Station Command                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
CFE_Status_t UTRX_APP_ProcessCmd(const UTRX_APP_ProcessCmd_t *Msg)
{
    CFE_Status_t               status;
    void *                     TblAddr;
    UTRX_APP_ExampleTable_t *TblPtr;
    const char *               TableName = "UTRX_APP.ExampleTable";

    /* Utrx Use of Example Table */

    status = CFE_TBL_GetAddress(&TblAddr, UTRX_APP_Data.TblHandles[0]);

    if (status < CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Utrx App: Fail to get table address: 0x%08lx", (unsigned long)status);
        return status;
    }

    TblPtr = TblAddr;
    CFE_ES_WriteToSysLog("Utrx App: Example Table Value 1: %d  Value 2: %d", TblPtr->Int1, TblPtr->Int2);

    UTRX_APP_GetCrc(TableName);

    status = CFE_TBL_ReleaseAddress(UTRX_APP_Data.TblHandles[0]);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Utrx App: Fail to release table address: 0x%08lx", (unsigned long)status);
        return status;
    }

    /* Invoke a function provided by UTRX_APP_LIB */
    SAMPLE_LIB_Function();

    return CFE_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* A simple example command that displays a passed-in value                   */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
CFE_Status_t UTRX_APP_DisplayParamCmd(const UTRX_APP_DisplayParamCmd_t *Msg)
{
    CFE_EVS_SendEvent(UTRX_APP_VALUE_INF_EID, CFE_EVS_EventType_INFORMATION,
                      "UTRX_APP: ValU32=%lu, ValI16=%d, ValStr=%s", (unsigned long)Msg->Payload.ValU32,
                      (int)Msg->Payload.ValI16, Msg->Payload.ValStr);

    return CFE_SUCCESS;
}

/**********************************************************************************/
CFE_Status_t UTRX_APP_ResetDeviceCmdCountersCmd(const UTRX_APP_ResetDeviceCmdCountersCmd_t *Msg)
{
    UTRX_APP_Data.AppCnt.DeviceCmdCounter = 0;
    UTRX_APP_Data.AppCnt.DeviceErrCounter = 0;

    CFE_EVS_SendEvent(UTRX_APP_RESET_DEVICE_COUNTER_EID, CFE_EVS_EventType_INFORMATION,
                      "UTRX: Reset Device Cmd Counters");

    return CFE_SUCCESS;
}

CFE_Status_t UTRX_APP_ResetAppCmdCountersCmd(const UTRX_APP_ResetAppCmdCountersCmd_t *Msg)
{
    UTRX_APP_Data.AppCnt.AppCmdCounter = 0;
    UTRX_APP_Data.AppCnt.AppErrCounter = 0;

    CFE_EVS_SendEvent(UTRX_APP_RESET_APP_COUNTER_EID, CFE_EVS_EventType_INFORMATION,
                      "UTRX: Reset App Cmd Counters");

    return CFE_SUCCESS;
}

void CmdErrCounter(UTRX_AppCount_t * AppCnt, UTRX_CmdReport_t * ExecMsg) {
    if(!AppCnt)
        return;
    if (ExecMsg->RetCodeType == CFE_STATUS_BAD_COMMAND_CODE)
        return;
    /**
     * Increment the command counters.
     */
    if (ExecMsg->RetCodeType != CMD_RETCODE_TYPE_DRIVER) {
        /**
         * This was an Application-level command...
         */
        AppCnt->AppCmdCounter++;
        if (ExecMsg->RetCode != CFE_SUCCESS) {
            AppCnt->AppErrCounter++;
        }
    }
    else {
        /**
         * or else one for the hardware.
         */
        AppCnt->DeviceCmdCounter++;
        if (ExecMsg->RetCode != DEVICE_SUCCESS) {
            AppCnt->DeviceErrCounter++;
        }
    }
    return;
}

void UTRX_ReportHousekeeping(void)
{
    CFE_EVS_SendEvent(5003, CFE_EVS_EventType_ERROR,
                          "UTRX: ReportHousekeeping command sent successfully");

    memset(&UTRX_APP_Data.ExecReportMsg.Data.hk, 0, sizeof(UTRX_HK_t));
     CFE_MSG_Init(CFE_MSG_PTR(UTRX_APP_Data.ExecReportMsg.TlmHeader),
             CFE_SB_ValueToMsgId(UTRX_APP_HK_TLM_MID),
             sizeof(UTRX_APP_Data.ExecReportMsg));

    if(csp_checkstate_ping(CSP_NODE_UTRX))
        return;
    int32 status = 0;
    UTRX_APP_Data.ExecReportMsg.Report.DataSize = sizeof(UTRX_HK_t);
    UTRX_HK_t* hk = &UTRX_APP_Data.ExecReportMsg.Data.hk;
    
    status |= UTRX_TLM_GetTempBrd(&hk->TempBrd);
	status |= UTRX_TLM_GetLastRssi(&hk->LastRssi);
	status |= UTRX_TLM_GetLastRferr(&hk->LastRferr);
	status |= UTRX_TLM_GetActiveConf(&hk->ActiveConf);
	status |= UTRX_TLM_GetBootCount(&hk->BootCount);
	status |= UTRX_TLM_GetBootCause(&hk->BootCause);
	status |= UTRX_TLM_GetLastContact(&hk->LastContact);
	status |= UTRX_TLM_GetTotTxBytes(&hk->TotTxBytes);
	status |= UTRX_TLM_GetTotRxBytes(&hk->TotRxBytes);

    CFE_SB_TimeStampMsg((CFE_MSG_Message_t *)&UTRX_APP_Data.ExecReportMsg);
    CFE_SB_TransmitMsg((CFE_MSG_Message_t *)&UTRX_APP_Data.ExecReportMsg, true);

    return ;
 

} 


void UTRX_ReportBeacon(void)
{


     memset(&UTRX_APP_Data.ExecReportMsg.Data.bcn, 0, sizeof(UTRX_BCN_t));
     CFE_MSG_Init(CFE_MSG_PTR(UTRX_APP_Data.ExecReportMsg.TlmHeader),
             CFE_SB_ValueToMsgId(UTRX_APP_BCN_TLM_MID),
             sizeof(UTRX_APP_Data.ExecReportMsg));


    if(csp_checkstate_ping(CSP_NODE_UTRX))
        return;
    int32 status = 0;
    UTRX_APP_Data.ExecReportMsg.Report.DataSize = sizeof(UTRX_BCN_t);
    UTRX_BCN_t* bcn = &UTRX_APP_Data.ExecReportMsg.Data.bcn;
    status |= UTRX_RXCONF_GetBaud(&bcn->rx_baudrate);
    status |= UTRX_TLM_GetLastRssi(&bcn->LastRssi);
    status |= UTRX_TLM_GetActiveConf(&bcn->ActiveConf);
    status |= UTRX_TLM_GetBootCount(&bcn->BootCount);
    status |= UTRX_TLM_GetBootCause(&bcn->BootCause);
    status |= UTRX_TLM_GetTotRxBytes(&bcn->TotRxBytes);
    status |= UTRX_TXCONF_GetBaud(&bcn->tx_baudrate);
    
	
    CFE_SB_TimeStampMsg((CFE_MSG_Message_t *)&UTRX_APP_Data.ExecReportMsg);
    CFE_SB_TransmitMsg((CFE_MSG_Message_t *)&UTRX_APP_Data.ExecReportMsg, true);

    return;

}
