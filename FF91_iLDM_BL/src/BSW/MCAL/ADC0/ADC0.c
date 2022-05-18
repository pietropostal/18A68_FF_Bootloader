/*
 *    JANI HOVAN, COPYRIGHT (c) 2020
 *    ALL RIGHTS RESERVED
 */

/**
* \file ADC0.c
* \ingroup grpXXX
* \brief ADC0 driver implementation of S32K144.
* \version 1.0.0
* \author Jani Hovan
* \date 2020-10-04
*/

/* === INCLUDES ============================================================= */
#include "board.h"    /* MCU registers */

#include "ADC0.h"     /* Module header */

/* === TYPEDEFS ============================================================= */
/* none */
/* === FORWARD DECLARATIONS ================================================= */
/* none */
/* === SYMBOLIC CONSTANTS =================================================== */
/* none */
/* === MACROS =============================================================== */
/* none */
/* === EXPORTED VARIABLES =================================================== */
uint16_t ADC0_aResults[ ADC_CHANNEL_AMOUNT ];

/* === LOCAL VARIABLES ====================================================== */
uint8_t  ADC0loc_actChannel;

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
void ADC0_vInit( void )
{
    uint32_t  PrioStartBit;


    /* SIM_CHIPCTL -> ACC_SUPPLY : Internal supplies monitored on ADC0 */


    /*=== configure pins =====================================================*/


    /*=== configure NVIC for ADC0 Interrupts =================================*/
    /* ISER: Interrupt Set Enable Register */
    /* ICER: Interrupt Clear Enable Register */
    /* ISPR: Interrupt Set Pending Register */
    /* ICPR: Interrupt Clear Pending Register */
    /* IABR: Interrupt Active bit Register */
    /* IP: Interrupt Priority Register */

    S32_NVIC->ICPR[1] = 1U << (ADC0_IRQn % 32U);  /* clear any pending IRQ */
    S32_NVIC->ISER[1] = 1U << (ADC0_IRQn % 32U);  /* enable IRQ */
    PrioStartBit      = 8U * (ADC0_IRQn % 4U) + 4U;
    S32_NVIC->IP[ADC0_IRQn] |= 10U << PrioStartBit; /* priority 10 of 0-15 */


    /*=== configure ADC0 =====================================================*/
    //SCG->FIRCDIV =  SCG_FIRCDIV_FIRCDIV2(4);  /* FIRCDIV2 = 4: FIRCDIV2 divide by 8 */
    PCC->PCCn[PCC_ADC0_INDEX] &=~ PCC_PCCn_CGC_MASK;  /* Disable clock to change PCS */
    PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_PCS(1U);    /* PCS=1: Select SOSCDIV2 */   /* PCS = 3: Select FIRCDIV2 */
    PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_CGC_MASK;   /* Enable bus clock in ADC */
    
    /***** Calibrate ADC0 *****/
    ADC0->SC3 = ADC_SC3_CAL_MASK   /* CAL = 1: Start calibration sequence */
              | ADC_SC3_AVGE_MASK  /* AVGE = 1: Enable hardware average */
              | ADC_SC3_AVGS(3U);  /* AVGS = 11b: 32 samples averaged */

    /* Wait for completion */
    while(((ADC0->SC1[ 0U ] & ADC_SC1_COCO_MASK)>>ADC_SC1_COCO_SHIFT) == 0U);  //warum nicht SC3 -> CAL  !?!?!??!??!?!??!?!?!


    ADC0->SC1[ 0U ] =0x00001FU; /* ADCH=1F: Module is disabled for conversions*/
                                /* AIEN=0: Interrupts are disabled */

    ADC0->CFG1 = 0x000000004U;  /* ADICLK=0: Input clk=ALTCLK1=SOSCDIV2 */
                                /* ADIV=0: Prescaler=1 */
                                /* MODE=1: 12-bit conversion */

    ADC0->CFG2 = 0x00000000CU;  /* SMPLTS=12(default): sample time is 13 ADC clks */

    ADC0->SC2 = 0x00000000U;    /* ADTRG=0: SW trigger */
                                /* ACFE,ACFGT,ACREN=0: Compare func disabled */
                                /* DMAEN=0: DMA disabled */
                                /* REFSEL=0: Voltage reference pins= VREFH, VREEFL */

    ADC0->SC3 = 0x00000000U;    /* CAL=0: Do not start calibration sequence */
                                /* ADCO=0: One conversion performed */
                                /* AVGE,AVGS=0: HW average function disabled */
    
} /* END ADC0_vInit() */

/******************************************************************************/

