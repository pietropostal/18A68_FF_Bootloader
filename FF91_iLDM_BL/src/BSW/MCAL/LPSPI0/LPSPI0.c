/*
 *    JANI HOVAN, COPYRIGHT (c) 2020
 *    ALL RIGHTS RESERVED
 */

/**
* \file LPSPI0.c
* \ingroup grpXXX
* \brief SPI0 lo-level driver for S32K144 (NXP).
* \version 1.0.0
* \author Jani Hovan
* \date 2020-10-04
*/

/* === INCLUDES ============================================================= */
#include "board.h"

#include "LPSPI.h"   /* common data for all LPSPIs */
#include "LPSPI0.h"  /* module header */

/* === TYPEDEFS ============================================================= */
#define LPSPI0_BUFF_SIZE   5
typedef struct strLPSPI0_ExchangeData
{
    uint32_t aTxBuff[ LPSPI0_BUFF_SIZE ];
    uint32_t aRxBuff[ LPSPI0_BUFF_SIZE ];
    uint8_t  DataAmountToSend;
    uint8_t  DataCnt;
}strLPSPI0_ExchangeData_t;

/* === FORWARD DECLARATIONS ================================================= */
/* none */
/* === SYMBOLIC CONSTANTS =================================================== */
/* none */
/* === MACROS =============================================================== */
/* none */
/* === EXPORTED VARIABLES =================================================== */
/* none */
/* === LOCAL VARIABLES ====================================================== */
static strLPSPI0_ExchangeData_t strLPSPI0_ExchangeData;

/* === EXPORTED FUNCTIONS =================================================== */

/**
 * \brief Init this module.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
void LPSPI0_vInit( const strLPSPI_config_t * argConfig )
{
//	uint32_t  PrioStartBit;
	uint32_t  tmpPCCn;
	uint32_t  tmpCR;
	uint32_t  tmpIER;
	uint32_t  tmpDER;
	uint32_t  tmpCFGR0;
	uint32_t  tmpCFGR1;
	uint32_t  tmpTCR;
	uint32_t  tmpCCR;
	uint32_t  tmpFCR;
	uint8_t   ii;


	/* clear transfer data */
	strLPSPI0_ExchangeData.DataAmountToSend = 0;
	strLPSPI0_ExchangeData.DataCnt = 0;
	for (ii = 0; ii < LPSPI0_BUFF_SIZE; ii ++)
	{
	    strLPSPI0_ExchangeData.aRxBuff[ ii ] = 0;
	    strLPSPI0_ExchangeData.aTxBuff[ ii ] = 0;
	}


	/*___configure pins_______________________________________________________*/

	//geht auch PORT_MUX_PIN_ALT3 statt PORT_PCR_MUX(3)

	/*___LPSPI0_PCS0_________________*/
#if 0 /* PORTB0 */
	PCC->PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clocks for PORTB */
	PORTB->PCR[0] &= ~PORT_MUX_MASK; /* clear MUX values */
	PORTB->PCR[0] |= PORT_PCR_MUX(3); /* set MUX=ALT3 : LPSPI0_PCS0 */
#endif
#if 0 /* PORTB5 */
	PCC->PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clocks for PORTB */
	PORTB->PCR[5] &= ~PORT_MUX_MASK; /* clear MUX values */
	PORTB->PCR[5] |= PORT_PCR_MUX(4); /* set MUX=ALT4 : LPSPI0_PCS0 */
#endif
	/*___LPSPI0_PCS1_________________*/
#if 1 /* PORTB5 */
	PCC->PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clocks for PORTB */
	PORTB->PCR[5] &= ~PORT_MUX_MASK; /* clear MUX values */
	PORTB->PCR[5] |= PORT_PCR_MUX(3); /* set MUX=ALT3 : LPSPI0_PCS1 */
#endif
	/*___LPSPI0_SCK__________________*/
#if 1 /* PORTB2 */
	PCC->PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clocks for PORTB */
	PORTB->PCR[2] &= ~PORT_MUX_MASK; /* clear MUX values */
	PORTB->PCR[2] |= PORT_PCR_MUX(3); /* set MUX=ALT3 : LPSPI0_SCK */
#endif
#if 0 /* PTD15 */
	PCC->PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clocks for PORTD */
	PORTD->PCR[15] &= ~PORT_MUX_MASK; /* clear MUX values */
	PORTD->PCR[15] |= PORT_PCR_MUX(4); /* set MUX=ALT4 : LPSPI0_SCK */
#endif
	/*___LPSPI0_SIN__________________*/
