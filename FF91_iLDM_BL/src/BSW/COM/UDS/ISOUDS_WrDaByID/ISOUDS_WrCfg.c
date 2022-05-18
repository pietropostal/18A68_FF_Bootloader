/***************************************************************************************************
 ** Copyright (c) 2019 EMBITEL
 **
 ** This software is the property of EMBITEL.
 ** It can not be used or duplicated without EMBITEL authorization.
 **
 ** -------------------------------------------------------------------------------------------------
 ** File Name    : ISOUDS_wrcfg.c
 ** Module name  : CANWRDBID
 ** -------------------------------------------------------------------------------------------------
 ** Description : Configuration file of component CanSrv_WrDaByID.c
 ** This file must exclusively contain informations needed to
 ** use this component.
 **
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

/**************************************** Inclusion files *****************************************/
#include "ISOUDS_wrcfg.h"
#include "ISOUDS_WrDaByID.h"
#include "ISOUDS_RdCfg.h"
#include "ISOUDS_SA.h"
#include "Flash.h"
#include "FLSHM.h"

/********************** Declaration of local symbol and constants *********************************/

/********************************* Declaration of local macros ************************************/

/********************************* Declaration of local types *************************************/

/******************************* Declaration of local variaCanSrves *******************************/

/********************* DID'S flag******************************************************************/
uint8 CanSrv_WrTrigFlag  ;

/******************************* Declaration of local constants ***********************************/

/****************************** Declaration of exported variaCanSrves *****************************/

/****************************** Declaration of exported constants *********************************/
CONST(CanSrv_WrDidType, CanSrv_VAR) CanSrv_cWrConfTab[CANSRV_WRCONFTABSIZE] =
{
		{
				(uint16)ISOUDS_ID_BOOT_TEST_TOOL_FP,
				(uint8)BOOTLOADER_TEST_TOOL_FP_SIZE,
				&CanSrv_WriteTASK,
				(uint8)CANSRV_DIDSS_T_T_T_F
		},
		{
				(uint16)ISOUDS_ID_APP_SW_FP,
				(uint8)APPLICATION_FP_SIZE,
				&CanSrv_WriteTASK,
				(uint8)CANSRV_DIDSS_F_T_T_F
		},
		{
				(uint16)ISOUDS_ID_CAL_DATA_FP,
				(uint8)CALIBRATION_DATA_FP_SIZE,
				&CanSrv_WriteTASK,
				(uint8)CANSRV_DIDSS_F_T_T_F
		},

		// enrico added
		{
				(uint16)ISOUDS_ID_ECU_MODE,
				(uint8)ECU_MODE_SIZE,
				&CanSrv_WriteTASK,
				(uint8)CANSRV_DIDSS_F_T_T_F
		},
		{
				(uint16)ISOUDS_ID_ECU_MAN_DATE,
				(uint8)ECU_MAN_DATE_SIZE,
				&CanSrv_WriteTASK,
				(uint8)CANSRV_DIDSS_F_T_T_F
		},
		{
				(uint16)ISOUDS_ID_ECU_SR_NUM,
				(uint8)ECU_SERIAL_NUM_SIZE,
				&CanSrv_WriteTASK,
				(uint8)CANSRV_DIDSS_F_T_T_F
		},
		{
				(uint16)ISOUDS_ID_VEH_MAN_ECU_HW_NUM,
				(uint8)VEHICLE_MAN_ECU_HW_NUM_SIZE,
				&CanSrv_WriteTASK,
				(uint8)CANSRV_DIDSS_F_T_T_F
		}

};

/***************************************************************************************************
 **                                      FUNCTIONS                                                 **
 ***************************************************************************************************/

/**************************** Internal functions declarations *************************************/

/******************************** Function definitions ********************************************/

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

