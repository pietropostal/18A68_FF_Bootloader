/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : FLSHM_Comn.h
** Module name  : FLSH Manager common header file
** -------------------------------------------------------------------------------------------------
**
** Description : FLASHM_Comn.h  file should be common between application and bootloader
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
#include "Platform_Types.h"
#include "FLSHM_Cfg.h"
#include "Flash.h"


/********************************** Component configuration ***************************************/

/********************************* Declaration of local functions *********************************/

/************************** Declaration of local symbol and constants *****************************/

/********************************* Declaration of local macros ************************************/

/********************************* Declaration of local types *************************************/

//#define FLSHM_COMMON_RAM_ADDR	0x05300

#define	FLSHM_NO_REPROG_REQ					0x00u
#define	FLSHM_REPROG_REQ					0xA5A5A5A5
#define FLSHM_DFLASH_START_ADDRESS 			0x10000000
#define FLASHM_MIN_WRITE_SIZE 		 		8u

/******************************* Declaration of local variables ***********************************/

/******************************* Declaration of local constants ***********************************/

/****************************** Declaration of exported variables *********************************/

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
FUNC(uint32, FLSHM_CODE) FLSHM_GetReprogStat(void);

/***************************************************************************************************
** Function         : FLSHM_SetReprogStat

** Description      : Sets the Reprog Request status

** Parameter        : None

** Return value     : None

** Remarks          : None
***************************************************************************************************/
FUNC(status_t, FLSHM_CODE) FLSHM_ClrReprogReq(void);

/***************************************************************************************************
** Function         : FLSHM_SetReprogStat

** Description      : Sets the Reprog Request status

** Parameter        : None

** Return value     : None

** Remarks          : None
***************************************************************************************************/
FUNC(status_t, FLSHM_CODE) FLSHM_ReqReprog(void);


