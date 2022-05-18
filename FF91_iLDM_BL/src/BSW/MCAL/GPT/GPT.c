/** Copyright (c) 2019 EMBITEL
**
** This software is the property of Embitel.
** It can not be used or duplicated without Embitel authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : GPT.c
** Module name  : GENERAL PURPOSE TIMER
** -------------------------------------------------------------------------------------------------
** Description : Include file of component GPT.c
**
** -------------------------------------------------------------------------------------------------
**
****************************************************************************************************
** R E V I S I O N  H I S T O R Y
****************************************************************************************************
** V01.00 10/08/2018
** - First release
*/

/**************************************** Inclusion files *****************************************/
#include "GPT.h"

/********************** Component configuration *******************************/

/* 1ms timer for normal operations */
static volatile uint32_t  GPT_Cntr1ms;
/* Timer trigger Flag */
static uint32_t GPT_CH0_TrigFlag;

/************************** Function definitions ******************************/
/*******************************************************************************
 *
** Function name: GPT_Init
** Description: Timer Initialization function
** Parameter index : Description
** Return value: None
** Remarks: global variables used, side effects
*******************************************************************************/
void GPT_init(void) 
{
	PCC->PCCn[PCC_LPIT_INDEX] = PCC_PCCn_PCS(6);    /* Clock Src = 6 (SPLL2_DIV2_CLK)*/
	PCC->PCCn[PCC_LPIT_INDEX] |= PCC_PCCn_CGC_MASK; /* Enable clk to GPT regs */
	GPT->MCR= MCR_MASK;    /* DBG_EN-0: Timer chans stop in Debug mode */
						   /* DOZE_EN=0: Timer chans are stopped in DOZE mode */
						   /* SW_RST=0: SW reset does not reset timer chans, regs */
						   /* M_CEN=1: enable module clk (allows writing other GPT regs)*/

	/* MIER=1: Timer Interrupt Enabled for Chan 0 */
	GPT->MIER = MIER_MASK;
	/* TVAL 0 Timeout period: 40M clocks */
	GPT->TMR[0].TVAL = TVAL_MASK;
	/* TCTRL=1: Timer channel is enabled */
	GPT->TMR[0].TCTRL = TCTRL_MASK;
							 

	/* IRQ48-GPT ch0: clr any pending IRQ*/
	S32_NVIC->ICPR[1U] = ICPR_MASK;
	/* IRQ48-GPT ch0: enable IRQ */
	S32_NVIC->ISER[1U]=ISER_MASK ;
	 /* IRQ48-GPT ch0: priority 10 of 0-15*/
	S32_NVIC->IP[48U] =IP_MASK ;
	
    /*Initialise the Variables */
	GPT_Cntr1ms = (uint32_t)0;	
	GPT_CH0_TrigFlag = FALSE;
}

/*******************************************************************************
** Function name: GPT_Sleep
** Description: GPT_Sleep
** Parameter index : None
** Return value: None
** Remarks: global variables used, side effects
*******************************************************************************/
void GPT_Sleep(void)
{
    /* clear interrupt flag.*/
	GPT->MIER  = 0u;
	/* disable  interrupt*/	
	GPT->MIER |= 1u;
	/* Stop timer   */    	
	GPT->SETTEN     = 0x14u;                             
}
/*******************************************************************************
** Function               : GPT_GetElapsedTime
** Description            : Calculates the time period difference in 1ms,
                            between provided input and the free running timer
** Parameter  timetMarkVal  : Mark timer value to know the time difference.
** Return value           : uint32 - Time difference in 1ms/bit resolution
** Remarks                : None
*******************************************************************************/
uint32_t GPT_GetElapsedTime(uint32_t timetMarkVal)
{
    uint32_t retDiff;             /* local to caluclate difference time in 1ms */
    uint32_t timetCt1msCpy;        /* local to copy running counter value */

    /* make a copy of the free running 1ms couter */
    timetCt1msCpy = GPT_Cntr1ms;

    /* has the running counter crossed the 32-bit limit at least once */
    if(timetCt1msCpy < timetMarkVal)
    {
        /* YES: then its an overflow, so take care wiht difference     */
        /* however multiple such overflows will be treated just as one */
        retDiff = timetCt1msCpy + ((uint32_t)0xFFFFFFFFU - timetMarkVal);
    }
    else
    {
        /* NO: no overflow, normal difference gives time elapsed */
        retDiff = timetCt1msCpy - timetMarkVal;
    }

    /* return time elapsed in 1ms resolution */
    return (retDiff);
}

/*******************************************************************************
** Function                 : LPIT0_Ch0_IRQHandler
** Description              : Scheduler timer tick ISR
** Parameter                : None
** Return value             : None
** Remarks                  : None
*******************************************************************************/
volatile uint32 Tmr_SessCntr1ms;
void LPIT0_Ch0_IRQHandler (void)
{
	/* Reset the counter to avoid overflow */
	if (GPT_Cntr1ms == 0xFFFFFFFFU)
	{
        GPT_Cntr1ms = 0;
	}
	else
	{
        GPT_Cntr1ms++;
		Tmr_SessCntr1ms++;
	}
	/* Increment global 1ms counter */
	/* Clear GPT timer flag 0 */
	 GPT->MSR |= LPIT_MSR_TIF0_MASK; 
	 
	if(FALSE == GPT_CH0_TrigFlag)
	{
		/* Set the Trigger Flag */
		GPT_CH0_TrigFlag = TRUE;
	}
	else
	{
        /* Do nothing */
	}         
}

/*******************************************************************************
** Function name: GPT_GetSystemTime
** Description:  Returns free running timer value
** Parameter index : Description
** Return value: GPT_Cntr1ms
*******************************************************************************/
uint32_t GPT_GetSystemTime(void)
{
	return(GPT_Cntr1ms);
}

/*******************************************************************************
** Function name: GPT_Get1msTrig
** Description:  Returns timer flag
** Parameter index : Description
** Return value: GPT_CH0_TrigFlag
*******************************************************************************/
int GPT_Get1msTrig(void)
{
    /* Return  GPT_CH0_TrigFlag status */
    return (GPT_CH0_TrigFlag);
}
/*******************************************************************************
** Function name: GPT_Reset1msTrig
** Description:  Reset Timer Flag
** Parameter index : Description
** Return value: None
*******************************************************************************/
void GPT_Reset1msTrig(void)
{
    /* Rset GPT_Ch0_TrigFlag */
	GPT_CH0_TrigFlag = FALSE;
}
/*******************************************************************************
** Function               : GPT_Get1ms

** Description            : Returns Timer_Get1ms status

** Parameter              : None

** Return value           : boolean - 1msTrig status

** Remarks                : None
*******************************************************************************/
uint32_t GPT_Get1ms(void)
{
    return (GPT_Cntr1ms);
}