FUNC(uint8, CAN_CODE)CanSrv_WriteTASK(VAR(uint8, AUTOMATIC)DID_Index,
		CONST(uint8, AUTOMATIC)srcBuff[],
		VAR(uint8, AUTOMATIC)len
)
{
	VAR(uint8,  AUTOMATIC)indx;
	VAR(uint8,  AUTOMATIC)WriteTask_Retval = 2U;
	VAR(uint8,  AUTOMATIC)SIDLength = 0U;
	uint8 up_retval = 0u;

	/* Get Security access detail*/
	if((uint8)ISOUDS_TRUE == ISOUDS_GetSAStLevel(1U))
	{
		/* Test supported write id*/
		switch(CanSrv_cWrConfTab[DID_Index].wrDid)
		{
			case ISOUDS_ID_BOOT_TEST_TOOL_FP:
			{

				/* Get supported id Length*/
				SIDLength = BOOTLOADER_TEST_TOOL_FP_SIZE;

				/* filling buffer by Source buffer*/
				for(indx = (uint8)0u; indx<SIDLength; indx++)
				{
					ISOUDS_Bootloader_FingerPrint[indx] = srcBuff[indx];
				}

				WriteTask_Retval = 1;
			} break;

			case ISOUDS_ID_APP_SW_FP:
			{

				/* Get supported id Length*/
				SIDLength = APPLICATION_FP_SIZE;

				/* filling buffer by Source buffer*/
				for(indx = (uint8)0u; indx<SIDLength; indx++)
				{
					ISOUDS_Application_FingerPrint[indx] = srcBuff[indx];
				}
				WriteTask_Retval = 1;
			} break;

			case ISOUDS_ID_CAL_DATA_FP:
			{

				/* Get supported id Length*/
				SIDLength = CALIBRATION_DATA_FP_SIZE;

				/* filling buffer by Source buffer*/
				for(indx = (uint8)0u; indx<SIDLength; indx++)
				{
					ISOUDS_CalbritionData_FingerPrint[indx] = srcBuff[indx];
				}
				WriteTask_Retval = 1;
			} break;

			// enrico added
			case ISOUDS_ID_ECU_MODE:
			{
				if( (len == 1) && ((srcBuff[0] == PRODUCTION_MODE) || (srcBuff[0] == MANFACTURING_MODE)) )
				{
					// check OTM
					if(1) // ((uint8 *)ECU_MODE_ADDR)[0] == 0xFF )
					{
						// Erase Sector and write data
						up_retval = FLASH_DRV_EraseSector( ECU_MODE_ADDR, FEATURE_FLS_PF_BLOCK_SECTOR_SIZE);
						if(STATUS_SUCCESS == up_retval)
						{
							/* Flash the data */
							up_retval = FLASH_DRV_Program( ECU_MODE_ADDR, 8, &srcBuff[0] );

							/* Check if the flash success */
							if (up_retval == STATUS_SUCCESS)
							{
								WriteTask_Retval = 1;
							}
						}

						FLSHM_ECUmode = srcBuff[0];

						WriteTask_Retval = 1;
					}
					else
					{
						// already written
						// enrico TODO error codes
						WriteTask_Retval = 2;
					}
				}
				else
				{
					// enrico TODO error codes
					WriteTask_Retval = 2;
				}

			} break;

			case ISOUDS_ID_ECU_MAN_DATE:
			{
				if( len == ECU_MAN_DATE_SIZE )
				{
					// Erase Sector and write data
					up_retval = FLASH_DRV_EraseSector( ECU_MAN_DATE_ADDR, FEATURE_FLS_PF_BLOCK_SECTOR_SIZE);
					if(STATUS_SUCCESS == up_retval)
					{
						/* Flash the header */
						up_retval = FLASH_DRV_Program( ECU_MAN_DATE_ADDR, 8, &srcBuff[0] );

						/* Check if the flash success */
						if (up_retval == STATUS_SUCCESS)
						{
							WriteTask_Retval = 1;
						}
					}
				}
				else
				{
					// enrico TODO error codes
					WriteTask_Retval = 2;
				}

			} break;

			case ISOUDS_ID_ECU_SR_NUM:
			{
				if( len == ECU_SERIAL_NUM_SIZE )
				{
					// Erase Sector and write data
					up_retval = FLASH_DRV_EraseSector( ECU_SR_NUM_ADDR, FEATURE_FLS_PF_BLOCK_SECTOR_SIZE);
					if(STATUS_SUCCESS == up_retval)
					{
						/* Flash the header */
						up_retval = FLASH_DRV_Program( ECU_SR_NUM_ADDR, 8*4, &srcBuff[0] );

						/* Check if the flash success */
						if (up_retval == STATUS_SUCCESS)
						{
							WriteTask_Retval = 1;
						}
					}
				}
				else
				{
					// enrico TODO error codes
					WriteTask_Retval = 2;
				}

			} break;

			case ISOUDS_ID_VEH_MAN_ECU_HW_NUM:
			{
				if( len == VEHICLE_MAN_ECU_HW_NUM_SIZE )
				{
					// Erase Sector and write data
					up_retval = FLASH_DRV_EraseSector( VEH_MAN_ECU_HW_NUM_ADDR, FEATURE_FLS_PF_BLOCK_SECTOR_SIZE);
					if(STATUS_SUCCESS == up_retval)
					{
						/* Flash the header */
						up_retval = FLASH_DRV_Program( VEH_MAN_ECU_HW_NUM_ADDR, 8, &srcBuff[0] );

						/* Check if the flash success */
						if (up_retval == STATUS_SUCCESS)
						{
							WriteTask_Retval = 1;
						}
					}
				}
				else
				{
					// enrico TODO error codes
					WriteTask_Retval = 2;
				}

			} break;

			default:
			{
				break;
			}
		} 
	}
	else/* Return NACK on security failure*/
	{
		WriteTask_Retval = 0x00U;
	}

	return (WriteTask_Retval);
}
