/***************************************************************************************************
 **
 ** -------------------------------------------------------------------------------------------------
 ** File Name    : ISOUDS_SA.c
 **
 ** Description  : Security Access Service
 **
 ** -------------------------------------------------------------------------------------------------
 **
 ***************************************************************************************************/

/**************************************** Inclusion files *****************************************/
#include <string.h>
#include "ISOUDS.h"
#include "ISOUDS_SA.h"
#include "ISOUDS_SeedKey.h"
#include "FLSHM.h"
#include "ecc.h"

/********************** Declaration of local symbol and constants *********************************/
/* Request Seed security access Type */
//#define     ISOUDS_SAREQSEED            ((uint8)1)
/* Send Key security access Type */
#define     ISOUDS_SASENDKEY            ((uint8)2)

/* Seed SIZE */
#define     ISOUDS_SASEED_MAXSIZE           (8)
/* Security Access Service length */
#define     ISOUDS_SASERLEN             (2)
/********************************* Declaration of local macros ************************************/

/********************************* Declaration of local types *************************************/

/******************************* Declaration of local variables ***********************************/

/******************************* Declaration of local constants ***********************************/

/****************************** Declaration of exported variables *********************************/
/* Is seed Static or to be generated each time when Unlock request comes is decided by this variable */
/* ISOUDS_TRUE = Same seed everytime for same level
   ISOUDS_FALSE = Random seed is generated every time */
uint8 ISOUDS_SAStatic_Seed;

/* Status to indicate which security Access level is currently there */
uint8 ISOUDS_SALevel;
/* Attempt counts if Exceeds limit ECU is locked for some time and
will not accept any request for unlocking */
uint8 ISOUDS_SAAttCnt;

/* Timers */
/* Security Access Delay timer for session.
After this time particular session will time out and ECU will lock again */
uint32 ISOUDS_SATimerSession;
/* Security Access Delay timer for Recevie key
Under this time the key should be Received for send seed.otherwise it will be count as ISOUDS_FALSE attempt*/
uint32 ISOUDS_SATimerWaitingForKey;
/* Security Access delay timer to lock ECU if attempt count exceeds limit */
uint32 ISOUDS_SATimerAttCntExceeded;

/* Requested Current Security levels */
uint8 ISOUDS_SACurrentRequestedLevel;

/* To start stop the timers */
uint32 ISOUDS_SATimerSessionRunning;
uint32 ISOUDS_SATimerWaitingForKeyRunning;
uint32 ISOUDS_SATimerAttCntExceededRunning;
uint32 ISOUDS_SALockTime;

uint32 ISOUDS_SAPowerOnDelayTime;
uint8 ISOUDS_SAPowerOnDelayFlag;


/* Variable to Check ISOUDS Session change */
uint8 ISOUDS_OldSess;

/* Seed */
uint8 GenratedSeed[ISOUDS_SASEED_MAXSIZE]  = { 0x00U };

/* security access Service State */
static uint8 ISOUDS_SAState;
/****************************** Declaration of exported constants *********************************/

/***************************************************************************************************
 **                                      FUNCTIONS                                                 **
 ***************************************************************************************************/

/**************************** Internal functions declarations *************************************/
static void ISOUDS_GetSeed (uint8 *datavalue,uint8 SeedSize);
static void ISOUDS_FillSeed( uint8_t buffer[8] );
uint8 ISOUDS_ValidateKey (uint8 *datavalue, uint8 SecurityLevel);
/******************************** Function definitions ********************************************/

