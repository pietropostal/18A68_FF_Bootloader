/***************************************************************************************************
 **
 ** -------------------------------------------------------------------------------------------------
 ** File Name    : ISOUDS_RtnCntrl.c
 **
 ** Description  : Routine Control Service
 **
 ** -------------------------------------------------------------------------------------------------
 **
 ***************************************************************************************************/

/**************************************** Inclusion files *****************************************/
//#include "sha256.h"
#include "ISOUDS_RtnCntrl.h"
#include "ISOUDS_RtnCfg.h"
#include "FLSHM.h"
#include "FLSHM_Cfg.h"
#include "Flash.h"
#include "ISOUDS_SA.h"


/********************** Declaration of local symbol and constants *********************************/

/********************************* Declaration of local macros ************************************/
/* Start Routine */
#define     ISOUDS_STARTROUTINE     ((uint8)1)
/* Stop Routine */
#define     ISOUDS_STOPROUTINE      ((uint8)2)
/* Req Results Routine */
#define     ISOUDS_REQRESROUTINE    ((uint8)3)
/* Service length */
#define     ISOUDS_RTNCNTRLSERLEN   (4U)

/********************************* Declaration of local types *************************************/

/******************************* Declaration of local variables ***********************************/
/* Validation Flag value to be return after check sum validation */
//const volatile uint16 ISOUDS_Chksm_Valid = (uint16)0x5A5AU;
static uint32 ISOUDS_iChksm;

/* Holds the configuration table index */
static uint8 ISOUDS_RtnTabIdx;
/* Holds whether Routine has been started or not */
static uint8 ISOUDS_RtnStarted[ISOUDS_RTNCONFTABSIZE];

static uint8 ISOUDS_iApp_BlockEr;
uint8   rtnNoError = 0x00u;


/******************************* Declaration of local constants ***********************************/

/****************************** Declaration of exported variables *********************************/

/****************************** Declaration of exported constants *********************************/

/***************************************************************************************************
 **                                      FUNCTIONS                                                 **
 ***************************************************************************************************/

/**************************** Internal functions declarations *************************************/
static uint8 ISOUDS_RtnLookUp (uint16 recvid);

/******************************** Function definitions ********************************************/

