/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name 	: CanTp.c
** Module Name 	: CanTp
** -------------------------------------------------------------------------------------------------
**
** Documentation reference : EME-17ST013-12070.01 (SWLLD CanTp)
**
** -------------------------------------------------------------------------------------------------
****************************************************************************************************
** R E V I S I O N H I S T O R Y
****************************************************************************************************
** V01.00 13/07/2019
** - Baseline Created
**
***************************************************************************************************/
/*************************** Inclusion files ******************************************************/
#include "CanTp.h"
#include "CanIf.h"
#include "ISOUDS.h"
/********************** Declaration of local symbol and constants *********************************/
/****************************** Declaration of exported variables *********************************/
/****************************** Declaration of exported constants *********************************/
/********************************* Declaration of local macros ************************************/
/********************************* Declaration of local types *************************************/
/******************************* Declaration of local variables ***********************************/
static VAR(uint8, AUTOMATIC) ISOTP_FirstFCRcvd;
static VAR(uint8, AUTOMATIC) ISOTP_BlkSize;
static VAR(uint16, AUTOMATIC) ISOTP_STmin;
static VAR(uint16, AUTOMATIC) ISOTP_TpBuffIdx;
static VAR(uint16, AUTOMATIC) ISOTP_BSLen;
static volatile VAR(uint32, AUTOMATIC) ISOTP_NATime;
static volatile VAR(uint32, AUTOMATIC) ISOTP_NBTime;
static volatile VAR(uint32, AUTOMATIC) ISOTP_NCTime;
static VAR(uint32, AUTOMATIC) ISOTP_TimeOutNA;
static VAR(uint32, AUTOMATIC) ISOTP_TimeOutNB;
static VAR(uint32, AUTOMATIC) ISOTP_TimeOutNC;
static VAR(ISOTP_CfgType, AUTOMATIC) ISOTP_FrmCfg;
static VAR(ISOTP_CfgType, AUTOMATIC)  ISOTP_FirstFrmCfg;
static VAR(uint8, AUTOMATIC) ISOTP_NWLSt;
static VAR(CanIf_Msg_Type, AUTOMATIC) ISOTP_canfrm;
static VAR(ISOTP_App_CfgType, AUTOMATIC)  ISOTP_TP_Cfg;
static VAR(uint8, AUTOMATIC) ISOTP_St;
static VAR(uint8, AUTOMATIC) ISOTP_StMultiFrame;
static VAR(uint8, AUTOMATIC) ISOTP_BuffFlowCtrl[3U] = {0x30U, 0x00U, 0x00U};
static VAR(ISOTP_App_CfgType, AUTOMATIC) ISOTP_TP_flowctrl =
{
  (uint8 *)&ISOTP_BuffFlowCtrl[0U], 3U
};

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/**************************** Internal functions declarations *************************************/
static FUNC(void, CAN_CODE) ISOTP_iTmrMon (void);
static FUNC(void, CAN_CODE) ISOTP_Rst (void);
#if (ISOTP_ST_PADDING == ISOTP_PAD_REQUIRED)
static FUNC(void, CAN_CODE) ISOTP_PrfrmPad (VAR(uint16, AUTOMATIC) byteIdx);
#endif


/******************************** Function definitions ********************************************/

/***************************************************************************************************
** Function                 : ISOTP_Init

** Description              : Initialization of CAN TP parameters

** Parameter                : None

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
FUNC(void, CAN_CODE) ISOTP_Init (void)
{
    /* Initialize to IDLE state */
    ISOTP_St = (uint8)ISOTP_IDLE;
    ISOTP_NWLSt = (uint8)ISOTP_NWLST_IDLE;

    /* Initialize the counters to O */
    ISOTP_NATime = (uint32)ISOTP_ZERO;
    ISOTP_NBTime = (uint32)ISOTP_ZERO;
    ISOTP_NCTime = (uint32)ISOTP_ZERO;

    /* Initialize the first FC frame received to ISOTP_FALSE */
    ISOTP_FirstFCRcvd = (uint8)ISOTP_ZERO;

    /* Initialize the Tp buffer Index to 0 */
    ISOTP_TpBuffIdx = (uint16)ISOTP_ZERO;
	
    ISOTP_StMultiFrame = ISOTP_FALSE;

    /* set the CAN ID tx parameters as per configuration */
    ISOTP_canfrm.Msg_ID = (uint32)ISOTP_TXOBD_CANID;    
}

