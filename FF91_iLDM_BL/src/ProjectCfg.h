/*****************************************************************************************************
** Copyright (c) 2018 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : ProjectCfg.h
** Module name  : Project Configuration Header File
** -------------------------------------------------------------------------------------------------
**
** Description : Project configuration file
**
** -------------------------------------------------------------------------------------------------
**
** Documentation reference :
**
****************************************************************************************************
** R E V I S I O N  H I S T O R Y
****************************************************************************************************
** V01.00 05/10/2018
** - Baseline Created
***************************************************************************************************/
/*To avoid multi-inclusions */
#ifndef _PROJECT_CFG_H_
#define _PROJECT_CFG_H_

#define BL_VERSION_MAJOR	(1)
#define BL_VERSION_MINOR	(1)
#define BL_VERSION_RC		(1)
#define BL_VERSION_SMINOR	(0)
#define BL_VERSION_BUILD	(0)
#define BL_VERSION_YEAR		(22)
#define BL_VERSION_MONTH	(6)
#define BL_VERSION_DAY		(13)

// Defile LOGO ECU
#define FF91_FFL	0

// set HW to Gateway
#define GATEWAY_HW	1

// For Debug only!
#define DISABLE_SECURITY_ACCESS (1)
#define DISABLE_SIGNATURE_CHECK (1)

// Enrico
#define BUS_ID (0x0) 	// BODY
#define ECU_ID (0x3) 	// TODO change with coding 0x3/0x4/0x5/0xC
#define KEY_VERSION (1)	// 0x1 = Development Key

// Enrico Default values, not handled be Coding PIN eval

/* ECU TX ID */
#define CANT_TX_ID           	(0x646U)

/* ECU Physical request id */
#define CANT_PHYS_REQ_ID        (0x645U)

/* ECU Functional request id */
#define CANT_FUNC_REQ_ID        (0x7FFU)

#define CAN_VERSIONINFO_ID      (0x647U)
#define CAN_RESETREASON_ID      (0x642U)


// Address Blocks
#define			APP_SW_ID_ADDR				 (0x1FC00) // R OK
#define			CAL_ID_ADDR				 	 (0x1FC10) // R TODO
#define			APPL_SW_PART_NUMBER_ADDR	 (0x1FC20) // R OK
#define			CAL_PART_NUMBER_ADDR	 	 (0x1FC30) // R TODO
#define			APP_CRC_ADDR			 	 (0x1FFFC)
#define			APP_VALID_FLAGS_ADDR	 	 (0x20000)

#define 		CALIB_ADDR				     (0x60000) // -- 61FFF

#define         ECU_MAN_DATE_ADDR            (0x70000) // RW OK
#define 		ECU_SR_NUM_ADDR				 (0x71000) // RW OK
#define 		HW_VERSION_ADDR				 (0x72000) // RW TODO
#define         ECU_MODE_ADDR        		 (0x73000) // RW OK
#define			VEH_MAN_ECU_HW_NUM_ADDR    	 (0x74000) // RW OK
#define			BL_DIAG_TEST_TOOL_ADDR  	 (0x75000) // RW TODO
#define			APP_DIAG_TEST_TOOL_ADDR    	 (0x76000) // RW TODO
#define			CAL_DIAG_TEST_TOOL_ADDR    	 (0x77000) // RW TODO
#define			VIN_ADDR    	 			 (0x78000) // RW TODO
#define			BL_DATA_ADDR   	 			 (0x7F000) // TODO




#endif	/* _PROJECT_CFG_H_ */