/***************************************************************************************************
 ** Function                 : ISOUDS_SAInit

 ** Description              : Initializes the required security parameters

 ** Parameter                : None

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_SAInit (uint8 bootFlag)
{
	/* Initialize the ECU Unlock status to ISOUDS_FALSE */
	if(bootFlag == 0)
	{
	    ISOUDS_StECUUnLock = ISOUDS_FALSE;
		ISOUDS_SAPowerOnDelayFlag = ISOUDS_TRUE;
		ISOUDS_SAPowerOnDelayTime = 1;
	}
	else
	{
		 //ISOUDS_StECUUnLock = ISOUDS_TRUE; // Already Unlocked in Application
		//ISOUDS_StECUUnLock = ISOUDS_FALSE;
		ISOUDS_SAPowerOnDelayFlag = ISOUDS_FALSE;
		ISOUDS_SAPowerOnDelayTime = 0;
	}
	/* Is seed Static or to be generated each time when Unlock request comes is decided by this variable */
	/* ISOUDS_TRUE = Same seed everytime for same level
       ISOUDS_FALSE = Random seed is generated every time */
	ISOUDS_SAStatic_Seed = ISOUDS_TRUE;

	/* Status to indicate which security Access level is currently there */
	ISOUDS_SALevel = 0x00;
	/* Attempt counts if Exceeds limit ECU is locked for some time and
    will not accept any request for unlocking */
	ISOUDS_SAAttCnt = 0x00;

	/* Timers */
	/* Security Access Delay timer for session.
    After this time particular session will time out and ECU will lock again */
	ISOUDS_SATimerSession = 0x0000;
	/* Security Access Delay timer for Recevie key
    Under this time the key should be Received for send seed.otherwise it will be count as ISOUDS_FALSE attempt*/
	ISOUDS_SATimerWaitingForKey = 0x0000;
	/* Security Access delay timer to lock ECU if attempt count exceeds limit */
	ISOUDS_SATimerAttCntExceeded = 0x0000;

	/* Requested Current Security levels */
	ISOUDS_SACurrentRequestedLevel = 0x00;

	/* To start stop the timers */
	ISOUDS_SATimerSessionRunning = ISOUDS_FALSE;
	ISOUDS_SATimerWaitingForKeyRunning = ISOUDS_FALSE;
	ISOUDS_SATimerAttCntExceededRunning = ISOUDS_FALSE;



	/* security access Service State */
	ISOUDS_SAState = ISOUDS_SA_STATE_A;

	if (bootFlag == 1)
	{
		/* Variable to Check ISOUDS Session change */
		ISOUDS_OldSess = ISOUDS_PRGS;
	}
	else
	{
		/* Variable to Check ISOUDS Session change */
		ISOUDS_OldSess = ISOUDS_DS;
	}
}

