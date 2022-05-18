/*******************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -----------------------------------------------------------------------------
** File Name : Mcu.c
** Module Name : MCU
** -----------------------------------------------------------------------------
**
** Description : Micro-controller Clock Unit Module
**
** -----------------------------------------------------------------------------
**
** Documentation reference : LLD_MCU
**
********************************************************************************
** R E V I S I O N H I S T O R Y
********************************************************************************
** V01.00 06/08/2018
** - Baseline Created
*******************************************************************************/
/*************************** Inclusion files **********************************/

#include "Mcu.h"
static int Mcu_MultFactor,Mcu_DivFactor,Mcu_TempFlag=0;
void Mcu_Prescaling(void);
/*******************************************************************************
** FUNCTIONS **
*******************************************************************************/

/******************** Internal functions declarations *************************/

/************************** Function definitions ******************************/
/*******************************************************************************
** Function name: Mcu_Init.
** Description: Initialization of MCU Module.
** Parameter index : Initialization of Clock Registers.
** Return value: None
** Remarks: None
*******************************************************************************/
void Mcu_Init(void)
{
	/* SOSCDIV1 & SOSCDIV2 =1: divide by 1 */
	 SCG->SOSCDIV = SCG_SOSCDIV_SOSCDIV1(1U) | SCG_SOSCDIV_SOSCDIV2(1U);

	 /* configuring the external reference clock and and 1=LOW FREQ 2=MEDIUM
	  *  1-8MHz 3=8-40MHz*/
	 SCG->SOSCCFG =  SCG_SOSCCFG_RANGE(MCU_RANGE_CLK) | SCG_SOSCCFG_EREFS(1U);

	 /* Ensure SOSCCSR unlocked */
	 while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK);

	 /*  Enable oscillator */
	 SCG->SOSCCSR=SCG_SOSCCSR_SOSCEN(1U);

	 /* Wait for system  OSC clock valid */
	 while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK));

	 /* PLL Configurations*/

	 /* Ensure SPLLCSR unlocked */
	 while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK);

	 /* SPLLDIV1 divide by 16; SPLLDIV2 divide by 16 */
	 SCG->SPLLDIV=SCG_SPLLDIV_SPLLDIV1(5U) | SCG_SPLLDIV_SPLLDIV2(5U);

	 /*  Mcu_Prescaling function to get the values of multiplier  and
	  * divider values */
	 Mcu_Prescaling();

	 /* LOADING THE MULTIPLIER AND DIVIDER VALUES   */
	 SCG->SPLLCFG = SCG_SPLLCFG_MULT(Mcu_MultFactor) | SCG_SPLLCFG_PREDIV(Mcu_DivFactor);

	 /* Ensure SPLLCSR unlocked */
	 while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK);

	 /*  Enable SPLL */
	 SCG->SPLLCSR = SCG_SPLLCSR_SPLLEN(1U);

	 /* Wait for SPLL valid */
	  while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK));

	  /* Change to normal RUN mode with 8MHz SOSC, 80 MHz PLL*/
	  SCG->RCCR=  SCG_RCCR_SCS(6U) | SCG_RCCR_DIVCORE(1U) |
			  SCG_RCCR_DIVBUS(MCU_BUS_CLOCK_DIVI) | SCG_RCCR_DIVSLOW(MCU_Sldivi_Clock);

	 while (((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) != 6U)
	 {
		 /* d0 nothing  checking the flag*/
	 }
}

/*******************************************************************************
** Function name: Mcu_Prescaling.
** Description: Pre-scaling the clock according to the system clock required.
** Parameter index : Calculation of multiplier and divisor values.
** Return value: None
** Remarks: None
*******************************************************************************/

void Mcu_Prescaling(void)
{
int i,j,clkout;

for(i=1U;i<=8U;i++)
{
	for(j=16U;j<=47U;j++)
	{
		clkout=(MCU_OSC_CLK*j)/i;


				if(MCU_SYSTEM_CLK*4==clkout)
				{
					Mcu_DivFactor=i-1;
					Mcu_MultFactor=j+16;
					Mcu_TempFlag=1;
					break;


				}
	}

	if(Mcu_TempFlag==1)
	{
		Mcu_TempFlag=0;
		break;
	}
}

}
