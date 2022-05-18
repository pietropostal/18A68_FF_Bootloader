/***************************************************************************************************
 **
 ** -------------------------------------------------------------------------------------------------
 ** File Name    : ISOUDS.c
 **
 ** Description  : Unified Diagnostic Services Stack
 **
 ** -------------------------------------------------------------------------------------------------
 **
 ***************************************************************************************************/

/**************************************** Inclusion files *****************************************/
#include "CanTp.h"
#include "ISOUDS.h"
#include "ISOUDS_StrtDiagSess.h"
#include "ISOUDS_RtnCntrl.h"
#include "ISOUDS_ReqDwnld.h"
#include "ISOUDS_TrnsfrDa.h"
#include "ISOUDS_TrnsfrExit.h"
#include "ISOUDS_ECUReset.h"
#include "ISOUDS_TstrPrsnt.h"
#include "ISOUDS_SA.h"
#include "ISOUDS_CommCntrl.h"
#include "ISOUDS_CntrlDTCSetting.h"
#include "ISOUDS_RdDaByID.h"
#include "ISOUDS_WrDaByID.h"
#include "FLSHM.h"
#include "FLSHM_Cfg.h"
#include "WDT.h"
#include "system_S32K144.h"


/********************** Declaration of local symbol and constants *********************************/
#define     ISOUDS_ONE                 (1)
/* Negative response length */
#define     ISOUDS_NEGRESPLEN          (3)
/* invalid Service ID */
#define     ISOUDS_IDNONE              (0)
/* Single Frame */
#define     ISOUDS_SINGLEFRAME         (0)
/* Multiple Frame */
#define     ISOUDS_MULTIPLEFRAME       (1)
/* Session Selection(SS) Configuration */

/*
stubs :
 */

/*----------------------------------------------------------------------------------------------*/
/*                  E P D R                    EXTDS    = Extended Disgnostic Session */
/*                  X R S E                    PRGS     = Programming Session */
/*                  T G   S                    DS       = Default Session */
/*                  D S   V                    RESV     = Reserved */
/*                  S                          */
/*----------------------------------------------------------------------------------------------*/
#define  ISOUDS_SS_T_T_T_F     (0x0E)          /* T -> ISOUDS_TRUE , F -> ISOUDS_FALSE */
#define  ISOUDS_SS_T_F_T_F     (0x0A)          /* T -> ISOUDS_TRUE , F -> ISOUDS_FALSE */
#define  ISOUDS_SS_T_T_F_F     (0x0C)          /* T -> ISOUDS_TRUE , F -> ISOUDS_FALSE */
#define  ISOUDS_SS_T_F_F_F     (0x08)          /* T -> ISOUDS_TRUE , F -> ISOUDS_FALSE */
#define  ISOUDS_SS_F_T_F_F     (0x04)          /* T -> ISOUDS_TRUE , F -> ISOUDS_FALSE */

/*----------------------------------------------------------------------------------------------*/
/*                  F P 	                    FUNC     = Functional Request */
/*                  U H 	                    PRGS     = Physical request */
/*                  N Y 	                    */
/*                  C   	                    */
/*----------------------------------------------------------------------------------------------*/
#define  ISOUDS_REQ_TYPE_T_T    (0x03)          /* T -> ISOUDS_TRUE , F -> ISOUDS_FALSE */
#define  ISOUDS_REQ_TYPE_T_F    (0x02)          /* T -> ISOUDS_TRUE , F -> ISOUDS_FALSE */
#define  ISOUDS_REQ_TYPE_F_T    (0x01)          /* T -> ISOUDS_TRUE , F -> ISOUDS_FALSE */

/*
ISOUDS_SS_T_T_T_F implies that service is supported in Extended Diagnostic, Programming and
Default session
ISOUDS_SS_T_F_T_F implies that service is supported in Extended and default session only
ISOUDS_SS_T_F_F_F implies that service is supported in Extended Diagnostic session only
 */

/********************************* Declaration of local macros ************************************/
#define M_ISOUDS_NUMSRV    (sizeof(ISOUDS_iTab)/sizeof(ISOUDS_iTabType))

/********************************* Declaration of local types *************************************/
typedef struct
{
	uint8 ReqMsgType;          /* Service id */
	uint8 SID;          /* Service id */
	void (*ISOUDS_FunPtr)(ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[]);/* Hold address of the
                                                                            UDS service function */
	uint8 srvSess;      /* Diagnostic session in which the service is supported */
}ISOUDS_iTabType;

