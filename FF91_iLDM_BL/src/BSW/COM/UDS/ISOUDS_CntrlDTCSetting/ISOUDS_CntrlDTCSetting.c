/*******************************************************************************
**
** -----------------------------------------------------------------------------
** File Name    : ISOUDS_CntrlDTCSetting.c
**
** Description  : Control DTC Setting Service
**
** -----------------------------------------------------------------------------
**
*******************************************************************************/

/**************************************** Inclusion files *********************/
#include "ISOUDS_CntrlDTCSetting.h"

/********************** Declaration of local symbol and constants *************/
#define ISOUDS_DTCSETON     (uint8)1    /* DTC Setting ON */
#define ISOUDS_DTCSETOFF    (uint8)2    /* DTC Setting OFF */
#define ISOUDS_CNTRLDTCSETSERLEN    (2) /* Service Length */


/********************************* Declaration of local macros ****************/

/********************************* Declaration of local types *****************/

/******************************* Declaration of local variables ***************/

/******************************* Declaration of local constants ***************/

/****************************** Declaration of exported variables *************/

/****************************** Declaration of exported constants *************/

/*******************************************************************************
**                                      FUNCTIONS                              *
*******************************************************************************/

/**************************** Internal functions declarations *****************/

/******************************** Function definitions ************************/
/*******************************************************************************
** Function                 : ISOUDS_CntrlDTCSetting

** Description              : Control DTC Setting

** Parameter canSrvDConfPtr : Pointer to service configuration structure

** Parameter dataBuff       : Pointer to service data buffer

** Return value             : None
*******************************************************************************/
void ISOUDS_CntrlDTCSetting (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[])
{
    uint8 posResp;
    uint8 DtcOnOff;
	

    /* init service state with negative response */
    ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

    /* check if we have received correct message request length */
    if (ISOUDSConfPtr->srvLen >= (uint16)ISOUDS_CNTRLDTCSETSERLEN)
    {
        /* get the DTC setting value */
        DtcOnOff = dataBuff[0] & (uint8)0x7F;

        /* Get only the suppressPosRspMsgIndicationBit value */
        /* 1-> implies Do not send positive response */
        posResp = dataBuff[0] & (uint8)0x80;
		
        /* Check if the reset type is of hardReset */
        if ((DtcOnOff == ISOUDS_DTCSETON) || (DtcOnOff == ISOUDS_DTCSETOFF))
        {			
			
					
                    /* check if positive response is to be sent */
                    if (posResp == (uint8)0)
                    {
                        /* Store the reset type in response buffer */
                        dataBuff[0] = DtcOnOff;

                        /* Response length for the current Service - including 
						   SID */
                        ISOUDSConfPtr->srvLen = (uint16)2;

                        /* Send positive response */
                        ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
                    }
                    else
                    {
                        /* Reset the required SrvD parameters and Go To IDLE 
						   state */
                        ISOUDS_Rst ();
                    }

        }
        else
        {
            /* Sub Function Not Supported */
            ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_SFNS;
        }
    }
    else
    {
        /* Invalid Message Length Or Invalid Format */
        ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_IMLOIF;
    }
}
/**************************** Internal Function definitions *******************/
