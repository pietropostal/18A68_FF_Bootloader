/***************************************************************************************************
 ** Copyright (c) 2019 EMBITEL
 **
 ** This software is the property of EMBITEL.
 ** It can not be used or duplicated without EMBITEL.
 **
 ** -------------------------------------------------------------------------------------------------
 ** File Name    : CanId_Cfg.c
 ** Module Name  : CanIf
 ** -------------------------------------------------------------------------------------------------
 **
 ** Description : Configuration parameter of CanIf Module.
 **
 **
 ** -------------------------------------------------------------------------------------------------
 **
 ** Documentation reference : None
 **
 ****************************************************************************************************
 ** R E V I S I O N H I S T O R Y
 ****************************************************************************************************
 ** V01.00 05/08/2019
 ** - Baseline Created
 ** ------------------------------------------------------------------------------------------------
 **
 **
 ***************************************************************************************************/
/**************************************** Inclusion files *****************************************/
#include "CANT.h"
#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "CanTp.h"
#include "ISOUDS.h"
#include "FLSHM.h"
#include "version_info.h"
#include "Globals.h"

/********************** Declaration of local symbol and constants *********************************/
/********************************* Declaration of local macros ************************************/

/********************************* Declaration of local types *************************************/


/******************************* Declaration of local variables ***********************************/
/******************************* Declaration of local constants ***********************************/
/****************************** Declaration of exported variables *********************************/

/**************************************************************************************************
 ** FUNCTIONS **
 **************************************************************************************************/
/******************** Internal functions declarations ********************************************/
/************************** Function definitions *************************************************/

// Enrico moved to this file and make writeable
/* CANIF Receive Message configuration table */
VAR(CANT_RxMsgConfigType, CANT_CONST) CANT_RxMsgTable_PSM[2] =
{
	//{Diag_PMS_Req, CANT_XTD_STANDARD, CANT_EIGHT, &CANT_VCU_0x616_Callback},
	{CANT_PHYS_REQ_ID, CANT_STANDARD_ID, CANT_EIGHT,(void (*)(P2VAR(CanIf_Msg_Type, AUTOMATIC, CanTp)))(ISOTP_RxMsgCbk)},
    {CANT_FUNC_REQ_ID, CANT_STANDARD_ID, CANT_EIGHT,(void (*)(P2VAR(CanIf_Msg_Type, AUTOMATIC, CanTp)))(ISOTP_RxMsgCbk)},
};

//  Enrico added configuration
static uint32 versioninfo_id = CAN_VERSIONINFO_ID, uds_tx_id = CANT_TX_ID;

EXTERN FUNC(void, CANIF_CODE) CanIf_ConfigureIDs( uint32 uds_rx, uint32 uds_tx, uint32 version_id, uint32 reset_id )
{
	CANT_RxMsgTable_PSM[0].CANT_ID = uds_rx;
	uds_tx_id = uds_tx;
	versioninfo_id = version_id;
}


FUNC(void, CANIF_CODE) CANIF_DIAG_TRANSMIT(CanIf_Msg_Type DIAG_message)
{
	/*PASSENGER ECU Selected*/
	/* Data Frame*/
	VAR(CANIF_TxMsgConfigType, CANIF_VAR) CAN_txmessage;

	/* Data Frame Message ID*/
	CAN_txmessage.CANT_ID = uds_tx_id; // Enrico

	/*To select CAN ID is Extended or Standard*/
	CAN_txmessage.CANT_XTD = CANT_STANDARD_ID;

	/*Data Frame Data Length*/
	CAN_txmessage.CANT_DataLen = DIAG_message.DLC;

	CAN_txmessage.CANT_DataPtr = &DIAG_message.dataBuff[0u];

	/*Send Data to CAN Network*/
	CanIf_TransmitMsg(&CAN_txmessage, CANIF_DIAG_MSG_TX_INDX);
}

#if 0 // enrico requirement is removed
FUNC(void, CANIF_CODE) CANIF_RESET_REASON_TRANSMIT(void)
{
	uint8 ecu_reset_reason;
	uint8 RevID;
	uint32 HardwareID;
	uint8 buff[8]={0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA};

	/*PASSENGER ECU Selected*/
	/* Data Frame*/
	VAR(CANIF_TxMsgConfigType, CANIF_VAR) CAN_txmessage;

	/* Data Frame Message ID*/
	CAN_txmessage.CANT_ID = CAN_RESETREASON_ID;

	/*To select CAN ID is Extended or Standard*/
	CAN_txmessage.CANT_XTD = CANT_STANDARD_ID;

	/*Data Frame Data Length*/
	CAN_txmessage.CANT_DataLen = 8;

	HardwareID= (uint32)0x12345678;

	RevID=(uint8)0x12;

	/*Hardware part number need to update*/
	buff[0]=(uint8)((HardwareID&0xFF0000)>>16);
	buff[1]=(uint8)((HardwareID&0xFF00)>>8);
	buff[2]=(uint8)((HardwareID&0xFF));

   /* Hardware revision ID */
	buff[3]=RevID;//System Device Identification Register

	if(RCM_SRS_POR(ECU_RESET_REASON)==TRUE)
	{
		ecu_reset_reason=0x01;
	}
	else if((RCM_SRS_WDOG(ECU_RESET_REASON))==TRUE)
	{
		ecu_reset_reason=0x02;
	}
	else if(ISOUDS_EcuRstReq==TRUE)
	{
		ecu_reset_reason=0x04;
	}else
	{

		/* do nothing*/
	}

	/*ECU reset reason*/
	buff[5]=ecu_reset_reason;

	/*Bootloader struck reason*/
	buff[6]=bootloader_struck_reason;

	/*Resrved*/
	buff[7]=0xFF;

	CAN_txmessage.CANT_DataPtr = &buff[0u];

   if(ecu_reset_reason!=0x00U)
   {
	/*Send Data to CAN Network*/
	CanIf_TransmitMsg(&CAN_txmessage,CANIF_RESET_REASON_TX_MSG_INDX);
   }
   else
   {
	   /* do nothing */
   }

}
#endif


FUNC(void, CANIF_CODE) CANIF_VERSION_MESSAGE_TRANSMIT(void)
{
	CANApplDef_strTxMsg_t *msg;

	/*PASSENGER ECU Selected*/
	/* Data Frame*/
	VAR(CANIF_TxMsgConfigType, CANIF_VAR) CAN_txmessage;

	/* Data Frame Message ID*/
	// Enrico adapt Version ID
	CAN_txmessage.CANT_ID = versioninfo_id; // Enrico

	/*To select CAN ID is Extended or Standard*/
	CAN_txmessage.CANT_XTD = CANT_STANDARD_ID;

	/*Data Frame Data Length*/
	CAN_txmessage.CANT_DataLen = 8;


	// wait for coding
	if( eCodingType )
	{
		uint8 coding = (uint8)eCodingType - 1u;

		msg = CANIF_VersionInfo( coding );

		CAN_txmessage.CANT_DataPtr = &msg->aMsg[0];

		/*Send Data to CAN Network*/
		CanIf_TransmitMsg(&CAN_txmessage,CANIF_VERSION_MESSAGE_TX_INDX);
	}


}
/******************** Declaration of exported constant *******************************************/