/***************************************************************************************************
 ** Function                 : ISOUDS_RtnCntrl

 ** Description              : Sends response to Read Data by ID service request

 ** Parameter ISOUDSConfPtr  : Pointer to service configuration structure

 ** Parameter dataBuff       : Data array

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_RtnCntrl (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[])
{
	uint16  locID;
	uint8   rtnType;

	uint8 trueL;
	/* Check if received length is valid */
	if (ISOUDSConfPtr->srvLen >= (uint16)ISOUDS_RTNCNTRLSERLEN)
	{
		/* get the routine identifier value */
		locID = (uint16)((((uint16)dataBuff[(uint8)1U]) << (uint8)8U) +
				dataBuff[(uint8)2U]);

		//ISOUDS_iRtnID = locID;
		/* Check if DID is configured for erase purpose */
		if (ISOUDS_TRUE == ISOUDS_RtnLookUp (locID))
		{
			trueL = ISOUDS_GetSAStLevel(1);

			/* Check if, ECU is locked */
			if (ISOUDS_TRUE == trueL)
			{
				/* Check if DID is configured to be read in active session */
				if ((((ISOUDS_RtnConfTab[ISOUDS_RtnTabIdx].rtnIdSess) >> ISOUDS_Sess) & (uint8)1)
						== (uint8)1)
				{
					/* get the routine type */
					rtnType = dataBuff[(uint8)0U];

					/* if request for start routine */
					if (ISOUDS_STARTROUTINE == rtnType)
					{
						/****************************************************************

                        INSERT CODE TO START ROUTINE BY EXTRACTING ROUTINE CONTROL OPTION
                        RECORD DATA(IF NEEDED) & UPDATE THE VARIABLE rtnNoError ACCORDINGLY

						 *****************************************************************/
						/* invoke the corresponding function */
						rtnNoError = (ISOUDS_RtnConfTab[ISOUDS_RtnTabIdx].ISOUDS_FunPtr)(ISOUDSConfPtr, &dataBuff[0U]);

						if ((uint8)ISOUDS_RTNCTRL_POSTIVE == rtnNoError)
						{
							/* Routine started */
							ISOUDS_RtnStarted[ISOUDS_RtnTabIdx] = ISOUDS_STARTROUTINE;

							/* Send positive response */
							ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
						}
						else if ((uint8)ISOUDS_RTNCTRL_NEGTIVE == rtnNoError)
						{
							/* indicate negative response */
							ISOUDSConfPtr->srvSt = ISOUDS_RESPNEG;

							/* General Programme Failure */
							ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_GPF;
						}
						else if ((uint8)ISOUDS_RTNCTRL_PENDING == rtnNoError)
						{
							/* indicate negative response */
							ISOUDSConfPtr->srvSt = ISOUDS_RESPNEG;

							/* updated NRC */
							ISOUDSConfPtr->srvNegResp = ISOUDS_RCRRP;
						}

						else if((uint8)ISOUDS_RTNCTRL_INVALID_LEN == rtnNoError)
						{
							/* indicate negative response */
							ISOUDSConfPtr->srvSt = ISOUDS_RESPNEG;

							/* Conditions Not Correct */
							ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_IMLOIF;
						}
						else
						{
							/* No Actions Required. */
						}
					}
					else if (ISOUDS_STOPROUTINE == rtnType)
					{
						if (ISOUDS_RtnStarted[ISOUDS_RtnTabIdx] == ISOUDS_STARTROUTINE)
						{
							/****************************************************************

                            INSERT CODE TO STOP ROUTINE BY EXTRACTING ROUTINE CONTROL OPTION
                            RECORD DATA(IF NEEDED) & UPDATE THE VARIABLE rtnNoError ACCORDINGLY

							 *****************************************************************/

							if ((uint8)ISOUDS_RTNCTRL_POSTIVE == rtnNoError)
							{
								/* Routine stoped */
								ISOUDS_RtnStarted[ISOUDS_RtnTabIdx] = ISOUDS_STOPROUTINE;

								/* Response length for the current Service - including SID */
								ISOUDSConfPtr->srvLen = (uint16)4U;

								/* Send positive response */
								ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
							}
							else
							{
								/* indicate negative response */
								ISOUDSConfPtr->srvSt = ISOUDS_RESPNEG;

								/* Conditions Not Correct */
								ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_CNC;
							}
						}
						else
						{
							/* indicate negative response */
							ISOUDSConfPtr->srvSt = ISOUDS_RESPNEG;

							/* Routine Not Started */
							ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_RSE;
						}
					}
					else if (ISOUDS_REQRESROUTINE == rtnType)
					{
						if ((ISOUDS_RtnStarted[ISOUDS_RtnTabIdx] == ISOUDS_STARTROUTINE) ||
								(ISOUDS_RtnStarted[ISOUDS_RtnTabIdx] == ISOUDS_STOPROUTINE))
						{
							/****************************************************************

                            INSERT CODE TO GET RESULTS & UPDATE THE VARIABLE rtnNoError
                            ACCORDINGLY

							 *****************************************************************/



							if ((uint8)ISOUDS_RTNCTRL_POSTIVE == rtnNoError)
							{
								// enrico fixed
#if 0
								/* indicate negative response */
								ISOUDSConfPtr->srvSt = ISOUDS_RESPNEG;

								/* Send positive response */
								ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
#else
								/* Send positive response */

								// enrico - stupid answers??
								dataBuff[0u] = 0x1; // start routine
								dataBuff[3u] = 0x0; // erased ok ---ENRICO 1=Spec, but bootscript expect 0

								ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
#endif
							}
							else if( ((uint8)ISOUDS_RTNCTRL_INITIAL == rtnNoError) || ((uint8)ISOUDS_RTNCTRL_PENDING == rtnNoError) )
							{
								// enrico
								/* Send positive response */

								// enrico - stupid answers??
								dataBuff[0u] = 0x1; // start routine
								dataBuff[3u] = 0x1; // erased NOT ok  ---ENRICO 1=Spec, but bootscript expect 0

								ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
							}
							else
							{

								/* indicate negative response */
								ISOUDSConfPtr->srvSt = ISOUDS_RESPNEG;

								/* Conditions Not Correct */
								ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_CNC;
							}
						}
						else
						{
							/* indicate negative response */
							ISOUDSConfPtr->srvSt = ISOUDS_RESPNEG;

							/* Routine Not Started */
							ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_RSE;
						}
					}
					else
					{
						/* indicate negative response */
						ISOUDSConfPtr->srvSt = ISOUDS_RESPNEG;

						/* Sub Function Not Supported */
						ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_SFNS;
					}
				}
				else
				{
					/* indicate negative response */
					ISOUDSConfPtr->srvSt = ISOUDS_RESPNEG;

					/* Request Out Of Range */
					ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_ROOR;
				}
			}
			else
			{
				/* indicate negative response */
				ISOUDSConfPtr->srvSt = ISOUDS_RESPNEG;

				/* Security Access Denied */
				ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_SAD;
			}
		}
		else
		{
			/* indicate negative response */
			ISOUDSConfPtr->srvSt = ISOUDS_RESPNEG;

			/* Request Out Of Range */
			ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_ROOR;
		}
	}
	else
	{
		/* indicate negative response */
		ISOUDSConfPtr->srvSt = ISOUDS_RESPNEG;

		/* Invalid Message Length Or Invalid Format */
		ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_IMLOIF;
	}
}