/***************************************************************************************************
 ** Function                 : ISOUDS_SA

 ** Description              : Sends the response to security access service request

 ** Parameter ISOUDSConfPtr  : Pointer to service configuration structure

 ** Parameter dataBuff       : Data array

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_SA (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[])
{
	uint8 iChkValidKey = 0x00;
	uint8 idx = 0x00;
	uint8 iSAlevelSupported = 0x00;
	uint8 SecLevel;
	static uint16 SeedSize = 0;
	uint8 CheckRequestedLevel;

	/* Reimplementation of SA as per Appendix I,ISO 14229-1    */
	/*---------------------------------------------------------------------------------------------------------------------------------------------*/
	/* Check if the security access type is of requestSeed */
	CheckRequestedLevel = dataBuff[0];
	if(((CheckRequestedLevel % 2) == 1) && (CheckRequestedLevel >= 1)&& (CheckRequestedLevel <= 41))
	{
		ISOUDS_SAState = ISOUDS_SA_STATE_A;
	}
	else
	{
		/* Do Nothing */
	}

	/* If attempt count is exceeded,ignore everything until timer expires */
	if(((ISOUDS_SATimerAttCntExceededRunning == ISOUDS_TRUE) ||
			((uint8)TRUE == ISOUDS_SAPowerOnDelayFlag)) &&
			(((CheckRequestedLevel % 2) == 1) && (CheckRequestedLevel >= 1)&& (CheckRequestedLevel <= 41)))
	{
		/* Negative response */
		ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

		/* NRC - Request Sequence Error */
		ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_RTDNE;
	}
	else
	{
		switch(ISOUDS_SAState)
		{
		case ISOUDS_SA_STATE_A:
		case ISOUDS_SA_STATE_C:
		{
			/* If service is invoked due to reception of new request */
			if (ISOUDSConfPtr->srvSt == (uint8)ISOUDS_RXMSG)
			{
				/* store the security access type */
				ISOUDS_SACurrentRequestedLevel = dataBuff[0];

				/* Check if the security access type is of requestSeed */
				if (((ISOUDS_SACurrentRequestedLevel%2) == 1) && ((1 <= ISOUDS_SACurrentRequestedLevel) && (ISOUDS_SACurrentRequestedLevel  <= 0x7D)))
				{
					/* If sufficient bytes are received */
					if (ISOUDSConfPtr->srvLen == (uint16)ISOUDS_SASERLEN)
					{
						/* Check if ECU is already unlocked with current level or not */
						// enrico removed this state
						if(0) // ((ISOUDS_StECUUnLock == ISOUDS_TRUE) && (ISOUDS_SACurrentRequestedLevel == ISOUDS_SALevel))
						{
							/* Send positive response with seed = 0 */
							/* prepare the response */
							dataBuff[0] = ISOUDS_SACurrentRequestedLevel;

							if(ISOUDS_SACurrentRequestedLevel == 0x01)
							{
								SeedSize = 4;
							}
							else if(ISOUDS_SACurrentRequestedLevel == 0x03)
							{
								SeedSize = 4;
							}
							else if(ISOUDS_SACurrentRequestedLevel == 0x7D)
							{
								SeedSize = 4;
							}

							/* Send seed with a value of zero */
							for (idx = (uint8)1; idx <= (uint8)SeedSize; idx++)
							{
								dataBuff[idx] = (uint8)0x00;
							}

							/* Response length for the current Service - including SID */
							ISOUDSConfPtr->srvLen = (uint16)SeedSize + (uint16)2;

							/* Send positive response */
							ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;

							ISOUDS_SAState = ISOUDS_SA_STATE_D;
						}
						else
						{
							/* Clear SA level check supported or not */
							iSAlevelSupported = ISOUDS_FALSE;

							/* Check here if the particular security level is supported or not
                                If supported add the code in case to genrate particular level seed and
                                put in buffer,else send negative response */
							/* whatever security level is supported please add the code in that case to generate that
                                seed,fill that seed and set iSAlevelSupported = ISOUDS_TRUE; */
							switch(ISOUDS_SACurrentRequestedLevel)
							{
								case 1:
								{
									iSAlevelSupported = ISOUDS_TRUE;
									// Enrico FIXED to 4
									//SeedSize = 5;
									//ISOUDS_GetSeed((uint8 *)(&dataBuff[1]),SeedSize);

									SeedSize = 4;
									ISOUDS_GetSeed((uint8 *)(&dataBuff[1+4]),SeedSize);
									ISOUDS_FillSeed(&dataBuff[1]); // Order matters!
								}
								break;
								case 3:
								{
#if 0
									iSAlevelSupported = ISOUDS_FALSE;
									SeedSize = 4;
									ISOUDS_GetSeed((uint8 *)(&dataBuff[1]),SeedSize);
#endif
								}
								break;

								break;
								case 0x7D:
								{
									iSAlevelSupported = ISOUDS_FALSE;
#if 0
									SeedSize = 4;
									ISOUDS_GetSeed((uint8 *)(&dataBuff[1]),SeedSize);
#endif
								}
								break;
								default:
								{
									iSAlevelSupported = ISOUDS_FALSE;

									/****************************************************************

											INSERT CODE TO GENERATE SEED AND UPDATE THE VARIABLE
											iSAlevelSupported Accordingly.

									 *****************************************************************/
									/****************************************************************

											INSERT CODE TO COPY GENERATED SEED INTO RESPONSE BUFFER
											E.g.
											for (idx = (uint8)0; idx < (uint8)32; idx++)
											{
											dataBuff[idx + (uint8)1] = GenratedSeed[idx];
											}

									 *****************************************************************/

								}
								break;
							}

							if(iSAlevelSupported == ISOUDS_TRUE)
							{
								/* Send positive response */

								/* Change state machine to Seed send waiting for response */
								/* If any one state is unlocked then change to State D else state B */
								if(ISOUDS_StECUUnLock == ISOUDS_TRUE)
								{
									ISOUDS_SAState = ISOUDS_SA_STATE_D;
								}
								else
								{
									ISOUDS_SAState = ISOUDS_SA_STATE_B;
								}

								/* Get the Current timer value. */
								ISOUDS_SATimerWaitingForKey = 1;

								/* Change current Security level to Requested level */
								ISOUDS_SALevel = ISOUDS_SACurrentRequestedLevel;

								/* prepare the response */
								dataBuff[0] = ISOUDS_SACurrentRequestedLevel;

								/* Response length for the current Service - including SID */
								// Enrico fixed to CANOO req
								//ISOUDSConfPtr->srvLen = ((uint16)SeedSize + (uint16)2);
								ISOUDSConfPtr->srvLen = ((uint16)SeedSize + (uint16)2 + 4u);

								/* Send positive response */
								ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
							}
							else
							{
								/* Security level is not supported send negative response */
								/* Negative response */
								ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

								/* NRC - subFunction not suported */
								ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_SFNS;
							}
						}
					}
					else
					{
						/* Negative response */
						ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

						/* NRC - Request Sequence Error */
						ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_IMLOIF;
					}
				}
				else if ((ISOUDS_SACurrentRequestedLevel == 4) || (ISOUDS_SACurrentRequestedLevel == 8) || (ISOUDS_SACurrentRequestedLevel == 0x7E))
				{
					/* Negative response */
					ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

					/* NRC - Request Sequence Error */
					ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_RSE;
				}
				else
				{
					/* Negative response */
					ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

					/* Invalid Message Length Or Invalid Format */
					ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_SFNS;
				}
			}
			else
			{
				/* Negative response */
				ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

				/* NRC - Request Sequence Error */
				ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_IMLOIF;
			}
		}
		break;
		case ISOUDS_SA_STATE_B:
		case ISOUDS_SA_STATE_D:
		{
			/* If service is invoked due to reception of new request */
			if ((ISOUDSConfPtr->srvSt == (uint8)ISOUDS_RXMSG) &&
					(ISOUDS_SAState == ISOUDS_SA_STATE_B))
			{


				/* If sufficient bytes are received */
				// Enrico: FIXME temp fix!!
				//if (ISOUDSConfPtr->srvLen == ((uint16)KEYSIZE + (uint16)2))
				if(1)
				{

					SecLevel = dataBuff[0];

					if(((SecLevel%2) == 0) && ((2 <= SecLevel) && (SecLevel <= 0x7E)))
					{


						/* Clear SA level check supported or not */
						iSAlevelSupported = ISOUDS_TRUE;
						/* Clear Valid key check */
						iChkValidKey = ISOUDS_FALSE;



						/* Check here if the particular security level is supported or not
                            If supported add the code in case to validate particular level key and
                            fill in buffer,else send negative response */
						/* whatever security level is supported please add the code in that case to validate that
                            key,fill that key and set iSAlevelSupported = ISOUDS_TRUE; */
						switch(SecLevel)
						{
						case 2:
						case 4:
						case 0x7E:
						{
							iSAlevelSupported = ISOUDS_TRUE;



							/* Compare recived Key request with Generated one */
							if(ISOUDS_ValidateKey((uint8 *)(&dataBuff[1]), SecLevel))
							{
								iChkValidKey = ISOUDS_TRUE;
							}
							else
							{
								if(FLSHM_ECUmode==SA_MANUFACTURING_MODE)
								{
						          iChkValidKey = ISOUDS_TRUE;

								}
								else
								{
								iChkValidKey = ISOUDS_FALSE;
								}
							}
						}
						break;
						default:
						{
							iSAlevelSupported = ISOUDS_FALSE;

							/****************************************************************

                                    INSERT CODE TO VALIDATE KEY & ACCORDINGLY UPDATED THE VARIABLE
                                    iChkValidKey. IF iChkValidKey IS ISOUDS_TRUE, THEN KEY IS VALID.

							 *****************************************************************/

							iChkValidKey = ISOUDS_FALSE;
						}
						break;
						}

						if(iSAlevelSupported == ISOUDS_TRUE)
						{
							/* Check if the received key matches with the generated key */
							if (iChkValidKey == ISOUDS_TRUE)
							{
								/* Unlock the ECU */
								ISOUDS_StECUUnLock = ISOUDS_TRUE;

								/* Store current Unlocked level */
								ISOUDS_SALevel = ISOUDS_SACurrentRequestedLevel;

								/* Send positive response */
								dataBuff[0] = ISOUDS_SALevel +1;

								/* Response length for the current Service - including SID */
								ISOUDSConfPtr->srvLen = (uint16)2;

								/* Send positive response */
								ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;

								/* Start the Session Timer */
								ISOUDS_SATimerSessionRunning = ISOUDS_TRUE;

								/* Get the Current timer value. */
								ISOUDS_SATimerSession = 1;

								/* Clear the attempt Counter */
								ISOUDS_SAAttCnt = 0x00;

								/* Change State */
								ISOUDS_SAState = ISOUDS_SA_STATE_C;

								/* Stop waiting for key Timer */
								ISOUDS_SATimerWaitingForKeyRunning = ISOUDS_FALSE;

								/* Clear waitng for Key Timer */
								ISOUDS_SATimerWaitingForKey = 0x0000;
							}
							/* Invalid key is provided */
							else if(iChkValidKey == ISOUDS_FALSE)
							{
								/* Invalid Key So increment attempt count */
								ISOUDS_SAAttCnt++;

								/* Check for Attempt counts and start Timer */
								if(ISOUDS_SAAttCnt > ISOUDS_MAXATTEMTCOUNT)
								{
									if(ISOUDS_SATimerAttCntExceeded == 0U)
									{
										/* Start attempt count timer to block future attempts */
										/* Get the Current timer value. */
										ISOUDS_SATimerAttCntExceeded = 1;

										ISOUDS_SATimerAttCntExceededRunning = ISOUDS_TRUE;
									}
									/* Negative response */
									ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

									/* NRC - invalid key */
									ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_ENOA;
								}
								else
								{
									/* Negative response */
									ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

									/* NRC - invalid key */
									ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_IK;

									/* Stop waiting for key Timer */
									ISOUDS_SATimerWaitingForKeyRunning = ISOUDS_FALSE;

									/* Clear waitng for Key Timer */
									ISOUDS_SATimerWaitingForKey = 0x0000;
								}

						}
						else
						{
							/* Negative response */
							ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

							/* NRC - subFunction not suported */
							ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_SFNS;
						}
					}
					else
					{
						/* Negative response */
						ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

						/* NRC - subFunction not suported */
						ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_SFNS;
					}
				}
				else
				{
					/* Negative response */
					ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

					/* Invalid Message Length Or Invalid Format */
					// Enrico bugfix
					//ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_RSE;
					ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_IMLOIF;
				}
			}
			else
			{
				/* Negative response */
				ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

				/* NRC - Request Sequence Error */
				// Enrico bugfix
				//ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_IMLOIF;
				ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_RSE;
			}
		}
		break;

		default:
		{
			/* Negative response */
			ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

			/* Invalid Message Length Or Invalid Format */
			ISOUDSConfPtr->srvNegResp = (uint8)ISOUDS_IMLOIF;

		}
		break;

		}
	}
}
}

