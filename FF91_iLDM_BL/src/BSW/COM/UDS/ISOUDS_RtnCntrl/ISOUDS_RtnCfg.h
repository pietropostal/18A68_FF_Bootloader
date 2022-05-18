/***************************************************************************************************
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_RtnCfg.h
**
** Description  : Include file component for ISOUDS_RtnCfg.c
**
** -------------------------------------------------------------------------------------------------
**
***************************************************************************************************/

/* To avoid multi-inclusions */
#ifndef ISOUDS_RTNCFG_H
#define ISOUDS_RTNCFG_H

/************************************* Inclusion files ********************************************/
#include "ISOUDS.h"


/************************** Declaration of global symbol and constants ****************************/
/* Routine Control ID  Configuration Table size */
#define     ISOUDS_RTNCONFTABSIZE            (4)

/* DID Defines */
/* DID Session Selection (DIDSS) Configuration */
/*----------------------------------------------------------------------------------------------*/
/*                    E P D R                    EXTDS    = Extended Disgnostic Session */
/*                    X R S E                    PRGS     = Programming Session */
/*                    T G   S                    DS       = Default Session */
/*                    D S   V                    RESV     = Reserved */
/*                    S                          */
/*----------------------------------------------------------------------------------------------*/
#define  ISOUDS_DIDSS_T_T_T_F     (0x0E)          /* T -> TRUE , F -> FALSE */
#define  ISOUDS_DIDSS_T_F_F_F     (0x08)          /* T -> TRUE , F -> FALSE */
#define	 ISOUDS_DIDSS_F_T_F_F	  (0x04)          /* T -> ISOUDS_TRUE , F -> ISOUDS_FALSE */



/* Routine identifier to Erase Flash. */
#define  ISOUDS_RTNID_ERASE          ((uint16)0xFF00)




/* Routine identifier to Check Programming Dependencies. */    
#define  ISOUDS_RTNID_VALIDATION    		((uint16)0xF000)

/* Routine identifier to Check Programming Dependencies. */    
#define  ISOUDS_RTNID_AUTHORIZATION    		((uint16)0xFF01)

// Check Memory
#define  ISOUDS_RTNID_CHECKMEMORY   		((uint16)0x0202)

#define ISOUDS_RTNID_ECUMODE ((uint16)0xFF03)


/********************************* Declaration of global macros ***********************************/

/********************************* Declaration of global types ************************************/
typedef struct
{
    /* Data Identifier */
    uint16 rtnid;                                   
    /* Hold address of the UDS service funtion */
    uint8 (*ISOUDS_FunPtr)(ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[]);
    /* session in which the ID is supported */
    uint8  rtnIdSess;
    /* wether the service is for App or Secondary boot loader */    
    uint8  rtnAppServ;     
}ISOUDS_RtnIdType;

/****************************** External Links of global variables ********************************/

/****************************** External Links of global constants ********************************/

extern const ISOUDS_RtnIdType ISOUDS_RtnConfTab[ISOUDS_RTNCONFTABSIZE];

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/
extern uint8 ISOUDS_CheckAppValidation  (ISOUDS_ConfType *ISOUDS_Srv_ConfPtr, uint8 dataBuff[]);
extern uint8 ISOUDS_EraseFlash     (ISOUDS_ConfType *ISOUDS_Srv_ConfPtr, uint8 dataBuff[]);
extern uint8 ISOUDS_CheckMemory     (ISOUDS_ConfType *ISOUDS_Srv_ConfPtr, uint8 dataBuff[]);
extern uint8 ISOUDS_CheckAppAuthorization (ISOUDS_ConfType *ISOUDS_Srv_ConfPtr, uint8 dataBuff[]);
extern uint8 ISOUDS_CheckECUMode(ISOUDS_ConfType *ISOUDS_Srv_ConfPtr, uint8 dataBuff[]);

/********************************** Function definitions ******************************************/

#endif  /* ISOUDS_RTNCFG_H */
