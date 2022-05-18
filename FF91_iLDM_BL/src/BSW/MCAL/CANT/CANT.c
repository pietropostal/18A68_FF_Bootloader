/**************************************************************************************************
** Copyright (c) 2018 Embitel
**
** This software is the property of Embitel.
** It can not be used or duplicated without Embitel authorization.
**
** ------------------------------------------------------------------------------------------------
** File Name     					: CANT.c
** Module Name   					: CANT
** ------------------------------------------------------------------------------------------------
**
** Description : CAN Target
**
** ------------------------------------------------------------------------------------------------
**
** Documentation reference : LLD_CANT.01
**
***************************************************************************************************
** R E V I S I O N H I S T O R Y
***************************************************************************************************
** V01.00 06/12/2019
** - Baseline Created
** ------------------------------------------------------------------------------------------------
**
**
**************************************************************************************************/
/************************************** Inclusion files ******************************************/

#include "CANT.h"

/************************** Function declaration *************************************************/
static void CANT_iChkTxRx(void);
static void CANT_iConfTxMsgObj(void);
static void CANT_iChkErrorSt(void);
void CAN_RxMsgFiltrInit(const CANT_RxMsgConfigType  *ptrto_TxRxMessageTable, uint8_t NumofRxMsgs);
CAN_Type *CAN_0;
SMC_Type *SMC_0;
S32_NVIC_Type *S32_NVIC_0;
static uint8_t CANT_RxFitEle = CAN_CLR;
static uint8_t CANT_TxFitEle = CAN_CLR;
volatile static uint32_t CANT_LastMsgId = CAN_CLR;


/* ID Filter table */
const can_id_table_t Rx_Fifo_Filter[NO_RX_FILTER_ELEMENT]= {
		{CAN_FRAME_STD, RX_FILTER_IDE_1},
		{CAN_FRAME_STD, RX_FILTER_IDE_2},
		{CAN_FRAME_EXT, RX_FILTER_IDE_3},
		{CAN_NULL, CAN_NULL}
};
CAN_Dr_t CAN_Bus_RX_state;



// Enrico
#define MAX_ISR_COUNTER (4u)

static uint32 isr_counter;


static void handleISROverflow()
{
	if( isr_counter < MAX_ISR_COUNTER )
	{
		isr_counter++;
	}
	else if( isr_counter == MAX_ISR_COUNTER )
	{
		isr_counter++;
		CANT_DisInterrupt();
	}
}


void CANT_MainLoop( void )
{
	if( isr_counter >= MAX_ISR_COUNTER )
	{
		isr_counter = 0;
		CANT_EnInterrupt();
	}
}

