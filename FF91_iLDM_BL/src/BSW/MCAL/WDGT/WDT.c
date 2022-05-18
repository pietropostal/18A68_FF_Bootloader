/**************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** ------------------------------------------------------------------------------------------------
** File Name     : WDT.c
** Module Name   : WDT
** ------------------------------------------------------------------------------------------------
**
** Description : Watchdog Target
**
** ------------------------------------------------------------------------------------------------
**
** Documentation reference :
**
***************************************************************************************************
** R E V I S I O N H I S T O R Y
***************************************************************************************************
** V01.00 16/08/2018
** - Baseline Created
**
***************************************************************************************************/
/************************************** Inclusion files *******************************************/
#include "WDT.h"

/********************************* Component configuration ****************************************/

/*********************** Declaration of local symbol and constants ********************************/

/****************************** Declaration of local macros ***************************************/

/****************************** Declaration of local types ****************************************/

/**************************** Declaration of local variables **************************************/
/*Flag for Watchdog Reset*/
static boolean  WDT_ResetImmediateFlag;

/**************************** Declaration of local constants **************************************/

/************************** Declaration of exported variables *************************************/

/*************************** Declaration of exported constant *************************************/

/*************************** Internal functions declarations **************************************/

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
void WDT_Init(void)
{
	/*Disable global interrupts*/
	DISABLE_INTERRUPTS();

	if ((WDOG->CS & WDOG_CS_CMD32EN_MASK) != 0U)
	{
		WDOG->CNT = FEATURE_WDOG_UNLOCK_VALUE;
		(void)WDOG->CNT;
	}

	/* Configure timeout */
	WDOG->TOVAL = (uint32_t)WDT_CFG_TIMEOUT+1;

	WDOG->CS  = (uint32_t ) ((1UL << WDOG_CS_CMD32EN_SHIFT) |
							(FEATURE_WDOG_CLK_FROM_LPO << WDOG_CS_CLK_SHIFT) |
									(1U << WDOG_CS_EN_SHIFT) |
								(1U << WDOG_CS_UPDATE_SHIFT));
#if WDT_CFG_INTERRUPT_EN
	WDOG->CS  = (uint32_t) ((1U << WDOG_CS_WIN_SHIFT) | (1UL << WDOG_CS_CMD32EN_SHIFT) |
							(FEATURE_WDOG_CLK_FROM_LPO << WDOG_CS_CLK_SHIFT) |
									(1U << WDOG_CS_EN_SHIFT) |
								(1U << WDOG_CS_UPDATE_SHIFT) | (1U << WDOG_CS_INT_SHIFT));
#endif


	/* wait until new configuration takes effect */
	while(((WDOG->CS & WDOG_CS_RCS_MASK) >> WDOG_CS_RCS_SHIFT) == 0UL);

	/* Enable global interrupts */
	ENABLE_INTERRUPTS();

}

/***************************************************************************************************
** Function name    : WDT_Refresh
** Description      : This function Refreshes the WDOG counter.
** Parameter 		: None
** Return value     : None
** Remarks          : None
***************************************************************************************************/
void WDT_Refresh(void)
{
	/*Disable global interrupts*/
	DISABLE_INTERRUPTS();

	/* Reset Flag is TRUE, Refresh WachDog */
	if(WDT_ResetImmediateFlag == FALSE)
	{
		/* For 32-bit write refresh write sequence, WDOG_CS[CMD32EN] should be 1*/
		if(((WDOG->CS & WDOG_CS_CMD32EN_MASK) >> WDOG_CS_CMD32EN_SHIFT) == 1UL)
		{
			/* Write of the WDOG unlock key to CNT register, must be done in order to allow any modifications*/
			WDOG->CNT = (uint32_t) FEATURE_WDOG_TRIGGER_VALUE;
		}
		else
		{
			/* Do Nothing */
		}
	}
	/* Enable global interrupts */
	ENABLE_INTERRUPTS();
}

/***************************************************************************************************
** Function name    : WDT_ResetImmediate
** Description      : This function resets the WDOG.
** Parameter 		: None
** Return value     : None
** Remarks          : None
***************************************************************************************************/
void WDT_ResetImmediate(void)
{
	/* Reset Flag */
	WDT_ResetImmediateFlag = TRUE;
}

/***************************************************************************************************
** Function name    : WDT_Disable
** Description      : This function disables the WDOG.
** Parameter 		: None
** Return value     : None
** Remarks          : None
***************************************************************************************************/
void WDT_Disable(void)
{
	/*Disable global interrupts*/
	DISABLE_INTERRUPTS();
	/*unlock WatchDog*/
	WDOG->CNT = (uint32_t)FEATURE_WDOG_UNLOCK_VALUE;
	/* disable WatchDog */
	WDOG->CS &= ~WDOG_CS_EN_MASK;
	/* Enable global interrupts */
	ENABLE_INTERRUPTS();
}