/******************************* Declaration of local variables ***********************************/


/******************************* Declaration of local constants ***********************************/
/* UDS table with service ids and related functions. */
static const ISOUDS_iTabType ISOUDS_iTab[ISOUDS_TABSIZE] =
{
		{
				(uint8)ISOUDS_REQ_TYPE_T_T ,
				(uint8)ISOUDS_SIDSTRTDIAGSESS,
				&ISOUDS_StrtDiagSess,
				(uint8)ISOUDS_SS_T_T_T_F
		},
		{
				(uint8)ISOUDS_REQ_TYPE_T_T ,
				(uint8)ISOUDS_SIDECURST,
				&ISOUDS_ECUReset,
				(uint8)ISOUDS_SS_T_T_T_F
		},
		{
				(uint8)ISOUDS_REQ_TYPE_T_T ,
				(uint8)ISOUDS_SIDTSTRPRSNT,
				&ISOUDS_TstrPrsnt,
				(uint8)ISOUDS_SS_T_T_T_F
		},
		{
				(uint8)ISOUDS_REQ_TYPE_T_T ,
				(uint8)ISOUDS_SIDSA ,
				&ISOUDS_SA,
				(uint8)ISOUDS_SS_T_T_F_F
		},
		{
				(uint8)ISOUDS_REQ_TYPE_T_T,
				(uint8)ISOUDS_SIDRTNCNTRLID,
				&ISOUDS_RtnCntrl,
				(uint8)ISOUDS_SS_T_T_F_F
		},
		{
				(uint8)ISOUDS_REQ_TYPE_T_T,
				(uint8)ISOUDS_SIDREQDWNLD,
				&ISOUDS_ReqDwnld,
				(uint8)ISOUDS_SS_F_T_F_F
		},
		{
				(uint8)ISOUDS_REQ_TYPE_T_T,
				(uint8)ISOUDS_SIDTRNSFRDTID,
				&ISOUDS_TrnsfrDa,
				(uint8)ISOUDS_SS_F_T_F_F
		},
		{
				(uint8)ISOUDS_REQ_TYPE_T_T,
				(uint8)ISOUDS_SIDTRNSFREXITDID,
				&ISOUDS_TrnsfrExit,
				(uint8)ISOUDS_SS_F_T_F_F
		},
		{
				(uint8)ISOUDS_REQ_TYPE_T_T,
				(uint8)ISOUDS_SIDRDDABYID,
				&ISOUDS_RdDaByID,
				(uint8)ISOUDS_SS_T_T_T_F
		},
		{
				(uint8)ISOUDS_REQ_TYPE_T_T,
				(uint8)CANSRV_SIDWRDABYID,
				&CanSrv_WrDaByID,
				(uint8)ISOUDS_SS_T_T_T_F
		},
		{
				(uint8)ISOUDS_REQ_TYPE_T_T ,
				(uint8)ISOUDS_SIDCOMMCNTRL,
				&ISOUDS_CommCntrl,
				(uint8)ISOUDS_SS_T_T_T_F
		},
		{
				(uint8)ISOUDS_REQ_TYPE_T_T ,
				(uint8)ISOUDS_SIDCNTRLDTCSET,
				&ISOUDS_CntrlDTCSetting,
				(uint8)ISOUDS_SS_T_T_T_F
		},
};

/****************************** Declaration of exported variables *********************************/
/* index */
static uint8 ISOUDS_iTabIdx;

/* Response pending state */
static uint8 ISOUDS_iStRespPendSnt;

/* P2 Timer */
static uint32 ISOUDS_iTmrP2;

/* S3 Timer */
static uint32 ISOUDS_iTmrS3;

/* P2 timer Limit */
static uint32 ISOUDS_iTmrP2Lim;

/* Boot State Seqeunce */
static ISOUDS_BootSeqType ISOUDS_BootState;

/* Positive response supression bit */
static uint8 suppressPosRspMsgIndicationBit;

/* ECU Reset Request */
uint8 ISOUDS_EcuRstReq;

/* UDS Buffer for data */
uint8 ISOUDS_Buff[ISOUDS_BUFFSIZE];

/* Timer for Ecu Reset */
uint32 ISOUDS_TmrECURst;

/* Timer Limits */
uint32 ISOUDS_iTmrP2Min;
uint32 ISOUDS_iTmrP2Max;
uint32 ISOUDS_iTmrSTmin;

