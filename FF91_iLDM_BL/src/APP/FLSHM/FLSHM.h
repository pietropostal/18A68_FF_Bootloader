/*****************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : FLSHM.h
** Module name  : FLSHM driver
** -------------------------------------------------------------------------------------------------
**
** Description : Include file of component FLSHM.c
**
** -------------------------------------------------------------------------------------------------
**
** Documentation reference :
**
****************************************************************************************************
** R E V I S I O N  H I S T O R Y
****************************************************************************************************
** V01.00 05/10/2019
** - Baseline Created
***************************************************************************************************/
/*To avoid multi-inclusions */
#ifndef _FLSHM_H_
#define _FLSHM_H_

#include "ISOUDS.h"

#define FLSHM_ZERO		0U
#define FLSHM_ONE		1U
#define FLSHM_EIGHT		8U

typedef struct  {
	uint8 chunk[64];
	uint32 chunk_len;
	uint64 bitlen;
	uint32 hash[8];
}sha256_control;

extern uint32 SHA_datalen;

typedef struct
{
	uint32					BlockStartAddress;
	uint32					BlockEndAddress;
	uint32					BlockValiFlgAdd;
}FLSHM_BlockInfo_t;

typedef struct
{
	uint32 CRC_32B;
	uint32 ImageSize;
	uint8 has_signature[32];
	uint8 ECU_mode;
}FLSHM_Valid_Header_t;

typedef enum
{
	 FLSHM_IDLE,
     FLSHM_ERASEFAILED,
	 FLSHM_VERFIYFAILED,
     FLSHM_PROGFAILED,
     FLSHM_SUCCESS,
     FLSHM_WRONGADDRESS,
     FLSHM_INPROGRESS
}FLSHM_ProgStat_t;

typedef enum
{
	FLASHMGR_IDLE		= 0,
	FLASHMGR_ERASE_REQ,
	FLASHMGR_ERASE,
	FLASHMGR_ERASE_DONE,
	FLASHMGR_PROGRAM,
	FLASHMGR_PROGRAM_DONE,
	FLASHMGR_VERIFY,
	FLASHMGR_VERIFY_DONE,
	FLASHMGR_VERIFY_FP,
	FLASHMGR_VERIFY_FP_DONE,
	FLASHMGR_VERIFY_MODE,
	FLASHMGR_VERIFY_MODE_DONE

}FLSHM_FlshMngrState_t;

typedef enum
{
	FLSHM_APPVALDN_IDLE,
	FLSHM_APPVALDN_REQ,
	FLSHM_APPVALDN_REQ_ACCEPT,
	FLSHM_APPVALDN_RUNNING,
	FLSHM_APPVLDN_FAIL,
	FLSHM_APPVLDN_PASS,
	FLSHM_APPATHRZN_IDLE,
	FLSHM_APPATHRZN_REQ,
	FLSHM_APPATHRZN_RUNNING,
	FLSHM_APPATHRZN_FAIL,
	FLSHM_APPATHRZN_PASS,
	FLSHM_DWNLD_VLDN_REQ,
	FLSHM_DWNLD_VLDN_RUNNING,
	FLSHM_DWNLD_VLDN_FAIL,
	FLSHM_DWNLD_VLDN_PASS,
	FLSHM_DWNLD_ATHRZN_REQ,
	FLSHM_DWNLD_ATHRZN_RUNNING,
	FLSHM_DWNLD_ATHRZN_FAIL,
	FLSHM_DWNLD_ATHRZN_PASS,
	FLSHM_CALVALDN_REQ,
	FLSHM_CALVALDN_RUNNING,
	FLSHM_CALVALDN_PASS,
	FLSHM_CALVALDN_FAIL,
	FLSHM_CALATHRZN_REQ,
	FLSHM_CALATHRZN_RUNNING,
	FLSHM_CALATHRZN_PASS,
	FLSHM_CALATHRZN_FAIL,
	FLSHM_MANUFT_MODE,
	FLSH_PRODUCT_MODE,
	
}FLSHM_AppVldnStat_t;

typedef enum
{
	PROG_FALSE,
	PROG_TRUE
}FLSHM_Prog_Stat_t;

#define NOT_STRUCK_IN_BOOTLOADER 0x00U
#define APPL_NOT_PRESENT 0x01U
#define APPL_CRC_FAILED 0x02U
#define CAL_CRC_FAILED 0x03U
#define UNATHUR_COMPONENT 0x04U
#define INVALID_BOOTLOADER 0x05U
#define UDS_COMMAND_TO_STAY_BOOTLOADER 0x06U


// Ehrich fixed size
#define TRANSFERDATA_BLOCKSIZE      4096U
//#define TRANSFERDATA_BLOCKSIZE      3072U

//#define FLSHM_ZERO					0U

#define MANFACTURING_MODE 	(0x01)
#define PRODUCTION_MODE 	(0x02)

extern uint8 SBC_InitStat;

