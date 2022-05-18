/*
 *    JANI HOVAN, COPYRIGHT (c) 2021
 *    ALL RIGHTS RESERVED
 */

/**
* \file IO_S32K144_48pin_LQFP.h
* \ingroup grpXXX
* \brief Pin definitions.
* \version 1.0.0
* \author Jani Hovan
* \date 2021-07-20
*/

#ifndef __IO_H
#define __IO_H

/* === INCLUDES ============================================================= */
#include "board.h"

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
#define PORT_MUX_PIN_ALT3         0x00000300
#define PORT_MUX_PIN_ALT4         0x00000400
#define PORT_MUX_PIN_ALT5         0x00000500
#define PORT_MUX_PIN_ALT6         0x00000600
#define PORT_MUX_PIN_ALT7         0x00000700

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

/*___PIN 001: PTD1/FTM0_CH3/LPSPI1_SIN/FTM2_CH1/FXIO_D1/TRGMUX_OUT2___________*/
#define IO_PIN1_toOUT()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[1] &= ~PORT_MUX_MASK; PORTD->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_1;}
#define IO_PIN1_toIN()             {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[1] &= ~PORT_MUX_MASK; PORTD->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_1;}
#define IO_PIN1_toHI()             {PTD->PSOR |= PORT_PIN_1;}
#define IO_PIN1_toLO()             {PTD->PCOR |= PORT_PIN_1;}
#define IO_PIN1_TOGGLE()           {PTD->PTOR |= PORT_PIN_1;}
#define IO_PIN1_getINPUT()         {(PTD->PDIR & PORT_PIN_1) >> 1;}
#define IO_PIN1_isHI()             ((PTD->PDIR & PORT_PIN_1) == PORT_PIN_1)
#define IO_PIN1_isLO()             ((PTD->PDIR & PORT_PIN_1) != PORT_PIN_1)
#define IO_PIN1_PULLoff()          {PORTD->PCR[1] &= ~PORT_PULL_MASK;}
#define IO_PIN1_PULLup()           {PORTD->PCR[1] &= ~PORT_PULL_MASK; PORTD->PCR[1] |= PORT_PULL_UP;}
#define IO_PIN1_PULLdown()         {PORTD->PCR[1] &= ~PORT_PULL_MASK; PORTD->PCR[1] |= PORT_PULL_DOWN;}
#define IO_PIN1_INToff()           {PORTD->PCR[1] &= ~PORT_IRQC_MASK;}
#define IO_PIN1_INTfalling()       {PORTD->PCR[1] &= ~PORT_IRQC_MASK; PORTD->PCR[1] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN1_INTrising()        {PORTD->PCR[1] &= ~PORT_IRQC_MASK; PORTD->PCR[1] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN1_INTany()           {PORTD->PCR[1] &= ~PORT_IRQC_MASK; PORTD->PCR[1] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN1_INTclear()         {PORTD->PCR[1] |= 0x01000000;}

/*___PIN 002: PTD0/FTM0_CH2/LPSPI1_SCK/FTM2_CH0/FXIO_D0/TRGMUX_OUT1___________*/
#define IO_PIN2_toOUT()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[0] &= ~PORT_MUX_MASK; PORTD->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_0;}
#define IO_PIN2_toIN()             {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[0] &= ~PORT_MUX_MASK; PORTD->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_0;}
#define IO_PIN2_toHI()             {PTD->PSOR |= PORT_PIN_0;}
#define IO_PIN2_toLO()             {PTD->PCOR |= PORT_PIN_0;}
#define IO_PIN2_TOGGLE()           {PTD->PTOR |= PORT_PIN_0;}
#define IO_PIN2_getINPUT()         {(PTD->PDIR & PORT_PIN_0) >> 0;}
#define IO_PIN2_isHI()             ((PTD->PDIR & PORT_PIN_0) == PORT_PIN_0)
#define IO_PIN2_isLO()             ((PTD->PDIR & PORT_PIN_0) != PORT_PIN_0)
#define IO_PIN2_PULLoff()          {PORTD->PCR[0] &= ~PORT_PULL_MASK;}
#define IO_PIN2_PULLup()           {PORTD->PCR[0] &= ~PORT_PULL_MASK; PORTD->PCR[0] |= PORT_PULL_UP;}
#define IO_PIN2_PULLdown()         {PORTD->PCR[0] &= ~PORT_PULL_MASK; PORTD->PCR[0] |= PORT_PULL_DOWN;}
#define IO_PIN2_INToff()           {PORTD->PCR[0] &= ~PORT_IRQC_MASK;}
#define IO_PIN2_INTfalling()       {PORTD->PCR[0] &= ~PORT_IRQC_MASK; PORTD->PCR[0] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN2_INTrising()        {PORTD->PCR[0] &= ~PORT_IRQC_MASK; PORTD->PCR[0] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN2_INTany()           {PORTD->PCR[0] &= ~PORT_IRQC_MASK; PORTD->PCR[0] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN2_INTclear()         {PORTD->PCR[0] |= 0x01000000;}

/*___PIN 003: PTE5/TCLK2/FTM2_QD_PHA/FTM2_CH3/CAN0_TX/FXIO_D7/EWM_IN__________*/
#define IO_PIN3_toOUT()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[5] &= ~PORT_MUX_MASK; PORTE->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_5;}
#define IO_PIN3_toIN()             {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[5] &= ~PORT_MUX_MASK; PORTE->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_5;}
#define IO_PIN3_toHI()             {PTE->PSOR |= PORT_PIN_5;}
#define IO_PIN3_toLO()             {PTE->PCOR |= PORT_PIN_5;}
#define IO_PIN3_TOGGLE()           {PTE->PTOR |= PORT_PIN_5;}
#define IO_PIN3_getINPUT()         {(PTE->PDIR & PORT_PIN_5) >> 5;}
#define IO_PIN3_isHI()             ((PTE->PDIR & PORT_PIN_5) == PORT_PIN_5)
#define IO_PIN3_isLO()             ((PTE->PDIR & PORT_PIN_5) != PORT_PIN_5)
#define IO_PIN3_PULLoff()          {PORTE->PCR[5] &= ~PORT_PULL_MASK;}
#define IO_PIN3_PULLup()           {PORTE->PCR[5] &= ~PORT_PULL_MASK; PORTE->PCR[5] |= PORT_PULL_UP;}
#define IO_PIN3_PULLdown()         {PORTE->PCR[5] &= ~PORT_PULL_MASK; PORTE->PCR[5] |= PORT_PULL_DOWN;}
#define IO_PIN3_INToff()           {PORTE->PCR[5] &= ~PORT_IRQC_MASK;}
#define IO_PIN3_INTfalling()       {PORTE->PCR[5] &= ~PORT_IRQC_MASK; PORTE->PCR[5] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN3_INTrising()        {PORTE->PCR[5] &= ~PORT_IRQC_MASK; PORTE->PCR[5] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN3_INTany()           {PORTE->PCR[5] &= ~PORT_IRQC_MASK; PORTE->PCR[5] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN3_INTclear()         {PORTE->PCR[5] |= 0x01000000;}

/*___PIN 004: PTE4/FTM2_QD_PHB/FTM2_CH2/CAN0_RX/FXIO_D6/EWM_OUT_b_____________*/
#define IO_PIN4_toOUT()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[4] &= ~PORT_MUX_MASK; PORTE->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_4;}
#define IO_PIN4_toIN()             {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[4] &= ~PORT_MUX_MASK; PORTE->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_4;}
#define IO_PIN4_toHI()             {PTE->PSOR |= PORT_PIN_4;}
#define IO_PIN4_toLO()             {PTE->PCOR |= PORT_PIN_4;}
#define IO_PIN4_TOGGLE()           {PTE->PTOR |= PORT_PIN_4;}
#define IO_PIN4_getINPUT()         {(PTE->PDIR & PORT_PIN_4) >> 4;}
#define IO_PIN4_isHI()             ((PTE->PDIR & PORT_PIN_4) == PORT_PIN_4)
#define IO_PIN4_isLO()             ((PTE->PDIR & PORT_PIN_4) != PORT_PIN_4)
#define IO_PIN4_PULLoff()          {PORTE->PCR[4] &= ~PORT_PULL_MASK;}
#define IO_PIN4_PULLup()           {PORTE->PCR[4] &= ~PORT_PULL_MASK; PORTE->PCR[4] |= PORT_PULL_UP;}
#define IO_PIN4_PULLdown()         {PORTE->PCR[4] &= ~PORT_PULL_MASK; PORTE->PCR[4] |= PORT_PULL_DOWN;}
#define IO_PIN4_INToff()           {PORTE->PCR[4] &= ~PORT_IRQC_MASK;}
#define IO_PIN4_INTfalling()       {PORTE->PCR[4] &= ~PORT_IRQC_MASK; PORTE->PCR[4] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN4_INTrising()        {PORTE->PCR[4] &= ~PORT_IRQC_MASK; PORTE->PCR[4] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN4_INTany()           {PORTE->PCR[4] &= ~PORT_IRQC_MASK; PORTE->PCR[4] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN4_INTclear()         {PORTE->PCR[4] |= 0x01000000;}

/*___PIN 005: VDD_____________________________________________________________*/

/*___PIN 006: VDDA____________________________________________________________*/

/*___PIN 007: VSS_____________________________________________________________*/

/*___PIN 008: PTB7/LPI2C0_SCL/EXTAL___________________________________________*/
#define IO_PIN8_toOUT()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[7] &= ~PORT_MUX_MASK; PORTB->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_7;}
#define IO_PIN8_toIN()             {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[7] &= ~PORT_MUX_MASK; PORTB->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_7;}
#define IO_PIN8_toHI()             {PTB->PSOR |= PORT_PIN_7;}
#define IO_PIN8_toLO()             {PTB->PCOR |= PORT_PIN_7;}
#define IO_PIN8_TOGGLE()           {PTB->PTOR |= PORT_PIN_7;}
#define IO_PIN8_getINPUT()         {(PTB->PDIR & PORT_PIN_7) >> 7U;}
#define IO_PIN8_isHI()             ((PTB->PDIR & PORT_PIN_7) == PORT_PIN_7)
#define IO_PIN8_isLO()             ((PTB->PDIR & PORT_PIN_7) != PORT_PIN_7)
#define IO_PIN8_PULLoff()          {PORTB->PCR[7] &= ~PORT_PULL_MASK;}
#define IO_PIN8_PULLup()           {PORTB->PCR[7] &= ~PORT_PULL_MASK; PORTB->PCR[7] |= PORT_PULL_UP;}
#define IO_PIN8_PULLdown()         {PORTB->PCR[7] &= ~PORT_PULL_MASK; PORTB->PCR[7] |= PORT_PULL_DOWN;}
#define IO_PIN8_INToff()           {PORTB->PCR[7] &= ~PORT_IRQC_MASK;}
#define IO_PIN8_INTfalling()       {PORTB->PCR[7] &= ~PORT_IRQC_MASK; PORTB->PCR[7] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN8_INTrising()        {PORTB->PCR[7] &= ~PORT_IRQC_MASK; PORTB->PCR[7] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN8_INTany()           {PORTB->PCR[7] &= ~PORT_IRQC_MASK; PORTB->PCR[7] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN8_INTclear()         {PORTB->PCR[7] |= 0x01000000;}