/************************** Function definitions *************************************************/
/**************************************************************************************************
** Function name : CANT_Init
** Description   : Initialization of CAN
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CANT_Init(uint32_t CAN_Baudrate,const CANT_RxMsgConfigType  *ptrto_CANIL_TxRxMessageTable, uint8_t NumofRxMsgs)
{
	/*S32_NVIC_Type *S32_NVIC_0;*/
	PCC_Type *PCC_0;
	PORT_Type *PORTC_0;
	uint32_t databyte,Timeout = CAN_CLR;

	/*Initializing the Base address to the pointer*/
	CAN_0 = (CAN_Type*)CAN0_BASE;

	/*Initializing the Base address to the pointer*/
	SMC_0 = (SMC_Type*)SMC_BASE;

	/*Initializing the Base address to the pointer*/
	S32_NVIC_0 = (S32_NVIC_Type*)S32_NVIC_BASE;

	/*Initializing the Base address to the pointer*/
	PCC_0 = (PCC_Type*)PCC_BASE;

	/*Initializing the Base address to the pointer*/
	PORTC_0 = (PORT_Type*)PORTC_BASE;

	/* Enable clock for PORTE */
	PCC_0->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK;

	/* Port E4:  MUX = ALT5, CAN0_RX 	     */
	PORTC_0->PCR[ID_2] |= PORT_PCR_MUX(NO_3);

	/* Port E5:  MUX = ALT5, CAN0_TX         */
	PORTC_0->PCR[ID_3] |= PORT_PCR_MUX(NO_3);

	/* CGC=1: enable clock to FlexCAN0 */
	PCC_0->PCCn[PCC_FlexCAN0_INDEX] |= PCC_PCCn_CGC_MASK;

    /* To access the memory mapped registers,enter disable mode (hard reset). */
    if(CAN_CLR == ((CAN_0->MCR & CAN_MCR_MDIS_MASK) >> CAN_MCR_MDIS_SHIFT))
    {
    	/* Clock disable (module) */
        CAN_0->MCR = (uint32_t)((CAN_0->MCR & ~CAN_MCR_MDIS_MASK) | CAN_MCR_MDIS(CAN_SET));

        /* Wait until disable mode acknowledged */
        while( (((CAN_0->MCR & CAN_MCR_LPMACK_MASK) >> CAN_MCR_LPMACK_SHIFT) == CAN_CLR) &&
        													(CAN0_TIMEOUT_CFG > Timeout)){
        	Timeout++;
        }
    }else{
    	/*Do nothing*/
    }

    /* Select a source clock for the FlexCAN engine */
	CAN_0->CTRL1 = (uint32_t)(CAN_0->CTRL1 & ~(uint32_t)CAN_CTRL1_CLKSRC_MASK);

    /* Clearing the freeze mode setting */
    CAN_0->MCR = (uint32_t)(CAN_0->MCR & ~CAN_MCR_MDIS_MASK);

    CAN_0->MCR =(uint32_t)(CAN_0->MCR & ~CAN_MCR_MDIS_MASK);
    CAN_0->MCR =(uint32_t)(CAN_0->MCR & ~CAN_MCR_FRZ_MASK);
    CAN_0->MCR =(uint32_t)(CAN_0->MCR & ~CAN_MCR_HALT_MASK);

    /* Clearing the timeOut variable*/
    Timeout = CAN_CLR;

    /* Wait until disable mode acknowledged */
    while( (((CAN_0->MCR & CAN_MCR_LPMACK_MASK) >> CAN_MCR_LPMACK_SHIFT) != CAN_CLR) &&
    													(CAN0_TIMEOUT_CFG > Timeout)){
    	Timeout++;
    }

    /* Enter into Freeze mode*/
    CANT_Freeze_Enter();

    /* Reset the FLEXCAN */
    CAN_0->MCR =(uint32_t)((CAN_0->MCR & ~CAN_MCR_SOFTRST_MASK)| CAN_MCR_SOFTRST(CAN_SOFTRST_REQ));

    /* Clearing the timeOut variable*/
    Timeout =CAN_CLR;

    /* Wait until disable mode acknowledged */
    while( (((CAN_0->MCR & CAN_MCR_SOFTRST_MASK) >> CAN_MCR_SOFTRST_SHIFT) != CAN_CLR) &&
    													(CAN0_TIMEOUT_CFG > Timeout)){
    	Timeout++;
    }

    /* Clear MB region */
    for (databyte = CAN_CLR; databyte < MAX_NUM_OF_MB_DWORD; databyte++) {
    	CAN_0->RAMn[databyte] = CAN_CLR;
    }

    /* Clear RXIMR region */
    for (databyte = CAN_CLR; databyte < MAX_NUM_OF_MB; databyte++) {
    	CAN_0->RXIMR[databyte] = CAN_CLR;
    }

    /* Disable all MB interrupts */
    CAN_0->IMASK1 = CAN_CLR;

    /* Clear all MB interrupt flags */
    CAN_0->IFLAG1 = (uint32_t)CAN_IMASK1_BUF31TO0M_MASK;

    /* Disable can fd */
    CAN_0->MCR = (uint32_t)((CAN_0->MCR & (~(uint32_t)CAN_MCR_FDEN_MASK)));

    /* Disable the use of extended bit time definitions */
    CAN_0->CBT = (uint32_t)(CAN_0->CBT & (~(uint32_t)CAN_CBT_BTF_MASK));

    /* Disable the Stuff Bit Count */
    CAN_0->CTRL2 =(uint32_t)((CAN_0->CTRL2 & ~((uint32_t)CAN_CTRL2_ISOCANFDEN_MASK)) );

    /* Set operation mode as normal */
    CAN_0->MCR   = (uint32_t)((CAN_0->MCR & ~CAN_MCR_SUPV_MASK) | CAN_MCR_SUPV(CAN_SUPV_MODE));
    CAN_0->CTRL1 = (uint32_t)((CAN_0->CTRL1 & ~((uint32_t)CAN_CTRL1_LOM_MASK)));
    CAN_0->CTRL1 = (uint32_t)((CAN_0->CTRL1 & ~((uint32_t)CAN_CTRL1_LPB_MASK)));

    /* Set the maximum number of MBs*/
    CAN_0->MCR = (uint32_t)((CAN_0->MCR & ~(uint32_t)CAN_MCR_MAXMB_MASK) |
    							(( (uint32_t)(CANT_MAXMB_CNT) << CAN_MCR_MAXMB_SHIFT) &
    															CAN_MCR_MAXMB_MASK));

    /* Sets the FlexCAN time segments for setting up bit rate */
    CAN_0->CTRL1 = (uint32_t)(((CAN_0->CTRL1) & ~((CAN_CTRL1_PROPSEG_MASK | CAN_CTRL1_PSEG2_MASK |
    											CAN_CTRL1_PSEG1_MASK |CAN_CTRL1_PRESDIV_MASK) |
    											CAN_CTRL1_RJW_MASK | CAN_CTRL1_BOFFREC_MASK )));
    
    /*Setting the Bus off Error,Rx & TX warning mask*/
    CAN_0->CTRL1 = (uint32_t)(((CAN_0->CTRL1) | (CAN_CTRL1_PROPSEG(NO_7) |CAN_CTRL1_ERRMSK_MASK |
    											CAN_CTRL1_RWRNMSK_MASK |CAN_CTRL1_PSEG2(NO_1) |
											  CAN_CTRL1_TWRNMSK_MASK | CAN_CTRL1_BOFFMSK_MASK |
											  CAN_CTRL1_PSEG1(NO_4) | CAN_CTRL1_PRESDIV(CAN_Baudrate) |
									  	  	  	  	  	  	  	  	  CAN_CTRL1_RJW(NO_1))));

    // TEST!!!!! TODO ENRICO

	CAN_0->CTRL1 = 0x3DB0096;


    /*Setting the no of FIFO filter are 10MB (10 * 4Dword = 40element)*/
    CAN_0->CTRL2 = (uint32_t)((CAN_0->CTRL2) | CAN_CTRL2_BOFFDONEMSK_MASK
    															|CAN_CTRL2_RFFN(RX_FIFO_CFG));

    /*Enabling the WR_Waringin and RX FIFO*/
    CAN_0->MCR = (uint32_t)((CAN_0->MCR) | CAN_MCR_WRNEN_MASK | CAN_MCR_RFEN_MASK);

    if(ptrto_CANIL_TxRxMessageTable != NULL)
    {
    	/* Configure Rx message buffer */
    	CAN_RxMsgFiltrInit(ptrto_CANIL_TxRxMessageTable, NumofRxMsgs);
    }
    else
    {
    	/* Do Nothing */
    }

    /* Configure Tx message buffer */
    CANT_iConfTxMsgObj();

    /* Exit from Freeze mode */
    CANT_Freeze_Exit();

    /* Enable can0 interrupt */
    /* ENRICO: Disabled ISR!!!*/
    S32_NVIC_0->ISER[((uint32_t)CAN0_ORed_IRQn) >> CAN_NVIC_HDLR_SHIFT] =
    		((uint32_t)NO_1 << ((uint32_t)(CAN0_ORed_IRQn) & CAN_NVIC_HDLR_MASK));
    S32_NVIC_0->ISER[((uint32_t)CAN0_Error_IRQn) >> CAN_NVIC_HDLR_SHIFT] =
    		((uint32_t)NO_1 << ((uint32_t)(CAN0_Error_IRQn) & CAN_NVIC_HDLR_MASK));
    S32_NVIC_0->ISER[((uint32_t)CAN0_ORed_0_15_MB_IRQn) >> CAN_NVIC_HDLR_SHIFT] =
    		((uint32_t)NO_1 << ((uint32_t)(CAN0_ORed_0_15_MB_IRQn) &(uint32_t)CAN_NVIC_HDLR_MASK));
    S32_NVIC_0->ISER[((uint32_t)CAN0_ORed_16_31_MB_IRQn) >> CAN_NVIC_HDLR_SHIFT] =
    		((uint32_t)NO_1 <<((uint32_t)(CAN0_ORed_16_31_MB_IRQn) &(uint32_t)CAN_NVIC_HDLR_MASK));
    S32_NVIC_0->ISER[((uint32_t)CAN0_Wake_Up_IRQn) >> CAN_NVIC_HDLR_SHIFT] =
    		((uint32_t)NO_1 << ((uint32_t)(CAN0_Wake_Up_IRQn) & (uint32_t)CAN_NVIC_HDLR_MASK));


}

