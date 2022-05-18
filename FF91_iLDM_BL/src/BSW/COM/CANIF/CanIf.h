/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : CanIf.h
** Module name  : CAN Interaction-Presentation Layer
** -------------------------------------------------------------------------------------------------
** Description : Include file of component CanIf.c
**
** -------------------------------------------------------------------------------------------------
**
** Documentation reference : None
**
****************************************************************************************************
** R E V I S I O N  H I S T O R Y
****************************************************************************************************
** V01.00 05/08/2019
** - Baseline Created
** ------------------------------------------------------------------------------------------------
**
**
***************************************************************************************************/

/* To avoid multi-inclusions */
#ifndef CANIF_H
#define CANIF_H

/************************************* Inclusion files ********************************************/
#include "Platform_Types.h"
#include "Compiler.h"
#include "ProjectCfg.h"
/****************************** External links of global variables ********************************/
/************************** Declaration of global symbol and constants ****************************/
/*This variable indicates whether TP Message Transmission is in Progress or Not*/
EXTERN VAR(uint8, CANIF_VAR) CANIF_CANTPMsgStatus;

/********************************* Declaration of global macros ***********************************/


#define     CANIF_ZERO       (uint8)0x00u


#define CANT_EIGHT           ((uint8)0x08U)

/********************************* Declaration of global types ************************************/
typedef struct
{
    VAR(uint32, CANIF_VAR) Msg_ID;
    VAR(uint8, CANIF_VAR)  Id_Type;
    VAR(uint8, CANIF_VAR)  DLC;
    VAR(uint8, CANIF_VAR)  dataBuff[8u];
}CanIf_Msg_Type;
/* structure to hold the CANIF ID, data and call back function */
typedef struct
{
    VAR(uint32, CANIF_VAR) CANT_ID;						/* CANIF ID */
    VAR(uint8, CANIF_VAR) CANT_XTD;						/* CANIF Standard/Extended */
    VAR(uint8, CANIF_VAR) CANT_DataLen;					/* Number of data bytes */
    FUNC(void, CANIF_CODE) (*funcptr)(P2VAR(CanIf_Msg_Type, AUTOMATIC, CANIF_VAR) CANT_RxData);
														/* Callback Function */
}CANT_RxMsgConfigType;


/* structure to hold the CANIF ID, Data, Data Length */
typedef struct
{
    VAR(uint32, CANIF_VAR) CANT_ID;						/* CAN ID */
    VAR(uint8, CANIF_VAR) CANT_XTD;						/* CAN Standard/Extended */
    VAR(uint8, CANIF_VAR) CANT_DataLen;				/* Number of data bytes */
    P2VAR(uint8, AUTOMATIC, CANIF_VAR) CANT_DataPtr;	/* Data Pointer */
}CANIF_TxMsgConfigType;

/******************** Declaration of global macros ***********************************************/


/* Receive frames type */
/* CAN message configuration structure for receive frames */
typedef struct
{
    VAR(uint32, TYPEDEF) canID;                     /* CAN receive message ID */
    VAR(uint8, TYPEDEF) idType;                     /* ID type : Standard or extended */
     /* Pointer to callback function in case of TimeOut */
    P2FUNC(void, CAN_CODE, funCanAppPtr)(const CanIf_Msg_Type *rxFrame);
}Can_RxMsgConfType;

/* Transmit frames type */
/* CAN message configuration structure for transmit frames */
typedef struct
{
    VAR(uint32, TYPEDEF) canID;                     /* CAN transmit message ID */
    VAR(uint8, TYPEDEF) idType;                     /* ID type : Standard or extended */
    VAR(uint8, TYPEDEF) CanMailbox;                 /* Mail box number */
   P2FUNC(void, CAN_CODE, funCanAppPtr)(void);     /* Pointer to call back for CAN message */
}Can_TxMsgConfType;

typedef struct
{
    VAR(uint32, CANIF_VAR) SID;
    VAR(uint8, CANIF_VAR)  IDE;
    VAR(uint8, CANIF_VAR)  LENGTH;
    VAR(uint8, CANIF_VAR)  data8[8u];
}CANTConfigFrame;

/****************************** External links of global constants ********************************/
/* CAN transmit message table */
EXTERN  CONST(Can_TxMsgConfType, CAN_APPL_CONST) CanIf_TxMsgTab[];
/*ECU Localization status*/
EXTERN VAR(uint8, CANIF_VAR) u8ECULocalisationstatus;
/* CAN Receive Message table */
EXTERN  CONST(Can_RxMsgConfType, CAN_APPL_CONST) CanIf_RxMsgTab[];

/********************************** Function definitions ******************************************/
/***************************************************************************************************
** Function                 : CanIf_Init
** Description              : Initializing parameters of IF layer
** Parameter                : None
** Return value             : None
** Remarks                  : None
***************************************************************************************************/
EXTERN FUNC(void, CAN_CODE) CanIf_Init(void);

/***************************************************************************************************
** Function                 : CanIf_TransmitMsg
** Description              : Transmits the Can frame.
** Parameter                : Transmit_frame.
** Return value             : None
** Remarks                  : None
***************************************************************************************************/
EXTERN FUNC(void, CANIF_CODE) CanIf_TransmitMsg(P2VAR(CANIF_TxMsgConfigType,AUTOMATIC, CANIF_VAR) Transmit_frame,uint8 MsgIndex);

/***************************************************************************************************
** Function                 : CanIf_TxIndication
** Description              : Tx Indication function.
** Parameter                : None
** Return value             : None
** Remarks                  : None
***************************************************************************************************/
EXTERN FUNC(void, CAN_CODE) CanIf_TxIndication(void);

/***************************************************************************************************
** Function                 : CanIf_RxIndication
** Description              : Rx Indication function.
** Parameter                : pointer CANIF_RxDataPtr
** Return value             : None
** Remarks                  : None
***************************************************************************************************/

EXTERN FUNC(void, CANIF_CODE) CanIf_RxIndication(P2VAR(CanIf_Msg_Type, AUTOMATIC, CANIF_VAR) \
															CANIF_RxDataPtr);
#endif  /* CANIF_H */