/***************************************************************************************************
** Function                 : ISOTP_RxMsgCbk

** Description              : Receive callback function of Diagnostic frame

** Parameter rxData         : Data array

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
CanIf_Msg_Type lendata;
FUNC(void, CAN_CODE) ISOTP_RxMsgCbk(P2CONST(CanIf_Msg_Type, AUTOMATIC, CAN_TP) rxFrame)
{
    VAR(uint16, AUTOMATIC)  dataLen;
    VAR(uint16, AUTOMATIC) idx;
    VAR(uint8, AUTOMATIC) cFSeqNum;
    VAR(uint8, AUTOMATIC) frmType;
    VAR(uint8, AUTOMATIC) flwStFC;
    VAR(uint8, AUTOMATIC) RespBuf[3];
    static VAR(uint8, AUTOMATIC) Srv_id;

#if (ISOTP_ST_PADDING != ISOTP_PAD_REQUIRED)
    uint8 processCF;
#endif
    lendata = rxFrame[0];
    
#if (ISOTP_ST_PADDING == ISOTP_PAD_REQUIRED)
    if (rxFrame->DLC == (uint8)ISOTP_EIGHT)
#else
    if (rxFrame->dlc > (uint8)ISOTP_ONE)
#endif
    {
        /* Get the PDU frame Type */
        frmType = rxFrame->dataBuff[ISOTP_ZERO] & (uint8)ISOTP_FRAMEMASK;

        switch (frmType)
        {
            /* Single Frame */
            case ISOTP_SF:
            {
                /* Check if Tx is not in Progress and processing is not in progress */
                if ((ISOTP_NWLSt != (uint8)ISOTP_NWLST_TXINPROG) && 
                                                     (ISOTP_NWLSt != (uint8)ISOTP_NWLST_PROCINPROG))
                {
                    /* Get the Length info */
                    dataLen = (uint16)rxFrame->dataBuff[ISOTP_ZERO] & (uint16)ISOTP_SEQMASK;

                    /* Check if RX in Progress. */
                    if(ISOTP_StMultiFrame == ISOTP_TRUE)
                    {							   
                      /* Store the length info in conf structure */
                      ISOTP_FirstFrmCfg.nBytes = dataLen;
                      
                      for (idx = (uint8)ISOTP_ZERO; idx < dataLen; idx++)
                      {
                         ISOTP_FirstFrmCfg.tpBuff[idx] = rxFrame->dataBuff[idx + (uint8)ISOTP_ONE];
                      }
                        
                        /* Call the message Indication function */
					   	ISOUDS_MsgIndiIm(&ISOTP_FirstFrmCfg);
					}
					else
					{
						/* Check if data length received is valid */
						if ((dataLen > (uint16)ISOTP_ZERO) && (dataLen <= (uint16)ISOTP_SEVEN))
						{
							#if (ISOTP_ST_PADDING != ISOTP_PAD_REQUIRED)
							if (rxFrame->dlc >= (dataLen + ISOTP_ONE))
							#endif
							{
								/* Check if Tp state is not in IDLE */
								if (ISOTP_St != (uint8)ISOTP_IDLE)
								{
									/* reset all the TP counters */
									ISOTP_NATime = (uint32)ISOTP_ZERO;
									ISOTP_NBTime = (uint32)ISOTP_ZERO;
									ISOTP_NCTime = (uint32)ISOTP_ZERO;

                              /* Reset Tp parameters, go to IDLE state */
                              ISOTP_Rst ();
                            }

                            /* Store the length info in conf structure */
                            ISOTP_FrmCfg.nBytes = dataLen;

                            for (idx = (uint8)ISOTP_ZERO; idx < dataLen; idx++)
                            {
                               ISOTP_FrmCfg.tpBuff[idx] = rxFrame->dataBuff[idx + (uint8)ISOTP_ONE];
                            }
								ISOUDS_Conf.srvFrame = (uint8)0;
								/*Check whether the Request Message is Functional or Physical*/
								if(rxFrame->Msg_ID == Diag_FUN_Req)
								{
									/*Call the message Indication function*/
									ISOUDS_MsgIndi(&ISOTP_FrmCfg, ISOTP_FUNC_REQUEST);
								}
								else
								{
									/*Call the message Indication function*/
									ISOUDS_MsgIndi(&ISOTP_FrmCfg, ISOTP_PHY_REQUEST);
								}

                            /* Reset Tp parameters, go to IDLE state */
                            ISOTP_Rst ();
                          }
                        }
                    }
                }
                break;
            }
            
            /* First Frame */
            case ISOTP_FF:
            {
                /* Check if Tx is not in Progress */
                if ((ISOTP_NWLSt != (uint8)ISOTP_NWLST_TXINPROG) && 
                                                     (ISOTP_NWLSt != (uint8)ISOTP_NWLST_PROCINPROG))
                {
                    #if (ISOTP_ST_PADDING != ISOTP_PAD_REQUIRED)
                    if (rxFrame->dlc == (uint8)ISOTP_EIGHT)
                    #endif
                    {
                        /* Get the data length info */
                        dataLen = ((uint16)(((uint16)rxFrame->dataBuff[ISOTP_ZERO] & 
                                             (uint16)ISOTP_SEQMASK) << ISOTP_EIGHT) +
                                             (uint16)rxFrame->dataBuff[ISOTP_ONE]);
                        
                        /* Store the current service ID*/
                        Srv_id = (uint8)rxFrame->dataBuff[ISOTP_TWO];
                        
						/* Set Multiframe Status to TRUE */
						ISOTP_StMultiFrame = ISOTP_TRUE;
						
                        /* Data Length is greater than Buffer size defined */                          
                        if(dataLen <= ISOTP_BUFFSIZE)  
                        {
                        /* Check if data length is valid */
                        if (dataLen > (uint16)ISOTP_SEVEN)
                        {
                            /* Check if Tp state is not in IDLE */
                            if (ISOTP_St != (uint8)ISOTP_IDLE)
                            {
                                /* reset all the TP counters */
                                ISOTP_NATime = (uint32)ISOTP_ZERO;
                                ISOTP_NBTime = (uint32)ISOTP_ZERO;
                                ISOTP_NCTime = (uint32)ISOTP_ZERO;

                                /* Reset Tp parameters, go to IDLE state */
                                ISOTP_Rst ();
                            }                            

                            /* Store the length info in conf structure */
                            ISOTP_FrmCfg.nBytes = dataLen;

                            /* Call the first frame Indication function */
                            flwStFC = ISOTP_FCCTS;
							
							/*Check whether the Request Message is Functional or Physical*/
							if(rxFrame->Msg_ID == Diag_FUN_Req)
							{
								ISOUDS_FFIndi(&ISOTP_FrmCfg, ISOTP_FUNC_REQUEST);
							}
							else
							{
								/*Call the message Indication function*/
								ISOUDS_FFIndi(&ISOTP_FrmCfg, ISOTP_PHY_REQUEST);
							}

                            /* If return value is continue to send(CTS) */
                            if (flwStFC == (uint8)ISOTP_FCCTS)
                            {
                                /* Change state to receive in progress */
                                ISOTP_NWLSt = (uint8)ISOTP_NWLST_RXINPROG;

                                /* Store the received 6 bytes of FF */
                                for (idx = (uint8)ISOTP_ZERO; idx < (uint8)ISOTP_SIX; idx ++)
                                {
                                   ISOTP_FrmCfg.tpBuff[idx] = 
                                                          rxFrame->dataBuff[idx + (uint8)ISOTP_TWO];
                                }

                                ISOTP_TpBuffIdx = idx;

                                /* Decrement the number of bytes by 6 */
                                ISOTP_FrmCfg.nBytes -= (uint16)ISOTP_SIX;

                                ISOTP_FrmCfg.seqNum = (uint8)ISOTP_ZERO;

                                /* Form the Byte 1 of PCI for FC frame Tx */
                                ISOTP_FrmCfg.frmInfo = (uint8)ISOTP_FC | (uint8)ISOTP_FCCTS;

                                /* Set the timer limits */
                                ISOTP_TimeOutNA = 
                                           ((uint32)(ISOTP_iTimeOut[ISOTP_RXIDX].tmrA))* 
                                            (uint32)ISOTP_TIMERLMT;
                                ISOTP_TimeOutNB = 
                                           ((uint32)(ISOTP_iTimeOut[ISOTP_RXIDX].tmrB))* 
                                            (uint32)ISOTP_TIMERLMT;
                                ISOTP_TimeOutNC = 
                                           ((uint32)(ISOTP_iTimeOut[ISOTP_RXIDX].tmrC))* 
                                            (uint32)ISOTP_TIMERLMT;

                                /* Start Timer B */
                                ISOTP_NBTime = (uint32)ISOTP_ONE;

                                /* change the state to Flow control Tx Request */
                                ISOTP_St = (uint8)ISOTP_FCTXREQ;
                                
                                /* Transmit the Flow Control Message. */
                                ISOTP_TxRequest(&ISOTP_TP_flowctrl);
                                
                            }
                            /* If return value is Overflow(OVFLW) */
                            else if (flwStFC == (uint8)ISOTP_FCOVFLW)
                            {
                                /* Form the Byte 1 of PCI for FC frame Tx */
                                ISOTP_FrmCfg.frmInfo = (uint8)ISOTP_FC | (uint8)ISOTP_FCOVFLW;

                                /* Set the timer B limit */
                                ISOTP_TimeOutNB = ((uint32)(ISOTP_iTimeOut[ISOTP_RXIDX].tmrB)) * 
                                                   (uint32)ISOTP_TIMERLMT;

                                /* Start Timer B */
                                ISOTP_NBTime = (uint32)ISOTP_ONE;

                                /* change the state to Flow control Tx Request */
                                ISOTP_St = (uint8)ISOTP_FCTXREQ;

                                /* Change the network status to IDLE */
                                ISOTP_NWLSt = (uint8)ISOTP_NWLST_IDLE;
                            }
                            /* Invalid Value : Incorrect Data length */
                            else
                            {
                                /* Reset the Tp parameters */
                                ISOTP_Rst ();

                                /* Change the network status to IDLE */
                                ISOTP_NWLSt = (uint8)ISOTP_NWLST_IDLE;
                            }
                            
                            
                        }
                        else
                        {
                            /* Reset the Tp parameters */
                            ISOTP_Rst ();
                        }
                      }
                      else
                      {
                      /* Reset the Tp parameters */
                            ISOTP_Rst ();
                      }
                    }
                }
                break;
            }
            
            /* Consecutive frame */
            case ISOTP_CF:
            {
                /* Check if Rx is in Progress */
                if (ISOTP_NWLSt == (uint8)ISOTP_NWLST_RXINPROG)
                {
                    /* Check if Consecutive frame is awaited */
                    if (ISOTP_St == (uint8)ISOTP_CFWAIT)
                    {
#if (ISOTP_ST_PADDING != ISOTP_PAD_REQUIRED)
                        processCF = ISOTP_ZERO;

                        /* Check if last CF is to be received */
                        if (ISOTP_FrmCfg.nBytes <= (uint16)ISOTP_SEVEN)
                        {
                            if (rxFrame->dlc >= ((uint8)ISOTP_FrmCfg.nBytes + ISOTP_ONE))
                            {
                                processCF = ISOTP_ONE;
                            }
                        }
                        /* Not the last CF */
                        else
                        {
                            if (rxFrame->dlc == (uint8)ISOTP_EIGHT)
                            {
                                processCF = ISOTP_ONE;
                            }
                        }

                        if (processCF == ISOTP_ONE)
#endif
                        {
                            /* Get the sequence number */
                            cFSeqNum = rxFrame->dataBuff[ISOTP_ZERO] & (uint8)ISOTP_SEQMASK;

                            /* Stop timer C */
                            ISOTP_NCTime = (uint32)ISOTP_ZERO;

                            /* Check if the received sequence number is correct */
                            if (cFSeqNum == 
                                  ((ISOTP_FrmCfg.seqNum + (uint8)ISOTP_ONE) & (uint8)ISOTP_SEQMASK))
                            {
                                /* Increment to next sequence number - same as cFSeqNum */
                                ISOTP_FrmCfg.seqNum = cFSeqNum;

                                /* change state to consecutive frame received */
                                ISOTP_St = (uint8)ISOTP_CFRX;

                                /* Decrement the nBytes by the number of data bytes 
                                   received in CF */
                                if (ISOTP_FrmCfg.nBytes >= (uint16)ISOTP_SEVEN)
                                {
                                    /* Decrement number of bytes by 7 */
                                    ISOTP_FrmCfg.nBytes -= (uint16)ISOTP_SEVEN;

                                    /* Copy the data received */
                                    for (idx = (uint8)ISOTP_ZERO; idx < (uint8)ISOTP_SEVEN; idx++)
                                    {
                                        ISOTP_FrmCfg.tpBuff[ISOTP_TpBuffIdx + idx] =
                                                          rxFrame->dataBuff[idx + (uint8)ISOTP_ONE];
                                    }

                                    /* Increment the Tp buffer index */
                                    ISOTP_TpBuffIdx += idx;
                                }
                                else
                                {
                                    /* Copy the data received */
                                    for (idx = (uint16)ISOTP_ZERO; idx < ISOTP_FrmCfg.nBytes; idx++)
                                    {
                                        ISOTP_FrmCfg.tpBuff[ISOTP_TpBuffIdx + idx] =
                                                          rxFrame->dataBuff[idx + (uint8)ISOTP_ONE];
                                    }

                                    /* completely received the total number of bytes */
                                    ISOTP_FrmCfg.nBytes = (uint16)ISOTP_ZERO;
                                }

                                /* Decrement the block size length by the number of data bytes - */
                                /*  -  received in CF */
                                ISOTP_BSLen -= (uint8)ISOTP_SEVEN;

                                /* If all the bytes have been received */
                                if (ISOTP_FrmCfg.nBytes == (uint16)ISOTP_ZERO)
                                {
                                    /*Check whether the Request Message is Functional or Physical*/
									if(rxFrame->Msg_ID == Diag_FUN_Req)
									{
										/*Call the message Indication function*/
										ISOUDS_MsgIndi(&ISOTP_FrmCfg, ISOTP_FUNC_REQUEST);
									}
									else
									{
										/*Call the message Indication function*/
										ISOUDS_MsgIndi(&ISOTP_FrmCfg, ISOTP_PHY_REQUEST);
									}
									/* Set Multiframe Status to FALSE */
						            ISOTP_StMultiFrame = ISOTP_FALSE;

                                    /* Reset Tp Parameters and change state to IDLE */
                                    ISOTP_Rst ();
                                }
                                /* another consecutive frame is awaited */
                                else if (ISOTP_BSLen > (uint8)ISOTP_ZERO)
                                {
                                    /* Start timer C */
                                    ISOTP_NCTime = (uint32)ISOTP_ONE;

                                    /* Change state to CF wait */
                                    ISOTP_St = (uint8)ISOTP_CFWAIT;
                                }
                                /* flow control frame is to be transmitted */
                                else if (ISOTP_FrmCfg.nBytes > (uint16)ISOTP_ZERO)
                                {
                                    /* Start timer B */
                                    ISOTP_NBTime = (uint32)ISOTP_ONE;

                                    /* Change state to FC frame TX */
                                    ISOTP_St = (uint8)ISOTP_FCTXREQ;
                                }
                                else
                                {
                                    /* Do nothing */
                                }
                            }
                            /* Incorrect sequence number */
                            else
                            {
                                /* Reset Tp Parameters and change state to IDLE */
                                ISOTP_Rst ();
                                                             
                                RespBuf[ISOTP_ZERO] = (uint8)ISOTP_NEGRES;
                                RespBuf[ISOTP_ONE]  = (uint8)Srv_id;
                                RespBuf[ISOTP_TWO]  = (uint8)ISOTP_RSE;
                                
                                ISOTP_TP_Cfg.dataPtr = &RespBuf[ISOTP_ZERO];
                                ISOTP_TP_Cfg.dataLen = ISOTP_NEGRESPLEN;
                                
                                ISOTP_TxRequest(&ISOTP_TP_Cfg);

                                /* Reset UDS parameters */
                                ISOUDS_Rst ();

                                /* change the state to IDLE */
                                ISOTP_NWLSt = (uint8)ISOTP_NWLST_IDLE;                                
                            }
                        }
                    }
                }
                break;
            }
            
            /* Flow control */
            case ISOTP_FC:
            {
                /* Check if Tx is in Progress */
                if (ISOTP_NWLSt == (uint8)ISOTP_NWLST_TXINPROG)
                {
                    /* Check if Flow control frame is awaited */
                    if (ISOTP_St == (uint8)ISOTP_FCWAIT)
                    {
#if (ISOTP_ST_PADDING != ISOTP_PAD_REQUIRED)
                        if (rxFrame->dlc >= (uint8)ISOTP_THREE)
#endif
                        {
                            /* Check if the Flow status is Continue To Send */
                            if ((rxFrame->dataBuff[ISOTP_ZERO] & 
                                                        (uint8)ISOTP_SEQMASK) == (uint8)ISOTP_FCCTS)
                            {
                                /* Check if First flow control frame is already received or not */
                                if (ISOTP_FirstFCRcvd == (uint8)ISOTP_ZERO)
                                {
                                    /* Update Block Size */
                                    ISOTP_BlkSize = rxFrame->dataBuff[ISOTP_ONE];

                                    /* Check if seperation time is greater than 0x7F and not in the 
                                       range [F1, F9] */
                                    if ((rxFrame->dataBuff[ISOTP_TWO] > (uint8)ISOTP_TIMERLMT1) &&
                                       ((rxFrame->dataBuff[ISOTP_TWO] < (uint8)ISOTP_TIMERLMT2) ||
                                        (rxFrame->dataBuff[ISOTP_TWO] > (uint8)ISOTP_TIMERLMT3)))
                                    {
                                        /* limit values greater than 0x7F to max valid value 
                                           i.e.0x7F */
                                        ISOTP_STmin = 
                                                ((uint16)ISOTP_TIMERLMT1) * (uint16)ISOTP_TIMERLMT;
                                    }
                                    /* If seperation time is in the range [F1, F9] */
                                    else if 
                                        ((rxFrame->dataBuff[ISOTP_TWO] >= (uint8)ISOTP_TIMERLMT2) && 
                                         (rxFrame->dataBuff[ISOTP_TWO] <= (uint8)ISOTP_TIMERLMT3))
                                    {
                                        ISOTP_STmin = ((uint16)rxFrame->dataBuff[ISOTP_TWO]) - 
                                                       (uint16)ISOTP_FRAMEMASK;
                                    }
                                    else
                                    {
                                        ISOTP_STmin = ((uint16)rxFrame->dataBuff[ISOTP_TWO]) * 
                                                       (uint16)ISOTP_TIMERLMT;
                                    }

                                    /* First flow frame received */
                                    ISOTP_FirstFCRcvd = (uint8)ISOTP_ONE;
                                }
                                
                                /* Check if block size is zero */
                                if (ISOTP_BlkSize == (uint8)ISOTP_ZERO)
                                {
                                    /* Transmit all blocks at a time */
                                    ISOTP_BSLen = (uint16)ISOTP_FrmCfg.nBytes;
                                }
                                else
                                {
                                    /* total number of bytes */
                                    ISOTP_BSLen = (uint16)((uint16)ISOTP_BlkSize * 
                                                           (uint8)ISOTP_SEVEN);
                                }

                                /* Stop timer B */
                                ISOTP_NBTime = (uint8)ISOTP_ZERO;

                                /* Request for Tx of CF is put immediately here - so no need of -
                                    - starting timer C here */

                                /* Change the state to Consecutive frame Tx Wait */
                                ISOTP_St = (uint8)ISOTP_CFTXWAIT;

                                /* N_PCI for CF */
                                ISOTP_canfrm.dataBuff[ISOTP_ZERO] = ISOTP_FrmCfg.frmInfo;

                                /* Data of consecutive frame to be transmitted */
                                if (ISOTP_FrmCfg.nBytes < (uint16)ISOTP_SEVEN)
                                {
                                    for (idx = (uint16)ISOTP_ZERO; idx < ISOTP_FrmCfg.nBytes; idx++)
                                    {
                                        ISOTP_canfrm.dataBuff[idx + (uint8)ISOTP_ONE] =
                                                    ISOTP_FrmCfg.tpBuff[ISOTP_TpBuffIdx + idx];
                                    }

#if (ISOTP_ST_PADDING == ISOTP_PAD_REQUIRED)
                                    /* Perform Padding */
                                    ISOTP_PrfrmPad (ISOTP_FrmCfg.nBytes);

                                    ISOTP_canfrm.DLC = (uint8)ISOTP_EIGHT;
#else
                                    ISOTP_canfrm.dlc = (uint8)(ISOTP_FrmCfg.nBytes + ISOTP_ONE);

#endif
                                }
                                else
                                {
                                    for (idx = (uint8)ISOTP_ZERO; idx < (uint8)ISOTP_SEVEN; idx++)
                                    {
                                        ISOTP_canfrm.dataBuff[idx + (uint8)ISOTP_ONE] =
                                                    ISOTP_FrmCfg.tpBuff[ISOTP_TpBuffIdx + idx];
                                    }

                                    ISOTP_canfrm.DLC = (uint8)ISOTP_EIGHT;
                                }

                                /* Start the timer A */
                                ISOTP_NATime = (uint32)ISOTP_ONE;

                                /* Request data link layer for Tx of CF */
                                CANIF_DIAG_TRANSMIT(ISOTP_canfrm);

                            }
                            /* Flow control status is WAIT */
                            else if ((rxFrame->dataBuff[ISOTP_ZERO] & (uint8)ISOTP_SEQMASK) == 
                                                                                  (uint8)ISOTP_FCWT)
                            {
                                /* Re-start the timer B */
                                ISOTP_NBTime = (uint32)ISOTP_ONE;

                                /* Wait for next flow control frame */
                            }
                            /* If Flow status is overflow/ FS is incorrect */
                            else
                            {
                                /* Stop the timer B */
                                ISOTP_NBTime = (uint32)ISOTP_ZERO;

                                /* Reset Tp parameters and change state to IDLE */
                                ISOTP_Rst ();

                                /* Reset UDS parameters */
                                ISOUDS_Rst ();

                                /* Change the network status to IDLE */
                                ISOTP_NWLSt = (uint8)ISOTP_NWLST_IDLE;                                
                            }
                        }
                    }
                }
                break;
            }
            default:
            {
                /* Do Nothing */
                break;
            }
        }
    }
}

