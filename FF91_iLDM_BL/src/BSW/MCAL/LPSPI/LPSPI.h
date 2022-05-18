/*
 *    JANI HOVAN, COPYRIGHT (c) 2020
 *    ALL RIGHTS RESERVED
 */

/**
* \file LPSPI.h
* \ingroup grpXXX
* \brief Comon code for all LPSPIx of S32K144.
* \version 1.0.0
* \author Jani Hovan
* \date 2020-10-04
*/

#ifndef LPSPI_H_
#define LPSPI_H_

/* === INCLUDES ============================================================= */
/* none */
/* === TYPEDEFS ============================================================= */

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

/*! @brief Sample Point (Reg: CFGR1) */
typedef enum eLPSPI_CFGR1_SAMPLE
{
	LPSPI_SAMPLE_EDGE        = 0U,  /* sample on SCK edge */
	LPSPI_SAMPLE_DELAYED     = 1U,  /* sample on delayed SCK edge */
} eLPSPI_CFGR1_SAMPLE_t;

/*! @brief No Stall (Reg: CFGR1) */
typedef enum eLPSPI_CFGR1_NOSTALL
{
	LPSPI_NOSTALL_STALL      = 0U,  /* sample on SCK edge */
	LPSPI_NOSTALL_NOSTALL    = 1U,  /* sample on delayed SCK edge */
} eLPSPI_CFGR1_NOSTALL_t;

/*! @brief Chip Select Polarity (Reg: CFGR1) */
typedef enum eLPSPI_CFGR1_PCSPOL
{
	LPSPI_PCSPOL_ACTIVE_LO   = 0U,  /* PCS[n] pin is active low */
	LPSPI_PCSPOL_ACTIVE_HI   = 0b1111,  /* PCS[n] pin is active high (all 4 PCS-Pins) */
} eLPSPI_CFGR1_PCSPOL_t;

/*! @brief Pin Configuration (Reg: CFGR1) */
typedef enum eLPSPI_CFGR1_PINCFG
{
	LPSPI_PINCFG_SIN_IN_SOUT_OUT   = 0U,  /* SIN for input; SOUT for output */
	LPSPI_PINCFG_SIN_IN_OUT        = 1U,  /* SIN used for input and output */
	LPSPI_PINCFG_SOUT_IN_OUT       = 2U,  /* SOUT used for input and output */
	LPSPI_PINCFG_SIN_OUT_SOUT_IN   = 3U,  /* SIN for output; SOUT for input */
} eLPSPI_CFGR1_PINCFG_t;

/*! @brief Output Configuration (Reg: CFGR1) */
typedef enum eLPSPI_CFGR1_OUTCFG
{
	LPSPI_OUTCFG_RETAINED    = 0U,  /* Output data retains last value when chip-select is negated */
	LPSPI_OUTCFG_TRISTATE    = 1U,  /* Output data is tristated when CS is negated */
} eLPSPI_CFGR1_OUTCFG_t;

/*! @brief Peripheral Chip Select Configuration (Reg: CFGR1) */
typedef enum eLPSPI_CFGR1_PCSCFG
{
	LPSPI_PCSCFG_PCS_USED    = 0U,  /* PCS[3:2] are configured for chip-select function */
	LPSPI_PCSCFG_PCS_NOTUSED = 1U,  /* PCS[3:2] are configured for half-duplex 4-bit transfers (PCS[3:2]=DATA[3:2]) */
} eLPSPI_CFGR1_PCSCFG_t;

/*! @brief Frame Size (Reg: TCR) [8..4096 bits] */
typedef enum eLPSPI_TCR_FRAMESZ
{
	LPSPI_FRAMESZ_8bit       = 7U,  /* Frame-Size: 8bit */
	LPSPI_FRAMESZ_16bit      = 15U,  /* Frame-Size: 16bit */
	LPSPI_FRAMESZ_24bit      = 23U,  /* Frame-Size: 24bit */
	LPSPI_FRAMESZ_32bit      = 31U,  /* Frame-Size: 32bit */
} eLPSPI_TCR_FRAMESZ_t;

/*! @brief Transfer Width (Reg: TCR) */
typedef enum eLPSPI_TCR_WIDTH
{
	LPSPI_WIDTH_1bit         = 0U,  /* 1bit transfer */
	LPSPI_WIDTH_2bit         = 1U,  /* 2bit transfer */
	LPSPI_WIDTH_4bit         = 2U,  /* 4bit transfer */
} eLPSPI_TCR_WIDTH_t;

