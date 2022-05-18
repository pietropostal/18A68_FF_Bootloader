/*
 * version_info.h
 *
 *  Created on: 02.02.2022
 *      Author: enrico
 */

#ifndef BSW_COM_CANIF_VERSION_INFO_H_
#define BSW_COM_CANIF_VERSION_INFO_H_

#define CAN0APPL_xxLM_VERSIONINFOMUX_SIZE   (18U)

typedef struct CANApplDef_strTxMsg_tag  ///< Type of Tx-Message Struct
{
    uint8_t             TxEnabled;
    uint16_t            CycleTime;  /* [ms] */
    uint16_t            CycleTimeCnt;
    uint16_t            AmountToSend; /* 0xFF: endless */
    uint32_t            ID;
    uint8_t             DLC;
    uint8_t             Remote;
    uint8_t             Extended;
    uint8_t             aMsg[8];
}CANApplDef_strTxMsg_t;

extern void CANIF_VersionInfo_Init( void );
extern CANApplDef_strTxMsg_t *CANIF_VersionInfo( uint8 coding );

#endif /* BSW_COM_CANIF_VERSION_INFO_H_ */
