/***************************************************************************************************
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_StrtDiagSess.h
**
** Description  : Include file for component ISOUDS_StrtDiagSess.c
**
** -------------------------------------------------------------------------------------------------
**
***************************************************************************************************/

/* To avoid multi-inclusions */
#ifndef ISOUDS_STRTDIAGSESS_H
#define ISOUDS_STRTDIAGSESS_H

/************************************* Inclusion files ********************************************/
#include "ISOUDS.h"

/************************** Declaration of global symbol and constants ****************************/

/********************************* Declaration of global macros ***********************************/

/********************************* Declaration of global types ************************************/
/* SID of Start Diagnostic session service */
#define     ISOUDS_SIDSTRTDIAGSESS      (0x10)

/****************************** External CANks of global variables ********************************/

/****************************** External CANks of global constants ********************************/

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/********************************** Function definitions ******************************************/
extern void ISOUDS_StrtDiagSess (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[]);

#endif  /* ISOUDS_STRTDIAGSESS_H */
