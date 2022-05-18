/*
 *    WEBASTO GROUP, MCC, COPYRIGHT (c) 2017
 *    ALL RIGHTS RESERVED
 *
 */

/**
* \file IO_S32K144_100pin_LQFP.h
* \ingroup grpXXX
* \brief Pin definitions.
*
* $Author:   hovanj  $
* $Revision:   1.0  $
* $Date:   Jun 05 2014 11:53:30  $
*/

#ifndef __IO_H
#define __IO_H

/* === INCLUDES ============================================================= */
#include "board.h"
//#include "types.h"

/* === TYPEDEFS ============================================================= */
/* none */
/* === SYMBOLIC CONSTANTS =================================================== */
#define PORT_IRQC_MASK            0x000F0000
#define PORT_IRQC_FALLING         0x000A0000
#define PORT_IRQC_RISING          0x00090000
#define PORT_IRQC_EITHER          0x000B0000

#define PORT_MUX_MASK             0x00000700
#define PORT_MUX_PIN_DISABLED     0x00000000
#define PORT_MUX_PIN_ALT1_GPIO    0x00000100
#define PORT_MUX_PIN_ALT2         0x00000200

#define PORT_PULL_MASK            0x00000003
#define PORT_PULL_UP              0x00000003
#define PORT_PULL_DOWN            0x00000002

#define PORT_PIN_0                0x00000001
#define PORT_PIN_1                0x00000002
#define PORT_PIN_2                0x00000004
#define PORT_PIN_3                0x00000008
#define PORT_PIN_4                0x00000010
#define PORT_PIN_5                0x00000020
#define PORT_PIN_6                0x00000040
#define PORT_PIN_7                0x00000080
#define PORT_PIN_8                0x00000100
#define PORT_PIN_9                0x00000200
#define PORT_PIN_10               0x00000400
#define PORT_PIN_11               0x00000800
#define PORT_PIN_12               0x00001000
#define PORT_PIN_13               0x00002000
#define PORT_PIN_14               0x00004000
#define PORT_PIN_15               0x00008000
#define PORT_PIN_16               0x00010000
#define PORT_PIN_17               0x00020000

/* === EXPORTED MACROS ====================================================== */

//info:
// PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clock for PORT D */
// PORTD->PCR[0] =  0x00000100;  /* Port D0:  MUX = ALT1, GPIO */
// PTD->PDDR |= 1<<0;            /* Port D0:  Data Direction= output */
// PTD->PTOR |= 1<<0;            /* Toggle output on port D0 */

/*___PIN 001: PTE16/LPUART1_RTS/LPSPI2_SIN/FTM2_CH7/FXIO_D3/TRGMUX_OUT7_______*/
#define IO_PIN1_toOUT()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[16] &= ~PORT_MUX_MASK; PORTE->PCR[16] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_16;}
#define IO_PIN1_toIN()             {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[16] &= ~PORT_MUX_MASK; PORTE->PCR[16] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_16;}
#define IO_PIN1_toHI()             {PTE->PSOR |= PORT_PIN_16;}
#define IO_PIN1_toLO()             {PTE->PCOR |= PORT_PIN_16;}
#define IO_PIN1_TOGGLE()           {PTE->PTOR |= PORT_PIN_16;}
#define IO_PIN1_getINPUT()         {(PTE->PDIR & PORT_PIN_16) >> 16;}
#define IO_PIN1_isHI()             {(PTE->PDIR & PORT_PIN_16) == PORT_PIN_16;}
#define IO_PIN1_isLO()             {(PTE->PDIR & PORT_PIN_16) != PORT_PIN_16;}
#define IO_PIN1_PULLoff()          {PORTE->PCR[16] &= ~PORT_PULL_MASK;}
#define IO_PIN1_PULLup()           {PORTE->PCR[16] &= ~PORT_PULL_MASK; PORTE->PCR[16] |= PORT_PULL_UP;}
#define IO_PIN1_PULLdown()         {PORTE->PCR[16] &= ~PORT_PULL_MASK; PORTE->PCR[16] |= PORT_PULL_DOWN;}
#define IO_PIN1_INToff()           {PORTE->PCR[16] &= ~PORT_IRQC_MASK;}
#define IO_PIN1_INTfalling()       {PORTE->PCR[16] &= ~PORT_IRQC_MASK; PORTE->PCR[16] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN1_INTrising()        {PORTE->PCR[16] &= ~PORT_IRQC_MASK; PORTE->PCR[16] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN1_INTany()           {PORTE->PCR[16] &= ~PORT_IRQC_MASK; PORTE->PCR[16] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN1_INTclear()         {PORTE->PCR[16] |= 0x01000000;}

/*___PIN 002: PTE15/LPUART1_CTS/LPSPI2_SCK/FTM2_CH6/FXIO_D2/TRGMUX_OUT6_______*/
#define IO_PIN2_toOUT()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[15] &= ~PORT_MUX_MASK; PORTE->PCR[15] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_15;}
#define IO_PIN2_toIN()             {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[15] &= ~PORT_MUX_MASK; PORTE->PCR[15] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_15;}
#define IO_PIN2_toHI()             {PTE->PSOR |= PORT_PIN_15;}
#define IO_PIN2_toLO()             {PTE->PCOR |= PORT_PIN_15;}
#define IO_PIN2_TOGGLE()           {PTE->PTOR |= PORT_PIN_15;}
#define IO_PIN2_getINPUT()         {(PTE->PDIR & PORT_PIN_15) >> 15;}
#define IO_PIN2_isHI()             {(PTE->PDIR & PORT_PIN_15) == PORT_PIN_15;}
#define IO_PIN2_isLO()             {(PTE->PDIR & PORT_PIN_15) != PORT_PIN_15;}
#define IO_PIN2_PULLoff()          {PORTE->PCR[15] &= ~PORT_PULL_MASK;}
#define IO_PIN2_PULLup()           {PORTE->PCR[15] &= ~PORT_PULL_MASK; PORTE->PCR[15] |= PORT_PULL_UP;}
#define IO_PIN2_PULLdown()         {PORTE->PCR[15] &= ~PORT_PULL_MASK; PORTE->PCR[15] |= PORT_PULL_DOWN;}
#define IO_PIN2_INToff()           {PORTE->PCR[15] &= ~PORT_IRQC_MASK;}
#define IO_PIN2_INTfalling()       {PORTE->PCR[15] &= ~PORT_IRQC_MASK; PORTE->PCR[15] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN2_INTrising()        {PORTE->PCR[15] &= ~PORT_IRQC_MASK; PORTE->PCR[15] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN2_INTany()           {PORTE->PCR[15] &= ~PORT_IRQC_MASK; PORTE->PCR[15] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN2_INTclear()         {PORTE->PCR[15] |= 0x01000000;}

/*___PIN 003: PTD1/FTM0_CH3/LPSPI1_SIN/FTM2_CH1/FXIO_D1/TRGMUX_OUT2___________*/
#define IO_PIN3_toOUT()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[1] &= ~PORT_MUX_MASK; PORTD->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_1;}
#define IO_PIN3_toIN()             {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[1] &= ~PORT_MUX_MASK; PORTD->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_1;}
#define IO_PIN3_toHI()             {PTD->PSOR |= PORT_PIN_1;}
#define IO_PIN3_toLO()             {PTD->PCOR |= PORT_PIN_1;}
#define IO_PIN3_TOGGLE()           {PTD->PTOR |= PORT_PIN_1;}
#define IO_PIN3_getINPUT()         {(PTD->PDIR & PORT_PIN_1) >> 1;}
#define IO_PIN3_isHI()             {(PTD->PDIR & PORT_PIN_1) == PORT_PIN_1;}
#define IO_PIN3_isLO()             {(PTD->PDIR & PORT_PIN_1) != PORT_PIN_1;}
#define IO_PIN3_PULLoff()          {PORTD->PCR[1] &= ~PORT_PULL_MASK;}
#define IO_PIN3_PULLup()           {PORTD->PCR[1] &= ~PORT_PULL_MASK; PORTD->PCR[1] |= PORT_PULL_UP;}
#define IO_PIN3_PULLdown()         {PORTD->PCR[1] &= ~PORT_PULL_MASK; PORTD->PCR[1] |= PORT_PULL_DOWN;}
#define IO_PIN3_INToff()           {PORTD->PCR[1] &= ~PORT_IRQC_MASK;}
#define IO_PIN3_INTfalling()       {PORTD->PCR[1] &= ~PORT_IRQC_MASK; PORTD->PCR[1] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN3_INTrising()        {PORTD->PCR[1] &= ~PORT_IRQC_MASK; PORTD->PCR[1] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN3_INTany()           {PORTD->PCR[1] &= ~PORT_IRQC_MASK; PORTD->PCR[1] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN3_INTclear()         {PORTD->PCR[1] |= 0x01000000;}

/*___PIN 004: PTD0/FTM0_CH2/LPSPI1_SCK/FTM2_CH0/FXIO_D0/TRGMUX_OUT1___________*/
#define IO_PIN4_toOUT()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[0] &= ~PORT_MUX_MASK; PORTD->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_0;}
#define IO_PIN4_toIN()             {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[0] &= ~PORT_MUX_MASK; PORTD->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_0;}
#define IO_PIN4_toHI()             {PTD->PSOR |= PORT_PIN_0;}
#define IO_PIN4_toLO()             {PTD->PCOR |= PORT_PIN_0;}
#define IO_PIN4_TOGGLE()           {PTD->PTOR |= PORT_PIN_0;}
#define IO_PIN4_getINPUT()         {(PTD->PDIR & PORT_PIN_0) >> 0;}
#define IO_PIN4_isHI()             {(PTD->PDIR & PORT_PIN_0) == PORT_PIN_0;}
#define IO_PIN4_isLO()             {(PTD->PDIR & PORT_PIN_0) != PORT_PIN_0;}
#define IO_PIN4_PULLoff()          {PORTD->PCR[0] &= ~PORT_PULL_MASK;}
#define IO_PIN4_PULLup()           {PORTD->PCR[0] &= ~PORT_PULL_MASK; PORTD->PCR[0] |= PORT_PULL_UP;}
#define IO_PIN4_PULLdown()         {PORTD->PCR[0] &= ~PORT_PULL_MASK; PORTD->PCR[0] |= PORT_PULL_DOWN;}
#define IO_PIN4_INToff()           {PORTD->PCR[0] &= ~PORT_IRQC_MASK;}
#define IO_PIN4_INTfalling()       {PORTD->PCR[0] &= ~PORT_IRQC_MASK; PORTD->PCR[0] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN4_INTrising()        {PORTD->PCR[0] &= ~PORT_IRQC_MASK; PORTD->PCR[0] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN4_INTany()           {PORTD->PCR[0] &= ~PORT_IRQC_MASK; PORTD->PCR[0] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN4_INTclear()         {PORTD->PCR[0] |= 0x01000000;}

/*___PIN 005: PTE11/LPSPI2_PCS0/LPTMR0_ALT1/FTM2_CH5/FXIO_D5/TRGMUX_OUT5______*/
#define IO_PIN5_toOUT()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[11] &= ~PORT_MUX_MASK; PORTE->PCR[11] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_11;}
#define IO_PIN5_toIN()             {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[11] &= ~PORT_MUX_MASK; PORTE->PCR[11] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_11;}
#define IO_PIN5_toHI()             {PTE->PSOR |= PORT_PIN_11;}
#define IO_PIN5_toLO()             {PTE->PCOR |= PORT_PIN_11;}
#define IO_PIN5_TOGGLE()           {PTE->PTOR |= PORT_PIN_11;}
#define IO_PIN5_getINPUT()         {(PTE->PDIR & PORT_PIN_11) >> 11;}
#define IO_PIN5_isHI()             {(PTE->PDIR & PORT_PIN_11) == PORT_PIN_11;}
#define IO_PIN5_isLO()             {(PTE->PDIR & PORT_PIN_11) != PORT_PIN_11;}
#define IO_PIN5_PULLoff()          {PORTE->PCR[11] &= ~PORT_PULL_MASK;}
#define IO_PIN5_PULLup()           {PORTE->PCR[11] &= ~PORT_PULL_MASK; PORTE->PCR[11] |= PORT_PULL_UP;}
#define IO_PIN5_PULLdown()         {PORTE->PCR[11] &= ~PORT_PULL_MASK; PORTE->PCR[11] |= PORT_PULL_DOWN;}
#define IO_PIN5_INToff()           {PORTE->PCR[11] &= ~PORT_IRQC_MASK;}
#define IO_PIN5_INTfalling()       {PORTE->PCR[11] &= ~PORT_IRQC_MASK; PORTE->PCR[11] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN5_INTrising()        {PORTE->PCR[11] &= ~PORT_IRQC_MASK; PORTE->PCR[11] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN5_INTany()           {PORTE->PCR[11] &= ~PORT_IRQC_MASK; PORTE->PCR[11] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN5_INTclear()         {PORTE->PCR[11] |= 0x01000000;}

/*___PIN 006: PTE10/CLKOUT/LPSPI2_PCS1/FTM2_CH4/FXIO_D4/TRGMUX_OUT4___________*/
#define IO_PIN6_toOUT()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[10] &= ~PORT_MUX_MASK; PORTE->PCR[10] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_10;}
#define IO_PIN6_toIN()             {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[10] &= ~PORT_MUX_MASK; PORTE->PCR[10] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_10;}
#define IO_PIN6_toHI()             {PTE->PSOR |= PORT_PIN_10;}
#define IO_PIN6_toLO()             {PTE->PCOR |= PORT_PIN_10;}
#define IO_PIN6_TOGGLE()           {PTE->PTOR |= PORT_PIN_10;}
#define IO_PIN6_getINPUT()         {(PTE->PDIR & PORT_PIN_10) >> 10;}
#define IO_PIN6_isHI()             {(PTE->PDIR & PORT_PIN_10) == PORT_PIN_10;}
#define IO_PIN6_isLO()             {(PTE->PDIR & PORT_PIN_10) != PORT_PIN_10;}
#define IO_PIN6_PULLoff()          {PORTE->PCR[10] &= ~PORT_PULL_MASK;}
#define IO_PIN6_PULLup()           {PORTE->PCR[10] &= ~PORT_PULL_MASK; PORTE->PCR[10] |= PORT_PULL_UP;}
#define IO_PIN6_PULLdown()         {PORTE->PCR[10] &= ~PORT_PULL_MASK; PORTE->PCR[10] |= PORT_PULL_DOWN;}
#define IO_PIN6_INToff()           {PORTE->PCR[10] &= ~PORT_IRQC_MASK;}
#define IO_PIN6_INTfalling()       {PORTE->PCR[10] &= ~PORT_IRQC_MASK; PORTE->PCR[10] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN6_INTrising()        {PORTE->PCR[10] &= ~PORT_IRQC_MASK; PORTE->PCR[10] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN6_INTany()           {PORTE->PCR[10] &= ~PORT_IRQC_MASK; PORTE->PCR[10] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN6_INTclear()         {PORTE->PCR[10] |= 0x01000000;}

/*___PIN 007: PTE13/LPSPI2_PCS2/FTM2_FLT0_____________________________________*/
#define IO_PIN7_toOUT()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[13] &= ~PORT_MUX_MASK; PORTE->PCR[13] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_13;}
#define IO_PIN7_toIN()             {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[13] &= ~PORT_MUX_MASK; PORTE->PCR[13] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_13;}
#define IO_PIN7_toHI()             {PTE->PSOR |= PORT_PIN_13;}
#define IO_PIN7_toLO()             {PTE->PCOR |= PORT_PIN_13;}
#define IO_PIN7_TOGGLE()           {PTE->PTOR |= PORT_PIN_13;}
#define IO_PIN7_getINPUT()         {(PTE->PDIR & PORT_PIN_13) >> 13;}
#define IO_PIN7_isHI()             {(PTE->PDIR & PORT_PIN_13) == PORT_PIN_13;}
#define IO_PIN7_isLO()             {(PTE->PDIR & PORT_PIN_13) != PORT_PIN_13;}
#define IO_PIN7_PULLoff()          {PORTE->PCR[13] &= ~PORT_PULL_MASK;}
#define IO_PIN7_PULLup()           {PORTE->PCR[13] &= ~PORT_PULL_MASK; PORTE->PCR[13] |= PORT_PULL_UP;}
#define IO_PIN7_PULLdown()         {PORTE->PCR[13] &= ~PORT_PULL_MASK; PORTE->PCR[13] |= PORT_PULL_DOWN;}
#define IO_PIN7_INToff()           {PORTE->PCR[13] &= ~PORT_IRQC_MASK;}
#define IO_PIN7_INTfalling()       {PORTE->PCR[13] &= ~PORT_IRQC_MASK; PORTE->PCR[13] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN7_INTrising()        {PORTE->PCR[13] &= ~PORT_IRQC_MASK; PORTE->PCR[13] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN7_INTany()           {PORTE->PCR[13] &= ~PORT_IRQC_MASK; PORTE->PCR[13] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN7_INTclear()         {PORTE->PCR[13] |= 0x01000000;}

/*___PIN 008: PTE5/TCLK2/FTM2_QD_PHA/FTM2_CH3/CAN0_TX/FXIO_D7/EWM_IN__________*/
#define IO_PIN8_toOUT()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[5] &= ~PORT_MUX_MASK; PORTE->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_5;}
#define IO_PIN8_toIN()             {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[5] &= ~PORT_MUX_MASK; PORTE->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_5;}
#define IO_PIN8_toHI()             {PTE->PSOR |= PORT_PIN_5;}
#define IO_PIN8_toLO()             {PTE->PCOR |= PORT_PIN_5;}
#define IO_PIN8_TOGGLE()           {PTE->PTOR |= PORT_PIN_5;}
#define IO_PIN8_getINPUT()         {(PTE->PDIR & PORT_PIN_5) >> 5;}
#define IO_PIN8_isHI()             {(PTE->PDIR & PORT_PIN_5) == PORT_PIN_5;}
#define IO_PIN8_isLO()             {(PTE->PDIR & PORT_PIN_5) != PORT_PIN_5;}
#define IO_PIN8_PULLoff()          {PORTE->PCR[5] &= ~PORT_PULL_MASK;}
#define IO_PIN8_PULLup()           {PORTE->PCR[5] &= ~PORT_PULL_MASK; PORTE->PCR[5] |= PORT_PULL_UP;}
#define IO_PIN8_PULLdown()         {PORTE->PCR[5] &= ~PORT_PULL_MASK; PORTE->PCR[5] |= PORT_PULL_DOWN;}
#define IO_PIN8_INToff()           {PORTE->PCR[5] &= ~PORT_IRQC_MASK;}
#define IO_PIN8_INTfalling()       {PORTE->PCR[5] &= ~PORT_IRQC_MASK; PORTE->PCR[5] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN8_INTrising()        {PORTE->PCR[5] &= ~PORT_IRQC_MASK; PORTE->PCR[5] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN8_INTany()           {PORTE->PCR[5] &= ~PORT_IRQC_MASK; PORTE->PCR[5] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN8_INTclear()         {PORTE->PCR[5] |= 0x01000000;}

/*___PIN 009: PTE4/FTM2_QD_PHB/FTM2_CH2/CAN0_RX/FXIO_D6/EWM_OUT_b_____________*/
#define IO_PIN9_toOUT()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[4] &= ~PORT_MUX_MASK; PORTE->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_4;}
#define IO_PIN9_toIN()             {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[4] &= ~PORT_MUX_MASK; PORTE->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_4;}
#define IO_PIN9_toHI()             {PTE->PSOR |= PORT_PIN_4;}
#define IO_PIN9_toLO()             {PTE->PCOR |= PORT_PIN_4;}
#define IO_PIN9_TOGGLE()           {PTE->PTOR |= PORT_PIN_4;}
#define IO_PIN9_getINPUT()         {(PTE->PDIR & PORT_PIN_4) >> 4;}
#define IO_PIN9_isHI()             {(PTE->PDIR & PORT_PIN_4) == PORT_PIN_4;}
#define IO_PIN9_isLO()             {(PTE->PDIR & PORT_PIN_4) != PORT_PIN_4;}
#define IO_PIN9_PULLoff()          {PORTE->PCR[4] &= ~PORT_PULL_MASK;}
#define IO_PIN9_PULLup()           {PORTE->PCR[4] &= ~PORT_PULL_MASK; PORTE->PCR[4] |= PORT_PULL_UP;}
#define IO_PIN9_PULLdown()         {PORTE->PCR[4] &= ~PORT_PULL_MASK; PORTE->PCR[4] |= PORT_PULL_DOWN;}
#define IO_PIN9_INToff()           {PORTE->PCR[4] &= ~PORT_IRQC_MASK;}
#define IO_PIN9_INTfalling()       {PORTE->PCR[4] &= ~PORT_IRQC_MASK; PORTE->PCR[4] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN9_INTrising()        {PORTE->PCR[4] &= ~PORT_IRQC_MASK; PORTE->PCR[4] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN9_INTany()           {PORTE->PCR[4] &= ~PORT_IRQC_MASK; PORTE->PCR[4] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN9_INTclear()         {PORTE->PCR[4] |= 0x01000000;}

/*___PIN 010: VDD_____________________________________________________________*/

/*___PIN 011: VDDA____________________________________________________________*/

/*___PIN 012: VREFH___________________________________________________________*/

/*___PIN 013: VREFL___________________________________________________________*/

/*___PIN 014: VSS_____________________________________________________________*/

/*___PIN 015: PTB7/LPI2C0_SCL/EXTAL___________________________________________*/
#define IO_PIN15_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[7] &= ~PORT_MUX_MASK; PORTB->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_7;}
#define IO_PIN15_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[7] &= ~PORT_MUX_MASK; PORTB->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_7;}
#define IO_PIN15_toHI()            {PTB->PSOR |= PORT_PIN_7;}
#define IO_PIN15_toLO()            {PTB->PCOR |= PORT_PIN_7;}
#define IO_PIN15_TOGGLE()          {PTB->PTOR |= PORT_PIN_7;}
#define IO_PIN15_getINPUT()        {(PTB->PDIR & PORT_PIN_7) >> 7U;}
#define IO_PIN15_isHI()            {(PTB->PDIR & PORT_PIN_7) == PORT_PIN_7;}
#define IO_PIN15_isLO()            {(PTB->PDIR & PORT_PIN_7) != PORT_PIN_7;}
#define IO_PIN15_PULLoff()         {PORTB->PCR[7] &= ~PORT_PULL_MASK;}
#define IO_PIN15_PULLup()          {PORTB->PCR[7] &= ~PORT_PULL_MASK; PORTB->PCR[7] |= PORT_PULL_UP;}
#define IO_PIN15_PULLdown()        {PORTB->PCR[7] &= ~PORT_PULL_MASK; PORTB->PCR[7] |= PORT_PULL_DOWN;}
#define IO_PIN15_INToff()          {PORTB->PCR[7] &= ~PORT_IRQC_MASK;}
#define IO_PIN15_INTfalling()      {PORTB->PCR[7] &= ~PORT_IRQC_MASK; PORTB->PCR[7] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN15_INTrising()       {PORTB->PCR[7] &= ~PORT_IRQC_MASK; PORTB->PCR[7] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN15_INTany()          {PORTB->PCR[7] &= ~PORT_IRQC_MASK; PORTB->PCR[7] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN15_INTclear()        {PORTB->PCR[7] |= 0x01000000;}

