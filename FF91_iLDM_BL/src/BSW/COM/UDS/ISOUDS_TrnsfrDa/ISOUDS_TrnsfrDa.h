/***************************************************************************************************
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_TrnsfrDa.h
**
** Description  : Include file of component ISOUDS_TrnsfrDa.c
**
** -------------------------------------------------------------------------------------------------
**
***************************************************************************************************/

/* To avoid multi-inclusions */
#ifndef ISOUDS_TRNSFRDA_H
#define ISOUDS_TRNSFRDA_H

/************************************* Inclusion files ********************************************/
#include "ISOUDS.h"

/************************** Declaration of global symbol and constants ****************************/
#define ISOUDS_TRIDLE       (uint8)0 /* Transfer Data service in Idle state */
#define ISOUDS_REQDW        (uint8)1 /* Transfer Data service in ReqDownload state */
#define ISOUDS_REQDWTD      (uint8)2 /* Transfer Data service is busy with ReqDownload state */
#define ISOUDS_REQTDFNSH    (uint8)3 /* Transfer Data service finish */
#define ISOUDS_REQUP        (uint8)4 /* Transfer Data service in Request Upload state */
#define ISOUDS_REQUPTD      (uint8)5 /* Transfer Data service is busy with Request upload state */
#define ISOUDS_REQTDUPFNSH  (uint8)6 /* Transfer Data service finish */

/********************************* Declaration of global macros ***********************************/

/********************************* Declaration of global types ************************************/
/* SID of Transfer Data service */
#define ISOUDS_SIDTRNSFRDTID    (0x36)

/****************************** External CANks of global variables ********************************/

/****************************** External CANks of global constants ********************************/

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/********************************** Function definitions ******************************************/
extern void ISOUDS_TrnsfrDa (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[]);
extern void ISOUDS_TrnsfrDaExit (void);
extern uint8 ISOUDS_ReqTrnsfrDa (uint32 addr, uint32 size, uint8 servreq);
extern uint8 ISOUDS_ChkTrnsfrExit (void);

#endif  /* ISOUDS_TRNSFRDA_H */
