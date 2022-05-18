/**************************************************************************************************
** Copyright (c) 2018 Embitel
**
** This software is the property of Embitel.
** It can not be used or duplicated without Embitel authorization.
**
** ------------------------------------------------------------------------------------------------
** File Name     : CANT.c
** Module Name   : CANT
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
** V01.00 06/11/2018
** - Baseline Created
** ------------------------------------------------------------------------------------------------
**
**
**************************************************************************************************/
/************************************** Inclusion files ******************************************/

#ifndef CANT_H_
#define CANT_H_
#include "device_registers.h"
#include "CANT_Cfg.h"
#include "S32K144.h"
#include "stddef.h"
#include "CanIf.h"

/********************************* Declaration of global types ***********************************/

/* macros for masking and status */
#define sleepmode()							{\
												__asm volatile("wfi");\
											}
#define CANT_INIT            					  0U
#define CANT_ACTIVE          					  1U
#define CANT_BUSOFF          					  2U
#define CANT_MAXMB_CNT							  32U
#define CANT_ID_EXT_MASK                          0x3FFFFU
#define CANT_ID_EXT_SHIFT                         0U
#define CANT_ID_STD_MASK                          0x1FFC0000U
#define CANT_ID_STD_SHIFT                         18U
#define CANT_BUSOFF_INT                           (0x0004U)
//#define CANT_ALL_INT                              (0x0007U)
#define CANT_ALL_INT                              (CAN_ESR1_ERROVR_MASK|CAN_ESR1_ERRINT_FAST_MASK|CAN_ESR1_RWRNINT_MASK|CAN_ESR1_TWRNINT_MASK|CAN_ESR1_BOFFINT_MASK|CAN_ESR1_BOFFINT_MASK|CAN_ESR1_BOFFDONEINT_MASK|CAN_ESR1_ERRINT_MASK) // Enrico changed ISR Mask
#define CANT_MSGID_MASK                           18U
#define CANT_IDE_MASK                             21U
#define CANT_DLC_MASK_SHIFT						  0x0C400000
#define CANT_DLC_MASK(x) 						  (((uint32_t) \
								(((uint32_t)(x))<<CAN_WMBn_CS_DLC_SHIFT))|CANT_DLC_MASK_SHIFT)
#define MSG_BUF_SIZE                              4U
#define MSG_BUF_TRANSMIT						  16U

#define CAN_RX_BUFF_START						  5U
#define CAN_RX_BUFF_ALMOST_FULL					  6U
#define CAN_RX_BUFF_OVERFLOW					  7U
#define CANT_TXBUFFSTRT 						  25U
#define MIN_PRE_VALUE							  0u /* */
#define MAX_PRE_VALUE							  4U

#define CAN0_TIMEOUT_CFG						  (uint32_t)300u

#define RX_FIFO_CFG								 0x05u /*RFFN->gives 48 filter element*/

#define CAN_ID_EXT_MASK                          0x3FFFFu
#define CAN_ID_EXT_SHIFT                         0u
#define CAN_ID_EXT_WIDTH                         18u

#define CAN_ID_STD_MASK                          0x1FFC0000u
#define CAN_ID_STD_SHIFT                         18u
#define CAN_ID_STD_WIDTH                         11u

#define CAN_NULL								0u

/*Null pointer */
#define     CANIL_NULL_PTR						((void *)0)

#define CANT_TX_STATE()							((uint8_t)((CAN0->ESR1) & \
												CAN_ESR1_TX_MASK) >> CAN_ESR1_TX_SHIFT);
#define CAN_TX_IDLE								0

#define NO_RX_FILTER_ELEMENT					 4U

#define RX_FILTER_IDE_1							CANT_FUNC_REQ_ID // Enrico
#define RX_FILTER_IDE_2							0x95u
#define RX_FILTER_IDE_3							0x7DF01u

#define CAN_FRAME_STD							0u
#define CAN_FRAME_EXT							1u

#define CANT_PRESCALAR_FAC						750u

/* MB 0-5 was occupied by RX fifo Engine, Remaining 6-31 MB was used for Filter
So starting filter MB is 6, And Each MB has 4 Dword (32-Bit), So Fiter base =6*4=0x18 */
#define CAN_FIFO_FILTER_BASE					0x18u

#define CAN_RX_FILTER_IDE_SHIFT					30U
#define CAN_RX_FILTER_STD_SHIFT					19U
#define CAN_RX_FILTER_EXT_SHIFT					1U

#define CAN_RXFGMASK_FGM_CFG					0x7FFFFFFEU

#define CAN_BUFMG_ID5						0x05u
#define CAN_BUFMG_ID8						0x08u

#define CAN_FIFO_IDLE						0x0U
#define CAN_FIFO_ALMOST_FULL				0x01U
#define CAN_FIFO_OVERFLOW					0x02U
#define CAN_BUS_BUSY						0x0U
#define CAN_BUS_IDLE						0x01U
#define CAN_BUS_OFF							0x02U

