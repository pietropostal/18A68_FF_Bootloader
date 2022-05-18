/***************************************************************************************************
 ** Copyright (c) 2019 EMBITEL
 **
 ** This software is the property of EMBITEL.
 ** It can not be used or duplicated without EMBITEL authorization.
 **
 ** -------------------------------------------------------------------------------------------------
 ** File Name    : ISOUDS_RdCfg.c
 ** Module Name  : ISOUDS_RdDaByID
 ** -------------------------------------------------------------------------------------------------
 **
 ** Description : Values for types defined in CanSrv_RdCfg.h will reside in this file.
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

/**************************************** Inclusion files *****************************************/
#include "ISOUDS_RdCfg.h"
#include "ISOUDS_SA.h"
#include "ISOUDS_RdDaByID.h"

/********************************* Declaration of local macros ************************************/

/********************************* Declaration of local types *************************************/

/******************************* Declaration of local variables ***********************************/

/******************************* Declaration of local constants ***********************************/

/****************************** Declaration of exported variables *********************************/

/****************************** Declaration of exported constants *********************************/

CONST(uint8, CanSrv_VAR) BootLoader_Version[BOOTLOADER_VERSION_SIZE] __attribute__((section(".segmentDID0xF180"))) = {
		BL_VERSION_MAJOR,BL_VERSION_MINOR,BL_VERSION_RC,BL_VERSION_SMINOR,BL_VERSION_BUILD,
		BL_VERSION_YEAR,BL_VERSION_MONTH,BL_VERSION_DAY,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00
};

//VAR(uint8, CanSrv_VAR) Application_Version[APPLICATION_VERSION_SIZE] = {0xAA,0xDD,0xCC,0xBB,0xCC,19,7,15,4,0,0xFF,0xFF,0xFF,0xFF,0xFF};

CONST(uint8, CanSrv_VAR) Calibration_data_Version[CALIBRATION_DATA_VERSION_SIZE] = {0xCC,0xAA,0xBB,0xDD,0xEE,19,7,15,4,0,0xFF,0xFF,0xFF,0xFF,0xFF};

//CONST(uint8, CanSrv_VAR) ISOUDS_EcuSerialNum[ECU_SERIAL_NUM_SIZE]= {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0x11,0x12,0x13};

CONST(uint8, CanSrv_VAR) ISOUDS_VIN_Num[VEHICLE_IDENTIFICATION_NUM_SIZE]= {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17};

//CONST(uint8, CanSrv_VAR) ISOUDS_VehManEcuHwNum[VEHICLE_MAN_ECU_HW_NUM_SIZE]={0x01,0x02,0x03,0x04,0x05,0x06,0x07};

VAR(uint8, CanSrv_VAR)ISOUDS_VehManEcuHwVersion[VEHICLE_MAN_ECU_HW_VERSION_SIZE]={0xAA};

VAR(uint8, AUTOMATIC)   ISOUDS_Bootloader_FingerPrint[BOOTLOADER_TEST_TOOL_FP_SIZE];

VAR(uint8, AUTOMATIC)   ISOUDS_Application_FingerPrint[APPLICATION_FP_SIZE];

VAR(uint8, AUTOMATIC)   ISOUDS_CalbritionData_FingerPrint[CALIBRATION_DATA_FP_SIZE];

VAR(uint8, AUTOMATIC)   ISOUDS_ActiveDiag_session[ACTIVE_DIAG_SIZE];

CONST(uint8, AUTOMATIC)   ISOUDS_SW_componentPartNum[SOFTWARE_COMPONENT_PART_NUM_SIZE]  __attribute__((section(".segmentDID0xF188BOOT"))) = {
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
};

// enrico modified

