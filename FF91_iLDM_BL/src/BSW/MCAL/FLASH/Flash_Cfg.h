/** Copyright (c) 2019 EMBITEL
**
** This software is the property of Embitel.
** It can not be used or duplicated without Embitel authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : Flash_Cfg.h
** Module name  : FLASH DRIVER
** -------------------------------------------------------------------------------------------------
** Description : Flash driver with functionality of Read/Write
**
** -------------------------------------------------------------------------------------------------
**
****************************************************************************************************
** R E V I S I O N  H I S T O R Y
****************************************************************************************************
** V01.00
** - First release
*/

/*To avoid multi-inclusions */
#ifndef FLSHT_CFG_H
#define FLSHT_CFG_H
/**************************************** Inclusion files *****************************************/

/************************** Declaration of global symbol and constants ****************************/
#define FLASH_PRG_FLASH_BASE			0x00000000U
#define FLASH_PRG_FLASH_SIZE			0x00100000U
#define FLASH_DATA_FLASH_BASE			0x10000000U
#define FLASH_DATA_FLASH_SIZE			0x00000100U
#define FLASH_EEE_BASE					0x14000000U

#define PFLASH_SECTOR_SIZE				FEATURE_FLS_PF_BLOCK_SECTOR_SIZE
#define DFLASH_SECTOR_SIZE				FEATURE_FLS_DF_BLOCK_SECTOR_SIZE
/********************************* Declaration of global macros ***********************************/

/********************************* Declaration of global types ************************************/

/****************************** External links of global variables ********************************/

/****************************** External links of global constants ********************************/

/***************************************************************************************************
**                                            FUNCTIONS                                           **
***************************************************************************************************/

#endif /* FLSHT_CFG_H */