/**************************************************************************************************
** Function name : CAN_RxMsgFiltrInit
** Description   : Configure receive message buffer and H/w filter for message id's required.
** Parameter     : void
** Return value  : void
** Remarks       : global variables used, side effects
**************************************************************************************************/
void CAN_RxMsgFiltrInit(const CANT_RxMsgConfigType  *ptrto_TxRxMessageTable, uint8_t NumofRxMsgs)
{
	uint8_t bufNum;

	CANT_RxFitEle = CAN_CLR;
	
	if(ptrto_TxRxMessageTable != NULL)
	{
		/*Configuring the RX FIFO filter table*/
		for(bufNum = CAN_CLR; bufNum< NumofRxMsgs; bufNum++)
		{
				if(ptrto_TxRxMessageTable[bufNum].CANT_XTD == CANT_STANDARD)
				{
					CAN_0->RAMn[CAN_FIFO_FILTER_BASE + CANT_RxFitEle] =
								((ptrto_TxRxMessageTable[bufNum].CANT_ID)<<CAN_RX_FILTER_STD_SHIFT );
				}
				else
				{
					CAN_0->RAMn[CAN_FIFO_FILTER_BASE + CANT_RxFitEle] =
											((uint32_t)CAN_FRAME_EXT << CAN_RX_FILTER_IDE_SHIFT)|
								 ((ptrto_TxRxMessageTable[bufNum].CANT_ID)<<CAN_RX_FILTER_EXT_SHIFT );
				}
				/* Increment the Filter index*/
				CANT_RxFitEle++;
		}
	}
	else
	{
		/* Do Nothing */
	}

    /*Rx FIFO element format_A */
    CAN_0->MCR = ((CAN_0->MCR) & ~((uint32_t)CAN_MCR_IDAM_MASK));

    /*Disabling Individual Rx masking and queue, So global RX FIFO mask will be used*/
    CAN_0->MCR = (CAN_0->MCR & (~(uint32_t)CAN_MCR_IRMQ_MASK));

    /* RX FIFO global mask, take in consideration all filter fields*/
    CAN_0->RXFGMASK = CAN_RXFGMASK_FGM_CFG;

    /*Enabling the FIFO based interrupt*/
    for (bufNum = CAN_BUFMG_ID5; bufNum <CAN_BUFMG_ID8; bufNum++)
	{
		/* Enable buffer interrupt */
		CAN_0->IMASK1 = (uint32_t)((CAN_0 ->IMASK1) | (bit_shift_NO_1 << (bufNum)));
	}

}

