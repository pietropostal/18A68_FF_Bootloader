/*
 *    JANI HOVAN, COPYRIGHT (c) 2020
 *    ALL RIGHTS RESERVED
 */

/**
* \file UJA1075A.h
* \ingroup grpXXX
* \brief Driver for NXP UJA1075A CAN/LIN-SBC.
* \version 1.0.0
* \author Jani Hovan
* \date 2020-11-18
*/

#ifndef __UJA1075A_H
#define __UJA1075A_H

/* === INCLUDES ============================================================= */
#include "board.h"

/* === TYPEDEFS ============================================================= */

/*___WD_And_Status_Register___________________________________________________*/
typedef union
{
    uint16_t  reg;
    struct
    {
        uint16_t               : 3;  /* reserved */
        uint16_t   WLS2        : 1;  /* wake-up 2 status */
        uint16_t   WLS1        : 1;  /* wake-up 1 status */
        uint16_t   V2S         : 1;  /* V2 status */
        uint16_t   V1S         : 1;  /* V1 status */
        uint16_t   WOS_SWR     : 1;  /* watchdog off status / software reset */
        uint16_t   NWP         : 3;  /* nominal watchdog period */
        uint16_t   WMC         : 1;  /* watchdog mode control */
        uint16_t   RO          : 1;  /* RO (read-only-bit) */
        uint16_t   ADDR        : 3;  /* Address of register */
    }bits;
}uUJA1075A_REG_WD_And_Status_Register_t;

/*___Mode_Control_Register____________________________________________________*/
typedef union
{
    uint16_t  reg;
    struct
    {
        uint16_t               : 4;  /* reserved */
        uint16_t   PDC         : 1;  /* power distribution control */
        uint16_t   WBC         : 1;  /* wake bias control */
        uint16_t   LSC         : 1;  /* LIN slope control */
        uint16_t   ENC         : 1;  /* enable control */
        uint16_t   LHC         : 1;  /* limp home control */
        uint16_t   LHWC        : 1;  /* limp home warning control */
        uint16_t   MC          : 2;  /* mode control */
        uint16_t   RO          : 1;  /* RO (read-only-bit) */
        uint16_t   ADDR        : 3;  /* Address of register */
    }bits;
}uUJA1075A_REG_Mode_Control_Register_t;

/*___Int_Control_Register_____________________________________________________*/
typedef union
{
    uint16_t  reg;
    struct
    {
        uint16_t   WSE2        : 1;  /* WAKE2 sample enable */
        uint16_t   WSE1        : 1;  /* WAKE1 sample enable */
        uint16_t   RTHC        : 1;  /* reset threshold control */
        uint16_t   STBCC       : 1;  /* CAN standby control */
        uint16_t   WIC2        : 2;  /* wake-up interrupt 2 control */
        uint16_t   WIC1        : 2;  /* wake-up interrupt 1 control */
        uint16_t               : 1;  /* reserved */
        uint16_t   STBCL       : 1;  /* LIN is in lowpower mode, wake-up detection enabled */
        uint16_t   V2UIE       : 1;  /* V2 undervoltage interrupt can be requested */
        uint16_t   V1UIE       : 1;  /* V1 undervoltage interrupt can be requested */
        uint16_t   RO          : 1;  /* RO (read-only-bit) */
        uint16_t   ADDR        : 3;  /* Address of register */
    }bits;
}uUJA1075A_REG_Int_Control_Register_t;

/*___Int_Status_Register______________________________________________________*/
typedef union
{
    uint16_t  reg;
    struct
    {
        uint16_t               : 3;  /* reserved */
        uint16_t   CWI         : 1;  /* CAN wake-up interrupt pending */
        uint16_t   WI2         : 1;  /* wake-up interrupt 2 pending */
        uint16_t   POSI        : 1;  /* power-on status interrupt pending */
        uint16_t   WI1         : 1;  /* wake-up interrupt 1 pending */
        uint16_t   CI          : 1;  /* cyclic interrupt pending */
        uint16_t               : 1;  /* reserved */
        uint16_t   LWI         : 1;  /* LIN wake-up interrupt pending */
        uint16_t   V2UI        : 1;  /* V2 undervoltage warning interrupt pending */
        uint16_t   V1UI        : 1;  /* V1 undervoltage warning interrupt pending */
        uint16_t   RO          : 1;  /* RO (read-only-bit) */
        uint16_t   ADDR        : 3;  /* Address of register */
    }bits;
}uUJA1075A_REG_Int_Status_Register_t;


/* Watchdog period */
typedef enum
{
     UJA1075A_WDPERIOD_8ms = 0  /* Watchdog period 8ms */
    ,UJA1075A_WDPERIOD_16ms     /* Watchdog period 16ms */
	,UJA1075A_WDPERIOD_32ms     /* Watchdog period 32ms */
	,UJA1075A_WDPERIOD_64ms     /* Watchdog period 64ms */
	,UJA1075A_WDPERIOD_128ms    /* Watchdog period 128ms (default) */
	,UJA1075A_WDPERIOD_256ms    /* Watchdog period 256ms */
	,UJA1075A_WDPERIOD_1024ms   /* Watchdog period 1024ms */
	,UJA1075A_WDPERIOD_4096ms   /* Watchdog period 4096ms */

	,UJA1075A_WDPERIOD_AMOUNT
} eUJA1075A_WatchdogPeriod;

/* === SYMBOLIC CONSTANTS =================================================== */
#define UJA1075A__REGADDR__WATCHDOG_AND_STATUS_REG      0U
#define UJA1075A__REGADDR__MODE_CONTROL_REG             1U
#define UJA1075A__REGADDR__INTERRUPT_CONTROL_REG        2U
#define UJA1075A__REGADDR__INTERRUPT_STATUS_REG         3U
#define UJA1075A__RO_ReadWrite                          0U
#define UJA1075A__RO_ReadOnly                           1U
#define UJA1075A__MC_StandbyMode                        0U
#define UJA1075A__MC_SleepMode                          1U
#define UJA1975A__MC_NormalModeV2off                    2U
#define UJA1075A__MC_NormalModeV2on                     3U

/* === EXPORTED MACROS ====================================================== */
/* none */
/* === EXPORTED VARIABLES =================================================== */
/* none */
/* === EXPORTED FUNCTIONS =================================================== */
extern void UJA1075A_vInit(void);
extern void UJA1075A_vMain(void);

extern void UJA1075A_CMD_setNormal(void);
extern void UJA1075A_CMD_setSleep(void);
extern void UJA1075A_CMD_setStandby(void);
extern void UJA1075A_CMD_performWatchdogReset(void);

#endif /* __UJA1075A_H */