/***************************************************************************************************
** Function         : FLSHM_Init

** Description      : Initializes the Flash manager

** Parameter        : None

** Return value     : None

** Remarks          : None
***************************************************************************************************/
EXTERN FUNC(void, FLSHM_CODE) FLSHM_Init(void);

/***************************************************************************************************
** Function         : FLSHM_FblTask

** Description      : Runs the Flash manger

** Parameter        : None

** Return value     : None

** Remarks          : None
***************************************************************************************************/
FUNC(void, FLSHM_CODE) FLSHM_FblTask(void);

/***************************************************************************************************
** Function         : FLSHM_ValidteReqAddress

** Description      : Validates the requested address

** Parameter        : Address	: Address to be validated from
					: Size		: Size from the requested address

** Return value     : None

** Remarks          : None
***************************************************************************************************/
EXTERN FUNC(uint8, FLSHM_CODE) FLSHM_ValidteReqAddress(VAR(uint32, AUTOMATIC) ValidateAddress,\
                                                                 VAR(uint32, AUTOMATIC) ValidateSize);

/***************************************************************************************************
** Function         : FLSHM_FindBlockIndx

** Description      : Validates the requested address

** Parameter        : None

** Return value     : None

** Remarks          : None
***************************************************************************************************/
EXTERN FUNC(uint8, FLSHM_CODE) FLSHM_FindBlockIndx(VAR(uint32, AUTOMATIC) BlockAddress, \
                                                                    VAR(uint32, AUTOMATIC) BlockSize);

/***************************************************************************************************
** Function         : FLSHM_EraseAppReq

** Description      : Requests flash manager to erase application

** Parameter        : FlashEraseAddress : Flash start address to be erased
** 					  FlashEraseSize	: Flash Size to be erased
** Return value     : FLSHM_ProgStat_t : Flash manager erase request state

** Remarks          : None
***************************************************************************************************/
EXTERN FUNC(FLSHM_ProgStat_t, FLASHM_CODE) FLSHM_EraseAppReq(VAR(uint32, FLASHM_DATA) FlashEraseAddress, \
                                                                  VAR(uint32, FLSHM_DATA) FlashEraseSize);

/***************************************************************************************************
** Function         : FLSHM_ProgramReq

** Description      : Requests flash manager to enter Programming state

** Parameter        : Address			: Flash address to be programmed
** 					  Size				: Flash Size to be programmed
** Return value     : FLSHM_ProgStat_t	: Flash manager erase request state

** Remarks          : None
***************************************************************************************************/
EXTERN  FUNC(FLSHM_ProgStat_t, FLSHM_CODE) FLSHM_ProgramReq(VAR(uint32, AUTOMATIC) ProgramngAddress, \
                                                                  VAR(uint32, AUTOMATIC) ProgramngSize);

/***************************************************************************************************
** Function         : FLSHM_StateMachine

** Description      : Flash manager state machine

** Parameter        : None
**
** Return value     : None

** Remarks          : None
***************************************************************************************************/
EXTERN FUNC(void,FLSHT_CODE)	FLSHM_StateMachine(void);

/***************************************************************************************************
** Function         : FLSHM_WritePacketReq

** Description      : Receives the packet and stores it in local buffer

** Parameter        : DwnldSeqCntr : Download sequence counter
** 					: SrcBuff : Source buffer where the data to be copied
** 					: len: Length of the data to be copied
**
** Return value     : None

** Remarks          : None
***************************************************************************************************/
EXTERN FUNC(FLSHM_ProgStat_t,FLSHT_CODE) FLSHM_WritePacketReq(uint16 DwnldSeqCntr, uint8 *SrcBuff, uint16 len);

/***************************************************************************************************
** Function                 : FLSHM_AppValdnStateMnger

** Description              : Flash manager Application validation state manager

** Parameter                : None

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
FUNC(void, FLSHM_CODE) FLSHM_AppValdnStateMnger(void);

/***************************************************************************************************
** Function                 : FLSHM_GetAppValdnStat

** Description              : Flash manager Get the application validation status

** Parameter                : None

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
EXTERN FUNC(FLSHM_AppVldnStat_t, FLSHM_CODE) FLSHM_GetAppValdnStat(void);

/***************************************************************************************************
** Function                 : FLSHM_StartDwnlValdn

** Description              : Flash manager Start validating the downloaded Image

** Parameter                : None

** Return value             : FLSHM_ProgStat_t

** Remarks                  : None
***************************************************************************************************/
EXTERN  FUNC(FLSHM_AppVldnStat_t, FLSHM_CODE) FLSHM_StartDwnlValdn(VAR(uint32, FLASHM_DATA) FlashStrtAddress, \
                                           VAR(uint32, FLSHM_DATA) FlashVldnSize, VAR(uint16, FLSHM_VAR) CRC_Val);