/* UDS configuration */
ISOUDS_ConfType ISOUDS_Conf;

/* ISOTP UDS configuration */
ISOTP_App_CfgType ISOTP_UDS_Cfg;

/* Appl Flag to Set. */
// Enrico uint8 ISOUDS_ApplFlag;


/* Program Request. */
uint8 BootFlag_ECUSt;

/* Boot flag. */
uint8 ISOUDS_BootFlag;

/* Status to indicate whether ECU is unlocked or not */
uint8 ISOUDS_StECUUnLock;

/* UDS current session */
uint8 ISOUDS_Sess;

uint8 ISOUDS_RespAfterBoot;

uint8 ECU_reset_type;



/****************************** Declaration of exported constants *********************************/

/***************************************************************************************************
 **                                      FUNCTIONS                                                 **
 ***************************************************************************************************/

/**************************** Internal functions declarations *************************************/
static void ISOUDS_iTxNegResp (void);
static void ISOUDS_iTxRespPend (void);

/******************************** Function definitions ********************************************/

/***************************************************************************************************
 ** Function                 : ISOUDS_Init

 ** Description              : Initialization of UDS parameters

 ** Parameter                : None

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_Init (uint8 bootflag)
{
	/* Initialize to Default session */

	/* Initialize the state to IDLE */
	ISOUDS_Conf.srvSt = (uint8)ISOUDS_IDLE;

	/* Initialize Frame */
	ISOUDS_Conf.srvFrame = (uint8)ISOUDS_SINGLEFRAME;

	/* Initialize the Timer P2 to OFF state */
	ISOUDS_iTmrP2 = (uint32)0;

	/* Initialize the Timer S3 to 0FF state */
	ISOUDS_iTmrS3 = (uint32)0;

	/* Set the Tmr Value Range. */
	ISOUDS_iTmrP2Min = (uint32)ISOUDS_NRC78P2MINLIM;
	ISOUDS_iTmrP2Max = (uint32)ISOUDS_NRC78P2MAXLIM;
	ISOUDS_iTmrSTmin = (uint32)ISOUDS_S3TMRLIM;

	/* Ecu Reset Request */
	ISOUDS_EcuRstReq = ISOUDS_FALSE;

	/* Initialize the status of response pending sent to ISOUDS_FALSE */
	ISOUDS_iStRespPendSnt = ISOUDS_FALSE;

	/* Timer for Ecu Reset */
	ISOUDS_TmrECURst = (uint32)0;

	/* positive response supress bit */
	suppressPosRspMsgIndicationBit = ISOUDS_FALSE;


	ISOUDS_BootState = ISOUDS_SETBOOT_STATE;

	if(bootflag == 0)
	{
		ISOUDS_Sess = (uint8)ISOUDS_DS;
		ISOUDS_SAInit(0);

		ISOUDS_RespAfterBoot = ISOUDS_FALSE;
		// Enrico ISOUDS_ApplFlag = TRUE;
	}
	else
	{
		/* Switch to programming session  */
		ISOUDS_Sess = (uint8)ISOUDS_PRGS;
		ISOUDS_RespAfterBoot = ISOUDS_TRUE;

		ISOUDS_iTmrS3 = 1;

		// Enrico ISOUDS_ApplFlag = TRUE;

		ISOUDS_SAInit(1);
	}



	ISOUDS_TrnsfrDaExit();
}

/***************************************************************************************************
 ** Function                 : ISOUDS_MsgIndi

 ** Description              : Indicates that a new request has been received

 ** Parameter isoTpConfPtr   : Pointer to TP configuration structure

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_MsgIndi (const ISOTP_CfgType *isoTpConfPtr, uint8 ISOTP_ReqMsgTpe)
{
	uint16 idx;

	/* if the present state is IDLE or RXPEND */
	if ((ISOUDS_Conf.srvSt == (uint8)ISOUDS_IDLE) ||
			(ISOUDS_Conf.srvSt == (uint8)ISOUDS_RXPEND))
	{
		/* Check if single frame is received */
		if (ISOUDS_Conf.srvFrame == (uint8)ISOUDS_SINGLEFRAME)
		{
			/* Store the length of data bytes received */
			ISOUDS_Conf.srvLen = (uint16)isoTpConfPtr->nBytes;

			}

		/* Copy data from TP buffer to SrvD buffer */
		for (idx = (uint16)0; idx < ISOUDS_Conf.srvLen; idx++)
		{
			ISOUDS_Buff[idx] = isoTpConfPtr->tpBuff[idx];
		}

		/* Assign standard P2 timer limit */
		ISOUDS_iTmrP2Lim = (uint32)ISOUDS_STDP2LIM;

		/* Start timer P2 */
		ISOUDS_iTmrP2 = 1;

		/* Change state to RXMSG */
		ISOUDS_Conf.srvSt = (uint8)ISOUDS_RXMSG;

		/*Update Message Request Type*/
		ISOUDS_Conf.ReqType = (uint8)ISOTP_ReqMsgTpe;
	}
}