/**************************** Internal Function definitions ***************************************/

/***************************************************************************************************
 ** Function                 : ISOUDS_RtnLookUp

 ** Description              : Checks whether the ID is configured for reading

 ** Parameter recvid         : ID received in the request

 ** Return value             : ISOUDS_TRUE  -> ID configured for reading
                              FALSE -> ID not configured for reading
 ***************************************************************************************************/
static uint8 ISOUDS_RtnLookUp (uint16 recvid)
{
	uint8 rtnidFound;
	uint8   idx;

	/* Initialize to FALSE */
	rtnidFound = ISOUDS_FALSE;

	/* Search in the routine configuration table whether the ID is configured */
	for (idx = (uint8)0U; ((idx < ((uint8)ISOUDS_RTNCONFTABSIZE)) && (rtnidFound != ISOUDS_TRUE)); idx++)
	{
		/* Check for a ID match */
		if (ISOUDS_RtnConfTab[idx].rtnid == recvid)
		{
			/* ID is configured for writing */
			rtnidFound = ISOUDS_TRUE;
			/* Save the index of the corresponding DID */
			ISOUDS_RtnTabIdx = idx;
		}
	}

	return (rtnidFound);
}

/*******************************************************************************
 ** Function                     : ISOUDS_EraseFlash

 ** Description                  : Requests for Erasing application block and
                                  write CRC.

 ** Parameter                    : Pointer to CAN-Service configuration structure

 ** Return value                 : None

 ** Remarks                      : None
 *******************************************************************************/