/***************************************************************************************************
** Function                 : ISOTP_TxRequest

** Description              : Transmits either single frame or first frame

** Parameter nBytes         : number of bytes to be transmitted

** Parameter txData         : Data array

** Return value             : ISOTP_ISOUDS_TRUE - If tramission request is placed successfully
                              ISOTP_FALSE - If tramission request couldn't be placed

** Remarks                  : None
***************************************************************************************************/
FUNC(uint8, CAN_CODE) ISOTP_TxRequest (P2VAR(ISOTP_App_CfgType, AUTOMATIC,CAN_CODE) ISOTP_MsgCfg)
{
    uint8 retVal;
    uint16 idx;

    /* Check if TP state is idle */
    if ((ISOTP_St == (uint8)ISOTP_IDLE) &&
            (ISOTP_MsgCfg->dataLen <= (uint16)ISOTP_BUFFSIZE))
    {
        /* Set the status to transmission in progress */
        ISOTP_NWLSt = (uint8)ISOTP_NWLST_TXINPROG;

        /* Set the timer limits */
        ISOTP_TimeOutNA = ((uint32)ISOTP_iTimeOut[ISOTP_TXIDX].tmrA) * (uint32)ISOTP_TIMERLMT;

        /* Start the timer A */
        ISOTP_NATime = (uint32)ISOTP_ONE;

        /* decide whether Single frame or segmented frames is/are needed */
        if (ISOTP_MsgCfg->dataLen <= (uint16)ISOTP_SEVEN)
        {
            /* change the state to Single frame Transmission */
            ISOTP_St = (uint8)ISOTP_SFTX;

            /* Store the number of bytes */
            ISOTP_FrmCfg.nBytes = ISOTP_MsgCfg->dataLen;

            /* Form the SF frame */
            /* N_PCI */
            ISOTP_canfrm.dataBuff[ISOTP_ZERO] = (uint8)(ISOTP_MsgCfg->dataLen);

            /* N_Data */
            for (idx = (uint16)ISOTP_ZERO; idx < ISOTP_MsgCfg->dataLen; idx++)
            {
                ISOTP_FrmCfg.tpBuff[idx] = *((ISOTP_MsgCfg->dataPtr) + idx);
                ISOTP_canfrm.dataBuff[idx + (uint16)ISOTP_ONE] = ISOTP_FrmCfg.tpBuff[idx];
            }

#if (ISOTP_ST_PADDING == ISOTP_PAD_REQUIRED)
            /* if necessary, pad the remaining bytes */
            if (ISOTP_MsgCfg->dataLen < (uint8)ISOTP_SEVEN)
            {
                ISOTP_PrfrmPad (ISOTP_MsgCfg->dataLen);
            }

            ISOTP_canfrm.DLC = (uint8)ISOTP_EIGHT;
 
#else

            ISOTP_canfrm.dlc = (uint8)(ISOTP_MsgCfg->dataLen + 1);

#endif

            /* Request data link layer for Tx of CF */
            CANIF_DIAG_TRANSMIT(ISOTP_canfrm);
        }
        /* Segmentation necessary */
        else
        {
            /* change the state to First frame Transmission */
            ISOTP_St = (uint8)ISOTP_FFTX;

            /* Store the number of bytes */
            ISOTP_FrmCfg.nBytes = ISOTP_MsgCfg->dataLen;

            /* N_PCI - The data length is limited to 8bits - max 0xFF */
            ISOTP_FrmCfg.frmInfo = ((uint8)ISOTP_FF) |
                                   ((uint8)((ISOTP_FrmCfg.nBytes >> ISOTP_EIGHT) & 
                                   ((uint16)ISOTP_SEQMASK)));

            /* Sequence number */
            ISOTP_FrmCfg.seqNum = (uint8)ISOTP_ZERO;

            /* Copy data to Tp buffer */
            for (idx = (uint16)ISOTP_ZERO; idx < ISOTP_MsgCfg->dataLen; idx++)
            {
                ISOTP_FrmCfg.tpBuff[idx] = *((ISOTP_MsgCfg->dataPtr) + idx);
            }

            /* Set the timer limits */
            ISOTP_TimeOutNB = ((uint32)ISOTP_iTimeOut[ISOTP_TXIDX].tmrB) * (uint32)ISOTP_TIMERLMT;
            ISOTP_TimeOutNC = ((uint32)ISOTP_iTimeOut[ISOTP_TXIDX].tmrC) * (uint32)ISOTP_TIMERLMT;

            /* Form the FF */
            ISOTP_canfrm.dataBuff[ISOTP_ZERO] = ISOTP_FrmCfg.frmInfo;

            /* Length limited to 0xFF */
            ISOTP_canfrm.dataBuff[ISOTP_ONE] = (uint8)ISOTP_FrmCfg.nBytes;

            /* first 6 bytes to be transmitted */
            for (idx = (uint8)ISOTP_ZERO; idx < (uint8)ISOTP_SIX; idx++)
            {
                ISOTP_canfrm.dataBuff[idx + (uint8)ISOTP_TWO] = ISOTP_FrmCfg.tpBuff[idx];
            }

            ISOTP_canfrm.DLC = (uint8)ISOTP_EIGHT;

            
            /* Request data link layer for Tx of CF */
            CANIF_DIAG_TRANSMIT(ISOTP_canfrm);
        }

        /* Return ISOTP_ISOUDS_TRUE - if tx request is placed */
        retVal = (uint8)ISOTP_ONE;
    }
    else
    {
        /* Return ISOTP_FALSE - if tx request couldn't be placed */
        retVal = (uint8)ISOTP_ZERO;
    }

    return (retVal);
}

