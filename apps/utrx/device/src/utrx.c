#include <csp/csp.h>
#include <csp/csp_endian.h> // CSP_PRIO_HIGH
#include <gs/param/rparam.h>

#include <cfe.h>
#include <utrx.h>
#include <utrx_app_eventids.h>
#include "cfe_srl_csp.h"



//Process Command Function /////////////////////////////////////////////////////////////


int32 UTRX_GndwdtClear(void)
{
    int status;

    status = csp_transaction_w_opts(CSP_PRIO_NORM, CSP_NODE_UTRX, AX100_PORT_GNDWDT_RESET, 1000, NULL, 0, NULL, 0,CSP_O_CRC32);

    return status; 
}


int32 UTRX_Reboot(void)
{
    int32 status = DEVICE_ERROR;
    
    uint32 magic_word = csp_hton32(CSP_REBOOT_MAGIC);
    status = csp_transaction_w_opts(CSP_PRIO_NORM,CSP_NODE_UTRX,CSP_REBOOT,1000, &magic_word, sizeof(magic_word), NULL,0,CSP_O_CRC32);
    
    
    return status;
}

int32 UTRX_RXCONF_SetFreq(uint32 FreqRxconf)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_RXCONF;
    uint16 addr = UTRX_ADDR_RXCONF_FREQ;
    CFE_EVS_SendEvent(5003, CFE_EVS_EventType_ERROR,
                          "UTRX: RX SetFreq command sent successfully");

    status = CFE_SRL_ApiSetRparamCSP(GS_PARAM_UINT32, CSP_NODE_UTRX, table_id, addr, &FreqRxconf);
  
    return status;
}

int32 UTRX_RXCONF_GetFreq(uint32 *FreqRxconf)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_RXCONF;
    uint16 addr = UTRX_ADDR_RXCONF_FREQ;
    status = CFE_SRL_ApiGetRparamCSP(GS_PARAM_UINT32, CSP_NODE_UTRX, table_id, addr, FreqRxconf);
     
    return status;
}





int32 UTRX_RXCONF_GetBaud(uint32 *BaudRxconf)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_RXCONF;
    uint16 addr = UTRX_ADDR_RXCONF_BAUD;  

    status = CFE_SRL_ApiGetRparamCSP(GS_PARAM_UINT32, CSP_NODE_UTRX, table_id, addr, BaudRxconf);
   
    return status;
}

int32 UTRX_RXCONF_SetBaud(uint32 BaudRxconf)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_RXCONF;
    uint16 addr = UTRX_ADDR_RXCONF_BAUD;
    
    status = CFE_SRL_ApiSetRparamCSP(GS_PARAM_UINT32, CSP_NODE_UTRX, table_id, addr, &BaudRxconf);
   
    return status;
}

int32 UTRX_TXCONF_SetFreq(uint32 FreqTxconf)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_TXCONF;
    uint16 addr = UTRX_ADDR_RXCONF_FREQ;
   
    status = CFE_SRL_ApiSetRparamCSP(GS_PARAM_UINT32, CSP_NODE_UTRX, table_id, addr, &FreqTxconf);
 
    return status;
}

int32 UTRX_TXCONF_GetFreq(uint32 *FreqTxconf)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_TXCONF;
    uint16 addr = UTRX_ADDR_RXCONF_FREQ; // Same as receiver parameter

    status = CFE_SRL_ApiGetRparamCSP(GS_PARAM_UINT32, CSP_NODE_UTRX, table_id, addr, FreqTxconf);

    return status;
}



int32 UTRX_TXCONF_SetBaud(uint32 BaudTxconf)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_TXCONF;
    uint16 addr = UTRX_ADDR_TXCONF_BAUD;
    

   status = CFE_SRL_ApiSetRparamCSP(GS_PARAM_UINT32, CSP_NODE_UTRX, table_id, addr, &BaudTxconf);
   
    return status;
}

int32 UTRX_SetDefaultBaud(void)
{
    int32 status = DEVICE_SUCCESS;  
    status |= UTRX_RXCONF_SetBaud(UTRX_DEFUALT_BAUDRATE);
    status |= UTRX_TXCONF_SetBaud(UTRX_DEFUALT_BAUDRATE);

    return status;
}