/**
 * \brief Main function of this module.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
void ADC0_vMain( void )
{
    static uint8_t  state = 0U;

    switch (state)
    {
        case 0U:
            ADC0_vConvertChannelWithInterrupt(ADC_EXT_CHAN_0);
            state = 1U;
            break;
        case 1U:
            ADC0_vConvertChannelWithInterrupt(ADC_EXT_CHAN_1);
            state = 2U;
            break;
        case 2U:
            ADC0_vConvertChannelWithInterrupt(ADC_EXT_CHAN_2);
            state = 3U;
            break;
        case 3U:
            ADC0_vConvertChannelWithInterrupt(ADC_EXT_CHAN_3);
            state = 4U;
            break;
        case 4U:
            ADC0_vConvertChannelWithInterrupt(ADC_EXT_CHAN_4);
            state = 5U;
            break;
        case 5U:
            ADC0_vConvertChannelWithInterrupt(ADC_EXT_CHAN_5);
            state = 6U;
            break;
        case 6U:
            ADC0_vConvertChannelWithInterrupt(ADC_EXT_CHAN_6);
            state = 7U;
            break;
        case 7U:
            ADC0_vConvertChannelWithInterrupt(ADC_EXT_CHAN_7);
            state = 8U;
            break;
        case 8U:
            SIM->CHIPCTL |= 0x0004U; //x1xx - PTB13 to ADC0_SE8
            //SIM->CHIPCTL &= ~0x0004U; //x0xx - PTC0 to ADC0_SE8
            ADC0_vConvertChannelWithInterrupt(ADC_EXT_CHAN_8);
            state = 9U;
            break;
        case 9U:
            //SIM->CHIPCTL |= 0x0008U; //1xxx - PTB14 to ADC0_SE9
            SIM->CHIPCTL &= ~0x0008U; //0xxx - PTC1 to ADC0_SE9
            ADC0_vConvertChannelWithInterrupt(ADC_EXT_CHAN_9);
            state = 10U;
            break;
        case 10U:
            ADC0_vConvertChannelWithInterrupt(ADC_EXT_CHAN_10);
            state = 11U;
            break;
        case 11U:
            ADC0_vConvertChannelWithInterrupt(ADC_EXT_CHAN_11);
            state = 12U;
            break;
        case 12U:
            ADC0_vConvertChannelWithInterrupt(ADC_EXT_CHAN_12);
            state = 13U;
            break;
        case 13U:
            ADC0_vConvertChannelWithInterrupt(ADC_EXT_CHAN_13);
            state = 17U;
            break;
        case 14U:

            break;
        case 15U:

            break;
        case 16U:

            break;
        case 17U:
            ADC0_vConvertChannelWithInterrupt(ADC_V_REFSH);
            state = 0U;
            break;
        default:
            break;
    }//switch (state)

} /* END ADC0_vMain() */

/******************************************************************************/

/**
 * \brief Convert a single channel and enable the Interrupt.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
void ADC0_vConvertChannelWithInterrupt( eADC_SC1A_ADCH_t argAdcChannel )
{
    uint32_t  tmp = 0U;

    if ((ADC0->SC2 & ADC_SC2_ADACT_MASK) != ADC_SC2_ADACT_MASK)
    {
        /* ADACT-bit not set: Conversion not in progress */
        ADC0loc_actChannel = (uint8_t) argAdcChannel;
        tmp  = ADC_SC1_AIEN(1U);               /* enable interrupt */
        tmp |= ADC_SC1_ADCH(argAdcChannel);    /* set channel*/
        ADC0->SC1[ 0U ]  =  tmp;               /* Initiate Conversion*/
    }
} /* END ADC0_vConvertChannelWithInterrupt() */

/******************************************************************************/

/**
 * \brief Interrupt callback from ADC0.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
void ADC0_InterruptCallback( void )
{
    uint32_t tmp = 0U;

    tmp = ADC0->R[ 0U ];      /* For SW trigger mode, R[0] is used; Read ADC Data Result A (ADC0_RA) */
//    tmp = ((5000 * tmp) / (1 << 12));  /* Convert result to mv for 0-5V range */
    tmp = ((5000U * tmp) / 0xFFFU);      /* Convert result to mv for 0-5V range */
    ADC0_aResults[ ADC0loc_actChannel ] = (uint16_t)tmp;
} /* END ADC0_InterruptCallback() */



// Enrico
void ADC0_IRQHandler (void)
{
    ADC0_InterruptCallback();
#if 0
	while(1)
	{
		;
	}
#endif
}


/******************************************************************************/

/* === LOCAL FUNCTIONS ====================================================== */
/* none */