#define MAX_NUM_OF_MB						32U
/*1 MB has 4Dword, So total DWORD are 32*4*/
#define MAX_NUM_OF_MB_DWORD					128U
#define MB_OFFSET_0							0U
#define MB_OFFSET_1							1U
#define MB_OFFSET_2							2U
#define MB_OFFSET_3							3U

#define CAN0_RX_FIFO_IDE_MASK				0x0200000U
#define CAN0_RX_FIFO_EXT_MASK				0x1FFFFFFFU
#define CAN0_RX_FIFO_STD_SHIFT				18u

#define CAN0_RX_TEMP_BUFF					0x14u
#define CAN_SOSCDIV2_CLK					0x0u
#define CAN_SYSCLK							0x01u
#define CAN_DISABLE_CAN_MODULE				0x0u
#define CAN_ENABLE_CAN_MODULE				0x01u
#define CAN_DISABLE_FREEZE					0x0u
#define CAN_ENABLE_FREEZE					0x01u
#define CAN_NO_REQ_FREEZE					0x0u
#define CAN_REQ_FREEZE						0x01u
#define CAN_NO_SOFTRST_REQ					0x0u
#define CAN_SOFTRST_REQ						0x01u
#define CAN_FD_DISABLE						0x0u
#define CAN_FD_ENABLE						0x01u
#define CAN_EXT_BTF_DISABLE					0x0u
#define CAN_EXT_BTF_ENABLE					0x01u
#define CAN_ISO_FD_DISABLE					0x0U
#define CAN_ISO_FD_ENABLE					0x01U
#define CAN_USR_MODE						0x0U
#define CAN_SUPV_MODE						0x01U
#define CAN_LOM_DISABLE						0x0U
#define CAN_LOM_ENABLE						0x01U
#define CAN_LBM_DISABLE						0x0U
#define CAN_LBM_ENABLE						0x01U
#define CAN_IDAM_FORMAT_A					0x0U
#define CAN_RX_FIFO_INDI_DISABLE			0x0U
#define CAN_RX_FIFO_INDI_ENABLE				0x01U
#define CAN_VLP_NOT_ALLOW					0x0U
#define CAN_VLP_ALLOW						0x01U
#define CAN_PM_RUNN							0x0U
#define CAN_MB_DWORD_SIZE					0x04U

#define CAN_SET								0x01U
#define CAN_CLR								0x0U

#define CAN_MASK_MB_3_BYTE					0x000000FFUL
#define CAN_MASK_MB_2_BYTE					0x0000FF00UL
#define CAN_MASK_MB_1_BYTE					0x00FF0000UL
#define CAN_MASK_MB_0_BYTE					0xFF000000UL

#define CAN_SHIFT_MB_3_BYTE					24u
#define CAN_SHIFT_MB_2_BYTE					8u
#define CAN_SHIFT_MB_1_BYTE					8U
#define CAN_SHIFT_MB_0_BYTE					24U

#define CAN_SHIFT_TX_2_BYTE					8u
#define CAN_SHIFT_TX_1_BYTE					16
#define CAN_SHIFT_TX_0_BYTE					24U

#define CAN_NVIC_HDLR_MASK 					0x1FU
#define CAN_NVIC_HDLR_SHIFT					0x05u

#define ID_2								0x02u
#define ID_3								0x03u
#define ID_4								0x04u
#define ID_5								0x05u
#define ID_6								0x06u

#define NO_0								0x0u
#define NO_1								0x01u
#define NO_2								0x02u
#define NO_3								0x03u
#define NO_4								0x04u
#define NO_5								0x05u
#define NO_6								0x06u
#define NO_7								0x07u


#define bit_shift_NO_1						01UL

/* CAN standard or extended ID */
typedef enum
{
	CANT_STANDARD = 0,
	CANT_EXTENDED
}CANT_IDFormat_e;

/* For Receive frames */
typedef struct
{
    uint32_t canID;                     /* CAN receive message ID */
    uint8_t idType;                     /* ID type : Standard or extended */
    uint8_t dlcRx;                      /* data length */
    /* Pointer to call back for CAN message */
    void (*funCanAppPtr)(const uint8_t rxData[]);
    /* Pointer to callback function incase of TimeOut */
    void (*funCanTOPtr)(void);
}CANT_RxMsgConfType;                  /* CAN message configuration structure for receive frames */

/* For Transmit frames */
typedef struct
{
	uint32_t canID;         /* CAN transmit message ID */
	uint8_t idType;         /* ID type : Standard or extended */
	uint8_t dlc;            /* data length */
    /* Pointer to call back for CAN message */
    void (*funCanAppPtr)(void);
}CANT_TxMsgConfType;        /* CAN message configuration structure for transmit frames */

/*! @brief CAN Rx FIFO ID filter table structure
 * Implements : flexcan_id_table_t_Class
 */
typedef struct {
	uint8_t FrameType;    /*!< 0->Standard, 1->Extended*/
    uint32_t id;       /*!< Rx FIFO ID filter element*/
} can_id_table_t;



/*! @brief CAN status structure
 * Implements : CAN_Driver Status
 * Brief: 		This structure gives the status of CAN bus and RX Mailbox
 */