/***************************************************************************************************
** Function                 : ISOTP_TxCnfCbk

** Description              : Transmit callback function of Diagnostic frame

** Parameter                : None

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
FUNC(void, CAN_CODE) ISOTP_TxCnfCbk (void)
{
    /* check for the current state */
    switch (ISOTP_St)
    {
        /* TP state in Single frame Transmission */
        case ISOTP_SFTX:
        {
            /* Stop the timer A */
            ISOTP_NATime = (uint32)ISOTP_ZERO;

            /* Change the network state to IDLE */
            ISOTP_NWLSt = (uint8)ISOTP_NWLST_IDLE;

            /* Call the confirmation service primitive */
            ISOUDS_TxCnfCbk();

            /* reset Tp parameters and Go back to IDLE state */
            ISOTP_Rst ();           

            break;
        }
        
        /* TP state in First frame Transmission */
        case ISOTP_FFTX:
        {
            /* 6 bytes already transmitted in FF */
            ISOTP_FrmCfg.nBytes -= (uint16)ISOTP_SIX;

            /* Increment the sequence number */
            ISOTP_FrmCfg.seqNum += (uint8)ISOTP_ONE;

            /* form the PCI of CF to be transmitted */
            ISOTP_FrmCfg.frmInfo = (uint8)(ISOTP_CF) | (ISOTP_FrmCfg.seqNum);

            /* Next data byte idx of tp buffer to be transmitted */
            ISOTP_TpBuffIdx = (uint16)ISOTP_SIX;

            /* Stop the timer A */
            ISOTP_NATime = (uint32)ISOTP_ZERO;

            /* Start Timer B */
            ISOTP_NBTime = (uint32)ISOTP_ONE;

            /* Wait for FC frame */
            ISOTP_St = (uint8)ISOTP_FCWAIT;

            break;
        }
        
        /* TP state in Flow control transmission */
        case ISOTP_FCTX:
        {
            /* Stop timer A */
            ISOTP_NATime = (uint32)ISOTP_ZERO;

            /* Check if the flow status is continue to send */
            if ((ISOTP_FrmCfg.frmInfo & (uint8)ISOTP_SEQMASK) == (uint8)ISOTP_FCCTS)
            {
                /* Start timer C */
                ISOTP_NCTime = (uint32)ISOTP_ONE;

                /* Wait for CF frame */
                ISOTP_St = (uint8)ISOTP_CFWAIT;
            }
            /* flow status if overflow */
            else
            {
                /* reset Tp parametrs and go to IDLE state */
                ISOTP_Rst ();
            }
            break;
        }
        
        /* TP state in Consecutive frame Transmission wait state */
        case ISOTP_CFTXWAIT:
        {
            /* If BSLen is gretaer than or equal to 7 */
            if (ISOTP_BSLen >= (uint8)ISOTP_SEVEN)
            {
                /* Decrement the block size by 7 */
                ISOTP_BSLen -= (uint8)ISOTP_SEVEN;
            }

            /* Decrement the no. of bytes */
            if (ISOTP_FrmCfg.nBytes < (uint16)ISOTP_SEVEN)
            {
                ISOTP_FrmCfg.nBytes = (uint16)ISOTP_ZERO;
            }
            else
            {
                ISOTP_FrmCfg.nBytes -= (uint16)ISOTP_SEVEN;
            }

            /* Stop timer A */
            ISOTP_NATime = (uint32)ISOTP_ZERO;

            /* Check if all bytes are transmitted */
            if (ISOTP_FrmCfg.nBytes == (uint16)ISOTP_ZERO)
            {
                /* Change the network state to IDLE */
                ISOTP_NWLSt = (uint8)ISOTP_NWLST_IDLE;

                /* Indicate the SrvD of Tx finished */
                ISOUDS_TxCnfCbk();

                /* Reset Tp parameters and change state to IDLE */
                ISOTP_Rst ();               
            }
            
            /* Check if another block is to be transmitted */
            else if (ISOTP_BSLen > (uint16)ISOTP_ZERO)
            {
                /* Increment the tp buffer index */
                ISOTP_TpBuffIdx += (uint8)ISOTP_SEVEN;

                /* Next sequence number */
                ISOTP_FrmCfg.seqNum = 
                                    (ISOTP_FrmCfg.seqNum + (uint8)ISOTP_ONE) & (uint8)ISOTP_SEQMASK;

                /* Form the PCI of next CF */
                ISOTP_FrmCfg.frmInfo = (uint8)ISOTP_CF | ISOTP_FrmCfg.seqNum;

                /* Start timer C */
                ISOTP_NCTime = (uint32)ISOTP_ONE;

                /* Change state to CFTX */
                ISOTP_St = (uint8)ISOTP_CFTX;
            }
            
            /* if BSlen is zero Wait for Flow control frame */
            else if (ISOTP_BSLen == (uint8)ISOTP_ZERO)
            {
                /* Increment the tp buffer index */
                ISOTP_TpBuffIdx += (uint8)ISOTP_SEVEN;

                /* Next sequence number */
                ISOTP_FrmCfg.seqNum = (ISOTP_FrmCfg.seqNum + 
                                      (uint8)ISOTP_ONE) & (uint8)ISOTP_SEQMASK;

                /* Form the PCI of next CF */
                ISOTP_FrmCfg.frmInfo = (uint8)ISOTP_CF | ISOTP_FrmCfg.seqNum;

                /* Start Timer B*/
                ISOTP_NBTime = (uint32)ISOTP_ONE;

                /* Wait for FC frame */
                ISOTP_St = (uint8)ISOTP_FCWAIT;
            }
            else
            {
                /* Do Nothing */
            }
            break;
        }
        
        default:
        {
            /* Do Nothing */
            break;
        }
    }
}