/***************************************************************************************************
 ** Function                 : ISOUDS_GetSASt

 ** Description              : Gets ECU Lock Status

 ** Parameter ISOUDSConfPtr  : Pointer to service configuration structure

 ** Parameter dataBuff       : Data array

 ** Return value             : None
 ***************************************************************************************************/
uint8 ISOUDS_GetSASt (void)
{
	return (ISOUDS_StECUUnLock);
}

/***************************************************************************************************
 ** Function                 : ISOUDS_SAChkTimer

 ** Description              : Check Timers and Session change to lock ECU

 ** Parameter ISOUDSConfPtr  : void

 ** Parameter dataBuff       : void

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_SAChkTimer (void)
{
	if (ISOUDS_SATimerSession > 0)
	{
		/* Check for timer overflow */
		if(ISOUDS_SATimerSession >= ISOUDS_SASESSIONTIMERMAX)
		{
			/* Session Timeout Lock ECU and Reset Everything */
			ISOUDS_SAReset();

			/* Stop timer */
			ISOUDS_SATimerSessionRunning = ISOUDS_FALSE;

			/* Clear Timer */
			ISOUDS_SATimerSession = 0;
		}else
		{
			ISOUDS_SATimerSession += ISOUDS_PERIOD_SCHED;
		}

	}


	if (ISOUDS_SATimerWaitingForKey > 0)
	{
		/* Check for timer overflow */
		if(ISOUDS_SATimerWaitingForKey >= ISOUDS_SAWAITKEYMAX)
		{
			/* Key not Received */
			ISOUDS_SAReset();

			/* Increment Attempt Count */
			ISOUDS_SAAttCnt++;

			/* Stop timer */
			ISOUDS_SATimerWaitingForKeyRunning = ISOUDS_FALSE;

			/* Clear Timer */
			ISOUDS_SATimerWaitingForKey = 0;
		}
		else
		{
			ISOUDS_SATimerWaitingForKey += ISOUDS_PERIOD_SCHED;
		}
	}

	if (ISOUDS_SATimerAttCntExceeded > 0)
	{
		/* Check for timer overflow */
		if(ISOUDS_SATimerAttCntExceeded >= ISOUDS_SASESSIONTIMERMAX)
		{
			/* Attempt Timer Expired Allow ECU Unlocking */
			ISOUDS_SAReset();

			/* Clear Attempt Count */
			ISOUDS_SAAttCnt = 0;

			/* Stop timer */
			ISOUDS_SATimerAttCntExceededRunning = ISOUDS_FALSE;

			/* Clear Timer */
			ISOUDS_SATimerAttCntExceeded = 0;

			/* Get the Current timer value. */
			ISOUDS_SALockTime = 1;

			/* Clear the timer. */
			ISOUDS_SATimerSession = 0;

			/* Clear the timer. */
			ISOUDS_SATimerWaitingForKey = 0;
		}
		else
		{
			ISOUDS_SATimerAttCntExceeded += ISOUDS_PERIOD_SCHED;
		}

	}

	if (ISOUDS_SALockTime > 0)
	{
		/* Check for timer overflow */
		if(ISOUDS_SALockTime >= ISOUDS_SALOCKPERIOD)
		{
			/* Attempt Timer Expired Allow ECU Unlocking */
			ISOUDS_SAReset();

			/* Clear Attempt Count */
			ISOUDS_SAAttCnt = 0;

			/* Stop timer */
			ISOUDS_SATimerAttCntExceededRunning = ISOUDS_FALSE;

			/* Clear Timer */
			ISOUDS_SATimerAttCntExceeded = 0;

			/* Clear Timer. */
			ISOUDS_SALockTime = 0;
		}
		else
		{
			ISOUDS_SALockTime += ISOUDS_PERIOD_SCHED;
		}
	}

	/* Check for ECU Session change.IF session changes lock ECU and
        Reset Service Layer */
	if(ISOUDS_OldSess != ISOUDS_Sess)
	{
		/* Session change Reset SA */
		ISOUDS_SAReset();
	}

	if ((ISOUDS_SAPowerOnDelayTime > 0) && (ISOUDS_SAPowerOnDelayFlag == ISOUDS_TRUE))
	{
		if (ISOUDS_SAPowerOnDelayTime > ISOUDS_SAPOWERON_DELAY)
		{
			ISOUDS_SAPowerOnDelayFlag = ISOUDS_FALSE;
		}
		else
		{
			ISOUDS_SAPowerOnDelayTime += ISOUDS_PERIOD_SCHED;
		}
	}

	/* Copy current session into old for checking */
	ISOUDS_OldSess = ISOUDS_Sess;
}