/*___PIN 009: PTB6/LPI2C0_SDA/XTAL____________________________________________*/
#define IO_PIN9_toOUT()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[6] &= ~PORT_MUX_MASK; PORTB->PCR[6] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_6;}
#define IO_PIN9_toIN()             {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[6] &= ~PORT_MUX_MASK; PORTB->PCR[6] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_6;}
#define IO_PIN9_toHI()             {PTB->PSOR |= PORT_PIN_6;}
#define IO_PIN9_toLO()             {PTB->PCOR |= PORT_PIN_6;}
#define IO_PIN9_TOGGLE()           {PTB->PTOR |= PORT_PIN_6;}
#define IO_PIN9_getINPUT()         {(PTB->PDIR & PORT_PIN_6) >> 6U;}
#define IO_PIN9_isHI()             ((PTB->PDIR & PORT_PIN_6) == PORT_PIN_6)
#define IO_PIN9_isLO()             ((PTB->PDIR & PORT_PIN_6) != PORT_PIN_6)
#define IO_PIN9_PULLoff()          {PORTB->PCR[6] &= ~PORT_PULL_MASK;}
#define IO_PIN9_PULLup()           {PORTB->PCR[6] &= ~PORT_PULL_MASK; PORTB->PCR[6] |= PORT_PULL_UP;}
#define IO_PIN9_PULLdown()         {PORTB->PCR[6] &= ~PORT_PULL_MASK; PORTB->PCR[6] |= PORT_PULL_DOWN;}
#define IO_PIN9_INToff()           {PORTB->PCR[6] &= ~PORT_IRQC_MASK;}
#define IO_PIN9_INTfalling()       {PORTB->PCR[6] &= ~PORT_IRQC_MASK; PORTB->PCR[6] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN9_INTrising()        {PORTB->PCR[6] &= ~PORT_IRQC_MASK; PORTB->PCR[6] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN9_INTany()           {PORTB->PCR[6] &= ~PORT_IRQC_MASK; PORTB->PCR[6] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN9_INTclear()         {PORTB->PCR[6] |= 0x01000000;}

/*___PIN 010: PTD16/FTM0_CH1/LPSPI0_SIN/CMP0_RRT______________________________*/
#define IO_PIN10_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[16] &= ~PORT_MUX_MASK; PORTD->PCR[16] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_16;}
#define IO_PIN10_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[16] &= ~PORT_MUX_MASK; PORTD->PCR[16] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_16;}
#define IO_PIN10_toHI()            {PTD->PSOR |= PORT_PIN_16;}
#define IO_PIN10_toLO()            {PTD->PCOR |= PORT_PIN_16;}
#define IO_PIN10_TOGGLE()          {PTD->PTOR |= PORT_PIN_16;}
#define IO_PIN10_getINPUT()        {(PTD->PDIR & PORT_PIN_16) >> 16U;}
#define IO_PIN10_isHI()            ((PTD->PDIR & PORT_PIN_16) == PORT_PIN_16)
#define IO_PIN10_isLO()            ((PTD->PDIR & PORT_PIN_16) != PORT_PIN_16)
#define IO_PIN10_PULLoff()         {PORTD->PCR[16] &= ~PORT_PULL_MASK;}
#define IO_PIN10_PULLup()          {PORTD->PCR[16] &= ~PORT_PULL_MASK; PORTD->PCR[16] |= PORT_PULL_UP;}
#define IO_PIN10_PULLdown()        {PORTD->PCR[16] &= ~PORT_PULL_MASK; PORTD->PCR[16] |= PORT_PULL_DOWN;}
#define IO_PIN10_INToff()          {PORTD->PCR[16] &= ~PORT_IRQC_MASK;}
#define IO_PIN10_INTfalling()      {PORTD->PCR[16] &= ~PORT_IRQC_MASK; PORTD->PCR[16] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN10_INTrising()       {PORTD->PCR[16] &= ~PORT_IRQC_MASK; PORTD->PCR[16] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN10_INTany()          {PORTD->PCR[16] &= ~PORT_IRQC_MASK; PORTD->PCR[16] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN10_INTclear()        {PORTD->PCR[16] |= 0x01000000;}

/*___PIN 011: PTD15/FTM0_CH0/LPSPI0_SCK_______________________________________*/
#define IO_PIN11_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[15] &= ~PORT_MUX_MASK; PORTD->PCR[15] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_15;}
#define IO_PIN11_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[15] &= ~PORT_MUX_MASK; PORTD->PCR[15] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_15;}
#define IO_PIN11_toHI()            {PTD->PSOR |= PORT_PIN_15;}
#define IO_PIN11_toLO()            {PTD->PCOR |= PORT_PIN_15;}
#define IO_PIN11_TOGGLE()          {PTD->PTOR |= PORT_PIN_15;}
#define IO_PIN11_getINPUT()        {(PTD->PDIR & PORT_PIN_15) >> 15U;}
#define IO_PIN11_isHI()            ((PTD->PDIR & PORT_PIN_15) == PORT_PIN_15)
#define IO_PIN11_isLO()            ((PTD->PDIR & PORT_PIN_15) != PORT_PIN_15)
#define IO_PIN11_PULLoff()         {PORTD->PCR[15] &= ~PORT_PULL_MASK;}
#define IO_PIN11_PULLup()          {PORTD->PCR[15] &= ~PORT_PULL_MASK; PORTD->PCR[15] |= PORT_PULL_UP;}
#define IO_PIN11_PULLdown()        {PORTD->PCR[15] &= ~PORT_PULL_MASK; PORTD->PCR[15] |= PORT_PULL_DOWN;}
#define IO_PIN11_INToff()          {PORTD->PCR[15] &= ~PORT_IRQC_MASK;}
#define IO_PIN11_INTfalling()      {PORTD->PCR[15] &= ~PORT_IRQC_MASK; PORTD->PCR[15] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN11_INTrising()       {PORTD->PCR[15] &= ~PORT_IRQC_MASK; PORTD->PCR[15] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN11_INTany()          {PORTD->PCR[15] &= ~PORT_IRQC_MASK; PORTD->PCR[15] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN11_INTclear()        {PORTD->PCR[15] |= 0x01000000;}

/*___PIN 012: PTE9/FTM0_CH7/LPUART2_CTS_______________________________________*/
#define IO_PIN12_toOUT()           {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[9] &= ~PORT_MUX_MASK; PORTE->PCR[9] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_9;}
#define IO_PIN12_toIN()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[9] &= ~PORT_MUX_MASK; PORTE->PCR[9] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_9;}
#define IO_PIN12_toHI()            {PTE->PSOR |= PORT_PIN_9;}
#define IO_PIN12_toLO()            {PTE->PCOR |= PORT_PIN_9;}
#define IO_PIN12_TOGGLE()          {PTE->PTOR |= PORT_PIN_9;}
#define IO_PIN12_getINPUT()        {(PTE->PDIR & PORT_PIN_9) >> 9U;}
#define IO_PIN12_isHI()            ((PTE->PDIR & PORT_PIN_9) == PORT_PIN_9)
#define IO_PIN12_isLO()            ((PTE->PDIR & PORT_PIN_9) != PORT_PIN_9)
#define IO_PIN12_PULLoff()         {PORTE->PCR[9] &= ~PORT_PULL_MASK;}
#define IO_PIN12_PULLup()          {PORTE->PCR[9] &= ~PORT_PULL_MASK; PORTE->PCR[9] |= PORT_PULL_UP;}
#define IO_PIN12_PULLdown()        {PORTE->PCR[9] &= ~PORT_PULL_MASK; PORTE->PCR[9] |= PORT_PULL_DOWN;}
#define IO_PIN12_INToff()          {PORTE->PCR[9] &= ~PORT_IRQC_MASK;}
#define IO_PIN12_INTfalling()      {PORTE->PCR[9] &= ~PORT_IRQC_MASK; PORTE->PCR[9] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN12_INTrising()       {PORTE->PCR[9] &= ~PORT_IRQC_MASK; PORTE->PCR[9] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN12_INTany()          {PORTE->PCR[9] &= ~PORT_IRQC_MASK; PORTE->PCR[9] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN12_INTclear()        {PORTE->PCR[9] |= 0x01000000;}

/*___PIN 013: PTE8/FTM0_CH6/CMP0_IN3__________________________________________*/
#define IO_PIN13_toOUT()           {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[8] &= ~PORT_MUX_MASK; PORTE->PCR[8] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR |= PORT_PIN_8;}
#define IO_PIN13_toIN()            {PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; PORTE->PCR[8] &= ~PORT_MUX_MASK; PORTE->PCR[8] |= PORT_MUX_PIN_ALT1_GPIO; PTE->PDDR &= ~PORT_PIN_8;}
#define IO_PIN13_toHI()            {PTE->PSOR |= PORT_PIN_8;}
#define IO_PIN13_toLO()            {PTE->PCOR |= PORT_PIN_8;}
#define IO_PIN13_TOGGLE()          {PTE->PTOR |= PORT_PIN_8;}
#define IO_PIN13_getINPUT()        {(PTE->PDIR & PORT_PIN_8) >> 8U;}
#define IO_PIN13_isHI()            ((PTE->PDIR & PORT_PIN_8) == PORT_PIN_8)
#define IO_PIN13_isLO()            ((PTE->PDIR & PORT_PIN_8) != PORT_PIN_8)
#define IO_PIN13_PULLoff()         {PORTE->PCR[8] &= ~PORT_PULL_MASK;}
#define IO_PIN13_PULLup()          {PORTE->PCR[8] &= ~PORT_PULL_MASK; PORTE->PCR[8] |= PORT_PULL_UP;}
#define IO_PIN13_PULLdown()        {PORTE->PCR[8] &= ~PORT_PULL_MASK; PORTE->PCR[8] |= PORT_PULL_DOWN;}
#define IO_PIN13_INToff()          {PORTE->PCR[8] &= ~PORT_IRQC_MASK;}
#define IO_PIN13_INTfalling()      {PORTE->PCR[8] &= ~PORT_IRQC_MASK; PORTE->PCR[8] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN13_INTrising()       {PORTE->PCR[8] &= ~PORT_IRQC_MASK; PORTE->PCR[8] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN13_INTany()          {PORTE->PCR[8] &= ~PORT_IRQC_MASK; PORTE->PCR[8] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTE_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTE_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN13_INTclear()        {PORTE->PCR[8] |= 0x01000000;}

/*___PIN 014: PTB5/FTM0_CH5/LPSPI0_PCS1/LPSPI0_PCS0/CLKOUT/TRGMUX_IN0_________*/
#define IO_PIN14_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[5] &= ~PORT_MUX_MASK; PORTB->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_5;}
#define IO_PIN14_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[5] &= ~PORT_MUX_MASK; PORTB->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_5;}
#define IO_PIN14_toHI()            {PTB->PSOR |= PORT_PIN_5;}
#define IO_PIN14_toLO()            {PTB->PCOR |= PORT_PIN_5;}
#define IO_PIN14_TOGGLE()          {PTB->PTOR |= PORT_PIN_5;}
#define IO_PIN14_getINPUT()        {(PTB->PDIR & PORT_PIN_5) >> 5U;}
#define IO_PIN14_isHI()            ((PTB->PDIR & PORT_PIN_5) == PORT_PIN_5)
#define IO_PIN14_isLO()            ((PTB->PDIR & PORT_PIN_5) != PORT_PIN_5)
#define IO_PIN14_PULLoff()         {PORTB->PCR[5] &= ~PORT_PULL_MASK;}
#define IO_PIN14_PULLup()          {PORTB->PCR[5] &= ~PORT_PULL_MASK; PORTB->PCR[5] |= PORT_PULL_UP;}
#define IO_PIN14_PULLdown()        {PORTB->PCR[5] &= ~PORT_PULL_MASK; PORTB->PCR[5] |= PORT_PULL_DOWN;}
#define IO_PIN14_INToff()          {PORTB->PCR[5] &= ~PORT_IRQC_MASK;}
#define IO_PIN14_INTfalling()      {PORTB->PCR[5] &= ~PORT_IRQC_MASK; PORTB->PCR[5] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN14_INTrising()       {PORTB->PCR[5] &= ~PORT_IRQC_MASK; PORTB->PCR[5] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN14_INTany()          {PORTB->PCR[5] &= ~PORT_IRQC_MASK; PORTB->PCR[5] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN14_INTclear()        {PORTB->PCR[5] |= 0x01000000;}