int32 UTRX_RparamSave1(void)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_RXCONF;
   
    status = gs_rparam_save(CSP_NODE_UTRX, 1000, table_id, UTRX_TABLE_RXCONF); //time out : 1000 = 1 sec  
    return status;
}

int32 UTRX_RparamSave5(void)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_TXCONF;


    status = gs_rparam_save(CSP_NODE_UTRX, 1000, table_id, UTRX_TABLE_TXCONF);
   
    return status;
}

int32 UTRX_RparamSaveAll(void)
{
    int32 status = DEVICE_SUCCESS;
   
    status |= UTRX_RparamSave1();
    status |= UTRX_RparamSave5();

    return status;
}
/////////////////////////////////////////////////////////////////////////////////
//Request Telemetery/////////////////////////////////////////////////////////////
int32 UTRX_GetStatusConfiguration(UTRX_ConfBitTable_t *StatusConfiguration)
{
    int32 status = DEVICE_SUCCESS;
    uint8 ActiveConf;
    uint32 BaudRxconf;
    uint16 GuardRxconf;
    uint32 BaudTxconf;

    status |= UTRX_TLM_GetActiveConf(&ActiveConf);
    status |= UTRX_RXCONF_GetBaud(&BaudRxconf);
    status |= UTRX_RXCONF_GetGuard(&GuardRxconf);
    status |= UTRX_TXCONF_GetBaud(&BaudTxconf);

    if (ActiveConf == 0)
    {
        StatusConfiguration += 0x00 << 6;
    }
    else if (ActiveConf == 1)
    {
        StatusConfiguration += 0x01 << 6;
    }
    else if (ActiveConf == 2)
    {
        StatusConfiguration += 0x02 << 6;
    }
    else
    {
        StatusConfiguration += 0x03 << 6;
    }
    
    if (GuardRxconf == 0)
    {
        StatusConfiguration += 0x00 << 4;
    }
    else if (GuardRxconf == 150)
    {
        StatusConfiguration += 0x01 << 4;
    }
    else if (GuardRxconf == 300)
    {
        StatusConfiguration += 0x02 << 4;
    }
    else
    {
        StatusConfiguration += 0x03 << 4;
    }

    if (BaudRxconf == 2400)
    {
        StatusConfiguration += 0x00 << 2;
    }
    else if (BaudRxconf == 4800)
    {
        StatusConfiguration += 0x01 << 2;
    }
    else if (BaudRxconf == 9600)
    {
        StatusConfiguration += 0x02 << 2;
    }
    else
    {
        StatusConfiguration += 0x03 << 2;
    }

    if (BaudTxconf == 2400)
    {
        StatusConfiguration += 0x00 << 0;
    }
    else if (BaudTxconf == 4800)
    {
        StatusConfiguration += 0x01 << 0;
    }
    else if (BaudTxconf == 9600)
    {
        StatusConfiguration += 0x02 << 0;
    }
    else
    {
        StatusConfiguration += 0x03 << 0;
    }

    return status;
}





int32 UTRX_RXCONF_GetGuard(uint16 *GuardRxconf)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_RXCONF;
    uint16 addr = UTRX_ADDR_RXCONF_GUARD;
  

    status = CFE_SRL_ApiGetRparamCSP(GS_PARAM_UINT16,CSP_NODE_UTRX, table_id, addr, GuardRxconf);  
    return status;
}

int32 UTRX_TXCONF_GetBaud(uint32 *BaudTxconf)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_TXCONF;
    uint16 addr = UTRX_ADDR_TXCONF_BAUD;
   
    status = CFE_SRL_ApiGetRparamCSP(GS_PARAM_UINT32, CSP_NODE_UTRX, table_id, addr, BaudTxconf);
    
    return status;
}

int32 UTRX_TLM_GetTempBrd(int16 *TempBrd)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_TLM;
    uint16 addr = UTRX_ADDR_TLM_TEMP_BRD;
     
    status = CFE_SRL_ApiGetRparamCSP(GS_PARAM_UINT16, CSP_NODE_UTRX, table_id, addr, TempBrd);
   
    return status;
}


