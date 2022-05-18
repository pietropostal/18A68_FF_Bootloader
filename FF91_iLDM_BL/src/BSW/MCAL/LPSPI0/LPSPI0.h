/*
 *    JANI HOVAN, COPYRIGHT (c) 2020
 *    ALL RIGHTS RESERVED
 */

/**
* \file LPSPI0.h
* \ingroup grpXXX
* \brief SPI0 lo-level driver for S32K144 (NXP).
* \version 1.0.0
* \author Jani Hovan
* \date 2020-10-04
*/

#ifndef LPSPI0_H_
#define LPSPI0_H_

/* === INCLUDES ============================================================= */
#include "LPSPI.h"   /* strLPSPI_config_t */

/* === TYPEDEFS ============================================================= */
/* none */
/* === SYMBOLIC CONSTANTS =================================================== */
/* none */
/* === EXPORTED MACROS ====================================================== */
/* none */
/* === EXPORTED VARIABLES =================================================== */
/* none */
/* === EXPORTED FUNCTIONS =================================================== */
extern void LPSPI0_vInit( const strLPSPI_config_t * argConfig );
extern void LPSPI0_vMain( void );

extern void LPSPI0_vSendReceive8bitBlocking( uint8_t   argSendData, uint8_t *  pargRetVal );
extern void LPSPI0_vSendReceive16bitBlocking( uint16_t argSendData, uint16_t * pargRetVal );
extern void LPSPI0_vSendReceive32bitBlocking( uint32_t argSendData, uint32_t * pargRetVal );

extern void LPSPI0_vSendReceive8bitBuff( const uint8_t *  argSendBuff, uint8_t *  pargRetBuff, uint8_t argAmount );

#endif /* LPSPI0_H_ */
