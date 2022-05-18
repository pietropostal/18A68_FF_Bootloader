/*******************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -----------------------------------------------------------------------------
** File Name : Mcu.h
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
/******************************************************************************/
/* To avoid multi-inclusions */
#ifndef MCU_H_
#define MCU_H_


/*************************** Inclusion files **********************************/
/* include peripheral declarations S32K144 */
#include "Platform_Types.h"
#include "Mcu_Cfg.h"

/* THE RANGE OF OSCILLATOR MUST BE SELECTED 1-3 RANGE VALUE 1=LOW FREQ
 * 2=MEDIUM 1-8MHz 3=8-40MHz */
#if(MCU_OSC_CLK< 1000000U)
#define MCU_RANGE_CLK         1U /*LOW FREQ */
#elif(MCU_OSC_CLK<= 8000000U)
#define MCU_RANGE_CLK         2U /*MEDIUM 1-8MHz */
#elif(MCU_OSC_CLK<= 40000000U)
#define MCU_RANGE_CLK         3U /*HIGH   8-40MHz */
#endif

/* MCU_Sldivi_Clock */
#define MCU_Sldivi_Clock       MCU_BUS_CLOCK_DIVI+1

/****** Below clock interfaces can be used by other modules for their calculations******/
/* Bus clock */
#define MCU_BUS_CLK 		 MCU_SYSTEM_CLK/(MCU_BUS_CLOCK_DIVI+1U)
/* Flash clock */
#define MCU_FLASH_CLK        MCU_SYSTEM_CLK/(MCU_Sldivi_Clock+1U)
/*MCU_SPLLDIVI2_CLK */
#define MCU_SPLLDIVI2_CLK    (MCU_SYSTEM_CLK*2U)/16U
/*MCU_SPLLDIVI1_CLK */
#define MCU_SPLLDIVI1_CLK    (MCU_SYSTEM_CLK*2U)/16U

/*******************************************************************************
Forward declaration of external startup function
*******************************************************************************/
extern void Mcu_Init(void);

#endif /* MCU_H_ */