/***************************************************************************************************
** Function                 : FLSHM_ResetAppValdnStat

** Description              : Resets the CRC validation state to Idle

** Parameter                : None

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
EXTERN FUNC(void, FLSHM_CODE) FLSHM_ResetAppValdnStat(void);

/***************************************************************************************************
** Function                 : FLSHM_EcuResetRequest

** Description              : Flash ECU reset request 

** Parameter                : ResetFlag

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
EXTERN FUNC(void, FLSHM_CODE) FLSHM_EcuResetRequest(uint8 ResetFlag);

/***************************************************************************************************
** Function                 : FLSHM_GetCMDStatus

** Description              : Get Flash command status

** Parameter                : None

** Return value             : FLSHM_SUCCESS
**                              FLSHM_ERASEFAILED
**                              FLSHM_WRONGADDRESS

** Remarks                  : None
***************************************************************************************************/
EXTERN FUNC(FLSHM_ProgStat_t, FLSHM_CODE) FLSHM_GetCMDStatus(void);

/***************************************************************************************************
** Function                 : FLSHM_GetFlashState

** Description              : Get flash current state 

** Parameter                : None

** Return value             : FlashMgr_State

** Remarks                  : None
***************************************************************************************************/
EXTERN FUNC(FLSHM_FlshMngrState_t, FLSHM_CODE) FLSHM_GetFlashState(void);

/***************************************************************************************************
** Function                 : FLSHM_GetFlashLibState

** Description              : Get flash library current state

** Parameter                : None

** Return value             : FlashMgr_State

** Remarks                  : None
***************************************************************************************************/
EXTERN uint8 FLSHM_GetFlashLibState(void);

/***************************************************************************************************
** Function                 : FLSHM_StartDwnldAthrzn

** Description              : Flash manager start the component authorization after CRC validation success

** Parameter                : FlashStrtAddress,FlashAUTHsize,sig,sign_len

** Return value             : FLSHM_AppVldnStat_t type value

** Remarks                  : None
***************************************************************************************************/

FUNC(FLSHM_AppVldnStat_t, FLSHM_CODE) FLSHM_StartDwnldAthrzn(VAR(uint32, FLASHM_DATA) FlashStrtAddress,
                                 VAR(uint32, FLSHM_DATA) FlashAUTHsize, VAR(uint8, FLSHM_VAR) sig[],VAR(uint8, FLSHM_VAR)sign_len);
/***************************************************************************************************
** Function                 : FLSHM_SetMODE

** Description              : Flash manager set the ECU mode from manufacturing mode to Production mode

** Parameter                : ECUMODE

** Return value             : FLSHM_AppVldnStat_t type value

** Remarks                  : None
***************************************************************************************************/

EXTERN FUNC(FLSHM_AppVldnStat_t, FLSHM_CODE) FLSHM_SetMODE(VAR(uint8, FLASHM_DATA)ECUMODE);

/***************************************************************************************************
** Function                 : FLASHM_sha256_padding

** Description              : SHA256 algorithm padding api

** Parameter                :  ctr pointer of sha256_control type ,
**                             total_legth - total data length

** Return value             : FLSHM_AppVldnStat_t type value

** Remarks                  : None
***************************************************************************************************/

EXTERN FUNC(void, FLSHM_CODE) FLASHM_sha256_padding(sha256_control *ctr,uint32 total_legth);
/***************************************************************************************************
** Function                 : FLSHM_CreateSignature

** Description              : Creates the hash signature of given data or address

** Parameter                :  HashStrtAddress - NVM memory start address for hash signature,
**                             HashSize -slot size
**                             signature- data pointer for hash signature
**                             Hashtotal_size - total data length

** Return value             : none

** Remarks                  : None
***************************************************************************************************/
EXTERN  FUNC(void, FLSHM_CODE) FLSHM_CreateSignature(uint32 HashStrtAddress, uint32 HashSize,\
                                                        sha256_control *signature,uint32 Hashtotal_size);

/***************************************************************************************************
** Function                 : FLASHM_sha256_init

** Description              : Initialise the SHA algorithm

** Parameter                :  ctr pointer of sha256_control type,

** Return value             : none

** Remarks                  : None
***************************************************************************************************/
EXTERN FUNC(void, FLSHM_CODE) FLASHM_sha256_init(sha256_control *ctr);

/***************************************************************************************************
** Function                 : FLASHM_sha256_computation

** Description              : main function of SHA algorithm

** Parameter                :  ctr pointer of sha256_control type,

** Return value             : none

** Remarks                  : None
***************************************************************************************************/
EXTERN FUNC(void, FLSHM_CODE) FLASHM_sha256_computation(sha256_control  *ctr);

/***************************************************************************************************
** Function                 : FLSHM_GetAppFP

** Description              : get the calculated hash signature of DATA

** Parameter                :  pointer of FLASHM_sig_ptr,pointer of SIGnatre

** Return value             : none

** Remarks                  : None
***************************************************************************************************/
EXTERN FUNC(void, FLSHM_CODE) FLSHM_GetAppFP(uint8 *FLASHM_sig_ptr,sha256_control *SIGnatre);

#endif	/* FLSHM_H */