#if 1 /* PORTB3 */
	PCC->PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clocks for PORTB */
	PORTB->PCR[3] &= ~PORT_MUX_MASK; /* clear MUX values */
	PORTB->PCR[3] |= PORT_PCR_MUX(3); /* set MUX=ALT3 : LPSPI0_SIN */
#endif
#if 0 /* PTD16 */
	PCC->PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clocks for PORTD */
	PORTD->PCR[16] &= ~PORT_MUX_MASK; /* clear MUX values */
	PORTD->PCR[16] |= PORT_PCR_MUX(4); /* set MUX=ALT4 : LPSPI0_SIN */
#endif
	/*___LPSPI0_SOUT_________________*/
#if 1 /* PORTB4 */
	PCC->PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clocks for PORTB */
	PORTB->PCR[4] &= ~PORT_MUX_MASK; /* clear MUX values */
	PORTB->PCR[4] |= PORT_PCR_MUX(3); /* set MUX=ALT3 : LPSPI0_SOUT */
#endif
#if 0 /* PORTB1 */
	PCC->PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clocks for PORTB */
	PORTB->PCR[1] &= ~PORT_MUX_MASK; /* clear MUX values */
	PORTB->PCR[1] |= PORT_PCR_MUX(3); /* set MUX=ALT3 : LPSPI0_SOUT */
#endif


	/*___configure NVIC for LPSPI0 Interrupts_________________________________*/  //keine ahnung ob das hier geht mit den interrupts ?!?!?!??!?!?!!
	/* ISER: Interrupt Set Enable Register */
	/* ICER: Interrupt Clear Enable Register */
	/* ISPR: Interrupt Set Pending Register */
	/* ICPR: Interrupt Clear Pending Register */
	/* IABR: Interrupt Active bit Register */
	/* IP: Interrupt Priority Register */
