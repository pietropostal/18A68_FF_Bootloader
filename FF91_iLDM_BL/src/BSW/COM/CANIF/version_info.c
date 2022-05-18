#include <string.h>
#include "board.h"
#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "ProjectCfg.h"

#include "version_info.h"


enum
{
	 CAN0APPL_TX_ACCL_Version_Info = 0
    ,CAN0APPL_TX_HLL_Version_Info
    ,CAN0APPL_TX_HLR_Version_Info
    ,CAN0APPL_TX_RCLL_Version_Info
	,CAN0APPL_TX_RCLR_Version_Info
    ,CAN0APPL_TX_LGL_Version_Info
    ,CAN0APPL_TX_AMOUNT
};


const static uint8 Can0Appl_xxLM_VerionInfoMux[ CAN0APPL_xxLM_VERSIONINFOMUX_SIZE ] = {0x00U, 0x01U};

static CANApplDef_strTxMsg_t CAN0Appl_aTxMsg[ CAN0APPL_TX_AMOUNT ];



/*___Diag Constants___________________________________________________________*/ //TODO move this to Globals.h

/*___DID 0xF180 Bootloader Software Identification____________________________*/
#define BOOT_SW_ID_DID0xF180_SIZE                               (uint8_t)15U

/*___DID 0xF181 Application Software Indetification___________________________*/
#define APPL_SW_ID_DID0xF181_SIZE                               (uint8_t)15U

/*___DID 0xF182 Calibration Data Identification_______________________________*/
#define CAL_DATA_ID_DID0xF182_SIZE                              (uint8_t)15U

/*___DID 0xF188 Software Component Part Numbers_______________________________*/
#define ECU_SW_PART_NR_DID0xF188_SIZE                           (uint8_t)8U

/*___DID 0xF18B ECU Manufacturing Date________________________________________*/
#define ECU_MANUFACTURING_DATE_DID0xF18B_SIZE                   (uint8_t)4U

/*___DID 0xF18C ECU Serial Number_____________________________________________*/
#define ECU_SERIAL_NUMBER_DID0xF18C_SIZE                        (uint8_t)24U

/*___DID 0xF190 Vehicle Identification Number (VIN)___________________________*/
#define VEHICLE_ID_NUMBER_DID0xF190_SIZE                        (uint8_t)17U

/*___DID 0xF191 Vehicle Manufacturer ECU Hardware Number______________________*/
#define VEHICLE_MANUFACTURER_ECU_HW_NUMBER_DID0xF191_SIZE       (uint8_t)8U   //!?!?!??!? lt bootloader spec 1.13.1.4 ist das 21 bytes lang

/*___DID 0xF193 Vehicle Manufacturer ECU Hardware Version_____________________*/
#define VEHICLE_MANUFACTURER_ECU_HW_VERSION_DID0xF193_SIZE      (uint8_t)1U  //!?!?!? lt bootloader spec 1.13.1.5 ist das ECU Hardware Revision ID ?????

/*___DID 0xF198 Diagnostic Test Tool Information______________________________*/
#define DIAGNOSTIC_TEST_TOOL_INFO_DID0xF198_SIZE                (uint8_t)23U

/*___DID 0xF200 ECU Mode______________________________________________________*/
#define ECU_MODE_DID0xF200_SIZE                                 (uint8_t)1U



