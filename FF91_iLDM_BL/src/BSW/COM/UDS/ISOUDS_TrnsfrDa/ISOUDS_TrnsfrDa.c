/***************************************************************************************************
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_TrnsfrDa.c
**
** Description  : Transfer Data Service. This service is used to tranfer data between client and
**                server
**
** -------------------------------------------------------------------------------------------------
**
***************************************************************************************************/

/**************************************** Inclusion files *****************************************/
#include "ISOUDS_TrnsfrDa.h"
#include "FLSHM.h"
/********************** Declaration of local symbol and constants *********************************/

/********************************* Declaration of local macros ************************************/

#define     ISOUDS_TRNSFRDASERLEN       (1)      /* Service length */

/* NOTE:REMOVE BELOW MACROS AFTER INTEGRATION WITH FLASH MODULE */
//#define     ISOUDS_PRGSUCC  (uint8)0
//#define     ISOUDS_PRGERR_WRFAIL    (uint8)1

/********************************* Declaration of local types *************************************/

/******************************* Declaration of local variables ***********************************/
/* Transfer data block sequence counter */
static uint8 ISOUDS_DwBlkSeqCntr = 0U;
/* Transfer data block sequence counter for upload */
static uint8 ISOUDS_UpBlkSeqCntr = 0U;
/* Transfer data state */
static uint8 ISOUDS_TrnsfrDaSt = 0U;
/* Memory Size */
static uint32 ISOUDS_MemSize = 0U;
/* Memory start address */
static uint32 ISOUDS_MemStartAddr = 0U;
/* Number of bytes sent in previous response */
static uint16 ISOUDS_PrevLen = 0U;

/******************************* Declaration of local constants ***********************************/

/****************************** Declaration of exported variables *********************************/

/****************************** Declaration of exported constants *********************************/

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/**************************** Internal functions declarations *************************************/

/******************************** Function definitions ********************************************/