//	S32_NVIC->ICPR[6] = 1 << (LPSPI0_IRQn % 32);  /* clear any pending IRQ */
//	S32_NVIC->ISER[6] = 1 << (LPSPI0_IRQn % 32);  /* enable IRQ */
//	PrioStartBit = 8 * (LPSPI0_IRQn % 4) + 4;
//	S32_NVIC->IP[LPSPI0_IRQn] |= 10 << PrioStartBit; /* priority 10 of 0-15 */


	/*___PCCn_________________________________________________________________*/
	tmpPCCn = 0U;
	PCC->PCCn[PCC_LPSPI0_INDEX] = 0;        /* Disable clocks to modify PCS (default) */
	tmpPCCn |= (1U << PCC_PCCn_PR_SHIFT);   /* Peripheral is present */
	tmpPCCn |= (1U << PCC_PCCn_CGC_SHIFT);  /* Clock enabled */
	tmpPCCn |= (LPSPI_CLKSOURCE_SPLLDIV2 << PCC_PCCn_PCS_SHIFT); /* Peripheral Clock Source Select */
	PCC->PCCn[PCC_LPSPI0_INDEX] = tmpPCCn;


	/*___CR___________________________________________________________________*/
	LPSPI0->CR    = 0x00000000U;   /* Disable module for configuration */


	/*___IER__________________________________________________________________*/
	tmpIER = 0x00000000U; /* this is also LPSPI_INTERRUPT_NONE */
	switch(argConfig->IER_Interrupt)
	{
		case LPSPI_INTERRUPT_DATA:
			tmpIER |= (1U << LPSPI_IER_TDIE_SHIFT); /* Transmit Data Interrupt Enable */
			tmpIER |= (1U << LPSPI_IER_RDIE_SHIFT); /* Receive Data Interrupt Enable */
			break;
		case LPSPI_INTERRUPT_WORD:
			tmpIER |= (1U << LPSPI_IER_WCIE_SHIFT); /* Word Complete Interrupt Enable */
			break;
		case LPSPI_INTERRUPT_FRAME:
			tmpIER |= (1U << LPSPI_IER_FCIE_SHIFT); /* Frame Complete Interrupt Enable */
			break;
		case LPSPI_INTERRUPT_TRANSFER:
			tmpIER |= (1U << LPSPI_IER_TCIE_SHIFT); /* Transfer Complete Interrupt Enable */
			break;
		default:
			/* do nothing - cleared above */
			break;
	}


	/*___DER__________________________________________________________________*/
	tmpDER = 0x00000000U;
	tmpDER |= (argConfig->DER_DMA_Tx   << LPSPI_DER_TDDE_SHIFT);
	tmpDER |= (argConfig->DER_DMA_Rx   << LPSPI_DER_RDDE_SHIFT);


	/*___CFGR0________________________________________________________________*/
	tmpCFGR0 = 0x00000000U;
	/* RDM0=0: rec'd data to FIFO as normal */
	/* CIRFIFO=0; Circular FIFO is disabled */
	/* HRSEL, HRPOL, HREN=0: Host request disabled */


	/*___CFGR1________________________________________________________________*/
	tmpCFGR1 = 0x00000000U;
	tmpCFGR1 |= (argConfig->CFGR1_MasterSlave << LPSPI_CFGR1_MASTER_SHIFT);
	tmpCFGR1 |= (argConfig->CFGR1_SAMPLE << LPSPI_CFGR1_SAMPLE_SHIFT);
	tmpCFGR1 |= (argConfig->CFGR1_PCSPOL << LPSPI_CFGR1_PCSPOL_SHIFT);
	tmpCFGR1 |= (argConfig->CFGR1_PINCFG << LPSPI_CFGR1_PINCFG_SHIFT);
	tmpCFGR1 |= (argConfig->CFGR1_OUTCFG << LPSPI_CFGR1_OUTCFG_SHIFT);
	tmpCFGR1 |= (argConfig->CFGR1_PCSCFG << LPSPI_CFGR1_PCSCFG_SHIFT);
	//LPSPI0->CFGR1 = 0x00000001;   /* Configurations: master mode*/
									/* PCSCFG=0: PCS[3:2] are enabled */
									/* OUTCFG=0: Output data retains last value when CS negated */
									/* PINCFG=0: SIN is input, SOUT is output */
									/* MATCFG=0: Match disabled */
									/* PCSPOL=0: PCS is active low */
									/* NOSTALL=0: Stall if Tx FIFO empty or Rx FIFO full */
									/* AUTOPCS=0: does not apply for master mode */
									/* SAMPLE=0: input data sampled on SCK edge */
									/* MASTER=1: Master mode */


	/*___TCR__________________________________________________________________*/
	tmpTCR = 0x00000000U;
	tmpTCR |= (argConfig->TCR_FRAMESZ  << LPSPI_TCR_FRAMESZ_SHIFT);
	tmpTCR |= (argConfig->TCR_WIDTH    << LPSPI_TCR_WIDTH_SHIFT);
	tmpTCR |= (argConfig->TCR_TXMSK    << LPSPI_TCR_TXMSK_SHIFT);
	tmpTCR |= (argConfig->TCR_RXMSK    << LPSPI_TCR_RXMSK_SHIFT);
	tmpTCR |= (argConfig->TCR_CONT     << LPSPI_TCR_CONT_SHIFT);
	tmpTCR |= (argConfig->TCR_BYSW     << LPSPI_TCR_BYSW_SHIFT);
	tmpTCR |= (argConfig->TCR_LSBF     << LPSPI_TCR_LSBF_SHIFT);
	tmpTCR |= (argConfig->TCR_PCS      << LPSPI_TCR_PCS_SHIFT);
	tmpTCR |= (argConfig->TCR_PRESCALE << LPSPI_TCR_PRESCALE_SHIFT);
	tmpTCR |= (argConfig->TCR_CPHA     << LPSPI_TCR_CPHA_SHIFT);
	tmpTCR |= (argConfig->TCR_CPOL     << LPSPI_TCR_CPOL_SHIFT);
	//LPSPI0->TCR   = 0x5300000F;   /* Transmit cmd: PCS3, 16 bits, prescale func'l clk by 4, etc*/
	                                /* CPOL=0: SCK inactive state is low */
	                                /* CPHA=1: Change data on SCK lead'g, capture on trail'g edge*/
	                                /* PRESCALE=2: Functional clock divided by 2**2 = 4 */
	                                /* PCS=3: Transfer using PCS3 */
	                                /* LSBF=0: Data is transfered MSB first */
	                                /* BYSW=0: Byte swap disabled */
	                                /* CONT, CONTC=0: Continuous transfer disabled */
	                                /* RXMSK=0: Normal transfer: rx data stored in rx FIFO */
	                                /* TXMSK=0: Normal transfer: data loaded from tx FIFO */
	                                /* WIDTH=0: Single bit transfer */
	                                /* FRAMESZ=15: # bits in frame = 15+1=16 */


	/*___CCR__________________________________________________________________*/
	tmpCCR = 0x00000000U;
	tmpCCR |= (argConfig->CCR_SCKDIV   << LPSPI_CCR_SCKDIV_SHIFT);
	tmpCCR |= (argConfig->CCR_DBT      << LPSPI_CCR_DBT_SHIFT);
	tmpCCR |= (argConfig->CCR_PCSSCK   << LPSPI_CCR_PCSSCK_SHIFT);
	tmpCCR |= (argConfig->CCR_SCKPCS   << LPSPI_CCR_SCKPCS_SHIFT);
	//LPSPI0->CCR   = 0x04090808;   /* Clock dividers based on prescaled func'l clk of 100 nsec */
	                                /* SCKPCS=4: SCK to PCS delay = 4+1 = 5 (500 nsec) */
	                                /* PCSSCK=4: PCS to SCK delay = 9+1 = 10 (1 usec) */
	                                /* DBT=8: Delay between Transfers = 8+2 = 10 (1 usec) */
	                                /* SCKDIV=8: SCK divider =8+2 = 10 (1 usec: 1 MHz baud rate) */


	/*___FCR__________________________________________________________________*/
	tmpFCR = 0x00000000U;
	tmpFCR |= (argConfig->FCR_TXWATER  << LPSPI_FCR_TXWATER_SHIFT);
	tmpFCR |= (argConfig->FCR_RXWATER  << LPSPI_FCR_RXWATER_SHIFT);
	//LPSPI0->FCR   = 0x00000003;   /* RXWATER=0: Rx flags set when Rx FIFO >0 */
	                                /* TXWATER=3: Tx flags set when Tx FIFO <= 3 */


	/*___CR___________________________________________________________________*/
	tmpCR = 0x00000000U;
	tmpCR |= (1U << LPSPI_CR_MEN_SHIFT); /* MEN=0: module disabled; MEN=1: module enabled */
	tmpCR |= (argConfig->CR_DBGEN      << LPSPI_CR_DBGEN_SHIFT);
	//LPSPI0->CR    = 0x00000009;   /* Enable module for operation */
	/* DBGEN=1: module enabled in debug mode */
	/* DOZEN=0: module enabled in Doze mode */
	/* RST=0: Master logic not reset */
	/* MEN=1: Module is enabled */


	/* now write to the registers */
	LPSPI0->CR    = (uint32)tmpCR;
	LPSPI0->IER   = (uint32)tmpIER;
	LPSPI0->DER   = (uint32)tmpDER;
	LPSPI0->CFGR0 = (uint32)tmpCFGR0;
	LPSPI0->CFGR1 = (uint32)tmpCFGR1;
	LPSPI0->TCR   = (uint32)tmpTCR;
	LPSPI0->CCR   = (uint32)tmpCCR;
	LPSPI0->FCR   = (uint32)tmpFCR;
	LPSPI0->CR    = (uint32)tmpCR; /* enable module */
	//LPSPI0->TCR   = tmpTCR; //try to set after module enabled MEN=1

} /* END LPSPI0_vInit() */

