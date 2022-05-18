/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL.
**
** -------------------------------------------------------------------------------------------------
** File Name    : CanIf.c
** Module Name  : Can Interface Module
** -------------------------------------------------------------------------------------------------
**
** Description : Extracts the information from CAN driver and provides to upper layer and 
**               vice-versa.
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
 #include "CanTp.h"
/********************** Declaration of local symbol and constants *********************************/
/********************************* Declaration of local macros ************************************/
/********************************* Declaration of local types *************************************/
/******************************* Declaration of local variables ***********************************/

// Enrico
EXTERN VAR(CANT_RxMsgConfigType, CANT_CONST) CANT_RxMsgTable_PSM[2];

/*CANT Receive Message Table Size*/
VAR(uint8, CANT_VAR) CANT_RxMsgTablePSMSize ;

/******************************* Declaration of local constants ***********************************/
/****************************** Declaration of exported variables *********************************/
/****************************** Declaration of exported constants *********************************/
/*This variable indicates whether TP Message Transmission is in Progress or Not*/
VAR(uint8, CANIF_VAR) CANIF_CANTPMsgStatus;
VAR(uint8, CANIF_VAR) u8ECULocalisationstatus;
/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/***************************************************************************************************
** Function                 : CanIf_Init
** Description              : Initializing parameters of IF layer
** Parameter                : None
** Return value             : None
** Remarks                  : None
***************************************************************************************************/
FUNC(void, CAN_CODE) CanIf_Init(void)
{
	/* Get Table Size*/
	CANT_RxMsgTablePSMSize = (sizeof(CANT_RxMsgTable_PSM)/sizeof(CANT_RxMsgConfigType));

	/*Initialize CAN module*/
	CANT_Init(CAN_125KBPS, CANT_RxMsgTable_PSM, CANT_RxMsgTablePSMSize);

}
/***************************************************************************************************
** Function                 : CanIf_TransmitMsg
** Description              : Transmits the Can frame.
** Parameter                : Transmit_frame.
** Return value             : None
** Remarks                  : None
***************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_TransmitMsg(P2VAR(CANIF_TxMsgConfigType,AUTOMATIC, CANIF_VAR) Transmit_frame,uint8 MsgIndex)
{

	CAN0_TxMsg((uint32) Transmit_frame->CANT_ID, (uint32)Transmit_frame->CANT_DataLen,\
			(uint8*) Transmit_frame->CANT_DataPtr,Transmit_frame->CANT_XTD, MsgIndex);
}
/***************************************************************************************************
** Function                 : CanIf_RxIndication
** Description              : Rx Indication function.
** Parameter                : CAN Reception Data Pointer
** Return value             : None
** Remarks                  : None
***************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_RxIndication(P2VAR(CanIf_Msg_Type, AUTOMATIC, CANIF_VAR) \
								CANIF_RxDataPtr)
{
   /*Loop Index*/
  VAR(uint8, CANT_VAR) CANIF_iLoopIndex = CANIF_ZERO;

  for(CANIF_iLoopIndex = CANIF_ZERO; CANIF_iLoopIndex < CANT_RxMsgTablePSMSize; CANIF_iLoopIndex++)
  {
    /*Check Whether CAN Identifier is Matching*/
    if((CANIF_RxDataPtr->Msg_ID ) == (CANT_RxMsgTable_PSM[CANIF_iLoopIndex].CANT_ID))
    {
      /*Check Whether CAN Identifier is Standard or Extended and it is matching with
      the configured ID*/
      if(CANIF_RxDataPtr->Id_Type == (CANT_RxMsgTable_PSM[CANIF_iLoopIndex].CANT_XTD))
      {
        /*Check Whether DLC is Matching*/
        if((CANIF_RxDataPtr->DLC) == (CANT_RxMsgTable_PSM[CANIF_iLoopIndex].CANT_DataLen))
        {
          /*Callback Function for Handling CAN Rx Messages*/
          (CANT_RxMsgTable_PSM[CANIF_iLoopIndex].funcptr)(CANIF_RxDataPtr);

          /*Exit from the Loop*/
          CANIF_iLoopIndex = CANT_RxMsgTablePSMSize;
        }
        else
        {
          /*Incorrect Data Length length Received*/
        }
      }
      else
      {
        /*Incorrect Identifier Received*/
      }
    }
    else
    {
      /*Incorrect Id Received*/
    }
  }
}

/***************************************************************************************************
** Function                 : CanIf_TxIndication
** Description              : Tx Indication function.
** Parameter                : None
** Return value             : None
** Remarks                  : None
***************************************************************************************************/
FUNC(void, CAN_CODE) CanIf_TxIndication(void)
{
    /*CAN TP call back function to transmit rest of the bytes*/
	ISOTP_TxCnfCbk();
}
