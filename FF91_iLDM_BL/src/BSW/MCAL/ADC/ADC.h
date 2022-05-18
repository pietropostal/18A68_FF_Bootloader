/*
 *    JANI HOVAN, COPYRIGHT (c) 2020
 *    ALL RIGHTS RESERVED
 */

/**
* \file ADC.h
* \ingroup grpXXX
* \brief Comon code for all ADCx of S32K144.
* \version 1.0.0
* \author Jani Hovan
* \date 2020-10-04
*/

#ifndef ADC_H_
#define ADC_H_

/* === INCLUDES ============================================================= */
/* none */
/* === TYPEDEFS ============================================================= */

/*! @brief Input Channel Select (Reg: SC1A) */
typedef enum eADC_SC1A_ADCH
{
    ADC_EXT_CHAN_0           = 0U,
    ADC_EXT_CHAN_1           = 1U,
    ADC_EXT_CHAN_2           = 2U,
    ADC_EXT_CHAN_3           = 3U,
    ADC_EXT_CHAN_4           = 4U,
    ADC_EXT_CHAN_5           = 5U,
    ADC_EXT_CHAN_6           = 6U,
    ADC_EXT_CHAN_7           = 7U,
    ADC_EXT_CHAN_8           = 8U,
    ADC_EXT_CHAN_9           = 9U,
    ADC_EXT_CHAN_10          = 10U,
    ADC_EXT_CHAN_11          = 11U,
    ADC_EXT_CHAN_12          = 12U,
    ADC_EXT_CHAN_13          = 13U,
    ADC_EXT_CHAN_14          = 14U,
    ADC_EXT_CHAN_15          = 15U,
    ADC_INT_CHAN_0           = 21U,
    ADC_INT_CHAN_1           = 22U,
    ADC_INT_CHAN_2           = 23U,
    ADC_BAND_GAP             = 27U,
    ADC_INT_CHAN_3           = 28U,
    ADC_V_REFSH              = 29U,
    ADC_V_REFSL              = 30U,
    ADC_EXT_CHAN_16          = 32U,
    ADC_EXT_CHAN_17          = 33U,
    ADC_EXT_CHAN_18          = 34U,
    ADC_EXT_CHAN_19          = 35U,
    ADC_EXT_CHAN_20          = 36U,
    ADC_EXT_CHAN_21          = 37U,
    ADC_EXT_CHAN_22          = 38U,
    ADC_EXT_CHAN_23          = 39U,
    ADC_EXT_CHAN_24          = 40U,
    ADC_EXT_CHAN_25          = 41U,
    ADC_EXT_CHAN_26          = 42U,
    ADC_EXT_CHAN_27          = 43U,
    ADC_EXT_CHAN_28          = 44U,
    ADC_EXT_CHAN_29          = 45U,
    ADC_EXT_CHAN_30          = 46U,
    ADC_EXT_CHAN_31          = 47U,
    ADC_DISABLED             = 63U,
} eADC_SC1A_ADCH_t;

#define ADC_CHANNEL_AMOUNT     48U /* used as size for result buffer */


#if 0
/*! @brief Peripheral Module Clocking (Reg: PCC) */
typedef enum eLPSPI_PCC_Clocksource
{
    LPSPI_CLKSOURCE_NONE        = 0U,
	LPSPI_CLKSOURCE_SOSCDIV2    = 1U,
	LPSPI_CLKSOURCE_SIRCDIV2    = 2U,
	LPSPI_CLKSOURCE_FIRCDIV2    = 3U,
	LPSPI_CLKSOURCE_RESERVED1   = 4U,
	LPSPI_CLKSOURCE_RESERVED2   = 5U,
	LPSPI_CLKSOURCE_SPLLDIV2    = 6U,
	LPSPI_CLKSOURCE_RESERVED3   = 7U,
} eLPSPI_PCC_Clocksource_t;

/*! @brief LPSPI master or slave configuration. */
typedef enum eLPSPI_CFGR1_MasterSlave
{
    LPSPI_SLAVE              = 0U, /*!< LPSPI peripheral operates in slave mode. */
	LPSPI_MASTER             = 1U, /*!< LPSPI peripheral operates in master mode. */
} eLPSPI_CFGR1_MasterSlave_t;

/*! @brief Interrupt Usage (Reg: IER) */
typedef enum eLPSPI_IER_Interrupt
{
	LPSPI_INTERRUPT_NONE     = 0U,
	LPSPI_INTERRUPT_DATA     = 1U,
	LPSPI_INTERRUPT_WORD     = 2U,
	LPSPI_INTERRUPT_FRAME    = 3U,
	LPSPI_INTERRUPT_TRANSFER = 4U,
} eLPSPI_IER_Interrupt_t;

/*! @brief DMA Usage (Reg: DER) */
typedef enum eLPSPI_DER_DMAenable
{
	LPSPI_DMA_DISABLE        = 0U,
	LPSPI_DMA_ENABLE         = 1U,
} eLPSPI_DER_DMAenable_t;







typedef struct
{
//hier nicht nötig -> dynamisch    eADC_SC1A_ADCH_t             ADCH_InputChannelSelect;


	eLPSPI_CFGR1_MasterSlave_t   CFGR1_MasterSlave;
	eLPSPI_IER_Interrupt_t       IER_Interrupt;


}strADC_config_t;
#endif

/* === SYMBOLIC CONSTANTS =================================================== */
/* none */
/* === EXPORTED MACROS ====================================================== */
/* none */
/* === EXPORTED VARIABLES =================================================== */
/* none */
/* === EXPORTED FUNCTIONS =================================================== */
/* none */


#endif /* ADC_H_ */