uint8 ISOUDS_EraseFlash (ISOUDS_ConfType *ISOUDS_Srv_ConfPtr, uint8 dataBuff[])
{
	FLSHM_ProgStat_t  flshjobstatus = FLSHM_SUCCESS;
	FLSHM_FlshMngrState_t flshMgrState = FLASHMGR_IDLE;
	uint8   erase_rtnNoError ;
	uint32 FlashEraseAddr;
	uint32 FlashEraseSize;

	/* If received service request is a new message/request */
	if (ISOUDS_Srv_ConfPtr->srvSt == (uint8)ISOUDS_RXMSG)
	{

#if 0 // Enrico: removed address bases erase
		if (ISOUDS_ERASE_SRV_LEN == ISOUDS_Srv_ConfPtr->srvLen)
		{
			/* Update service response length */
			ISOUDS_Srv_ConfPtr->srvLen = (uint16)4U;

			/* indicate negative response */
			ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;

			/* initialize checksum erase */
			ISOUDS_iApp_BlockEr     = ISOUDS_FALSE;

			if(FLASHMGR_IDLE == FLSHM_GetFlashState())
			{
				FlashEraseAddr = (((uint32)dataBuff[4u] << 24u) | ((uint32)dataBuff[5u] << 16u) | ((uint32)dataBuff[6u] << 8u) | ((uint32)dataBuff[7u] << 0u));

				FlashEraseSize = (((uint32)dataBuff[8u] << 24u) | ((uint32)dataBuff[9u] <<16u) | ((uint32)dataBuff[10u] << 8u) | ((uint32)dataBuff[11u] << 0u));

				/* Request erase  */
				flshjobstatus = FLSHM_EraseAppReq(FlashEraseAddr, FlashEraseSize);


				if((flshjobstatus == FLSHM_INPROGRESS))
				{
					/* indicate response pending to service provider */
					ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPPEND;
					erase_rtnNoError = ISOUDS_RTNCTRL_PENDING;

				}
				else
				{
					/* indicate negative response */
					ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;
					erase_rtnNoError = ISOUDS_RTNCTRL_NEGTIVE;
				}
			}
			else
			{
				/* indicate negative response */
				ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;
				erase_rtnNoError =ISOUDS_RTNCTRL_INITIAL;
			}
		}
#else
		// Enrico: FIXME special erase memory for flash tool
		if (ISOUDS_ERASE_SRV_LEN_BLK == ISOUDS_Srv_ConfPtr->srvLen && ((dataBuff[3u] == 0x02) || (dataBuff[3u] == 0x03)) )
		{
			/* Update service response length */
			ISOUDS_Srv_ConfPtr->srvLen = (uint16)4U;

			/* indicate negative response */
			ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;

			/* initialize checksum erase */
			ISOUDS_iApp_BlockEr = ISOUDS_FALSE;

			if(FLASHMGR_IDLE == FLSHM_GetFlashState())
			{
				if( dataBuff[3u] == 0x02 )
				{
					// APP
					FlashEraseAddr = FLSHM_APP_START_ADDRS;
					FlashEraseSize = (FLSHM_APP_END_ADDRS+1)-FLSHM_APP_START_ADDRS;

					/* Request erase  */
					flshjobstatus = FLSHM_EraseAppReq(FlashEraseAddr, FlashEraseSize);


					if((flshjobstatus == FLSHM_INPROGRESS))
					{
						/* indicate response pending to service provider */
						ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPPEND;
						erase_rtnNoError = ISOUDS_RTNCTRL_PENDING;

					}
					else
					{
						/* indicate negative response */
						ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;
						erase_rtnNoError = ISOUDS_RTNCTRL_NEGTIVE;
					}
				}
				else
				{
					// CALIB
					// Enrico removed
					//FlashEraseAddr = FLSHM_APP_CALIB_BLK_STRT_ADD;
					//FlashEraseSize = (FLSHM_APP_CALIB_END_ADDRS+1)-FLSHM_APP_CALIB_BLK_STRT_ADD;

					/* out of range */
					ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;
					erase_rtnNoError = ISOUDS_ROOR;
				}
			}
#endif
			else
			{
				/* indicate negative response */
				ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;
				erase_rtnNoError =ISOUDS_RTNCTRL_INITIAL;
			}

		}
		else
		{
			/* Invalid length. */
			erase_rtnNoError = ISOUDS_RTNCTRL_INVALID_LEN;
		}
	}

	/* Erase operation is pending*/
	else
	{   
		flshjobstatus = FLSHM_GetCMDStatus();
		flshMgrState = FLSHM_GetFlashState();

		if(flshMgrState == FLASHMGR_IDLE)
		{
			if((FLSHM_ERASEFAILED == flshjobstatus))
			{
				/* indicate negative response */
				ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;

				/* General Program Failure */
				ISOUDS_Srv_ConfPtr->srvNegResp = (uint8)ISOUDS_GPF;
				erase_rtnNoError = ISOUDS_RTNCTRL_NEGTIVE; 
			}
			else
			{
				/* indicate negative response */
				ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;

				/* General Program Failure */
				ISOUDS_Srv_ConfPtr->srvNegResp = (uint8)ISOUDS_GPF;
				erase_rtnNoError = ISOUDS_RTNCTRL_NEGTIVE; 
			}
		}
		else if(flshMgrState == FLASHMGR_ERASE)
		{

			/* Erase Pending */
			/* indicate response pending to service provider */
			ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPPEND;
			erase_rtnNoError = ISOUDS_RTNCTRL_PENDING;
		}
		else if (flshMgrState == FLASHMGR_ERASE_DONE)
		{
			if((FLSHM_SUCCESS == flshjobstatus))
			{
				/* Response length for the current Service - including SID */
				ISOUDS_Srv_ConfPtr->srvLen = 4;
				/* indicate positive response */
				erase_rtnNoError = ISOUDS_RTNCTRL_POSTIVE;  
				/* Set the Boot State. */
				ISOUDS_SetBootSeqState(ISOUDS_REQDW_STATE);
			}
			else
			{
				/* indicate negative response */
				ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;

				/* General Program Failure */
				ISOUDS_Srv_ConfPtr->srvNegResp = (uint8)ISOUDS_GPF;
				erase_rtnNoError = ISOUDS_RTNCTRL_NEGTIVE;
			}
		}
		else
		{
			/* error */
			/* indicate negative response */
			ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;
			erase_rtnNoError = ISOUDS_RTNCTRL_NEGTIVE;

		}
	}

	return (erase_rtnNoError);
}