/*___PIN 016: PTB6/LPI2C0_SDA/XTAL____________________________________________*/
#define IO_PIN16_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[6] &= ~PORT_MUX_MASK; PORTB->PCR[6] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_6;}
#define IO_PIN16_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[6] &= ~PORT_MUX_MASK; PORTB->PCR[6] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_6;}
#define IO_PIN16_toHI()            {PTB->PSOR |= PORT_PIN_6;}
#define IO_PIN16_toLO()            {PTB->PCOR |= PORT_PIN_6;}
#define IO_PIN16_TOGGLE()          {PTB->PTOR |= PORT_PIN_6;}
#define IO_PIN16_getINPUT()        {(PTB->PDIR & PORT_PIN_6) >> 6U;}
#define IO_PIN16_isHI()            {(PTB->PDIR & PORT_PIN_6) == PORT_PIN_6;}
#define IO_PIN16_isLO()            {(PTB->PDIR & PORT_PIN_6) != PORT_PIN_6;}
#define IO_PIN16_PULLoff()         {PORTB->PCR[6] &= ~PORT_PULL_MASK;}
#define IO_PIN16_PULLup()          {PORTB->PCR[6] &= ~PORT_PULL_MASK; PORTB->PCR[6] |= PORT_PULL_UP;}
#define IO_PIN16_PULLdown()        {PORTB->PCR[6] &= ~PORT_PULL_MASK; PORTB->PCR[6] |= PORT_PULL_DOWN;}
#define IO_PIN16_INToff()          {PORTB->PCR[6] &= ~PORT_IRQC_MASK;}
#define IO_PIN16_INTfalling()      {PORTB->PCR[6] &= ~PORT_IRQC_MASK; PORTB->PCR[6] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN16_INTrising()       {PORTB->PCR[6] &= ~PORT_IRQC_MASK; PORTB->PCR[6] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN16_INTany()          {PORTB->PCR[6] &= ~PORT_IRQC_MASK; PORTB->PCR[6] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN16_INTclear()        {PORTB->PCR[6] |= 0x01000000;}

/*___PIN 017: PTE14/FTM0_FLT1/FTM2_FLT1_______________________________________*/
#define IO_PIN17_toOUT()           {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[14] &= ~PORT_MUX_MASK; PORTE->PCR[14] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_14;}
#define IO_PIN17_toIN()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[14] &= ~PORT_MUX_MASK; PORTE->PCR[14] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_14;}
#define IO_PIN17_toHI()            {PTE->PSOR |= PORT_PIN_14;}
#define IO_PIN17_toLO()            {PTE->PCOR |= PORT_PIN_14;}
#define IO_PIN17_TOGGLE()          {PTE->PTOR |= PORT_PIN_14;}
#define IO_PIN17_getINPUT()        {(PTE->PDIR & PORT_PIN_14) >> 14U;}
#define IO_PIN17_isHI()            {(PTE->PDIR & PORT_PIN_14) == PORT_PIN_14;}
#define IO_PIN17_isLO()            {(PTE->PDIR & PORT_PIN_14) != PORT_PIN_14;}
#define IO_PIN17_PULLoff()         {PORTE->PCR[14] &= ~PORT_PULL_MASK;}
#define IO_PIN17_PULLup()          {PORTE->PCR[14] &= ~PORT_PULL_MASK; PORTE->PCR[14] |= PORT_PULL_UP;}
#define IO_PIN17_PULLdown()        {PORTE->PCR[14] &= ~PORT_PULL_MASK; PORTE->PCR[14] |= PORT_PULL_DOWN;}
#define IO_PIN17_INToff()          {PORTE->PCR[14] &= ~PORT_IRQC_MASK;}
#define IO_PIN17_INTfalling()      {PORTE->PCR[14] &= ~PORT_IRQC_MASK; PORTE->PCR[14] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN17_INTrising()       {PORTE->PCR[14] &= ~PORT_IRQC_MASK; PORTE->PCR[14] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN17_INTany()          {PORTE->PCR[14] &= ~PORT_IRQC_MASK; PORTE->PCR[14] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN17_INTclear()        {PORTE->PCR[14] |= 0x01000000;}

/*___PIN 018: PTE3/FTM0_FLT0/LPUART2_RTS/FTM2_FLT0/TRGMUX_IN6/CMP0_OUT________*/
#define IO_PIN18_toOUT()           {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[3] &= ~PORT_MUX_MASK; PORTE->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_3;}
#define IO_PIN18_toIN()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[3] &= ~PORT_MUX_MASK; PORTE->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_3;}
#define IO_PIN18_toHI()            {PTE->PSOR |= PORT_PIN_3;}
#define IO_PIN18_toLO()            {PTE->PCOR |= PORT_PIN_3;}
#define IO_PIN18_TOGGLE()          {PTE->PTOR |= PORT_PIN_3;}
#define IO_PIN18_getINPUT()        {(PTE->PDIR & PORT_PIN_3) >> 3U;}
#define IO_PIN18_isHI()            {(PTE->PDIR & PORT_PIN_3) == PORT_PIN_3;}
#define IO_PIN18_isLO()            {(PTE->PDIR & PORT_PIN_3) != PORT_PIN_3;}
#define IO_PIN18_PULLoff()         {PORTE->PCR[3] &= ~PORT_PULL_MASK;}
#define IO_PIN18_PULLup()          {PORTE->PCR[3] &= ~PORT_PULL_MASK; PORTE->PCR[3] |= PORT_PULL_UP;}
#define IO_PIN18_PULLdown()        {PORTE->PCR[3] &= ~PORT_PULL_MASK; PORTE->PCR[3] |= PORT_PULL_DOWN;}
#define IO_PIN18_INToff()          {PORTE->PCR[3] &= ~PORT_IRQC_MASK;}
#define IO_PIN18_INTfalling()      {PORTE->PCR[3] &= ~PORT_IRQC_MASK; PORTE->PCR[3] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN18_INTrising()       {PORTE->PCR[3] &= ~PORT_IRQC_MASK; PORTE->PCR[3] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN18_INTany()          {PORTE->PCR[3] &= ~PORT_IRQC_MASK; PORTE->PCR[3] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN18_INTclear()        {PORTE->PCR[3] |= 0x01000000;}

/*___PIN 019: PTE12/FTM0_FLT3/LPUART2_TX______________________________________*/
#define IO_PIN19_toOUT()           {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[12] &= ~PORT_MUX_MASK; PORTE->PCR[12] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_12;}
#define IO_PIN19_toIN()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[12] &= ~PORT_MUX_MASK; PORTE->PCR[12] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_12;}
#define IO_PIN19_toHI()            {PTE->PSOR |= PORT_PIN_12;}
#define IO_PIN19_toLO()            {PTE->PCOR |= PORT_PIN_12;}
#define IO_PIN19_TOGGLE()          {PTE->PTOR |= PORT_PIN_12;}
#define IO_PIN19_getINPUT()        {(PTE->PDIR & PORT_PIN_12) >> 12U;}
#define IO_PIN19_isHI()            {(PTE->PDIR & PORT_PIN_12) == PORT_PIN_12;}
#define IO_PIN19_isLO()            {(PTE->PDIR & PORT_PIN_12) != PORT_PIN_12;}
#define IO_PIN19_PULLoff()         {PORTE->PCR[12] &= ~PORT_PULL_MASK;}
#define IO_PIN19_PULLup()          {PORTE->PCR[12] &= ~PORT_PULL_MASK; PORTE->PCR[12] |= PORT_PULL_UP;}
#define IO_PIN19_PULLdown()        {PORTE->PCR[12] &= ~PORT_PULL_MASK; PORTE->PCR[12] |= PORT_PULL_DOWN;}
#define IO_PIN19_INToff()          {PORTE->PCR[12] &= ~PORT_IRQC_MASK;}
#define IO_PIN19_INTfalling()      {PORTE->PCR[12] &= ~PORT_IRQC_MASK; PORTE->PCR[12] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN19_INTrising()       {PORTE->PCR[12] &= ~PORT_IRQC_MASK; PORTE->PCR[12] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN19_INTany()          {PORTE->PCR[12] &= ~PORT_IRQC_MASK; PORTE->PCR[12] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN19_INTclear()        {PORTE->PCR[12] |= 0x01000000;}

/*___PIN 020: PTD17/FTM0_FLT2/LPUART2_RX______________________________________*/
#define IO_PIN20_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[17] &= ~PORT_MUX_MASK; PORTD->PCR[17] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_17;}
#define IO_PIN20_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[17] &= ~PORT_MUX_MASK; PORTD->PCR[17] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_17;}
#define IO_PIN20_toHI()            {PTD->PSOR |= PORT_PIN_17;}
#define IO_PIN20_toLO()            {PTD->PCOR |= PORT_PIN_17;}
#define IO_PIN20_TOGGLE()          {PTD->PTOR |= PORT_PIN_17;}
#define IO_PIN20_getINPUT()        {(PTD->PDIR & PORT_PIN_17) >> 17U;}
#define IO_PIN20_isHI()            {(PTD->PDIR & PORT_PIN_17) == PORT_PIN_17;}
#define IO_PIN20_isLO()            {(PTD->PDIR & PORT_PIN_17) != PORT_PIN_17;}
#define IO_PIN20_PULLoff()         {PORTD->PCR[17] &= ~PORT_PULL_MASK;}
#define IO_PIN20_PULLup()          {PORTD->PCR[17] &= ~PORT_PULL_MASK; PORTD->PCR[17] |= PORT_PULL_UP;}
#define IO_PIN20_PULLdown()        {PORTD->PCR[17] &= ~PORT_PULL_MASK; PORTD->PCR[17] |= PORT_PULL_DOWN;}
#define IO_PIN20_INToff()          {PORTD->PCR[17] &= ~PORT_IRQC_MASK;}
#define IO_PIN20_INTfalling()      {PORTD->PCR[17] &= ~PORT_IRQC_MASK; PORTD->PCR[17] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN20_INTrising()       {PORTD->PCR[17] &= ~PORT_IRQC_MASK; PORTD->PCR[17] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN20_INTany()          {PORTD->PCR[17] &= ~PORT_IRQC_MASK; PORTD->PCR[17] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN20_INTclear()        {PORTD->PCR[17] |= 0x01000000;}

/*___PIN 021: PTD16/FTM0_CH1/LPSPI0_SIN/CMP0_RRT______________________________*/
#define IO_PIN21_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[16] &= ~PORT_MUX_MASK; PORTD->PCR[16] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_16;}
#define IO_PIN21_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[16] &= ~PORT_MUX_MASK; PORTD->PCR[16] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_16;}
#define IO_PIN21_toHI()            {PTD->PSOR |= PORT_PIN_16;}
#define IO_PIN21_toLO()            {PTD->PCOR |= PORT_PIN_16;}
#define IO_PIN21_TOGGLE()          {PTD->PTOR |= PORT_PIN_16;}
#define IO_PIN21_getINPUT()        {(PTD->PDIR & PORT_PIN_16) >> 16U;}
#define IO_PIN21_isHI()            {(PTD->PDIR & PORT_PIN_16) == PORT_PIN_16;}
#define IO_PIN21_isLO()            {(PTD->PDIR & PORT_PIN_16) != PORT_PIN_16;}
#define IO_PIN21_PULLoff()         {PORTD->PCR[16] &= ~PORT_PULL_MASK;}
#define IO_PIN21_PULLup()          {PORTD->PCR[16] &= ~PORT_PULL_MASK; PORTD->PCR[16] |= PORT_PULL_UP;}
#define IO_PIN21_PULLdown()        {PORTD->PCR[16] &= ~PORT_PULL_MASK; PORTD->PCR[16] |= PORT_PULL_DOWN;}
#define IO_PIN21_INToff()          {PORTD->PCR[16] &= ~PORT_IRQC_MASK;}
#define IO_PIN21_INTfalling()      {PORTD->PCR[16] &= ~PORT_IRQC_MASK; PORTD->PCR[16] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN21_INTrising()       {PORTD->PCR[16] &= ~PORT_IRQC_MASK; PORTD->PCR[16] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN21_INTany()          {PORTD->PCR[16] &= ~PORT_IRQC_MASK; PORTD->PCR[16] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN21_INTclear()        {PORTD->PCR[16] |= 0x01000000;}

/*___PIN 022: PTD15/FTM0_CH0/LPSPI0_SCK_______________________________________*/
#define IO_PIN22_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[15] &= ~PORT_MUX_MASK; PORTD->PCR[15] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_15;}
#define IO_PIN22_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[15] &= ~PORT_MUX_MASK; PORTD->PCR[15] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_15;}
#define IO_PIN22_toHI()            {PTD->PSOR |= PORT_PIN_15;}
#define IO_PIN22_toLO()            {PTD->PCOR |= PORT_PIN_15;}
#define IO_PIN22_TOGGLE()          {PTD->PTOR |= PORT_PIN_15;}
#define IO_PIN22_getINPUT()        {(PTD->PDIR & PORT_PIN_15) >> 15U;}
#define IO_PIN22_isHI()            {(PTD->PDIR & PORT_PIN_15) == PORT_PIN_15;}
#define IO_PIN22_isLO()            {(PTD->PDIR & PORT_PIN_15) != PORT_PIN_15;}
#define IO_PIN22_PULLoff()         {PORTD->PCR[15] &= ~PORT_PULL_MASK;}
#define IO_PIN22_PULLup()          {PORTD->PCR[15] &= ~PORT_PULL_MASK; PORTD->PCR[15] |= PORT_PULL_UP;}
#define IO_PIN22_PULLdown()        {PORTD->PCR[15] &= ~PORT_PULL_MASK; PORTD->PCR[15] |= PORT_PULL_DOWN;}
#define IO_PIN22_INToff()          {PORTD->PCR[15] &= ~PORT_IRQC_MASK;}
#define IO_PIN22_INTfalling()      {PORTD->PCR[15] &= ~PORT_IRQC_MASK; PORTD->PCR[15] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN22_INTrising()       {PORTD->PCR[15] &= ~PORT_IRQC_MASK; PORTD->PCR[15] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN22_INTany()          {PORTD->PCR[15] &= ~PORT_IRQC_MASK; PORTD->PCR[15] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN22_INTclear()        {PORTD->PCR[15] |= 0x01000000;}

/*___PIN 023: PTE9/FTM0_CH7/LPUART2_CTS_______________________________________*/
#define IO_PIN23_toOUT()           {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[9] &= ~PORT_MUX_MASK; PORTE->PCR[9] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_9;}
#define IO_PIN23_toIN()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[9] &= ~PORT_MUX_MASK; PORTE->PCR[9] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_9;}
#define IO_PIN23_toHI()            {PTE->PSOR |= PORT_PIN_9;}
#define IO_PIN23_toLO()            {PTE->PCOR |= PORT_PIN_9;}
#define IO_PIN23_TOGGLE()          {PTE->PTOR |= PORT_PIN_9;}
#define IO_PIN23_getINPUT()        {(PTE->PDIR & PORT_PIN_9) >> 9U;}
#define IO_PIN23_isHI()            {(PTE->PDIR & PORT_PIN_9) == PORT_PIN_9;}
#define IO_PIN23_isLO()            {(PTE->PDIR & PORT_PIN_9) != PORT_PIN_9;}
#define IO_PIN23_PULLoff()         {PORTE->PCR[9] &= ~PORT_PULL_MASK;}
#define IO_PIN23_PULLup()          {PORTE->PCR[9] &= ~PORT_PULL_MASK; PORTE->PCR[9] |= PORT_PULL_UP;}
#define IO_PIN23_PULLdown()        {PORTE->PCR[9] &= ~PORT_PULL_MASK; PORTE->PCR[9] |= PORT_PULL_DOWN;}
#define IO_PIN23_INToff()          {PORTE->PCR[9] &= ~PORT_IRQC_MASK;}
#define IO_PIN23_INTfalling()      {PORTE->PCR[9] &= ~PORT_IRQC_MASK; PORTE->PCR[9] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN23_INTrising()       {PORTE->PCR[9] &= ~PORT_IRQC_MASK; PORTE->PCR[9] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN23_INTany()          {PORTE->PCR[9] &= ~PORT_IRQC_MASK; PORTE->PCR[9] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN23_INTclear()        {PORTE->PCR[9] |= 0x01000000;}

/*___PIN 024: PTD14/FTM2_CH5/LPUART1_TX/CLKOUT________________________________*/
#define IO_PIN24_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[14] &= ~PORT_MUX_MASK; PORTD->PCR[14] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_14;}
#define IO_PIN24_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[14] &= ~PORT_MUX_MASK; PORTD->PCR[14] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_14;}
#define IO_PIN24_toHI()            {PTD->PSOR |= PORT_PIN_14;}
#define IO_PIN24_toLO()            {PTD->PCOR |= PORT_PIN_14;}
#define IO_PIN24_TOGGLE()          {PTD->PTOR |= PORT_PIN_14;}
#define IO_PIN24_getINPUT()        {(PTD->PDIR & PORT_PIN_14) >> 14U;}
#define IO_PIN24_isHI()            {(PTD->PDIR & PORT_PIN_14) == PORT_PIN_14;}
#define IO_PIN24_isLO()            {(PTD->PDIR & PORT_PIN_14) != PORT_PIN_14;}
#define IO_PIN24_PULLoff()         {PORTD->PCR[14] &= ~PORT_PULL_MASK;}
#define IO_PIN24_PULLup()          {PORTD->PCR[14] &= ~PORT_PULL_MASK; PORTD->PCR[14] |= PORT_PULL_UP;}
#define IO_PIN24_PULLdown()        {PORTD->PCR[14] &= ~PORT_PULL_MASK; PORTD->PCR[14] |= PORT_PULL_DOWN;}
#define IO_PIN24_INToff()          {PORTD->PCR[14] &= ~PORT_IRQC_MASK;}
#define IO_PIN24_INTfalling()      {PORTD->PCR[14] &= ~PORT_IRQC_MASK; PORTD->PCR[14] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN24_INTrising()       {PORTD->PCR[14] &= ~PORT_IRQC_MASK; PORTD->PCR[14] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN24_INTany()          {PORTD->PCR[14] &= ~PORT_IRQC_MASK; PORTD->PCR[14] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN24_INTclear()        {PORTD->PCR[14] |= 0x01000000;}

/*___PIN 025: PTD13/FTM2_CH4/LPUART1_RX/RTC_CLKOUT____________________________*/
#define IO_PIN25_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[13] &= ~PORT_MUX_MASK; PORTD->PCR[13] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_13;}
#define IO_PIN25_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[13] &= ~PORT_MUX_MASK; PORTD->PCR[13] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_13;}
#define IO_PIN25_toHI()            {PTD->PSOR |= PORT_PIN_13;}
#define IO_PIN25_toLO()            {PTD->PCOR |= PORT_PIN_13;}
#define IO_PIN25_TOGGLE()          {PTD->PTOR |= PORT_PIN_13;}
#define IO_PIN25_getINPUT()        {(PTD->PDIR & PORT_PIN_13) >> 13U;}
#define IO_PIN25_isHI()            {(PTD->PDIR & PORT_PIN_13) == PORT_PIN_13;}
#define IO_PIN25_isLO()            {(PTD->PDIR & PORT_PIN_13) != PORT_PIN_13;}
#define IO_PIN25_PULLoff()         {PORTD->PCR[13] &= ~PORT_PULL_MASK;}
#define IO_PIN25_PULLup()          {PORTD->PCR[13] &= ~PORT_PULL_MASK; PORTD->PCR[13] |= PORT_PULL_UP;}
#define IO_PIN25_PULLdown()        {PORTD->PCR[13] &= ~PORT_PULL_MASK; PORTD->PCR[13] |= PORT_PULL_DOWN;}
#define IO_PIN25_INToff()          {PORTD->PCR[13] &= ~PORT_IRQC_MASK;}
#define IO_PIN25_INTfalling()      {PORTD->PCR[13] &= ~PORT_IRQC_MASK; PORTD->PCR[13] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN25_INTrising()       {PORTD->PCR[13] &= ~PORT_IRQC_MASK; PORTD->PCR[13] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN25_INTany()          {PORTD->PCR[13] &= ~PORT_IRQC_MASK; PORTD->PCR[13] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN25_INTclear()        {PORTD->PCR[13] |= 0x01000000;}

/*___PIN 026: PTE8/FTM0_CH6/CMP0_IN3__________________________________________*/
#define IO_PIN26_toOUT()           {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[8] &= ~PORT_MUX_MASK; PORTE->PCR[8] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_8;}
#define IO_PIN26_toIN()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[8] &= ~PORT_MUX_MASK; PORTE->PCR[8] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_8;}
#define IO_PIN26_toHI()            {PTE->PSOR |= PORT_PIN_8;}
#define IO_PIN26_toLO()            {PTE->PCOR |= PORT_PIN_8;}
#define IO_PIN26_TOGGLE()          {PTE->PTOR |= PORT_PIN_8;}
#define IO_PIN26_getINPUT()        {(PTE->PDIR & PORT_PIN_8) >> 8U;}
#define IO_PIN26_isHI()            {(PTE->PDIR & PORT_PIN_8) == PORT_PIN_8;}
#define IO_PIN26_isLO()            {(PTE->PDIR & PORT_PIN_8) != PORT_PIN_8;}
#define IO_PIN26_PULLoff()         {PORTE->PCR[8] &= ~PORT_PULL_MASK;}
#define IO_PIN26_PULLup()          {PORTE->PCR[8] &= ~PORT_PULL_MASK; PORTE->PCR[8] |= PORT_PULL_UP;}
#define IO_PIN26_PULLdown()        {PORTE->PCR[8] &= ~PORT_PULL_MASK; PORTE->PCR[8] |= PORT_PULL_DOWN;}
#define IO_PIN26_INToff()          {PORTE->PCR[8] &= ~PORT_IRQC_MASK;}
#define IO_PIN26_INTfalling()      {PORTE->PCR[8] &= ~PORT_IRQC_MASK; PORTE->PCR[8] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN26_INTrising()       {PORTE->PCR[8] &= ~PORT_IRQC_MASK; PORTE->PCR[8] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN26_INTany()          {PORTE->PCR[8] &= ~PORT_IRQC_MASK; PORTE->PCR[8] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN26_INTclear()        {PORTE->PCR[8] |= 0x01000000;}