/***************************************************************************************************
** Function                 : ISOUDS_TrnsfrDa

** Description              : Sends response to Transfer data service request

** Parameter ISOUDSConfPtr : Pointer to service configuration structure

** Parameter dataBuff       : Data array

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
void ISOUDS_TrnsfrDa (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[])
{
    uint8 flshresultstatus = FLSHM_SUCCESS;
    uint16  length;    
    uint16  idx;
    uint8   *Readptr;   


    
    /* check if the length is valid */
    if (ISOUDSConfPtr->srvLen > (uint16)ISOUDS_TRNSFRDASERLEN)
   {
		if ((ISOUDS_TrnsfrDaSt == ISOUDS_TRIDLE))
		{                
			/* send negative response. Request Sequence Error */
			ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_RSE;
			ISOUDSConfPtr->srvLen = 3;
			/* Negative response */
			ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;
		}
		else
		{
		
			switch (ISOUDS_TrnsfrDaSt)
			{
				case ISOUDS_REQDW:
				case ISOUDS_REQDWTD:
				case ISOUDS_REQTDFNSH:
				{
					/* get the length */
					length = ISOUDSConfPtr->srvLen - (uint16)2u;
					
		
					 /* check whether this function is being called due to response pending */
					 if (ISOUDSConfPtr->srvSt == (uint8)ISOUDS_RESPPEND)
					 {
		
						/****************************************************************
		
						INSERT CODE TO CHECK IF FLASH WAS SUCCESS &
						UPDATE THE VARIABLE flshacc ACCORDINGLY
		
						*****************************************************************/
						flshresultstatus = FLSHM_GetCMDStatus();
						/* if previous flash is success */
						if ((FLSHM_SUCCESS == flshresultstatus))
						{

#if 0 // Enrico removed, this was wwrong..
							/* update the address */
							ISOUDS_MemStartAddr += (uint32)length;

							// Enrico Test
							if( ISOUDS_MemStartAddr > 0x8000)
								ISOUDS_MemStartAddr = ISOUDS_MemStartAddr;
		
							/* decrement the number of bytes written */
							// Enrico fixed overflow
							if( ISOUDS_MemSize >= length )
								ISOUDS_MemSize -= (uint32)length;
							else
								ISOUDS_MemSize = 0;
#endif
		
							/* send successful download block sequence counter*/
							dataBuff[0] = ISOUDS_DwBlkSeqCntr;
		
							/* increment the download block sequence counter */
							ISOUDS_DwBlkSeqCntr += (uint8)1;
		
							if (ISOUDS_MemSize == (uint32)0)
							{
								/* change the state transfer finish */
								ISOUDS_TrnsfrDaSt = ISOUDS_REQTDFNSH;
							   
								/* Set the Boot State. */
								ISOUDS_SetBootSeqState(ISOUDS_TRANSFEREXIT_STATE);
							}
							else if(ISOUDS_MemSize<length)
							{
								ISOUDS_MemSize = length; /*Padding extra bytes for completing a block*/
							}

		
							/* Response length for the current Service - including SID */
							ISOUDSConfPtr->srvLen = (uint16)2;
		
							/* Send positive response */
							ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
						}
						else if((FLSHM_PROGFAILED == flshresultstatus) ||
									   (FLSHM_WRONGADDRESS == flshresultstatus))
						{
							ISOUDS_TrnsfrDaExit();
				
							/* send negative response. General Programming Failure */
							ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_GPF;
							ISOUDSConfPtr->srvLen = 3;
							/* Negative response */
							ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;
						}
						else
						{
							/* set status to Pending. */
							ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_RCRRP;
	  
							/* wait in Response pending */
							ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPPEND;
						}
					 }
					 else
					 {
						/* check download sequence counter with the requested sequence counter*/
						if ((ISOUDS_TrnsfrDaSt != ISOUDS_REQTDFNSH) && (ISOUDS_DwBlkSeqCntr == dataBuff[(uint8)0]))
						{
							/* check if we have received more bytes than the required no. of bytes */
							if ((uint32)length <= ISOUDS_MemSize)
							{
		
								/****************************************************************
		
								INSERT CODE TO START FLASHING FROM THE ADDRESS ISOUDS_MemStartAddr
								WITH DATA BEING POINTED BY dataBuff[1] & SIZE INDICATED BY length &
								UPDATE THE VARIABLE flshacc ACCORDINGLY
		
								*****************************************************************/

								/* if flash request is not accepted*/
								if( ISOUDS_DwBlkSeqCntr == 2 )
									__asm("nop");

								flshresultstatus = FLSHM_WritePacketReq(ISOUDS_DwBlkSeqCntr, &dataBuff[(uint8)1],length);
								if (FLSHM_SUCCESS != flshresultstatus)
								{
									/* Exit transfer data */
									ISOUDS_TrnsfrDaExit();
									
									/* send negative response. General Programming Failure */
									ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_GPF;
									ISOUDSConfPtr->srvLen = 3;
									/* Negative response */
									ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;
								}
								else
								{
									/* update state machine to Request download transfer data */
									ISOUDS_TrnsfrDaSt = ISOUDS_REQDWTD;
									
									/* Response pending */
									ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_RCRRP;
									ISOUDSConfPtr->srvLen = 3;
									/* Negative response */
									ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;
								}
							}
							else
							{
								/* send negative response. Transfer Data Suspended */
								ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_TDS;
								ISOUDSConfPtr->srvLen = 3;
								/* Negative response */
								ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;
							}
						}
						/* check download sequence counter with previous requested sequence counter*/
						else if ((ISOUDS_TrnsfrDaSt != ISOUDS_REQDW)
								&& ((ISOUDS_DwBlkSeqCntr - (uint8)0x01) == dataBuff[0]))
						{
							/* send successful download block sequence counter*/
							dataBuff[0] = ISOUDS_DwBlkSeqCntr - (uint8)0x01;
		
							/* Response length for the current Service - including SID */
							ISOUDSConfPtr->srvLen = (uint16)2;
		
							/* Send positive response */
							ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
						}
						else if (ISOUDS_TrnsfrDaSt == ISOUDS_REQTDFNSH)
						{
							/* Request Sequence Error. All the bytes have been read */
							ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_RSE;
							ISOUDSConfPtr->srvLen = 3;
							/* Negative response */
							ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;
						}
						else
						{
							/* send negative response. Wrong Block Sequence Counter */
							ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_WBSC;
							ISOUDSConfPtr->srvLen = 3;
							/* Negative response */
							ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;
						}
					}
				}/* end of case ISOUDS_REQDW */
				break;
		
				case ISOUDS_REQUP:
				case ISOUDS_REQUPTD:
				case ISOUDS_REQTDUPFNSH:
				{
					/* check upload sequence counter with the requested sequence counter*/
					if ((ISOUDS_TrnsfrDaSt != ISOUDS_REQTDUPFNSH) && (ISOUDS_UpBlkSeqCntr == dataBuff[(uint8)0]))
					{
						/* check number of bytes to be sent */
						if (ISOUDS_MemSize > (uint32)((uint32)ISOUDS_BUFFSIZE - (uint8)2))
						{
							/* read only upto what can be handled */
							length = (uint16)((uint16)ISOUDS_BUFFSIZE - (uint8)2);
						}
						else
						{
							/* read remaining bytes */
							length = (uint16)ISOUDS_MemSize;
						}
		
						/* get the address */
						Readptr = (uint8*)ISOUDS_MemStartAddr;
		
						for (idx = (uint16)0; idx < length; idx++)
						{
							/* Read data into array */
							dataBuff[idx + (uint8)1] = *((uint8*)&Readptr[idx]);
						}
		
						/* decrement the number of bytes read */

						// Enrico fixed overflow
						if( ISOUDS_MemSize >= length )
							ISOUDS_MemSize -= (uint32)length;
						else
							ISOUDS_MemSize = 0;
		
						/* increment the address */
						ISOUDS_MemStartAddr += (uint32)length;
		
						/* Store number of bytes transmitted in this response, if we get
						request for transmitting the same data due to timeout in application
						layer while receiving response.Refer ISO 14229 */
						ISOUDS_PrevLen = (uint16)length;
		
						/* send successful upload block sequence counter*/
						dataBuff[0] = ISOUDS_UpBlkSeqCntr;
		
						/* increment upload sequence counter */
						ISOUDS_UpBlkSeqCntr += (uint8)1;
		
						if (ISOUDS_MemSize == (uint32)0x0)
						{
							/* update state machine to Request upload transfer data finish */
							ISOUDS_TrnsfrDaSt = ISOUDS_REQTDUPFNSH;
							
							/* Set the Boot State. */
							//ISOUDS_SetBootSeqState(ISOUDS_TRANSFEREXIT_STATE);
						}
						else
						{
							/* update state machine to Request upload transfer data */
							ISOUDS_TrnsfrDaSt = ISOUDS_REQUPTD;
						}
		
						/* Response length for the current Service - including SID and sequence counter */
						ISOUDSConfPtr->srvLen = (uint16)(length + (uint16)2);
		
						/* Positive response response */
						ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
					}
					/* check upload sequence counter with previous requested sequence counter*/
					else if ((ISOUDS_TrnsfrDaSt != ISOUDS_REQUP)
							&& ((ISOUDS_UpBlkSeqCntr - (uint8)0x01) == dataBuff[0]))
					{
						/* NOTE: The server responds with transfer data positively,
						but application might not receive the data. In such a scenario, application
						times out and re requests the data. In such case we reach this else if
						condition. since the data is already available in UDS buffer, we can simply
						set the length (previously transmitted number of bytes) and transmit the
						data. instead of re requesting the data, if application request for some
						other service, then UDS buffer will not hold data w.r.t. upload service. In
						such a scenario, APPLICATION has to re read the data with address set to
						(ISOUDS_MemStartAddr - (uint32)ISOUDS_PrevLen) and number of bytes to
						read should be set to ISOUDS_PrevLen.*/
		
						/* send successful upload block sequence counter*/
						dataBuff[0] = ISOUDS_UpBlkSeqCntr - (uint8)0x01;
		
						/* Response length for the current Service - including SID */
						ISOUDSConfPtr->srvLen = (uint16)(ISOUDS_PrevLen + (uint16)2);
		
						/* Send positive response */
						ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
					}
					else if (ISOUDS_TrnsfrDaSt == ISOUDS_REQTDUPFNSH)
					{
						/* Request Sequence Error. All the bytes have been read */
						ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_RSE;
						ISOUDSConfPtr->srvLen = 3;
						/* Negative response */
						ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;
					}
					else
					{
						/* Wrong Block Sequence Counter */
						ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_WBSC;
						ISOUDSConfPtr->srvLen = 3;
						/* Negative response */
						ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;
					}
				}/* end of case ISOUDS_REQUP */
				break;
		
				default:
				{
					/* we shouldn't reach here */
					ISOUDS_TrnsfrDaSt = ISOUDS_TRIDLE;
					
				}
			}/* end of switch */
		}
    }
    else
    {
        /* Invalid Message Length Or Invalid Format */
        ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_IMLOIF;
        ISOUDSConfPtr->srvLen = 3;
        /* Negative response */
        ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;
    }
}