/**************************************************************************************************
** Function name : CANT_RxMsgIdSet
** Description   : Configure the Rx message id
** Parameter     : RxMsgId				Specifies the CAN_ID
** 				   MsgFormat			Specifies the CAN types, Standard or Extended.
** 				   FitIdx				Index to write the ID
** Return value  : void
** Remarks       : global variables used, side effects
**************************************************************************************************/
void CANT_RxMsgIdSet(uint32_t CANT_RxMsgId,CANT_IDFormat_e CANT_MsgFormat,uint8_t CANT_FitIdx)
{
	uint8_t FilterIdx=CAN_CLR;

	/* Calculate the Index to write the Msg id*/
	FilterIdx = CAN_FIFO_FILTER_BASE + CANT_RxFitEle + CANT_FitIdx;
	if(FilterIdx < CAN_RAMn_COUNT)
	{
		if(CANT_STANDARD == CANT_MsgFormat)
		{
			CAN_0->RAMn[FilterIdx] = ((CANT_RxMsgId)<<CAN_RX_FILTER_STD_SHIFT );
		}else {
			CAN_0->RAMn[FilterIdx] = ((uint32_t)CAN_FRAME_EXT << CAN_RX_FILTER_IDE_SHIFT)|
						 	 	 	 	 ((CANT_RxMsgId)<<CAN_RX_FILTER_EXT_SHIFT );
		}
	}
	else
	{
		/* Do Nothing */
	}
}

/**************************************************************************************************
** Function name : CANT_iConfRxMsgObj
** Description   : Configure transmit message buffer for message id's required .
** Parameter     : void
** Return value  : void
** Remarks       : global variables used, side effects
**************************************************************************************************/
static void CANT_iConfTxMsgObj(void)
{
	/* Enable interrupt for transmit buffer */
	for(CANT_TxFitEle = CANT_TXBUFFSTRT; CANT_TxFitEle < MAX_NUM_OF_MB ; CANT_TxFitEle++)
	{
		CAN_0->IMASK1 = (uint32_t)((CAN_0 ->IMASK1) | (bit_shift_NO_1 << (CANT_TxFitEle)));
	}
}

/**************************************************************************************************
** Function name : CAN0_ORed_0_15_MB_IRQHandler
** Description   : Isr for a successful transmission or reception for CAN0
** 				   Message Buffers 0-15
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CAN0_ORed_0_15_MB_IRQHandler(void)
{
	handleISROverflow();
	CANT_iChkTxRx();
}

/**************************************************************************************************
** Function name : CAN0_ORed_16_31_MB_IRQHandler
** Description   : Isr for a successful transmission or reception for CAN0
** 				   Message Buffers 16-31
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CAN0_ORed_16_31_MB_IRQHandler(void)
{
	handleISROverflow();
	CANT_iChkTxRx();
}

/**************************************************************************************************
** Function name : CAN0_ORed_IRQHandler
** Description   : Isr for for CAN0 OR'ed interrupts (Bus Off,Transmit Warning,
** 				   Receive Warning)
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CAN0_ORed_IRQHandler(void)
{
	handleISROverflow();
	CANT_iChkErrorSt();
}

/**************************************************************************************************
** Function name : CAN0_Error_IRQHandler
** Description   : Isr interrupts indicating that errors were detected on the
**                 CAN0 bus
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CAN0_Error_IRQHandler(void)
{
	handleISROverflow();
	CANT_iChkErrorSt();
}

/**************************************************************************************************
** Function name : CAN0_Error_IRQHandler
** Description   : Isr interrupts indicating that errors were detected on the
**                 CAN0 bus
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CAN0_Wake_Up_IRQHandler(void)
{
	handleISROverflow();

	/* Enter into Freeze mode*/
    CANT_Freeze_Enter();

	/*Wakeup match event is disabled*/
	CAN_0->CTRL1_PN = (uint32_t)( (CAN_0->CTRL1_PN) & ~CAN_CTRL1_PN_WUMF_MSK_MASK);

    /*Exit from Pretended Network Mode*/
	CAN_0->MCR = (uint32_t)( (CAN_0->MCR) & ~(uint32_t)CAN_MCR_PNET_EN_MASK);

	/* VLPR and VLPS are not allowed */
    SMC_0->PMPROT =  (uint32_t)(SMC_0->PMPROT & ~(uint32_t)SMC_PMPROT_AVLP_MASK);

    /*Clearing the Stop Option */
    SMC_0->STOPCTRL = (uint32_t)( (SMC_0->STOPCTRL) & (~(uint32_t)SMC_PMCTRL_RUNM_MASK));

    /* Exit from Freeze mode */
    CANT_Freeze_Exit();
}