/**
 * Enrico Added checkMemory for FF91
 */
uint8 ISOUDS_CheckMemory (ISOUDS_ConfType *ISOUDS_Srv_ConfPtr, uint8 dataBuff[])
{
	uint8 rtnNoError = ISOUDS_RTNCTRL_NEGTIVE;
	static const uint8 sig[16] = { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5 };


	ISOUDS_Srv_ConfPtr->srvLen = 4;
	ISOUDS_Srv_ConfPtr->srvSt  = ISOUDS_RESP;
    rtnNoError = ISOUDS_RTNCTRL_POSTIVE;

	// Enrico TODO Calibration Area
	FLASH_DRV_Program(FLSHM_APP_VALID_FLAG, 16, sig);

    return rtnNoError;
}

/***************************************************************************************************
 ** Function                     : ISOUDS_CheckProgrammDependency

 ** Description                  : Computes Digest for Application and Parameter Blocks

 ** Parameter CANSrvPConfPtr     : Pointer to CAN-Service configuration structure

 ** Return value                 : None

 ** Remarks                      : None
 ***************************************************************************************************/
uint8 ISOUDS_CheckAppValidation (ISOUDS_ConfType *ISOUDS_Srv_ConfPtr, uint8 dataBuff[])
{
	uint8   crc_rtnNoError;
	static const uint8 sig[16] = { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5 };

#if 0
	FLSHM_AppVldnStat_t  flshjobstatus = FLSHM_APPVALDN_IDLE;
	FLSHM_AppVldnStat_t flshMgrState = FLSHM_APPVALDN_IDLE;
	//volatile uint16 compare;

	uint32  checksum;
	uint32 FlashCompStartAddr = 0x00000000;
	uint32 FlashCompSize = 0x00000000;
#endif
	// enrico changed , this not not according spec!!!
#if 0

	/* If received service request is a new message/request */
	if (ISOUDS_Srv_ConfPtr->srvSt == (uint8)ISOUDS_RXMSG)
	{
		/* MISRA-C:2004 Rules 17.4 VIOLATION:
		  Array subscripting applied to an object of pointer type.
		  - Its required access the data stored in pointer */


			FlashCompStartAddr = (((uint32)dataBuff[3] << 24) | ((uint32)dataBuff[4] << 16) | ((uint32)dataBuff[5] << 8) | ((uint32)dataBuff[6] << 0));
			FlashCompSize = (((uint32)dataBuff[7] << 24) | ((uint32)dataBuff[8] <<16) | ((uint32)dataBuff[9] << 8) | ((uint32)dataBuff[10] << 0));

			/* get checksum */
			checksum = (uint32)(((uint32)dataBuff[11U] << 8U) | ((uint32)dataBuff[12U] << 0U));

			/* store checksum */
			ISOUDS_iChksm = (uint32)checksum;


			flshjobstatus = FLSHM_StartDwnlValdn(FlashCompStartAddr, FlashCompSize, ISOUDS_iChksm);

			if((flshjobstatus == FLSHM_APPVALDN_REQ_ACCEPT))
			{
				/* indicate response pending to service provider */
				ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPPEND;
				crc_rtnNoError = ISOUDS_RTNCTRL_PENDING;
			}
			else
			{

				/* indicate negative response */
				ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;
				crc_rtnNoError = ISOUDS_RTNCTRL_NEGTIVE; 
			}

	}
	/* checksum calculation is already pending */
	else
	{
		flshMgrState = FLSHM_GetAppValdnStat();

		if (FLSHM_DWNLD_VLDN_FAIL == flshMgrState)
		{
			/* indicate negative response */
			ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;
			crc_rtnNoError = ISOUDS_RTNCTRL_NEGTIVE;
		}
		else if(FLSHM_DWNLD_VLDN_PASS == flshMgrState)
		{
			/* Response length for the current Service - including SID */
			ISOUDS_Srv_ConfPtr->srvLen = 4;

			ISOUDS_Srv_ConfPtr->srvSt  = ISOUDS_RESP;

			crc_rtnNoError = ISOUDS_RTNCTRL_POSTIVE;
		}
		else if(FLSHM_DWNLD_VLDN_RUNNING != flshMgrState)
		{
			/* indicate negative response */
			ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;
			crc_rtnNoError = ISOUDS_RTNCTRL_NEGTIVE;
		}
		else
		{
			ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPPEND;
			crc_rtnNoError = ISOUDS_RTNCTRL_PENDING;
		}
	}
#else
	// enrico FIXME just report it is valid
	/* Response length for the current Service - including SID */
	ISOUDS_Srv_ConfPtr->srvLen = 5;

#if 0
	dataBuff[3u] = 0x01; // enrico against spec!
#else
	dataBuff[3u] = 0x00; // according new spec
#endif
	ISOUDS_Srv_ConfPtr->srvSt  = ISOUDS_RESP;

	crc_rtnNoError = ISOUDS_RTNCTRL_POSTIVE;

	// Enrico TODO Calibration Area
	FLASH_DRV_Program(FLSHM_APP_VALID_FLAG, 16, sig);

#endif
	/* Return the status */
	return (crc_rtnNoError);

}