/*___PIN 027: PTB5/FTM0_CH5/LPSPI0_PCS1/LPSPI0_PCS0/CLKOUT/TRGMUX_IN0_________*/
#define IO_PIN27_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[5] &= ~PORT_MUX_MASK; PORTB->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_5;}
#define IO_PIN27_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[5] &= ~PORT_MUX_MASK; PORTB->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_5;}
#define IO_PIN27_toHI()            {PTB->PSOR |= PORT_PIN_5;}
#define IO_PIN27_toLO()            {PTB->PCOR |= PORT_PIN_5;}
#define IO_PIN27_TOGGLE()          {PTB->PTOR |= PORT_PIN_5;}
#define IO_PIN27_getINPUT()        {(PTB->PDIR & PORT_PIN_5) >> 5U;}
#define IO_PIN27_isHI()            {(PTB->PDIR & PORT_PIN_5) == PORT_PIN_5;}
#define IO_PIN27_isLO()            {(PTB->PDIR & PORT_PIN_5) != PORT_PIN_5;}
#define IO_PIN27_PULLoff()         {PORTB->PCR[5] &= ~PORT_PULL_MASK;}
#define IO_PIN27_PULLup()          {PORTB->PCR[5] &= ~PORT_PULL_MASK; PORTB->PCR[5] |= PORT_PULL_UP;}
#define IO_PIN27_PULLdown()        {PORTB->PCR[5] &= ~PORT_PULL_MASK; PORTB->PCR[5] |= PORT_PULL_DOWN;}
#define IO_PIN27_INToff()          {PORTB->PCR[5] &= ~PORT_IRQC_MASK;}
#define IO_PIN27_INTfalling()      {PORTB->PCR[5] &= ~PORT_IRQC_MASK; PORTB->PCR[5] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN27_INTrising()       {PORTB->PCR[5] &= ~PORT_IRQC_MASK; PORTB->PCR[5] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN27_INTany()          {PORTB->PCR[5] &= ~PORT_IRQC_MASK; PORTB->PCR[5] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN27_INTclear()        {PORTB->PCR[5] |= 0x01000000;}

/*___PIN 028: PTB4/FTM0_CH4/LPSPI0_SOUT/TRGMUX_IN1____________________________*/
#define IO_PIN28_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[4] &= ~PORT_MUX_MASK; PORTB->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_4;}
#define IO_PIN28_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[4] &= ~PORT_MUX_MASK; PORTB->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_4;}
#define IO_PIN28_toHI()            {PTB->PSOR |= PORT_PIN_4;}
#define IO_PIN28_toLO()            {PTB->PCOR |= PORT_PIN_4;}
#define IO_PIN28_TOGGLE()          {PTB->PTOR |= PORT_PIN_4;}
#define IO_PIN28_getINPUT()        {(PTB->PDIR & PORT_PIN_4) >> 4U;}
#define IO_PIN28_isHI()            {(PTB->PDIR & PORT_PIN_4) == PORT_PIN_4;}
#define IO_PIN28_isLO()            {(PTB->PDIR & PORT_PIN_4) != PORT_PIN_4;}
#define IO_PIN28_PULLoff()         {PORTB->PCR[4] &= ~PORT_PULL_MASK;}
#define IO_PIN28_PULLup()          {PORTB->PCR[4] &= ~PORT_PULL_MASK; PORTB->PCR[4] |= PORT_PULL_UP;}
#define IO_PIN28_PULLdown()        {PORTB->PCR[4] &= ~PORT_PULL_MASK; PORTB->PCR[4] |= PORT_PULL_DOWN;}
#define IO_PIN28_INToff()          {PORTB->PCR[4] &= ~PORT_IRQC_MASK;}
#define IO_PIN28_INTfalling()      {PORTB->PCR[4] &= ~PORT_IRQC_MASK; PORTB->PCR[4] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN28_INTrising()       {PORTB->PCR[4] &= ~PORT_IRQC_MASK; PORTB->PCR[4] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN28_INTany()          {PORTB->PCR[4] &= ~PORT_IRQC_MASK; PORTB->PCR[4] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN28_INTclear()        {PORTB->PCR[4] |= 0x01000000;}

/*___PIN 029: PTC3/FTM0_CH3/CAN0_TX/LPUART0_TX/ADC0_SE11/CMP0_IN4_____________*/
#define IO_PIN29_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[3] &= ~PORT_MUX_MASK; PORTC->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_3;}
#define IO_PIN29_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[3] &= ~PORT_MUX_MASK; PORTC->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_3;}
#define IO_PIN29_toHI()            {PTC->PSOR |= PORT_PIN_3;}
#define IO_PIN29_toLO()            {PTC->PCOR |= PORT_PIN_3;}
#define IO_PIN29_TOGGLE()          {PTC->PTOR |= PORT_PIN_3;}
#define IO_PIN29_getINPUT()        {(PTC->PDIR & PORT_PIN_3) >> 3U;}
#define IO_PIN29_isHI()            {(PTC->PDIR & PORT_PIN_3) == PORT_PIN_3;}
#define IO_PIN29_isLO()            {(PTC->PDIR & PORT_PIN_3) != PORT_PIN_3;}
#define IO_PIN29_PULLoff()         {PORTC->PCR[3] &= ~PORT_PULL_MASK;}
#define IO_PIN29_PULLup()          {PORTC->PCR[3] &= ~PORT_PULL_MASK; PORTC->PCR[3] |= PORT_PULL_UP;}
#define IO_PIN29_PULLdown()        {PORTC->PCR[3] &= ~PORT_PULL_MASK; PORTC->PCR[3] |= PORT_PULL_DOWN;}
#define IO_PIN29_INToff()          {PORTC->PCR[3] &= ~PORT_IRQC_MASK;}
#define IO_PIN29_INTfalling()      {PORTC->PCR[3] &= ~PORT_IRQC_MASK; PORTC->PCR[3] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN29_INTrising()       {PORTC->PCR[3] &= ~PORT_IRQC_MASK; PORTC->PCR[3] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN29_INTany()          {PORTC->PCR[3] &= ~PORT_IRQC_MASK; PORTC->PCR[3] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN29_INTclear()        {PORTC->PCR[3] |= 0x01000000;}

/*___PIN 030: PTC2/FTM0_CH2/CAN0_RX/LPUART0_RX/ADC0_SE10/CMP0_IN5_____________*/
#define IO_PIN30_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[2] &= ~PORT_MUX_MASK; PORTC->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_2;}
#define IO_PIN30_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[2] &= ~PORT_MUX_MASK; PORTC->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_2;}
#define IO_PIN30_toHI()            {PTC->PSOR |= PORT_PIN_2;}
#define IO_PIN30_toLO()            {PTC->PCOR |= PORT_PIN_2;}
#define IO_PIN30_TOGGLE()          {PTC->PTOR |= PORT_PIN_2;}
#define IO_PIN30_getINPUT()        {(PTC->PDIR & PORT_PIN_2) >> 2U;}
#define IO_PIN30_isHI()            {(PTC->PDIR & PORT_PIN_2) == PORT_PIN_2;}
#define IO_PIN30_isLO()            {(PTC->PDIR & PORT_PIN_2) != PORT_PIN_2;}
#define IO_PIN30_PULLoff()         {PORTC->PCR[2] &= ~PORT_PULL_MASK;}
#define IO_PIN30_PULLup()          {PORTC->PCR[2] &= ~PORT_PULL_MASK; PORTC->PCR[2] |= PORT_PULL_UP;}
#define IO_PIN30_PULLdown()        {PORTC->PCR[2] &= ~PORT_PULL_MASK; PORTC->PCR[2] |= PORT_PULL_DOWN;}
#define IO_PIN30_INToff()          {PORTC->PCR[2] &= ~PORT_IRQC_MASK;}
#define IO_PIN30_INTfalling()      {PORTC->PCR[2] &= ~PORT_IRQC_MASK; PORTC->PCR[2] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN30_INTrising()       {PORTC->PCR[2] &= ~PORT_IRQC_MASK; PORTC->PCR[2] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN30_INTany()          {PORTC->PCR[2] &= ~PORT_IRQC_MASK; PORTC->PCR[2] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN30_INTclear()        {PORTC->PCR[2] |= 0x01000000;}

/*___PIN 031: PTD7/LPUART2_TX/FTM2_FLT3/CMP0_IN6______________________________*/
#define IO_PIN31_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[7] &= ~PORT_MUX_MASK; PORTD->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_7;}
#define IO_PIN31_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[7] &= ~PORT_MUX_MASK; PORTD->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_7;}
#define IO_PIN31_toHI()            {PTD->PSOR |= PORT_PIN_7;}
#define IO_PIN31_toLO()            {PTD->PCOR |= PORT_PIN_7;}
#define IO_PIN31_TOGGLE()          {PTD->PTOR |= PORT_PIN_7;}
#define IO_PIN31_getINPUT()        {(PTD->PDIR & PORT_PIN_7) >> 7U;}
#define IO_PIN31_isHI()            {(PTD->PDIR & PORT_PIN_7) == PORT_PIN_7;}
#define IO_PIN31_isLO()            {(PTD->PDIR & PORT_PIN_7) != PORT_PIN_7;}
#define IO_PIN31_PULLoff()         {PORTD->PCR[7] &= ~PORT_PULL_MASK;}
#define IO_PIN31_PULLup()          {PORTD->PCR[7] &= ~PORT_PULL_MASK; PORTD->PCR[7] |= PORT_PULL_UP;}
#define IO_PIN31_PULLdown()        {PORTD->PCR[7] &= ~PORT_PULL_MASK; PORTD->PCR[7] |= PORT_PULL_DOWN;}
#define IO_PIN31_INToff()          {PORTD->PCR[7] &= ~PORT_IRQC_MASK;}
#define IO_PIN31_INTfalling()      {PORTD->PCR[7] &= ~PORT_IRQC_MASK; PORTD->PCR[7] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN31_INTrising()       {PORTD->PCR[7] &= ~PORT_IRQC_MASK; PORTD->PCR[7] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN31_INTany()          {PORTD->PCR[7] &= ~PORT_IRQC_MASK; PORTD->PCR[7] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN31_INTclear()        {PORTD->PCR[7] |= 0x01000000;}

/*___PIN 032: PTD6/LPUART2_RX/FTM2_FLT2/CMP0_IN7______________________________*/
#define IO_PIN32_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[6] &= ~PORT_MUX_MASK; PORTD->PCR[6] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_6;}
#define IO_PIN32_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[6] &= ~PORT_MUX_MASK; PORTD->PCR[6] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_6;}
#define IO_PIN32_toHI()            {PTD->PSOR |= PORT_PIN_6;}
#define IO_PIN32_toLO()            {PTD->PCOR |= PORT_PIN_6;}
#define IO_PIN32_TOGGLE()          {PTD->PTOR |= PORT_PIN_6;}
#define IO_PIN32_getINPUT()        {(PTD->PDIR & PORT_PIN_6) >> 6U;}
#define IO_PIN32_isHI()            {(PTD->PDIR & PORT_PIN_6) == PORT_PIN_6;}
#define IO_PIN32_isLO()            {(PTD->PDIR & PORT_PIN_6) != PORT_PIN_6;}
#define IO_PIN32_PULLoff()         {PORTD->PCR[6] &= ~PORT_PULL_MASK;}
#define IO_PIN32_PULLup()          {PORTD->PCR[6] &= ~PORT_PULL_MASK; PORTD->PCR[6] |= PORT_PULL_UP;}
#define IO_PIN32_PULLdown()        {PORTD->PCR[6] &= ~PORT_PULL_MASK; PORTD->PCR[6] |= PORT_PULL_DOWN;}
#define IO_PIN32_INToff()          {PORTD->PCR[6] &= ~PORT_IRQC_MASK;}
#define IO_PIN32_INTfalling()      {PORTD->PCR[6] &= ~PORT_IRQC_MASK; PORTD->PCR[6] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN32_INTrising()       {PORTD->PCR[6] &= ~PORT_IRQC_MASK; PORTD->PCR[6] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN32_INTany()          {PORTD->PCR[6] &= ~PORT_IRQC_MASK; PORTD->PCR[6] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN32_INTclear()        {PORTD->PCR[6] |= 0x01000000;}

/*___PIN 033: PTD5/FTM2_CH3/LPTMR0_ALT2/FTM2_FLT1/TRGMUX_IN7__________________*/
#define IO_PIN33_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[5] &= ~PORT_MUX_MASK; PORTD->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_5;}
#define IO_PIN33_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[5] &= ~PORT_MUX_MASK; PORTD->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_5;}
#define IO_PIN33_toHI()            {PTD->PSOR |= PORT_PIN_5;}
#define IO_PIN33_toLO()            {PTD->PCOR |= PORT_PIN_5;}
#define IO_PIN33_TOGGLE()          {PTD->PTOR |= PORT_PIN_5;}
#define IO_PIN33_getINPUT()        {(PTD->PDIR & PORT_PIN_5) >> 5U;}
#define IO_PIN33_isHI()            {(PTD->PDIR & PORT_PIN_5) == PORT_PIN_5;}
#define IO_PIN33_isLO()            {(PTD->PDIR & PORT_PIN_5) != PORT_PIN_5;}
#define IO_PIN33_PULLoff()         {PORTD->PCR[5] &= ~PORT_PULL_MASK;}
#define IO_PIN33_PULLup()          {PORTD->PCR[5] &= ~PORT_PULL_MASK; PORTD->PCR[5] |= PORT_PULL_UP;}
#define IO_PIN33_PULLdown()        {PORTD->PCR[5] &= ~PORT_PULL_MASK; PORTD->PCR[5] |= PORT_PULL_DOWN;}
#define IO_PIN33_INToff()          {PORTD->PCR[5] &= ~PORT_IRQC_MASK;}
#define IO_PIN33_INTfalling()      {PORTD->PCR[5] &= ~PORT_IRQC_MASK; PORTD->PCR[5] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN33_INTrising()       {PORTD->PCR[5] &= ~PORT_IRQC_MASK; PORTD->PCR[5] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN33_INTany()          {PORTD->PCR[5] &= ~PORT_IRQC_MASK; PORTD->PCR[5] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN33_INTclear()        {PORTD->PCR[5] |= 0x01000000;}

/*___PIN 034: PTD12/FTM2_CH2/LPUART2_RTS______________________________________*/
#define IO_PIN34_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[12] &= ~PORT_MUX_MASK; PORTD->PCR[12] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_12;}
#define IO_PIN34_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[12] &= ~PORT_MUX_MASK; PORTD->PCR[12] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_12;}
#define IO_PIN34_toHI()            {PTD->PSOR |= PORT_PIN_12;}
#define IO_PIN34_toLO()            {PTD->PCOR |= PORT_PIN_12;}
#define IO_PIN34_TOGGLE()          {PTD->PTOR |= PORT_PIN_12;}
#define IO_PIN34_getINPUT()        {(PTD->PDIR & PORT_PIN_12) >> 12U;}
#define IO_PIN34_isHI()            {(PTD->PDIR & PORT_PIN_12) == PORT_PIN_12;}
#define IO_PIN34_isLO()            {(PTD->PDIR & PORT_PIN_12) != PORT_PIN_12;}
#define IO_PIN34_PULLoff()         {PORTD->PCR[12] &= ~PORT_PULL_MASK;}
#define IO_PIN34_PULLup()          {PORTD->PCR[12] &= ~PORT_PULL_MASK; PORTD->PCR[12] |= PORT_PULL_UP;}
#define IO_PIN34_PULLdown()        {PORTD->PCR[12] &= ~PORT_PULL_MASK; PORTD->PCR[12] |= PORT_PULL_DOWN;}
#define IO_PIN34_INToff()          {PORTD->PCR[12] &= ~PORT_IRQC_MASK;}
#define IO_PIN34_INTfalling()      {PORTD->PCR[12] &= ~PORT_IRQC_MASK; PORTD->PCR[12] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN34_INTrising()       {PORTD->PCR[12] &= ~PORT_IRQC_MASK; PORTD->PCR[12] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN34_INTany()          {PORTD->PCR[12] &= ~PORT_IRQC_MASK; PORTD->PCR[12] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN34_INTclear()        {PORTD->PCR[12] |= 0x01000000;}

/*___PIN 035: PTD11/FTM2_CH1/FTM2_QD_PHA/LPUART2_CTS__________________________*/
#define IO_PIN35_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[11] &= ~PORT_MUX_MASK; PORTD->PCR[11] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_11;}
#define IO_PIN35_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[11] &= ~PORT_MUX_MASK; PORTD->PCR[11] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_11;}
#define IO_PIN35_toHI()            {PTD->PSOR |= PORT_PIN_11;}
#define IO_PIN35_toLO()            {PTD->PCOR |= PORT_PIN_11;}
#define IO_PIN35_TOGGLE()          {PTD->PTOR |= PORT_PIN_11;}
#define IO_PIN35_getINPUT()        {(PTD->PDIR & PORT_PIN_11) >> 11U;}
#define IO_PIN35_isHI()            {(PTD->PDIR & PORT_PIN_11) == PORT_PIN_11;}
#define IO_PIN35_isLO()            {(PTD->PDIR & PORT_PIN_11) != PORT_PIN_11;}
#define IO_PIN35_PULLoff()         {PORTD->PCR[11] &= ~PORT_PULL_MASK;}
#define IO_PIN35_PULLup()          {PORTD->PCR[11] &= ~PORT_PULL_MASK; PORTD->PCR[11] |= PORT_PULL_UP;}
#define IO_PIN35_PULLdown()        {PORTD->PCR[11] &= ~PORT_PULL_MASK; PORTD->PCR[11] |= PORT_PULL_DOWN;}
#define IO_PIN35_INToff()          {PORTD->PCR[11] &= ~PORT_IRQC_MASK;}
#define IO_PIN35_INTfalling()      {PORTD->PCR[11] &= ~PORT_IRQC_MASK; PORTD->PCR[11] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN35_INTrising()       {PORTD->PCR[11] &= ~PORT_IRQC_MASK; PORTD->PCR[11] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN35_INTany()          {PORTD->PCR[11] &= ~PORT_IRQC_MASK; PORTD->PCR[11] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN35_INTclear()        {PORTD->PCR[11] |= 0x01000000;}

/*___PIN 036: PTD10/FTM2_CH0/FTM2_QD_PHB______________________________________*/
#define IO_PIN36_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[10] &= ~PORT_MUX_MASK; PORTD->PCR[10] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_10;}
#define IO_PIN36_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[10] &= ~PORT_MUX_MASK; PORTD->PCR[10] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_10;}
#define IO_PIN36_toHI()            {PTD->PSOR |= PORT_PIN_10;}
#define IO_PIN36_toLO()            {PTD->PCOR |= PORT_PIN_10;}
#define IO_PIN36_TOGGLE()          {PTD->PTOR |= PORT_PIN_10;}
#define IO_PIN36_getINPUT()        {(PTD->PDIR & PORT_PIN_10) >> 10U;}
#define IO_PIN36_isHI()            {(PTD->PDIR & PORT_PIN_10) == PORT_PIN_10;}
#define IO_PIN36_isLO()            {(PTD->PDIR & PORT_PIN_10) != PORT_PIN_10;}
#define IO_PIN36_PULLoff()         {PORTD->PCR[10] &= ~PORT_PULL_MASK;}
#define IO_PIN36_PULLup()          {PORTD->PCR[10] &= ~PORT_PULL_MASK; PORTD->PCR[10] |= PORT_PULL_UP;}
#define IO_PIN36_PULLdown()        {PORTD->PCR[10] &= ~PORT_PULL_MASK; PORTD->PCR[10] |= PORT_PULL_DOWN;}
#define IO_PIN36_INToff()          {PORTD->PCR[10] &= ~PORT_IRQC_MASK;}
#define IO_PIN36_INTfalling()      {PORTD->PCR[10] &= ~PORT_IRQC_MASK; PORTD->PCR[10] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN36_INTrising()       {PORTD->PCR[10] &= ~PORT_IRQC_MASK; PORTD->PCR[10] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN36_INTany()          {PORTD->PCR[10] &= ~PORT_IRQC_MASK; PORTD->PCR[10] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN36_INTclear()        {PORTD->PCR[10] |= 0x01000000;}

/*___PIN 037: VSS_____________________________________________________________*/

/*___PIN 038: VDD_____________________________________________________________*/

/*___PIN 039: PTC1/FTM0_CH1/LPSPI2_SOUT/FTM1_CH7/ADC0_SE9_____________________*/
#define IO_PIN39_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[1] &= ~PORT_MUX_MASK; PORTC->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_1;}
#define IO_PIN39_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[1] &= ~PORT_MUX_MASK; PORTC->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_1;}
#define IO_PIN39_toHI()            {PTC->PSOR |= PORT_PIN_1;}
#define IO_PIN39_toLO()            {PTC->PCOR |= PORT_PIN_1;}
#define IO_PIN39_TOGGLE()          {PTC->PTOR |= PORT_PIN_1;}
#define IO_PIN39_getINPUT()        {(PTC->PDIR & PORT_PIN_1) >> 1U;}
#define IO_PIN39_isHI()            {(PTC->PDIR & PORT_PIN_1) == PORT_PIN_1;}
#define IO_PIN39_isLO()            {(PTC->PDIR & PORT_PIN_1) != PORT_PIN_1;}
#define IO_PIN39_PULLoff()         {PORTC->PCR[1] &= ~PORT_PULL_MASK;}
#define IO_PIN39_PULLup()          {PORTC->PCR[1] &= ~PORT_PULL_MASK; PORTC->PCR[1] |= PORT_PULL_UP;}
#define IO_PIN39_PULLdown()        {PORTC->PCR[1] &= ~PORT_PULL_MASK; PORTC->PCR[1] |= PORT_PULL_DOWN;}
#define IO_PIN39_INToff()          {PORTC->PCR[1] &= ~PORT_IRQC_MASK;}
#define IO_PIN39_INTfalling()      {PORTC->PCR[1] &= ~PORT_IRQC_MASK; PORTC->PCR[1] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN39_INTrising()       {PORTC->PCR[1] &= ~PORT_IRQC_MASK; PORTC->PCR[1] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN39_INTany()          {PORTC->PCR[1] &= ~PORT_IRQC_MASK; PORTC->PCR[1] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN39_INTclear()        {PORTC->PCR[1] |= 0x01000000;}

/*___PIN 040: PTC0/FTM0_CH0/LPSPI2_SIN/FTM1_CH6/ADC0_SE8______________________*/
#define IO_PIN40_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[0] &= ~PORT_MUX_MASK; PORTC->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_0;}
#define IO_PIN40_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[0] &= ~PORT_MUX_MASK; PORTC->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_0;}
#define IO_PIN40_toHI()            {PTC->PSOR |= PORT_PIN_0;}
#define IO_PIN40_toLO()            {PTC->PCOR |= PORT_PIN_0;}
#define IO_PIN40_TOGGLE()          {PTC->PTOR |= PORT_PIN_0;}
#define IO_PIN40_getINPUT()        {(PTC->PDIR & PORT_PIN_0) >> 0U;}
#define IO_PIN40_isHI()            {(PTC->PDIR & PORT_PIN_0) == PORT_PIN_0;}
#define IO_PIN40_isLO()            {(PTC->PDIR & PORT_PIN_0) != PORT_PIN_0;}
#define IO_PIN40_PULLoff()         {PORTC->PCR[0] &= ~PORT_PULL_MASK;}
#define IO_PIN40_PULLup()          {PORTC->PCR[0] &= ~PORT_PULL_MASK; PORTC->PCR[0] |= PORT_PULL_UP;}
#define IO_PIN40_PULLdown()        {PORTC->PCR[0] &= ~PORT_PULL_MASK; PORTC->PCR[0] |= PORT_PULL_DOWN;}
#define IO_PIN40_INToff()          {PORTC->PCR[0] &= ~PORT_IRQC_MASK;}
#define IO_PIN40_INTfalling()      {PORTC->PCR[0] &= ~PORT_IRQC_MASK; PORTC->PCR[0] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN40_INTrising()       {PORTC->PCR[0] &= ~PORT_IRQC_MASK; PORTC->PCR[0] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN40_INTany()          {PORTC->PCR[0] &= ~PORT_IRQC_MASK; PORTC->PCR[0] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN40_INTclear()        {PORTC->PCR[0] |= 0x01000000;}

