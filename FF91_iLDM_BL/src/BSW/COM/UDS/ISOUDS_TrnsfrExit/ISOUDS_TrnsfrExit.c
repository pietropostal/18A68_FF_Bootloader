/***************************************************************************************************
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_TrnsfrExit.c
**
** Description  : Data Transfer Exit Service
**
** -------------------------------------------------------------------------------------------------
**
***************************************************************************************************/

/**************************************** Inclusion files *****************************************/
#include "ISOUDS_TrnsfrExit.h"
#include "ISOUDS_TrnsfrDa.h"

/********************** Declaration of local symbol and constants *********************************/

/********************************* Declaration of local macros ************************************/
#define     ISOUDS_TRNSFREXITSERLEN       (1)      /* Service length */
/********************************* Declaration of local types *************************************/

/******************************* Declaration of local variables ***********************************/

/******************************* Declaration of local constants ***********************************/

/****************************** Declaration of exported variables *********************************/

/****************************** Declaration of exported constants *********************************/

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/**************************** Internal functions declarations *************************************/

/******************************** Function definitions ********************************************/

/***************************************************************************************************
** Function                 : ISOUDS_TrnsfrExit

** Description              : Sends response to Transfer exit service request

** Parameter ISOUDSConfPtr  : Pointer to service configuration structure

** Parameter dataBuff       : Data array

** Return value             : None
***************************************************************************************************/
void ISOUDS_TrnsfrExit (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[])
{
    /* check if received length is valid */
    if (ISOUDSConfPtr->srvLen == (uint16)ISOUDS_TRNSFREXITSERLEN)
    {
		/* check if we can exit transfer data */
		if (ISOUDS_FALSE == ISOUDS_ChkTrnsfrExit())
		{
			/* exit transfer data */
			ISOUDS_TrnsfrDaExit();
		
			/* Response length for the current Service - including SID */
			ISOUDSConfPtr->srvLen = (uint16)1;
		
			/* Send positive response */
			ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
			
			/* Set the Boot State. */
		    ISOUDS_SetBootSeqState(ISOUDS_COMPARECHECK_STATE);

		}
		else
		{
			/* Request Sequence error */
			ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_RSE;
		
			/* Negative response */
			ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;
		}
    }
    else
    {
        /* Invalid Message Length */
        ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_IMLOIF;

        /* Negative response */
        ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;
    }
}