/*___PIN 015: PTB4/FTM0_CH4/LPSPI0_SOUT/TRGMUX_IN1____________________________*/
#define IO_PIN15_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[4] &= ~PORT_MUX_MASK; PORTB->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_4;}
#define IO_PIN15_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[4] &= ~PORT_MUX_MASK; PORTB->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_4;}
#define IO_PIN15_toHI()            {PTB->PSOR |= PORT_PIN_4;}
#define IO_PIN15_toLO()            {PTB->PCOR |= PORT_PIN_4;}
#define IO_PIN15_TOGGLE()          {PTB->PTOR |= PORT_PIN_4;}
#define IO_PIN15_getINPUT()        {(PTB->PDIR & PORT_PIN_4) >> 4U;}
#define IO_PIN15_isHI()            ((PTB->PDIR & PORT_PIN_4) == PORT_PIN_4)
#define IO_PIN15_isLO()            ((PTB->PDIR & PORT_PIN_4) != PORT_PIN_4)
#define IO_PIN15_PULLoff()         {PORTB->PCR[4] &= ~PORT_PULL_MASK;}
#define IO_PIN15_PULLup()          {PORTB->PCR[4] &= ~PORT_PULL_MASK; PORTB->PCR[4] |= PORT_PULL_UP;}
#define IO_PIN15_PULLdown()        {PORTB->PCR[4] &= ~PORT_PULL_MASK; PORTB->PCR[4] |= PORT_PULL_DOWN;}
#define IO_PIN15_INToff()          {PORTB->PCR[4] &= ~PORT_IRQC_MASK;}
#define IO_PIN15_INTfalling()      {PORTB->PCR[4] &= ~PORT_IRQC_MASK; PORTB->PCR[4] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN15_INTrising()       {PORTB->PCR[4] &= ~PORT_IRQC_MASK; PORTB->PCR[4] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN15_INTany()          {PORTB->PCR[4] &= ~PORT_IRQC_MASK; PORTB->PCR[4] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN15_INTclear()        {PORTB->PCR[4] |= 0x01000000;}

/*___PIN 016: PTC3/FTM0_CH3/CAN0_TX/LPUART0_TX/ADC0_SE11/CMP0_IN4_____________*/
#define IO_PIN16_toANALOG()        {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[3] &= ~PORT_MUX_MASK; PORTC->PCR[3] |= PORT_MUX_PIN_DISABLED;}
#define IO_PIN16_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[3] &= ~PORT_MUX_MASK; PORTC->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_3;}
#define IO_PIN16_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[3] &= ~PORT_MUX_MASK; PORTC->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_3;}
#define IO_PIN16_toHI()            {PTC->PSOR |= PORT_PIN_3;}
#define IO_PIN16_toLO()            {PTC->PCOR |= PORT_PIN_3;}
#define IO_PIN16_TOGGLE()          {PTC->PTOR |= PORT_PIN_3;}
#define IO_PIN16_getINPUT()        {(PTC->PDIR & PORT_PIN_3) >> 3U;}
#define IO_PIN16_isHI()            ((PTC->PDIR & PORT_PIN_3) == PORT_PIN_3)
#define IO_PIN16_isLO()            ((PTC->PDIR & PORT_PIN_3) != PORT_PIN_3)
#define IO_PIN16_PULLoff()         {PORTC->PCR[3] &= ~PORT_PULL_MASK;}
#define IO_PIN16_PULLup()          {PORTC->PCR[3] &= ~PORT_PULL_MASK; PORTC->PCR[3] |= PORT_PULL_UP;}
#define IO_PIN16_PULLdown()        {PORTC->PCR[3] &= ~PORT_PULL_MASK; PORTC->PCR[3] |= PORT_PULL_DOWN;}
#define IO_PIN16_INToff()          {PORTC->PCR[3] &= ~PORT_IRQC_MASK;}
#define IO_PIN16_INTfalling()      {PORTC->PCR[3] &= ~PORT_IRQC_MASK; PORTC->PCR[3] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN16_INTrising()       {PORTC->PCR[3] &= ~PORT_IRQC_MASK; PORTC->PCR[3] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN16_INTany()          {PORTC->PCR[3] &= ~PORT_IRQC_MASK; PORTC->PCR[3] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN16_INTclear()        {PORTC->PCR[3] |= 0x01000000;}

/*___PIN 017: PTC2/FTM0_CH2/CAN0_RX/LPUART0_RX/ADC0_SE10/CMP0_IN5_____________*/
#define IO_PIN17_toANALOG()        {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[2] &= ~PORT_MUX_MASK;}
#define IO_PIN17_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[2] &= ~PORT_MUX_MASK; PORTC->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_2;}
#define IO_PIN17_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[2] &= ~PORT_MUX_MASK; PORTC->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_2;}
#define IO_PIN17_toHI()            {PTC->PSOR |= PORT_PIN_2;}
#define IO_PIN17_toLO()            {PTC->PCOR |= PORT_PIN_2;}
#define IO_PIN17_TOGGLE()          {PTC->PTOR |= PORT_PIN_2;}
#define IO_PIN17_getINPUT()        {(PTC->PDIR & PORT_PIN_2) >> 2U;}
#define IO_PIN17_isHI()            ((PTC->PDIR & PORT_PIN_2) == PORT_PIN_2)
#define IO_PIN17_isLO()            ((PTC->PDIR & PORT_PIN_2) != PORT_PIN_2)
#define IO_PIN17_PULLoff()         {PORTC->PCR[2] &= ~PORT_PULL_MASK;}
#define IO_PIN17_PULLup()          {PORTC->PCR[2] &= ~PORT_PULL_MASK; PORTC->PCR[2] |= PORT_PULL_UP;}
#define IO_PIN17_PULLdown()        {PORTC->PCR[2] &= ~PORT_PULL_MASK; PORTC->PCR[2] |= PORT_PULL_DOWN;}
#define IO_PIN17_INToff()          {PORTC->PCR[2] &= ~PORT_IRQC_MASK;}
#define IO_PIN17_INTfalling()      {PORTC->PCR[2] &= ~PORT_IRQC_MASK; PORTC->PCR[2] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN17_INTrising()       {PORTC->PCR[2] &= ~PORT_IRQC_MASK; PORTC->PCR[2] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN17_INTany()          {PORTC->PCR[2] &= ~PORT_IRQC_MASK; PORTC->PCR[2] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN17_INTclear()        {PORTC->PCR[2] |= 0x01000000;}

/*___PIN 018: PTD5/FTM2_CH3/LPTMR0_ALT2/FTM2_FLT1/TRGMUX_IN7__________________*/
#define IO_PIN18_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[5] &= ~PORT_MUX_MASK; PORTD->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_5;}
#define IO_PIN18_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[5] &= ~PORT_MUX_MASK; PORTD->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_5;}
#define IO_PIN18_toHI()            {PTD->PSOR |= PORT_PIN_5;}
#define IO_PIN18_toLO()            {PTD->PCOR |= PORT_PIN_5;}
#define IO_PIN18_TOGGLE()          {PTD->PTOR |= PORT_PIN_5;}
#define IO_PIN18_getINPUT()        {(PTD->PDIR & PORT_PIN_5) >> 5U;}
#define IO_PIN18_isHI()            ((PTD->PDIR & PORT_PIN_5) == PORT_PIN_5)
#define IO_PIN18_isLO()            ((PTD->PDIR & PORT_PIN_5) != PORT_PIN_5)
#define IO_PIN18_PULLoff()         {PORTD->PCR[5] &= ~PORT_PULL_MASK;}
#define IO_PIN18_PULLup()          {PORTD->PCR[5] &= ~PORT_PULL_MASK; PORTD->PCR[5] |= PORT_PULL_UP;}
#define IO_PIN18_PULLdown()        {PORTD->PCR[5] &= ~PORT_PULL_MASK; PORTD->PCR[5] |= PORT_PULL_DOWN;}
#define IO_PIN18_INToff()          {PORTD->PCR[5] &= ~PORT_IRQC_MASK;}
#define IO_PIN18_INTfalling()      {PORTD->PCR[5] &= ~PORT_IRQC_MASK; PORTD->PCR[5] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN18_INTrising()       {PORTD->PCR[5] &= ~PORT_IRQC_MASK; PORTD->PCR[5] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN18_INTany()          {PORTD->PCR[5] &= ~PORT_IRQC_MASK; PORTD->PCR[5] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN18_INTclear()        {PORTD->PCR[5] |= 0x01000000;}

/*___PIN 019: PTC1/FTM0_CH1/LPSPI2_SOUT/FTM1_CH7/ADC0_SE9_____________________*/
#define IO_PIN19_toANALOG()        {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[1] &= ~PORT_MUX_MASK;}
#define IO_PIN19_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[1] &= ~PORT_MUX_MASK; PORTC->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_1;}
#define IO_PIN19_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[1] &= ~PORT_MUX_MASK; PORTC->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_1;}
#define IO_PIN19_toHI()            {PTC->PSOR |= PORT_PIN_1;}
#define IO_PIN19_toLO()            {PTC->PCOR |= PORT_PIN_1;}
#define IO_PIN19_TOGGLE()          {PTC->PTOR |= PORT_PIN_1;}
#define IO_PIN19_getINPUT()        {(PTC->PDIR & PORT_PIN_1) >> 1U;}
#define IO_PIN19_isHI()            ((PTC->PDIR & PORT_PIN_1) == PORT_PIN_1)
#define IO_PIN19_isLO()            ((PTC->PDIR & PORT_PIN_1) != PORT_PIN_1)
#define IO_PIN19_PULLoff()         {PORTC->PCR[1] &= ~PORT_PULL_MASK;}
#define IO_PIN19_PULLup()          {PORTC->PCR[1] &= ~PORT_PULL_MASK; PORTC->PCR[1] |= PORT_PULL_UP;}
#define IO_PIN19_PULLdown()        {PORTC->PCR[1] &= ~PORT_PULL_MASK; PORTC->PCR[1] |= PORT_PULL_DOWN;}
#define IO_PIN19_INToff()          {PORTC->PCR[1] &= ~PORT_IRQC_MASK;}
#define IO_PIN19_INTfalling()      {PORTC->PCR[1] &= ~PORT_IRQC_MASK; PORTC->PCR[1] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN19_INTrising()       {PORTC->PCR[1] &= ~PORT_IRQC_MASK; PORTC->PCR[1] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN19_INTany()          {PORTC->PCR[1] &= ~PORT_IRQC_MASK; PORTC->PCR[1] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN19_INTclear()        {PORTC->PCR[1] |= 0x01000000;}

