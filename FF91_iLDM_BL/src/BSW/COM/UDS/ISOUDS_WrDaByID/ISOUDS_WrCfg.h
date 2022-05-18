/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_wrcfg.h
** Module name  : CANWRDBID
** -------------------------------------------------------------------------------------------------
** Description : Configuration file of component CanSrv_WrDaByID.c
** This file must exclusively contain informations needed to
** use this component.
** -------------------------------------------------------------------------------------------------
**
** Documentation reference :
**
****************************************************************************************************
** R E V I S I O N  H I S T O R Y
****************************************************************************************************
** 
** 
**
***************************************************************************************************/

/* To avoid multi-inclusions */
#ifndef CANSRV_WR__H
#define CANSRV_WR__H

/************************************* Inclusion files ********************************************/
//#include "typedefs.h"
#include "Platform_Types.h"
#include "ISOUDS.h"
/************************** Declaration of global symbol and constants ****************************/

/* DID Session Selection (DIDSS) Configuration */
/*------------------------------------------------------------------------------------------------*/
/*                    E P D R                    EXTDS    = Extended Diagnostic Session */
/*                    X R S E                    PRGS     = Programming Session */
/*                    T G   S                    DS       = Default Session */
/*                    D S   V                    RESV     = Reserved */
/*                    S                          */
/*------------------------------------------------------------------------------------------------*/
#define     CANSRV_DIDSS_F_T_F_F     (0x04) /* T -> TRUE , F -> FALSE */
#define  	CANSRV_DIDSS_T_T_T_F     (0x0E)	/* T -> TRUE , F -> FALSE */
#define  	CANSRV_DIDSS_F_T_T_F     (0x09)	/* T -> TRUE , F -> FALSE */

/* DID Write Configuration TaCanSrve size */
#define     CANSRV_WRCONFTABSIZE                                               (7u)


typedef struct
{
    VAR(uint16, CAN_CONST) wrDid;                          /* Holds the Data Identifier */
    VAR(uint8, CAN_CONST)  wrDidLen;                       /* Holds the DID length - no. of bytes*/
    /* Function pointer to callback function */
    P2FUNC(uint8, CAN_CONST, wrDid_funPtr) ( VAR(uint8, TYPEDEF),\
    		                                 CONST(uint8, TYPEDEF) [], VAR(uint8, TYPEDEF));
	VAR(uint8, CAN_CONST)  WrDidSess;					   /* Holds the DID Session selection*/
}CanSrv_WrDidType;

/****************************** EXTERNal links of global variaCanSrves ****************************/
/****************************** EXTERNal links of global constants ********************************/

EXTERN CONST(CanSrv_WrDidType, CanSrv_VAR) CanSrv_cWrConfTab[CANSRV_WRCONFTABSIZE];



/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/***************************************************************************************************
** Function         : CanSrv_WriteTASK
** Description      : Write DID'S data in Non Volatile memory from srcBuff[]
** Parameter        : uint8 srcBuff from where data to be written in NVM,
                      uint8 no of bytes to be write
                      uint8 DID index
					  uint8 NVM block no
** Return value     : 0X01 -> Write failure(DID already written)
** Remarks          : None
***************************************************************************************************/
EXTERN FUNC(uint8, CAN_CODE)CanSrv_WriteTASK( VAR(uint8, AUTOMATIC)DID_Index,\
                                              CONST(uint8, AUTOMATIC)srcBuff[],\
                                              VAR(uint8, AUTOMATIC)len);

#endif  /* CANSRV_WR__H */