const uint8_t aApplicationSoftwareIdentification[ APPL_SW_ID_DID0xF181_SIZE ] __attribute__((section(".sectionDID0xF181")));
//const uint8_t aBootloaderSoftwareIdentification[ BOOT_SW_ID_DID0xF180_SIZE ]   __attribute__((section(".sectionDID0xF180")));
extern const uint8 *BootLoader_Version;
#define aBootloaderSoftwareIdentification BootLoader_Version
const uint8_t aEcuManufacturingDate[ ECU_MANUFACTURING_DATE_DID0xF18B_SIZE ]   __attribute__((section(".sectionDID0xF18B")));
const uint8_t aVehicleIdentificationNumber[ VEHICLE_ID_NUMBER_DID0xF190_SIZE ] __attribute__((section(".sectionDID0xF190"))); /* Bootloader spec 1.13.1.3 */ /* DID 0xF190 */
const uint8_t aVehicleManufacturerEcuHwNumber[ VEHICLE_MANUFACTURER_ECU_HW_NUMBER_DID0xF191_SIZE ] __attribute__((section(".sectionDID0xF191")));
const uint8_t aVehicleManufacturerEcuHwVersion[ VEHICLE_MANUFACTURER_ECU_HW_VERSION_DID0xF193_SIZE ] __attribute__((section(".sectionDID0xF193")));
const uint8_t aDiagnosticTestToolInformationBoot[ DIAGNOSTIC_TEST_TOOL_INFO_DID0xF198_SIZE ] __attribute__((section(".sectionDID0xF198BOOT")));  /* Bootloader spec 1.13.2.2.3 und 1.11.11 DID 0xF198 */ //achtung!!!! one time programmable !!!!!!!!
const uint8_t aDiagnosticTestToolInformationAppl[ DIAGNOSTIC_TEST_TOOL_INFO_DID0xF198_SIZE ] __attribute__((section(".sectionDID0xF198APP")));  /* Bootloader spec 1.13.2.2.3 und 1.11.11 DID 0xF198 */ //achtung!!!! one time programmable !!!!!!!!
const uint8_t aDiagnosticTestToolInformationCal[ DIAGNOSTIC_TEST_TOOL_INFO_DID0xF198_SIZE ] __attribute__((section(".sectionDID0xF198CAL")));  /* Bootloader spec 1.13.2.2.3 und 1.11.11 DID 0xF198 */ //achtung!!!! one time programmable !!!!!!!!
const uint8_t aEcuMode[ ECU_MODE_DID0xF200_SIZE ]                              __attribute__((section(".sectionDID0xF200")));






/*___xxLM_Version_Info________________________________________________________*/
typedef union
{
  uint8_t   _u8[8];
  uint16_t  _u16[4];
  uint32_t  _u32[2];
  uint64_t  _u64;
  PRE_PACK struct
  {
	  uint16_t  xxLM_info_mux               : 8; // 1
      uint16_t  xxLM_versionMajor        	: 8; // 2
      uint16_t  xxLM_versionMinor        	: 8; // 3
      uint16_t  xxLM_versionRC 			 	: 8; // 4
      uint16_t  xxLM_versionSubMinor     	: 8; // 5
      uint16_t  xxLM_idBuildMachine      	: 8; // 6
      uint16_t  xxLM_idGitHashUpper      	: 16; // 7 + 8
  }POST_PACK _signal;
}u_xxLM_Version_Info_0x00;

#define CAN0TX_ACCL_Version_Info_0x00 ((u_xxLM_Version_Info_0x00 *)&CAN0Appl_aTxMsg[CAN0APPL_TX_ACCL_Version_Info].aMsg[0])
#define CAN0TX_HLL_Version_Info_0x00 ((u_xxLM_Version_Info_0x00 *)&CAN0Appl_aTxMsg[CAN0APPL_TX_HLL_Version_Info].aMsg[0])
#define CAN0TX_HLR_Version_Info_0x00 ((u_xxLM_Version_Info_0x00 *)&CAN0Appl_aTxMsg[CAN0APPL_TX_HLR_Version_Info].aMsg[0])
#define CAN0TX_RCLL_Version_Info_0x00 ((u_xxLM_Version_Info_0x00 *)&CAN0Appl_aTxMsg[CAN0APPL_TX_RCLL_Version_Info].aMsg[0])
#define CAN0TX_RCLR_Version_Info_0x00 ((u_xxLM_Version_Info_0x00 *)&CAN0Appl_aTxMsg[CAN0APPL_TX_RCLR_Version_Info].aMsg[0])
#define CAN0TX_LGL_Version_Info_0x00 ((u_xxLM_Version_Info_0x00 *)&CAN0Appl_aTxMsg[CAN0APPL_TX_LGL_Version_Info].aMsg[0])

typedef union
{
  uint8_t   _u8[8];
  uint16_t  _u16[4];
  uint32_t  _u32[2];
  uint64_t  _u64;
  PRE_PACK struct
  {
	  uint16_t  xxLM_info_mux               : 8; // 1
      uint16_t  xxLM_versionMajor        	: 8; // 2
      uint16_t  xxLM_versionMinor        	: 8; // 3
      uint16_t  xxLM_versionRC 				: 8; // 4
      uint16_t  xxLM_versionSubMinor     	: 8; // 5
      uint16_t  xxLM_idBuildMachine      	: 8; // 6
      uint16_t  xxLM_idGitHashUpper      	: 16; // 7 + 8
  }POST_PACK _signal;
}u_xxLM_Version_Info_0x01;