/**************************************************************************************************
** Function name : CANT_iChkTxRx
** Description   : Check for transmission / reception of CAN frames
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
static void CANT_iChkTxRx(void)
{
	uint32_t msgNbr,flag_recv = CAN_CLR;
	uint32_t rxData[CAN_MB_DWORD_SIZE];           /* Received message data (2 words) */
	//uint8_t Rx_Enable = CAN_CLR;
	CanIf_Msg_Type RxMsg;
	for(msgNbr = CAN_CLR; msgNbr<MAX_NUM_OF_MB; msgNbr++)
	{
		/* Check for individual flag*/
		flag_recv = (uint32_t)(((CAN_0->IFLAG1 &
				(uint32_t)(CAN_0->IMASK1 & CAN_IMASK1_BUF31TO0M_MASK)) >> (msgNbr)) & CAN_SET);

		if(flag_recv==CAN_SET){
			break;
		}else{
			/* Do Nothing */
		}
	}

	/* Check Tx/Rx interrupt flag and clear the interrupt */
	if(CAN_CLR != flag_recv )
	{
		/* Check whether the interrupt cause is receive and for valid receive buffer number */
		if(msgNbr == CAN_RX_BUFF_START)
		{
			RxMsg.DLC = (uint8_t)((CAN_0->RAMn[MB_OFFSET_0] & (uint32_t)CAN_WMBn_CS_DLC_MASK)
																	>> CAN_WMBn_CS_DLC_SHIFT);

			RxMsg.Id_Type = (uint8_t)((CAN_0->RAMn[MB_OFFSET_0] & (uint32_t)CAN_WMBn_CS_IDE_MASK)\
																				>> CAN_WMBn_CS_IDE_SHIFT);


			/* save data */
			rxData[NO_0]	=	CAN_0->RAMn[MB_OFFSET_2];
			/* For byte's swapping*/
			RxMsg.dataBuff[NO_3] =	(uint8_t)((rxData[NO_0] & CAN_MASK_MB_3_BYTE));
			RxMsg.dataBuff[NO_2] = (uint8_t)((rxData[NO_0] & CAN_MASK_MB_2_BYTE) >> CAN_SHIFT_TX_2_BYTE);
			RxMsg.dataBuff[NO_1] = (uint8_t)((rxData[NO_0] & CAN_MASK_MB_1_BYTE) >> CAN_SHIFT_TX_1_BYTE);
			RxMsg.dataBuff[NO_0] = (uint8_t)((rxData[NO_0] & CAN_MASK_MB_0_BYTE) >> CAN_SHIFT_TX_0_BYTE);

			rxData[NO_1] 	= 	CAN_0->RAMn[MB_OFFSET_3];
			/* For byte's swapping*/
			RxMsg.dataBuff[NO_7] = (uint8_t)((rxData[NO_1] & CAN_MASK_MB_3_BYTE));
			RxMsg.dataBuff[NO_6] = (uint8_t)((rxData[NO_1] & CAN_MASK_MB_2_BYTE) >> CAN_SHIFT_TX_2_BYTE);
			RxMsg.dataBuff[NO_5] = (uint8_t)((rxData[NO_1] & CAN_MASK_MB_1_BYTE) >> CAN_SHIFT_TX_1_BYTE);
			RxMsg.dataBuff[NO_4] = (uint8_t)((rxData[NO_1] & CAN_MASK_MB_0_BYTE) >> CAN_SHIFT_TX_0_BYTE);

			/*Reading the message ID*/
			rxData[NO_2] = CAN_0->RAMn[MB_OFFSET_0];
			rxData[NO_3] = CAN_0->RAMn[MB_OFFSET_1];

			if( (rxData[NO_2] & CAN0_RX_FIFO_IDE_MASK) != CAN_CLR){
				RxMsg.Msg_ID  =(rxData[MB_OFFSET_3]) & CAN0_RX_FIFO_EXT_MASK;
			}else{
				RxMsg.Msg_ID  = rxData[MB_OFFSET_3] >> CAN0_RX_FIFO_STD_SHIFT;
			}
			
			/* to be implemented in CANIF */
			CanIf_RxIndication(&RxMsg);

		}
		else if (msgNbr==CAN_RX_BUFF_ALMOST_FULL)
		{
			/* Change BUS state to FIFO Warning */
			CAN_Bus_RX_state.RxFifo_st = CAN_FIFO_ALMOST_FULL;
		}
		else if (msgNbr==CAN_RX_BUFF_OVERFLOW)
		{
			/* Change BUS state to Overflow */
			CAN_Bus_RX_state.RxFifo_st = CAN_FIFO_OVERFLOW;
		}
		/*Check whether the interrupt cause is transmit and for valid transmit buffer number*/
		/*else if(msgNbr==CANT_TXBUFFSTRT)*/
		else if(msgNbr>=CANT_TXBUFFSTRT && msgNbr < CANT_MAXMB_CNT)
		{
			/* To be implemented in CANIF */
			/* Tx callback function */
			CanIf_TxIndication();
			CANT_LastMsgId = CAN_CLR;
		}
		else
		{
			/* Do nothing */
		}

		/* Clear the corresponding message buffer interrupt flag*/
		CAN_0->IFLAG1 = (CAN_0->IFLAG1) | ( ((uint32_t)bit_shift_NO_1) << msgNbr);
	}
	else
	{
		/* Do nothing */
	}
}

