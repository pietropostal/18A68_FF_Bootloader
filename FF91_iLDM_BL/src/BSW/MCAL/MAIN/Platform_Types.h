/*******************************************************************************
** Copyright (c) 2019 Embitel
**
** This software is the property of Embitel.
** It can not be used or duplicated without Embitel authorization.
**
** -----------------------------------------------------------------------------
** File Name    : Platform_Types.h
** Module name  : Platform Module
** -----------------------------------------------------------------------------
** Description  : Platform Module for Embitel Project.
**
** -----------------------------------------------------------------------------
**
** Documentation reference :
**
********************************************************************************
** R E V I S I O N  H I S T O R Y
********************************************************************************
** V01.00 03/09/2018
** - Baseline Created
**
*******************************************************************************/

#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

/* Controller Header */
#include "device_registers.h"
#include "Compiler.h"
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
typedef unsigned char		uint8_t;    /**< \brief  8 bit unsigned value */
typedef unsigned short int  uint16_t;   /**< \brief 16 bit unsigned value */
typedef unsigned long int   uint32_t;   /**< \brief 32 bit unsigned value */


typedef signed char int8_t;             /**< \brief  8 bit signed value */
typedef short int   int16_t;            /**< \brief 16 bit signed value */
typedef long int    int32_t;            /**< \brief 32 bit signed value */

typedef unsigned char uint8;           /**< \brief 8 bit unsigned value  */
typedef unsigned short uint16;         /**< \brief 16 bit unsigned value */
typedef unsigned long uint32;           /**< \brief 32 bit unsigned value */
typedef unsigned long long  uint64;		/**< \brief 64 bit unsigned value */

typedef unsigned char       boolean;    /**< \brief for use with TRUE/FALSE */

/*******************************************************************************
**                      Global  Definitions                               **
*******************************************************************************/
#ifndef TRUE
#define TRUE 							1u
#endif
#ifndef FALSE
#define FALSE 							0u
#endif
#ifndef NULL
#define NULL_PTR ((void *)0)
#endif
//#define NULL							(void *)0u

// For testing on development board
//   1. Enable Test Pin direction
//   2. Requested Respective testing
//   3. Do not enable multiple testing together

#define ENABLE_TEST_PIN_DIR 		// Enable Test Pin Direction
//#define TEST_WDT_RESET 			// Block code
#define TEST_CAN_TX_BOARD   		// Enable CAN Tx from scheduler
//define TEST_TIMER_INTERRUPT_BOARD // Test Timer interrupt

#endif /* _TYPEDEFS_H_ */