/******************************************************************************/

/**
 * \brief Cyclic function of this module.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
void LPSPI0_vMain(void)
{

} /* END LPSPI0_vMain() */

/******************************************************************************/

void LPSPI0_vSendReceive8bitBlocking( uint8_t argSendData, uint8_t * pargRetVal )
{
    if ((LPSPI0->SR & LPSPI_SR_TDF_MASK) == LPSPI_SR_TDF_MASK)
    {
        /* Tx FIFO available */
        LPSPI0->CR |= LPSPI_CR_RTF_MASK + LPSPI_CR_RRF_MASK; /* peripheral reset */
        LPSPI0->IER = (uint32_t)0U; /* disable interrupts */
        LPSPI0->TCR &= ~LPSPI_TCR_FRAMESZ_MASK; /* clear frame-size */
        LPSPI0->TCR |= LPSPI_FRAMESZ_8bit  << LPSPI_TCR_FRAMESZ_SHIFT; /* set frame-size to 8bit */
        LPSPI0->SR |= LPSPI_SR_DMF_MASK + LPSPI_SR_REF_MASK + LPSPI_SR_TEF_MASK + LPSPI_SR_TCF_MASK + LPSPI_SR_FCF_MASK + LPSPI_SR_WCF_MASK + LPSPI_SR_TDF_MASK; /* clear status flags */
        LPSPI0->TDR = (uint32_t)argSendData;           /* Transmit data */

        //while( (LPSPI0->SR & LPSPI_SR_MBF_MASK) == LPSPI_SR_MBF_MASK ); /* wait as long LPSPI is busy */
        while( (LPSPI0->SR & LPSPI_SR_RDF_MASK) == 0 ); /* wait untill RDF flag is set: receive data flag */

        *pargRetVal = (uint8_t)LPSPI0->RDR; /* return value */
    }
} /* END LPSPI0_vSendReceive8bitBlocking() */