/*! @brief Transmit Data Mask (Reg: TCR) */
typedef enum eLPSPI_TCR_TXMSK
{
	LPSPI_TXMSK_TRANSFER_NORMAL = 0U,  /* Normal Transfer */
	LPSPI_TXMSK_TRANSFER_MASKED = 1U,  /* Mask Transmit Data */
} eLPSPI_TCR_TXMSK_t;

/*! @brief Receive Data Mask (Reg: TCR) */
typedef enum eLPSPI_TCR_RXMSK
{
	LPSPI_RXMSK_TRANSFER_NORMAL = 0U,  /* Normal Transfer */
	LPSPI_RXMSK_TRANSFER_MASKED = 1U,  /* Receive Data is Masked */
} eLPSPI_TCR_RXMSK_t;

/*! @brief Continuous Transfer (Reg: TCR) */
typedef enum eLPSPI_TCR_CONT
{
	LPSPI_CONT_DISABLED      = 0U,  /* Continuous Transfer Disabled */
	LPSPI_CONT_ENABLED       = 1U,  /* Continuous Transfer Enabled */
} eLPSPI_TCR_CONT_t;

/*! @brief Byte Swap (Reg: TCR) */
typedef enum eLPSPI_TCR_BYSW
{
	LPSPI_BYSW_DISABLED      = 0U,  /* Byte Swap Disabled */
	LPSPI_BYSW_ENABLED       = 1U,  /* Byte Swap Enabled */
} eLPSPI_TCR_BYSW_t;

/*! @brief LSB First (Reg: TCR) */
typedef enum eLPSPI_TCR_LSBF
{
	LPSPI_LSBF_MSB_FIRST     = 0U,  /* Data Transfered MSB first */
	LPSPI_LSBF_LSB_FIRST     = 1U,  /* Data Transfered LSB first */
} eLPSPI_TCR_LSBF_t;

/*! @brief Peripheral Chip Select (PCS) (Reg: TCR) */
typedef enum eLPSPI_TCR_PCS
{
	LPSPI_PCS_PCS0           = 0U,  /* Transfer using LPSPI_PCS[0] */
	LPSPI_PCS_PCS1           = 1U,  /* Transfer using LPSPI_PCS[1] */
	LPSPI_PCS_PCS2           = 2U,  /* Transfer using LPSPI_PCS[2] */
	LPSPI_PCS_PCS3           = 3U,  /* Transfer using LPSPI_PCS[3] */
} eLPSPI_TCR_PCS_t;

/*! @brief Prescaler values for LPSPI clock source (Reg: TCR) */
typedef enum eLPSPI_TCR_PRESCALE
{
	LPSPI_PRESCALE_DIV_1     = 0U,
	LPSPI_PRESCALE_DIV_2     = 1U,
	LPSPI_PRESCALE_DIV_4     = 2U,
	LPSPI_PRESCALE_DIV_8     = 3U,
	LPSPI_PRESCALE_DIV_16    = 4U,
	LPSPI_PRESCALE_DIV_32    = 5U,
	LPSPI_PRESCALE_DIV_64    = 6U,
	LPSPI_PRESCALE_DIV_128   = 7U,
} eLPSPI_TCR_PRESCALE_t;

/*! @brief Clock Phase (Reg: TCR) */
typedef enum eLPSPI_TCR_CPHA
{
	LPSPI_CPHA_CAPTURE_1ST_EDGE  = 0U,  /* Data is captured on the leading edge */
	LPSPI_CPHA_CAPTURE_2ND_EDGE  = 1U,  /* Data is captured on the trailing edge */
} eLPSPI_TCR_CPHA_t;

/*! @brief Clock Polarity (Reg: TCR) */
typedef enum eLPSPI_TCR_CPOL
{
	LPSPI_CPOL_INACTIVE_LO   = 0U,  /* The inactive state value of SCK is low (active high) */
	LPSPI_CPOL_INACTIVE_HI   = 1U,  /* The inactive state value of SCK is high (active low) */
} eLPSPI_TCR_CPOL_t;

