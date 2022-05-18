 /***************************************************************************************************
  ** Copyright (c) 2019 EMBITEL
  **
  ** This software is the property of EMBITEL.
  ** It can not be used or duplicated without EMBITEL authorization.
  **
  ** -------------------------------------------------------------------------------------------------
  ** File Name    : FLSHM.c
  ** Module name  : FLSH Manager
  ** -------------------------------------------------------------------------------------------------
  **
  ** Description : FLASHM Initialize, Read , Write and Erase functions
  **
  ** -------------------------------------------------------------------------------------------------
  **
  ** Documentation reference :
  **
  ****************************************************************************************************
  ** R E V I S I O N  H I S T O R Y
  ****************************************************************************************************
  ** V01.00 05/08/2019
  ** - Baseline Created
  ***************************************************************************************************/

 /************************************** Inclusion files *******************************************/
 #include "Flash.h"
 #include "FLSHM.h"
 #include "WDT.h"
 #include "FLSHM_Cfg.h"
 #include "UJA1075A.h"

 /********************************** Component configuration ***************************************/

 /********************************* Declaration of local functions *********************************/
 STATIC FUNC(FLSHM_ProgStat_t,FLSHT_CODE)	FLSHM_ProgrammMain(void);
 FUNC(FLSHM_ProgStat_t, FLSHM_CODE) Flash_ProgramApp(uint32  *PrgDst, uint8 *PrgSrc, uint16 PrgChunksize);
 STATIC FUNC(void,FLSHT_CODE)	FLSHM_ClearBuff(uint8 *Buff, uint16 size);
 STATIC FUNC(void, FLSHM_CODE) FLSHM_CalcCRC(uint32 CRCVldnAddress, uint32 CRCVldnsize);
 STATIC FUNC(FLSHM_ProgStat_t, FLSHM_CODE) FLSHM_UpdateAppValdnHdr(uint8 VldnBlock, uint32 BlkRxdCRC,
                                                                 uint32 VldnBlkSize,uint8 BlkFP[],uint8 BlkecuMODE);
 FUNC(void, FLSHM_CODE) FLSHM_JumpToApp(void);
 STATIC FUNC(void, FLSHM_CODE) FLSHM_ComputeCRC(uint8 *CRCDataBuffer, uint32 CRCdatalen);
 STATIC FUNC(void, FLSHM_CODE) FLSHM_GetAppCRC(void);
 STATIC FUNC(void, FLSHM_CODE) FLSHM_GetECUmode(void);
 STATIC FUNC(void, FLSHM_CODE) FLSHM_StartCalValdn(void);
 STATIC FUNC(void, FLSHM_CODE) FLSHM_StartCalAthrzn(void);
 STATIC FUNC(void, FLSHM_CODE) FLSHM_StartAppAthrzn(void);
 STATIC FUNC(void, FLSHM_CODE) FLSHM_StartAppValdn(void);


 /************************** Declaration of local symbol and constants *****************************/

 /********************************* Declaration of local macros ************************************/

 /********************************* Declaration of local types *************************************/

 /******************************* Declaration of local variables ***********************************/
 /* Start and end address for Erase request */
 STATIC VAR(uint32, FLSHM_VAR)					FLSHM_EraseStartAddress;
 STATIC VAR(uint32, FLSHM_VAR)					FLSHM_EraseEndAddress;
 /* Start and end address for Program request */
 STATIC VAR(uint32, FLSHM_VAR)					FLSHM_ProgStartAddress;
 STATIC VAR(uint32, FLSHM_VAR)					FLSHM_ProgCurrntAddress;
 STATIC VAR(uint32, FLSHM_VAR)					FLSHM_ProgEndAddress;
 /* Validation request information */
 STATIC VAR(uint32, FLSHM_VAR)					FLSHM_VldnSize;
 STATIC VAR(FLSHM_AppVldnStat_t, FLSHM_VAR)		FLSHM_ValdnState;
 STATIC VAR(uint32, FLSHM_VAR)					FLSHM_AthrznSize;
 STATIC VAR(FLSHM_Valid_Header_t, FLSHM_VAR)	FLSHM_ValidHeadVal;
 /* Assuming number of blocks could be less that 256 */
 STATIC VAR(uint8, FLSHM_VAR)					FLSHM_ValidnBlk;

 /* Stores the calculated CRC */
 STATIC VAR(uint16, FLSHM_VAR)					FLSHM_CalctdCRC;
 /* Validation memory pointer */
 STATIC VAR(uint32, FLSHM_VAR)					FLSHM_ValdnCurrAddress;
 /* Start block requested to erase */
 VAR(uint32, FLSHM_VAR)							FLSHM_EraseStartBlock;
 /* End block requested to erase */
 VAR(uint32, FLSHM_VAR)							FLSHM_EraseEndBlock;
 /* Erase block counter */
 VAR(uint32, FLSHM_VAR)							FLSHM_ErasCurrAddress;

 /* Flash manager State */
 STATIC VAR(FLSHM_FlshMngrState_t, FLSHM_VAR)	FLSHM_FlshMngrState;
 /* Program buffer */
 STATIC VAR(uint8, FLSHM_VAR) 				FLSHM_ProgramBuff[TRANSFERDATA_BLOCKSIZE];
 /* Flash to indicate program buffer is full */
 STATIC VAR(FLSHM_Prog_Stat_t, FLSHM_VAR) 	FLSHM_ProgramBuff_Full;
 /* Download sequence counter */
 STATIC VAR(uint16, FLSHM_VAR)				Flash_DwnldSeqCntr;
 STATIC VAR(uint16, FLSHM_VAR)				FlshMWriteReqSize;
 STATIC VAR(uint16, FLSHM_VAR)				FlshMWriteReqOddValues;

 /* Flash command status */
 STATIC	VAR(FLSHM_ProgStat_t, FLSHM_VAR)	FLSHM_CmdStat;

 STATIC CONST(FLSHM_BlockInfo_t, FLSHM_VAR)	FLSHM_BlockInfo[FLSHM_NUM_OF_BLOCKS] = {FLSHM_LOGICAL_BLK_TAB};

 /* Stores the current block being downloaded */
 STATIC VAR(uint8, FLSHM_VAR)				FLSHM_CurrentBlock;

 STATIC VAR(uint16, FLSHM_VAR) FLSHM_BootPwrUpDly = FLSHM_ZERO;
 /*Application CRC*/
 STATIC VAR( uint32,FLSHM_VAR)   AppCRC = FLSHM_ZERO;

 VAR(sha256_control,FLSHM_VAR)     FLASHM_ctr;
 VAR(uint32 ,FLSHM_VAR)            SHA_datalen=FLSHM_ZERO;
 VAR(uint8, FLSHM_VAR)             FLASHM_sig_bytes[32U];
 VAR(uint8 ,FLSHM_VAR)             FLSHM_ECUmode = MANFACTURING_MODE; // enrico set default
 VAR(uint8 ,FLSHM_VAR)             bootloader_struck_reason;

 VAR(uint8 ,FLSHM_VAR)             SBC_InitStat;


 /******************************* Declaration of local constants ***********************************/

 /****************************** Declaration of exported variables *********************************/

 /****************************** Declaration of exported constants *********************************/

 /***************************************************************************************************
  **                                      FUNCTIONS                                                 **
  ***************************************************************************************************/

 /***************************************************************************************************
  ** Function         : FLSHM_Init

  ** Description      : Initializes the Flash manager

  ** Parameter        : None

  ** Return value     : None

  ** Remarks          : None
  ***************************************************************************************************/
 FUNC(void, FLSHM_CODE) FLSHM_Init(void)
 {
  VAR(uint16, AUTOMATIC) index;

  /* Initialize the state manger states */
  FLSHM_FlshMngrState 		= FLASHMGR_IDLE;

  /* Initialize the Erase address */
  FLSHM_EraseStartAddress		= FLSHM_BlockInfo[FLSHM_ZERO].BlockStartAddress;
  FLSHM_EraseEndAddress		= FLSHM_BlockInfo[FLSHM_ZERO].BlockEndAddress;

  /* Initialize the Program start address */
  FLSHM_ProgStartAddress		= FLSHM_BlockInfo[FLSHM_ZERO].BlockStartAddress;
  FLSHM_ProgEndAddress		= FLSHM_BlockInfo[FLSHM_ZERO].BlockEndAddress;

  /* Clear the program buffer */
  for (index = FLSHM_ZERO; index < TRANSFERDATA_BLOCKSIZE; index++)
  {
   FLSHM_ProgramBuff[index] = FLSHM_ZERO;
  }

  /* Clear the buffer full status */
  FLSHM_ProgramBuff_Full = PROG_FALSE;

  /* Reset download sequence counter */
  Flash_DwnldSeqCntr		= FLSHM_ZERO;

  /* Current flash block pointer */
  FLSHM_CurrentBlock = FLSHM_ZERO;

  /* Flash command status */
  FLSHM_CmdStat = FLSHM_IDLE;

  FLSHM_ValdnState = /*FLSHM_DWNLD_VLDN_PASS*/FLSHM_APPVALDN_IDLE;

  // init ECU mode
  FLSHM_ECUmode = ((uint8 *) ECU_MODE_ADDR)[0];
  if( (FLSHM_ECUmode != PRODUCTION_MODE) || (FLSHM_ECUmode != MANFACTURING_MODE) )
  {
	  FLSHM_ECUmode = MANFACTURING_MODE;
  }

  AppCRC = FLSHM_ZERO;

  bootloader_struck_reason=INVALID_BOOTLOADER;

  //SBC_InitStat = FALSE;
  }


 /**
  * Used to jump to the entry point of the user application
  *
  *
  */
 void JumpToUserApplication( unsigned int userSP,  unsigned int userStartup)
 {
 	/* Check if Entry address is erased and return if erased */
 	if(userSP == 0xFFFFFFFF){
 		return;
 	}

 	/* Set up stack pointer */
 	__asm("msr msp, r0");
 	__asm("msr psp, r0");

 	/* Relocate vector table */
 	S32_SCB->VTOR = (uint32_t)FLSHM_APP_JUMP_ADDRESS;

 	/* Jump to application PC (r1) */
 	__asm("mov pc, r1");
 }

 /***************************************************************************************************
  ** Function         : FLSHM_JumpToApp

  ** Description      : Jumps to the application startup

  ** Parameter        : None

  ** Return value     : None

  ** Remarks          : None
  ***************************************************************************************************/
 FUNC(void, FLSHM_CODE) FLSHM_JumpToApp(void)
 {
	 // Enrico changed
  //void (*JumpToApp)(void);

  //uint32 *AppResetHandler = (uint32 *)FLSHM_APP_JUMP_ADDRESS;

  DISABLE_INTERRUPTS();

  //JumpToApp = (void(*)())(AppResetHandler[1]);
  //JumpToApp();


  JumpToUserApplication(*((uint32_t*)FLSHM_APP_JUMP_ADDRESS), *((uint32_t*)(FLSHM_APP_JUMP_ADDRESS + 4)));

  }



 /***************************************************************************************************
  ** Function         : FLSHM_FblTask

  ** Description      : Runs the Flash manger

  ** Parameter        : None

  ** Return value     : None

  ** Remarks          : None
  ***************************************************************************************************/
 FUNC(void, FLSHM_CODE) FLSHM_FblTask(void)
 {
  FLSHM_AppVldnStat_t ValidStat;

  /* Schedules the flash manager */
  FLSHM_StateMachine();

  // Enrico removed
#if 0
  /* Check if the boot-up delay is finished & in Default session*/
  if ((ISOUDS_DS == ISOUDS_GetSessionStat()) && (FLSHM_BootPwrUpDly >= BOOTUP_DELAY))
  {
   /* Get the Application validation state */
   ValidStat = FLSHM_GetAppValdnStat();


   /* To perform validity only once */
   if (FLSHM_APPVALDN_IDLE == ValidStat)
   {
    /* Start the CRC validation */
    FLSHM_StartAppValdn();
   }
   /* Validation success */
   else if (FLSHM_APPVLDN_PASS == ValidStat)
   {
    /* Application verified, start app authorization */
    FLSHM_StartAppAthrzn();
    
   }
   /* Application authorized, start cal validation */
   else if (FLSHM_APPATHRZN_PASS == ValidStat)
   {
     FLSHM_StartCalValdn();
   
   }
    /* calibration verified, start cal authorization */
   else if (FLSHM_CALVALDN_PASS == ValidStat)
   {
    
    FLSHM_StartCalAthrzn();
    
   }
   /* calibration authorized, jump now */
   else if (FLSHM_CALATHRZN_PASS == ValidStat)
   {
	bootloader_struck_reason=NOT_STRUCK_IN_BOOTLOADER;
     
	// Enrico removed
    //FLSHM_JumpToApp();
   }
   /* Application verification failed */
   else if (FLSHM_CALVALDN_FAIL == ValidStat)
   {
    /* calibration data is invalid continue Bootloader in Default session */
   }
  }
  else
  {
   /* Do nothing */
  }
#endif

  FLSHM_BootPwrUpDly++;
 }

 /***************************************************************************************************
  ** Function         : FLSHM_ValidteReqAddress

  ** Description      : Validates the requested address

  ** Parameter        : Address	: Address to be validated from
      : Size		: Size from the requested address

  ** Return value     : None

  ** Remarks          : None
  ***************************************************************************************************/
 FUNC(uint8, FLSHM_CODE) FLSHM_ValidteReqAddress(VAR(uint32, AUTOMATIC) ValidateAddress, \
                                                                   VAR(uint32, AUTOMATIC) ValidateSize)
 {
  uint8 BlkValidty = FALSE;
  uint8 LoopIndx = FLSHM_ZERO;

  /* Till the last logical block */
  for (LoopIndx = FLSHM_ZERO; LoopIndx < FLSHM_NUM_OF_BLOCKS; LoopIndx++)
  {
   /* Check if the requested size if within the range */
   if ((FLSHM_BlockInfo[LoopIndx].BlockStartAddress == ValidateAddress) &&
     ((FLSHM_BlockInfo[LoopIndx].BlockEndAddress) >= (ValidateAddress + ValidateSize - FLSHM_ONE)))
   {
    /* VValidation success */

    BlkValidty = TRUE;
    break;
   }
  }

  return BlkValidty;
  }

 /***************************************************************************************************
  ** Function         : FLSHM_FindBlockIndx

  ** Description      : Validates the requested address

  ** Parameter        : None

  ** Return value     : None

  ** Remarks          : None
  ***************************************************************************************************/
 FUNC(uint8, FLSHM_CODE) FLSHM_FindBlockIndx(VAR(uint32, AUTOMATIC) BlockAddress, VAR(uint32, AUTOMATIC) BlockSize)
 {
  uint8 BlkIndx = FLSHM_ZERO;
  uint8 LoopIndx = FLSHM_ZERO;

  /* Till the last logical block */
  for (LoopIndx = FLSHM_ZERO; LoopIndx < FLSHM_NUM_OF_BLOCKS; LoopIndx++)
  {
   /* Check if the requested address within the range */
   if ((FLSHM_BlockInfo[LoopIndx].BlockStartAddress <= BlockAddress) &&
     ((FLSHM_BlockInfo[LoopIndx].BlockEndAddress) >= (BlockAddress + BlockSize - FLSHM_ONE)))
   {
    /* Block index found */
    BlkIndx = LoopIndx;
    break;
   }
  }

  return BlkIndx;
  }

 /***************************************************************************************************
  ** Function         : FLSHM_EraseAppReq

  ** Description      : Requests flash manager to erase application

  ** Parameter        : FlashEraseAddress : Flash start address to be erased
  ** 					  FlashEraseSize	: Flash Size to be erased
  ** Return value     : FLSHM_ProgStat_t : Flash manager erase request state

  ** Remarks          : None
  ***************************************************************************************************/
 FUNC(FLSHM_ProgStat_t, FLASHM_CODE) FLSHM_EraseAppReq(VAR(uint32, FLASHM_DATA) FlashEraseAddress,\
                                                                   VAR(uint32, FLSHM_DATA) FlashEraseSize)
  {
  VAR(FLSHM_ProgStat_t, AUTOMATIC) retVal 	= FLSHM_INPROGRESS;

  /* Validate the address requested */
  if (FLSHM_ValidteReqAddress(FlashEraseAddress, FlashEraseSize) == TRUE)
  {
   /* Copy the erase start address requested */
   FLSHM_EraseStartAddress	= FlashEraseAddress;

   /* Copy the erase end address requested */
   FLSHM_EraseEndAddress	= (FlashEraseAddress+FlashEraseSize-1u);

   /* Erase in progress */
   FLSHM_CmdStat	= FLSHM_INPROGRESS;

   /* Change to erase requested */
   FLSHM_FlshMngrState		= FLASHMGR_ERASE_REQ;
  }
  else
  {
   /* Erase address requested in invalid */
   retVal = FLSHM_VERFIYFAILED;
  }

  return retVal;
  }

 /***************************************************************************************************
  ** Function         : FLSHM_ProgramReq

  ** Description      : Requests flash manager to enter Programming state

  ** Parameter        : Address			: Flash address to be programmed
  ** 					  Size				: Flash Size to be programmed
  ** Return value     : FLSHM_ProgStat_t	: Flash manager erase request state

  ** Remarks          : None
  ***************************************************************************************************/
 FUNC(FLSHM_ProgStat_t, FLSHM_CODE) FLSHM_ProgramReq(VAR(uint32, AUTOMATIC) ProgramngAddress, \
                                                                  VAR(uint32, AUTOMATIC) ProgramngSize)
 {
  VAR(FLSHM_ProgStat_t, AUTOMATIC) retVal 	= FLSHM_INPROGRESS;

  /* Validate the id the address requested  is application*/
  if (FLSHM_ValidteReqAddress(ProgramngAddress, ProgramngSize) == TRUE)
  {
   /* Check if erase already done */
   if (FLASHMGR_ERASE_DONE == FLSHM_FlshMngrState)
   {
    FLSHM_CurrentBlock = FLSHM_FindBlockIndx(ProgramngAddress, ProgramngSize);

    /* Copy the Program start address requested */
    FLSHM_ProgStartAddress	= ProgramngAddress;

    FLSHM_ProgCurrntAddress = ProgramngAddress;

    /* Copy the Program end address requested */
    FLSHM_ProgEndAddress	= (ProgramngAddress + ProgramngSize);

    /* Reset download sequence counter */
    Flash_DwnldSeqCntr		= FLSHM_ZERO;

    /* Program in progress */
    FLSHM_CmdStat = FLSHM_INPROGRESS;
    /* Change to Program memory */
    FLSHM_FlshMngrState		= FLASHMGR_PROGRAM;
   }
   else
   {
    /* Erase is not performed */
    retVal = FLSHM_VERFIYFAILED;
   }
  }
  else
  {
   /* ?oInvalid address requested */
   retVal = FLSHM_VERFIYFAILED;
  }

  return retVal;
  }

 /***************************************************************************************************
  ** Function         : FLSHM_StateMachine

  ** Description      : Flash manager state machine

  ** Parameter        : None
  **
  ** Return value     : None

  ** Remarks          : None
  ***************************************************************************************************/
 FUNC(void,FLSHT_CODE)	FLSHM_StateMachine(void)
 {
  VAR(uint8, AUTOMATIC) StateReturn_Val;


  /* Switch to Flash Manager state */
  switch (FLSHM_FlshMngrState)
  {
  /* Flash Manager Idle */
  case FLASHMGR_IDLE:
  {
   /* Do nothing */
   break;
  }
  /* Flash erase requested */
  case FLASHMGR_ERASE_REQ:
  {
   /* Get Erase block number */
	  FLSHM_ErasCurrAddress	= FLSHM_EraseStartAddress;

   /* store the erase start block */
	//  FLSHM_EraseStartBlock	= (uint32)Flash_GetMemSec(FLSHM_EraseStartAddress);
   /* store the erase end block */
   FLSHM_EraseEndBlock		= (uint32)Flash_GetMemSec(FLSHM_EraseEndAddress);

   FLSHM_FlshMngrState = FLASHMGR_ERASE;

   break;
  }
  /* Erase the Flash */
  case FLASHMGR_ERASE:
  {
   /* Till the erase request last block */
   if (FLSHM_ErasCurrAddress <= FLSHM_EraseEndAddress)
   {
    /* Erase the requested block */
    StateReturn_Val = (uint8)FLASH_DRV_EraseSector(FLSHM_ErasCurrAddress, FEATURE_FLS_PF_BLOCK_SECTOR_SIZE);

    /* Erase status */
    if (STATUS_SUCCESS == StateReturn_Val)
    {
     /* Erase success, Point to next block */
    	FLSHM_ErasCurrAddress += FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;
    }
    else
    {
     /* Erase failed */
     FLSHM_CmdStat = FLSHM_ERASEFAILED;
     FLSHM_FlshMngrState = FLASHMGR_IDLE;
    }
   }
   else
   {
    /* Erase is successful */
    FLSHM_CmdStat = FLSHM_SUCCESS;
    FLSHM_FlshMngrState = FLASHMGR_ERASE_DONE;
   }
   break;
  }
  /* Erase is successful */
  case FLASHMGR_ERASE_DONE:
  {
   /* Do nothing, Expecting Request download */
   break;
  }
  case FLASHMGR_VERIFY_FP_DONE:
  {
	  break;
  }
  /* Flash programming state */
  case FLASHMGR_PROGRAM:
  {
   /* Program main schedule */
   FLSHM_CmdStat = FLSHM_ProgrammMain();

   /* Program status */
   if ((FLSHM_SUCCESS == FLSHM_CmdStat) || (FLSHM_INPROGRESS == FLSHM_CmdStat))
   {
    /* Flash success */
    FLSHM_CmdStat = FLSHM_SUCCESS;
   }
   else
   {
    /* Program error */
    FLSHM_FlshMngrState = FLASHMGR_IDLE;
   }
   break;
  }
  case FLASHMGR_PROGRAM_DONE:
  {
   /* Programming done, Waiting for Validation */
   FLSHM_FlshMngrState = FLASHMGR_IDLE;
   break;
  }
  case FLASHMGR_VERIFY_DONE:
  {
   /* Programming done, Waiting for Validation */
   break;
  }

  case FLASHMGR_VERIFY:
  {
   /* Application downloaded image validation pass */
   if (FLSHM_DWNLD_VLDN_PASS == FLSHM_GetAppValdnStat())
   {

    /* Flash success */
    FLSHM_FlshMngrState = FLASHMGR_VERIFY_DONE;
   }
   /* Application downloaded image validation pass */
   else if(FLSHM_DWNLD_VLDN_FAIL== FLSHM_GetAppValdnStat())
   {
       FLSHM_FlshMngrState = FLASHMGR_IDLE;
   }
   else if(FLSHM_DWNLD_VLDN_RUNNING != FLSHM_GetAppValdnStat())
   {
    /* Validation Not running */
    FLSHM_FlshMngrState = FLASHMGR_IDLE;
   }
   else
   {

   }
   break;
  }
  case FLASHMGR_VERIFY_FP:
  {
   if (FLSHM_DWNLD_ATHRZN_PASS == FLSHM_GetAppValdnStat())
   {
    /* Update the Validation header */
      if( FLSHM_ECUmode!=MANFACTURING_MODE)
      {

	    FLSHM_UpdateAppValdnHdr(FLSHM_CurrentBlock, FLSHM_CalctdCRC, \
	    FLSHM_ValidHeadVal.ImageSize/*(FLSHM_ProgEndAddress-FLSHM_ProgStartAddress)*/,FLASHM_sig_bytes,FLSHM_ECUmode);
	    FLSHM_FlshMngrState = FLASHMGR_IDLE;
      }
      else
      {
    	FLSHM_FlshMngrState = FLASHMGR_VERIFY_FP_DONE;
      }


    /* Validation inprogress */
   } else if(FLSHM_DWNLD_ATHRZN_FAIL== FLSHM_GetAppValdnStat())
   {
	   FLSHM_EraseAppReq(FLSHM_ProgStartAddress,(FLSHM_ProgEndAddress-FLSHM_ProgStartAddress));

   }
   else if(FLSHM_DWNLD_ATHRZN_RUNNING != FLSHM_GetAppValdnStat())
   {
    /* Validation Not running */
    FLSHM_FlshMngrState = FLASHMGR_IDLE;
   }
   else
   {

   }

   break;
  }

  case FLASHMGR_VERIFY_MODE:
   {
    if (FLSH_PRODUCT_MODE == FLSHM_GetAppValdnStat())
    {

     /* Update the Validation header */
    	FLSHM_UpdateAppValdnHdr(FLSHM_CurrentBlock, FLSHM_CalctdCRC, \
    			FLSHM_ValidHeadVal.ImageSize/*(FLSHM_ProgEndAddress-FLSHM_ProgStartAddress)*/,FLASHM_sig_bytes,FLSHM_ECUmode);

     /* Flash success */
     FLSHM_FlshMngrState = FLASHMGR_IDLE;

     /* Validation in progress */
    } else
    {
     /* Flash failed */
     FLSHM_FlshMngrState = FLASHMGR_IDLE;
    }



    break;
   }
  default :
  {
   /* Reset the flash manager */
   FLSHM_FlshMngrState = FLASHMGR_IDLE;
   break;
  }
  }
  }

 /***************************************************************************************************
  ** Function         : Flash_ProgramApp

  ** Description      : Programs the application code if packet is received

  ** Parameter        : Dst : Destination address to be programmed
  ** 					  Src : Source address of data to be programmed
  ** 					  Chunksize: Size of the Block to be programmed
  **
  ** Return value     : None

  ** Remarks          : None
  ***************************************************************************************************/
 FUNC(FLSHM_ProgStat_t, FLSHM_CODE) Flash_ProgramApp(uint32  *PrgDst, uint8 *PrgSrc, uint16 PrgChunksize)
 {
  FLSHM_ProgStat_t	ret_p = FLSHM_SUCCESS;
  uint8 Prgretval = 0;
  uint32 PrgStrtaddress;
  uint8 *PrgSource;
  uint16 Prgsize_t;
  PrgStrtaddress = (uint32)PrgDst;
  PrgSource = PrgSrc;
  Prgsize_t = PrgChunksize;
  /* Validate the Address */
  if((PrgStrtaddress >= (uint32)FLSHM_BlockInfo[FLSHM_CurrentBlock].BlockStartAddress) &&\
                (PrgStrtaddress <= (uint32)(FLSHM_BlockInfo[FLSHM_CurrentBlock].BlockEndAddress)))  /* Application Range */
  {
   /* Write the requested chunk of data */
   /* Write the requested chunk of data */
   Prgretval = FLASH_DRV_Program((uint32)PrgStrtaddress, Prgsize_t, PrgSource);

   /* Enable the global interrupts */

   /*Flash write status */
   if (Prgretval == STATUS_SUCCESS)
   {
    /* Flash write success */
    ret_p = FLSHM_SUCCESS;

   }
   else
   {
    /* Flash write failed */
    ret_p = FLSHM_PROGFAILED;
   }
  }
  else
  {
   /* Invalid address write request */
   ret_p = FLSHM_WRONGADDRESS;
  }

  return ret_p;
 }

 /***************************************************************************************************
  ** Function         : FLSHM_ProgrammMain

  ** Description      : Polls for the new packet arrival for Application programming

  ** Parameter        : None
  **
  ** Return value     : FLSHM_ProgStat_t : Flash manager Status

  ** Remarks          : None
  ***************************************************************************************************/
 STATIC FUNC(FLSHM_ProgStat_t,FLSHM_CODE)	FLSHM_ProgrammMain(void)
 {
  FLSHM_ProgStat_t retVal_m;


  FLSHM_ProgStat_t ret_m = FLSHM_INPROGRESS;

  /* Check if the program buffer is filled */
  if (PROG_TRUE == FLSHM_ProgramBuff_Full)
  {
	/* Program the chunk of data */
	retVal_m = Flash_ProgramApp((uint32  *)FLSHM_ProgCurrntAddress, (uint8 *)FLSHM_ProgramBuff, FlshMWriteReqSize);

	/* Flash status */
	if(retVal_m != FLSHM_SUCCESS)
	{
		/* Program failed */
		ret_m = FLSHM_PROGFAILED;
	}
	else
	{
		/* Point the next flash chunk */
		FLSHM_ProgCurrntAddress += FlshMWriteReqSize;

		/* Program failed */
		ret_m = FLSHM_SUCCESS;
	}

	/* Check if program request is completed  */
	if ((uint32)FLSHM_ProgCurrntAddress >= (uint32)FLSHM_ProgEndAddress)
	{
	FLSHM_FlshMngrState = FLASHMGR_PROGRAM_DONE;
	}

	/* Clear the program buffer */
	// Enrico removed clear to keep Odd Values!!
	//FLSHM_ClearBuff(FLSHM_ProgramBuff, TRANSFERDATA_BLOCKSIZE);

	/* Clear the buffer full flag */
	FLSHM_ProgramBuff_Full = PROG_FALSE;
  }
  else
  {
   /* Do nothing .. download in progress */
  }

  return ret_m;
 }

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
 FUNC(FLSHM_ProgStat_t,FLSHT_CODE) FLSHM_WritePacketReq(uint16 DwnldSeqCntr, uint8 *SrcBuff, uint16 len)
 {
  uint8 *dstPtr = FLSHM_ProgramBuff;
  uint16 lent, i;

  // Enrico fixed return in case is still busy
  if( PROG_FALSE != FLSHM_ProgramBuff_Full )
	  return FLSHM_INPROGRESS;

  // Enrico Reset on first package
  if( 1u == DwnldSeqCntr )
  {
	  FlshMWriteReqOddValues = 0u;
	  FlshMWriteReqSize = 0u;
  }

  // Enrico invited OddValues to align flashing
  // copy odd values from old location
  for( i=0; i<FlshMWriteReqOddValues; i++)
  {
	  *dstPtr++ = FLSHM_ProgramBuff[FlshMWriteReqSize + i];
  }

  /* Read the length */
  lent = len;
  /* Run till the length */
  while(lent != FLSHM_ZERO)
  {
   /* Copy the data byte */
   *dstPtr++ = *SrcBuff++;
   lent--;
  }

  /* Save the download sequence counter */
  Flash_DwnldSeqCntr++;

  // Enrico invited OddValues to align flashing
  FlshMWriteReqSize = len + FlshMWriteReqOddValues;
  FlshMWriteReqOddValues = FlshMWriteReqSize % FLSHM_EIGHT;
  FlshMWriteReqSize -= FlshMWriteReqOddValues;

  /* Indicate packet is received */
  FLSHM_ProgramBuff_Full = PROG_TRUE;


  /* REturn packet is received */
  return FLSHM_SUCCESS;
 }


 /***************************************************************************************************
  ** Function         : FLSHM_ClearBuff

  ** Description      : Clears the buffer

  ** Parameter        : Buff: Buffer to be cleared
  ** 					: size: Size of the buffer
  **
  ** Return value     : None

  ** Remarks          : None
  ***************************************************************************************************/
 STATIC FUNC(void,FLSHT_CODE)	FLSHM_ClearBuff(uint8 *Buff, uint16 size)
 {
  /* Run till the size */
  while(size > FLSHM_ZERO)
  {
   /* Clear the byte */
   *Buff++ = FLSHM_ZERO;
   size--;
  }
 }

 /***************************************************************************************************
  ** Function         : FLSHM_CalcCRC

  ** Description      : Calculates the CRC

  ** Parameter        : Address : From where the CRC to be calculated
  **
  ** Return value     : None

  ** Remarks          : None
  ***************************************************************************************************/
 STATIC FUNC(void, FLSHM_CODE) FLSHM_CalcCRC(uint32 CRCVldnAddress, uint32 CRCVldnsize)
 {
  /* Temporary storage buffer */
  uint8 FLSHM_TempBuf[FLSHM_CRC_CALSLOT_SIZE];
  
  /* Temporary storage buffer index */  
  uint16 FLASHM_TempBuffIdx;
  
  /* Temporary storage pointer */
  uint8   * CRC_Pntr;
  
  /* Copy the data from validation block start address */
  for(FLASHM_TempBuffIdx=0U;FLASHM_TempBuffIdx<CRCVldnsize;FLASHM_TempBuffIdx++)
  {
	
  /* Extract byte data from validation block start address */
   CRC_Pntr = (uint8   *)CRCVldnAddress++;
   
   /* Copy the data to temporary buffer */
   FLSHM_TempBuf[FLASHM_TempBuffIdx]=(uint8)*CRC_Pntr ;
  }
  
  /* Compute the crc for a block */
  FLSHM_ComputeCRC(&FLSHM_TempBuf[0],CRCVldnsize);

}

 /***************************************************************************************************
  ** Function         : FLSHM_UpdateAppValdnHdr

  ** Description      : Updates the validation header

  ** Parameter        : None
  **
  ** Return value     : FLSHM_ProgStat_t :  Flash status

  ** Remarks          : None
  ***************************************************************************************************/
 STATIC FUNC(FLSHM_ProgStat_t, FLSHM_CODE) FLSHM_UpdateAppValdnHdr(uint8 VldnBlock, uint32 BlkRxdCRC, 
                                                                 uint32 VldnBlkSize,uint8 BlkFP[],uint8 BlkecuMODE)
{
  FLSHM_ProgStat_t ret_updt = FLSHM_PROGFAILED;
  uint8 up_retval = 0u;
  uint8 signt_idx;
  FLSHM_Valid_Header_t	ValidInfo;

  /* Check if the requested block is valid */
  if (VldnBlock < FLSHM_NUM_OF_BLOCKS)
  {
   /* Store the calculated CRC */
   ValidInfo.CRC_32B = (uint32)BlkRxdCRC;
   /* Store the image size */
   ValidInfo.ImageSize = (uint32)VldnBlkSize;

   ValidInfo.ECU_mode=(uint8)BlkecuMODE;

   for(signt_idx=0u;signt_idx<32u;signt_idx++)
   {
	 ValidInfo.has_signature[signt_idx]=BlkFP[signt_idx];
   }

   up_retval = (uint8)FLASH_DRV_EraseSector(FLSHM_BlockInfo[VldnBlock].BlockValiFlgAdd, FEATURE_FLS_PF_BLOCK_SECTOR_SIZE);

   if(STATUS_SUCCESS == up_retval)
   {
	   /* Flash the header */
	   up_retval = FLASH_DRV_Program(FLSHM_BlockInfo[VldnBlock].BlockValiFlgAdd, ((sizeof(FLSHM_Valid_Header_t))+(sizeof(FLSHM_Valid_Header_t)%8)), (uint8 *)&ValidInfo);

	   /* Check if the flash success */
	   if (up_retval == STATUS_SUCCESS)
	   {
		/* Flash success */
		ret_updt = FLSHM_SUCCESS;
	   }
	   else
	   {
		/* Flash fail */
		ret_updt = FLSHM_VERFIYFAILED;
	   }
   }
   else
   {
		/* Flash fail */
		ret_updt = FLSHM_VERFIYFAILED;
   }
  }
  else
  {
   /* Invalid image */
   ret_updt = FLSHM_VERFIYFAILED;
  }

  return ret_updt;
}

 /***************************************************************************************************
  ** Function                 : FLSHM_AppValdnStateMnger

  ** Description              : Flash manager Application validation state manager

  ** Parameter                : None

  ** Return value             : None

  ** Remarks                  : None
  ***************************************************************************************************/
 FUNC(void, FLSHM_CODE) FLSHM_AppValdnStateMnger(void)
 {

  uint8 AuthIDx;
  
  return; // Enrico: removed Validation

  switch(FLSHM_ValdnState)
  {
  case FLSHM_APPVALDN_IDLE:
  {
   /* Do nothing */
	  FLSHM_GetECUmode();

   break;
  }
  /* Request to start the validation of logical blocks */
  case FLSHM_APPVALDN_REQ:
  {
   /* Point to the first logical block */
   FLSHM_ValidnBlk =  FLSHM_ZERO;

   /* Get the CRC hearder information */
   FLSHM_ValidHeadVal = *((FLSHM_Valid_Header_t  *)FLSHM_BlockInfo[FLSHM_ValidnBlk].BlockValiFlgAdd);
   
   /* Init to null */
   AppCRC = FLSHM_ZERO;
   
   /*Check if application has been erased before */
   if (FLSHM_ValidHeadVal.ImageSize != 0xFFFFFFFFu)
   {
    /*Get the validation start address */
    FLSHM_ValdnCurrAddress = FLSHM_BlockInfo[FLSHM_ValidnBlk].BlockStartAddress ;

    /* Get the validation image size */
    FLSHM_VldnSize = FLSHM_ValidHeadVal.ImageSize ;

    /* Init to null */
    FLSHM_CalctdCRC = FLSHM_ZERO;
	
	/* Get the  ECU mode */
    // enrico removed
    // FLSHM_ECUmode=FLSHM_ValidHeadVal.ECU_mode;

    /* Change the state to start calculating CRC */
    FLSHM_ValdnState = FLSHM_APPVALDN_RUNNING;
   }
   else
   {
    /* No valid application present */
    FLSHM_ValdnState = FLSHM_APPVLDN_FAIL;

// STAT_FIX enrico
#if 0
    /*SBC driver init */
 	UJA1075A_vInit();

 	SBC_InitStat = TRUE;
#endif
// END_FIX

   }
   break;
  }
  
      /* Validating the image */
  case FLSHM_APPVALDN_RUNNING:
  {

    /* Check id reached the end of the image */
    if (FLSHM_VldnSize > FLSHM_ZERO)
    {
     /* Validate the image in a slot basis */
     if (FLSHM_VldnSize >= FLSHM_CRC_CALSLOT_SIZE)
     {
      /* Calculate the CRC for the requested slot */
      FLSHM_CalcCRC(FLSHM_ValdnCurrAddress, FLSHM_CRC_CALSLOT_SIZE);

      /* point to the next slot of memory */
      FLSHM_ValdnCurrAddress += FLSHM_CRC_CALSLOT_SIZE;

      /* get the next size*/
      FLSHM_VldnSize -= FLSHM_CRC_CALSLOT_SIZE;
     }
     else
     {
      /* Calculate the CRC for the last slot */
      FLSHM_CalcCRC(FLSHM_ValdnCurrAddress, FLSHM_VldnSize);

      FLSHM_VldnSize = FLSHM_ZERO;
     }
    }
    else
    { 
	/* Get the applicatin CRC */
     FLSHM_GetAppCRC();

     /* Compare the stored/received CRC with calculated */
     if (FLSHM_CalctdCRC == FLSHM_ValidHeadVal.CRC_32B)
     {
       /* CRC validation successful */
    FLSHM_ValdnState = FLSHM_APPVLDN_PASS;


     }
     else
     {
      /* CRC did not match and validation failed */
      FLSHM_ValdnState = FLSHM_APPVLDN_FAIL;

      // Enrico
      /*SBC driver init */
      //UJA1075A_vInit(); // enrico removed

      //SBC_InitStat = TRUE;
     }
    }

   break;
  }

  case FLSHM_APPATHRZN_REQ:
  {
   /* Point to the first logical block */
   FLSHM_ValidnBlk =  0U;

   /* Get the CRC hearder information */
   FLSHM_ValidHeadVal = *((FLSHM_Valid_Header_t  *)FLSHM_BlockInfo[FLSHM_ValidnBlk].BlockValiFlgAdd);


   /*Check if application has been erased before */
   if (FLSHM_ValidHeadVal.ImageSize != 0xFFFFFFFFu)
   {
    /*Get the validation start address */
    FLSHM_ValdnCurrAddress = FLSHM_BlockInfo[FLSHM_ValidnBlk].BlockStartAddress ;

    /* Get the validation image size */
    FLSHM_AthrznSize = FLSHM_ValidHeadVal.ImageSize ;

    /* Initialise SHA algorithm parameter */
    SHA_datalen=FLSHM_AthrznSize;
	
	 /* Initialise SHA algorithm parameter */
    FLASHM_sha256_init(&FLASHM_ctr);

    /* Change the state to start calculating CRC */
    FLSHM_ValdnState = FLSHM_APPATHRZN_RUNNING;
   }
   else
   {
    /* No valid application present */
    FLSHM_ValdnState = FLSHM_APPATHRZN_FAIL;
   }
   break;
  }

  case FLSHM_APPATHRZN_RUNNING:
  {

    /* Check id reached the end of the image */
    if (FLSHM_AthrznSize > FLSHM_ZERO)
    {
		 /* Validate the image in a slot basis */
		 if (FLSHM_AthrznSize >= FLSHM_SHA256_CALSLOT_SIZE)
		 {
		  /* Calculate the CRC for the requested slot */
		  FLSHM_CreateSignature(FLSHM_ValdnCurrAddress, FLSHM_SHA256_CALSLOT_SIZE,&FLASHM_ctr,SHA_datalen);

		  /* point to the next slot of memory */
		  FLSHM_ValdnCurrAddress += FLSHM_SHA256_CALSLOT_SIZE;

		  /* get the next size*/
		  FLSHM_AthrznSize -= FLSHM_SHA256_CALSLOT_SIZE;
     }
     else
     {
		  /* Calculate the CRC for the last slot */
		  FLSHM_CreateSignature(FLSHM_ValdnCurrAddress, FLSHM_AthrznSize,&FLASHM_ctr,SHA_datalen);

		  FLSHM_AthrznSize = FLSHM_ZERO;
     }
    }
    else
    {
		/* Get the calculated block hash signature */
		FLSHM_GetAppFP(FLASHM_sig_bytes,&FLASHM_ctr);
		
		/* Validate the hash signature */
    	for(AuthIDx=0U;AuthIDx<32U;AuthIDx++)
    	{
    	    if(FLASHM_sig_bytes[AuthIDx]==FLSHM_ValidHeadVal.has_signature[AuthIDx])
    	    {
				/* Component authorized */
    	        FLSHM_ValdnState = FLSHM_APPATHRZN_PASS;
    	    }
    	    else
    	    {
				/* Component not authorized */
				FLSHM_ValdnState =FLSHM_APPATHRZN_FAIL;
				
				/* Bootloader struck reason */
				bootloader_struck_reason=UNATHUR_COMPONENT;
				
    	        break;

    	    }
    	}
    }
   break;
  }
  
  case FLSHM_CALVALDN_REQ:
  {
	   /* Point to the first logical block */
	   FLSHM_ValidnBlk =  FLSHM_ONE;

	   /* Get the CRC hearder information */
	   FLSHM_ValidHeadVal = *((FLSHM_Valid_Header_t  *)FLSHM_BlockInfo[FLSHM_ValidnBlk].BlockValiFlgAdd);

	   /* Init to null */
	   AppCRC = FLSHM_ZERO;
		
	   /*Check if application has been erased before */
	   if (FLSHM_ValidHeadVal.ImageSize != 0xFFFFFFFFu)
	   {
			/*Get the validation start address */
			FLSHM_ValdnCurrAddress = FLSHM_BlockInfo[FLSHM_ValidnBlk].BlockStartAddress ;

			/* Get the validation image size */
			FLSHM_VldnSize = FLSHM_ValidHeadVal.ImageSize ;


			// enrico removed
			// FLSHM_ECUmode=FLSHM_ValidHeadVal.ECU_mode;

			/* initialize the CRC */
			FLSHM_CalctdCRC = 0xFFFFu;

			/* Change the state to start calculating CRC */
			FLSHM_ValdnState = FLSHM_CALVALDN_RUNNING;
	   }
	   else
	   {
			/* No valid application present */
			FLSHM_ValdnState = FLSHM_CALVALDN_FAIL;

		   /*SBC driver init */
			// UJA1075A_vInit(); Ehrich removed
			// SBC_InitStat = TRUE;
	   }
   break;
  }
  /* Validating the image */
  case FLSHM_CALVALDN_RUNNING:
  {

    /* Check id reached the end of the image */
    if (FLSHM_VldnSize > FLSHM_ZERO)
    {
		 /* Validate the image in a slot basis */
		 if (FLSHM_VldnSize >= FLSHM_CRC_CALSLOT_SIZE)
		 {
			  /* Calculate the CRC for the requested slot */
			  FLSHM_CalcCRC(FLSHM_ValdnCurrAddress, FLSHM_CRC_CALSLOT_SIZE);

			  /* point to the next slot of memory */
			  FLSHM_ValdnCurrAddress += FLSHM_CRC_CALSLOT_SIZE;

			  /* get the next size*/
			  FLSHM_VldnSize -= FLSHM_CRC_CALSLOT_SIZE;
		 }
		 else
		 {
			  /* Calculate the CRC for the last slot */
			  FLSHM_CalcCRC(FLSHM_ValdnCurrAddress, FLSHM_VldnSize);

			  FLSHM_VldnSize = FLSHM_ZERO;
		 }
    }
    else
    {
		 FLSHM_GetAppCRC();
		 /* Compare the stored/received CRC with calculated */
		 if (FLSHM_CalctdCRC == FLSHM_ValidHeadVal.CRC_32B)
		 {
			/* CRC validation successful */
			FLSHM_ValdnState = FLSHM_CALVALDN_PASS;
		 }
		 else
		 {
			/* CRC did not match and validation failed */
			FLSHM_ValdnState = FLSHM_CALVALDN_FAIL;
            
			/* Bootloader struck reason */
			bootloader_struck_reason=CAL_CRC_FAILED;

		   /*SBC driver init */
			// Ehrich removed
			//UJA1075A_vInit();
			//SBC_InitStat = TRUE;
		 }
    }

   break;
  }
  case FLSHM_CALATHRZN_REQ:
  {
   /* Point to the first logical block */
   FLSHM_ValidnBlk =  FLSHM_ONE;

   /* Get the CRC hearder information */
   FLSHM_ValidHeadVal = *((FLSHM_Valid_Header_t  *)FLSHM_BlockInfo[FLSHM_ValidnBlk].BlockValiFlgAdd);

   /*Check if application has been erased before */
   if (FLSHM_ValidHeadVal.ImageSize != 0xFFFFFFFFU)
   {
		/*Get the validation start address */
		FLSHM_ValdnCurrAddress = FLSHM_BlockInfo[FLSHM_ValidnBlk].BlockStartAddress ;

		/* Get the validation image size */
		FLSHM_AthrznSize = FLSHM_ValidHeadVal.ImageSize ;

		SHA_datalen=FLSHM_AthrznSize;

		FLASHM_sha256_init(&FLASHM_ctr);

		/* Change the state to start calculating CRC */
		FLSHM_ValdnState = FLSHM_CALATHRZN_RUNNING;
   }
   else
   {
		/* No valid application present */
		FLSHM_ValdnState = FLSHM_CALATHRZN_FAIL;


   }
   break;
  }

  case FLSHM_CALATHRZN_RUNNING:
  {
    /* Check id reached the end of the image */
    if (FLSHM_AthrznSize > FLSHM_ZERO)
    {
		 /* Validate the image in a slot basis */
		 if (FLSHM_AthrznSize >= FLSHM_SHA256_CALSLOT_SIZE)
		 {
			  /* Calculate the CRC for the requested slot */
			  FLSHM_CreateSignature(FLSHM_ValdnCurrAddress, FLSHM_SHA256_CALSLOT_SIZE,&FLASHM_ctr,SHA_datalen);

			  /* point to the next slot of memory */
			  FLSHM_ValdnCurrAddress += FLSHM_SHA256_CALSLOT_SIZE;

			  /* get the next size*/
			  FLSHM_AthrznSize -= FLSHM_SHA256_CALSLOT_SIZE;
		 }
		 else
		 {
			  /* Calculate the CRC for the last slot */
			  FLSHM_CreateSignature(FLSHM_ValdnCurrAddress, FLSHM_AthrznSize,&FLASHM_ctr,SHA_datalen);

			  FLSHM_AthrznSize = FLSHM_ZERO;
		 }
    }
	else
	{
		/* Get the component calculated signature */
		FLSHM_GetAppFP(FLASHM_sig_bytes,&FLASHM_ctr);
		
		/*Validate the calculated signature */
		for(AuthIDx=0U;AuthIDx<32U;AuthIDx++)
		{
			if(FLASHM_sig_bytes[AuthIDx]==FLSHM_ValidHeadVal.has_signature[AuthIDx])
			{
				FLSHM_ValdnState = FLSHM_CALATHRZN_PASS;
			}
			else
			{
				/* Unauthorized component */
				FLSHM_ValdnState = FLSHM_CALATHRZN_FAIL;
				
				/* Bootloader struck reason */
				bootloader_struck_reason=UNATHUR_COMPONENT;
			break;

			}
		}
	}
  break;
  }


  /* Request to start the validation of downloaded image */
  case FLSHM_DWNLD_VLDN_REQ:
  {
	   /* Checking component address */
	   if(FLSHM_ValdnCurrAddress == FLSHM_BlockInfo[FLSHM_ONE].BlockStartAddress)
	   {
			/* Validate only downloaded image */
			FLSHM_ValidnBlk = FLSHM_ONE;
		
	   }
	   else
	   {
			 /* Validate only downloaded image */
			FLSHM_ValidnBlk = FLSHM_ZERO;
	   }

	   /* initialize the CRC */
	   FLSHM_CalctdCRC = 0xFFFFu;
		
	   /* Init to null */
	   AppCRC = FLSHM_ZERO;

	   /* Start validation the downloaded image */
	   FLSHM_ValdnState = FLSHM_DWNLD_VLDN_RUNNING;
   break;
  }
  

  
  case FLSHM_DWNLD_VLDN_RUNNING:
  {

   /* Check id reached the end of the image */
   if (FLSHM_VldnSize > FLSHM_ZERO)
   {
		/* Validate the image in a slot basis */
		if (FLSHM_VldnSize >= FLSHM_CRC_CALSLOT_SIZE)
		{

			 /* Calculate the CRC for the requested slot */
			 FLSHM_CalcCRC(FLSHM_ValdnCurrAddress, FLSHM_CRC_CALSLOT_SIZE);

			 /* point to the next slot of memory */
			 FLSHM_ValdnCurrAddress += FLSHM_CRC_CALSLOT_SIZE;

			 /* get the next size*/
			 FLSHM_VldnSize -= FLSHM_CRC_CALSLOT_SIZE;

		}
		else
		{
			 /* Calculate the CRC for the last slot */
			 FLSHM_CalcCRC(FLSHM_ValdnCurrAddress, FLSHM_VldnSize);

			 FLSHM_VldnSize = FLSHM_ZERO;
		}
   }
   else
   {

	/* Get the calculated CRC */
    FLSHM_GetAppCRC();

    /* Compare the stored/received CRC with calculated */
    if (FLSHM_CalctdCRC == FLSHM_ValidHeadVal.CRC_32B)
    {
		 /* CRC  match and validation pass */
		 FLSHM_ValdnState = FLSHM_DWNLD_VLDN_PASS;


    }
    else
    {
		 /* CRC did not match and validation failed */
		 FLSHM_ValdnState = FLSHM_DWNLD_VLDN_FAIL;

		 if(FLSHM_ValidnBlk==FLSHM_ONE)
		 {
			 /* Bootloader struck reason */
			 bootloader_struck_reason=CAL_CRC_FAILED;
		 }
		 else if(FLSHM_ValidnBlk==FLSHM_ZERO)
		 {
			  /* Bootloader struck reason */
			 bootloader_struck_reason=APPL_CRC_FAILED;
		 }
		 else
		 {
			 /* do nothing */
		 }
    }
   }
   break;
  }


  case FLSHM_DWNLD_ATHRZN_REQ:
  {
   if(FLSHM_ValdnCurrAddress == FLSHM_BlockInfo[FLSHM_ONE].BlockStartAddress)
   {
		/* Validate only downloaded image */
		FLSHM_ValidnBlk = FLSHM_ONE;
   }
   else
   {
		/* Validate only downloaded image */
		FLSHM_ValidnBlk = FLSHM_ZERO;
   }
   /*Get the validation start address */
    FLSHM_ValdnCurrAddress = FLSHM_BlockInfo[FLSHM_ValidnBlk].BlockStartAddress ;

   /* Get the validation image size */
    FLSHM_AthrznSize = FLSHM_ValidHeadVal.ImageSize ;
   
   /* SHA algorithm initialization */
   FLASHM_sha256_init(&FLASHM_ctr);
   
   /* Initialising SHA algorithm parameters */
   SHA_datalen=FLSHM_AthrznSize;

   /* Start authorization of the downloaded image */
   FLSHM_ValdnState = FLSHM_DWNLD_ATHRZN_RUNNING;
   
   break;
  }
  case FLSHM_DWNLD_ATHRZN_RUNNING:
  {

   /* Check id reached the end of the image */
   if (FLSHM_AthrznSize > FLSHM_ZERO)
   {
		/* Validate the image in a slot basis */
		if (FLSHM_AthrznSize >= FLSHM_SHA256_CALSLOT_SIZE)
		{
            /* Create the hash algorithm for a slot */
			 FLSHM_CreateSignature(FLSHM_ValdnCurrAddress, FLSHM_SHA256_CALSLOT_SIZE,&FLASHM_ctr,SHA_datalen);

			 /* point to the next slot of memory */
			 FLSHM_ValdnCurrAddress += FLSHM_SHA256_CALSLOT_SIZE;

			 /* get the next size*/
			 FLSHM_AthrznSize -= FLSHM_SHA256_CALSLOT_SIZE;

		}
		else
		{
			 /* Create the remaining data hash algorithm for a slot */
			 FLSHM_CreateSignature(FLSHM_ValdnCurrAddress, FLSHM_AthrznSize,&FLASHM_ctr,SHA_datalen);

			 FLSHM_AthrznSize = FLSHM_ZERO;
		}
   }
   else
   {

	/* Get the calculated hash signature */
	FLSHM_GetAppFP(FLASHM_sig_bytes,&FLASHM_ctr);

	/* Validate the calculted hash signature */
    for(AuthIDx=0u;AuthIDx<32u;AuthIDx++)
    {
		if(FLASHM_sig_bytes[AuthIDx]==FLSHM_ValidHeadVal.has_signature[AuthIDx])
		{
			/* Authorized component */
			FLSHM_ValdnState = FLSHM_DWNLD_ATHRZN_PASS;
		}
		else
		{
			/* Un authorized component */
			FLSHM_ValdnState = FLSHM_DWNLD_ATHRZN_FAIL;

			bootloader_struck_reason=UNATHUR_COMPONENT;
		break;

		}
    }
   }

   break;
  }
  
  case FLSHM_MANUFT_MODE:
  {
	  // enrico modified
		/* validate the ECU mode in manufacturing mode */
    //if(FLSHM_ECUmode==MANFACTURING_MODE)
    {
	
      //FLSHM_ECUmode=PRODUCTION_MODE;

	  FLSHM_ValdnState =FLSH_PRODUCT_MODE;
    }
	 break;

  }

  case FLSHM_APPVLDN_FAIL:
  {
   /* Do nothing */
   break;
  }
  case FLSHM_APPVLDN_PASS:
  {
   /* Do nothing */
   break;
  }
  case FLSHM_DWNLD_VLDN_FAIL:
  {
   /* Do nothing */
   break;
  }
  case FLSHM_DWNLD_VLDN_PASS:
  {
   /* Do nothing */
   break;
  }
  case FLSHM_APPATHRZN_PASS:
  {
   /* Do nothing */
   break;
  }
  case FLSHM_DWNLD_ATHRZN_PASS:
  {
   /* Do nothing */
   break;
  }
  case FLSHM_DWNLD_ATHRZN_FAIL:
  {
   /* Do nothing */
   break;
  }
  case FLSH_PRODUCT_MODE:
  {
	  break;
  }
  case FLSHM_APPATHRZN_FAIL:
  {
   /* Do nothing */
   break;
  }
  default:
  {

   break;
  }
  }
 }

 /***************************************************************************************************
  ** Function                 : FLSHM_GetAppValdnStat

  ** Description              : Flash manager Get the application validation status

  ** Parameter                : None

  ** Return value             : None

  ** Remarks                  : None
  ***************************************************************************************************/
 FUNC(FLSHM_AppVldnStat_t, FLSHM_CODE) FLSHM_GetAppValdnStat(void)
 {
	return FLSHM_ValdnState;
 }

 /***************************************************************************************************
  ** Function                 : FLSHM_StartAppValdn

  ** Description              : Flash manager Start Application validation

  ** Parameter                : None

  ** Return value             : None

  ** Remarks                  : None
  ***************************************************************************************************/
 STATIC FUNC(void, FLSHM_CODE) FLSHM_StartAppValdn(void)
 {
	  /* Change the state to validate all the logical blocks */
	  FLSHM_ValdnState = FLSHM_APPVALDN_REQ;
}

 /***************************************************************************************************
  ** Function                 : FLSHM_StartAppAthrzn

  ** Description              : Flash manager Start Application authorization

  ** Parameter                : None

  ** Return value             : None

  ** Remarks                  : None
  ***************************************************************************************************/
 STATIC FUNC(void, FLSHM_CODE) FLSHM_StartAppAthrzn(void)
 {
	  /* Change the state to validate all the logical blocks */
	  FLSHM_ValdnState = FLSHM_APPATHRZN_REQ;
 }

 /***************************************************************************************************
   ** Function                 : FLSHM_StartCalValdn

   ** Description              : Flash manager Start Calibration data validation

   ** Parameter                : None

   ** Return value             : None

   ** Remarks                  : None
   ***************************************************************************************************/