/***************************************************************************************************
 ** Function                 : ISOUDS_SAReset

 ** Description              : Resets the SA service parameters

 ** Parameter ISOUDSConfPtr  : void

 ** Parameter dataBuff       : void

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_SAReset (void)
{
	/* Stop all Timers */
	ISOUDS_SATimerSessionRunning = ISOUDS_FALSE;
	ISOUDS_SATimerWaitingForKeyRunning = ISOUDS_FALSE;

	/* Clear all counters */
	ISOUDS_SATimerSession = 0;
	ISOUDS_SATimerWaitingForKey = 0;

	/* Change state to Default */
	ISOUDS_SAState = ISOUDS_SA_STATE_A;

	/* lock the ECU */
	ISOUDS_StECUUnLock = ISOUDS_FALSE;
}

/***************************************************************************************************
 ** Function                 : ISOUDS_GetSAStLevel

 ** Description              : Gets ECU Lock Status of particular Level

 ** Parameter ISOUDSConfPtr  : Pointer to service configuration structure

 ** Parameter dataBuff       : Data array

 ** Return value             : uint8
                                ISOUDS_TRUE = particular level is supported and unlocked.
                                ISOUDS_FALSE = particular level is not unlocked or may be not supported.
 ***************************************************************************************************/
uint8 ISOUDS_GetSAStLevel (uint8 SALevel)
{
#if DISABLE_SECURITY_ACCESS
	return ISOUDS_TRUE;
#else
	uint8 iLevelStatus = ISOUDS_FALSE;
	/* Check if particular Security level is current level or not */
	if((SALevel == ISOUDS_SALevel) && (ISOUDS_StECUUnLock == ISOUDS_TRUE))
	{
		iLevelStatus = ISOUDS_TRUE;
	}
	else
	{
		iLevelStatus = ISOUDS_FALSE;
	}
	return (iLevelStatus);
#endif
}