/***************************************************************************************************
** Function                 : ISOTP_Main

** Description              : TP Main function, runs continuously in Background

** Parameter                : None

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
FUNC(void, CAN_CODE) ISOTP_Main (void)
{
	VAR(uint16, AUTOMATIC) idx;

    /* If state is in consecutive frame transmission state */
    if (ISOTP_St == (uint8)ISOTP_CFTX)
    {
        /* Check if STMin value is reached */
        if (ISOTP_NCTime >= ISOTP_STmin)
        {
            /* N_PCI for CF */
            ISOTP_canfrm.dataBuff[ISOTP_ZERO] = ISOTP_FrmCfg.frmInfo;

            /* Data of consecutive frame to be transmitted */
            if (ISOTP_FrmCfg.nBytes < (uint16)ISOTP_SEVEN)
            {
                for (idx = (uint16)ISOTP_ZERO; idx < ISOTP_FrmCfg.nBytes; idx++)
                {
                    ISOTP_canfrm.dataBuff[idx + (uint16)ISOTP_ONE] =
                                ISOTP_FrmCfg.tpBuff[ISOTP_TpBuffIdx + idx];
                }

#if (ISOTP_ST_PADDING == ISOTP_PAD_REQUIRED)
                /* Peform Padding */
                ISOTP_PrfrmPad (ISOTP_FrmCfg.nBytes);

                ISOTP_canfrm.DLC = (uint8)ISOTP_EIGHT;
#else
                ISOTP_canfrm.dlc = (uint8)(ISOTP_FrmCfg.nBytes + ISOTP_ONE);
#endif
            }
            else
            {
                for (idx = (uint8)ISOTP_ZERO; idx < (uint8)ISOTP_SEVEN; idx++)
                {
                  ISOTP_canfrm.dataBuff[idx + (uint8)ISOTP_ONE] = 
                                                         ISOTP_FrmCfg.tpBuff[ISOTP_TpBuffIdx + idx];
                }
                ISOTP_canfrm.DLC = (uint8)ISOTP_EIGHT;
            }

            /* Stop timer C */
            ISOTP_NCTime = (uint32)ISOTP_ZERO;

            /* Start Timer A */
            ISOTP_NATime = (uint32)ISOTP_ONE;

            /* Change state to CFTXWAIT */
            ISOTP_St = (uint8)ISOTP_CFTXWAIT;

            /* Request data link layer for Tx of CF */
            CANIF_DIAG_TRANSMIT(ISOTP_canfrm);
        }
    }
    /* If state is in FCTXREQ */
    else if (ISOTP_St == (uint8)ISOTP_FCTXREQ)
    {
        /* N_PCI for FC */
        ISOTP_canfrm.dataBuff[ISOTP_ZERO] = ISOTP_FrmCfg.frmInfo;

        ISOTP_canfrm.dataBuff[ISOTP_ONE] = (uint8)ISOTP_FCBS;

        /* store the Block Size length */
        ISOTP_BSLen = (uint16)ISOTP_FCBS * (uint8)ISOTP_SEVEN;

        /* Store the minimum separation time */
        ISOTP_canfrm.dataBuff[ISOTP_TWO] = (uint8)ISOTP_FCSTMIN;

#if (ISOTP_ST_PADDING == ISOTP_PAD_REQUIRED)
        /* pad the remaining bytes*/
        ISOTP_PrfrmPad ((uint8)ISOTP_TWO);
        ISOTP_canfrm.DLC = (uint8)ISOTP_EIGHT;

#else
        ISOTP_canfrm.dlc = (uint8)ISOTP_THREE;
#endif

        /* Stop timer B */
        ISOTP_NBTime = (uint32)ISOTP_ZERO;

        /* Start timer A */
        ISOTP_NATime = (uint32)ISOTP_ONE;

        /* Change state to FC TX */
        ISOTP_St = (uint8)ISOTP_FCTX;

        /* Request data link layer for Tx of FC */
        CANIF_DIAG_TRANSMIT(ISOTP_canfrm);
    }
    else
    {
        /* Do Nothing */
    }

    /* Call the timer Monitoring Function */
	ISOTP_iTmrMon();
}