/*! @brief SCK Divider (Reg: CCR) [0..255] */
typedef enum eLPSPI_CCR_SCKDIV
{
	LPSPI_SCKDIV_DIV_2       = 0U,  /* (LPSPI-Clock / PRESCALE) / 2 */
	LPSPI_SCKDIV_DIV_3       = 1U,  /* (LPSPI-Clock / PRESCALE) / 3 */
	LPSPI_SCKDIV_DIV_4       = 2U,  /* (LPSPI-Clock / PRESCALE) / 4 */
	LPSPI_SCKDIV_DIV_5       = 3U,  /* (LPSPI-Clock / PRESCALE) / 5 */
	LPSPI_SCKDIV_DIV_6       = 4U,  /* (LPSPI-Clock / PRESCALE) / 6 */
	LPSPI_SCKDIV_DIV_7       = 5U,  /* (LPSPI-Clock / PRESCALE) / 7 */
	LPSPI_SCKDIV_DIV_8       = 6U,  /* (LPSPI-Clock / PRESCALE) / 8 */
	LPSPI_SCKDIV_DIV_9       = 7U,  /* (LPSPI-Clock / PRESCALE) / 9 */
	LPSPI_SCKDIV_DIV_10      = 8U,  /* (LPSPI-Clock / PRESCALE) / 10 */
	LPSPI_SCKDIV_DIV_20      = 18U, /* (LPSPI-Clock / PRESCALE) / 20 */
	LPSPI_SCKDIV_DIV_30      = 28U, /* (LPSPI-Clock / PRESCALE) / 30 */
	LPSPI_SCKDIV_DIV_40      = 38U, /* (LPSPI-Clock / PRESCALE) / 40 */
	LPSPI_SCKDIV_DIV_100     = 98U, /* (LPSPI-Clock / PRESCALE) / 100 */
	LPSPI_SCKDIV_DIV_200     = 198U, /* (LPSPI-Clock / PRESCALE) / 200 */
} eLPSPI_CCR_SCKDIV_t;

/*! @brief Delay Between Transfers (Reg: CCR) [0..255] */
typedef enum eLPSPI_CCR_DBT
{
	LPSPI_DBT_2CYCLES        = 0U,  /* (LPSPI-Clock / PRESCALE) * 2 Cycles */
	LPSPI_DBT_4CYCLES        = 2U,  /* (LPSPI-Clock / PRESCALE) * 4 Cycles */
	LPSPI_DBT_8CYCLES        = 6U,  /* (LPSPI-Clock / PRESCALE) * 8 Cycles */
	LPSPI_DBT_10CYCLES       = 8U,  /* (LPSPI-Clock / PRESCALE) * 10 Cycles */
} eLPSPI_CCR_DBT_t;

/*! @brief PCS-to-SCK Delay (Reg: CCR) [0..255] */
typedef enum eLPSPI_CCR_PCSSCK
{
	LPSPI_PCSSCK_2CYCLES     = 1U,  /* (LPSPI-Clock / PRESCALE) * 2 Cycles */
	LPSPI_PCSSCK_4CYCLES     = 3U,  /* (LPSPI-Clock / PRESCALE) * 4 Cycles */
	LPSPI_PCSSCK_8CYCLES     = 7U,  /* (LPSPI-Clock / PRESCALE) * 8 Cycles */
	LPSPI_PCSSCK_10CYCLES    = 9U,  /* (LPSPI-Clock / PRESCALE) * 10 Cycles */
	LPSPI_PCSSCK_20CYCLES    = 19U, /* (LPSPI-Clock / PRESCALE) * 20 Cycles */
} eLPSPI_CCR_PCSSCK_t;

/*! @brief SCK-to-PCS Delay (Reg: CCR) [0..255] */
typedef enum eLPSPI_CCR_SCKPCS
{
	LPSPI_SCKPCS_2CYCLES     = 1U,  /* (LPSPI-Clock / PRESCALE) * 2 Cycles */
	LPSPI_SCKPCS_4CYCLES     = 3U,  /* (LPSPI-Clock / PRESCALE) * 4 Cycles */
	LPSPI_SCKPCS_8CYCLES     = 7U,  /* (LPSPI-Clock / PRESCALE) * 8 Cycles */
	LPSPI_SCKPCS_10CYCLES    = 9U,  /* (LPSPI-Clock / PRESCALE) * 10 Cycles */
	LPSPI_SCKPCS_20CYCLES    = 19U, /* (LPSPI-Clock / PRESCALE) * 20 Cycles */
} eLPSPI_CCR_SCKPCS_t;