STATIC FUNC(void, FLSHM_CODE) FLSHM_StartCalValdn(void)
  {
	   /* Change the state to validate all the logical blocks */
	   FLSHM_ValdnState = FLSHM_CALVALDN_REQ;
  }
 /***************************************************************************************************
    ** Function                 : FLSHM_StartCalAthrzn

    ** Description              : Flash manager Start Calibration data authorization

    ** Parameter                : None

    ** Return value             : None

    ** Remarks                  : None
    ***************************************************************************************************/

STATIC FUNC(void, FLSHM_CODE) FLSHM_StartCalAthrzn(void)
  {
	   /* Change the state to validate all the logical blocks */
	   FLSHM_ValdnState = FLSHM_CALATHRZN_REQ;
  }

 /***************************************************************************************************
  ** Function                 : FLSHM_StartDwnlValdn

  ** Description              : Flash manager Start validating the downloaded Image

  ** Parameter                : FlashStrtAddress: Start address of the flash download validation
        : FlashEndAddress: End address of the flash download validation
        : CRC : CRC of the image received

  ** Return value             : FLSHM_ProgStat_t

  ** Remarks                  : None
  ***************************************************************************************************/
 FUNC(FLSHM_AppVldnStat_t, FLSHM_CODE) FLSHM_StartDwnlValdn(VAR(uint32, FLASHM_DATA) FlashStrtAddress,
                                          VAR(uint32, FLSHM_DATA) FlashVldnSize, VAR(uint16, FLSHM_VAR) CRC_Val)
 {
  /* Change the validation state to Validation req */
	 FLSHM_ValdnState = FLSHM_DWNLD_VLDN_REQ;

  uint8 rtrnVal=0u;

  /* Save the received CRC */
  FLSHM_ValidHeadVal.CRC_32B = CRC_Val;

  FLSHM_ValdnCurrAddress = FlashStrtAddress ;

  FLSHM_VldnSize = FlashVldnSize;

  FLSHM_ValidHeadVal.ImageSize=FLSHM_VldnSize;



   /* If flash program is downloaded is done before */
   if (FLASHMGR_IDLE== FLSHM_FlshMngrState)
   {
    /* Change the state to Verify Program downloaded */
    FLSHM_FlshMngrState = FLASHMGR_VERIFY;
	
	rtrnVal=FLSHM_APPVALDN_REQ_ACCEPT;


   }
   else
   {
    /* Do nothing */
   }
   



  return rtrnVal;
 }

 /***************************************************************************************************
  ** Function                 : FLSHM_StartDwnlValdn

  ** Description              : Flash manager Start validating the downloaded Image

  ** Parameter                : FlashStrtAddress: Start address of the flash download validation
        : FlashEndAddress: End address of the flash download validation
        : CRC : CRC of the image received

  ** Return value             : FLSHM_ProgStat_t

  ** Remarks                  : None
  ***************************************************************************************************/

 FUNC(FLSHM_AppVldnStat_t, FLSHM_CODE) FLSHM_StartDwnldAthrzn(VAR(uint32, FLASHM_DATA) FlashStrtAddress,
                                  VAR(uint32, FLSHM_DATA) FlashAUTHsize, VAR(uint8, FLSHM_VAR) sig[],VAR(uint8, FLSHM_VAR)sign_len)
 {
  /* Change the validation state to Validation req */

	 FLSHM_ValdnState = FLSHM_DWNLD_ATHRZN_REQ;
	 uint8 AuthrtrnVal=0u;
	 uint8 Sign_idx;
	 
	 
	 if(sign_len!=0u)
	 {
	
	/* Store the signature of component */
	 for(Sign_idx=0u;Sign_idx<sign_len;Sign_idx++)
	 {
		FLSHM_ValidHeadVal.has_signature[Sign_idx]=sig[Sign_idx];
	 }
	 }


	/* Copy the start address of component */
	FLSHM_ValdnCurrAddress = FlashStrtAddress ;

	FLSHM_AthrznSize = FlashAUTHsize /*-FLSHM_ONE*/ ;


	/* Copy the Component size */
	FLSHM_ValidHeadVal.ImageSize=FLSHM_AthrznSize;


	   /* If flash program is downloaded is done before */
	if (FLASHMGR_VERIFY_DONE== FLSHM_FlshMngrState)
	{
		 /* Change the state to Verify Program downloaded */
		 FLSHM_FlshMngrState = FLASHMGR_VERIFY_FP;
		 
		 AuthrtrnVal=FLSHM_APPVALDN_REQ_ACCEPT;
	}
	else
	{
		/* Do nothing */
	}
	
	
	return AuthrtrnVal;
 }

 FUNC(FLSHM_AppVldnStat_t, FLSHM_CODE)  FLSHM_SetMODE(VAR(uint8, FLASHM_DATA)ECUMODE)

 {
  
	 uint8 ModertrnVal=0U;

	/* Validate validation state and ECU mode */
	 if (	(FLSHM_ValdnState==FLSHM_DWNLD_ATHRZN_PASS) &&
			(ECUMODE==PRODUCTION_MODE)
			/*&&(FLSHM_FlshMngrState==FLASHMGR_VERIFY_FP_DONE)*/
	 )
	 {
		 /* ECU mode is production mode */
		if( (FLSHM_ECUmode == PRODUCTION_MODE) || (FLSHM_ECUmode==0u) )
		{
			// FLSHM_ECUmode = MANFACTURING_MODE; // enrico removed
		}
		/* Change the flash manager state */
		FLSHM_FlshMngrState = FLASHMGR_VERIFY_MODE;

        /* Change the validation state */
		FLSHM_ValdnState = FLSHM_MANUFT_MODE;

		ModertrnVal = FLSHM_APPVALDN_REQ_ACCEPT;
	 }

	   
	  return ModertrnVal;
 }

 STATIC FUNC(void, FLSHM_CODE) FLSHM_GetECUmode(void)
 {
#if 0 // enrico removed
	 uint8 AppMode;
	 uint8 CalMode;
	  /* Get the CRC hearder information */
	   FLSHM_ValidHeadVal = *((FLSHM_Valid_Header_t  *)FLSHM_BlockInfo[0u].BlockValiFlgAdd);
	   AppMode=FLSHM_ValidHeadVal.ECU_mode;

	   FLSHM_ValidHeadVal = *((FLSHM_Valid_Header_t  *)FLSHM_BlockInfo[1u].BlockValiFlgAdd);
	   CalMode=FLSHM_ValidHeadVal.ECU_mode;
	   if((AppMode!=MANFACTURING_MODE)|| (CalMode != MANFACTURING_MODE))
	   {
		   FLSHM_ECUmode=PRODUCTION_MODE;
	   }
	   else if((AppMode==0xFF)&&(CalMode==0xFF))
	   {
		   FLSHM_ECUmode=MANFACTURING_MODE;
	   }
#endif
 }
 /***************************************************************************************************
  ** Function                 : FLSHM_ResetAppValdnStat

  ** Description              : Resets the CRC validation state to Idle

  ** Parameter                : None

  ** Return value             : None

  ** Remarks                  : None
  ***************************************************************************************************/
 FUNC(void, FLSHM_CODE) FLSHM_ResetAppValdnStat(void)
 {
	  /* Reset the Validation manager ot Idle */
	  FLSHM_ValdnState = FLSHM_APPVALDN_IDLE;
 }

 /***************************************************************************************************
  ** Function                 : FLSHM_GetCMDStatus

  ** Description              : Get Flash command status

  ** Parameter                : None

  ** Return value             : FLSHM_SUCCESS
  **                              FLSHM_ERASEFAILED
  **                              FLSHM_WRONGADDRESS

  ** Remarks                  : None
  ***************************************************************************************************/
 FLSHM_ProgStat_t FLSHM_GetCMDStatus(void)
 {
	return FLSHM_CmdStat;
 }

 /***************************************************************************************************
  ** Function                 : FLSHM_GetFlashState

  ** Description              : Get flash current state

  ** Parameter                : None

  ** Return value             : FlashMgr_State

  ** Remarks                  : None
  ***************************************************************************************************/
 FLSHM_FlshMngrState_t FLSHM_GetFlashState(void)
 {
	return FLSHM_FlshMngrState;
 }
 /***************************************************************************************************
  ** Function                 : FLSHM_ComputeCRC

  ** Description              : Calculate CRC-32 of downloaded image

  ** Parameter                : Flash data need to calculate CRC-32 and Datalength

  ** Return value             : None

  ** Remarks                  : None
  ***************************************************************************************************/

 STATIC FUNC(void, FLSHM_CODE) FLSHM_ComputeCRC(uint8 *CRCDataBuffer, uint32 CRCdatalen)
 {
  uint8 CRC_idx;
  uint32 CRCLoopIdx;
  uint8 byte;
  uint32 Mask;

  /* checksum algorithm as taken from IAR-document */
  for(CRCLoopIdx = FLSHM_ZERO; CRCLoopIdx < CRCdatalen; CRCLoopIdx++)
  {
   byte = CRCDataBuffer[CRCLoopIdx];

   AppCRC ^= (uint32)byte;

   for (CRC_idx = FLSHM_ZERO; CRC_idx < FLSHM_EIGHT; ++CRC_idx)
   {
    Mask = -(AppCRC & FLSHM_ONE);

    AppCRC = ((AppCRC >> FLSHM_ONE) ^ (FLSHM_CRC_POLYNML & Mask));
   }
  }
 }

 /***************************************************************************************************
   ** Function                 : FLSHM_GetAppCRC

   ** Description              : Get flash data CRC

   ** Parameter                : None

   ** Return value             : None

   ** Remarks                  : None
   ***************************************************************************************************/
 STATIC FUNC(void, FLSHM_CODE) FLSHM_GetAppCRC(void)
{
	  /*Update the Calculated CRC*/
	  FLSHM_CalctdCRC = (uint16)AppCRC;
}

 /***************************************************************************************************
    ** Function                 : FLSHM_GetAppFP

    ** Description              : Get flash data hash signature

    ** Parameter                : signature buffer

    ** Return value             : None

    ** Remarks                  : None
    ***************************************************************************************************/

 FUNC(void, FLSHM_CODE) FLSHM_GetAppFP(uint8 *FLASHM_sig_ptr,sha256_control *SIGnatre)
 {
	 uint8 sign_i,hash_j;
	 uint32 sig_data;
	 hash_j=0u;
/* Copy the calculated hash signature byte by byte */
  for(sign_i=0u;sign_i<32u;)
  {
	  sig_data=SIGnatre->hash[hash_j];
	  FLASHM_sig_ptr[sign_i]=(uint8 )((sig_data&0xFF000000u)>>24u);
	  FLASHM_sig_ptr[sign_i+1u]=(uint8)((sig_data&0xFF0000u)>>16u);
	  FLASHM_sig_ptr[sign_i+2u]=(uint8)((sig_data&0xFF00u)>>8u);
	  FLASHM_sig_ptr[sign_i+3u]=(uint8)(sig_data&0xFFu);
	  sign_i=sign_i+4u;
	  hash_j++;
  }

 }

 /***************************************************************************************************
     ** Function                 : FLSHM_CreateSignature

     ** Description              : Get the  flash data for hash signature

     ** Parameter                : flash data start address and Flash data size

     ** Return value             : None

     ** Remarks                  : None
     ***************************************************************************************************/

 FUNC(void, FLSHM_CODE) FLSHM_CreateSignature(uint32 HashStrtAddress, uint32 HashSize,\
                                                        sha256_control *signature,uint32 Hashtotal_size)
 {
  uint8 FLSHM_TempBuf[128u];
 
  uint32 FLASHM_TempBuffIdx;
  uint32 no_of_chucks;
    uint32 rem_data;
    uint32 data_index;
    uint32 index;
    uint32 count;
    count=0u;
   
  uint8   * signature_Pntr;

  for(FLASHM_TempBuffIdx=0u;FLASHM_TempBuffIdx<HashSize;FLASHM_TempBuffIdx++)
  {
   signature_Pntr = (uint8   *)HashStrtAddress++;
   FLSHM_TempBuf[FLASHM_TempBuffIdx]=(uint8)*signature_Pntr ;
  }

    no_of_chucks=(HashSize/64u);
    rem_data=(HashSize%64u);

    if(no_of_chucks>0)
    {
     for(index=0;index<no_of_chucks;index++)
    {
    	 signature->chunk_len=64u;
      for(data_index=0;data_index<64u;data_index++)
      {
       /*passing data to calculate chunk*/
    	  signature->chunk[data_index]=FLSHM_TempBuf[data_index+count];

      }
      FLASHM_sha256_computation(signature);
      count=count+64u;

    }
    }



    if(rem_data>0)
    {
    	signature->chunk_len=rem_data;
     for(data_index=0;data_index<rem_data;data_index++)
     {
    	 signature->chunk[data_index]=FLSHM_TempBuf[data_index+count];

     }
     FLASHM_sha256_padding(signature,Hashtotal_size);
     //rem_data=0;
    }
  
 }


 /***************************************************************************************************
       ** Function                 : FLASHM_sha256_init

       ** Description              : Initialize the hash signature pointer

       ** Parameter                : hash signature structure pointer

       ** Return value             : None

       ** Remarks                  : None
       ***************************************************************************************************/
 FUNC(void, FLSHM_CODE) FLASHM_sha256_init(sha256_control *ctr)
 {
  ctr->bitlen = 0u;
  /* hash values are initialized according to sha256 alogrithm by NSA*/
  ctr->hash[0] = 0x6a09e667u;
  ctr->hash[1] = 0xbb67ae85u;
  ctr->hash[2] = 0x3c6ef372u;
  ctr->hash[3] = 0xa54ff53au;
  ctr->hash[4] = 0x510e527fu;
  ctr->hash[5] = 0x9b05688cu;
  ctr->hash[6] = 0x1f83d9abu;
  ctr->hash[7] = 0x5be0cd19u;
 }

 /***************************************************************************************************
 ** Function                 : FLASHM_sha256_padding

 ** Description              : Pad the additional bytes for SHA-256 algorithm

 ** Parameter                : hash signature structure pointer

 ** Return value             : None

 ** Remarks                  : None
 ***************************************************************************************************/
 FUNC(void, FLSHM_CODE) FLASHM_sha256_padding(sha256_control *ctr,uint32 total_legth)
{
  uint32 chunk_index=0u;
  chunk_index = ctr->chunk_len;

  /*Pad whatever data is left in the input buffer.*/
  if (ctr->chunk_len < 56u)
  {
   /*if msg length is less than 56 byte then add 1 bit to show end of msg*/

   ctr->chunk[chunk_index] = 0x80u;
   chunk_index++;
   for (;chunk_index<56u;chunk_index++)
   {
    ctr->chunk[chunk_index] = 0x00u;
   }

  }
  else
  {
   /*if its greater than 56byte than add 1bit to show end of msg*/
   ctr->chunk[chunk_index] = 0x80u;
   chunk_index++;
   for (;chunk_index<64u;chunk_index++)
   {
    ctr->chunk[chunk_index] = 0x00u;
   }

   FLASHM_sha256_computation(ctr);
   /*pad and add length of input msg*/
   for(chunk_index=0u;chunk_index<56u;chunk_index++)
   {
    ctr->chunk[chunk_index]=0u;
   }

  }

  /*Append to the padding the total message's length in bits and transform.*/
  ctr->chunk_len=total_legth;
  ctr->bitlen = (uint64)((ctr->bitlen + ((uint64)ctr->chunk_len * 8u)));
  ctr->chunk[63] = (uint8)(ctr->bitlen);
  ctr->chunk[62] = (uint8)(ctr->bitlen >> 8u);
  ctr->chunk[61] = (uint8)(ctr->bitlen >> 16u);
  ctr->chunk[60] = (uint8)(ctr->bitlen >> 24u);
  ctr->chunk[59] = (uint8)(ctr->bitlen >> 32u);
  ctr->chunk[58] = (uint8)(ctr->bitlen >> 40u);
  ctr->chunk[57] = (uint8)(ctr->bitlen >> 48u);
  ctr->chunk[56] = (uint8)(ctr->bitlen >> 56u);
  FLASHM_sha256_computation(ctr);
 }
 /***************************************************************************************************
  ** Function                 :  FLASHM_sha256_computation

  ** Description              : compute the hash signature for data

  ** Parameter                : hash signature structure pointer

  ** Return value             : None

  ** Remarks                  : None
  ***************************************************************************************************/
  FUNC(void, FLSHM_CODE) FLASHM_sha256_computation(sha256_control  *ctr)
  {
  /****** constant values which is predefined in sha256 by NSA*******************/
  const uint32 k[64] =
  {
    0x428a2f98u,0x71374491u,0xb5c0fbcfu,0xe9b5dba5u,0x3956c25bu,0x59f111f1u,0x923f82a4u,0xab1c5ed5u,
    0xd807aa98u,0x12835b01u,0x243185beu,0x550c7dc3u,0x72be5d74u,0x80deb1feu,0x9bdc06a7u,0xc19bf174u,
    0xe49b69c1u,0xefbe4786u,0x0fc19dc6u,0x240ca1ccu,0x2de92c6fu,0x4a7484aau,0x5cb0a9dcu,0x76f988dau,
    0x983e5152u,0xa831c66du,0xb00327c8u,0xbf597fc7u,0xc6e00bf3u,0xd5a79147u,0x06ca6351u,0x14292967u,
    0x27b70a85u,0x2e1b2138u,0x4d2c6dfcu,0x53380d13u,0x650a7354u,0x766a0abbu,0x81c2c92eu,0x92722c85u,
    0xa2bfe8a1u,0xa81a664bu,0xc24b8b70u,0xc76c51a3u,0xd192e819u,0xd6990624u,0xf40e3585u,0x106aa070u,
    0x19a4c116u,0x1e376c08u,0x2748774cu,0x34b0bcb5u,0x391c0cb3u,0x4ed8aa4au,0x5b9cca4fu,0x682e6ff3u,
    0x748f82eeu,0x78a5636fu,0x84c87814u,0x8cc70208u,0x90befffau,0xa4506cebu,0xbef9a3f7u,0xc67178f2u
  };
  uint32 hash_temp_a=0u;
  uint32	hash_temp_b=0u;
  uint32	hash_temp_c=0u;
  uint32	hash_temp_d=0u;
  uint32	hash_temp_e=0u;
  uint32	hash_temp_f=0u;
  uint32	hash_temp_g=0u;
  uint32	hash_temp_h=0u;
  uint32	i, j;
  uint32	temp1=0u, temp2=0u;
  uint32	msg_block[64];

  /*as sha256 output big endian conv msg to big endian formate*/
  j=0u;
  for (i=0u;i<16u;++i)
  {
   msg_block[i] = ((uint32)ctr->chunk[j] << 24) | ((uint32)ctr->chunk[j + 1u] << 16) | ((uint32)ctr->chunk[j + 2u] << 8) | ((uint32)ctr->chunk[j + 3u]);
   j+=4u;
  }

  /*expand the msg block from 16 to 64*/
  for (i=16u; i < 64u; ++i)
  {
   msg_block[i] = SIG1(msg_block[i - 2u]) + msg_block[i - 7u] + SIG0(msg_block[i - 15u]) + msg_block[i - 16u];
  }

  /*copy the initial hash values in temporary varibale*/
  hash_temp_a = ctr->hash[0u];
  hash_temp_b = ctr->hash[1u];
  hash_temp_c = ctr->hash[2u];
  hash_temp_d = ctr->hash[3u];
  hash_temp_e = ctr->hash[4u];
  hash_temp_f = ctr->hash[5u];
  hash_temp_g = ctr->hash[6u];
  hash_temp_h = ctr->hash[7u];


  /*calculate using sha256 standard operation*/
  for (i = 0u; i < 64u; ++i)
  {
   /*E1=(e>>2)^(e>>11)^(e>>25)*/
   /*CH=(e & f) ^((~e)& g)*/
   /*temp1 Adds and stores values of E1 block, CH block,K constant value along with input msg*/
   temp1 =  hash_temp_h + E1( hash_temp_e) + CH( hash_temp_e, hash_temp_f, hash_temp_g) + k[i] + msg_block[i];
   /*E0=(a>>2)^(a>>13)^(a>>22)*/
   /*MAJ=(a&b)^(a&c)^(b&c)*/
   /*temp2 adds and stores E0 block and MAJ block.*/
   temp2 = E0( hash_temp_a) + MAJ( hash_temp_a, hash_temp_b, hash_temp_c);
   hash_temp_h =  hash_temp_g;
   hash_temp_g =  hash_temp_f;
   hash_temp_f =  hash_temp_e;
   hash_temp_e =  hash_temp_d + temp1;
   hash_temp_d =  hash_temp_c;
   hash_temp_c =  hash_temp_b;
   hash_temp_b =  hash_temp_a;
   hash_temp_a = temp1 + temp2;
  }

  /*add the inital hash value to produced hash value which will be output for that chunk*/
  ctr->hash[0] +=  hash_temp_a;
  ctr->hash[1] +=  hash_temp_b;
  ctr->hash[2] +=  hash_temp_c;
  ctr->hash[3] +=  hash_temp_d;
  ctr->hash[4] +=  hash_temp_e;
  ctr->hash[5] +=  hash_temp_f;
  ctr->hash[6] +=  hash_temp_g;
  ctr->hash[7] +=  hash_temp_h;
  }