/*___PIN 020: PTC16/FTM1_FLT2/CAN2_RX/ADC0_SE14_______________________________*/
#define IO_PIN20_toANALOG()        {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[16] &= ~PORT_MUX_MASK;}
#define IO_PIN20_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[16] &= ~PORT_MUX_MASK; PORTC->PCR[16] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_16;}
#define IO_PIN20_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[16] &= ~PORT_MUX_MASK; PORTC->PCR[16] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_16;}
#define IO_PIN20_toHI()            {PTC->PSOR |= PORT_PIN_16;}
#define IO_PIN20_toLO()            {PTC->PCOR |= PORT_PIN_16;}
#define IO_PIN20_TOGGLE()          {PTC->PTOR |= PORT_PIN_16;}
#define IO_PIN20_getINPUT()        {(PTC->PDIR & PORT_PIN_16) >> 16U;}
#define IO_PIN20_isHI()            ((PTC->PDIR & PORT_PIN_16) == PORT_PIN_16)
#define IO_PIN20_isLO()            ((PTC->PDIR & PORT_PIN_16) != PORT_PIN_16)
#define IO_PIN20_PULLoff()         {PORTC->PCR[16] &= ~PORT_PULL_MASK;}
#define IO_PIN20_PULLup()          {PORTC->PCR[16] &= ~PORT_PULL_MASK; PORTC->PCR[16] |= PORT_PULL_UP;}
#define IO_PIN20_PULLdown()        {PORTC->PCR[16] &= ~PORT_PULL_MASK; PORTC->PCR[16] |= PORT_PULL_DOWN;}
#define IO_PIN20_INToff()          {PORTC->PCR[16] &= ~PORT_IRQC_MASK;}
#define IO_PIN20_INTfalling()      {PORTC->PCR[16] &= ~PORT_IRQC_MASK; PORTC->PCR[16] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN20_INTrising()       {PORTC->PCR[16] &= ~PORT_IRQC_MASK; PORTC->PCR[16] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN20_INTany()          {PORTC->PCR[16] &= ~PORT_IRQC_MASK; PORTC->PCR[16] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN20_INTclear()        {PORTC->PCR[16] |= 0x01000000;}

/*___PIN 021: PTC15/FTM1_CH3/LPSPI2_SCK/TRGMUX_IN8/ADC0_SE13__________________*/
#define IO_PIN21_toANALOG()        {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[15] &= ~PORT_MUX_MASK;}
#define IO_PIN21_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[15] &= ~PORT_MUX_MASK; PORTC->PCR[15] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_15;}
#define IO_PIN21_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[15] &= ~PORT_MUX_MASK; PORTC->PCR[15] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_15;}
#define IO_PIN21_toHI()            {PTC->PSOR |= PORT_PIN_15;}
#define IO_PIN21_toLO()            {PTC->PCOR |= PORT_PIN_15;}
#define IO_PIN21_TOGGLE()          {PTC->PTOR |= PORT_PIN_15;}
#define IO_PIN21_getINPUT()        {(PTC->PDIR & PORT_PIN_15) >> 15U;}
#define IO_PIN21_isHI()            ((PTC->PDIR & PORT_PIN_15) == PORT_PIN_15)
#define IO_PIN21_isLO()            ((PTC->PDIR & PORT_PIN_15) != PORT_PIN_15)
#define IO_PIN21_PULLoff()         {PORTC->PCR[15] &= ~PORT_PULL_MASK;}
#define IO_PIN21_PULLup()          {PORTC->PCR[15] &= ~PORT_PULL_MASK; PORTC->PCR[15] |= PORT_PULL_UP;}
#define IO_PIN21_PULLdown()        {PORTC->PCR[15] &= ~PORT_PULL_MASK; PORTC->PCR[15] |= PORT_PULL_DOWN;}
#define IO_PIN21_INToff()          {PORTC->PCR[15] &= ~PORT_IRQC_MASK;}
#define IO_PIN21_INTfalling()      {PORTC->PCR[15] &= ~PORT_IRQC_MASK; PORTC->PCR[15] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN21_INTrising()       {PORTC->PCR[15] &= ~PORT_IRQC_MASK; PORTC->PCR[15] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN21_INTany()          {PORTC->PCR[15] &= ~PORT_IRQC_MASK; PORTC->PCR[15] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN21_INTclear()        {PORTC->PCR[15] |= 0x01000000;}

/*___PIN 022: PTC14/FTM1_CH2/LPSPI2_PCS0/TRGMUX_IN9/ADC0_SE12_________________*/
#define IO_PIN22_toANALOG()        {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[14] &= ~PORT_MUX_MASK;}
#define IO_PIN22_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[14] &= ~PORT_MUX_MASK; PORTC->PCR[14] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_14;}
#define IO_PIN22_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[14] &= ~PORT_MUX_MASK; PORTC->PCR[14] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_14;}
#define IO_PIN22_toHI()            {PTC->PSOR |= PORT_PIN_14;}
#define IO_PIN22_toLO()            {PTC->PCOR |= PORT_PIN_14;}
#define IO_PIN22_TOGGLE()          {PTC->PTOR |= PORT_PIN_14;}
#define IO_PIN22_getINPUT()        {(PTC->PDIR & PORT_PIN_14) >> 14U;}
#define IO_PIN22_isHI()            ((PTC->PDIR & PORT_PIN_14) == PORT_PIN_14)
#define IO_PIN22_isLO()            ((PTC->PDIR & PORT_PIN_14) != PORT_PIN_14)
#define IO_PIN22_PULLoff()         {PORTC->PCR[14] &= ~PORT_PULL_MASK;}
#define IO_PIN22_PULLup()          {PORTC->PCR[14] &= ~PORT_PULL_MASK; PORTC->PCR[14] |= PORT_PULL_UP;}
#define IO_PIN22_PULLdown()        {PORTC->PCR[14] &= ~PORT_PULL_MASK; PORTC->PCR[14] |= PORT_PULL_DOWN;}
#define IO_PIN22_INToff()          {PORTC->PCR[14] &= ~PORT_IRQC_MASK;}
#define IO_PIN22_INTfalling()      {PORTC->PCR[14] &= ~PORT_IRQC_MASK; PORTC->PCR[14] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN22_INTrising()       {PORTC->PCR[14] &= ~PORT_IRQC_MASK; PORTC->PCR[14] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN22_INTany()          {PORTC->PCR[14] &= ~PORT_IRQC_MASK; PORTC->PCR[14] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN22_INTclear()        {PORTC->PCR[14] |= 0x01000000;}

/*___PIN 023: PTB3/FTM1_CH1/LPSPI0_SIN/FTM1_QD_PHA/TRGMUX_IN2/ADC0_SE7________*/
#define IO_PIN23_toANALOG()        {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[3] &= ~PORT_MUX_MASK;}
#define IO_PIN23_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[3] &= ~PORT_MUX_MASK; PORTB->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_3;}
#define IO_PIN23_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[3] &= ~PORT_MUX_MASK; PORTB->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_3;}
#define IO_PIN23_toHI()            {PTB->PSOR |= PORT_PIN_3;}
#define IO_PIN23_toLO()            {PTB->PCOR |= PORT_PIN_3;}
#define IO_PIN23_TOGGLE()          {PTB->PTOR |= PORT_PIN_3;}
#define IO_PIN23_getINPUT()        {(PTB->PDIR & PORT_PIN_3) >> 3U;}
#define IO_PIN23_isHI()            ((PTB->PDIR & PORT_PIN_3) == PORT_PIN_3)
#define IO_PIN23_isLO()            ((PTB->PDIR & PORT_PIN_3) != PORT_PIN_3)
#define IO_PIN23_PULLoff()         {PORTB->PCR[3] &= ~PORT_PULL_MASK;}
#define IO_PIN23_PULLup()          {PORTB->PCR[3] &= ~PORT_PULL_MASK; PORTB->PCR[3] |= PORT_PULL_UP;}
#define IO_PIN23_PULLdown()        {PORTB->PCR[3] &= ~PORT_PULL_MASK; PORTB->PCR[3] |= PORT_PULL_DOWN;}
#define IO_PIN23_INToff()          {PORTB->PCR[3] &= ~PORT_IRQC_MASK;}
#define IO_PIN23_INTfalling()      {PORTB->PCR[3] &= ~PORT_IRQC_MASK; PORTB->PCR[3] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN23_INTrising()       {PORTB->PCR[3] &= ~PORT_IRQC_MASK; PORTB->PCR[3] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN23_INTany()          {PORTB->PCR[3] &= ~PORT_IRQC_MASK; PORTB->PCR[3] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN23_INTclear()        {PORTB->PCR[3] |= 0x01000000;}

/*___PIN 024: PTB2/FTM1_CH0/LPSPI0_SCK/FTM1_QD_PHB/TRGMUX_IN3/ADC0_SE6________*/
#define IO_PIN24_toANALOG()        {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[2] &= ~PORT_MUX_MASK;}
#define IO_PIN24_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[2] &= ~PORT_MUX_MASK; PORTB->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_2;}
#define IO_PIN24_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[2] &= ~PORT_MUX_MASK; PORTB->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_2;}
#define IO_PIN24_toHI()            {PTB->PSOR |= PORT_PIN_2;}
#define IO_PIN24_toLO()            {PTB->PCOR |= PORT_PIN_2;}
#define IO_PIN24_TOGGLE()          {PTB->PTOR |= PORT_PIN_2;}
#define IO_PIN24_getINPUT()        {(PTB->PDIR & PORT_PIN_2) >> 2U;}
#define IO_PIN24_isHI()            ((PTB->PDIR & PORT_PIN_2) == PORT_PIN_2)
#define IO_PIN24_isLO()            ((PTB->PDIR & PORT_PIN_2) != PORT_PIN_2)
#define IO_PIN24_PULLoff()         {PORTB->PCR[2] &= ~PORT_PULL_MASK;}
#define IO_PIN24_PULLup()          {PORTB->PCR[2] &= ~PORT_PULL_MASK; PORTB->PCR[2] |= PORT_PULL_UP;}
#define IO_PIN24_PULLdown()        {PORTB->PCR[2] &= ~PORT_PULL_MASK; PORTB->PCR[2] |= PORT_PULL_DOWN;}
#define IO_PIN24_INToff()          {PORTB->PCR[2] &= ~PORT_IRQC_MASK;}
#define IO_PIN24_INTfalling()      {PORTB->PCR[2] &= ~PORT_IRQC_MASK; PORTB->PCR[2] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN24_INTrising()       {PORTB->PCR[2] &= ~PORT_IRQC_MASK; PORTB->PCR[2] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN24_INTany()          {PORTB->PCR[2] &= ~PORT_IRQC_MASK; PORTB->PCR[2] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN24_INTclear()        {PORTB->PCR[2] |= 0x01000000;}

/*___PIN 025: PTB1/LPUART0_TX/LPSPI0_SOUT/TCLK0/CAN0_TX/ADC0_SE5/ADC1_SE15____*/
#define IO_PIN25_toANALOG()        {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[1] &= ~PORT_MUX_MASK;}
#define IO_PIN25_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[1] &= ~PORT_MUX_MASK; PORTB->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_1;}
#define IO_PIN25_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[1] &= ~PORT_MUX_MASK; PORTB->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_1;}
#define IO_PIN25_toHI()            {PTB->PSOR |= PORT_PIN_1;}
#define IO_PIN25_toLO()            {PTB->PCOR |= PORT_PIN_1;}
#define IO_PIN25_TOGGLE()          {PTB->PTOR |= PORT_PIN_1;}
#define IO_PIN25_getINPUT()        {(PTB->PDIR & PORT_PIN_1) >> 1U;}
#define IO_PIN25_isHI()            ((PTB->PDIR & PORT_PIN_1) == PORT_PIN_1)
#define IO_PIN25_isLO()            ((PTB->PDIR & PORT_PIN_1) != PORT_PIN_1)
#define IO_PIN25_PULLoff()         {PORTB->PCR[1] &= ~PORT_PULL_MASK;}
#define IO_PIN25_PULLup()          {PORTB->PCR[1] &= ~PORT_PULL_MASK; PORTB->PCR[1] |= PORT_PULL_UP;}
#define IO_PIN25_PULLdown()        {PORTB->PCR[1] &= ~PORT_PULL_MASK; PORTB->PCR[1] |= PORT_PULL_DOWN;}
#define IO_PIN25_INToff()          {PORTB->PCR[1] &= ~PORT_IRQC_MASK;}
#define IO_PIN25_INTfalling()      {PORTB->PCR[1] &= ~PORT_IRQC_MASK; PORTB->PCR[1] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN25_INTrising()       {PORTB->PCR[1] &= ~PORT_IRQC_MASK; PORTB->PCR[1] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN25_INTany()          {PORTB->PCR[1] &= ~PORT_IRQC_MASK; PORTB->PCR[1] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN25_INTclear()        {PORTB->PCR[1] |= 0x01000000;}

