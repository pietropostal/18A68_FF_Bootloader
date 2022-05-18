/*
 *    JANI HOVAN, COPYRIGHT (c) 2020
 *    ALL RIGHTS RESERVED
 */

/**
* \file board.h
* \ingroup grpXXX
* \brief Board (PCB) specific defines and configurations.
* \version 1.0.0
* \author Jani Hovan
* \date 2020-10-04
*/

#ifndef __BOARD_H
#define __BOARD_H

/* === INCLUDES ============================================================= */
#include "S32K144.h"           /* Include the derivative-specific header file */
#include "fsl_core_cm4.h"      /* ENABLE_INTERRUPTS(); DISABLE_INTERRUPTS() */

#define S32K144_48PIN               /* 48pin LQFP */
//#define S32K144_64PIN               /* 48pin LQFP */
//#define S32K144_100PIN              /* 100pin LQFP */

#if defined S32K144_48PIN
    #include "IO_S32K144_48pin_LQFP.h"    /* Register-Definitions for the MCU */
#elif defined S32K144_64PIN
    #include "IO_S32K144_64pin_LQFP.h"    /* Register-Definitions for the MCU */
#elif defined S32K144_100PIN
    #include "IO_S32K144_100pin_LQFP.h"   /* Register-Definitions for the MCU */
#endif

#include "myTypes.h"

/* === TYPEDEFS ============================================================= */
/* none */
/* === SYMBOLIC CONSTANTS =================================================== */
#if defined(__GNUC__)   // LPCXpresso Tools
  #define PRE_PACK
  #define POST_PACK     __attribute__((packed))
#else                   // Other toolchain
  #define PRE_PACK      __packed
  #define POST_PACK
#endif

/* === EXPORTED MACROS ====================================================== */
#define EXT_OSC_USED          1U    /* external oscillator used? 0:NO 1:YES */
#define CLOCK_EXT_OSC__MHZ    8U    /* frequency of external oscillator [MHz] */
#define CLOCK_CORE__MHZ       80U   /* frequency of core-clock [MHz] */
#define SPLL_CLK__MHZ         80U   /* frequency of PLL-clock [MHz] */
#define SPLLDIV1_CLK__		  80U   /* asynchronous peripheral sources */
#define SPLLDIV2_CLK__        40U   /* asynchronous peripheral sources */
#define CLOCK_BUS__MHZ        (CLOCK_CORE__MHZ >> 1) /* div by 2 */              //unused by now !!!!!!!!!!!!!!!!!!


#define EnableAllInterrupts()      ENABLE_INTERRUPTS()
#define DisableAllInterrupts()     DISABLE_INTERRUPTS()

#define NOP()                      __asm volatile ("nop")


#define REGULATION_SAE
//#define REGULATION_ECE_CCC

//#define FREEDOMBOARD_144K
#define iLDM


/* IO-Definitions */

#if defined FREEDOMBOARD_144K

#define FRDM144K_LED_B_toOUT()     IO_PIN2_toOUT() //PORTD0
#define FRDM144K_LED_B_TOGGLE()    IO_PIN2_TOGGLE()

#define FRDM144K_LED_R_toOUT()     IO_PIN11_toOUT()  //PORTD15
#define FRDM144K_LED_R_TOGGLE()    IO_PIN11_TOGGLE()

#endif

#if defined iLDM

#define MCU_LEDD_ENA_toOUT()         IO_PIN10_toOUT()
#define MCU_LEDD_ENA_doENABLE()      IO_PIN10_toHI()
#define MCU_LEDD_ENA_doDISABLE()     IO_PIN10_toLO()

#define SPI_CS_POTI_toOUT()          IO_PIN11_toOUT()
#define SPI_CS_POTI_doACTIVATE()     IO_PIN11_toLO()
#define SPI_CS_POTI_doDEACTIVATE()   IO_PIN11_toHI()

#define MCU_24V0_ENABLE_toOUT()      IO_PIN13_toOUT()
#define MCU_24V0_ENABLE_doENABLE()   IO_PIN13_toHI()
#define MCU_24V0_ENABLE_doDISABLE()  IO_PIN13_toLO()

#define MCU_24V0_SYNC_toOUT()        IO_PIN3_toOUT()
#define MCU_24V0_SYNC_toHI()         IO_PIN3_toHI()
#define MCU_24V0_SYNC_toLO()         IO_PIN3_toLO()

#define MCU_24V0_PGOOD_toIN()        IO_PIN12_toIN()
#define MCU_24V0_PGOOD_isLO()        IO_PIN12_isLO()

#define MCU_LEDA_ENA_toOUT()         IO_PIN18_toOUT()
#define MCU_LEDA_ENA_doENABLE()      IO_PIN18_toHI()
#define MCU_LEDA_ENA_doDISABLE()     IO_PIN18_toLO()

#define MCU_LWC_ENA_toOUT()          IO_PIN28_toOUT()
#define MCU_LWC_ENA_doENABLE()       IO_PIN28_toHI()
#define MCU_LWC_ENA_doDISABLE()      IO_PIN28_toLO()

#define MCU_LWC_ST_toIN()            IO_PIN4_toIN()
#define MCU_LWC_ST_isHI()            IO_PIN4_isHI()

#define TPS92520_CS_toOUT()          IO_PIN33_toOUT()
#define TPS92520_CS_toHI()           IO_PIN33_toHI()
#define TPS92520_CS_toLO()           IO_PIN33_toLO()


#define MCU_LEDC_ENA_toOUT()         IO_PIN39_toOUT()
#define MCU_LEDC_ENA_doENABLE()      IO_PIN39_toHI()
#define MCU_LEDC_ENA_doDISABLE()     IO_PIN39_toLO()

#define MCU_LEDB_ENA_toOUT()         IO_PIN40_toOUT()
#define MCU_LEDB_ENA_doENABLE()      IO_PIN40_toHI()
#define MCU_LEDB_ENA_doDISABLE()     IO_PIN40_toLO()

#define MCU_KL30_PS_ENA_toOUT()      IO_PIN41_toOUT()
#define MCU_KL30_PS_ENA_doENABLE()   IO_PIN41_toHI()
#define MCU_KL30_PS_ENA_doDISABLE()  IO_PIN41_toLO()

#define KL30_MEAS_toANALOG()         IO_PIN38_toANALOG()
#define TEMP_MEAS_toANALOG()         IO_PIN37_toANALOG()
#define MCU_LEDC_NTC_toANALOG()      IO_PIN25_toANALOG()
#define MCU_LEDC_BIN_toANALOG()      IO_PIN32_toANALOG()
#define MCU_LEDA_BIN_toANALOG()      IO_PIN22_toANALOG()
#define MCU_LEDA_NTC_toANALOG()      IO_PIN19_toANALOG()
#define SYS_CODE_toANALOG()          IO_PIN26_toANALOG()

#define ADCchannel_KL30              ADC_EXT_CHAN_0
#define ADCchannel_tempPCB           ADC_EXT_CHAN_1
#define ADCchannel_tempLEDA          ADC_EXT_CHAN_9
#define ADCchannel_binLEDA           ADC_EXT_CHAN_12
#define ADCchannel_tempLEDC          ADC_EXT_CHAN_5
#define ADCchannel_binLEDC           ADC_EXT_CHAN_8
#define ADCchannel_SYS_CODE          ADC_EXT_CHAN_4

#endif



/* === EXPORTED VARIABLES =================================================== */
/* none */
/* === EXPORTED FUNCTIONS =================================================== */
/* none */


#endif /* __BOARD_H */
