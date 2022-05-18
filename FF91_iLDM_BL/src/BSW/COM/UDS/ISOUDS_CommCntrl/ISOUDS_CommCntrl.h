/*******************************************************************************
**
** -----------------------------------------------------------------------------
** File Name    : ISOUDS_CommCntrl.h
**
** Description  : Include component of ISOUDS_CommCntrl.c
**
** -----------------------------------------------------------------------------
**
*******************************************************************************/

/* To avoid multi-inclusions */
#ifndef ISOUDS_COMMCNTRL_H
#define ISOUDS_COMMCNTRL_H

/************************************* Inclusion files ************************/
#include "ISOUDS.h"

/************************** Declaration of global symbol and constants ********/
/* SID of Communication Control service */
#define     ISOUDS_SIDCOMMCNTRL        (0x28)

/********************************* Declaration of global macros ***************/

/********************************* Declaration of global types ****************/

/****************************** External CANks of global variables ************/

/****************************** External CANks of global constants ************/

/*******************************************************************************
**                                      FUNCTIONS                              *
*******************************************************************************/

/********************************** Function definitions **********************/
extern void ISOUDS_CommCntrl (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[]);


#endif  /* ISOUDS_COMMCNTRL_H */