/*___PIN 026: PTB0/LPUART0_RX/LPSPI0_PCS0/LPTMR0_ALT3/CAN0_RX/ADC0_SE4/ADC1_SE14_*/
#define IO_PIN26_toANALOG()        {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[0] &= ~PORT_MUX_MASK;}
#define IO_PIN26_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[0] &= ~PORT_MUX_MASK; PORTB->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_0;}
#define IO_PIN26_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[0] &= ~PORT_MUX_MASK; PORTB->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_0;}
#define IO_PIN26_toHI()            {PTB->PSOR |= PORT_PIN_0;}
#define IO_PIN26_toLO()            {PTB->PCOR |= PORT_PIN_0;}
#define IO_PIN26_TOGGLE()          {PTB->PTOR |= PORT_PIN_0;}
#define IO_PIN26_getINPUT()        {(PTB->PDIR & PORT_PIN_0) >> 0U;}
#define IO_PIN26_isHI()            ((PTB->PDIR & PORT_PIN_0) == PORT_PIN_0)
#define IO_PIN26_isLO()            ((PTB->PDIR & PORT_PIN_0) != PORT_PIN_0)
#define IO_PIN26_PULLoff()         {PORTB->PCR[0] &= ~PORT_PULL_MASK;}
#define IO_PIN26_PULLup()          {PORTB->PCR[0] &= ~PORT_PULL_MASK; PORTB->PCR[0] |= PORT_PULL_UP;}
#define IO_PIN26_PULLdown()        {PORTB->PCR[0] &= ~PORT_PULL_MASK; PORTB->PCR[0] |= PORT_PULL_DOWN;}
#define IO_PIN26_INToff()          {PORTB->PCR[0] &= ~PORT_IRQC_MASK;}
#define IO_PIN26_INTfalling()      {PORTB->PCR[0] &= ~PORT_IRQC_MASK; PORTB->PCR[0] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN26_INTrising()       {PORTB->PCR[0] &= ~PORT_IRQC_MASK; PORTB->PCR[0] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN26_INTany()          {PORTB->PCR[0] &= ~PORT_IRQC_MASK; PORTB->PCR[0] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN26_INTclear()        {PORTB->PCR[0] |= 0x01000000;}

/*___PIN 027: PTC9/LPUART1_TX/FTM1_FLT1/LPUART0_RTS___________________________*/
#define IO_PIN27_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[9] &= ~PORT_MUX_MASK; PORTC->PCR[9] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_9;}
#define IO_PIN27_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[9] &= ~PORT_MUX_MASK; PORTC->PCR[9] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_9;}
#define IO_PIN27_toHI()            {PTC->PSOR |= PORT_PIN_9;}
#define IO_PIN27_toLO()            {PTC->PCOR |= PORT_PIN_9;}
#define IO_PIN27_TOGGLE()          {PTC->PTOR |= PORT_PIN_9;}
#define IO_PIN27_getINPUT()        {(PTC->PDIR & PORT_PIN_9) >> 9U;}
#define IO_PIN27_isHI()            ((PTC->PDIR & PORT_PIN_9) == PORT_PIN_9)
#define IO_PIN27_isLO()            ((PTC->PDIR & PORT_PIN_9) != PORT_PIN_9)
#define IO_PIN27_PULLoff()         {PORTC->PCR[9] &= ~PORT_PULL_MASK;}
#define IO_PIN27_PULLup()          {PORTC->PCR[9] &= ~PORT_PULL_MASK; PORTC->PCR[9] |= PORT_PULL_UP;}
#define IO_PIN27_PULLdown()        {PORTC->PCR[9] &= ~PORT_PULL_MASK; PORTC->PCR[9] |= PORT_PULL_DOWN;}
#define IO_PIN27_INToff()          {PORTC->PCR[9] &= ~PORT_IRQC_MASK;}
#define IO_PIN27_INTfalling()      {PORTC->PCR[9] &= ~PORT_IRQC_MASK; PORTC->PCR[9] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN27_INTrising()       {PORTC->PCR[9] &= ~PORT_IRQC_MASK; PORTC->PCR[9] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN27_INTany()          {PORTC->PCR[9] &= ~PORT_IRQC_MASK; PORTC->PCR[9] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN27_INTclear()        {PORTC->PCR[9] |= 0x01000000;}

/*___PIN 028: PTC8/LPUART1_RX/FTM1_FLT0/LPUART0_CTS___________________________*/
#define IO_PIN28_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[8] &= ~PORT_MUX_MASK; PORTC->PCR[8] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_8;}
#define IO_PIN28_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[8] &= ~PORT_MUX_MASK; PORTC->PCR[8] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_8;}
#define IO_PIN28_toHI()            {PTC->PSOR |= PORT_PIN_8;}
#define IO_PIN28_toLO()            {PTC->PCOR |= PORT_PIN_8;}
#define IO_PIN28_TOGGLE()          {PTC->PTOR |= PORT_PIN_8;}
#define IO_PIN28_getINPUT()        {(PTC->PDIR & PORT_PIN_8) >> 8U;}
#define IO_PIN28_isHI()            ((PTC->PDIR & PORT_PIN_8) == PORT_PIN_8)
#define IO_PIN28_isLO()            ((PTC->PDIR & PORT_PIN_8) != PORT_PIN_8)
#define IO_PIN28_PULLoff()         {PORTC->PCR[8] &= ~PORT_PULL_MASK;}
#define IO_PIN28_PULLup()          {PORTC->PCR[8] &= ~PORT_PULL_MASK; PORTC->PCR[8] |= PORT_PULL_UP;}
#define IO_PIN28_PULLdown()        {PORTC->PCR[8] &= ~PORT_PULL_MASK; PORTC->PCR[8] |= PORT_PULL_DOWN;}
#define IO_PIN28_INToff()          {PORTC->PCR[8] &= ~PORT_IRQC_MASK;}
#define IO_PIN28_INTfalling()      {PORTC->PCR[8] &= ~PORT_IRQC_MASK; PORTC->PCR[8] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN28_INTrising()       {PORTC->PCR[8] &= ~PORT_IRQC_MASK; PORTC->PCR[8] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN28_INTany()          {PORTC->PCR[8] &= ~PORT_IRQC_MASK; PORTC->PCR[8] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN28_INTclear()        {PORTC->PCR[8] |= 0x01000000;}

/*___PIN 029: PTA7/FTM0_FLT2/RTC_CLKIN/LPUART1_RTS/ADC0_SE3___________________*/
#define IO_PIN29_toANALOG()        {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[7] &= ~PORT_MUX_MASK;}
#define IO_PIN29_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[7] &= ~PORT_MUX_MASK; PORTA->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_7;}
#define IO_PIN29_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[7] &= ~PORT_MUX_MASK; PORTA->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_7;}
#define IO_PIN29_toHI()            {PTA->PSOR |= PORT_PIN_7;}
#define IO_PIN29_toLO()            {PTA->PCOR |= PORT_PIN_7;}
#define IO_PIN29_TOGGLE()          {PTA->PTOR |= PORT_PIN_7;}
#define IO_PIN29_getINPUT()        {(PTA->PDIR & PORT_PIN_7) >> 7U;}
#define IO_PIN29_isHI()            ((PTA->PDIR & PORT_PIN_7) == PORT_PIN_7)
#define IO_PIN29_isLO()            ((PTA->PDIR & PORT_PIN_7) != PORT_PIN_7)
#define IO_PIN29_PULLoff()         {PORTA->PCR[7] &= ~PORT_PULL_MASK;}
#define IO_PIN29_PULLup()          {PORTA->PCR[7] &= ~PORT_PULL_MASK; PORTA->PCR[7] |= PORT_PULL_UP;}
#define IO_PIN29_PULLdown()        {PORTA->PCR[7] &= ~PORT_PULL_MASK; PORTA->PCR[7] |= PORT_PULL_DOWN;}
#define IO_PIN29_INToff()          {PORTA->PCR[7] &= ~PORT_IRQC_MASK;}
#define IO_PIN29_INTfalling()      {PORTA->PCR[7] &= ~PORT_IRQC_MASK; PORTA->PCR[7] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN29_INTrising()       {PORTA->PCR[7] &= ~PORT_IRQC_MASK; PORTA->PCR[7] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN29_INTany()          {PORTA->PCR[7] &= ~PORT_IRQC_MASK; PORTA->PCR[7] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN29_INTclear()        {PORTA->PCR[7] |= 0x01000000;}

/*___PIN 030: VSS_____________________________________________________________*/

/*___PIN 031: VDD_____________________________________________________________*/

/*___PIN 032: PTB13/FTM0_CH1/FTM3_FLT1/CAN2_TX/ADC1_SE8/ADC0_SE8______________*/
#define IO_PIN32_toANALOG()        {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[13] &= ~PORT_MUX_MASK;}
#define IO_PIN32_toOUT()           {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[13] &= ~PORT_MUX_MASK; PORTB->PCR[13] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR |= PORT_PIN_13;}
#define IO_PIN32_toIN()            {PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; PORTB->PCR[13] &= ~PORT_MUX_MASK; PORTB->PCR[13] |= PORT_MUX_PIN_ALT1_GPIO; PTB->PDDR &= ~PORT_PIN_13;}
#define IO_PIN32_toHI()            {PTB->PSOR |= PORT_PIN_13;}
#define IO_PIN32_toLO()            {PTB->PCOR |= PORT_PIN_13;}
#define IO_PIN32_TOGGLE()          {PTB->PTOR |= PORT_PIN_13;}
#define IO_PIN32_getINPUT()        {(PTB->PDIR & PORT_PIN_13) >> 13U;}
#define IO_PIN32_isHI()            ((PTB->PDIR & PORT_PIN_13) == PORT_PIN_13)
#define IO_PIN32_isLO()            ((PTB->PDIR & PORT_PIN_13) != PORT_PIN_13)
#define IO_PIN32_PULLoff()         {PORTB->PCR[13] &= ~PORT_PULL_MASK;}
#define IO_PIN32_PULLup()          {PORTB->PCR[13] &= ~PORT_PULL_MASK; PORTB->PCR[13] |= PORT_PULL_UP;}
#define IO_PIN32_PULLdown()        {PORTB->PCR[13] &= ~PORT_PULL_MASK; PORTB->PCR[13] |= PORT_PULL_DOWN;}
#define IO_PIN32_INToff()          {PORTB->PCR[13] &= ~PORT_IRQC_MASK;}
#define IO_PIN32_INTfalling()      {PORTB->PCR[13] &= ~PORT_IRQC_MASK; PORTB->PCR[13] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN32_INTrising()       {PORTB->PCR[13] &= ~PORT_IRQC_MASK; PORTB->PCR[13] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN32_INTany()          {PORTB->PCR[13] &= ~PORT_IRQC_MASK; PORTB->PCR[13] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTB_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN32_INTclear()        {PORTB->PCR[13] |= 0x01000000;}