/*___PIN 041: PTD9/FXIO_D0/FTM2_FLT3/FTM1_CH5_________________________________*/
#define IO_PIN41_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[9] &= ~PORT_MUX_MASK; PORTD->PCR[9] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_9;}
#define IO_PIN41_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[9] &= ~PORT_MUX_MASK; PORTD->PCR[9] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_9;}
#define IO_PIN41_toHI()            {PTD->PSOR |= PORT_PIN_9;}
#define IO_PIN41_toLO()            {PTD->PCOR |= PORT_PIN_9;}
#define IO_PIN41_TOGGLE()          {PTD->PTOR |= PORT_PIN_9;}
#define IO_PIN41_getINPUT()        {(PTD->PDIR & PORT_PIN_9) >> 9U;}
#define IO_PIN41_isHI()            {(PTD->PDIR & PORT_PIN_9) == PORT_PIN_9;}
#define IO_PIN41_isLO()            {(PTD->PDIR & PORT_PIN_9) != PORT_PIN_9;}
#define IO_PIN41_PULLoff()         {PORTD->PCR[9] &= ~PORT_PULL_MASK;}
#define IO_PIN41_PULLup()          {PORTD->PCR[9] &= ~PORT_PULL_MASK; PORTD->PCR[9] |= PORT_PULL_UP;}
#define IO_PIN41_PULLdown()        {PORTD->PCR[9] &= ~PORT_PULL_MASK; PORTD->PCR[9] |= PORT_PULL_DOWN;}
#define IO_PIN41_INToff()          {PORTD->PCR[9] &= ~PORT_IRQC_MASK;}
#define IO_PIN41_INTfalling()      {PORTD->PCR[9] &= ~PORT_IRQC_MASK; PORTD->PCR[9] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN41_INTrising()       {PORTD->PCR[9] &= ~PORT_IRQC_MASK; PORTD->PCR[9] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN41_INTany()          {PORTD->PCR[9] &= ~PORT_IRQC_MASK; PORTD->PCR[9] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN41_INTclear()        {PORTD->PCR[9] |= 0x01000000;}

/*___PIN 042: PTD8/FTM2_FLT2/FXIO_D1/FTM1_CH4_________________________________*/
#define IO_PIN42_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[8] &= ~PORT_MUX_MASK; PORTD->PCR[8] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_8;}
#define IO_PIN42_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[8] &= ~PORT_MUX_MASK; PORTD->PCR[8] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_8;}
#define IO_PIN42_toHI()            {PTD->PSOR |= PORT_PIN_8;}
#define IO_PIN42_toLO()            {PTD->PCOR |= PORT_PIN_8;}
#define IO_PIN42_TOGGLE()          {PTD->PTOR |= PORT_PIN_8;}
#define IO_PIN42_getINPUT()        {(PTD->PDIR & PORT_PIN_8) >> 8U;}
#define IO_PIN42_isHI()            {(PTD->PDIR & PORT_PIN_8) == PORT_PIN_8;}
#define IO_PIN42_isLO()            {(PTD->PDIR & PORT_PIN_8) != PORT_PIN_8;}
#define IO_PIN42_PULLoff()         {PORTD->PCR[8] &= ~PORT_PULL_MASK;}
#define IO_PIN42_PULLup()          {PORTD->PCR[8] &= ~PORT_PULL_MASK; PORTD->PCR[8] |= PORT_PULL_UP;}
#define IO_PIN42_PULLdown()        {PORTD->PCR[8] &= ~PORT_PULL_MASK; PORTD->PCR[8] |= PORT_PULL_DOWN;}
#define IO_PIN42_INToff()          {PORTD->PCR[8] &= ~PORT_IRQC_MASK;}
#define IO_PIN42_INTfalling()      {PORTD->PCR[8] &= ~PORT_IRQC_MASK; PORTD->PCR[8] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN42_INTrising()       {PORTD->PCR[8] &= ~PORT_IRQC_MASK; PORTD->PCR[8] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN42_INTany()          {PORTD->PCR[8] &= ~PORT_IRQC_MASK; PORTD->PCR[8] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN42_INTclear()        {PORTD->PCR[8] |= 0x01000000;}

/*___PIN 043: PTC17/FTM1_FLT3/CAN2_TX/ADC0_SE15_______________________________*/
#define IO_PIN43_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[17] &= ~PORT_MUX_MASK; PORTC->PCR[17] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_17;}
#define IO_PIN43_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[17] &= ~PORT_MUX_MASK; PORTC->PCR[17] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_17;}
#define IO_PIN43_toHI()            {PTC->PSOR |= PORT_PIN_17;}
#define IO_PIN43_toLO()            {PTC->PCOR |= PORT_PIN_17;}
#define IO_PIN43_TOGGLE()          {PTC->PTOR |= PORT_PIN_17;}
#define IO_PIN43_getINPUT()        {(PTC->PDIR & PORT_PIN_17) >> 17U;}
#define IO_PIN43_isHI()            {(PTC->PDIR & PORT_PIN_17) == PORT_PIN_17;}
#define IO_PIN43_isLO()            {(PTC->PDIR & PORT_PIN_17) != PORT_PIN_17;}
#define IO_PIN43_PULLoff()         {PORTC->PCR[17] &= ~PORT_PULL_MASK;}
#define IO_PIN43_PULLup()          {PORTC->PCR[17] &= ~PORT_PULL_MASK; PORTC->PCR[17] |= PORT_PULL_UP;}
#define IO_PIN43_PULLdown()        {PORTC->PCR[17] &= ~PORT_PULL_MASK; PORTC->PCR[17] |= PORT_PULL_DOWN;}
#define IO_PIN43_INToff()          {PORTC->PCR[17] &= ~PORT_IRQC_MASK;}
#define IO_PIN43_INTfalling()      {PORTC->PCR[17] &= ~PORT_IRQC_MASK; PORTC->PCR[17] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN43_INTrising()       {PORTC->PCR[17] &= ~PORT_IRQC_MASK; PORTC->PCR[17] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN43_INTany()          {PORTC->PCR[17] &= ~PORT_IRQC_MASK; PORTC->PCR[17] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN43_INTclear()        {PORTC->PCR[17] |= 0x01000000;}

/*___PIN 044: PTC16/FTM1_FLT2/CAN2_RX/ADC0_SE14_______________________________*/
#define IO_PIN44_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[16] &= ~PORT_MUX_MASK; PORTC->PCR[16] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_16;}
#define IO_PIN44_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[16] &= ~PORT_MUX_MASK; PORTC->PCR[16] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_16;}
#define IO_PIN44_toHI()            {PTC->PSOR |= PORT_PIN_16;}
#define IO_PIN44_toLO()            {PTC->PCOR |= PORT_PIN_16;}
#define IO_PIN44_TOGGLE()          {PTC->PTOR |= PORT_PIN_16;}
#define IO_PIN44_getINPUT()        {(PTC->PDIR & PORT_PIN_16) >> 16U;}
#define IO_PIN44_isHI()            {(PTC->PDIR & PORT_PIN_16) == PORT_PIN_16;}
#define IO_PIN44_isLO()            {(PTC->PDIR & PORT_PIN_16) != PORT_PIN_16;}
#define IO_PIN44_PULLoff()         {PORTC->PCR[16] &= ~PORT_PULL_MASK;}
#define IO_PIN44_PULLup()          {PORTC->PCR[16] &= ~PORT_PULL_MASK; PORTC->PCR[16] |= PORT_PULL_UP;}
#define IO_PIN44_PULLdown()        {PORTC->PCR[16] &= ~PORT_PULL_MASK; PORTC->PCR[16] |= PORT_PULL_DOWN;}
#define IO_PIN44_INToff()          {PORTC->PCR[16] &= ~PORT_IRQC_MASK;}
#define IO_PIN44_INTfalling()      {PORTC->PCR[16] &= ~PORT_IRQC_MASK; PORTC->PCR[16] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN44_INTrising()       {PORTC->PCR[16] &= ~PORT_IRQC_MASK; PORTC->PCR[16] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN44_INTany()          {PORTC->PCR[16] &= ~PORT_IRQC_MASK; PORTC->PCR[16] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN44_INTclear()        {PORTC->PCR[16] |= 0x01000000;}

/*___PIN 045: PTC15/FTM1_CH3/LPSPI2_SCK/TRGMUX_IN8/ADC0_SE13__________________*/
#define IO_PIN45_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[15] &= ~PORT_MUX_MASK; PORTC->PCR[15] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_15;}
#define IO_PIN45_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[15] &= ~PORT_MUX_MASK; PORTC->PCR[15] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_15;}
#define IO_PIN45_toHI()            {PTC->PSOR |= PORT_PIN_15;}
#define IO_PIN45_toLO()            {PTC->PCOR |= PORT_PIN_15;}
#define IO_PIN45_TOGGLE()          {PTC->PTOR |= PORT_PIN_15;}
#define IO_PIN45_getINPUT()        {(PTC->PDIR & PORT_PIN_15) >> 15U;}
#define IO_PIN45_isHI()            {(PTC->PDIR & PORT_PIN_15) == PORT_PIN_15;}
#define IO_PIN45_isLO()            {(PTC->PDIR & PORT_PIN_15) != PORT_PIN_15;}
#define IO_PIN45_PULLoff()         {PORTC->PCR[15] &= ~PORT_PULL_MASK;}
#define IO_PIN45_PULLup()          {PORTC->PCR[15] &= ~PORT_PULL_MASK; PORTC->PCR[15] |= PORT_PULL_UP;}
#define IO_PIN45_PULLdown()        {PORTC->PCR[15] &= ~PORT_PULL_MASK; PORTC->PCR[15] |= PORT_PULL_DOWN;}
#define IO_PIN45_INToff()          {PORTC->PCR[15] &= ~PORT_IRQC_MASK;}
#define IO_PIN45_INTfalling()      {PORTC->PCR[15] &= ~PORT_IRQC_MASK; PORTC->PCR[15] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN45_INTrising()       {PORTC->PCR[15] &= ~PORT_IRQC_MASK; PORTC->PCR[15] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN45_INTany()          {PORTC->PCR[15] &= ~PORT_IRQC_MASK; PORTC->PCR[15] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN45_INTclear()        {PORTC->PCR[15] |= 0x01000000;}

/*___PIN 046: PTC14/FTM1_CH2/LPSPI2_PCS0/TRGMUX_IN9/ADC0_SE12_________________*/
#define IO_PIN46_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[14] &= ~PORT_MUX_MASK; PORTC->PCR[14] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_14;}
#define IO_PIN46_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[14] &= ~PORT_MUX_MASK; PORTC->PCR[14] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_14;}
#define IO_PIN46_toHI()            {PTC->PSOR |= PORT_PIN_14;}
#define IO_PIN46_toLO()            {PTC->PCOR |= PORT_PIN_14;}
#define IO_PIN46_TOGGLE()          {PTC->PTOR |= PORT_PIN_14;}
#define IO_PIN46_getINPUT()        {(PTC->PDIR & PORT_PIN_14) >> 14U;}
#define IO_PIN46_isHI()            {(PTC->PDIR & PORT_PIN_14) == PORT_PIN_14;}
#define IO_PIN46_isLO()            {(PTC->PDIR & PORT_PIN_14) != PORT_PIN_14;}
#define IO_PIN46_PULLoff()         {PORTC->PCR[14] &= ~PORT_PULL_MASK;}
#define IO_PIN46_PULLup()          {PORTC->PCR[14] &= ~PORT_PULL_MASK; PORTC->PCR[14] |= PORT_PULL_UP;}
#define IO_PIN46_PULLdown()        {PORTC->PCR[14] &= ~PORT_PULL_MASK; PORTC->PCR[14] |= PORT_PULL_DOWN;}
#define IO_PIN46_INToff()          {PORTC->PCR[14] &= ~PORT_IRQC_MASK;}
#define IO_PIN46_INTfalling()      {PORTC->PCR[14] &= ~PORT_IRQC_MASK; PORTC->PCR[14] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN46_INTrising()       {PORTC->PCR[14] &= ~PORT_IRQC_MASK; PORTC->PCR[14] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN46_INTany()          {PORTC->PCR[14] &= ~PORT_IRQC_MASK; PORTC->PCR[14] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN46_INTclear()        {PORTC->PCR[14] |= 0x01000000;}

/*___PIN 047: PTB3/FTM1_CH1/LPSPI0_SIN/FTM1_QD_PHA/TRGMUX_IN2/ADC0_SE7________*/
#define IO_PIN47_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[3] &= ~PORT_MUX_MASK; PORTB->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_3;}
#define IO_PIN47_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[3] &= ~PORT_MUX_MASK; PORTB->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_3;}
#define IO_PIN47_toHI()            {PTB->PSOR |= PORT_PIN_3;}
#define IO_PIN47_toLO()            {PTB->PCOR |= PORT_PIN_3;}
#define IO_PIN47_TOGGLE()          {PTB->PTOR |= PORT_PIN_3;}
#define IO_PIN47_getINPUT()        {(PTB->PDIR & PORT_PIN_3) >> 3U;}
#define IO_PIN47_isHI()            {(PTB->PDIR & PORT_PIN_3) == PORT_PIN_3;}
#define IO_PIN47_isLO()            {(PTB->PDIR & PORT_PIN_3) != PORT_PIN_3;}
#define IO_PIN47_PULLoff()         {PORTB->PCR[3] &= ~PORT_PULL_MASK;}
#define IO_PIN47_PULLup()          {PORTB->PCR[3] &= ~PORT_PULL_MASK; PORTB->PCR[3] |= PORT_PULL_UP;}
#define IO_PIN47_PULLdown()        {PORTB->PCR[3] &= ~PORT_PULL_MASK; PORTB->PCR[3] |= PORT_PULL_DOWN;}
#define IO_PIN47_INToff()          {PORTB->PCR[3] &= ~PORT_IRQC_MASK;}
#define IO_PIN47_INTfalling()      {PORTB->PCR[3] &= ~PORT_IRQC_MASK; PORTB->PCR[3] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN47_INTrising()       {PORTB->PCR[3] &= ~PORT_IRQC_MASK; PORTB->PCR[3] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN47_INTany()          {PORTB->PCR[3] &= ~PORT_IRQC_MASK; PORTB->PCR[3] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN47_INTclear()        {PORTB->PCR[3] |= 0x01000000;}

/*___PIN 048: PTB2/FTM1_CH0/LPSPI0_SCK/FTM1_QD_PHB/TRGMUX_IN3/ADC0_SE6________*/
#define IO_PIN48_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[2] &= ~PORT_MUX_MASK; PORTB->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_2;}
#define IO_PIN48_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[2] &= ~PORT_MUX_MASK; PORTB->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_2;}
#define IO_PIN48_toHI()            {PTB->PSOR |= PORT_PIN_2;}
#define IO_PIN48_toLO()            {PTB->PCOR |= PORT_PIN_2;}
#define IO_PIN48_TOGGLE()          {PTB->PTOR |= PORT_PIN_2;}
#define IO_PIN48_getINPUT()        {(PTB->PDIR & PORT_PIN_2) >> 2U;}
#define IO_PIN48_isHI()            {(PTB->PDIR & PORT_PIN_2) == PORT_PIN_2;}
#define IO_PIN48_isLO()            {(PTB->PDIR & PORT_PIN_2) != PORT_PIN_2;}
#define IO_PIN48_PULLoff()         {PORTB->PCR[2] &= ~PORT_PULL_MASK;}
#define IO_PIN48_PULLup()          {PORTB->PCR[2] &= ~PORT_PULL_MASK; PORTB->PCR[2] |= PORT_PULL_UP;}
#define IO_PIN48_PULLdown()        {PORTB->PCR[2] &= ~PORT_PULL_MASK; PORTB->PCR[2] |= PORT_PULL_DOWN;}
#define IO_PIN48_INToff()          {PORTB->PCR[2] &= ~PORT_IRQC_MASK;}
#define IO_PIN48_INTfalling()      {PORTB->PCR[2] &= ~PORT_IRQC_MASK; PORTB->PCR[2] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN48_INTrising()       {PORTB->PCR[2] &= ~PORT_IRQC_MASK; PORTB->PCR[2] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN48_INTany()          {PORTB->PCR[2] &= ~PORT_IRQC_MASK; PORTB->PCR[2] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN48_INTclear()        {PORTB->PCR[2] |= 0x01000000;}

/*___PIN 049: PTC13/FTM3_CH7/FTM2_CH7/LPUART2_RTS_____________________________*/
#define IO_PIN49_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[13] &= ~PORT_MUX_MASK; PORTC->PCR[13] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_13;}
#define IO_PIN49_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[13] &= ~PORT_MUX_MASK; PORTC->PCR[13] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_13;}
#define IO_PIN49_toHI()            {PTC->PSOR |= PORT_PIN_13;}
#define IO_PIN49_toLO()            {PTC->PCOR |= PORT_PIN_13;}
#define IO_PIN49_TOGGLE()          {PTC->PTOR |= PORT_PIN_13;}
#define IO_PIN49_getINPUT()        {(PTC->PDIR & PORT_PIN_13) >> 13U;}
#define IO_PIN49_isHI()            {(PTC->PDIR & PORT_PIN_13) == PORT_PIN_13;}
#define IO_PIN49_isLO()            {(PTC->PDIR & PORT_PIN_13) != PORT_PIN_13;}
#define IO_PIN49_PULLoff()         {PORTC->PCR[13] &= ~PORT_PULL_MASK;}
#define IO_PIN49_PULLup()          {PORTC->PCR[13] &= ~PORT_PULL_MASK; PORTC->PCR[13] |= PORT_PULL_UP;}
#define IO_PIN49_PULLdown()        {PORTC->PCR[13] &= ~PORT_PULL_MASK; PORTC->PCR[13] |= PORT_PULL_DOWN;}
#define IO_PIN49_INToff()          {PORTC->PCR[13] &= ~PORT_IRQC_MASK;}
#define IO_PIN49_INTfalling()      {PORTC->PCR[13] &= ~PORT_IRQC_MASK; PORTC->PCR[13] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN49_INTrising()       {PORTC->PCR[13] &= ~PORT_IRQC_MASK; PORTC->PCR[13] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN49_INTany()          {PORTC->PCR[13] &= ~PORT_IRQC_MASK; PORTC->PCR[13] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN49_INTclear()        {PORTC->PCR[13] |= 0x01000000;}

/*___PIN 050: PTC12/FTM3_CH6/FTM2_CH6/LPUART2_CTS_____________________________*/
#define IO_PIN50_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[12] &= ~PORT_MUX_MASK; PORTC->PCR[12] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_12;}
#define IO_PIN50_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[12] &= ~PORT_MUX_MASK; PORTC->PCR[12] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_12;}
#define IO_PIN50_toHI()            {PTC->PSOR |= PORT_PIN_12;}
#define IO_PIN50_toLO()            {PTC->PCOR |= PORT_PIN_12;}
#define IO_PIN50_TOGGLE()          {PTC->PTOR |= PORT_PIN_12;}
#define IO_PIN50_getINPUT()        {(PTC->PDIR & PORT_PIN_12) >> 12U;}
#define IO_PIN50_isHI()            {(PTC->PDIR & PORT_PIN_12) == PORT_PIN_12;}
#define IO_PIN50_isLO()            {(PTC->PDIR & PORT_PIN_12) != PORT_PIN_12;}
#define IO_PIN50_PULLoff()         {PORTC->PCR[12] &= ~PORT_PULL_MASK;}
#define IO_PIN50_PULLup()          {PORTC->PCR[12] &= ~PORT_PULL_MASK; PORTC->PCR[12] |= PORT_PULL_UP;}
#define IO_PIN50_PULLdown()        {PORTC->PCR[12] &= ~PORT_PULL_MASK; PORTC->PCR[12] |= PORT_PULL_DOWN;}
#define IO_PIN50_INToff()          {PORTC->PCR[12] &= ~PORT_IRQC_MASK;}
#define IO_PIN50_INTfalling()      {PORTC->PCR[12] &= ~PORT_IRQC_MASK; PORTC->PCR[12] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN50_INTrising()       {PORTC->PCR[12] &= ~PORT_IRQC_MASK; PORTC->PCR[12] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN50_INTany()          {PORTC->PCR[12] &= ~PORT_IRQC_MASK; PORTC->PCR[12] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN50_INTclear()        {PORTC->PCR[12] |= 0x01000000;}

/*___PIN 051: PTC11/FTM3_CH5/TRGMUX_IN10______________________________________*/
#define IO_PIN51_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[11] &= ~PORT_MUX_MASK; PORTC->PCR[11] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_11;}
#define IO_PIN51_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[11] &= ~PORT_MUX_MASK; PORTC->PCR[11] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_11;}
#define IO_PIN51_toHI()            {PTC->PSOR |= PORT_PIN_11;}
#define IO_PIN51_toLO()            {PTC->PCOR |= PORT_PIN_11;}
#define IO_PIN51_TOGGLE()          {PTC->PTOR |= PORT_PIN_11;}
#define IO_PIN51_getINPUT()        {(PTC->PDIR & PORT_PIN_11) >> 11U;}
#define IO_PIN51_isHI()            {(PTC->PDIR & PORT_PIN_11) == PORT_PIN_11;}
#define IO_PIN51_isLO()            {(PTC->PDIR & PORT_PIN_11) != PORT_PIN_11;}
#define IO_PIN51_PULLoff()         {PORTC->PCR[11] &= ~PORT_PULL_MASK;}
#define IO_PIN51_PULLup()          {PORTC->PCR[11] &= ~PORT_PULL_MASK; PORTC->PCR[11] |= PORT_PULL_UP;}
#define IO_PIN51_PULLdown()        {PORTC->PCR[11] &= ~PORT_PULL_MASK; PORTC->PCR[11] |= PORT_PULL_DOWN;}
#define IO_PIN51_INToff()          {PORTC->PCR[11] &= ~PORT_IRQC_MASK;}
#define IO_PIN51_INTfalling()      {PORTC->PCR[11] &= ~PORT_IRQC_MASK; PORTC->PCR[11] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN51_INTrising()       {PORTC->PCR[11] &= ~PORT_IRQC_MASK; PORTC->PCR[11] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN51_INTany()          {PORTC->PCR[11] &= ~PORT_IRQC_MASK; PORTC->PCR[11] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN51_INTclear()        {PORTC->PCR[11] |= 0x01000000;}