/**************************** Internal Function definitions ***************************************/
/***************************************************************************************************
 ** Function                 : ISOUDS_GetSeed

 ** Description              : Fills the Seed in provided buffer.

 ** Parameter datavalue      : None

 ** Return value             : None
 ***************************************************************************************************/
 void ISOUDS_GetSeed (uint8 *datavalue, uint8 SeedSize)
{
	uint8 idx;
	uint32 tempSeedVal;
	uint8 *Ptr2Seed;



	if(ISOUDS_SACurrentRequestedLevel == 1)
	{
		tempSeedVal = GetSeedLevel1();
		Ptr2Seed = (uint8*)&tempSeedVal;

		GenratedSeed[0] = Ptr2Seed[0] ^ 0x66u;
		GenratedSeed[1] = Ptr2Seed[1] ^ 0x66u;
		GenratedSeed[2] = Ptr2Seed[2] ^ 0x66u;
		GenratedSeed[3] = Ptr2Seed[3] ^ 0x66u;
		GenratedSeed[4] = Ptr2Seed[4] ^ 0x66u;
	}
	else
	{

	}

	for (idx = (uint8)0u; idx < (uint8)SeedSize; idx++)
	{
		datavalue[idx] = GenratedSeed[idx];
	}
}


 // enrico added
 static void ISOUDS_FillSeed( uint8_t buffer[8] )
 {
	buffer[0] = BUS_ID;
	buffer[1] = ECU_ID;
	buffer[2] = (KEY_VERSION & 0xFF);
	buffer[3] = ((KEY_VERSION>>8) & 0xFF);
	buffer[4] = GenratedSeed[0];
	buffer[5] = GenratedSeed[1];
	buffer[6] = GenratedSeed[2];
	buffer[7] = GenratedSeed[3];
 }

