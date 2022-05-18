/***************************************************************************************************
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_ECUReset.c
**
** Description  : ECU Reset
**
** -------------------------------------------------------------------------------------------------
**
***************************************************************************************************/

/**************************************** Inclusion files *****************************************/
#include "ISOUDS_ECUReset.h"
#include "ISOUDS_SA.h"

/********************** Declaration of local symbol and constants *********************************/
#define     ISOUDS_HARDRESET        (uint8)1
#define     ISOUDS_KEYOFFONRESET    (uint8)2
#define     ISOUDS_SOFTRESET        (uint8)3
#define     ISOUDS_ECURESETSERLEN   (2)         /* Service Length */

/********************************* Declaration of local macros ************************************/

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
** Function                 : ISOUDS_ECUReset

** Description              : Resets ECU

** Parameter canSrvDConfPtr : Pointer to service configuration structure

** Parameter dataBuff       : Pointer to service data buffer

** Return value             : None
***************************************************************************************************/
void ISOUDS_ECUReset (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[])
{
    uint8 posResp;
    uint8 rstType;
    //uint8 cnc;

    /* init service state with negative response */
    ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

    /* check if we have received correct message request length */
    if (ISOUDSConfPtr->srvLen == (uint16)ISOUDS_ECURESETSERLEN)
    {
        /* get the reset type parameter value */
        rstType = dataBuff[0] & (uint8)0x7F;

        /* Get only the suppressPosRspMsgIndicationBit value */
        /* 1-> implies Do not send positive response */
        posResp = dataBuff[0] & (uint8)0x80;

        /* Check if the reset type is of hardReset */
        if ((rstType == ISOUDS_HARDRESET) || (rstType == ISOUDS_KEYOFFONRESET)||(rstType ==ISOUDS_SOFTRESET))
        {
            /* check if ECU is unlocked */
            if (ISOUDS_TRUE == ISOUDS_GetSAStLevel(1))
            {
                /***************************************************************
                INSERT CODE TO CHECK IF CONDITIONS ARE CORRECT TO RESET ECU &
                UPDATE THE VARIABLE cnc ACCORDINGLY
                ***************************************************************/

                    /* request ECU Reset */
                    ISOUDS_ReqECUReset(rstType);
                    
                    /* Save ECU Reset reason in NVM */
                    
                    /* Switch to Default session */
                    ISOUDS_Sess = (uint8)ISOUDS_DS;

                    /* check if positive response is to be sent */
                    if (posResp == (uint8)0)
                    {
                        /* Store the reset type in response buffer */
                        dataBuff[0] = rstType;

                        /* Response length for the current Service - including SID */
                        ISOUDSConfPtr->srvLen = (uint16)2;

                        /* Send positive response */
                        ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;

                        BootFlag_ECUSt=1;
                    }
                    else
                    {
                        /* Reset the required SrvD parameters and Go To IDLE state */
                        ISOUDS_Rst ();
                    }

            }
            else
            {
                /* Security Access Denied */
                ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_SAD;
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

/**************************** Internal Function definitions ***************************************/
