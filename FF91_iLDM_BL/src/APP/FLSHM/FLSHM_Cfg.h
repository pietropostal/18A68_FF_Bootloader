/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : FLSHM_Cfg.h
** Module name  : FLSHM driver
** -------------------------------------------------------------------------------------------------
**
** Description : Configuration file for CFlash Module
**
** -------------------------------------------------------------------------------------------------
**
** Documentation reference :
**
****************************************************************************************************
** R E V I S I O N  H I S T O R Y
****************************************************************************************************
** V01.00 05/8/2019
** - Baseline Created
***************************************************************************************************/



/********************************************************************************************
 *	|
 *	|__________________S32K144 Memory Architecture__________________________
 *	|
 *	|
 *	|	S32K144  		==> 512 KB Program memory
 *	|
 *	|	1 Sector  		==> 4096 Bytes
 *	|
 *  |	Total sector 	==> 128 Sector (0 to 127)
 *  |
 *	|	Start Address 	==> 0x00000000
 *	|
 *	|	End Address  	==> 0x0007FFFF
 *	|
 *	|__________________Boot loader Memory Mapping____________________________
 *	|
 *	|
 *	|	Boot loader Memory Size ==> 32 KB
 *	|
 *	|	Assigned Sector 		==> 0 to 8
 *	|
 *	|	Start Address 			==> 0x00000000
 *	|
 *	|	End Address   			==> 0x00007FFF
 *	|
 *	|_________________Application Memory Mapping_____________________________
 *	|
 *	|
 *	|	Application Memory Size	==> 240 KB
 *	|
 * 	|	Assigned Sector 		==> 8 to 60
 *  |
 *  |Header Information 		==> 44 Byte
 *	|
 *	|			Start Address	==> 0x00043000
 *	|			End Address   	==> 0x00043FFF
 *	|
 *	|Application Information
 *	|
 *	|			Start Address 	==> 0x00008000U
 *	|			End Address   	==> 0x00043FFFU
 *	|
 *  |_________________Calibration Memory Mapping_____________________________
 *	|
 *	|
 *	|	Calibration Memory Size	==> 240 KB
 *	|
 * 	|	Assigned Sector 		==> 8 to 60
 *  |
 *  |Header Information 		==> 44 Byte
 *	|
 *	|			Start Address	==> 0x0007F000
 *	|			End Address   	==> 0x0007FFFF
 *	|
 *	|Calibration Information
 *	|
 *	|			Start Address 	==> 0x00044000
 *	|			End Address   	==> 0x0007FFFF
 *	|_______________________________________________________________________
 *
 *
 *******************************************************************************************/


// Enrico Changed mapping

/* Application Start Address*/
#define FLSHM_APP_START_ADDRS			0x00008000U

/* Application End Address*/
#define FLSHM_APP_END_ADDRS				(APP_VALID_FLAGS_ADDR+0xFFFU)

/* Application validity record address*/
#define FLSHM_APP_VALID_FLAG			APP_VALID_FLAGS_ADDR


/* Calibration Start Address*/
#define FLSHM_APP_CALIB_BLK_STRT_ADD	CALIB_ADDR

/* Calibration End Address*/
#define FLSHM_APP_CALIB_END_ADDRS		(CALIB_ADDR+0x1FFFU)

/* Calibration validity record address*/
#define FLSHM_APP_CALIB_VALID_ADDRS		(CALIB_ADDR+0x1000U)


/* Number of Block*/
#define FLSHM_NUM_OF_BLOCKS				0x2U

/* Programming Block Table*/
#define FLSHM_LOGICAL_BLK_TAB \
		{FLSHM_APP_START_ADDRS, 		FLSHM_APP_END_ADDRS,            FLSHM_APP_VALID_FLAG},\
		{FLSHM_APP_CALIB_BLK_STRT_ADD,  FLSHM_APP_CALIB_END_ADDRS,      FLSHM_APP_CALIB_VALID_ADDRS}

/* Polynomial*/
#define FLSHM_CRC_POLYNML				0xEDB88320U

/* Bootup delay to accomodate receiving program session request during bootup: initial 20 ms is scheduled for 1msec */
#define BOOTUP_DELAY					(2U)

#define FLSHM_CRC_CALSLOT_SIZE			0x300U

#define FLSHM_SHA256_CALSLOT_SIZE		128U


/* Application reset handler address*/
#define FLSHM_APP_JUMP_ADDRESS			FLSHM_APP_START_ADDRS




#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define E0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define E1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))