int32 UTRX_TLM_GetLastRssi(int16 *LastRssi)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_TLM;
    uint16 addr = UTRX_ADDR_TLM_LAST_RSSI;
    

   status = CFE_SRL_ApiGetRparamCSP(GS_PARAM_UINT16, CSP_NODE_UTRX, table_id, addr, LastRssi);
    
   return status;
}

int32 UTRX_TLM_GetLastRferr(int16 *LastRferr)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_TLM;
    uint16 addr = UTRX_ADDR_TLM_LAST_RFERR;
    

    status = CFE_SRL_ApiGetRparamCSP(GS_PARAM_UINT16, CSP_NODE_UTRX, table_id, addr, LastRferr);
  
    return status;
}

int32 UTRX_TLM_GetActiveConf(uint8 *ActiveConf)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_TLM;
    uint16 addr = UTRX_ADDR_TLM_ACTIVE_CONF;
     
    status = CFE_SRL_ApiGetRparamCSP(GS_PARAM_UINT8, CSP_NODE_UTRX, table_id, addr, ActiveConf);
    
    return status;
}

int32 UTRX_TLM_GetBootCount(uint16 *BootCount)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_TLM;
    uint16 addr = UTRX_ADDR_TLM_BOOT_COUNT;
    
    status = CFE_SRL_ApiGetRparamCSP(GS_PARAM_UINT16, CSP_NODE_UTRX, table_id, addr, BootCount);
    

    return status;
}

int32 UTRX_TLM_GetBootCause(uint32 *BootCause)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_TLM;
    uint16 addr = UTRX_ADDR_TLM_BOOT_CAUSE;
   
    status = CFE_SRL_ApiGetRparamCSP(GS_PARAM_UINT32, CSP_NODE_UTRX, table_id, addr, BootCause);
    
    return status;
}

int32 UTRX_TLM_GetLastContact(uint32 *LastContact)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_TLM;
    uint16 addr = UTRX_ADDR_TLM_LAST_CONTACT;
   
    status = CFE_SRL_ApiGetRparamCSP(GS_PARAM_UINT32, CSP_NODE_UTRX, table_id, addr, LastContact);  

    return status;
}

int32 UTRX_TLM_GetTotTxBytes(uint32 *TotTxBytes)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_TLM;
    uint16 addr = UTRX_ADDR_TLM_TOT_TX_BYTES;
     

    status = CFE_SRL_ApiGetRparamCSP(GS_PARAM_UINT32, CSP_NODE_UTRX, table_id, addr, TotTxBytes);
    
    return status;
}

int32 UTRX_TLM_GetTotRxBytes(uint32 *TotRxBytes)
{
    int32 status = DEVICE_SUCCESS;
    gs_param_table_id_t table_id = UTRX_TABLE_TLM;
    uint16 addr = UTRX_ADDR_TLM_TOT_RX_BYTES;
    
    status = CFE_SRL_ApiGetRparamCSP(GS_PARAM_UINT32, CSP_NODE_UTRX, table_id, addr, TotRxBytes);
  
    return status;
}

UTRX_csp_transconf_t * transconf[32];

int32 csp_checkstate_ping(uint8_t node)
{   
    if (transconf[node] == NULL) {
        CFE_EVS_SendEvent(5004, CFE_EVS_EventType_ERROR,
                          "UTRX: transconf[%d] is NULL, cannot ping", node);
        return IFC_ERROR;
    }

    int rtt = CFE_SRL_PingCSP(node, 1000, 4, transconf[node]->opts);


    if (rtt > 0) {
        OS_printf("[CSP] Ping to node %d successful, RTT = %d ms\n", node, rtt);
        return IFC_OK;
    } 
    else {
        OS_printf("[CSP] Ping to node %d failed\n", node);
        return IFC_ERROR;
    }
}

int32 csp_transconf_get(uint8_t node, UTRX_csp_transconf_t* conf)
{
    if(!conf)
        return IFC_ERR_NULL;
    if(!transconf[node])
        return IFC_ERR_NOT_FOUND;

    conf = transconf[node];
    
    return IFC_OK;
}

uint32 csp_get_timeout(uint8_t node)
{
    UTRX_csp_transconf_t tsconf;
    if(csp_transconf_get(node, &tsconf) != 0)
        return CSP_DEFAULT_TIMEOUT_LOCAL;
    return tsconf.timeout;
}