/**************************************************************************************************
** Function name : CANT_iChkErrorSt
** Description   : Check the Error state of the CAN bus
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
static void CANT_iChkErrorSt(void)
{
	if(((CAN_0->ESR1 & CANT_BUSOFF_INT)>>CAN_ESR1_BOFFINT_SHIFT ) == CAN_SET)
	{
		 /* Change CAN state to BusOff state */
		CAN_Bus_RX_state.CANbus_st = CAN_BUS_OFF;

		/*Clearing the BUS OFF interrupt*/
		CAN_0->ESR1 = (uint32_t)(CAN_0->ESR1 | CAN_ESR1_BOFFDONEINT_MASK);

	}else{
		/* Do Nothing */
	}

	/* Clear all other interrupts in ERRSTAT register (Error, Bus-off, Wakeup) */
	CAN_0->ESR1 = (uint32_t)CANT_ALL_INT;

	/*  ensure the flags are cleared before continuing. */
	(void)(CAN_0->ESR1);
}

/**************************************************************************************************
** Function name : CANT_TxMsg
** Description   : Initialize the RAM area to transmit the message.
** Parameter     : CAT_ID				Specifies the CAN_ID
** 				   CANT_DataLen			No of data to transmit
** 				   CANT_DataPtr			Pointer to a Buffer
** 				   CANT_XTD				Specifies the CAN types, Standard or Extended.
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CAN0_TxMsg(uint32_t CANT_ID, uint32_t CANT_DataLen,const uint8_t* CANT_DataPtr,
																		CANT_IDFormat_e CANT_XTD, uint8_t MesgBuffIndx)
{
	uint32_t TempCal;

	if(CANT_DataPtr != NULL)
	{
		if((uint8_t)CANT_XTD == CAN_FRAME_EXT)
		{
			/* IDE=1: Extended ID */
			CAN_0->RAMn[ ((CANT_TXBUFFSTRT + MesgBuffIndx)*MSG_BUF_SIZE) + NO_0] = ((uint32_t)NO_1 << CANT_IDE_MASK);
			/* Get message id from rx message table */
            CAN_0->RAMn[((CANT_TXBUFFSTRT + MesgBuffIndx)*MSG_BUF_SIZE) + NO_1] = CAN0_RX_FIFO_EXT_MASK & (uint32_t)(CANT_ID);
		}
		else
		{
			/* Get message id from rx message table */
			CAN_0->RAMn[((CANT_TXBUFFSTRT + MesgBuffIndx)*MSG_BUF_SIZE) + NO_1] =(uint32_t)(CANT_ID<<CANT_MSGID_MASK);
		}

		/* Fill data bytes in message buffer */
		CAN_0->RAMn[((CANT_TXBUFFSTRT + MesgBuffIndx)*MSG_BUF_SIZE) + NO_2] = \
												(uint32_t)(CANT_DataPtr[NO_3]|
												((uint32_t)CANT_DataPtr[NO_2]<<CAN_SHIFT_MB_2_BYTE)|
												((uint32_t)CANT_DataPtr[NO_1]<<CAN_SHIFT_TX_1_BYTE)|
												((uint32_t)CANT_DataPtr[NO_0]<<CAN_SHIFT_MB_0_BYTE));
		CAN_0->RAMn[((CANT_TXBUFFSTRT + MesgBuffIndx)*MSG_BUF_SIZE) + NO_3] = \
												(uint32_t)(CANT_DataPtr[NO_7]|
												((uint32_t)CANT_DataPtr[NO_6]<<CAN_SHIFT_MB_2_BYTE)| \
												((uint32_t)CANT_DataPtr[NO_5]<<CAN_SHIFT_TX_1_BYTE)|
												((uint32_t)CANT_DataPtr[NO_4]<<CAN_SHIFT_MB_0_BYTE));

		TempCal = ((uint32_t)(((uint32_t)(CANT_DataLen))<<CAN_WMBn_CS_DLC_SHIFT));

		TempCal = TempCal | (uint32_t)CANT_DLC_MASK_SHIFT;

		/* Get dlc from rx message table and enable transmit */
		CAN_0->RAMn[((CANT_TXBUFFSTRT + MesgBuffIndx)*MSG_BUF_SIZE) + NO_0] =
									CAN_0->RAMn[((CANT_TXBUFFSTRT + MesgBuffIndx)*MSG_BUF_SIZE) + NO_0] | TempCal;

		CANT_LastMsgId = CANT_ID;
	}
	else
	{
		/* Do Nothing */
	}
		
}

/**************************************************************************************************
** Function name : CANT_Sleep
** Description   : Configures the CAN to wakeup upon RX message
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CANT_WakeupInit(void)
{
	/* Enter into Freeze mode*/
	CANT_Freeze_Enter();

	/* Wakeup match event is enabled */
    CAN_0->CTRL1_PN = (uint32_t)( (CAN_0->CTRL1_PN) | CAN_CTRL1_PN_WUMF_MSK_MASK);

    /* ID Filter 1 for Pretended Networking filtering */
    CAN_0->FLT_ID1 = (uint32_t)(Rx_Fifo_Filter[NO_1].id);

    /*Enter to Pretended Network Mode*/
	CAN_0->MCR = (uint32_t)( (CAN_0->MCR) | CAN_MCR_PNET_EN_MASK);

    /* Exit from Freeze mode*/
	CANT_Freeze_Exit();
}

