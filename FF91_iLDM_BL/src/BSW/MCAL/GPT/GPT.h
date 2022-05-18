/** Copyright (c) 2019 EMBITEL
**
** This software is the property of Embitel.
** It can not be used or duplicated without Embitel authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : GPT.h
** Module name  : GENERAL PURPOSE TIMER
** -------------------------------------------------------------------------------------------------
** Description : Include file of component GPT.h
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
/* To avoid multi-inclusions */
#ifndef GPT_H
#define GPT_H
#include "Platform_Types.h"
#include "GPT_Cfg.h"


#define     GPT   (LPIT0)

#define     ICPR_MASK    (1U << (48U % 32U))

#define     ISER_MASK    (1 << (48U % 32U))

#define     IP_MASK      (0xA0)

#define     MCR_MASK     (0x00000001U)

#define    MIER_MASK   ( 0x00000001)

#define    TCTRL_MASK  (0x00000001U)

extern volatile uint32 Tmr_SessCntr1ms;
//************************** Function definitions ******************************/
/***********************************************************
** Function name: GPT_init
** Description: GPT_init
** Parameter index : Description
** Return value: None
** Remarks: global variables used, side effects
*******************************************************************************/
extern void GPT_init(void);
/*******************************************************************************
** Function name: GPT_Sleep
** Description: GPT_Sleep
** Parameter index : Description
** Return value: None
** Remarks: global variables used, side effects
*******************************************************************************/
extern void GPT_Sleep(void);
/*******************************************************************************
** Function                 : GPT_GetElapsedTime
** Description              : Time period difference in 1ms
** Parameter                : None
** Return value             : None
** Remarks                  : None
*************************************************************/

extern uint32_t GPT_GetElapsedTime(uint32_t timetMarkVal);
/***********************************************************
** Function name: GPT_GetSystemTime
** Description:  Returns free running timer value
** Parameter index : Description
** Return value: GPT_Cntr1ms
** Remarks: global variables used, side effects
*******************************************************************************/
extern uint32_t GPT_GetSystemTime(void);
/*******************************************************************************
** Function name: GPT_Get1msTrig
** Description:  Returns timer flag
** Parameter index : Description
** Return value: GPT_Ch0_TrigFlag
*******************************************************************************/
extern int GPT_Get1msTrig(void);
/*******************************************************************************
** Function name: GPT_Reset1msTrig
** Description:  Reset Timer Flag
** Parameter index : Description
** Return value: None
*******************************************************************************/
void GPT_Reset1msTrig(void);
/***********************************************************
** Function name: LPITO_Ch0_IRQHandler
** Description: LPITO_Ch0_IRQHandler
** Parameter index : Description
** Return value: None
** Remarks: global variables used, side effects
*******************************************************************************/
extern void LPITO_Ch0_IRQHandler (void) ;
extern uint32_t GPT_Get1ms(void);
#endif /*end of GPT.H*/

