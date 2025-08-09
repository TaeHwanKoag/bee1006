#ifndef UTRX_AX100_CMDS_H
#define UTRX_AX100_CMDS_H

#include "utrx_app.h"
#include "utrx_app_dispatch.h"
#include "utrx_app_cmds.h"
#include "utrx_app_eventids.h"
#include "utrx_app_msgids.h"
#include "utrx_app_msg.h"
#include "utrx_app_fcncodes.h"
#include "cfe_srl_csp.h"
#include <gs/param/rparam.h>

void UTRX_AX100_GndwdtClearCmd(const UTRX_AX100_GndwdtClear_t *Msg);
void UTRX_AX100_UTRX_RebootCmd(const UTRX_AX100_UTRX_Reboot_t *Msg);
void UTRX_AX100_RXCONF_SetBaudCmd(const UTRX_AX100_RXCONF_SetBaudCmd_t *Msg);
void UTRX_AX100_TXCONF_SetBaudCmd(const UTRX_AX100_TXCONF_SetBaudCmd_t *Msg);
void UTRX_AX100_RXCONF_SetFreqCmd(const UTRX_AX100_RXCONF_SetFreqCmd_t *Msg);
void UTRX_AX100_TXCONF_SetFreqCmd(const UTRX_AX100_TXCONF_SetFreqCmd_t *Msg);
void UTRX_AX100_SetDefaultBaudCmd(const UTRX_AX100_SetDefaultBaudCmd_t *Msg);
void UTRX_AX100_RparamSave1Cmd(const UTRX_AX100_RparamSave1Cmd_t *Msg);
void UTRX_AX100_RparamSave5Cmd(const UTRX_AX100_RparamSave5Cmd_t *Msg);
void UTRX_AX100_RparamSaveAllCmd(const UTRX_AX100_RparamSaveAllCmd_t *Msg);
void UTRX_AX100_CheckStatePingCmd(const UTRX_AX100_CheckStatePingCmd_t *Msg);

#endif /* UTRX_AX100_CMDS_H */