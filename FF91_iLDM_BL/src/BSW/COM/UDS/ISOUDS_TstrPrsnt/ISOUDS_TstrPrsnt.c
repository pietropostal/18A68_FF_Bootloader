/*******************************************************************************
**
** -----------------------------------------------------------------------------
** File Name    : ISOUDS_TstrPrsnt.c
**
** Description  : Tester Present Service
**
** -----------------------------------------------------------------------------
**
*******************************************************************************/

/**************************************** Inclusion files *********************/
#include "ISOUDS_TstrPrsnt.h"
#include "ISOUDS_SA.h"
#include "ISOUDS_TrnsfrDa.h"
#include "FLSHM.h"

/********************** Declaration of local symbol and constants *************/

/********************************* Declaration of local types *****************/
#define     ISOUDS_TSTRPRSNTSERLEN      (2)     /* Service Length */

/******************************* Declaration of local variables ***************/

/* After this time if tester not present it will timeout and switch to default 
   session */
uint32 ISOUDS_SessionTimeoutCntr;

/******************************* Declaration of local constants ***************/

/****************************** Declaration of exported variables *************/

/****************************** Declaration of exported constants *************/

/*******************************************************************************
**                                      FUNCTIONS                              *
*******************************************************************************/

/**************************** Internal functions declarations *****************/

/******************************** Function definitions ************************/

/*******************************************************************************
** Function                 : ISOUDS_TstrPrsnt

** Description              : Sends response to Tester Present(0x3E) service 
							  request

** Parameter canSrvDConfPtr : Pointer to service configuration structure

** Parameter dataBuff       : Data array

** Return value             : None
*******************************************************************************/
void ISOUDS_TstrPrsnt (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[])
{
    uint8 subFunc;
	
    if (ISOUDS_Sess != ISOUDS_DS)
    {
		/* Restart the counter */
    	ISOUDS_SessionTimeoutCntr =  1;
    }
    else
    {
		/* Reset the counter */
		ISOUDS_SessionTimeoutCntr =  0;
    }
	
    /* If sufficient bytes are received */
    if (ISOUDSConfPtr->srvLen == (uint16)ISOUDS_TSTRPRSNTSERLEN)
    {
        /* Get the sub-function parameter */
        subFunc = dataBuff[0] & 0x7F;

        /* Check for supported Sub-function */
        if (subFunc == (uint8)0x00)
        {			
            /* Store the new session value */
            dataBuff[0] = subFunc;

            /* Response length for the current Service ID */
            ISOUDSConfPtr->srvLen = (uint16)2;

            /* Send positive response */
            ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
        }
        /* Sub-Function is not supported */
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
}


/*******************************************************************************
** Function name    : ISOUDS_MonitorTstrPrsnt
**
** Description      : Monitoring Tester Present
**
** Parameter 		: None
**
** Return value     : None
**
** Remarks          : None
*******************************************************************************/
void ISOUDS_MonitorTstrPrsnt(void)
{
	/* local to copy running counter value */     
    /* Check for timer overflow */
    if (ISOUDS_SessionTimeoutCntr > 0)
    {
	    if(ISOUDS_SessionTimeoutCntr >= ISOUDS_TSTRPRSNTSESSIONTIMERMAX)		    
	    {
			ISOUDS_Sess = ISOUDS_DS;
	        /* Clear Timer */
	        ISOUDS_SessionTimeoutCntr = 0;
			
			ISOUDS_Rst();
			
			ISOUDS_SAReset();
			
			ISOUDS_TrnsfrDaExit();
			
			FLSHM_Init();
	    }
	    else
	    {
		    ISOUDS_SessionTimeoutCntr += ISOUDS_PERIOD_SCHED;
	    }
    }
    else
    {
	    /* Do nothing */
    }
}