#define CAN0TX_ACCL_Version_Info_0x01 ((u_xxLM_Version_Info_0x01 *)&CAN0Appl_aTxMsg[CAN0APPL_TX_ACCL_Version_Info].aMsg[0])
#define CAN0TX_HLL_Version_Info_0x01 ((u_xxLM_Version_Info_0x01 *)&CAN0Appl_aTxMsg[CAN0APPL_TX_HLL_Version_Info].aMsg[0])
#define CAN0TX_HLR_Version_Info_0x01 ((u_xxLM_Version_Info_0x01 *)&CAN0Appl_aTxMsg[CAN0APPL_TX_HLR_Version_Info].aMsg[0])
#define CAN0TX_RCLL_Version_Info_0x01 ((u_xxLM_Version_Info_0x01 *)&CAN0Appl_aTxMsg[CAN0APPL_TX_RCLL_Version_Info].aMsg[0])
#define CAN0TX_RCLR_Version_Info_0x01 ((u_xxLM_Version_Info_0x01 *)&CAN0Appl_aTxMsg[CAN0APPL_TX_RCLR_Version_Info].aMsg[0])
#define CAN0TX_LGL_Version_Info_0x01 ((u_xxLM_Version_Info_0x01 *)&CAN0Appl_aTxMsg[CAN0APPL_TX_LGL_Version_Info].aMsg[0])


void CANIF_VersionInfo_Init( void )
{
	(void)memset( &CAN0Appl_aTxMsg[0], 0, sizeof(CAN0Appl_aTxMsg) );
}


