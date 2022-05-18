/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_WrDaByID.h
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
#ifndef CANSRV_WRDABYID_H
#define CANSRV_WRDABYID_H

/************************************* Inclusion files ********************************************/
//#include "typedefs.h"
#include "ISOUDS.h"
#include "Platform_Types.h"
#include "ISOUDS_wrcfg.h"

/************************** Declaration of global symbol and constants ****************************/
/* DID with READ/WRITE */
/*------------------------------------------------------------------------------------------------*/


#define         ISOUDS_ID_BOOT_TEST_TOOL_FP              (uint16)(0xF15AU)
#define         ISOUDS_ID_APP_SW_FP                      (uint16)(0xF184U)
#define         ISOUDS_ID_CAL_DATA_FP                    (uint16)(0xF185U)

/* DID size FOR READ/WRITE once (in byte) */
/*------------------------------------------------------------------------------------------------*/

#define BOOTLOADER_TEST_TOOL_FP_SIZE                      (51U)
#define APPLICATION_FP_SIZE                               (51U)
#define CALIBRATION_DATA_FP_SIZE                          (51U)

                                                      
/************************flag Once Write/Read anytime  ********************************************/


/********************************* Declaration of global macros ***********************************/

/********************************* Declaration of global types ************************************/
/* SID of Write Data By Identifier service */
#define CANSRV_SIDWRDABYID              (0x2E)

/****************************** EXTERNal links of global variaCanSrves ****************************/

/****************************** EXTERNal links of global constants ********************************/

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/********************************** Function definitions ******************************************/

/***************************************************************************************************
** Function                 : CanSrv_WrDaByID
** Description              : Sends response to Write Data by ID service request
** Parameter canSrvDConfPtr : Pointer to service configuration structure
** Parameter dataBuff       : Pointer to service data buffer
** Return value             : None
** Remarks                  : None
***************************************************************************************************/
EXTERN FUNC(void, CAN_CODE)CanSrv_WrDaByID(P2VAR(ISOUDS_ConfType,AUTOMATIC,CAN_APPL_DATA)canSrvDConfPtr,\
                                                                  VAR(uint8, AUTOMATIC) dataBuff[]);
								
#endif  /* CANSRV_WRDABYID_H */
