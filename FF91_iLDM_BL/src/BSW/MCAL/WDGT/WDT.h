/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name     : WDT.c
** Module Name   : WDT
** -------------------------------------------------------------------------------------------------
**
** Description : Watchdog Target
**
** -------------------------------------------------------------------------------------------------
**
** Documentation reference :
**
****************************************************************************************************
** R E V I S I O N H I S T O R Y
****************************************************************************************************
** V01.00 16/08/2018
** - Baseline Created
***************************************************************************************************/
/* To avoid multi-inclusions */
#ifndef WDT_H_
#define WDT_H_
/************************************** Inclusion files *******************************************/
#include "Platform_Types.h"
#include "WDT_Cfg.h"
/******************************* Declaration of global macros *************************************/

/*********************** Declaration of global symbol and constants *******************************/

/****************************** Declaration of global types ***************************************/

/********************************* Component configuration ****************************************/

/************************** External links of global variables ************************************/

/************************** External links of global constant *************************************/

/******************************** Function definitions ********************************************/

/***************************************************************************************************
** FUNCTIONS **
***************************************************************************************************/
/***************************************************************************************************
** Function name    : WDT_Init
** Description      : This function Configures all WDOG registers.
** Parameter 		: None
** Return value     : None
** Remarks          : None
***************************************************************************************************/
extern void WDT_Init(void);

/***************************************************************************************************
** Function name    : WDT_Refresh
** Description      : This function Refreshes the WDOG counter.
** Parameter 		: None
** Return value     : None
** Remarks          : None
***************************************************************************************************/
extern void WDT_Refresh(void);

/***************************************************************************************************
** Function name    : WDT_ResetImmediate
** Description      : This function resets the WDOG.
** Parameter 		: None
** Return value     : None
** Remarks          : None
***************************************************************************************************/
extern void WDT_ResetImmediate(void);

/***************************************************************************************************
** Function name    : WDT_Disable
** Description      : This function disables the WDOG.
** Parameter 		: None
** Return value     : None
** Remarks          : None
***************************************************************************************************/
extern void WDT_Disable(void);

#endif /* WDT_H_ */