/*___PIN 033: PTD3/FTM3_CH5/LPSPI1_PCS0/FXIO_D5/FXIO_D7/TRGMUX_IN4/NMI_b/ADC1_SE3_*/
#define IO_PIN33_toANALOG()        {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[3] &= ~PORT_MUX_MASK;}
#define IO_PIN33_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[3] &= ~PORT_MUX_MASK; PORTD->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_3;}
#define IO_PIN33_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[3] &= ~PORT_MUX_MASK; PORTD->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_3;}
#define IO_PIN33_toHI()            {PTD->PSOR |= PORT_PIN_3;}
#define IO_PIN33_toLO()            {PTD->PCOR |= PORT_PIN_3;}
#define IO_PIN33_TOGGLE()          {PTD->PTOR |= PORT_PIN_3;}
#define IO_PIN33_getINPUT()        {(PTD->PDIR & PORT_PIN_3) >> 3U;}
#define IO_PIN33_isHI()            ((PTD->PDIR & PORT_PIN_3) == PORT_PIN_3)
#define IO_PIN33_isLO()            ((PTD->PDIR & PORT_PIN_3) != PORT_PIN_3)
#define IO_PIN33_PULLoff()         {PORTD->PCR[3] &= ~PORT_PULL_MASK;}
#define IO_PIN33_PULLup()          {PORTD->PCR[3] &= ~PORT_PULL_MASK; PORTD->PCR[3] |= PORT_PULL_UP;}
#define IO_PIN33_PULLdown()        {PORTD->PCR[3] &= ~PORT_PULL_MASK; PORTD->PCR[3] |= PORT_PULL_DOWN;}
#define IO_PIN33_INToff()          {PORTD->PCR[3] &= ~PORT_IRQC_MASK;}
#define IO_PIN33_INTfalling()      {PORTD->PCR[3] &= ~PORT_IRQC_MASK; PORTD->PCR[3] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN33_INTrising()       {PORTD->PCR[3] &= ~PORT_IRQC_MASK; PORTD->PCR[3] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN33_INTany()          {PORTD->PCR[3] &= ~PORT_IRQC_MASK; PORTD->PCR[3] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN33_INTclear()        {PORTD->PCR[3] |= 0x01000000;}

/*___PIN 034: PTD2/FTM3_CH4/LPSPI1_SOUT/FXIO_D4/FXIO_D6/TRGMUX_IN5/ADC1_SE2___*/
#define IO_PIN34_toANALOG()        {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[2] &= ~PORT_MUX_MASK;}
#define IO_PIN34_toOUT()           {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[2] &= ~PORT_MUX_MASK; PORTD->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR |= PORT_PIN_2;}
#define IO_PIN34_toIN()            {PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; PORTD->PCR[2] &= ~PORT_MUX_MASK; PORTD->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTD->PDDR &= ~PORT_PIN_2;}
#define IO_PIN34_toHI()            {PTD->PSOR |= PORT_PIN_2;}
#define IO_PIN34_toLO()            {PTD->PCOR |= PORT_PIN_2;}
#define IO_PIN34_TOGGLE()          {PTD->PTOR |= PORT_PIN_2;}
#define IO_PIN34_getINPUT()        {(PTD->PDIR & PORT_PIN_2) >> 2U;}
#define IO_PIN34_isHI()            ((PTD->PDIR & PORT_PIN_2) == PORT_PIN_2)
#define IO_PIN34_isLO()            ((PTD->PDIR & PORT_PIN_2) != PORT_PIN_2)
#define IO_PIN34_PULLoff()         {PORTD->PCR[2] &= ~PORT_PULL_MASK;}
#define IO_PIN34_PULLup()          {PORTD->PCR[2] &= ~PORT_PULL_MASK; PORTD->PCR[2] |= PORT_PULL_UP;}
#define IO_PIN34_PULLdown()        {PORTD->PCR[2] &= ~PORT_PULL_MASK; PORTD->PCR[2] |= PORT_PULL_DOWN;}
#define IO_PIN34_INToff()          {PORTD->PCR[2] &= ~PORT_IRQC_MASK;}
#define IO_PIN34_INTfalling()      {PORTD->PCR[2] &= ~PORT_IRQC_MASK; PORTD->PCR[2] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN34_INTrising()       {PORTD->PCR[2] &= ~PORT_IRQC_MASK; PORTD->PCR[2] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN34_INTany()          {PORTD->PCR[2] &= ~PORT_IRQC_MASK; PORTD->PCR[2] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTD_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTD_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN34_INTclear()        {PORTD->PCR[2] |= 0x01000000;}

/*___PIN 035: PTA3/FTM3_CH1/LPI2C0_SCL/EWM_IN/FXIO_D5/LPUART0_TX/ADC1_SE1_____*/
#define IO_PIN35_toANALOG()        {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[3] &= ~PORT_MUX_MASK;}
#define IO_PIN35_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[3] &= ~PORT_MUX_MASK; PORTA->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_3;}
#define IO_PIN35_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[3] &= ~PORT_MUX_MASK; PORTA->PCR[3] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_3;}
#define IO_PIN35_toHI()            {PTA->PSOR |= PORT_PIN_3;}
#define IO_PIN35_toLO()            {PTA->PCOR |= PORT_PIN_3;}
#define IO_PIN35_TOGGLE()          {PTA->PTOR |= PORT_PIN_3;}
#define IO_PIN35_getINPUT()        {(PTA->PDIR & PORT_PIN_3) >> 3U;}
#define IO_PIN35_isHI()            ((PTA->PDIR & PORT_PIN_3) == PORT_PIN_3)
#define IO_PIN35_isLO()            ((PTA->PDIR & PORT_PIN_3) != PORT_PIN_3)
#define IO_PIN35_PULLoff()         {PORTA->PCR[3] &= ~PORT_PULL_MASK;}
#define IO_PIN35_PULLup()          {PORTA->PCR[3] &= ~PORT_PULL_MASK; PORTA->PCR[3] |= PORT_PULL_UP;}
#define IO_PIN35_PULLdown()        {PORTA->PCR[3] &= ~PORT_PULL_MASK; PORTA->PCR[3] |= PORT_PULL_DOWN;}
#define IO_PIN35_INToff()          {PORTA->PCR[3] &= ~PORT_IRQC_MASK;}
#define IO_PIN35_INTfalling()      {PORTA->PCR[3] &= ~PORT_IRQC_MASK; PORTA->PCR[3] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN35_INTrising()       {PORTA->PCR[3] &= ~PORT_IRQC_MASK; PORTA->PCR[3] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN35_INTany()          {PORTA->PCR[3] &= ~PORT_IRQC_MASK; PORTA->PCR[3] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN35_INTclear()        {PORTA->PCR[3] |= 0x01000000;}

/*___PIN 036: PTA2/FTM3_CH0/LPI2C0_SDA/EWM_OUT_b/FXIO_D4/LPUART0_RX/ADC1_SE0__*/
#define IO_PIN36_toANALOG()        {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[2] &= ~PORT_MUX_MASK;}
#define IO_PIN36_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[2] &= ~PORT_MUX_MASK; PORTA->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_2;}
#define IO_PIN36_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[2] &= ~PORT_MUX_MASK; PORTA->PCR[2] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_2;}
#define IO_PIN36_toHI()            {PTA->PSOR |= PORT_PIN_2;}
#define IO_PIN36_toLO()            {PTA->PCOR |= PORT_PIN_2;}
#define IO_PIN36_TOGGLE()          {PTA->PTOR |= PORT_PIN_2;}
#define IO_PIN36_getINPUT()        {(PTA->PDIR & PORT_PIN_2) >> 2U;}
#define IO_PIN36_isHI()            ((PTA->PDIR & PORT_PIN_2) == PORT_PIN_2)
#define IO_PIN36_isLO()            ((PTA->PDIR & PORT_PIN_2) != PORT_PIN_2)
#define IO_PIN36_PULLoff()         {PORTA->PCR[2] &= ~PORT_PULL_MASK;}
#define IO_PIN36_PULLup()          {PORTA->PCR[2] &= ~PORT_PULL_MASK; PORTA->PCR[2] |= PORT_PULL_UP;}
#define IO_PIN36_PULLdown()        {PORTA->PCR[2] &= ~PORT_PULL_MASK; PORTA->PCR[2] |= PORT_PULL_DOWN;}
#define IO_PIN36_INToff()          {PORTA->PCR[2] &= ~PORT_IRQC_MASK;}
#define IO_PIN36_INTfalling()      {PORTA->PCR[2] &= ~PORT_IRQC_MASK; PORTA->PCR[2] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN36_INTrising()       {PORTA->PCR[2] &= ~PORT_IRQC_MASK; PORTA->PCR[2] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN36_INTany()          {PORTA->PCR[2] &= ~PORT_IRQC_MASK; PORTA->PCR[2] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN36_INTclear()        {PORTA->PCR[2] |= 0x01000000;}

/*___PIN 037: PTA1/FTM1_CH1/LPI2C0_SDAS/FXIO_D3/FTM1_QD_PHA/LPUART0_RTS/TRGMUX_OUT0/ADC0_SE1/CMP0_IN1_*/
#define IO_PIN37_toANALOG()        {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[1] &= ~PORT_MUX_MASK;}
#define IO_PIN37_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[1] &= ~PORT_MUX_MASK; PORTA->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_1;}
#define IO_PIN37_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[1] &= ~PORT_MUX_MASK; PORTA->PCR[1] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_1;}
#define IO_PIN37_toHI()            {PTA->PSOR |= PORT_PIN_1;}
#define IO_PIN37_toLO()            {PTA->PCOR |= PORT_PIN_1;}
#define IO_PIN37_TOGGLE()          {PTA->PTOR |= PORT_PIN_1;}
#define IO_PIN37_getINPUT()        {(PTA->PDIR & PORT_PIN_1) >> 1U;}
#define IO_PIN37_isHI()            ((PTA->PDIR & PORT_PIN_1) == PORT_PIN_1)
#define IO_PIN37_isLO()            ((PTA->PDIR & PORT_PIN_1) != PORT_PIN_1)
#define IO_PIN37_PULLoff()         {PORTA->PCR[1] &= ~PORT_PULL_MASK;}
#define IO_PIN37_PULLup()          {PORTA->PCR[1] &= ~PORT_PULL_MASK; PORTA->PCR[1] |= PORT_PULL_UP;}
#define IO_PIN37_PULLdown()        {PORTA->PCR[1] &= ~PORT_PULL_MASK; PORTA->PCR[1] |= PORT_PULL_DOWN;}
#define IO_PIN37_INToff()          {PORTA->PCR[1] &= ~PORT_IRQC_MASK;}
#define IO_PIN37_INTfalling()      {PORTA->PCR[1] &= ~PORT_IRQC_MASK; PORTA->PCR[1] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN37_INTrising()       {PORTA->PCR[1] &= ~PORT_IRQC_MASK; PORTA->PCR[1] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN37_INTany()          {PORTA->PCR[1] &= ~PORT_IRQC_MASK; PORTA->PCR[1] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN37_INTclear()        {PORTA->PCR[1] |= 0x01000000;}