/******************************************************************************/

void LPSPI0_vSendReceive16bitBlocking( uint16_t argSendData, uint16_t * pargRetVal )
{
    if ((LPSPI0->SR & LPSPI_SR_TDF_MASK) == LPSPI_SR_TDF_MASK)
    {
        /* Tx FIFO available */
        LPSPI0->CR |= LPSPI_CR_RTF_MASK + LPSPI_CR_RRF_MASK; /* peripheral reset */
        LPSPI0->IER = (uint32_t)0U; /* disable interrupts */
        LPSPI0->TCR &= ~LPSPI_TCR_FRAMESZ_MASK; /* clear frame-size */
        LPSPI0->TCR |= LPSPI_FRAMESZ_16bit  << LPSPI_TCR_FRAMESZ_SHIFT; /* set frame-size to 16bit */
        LPSPI0->SR |= LPSPI_SR_DMF_MASK + LPSPI_SR_REF_MASK + LPSPI_SR_TEF_MASK + LPSPI_SR_TCF_MASK + LPSPI_SR_FCF_MASK + LPSPI_SR_WCF_MASK + LPSPI_SR_TDF_MASK; /* clear status flags */
        LPSPI0->TDR = (uint32_t)argSendData;           /* Transmit data */

        //while( (LPSPI0->SR & LPSPI_SR_MBF_MASK) == LPSPI_SR_MBF_MASK ); /* wait as long LPSPI is busy */
        while( (LPSPI0->SR & LPSPI_SR_RDF_MASK) == 0 ); /* wait untill RDF flag is set: receive data flag */

        *pargRetVal = (uint16_t)LPSPI0->RDR; /* return value */
    }
} /* LPSPI0_vSendReceive16bitBlocking() */

/******************************************************************************/

void LPSPI0_vSendReceive32bitBlocking( uint32_t argSendData, uint32_t * pargRetVal )
{
   // uint32_t  tmpData = 0;

    if ((LPSPI0->SR & LPSPI_SR_TDF_MASK) == LPSPI_SR_TDF_MASK)
    {
        /* Tx FIFO available */
        LPSPI0->CR |= LPSPI_CR_RTF_MASK + LPSPI_CR_RRF_MASK; /* peripheral reset */
        LPSPI0->IER = (uint32_t)0U; /* disable interrupts */
        LPSPI0->TCR &= ~LPSPI_TCR_FRAMESZ_MASK; /* clear frame-size */
        LPSPI0->TCR |= LPSPI_FRAMESZ_32bit  << LPSPI_TCR_FRAMESZ_SHIFT; /* set frame-size to 8bit */
        LPSPI0->SR |= LPSPI_SR_DMF_MASK + LPSPI_SR_REF_MASK + LPSPI_SR_TEF_MASK + LPSPI_SR_TCF_MASK + LPSPI_SR_FCF_MASK + LPSPI_SR_WCF_MASK + LPSPI_SR_TDF_MASK; /* clear status flags */
        LPSPI0->TDR = (uint32_t)argSendData;           /* Transmit data */

        while( (LPSPI0->SR & LPSPI_SR_RDF_MASK) == 0 ); /* wait untill RDF flag is set: receive data flag */

        *pargRetVal = LPSPI0->RDR; /* return value */
    }
} /* END LPSPI0_vSendReceive32bitBlocking() */

/******************************************************************************/

void LPSPI0_vSendReceive8bitBuff( const uint8_t *  argSendBuff, uint8_t *  pargRetBuff, uint8_t argAmount )
{
    uint8_t ii;

    /* copy given data into internal buffer */
    for (ii = 0; ii < argAmount; ii ++)
    {
        if (ii < LPSPI0_BUFF_SIZE)
        {
            strLPSPI0_ExchangeData.aTxBuff[ ii ] = * (argSendBuff + ii);
        }
    }

    if (argAmount > LPSPI0_BUFF_SIZE)
    {
        strLPSPI0_ExchangeData.DataAmountToSend = LPSPI0_BUFF_SIZE;
    }
    else
    {
        strLPSPI0_ExchangeData.DataAmountToSend = argAmount;
    }

    strLPSPI0_ExchangeData.DataCnt = 0;

    //enable interrupts: LPSPI0->IER = ...
    //put 1st data-element to spi send register
    //..
}



/******************************************************************************/


/* === LOCAL FUNCTIONS ====================================================== */
/* none */