/***************************************************************************************************
 ** Function                 : ISOUDS_RetriveSeed

 ** Description              : Retrive seed from provided key.

 ** Parameter datavalue      : None

 ** Return value             : None
 ***************************************************************************************************/
uint8 ISOUDS_ValidateKey (uint8 *datavalue, uint8 SecurityLevel)
{
	uint8 ret;

#if 0 // Enrico
	uint8 KeySize;
	uint8  ByteIdx;

	uint8 CalculatedKey[40] = {0};

	ret = ISOUDS_FALSE;

	if(SecurityLevel == 2)
	{
		KeySize = KEYSIZE;
		Seed_Level1  =  (uint64)GenratedSeed[4];
		Seed_Level1 |= ((uint64)GenratedSeed[3] << 8);
		Seed_Level1 |= ((uint64)GenratedSeed[2] << 16);
		Seed_Level1 |= ((uint64)GenratedSeed[1] << 24);
		Seed_Level1 |= ((uint64)GenratedSeed[0] << 32);

		/* Get the Key. */
		generateKeyLevel1(Seed_Level1 , CalculatedKey);
	}
	else /*if(SecurityLevel == 4)*/
	{

	}

	for(ByteIdx = 0u; ByteIdx < KeySize; ByteIdx++)

	{

		if(CalculatedKey[ByteIdx] ==  datavalue [ByteIdx] )
		{
			/* Set the return value as ISOUDS_TRUE and keep comparing */
			ret = ISOUDS_TRUE;
		}
		else
		{
			/* Set the return value as ISOUDS_FALSE and stop comparing */
			ret = ISOUDS_FALSE;
			break;
		}
	}
#else // ECDSA

#define SECURITY_ACCESS_PUBLIC_KEY_VERSION      (1u)
#define SECURITY_ACCESS_PUBLIC_KEYSIZE          (uint8_t)91u
#define SECURITY_ACCESS_PUBLIC_OFFSET           (uint8_t)27u
#define SA_DATA_SIZE							(8u) // BUS_ID, ECU_ID, KEY_REV*2, Nonce*4

	if( 2u == SecurityLevel )
	{
		// in datavalue is the signature

		sha256_control sha256;
		uint32_t h,i;
		uint8_t hash[32];

		// Public key for security access: DevelopmentKey
		const uint8_t publickey[SECURITY_ACCESS_PUBLIC_KEYSIZE] = {
			    0x30u, 0x59u, 0x30u, 0x13u, 0x06u, 0x07u, 0x2Au, 0x86u,
				0x48u, 0xCEu, 0x3Du, 0x02u, 0x01u, 0x06u, 0x08u, 0x2Au,
				0x86u, 0x48u, 0xCEu, 0x3Du, 0x03u, 0x01u, 0x07u, 0x03u,
				0x42u, 0x00u, 0x04u, 0x03u, 0xFFu, 0x66u, 0xD7u, 0x00u,
				0x02u, 0x1Du, 0x5Du, 0xFEu, 0x40u, 0xDCu, 0x4Bu, 0xCFu,
				0x35u, 0x1Cu, 0xDDu, 0x12u, 0x92u, 0xD5u, 0x17u, 0x70u,
				0x3Eu, 0x3Fu, 0xD2u, 0xDDu, 0xEBu, 0x56u, 0x26u, 0xD3u,
				0x06u, 0x9Au, 0xE8u, 0x6Cu, 0xADu, 0x2Cu, 0x3Bu, 0xE8u,
				0xAEu, 0x7Bu, 0x62u, 0x27u, 0x52u, 0xE1u, 0x42u, 0x86u,
				0xA7u, 0x0Cu, 0x00u, 0xEAu, 0xA1u, 0x85u, 0xCFu, 0xC0u,
				0x51u, 0x42u, 0xE3u, 0x73u, 0x59u, 0x3Du, 0x15u, 0xDAu,
				0xE5u, 0x34u, 0x3Bu
		};

		// first calculate sha256 over the bytes
		// enrico: tested ok!
		FLASHM_sha256_init(&sha256);
		sha256.chunk_len = SA_DATA_SIZE;
		ISOUDS_FillSeed(&sha256.chunk[0]);
		FLASHM_sha256_padding( &sha256, SA_DATA_SIZE );

		// convert hash to byte array
		for( i=0; i<8; i++)
		{
			h = sha256.hash[i];
			hash[i*4+0] = (uint8_t)((h >> 24) & 0xFF);
			hash[i*4+1] = (uint8_t)((h >> 16) & 0xFF);
			hash[i*4+2] = (uint8_t)((h >> 8) & 0xFF);
			hash[i*4+3] = (uint8_t)((h) & 0xFF);
		}

		ret = ecdsa_verify( &publickey[SECURITY_ACCESS_PUBLIC_OFFSET], hash, &datavalue[0] ) == 0 ? ISOUDS_FALSE : ISOUDS_TRUE;
	}
	else
	{
		ret = ISOUDS_FALSE;
	}
#endif
	/* Return the value */
	return(ret);
}