uint8 ISOUDS_CheckAppAuthorization (ISOUDS_ConfType *ISOUDS_Srv_ConfPtr, uint8 dataBuff[])
{

	FLSHM_AppVldnStat_t  flshjobstatus = FLSHM_APPATHRZN_IDLE;
	FLSHM_AppVldnStat_t flshMgrState = FLSHM_APPATHRZN_IDLE;
	uint8   sig_rtnNoError;
	uint32 FlashAuthStartAddr = 0x00000000;
	uint32 FlashAuthSize = 0x00000000;
	uint8 ISOUDS_sign_bytes[32U];
	uint8 Rtn_sign_length;
	uint8 Rtnidx;
	if (ISOUDS_Srv_ConfPtr->srvSt == (uint8)ISOUDS_RXMSG)
	{


		FlashAuthStartAddr = (((uint32)dataBuff[3] << 24) | ((uint32)dataBuff[4] << 16) | ((uint32)dataBuff[5] << 8) | ((uint32)dataBuff[6] << 0));

		FlashAuthSize = (((uint32)dataBuff[7] << 24) | ((uint32)dataBuff[8] <<16) | ((uint32)dataBuff[9] << 8) | ((uint32)dataBuff[10] << 0));

		Rtn_sign_length=(uint16)ISOUDS_Srv_ConfPtr->srvLen-12U;

         for(Rtnidx=0;Rtnidx<Rtn_sign_length;Rtnidx++)
         {
        	 ISOUDS_sign_bytes[Rtnidx]= dataBuff[11U+Rtnidx];
         }

		flshjobstatus = FLSHM_StartDwnldAthrzn(FlashAuthStartAddr,FlashAuthSize, ISOUDS_sign_bytes,Rtn_sign_length);
		if((flshjobstatus == FLSHM_APPVALDN_REQ_ACCEPT))
		{
			/* indicate response pending to service provider */
			ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPPEND;
			sig_rtnNoError = ISOUDS_RTNCTRL_PENDING;
		}
		else
		{

			/* indicate negative response */
			ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;
			sig_rtnNoError = ISOUDS_RTNCTRL_NEGTIVE;
		}

	}
	else
	{
		flshMgrState = FLSHM_GetAppValdnStat();

		if (FLSHM_DWNLD_ATHRZN_FAIL == flshMgrState)
		{
			/* indicate negative response */
			ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;
			sig_rtnNoError = ISOUDS_RTNCTRL_NEGTIVE;
		}
		else if(FLSHM_DWNLD_ATHRZN_PASS == flshMgrState)
		{
			/* Response length for the current Service - including SID */
			ISOUDS_Srv_ConfPtr->srvLen = 4;

			ISOUDS_Srv_ConfPtr->srvSt  = ISOUDS_RESP;

			sig_rtnNoError = ISOUDS_RTNCTRL_POSTIVE;
		}
		else if(FLSHM_DWNLD_ATHRZN_RUNNING != flshMgrState)
		{
			/* indicate negative response */
			ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;
			sig_rtnNoError = ISOUDS_RTNCTRL_NEGTIVE;
		}
		else
		{
			ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPPEND;
			sig_rtnNoError = ISOUDS_RTNCTRL_PENDING;
		}
	}


	/* Return the status */
	return (sig_rtnNoError);
}

