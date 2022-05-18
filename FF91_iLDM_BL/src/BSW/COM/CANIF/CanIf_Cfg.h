/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : CanIf.h
** Module name  : Configuration parameter of CanIf Module.
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
#ifndef CANIF_CFG_H
#define CANIF_CFG_H

/************************************* Inclusion files ********************************************/
#include "Platform_Types.h"
#include "Compiler.h"
#include "ProjectCfg.h"
/********************** component configuration **************************************************/
#define CANT_EXTENDED_ID     (CANT_EXTENDED)
#define CANT_STANDARD_ID     (CANT_STANDARD)

/*TBD*/
#define ECU_RESET_REASON            RCM->SRS

// Physical Id // Enrico removed
 //#define Diag_PHY_Req   						   CANT_PHYS_REQ_ID

// Functional Id
 #define Diag_FUN_Req 								CANT_FUNC_REQ_ID

 #define CANIF_DIAG_MSG_TX_INDX		 	     0u
 #define CANIF_RESET_REASON_TX_MSG_INDX		 1u
 #define CANIF_VERSION_MESSAGE_TX_INDX		 2u


/****************************** Declaration of exported variables *********************************/

/************************** Function definitions *************************************************/
#if 0 // enrico requirement is removed
EXTERN FUNC(void, CANIF_CODE) CANIF_RESET_REASON_TRANSMIT(void);
#endif

EXTERN FUNC(void, CANIF_CODE) CANIF_VERSION_MESSAGE_TRANSMIT(void);
EXTERN FUNC(void, CANIF_CODE) CANIF_DIAG_TRANSMIT(CanIf_Msg_Type DIAG_message);

// Enrico added
EXTERN FUNC(void, CANIF_CODE) CanIf_ConfigureIDs( uint32 uds_rx, uint32 uds_tx, uint32 version_id, uint32 reset_id );

/*************************************************************************************************/
#endif  /* CANIF_H */
