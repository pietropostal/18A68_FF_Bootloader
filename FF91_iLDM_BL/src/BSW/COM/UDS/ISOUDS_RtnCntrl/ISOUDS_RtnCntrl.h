/***************************************************************************************************
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_RtnCntrl.h
**
** Description  : Include file component for ISOUDS_RtnCntrl.c
**
** -------------------------------------------------------------------------------------------------
**
***************************************************************************************************/

/* To avoid multi-inclusions */
#ifndef ISOUDS_RTNCNTRL_H
#define ISOUDS_RTNCNTRL_H

/************************************* Inclusion files ********************************************/
#include "ISOUDS.h"

/************************** Declaration of global symbol and constants ****************************/

/********************************* Declaration of global macros ***********************************/

/********************************* Declaration of global types ************************************/
/* SID of Read Data By Identifier service */
#define     ISOUDS_SIDRTNCNTRLID        (0x31U)

/* Responses of rountine control */
#define     ISOUDS_RTNCTRL_INITIAL          ((uint8)0x00)
#define     ISOUDS_RTNCTRL_POSTIVE          ((uint8)0x01)
#define     ISOUDS_RTNCTRL_NEGTIVE          ((uint8)0x02)
#define     ISOUDS_RTNCTRL_PENDING          ((uint8)0x03)
//#define     ISOUDS_RTNCTRL_OTHER            ((uint8)0x04)
#define     ISOUDS_RTNCTRL_SFNS             ((uint8)0x05)
#define     ISOUDS_RTNCTRL_INVALID_LEN      ((uint8)0x06)


#define		ISOUDS_ERASE_ADD_LEN_ID		((uint8)0x44)

#define		ISOUDS_ERASE_SRV_LEN		(((ISOUDS_ERASE_ADD_LEN_ID & 0xF0) >> 4) + (ISOUDS_ERASE_ADD_LEN_ID & 0xF) + 5)
#define		ISOUDS_ERASE_SRV_LEN_BLK    (5)

/****************************** External Links of global variables ********************************/


/****************************** External Links of global constants ********************************/

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/********************************** Function definitions ******************************************/
extern void  ISOUDS_RtnCntrl (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[]);
#endif  /* ISOUDS_RTNCNTRL_H */
