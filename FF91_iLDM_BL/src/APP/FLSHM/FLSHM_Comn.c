
/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : FLSHM_Comn.c
** Module name  : FLSH Manager common source
** -------------------------------------------------------------------------------------------------
**
** Description : FLASHM_Comn.c  file should be common between application and bootloader
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
#include "FLSHM_Comn.h"


/********************************** Component configuration ***************************************/

/********************************* Declaration of local functions *********************************/

/************************** Declaration of local symbol and constants *****************************/

/********************************* Declaration of local macros ************************************/

/********************************* Declaration of local types *************************************/

/******************************* Declaration of local variables ***********************************/
/*********************************** Start of Common Data *****************************************/

/*********************************** End of Common data   *****************************************/
/******************************* Declaration of local constants ***********************************/

/****************************** Declaration of exported variables *********************************/
//__attribute__ ((section(".SharedRAMSection"))) uint8 ReprogReqFlg;
extern uint32_t __BOOTFLAGS[];
static uint32* ReprogFlgAddrss = (uint32*)__BOOTFLAGS;
//static uint8 ReprogrammingFlgBuff[8] = {FLSHM_REPROG_REQ,0,0,0,0,0,0,0}; // Enrico removed

/****************************** Declaration of exported constants *********************************/

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/***************************************************************************************************
** Function         : FLSHM_GetReprogStat

** Description      : returns the Flash reprog status

** Parameter        : None

** Return value     : None

** Remarks          : None
***************************************************************************************************/
FUNC(uint32, FLSHM_CODE) FLSHM_GetReprogStat(void)
{
	return (*ReprogFlgAddrss);
}

/***************************************************************************************************
** Function         : FLSHM_SetReprogStat

** Description      : Sets the Reprog Request status

** Parameter        : None

** Return value     : None

** Remarks          : None
***************************************************************************************************/
FUNC(status_t, FLSHM_CODE) FLSHM_ClrReprogReq(void)
{
	//status_t RetVal;
	// Ehrich changed
	//RetVal = FLASH_DRV_EraseSector(FLSHM_DFLASH_START_ADDRESS,FEATURE_FLS_PF_BLOCK_SECTOR_SIZE);
	ReprogFlgAddrss[0] = 0;

	//return RetVal;
	return STATUS_SUCCESS;
}

#if 0 // Enrico
/***************************************************************************************************
** Function         : FLSHM_SetReprogStat

** Description      : Sets the Reprog Request status

** Parameter        : None

** Return value     : None

** Remarks          : None
***************************************************************************************************/
FUNC(status_t, FLSHM_CODE) FLSHM_ReqReprog(void)
{
	status_t RetVal;
	RetVal = FLASH_DRV_Program((uint32)ReprogFlgAddrss ,FLASHM_MIN_WRITE_SIZE,ReprogrammingFlgBuff);

	return RetVal;
}
#endif