typedef struct {
	uint8_t CANbus_st;
	uint8_t RxFifo_st;
}CAN_Dr_t;

/****************************** External links of global constants *******************************/

extern CAN_Type *CAN_0;
const can_id_table_t Rx_Fifo_Filter[NO_RX_FILTER_ELEMENT];
/************************** Function declarations*************************************************/

/**************************************************************************************************
** Function name : CANT_Init
** Description   : Initialization of CAN
** Parameter     : CAN_Baudrate	->Initialize the CAN with Baudrate.
** Return value  : void
** Remarks       : None
**************************************************************************************************/
extern void CANT_Init(uint32_t CAN_Baudrate,const CANT_RxMsgConfigType  *ptrto_CANIL_TxRxMessageTable, uint8_t NumofRxMsgs);

// Enrico
extern void CANT_MainLoop( void );
/**************************************************************************************************
** Function name : CANT_RxMsgIdSet
** Description   : Configure the Rx message id
** Parameter     : RxMsgId				Specifies the CAN_ID
** 				   MsgFormat			Specifies the CAN types, Standard or Extended.
** 				   FitIdx				Index to write the ID
** Return value  : void
** Remarks       : global variables used, side effects
**************************************************************************************************/
void CANT_RxMsgIdSet(uint32_t CANT_RxMsgId,CANT_IDFormat_e CANT_MsgFormat,uint8_t CANT_FitIdx);

/**************************************************************************************************
** Function name : CANT_TxMsg
** Description   : Transmits the CAN frame
** Parameter     : Index of the frame in message table data buffer array
** Return value  : void
** Remarks       : None
**************************************************************************************************/
extern void CAN0_TxMsg(uint32_t CANT_ID, uint32_t CANT_DataLen,const uint8_t* CANT_DataPtr,
																			CANT_IDFormat_e CANT_XTD, uint8_t MesgBuffIndx);

/**************************************************************************************************
** Function name : CAN0_ORed_0_15_MB_IRQHandler
** Description   : Isr for a successful transmission or reception for CAN0
** 				   Message Buffers 0-15
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CAN0_ORed_0_15_MB_IRQHandler(void);

/**************************************************************************************************
** Function name : CAN0_ORed_16_31_MB_IRQHandler
** Description   : Isr for a successful transmission or reception for CAN0
** 				   Message Buffers 16-31
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CAN0_ORed_16_31_MB_IRQHandler(void);
/**************************************************************************************************
** Function name : CAN0_Error_IRQHandler
** Description   : Isr interrupts indicating that errors were detected on the
**                 CAN0 bus
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CAN0_Wake_Up_IRQHandler(void);
/**************************************************************************************************
** Function name : CAN0_ORed_IRQHandler
** Description   : Isr for for CAN0 OR'ed interrupts (Bus Off,Transmit Warning,
** 				   Receive Warning)
** Parameter     : void
** Return value  : void
** Remarks       : None
***************************************************************************************************/
void CAN0_ORed_IRQHandler(void);

/**************************************************************************************************
** Function name : CAN0_Error_IRQHandler
** Description   : Isr interrupts indicating that errors were detected on the
**                 CAN0 bus
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CAN0_Error_IRQHandler(void);

/**************************************************************************************************
** Function name : CANT_Sleep
** Description   : Configures the CAN to wakeup upon RX message
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CANT_WakeupInit(void);

/**************************************************************************************************
** Function name : CANT_Bus_St
** Description   : Returns the status of CAN bus
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
extern uint8_t CANT_Bus_St(void);

/**************************************************************************************************
** Function name : Enter Freeze mode
** Description   : Enter into Freeze mode
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CANT_Freeze_Enter(void);

/**************************************************************************************************
** Function name : Exit Freeze mode
** Description   : Exit from Freeze mode
** Parameter     : void
** Return value  : void
** Remarks       : None
**************************************************************************************************/
void CANT_Freeze_Exit(void);
/**************************************************************************************************
** Function name : CANT_EnInterrupt
** Description   : Enable the CAN interrupt
** Parameter     : void
** Return value  : None
** Remarks       : None
**************************************************************************************************/
void CANT_EnInterrupt(void);
/**************************************************************************************************
** Function name : CANT_DisInterrupt
** Description   : Disable the CAN interrupt
** Parameter     : void
** Return value  : None
** Remarks       : None
**************************************************************************************************/
void CANT_DisInterrupt(void);
/**************************************************************************************************
** Function name : CANT_Enable
** Description   : Enable the CAN module
** Parameter     : void
** Return value  : None
** Remarks       : None
**************************************************************************************************/
void CANT_Enable(void);
/**************************************************************************************************
** Function name : CANT_Enable
** Description   : Disable the CAN module
** Parameter     : void
** Return value  : None
** Remarks       : None
**************************************************************************************************/
void CANT_Disable(void);
/*******************************************************************************
** Function name : System_sleep
** Description   : Makes the MCU to enter sleep mode
** Parameter     : void
** Return value  : void
** Remarks       : None
*******************************************************************************/


// Enrico:
void CANT_HandleError( void );


void System_sleep(void);
#endif /* CANT_H_ */