/***************************************************************************************************
 ** Function                 : ISOUDS_MsgIndiIm

 ** Description              : Indicates that a new request has been received

 ** Parameter isoTpConfPtr   : Pointer to TP configuration structure

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_MsgIndiIm (const ISOTP_CfgType *isoTpConfPtr)
{
	/* Service ID. */
	uint16 id = 0;
	uint8 idx = 0;
	uint8 len = 0;
	uint8 Buff[8];

	/* UDS configuration */
	ISOUDS_ConfType L_ISOUDS_Conf;

	/* Store the length of data bytes received */
	len = (uint8)isoTpConfPtr->nBytes;

	L_ISOUDS_Conf.srvLen = len;
	
	id=isoTpConfPtr->tpBuff[0u];

	/* Copy data from TP buffer to SrvD buffer */
	for (idx = (uint16)0; idx < len; idx++)
	{
		Buff[idx] = isoTpConfPtr->tpBuff[idx];
	}


	switch(id)
	{
		case ISOUDS_SIDSTRTDIAGSESS:
		{
			ISOUDS_StrtDiagSess(&L_ISOUDS_Conf, &Buff[1]);
			break;
		}
		case ISOUDS_SIDTRNSFRDTID:
		{
			ISOUDS_TrnsfrDa(&L_ISOUDS_Conf, &Buff[1]);
			break;
		}
		case ISOUDS_SIDTRNSFREXITDID:
		{
			ISOUDS_TrnsfrExit(&L_ISOUDS_Conf, &Buff[1]);
			break;
		}
		case ISOUDS_SIDECURST:
		{
			ISOUDS_ECUReset(&L_ISOUDS_Conf, &Buff[1]);
			break;
		}
		case ISOUDS_SIDTSTRPRSNT:
		{
			suppressPosRspMsgIndicationBit = (ISOUDS_Buff[1] >> 7);
			ISOUDS_Buff[1] = (ISOUDS_Buff[1] & 0x7f);
			ISOUDS_TstrPrsnt(&L_ISOUDS_Conf, &Buff[1]);
			break;
		}

		default:
		{
			break;
		}
	}
}



/***************************************************************************************************
 ** Function                 : ISOUDS_FFIndi

 ** Description              : Indicates that the first frame of new request has been received

 ** Parameter isoTpConfPtr   : Pointer to TP configuration structure

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_FFIndi (const ISOTP_CfgType *isoTpConfPtr, uint8 ISOTP_ReqMsgTpe)
{

	/* if the present state is IDLE or RXPEND */
	if ((ISOUDS_Conf.srvSt == (uint8)ISOUDS_IDLE) || (ISOUDS_Conf.srvSt == (uint8)ISOUDS_RXPEND))
	{
		/* Store the length of data bytes */
		ISOUDS_Conf.srvLen = (uint16)isoTpConfPtr->nBytes;

		/* Change state to Reception Pending */
		ISOUDS_Conf.srvSt = (uint8)ISOUDS_RXPEND;

		/* request received in Multiple Frame */
		ISOUDS_Conf.srvFrame = (uint8)ISOUDS_MULTIPLEFRAME;

		/* Stop Timer S3 */
		ISOUDS_iTmrS3 = (uint32)0;

		/*Update Message Request Type*/
		ISOUDS_Conf.ReqType = (uint8)ISOTP_ReqMsgTpe;
	}
}

