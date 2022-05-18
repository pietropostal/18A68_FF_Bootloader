/***************************************************************************************************
 ** Copyright (c) 2019 EMBITEL
 **
 ** This software is the property of EMBITEL.
 ** It can not be used or duplicated without EMBITEL authorization.
 **
 ** -------------------------------------------------------------------------------------------------
 ** File Name    : ISOUDS_RdCfg.h
 ** Module Name  : ISOUDS_RdDaByID
 ** -------------------------------------------------------------------------------------------------
 **
 ** Description : Include file of component CanSrv_RdCfg.c
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
#ifndef ISOUDS_RDCFG_H
#define ISOUDS_RDCFG_H

/************************************* Inclusion files ********************************************/
#include "Platform_Types.h"
#include "Compiler.h"

/************************** Declaration of global symbol and constants ****************************/
/* DID Read Configuration Table size */
#define     ISOUDS_RDCONFTABSIZE            			  (14U)

#define BOOTLOADER_VERSION_SIZE                           (15U)
#define APPLICATION_VERSION_SIZE                          (15U)
#define CALIBRATION_DATA_VERSION_SIZE                     (15U)
#define BOOTLOADER_TEST_TOOL_FP_SIZE                      (51U)
#define APPLICATION_FP_SIZE                               (51U)
#define CALIBRATION_DATA_FP_SIZE                          (51U)
#define ACTIVE_DIAG_SIZE                                  (1U)
#define SOFTWARE_COMPONENT_PART_NUM_SIZE                  (25U)
#define ECU_MAN_DATE_SIZE                                 (4U)
#define ECU_SERIAL_NUM_SIZE                               (24U)
#define VEHICLE_IDENTIFICATION_NUM_SIZE                   (17U)
#define VEHICLE_MAN_ECU_HW_NUM_SIZE                       (8U)
#define VEHICLE_MAN_ECU_HW_VERSION_SIZE                   (1U)
#define ECU_MODE_SIZE                                     (1U)

/* NULL function pointer */
#define     ISOUDS_RDFUNCNULLPTR            ((uint8 (*) (uint8 srcBuff[], uint8 len))0)

/* DID Defines */
//#define     ISOUDS_DUMMYDID                 			(uint16)(0x0001U)


#define         ISOUDS_ID_BOOT_SW_ID                     (uint16)(0xF180U)
#define         ISOUDS_ID_APP_SW_ID                      (uint16)(0xF181U)
#define         ISOUDS_ID_CAL_DATA_ID                    (uint16)(0xF182U)
#define         ISOUDS_ID_BOOT_TEST_TOOL_FP              (uint16)(0xF15AU)
#define         ISOUDS_ID_APP_SW_FP                      (uint16)(0xF184U)
#define         ISOUDS_ID_CAL_DATA_FP                    (uint16)(0xF185U)
#define         ISOUDS_ID_ACTIVE_DIAG_SESSION            (uint16)(0xF186U)
#define         ISOUDS_ID_SW_COMP_PART_NUM               (uint16)(0xF188U)
#define         ISOUDS_ID_ECU_MAN_DATE                	 (uint16)(0xF18BU)
#define         ISOUDS_ID_ECU_SR_NUM                     (uint16)(0xF18CU)
#define         ISOUDS_ID_VIN_NUM                        (uint16)(0xF190U)
#define         ISOUDS_ID_VEH_MAN_ECU_HW_NUM             (uint16)(0xF191U)
#define         ISOUDS_ID_VEH_MAN_ECU_HW_VER_NUM         (uint16)(0xF193U)
#define         ISOUDS_ID_ECU_MODE				         (uint16)(0xF200U)


extern CONST(uint8, AUTOMATIC)   ISOUDS_SW_componentPartNum[SOFTWARE_COMPONENT_PART_NUM_SIZE];



/* DID Session Selection (DIDSS) Configuration */
/*----------------------------------------------------------------------------------------------*/
/*                    E P D R                    EXTDS    = Extended Disgnostic Session */
/*                    X R S E                    PRGS     = Programming Session */
/*                    T G   S                    DS       = Default Session */
/*                    D S   V                    RESV     = Reserved */
/*                    S                          */
/*----------------------------------------------------------------------------------------------*/
#define  ISOUDS_DIDSS_T_T_T_F     (0x0E)          /* T -> ISOUDS_TRUE , F -> ISOUDS_FALSE */
#define  ISOUDS_DIDSS_T_F_T_F     (0x0A)          /* T -> ISOUDS_TRUE , F -> ISOUDS_FALSE */
#define  ISOUDS_DIDSS_T_F_F_F     (0x08)          /* T -> ISOUDS_TRUE , F -> ISOUDS_FALSE */
#define	 ISOUDS_DIDSS_F_T_F_F	  (0x04)          /* T -> ISOUDS_TRUE , F -> ISOUDS_FALSE */
#define	 ISOUDS_DIDSS_F_T_T_F	  (0x09)          /* T -> ISOUDS_TRUE , F -> ISOUDS_FALSE */

/********************************* Declaration of global macros ***********************************/

/********************************* Declaration of global types ************************************/
typedef struct
{
	uint16 rdDid;                           /* Data Identifier */
	uint8  rdDidLen;                        /* DID length - no. of bytes */
	uint8 *rdDidAddr;                       /* address of the DID */
	uint8 (*rdDid_funPtr) (uint8 [], uint8);/* Function pointer to callback function */
	uint8  rdDidSess;                       /* session in which the DID is supported */
	uint8  secured;                      	/* Secured */
}ISOUDS_RdDidType;


/****************************** External links of global variables ********************************/

/****************************** External links of global constants ********************************/
EXTERN  CONST(ISOUDS_RdDidType, CanSrv_VAR) ISOUDS_RdConfTab[];
EXTERN VAR(uint8, AUTOMATIC)   ISOUDS_Bootloader_FingerPrint[BOOTLOADER_TEST_TOOL_FP_SIZE];
EXTERN VAR(uint8, AUTOMATIC)   ISOUDS_Application_FingerPrint[APPLICATION_FP_SIZE];
EXTERN VAR(uint8, AUTOMATIC)   ISOUDS_CalbritionData_FingerPrint[CALIBRATION_DATA_FP_SIZE];
EXTERN VAR(uint8, AUTOMATIC)   ISOUDS_ActiveDiag_session[ACTIVE_DIAG_SIZE ];
EXTERN CONST(uint8, AUTOMATIC)   ISOUDS_SW_componentPartNum[SOFTWARE_COMPONENT_PART_NUM_SIZE];
EXTERN VAR(uint8, AUTOMATIC)   ISOUDS_ECU_mode[ECU_MODE_SIZE];
EXTERN VAR(uint8, CanSrv_VAR) Application_Version[APPLICATION_VERSION_SIZE];
EXTERN VAR(uint8, CanSrv_VAR)ISOUDS_VehManEcuHwVersion[VEHICLE_MAN_ECU_HW_VERSION_SIZE];
EXTERN VAR(uint8, CanSrv_VAR)ISOUDS_VehManEcuHwVersion[VEHICLE_MAN_ECU_HW_VERSION_SIZE];
EXTERN VAR(uint8, CanSrv_VAR) Application_Version[APPLICATION_VERSION_SIZE];

#endif  /* ISOUDS_RDCFG_H */