/***************************************************************************************************
** Function                 : ISOUDS_TrnsfrDaExit

** Description              : Resets Transfer data service state

** Parameters               : None

** Return value             : None
***************************************************************************************************/
void ISOUDS_TrnsfrDaExit (void)
{
    /* change the state to idle */
    ISOUDS_TrnsfrDaSt = ISOUDS_TRIDLE;

    /* Reset the Memory start address */
    ISOUDS_MemStartAddr = (uint32)0x00;

    /* Reset the Memory size */
    ISOUDS_MemSize =  (uint32)0x00;

    /* Reset download block sequence counter */
    ISOUDS_DwBlkSeqCntr = (uint8)0;

    /* Reset upload block sequence counter */
    ISOUDS_UpBlkSeqCntr = (uint8)0;

    /* Number of bytes sent in previous response */
    ISOUDS_PrevLen = (uint16)0;
}

/***************************************************************************************************
** Function                 : ISOUDS_ReqTrnsfrDa

** Description              : Request for Transfer data service

** Parameter addr           : Address form where the download/upload has to start

** Parameter size           : Number of bytes to be downloaded/uploaded

** Parameter servreq        : Service Request- Request Download or Request Upload

** Return value             : ISOUDS_TRUE : Success ISOUDS_FALSE: Download/Upload in progress
***************************************************************************************************/
uint8 ISOUDS_ReqTrnsfrDa (uint32 addr, uint32 size, uint8 servreq)
{
    uint8 return_val;

    /* init return value */
    //return_val = ISOUDS_FALSE;

    if (((ISOUDS_TrnsfrDaSt == ISOUDS_REQDWTD) || (ISOUDS_TrnsfrDaSt == ISOUDS_REQTDFNSH)) ||
        ((ISOUDS_TrnsfrDaSt == ISOUDS_REQUPTD) || (ISOUDS_TrnsfrDaSt == ISOUDS_REQTDUPFNSH)))
    {
        /* transfer data for download/upload is in progress */
        return_val = ISOUDS_FALSE;
    }
    else
    {
        if (ISOUDS_REQDW == servreq)
        {
            /* change the state to request download */
            ISOUDS_TrnsfrDaSt = ISOUDS_REQDW;

            /* initializes download sequence counter */
            ISOUDS_DwBlkSeqCntr = (uint8)1;

            /* reset upload sequence counter */
            ISOUDS_UpBlkSeqCntr = (uint8)0;
        }
        else if (ISOUDS_REQUP == servreq)
        {
            /* change the state to request upload */
            ISOUDS_TrnsfrDaSt = ISOUDS_REQUP;

            /* initialise download sequence counter */
            ISOUDS_UpBlkSeqCntr = (uint8)1;

            /* reset download sequence counter */
            ISOUDS_DwBlkSeqCntr = (uint8)0;
        }
        else
        {
            /* we shouldn't reach here. Change state to idle */
            ISOUDS_TrnsfrDaSt = ISOUDS_TRIDLE;
        }


        /* get the address from where the data needs to be read/written */
        ISOUDS_MemStartAddr = addr;

        /* get the number of bytes to be read/written */
        ISOUDS_MemSize = size;
        
        FLSHM_ProgramReq(addr,size); // sets the Pre programming parameters , copies the Flash routines into RAM
        
        /* Number of bytes sent in previous response */
        ISOUDS_PrevLen = (uint16)0;

        /* transfer data for Upload/Download accepted */
        return_val = ISOUDS_TRUE;
    }

    return (return_val);
}

/***************************************************************************************************
** Function                 : ISOUDS_ChkTrnsfrExit

** Description              : Checks for Transfer data service exit

** Parameters               : None

** Return value             : ISOUDS_TRUE: exit transfer data/ ISOUDS_FALSE: conditions not correct to exit
***************************************************************************************************/
uint8 ISOUDS_ChkTrnsfrExit (void)
{
    uint8 return_val;

    /* check if download/upload is active */
    if (((ISOUDS_TrnsfrDaSt == ISOUDS_TRIDLE) && (ISOUDS_DwBlkSeqCntr == (uint8)0)) &&
         (ISOUDS_UpBlkSeqCntr == (uint8)0))
    {
        return_val = ISOUDS_TRUE;
    }
    else
    {
        return_val = ISOUDS_FALSE; 
    }

    return (return_val);
}