/*___PIN 052: PTC10/FTM3_CH4/TRGMUX_IN11______________________________________*/
#define IO_PIN52_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[10] &= ~PORT_MUX_MASK; PORTC->PCR[10] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_10;}
#define IO_PIN52_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[10] &= ~PORT_MUX_MASK; PORTC->PCR[10] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_10;}
#define IO_PIN52_toHI()            {PTC->PSOR |= PORT_PIN_10;}
#define IO_PIN52_toLO()            {PTC->PCOR |= PORT_PIN_10;}
#define IO_PIN52_TOGGLE()          {PTC->PTOR |= PORT_PIN_10;}
#define IO_PIN52_getINPUT()        {(PTC->PDIR & PORT_PIN_10) >> 10U;}
#define IO_PIN52_isHI()            {(PTC->PDIR & PORT_PIN_10) == PORT_PIN_10;}
#define IO_PIN52_isLO()            {(PTC->PDIR & PORT_PIN_10) != PORT_PIN_10;}
#define IO_PIN52_PULLoff()         {PORTC->PCR[10] &= ~PORT_PULL_MASK;}
#define IO_PIN52_PULLup()          {PORTC->PCR[10] &= ~PORT_PULL_MASK; PORTC->PCR[10] |= PORT_PULL_UP;}
#define IO_PIN52_PULLdown()        {PORTC->PCR[10] &= ~PORT_PULL_MASK; PORTC->PCR[10] |= PORT_PULL_DOWN;}
#define IO_PIN52_INToff()          {PORTC->PCR[10] &= ~PORT_IRQC_MASK;}
#define IO_PIN52_INTfalling()      {PORTC->PCR[10] &= ~PORT_IRQC_MASK; PORTC->PCR[10] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN52_INTrising()       {PORTC->PCR[10] &= ~PORT_IRQC_MASK; PORTC->PCR[10] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN52_INTany()          {PORTC->PCR[10] &= ~PORT_IRQC_MASK; PORTC->PCR[10] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN52_INTclear()        {PORTC->PCR[10] |= 0x01000000;}

/*___PIN 053: PTB1/LPUART0_TX/LPSPI0_SOUT/TCLK0/CAN0_TX/ADC0_SE5/ADC1_SE15____*/
#define IO_PIN53_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[1] &= ~PORT_MUX_MASK; PORTB->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_1;}
#define IO_PIN53_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[1] &= ~PORT_MUX_MASK; PORTB->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_1;}
#define IO_PIN53_toHI()            {PTB->PSOR |= PORT_PIN_1;}
#define IO_PIN53_toLO()            {PTB->PCOR |= PORT_PIN_1;}
#define IO_PIN53_TOGGLE()          {PTB->PTOR |= PORT_PIN_1;}
#define IO_PIN53_getINPUT()        {(PTB->PDIR & PORT_PIN_1) >> 1U;}
#define IO_PIN53_isHI()            {(PTB->PDIR & PORT_PIN_1) == PORT_PIN_1;}
#define IO_PIN53_isLO()            {(PTB->PDIR & PORT_PIN_1) != PORT_PIN_1;}
#define IO_PIN53_PULLoff()         {PORTB->PCR[1] &= ~PORT_PULL_MASK;}
#define IO_PIN53_PULLup()          {PORTB->PCR[1] &= ~PORT_PULL_MASK; PORTB->PCR[1] |= PORT_PULL_UP;}
#define IO_PIN53_PULLdown()        {PORTB->PCR[1] &= ~PORT_PULL_MASK; PORTB->PCR[1] |= PORT_PULL_DOWN;}
#define IO_PIN53_INToff()          {PORTB->PCR[1] &= ~PORT_IRQC_MASK;}
#define IO_PIN53_INTfalling()      {PORTB->PCR[1] &= ~PORT_IRQC_MASK; PORTB->PCR[1] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN53_INTrising()       {PORTB->PCR[1] &= ~PORT_IRQC_MASK; PORTB->PCR[1] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN53_INTany()          {PORTB->PCR[1] &= ~PORT_IRQC_MASK; PORTB->PCR[1] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN53_INTclear()        {PORTB->PCR[1] |= 0x01000000;}

/*___PIN 054: PTB0/LPUART0_RX/LPSPI0_PCS0/LPTMR0_ALT3/CAN0_RX/ADC0_SE4/ADC1_SE14_*/
#define IO_PIN54_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[0] &= ~PORT_MUX_MASK; PORTB->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_0;}
#define IO_PIN54_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[0] &= ~PORT_MUX_MASK; PORTB->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_0;}
#define IO_PIN54_toHI()            {PTB->PSOR |= PORT_PIN_0;}
#define IO_PIN54_toLO()            {PTB->PCOR |= PORT_PIN_0;}
#define IO_PIN54_TOGGLE()          {PTB->PTOR |= PORT_PIN_0;}
#define IO_PIN54_getINPUT()        {(PTB->PDIR & PORT_PIN_0) >> 0U;}
#define IO_PIN54_isHI()            {(PTB->PDIR & PORT_PIN_0) == PORT_PIN_0;}
#define IO_PIN54_isLO()            {(PTB->PDIR & PORT_PIN_0) != PORT_PIN_0;}
#define IO_PIN54_PULLoff()         {PORTB->PCR[0] &= ~PORT_PULL_MASK;}
#define IO_PIN54_PULLup()          {PORTB->PCR[0] &= ~PORT_PULL_MASK; PORTB->PCR[0] |= PORT_PULL_UP;}
#define IO_PIN54_PULLdown()        {PORTB->PCR[0] &= ~PORT_PULL_MASK; PORTB->PCR[0] |= PORT_PULL_DOWN;}
#define IO_PIN54_INToff()          {PORTB->PCR[0] &= ~PORT_IRQC_MASK;}
#define IO_PIN54_INTfalling()      {PORTB->PCR[0] &= ~PORT_IRQC_MASK; PORTB->PCR[0] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN54_INTrising()       {PORTB->PCR[0] &= ~PORT_IRQC_MASK; PORTB->PCR[0] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN54_INTany()          {PORTB->PCR[0] &= ~PORT_IRQC_MASK; PORTB->PCR[0] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN54_INTclear()        {PORTB->PCR[0] |= 0x01000000;}

/*___PIN 055: PTC9/LPUART1_TX/FTM1_FLT1/LPUART0_RTS___________________________*/
#define IO_PIN55_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[9] &= ~PORT_MUX_MASK; PORTC->PCR[9] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_9;}
#define IO_PIN55_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[9] &= ~PORT_MUX_MASK; PORTC->PCR[9] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_9;}
#define IO_PIN55_toHI()            {PTC->PSOR |= PORT_PIN_9;}
#define IO_PIN55_toLO()            {PTC->PCOR |= PORT_PIN_9;}
#define IO_PIN55_TOGGLE()          {PTC->PTOR |= PORT_PIN_9;}
#define IO_PIN55_getINPUT()        {(PTC->PDIR & PORT_PIN_9) >> 9U;}
#define IO_PIN55_isHI()            {(PTC->PDIR & PORT_PIN_9) == PORT_PIN_9;}
#define IO_PIN55_isLO()            {(PTC->PDIR & PORT_PIN_9) != PORT_PIN_9;}
#define IO_PIN55_PULLoff()         {PORTC->PCR[9] &= ~PORT_PULL_MASK;}
#define IO_PIN55_PULLup()          {PORTC->PCR[9] &= ~PORT_PULL_MASK; PORTC->PCR[9] |= PORT_PULL_UP;}
#define IO_PIN55_PULLdown()        {PORTC->PCR[9] &= ~PORT_PULL_MASK; PORTC->PCR[9] |= PORT_PULL_DOWN;}
#define IO_PIN55_INToff()          {PORTC->PCR[9] &= ~PORT_IRQC_MASK;}
#define IO_PIN55_INTfalling()      {PORTC->PCR[9] &= ~PORT_IRQC_MASK; PORTC->PCR[9] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN55_INTrising()       {PORTC->PCR[9] &= ~PORT_IRQC_MASK; PORTC->PCR[9] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN55_INTany()          {PORTC->PCR[9] &= ~PORT_IRQC_MASK; PORTC->PCR[9] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN55_INTclear()        {PORTC->PCR[9] |= 0x01000000;}

/*___PIN 056: PTC8/LPUART1_RX/FTM1_FLT0/LPUART0_CTS___________________________*/
#define IO_PIN56_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[8] &= ~PORT_MUX_MASK; PORTC->PCR[8] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_8;}
#define IO_PIN56_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[8] &= ~PORT_MUX_MASK; PORTC->PCR[8] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_8;}
#define IO_PIN56_toHI()            {PTC->PSOR |= PORT_PIN_8;}
#define IO_PIN56_toLO()            {PTC->PCOR |= PORT_PIN_8;}
#define IO_PIN56_TOGGLE()          {PTC->PTOR |= PORT_PIN_8;}
#define IO_PIN56_getINPUT()        {(PTC->PDIR & PORT_PIN_8) >> 8U;}
#define IO_PIN56_isHI()            {(PTC->PDIR & PORT_PIN_8) == PORT_PIN_8;}
#define IO_PIN56_isLO()            {(PTC->PDIR & PORT_PIN_8) != PORT_PIN_8;}
#define IO_PIN56_PULLoff()         {PORTC->PCR[8] &= ~PORT_PULL_MASK;}
#define IO_PIN56_PULLup()          {PORTC->PCR[8] &= ~PORT_PULL_MASK; PORTC->PCR[8] |= PORT_PULL_UP;}
#define IO_PIN56_PULLdown()        {PORTC->PCR[8] &= ~PORT_PULL_MASK; PORTC->PCR[8] |= PORT_PULL_DOWN;}
#define IO_PIN56_INToff()          {PORTC->PCR[8] &= ~PORT_IRQC_MASK;}
#define IO_PIN56_INTfalling()      {PORTC->PCR[8] &= ~PORT_IRQC_MASK; PORTC->PCR[8] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN56_INTrising()       {PORTC->PCR[8] &= ~PORT_IRQC_MASK; PORTC->PCR[8] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN56_INTany()          {PORTC->PCR[8] &= ~PORT_IRQC_MASK; PORTC->PCR[8] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN56_INTclear()        {PORTC->PCR[8] |= 0x01000000;}

/*___PIN 057: PTA7/FTM0_FLT2/RTC_CLKIN/LPUART1_RTS/ADC0_SE3___________________*/
#define IO_PIN57_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[7] &= ~PORT_MUX_MASK; PORTA->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_7;}
#define IO_PIN57_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[7] &= ~PORT_MUX_MASK; PORTA->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_7;}
#define IO_PIN57_toHI()            {PTA->PSOR |= PORT_PIN_7;}
#define IO_PIN57_toLO()            {PTA->PCOR |= PORT_PIN_7;}
#define IO_PIN57_TOGGLE()          {PTA->PTOR |= PORT_PIN_7;}
#define IO_PIN57_getINPUT()        {(PTA->PDIR & PORT_PIN_7) >> 7U;}
#define IO_PIN57_isHI()            {(PTA->PDIR & PORT_PIN_7) == PORT_PIN_7;}
#define IO_PIN57_isLO()            {(PTA->PDIR & PORT_PIN_7) != PORT_PIN_7;}
#define IO_PIN57_PULLoff()         {PORTA->PCR[7] &= ~PORT_PULL_MASK;}
#define IO_PIN57_PULLup()          {PORTA->PCR[7] &= ~PORT_PULL_MASK; PORTA->PCR[7] |= PORT_PULL_UP;}
#define IO_PIN57_PULLdown()        {PORTA->PCR[7] &= ~PORT_PULL_MASK; PORTA->PCR[7] |= PORT_PULL_DOWN;}
#define IO_PIN57_INToff()          {PORTA->PCR[7] &= ~PORT_IRQC_MASK;}
#define IO_PIN57_INTfalling()      {PORTA->PCR[7] &= ~PORT_IRQC_MASK; PORTA->PCR[7] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN57_INTrising()       {PORTA->PCR[7] &= ~PORT_IRQC_MASK; PORTA->PCR[7] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN57_INTany()          {PORTA->PCR[7] &= ~PORT_IRQC_MASK; PORTA->PCR[7] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN57_INTclear()        {PORTA->PCR[7] |= 0x01000000;}

/*___PIN 058: PTA6/FTM0_FLT1/LPSPI1_PCS1/LPUART1_CTS/ADC0_SE2_________________*/
#define IO_PIN58_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[6] &= ~PORT_MUX_MASK; PORTA->PCR[6] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_6;}
#define IO_PIN58_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[6] &= ~PORT_MUX_MASK; PORTA->PCR[6] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_6;}
#define IO_PIN58_toHI()            {PTA->PSOR |= PORT_PIN_6;}
#define IO_PIN58_toLO()            {PTA->PCOR |= PORT_PIN_6;}
#define IO_PIN58_TOGGLE()          {PTA->PTOR |= PORT_PIN_6;}
#define IO_PIN58_getINPUT()        {(PTA->PDIR & PORT_PIN_6) >> 6U;}
#define IO_PIN58_isHI()            {(PTA->PDIR & PORT_PIN_6) == PORT_PIN_6;}
#define IO_PIN58_isLO()            {(PTA->PDIR & PORT_PIN_6) != PORT_PIN_6;}
#define IO_PIN58_PULLoff()         {PORTA->PCR[6] &= ~PORT_PULL_MASK;}
#define IO_PIN58_PULLup()          {PORTA->PCR[6] &= ~PORT_PULL_MASK; PORTA->PCR[6] |= PORT_PULL_UP;}
#define IO_PIN58_PULLdown()        {PORTA->PCR[6] &= ~PORT_PULL_MASK; PORTA->PCR[6] |= PORT_PULL_DOWN;}
#define IO_PIN58_INToff()          {PORTA->PCR[6] &= ~PORT_IRQC_MASK;}
#define IO_PIN58_INTfalling()      {PORTA->PCR[6] &= ~PORT_IRQC_MASK; PORTA->PCR[6] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN58_INTrising()       {PORTA->PCR[6] &= ~PORT_IRQC_MASK; PORTA->PCR[6] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN58_INTany()          {PORTA->PCR[6] &= ~PORT_IRQC_MASK; PORTA->PCR[6] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN58_INTclear()        {PORTA->PCR[6] |= 0x01000000;}

/*___PIN 059: PTE7/FTM0_CH7/FTM3_FLT0_________________________________________*/
#define IO_PIN59_toOUT()           {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[7] &= ~PORT_MUX_MASK; PORTE->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_7;}
#define IO_PIN59_toIN()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[7] &= ~PORT_MUX_MASK; PORTE->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_7;}
#define IO_PIN59_toHI()            {PTE->PSOR |= PORT_PIN_7;}
#define IO_PIN59_toLO()            {PTE->PCOR |= PORT_PIN_7;}
#define IO_PIN59_TOGGLE()          {PTE->PTOR |= PORT_PIN_7;}
#define IO_PIN59_getINPUT()        {(PTE->PDIR & PORT_PIN_7) >> 7U;}
#define IO_PIN59_isHI()            {(PTE->PDIR & PORT_PIN_7) == PORT_PIN_7;}
#define IO_PIN59_isLO()            {(PTE->PDIR & PORT_PIN_7) != PORT_PIN_7;}
#define IO_PIN59_PULLoff()         {PORTE->PCR[7] &= ~PORT_PULL_MASK;}
#define IO_PIN59_PULLup()          {PORTE->PCR[7] &= ~PORT_PULL_MASK; PORTE->PCR[7] |= PORT_PULL_UP;}
#define IO_PIN59_PULLdown()        {PORTE->PCR[7] &= ~PORT_PULL_MASK; PORTE->PCR[7] |= PORT_PULL_DOWN;}
#define IO_PIN59_INToff()          {PORTE->PCR[7] &= ~PORT_IRQC_MASK;}
#define IO_PIN59_INTfalling()      {PORTE->PCR[7] &= ~PORT_IRQC_MASK; PORTE->PCR[7] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN59_INTrising()       {PORTE->PCR[7] &= ~PORT_IRQC_MASK; PORTE->PCR[7] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN59_INTany()          {PORTE->PCR[7] &= ~PORT_IRQC_MASK; PORTE->PCR[7] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN59_INTclear()        {PORTE->PCR[7] |= 0x01000000;}

/*___PIN 060: VSS_____________________________________________________________*/

/*___PIN 061: VDD_____________________________________________________________*/

/*___PIN 062: PTA17/FTM0_CH6/FTM3_FLT0/EWM_OUT_b______________________________*/
#define IO_PIN62_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[17] &= ~PORT_MUX_MASK; PORTA->PCR[17] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_17;}
#define IO_PIN62_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[17] &= ~PORT_MUX_MASK; PORTA->PCR[17] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_17;}
#define IO_PIN62_toHI()            {PTA->PSOR |= PORT_PIN_17;}
#define IO_PIN62_toLO()            {PTA->PCOR |= PORT_PIN_17;}
#define IO_PIN62_TOGGLE()          {PTA->PTOR |= PORT_PIN_17;}
#define IO_PIN62_getINPUT()        {(PTA->PDIR & PORT_PIN_17) >> 17U;}
#define IO_PIN62_isHI()            {(PTA->PDIR & PORT_PIN_17) == PORT_PIN_17;}
#define IO_PIN62_isLO()            {(PTA->PDIR & PORT_PIN_17) != PORT_PIN_17;}
#define IO_PIN62_PULLoff()         {PORTA->PCR[17] &= ~PORT_PULL_MASK;}
#define IO_PIN62_PULLup()          {PORTA->PCR[17] &= ~PORT_PULL_MASK; PORTA->PCR[17] |= PORT_PULL_UP;}
#define IO_PIN62_PULLdown()        {PORTA->PCR[17] &= ~PORT_PULL_MASK; PORTA->PCR[17] |= PORT_PULL_DOWN;}
#define IO_PIN62_INToff()          {PORTA->PCR[17] &= ~PORT_IRQC_MASK;}
#define IO_PIN62_INTfalling()      {PORTA->PCR[17] &= ~PORT_IRQC_MASK; PORTA->PCR[17] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN62_INTrising()       {PORTA->PCR[17] &= ~PORT_IRQC_MASK; PORTA->PCR[17] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN62_INTany()          {PORTA->PCR[17] &= ~PORT_IRQC_MASK; PORTA->PCR[17] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN62_INTclear()        {PORTA->PCR[17] |= 0x01000000;}

/*___PIN 063: PTB17/FTM0_CH5/LPSPI1_PCS3______________________________________*/
#define IO_PIN63_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[17] &= ~PORT_MUX_MASK; PORTB->PCR[17] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_17;}
#define IO_PIN63_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[17] &= ~PORT_MUX_MASK; PORTB->PCR[17] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_17;}
#define IO_PIN63_toHI()            {PTB->PSOR |= PORT_PIN_17;}
#define IO_PIN63_toLO()            {PTB->PCOR |= PORT_PIN_17;}
#define IO_PIN63_TOGGLE()          {PTB->PTOR |= PORT_PIN_17;}
#define IO_PIN63_getINPUT()        {(PTB->PDIR & PORT_PIN_17) >> 17U;}
#define IO_PIN63_isHI()            {(PTB->PDIR & PORT_PIN_17) == PORT_PIN_17;}
#define IO_PIN63_isLO()            {(PTB->PDIR & PORT_PIN_17) != PORT_PIN_17;}
#define IO_PIN63_PULLoff()         {PORTB->PCR[17] &= ~PORT_PULL_MASK;}
#define IO_PIN63_PULLup()          {PORTB->PCR[17] &= ~PORT_PULL_MASK; PORTB->PCR[17] |= PORT_PULL_UP;}
#define IO_PIN63_PULLdown()        {PORTB->PCR[17] &= ~PORT_PULL_MASK; PORTB->PCR[17] |= PORT_PULL_DOWN;}
#define IO_PIN63_INToff()          {PORTB->PCR[17] &= ~PORT_IRQC_MASK;}
#define IO_PIN63_INTfalling()      {PORTB->PCR[17] &= ~PORT_IRQC_MASK; PORTB->PCR[17] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN63_INTrising()       {PORTB->PCR[17] &= ~PORT_IRQC_MASK; PORTB->PCR[17] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN63_INTany()          {PORTB->PCR[17] &= ~PORT_IRQC_MASK; PORTB->PCR[17] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN63_INTclear()        {PORTB->PCR[17] |= 0x01000000;}

/*___PIN 064: PTB16/FTM0_CH4/LPSPI1_SOUT/ADC1_SE15____________________________*/
#define IO_PIN64_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[16] &= ~PORT_MUX_MASK; PORTB->PCR[16] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_16;}
#define IO_PIN64_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[16] &= ~PORT_MUX_MASK; PORTB->PCR[16] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_16;}
#define IO_PIN64_toHI()            {PTB->PSOR |= PORT_PIN_16;}
#define IO_PIN64_toLO()            {PTB->PCOR |= PORT_PIN_16;}
#define IO_PIN64_TOGGLE()          {PTB->PTOR |= PORT_PIN_16;}
#define IO_PIN64_getINPUT()        {(PTB->PDIR & PORT_PIN_16) >> 16U;}
#define IO_PIN64_isHI()            {(PTB->PDIR & PORT_PIN_16) == PORT_PIN_16;}
#define IO_PIN64_isLO()            {(PTB->PDIR & PORT_PIN_16) != PORT_PIN_16;}
#define IO_PIN64_PULLoff()         {PORTB->PCR[16] &= ~PORT_PULL_MASK;}
#define IO_PIN64_PULLup()          {PORTB->PCR[16] &= ~PORT_PULL_MASK; PORTB->PCR[16] |= PORT_PULL_UP;}
#define IO_PIN64_PULLdown()        {PORTB->PCR[16] &= ~PORT_PULL_MASK; PORTB->PCR[16] |= PORT_PULL_DOWN;}
#define IO_PIN64_INToff()          {PORTB->PCR[16] &= ~PORT_IRQC_MASK;}
#define IO_PIN64_INTfalling()      {PORTB->PCR[16] &= ~PORT_IRQC_MASK; PORTB->PCR[16] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN64_INTrising()       {PORTB->PCR[16] &= ~PORT_IRQC_MASK; PORTB->PCR[16] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN64_INTany()          {PORTB->PCR[16] &= ~PORT_IRQC_MASK; PORTB->PCR[16] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN64_INTclear()        {PORTB->PCR[16] |= 0x01000000;}