/***************************************************************************************************
** Function                 : ISOTP_GetStatus

** Description              : Returns the status of TP module.

** Parameter rxData         : None

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
FUNC(uint8, CAN_CODE) ISOTP_GetStatus(void)
{
   /* Reurn the Status of ISOTP. */
   return(ISOTP_St);
}


/**************************** Internal Function definitions ***************************************/

/***************************************************************************************************
** Function                 : ISOTP_Rst

** Description              : Resets the required TP parameters.

** Parameter rxData         : None

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
static FUNC(void, CAN_CODE) ISOTP_Rst (void)
{
    /* Reset the Block size length */
    ISOTP_BSLen = (uint16)ISOTP_ZERO;

    /* Reset the first Flow control frame received to ISOTP_FALSE */
    ISOTP_FirstFCRcvd = (uint8)ISOTP_ZERO;

    /* Reset the Tp buffer index to 0 */
    ISOTP_TpBuffIdx = (uint8)ISOTP_ZERO;

    /* Reset the frame info */
    ISOTP_FrmCfg.frmInfo = (uint8)ISOTP_ZERO;

    /* Reset the sequence number */
    ISOTP_FrmCfg.seqNum = (uint8)ISOTP_ZERO;

    /* Reset the number of bytes */
    ISOTP_FrmCfg.nBytes = (uint16)ISOTP_ZERO;
	
	ISOTP_StMultiFrame = ISOTP_FALSE;

    /* change state to IDLE */
    ISOTP_St = (uint8)ISOTP_IDLE;
}