CONST(ISOUDS_RdDidType,CanSrv_VAR) ISOUDS_RdConfTab[] =
{
		{
				(uint16)ISOUDS_ID_BOOT_SW_ID ,
				(uint8)BOOTLOADER_VERSION_SIZE,
				/* MISRA RULE 11.4 VIOLATION: cast from pointer to uint8* pointer to facilitate reading - of individual bytes from the address locations */
				(uint8 *)BootLoader_Version,
				&ISOUDS_RdArrData,
				(uint8)ISOUDS_DIDSS_T_T_T_F,
				ISOUDS_TRUE
		},
		{
				(uint16)ISOUDS_ID_APP_SW_ID ,
				(uint8)APPLICATION_VERSION_SIZE ,
				/* MISRA RULE 11.4 VIOLATION: cast from pointer to uint8* pointer to facilitate reading - of individual bytes from the address locations */
				(uint8 *)APP_SW_ID_ADDR,
				&ISOUDS_RdArrData,
				(uint8)ISOUDS_DIDSS_T_T_T_F,
				ISOUDS_TRUE
		},
		{
				(uint16)ISOUDS_ID_CAL_DATA_ID ,
				(uint8) CALIBRATION_DATA_VERSION_SIZE  ,
				/* MISRA RULE 11.4 VIOLATION: cast from pointer to uint8* pointer to facilitate reading - of individual bytes from the address locations */
				(uint8 *)Calibration_data_Version,
				&ISOUDS_RdArrData,
				(uint8)ISOUDS_DIDSS_T_T_T_F,
				ISOUDS_TRUE
		},
		{
				(uint16)ISOUDS_ID_BOOT_TEST_TOOL_FP ,
				(uint8)BOOTLOADER_TEST_TOOL_FP_SIZE ,
				/* MISRA RULE 11.4 VIOLATION: cast from pointer to uint8* pointer to facilitate reading - of individual bytes from the address locations */
				(uint8 *)ISOUDS_Bootloader_FingerPrint,
				&ISOUDS_RdArrData,
				(uint8)ISOUDS_DIDSS_T_T_T_F,
				ISOUDS_TRUE
		},
		{
				(uint16)ISOUDS_ID_APP_SW_FP ,
				(uint8)APPLICATION_FP_SIZE ,
				/* MISRA RULE 11.4 VIOLATION: cast from pointer to uint8* pointer to facilitate reading - of individual bytes from the address locations */
				(uint8 *)ISOUDS_Application_FingerPrint,
				&ISOUDS_RdArrData,
				(uint8)ISOUDS_DIDSS_T_T_T_F,
				ISOUDS_TRUE
		},
		{
				(uint16)ISOUDS_ID_CAL_DATA_FP ,
				(uint8)CALIBRATION_DATA_FP_SIZE ,
				/* MISRA RULE 11.4 VIOLATION: cast from pointer to uint8* pointer to facilitate reading -
			            - of individual bytes from the address locations */
				(uint8 *)ISOUDS_CalbritionData_FingerPrint,
				&ISOUDS_RdArrData,
				(uint8)ISOUDS_DIDSS_T_T_T_F,
				ISOUDS_TRUE
		},
		{
				(uint16)ISOUDS_ID_ACTIVE_DIAG_SESSION ,
				(uint8)ACTIVE_DIAG_SIZE ,
				/* MISRA RULE 11.4 VIOLATION: cast from pointer to uint8* pointer to facilitate reading -
						            - of individual bytes from the address locations */
				(uint8 *)ISOUDS_ActiveDiag_session,
				&ISOUDS_RdArrData,
				(uint8)ISOUDS_DIDSS_T_T_T_F,
				ISOUDS_TRUE
		},
		{
				(uint16)ISOUDS_ID_SW_COMP_PART_NUM ,
				(uint8)SOFTWARE_COMPONENT_PART_NUM_SIZE ,
				/* MISRA RULE 11.4 VIOLATION: cast from pointer to uint8* pointer to facilitate reading -
												            - of individual bytes from the address locations */
				(uint8 *)APPL_SW_PART_NUMBER_ADDR,
				&ISOUDS_RdArrData,
				(uint8)ISOUDS_DIDSS_T_T_T_F,
				ISOUDS_TRUE
		},
		{
				(uint16)ISOUDS_ID_ECU_MAN_DATE,
				(uint8)ECU_MAN_DATE_SIZE,
				/* MISRA RULE 11.4 VIOLATION: cast from pointer to uint8* pointer to facilitate reading -
	            - of individual bytes from the address locations */
				(uint8 *)ECU_MAN_DATE_ADDR,
				&ISOUDS_RdArrData,
				(uint8)ISOUDS_DIDSS_T_T_T_F,
				ISOUDS_TRUE
		},

		{
				(uint16)ISOUDS_ID_ECU_SR_NUM,
				(uint8)ECU_SERIAL_NUM_SIZE,
				/* MISRA RULE 11.4 VIOLATION: cast from pointer to uint8* pointer to facilitate reading -
            - of individual bytes from the address locations */
				(uint8 *)ECU_SR_NUM_ADDR,
				&ISOUDS_RdArrData,
				(uint8)ISOUDS_DIDSS_T_T_T_F,
				ISOUDS_TRUE
		},
		{
				(uint16)ISOUDS_ID_VIN_NUM,
				(uint8)VEHICLE_IDENTIFICATION_NUM_SIZE,
				/* MISRA RULE 11.4 VIOLATION: cast from pointer to uint8* pointer to facilitate reading -
	            - of individual bytes from the address locations */
				(uint8 *)ISOUDS_VIN_Num,
				&ISOUDS_RdArrData,
				(uint8)ISOUDS_DIDSS_T_T_T_F,
				ISOUDS_TRUE
		},
		{
				(uint16)ISOUDS_ID_VEH_MAN_ECU_HW_NUM,
				(uint8)VEHICLE_MAN_ECU_HW_NUM_SIZE,
				/* MISRA RULE 11.4 VIOLATION: cast from pointer to uint8* pointer to facilitate reading -
            - of individual bytes from the address locations */
				//(uint8 *)ISOUDS_VehManEcuHwNum,
				(uint8 *)VEH_MAN_ECU_HW_NUM_ADDR,
				&ISOUDS_RdArrData,
				(uint8)ISOUDS_DIDSS_T_T_T_F,
				ISOUDS_TRUE
		},
		{
				(uint16)ISOUDS_ID_VEH_MAN_ECU_HW_VER_NUM,
				(uint8)VEHICLE_MAN_ECU_HW_VERSION_SIZE,
				/* MISRA RULE 11.4 VIOLATION: cast from pointer to uint8* pointer to facilitate reading -
            - of individual bytes from the address locations */
				(uint8 *)ISOUDS_VehManEcuHwVersion,
				&ISOUDS_RdArrData,
				(uint8)ISOUDS_DIDSS_T_T_T_F,
				ISOUDS_TRUE
		},
		{
				(uint16)ISOUDS_ID_ECU_MODE,
				(uint8)ECU_MODE_SIZE,
				/* MISRA RULE 11.4 VIOLATION: cast from pointer to uint8* pointer to facilitate reading -
            - of individual bytes from the address locations */
				// enrico modified
				(uint8*)&FLSHM_ECUmode,
				//(uint8 *)ISOUDS_ECU_mode,
				&ISOUDS_RdArrData,
				(uint8)ISOUDS_DIDSS_T_T_T_F,
				ISOUDS_TRUE
		},
};