/*___PIN 065: PTB15/FTM0_CH3/LPSPI1_SIN/ADC1_SE14_____________________________*/
#define IO_PIN65_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[15] &= ~PORT_MUX_MASK; PORTB->PCR[15] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_15;}
#define IO_PIN65_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[15] &= ~PORT_MUX_MASK; PORTB->PCR[15] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_15;}
#define IO_PIN65_toHI()            {PTB->PSOR |= PORT_PIN_15;}
#define IO_PIN65_toLO()            {PTB->PCOR |= PORT_PIN_15;}
#define IO_PIN65_TOGGLE()          {PTB->PTOR |= PORT_PIN_15;}
#define IO_PIN65_getINPUT()        {(PTB->PDIR & PORT_PIN_15) >> 15U;}
#define IO_PIN65_isHI()            {(PTB->PDIR & PORT_PIN_15) == PORT_PIN_15;}
#define IO_PIN65_isLO()            {(PTB->PDIR & PORT_PIN_15) != PORT_PIN_15;}
#define IO_PIN65_PULLoff()         {PORTB->PCR[15] &= ~PORT_PULL_MASK;}
#define IO_PIN65_PULLup()          {PORTB->PCR[15] &= ~PORT_PULL_MASK; PORTB->PCR[15] |= PORT_PULL_UP;}
#define IO_PIN65_PULLdown()        {PORTB->PCR[15] &= ~PORT_PULL_MASK; PORTB->PCR[15] |= PORT_PULL_DOWN;}
#define IO_PIN65_INToff()          {PORTB->PCR[15] &= ~PORT_IRQC_MASK;}
#define IO_PIN65_INTfalling()      {PORTB->PCR[15] &= ~PORT_IRQC_MASK; PORTB->PCR[15] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN65_INTrising()       {PORTB->PCR[15] &= ~PORT_IRQC_MASK; PORTB->PCR[15] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN65_INTany()          {PORTB->PCR[15] &= ~PORT_IRQC_MASK; PORTB->PCR[15] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN65_INTclear()        {PORTB->PCR[15] |= 0x01000000;}

/*___PIN 066: PTB14/FTM0_CH2/LPSPI1_SCK/ADC1_SE9/ADC0_SE9_____________________*/
#define IO_PIN66_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[14] &= ~PORT_MUX_MASK; PORTB->PCR[14] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_14;}
#define IO_PIN66_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[14] &= ~PORT_MUX_MASK; PORTB->PCR[14] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_14;}
#define IO_PIN66_toHI()            {PTB->PSOR |= PORT_PIN_14;}
#define IO_PIN66_toLO()            {PTB->PCOR |= PORT_PIN_14;}
#define IO_PIN66_TOGGLE()          {PTB->PTOR |= PORT_PIN_14;}
#define IO_PIN66_getINPUT()        {(PTB->PDIR & PORT_PIN_14) >> 14U;}
#define IO_PIN66_isHI()            {(PTB->PDIR & PORT_PIN_14) == PORT_PIN_14;}
#define IO_PIN66_isLO()            {(PTB->PDIR & PORT_PIN_14) != PORT_PIN_14;}
#define IO_PIN66_PULLoff()         {PORTB->PCR[14] &= ~PORT_PULL_MASK;}
#define IO_PIN66_PULLup()          {PORTB->PCR[14] &= ~PORT_PULL_MASK; PORTB->PCR[14] |= PORT_PULL_UP;}
#define IO_PIN66_PULLdown()        {PORTB->PCR[14] &= ~PORT_PULL_MASK; PORTB->PCR[14] |= PORT_PULL_DOWN;}
#define IO_PIN66_INToff()          {PORTB->PCR[14] &= ~PORT_IRQC_MASK;}
#define IO_PIN66_INTfalling()      {PORTB->PCR[14] &= ~PORT_IRQC_MASK; PORTB->PCR[14] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN66_INTrising()       {PORTB->PCR[14] &= ~PORT_IRQC_MASK; PORTB->PCR[14] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN66_INTany()          {PORTB->PCR[14] &= ~PORT_IRQC_MASK; PORTB->PCR[14] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN66_INTclear()        {PORTB->PCR[14] |= 0x01000000;}

/*___PIN 067: PTB13/FTM0_CH1/FTM3_FLT1/CAN2_TX/ADC1_SE8/ADC0_SE8______________*/
#define IO_PIN67_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[13] &= ~PORT_MUX_MASK; PORTB->PCR[13] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_13;}
#define IO_PIN67_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[13] &= ~PORT_MUX_MASK; PORTB->PCR[13] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_13;}
#define IO_PIN67_toHI()            {PTB->PSOR |= PORT_PIN_13;}
#define IO_PIN67_toLO()            {PTB->PCOR |= PORT_PIN_13;}
#define IO_PIN67_TOGGLE()          {PTB->PTOR |= PORT_PIN_13;}
#define IO_PIN67_getINPUT()        {(PTB->PDIR & PORT_PIN_13) >> 13U;}
#define IO_PIN67_isHI()            {(PTB->PDIR & PORT_PIN_13) == PORT_PIN_13;}
#define IO_PIN67_isLO()            {(PTB->PDIR & PORT_PIN_13) != PORT_PIN_13;}
#define IO_PIN67_PULLoff()         {PORTB->PCR[13] &= ~PORT_PULL_MASK;}
#define IO_PIN67_PULLup()          {PORTB->PCR[13] &= ~PORT_PULL_MASK; PORTB->PCR[13] |= PORT_PULL_UP;}
#define IO_PIN67_PULLdown()        {PORTB->PCR[13] &= ~PORT_PULL_MASK; PORTB->PCR[13] |= PORT_PULL_DOWN;}
#define IO_PIN67_INToff()          {PORTB->PCR[13] &= ~PORT_IRQC_MASK;}
#define IO_PIN67_INTfalling()      {PORTB->PCR[13] &= ~PORT_IRQC_MASK; PORTB->PCR[13] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN67_INTrising()       {PORTB->PCR[13] &= ~PORT_IRQC_MASK; PORTB->PCR[13] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN67_INTany()          {PORTB->PCR[13] &= ~PORT_IRQC_MASK; PORTB->PCR[13] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN67_INTclear()        {PORTB->PCR[13] |= 0x01000000;}

/*___PIN 068: PTB12/FTM0_CH0/FTM3_FLT2/CAN2_RX/ADC1_SE7_______________________*/
#define IO_PIN68_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[12] &= ~PORT_MUX_MASK; PORTB->PCR[12] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_12;}
#define IO_PIN68_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[12] &= ~PORT_MUX_MASK; PORTB->PCR[12] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_12;}
#define IO_PIN68_toHI()            {PTB->PSOR |= PORT_PIN_12;}
#define IO_PIN68_toLO()            {PTB->PCOR |= PORT_PIN_12;}
#define IO_PIN68_TOGGLE()          {PTB->PTOR |= PORT_PIN_12;}
#define IO_PIN68_getINPUT()        {(PTB->PDIR & PORT_PIN_12) >> 12U;}
#define IO_PIN68_isHI()            {(PTB->PDIR & PORT_PIN_12) == PORT_PIN_12;}
#define IO_PIN68_isLO()            {(PTB->PDIR & PORT_PIN_12) != PORT_PIN_12;}
#define IO_PIN68_PULLoff()         {PORTB->PCR[12] &= ~PORT_PULL_MASK;}
#define IO_PIN68_PULLup()          {PORTB->PCR[12] &= ~PORT_PULL_MASK; PORTB->PCR[12] |= PORT_PULL_UP;}
#define IO_PIN68_PULLdown()        {PORTB->PCR[12] &= ~PORT_PULL_MASK; PORTB->PCR[12] |= PORT_PULL_DOWN;}
#define IO_PIN68_INToff()          {PORTB->PCR[12] &= ~PORT_IRQC_MASK;}
#define IO_PIN68_INTfalling()      {PORTB->PCR[12] &= ~PORT_IRQC_MASK; PORTB->PCR[12] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN68_INTrising()       {PORTB->PCR[12] &= ~PORT_IRQC_MASK; PORTB->PCR[12] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN68_INTany()          {PORTB->PCR[12] &= ~PORT_IRQC_MASK; PORTB->PCR[12] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN68_INTclear()        {PORTB->PCR[12] |= 0x01000000;}

/*___PIN 069: PTD4/FTM0_FLT3/FTM3_FLT3/ADC1_SE6_______________________________*/
#define IO_PIN69_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[4] &= ~PORT_MUX_MASK; PORTD->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_4;}
#define IO_PIN69_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[4] &= ~PORT_MUX_MASK; PORTD->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_4;}
#define IO_PIN69_toHI()            {PTD->PSOR |= PORT_PIN_4;}
#define IO_PIN69_toLO()            {PTD->PCOR |= PORT_PIN_4;}
#define IO_PIN69_TOGGLE()          {PTD->PTOR |= PORT_PIN_4;}
#define IO_PIN69_getINPUT()        {(PTD->PDIR & PORT_PIN_4) >> 4U;}
#define IO_PIN69_isHI()            {(PTD->PDIR & PORT_PIN_4) == PORT_PIN_4;}
#define IO_PIN69_isLO()            {(PTD->PDIR & PORT_PIN_4) != PORT_PIN_4;}
#define IO_PIN69_PULLoff()         {PORTD->PCR[4] &= ~PORT_PULL_MASK;}
#define IO_PIN69_PULLup()          {PORTD->PCR[4] &= ~PORT_PULL_MASK; PORTD->PCR[4] |= PORT_PULL_UP;}
#define IO_PIN69_PULLdown()        {PORTD->PCR[4] &= ~PORT_PULL_MASK; PORTD->PCR[4] |= PORT_PULL_DOWN;}
#define IO_PIN69_INToff()          {PORTD->PCR[4] &= ~PORT_IRQC_MASK;}
#define IO_PIN69_INTfalling()      {PORTD->PCR[4] &= ~PORT_IRQC_MASK; PORTD->PCR[4] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN69_INTrising()       {PORTD->PCR[4] &= ~PORT_IRQC_MASK; PORTD->PCR[4] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN69_INTany()          {PORTD->PCR[4] &= ~PORT_IRQC_MASK; PORTD->PCR[4] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN69_INTclear()        {PORTD->PCR[4] |= 0x01000000;}

/*___PIN 070: PTD3/FTM3_CH5/LPSPI1_PCS0/FXIO_D5/FXIO_D7/TRGMUX_IN4/NMI_b/ADC1_SE3_*/
#define IO_PIN70_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[3] &= ~PORT_MUX_MASK; PORTD->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_3;}
#define IO_PIN70_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[3] &= ~PORT_MUX_MASK; PORTD->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_3;}
#define IO_PIN70_toHI()            {PTD->PSOR |= PORT_PIN_3;}
#define IO_PIN70_toLO()            {PTD->PCOR |= PORT_PIN_3;}
#define IO_PIN70_TOGGLE()          {PTD->PTOR |= PORT_PIN_3;}
#define IO_PIN70_getINPUT()        {(PTD->PDIR & PORT_PIN_3) >> 3U;}
#define IO_PIN70_isHI()            {(PTD->PDIR & PORT_PIN_3) == PORT_PIN_3;}
#define IO_PIN70_isLO()            {(PTD->PDIR & PORT_PIN_3) != PORT_PIN_3;}
#define IO_PIN70_PULLoff()         {PORTD->PCR[3] &= ~PORT_PULL_MASK;}
#define IO_PIN70_PULLup()          {PORTD->PCR[3] &= ~PORT_PULL_MASK; PORTD->PCR[3] |= PORT_PULL_UP;}
#define IO_PIN70_PULLdown()        {PORTD->PCR[3] &= ~PORT_PULL_MASK; PORTD->PCR[3] |= PORT_PULL_DOWN;}
#define IO_PIN70_INToff()          {PORTD->PCR[3] &= ~PORT_IRQC_MASK;}
#define IO_PIN70_INTfalling()      {PORTD->PCR[3] &= ~PORT_IRQC_MASK; PORTD->PCR[3] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN70_INTrising()       {PORTD->PCR[3] &= ~PORT_IRQC_MASK; PORTD->PCR[3] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN70_INTany()          {PORTD->PCR[3] &= ~PORT_IRQC_MASK; PORTD->PCR[3] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN70_INTclear()        {PORTD->PCR[3] |= 0x01000000;}

/*___PIN 071: PTD2/FTM3_CH4/LPSPI1_SOUT/FXIO_D4/FXIO_D6/TRGMUX_IN5/ADC1_SE2___*/
#define IO_PIN71_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[2] &= ~PORT_MUX_MASK; PORTD->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_2;}
#define IO_PIN71_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[2] &= ~PORT_MUX_MASK; PORTD->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_2;}
#define IO_PIN71_toHI()            {PTD->PSOR |= PORT_PIN_2;}
#define IO_PIN71_toLO()            {PTD->PCOR |= PORT_PIN_2;}
#define IO_PIN71_TOGGLE()          {PTD->PTOR |= PORT_PIN_2;}
#define IO_PIN71_getINPUT()        {(PTD->PDIR & PORT_PIN_2) >> 2U;}
#define IO_PIN71_isHI()            {(PTD->PDIR & PORT_PIN_2) == PORT_PIN_2;}
#define IO_PIN71_isLO()            {(PTD->PDIR & PORT_PIN_2) != PORT_PIN_2;}
#define IO_PIN71_PULLoff()         {PORTD->PCR[2] &= ~PORT_PULL_MASK;}
#define IO_PIN71_PULLup()          {PORTD->PCR[2] &= ~PORT_PULL_MASK; PORTD->PCR[2] |= PORT_PULL_UP;}
#define IO_PIN71_PULLdown()        {PORTD->PCR[2] &= ~PORT_PULL_MASK; PORTD->PCR[2] |= PORT_PULL_DOWN;}
#define IO_PIN71_INToff()          {PORTD->PCR[2] &= ~PORT_IRQC_MASK;}
#define IO_PIN71_INTfalling()      {PORTD->PCR[2] &= ~PORT_IRQC_MASK; PORTD->PCR[2] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN71_INTrising()       {PORTD->PCR[2] &= ~PORT_IRQC_MASK; PORTD->PCR[2] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN71_INTany()          {PORTD->PCR[2] &= ~PORT_IRQC_MASK; PORTD->PCR[2] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN71_INTclear()        {PORTD->PCR[2] |= 0x01000000;}

/*___PIN 072: PTA3/FTM3_CH1/LPI2C0_SCL/EWM_IN/FXIO_D5/LPUART0_TX/ADC1_SE1_____*/
#define IO_PIN72_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[3] &= ~PORT_MUX_MASK; PORTA->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_3;}
#define IO_PIN72_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[3] &= ~PORT_MUX_MASK; PORTA->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_3;}
#define IO_PIN72_toHI()            {PTA->PSOR |= PORT_PIN_3;}
#define IO_PIN72_toLO()            {PTA->PCOR |= PORT_PIN_3;}
#define IO_PIN72_TOGGLE()          {PTA->PTOR |= PORT_PIN_3;}
#define IO_PIN72_getINPUT()        {(PTA->PDIR & PORT_PIN_3) >> 3U;}
#define IO_PIN72_isHI()            {(PTA->PDIR & PORT_PIN_3) == PORT_PIN_3;}
#define IO_PIN72_isLO()            {(PTA->PDIR & PORT_PIN_3) != PORT_PIN_3;}
#define IO_PIN72_PULLoff()         {PORTA->PCR[3] &= ~PORT_PULL_MASK;}
#define IO_PIN72_PULLup()          {PORTA->PCR[3] &= ~PORT_PULL_MASK; PORTA->PCR[3] |= PORT_PULL_UP;}
#define IO_PIN72_PULLdown()        {PORTA->PCR[3] &= ~PORT_PULL_MASK; PORTA->PCR[3] |= PORT_PULL_DOWN;}
#define IO_PIN72_INToff()          {PORTA->PCR[3] &= ~PORT_IRQC_MASK;}
#define IO_PIN72_INTfalling()      {PORTA->PCR[3] &= ~PORT_IRQC_MASK; PORTA->PCR[3] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN72_INTrising()       {PORTA->PCR[3] &= ~PORT_IRQC_MASK; PORTA->PCR[3] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN72_INTany()          {PORTA->PCR[3] &= ~PORT_IRQC_MASK; PORTA->PCR[3] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN72_INTclear()        {PORTA->PCR[3] |= 0x01000000;}

/*___PIN 073: PTA2/FTM3_CH0/LPI2C0_SDA/EWM_OUT_b/FXIO_D4/LPUART0_RX/ADC1_SE0__*/
#define IO_PIN73_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[2] &= ~PORT_MUX_MASK; PORTA->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_2;}
#define IO_PIN73_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[2] &= ~PORT_MUX_MASK; PORTA->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_2;}
#define IO_PIN73_toHI()            {PTA->PSOR |= PORT_PIN_2;}
#define IO_PIN73_toLO()            {PTA->PCOR |= PORT_PIN_2;}
#define IO_PIN73_TOGGLE()          {PTA->PTOR |= PORT_PIN_2;}
#define IO_PIN73_getINPUT()        {(PTA->PDIR & PORT_PIN_2) >> 2U;}
#define IO_PIN73_isHI()            {(PTA->PDIR & PORT_PIN_2) == PORT_PIN_2;}
#define IO_PIN73_isLO()            {(PTA->PDIR & PORT_PIN_2) != PORT_PIN_2;}
#define IO_PIN73_PULLoff()         {PORTA->PCR[2] &= ~PORT_PULL_MASK;}
#define IO_PIN73_PULLup()          {PORTA->PCR[2] &= ~PORT_PULL_MASK; PORTA->PCR[2] |= PORT_PULL_UP;}
#define IO_PIN73_PULLdown()        {PORTA->PCR[2] &= ~PORT_PULL_MASK; PORTA->PCR[2] |= PORT_PULL_DOWN;}
#define IO_PIN73_INToff()          {PORTA->PCR[2] &= ~PORT_IRQC_MASK;}
#define IO_PIN73_INTfalling()      {PORTA->PCR[2] &= ~PORT_IRQC_MASK; PORTA->PCR[2] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN73_INTrising()       {PORTA->PCR[2] &= ~PORT_IRQC_MASK; PORTA->PCR[2] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN73_INTany()          {PORTA->PCR[2] &= ~PORT_IRQC_MASK; PORTA->PCR[2] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN73_INTclear()        {PORTA->PCR[2] |= 0x01000000;}

/*___PIN 074: PTB11/FTM3_CH3/LPI2C0_HREQ______________________________________*/
#define IO_PIN74_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[11] &= ~PORT_MUX_MASK; PORTB->PCR[11] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_11;}
#define IO_PIN74_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[11] &= ~PORT_MUX_MASK; PORTB->PCR[11] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_11;}
#define IO_PIN74_toHI()            {PTB->PSOR |= PORT_PIN_11;}
#define IO_PIN74_toLO()            {PTB->PCOR |= PORT_PIN_11;}
#define IO_PIN74_TOGGLE()          {PTB->PTOR |= PORT_PIN_11;}
#define IO_PIN74_getINPUT()        {(PTB->PDIR & PORT_PIN_11) >> 11U;}
#define IO_PIN74_isHI()            {(PTB->PDIR & PORT_PIN_11) == PORT_PIN_11;}
#define IO_PIN74_isLO()            {(PTB->PDIR & PORT_PIN_11) != PORT_PIN_11;}
#define IO_PIN74_PULLoff()         {PORTB->PCR[11] &= ~PORT_PULL_MASK;}
#define IO_PIN74_PULLup()          {PORTB->PCR[11] &= ~PORT_PULL_MASK; PORTB->PCR[11] |= PORT_PULL_UP;}
#define IO_PIN74_PULLdown()        {PORTB->PCR[11] &= ~PORT_PULL_MASK; PORTB->PCR[11] |= PORT_PULL_DOWN;}
#define IO_PIN74_INToff()          {PORTB->PCR[11] &= ~PORT_IRQC_MASK;}
#define IO_PIN74_INTfalling()      {PORTB->PCR[11] &= ~PORT_IRQC_MASK; PORTB->PCR[11] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN74_INTrising()       {PORTB->PCR[11] &= ~PORT_IRQC_MASK; PORTB->PCR[11] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN74_INTany()          {PORTB->PCR[11] &= ~PORT_IRQC_MASK; PORTB->PCR[11] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN74_INTclear()        {PORTB->PCR[11] |= 0x01000000;}

/*___PIN 075: PTB10/FTM3_CH2/LPI2C0_SDAS______________________________________*/
#define IO_PIN75_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[10] &= ~PORT_MUX_MASK; PORTB->PCR[10] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_10;}
#define IO_PIN75_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[10] &= ~PORT_MUX_MASK; PORTB->PCR[10] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_10;}
#define IO_PIN75_toHI()            {PTB->PSOR |= PORT_PIN_10;}
#define IO_PIN75_toLO()            {PTB->PCOR |= PORT_PIN_10;}
#define IO_PIN75_TOGGLE()          {PTB->PTOR |= PORT_PIN_10;}
#define IO_PIN75_getINPUT()        {(PTB->PDIR & PORT_PIN_10) >> 10U;}
#define IO_PIN75_isHI()            {(PTB->PDIR & PORT_PIN_10) == PORT_PIN_10;}
#define IO_PIN75_isLO()            {(PTB->PDIR & PORT_PIN_10) != PORT_PIN_10;}
#define IO_PIN75_PULLoff()         {PORTB->PCR[10] &= ~PORT_PULL_MASK;}
#define IO_PIN75_PULLup()          {PORTB->PCR[10] &= ~PORT_PULL_MASK; PORTB->PCR[10] |= PORT_PULL_UP;}
#define IO_PIN75_PULLdown()        {PORTB->PCR[10] &= ~PORT_PULL_MASK; PORTB->PCR[10] |= PORT_PULL_DOWN;}
#define IO_PIN75_INToff()          {PORTB->PCR[10] &= ~PORT_IRQC_MASK;}
#define IO_PIN75_INTfalling()      {PORTB->PCR[10] &= ~PORT_IRQC_MASK; PORTB->PCR[10] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN75_INTrising()       {PORTB->PCR[10] &= ~PORT_IRQC_MASK; PORTB->PCR[10] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN75_INTany()          {PORTB->PCR[10] &= ~PORT_IRQC_MASK; PORTB->PCR[10] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN75_INTclear()        {PORTB->PCR[10] |= 0x01000000;}

/*___PIN 076: PTB9/FTM3_CH1/LPI2C0_SCLS_______________________________________*/
#define IO_PIN76_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[9] &= ~PORT_MUX_MASK; PORTB->PCR[9] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_9;}
#define IO_PIN76_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[9] &= ~PORT_MUX_MASK; PORTB->PCR[9] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_9;}
#define IO_PIN76_toHI()            {PTB->PSOR |= PORT_PIN_9;}
#define IO_PIN76_toLO()            {PTB->PCOR |= PORT_PIN_9;}
#define IO_PIN76_TOGGLE()          {PTB->PTOR |= PORT_PIN_9;}
#define IO_PIN76_getINPUT()        {(PTB->PDIR & PORT_PIN_9) >> 9U;}
#define IO_PIN76_isHI()            {(PTB->PDIR & PORT_PIN_9) == PORT_PIN_9;}
#define IO_PIN76_isLO()            {(PTB->PDIR & PORT_PIN_9) != PORT_PIN_9;}
#define IO_PIN76_PULLoff()         {PORTB->PCR[9] &= ~PORT_PULL_MASK;}
#define IO_PIN76_PULLup()          {PORTB->PCR[9] &= ~PORT_PULL_MASK; PORTB->PCR[9] |= PORT_PULL_UP;}
#define IO_PIN76_PULLdown()        {PORTB->PCR[9] &= ~PORT_PULL_MASK; PORTB->PCR[9] |= PORT_PULL_DOWN;}
#define IO_PIN76_INToff()          {PORTB->PCR[9] &= ~PORT_IRQC_MASK;}
#define IO_PIN76_INTfalling()      {PORTB->PCR[9] &= ~PORT_IRQC_MASK; PORTB->PCR[9] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN76_INTrising()       {PORTB->PCR[9] &= ~PORT_IRQC_MASK; PORTB->PCR[9] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN76_INTany()          {PORTB->PCR[9] &= ~PORT_IRQC_MASK; PORTB->PCR[9] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN76_INTclear()        {PORTB->PCR[9] |= 0x01000000;}