/**************************************************************************************************
** Function name : CANT_Bus_St
** Description   : Returns the CAN bus status
** Parameter     : void
** Return value  : CAN bus state
** Remarks       : None
**************************************************************************************************/
uint8_t CANT_Bus_St(void)
{
	uint8_t Bus_state;
	/*Checking is CAN bus is in OFF state*/
	if(CAN_Bus_RX_state.CANbus_st == CAN_BUS_OFF){
		Bus_state = CAN_BUS_OFF;
	}else{
		/*Copying the IDLE value to local variable*/
		Bus_state = ((uint8_t)((CAN_0->ESR1) & CAN_ESR1_IDLE_MASK) >> CAN_ESR1_IDLE_SHIFT);
	}
	return Bus_state;
}

/**************************************************************************************************
** Function name : Enter Freeze mode
** Description   : Enter into Freeze mode
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CANT_Freeze_Enter(void)
{
	uint32_t Timeout = CAN_CLR;

    /* Enter the freeze mode */
    CAN_0->MCR = (uint32_t)((CAN_0->MCR & ~CAN_MCR_FRZ_MASK)  | CAN_MCR_FRZ(CAN_ENABLE_FREEZE));
    CAN_0->MCR = (uint32_t)((CAN_0->MCR & ~CAN_MCR_HALT_MASK) | CAN_MCR_HALT(CAN_REQ_FREEZE));

    /* Wait until disable mode acknowledged */
    while( (((CAN_0->MCR & CAN_MCR_FRZACK_MASK) >> CAN_MCR_FRZACK_SHIFT) == CAN_CLR) &&
    													(CAN0_TIMEOUT_CFG > Timeout)){
    	Timeout++;
    }
}

/**************************************************************************************************
** Function name : Exit Freeze mode
** Description   : Exit from Freeze mode
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CANT_Freeze_Exit(void)
{
	uint32_t Timeout = CAN_CLR;

    /* Exit freeze mode */
    CAN_0->MCR =  (uint32_t)((CAN_0->MCR & ~CAN_MCR_HALT_MASK));
    CAN_0->MCR = (uint32_t)((CAN_0->MCR & ~CAN_MCR_FRZ_MASK));

    /* Wait until disable mode acknowledged */
    while( (((CAN_0->MCR & CAN_MCR_FRZACK_MASK) >> CAN_MCR_FRZACK_SHIFT) != CAN_CLR) &&
    													(CAN0_TIMEOUT_CFG > Timeout)){
    	Timeout++;
    }
}

/**************************************************************************************************
** Function name : CANT_EnInterrupt
** Description   : Enable the CAN interrupt
** Parameter     : void
** Return value  : None
** Remarks       : None
**************************************************************************************************/
void CANT_EnInterrupt(void)
{
	/* Enable can0 interrupt */
    S32_NVIC_0->ISER[((uint32_t)CAN0_ORed_IRQn) >> CAN_NVIC_HDLR_SHIFT] =
    		((uint32_t)NO_1 << ((uint32_t)(CAN0_ORed_IRQn) & CAN_NVIC_HDLR_MASK));
    S32_NVIC_0->ISER[((uint32_t)CAN0_Error_IRQn) >> CAN_NVIC_HDLR_SHIFT] =
    		((uint32_t)NO_1 << ((uint32_t)(CAN0_Error_IRQn) & CAN_NVIC_HDLR_MASK));
    S32_NVIC_0->ISER[((uint32_t)CAN0_ORed_0_15_MB_IRQn) >> CAN_NVIC_HDLR_SHIFT] =
    		((uint32_t)NO_1 << ((uint32_t)(CAN0_ORed_0_15_MB_IRQn) &(uint32_t)CAN_NVIC_HDLR_MASK));
    S32_NVIC_0->ISER[((uint32_t)CAN0_ORed_16_31_MB_IRQn) >> CAN_NVIC_HDLR_SHIFT] =
    		((uint32_t)NO_1 <<((uint32_t)(CAN0_ORed_16_31_MB_IRQn) &(uint32_t)CAN_NVIC_HDLR_MASK));
    S32_NVIC_0->ISER[((uint32_t)CAN0_Wake_Up_IRQn) >> CAN_NVIC_HDLR_SHIFT] =
    		((uint32_t)NO_1 << ((uint32_t)(CAN0_Wake_Up_IRQn) & (uint32_t)CAN_NVIC_HDLR_MASK));
}