/***************************************************************************************************
 ** Function                 : ISOUDS_Main

 ** Description              : UDS Main Function

 ** Parameter                : None

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_Main (void)
{
	uint8   idx;
	uint8 srvFound;


	/* Initialization */
	srvFound = ISOUDS_FALSE;

	/* check the current state */
	if (ISOUDS_Conf.srvSt == (uint8)ISOUDS_RXMSG)
	{
		/* Store the service ID information */
		ISOUDS_Conf.srvId = ISOUDS_Buff[0];

		/* Only certain services support suppressPosRspMsgIndicationBit so if the service is supporting
        suppressPosRspMsgIndicationBit bit then we extract it else we set it to ISOUDS_FALSE and neglect*/
		if( (ISOUDS_Conf.srvId == ISOUDS_SIDSTRTDIAGSESS) || (ISOUDS_Conf.srvId == ISOUDS_SIDTSTRPRSNT) /*     ||\
            (ISOUDS_Conf.srvId == ISOUDS_SIDRTNCNTRLID)*/)
		{
			/* suppressPosRspMsgIndicationBit is supported */
			/* Check for positive response suppress bit and change sub function
            do that it does not effect other services i.e remove 7th bit*/
			suppressPosRspMsgIndicationBit = (ISOUDS_Buff[1] >> 7);
			ISOUDS_Buff[1] = (ISOUDS_Buff[1] & 0x7f);
		}
		else
		{
			/* suppressPosRspMsgIndicationBit is not supported,
            dont change anything and set it to zero */
			suppressPosRspMsgIndicationBit = ISOUDS_FALSE;
		}

		/* Depending on received SID, select the appropriate service */
		for (idx = (uint8)0; ((idx < ((uint8)M_ISOUDS_NUMSRV)) && (srvFound != ISOUDS_TRUE)); idx++)
		{
			if (ISOUDS_iTab[idx].SID == ISOUDS_Conf.srvId)
			{
				if (ISOUDS_iTab[idx].ReqMsgType & ISOUDS_Conf.ReqType)
				{
					srvFound = ISOUDS_TRUE;

					/* Check if the service is allowed in the current session */
					if (((ISOUDS_iTab[idx].srvSess) & ((uint8)((uint8)ISOUDS_ONE << ISOUDS_Sess))) != (uint8)0)
					{
						/* Store the table index */
						ISOUDS_iTabIdx = idx;
#if 0
						/* Call the service function */
						// TOOD: Debug enrico
						if(ISOUDS_Buff[0] == 0x27 && ISOUDS_Buff[1] == 0x2)
						{
							asm("nop");
						}
#endif
						(ISOUDS_iTab[idx].ISOUDS_FunPtr) (&ISOUDS_Conf, &ISOUDS_Buff[1]);
					}
					else
					{
						/* Negative response: Service Not Supported In Active Session */
						ISOUDS_Conf.srvNegResp = (uint8)ISOUDS_SNSIAS;

						/* Update the status to Negative Response state */
						ISOUDS_Conf.srvSt = (uint8)ISOUDS_RESPNEG;
					}
				}
			}
		}
		/* Unknown or Unsupported service */
		if (srvFound == ISOUDS_FALSE)
		{
			/* Update service response length */
			ISOUDS_Conf.srvLen = (uint16)3u;

			/* Negative response: Service Not Supported */
			ISOUDS_Conf.srvNegResp = (uint8)ISOUDS_SNS;

			/* Update the status to Negative Response state */
			ISOUDS_Conf.srvSt = (uint8)ISOUDS_RESPNEG;
		}
	}
	else if (ISOUDS_Conf.srvSt == (uint8)ISOUDS_RESPPEND)
	{
		/* Call the service function */
		(ISOUDS_iTab[ISOUDS_iTabIdx].ISOUDS_FunPtr) (&ISOUDS_Conf, &ISOUDS_Buff[1]);
	}
	else
	{
		/* Do Nothing */
	}

	if (ISOUDS_Conf.srvSt == (uint8)ISOUDS_RESP)
	{
		if(suppressPosRspMsgIndicationBit == ISOUDS_FALSE)
		{
			/* Update the Service ID for Positive response */
			ISOUDS_Buff[0] = ISOUDS_Conf.srvId + (uint8)0x40;

			/* Stop timer P2 */
			ISOUDS_iTmrP2 = (uint32)0;

			/* Change state to Tx confirmation pending */
			ISOUDS_Conf.srvSt = (uint8)ISOUDS_TXPEND;

			/* get data pointer */
			ISOTP_UDS_Cfg.dataPtr = &ISOUDS_Buff[0];

			/* get the length */
			ISOTP_UDS_Cfg.dataLen = ISOUDS_Conf.srvLen;

			/* Request for transmission of positive response */
			ISOTP_TxRequest (&ISOTP_UDS_Cfg);
		}
		else
		{
			/* No need to send any positive response */
			/* Change state to Ideal */
			ISOUDS_Conf.srvSt = (uint8)ISOUDS_IDLE;

			/* positive response suppress bit */
			suppressPosRspMsgIndicationBit = ISOUDS_FALSE;
		}

		/* Stop Timer S3 */
		ISOUDS_iTmrS3 = (uint32)0;
	}
	else if (ISOUDS_Conf.srvSt == (uint8)ISOUDS_RESPNEG)
	{
		/* If the service negative response code is ISOUDS_RCRRP */
		if (ISOUDS_Conf.srvNegResp == (uint8)ISOUDS_RCRRP)
		{
			/* change state to Response pending */
			ISOUDS_Conf.srvSt = (uint8)ISOUDS_RESPPEND;

			/* Service has a response pending, transmit negative response */
			/* and switch to ISOUDS_RESPPEND state */
			ISOUDS_iTxRespPend();
		}
		else
		{
			/* Change state to Tx confirmation pending */
			ISOUDS_Conf.srvSt = (uint8)ISOUDS_TXPEND;

			/* Request Transmission of negative response */
			ISOUDS_iTxNegResp ();
		}
	}
	else
	{
		/* Do Nothing */
	}

	/* check if state is in Tx response pending */
	if (ISOUDS_Conf.srvSt == (uint8)ISOUDS_TXRESPPEND)
	{
		/* Go back to Response pending - Dont wait for Tx confirmation */
		ISOUDS_Conf.srvSt = (uint8)ISOUDS_RESPPEND;
	}


	ISOUDS_Mon();
}