CANApplDef_strTxMsg_t *CANIF_VersionInfo( uint8 coding )
{
	static uint8 tmpCnt = 0;
	uint8 tmpVal;
	uint8 *p;

    tmpVal = Can0Appl_xxLM_VerionInfoMux[ tmpCnt ]; /* get MUX-value */

    tmpCnt ++; /* next index in Mux-Array */
    if (tmpCnt >= CAN0APPL_xxLM_VERSIONINFOMUX_SIZE)
    {
        tmpCnt = 0;
    }


	CAN0Appl_aTxMsg[CAN0APPL_TX_ACCL_Version_Info].aMsg[0] = tmpVal; /* set MUX value */
	CAN0Appl_aTxMsg[CAN0APPL_TX_HLL_Version_Info].aMsg[0] = tmpVal; /* set MUX value */
	CAN0Appl_aTxMsg[CAN0APPL_TX_HLR_Version_Info].aMsg[0] = tmpVal; /* set MUX value */
	CAN0Appl_aTxMsg[CAN0APPL_TX_RCLL_Version_Info].aMsg[0] = tmpVal; /* set MUX value */
	CAN0Appl_aTxMsg[CAN0APPL_TX_RCLR_Version_Info].aMsg[0] = tmpVal; /* set MUX value */
	CAN0Appl_aTxMsg[CAN0APPL_TX_LGL_Version_Info].aMsg[0] = tmpVal; /* set MUX value */

	// fill all with 0x55 as default
	memset( &CAN0TX_ACCL_Version_Info_0x00->_u8[1], 0x55, 7 );
	memset( &CAN0TX_HLL_Version_Info_0x00->_u8[1], 0x55, 7 );
	memset( &CAN0TX_HLR_Version_Info_0x00->_u8[1], 0x55, 7 );
	memset( &CAN0TX_RCLL_Version_Info_0x00->_u8[1], 0x55, 7 );
	memset( &CAN0TX_RCLR_Version_Info_0x00->_u8[1], 0x55, 7 );
	memset( &CAN0TX_LGL_Version_Info_0x00->_u8[1], 0x55, 7 );

	switch ( tmpVal)
	{

	// Boot Version
	case 0x00U:

		p = (uint8_t *)&aBootloaderSoftwareIdentification;

		CAN0TX_ACCL_Version_Info_0x00->_signal.xxLM_versionMajor    = (*(p + 0));
		CAN0TX_ACCL_Version_Info_0x00->_signal.xxLM_versionMinor    = (*(p + 1));
		CAN0TX_ACCL_Version_Info_0x00->_signal.xxLM_versionRC 		= (*(p + 2));
		CAN0TX_ACCL_Version_Info_0x00->_signal.xxLM_versionSubMinor = (*(p + 3));
		CAN0TX_ACCL_Version_Info_0x00->_signal.xxLM_idBuildMachine  = 0x0;
		CAN0TX_ACCL_Version_Info_0x00->_signal.xxLM_idGitHashUpper  = 0x0;

		CAN0TX_HLL_Version_Info_0x00->_signal.xxLM_versionMajor    	= (*(p + 0));
		CAN0TX_HLL_Version_Info_0x00->_signal.xxLM_versionMinor    	= (*(p + 1));
		CAN0TX_HLL_Version_Info_0x00->_signal.xxLM_versionRC 		= (*(p + 2));
		CAN0TX_HLL_Version_Info_0x00->_signal.xxLM_versionSubMinor 	= (*(p + 3));
		CAN0TX_HLL_Version_Info_0x00->_signal.xxLM_idBuildMachine  	= 0x0;
		CAN0TX_HLL_Version_Info_0x00->_signal.xxLM_idGitHashUpper  	= 0x0;

		CAN0TX_HLR_Version_Info_0x00->_signal.xxLM_versionMajor    	= (*(p + 0));
		CAN0TX_HLR_Version_Info_0x00->_signal.xxLM_versionMinor    	= (*(p + 1));
		CAN0TX_HLR_Version_Info_0x00->_signal.xxLM_versionRC 		= (*(p + 2));
		CAN0TX_HLR_Version_Info_0x00->_signal.xxLM_versionSubMinor 	= (*(p + 3));
		CAN0TX_HLR_Version_Info_0x00->_signal.xxLM_idBuildMachine  	= 0x0;
		CAN0TX_HLR_Version_Info_0x00->_signal.xxLM_idGitHashUpper  	= 0x0;

		CAN0TX_RCLL_Version_Info_0x00->_signal.xxLM_versionMajor    = (*(p + 0));
		CAN0TX_RCLL_Version_Info_0x00->_signal.xxLM_versionMinor    = (*(p + 1));
		CAN0TX_RCLL_Version_Info_0x00->_signal.xxLM_versionRC 		= (*(p + 2));
		CAN0TX_RCLL_Version_Info_0x00->_signal.xxLM_versionSubMinor = (*(p + 3));
		CAN0TX_RCLL_Version_Info_0x00->_signal.xxLM_idBuildMachine  = 0x0;
		CAN0TX_RCLL_Version_Info_0x00->_signal.xxLM_idGitHashUpper  = 0x0;

		CAN0TX_RCLR_Version_Info_0x00->_signal.xxLM_versionMajor    = (*(p + 0));
		CAN0TX_RCLR_Version_Info_0x00->_signal.xxLM_versionMinor    = (*(p + 1));
		CAN0TX_RCLR_Version_Info_0x00->_signal.xxLM_versionRC 		= (*(p + 2));
		CAN0TX_RCLR_Version_Info_0x00->_signal.xxLM_versionSubMinor = (*(p + 3));
		CAN0TX_RCLR_Version_Info_0x00->_signal.xxLM_idBuildMachine  = 0x0;
		CAN0TX_RCLR_Version_Info_0x00->_signal.xxLM_idGitHashUpper  = 0x0;

		CAN0TX_LGL_Version_Info_0x00->_signal.xxLM_versionMajor    	= (*(p + 0));
		CAN0TX_LGL_Version_Info_0x00->_signal.xxLM_versionMinor    	= (*(p + 1));
		CAN0TX_LGL_Version_Info_0x00->_signal.xxLM_versionRC 	 	= (*(p + 2));
		CAN0TX_LGL_Version_Info_0x00->_signal.xxLM_versionSubMinor 	= (*(p + 3));
		CAN0TX_LGL_Version_Info_0x00->_signal.xxLM_idBuildMachine  	= 0x0;
		CAN0TX_LGL_Version_Info_0x00->_signal.xxLM_idGitHashUpper  	= 0x0;

		break;




		// Appl Version
		case 0x01U:

			p = (uint8_t *)&aApplicationSoftwareIdentification;

			CAN0TX_ACCL_Version_Info_0x01->_signal.xxLM_versionMajor    = (*(p + 0));
			CAN0TX_ACCL_Version_Info_0x01->_signal.xxLM_versionMinor    = (*(p + 1));
			CAN0TX_ACCL_Version_Info_0x01->_signal.xxLM_versionRC 		= (*(p + 2));
			CAN0TX_ACCL_Version_Info_0x01->_signal.xxLM_versionSubMinor = (*(p + 3));
			CAN0TX_ACCL_Version_Info_0x01->_signal.xxLM_idBuildMachine  = 0x0;
			CAN0TX_ACCL_Version_Info_0x01->_signal.xxLM_idGitHashUpper  = 0x0;

			CAN0TX_HLL_Version_Info_0x01->_signal.xxLM_versionMajor    	= (*(p + 0));
			CAN0TX_HLL_Version_Info_0x01->_signal.xxLM_versionMinor    	= (*(p + 1));
			CAN0TX_HLL_Version_Info_0x01->_signal.xxLM_versionRC 		= (*(p + 2));
			CAN0TX_HLL_Version_Info_0x01->_signal.xxLM_versionSubMinor 	= (*(p + 3));
			CAN0TX_HLL_Version_Info_0x01->_signal.xxLM_idBuildMachine  	= 0x0;
			CAN0TX_HLL_Version_Info_0x01->_signal.xxLM_idGitHashUpper  	= 0x0;

			CAN0TX_HLR_Version_Info_0x01->_signal.xxLM_versionMajor    	= (*(p + 0));
			CAN0TX_HLR_Version_Info_0x01->_signal.xxLM_versionMinor    	= (*(p + 1));
			CAN0TX_HLR_Version_Info_0x01->_signal.xxLM_versionRC 		= (*(p + 2));
			CAN0TX_HLR_Version_Info_0x01->_signal.xxLM_versionSubMinor 	= (*(p + 3));
			CAN0TX_HLR_Version_Info_0x01->_signal.xxLM_idBuildMachine  	= 0x0;
			CAN0TX_HLR_Version_Info_0x01->_signal.xxLM_idGitHashUpper  	= 0x0;

			CAN0TX_RCLL_Version_Info_0x01->_signal.xxLM_versionMajor    = (*(p + 0));
			CAN0TX_RCLL_Version_Info_0x01->_signal.xxLM_versionMinor    = (*(p + 1));
			CAN0TX_RCLL_Version_Info_0x01->_signal.xxLM_versionRC 		= (*(p + 2));
			CAN0TX_RCLL_Version_Info_0x01->_signal.xxLM_versionSubMinor = (*(p + 3));
			CAN0TX_RCLL_Version_Info_0x01->_signal.xxLM_idBuildMachine  = 0x0;
			CAN0TX_RCLL_Version_Info_0x01->_signal.xxLM_idGitHashUpper  = 0x0;

			CAN0TX_RCLR_Version_Info_0x01->_signal.xxLM_versionMajor    = (*(p + 0));
			CAN0TX_RCLR_Version_Info_0x01->_signal.xxLM_versionMinor    = (*(p + 1));
			CAN0TX_RCLR_Version_Info_0x01->_signal.xxLM_versionRC 		= (*(p + 2));
			CAN0TX_RCLR_Version_Info_0x01->_signal.xxLM_versionSubMinor = (*(p + 3));
			CAN0TX_RCLR_Version_Info_0x01->_signal.xxLM_idBuildMachine  = 0x0;
			CAN0TX_RCLR_Version_Info_0x01->_signal.xxLM_idGitHashUpper  = 0x0;

			CAN0TX_LGL_Version_Info_0x01->_signal.xxLM_versionMajor    	= (*(p + 0));
			CAN0TX_LGL_Version_Info_0x01->_signal.xxLM_versionMinor    	= (*(p + 1));
			CAN0TX_LGL_Version_Info_0x01->_signal.xxLM_versionRC 	 	= (*(p + 2));
			CAN0TX_LGL_Version_Info_0x01->_signal.xxLM_versionSubMinor 	= (*(p + 3));
			CAN0TX_LGL_Version_Info_0x01->_signal.xxLM_idBuildMachine  	= 0x0;
			CAN0TX_LGL_Version_Info_0x01->_signal.xxLM_idGitHashUpper  	= 0x0;

			break;



		default:
			break;
	}//switch()

	return &CAN0Appl_aTxMsg[ coding % 4 ];
}

