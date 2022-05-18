/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_WrDaByID.c
** Module name  : CANWRDBID
** -------------------------------------------------------------------------------------------------
** Description : Configuration file of component CanSrv_WrDaByID.c
** This file must exclusively contain informations needed to
** use this component.
** -------------------------------------------------------------------------------------------------
**
** Documentation reference :
**
****************************************************************************************************
** R E V I S I O N  H I S T O R Y
****************************************************************************************************
** 
**
***************************************************************************************************/

/**************************************** Inclusion files *****************************************/

#include "ISOUDS_WrDaByID.h"

/********************** Declaration of local symbol and constants *********************************/

/********************************* Declaration of local macros ************************************/

/********************************* Declaration of local types *************************************/

/******************************* Declaration of local variaCanSrves *******************************/
/* MISRA RULE 8.7 VIOLATION: 'CanSrv_iRecvWrDid' is made static so that its value is retained -
    - when the service is called again due to response pending state */
STATIC VAR(uint8, CAN_VAR) CanSrv_iWrTabIdx;
STATIC VAR(uint16, CAN_VAR) CanSrv_iRecvWrDid;
/******************************* Declaration of local constants ***********************************/

/****************************** Declaration of exported variaCanSrves *****************************/

/****************************** Declaration of exported constants *********************************/

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/**************************** Internal functions declarations *************************************/

STATIC FUNC(boolean, CAN_CODE) CanSrv_iWrLookUp (VAR(uint16, AUTOMATIC) recvWrDid);

/******************************** Function definitions ********************************************/

/***************************************************************************************************
** Function                 : CanSrv_WrDaByID
** Description              : Sends response to Write Data by ID service request
** Parameter canSrvDConfPtr : Pointer to service configuration structure
** Parameter dataBuff       : Pointer to service data buffer
** Return value             : None
** Remarks                  : None
***************************************************************************************************/
FUNC(void, CAN_CODE) CanSrv_WrDaByID(P2VAR(ISOUDS_ConfType,AUTOMATIC,CAN_APPL_DATA)canSrvDConfPtr,\
                                                      VAR(uint8, AUTOMATIC) dataBuff[])
{
    VAR(uint8, AUTOMATIC)   WrDaSt;
    
    /* If service is invoked due to reception of new request */
    if (canSrvDConfPtr->srvSt == (uint8)ISOUDS_RXMSG)
    {
        /* Check if sufficient bytes are received */
        if (canSrvDConfPtr->srvLen > (uint8)3)
        {
            /* copy the data identifier value */
            CanSrv_iRecvWrDid = (((uint16)(((uint16)dataBuff[0]) << 8)) + ((uint16)dataBuff[1]));
			
            /* Check if DID is configured for write purpose */
            if (TRUE == CanSrv_iWrLookUp (CanSrv_iRecvWrDid))
            {
				 /* Check if DID is configured to be read in active session */
                if ((((CanSrv_cWrConfTab[CanSrv_iWrTabIdx].WrDidSess) >> ISOUDS_Sess) & (uint8)1) == (uint8)1)
                {
					/* Check if the received length is valid for write purpose */
					if (canSrvDConfPtr->srvLen == (CanSrv_cWrConfTab[CanSrv_iWrTabIdx].wrDidLen + (uint8)3))
					{
					   /* Execute the function for writing purpose */
						WrDaSt = (CanSrv_cWrConfTab[CanSrv_iWrTabIdx].wrDid_funPtr)(\
													CanSrv_iWrTabIdx,\
													&dataBuff[2],\
													CanSrv_cWrConfTab[CanSrv_iWrTabIdx].wrDidLen);

						/* Write Ok - DID written */
						if (WrDaSt == (uint8)0x01)
						{
								
							/* Prepare the response */
							dataBuff[0] = (uint8)(CanSrv_iRecvWrDid >> 8);
							dataBuff[1] = (uint8)CanSrv_iRecvWrDid;
							
							/* Response length for the current Service - including SID */
							canSrvDConfPtr->srvLen = (uint8)3;

							/* Send positive response */
							canSrvDConfPtr->srvSt = (uint8)ISOUDS_RESP;
										
						}
						else if (WrDaSt == (uint8)0x00)
						{
							/* Negative response */
							canSrvDConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

							/* NRC - Security access denied */
							canSrvDConfPtr->srvNegResp = (uint8)ISOUDS_SAD;
						}
						/* if service is invoked due to response pending state */
						else if (WrDaSt == (uint8)0x02)
						{
							/* Negative response */
							canSrvDConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

							/* NRC - Conditions not correct */
							canSrvDConfPtr->srvNegResp = (uint8)ISOUDS_IMLOIF;
						}
						else
						{
							/* Negative response */
							canSrvDConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

							/* NRC - Conditions not correct */
							canSrvDConfPtr->srvNegResp = (uint8)ISOUDS_CNC;
						}
											
					}					
					/* invalid message length */
					
					else
					{
						/* Negative response */
						canSrvDConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

						/* Invalid Message Length Or Invalid Format */
						canSrvDConfPtr->srvNegResp = (uint8)ISOUDS_IMLOIF;
					}
                }
                else
                {
					/* Negative response */
					canSrvDConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

					/* NRC - Request Out Of Range */
					canSrvDConfPtr->srvNegResp = (uint8)ISOUDS_ROOR;
                }
            }
            /* DID not supported for write purpose */
            else
            {
                /* Negative response */
                canSrvDConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

                /* NRC - Request Out Of Range */
                canSrvDConfPtr->srvNegResp = (uint8)ISOUDS_ROOR;
            }
		}
		/* invalid message length */
		else
		{
			/* Negative response */
			canSrvDConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

			/* Invalid Message Length Or Invalid Format */
			canSrvDConfPtr->srvNegResp = (uint8)ISOUDS_IMLOIF;
		}
    }
    else
    {
		/* Negative response */
		canSrvDConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

		/* NRC - Request Out Of Range */
		canSrvDConfPtr->srvNegResp = (uint8)ISOUDS_ROOR;
    }
}

/**************************** Internal Function definitions ***************************************/

/***************************************************************************************************
** Function                 : CanSrv_iWrLookUp
** Description              : Checks whether the DID is configured for Writing
** Parameter recvWrDid      : DID received in the request
** Return value             : TRUE  -> DID configured for writing
                              FALSE -> DID not configured for writing
** Remarks                  : None
***************************************************************************************************/
STATIC FUNC(boolean, CAN_CODE) CanSrv_iWrLookUp (VAR(uint16, AUTOMATIC) recvWrDid)
{
    VAR(boolean, AUTOMATIC) wrDidFound;
    VAR(uint8, AUTOMATIC)   idx;

    /* Initialize to FALSE */
    wrDidFound = FALSE;

    /* Search in the Write configuration taCanSrve whether the DID is configured */
    
    for (idx = (uint8)0; ((idx < ((uint8)CANSRV_WRCONFTABSIZE)) && (wrDidFound != TRUE)); idx++)
    {
        /* Check for a DID match */
        if (CanSrv_cWrConfTab[idx].wrDid == recvWrDid)
        {
            /* DID is configured for writing */
            wrDidFound = TRUE;

            /* Save the index of the corresponding DID */
            CanSrv_iWrTabIdx = idx;
        }
    }
    return (wrDidFound);
}