/*___PIN 077: PTB8/FTM3_CH0___________________________________________________*/
#define IO_PIN77_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[8] &= ~PORT_MUX_MASK; PORTB->PCR[8] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_8;}
#define IO_PIN77_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[8] &= ~PORT_MUX_MASK; PORTB->PCR[8] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_8;}
#define IO_PIN77_toHI()            {PTB->PSOR |= PORT_PIN_8;}
#define IO_PIN77_toLO()            {PTB->PCOR |= PORT_PIN_8;}
#define IO_PIN77_TOGGLE()          {PTB->PTOR |= PORT_PIN_8;}
#define IO_PIN77_getINPUT()        {(PTB->PDIR & PORT_PIN_8) >> 8U;}
#define IO_PIN77_isHI()            {(PTB->PDIR & PORT_PIN_8) == PORT_PIN_8;}
#define IO_PIN77_isLO()            {(PTB->PDIR & PORT_PIN_8) != PORT_PIN_8;}
#define IO_PIN77_PULLoff()         {PORTB->PCR[8] &= ~PORT_PULL_MASK;}
#define IO_PIN77_PULLup()          {PORTB->PCR[8] &= ~PORT_PULL_MASK; PORTB->PCR[8] |= PORT_PULL_UP;}
#define IO_PIN77_PULLdown()        {PORTB->PCR[8] &= ~PORT_PULL_MASK; PORTB->PCR[8] |= PORT_PULL_DOWN;}
#define IO_PIN77_INToff()          {PORTB->PCR[8] &= ~PORT_IRQC_MASK;}
#define IO_PIN77_INTfalling()      {PORTB->PCR[8] &= ~PORT_IRQC_MASK; PORTB->PCR[8] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN77_INTrising()       {PORTB->PCR[8] &= ~PORT_IRQC_MASK; PORTB->PCR[8] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN77_INTany()          {PORTB->PCR[8] &= ~PORT_IRQC_MASK; PORTB->PCR[8] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN77_INTclear()        {PORTB->PCR[8] |= 0x01000000;}

/*___PIN 078: PTA1/FTM1_CH1/LPI2C0_SDAS/FXIO_D3/FTM1_QD_PHA/LPUART0_RTS/TRGMUX_OUT0/ADC0_SE1/CMP0_IN1_*/
#define IO_PIN78_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[1] &= ~PORT_MUX_MASK; PORTA->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_1;}
#define IO_PIN78_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[1] &= ~PORT_MUX_MASK; PORTA->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_1;}
#define IO_PIN78_toHI()            {PTA->PSOR |= PORT_PIN_1;}
#define IO_PIN78_toLO()            {PTA->PCOR |= PORT_PIN_1;}
#define IO_PIN78_TOGGLE()          {PTA->PTOR |= PORT_PIN_1;}
#define IO_PIN78_getINPUT()        {(PTA->PDIR & PORT_PIN_1) >> 1U;}
#define IO_PIN78_isHI()            {(PTA->PDIR & PORT_PIN_1) == PORT_PIN_1;}
#define IO_PIN78_isLO()            {(PTA->PDIR & PORT_PIN_1) != PORT_PIN_1;}
#define IO_PIN78_PULLoff()         {PORTA->PCR[1] &= ~PORT_PULL_MASK;}
#define IO_PIN78_PULLup()          {PORTA->PCR[1] &= ~PORT_PULL_MASK; PORTA->PCR[1] |= PORT_PULL_UP;}
#define IO_PIN78_PULLdown()        {PORTA->PCR[1] &= ~PORT_PULL_MASK; PORTA->PCR[1] |= PORT_PULL_DOWN;}
#define IO_PIN78_INToff()          {PORTA->PCR[1] &= ~PORT_IRQC_MASK;}
#define IO_PIN78_INTfalling()      {PORTA->PCR[1] &= ~PORT_IRQC_MASK; PORTA->PCR[1] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN78_INTrising()       {PORTA->PCR[1] &= ~PORT_IRQC_MASK; PORTA->PCR[1] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN78_INTany()          {PORTA->PCR[1] &= ~PORT_IRQC_MASK; PORTA->PCR[1] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN78_INTclear()        {PORTA->PCR[1] |= 0x01000000;}

/*___PIN 079: PTA0/FTM2_CH1/LPI2C0_SCLS/FXIO_D2/FTM2_QD_PHA/LPUART0_CTS/TRGMUX_OUT3/ADC0_SE0/CMP0_IN0_*/
#define IO_PIN79_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[0] &= ~PORT_MUX_MASK; PORTA->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_0;}
#define IO_PIN79_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[0] &= ~PORT_MUX_MASK; PORTA->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_0;}
#define IO_PIN79_toHI()            {PTA->PSOR |= PORT_PIN_0;}
#define IO_PIN79_toLO()            {PTA->PCOR |= PORT_PIN_0;}
#define IO_PIN79_TOGGLE()          {PTA->PTOR |= PORT_PIN_0;}
#define IO_PIN79_getINPUT()        {(PTA->PDIR & PORT_PIN_0) >> 0U;}
#define IO_PIN79_isHI()            {(PTA->PDIR & PORT_PIN_0) == PORT_PIN_0;}
#define IO_PIN79_isLO()            {(PTA->PDIR & PORT_PIN_0) != PORT_PIN_0;}
#define IO_PIN79_PULLoff()         {PORTA->PCR[0] &= ~PORT_PULL_MASK;}
#define IO_PIN79_PULLup()          {PORTA->PCR[0] &= ~PORT_PULL_MASK; PORTA->PCR[0] |= PORT_PULL_UP;}
#define IO_PIN79_PULLdown()        {PORTA->PCR[0] &= ~PORT_PULL_MASK; PORTA->PCR[0] |= PORT_PULL_DOWN;}
#define IO_PIN79_INToff()          {PORTA->PCR[0] &= ~PORT_IRQC_MASK;}
#define IO_PIN79_INTfalling()      {PORTA->PCR[0] &= ~PORT_IRQC_MASK; PORTA->PCR[0] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN79_INTrising()       {PORTA->PCR[0] &= ~PORT_IRQC_MASK; PORTA->PCR[0] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN79_INTany()          {PORTA->PCR[0] &= ~PORT_IRQC_MASK; PORTA->PCR[0] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN79_INTclear()        {PORTA->PCR[0] |= 0x01000000;}

/*___PIN 080: PTC7/LPUART1_TX/CAN1_TX/FTM3_CH3/FTM1_QD_PHA/ADC1_SE5___________*/
#define IO_PIN80_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[7] &= ~PORT_MUX_MASK; PORTC->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_7;}
#define IO_PIN80_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[7] &= ~PORT_MUX_MASK; PORTC->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_7;}
#define IO_PIN80_toHI()            {PTC->PSOR |= PORT_PIN_7;}
#define IO_PIN80_toLO()            {PTC->PCOR |= PORT_PIN_7;}
#define IO_PIN80_TOGGLE()          {PTC->PTOR |= PORT_PIN_7;}
#define IO_PIN80_getINPUT()        {(PTC->PDIR & PORT_PIN_7) >> 7U;}
#define IO_PIN80_isHI()            {(PTC->PDIR & PORT_PIN_7) == PORT_PIN_7;}
#define IO_PIN80_isLO()            {(PTC->PDIR & PORT_PIN_7) != PORT_PIN_7;}
#define IO_PIN80_PULLoff()         {PORTC->PCR[7] &= ~PORT_PULL_MASK;}
#define IO_PIN80_PULLup()          {PORTC->PCR[7] &= ~PORT_PULL_MASK; PORTC->PCR[7] |= PORT_PULL_UP;}
#define IO_PIN80_PULLdown()        {PORTC->PCR[7] &= ~PORT_PULL_MASK; PORTC->PCR[7] |= PORT_PULL_DOWN;}
#define IO_PIN80_INToff()          {PORTC->PCR[7] &= ~PORT_IRQC_MASK;}
#define IO_PIN80_INTfalling()      {PORTC->PCR[7] &= ~PORT_IRQC_MASK; PORTC->PCR[7] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN80_INTrising()       {PORTC->PCR[7] &= ~PORT_IRQC_MASK; PORTC->PCR[7] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN80_INTany()          {PORTC->PCR[7] &= ~PORT_IRQC_MASK; PORTC->PCR[7] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN80_INTclear()        {PORTC->PCR[7] |= 0x01000000;}

/*___PIN 081: PTC6/LPUART1_RX/CAN1_RX/FTM3_CH2/FTM1_QD_PHB/ADC1_SE4___________*/
#define IO_PIN81_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[6] &= ~PORT_MUX_MASK; PORTC->PCR[6] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_6;}
#define IO_PIN81_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[6] &= ~PORT_MUX_MASK; PORTC->PCR[6] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_6;}
#define IO_PIN81_toHI()            {PTC->PSOR |= PORT_PIN_6;}
#define IO_PIN81_toLO()            {PTC->PCOR |= PORT_PIN_6;}
#define IO_PIN81_TOGGLE()          {PTC->PTOR |= PORT_PIN_6;}
#define IO_PIN81_getINPUT()        {(PTC->PDIR & PORT_PIN_6) >> 6U;}
#define IO_PIN81_isHI()            {(PTC->PDIR & PORT_PIN_6) == PORT_PIN_6;}
#define IO_PIN81_isLO()            {(PTC->PDIR & PORT_PIN_6) != PORT_PIN_6;}
#define IO_PIN81_PULLoff()         {PORTC->PCR[6] &= ~PORT_PULL_MASK;}
#define IO_PIN81_PULLup()          {PORTC->PCR[6] &= ~PORT_PULL_MASK; PORTC->PCR[6] |= PORT_PULL_UP;}
#define IO_PIN81_PULLdown()        {PORTC->PCR[6] &= ~PORT_PULL_MASK; PORTC->PCR[6] |= PORT_PULL_DOWN;}
#define IO_PIN81_INToff()          {PORTC->PCR[6] &= ~PORT_IRQC_MASK;}
#define IO_PIN81_INTfalling()      {PORTC->PCR[6] &= ~PORT_IRQC_MASK; PORTC->PCR[6] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN81_INTrising()       {PORTC->PCR[6] &= ~PORT_IRQC_MASK; PORTC->PCR[6] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN81_INTany()          {PORTC->PCR[6] &= ~PORT_IRQC_MASK; PORTC->PCR[6] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN81_INTclear()        {PORTC->PCR[6] |= 0x01000000;}

/*___PIN 082: PTA16/FTM1_CH3/LPSPI1_PCS2/ADC1_SE13____________________________*/
#define IO_PIN82_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[16] &= ~PORT_MUX_MASK; PORTA->PCR[16] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_16;}
#define IO_PIN82_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[16] &= ~PORT_MUX_MASK; PORTA->PCR[16] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_16;}
#define IO_PIN82_toHI()            {PTA->PSOR |= PORT_PIN_16;}
#define IO_PIN82_toLO()            {PTA->PCOR |= PORT_PIN_16;}
#define IO_PIN82_TOGGLE()          {PTA->PTOR |= PORT_PIN_16;}
#define IO_PIN82_getINPUT()        {(PTA->PDIR & PORT_PIN_16) >> 16U;}
#define IO_PIN82_isHI()            {(PTA->PDIR & PORT_PIN_16) == PORT_PIN_16;}
#define IO_PIN82_isLO()            {(PTA->PDIR & PORT_PIN_16) != PORT_PIN_16;}
#define IO_PIN82_PULLoff()         {PORTA->PCR[16] &= ~PORT_PULL_MASK;}
#define IO_PIN82_PULLup()          {PORTA->PCR[16] &= ~PORT_PULL_MASK; PORTA->PCR[16] |= PORT_PULL_UP;}
#define IO_PIN82_PULLdown()        {PORTA->PCR[16] &= ~PORT_PULL_MASK; PORTA->PCR[16] |= PORT_PULL_DOWN;}
#define IO_PIN82_INToff()          {PORTA->PCR[16] &= ~PORT_IRQC_MASK;}
#define IO_PIN82_INTfalling()      {PORTA->PCR[16] &= ~PORT_IRQC_MASK; PORTA->PCR[16] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN82_INTrising()       {PORTA->PCR[16] &= ~PORT_IRQC_MASK; PORTA->PCR[16] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN82_INTany()          {PORTA->PCR[16] &= ~PORT_IRQC_MASK; PORTA->PCR[16] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN82_INTclear()        {PORTA->PCR[16] |= 0x01000000;}

/*___PIN 083: PTA15/FTM1_CH2/LPSPI0_PCS3/LPSPI2_PCS3/ADC1_SE12________________*/
#define IO_PIN83_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[15] &= ~PORT_MUX_MASK; PORTA->PCR[15] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_15;}
#define IO_PIN83_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[15] &= ~PORT_MUX_MASK; PORTA->PCR[15] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_15;}
#define IO_PIN83_toHI()            {PTA->PSOR |= PORT_PIN_15;}
#define IO_PIN83_toLO()            {PTA->PCOR |= PORT_PIN_15;}
#define IO_PIN83_TOGGLE()          {PTA->PTOR |= PORT_PIN_15;}
#define IO_PIN83_getINPUT()        {(PTA->PDIR & PORT_PIN_15) >> 15U;}
#define IO_PIN83_isHI()            {(PTA->PDIR & PORT_PIN_15) == PORT_PIN_15;}
#define IO_PIN83_isLO()            {(PTA->PDIR & PORT_PIN_15) != PORT_PIN_15;}
#define IO_PIN83_PULLoff()         {PORTA->PCR[15] &= ~PORT_PULL_MASK;}
#define IO_PIN83_PULLup()          {PORTA->PCR[15] &= ~PORT_PULL_MASK; PORTA->PCR[15] |= PORT_PULL_UP;}
#define IO_PIN83_PULLdown()        {PORTA->PCR[15] &= ~PORT_PULL_MASK; PORTA->PCR[15] |= PORT_PULL_DOWN;}
#define IO_PIN83_INToff()          {PORTA->PCR[15] &= ~PORT_IRQC_MASK;}
#define IO_PIN83_INTfalling()      {PORTA->PCR[15] &= ~PORT_IRQC_MASK; PORTA->PCR[15] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN83_INTrising()       {PORTA->PCR[15] &= ~PORT_IRQC_MASK; PORTA->PCR[15] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN83_INTany()          {PORTA->PCR[15] &= ~PORT_IRQC_MASK; PORTA->PCR[15] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN83_INTclear()        {PORTA->PCR[15] |= 0x01000000;}

/*___PIN 084: PTE6/LPSPI0_PCS2/FTM3_CH7/LPUART1_RTS/ADC1_SE11_________________*/
#define IO_PIN84_toOUT()           {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[6] &= ~PORT_MUX_MASK; PORTE->PCR[6] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_6;}
#define IO_PIN84_toIN()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[6] &= ~PORT_MUX_MASK; PORTE->PCR[6] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_6;}
#define IO_PIN84_toHI()            {PTE->PSOR |= PORT_PIN_6;}
#define IO_PIN84_toLO()            {PTE->PCOR |= PORT_PIN_6;}
#define IO_PIN84_TOGGLE()          {PTE->PTOR |= PORT_PIN_6;}
#define IO_PIN84_getINPUT()        {(PTE->PDIR & PORT_PIN_6) >> 6U;}
#define IO_PIN84_isHI()            {(PTE->PDIR & PORT_PIN_6) == PORT_PIN_6;}
#define IO_PIN84_isLO()            {(PTE->PDIR & PORT_PIN_6) != PORT_PIN_6;}
#define IO_PIN84_PULLoff()         {PORTE->PCR[6] &= ~PORT_PULL_MASK;}
#define IO_PIN84_PULLup()          {PORTE->PCR[6] &= ~PORT_PULL_MASK; PORTE->PCR[6] |= PORT_PULL_UP;}
#define IO_PIN84_PULLdown()        {PORTE->PCR[6] &= ~PORT_PULL_MASK; PORTE->PCR[6] |= PORT_PULL_DOWN;}
#define IO_PIN84_INToff()          {PORTE->PCR[6] &= ~PORT_IRQC_MASK;}
#define IO_PIN84_INTfalling()      {PORTE->PCR[6] &= ~PORT_IRQC_MASK; PORTE->PCR[6] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN84_INTrising()       {PORTE->PCR[6] &= ~PORT_IRQC_MASK; PORTE->PCR[6] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN84_INTany()          {PORTE->PCR[6] &= ~PORT_IRQC_MASK; PORTE->PCR[6] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN84_INTclear()        {PORTE->PCR[6] |= 0x01000000;}

/*___PIN 085: PTE2/LPSPI0_SOUT/LPTMR0_ALT3/FTM3_CH6/LPUART1_CTS/ADC1_SE10_____*/
#define IO_PIN85_toOUT()           {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[2] &= ~PORT_MUX_MASK; PORTE->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_2;}
#define IO_PIN85_toIN()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[2] &= ~PORT_MUX_MASK; PORTE->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_2;}
#define IO_PIN85_toHI()            {PTE->PSOR |= PORT_PIN_2;}
#define IO_PIN85_toLO()            {PTE->PCOR |= PORT_PIN_2;}
#define IO_PIN85_TOGGLE()          {PTE->PTOR |= PORT_PIN_2;}
#define IO_PIN85_getINPUT()        {(PTE->PDIR & PORT_PIN_2) >> 2U;}
#define IO_PIN85_isHI()            {(PTE->PDIR & PORT_PIN_2) == PORT_PIN_2;}
#define IO_PIN85_isLO()            {(PTE->PDIR & PORT_PIN_2) != PORT_PIN_2;}
#define IO_PIN85_PULLoff()         {PORTE->PCR[2] &= ~PORT_PULL_MASK;}
#define IO_PIN85_PULLup()          {PORTE->PCR[2] &= ~PORT_PULL_MASK; PORTE->PCR[2] |= PORT_PULL_UP;}
#define IO_PIN85_PULLdown()        {PORTE->PCR[2] &= ~PORT_PULL_MASK; PORTE->PCR[2] |= PORT_PULL_DOWN;}
#define IO_PIN85_INToff()          {PORTE->PCR[2] &= ~PORT_IRQC_MASK;}
#define IO_PIN85_INTfalling()      {PORTE->PCR[2] &= ~PORT_IRQC_MASK; PORTE->PCR[2] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN85_INTrising()       {PORTE->PCR[2] &= ~PORT_IRQC_MASK; PORTE->PCR[2] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN85_INTany()          {PORTE->PCR[2] &= ~PORT_IRQC_MASK; PORTE->PCR[2] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN85_INTclear()        {PORTE->PCR[2] |= 0x01000000;}

/*___PIN 086: VSS_____________________________________________________________*/

/*___PIN 087: VDD_____________________________________________________________*/

/*___PIN 088: PTA14/FTM0_FLT0/FTM3_FLT1/EWM_IN/FTM1_FLT0______________________*/
#define IO_PIN88_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[14] &= ~PORT_MUX_MASK; PORTA->PCR[14] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_14;}
#define IO_PIN88_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[14] &= ~PORT_MUX_MASK; PORTA->PCR[14] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_14;}
#define IO_PIN88_toHI()            {PTA->PSOR |= PORT_PIN_14;}
#define IO_PIN88_toLO()            {PTA->PCOR |= PORT_PIN_14;}
#define IO_PIN88_TOGGLE()          {PTA->PTOR |= PORT_PIN_14;}
#define IO_PIN88_getINPUT()        {(PTA->PDIR & PORT_PIN_14) >> 14U;}
#define IO_PIN88_isHI()            {(PTA->PDIR & PORT_PIN_14) == PORT_PIN_14;}
#define IO_PIN88_isLO()            {(PTA->PDIR & PORT_PIN_14) != PORT_PIN_14;}
#define IO_PIN88_PULLoff()         {PORTA->PCR[14] &= ~PORT_PULL_MASK;}
#define IO_PIN88_PULLup()          {PORTA->PCR[14] &= ~PORT_PULL_MASK; PORTA->PCR[14] |= PORT_PULL_UP;}
#define IO_PIN88_PULLdown()        {PORTA->PCR[14] &= ~PORT_PULL_MASK; PORTA->PCR[14] |= PORT_PULL_DOWN;}
#define IO_PIN88_INToff()          {PORTA->PCR[14] &= ~PORT_IRQC_MASK;}
#define IO_PIN88_INTfalling()      {PORTA->PCR[14] &= ~PORT_IRQC_MASK; PORTA->PCR[14] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN88_INTrising()       {PORTA->PCR[14] &= ~PORT_IRQC_MASK; PORTA->PCR[14] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN88_INTany()          {PORTA->PCR[14] &= ~PORT_IRQC_MASK; PORTA->PCR[14] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN88_INTclear()        {PORTA->PCR[14] |= 0x01000000;}

/*___PIN 089: PTA13/FTM1_CH7/CAN1_TX/FTM2_QD_PHA______________________________*/
#define IO_PIN89_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[13] &= ~PORT_MUX_MASK; PORTA->PCR[13] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_13;}
#define IO_PIN89_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[13] &= ~PORT_MUX_MASK; PORTA->PCR[13] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_13;}
#define IO_PIN89_toHI()            {PTA->PSOR |= PORT_PIN_13;}
#define IO_PIN89_toLO()            {PTA->PCOR |= PORT_PIN_13;}
#define IO_PIN89_TOGGLE()          {PTA->PTOR |= PORT_PIN_13;}
#define IO_PIN89_getINPUT()        {(PTA->PDIR & PORT_PIN_13) >> 13U;}
#define IO_PIN89_isHI()            {(PTA->PDIR & PORT_PIN_13) == PORT_PIN_13;}
#define IO_PIN89_isLO()            {(PTA->PDIR & PORT_PIN_13) != PORT_PIN_13;}
#define IO_PIN89_PULLoff()         {PORTA->PCR[13] &= ~PORT_PULL_MASK;}
#define IO_PIN89_PULLup()          {PORTA->PCR[13] &= ~PORT_PULL_MASK; PORTA->PCR[13] |= PORT_PULL_UP;}
#define IO_PIN89_PULLdown()        {PORTA->PCR[13] &= ~PORT_PULL_MASK; PORTA->PCR[13] |= PORT_PULL_DOWN;}
#define IO_PIN89_INToff()          {PORTA->PCR[13] &= ~PORT_IRQC_MASK;}
#define IO_PIN89_INTfalling()      {PORTA->PCR[13] &= ~PORT_IRQC_MASK; PORTA->PCR[13] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN89_INTrising()       {PORTA->PCR[13] &= ~PORT_IRQC_MASK; PORTA->PCR[13] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN89_INTany()          {PORTA->PCR[13] &= ~PORT_IRQC_MASK; PORTA->PCR[13] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN89_INTclear()        {PORTA->PCR[13] |= 0x01000000;}