/*! @brief Transmit FIFO Watermark (Reg: FCR) [0..3] */
typedef enum eLPSPI_FCR_TXWATER
{
	LPSPI_TXWATER_0WORDS     = 0U,  /* Transmit FIFO Watermark: 0 Words */
	LPSPI_TXWATER_1WORDS     = 1U,  /* Transmit FIFO Watermark: 1 Words */
	LPSPI_TXWATER_2WORDS     = 2U,  /* Transmit FIFO Watermark: 2 Words */
	LPSPI_TXWATER_3WORDS     = 3U,  /* Transmit FIFO Watermark: 3 Words */
} eLPSPI_FCR_TXWATER_t;

/*! @brief Receive FIFO Watermark (Reg: FCR) [0..3] */
typedef enum eLPSPI_FCR_RXWATER
{
	LPSPI_RXWATER_0WORDS     = 0U,  /* Transmit FIFO Watermark: 0 Words */
	LPSPI_RXWATER_1WORDS     = 1U,  /* Transmit FIFO Watermark: 1 Words */
	LPSPI_RXWATER_2WORDS     = 2U,  /* Transmit FIFO Watermark: 2 Words */
	LPSPI_RXWATER_3WORDS     = 3U,  /* Transmit FIFO Watermark: 3 Words */
} eLPSPI_FCR_RXWATER_t;

/*! @brief Debug Enable (Reg: CR) */
typedef enum eLPSPI_CR_DBGEN
{
    LPSPI_DBGEN_NO           = 0U,  /* LPSPI disabled in debug mode */
    LPSPI_DBGEN_YES          = 1U,  /* LPSPI enabled in debug mode */
} eLPSPI_CR_DBGEN_t;


typedef struct
{
	eLPSPI_PCC_Clocksource_t     PCC_Clocksource;
	eLPSPI_CFGR1_MasterSlave_t   CFGR1_MasterSlave;
	eLPSPI_IER_Interrupt_t       IER_Interrupt;
	eLPSPI_DER_DMAenable_t       DER_DMA_Tx;
	eLPSPI_DER_DMAenable_t       DER_DMA_Rx;
	eLPSPI_CFGR1_SAMPLE_t        CFGR1_SAMPLE;
	eLPSPI_CFGR1_NOSTALL_t       CFGR1_NOSTALL;
	eLPSPI_CFGR1_PCSPOL_t        CFGR1_PCSPOL;
	eLPSPI_CFGR1_PINCFG_t        CFGR1_PINCFG;
	eLPSPI_CFGR1_OUTCFG_t        CFGR1_OUTCFG;
	eLPSPI_CFGR1_PCSCFG_t        CFGR1_PCSCFG;
	eLPSPI_TCR_FRAMESZ_t         TCR_FRAMESZ;
	eLPSPI_TCR_WIDTH_t           TCR_WIDTH;
	eLPSPI_TCR_TXMSK_t           TCR_TXMSK;
	eLPSPI_TCR_RXMSK_t           TCR_RXMSK;
	eLPSPI_TCR_CONT_t            TCR_CONT;
	eLPSPI_TCR_BYSW_t            TCR_BYSW;
	eLPSPI_TCR_LSBF_t            TCR_LSBF;
	eLPSPI_TCR_PCS_t             TCR_PCS;
	eLPSPI_TCR_PRESCALE_t        TCR_PRESCALE;
	eLPSPI_TCR_CPHA_t            TCR_CPHA;
	eLPSPI_TCR_CPOL_t            TCR_CPOL;
	eLPSPI_CCR_SCKDIV_t          CCR_SCKDIV;
	eLPSPI_CCR_DBT_t             CCR_DBT;
	eLPSPI_CCR_PCSSCK_t          CCR_PCSSCK;
	eLPSPI_CCR_SCKPCS_t          CCR_SCKPCS;
	eLPSPI_FCR_TXWATER_t         FCR_TXWATER;
	eLPSPI_FCR_RXWATER_t         FCR_RXWATER;
	eLPSPI_CR_DBGEN_t            CR_DBGEN;

}strLPSPI_config_t;


/* === SYMBOLIC CONSTANTS =================================================== */
/* none */
/* === EXPORTED MACROS ====================================================== */
/* none */
/* === EXPORTED VARIABLES =================================================== */
/* none */
/* === EXPORTED FUNCTIONS =================================================== */
/* none */


#endif /* LPSPI_H_ */
