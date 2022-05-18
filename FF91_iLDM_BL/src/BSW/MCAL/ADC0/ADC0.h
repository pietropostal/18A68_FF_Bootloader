/*
 *    JANI HOVAN, COPYRIGHT (c) 2020
 *    ALL RIGHTS RESERVED
 */

/**
* \file ADC0.h
* \ingroup grpXXX
* \brief ADC0 driver implementation of S32K144.
* \version 1.0.0
* \author Jani Hovan
* \date 2020-10-04
*/

#ifndef ADC0_H_
#define ADC0_H_

/* === INCLUDES ============================================================= */
#include "board.h"
#include "ADC.h"      /* common data for all ADCs */

/* === TYPEDEFS ============================================================= */
/* none */
/* === SYMBOLIC CONSTANTS =================================================== */
/* none */
/* === EXPORTED MACROS ====================================================== */
/* none */
/* === EXPORTED VARIABLES =================================================== */
extern uint16_t ADC0_aResults[ ADC_CHANNEL_AMOUNT ];

/* === EXPORTED FUNCTIONS =================================================== */
extern void ADC0_vInit( void );
extern void ADC0_vMain( void );
extern void ADC0_vConvertChannelWithInterrupt( eADC_SC1A_ADCH_t argAdcChannel );
extern void ADC0_InterruptCallback( void );

#endif /* ADC0_H_ */