/***************************************************************************************************
 ** Function                 : ISOUDS_TxCnfCbk

 ** Description              : Confirmation of response sent

 ** Parameter                : None

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_TxCnfCbk (void)
{
	/* Check if the current state is Tx confiramtion Pending */
	if (ISOUDS_Conf.srvSt == (uint8)ISOUDS_TXPEND)
	{
		/* Reset the required parameters and go to IDLE state */
		ISOUDS_Rst ();
	}

	/* check if Ecu reset is requested */
	if ((ISOUDS_EcuRstReq == ISOUDS_TRUE))
	{
		/* reset the flag */
		ISOUDS_EcuRstReq = ISOUDS_FALSE;

		/* reset timer */
		ISOUDS_TmrECURst = (uint32)1;

		/* invoke the function to Reset ECU */
		if(ECU_reset_type==0x01)
		{
			SystemSoftwareReset();


		}
		else if(ECU_reset_type==0x03)
		{
		   SystemSoftwareReset();
		}else
		{
			/* do nothing */
		}

	}

}

/***************************************************************************************************
 ** Function                 : ISOUDS_Rst

 ** Description              : Resets the ISOUDS parameters

 ** Parameter                : None

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_Rst (void)
{
	/* Reset the state to IDLE */
	ISOUDS_Conf.srvSt = (uint8)ISOUDS_IDLE;

	/* Reset the service ID to invalid */
	ISOUDS_Conf.srvId = (uint8)ISOUDS_IDNONE;

	/* Initialize Frame */
	ISOUDS_Conf.srvFrame = (uint8)ISOUDS_SINGLEFRAME;

	/* Reset the service index value to Invalid */
	ISOUDS_iTabIdx = (uint8)0xFF;

	/* Reset the response pending sent to ISOUDS_FALSE */
	ISOUDS_iStRespPendSnt = (uint8)ISOUDS_FALSE;

	/* Check if active session is not default session */
	if (ISOUDS_Sess != (uint8)ISOUDS_DS)
	{
		/* Start the S3 timer */
		ISOUDS_iTmrS3 = 1;
	}

	/* Positive response suppression bit */
	suppressPosRspMsgIndicationBit = ISOUDS_FALSE;

}

