/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name : CanTp.h
** Module Name : CanTp
** -------------------------------------------------------------------------------------------------
**
** Description : Include file of component CanTp.c
** This file must exclusively contain informations needed to
** use this component.
**
** -------------------------------------------------------------------------------------------------
**
** Documentation reference : EME-17ST013-12070.01 (SWLLD CanTp)
**
****************************************************************************************************
** R E V I S I O N H I S T O R Y
****************************************************************************************************
** V01.00 13/07/2019
** - Baseline Created
**
***************************************************************************************************/
/* To avoid multi-inclusions */
#ifndef CanTp_H
#define CanTp_H

/************************************* Inclusion files ********************************************/
#include "CanTp_Cfg.h"
#include "Platform_Types.h"
#include "Compiler.h"
#include "CanIf_Cfg.h"
#include "CanIf.h"

/************************** Declaration of global symbol and constants ****************************/
/****************************** External links of global variables ********************************/

/********************************* Declaration of global macros ***********************************/

#define     ISOTP_FALSE                 0x00U  
#define     ISOTP_TRUE                  0x01U

#define     ISOTP_ZERO                  0x00U
#define     ISOTP_ONE                   0x01U
#define     ISOTP_TWO                   0x02U
#define     ISOTP_THREE                 0x03U
#define     ISOTP_SIX                   0x06U
#define     ISOTP_SEVEN                 0x07U
#define     ISOTP_EIGHT                 0x08U
#define     ISOTP_FRAMEMASK             (0xF0U)  
#define     ISOTP_SEQMASK               (0x0FU)  
#define     ISOTP_TIMERLMT              (0x0AU)

#define     ISOTP_TIMERLMT1             (0x7FU)  
#define     ISOTP_TIMERLMT2             (0xF1U)  
#define     ISOTP_TIMERLMT3             (0xF9U)  

/* Frame Types */
#define     ISOTP_SF                    (0x00U)  /* Single frame */
#define     ISOTP_FF                    (0x10U)  /* First frame */
#define     ISOTP_CF                    (0x20U)  /* Consecutive frame */
#define     ISOTP_FC                    (0x30U)  /* Flow Control frame */

/* Index of ISOTP_iTimeOut[] structure */
#define     ISOTP_TXIDX                 (0x00U)  /* Transmission(sender) timer limits index */
#define     ISOTP_RXIDX                 (0x01U)  /* Reception(receiver) timer limits index */

/* State machine values */
#define     ISOTP_NWLST_IDLE            (0x00U)      /* Idle */
#define     ISOTP_NWLST_RXINPROG        (0x01U)      /* Receive in progress */
#define     ISOTP_NWLST_PROCINPROG      (0x02U)      /* Processing in progress */
#define     ISOTP_NWLST_TXINPROG        (0x03U)      /* Transmission in progress */

/* Flow status : Continue To Send */
#define     ISOTP_FCCTS                 (0x00U)
/* Flow status : WAIT */                
#define     ISOTP_FCWT                  (0x01U)
/* Flow status : Overflow */            
#define     ISOTP_FCOVFLW               (0x02U)
                                        
/* State machine values */              
#define     ISOTP_IDLE                  (0x00U)
//#define     ISOTP_SFRX                  (0x01U)
#define     ISOTP_SFTX                  (0x02U)
//#define     ISOTP_FFRX                  (0x03U)
#define     ISOTP_FCTX                  (0x04U)
#define     ISOTP_FCTXREQ               (0x05U)
#define     ISOTP_CFWAIT                (0x06U)
#define     ISOTP_CFRX                  (0x07U)
#define     ISOTP_FFTX                  (0x08U)
#define     ISOTP_FCWAIT                (0x09U)
#define     ISOTP_CFTXWAIT              (0x0AU)
#define     ISOTP_CFTX                  (0x0BU)
#define     ISOTP_NEGRES                (0x7FU)      /* Negative Response Service Identifier */
#define     ISOTP_RSE                   (0x24U)      /* Request Sequence Error */
#define     ISOTP_NEGRESPLEN            (0x03U)        /* Negative response length */

/*Macros which indicates functional or physical request*/
#define ISOTP_PHY_REQUEST				0x1U
#define ISOTP_FUNC_REQUEST				0x2U
/********************************* Declaration of global types ************************************/
typedef struct
{
    uint32 tmrA;     /* timer A */
    uint32 tmrB;     /* timer B */
    uint32 tmrC;     /* timer C */
}ISOTP_TimeoutT;

enum
{
    ISOTP_OK = 0,
    ISOTP_TIMEOUT_A,
    ISOTP_TIMEOUT_BS,
    ISOTP_TIMEOUT_CR,
    ISOTP_WRONG_SN,
    ISOTP_INVALID_FS,
    ISOTP_UNEXP_PDU,
    ISOTP_WFT_OVRN,
    ISOTP_BUFFER_OVFLW,
    ISOTP_ERROR
};

typedef struct
{
    uint8 frmInfo;                    /* Byte #1 of PCI */
    uint8 seqNum;                     /* Sequence number (for Segmented frames) */
    uint16 nBytes;                    /* total number of bytes */
    uint8 tpBuff[ISOTP_BUFFSIZE];  /* data buffer */
}ISOTP_CfgType;

typedef struct
{
    uint8 *dataPtr;                    /* pointer to data */        
    uint16 dataLen;                    /* data buffer */
}ISOTP_App_CfgType;

/****************************** External links of global constants ********************************/
EXTERN  CONST(ISOTP_TimeoutT, CanSrv_VAR) ISOTP_iTimeOut[ISOTP_TIMEOUT_TAB];

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/
/***************************************************************************************************
** Function                 : CanTp_Init

** Description              : Initialization of CAN TP parameters

** Parameter                : None

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
EXTERN  FUNC(void, CAN_CODE) ISOTP_Init (void);
/***************************************************************************************************
** Function                 : CanTp_RxMsgCbk

** Description              : Receive callback function of Diagnostic frame

** Parameter rxData         : Data array

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
EXTERN  FUNC(void, CAN_CODE) ISOTP_RxMsgCbk(P2CONST(CanIf_Msg_Type, AUTOMATIC, CAN_TP) rxFrame);
/***************************************************************************************************
** Function                 : CanTp_TxRequest

** Description              : Transmits either single frame or first frame

** Parameter nBytes         : number of bytes to be transmitted

** Parameter txData         : Data array

** Return value             : CanTp_TRUE - If tramission request is placed successfully
                              CanTp_FALSE - If tramission request couldn't be placed

** Remarks                  : None
***************************************************************************************************/
EXTERN  FUNC(uint8, CAN_CODE) ISOTP_TxRequest (P2VAR(ISOTP_App_CfgType, AUTOMATIC,CAN_CODE)\
																					ISOTP_MsgCfg);
/***************************************************************************************************
** Function                 : CanTp_TxCnfCbk

** Description              : Transmit callback function of Diagnostic frame

** Parameter                : None

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
EXTERN  FUNC(void, CAN_CODE) ISOTP_TxCnfCbk (void);
/***************************************************************************************************
** Function                 : CanTp_Main

** Description              : TP Main function, runs continuously in Background

** Parameter                : None

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
EXTERN  FUNC(void, CAN_CODE) ISOTP_Main (void);
/***************************************************************************************************
** Function                 : CanTp_GetStatus

** Description              : Returns the status of TP module.

** Parameter rxData         : None

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
EXTERN  FUNC(uint8, CAN_CODE) ISOTP_GetStatus(void);
#endif