/*___PIN 090: PTA12/FTM1_CH6/CAN1_RX/FTM2_QD_PHB______________________________*/
#define IO_PIN90_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[12] &= ~PORT_MUX_MASK; PORTA->PCR[12] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_12;}
#define IO_PIN90_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[12] &= ~PORT_MUX_MASK; PORTA->PCR[12] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_12;}
#define IO_PIN90_toHI()            {PTA->PSOR |= PORT_PIN_12;}
#define IO_PIN90_toLO()            {PTA->PCOR |= PORT_PIN_12;}
#define IO_PIN90_TOGGLE()          {PTA->PTOR |= PORT_PIN_12;}
#define IO_PIN90_getINPUT()        {(PTA->PDIR & PORT_PIN_12) >> 12U;}
#define IO_PIN90_isHI()            {(PTA->PDIR & PORT_PIN_12) == PORT_PIN_12;}
#define IO_PIN90_isLO()            {(PTA->PDIR & PORT_PIN_12) != PORT_PIN_12;}
#define IO_PIN90_PULLoff()         {PORTA->PCR[12] &= ~PORT_PULL_MASK;}
#define IO_PIN90_PULLup()          {PORTA->PCR[12] &= ~PORT_PULL_MASK; PORTA->PCR[12] |= PORT_PULL_UP;}
#define IO_PIN90_PULLdown()        {PORTA->PCR[12] &= ~PORT_PULL_MASK; PORTA->PCR[12] |= PORT_PULL_DOWN;}
#define IO_PIN90_INToff()          {PORTA->PCR[12] &= ~PORT_IRQC_MASK;}
#define IO_PIN90_INTfalling()      {PORTA->PCR[12] &= ~PORT_IRQC_MASK; PORTA->PCR[12] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN90_INTrising()       {PORTA->PCR[12] &= ~PORT_IRQC_MASK; PORTA->PCR[12] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN90_INTany()          {PORTA->PCR[12] &= ~PORT_IRQC_MASK; PORTA->PCR[12] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN90_INTclear()        {PORTA->PCR[12] |= 0x01000000;}

/*___PIN 091: PTA11/FTM1_CH5/FXIO_D1/CMP0_RRT_________________________________*/
#define IO_PIN91_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[11] &= ~PORT_MUX_MASK; PORTA->PCR[11] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_11;}
#define IO_PIN91_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[11] &= ~PORT_MUX_MASK; PORTA->PCR[11] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_11;}
#define IO_PIN91_toHI()            {PTA->PSOR |= PORT_PIN_11;}
#define IO_PIN91_toLO()            {PTA->PCOR |= PORT_PIN_11;}
#define IO_PIN91_TOGGLE()          {PTA->PTOR |= PORT_PIN_11;}
#define IO_PIN91_getINPUT()        {(PTA->PDIR & PORT_PIN_11) >> 11U;}
#define IO_PIN91_isHI()            {(PTA->PDIR & PORT_PIN_11) == PORT_PIN_11;}
#define IO_PIN91_isLO()            {(PTA->PDIR & PORT_PIN_11) != PORT_PIN_11;}
#define IO_PIN91_PULLoff()         {PORTA->PCR[11] &= ~PORT_PULL_MASK;}
#define IO_PIN91_PULLup()          {PORTA->PCR[11] &= ~PORT_PULL_MASK; PORTA->PCR[11] |= PORT_PULL_UP;}
#define IO_PIN91_PULLdown()        {PORTA->PCR[11] &= ~PORT_PULL_MASK; PORTA->PCR[11] |= PORT_PULL_DOWN;}
#define IO_PIN91_INToff()          {PORTA->PCR[11] &= ~PORT_IRQC_MASK;}
#define IO_PIN91_INTfalling()      {PORTA->PCR[11] &= ~PORT_IRQC_MASK; PORTA->PCR[11] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN91_INTrising()       {PORTA->PCR[11] &= ~PORT_IRQC_MASK; PORTA->PCR[11] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN91_INTany()          {PORTA->PCR[11] &= ~PORT_IRQC_MASK; PORTA->PCR[11] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN91_INTclear()        {PORTA->PCR[11] |= 0x01000000;}

/*___PIN 092: PTA10/FTM1_CH4/FXIO_D0/JTAG_TDO/noetm_TRACE_SWO_________________*/
#define IO_PIN92_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[10] &= ~PORT_MUX_MASK; PORTA->PCR[10] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_10;}
#define IO_PIN92_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[10] &= ~PORT_MUX_MASK; PORTA->PCR[10] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_10;}
#define IO_PIN92_toHI()            {PTA->PSOR |= PORT_PIN_10;}
#define IO_PIN92_toLO()            {PTA->PCOR |= PORT_PIN_10;}
#define IO_PIN92_TOGGLE()          {PTA->PTOR |= PORT_PIN_10;}
#define IO_PIN92_getINPUT()        {(PTA->PDIR & PORT_PIN_10) >> 10U;}
#define IO_PIN92_isHI()            {(PTA->PDIR & PORT_PIN_10) == PORT_PIN_10;}
#define IO_PIN92_isLO()            {(PTA->PDIR & PORT_PIN_10) != PORT_PIN_10;}
#define IO_PIN92_PULLoff()         {PORTA->PCR[10] &= ~PORT_PULL_MASK;}
#define IO_PIN92_PULLup()          {PORTA->PCR[10] &= ~PORT_PULL_MASK; PORTA->PCR[10] |= PORT_PULL_UP;}
#define IO_PIN92_PULLdown()        {PORTA->PCR[10] &= ~PORT_PULL_MASK; PORTA->PCR[10] |= PORT_PULL_DOWN;}
#define IO_PIN92_INToff()          {PORTA->PCR[10] &= ~PORT_IRQC_MASK;}
#define IO_PIN92_INTfalling()      {PORTA->PCR[10] &= ~PORT_IRQC_MASK; PORTA->PCR[10] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN92_INTrising()       {PORTA->PCR[10] &= ~PORT_IRQC_MASK; PORTA->PCR[10] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN92_INTany()          {PORTA->PCR[10] &= ~PORT_IRQC_MASK; PORTA->PCR[10] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN92_INTclear()        {PORTA->PCR[10] |= 0x01000000;}

/*___PIN 093: PTE1/LPSPI0_SIN/LPI2C0_HREQ/LPSPI1_PCS0/FTM1_FLT1_______________*/
#define IO_PIN93_toOUT()           {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[1] &= ~PORT_MUX_MASK; PORTE->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_1;}
#define IO_PIN93_toIN()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[1] &= ~PORT_MUX_MASK; PORTE->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_1;}
#define IO_PIN93_toHI()            {PTE->PSOR |= PORT_PIN_1;}
#define IO_PIN93_toLO()            {PTE->PCOR |= PORT_PIN_1;}
#define IO_PIN93_TOGGLE()          {PTE->PTOR |= PORT_PIN_1;}
#define IO_PIN93_getINPUT()        {(PTE->PDIR & PORT_PIN_1) >> 1U;}
#define IO_PIN93_isHI()            {(PTE->PDIR & PORT_PIN_1) == PORT_PIN_1;}
#define IO_PIN93_isLO()            {(PTE->PDIR & PORT_PIN_1) != PORT_PIN_1;}
#define IO_PIN93_PULLoff()         {PORTE->PCR[1] &= ~PORT_PULL_MASK;}
#define IO_PIN93_PULLup()          {PORTE->PCR[1] &= ~PORT_PULL_MASK; PORTE->PCR[1] |= PORT_PULL_UP;}
#define IO_PIN93_PULLdown()        {PORTE->PCR[1] &= ~PORT_PULL_MASK; PORTE->PCR[1] |= PORT_PULL_DOWN;}
#define IO_PIN93_INToff()          {PORTE->PCR[1] &= ~PORT_IRQC_MASK;}
#define IO_PIN93_INTfalling()      {PORTE->PCR[1] &= ~PORT_IRQC_MASK; PORTE->PCR[1] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN93_INTrising()       {PORTE->PCR[1] &= ~PORT_IRQC_MASK; PORTE->PCR[1] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN93_INTany()          {PORTE->PCR[1] &= ~PORT_IRQC_MASK; PORTE->PCR[1] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN93_INTclear()        {PORTE->PCR[1] |= 0x01000000;}

/*___PIN 094: PTE0/LPSPI0_SCK/TCLK1/LPSPI1_SOUT/FTM1_FLT2_____________________*/
#define IO_PIN94_toOUT()           {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[0] &= ~PORT_MUX_MASK; PORTE->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_0;}
#define IO_PIN94_toIN()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[0] &= ~PORT_MUX_MASK; PORTE->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_0;}
#define IO_PIN94_toHI()            {PTE->PSOR |= PORT_PIN_0;}
#define IO_PIN94_toLO()            {PTE->PCOR |= PORT_PIN_0;}
#define IO_PIN94_TOGGLE()          {PTE->PTOR |= PORT_PIN_0;}
#define IO_PIN94_getINPUT()        {(PTE->PDIR & PORT_PIN_0) >> 0U;}
#define IO_PIN94_isHI()            {(PTE->PDIR & PORT_PIN_0) == PORT_PIN_0;}
#define IO_PIN94_isLO()            {(PTE->PDIR & PORT_PIN_0) != PORT_PIN_0;}
#define IO_PIN94_PULLoff()         {PORTE->PCR[0] &= ~PORT_PULL_MASK;}
#define IO_PIN94_PULLup()          {PORTE->PCR[0] &= ~PORT_PULL_MASK; PORTE->PCR[0] |= PORT_PULL_UP;}
#define IO_PIN94_PULLdown()        {PORTE->PCR[0] &= ~PORT_PULL_MASK; PORTE->PCR[0] |= PORT_PULL_DOWN;}
#define IO_PIN94_INToff()          {PORTE->PCR[0] &= ~PORT_IRQC_MASK;}
#define IO_PIN94_INTfalling()      {PORTE->PCR[0] &= ~PORT_IRQC_MASK; PORTE->PCR[0] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN94_INTrising()       {PORTE->PCR[0] &= ~PORT_IRQC_MASK; PORTE->PCR[0] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN94_INTany()          {PORTE->PCR[0] &= ~PORT_IRQC_MASK; PORTE->PCR[0] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN94_INTclear()        {PORTE->PCR[0] |= 0x01000000;}

/*___PIN 095: PTC5/FTM2_CH0/RTC_CLKOUT/FTM2_QD_PHB/JTAG_TDI___________________*/
#define IO_PIN95_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[5] &= ~PORT_MUX_MASK; PORTC->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_5;}
#define IO_PIN95_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[5] &= ~PORT_MUX_MASK; PORTC->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_5;}
#define IO_PIN95_toHI()            {PTC->PSOR |= PORT_PIN_5;}
#define IO_PIN95_toLO()            {PTC->PCOR |= PORT_PIN_5;}
#define IO_PIN95_TOGGLE()          {PTC->PTOR |= PORT_PIN_5;}
#define IO_PIN95_getINPUT()        {(PTC->PDIR & PORT_PIN_5) >> 5U;}
#define IO_PIN95_isHI()            {(PTC->PDIR & PORT_PIN_5) == PORT_PIN_5;}
#define IO_PIN95_isLO()            {(PTC->PDIR & PORT_PIN_5) != PORT_PIN_5;}
#define IO_PIN95_PULLoff()         {PORTC->PCR[5] &= ~PORT_PULL_MASK;}
#define IO_PIN95_PULLup()          {PORTC->PCR[5] &= ~PORT_PULL_MASK; PORTC->PCR[5] |= PORT_PULL_UP;}
#define IO_PIN95_PULLdown()        {PORTC->PCR[5] &= ~PORT_PULL_MASK; PORTC->PCR[5] |= PORT_PULL_DOWN;}
#define IO_PIN95_INToff()          {PORTC->PCR[5] &= ~PORT_IRQC_MASK;}
#define IO_PIN95_INTfalling()      {PORTC->PCR[5] &= ~PORT_IRQC_MASK; PORTC->PCR[5] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN95_INTrising()       {PORTC->PCR[5] &= ~PORT_IRQC_MASK; PORTC->PCR[5] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN95_INTany()          {PORTC->PCR[5] &= ~PORT_IRQC_MASK; PORTC->PCR[5] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN95_INTclear()        {PORTC->PCR[5] |= 0x01000000;}

/*___PIN 096: PTC4/FTM1_CH0/RTC_CLKOUT/EWM_IN/FTM1_QD_PHB/JTAG_TCLK/SWD_CLK/CMP0_IN2_*/
#define IO_PIN96_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[4] &= ~PORT_MUX_MASK; PORTC->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_4;}
#define IO_PIN96_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[4] &= ~PORT_MUX_MASK; PORTC->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_4;}
#define IO_PIN96_toHI()            {PTC->PSOR |= PORT_PIN_4;}
#define IO_PIN96_toLO()            {PTC->PCOR |= PORT_PIN_4;}
#define IO_PIN96_TOGGLE()          {PTC->PTOR |= PORT_PIN_4;}
#define IO_PIN96_getINPUT()        {(PTC->PDIR & PORT_PIN_4) >> 4U;}
#define IO_PIN96_isHI()            {(PTC->PDIR & PORT_PIN_4) == PORT_PIN_4;}
#define IO_PIN96_isLO()            {(PTC->PDIR & PORT_PIN_4) != PORT_PIN_4;}
#define IO_PIN96_PULLoff()         {PORTC->PCR[4] &= ~PORT_PULL_MASK;}
#define IO_PIN96_PULLup()          {PORTC->PCR[4] &= ~PORT_PULL_MASK; PORTC->PCR[4] |= PORT_PULL_UP;}
#define IO_PIN96_PULLdown()        {PORTC->PCR[4] &= ~PORT_PULL_MASK; PORTC->PCR[4] |= PORT_PULL_DOWN;}
#define IO_PIN96_INToff()          {PORTC->PCR[4] &= ~PORT_IRQC_MASK;}
#define IO_PIN96_INTfalling()      {PORTC->PCR[4] &= ~PORT_IRQC_MASK; PORTC->PCR[4] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN96_INTrising()       {PORTC->PCR[4] &= ~PORT_IRQC_MASK; PORTC->PCR[4] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN96_INTany()          {PORTC->PCR[4] &= ~PORT_IRQC_MASK; PORTC->PCR[4] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN96_INTclear()        {PORTC->PCR[4] |= 0x01000000;}

/*___PIN 097: PTA5/TCLK1/RESET_b______________________________________________*/
#define IO_PIN97_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[5] &= ~PORT_MUX_MASK; PORTA->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_5;}
#define IO_PIN97_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[5] &= ~PORT_MUX_MASK; PORTA->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_5;}
#define IO_PIN97_toHI()            {PTA->PSOR |= PORT_PIN_5;}
#define IO_PIN97_toLO()            {PTA->PCOR |= PORT_PIN_5;}
#define IO_PIN97_TOGGLE()          {PTA->PTOR |= PORT_PIN_5;}
#define IO_PIN97_getINPUT()        {(PTA->PDIR & PORT_PIN_5) >> 5U;}
#define IO_PIN97_isHI()            {(PTA->PDIR & PORT_PIN_5) == PORT_PIN_5;}
#define IO_PIN97_isLO()            {(PTA->PDIR & PORT_PIN_5) != PORT_PIN_5;}
#define IO_PIN97_PULLoff()         {PORTA->PCR[5] &= ~PORT_PULL_MASK;}
#define IO_PIN97_PULLup()          {PORTA->PCR[5] &= ~PORT_PULL_MASK; PORTA->PCR[5] |= PORT_PULL_UP;}
#define IO_PIN97_PULLdown()        {PORTA->PCR[5] &= ~PORT_PULL_MASK; PORTA->PCR[5] |= PORT_PULL_DOWN;}
#define IO_PIN97_INToff()          {PORTA->PCR[5] &= ~PORT_IRQC_MASK;}
#define IO_PIN97_INTfalling()      {PORTA->PCR[5] &= ~PORT_IRQC_MASK; PORTA->PCR[5] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN97_INTrising()       {PORTA->PCR[5] &= ~PORT_IRQC_MASK; PORTA->PCR[5] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN97_INTany()          {PORTA->PCR[5] &= ~PORT_IRQC_MASK; PORTA->PCR[5] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN97_INTclear()        {PORTA->PCR[5] |= 0x01000000;}

/*___PIN 098: PTA4/CMP0_OUT/EWM_OUT_b/JTAG_TMS/SWD_DIO________________________*/
#define IO_PIN98_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[4] &= ~PORT_MUX_MASK; PORTA->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_4;}
#define IO_PIN98_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[4] &= ~PORT_MUX_MASK; PORTA->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_4;}
#define IO_PIN98_toHI()            {PTA->PSOR |= PORT_PIN_4;}
#define IO_PIN98_toLO()            {PTA->PCOR |= PORT_PIN_4;}
#define IO_PIN98_TOGGLE()          {PTA->PTOR |= PORT_PIN_4;}
#define IO_PIN98_getINPUT()        {(PTA->PDIR & PORT_PIN_4) >> 4U;}
#define IO_PIN98_isHI()            {(PTA->PDIR & PORT_PIN_4) == PORT_PIN_4;}
#define IO_PIN98_isLO()            {(PTA->PDIR & PORT_PIN_4) != PORT_PIN_4;}
#define IO_PIN98_PULLoff()         {PORTA->PCR[4] &= ~PORT_PULL_MASK;}
#define IO_PIN98_PULLup()          {PORTA->PCR[4] &= ~PORT_PULL_MASK; PORTA->PCR[4] |= PORT_PULL_UP;}
#define IO_PIN98_PULLdown()        {PORTA->PCR[4] &= ~PORT_PULL_MASK; PORTA->PCR[4] |= PORT_PULL_DOWN;}
#define IO_PIN98_INToff()          {PORTA->PCR[4] &= ~PORT_IRQC_MASK;}
#define IO_PIN98_INTfalling()      {PORTA->PCR[4] &= ~PORT_IRQC_MASK; PORTA->PCR[4] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN98_INTrising()       {PORTA->PCR[4] &= ~PORT_IRQC_MASK; PORTA->PCR[4] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN98_INTany()          {PORTA->PCR[4] &= ~PORT_IRQC_MASK; PORTA->PCR[4] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN98_INTclear()        {PORTA->PCR[4] |= 0x01000000;}

/*___PIN 099: PTA9/LPUART2_TX/LPSPI2_PCS0/FXIO_D7/FTM3_FLT2/FTM1_FLT3_________*/
#define IO_PIN99_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[9] &= ~PORT_MUX_MASK; PORTA->PCR[9] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_9;}
#define IO_PIN99_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[9] &= ~PORT_MUX_MASK; PORTA->PCR[9] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_9;}
#define IO_PIN99_toHI()            {PTA->PSOR |= PORT_PIN_9;}
#define IO_PIN99_toLO()            {PTA->PCOR |= PORT_PIN_9;}
#define IO_PIN99_TOGGLE()          {PTA->PTOR |= PORT_PIN_9;}
#define IO_PIN99_getINPUT()        {(PTA->PDIR & PORT_PIN_9) >> 9U;}
#define IO_PIN99_isHI()            {(PTA->PDIR & PORT_PIN_9) == PORT_PIN_9;}
#define IO_PIN99_isLO()            {(PTA->PDIR & PORT_PIN_9) != PORT_PIN_9;}
#define IO_PIN99_PULLoff()         {PORTA->PCR[9] &= ~PORT_PULL_MASK;}
#define IO_PIN99_PULLup()          {PORTA->PCR[9] &= ~PORT_PULL_MASK; PORTA->PCR[9] |= PORT_PULL_UP;}
#define IO_PIN99_PULLdown()        {PORTA->PCR[9] &= ~PORT_PULL_MASK; PORTA->PCR[9] |= PORT_PULL_DOWN;}
#define IO_PIN99_INToff()          {PORTA->PCR[9] &= ~PORT_IRQC_MASK;}
#define IO_PIN99_INTfalling()      {PORTA->PCR[9] &= ~PORT_IRQC_MASK; PORTA->PCR[9] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN99_INTrising()       {PORTA->PCR[9] &= ~PORT_IRQC_MASK; PORTA->PCR[9] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN99_INTany()          {PORTA->PCR[9] &= ~PORT_IRQC_MASK; PORTA->PCR[9] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN99_INTclear()        {PORTA->PCR[9] |= 0x01000000;}

/*___PIN 100: PTA8/LPUART2_RX/LPSPI2_SOUT/FXIO_D6/FTM3_FLT3___________________*/
#define IO_PIN100_toOUT()          {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[8] &= ~PORT_MUX_MASK; PORTA->PCR[8] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_8;}
#define IO_PIN100_toIN()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[8] &= ~PORT_MUX_MASK; PORTA->PCR[8] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_8;}
#define IO_PIN100_toHI()           {PTA->PSOR |= PORT_PIN_8;}
#define IO_PIN100_toLO()           {PTA->PCOR |= PORT_PIN_8;}
#define IO_PIN100_TOGGLE()         {PTA->PTOR |= PORT_PIN_8;}
#define IO_PIN100_getINPUT()       {(PTA->PDIR & PORT_PIN_8) >> 8U;}
#define IO_PIN100_isHI()           {(PTA->PDIR & PORT_PIN_8) == PORT_PIN_8;}
#define IO_PIN100_isLO()           {(PTA->PDIR & PORT_PIN_8) != PORT_PIN_8;}
#define IO_PIN100_PULLoff()        {PORTA->PCR[8] &= ~PORT_PULL_MASK;}
#define IO_PIN100_PULLup()         {PORTA->PCR[8] &= ~PORT_PULL_MASK; PORTA->PCR[8] |= PORT_PULL_UP;}
#define IO_PIN100_PULLdown()       {PORTA->PCR[8] &= ~PORT_PULL_MASK; PORTA->PCR[8] |= PORT_PULL_DOWN;}
#define IO_PIN100_INToff()         {PORTA->PCR[8] &= ~PORT_IRQC_MASK;}
#define IO_PIN100_INTfalling()     {PORTA->PCR[8] &= ~PORT_IRQC_MASK; PORTA->PCR[8] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN100_INTrising()      {PORTA->PCR[8] &= ~PORT_IRQC_MASK; PORTA->PCR[8] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN100_INTany()         {PORTA->PCR[8] &= ~PORT_IRQC_MASK; PORTA->PCR[8] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN100_INTclear()       {PORTA->PCR[8] |= 0x01000000;}


/* === EXPORTED VARIABLES =================================================== */
/* none */
/* === EXPORTED FUNCTIONS =================================================== */
extern void IO_vInit(void);
extern void IO_vMain(void);


#endif /* __IO_H */


/* === HISTORY ============================================================== */
/* $Log:   $
 * 
*/
