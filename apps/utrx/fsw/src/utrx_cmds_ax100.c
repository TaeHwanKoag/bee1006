#include "utrx_cmds_ax100.h"
/********************SET*************************************************************/







void UTRX_AX100_GndwdtClearCmd(const UTRX_AX100_GndwdtClear_t *Msg) {
    int status = UTRX_GndwdtClear();

    UTRX_APP_Data.Report.CommandCode = UTRX_GNDWDT_CLEAR_CC;
    UTRX_APP_Data.Report.ReturnType = CMD_RETCODE_TYPE_DRIVER;
    UTRX_APP_Data.Report.ReturnCode = status;
    UTRX_APP_Data.Report.ReturnDataSize = 0;

    CmdErrCounter(&UTRX_APP_Data.AppCnt, &UTRX_APP_Data.Report);
}

void UTRX_AX100_UTRX_RebootCmd(const UTRX_AX100_UTRX_Reboot_t *Msg) {
    int status = UTRX_Reboot();

    UTRX_APP_Data.Report.CommandCode = UTRX_REBOOT_CC;
    UTRX_APP_Data.Report.ReturnType = CMD_RETCODE_TYPE_DRIVER;
    UTRX_APP_Data.Report.ReturnCode = status;
    UTRX_APP_Data.Report.ReturnDataSize = 0;

    CmdErrCounter(&UTRX_APP_Data.AppCnt, &UTRX_APP_Data.Report);
}

void UTRX_AX100_RXCONF_SetBaudCmd(const UTRX_AX100_RXCONF_SetBaudCmd_t *Msg) {
    int status = UTRX_RXCONF_SetBaud(Msg->arg);

    UTRX_APP_Data.Report.CommandCode = UTRX_RXCONF_SET_BAUD_CC;
    UTRX_APP_Data.Report.ReturnType = CMD_RETCODE_TYPE_DRIVER;
    UTRX_APP_Data.Report.ReturnCode = status;
    UTRX_APP_Data.Report.ReturnDataSize = 0;

    CmdErrCounter(&UTRX_APP_Data.AppCnt, &UTRX_APP_Data.Report);
}

void UTRX_AX100_TXCONF_SetBaudCmd(const UTRX_AX100_TXCONF_SetBaudCmd_t *Msg) {
    int status = UTRX_TXCONF_SetBaud(Msg->arg);

    UTRX_APP_Data.Report.CommandCode = UTRX_TXCONF_SET_BAUD_CC;
    UTRX_APP_Data.Report.ReturnType = CMD_RETCODE_TYPE_DRIVER;
    UTRX_APP_Data.Report.ReturnCode = status;
    UTRX_APP_Data.Report.ReturnDataSize = 0;

    CmdErrCounter(&UTRX_APP_Data.AppCnt, &UTRX_APP_Data.Report);
}

void UTRX_AX100_RXCONF_SetFreqCmd(const UTRX_AX100_RXCONF_SetFreqCmd_t *Msg) {
    int status = UTRX_RXCONF_SetFreq(Msg->arg);

    UTRX_APP_Data.Report.CommandCode = UTRX_RXCONF_SET_FREQ_CC;
    UTRX_APP_Data.Report.ReturnType = CMD_RETCODE_TYPE_DRIVER;
    UTRX_APP_Data.Report.ReturnCode = status;
    UTRX_APP_Data.Report.ReturnDataSize = 0;

    CmdErrCounter(&UTRX_APP_Data.AppCnt, &UTRX_APP_Data.Report);
}

void UTRX_AX100_TXCONF_SetFreqCmd(const UTRX_AX100_TXCONF_SetFreqCmd_t *Msg) {
    int status = UTRX_TXCONF_SetFreq(Msg->arg);

    UTRX_APP_Data.Report.CommandCode = UTRX_TXCONF_SET_FREQ_CC;
    UTRX_APP_Data.Report.ReturnType = CMD_RETCODE_TYPE_DRIVER;
    UTRX_APP_Data.Report.ReturnCode = status;
    UTRX_APP_Data.Report.ReturnDataSize = 0;

    CmdErrCounter(&UTRX_APP_Data.AppCnt, &UTRX_APP_Data.Report);
}

void UTRX_AX100_SetDefaultBaudCmd(const UTRX_AX100_SetDefaultBaudCmd_t *Msg) {
    int status = UTRX_SetDefaultBaud();

    UTRX_APP_Data.Report.CommandCode = UTRX_SET_DEFAULT_BAUD_CC;
    UTRX_APP_Data.Report.ReturnType = CMD_RETCODE_TYPE_DRIVER;
    UTRX_APP_Data.Report.ReturnCode = status;
    UTRX_APP_Data.Report.ReturnDataSize = 0;

    CmdErrCounter(&UTRX_APP_Data.AppCnt, &UTRX_APP_Data.Report);
}

void UTRX_AX100_RparamSave1Cmd(const UTRX_AX100_RparamSave1Cmd_t *Msg) {
    int status = UTRX_RparamSave1();

    UTRX_APP_Data.Report.CommandCode = UTRX_RPARAM_SAVE_1_CC;
    UTRX_APP_Data.Report.ReturnType = CMD_RETCODE_TYPE_DRIVER;
    UTRX_APP_Data.Report.ReturnCode = status;
    UTRX_APP_Data.Report.ReturnDataSize = 0;

    CmdErrCounter(&UTRX_APP_Data.AppCnt, &UTRX_APP_Data.Report);
}

void UTRX_AX100_RparamSave5Cmd(const UTRX_AX100_RparamSave5Cmd_t *Msg) {
    int status = UTRX_RparamSave5();

    UTRX_APP_Data.Report.CommandCode = UTRX_RPARAM_SAVE_5_CC;
    UTRX_APP_Data.Report.ReturnType = CMD_RETCODE_TYPE_DRIVER;
    UTRX_APP_Data.Report.ReturnCode = status;
    UTRX_APP_Data.Report.ReturnDataSize = 0;

    CmdErrCounter(&UTRX_APP_Data.AppCnt, &UTRX_APP_Data.Report);
}

void UTRX_AX100_RparamSaveAllCmd(const UTRX_AX100_RparamSaveAllCmd_t *Msg) {
    int status = UTRX_RparamSaveAll();

    UTRX_APP_Data.Report.CommandCode = UTRX_RPARAM_SAVE_ALL_CC;
    UTRX_APP_Data.Report.ReturnType = CMD_RETCODE_TYPE_DRIVER;
    UTRX_APP_Data.Report.ReturnCode = status;
    UTRX_APP_Data.Report.ReturnDataSize = 0;

    CmdErrCounter(&UTRX_APP_Data.AppCnt, &UTRX_APP_Data.Report);
}

void UTRX_AX100_CheckStatePingCmd(const UTRX_AX100_CheckStatePingCmd_t *Msg) {
    int status = csp_checkstate_ping(CSP_NODE_UTRX);

    UTRX_APP_Data.Report.CommandCode = UTRX_CHECK_STATE_PING_CC;
    UTRX_APP_Data.Report.ReturnType = CMD_RETCODE_TYPE_DRIVER;
    UTRX_APP_Data.Report.ReturnCode = status;
    UTRX_APP_Data.Report.ReturnDataSize = 0;

    CmdErrCounter(&UTRX_APP_Data.AppCnt, &UTRX_APP_Data.Report);
}
