/***************************************************************************************************
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_ReqDwnld.c
**
** Description  : This service checks the Data transfer can be performed or not for flashing the
**                calibration data and software
**
** -------------------------------------------------------------------------------------------------
**
***************************************************************************************************/

/**************************************** Inclusion files *****************************************/
#include "ISOUDS.h"
#include "ISOUDS_ReqDwnld.h"
#include "ISOUDS_TrnsfrDa.h"
#include "FLSHM.h"
#include "FLSHM_Cfg.h"
#include "ISOUDS_SA.h"
/********************** Declaration of local symbol and constants *********************************/

/********************************* Declaration of local macros ************************************/
#define ISOUDS_DAFRMTID         (uint8)0x00         /* dataFormatIdentifier */
#define ISOUDS_ADDRLENFRMTID    (uint8)0x44        /* address and length format identifier */

/********************************* Declaration of local types *************************************/

/******************************* Declaration of local variables ***********************************/
static uint32 flshAddr;
static uint32 flshAddrLen;
static uint32 flshSize;
static uint32 flshSizeLen;
/******************************* Declaration of local constants ***********************************/

/****************************** Declaration of exported variables *********************************/

/****************************** Declaration of exported constants *********************************/

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/**************************** Internal functions declarations *************************************/
static uint8 ISOUDS_ValidateInfo (uint8 data[]);

/******************************** Function definitions ********************************************/

/***************************************************************************************************
** Function                 : ISOUDS_ReqDwnld

** Description              : Checks all requirements related to flash/calibration before starting
                              the Transfer data service

** Parameter ISOUDSConfPtr  : Pointer to service configuration structure

** Parameter data           : Data array

** Return value             : None
***************************************************************************************************/
void ISOUDS_ReqDwnld (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[])
{
    uint8   memAddrSizeLen;
    uint8 validaddr;
    uint8 reqAccpt;
    uint8 dwnldaccpt;    
    

    /* Calculate the length info from addressAndLengthFormatIdentifier */
    memAddrSizeLen = (uint8)((dataBuff[1] & (uint8)0x0F) + ((uint8)(dataBuff[1] >> (uint8)4)));
    
    /* Set srvSt default to Negative response */
    ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

    /* check if ECU is unlocked */
    if ((uint8)ISOUDS_TRUE == ISOUDS_GetSAStLevel(1))
    {
        /* Check if Service request length is valid */
        if ((ISOUDSConfPtr->srvLen > (uint16)3) &&
        (ISOUDSConfPtr->srvLen == (uint16)((uint16)memAddrSizeLen + (uint16)3)))
        {
			/* Get the Size of Address and Length Size. */
			flshAddrLen = dataBuff[1] & 0x0F;
			flshSizeLen = (dataBuff[1] & 0xF0) >> 4;
				
			/* Check if the received dataFormatIdentifier and addressAndLengthFormatIdentifier -
				- are supported */
			if ((dataBuff[0] == ISOUDS_DAFRMTID) && 
				(flshAddrLen != ISOUDS_ADDRLENFRMTID) &&
				(flshSizeLen != ISOUDS_ADDRLENFRMTID))
			{                               
				
				
				/* Code to get flash address and length. */
				flshAddr = (uint32)0x00;
				flshSize = (uint32)0x00;
			
				/* Validate the Address and Length provided. */
				validaddr = ISOUDS_ValidateInfo(&dataBuff[2]);
				
				/* Check if flash address and end address lie within the 
				   application block */
				if (validaddr == (uint8)ISOUDS_TRUE)
				{                                       
					/* Code to get status of download request. */
					dwnldaccpt = ISOUDS_ChkTrnsfrExit();
					
					
					if (dwnldaccpt == (uint8)ISOUDS_TRUE)
					{                                   
						/* Request for Download Service */
					   reqAccpt = ISOUDS_ReqTrnsfrDa(flshAddr, flshSize, 
																  ISOUDS_REQDW);
						   
						/* Check if the request for download is accepted */
						if (reqAccpt == (uint8)ISOUDS_TRUE)
						{
#ifdef FF91
							/* Length format identifier */
							dataBuff[0] = (uint8)0x20;
			
							/*  block length = 3k Bytes = 0xC00 */
							dataBuff[1] = (uint8)0x0C;
							dataBuff[2] = (uint8)0x00;

							/* Response length for the current Service ID */
							ISOUDSConfPtr->srvLen = (uint16)4;
#else
							// Enrico special FF91 handling!

							/* Length format identifier */
							dataBuff[0] = (uint8)0x40;

							/*  block length = 1k+2 Bytes = 0x402 */
							dataBuff[1] = (uint8)0x00;
							dataBuff[2] = (uint8)0x00;
							dataBuff[3] = (uint8)0x04;
							dataBuff[4] = (uint8)0x02;

							/* Response length for the current Service ID */
							ISOUDSConfPtr->srvLen = (uint16)6;
#endif
			
							/* Send positive response */
							ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
							
							/* Set the Boot State. */
							//ISOUDS_SetBootSeqState(ISOUDS_TRANSFERDATA_STATE);
						}
						/* Negative response - Request not accepted */
						else
						{                               
						   /* Conditions Not Correct */
						   ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_CNC;
						}
					}
					else
					{
						/* Download Not Accepted */
						ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_UDNA;
					}
				}
				/* Negative response - Invalid Memory adddress/size */
				else
				{
					/* Request Out of Range */
					ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_ROOR;
				}
				
			}
			else
			{
				/* Negative response */
				/* dataFormatIdentifier/ addressAndLengthFormatIdentifier is not valid */
				/* Request Out of Range */
				ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_ROOR;
			}
        }
        else
        {           
           /* Negative response - Invalid Message Length Or Invalid Format */
           ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_IMLOIF;
        }
    }
    else
    {
        /* Negative response - Security access denied */
        ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_SAD;
    }
}

/**************************** Internal Function definitions ***************************************/

/***************************************************************************************************
** Function                 : ISOUDS_ValidateInfo

** Description              : Extracts and Validates the address and length

** Parameter data           : Data array

** Return value             : (uint8)ISOUDS_TRUE:  Address Validation Success 
**                          : (uint8)ISOUDS_FALSE: Address Validation not Success
***************************************************************************************************/
static uint8 ISOUDS_ValidateInfo (uint8 data[])
{
  uint8 idx;
  volatile uint8 shift;
  volatile uint8 return_val;

  return_val = (uint8)ISOUDS_FALSE; 
  
  /* Extract the Address for databuffer. */
  for(idx = 0; idx < flshAddrLen; idx++)
  {
    shift = ((flshAddrLen - (1U + idx)));
    flshAddr |= (uint32)(((uint32)data[idx] & (uint32)0xFFU) << ((uint32)(8U * shift)));
  }
  
  /* Extract the length for databuffer. */
  for(idx = 0; idx < flshSizeLen; idx++)
  {
    shift = ((flshSizeLen - (1U + idx)));
    flshSize |= (uint32)(((uint32)data[flshAddrLen + idx] & (uint32)0xFFU) << ((uint32)(8U * shift)));
  }
  
   /* Validate the address and length. */
  if(FLSHM_ValidteReqAddress(flshAddr, flshSize) == TRUE)
  {
    return_val = (uint8)ISOUDS_TRUE;
    
    /* Set the Flash Addresss, if its for Bootloader update. */
    
   }
  else
  { 
    /* No Actions Required. */    
  }
  
  return (return_val);
}