/*___PIN 038: PTA0/FTM2_CH1/LPI2C0_SCLS/FXIO_D2/FTM2_QD_PHA/LPUART0_CTS/TRGMUX_OUT3/ADC0_SE0/CMP0_IN0_*/
#define IO_PIN38_toANALOG()        {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[0] &= ~PORT_MUX_MASK;}
#define IO_PIN38_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[0] &= ~PORT_MUX_MASK; PORTA->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_0;}
#define IO_PIN38_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[0] &= ~PORT_MUX_MASK; PORTA->PCR[0] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_0;}
#define IO_PIN38_toHI()            {PTA->PSOR |= PORT_PIN_0;}
#define IO_PIN38_toLO()            {PTA->PCOR |= PORT_PIN_0;}
#define IO_PIN38_TOGGLE()          {PTA->PTOR |= PORT_PIN_0;}
#define IO_PIN38_getINPUT()        {(PTA->PDIR & PORT_PIN_0) >> 0U;}
#define IO_PIN38_isHI()            ((PTA->PDIR & PORT_PIN_0) == PORT_PIN_0)
#define IO_PIN38_isLO()            ((PTA->PDIR & PORT_PIN_0) != PORT_PIN_0)
#define IO_PIN38_PULLoff()         {PORTA->PCR[0] &= ~PORT_PULL_MASK;}
#define IO_PIN38_PULLup()          {PORTA->PCR[0] &= ~PORT_PULL_MASK; PORTA->PCR[0] |= PORT_PULL_UP;}
#define IO_PIN38_PULLdown()        {PORTA->PCR[0] &= ~PORT_PULL_MASK; PORTA->PCR[0] |= PORT_PULL_DOWN;}
#define IO_PIN38_INToff()          {PORTA->PCR[0] &= ~PORT_IRQC_MASK;}
#define IO_PIN38_INTfalling()      {PORTA->PCR[0] &= ~PORT_IRQC_MASK; PORTA->PCR[0] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN38_INTrising()       {PORTA->PCR[0] &= ~PORT_IRQC_MASK; PORTA->PCR[0] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN38_INTany()          {PORTA->PCR[0] &= ~PORT_IRQC_MASK; PORTA->PCR[0] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN38_INTclear()        {PORTA->PCR[0] |= 0x01000000;}

/*___PIN 039: PTC7/LPUART1_TX/CAN1_TX/FTM3_CH3/FTM1_QD_PHA/ADC1_SE5___________*/
#define IO_PIN39_toANALOG()        {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[7] &= ~PORT_MUX_MASK;}
#define IO_PIN39_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[7] &= ~PORT_MUX_MASK; PORTC->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_7;}
#define IO_PIN39_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[7] &= ~PORT_MUX_MASK; PORTC->PCR[7] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_7;}
#define IO_PIN39_toHI()            {PTC->PSOR |= PORT_PIN_7;}
#define IO_PIN39_toLO()            {PTC->PCOR |= PORT_PIN_7;}
#define IO_PIN39_TOGGLE()          {PTC->PTOR |= PORT_PIN_7;}
#define IO_PIN39_getINPUT()        {(PTC->PDIR & PORT_PIN_7) >> 7U;}
#define IO_PIN39_isHI()            ((PTC->PDIR & PORT_PIN_7) == PORT_PIN_7)
#define IO_PIN39_isLO()            ((PTC->PDIR & PORT_PIN_7) != PORT_PIN_7)
#define IO_PIN39_PULLoff()         {PORTC->PCR[7] &= ~PORT_PULL_MASK;}
#define IO_PIN39_PULLup()          {PORTC->PCR[7] &= ~PORT_PULL_MASK; PORTC->PCR[7] |= PORT_PULL_UP;}
#define IO_PIN39_PULLdown()        {PORTC->PCR[7] &= ~PORT_PULL_MASK; PORTC->PCR[7] |= PORT_PULL_DOWN;}
#define IO_PIN39_INToff()          {PORTC->PCR[7] &= ~PORT_IRQC_MASK;}
#define IO_PIN39_INTfalling()      {PORTC->PCR[7] &= ~PORT_IRQC_MASK; PORTC->PCR[7] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN39_INTrising()       {PORTC->PCR[7] &= ~PORT_IRQC_MASK; PORTC->PCR[7] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN39_INTany()          {PORTC->PCR[7] &= ~PORT_IRQC_MASK; PORTC->PCR[7] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN39_INTclear()        {PORTC->PCR[7] |= 0x01000000;}

/*___PIN 040: PTC6/LPUART1_RX/CAN1_RX/FTM3_CH2/FTM1_QD_PHB/ADC1_SE4___________*/
#define IO_PIN40_toANALOG()        {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[6] &= ~PORT_MUX_MASK;}
#define IO_PIN40_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[6] &= ~PORT_MUX_MASK; PORTC->PCR[6] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_6;}
#define IO_PIN40_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[6] &= ~PORT_MUX_MASK; PORTC->PCR[6] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_6;}
#define IO_PIN40_toHI()            {PTC->PSOR |= PORT_PIN_6;}
#define IO_PIN40_toLO()            {PTC->PCOR |= PORT_PIN_6;}
#define IO_PIN40_TOGGLE()          {PTC->PTOR |= PORT_PIN_6;}
#define IO_PIN40_getINPUT()        {(PTC->PDIR & PORT_PIN_6) >> 6U;}
#define IO_PIN40_isHI()            ((PTC->PDIR & PORT_PIN_6) == PORT_PIN_6)
#define IO_PIN40_isLO()            ((PTC->PDIR & PORT_PIN_6) != PORT_PIN_6)
#define IO_PIN40_PULLoff()         {PORTC->PCR[6] &= ~PORT_PULL_MASK;}
#define IO_PIN40_PULLup()          {PORTC->PCR[6] &= ~PORT_PULL_MASK; PORTC->PCR[6] |= PORT_PULL_UP;}
#define IO_PIN40_PULLdown()        {PORTC->PCR[6] &= ~PORT_PULL_MASK; PORTC->PCR[6] |= PORT_PULL_DOWN;}
#define IO_PIN40_INToff()          {PORTC->PCR[6] &= ~PORT_IRQC_MASK;}
#define IO_PIN40_INTfalling()      {PORTC->PCR[6] &= ~PORT_IRQC_MASK; PORTC->PCR[6] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN40_INTrising()       {PORTC->PCR[6] &= ~PORT_IRQC_MASK; PORTC->PCR[6] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN40_INTany()          {PORTC->PCR[6] &= ~PORT_IRQC_MASK; PORTC->PCR[6] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN40_INTclear()        {PORTC->PCR[6] |= 0x01000000;}

/*___PIN 041: PTA13/FTM1_CH7/CAN1_TX/FTM2_QD_PHA______________________________*/
#define IO_PIN41_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[13] &= ~PORT_MUX_MASK; PORTA->PCR[13] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_13;}
#define IO_PIN41_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[13] &= ~PORT_MUX_MASK; PORTA->PCR[13] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_13;}
#define IO_PIN41_toHI()            {PTA->PSOR |= PORT_PIN_13;}
#define IO_PIN41_toLO()            {PTA->PCOR |= PORT_PIN_13;}
#define IO_PIN41_TOGGLE()          {PTA->PTOR |= PORT_PIN_13;}
#define IO_PIN41_getINPUT()        {(PTA->PDIR & PORT_PIN_13) >> 13U;}
#define IO_PIN41_isHI()            ((PTA->PDIR & PORT_PIN_13) == PORT_PIN_13)
#define IO_PIN41_isLO()            ((PTA->PDIR & PORT_PIN_13) != PORT_PIN_13)
#define IO_PIN41_PULLoff()         {PORTA->PCR[13] &= ~PORT_PULL_MASK;}
#define IO_PIN41_PULLup()          {PORTA->PCR[13] &= ~PORT_PULL_MASK; PORTA->PCR[13] |= PORT_PULL_UP;}
#define IO_PIN41_PULLdown()        {PORTA->PCR[13] &= ~PORT_PULL_MASK; PORTA->PCR[13] |= PORT_PULL_DOWN;}
#define IO_PIN41_INToff()          {PORTA->PCR[13] &= ~PORT_IRQC_MASK;}
#define IO_PIN41_INTfalling()      {PORTA->PCR[13] &= ~PORT_IRQC_MASK; PORTA->PCR[13] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN41_INTrising()       {PORTA->PCR[13] &= ~PORT_IRQC_MASK; PORTA->PCR[13] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN41_INTany()          {PORTA->PCR[13] &= ~PORT_IRQC_MASK; PORTA->PCR[13] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN41_INTclear()        {PORTA->PCR[13] |= 0x01000000;}

/*___PIN 042: PTA12/FTM1_CH6/CAN1_RX/FTM2_QD_PHB______________________________*/
#define IO_PIN42_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[12] &= ~PORT_MUX_MASK; PORTA->PCR[12] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_12;}
#define IO_PIN42_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[12] &= ~PORT_MUX_MASK; PORTA->PCR[12] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_12;}
#define IO_PIN42_toHI()            {PTA->PSOR |= PORT_PIN_12;}
#define IO_PIN42_toLO()            {PTA->PCOR |= PORT_PIN_12;}
#define IO_PIN42_TOGGLE()          {PTA->PTOR |= PORT_PIN_12;}
#define IO_PIN42_getINPUT()        {(PTA->PDIR & PORT_PIN_12) >> 12U;}
#define IO_PIN42_isHI()            ((PTA->PDIR & PORT_PIN_12) == PORT_PIN_12)
#define IO_PIN42_isLO()            ((PTA->PDIR & PORT_PIN_12) != PORT_PIN_12)
#define IO_PIN42_PULLoff()         {PORTA->PCR[12] &= ~PORT_PULL_MASK;}
#define IO_PIN42_PULLup()          {PORTA->PCR[12] &= ~PORT_PULL_MASK; PORTA->PCR[12] |= PORT_PULL_UP;}
#define IO_PIN42_PULLdown()        {PORTA->PCR[12] &= ~PORT_PULL_MASK; PORTA->PCR[12] |= PORT_PULL_DOWN;}
#define IO_PIN42_INToff()          {PORTA->PCR[12] &= ~PORT_IRQC_MASK;}
#define IO_PIN42_INTfalling()      {PORTA->PCR[12] &= ~PORT_IRQC_MASK; PORTA->PCR[12] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN42_INTrising()       {PORTA->PCR[12] &= ~PORT_IRQC_MASK; PORTA->PCR[12] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN42_INTany()          {PORTA->PCR[12] &= ~PORT_IRQC_MASK; PORTA->PCR[12] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN42_INTclear()        {PORTA->PCR[12] |= 0x01000000;}

/*___PIN 043: PTA11/FTM1_CH5/FXIO_D1/CMP0_RRT_________________________________*/
#define IO_PIN43_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[11] &= ~PORT_MUX_MASK; PORTA->PCR[11] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_11;}
#define IO_PIN43_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[11] &= ~PORT_MUX_MASK; PORTA->PCR[11] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_11;}
#define IO_PIN43_toHI()            {PTA->PSOR |= PORT_PIN_11;}
#define IO_PIN43_toLO()            {PTA->PCOR |= PORT_PIN_11;}
#define IO_PIN43_TOGGLE()          {PTA->PTOR |= PORT_PIN_11;}
#define IO_PIN43_getINPUT()        {(PTA->PDIR & PORT_PIN_11) >> 11U;}
#define IO_PIN43_isHI()            ((PTA->PDIR & PORT_PIN_11) == PORT_PIN_11)
#define IO_PIN43_isLO()            ((PTA->PDIR & PORT_PIN_11) != PORT_PIN_11)
#define IO_PIN43_PULLoff()         {PORTA->PCR[11] &= ~PORT_PULL_MASK;}
#define IO_PIN43_PULLup()          {PORTA->PCR[11] &= ~PORT_PULL_MASK; PORTA->PCR[11] |= PORT_PULL_UP;}
#define IO_PIN43_PULLdown()        {PORTA->PCR[11] &= ~PORT_PULL_MASK; PORTA->PCR[11] |= PORT_PULL_DOWN;}
#define IO_PIN43_INToff()          {PORTA->PCR[11] &= ~PORT_IRQC_MASK;}
#define IO_PIN43_INTfalling()      {PORTA->PCR[11] &= ~PORT_IRQC_MASK; PORTA->PCR[11] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN43_INTrising()       {PORTA->PCR[11] &= ~PORT_IRQC_MASK; PORTA->PCR[11] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN43_INTany()          {PORTA->PCR[11] &= ~PORT_IRQC_MASK; PORTA->PCR[11] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN43_INTclear()        {PORTA->PCR[11] |= 0x01000000;}