/***************************************************************************************************
** Function                 : ISOTP_iTmrMon

** Description              : Monitors the TP timers.

** Parameter rxData         : None

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
static FUNC(void, CAN_CODE) ISOTP_iTmrMon (void)
{
    /* Check if counter A is running */
    if (ISOTP_NATime > (uint32)ISOTP_ZERO)
    {
        /* Check if the counter limit is reached */
        if (ISOTP_NATime >= ISOTP_TimeOutNA)
        {
            /* Abort Message transmission/ reception */
            ISOTP_Rst ();
            ISOUDS_Rst();

            /* Reset the counter */
            ISOTP_NATime = (uint32)ISOTP_ZERO;

            /* Clear the transmission request placed */
            ISOTP_CANIF_ABORTTRANSMIT();

            /* Change the network status to IDLE */
            ISOTP_NWLSt = (uint8)ISOTP_NWLST_IDLE;
        }
        /* Else increment the counter */
        else
        {
            ISOTP_NATime += (uint32)ISOTP_PERIOD_SCHED;
        }
    }

    /* Check if counter B is running */
    if (ISOTP_NBTime > (uint32)ISOTP_ZERO)
    {
        /* Check if the counter limit is reached */
        if (ISOTP_NBTime >= ISOTP_TimeOutNB)
        {
            /* Abort Message transmission/ reception */
            ISOTP_Rst ();
            ISOUDS_Rst();
            
            /* Reset the counter */
            ISOTP_NBTime = (uint32)ISOTP_ZERO;            

            /* Change the network status to IDLE */
            ISOTP_NWLSt = (uint8)ISOTP_NWLST_IDLE;
        }
        /* Else increment the counter */
        else
        {
            ISOTP_NBTime += (uint32)ISOTP_PERIOD_SCHED;
        }
    }

    /* Check if counter C is running */
    if (ISOTP_NCTime > (uint32)ISOTP_ZERO)
    {
        /* Check if the counter limit is reached */
        if (ISOTP_NCTime >= ISOTP_TimeOutNC)
        {
            /* Abort Message transmission/ reception */
            ISOTP_Rst ();
            ISOUDS_Rst();
            
            /* Reset the counter */
            ISOTP_NCTime = (uint32)ISOTP_ZERO;            

            /* Change the network status to IDLE */
            ISOTP_NWLSt = (uint8)ISOTP_NWLST_IDLE;
        }
        /* Else increment the counter */
        else
        {
            ISOTP_NCTime += (uint32)ISOTP_PERIOD_SCHED;
        }
    }
}


#if (ISOTP_ST_PADDING == ISOTP_PAD_REQUIRED)
/***************************************************************************************************
** Function                 : ISOTP_PrfrmPad

** Description              : Indicates that a new request has been received

** Parameter                : None

** Return value             : None

** Remarks                  : None
***************************************************************************************************/
static FUNC(void, CAN_CODE) ISOTP_PrfrmPad (uint16 byteIdx)
{
	VAR(uint8, AUTOMATIC) idx;

    /* append the remaining bytes */
    for (idx = (uint8)byteIdx; idx < (uint8)ISOTP_SEVEN; idx++)
    {
        ISOTP_canfrm.dataBuff[idx + (uint8)ISOTP_ONE] = (uint8)ISOTP_PADDATA_VAL;
    }
}
#endif
