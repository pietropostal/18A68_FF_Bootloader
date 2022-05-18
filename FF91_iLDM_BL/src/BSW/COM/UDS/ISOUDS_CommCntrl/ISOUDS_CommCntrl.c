/*******************************************************************************
**
** -----------------------------------------------------------------------------
** File Name    : ISOUDS_CommCntrl.c
**
** Description  : Communication Control Service
**
** -----------------------------------------------------------------------------
**
*******************************************************************************/

/**************************************** Inclusion files *********************/
#include "ISOUDS_CommCntrl.h"
#include "CanIf.h"

/********************** Declaration of local symbol and constants *************/
#define    ISOUDS_ERXTX         (uint8)0  /* Enable Rx and Tx */
#define    ISOUDS_ERXDTX        (uint8)1  /* Enable Rx and Disable Tx */
#define    ISOUDS_DRXETX        (uint8)2  /* Disable RX and Enable Tx */
#define    ISOUDS_DRXTX         (uint8)3  /* Disable Rx and Tx */

#define    ISOUDS_NCM           (uint8)1  /* Network Comm Messages */
#define    ISOUDS_NWMCM         (uint8)2  /* Netwrok Mgmt Comm Messages */
#define    ISOUDS_NWMCMANCM     (uint8)3  /* Network comm and Mgmt Comm 
										     messages */




#define    ISOUDS_CMMCNTRLSERLEN    (3)   /* Service Length */


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
//#pragma section APPLICATIONMEM
/*******************************************************************************
** Function                 : ISOUDS_CommCntrl

** Description              : Communication Control

** Parameter canSrvDConfPtr : Pointer to service configuration structure

** Parameter dataBuff       : Pointer to service data buffer

** Return value             : None
*******************************************************************************/
void ISOUDS_CommCntrl (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[])
{
    uint8 posResp;
    uint8 ctrlType;
    // uint8 cnc;
    uint8 commTypelownib;
    uint8 commTypehighnib;
	uint8 commType;
    //uint8 req;

    /* Init */


    /* init service state with negative response */
    ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

    /* check if we have received correct message request length */
    if (ISOUDSConfPtr->srvLen == (uint16)ISOUDS_CMMCNTRLSERLEN)
    {
        /* get the control type parameter value */
        ctrlType = dataBuff[0] & (uint8)0x7F;

        /* Get only the suppressPosRspMsgIndicationBit value */
        /* 1-> implies Do not send positive response */
        posResp = dataBuff[0] & (uint8)0x80;

        /* check if control type is valid  */
        if (ctrlType <= ISOUDS_DRXTX)
        {
            /* get the lower nibble value */
            commTypelownib = dataBuff[1] & (uint8)0x03;

            /* get the higher nibble value */
            commTypehighnib = dataBuff[1] & (uint8)0xF0;
			
			commType = commTypelownib + commTypehighnib;

            /****************************************************************

            INSERT CODE TO CHECK IF REQUEST IS VALID & UPDATE THE
            VARIABLE req ACCORDINGLY

            *****************************************************************/
			

				/* Check if request received for Normal Communication messages*/
				if ((commType & ISOUDS_NCM) == ISOUDS_NCM)
				{
					if(ctrlType == ISOUDS_ERXTX)
					{
						/****************************************************************

								INSERT CODE TO STOP COMMUNICATION

						*****************************************************************/
					}
					
					else if(ctrlType == ISOUDS_ERXDTX)
					{
						/****************************************************************

								INSERT CODE TO STOP COMMUNICATION

						*****************************************************************/
					}
					else if(ctrlType == ISOUDS_DRXETX)
					{
						/****************************************************************

							INSERT CODE TO STOP COMMUNICATION

						*****************************************************************/
					}
					
					else /*if(ctrlType == ISOUDS_DRXTX)*/
					{
					/****************************************************************

						INSERT CODE TO STOP COMMUNICATION

				    *****************************************************************/
					}
				}
				else
				{
					/* Do nothing */
				}
				
				/* Check if request received for Network Communication 
				messages*/
				if ((commType & ISOUDS_NWMCM) == ISOUDS_NWMCM)
				{
					if(ctrlType == ISOUDS_ERXTX)
					{
							/* To be defined */
					}
					
					else if(ctrlType == ISOUDS_ERXDTX)
					{
						/* To be defined */
					}
					else if(ctrlType == ISOUDS_DRXETX)
					{
						/* To be defined */					
					}
					
					else /*if(ctrlType == ISOUDS_DRXTX)*/
					{
						/* To be defined */			
					}
				}
				else
				{
					/* Do nothing */
				}
			
				
				/***************************************************************

                INSERT CODE TO CHECK IF ALL CONDITIONS ARE MET & UPDATE THE
                VARIABLE cnc ACCORDINGLY

                ***************************************************************/

                    /* check if positive response is to be sent */
                    if (posResp == (uint8)0)
                    {
                        /* Store the reset type in response buffer */
                        dataBuff[0] = ctrlType;

                        /* Response length for the current Service - including 
						SID */
                        ISOUDSConfPtr->srvLen = (uint16)2;

                        /* Send positive response */
                        ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
                    }
                    else
                    {
                        /* Reset the required UDS parameters and Go To IDLE 
						state */
                        ISOUDS_Rst();
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