/**************************************************************************************************
** Function name : CANT_DisInterrupt
** Description   : Disable the CAN interrupt
** Parameter     : void
** Return value  : None
** Remarks       : None
**************************************************************************************************/
void CANT_DisInterrupt(void)
{
	/* Disable can0 interrupt */
    S32_NVIC_0->ICER[((uint32_t)CAN0_ORed_IRQn) >> CAN_NVIC_HDLR_SHIFT] =
    		((uint32_t)NO_1 << ((uint32_t)(CAN0_ORed_IRQn) & CAN_NVIC_HDLR_MASK));
    S32_NVIC_0->ICER[((uint32_t)CAN0_Error_IRQn) >> CAN_NVIC_HDLR_SHIFT] =
    		((uint32_t)NO_1 << ((uint32_t)(CAN0_Error_IRQn) & CAN_NVIC_HDLR_MASK));
    S32_NVIC_0->ICER[((uint32_t)CAN0_ORed_0_15_MB_IRQn) >> CAN_NVIC_HDLR_SHIFT] =
    		((uint32_t)NO_1 << ((uint32_t)(CAN0_ORed_0_15_MB_IRQn) &(uint32_t)CAN_NVIC_HDLR_MASK));
    S32_NVIC_0->ICER[((uint32_t)CAN0_ORed_16_31_MB_IRQn) >> CAN_NVIC_HDLR_SHIFT] =
    		((uint32_t)NO_1 <<((uint32_t)(CAN0_ORed_16_31_MB_IRQn) &(uint32_t)CAN_NVIC_HDLR_MASK));
    S32_NVIC_0->ICER[((uint32_t)CAN0_Wake_Up_IRQn) >> CAN_NVIC_HDLR_SHIFT] =
    		((uint32_t)NO_1 << ((uint32_t)(CAN0_Wake_Up_IRQn) & (uint32_t)CAN_NVIC_HDLR_MASK));
}

/**************************************************************************************************
** Function name : CANT_Enable
** Description   : Enable the CAN module
** Parameter     : void
** Return value  : None
** Remarks       : None
**************************************************************************************************/
void CANT_Enable(void)
{
	uint32_t Timeout = CAN_CLR;

	/* Check for low power mode */
    if( CAN_SET == ((CAN_0->MCR & CAN_MCR_LPMACK_MASK) >> CAN_MCR_LPMACK_SHIFT))
    {
        /* Enable clock */
    	CAN_0->MCR = (CAN_0->MCR & ~CAN_MCR_MDIS_MASK) | CAN_MCR_MDIS(CAN_CLR);
    	CAN_0->MCR = (CAN_0->MCR & ~CAN_MCR_FRZ_MASK) | CAN_MCR_FRZ(CAN_CLR);
    	CAN_0->MCR = (CAN_0->MCR & ~CAN_MCR_HALT_MASK) | CAN_MCR_HALT(CAN_CLR);

        /* Wait until enabled */
        while ( (CAN_CLR != ((CAN_0->MCR & CAN_MCR_NOTRDY_MASK) >> CAN_MCR_NOTRDY_SHIFT)) &&
        		(CAN0_TIMEOUT_CFG > Timeout) )
        {
        	Timeout++;
        }
    }
	else 
	{
		/* Do Nothing */
	}
}

/**************************************************************************************************
** Function name : CANT_Disable
** Description   : Disable the CAN module
** Parameter     : void
** Return value  : None
** Remarks       : None
**************************************************************************************************/
void CANT_Disable(void)
{
	uint32_t Timeout = CAN_CLR;

    /* To access the memory mapped registers */
    /* Enter disable mode (hard reset). */
    if( CAN_CLR == ((CAN_0->MCR & CAN_MCR_MDIS_MASK) >> CAN_MCR_MDIS_SHIFT))
    {
        /* Clock disable (module) */
    	CAN_0->MCR = (CAN_0->MCR & ~CAN_MCR_MDIS_MASK) | CAN_MCR_MDIS(CAN_SET);

        /* Wait until disable mode acknowledged */
        while ( (CAN_CLR == ((CAN_0->MCR & CAN_MCR_LPMACK_MASK) >> CAN_MCR_LPMACK_SHIFT)) &&
        		(CAN0_TIMEOUT_CFG > Timeout)) {
        	Timeout++;
        }
    }
	else 
	{
		/* Do Nothing */
	}
}

// Enrico:
void CANT_HandleError( void )
{
	CANT_iChkErrorSt();
}

/*******************************************************************************
** Function name : System_sleep
** Description   : Makes the MCU to enter sleep mode
** Parameter     : void
** Return value  : void
** Remarks       : None
*******************************************************************************/
void System_sleep(void)
{
	CANT_WakeupInit();
	/*Allowing very low power*/
    SMC->PMPROT =  (uint32_t)((SMC->PMPROT & ~SMC_PMPROT_AVLP_MASK) | SMC_PMPROT_AVLP(NO_1));



     /* Setting the Stop Mode Control to Normal stop*/
    SMC->PMCTRL =  (uint32_t)((SMC->PMCTRL & ~SMC_PMCTRL_STOPM_MASK) | SMC_PMCTRL_STOPM(NO_0));



     /* Configuring -Stop with system clock disabled and bus clock enabled*/
    SMC->STOPCTRL = (uint32_t)( (SMC->STOPCTRL) | SMC_STOPCTRL_STOPO(NO_2));



    /* Set the SLEEPDEEP bit to enable deep sleep mode (STOP)*/
    S32_SCB->SCR |= S32_SCB_SCR_SLEEPDEEP_MASK;



    /*Entering to the sleep mode with WAIT FOR INTERRUPT*/
    sleepmode();
}