/***************************************************************************************************
 ** Function                 : ISOUDS_Mon

 ** Description              : Monitors the service distributor timers

 ** Parameter                : None

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_Mon (void)
{
	static uint8 counter = 0;

	/* Check if active session is not default session - timer will not run in Default session */
	if (ISOUDS_Sess != (uint8)ISOUDS_DS)
	{
		/* Check if timer S3 is running */
		if (ISOUDS_iTmrS3 > (uint32)0)
		{
			/* If Timer limit is reached */
			if (ISOUDS_iTmrS3 >= (uint32)ISOUDS_iTmrSTmin)
			{
				/* Switch to default session  */
				ISOUDS_Sess = (uint8)ISOUDS_DS;

				/* Stop timer S3 */
				ISOUDS_iTmrS3 = (uint32)0;

				/* Reset ISOUDS parameters */
				ISOUDS_Rst ();

				FLSHM_Init();

				ISOUDS_TrnsfrDaExit();

				// ISOUDS_ApplFlag=FALSE; Ehrich, removed
			}
			else
			{
				ISOUDS_iTmrS3 += ISOUDS_PERIOD_SCHED;
			}
		}


		// Enrico
		if( ISOUDS_RespAfterBoot )
		{
			// Safety counter, else we see WD resets. not sure why this is needed
			if( counter >= 16 )
			{
				static uint8 dataBuff[8];

				ISOUDS_RespAfterBoot = ISOUDS_FALSE;

				// Enrico: send pos reponse
				dataBuff[0] = 0x06; // Data length
				dataBuff[1] = 0x50; // ID
				dataBuff[2] = 0x02; // Prog Session
				dataBuff[3] = (uint8)(((uint16)ISOUDS_STDP2LIM) >> 8);
				dataBuff[4] = (uint8)ISOUDS_STDP2LIM;
				dataBuff[5] = (uint8)(((uint16)ISOUDS_NRC78P2MAXLIM) >> 8);
				dataBuff[6] = (uint8)ISOUDS_NRC78P2MAXLIM;
				dataBuff[7] = 0xAA;

				ISOTP_UDS_Cfg.dataPtr = &dataBuff[1];
				ISOTP_UDS_Cfg.dataLen = dataBuff[0];

				/* Request for transmission of positive response */
				ISOTP_TxRequest (&ISOTP_UDS_Cfg);
			}
			else
			{
				counter++;
			}
		}
	}

	/* Check if timer P2 is running */
	if (ISOUDS_iTmrP2 > (uint32)0)
	{
		/* If Timer limit is reached */
		if (ISOUDS_iTmrP2 >= ISOUDS_iTmrP2Lim)
		{
			/* Reset ISOUDS parameters */
			ISOUDS_Rst ();

			/* Stop timer P2 */
			ISOUDS_iTmrP2 = (uint32)0;
		}
		else
		{
			ISOUDS_iTmrP2 += ISOUDS_PERIOD_SCHED;
		}
	}

	/* Check if timer P2 is running */
	if (ISOUDS_TmrECURst > (uint32)0)
	{
		/* If Timer limit is reached */
		if (ISOUDS_TmrECURst >= 100)
		{
			/* Reset ISOUDS parameters */
			ISOUDS_Rst ();

			/* Stop timer P2 */
			ISOUDS_TmrECURst = (uint32)0;

			WDT_ResetImmediate();
		}
		else
		{
			ISOUDS_TmrECURst += ISOUDS_PERIOD_SCHED;
		}
	}

	ISOUDS_SAChkTimer();
}

/***************************************************************************************************
 ** Function                 : ISOUDS_ReqECUReset

 ** Description              : Request ECU Reset

 ** Parameter                : None

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_ReqECUReset (uint8 reset_type)
{
	/* Request ECU reset */
	ISOUDS_EcuRstReq = ISOUDS_TRUE;

	/* Get the Current Timer Value. */
	ISOUDS_TmrECURst = 1;

	/* Reset type */
	ECU_reset_type=reset_type;
}

/***************************************************************************************************
 ** Function                 : ISOUDS_SetBootSeqState

 ** Description              : Sets the Boot State

 ** Parameter                : None

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_SetBootSeqState (ISOUDS_BootSeqType BootSt)
{
	/* Sets the Boot State. */
	ISOUDS_BootState = BootSt;
}

/***************************************************************************************************
 ** Function                 : ISOUDS_CheckBootSeqState

 ** Description              : Checks the Boot State provided.

 ** Parameter                : None

 ** Return value             : None
 ***************************************************************************************************/
uint8 ISOUDS_CheckBootSeqState (ISOUDS_BootSeqType BootSt)
{
	uint8 ret;



	/* Check the Boot State. */
	if(ISOUDS_BootState == BootSt)
	{
		ret = ISOUDS_TRUE;
	}
	else
	{
		ret = ISOUDS_FALSE;
	}

	/* Return the Boot State. */
	return(ret);
}