/*___PIN 044: PTA10/FTM1_CH4/FXIO_D0/JTAG_TDO/noetm_TRACE_SWO_________________*/
#define IO_PIN44_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[10] &= ~PORT_MUX_MASK; PORTA->PCR[10] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_10;}
#define IO_PIN44_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[10] &= ~PORT_MUX_MASK; PORTA->PCR[10] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_10;}
#define IO_PIN44_toHI()            {PTA->PSOR |= PORT_PIN_10;}
#define IO_PIN44_toLO()            {PTA->PCOR |= PORT_PIN_10;}
#define IO_PIN44_TOGGLE()          {PTA->PTOR |= PORT_PIN_10;}
#define IO_PIN44_getINPUT()        {(PTA->PDIR & PORT_PIN_10) >> 10U;}
#define IO_PIN44_isHI()            ((PTA->PDIR & PORT_PIN_10) == PORT_PIN_10)
#define IO_PIN44_isLO()            ((PTA->PDIR & PORT_PIN_10) != PORT_PIN_10)
#define IO_PIN44_PULLoff()         {PORTA->PCR[10] &= ~PORT_PULL_MASK;}
#define IO_PIN44_PULLup()          {PORTA->PCR[10] &= ~PORT_PULL_MASK; PORTA->PCR[10] |= PORT_PULL_UP;}
#define IO_PIN44_PULLdown()        {PORTA->PCR[10] &= ~PORT_PULL_MASK; PORTA->PCR[10] |= PORT_PULL_DOWN;}
#define IO_PIN44_INToff()          {PORTA->PCR[10] &= ~PORT_IRQC_MASK;}
#define IO_PIN44_INTfalling()      {PORTA->PCR[10] &= ~PORT_IRQC_MASK; PORTA->PCR[10] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN44_INTrising()       {PORTA->PCR[10] &= ~PORT_IRQC_MASK; PORTA->PCR[10] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN44_INTany()          {PORTA->PCR[10] &= ~PORT_IRQC_MASK; PORTA->PCR[10] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN44_INTclear()        {PORTA->PCR[10] |= 0x01000000;}

/*___PIN 045: PTC5/FTM2_CH0/RTC_CLKOUT/FTM2_QD_PHB/JTAG_TDI___________________*/
#define IO_PIN45_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[5] &= ~PORT_MUX_MASK; PORTC->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_5;}
#define IO_PIN45_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[5] &= ~PORT_MUX_MASK; PORTC->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_5;}
#define IO_PIN45_toHI()            {PTC->PSOR |= PORT_PIN_5;}
#define IO_PIN45_toLO()            {PTC->PCOR |= PORT_PIN_5;}
#define IO_PIN45_TOGGLE()          {PTC->PTOR |= PORT_PIN_5;}
#define IO_PIN45_getINPUT()        {(PTC->PDIR & PORT_PIN_5) >> 5U;}
#define IO_PIN45_isHI()            ((PTC->PDIR & PORT_PIN_5) == PORT_PIN_5)
#define IO_PIN45_isLO()            ((PTC->PDIR & PORT_PIN_5) != PORT_PIN_5)
#define IO_PIN45_PULLoff()         {PORTC->PCR[5] &= ~PORT_PULL_MASK;}
#define IO_PIN45_PULLup()          {PORTC->PCR[5] &= ~PORT_PULL_MASK; PORTC->PCR[5] |= PORT_PULL_UP;}
#define IO_PIN45_PULLdown()        {PORTC->PCR[5] &= ~PORT_PULL_MASK; PORTC->PCR[5] |= PORT_PULL_DOWN;}
#define IO_PIN45_INToff()          {PORTC->PCR[5] &= ~PORT_IRQC_MASK;}
#define IO_PIN45_INTfalling()      {PORTC->PCR[5] &= ~PORT_IRQC_MASK; PORTC->PCR[5] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN45_INTrising()       {PORTC->PCR[5] &= ~PORT_IRQC_MASK; PORTC->PCR[5] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN45_INTany()          {PORTC->PCR[5] &= ~PORT_IRQC_MASK; PORTC->PCR[5] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN45_INTclear()        {PORTC->PCR[5] |= 0x01000000;}

/*___PIN 046: PTC4/FTM1_CH0/RTC_CLKOUT/EWM_IN/FTM1_QD_PHB/JTAG_TCLK/SWD_CLK/CMP0_IN2_*/
#define IO_PIN46_toOUT()           {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[4] &= ~PORT_MUX_MASK; PORTC->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR |= PORT_PIN_4;}
#define IO_PIN46_toIN()            {PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; PORTC->PCR[4] &= ~PORT_MUX_MASK; PORTC->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTC->PDDR &= ~PORT_PIN_4;}
#define IO_PIN46_toHI()            {PTC->PSOR |= PORT_PIN_4;}
#define IO_PIN46_toLO()            {PTC->PCOR |= PORT_PIN_4;}
#define IO_PIN46_TOGGLE()          {PTC->PTOR |= PORT_PIN_4;}
#define IO_PIN46_getINPUT()        {(PTC->PDIR & PORT_PIN_4) >> 4U;}
#define IO_PIN46_isHI()            ((PTC->PDIR & PORT_PIN_4) == PORT_PIN_4)
#define IO_PIN46_isLO()            ((PTC->PDIR & PORT_PIN_4) != PORT_PIN_4)
#define IO_PIN46_PULLoff()         {PORTC->PCR[4] &= ~PORT_PULL_MASK;}
#define IO_PIN46_PULLup()          {PORTC->PCR[4] &= ~PORT_PULL_MASK; PORTC->PCR[4] |= PORT_PULL_UP;}
#define IO_PIN46_PULLdown()        {PORTC->PCR[4] &= ~PORT_PULL_MASK; PORTC->PCR[4] |= PORT_PULL_DOWN;}
#define IO_PIN46_INToff()          {PORTC->PCR[4] &= ~PORT_IRQC_MASK;}
#define IO_PIN46_INTfalling()      {PORTC->PCR[4] &= ~PORT_IRQC_MASK; PORTC->PCR[4] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN46_INTrising()       {PORTC->PCR[4] &= ~PORT_IRQC_MASK; PORTC->PCR[4] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN46_INTany()          {PORTC->PCR[4] &= ~PORT_IRQC_MASK; PORTC->PCR[4] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTC_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTC_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN46_INTclear()        {PORTC->PCR[4] |= 0x01000000;}

/*___PIN 047: PTA5/TCLK1/RESET_b______________________________________________*/
#define IO_PIN47_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[5] &= ~PORT_MUX_MASK; PORTA->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_5;}
#define IO_PIN47_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[5] &= ~PORT_MUX_MASK; PORTA->PCR[5] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_5;}
#define IO_PIN47_toHI()            {PTA->PSOR |= PORT_PIN_5;}
#define IO_PIN47_toLO()            {PTA->PCOR |= PORT_PIN_5;}
#define IO_PIN47_TOGGLE()          {PTA->PTOR |= PORT_PIN_5;}
#define IO_PIN47_getINPUT()        {(PTA->PDIR & PORT_PIN_5) >> 5U;}
#define IO_PIN47_isHI()            ((PTA->PDIR & PORT_PIN_5) == PORT_PIN_5)
#define IO_PIN47_isLO()            ((PTA->PDIR & PORT_PIN_5) != PORT_PIN_5)
#define IO_PIN47_PULLoff()         {PORTA->PCR[5] &= ~PORT_PULL_MASK;}
#define IO_PIN47_PULLup()          {PORTA->PCR[5] &= ~PORT_PULL_MASK; PORTA->PCR[5] |= PORT_PULL_UP;}
#define IO_PIN47_PULLdown()        {PORTA->PCR[5] &= ~PORT_PULL_MASK; PORTA->PCR[5] |= PORT_PULL_DOWN;}
#define IO_PIN47_INToff()          {PORTA->PCR[5] &= ~PORT_IRQC_MASK;}
#define IO_PIN47_INTfalling()      {PORTA->PCR[5] &= ~PORT_IRQC_MASK; PORTA->PCR[5] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN47_INTrising()       {PORTA->PCR[5] &= ~PORT_IRQC_MASK; PORTA->PCR[5] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN47_INTany()          {PORTA->PCR[5] &= ~PORT_IRQC_MASK; PORTA->PCR[5] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN47_INTclear()        {PORTA->PCR[5] |= 0x01000000;}

/*___PIN 048: PTA4/CMP0_OUT/EWM_OUT_b/JTAG_TMS/SWD_DIO________________________*/
#define IO_PIN48_toOUT()           {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[4] &= ~PORT_MUX_MASK; PORTA->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR |= PORT_PIN_4;}
#define IO_PIN48_toIN()            {PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; PORTA->PCR[4] &= ~PORT_MUX_MASK; PORTA->PCR[4] |= PORT_MUX_PIN_ALT1_GPIO; PTA->PDDR &= ~PORT_PIN_4;}
#define IO_PIN48_toHI()            {PTA->PSOR |= PORT_PIN_4;}
#define IO_PIN48_toLO()            {PTA->PCOR |= PORT_PIN_4;}
#define IO_PIN48_TOGGLE()          {PTA->PTOR |= PORT_PIN_4;}
#define IO_PIN48_getINPUT()        {(PTA->PDIR & PORT_PIN_4) >> 4U;}
#define IO_PIN48_isHI()            ((PTA->PDIR & PORT_PIN_4) == PORT_PIN_4)
#define IO_PIN48_isLO()            ((PTA->PDIR & PORT_PIN_4) != PORT_PIN_4)
#define IO_PIN48_PULLoff()         {PORTA->PCR[4] &= ~PORT_PULL_MASK;}
#define IO_PIN48_PULLup()          {PORTA->PCR[4] &= ~PORT_PULL_MASK; PORTA->PCR[4] |= PORT_PULL_UP;}
#define IO_PIN48_PULLdown()        {PORTA->PCR[4] &= ~PORT_PULL_MASK; PORTA->PCR[4] |= PORT_PULL_DOWN;}
#define IO_PIN48_INToff()          {PORTA->PCR[4] &= ~PORT_IRQC_MASK;}
#define IO_PIN48_INTfalling()      {PORTA->PCR[4] &= ~PORT_IRQC_MASK; PORTA->PCR[4] |= PORT_IRQC_FALLING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN48_INTrising()       {PORTA->PCR[4] &= ~PORT_IRQC_MASK; PORTA->PCR[4] |= PORT_IRQC_RISING; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN48_INTany()          {PORTA->PCR[4] &= ~PORT_IRQC_MASK; PORTA->PCR[4] |= PORT_IRQC_EITHER; S32_NVIC->ISER[(uint32_t)(PORTA_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(PORTA_IRQn) & (uint32_t)0x1FU));}
#define IO_PIN48_INTclear()        {PORTA->PCR[4] |= 0x01000000;}


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
