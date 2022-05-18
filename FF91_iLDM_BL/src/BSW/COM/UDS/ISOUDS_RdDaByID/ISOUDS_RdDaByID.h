/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_RdDaByID.h
** Module Name  : ISOUDS_RdDaByID
** -------------------------------------------------------------------------------------------------
**
** Description : Include file of component CanSrv_RdDaByID.c
** This file must exclusively contain informations needed to
** use this component.
**
** -------------------------------------------------------------------------------------------------
**
** Documentation reference : EME-17ST013-12211.01(SWLLD CanSrv_RdDaByID)
**
****************************************************************************************************
** R E V I S I O N H I S T O R Y
****************************************************************************************************
** V01.00 16/07/2019
** - Baseline Created
**
***************************************************************************************************/

/* To avoid multi-inclusions */
#ifndef ISOUDS_RDDABYID_H
#define ISOUDS_RDDABYID_H

/************************************* Inclusion files ********************************************/
#include "ISOUDS.h"

/************************** Declaration of global symbol and constants ****************************/

/********************************* Declaration of global macros ***********************************/

/********************************* Declaration of global types ************************************/
/* SID of Read Data By Identifier service */
#define     ISOUDS_SIDRDDABYID       	(0x22)
#define 	NULL_PTR 					((void *)0)
/****************************** External links of global variables ********************************/

/****************************** External links of global constants ********************************/

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/********************************** Function definitions ******************************************/
EXTERN  void ISOUDS_RdDaByID (P2VAR(ISOUDS_ConfType, AUTOMATIC,CAN_CODE) ISOUDSConfPtr, \
																VAR(uint8, AUTOMATIC) dataBuff[]);
EXTERN  VAR(uint8, AUTOMATIC) ISOUDS_RdArrData (VAR(uint8, AUTOMATIC) srcBuff[], \
																VAR(uint8, AUTOMATIC) len);

#endif  /* ISOUDS_RDDABYID_H */
