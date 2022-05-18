/***************************************************************************************************
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS.h
**
** Description  : Include file of component ISOUDS.c
**
** -------------------------------------------------------------------------------------------------
**
***************************************************************************************************/

/* To avoid multi-inclusions */
#ifndef ISOUDS_H
#define ISOUDS_H

/************************************* Inclusion files ********************************************/
#include "CanTp.h"
#include "UDS_Cfg.h"
/************************** Declaration of global symbol and constants ****************************/
#define     ISOUDS_TRUE            (0x01)      /* ISOUDS_TRUE state */
#define     ISOUDS_FALSE           (0x00)      /* ISOUDS_FALSE state */

#define     ISOUDS_DS              (0x01)      /* Default Session */
#define     ISOUDS_PRGS            (0x02)      /* Programming Session */
#define     ISOUDS_EXTDS           (0x03)      /* Extended diagnostic Session */
//#define     ISOUDS_SSDS          	(0x04)      /* Extended diagnostic Session */
#define     ISOUDS_NEGRESPSID      (0x7F)      /* SID for Negative response */

/* Negative response codes (ISO 14229) */
#define     ISOUDS_SNSIAS			(0x7FU)/* Service Not Supported In Active Session */
#define     ISOUDS_SNS				(0x11U)/* Service Not Supported */
#define     ISOUDS_SFNS				(0x12U)/* Sub Function Not Supported */
#define     ISOUDS_IMLOIF			(0x13U)/*Incorrect Message Length Or Invalid Format*/
//#define     ISOUDS_RESTOOLONG		(0x14U)   Response Too Long
#define     ISOUDS_RCRRP			(0x78U)/*Request Correctly ReceivedResponse Pending*/
#define     ISOUDS_ROOR				(0x31U)/* Request Out of Range */
#define     ISOUDS_CNC				(0x22U)/* Conditions Not Correct */
#define     ISOUDS_GPF				(0x72U)/* General Programming Failure */
#define     ISOUDS_SAD     			(0x33U)/* Security Access Denied */
#define     ISOUDS_UDNA    			(0x70U)/* Upload/Download not accepted */
#define     ISOUDS_RSE     			(0x24U)/* Request Sequence Error */
#define     ISOUDS_WBSC    			(0x73U)/* Wrong Block Sequence Counter*/
#define     ISOUDS_TDS     			(0x71U)/* Transfer Data Suspended */
#define     ISOUDS_IK      			(0x35U)/* Invalid Key */
#define     ISOUDS_ENOA    			(0x36U)/* Exceeded Number of Attempts */
#define     ISOUDS_RTDNE   			(0x37U)/* Required Time Delay Not Expired */
//#define     ISOUDS_SFNSACTSESS		(0x7EU) Security Access Denied 

/* State machine values */
#define     ISOUDS_IDLE				(0x00)      /* Idle */
#define     ISOUDS_RXPEND			(0x01)      /* Receive Pending */
#define     ISOUDS_RXMSG			(0x02)      /* Message received */
#define     ISOUDS_RESP				(0x03)      /* Positive response */
#define     ISOUDS_RESPNEG			(0x04)      /* Negative response */
#define     ISOUDS_RESPPEND			(0x05)      /* Response pending */
#define     ISOUDS_TXRESPPEND		(0x06)      /* Transmit response pending */
#define     ISOUDS_TXPEND			(0x07)      /* Transmission confirmation Pending */

/********************************* Declaration of global macros ***********************************/




/********************************* Declaration of global types ************************************/
typedef struct
{
    uint8  ReqType;          /* UDS service state */
    uint8  srvSt;          /* UDS service state */
    uint8  srvId;          /* UDS service id */
    uint8  srvNegResp;     /* Negative response code of the service */
    uint8  srvFrame;       /* Service request received in single or multiple frame */
    uint16 srvLen;         /* length */
}ISOUDS_ConfType;

/*BootSeqence state*/
typedef enum
{
   ISOUDS_SETBOOT_STATE = 0x10,
   ISOUDS_ACCESSTIMEORLINK_STATE,
   ISOUDS_ERASEFLASH_STATE ,
   ISOUDS_REQDW_STATE,
   ISOUDS_TRANSFERDATA_STATE,
   ISOUDS_TRANSFEREXIT_STATE,
   ISOUDS_COMPARECHECK_STATE,
   ISOUDS_UPDATEHISTORY_STATE,
   ISOUDS_CLRBOOT_STATE,
   ISOUDS_RESET_STATE,   
} ISOUDS_BootSeqType;

/****************************** External CANks of global variables ********************************/
/* ECU Reset Request */
extern uint8 ISOUDS_EcuRstReq;

/* UDS Buffer for data */
extern uint8 ISOUDS_Buff[ISOUDS_BUFFSIZE];

/* UDS current session */
extern uint8 ISOUDS_Sess;

/* Timer for Ecu Reset */
extern uint32 ISOUDS_TmrECURst;

/* UDS configuration */
extern ISOUDS_ConfType ISOUDS_Conf;
extern uint8 BootFlag_ECUSt;
extern uint8 FLSHM_ECUmode;
extern uint8 bootloader_struck_reason;

extern uint8 ISOUDS_ApplFlag;
extern uint8 ISOUDS_BootFlag;
/****************************** External CANks of global constants ********************************/

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/********************************** Function definitions ******************************************/
extern void ISOUDS_Init (uint8 bootflag);
extern void ISOUDS_Main (void);
extern void ISOUDS_MsgIndi (const ISOTP_CfgType *isoTpConfPtr, uint8 ISOTP_ReqMsgTpe);
extern void ISOUDS_FFIndi (const ISOTP_CfgType *isoTpConfPtr, uint8 ISOTP_ReqMsgTpe);
extern void ISOUDS_TxCnfCbk (void);
extern void ISOUDS_Rst (void);
extern void ISOUDS_Mon (void);
extern void ISOUDS_ReqECUReset (uint8 reset_type);
extern void ISOUDS_SetBootSeqState (ISOUDS_BootSeqType BootSt);
extern uint8 ISOUDS_CheckBootSeqState (ISOUDS_BootSeqType BootSt);
extern void ISOUDS_EnterAppl (void);
extern uint8 ISOUDS_SetAccessParameters(uint32 P2min, uint32 P2max, uint32 STmin);
extern uint8 ISOUDS_GetSessionStat(void);
extern void ISOUDS_MsgIndiIm (const ISOTP_CfgType *isoTpConfPtr);
#endif  /* ISOUDS_H */