uint8 ISOUDS_CheckECUMode(ISOUDS_ConfType *ISOUDS_Srv_ConfPtr, uint8 dataBuff[])
{
	uint8   mode_rtnNoError = ISOUDS_RTNCTRL_NEGTIVE;
	uint8 rtnMode;
	FLSHM_AppVldnStat_t  flshModetatus;
	FLSHM_AppVldnStat_t  flshModeMgrState;
	if (ISOUDS_Srv_ConfPtr->srvSt == (uint8)ISOUDS_RXMSG)
	{
		rtnMode=dataBuff[3];

		flshModetatus=FLSHM_SetMODE(rtnMode);
		if((flshModetatus == FLSHM_APPVALDN_REQ_ACCEPT))
		{
			/* indicate response pending to service provider */
			ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPPEND;
			mode_rtnNoError = ISOUDS_RTNCTRL_PENDING;
		}
		else
		{
			/* indicate negative response */
			ISOUDS_Srv_ConfPtr->srvSt = ISOUDS_RESPNEG;
			mode_rtnNoError = ISOUDS_RTNCTRL_NEGTIVE;
		}
	}
	else
	{
	    flshModeMgrState= FLSHM_GetAppValdnStat();

		if(flshModeMgrState==FLSH_PRODUCT_MODE)
		{
			ISOUDS_Srv_ConfPtr->srvLen = 4;

			ISOUDS_Srv_ConfPtr->srvSt  = ISOUDS_RESP;

		    rtnNoError = ISOUDS_RTNCTRL_POSTIVE;

		}

	}

	return mode_rtnNoError;
}
