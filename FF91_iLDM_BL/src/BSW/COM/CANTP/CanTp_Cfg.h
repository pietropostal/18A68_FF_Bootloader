/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name : CanTp_cfg.h
** Module Name : CanTp
** -------------------------------------------------------------------------------------------------
**
** Description : Configuration file of component CanTp.c
** This file must exclusively contain informations needed to
** use this component.
**
** -------------------------------------------------------------------------------------------------
**
** Documentation reference : EME-17ST013-12070.01 (SWLLD CanTp)
**
****************************************************************************************************
** R E V I S I O N H I S T O R Y
****************************************************************************************************
** V01.00 13/07/2019
** - Baseline Created
**
***************************************************************************************************/
/* To avoid multi-inclusions */
#ifndef CanTp_CFG_H
#define CanTp_CFG_H

/************************************* Inclusion files ********************************************/
#include "CanIf.h"
/********************************* Declaration of global macros ***********************************/
/********************************* Declaration of global types ************************************/
/****************************** External links of global variables ********************************/
/****************************** External links of global constants ********************************/

/************************** Declaration of global symbol and constants ****************************/
/* The periodic scheduling interval of iso15765 in units of 0.1 ms */
#define     ISOTP_PERIOD_SCHED       (10U)

/* iso15765 Transmission CAN ID type- either standard or extended */


/* iso15765 Transmission CAN ID */
#define     ISOTP_TXOBD_CANID        (0x79BU) // Enrico -> ISOTP ID

/* iso15765 buffer size */
#define     ISOTP_BUFFSIZE           (4095u)

/* Flow control block size */
#define     ISOTP_FCBS               (0x0AU)

/* Flow control minimum segmentation time */
#define     ISOTP_FCSTMIN            (0x01U)

/* Maximum number of FC.Wait frame transmissions */
/* Sender timeout values */
#define     ISOTP_NAS_TIMEOUT_MS      (/* ISO_TP_MAX_TIMEOUT   * */1000U)    /* N_As timeout value in ms */
#define     ISOTP_NBS_TIMEOUT_MS      (/* ISO_TP_MAX_TIMEOUT   * */1000U)    /* N_Bs timeout value in ms */
#define     ISOTP_NCS_TIMEOUT_MS      (/* ISO_TP_MAX_TIMEOUT   * */1000U)    /* N_Cs timeout value in ms */
                                       /*                        */
/* Receiver timeout values */          /*                        */
#define     ISOTP_NAR_TIMEOUT_MS      (/* ISO_TP_MAX_TIMEOUT   * */1000U)    /* N_Ar timeout value in ms */
#define     ISOTP_NBR_TIMEOUT_MS      (/* ISO_TP_MAX_TIMEOUT   * */1000U)    /* N_Br timeout value in ms */
#define     ISOTP_NCR_TIMEOUT_MS      (/* ISO_TP_MAX_TIMEOUT   * */1000U)    /* N_Cr timeout value in ms */
                                      
/* Padding related values. */  
#define     ISOTP_PAD_REQUIRED        0x00U
//#define     ISOTP_PAD_NOTREQ          0x01U                                      
#define     ISOTP_ST_PADDING          ISOTP_PAD_REQUIRED
                                      
/* Padding data value */              
#define     ISOTP_PADDATA_VAL         0xFF
                                      
/* Timeout Table Size. */             
#define     ISOTP_TIMEOUT_TAB         0x02


/* Ganesh TBD: CAN Abort request has to be implemented */
#define     ISOTP_CANIF_ABORTTRANSMIT()   //CanIf_AbortTransmission()

#endif