/***************************************************************************************************
 ** Function                 : ISOUDS_EnterAppl

 ** Description              : Enters the Boot

 ** Parameter                : None

 ** Return value             : None
 ***************************************************************************************************/
void ISOUDS_EnterAppl (void)
{
	/* Jump to Startup Code of Application. */

	void (*JumpToApp)(void);

	uint32 *AppResetHandler = (uint32 *)FLSHM_APP_JUMP_ADDRESS;

	DISABLE_INTERRUPTS();


	JumpToApp = (void(*)())(AppResetHandler[1]);

	JumpToApp();

}

/***************************************************************************************************
 ** Function                 : ISOUDS_SetAccessParameters

 ** Description              : Set Access time Parameters

 ** Parameter                : None

 ** Return value             : None
 ***************************************************************************************************/
uint8 ISOUDS_SetAccessParameters (uint32 P2min, uint32 P2max, uint32 STmin)
{

	/* Set the Tmr Value Range. */
	ISOUDS_iTmrP2Min = (uint32)P2min;
	ISOUDS_iTmrP2Max = (uint32)P2max;
	ISOUDS_iTmrSTmin = (uint32)STmin;

	return(1);
}

/**************************** Internal Function definitions ***************************************/

/***************************************************************************************************
 ** Function                 : ISOUDS_iTxNegResp

 ** Description              : Transmits the negative response

 ** Parameter                : None

 ** Return value             : None
 ***************************************************************************************************/
static void ISOUDS_iTxNegResp (void)
{
	/* SID for negative response */
	ISOUDS_Buff[0] = (uint8)ISOUDS_NEGRESPSID;

	/* Updates the buffer with the SID of received frame */
	ISOUDS_Buff[1] = ISOUDS_Conf.srvId;

	/* Updates the Negative response code */
	ISOUDS_Buff[2] = ISOUDS_Conf.srvNegResp;

	/* Stop timer P2 */
	ISOUDS_iTmrP2 = (uint32)0;

	/* get data pointer */
	ISOTP_UDS_Cfg.dataPtr = &ISOUDS_Buff[0];

	/* get the length */
	ISOTP_UDS_Cfg.dataLen = ISOUDS_NEGRESPLEN;

	/* Request for transmission of negative response */
	ISOTP_TxRequest (&ISOTP_UDS_Cfg);
}

/***************************************************************************************************
 ** Function                 : ISOUDS_iTxRespPend

 ** Description              : Transmits the response pending message

 ** Parameter                : None

 ** Return value             : None
 ***************************************************************************************************/
static void ISOUDS_iTxRespPend (void)
{
	uint8 dataBuff[3];


	if ((ISOUDS_iTmrP2 > (uint32)ISOUDS_iTmrP2Min) ||
			(ISOUDS_iStRespPendSnt == (uint8)ISOUDS_FALSE))
	{
		/* SID for Negative Response */
		dataBuff[0] = (uint8)ISOUDS_NEGRESPSID;

		/*  SID of received frame */
		dataBuff[1] = ISOUDS_Conf.srvId;

		/*  Negative response code */
		dataBuff[2] = ISOUDS_Conf.srvNegResp;

		/* get data pointer */
		ISOTP_UDS_Cfg.dataPtr = &dataBuff[0];

		/* get the length */
		ISOTP_UDS_Cfg.dataLen = ISOUDS_NEGRESPLEN;

		/* Request for transmission of negative response */
		ISOTP_TxRequest (&ISOTP_UDS_Cfg);

		/* Assign P2* timer limit */
		ISOUDS_iTmrP2Lim = (uint32)ISOUDS_iTmrP2Max;

		/* Re-start timer P2 */
		ISOUDS_iTmrP2 = 1;

		/* change state to Transmit response pending */
		ISOUDS_Conf.srvSt = (uint8)ISOUDS_TXRESPPEND;

		/* Response pending Transmitted */
		ISOUDS_iStRespPendSnt = (uint8)ISOUDS_TRUE;
	}
	else
	{
		/* stay in Response pending state - Response pending already Transmitted */
		ISOUDS_Conf.srvSt = (uint8)ISOUDS_RESPPEND;
	}
}

uint8 ISOUDS_GetSessionStat(void)
{
	return ISOUDS_Sess;
}
