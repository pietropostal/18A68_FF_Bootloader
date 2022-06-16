/***************************************************************************************************
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_StrtDiagSess.c
**
** Description  : Start Diagnostic session
**
** -------------------------------------------------------------------------------------------------
**
***************************************************************************************************/

/**************************************** Inclusion files *****************************************/
#include "ISOUDS_StrtDiagSess.h"

/********************** Declaration of local symbol and constants *********************************/

/********************************* Declaration of local macros ************************************/
#define     ISOUDS_STRTDIAGSERLEN       (2)     /* Service Length */
/********************************* Declaration of local types *************************************/

/******************************* Declaration of local variables ***********************************/

/******************************* Declaration of local constants ***********************************/

/****************************** Declaration of exported variables *********************************/

/****************************** Declaration of exported constants *********************************/

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/**************************** Internal functions declarations *************************************/
static uint8 ISOUDS_SwtDfltSess (void);
static uint8 ISOUDS_SwtExtDiagSess (void);
static uint8 ISOUDS_SwtProgSess (ISOUDS_ConfType *ISOUDSConfPtr);

/******************************** Function definitions ********************************************/

/***************************************************************************************************
** Function                 : ISOUDS_StrtDiagSess

** Description              : Sends response to StartDiagnostic session (0x10) service request

** Parameter ISOUDSConfPtr  : Pointer to service configuration structure

** Parameter data           : Data array

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
void ISOUDS_StrtDiagSess (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[])
{
    uint8   newSess;
    uint8   posResp;
    uint16  p2aValue;
    uint8 stSessSwt;

    /* Initialization */
    posResp = (uint8)0;

    /* status of session switching initialized to ISOUDS_FALSE */
    stSessSwt = ISOUDS_FALSE;

    /* If sufficient bytes are received */
    if (ISOUDSConfPtr->srvLen == (uint16)ISOUDS_STRTDIAGSERLEN)
    {
        /* Get the session value */
        newSess = dataBuff[0] & (uint8)0x7F;

        /* Get only the suppressPosRspMsgIndicationBit value */
        /* 1-> implies Do not send positive response */
        posResp = dataBuff[0] & (uint8)0x80;

        /* Check if the requested session is default session */
        if (newSess == (uint8)ISOUDS_DS)
        {
            /* Check Pre-conditions and switch to default session */
            stSessSwt = ISOUDS_SwtDfltSess ();

        }
        /* Check if the requested session is Extended Diagnostic session */
        else if (newSess == (uint8)ISOUDS_EXTDS)
        {
            /* Check Pre-conditions and switch to extended diagnostic session */
            stSessSwt = ISOUDS_SwtExtDiagSess ();

             }

        /* check if the requested session is Programming session */
        else if (newSess == (uint8)ISOUDS_PRGS)
        {
            /* Check Pre-conditions and switch to Programming session */
            stSessSwt = ISOUDS_SwtProgSess (ISOUDSConfPtr);

            //Enrico ISOUDS_ApplFlag=TRUE;

        }
        /* Invalid Session value provided */
        else
        {
            /* Negative response */
            ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

            /* SubFunction not supported */
            ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_SFNS;
        }
    }
    /* Length is less than specified */
    else
    {
        /* Negative response */
        ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

        /* Invalid Message Length Or Invalid Format */
        ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_IMLOIF;
    }

    /* Check if the session switching was successful */
    if (stSessSwt == ISOUDS_TRUE)
    {
        /* Check if positive response is to be sent */
        if (posResp == (uint8)0)
        {
            /* Store the changed session value */
            dataBuff[0] = (uint8)ISOUDS_Sess;

            /* Store the standard P2 Value - resolution 1ms/bit */
            /* MISRA RULE 12.8 VIOLATION: Excessive shift value : the expression evaluates to -
              - 0 for the current value of 50, but if the value is increased beyond 8 bits,  -
              - this MISRA violation will not exist */
            dataBuff[1] = (uint8)(((uint16)ISOUDS_STDP2LIM) >> 8);
            dataBuff[2] = (uint8)ISOUDS_STDP2LIM;

            /* Store the P2* value - resolution 10 ms/bit */
            p2aValue    = (uint16)(((uint32)ISOUDS_NRC78P2MAXLIM) / ((uint8)0x0A)); // P2 Value according UDS
            //p2aValue    = (uint16)(((uint32)ISOUDS_NRC78P2MAXLIM));

            dataBuff[3] = (uint8)(p2aValue >> 8);
            dataBuff[4] = (uint8)p2aValue;

            /* Response length for the current Service ID - including SID */
            ISOUDSConfPtr->srvLen = (uint16)6;

            /* Send positive response */
            ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
        }
        else
        {
            /* Reset the required SrvD parameters and Go To IDLE state */
            ISOUDS_Rst ();
        }
    }
}

/**************************** Internal Function definitions ***************************************/

/***************************************************************************************************
** Function                 : ISOUDS_SwtDfltSess

** Description              : Check for conditions and switch to default session

** Parameter                : None

** Return value             : ISOUDS_TRUE -> Switching session successfull, ISOUDS_FALSE -> Unsuccessful

** Remarks                  : None
***************************************************************************************************/
static uint8 ISOUDS_SwtDfltSess (void)
{
	uint8 retVal;

    /* Check if the current session is default session */
    if (ISOUDS_Sess == (uint8)ISOUDS_DS)
    {
        /* Session switching successful */
        retVal = ISOUDS_TRUE;
    }
    /* current session is extended diagnostic session */
    else
    {
        /* Switch session as per request */
        ISOUDS_Sess = (uint8)ISOUDS_DS;

        /* Session switching successful */
        retVal = ISOUDS_TRUE;
    }

    return (retVal);
}

/***************************************************************************************************
** Function                 : ISOUDS_SwtExtDiagSess

** Description              : Check for conditions and switch to extended diagnostic session

** Parameter                : None

** Return value             : ISOUDS_TRUE -> Switching session successfull, ISOUDS_FALSE -> Unsuccessful

** Remarks                  : None
***************************************************************************************************/
static uint8 ISOUDS_SwtExtDiagSess (void)
{
	uint8 retVal;

    /* Check if the current session is extended diagnostic session */
    if (ISOUDS_Sess == (uint8)ISOUDS_EXTDS)
    {
        /* Reset required parameters during extended diag session transition */

        /* Session switching successful */
        retVal = ISOUDS_TRUE;
    }
    else
    {
        /* Switch session as per request */
        ISOUDS_Sess = (uint8)ISOUDS_EXTDS;

        /* reset the required parameters during extended diag session transition */

        /* Session switching successful */
        retVal = ISOUDS_TRUE;
    }

    return (retVal);
}

/***************************************************************************************************
** Function                 : ISOUDS_SwtProgSess

** Description              : Check for conditions and switch to programming session

** Parameter                : None

** Return value             : ISOUDS_TRUE -> Switching session successfull, ISOUDS_FALSE -> Unsuccessful

** Remarks                  : None
***************************************************************************************************/
static uint8 ISOUDS_SwtProgSess (ISOUDS_ConfType *ISOUDSConfPtr)
{
	uint8 retVal;

    /* Check if the current session is extended diagnostic session */
    if (ISOUDS_Sess == (uint8)ISOUDS_PRGS)
    {
		/* Session switching successful */
		retVal = ISOUDS_TRUE;
    }
	else
	{
		/* Switch session as per request */
		ISOUDS_Sess = (uint8)ISOUDS_PRGS;

		/* reset the required parameters during programming session transition */

		/* Session switching successful */
		retVal = ISOUDS_TRUE;

	}


    return (retVal);
}
