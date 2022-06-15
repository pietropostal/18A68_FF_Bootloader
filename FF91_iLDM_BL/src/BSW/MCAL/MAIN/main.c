/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "S32K144.h" /* include peripheral declarations S32K142 */
#include "Mcu.h"
#include "GPT.h"
#include "WDT.h"
#include "Flash.h"
#include "SchM.h"
#include "CanTp.h"
#include "CanIf_Cfg.h"
#include"ISOUDS.h"
#include"FLSHM.h"
#include"FLSHM_Comn.h"
#include "board.h"        /* MCU registers */
#include "Globals.h"
#include "LPSPI0.h"
#include "ADC.h"
#include "ADC0.h"
#include "UJA1075A.h"     /* Module header */


/*___Coding Thresholds___ mV*/

#define CODING_THRESH_HLL_LO       0U
#define CODING_THRESH_HLL_HI       500U
#define CODING_THRESH_ACCL_LO      501U
#define CODING_THRESH_ACCL_HI      1500U
#define CODING_THRESH_HLR_LO       1501U
#define CODING_THRESH_HLR_HI       2500U
#define CODING_THRESH_RCLL_LO      2501U
#define CODING_THRESH_RCLL_HI      3500U
#define CODING_THRESH_LGL_LO       3501U
#define CODING_THRESH_LGL_HI       4500U
#define CODING_THRESH_RCLR_LO      4501U
#define CODING_THRESH_RCLR_HI      5000U

eCodingType_t  eCodingType = Coding_None;

uint8 Coding_StartupFinished = 0;


// Start_FIX Enrico
FUNC(void, FLSHM_CODE) FLSHM_JumpToApp(void);
// END_Fix

#if 0 // Enrico removed, not used
void App_SetCanBaudrate(uint32_t *CAN_BaudRate)
{
	*CAN_BaudRate = CAN_500KBPS;
}
#endif



static void handleCoding()
{
#if FF91_FFL
	eCodingType = Coding_FFL;
	CanIf_ConfigureIDs( 0x745, 0x746, 0x747, 0x742 );
#else
    uint16_t         tmpVal;

    ADC0_vMain();
    tmpVal = ADC0_aResults[ ADCchannel_SYS_CODE ];

	/*___Check for Coding-Type___*/

	if (
			(CODING_THRESH_HLL_LO <= tmpVal)
			&&
			(CODING_THRESH_HLL_HI >= tmpVal)
	   )
	{
		eCodingType = Coding_HLL;
		CanIf_ConfigureIDs( 0x645, 0x646, 0x647, 0x642 );
	}
	else if (
			(CODING_THRESH_ACCL_LO <= tmpVal)
			&&
			(CODING_THRESH_ACCL_HI >= tmpVal)
			)
	{
		eCodingType = Coding_ACCL;
		CanIf_ConfigureIDs( 0x715, 0x716, 0x717, 0x712 );
	}
	else if (
			(CODING_THRESH_HLR_LO <= tmpVal)
			&&
			(CODING_THRESH_HLR_HI >= tmpVal)
			)
	{
		eCodingType = Coding_HLR;
		CanIf_ConfigureIDs( 0x64D, 0x64E, 0x64F, 0x64A );
	}
	else if (
			(CODING_THRESH_RCLL_LO <= tmpVal)
			&&
			(CODING_THRESH_RCLL_HI >= tmpVal)
			)
	{
		eCodingType = Coding_RCLL;
		CanIf_ConfigureIDs( 0x6FD, 0x6FE, 0x6FF, 0x6FA );
	}
	else if (
			(CODING_THRESH_LGL_LO <= tmpVal)
			&&
			(CODING_THRESH_LGL_HI >= tmpVal)
			)
	{
		eCodingType = Coding_LGL;
		CanIf_ConfigureIDs( 0x6ED, 0x6EE, 0x6EF, 0x6EA );
	}
	else if (
			(CODING_THRESH_RCLR_LO <= tmpVal)
			&&
			(CODING_THRESH_RCLR_HI >= tmpVal)
			)
	{
		eCodingType = Coding_RCLR;
		CanIf_ConfigureIDs( 0x705, 0x706, 0x707, 0x702 );
	}

#endif

}



void Coding_Startup(void)
{
	static uint16 coding_counter = 50+1; // wait 50ms

	if( 1 == coding_counter )
	{
		handleCoding();

		UJA1075A_CMD_setNormal();

		/* Initialize CAN module */
		CanIf_Init();
		/* Initialize CAN TP module */
		ISOTP_Init();

		/* Initialize UDS module */
		if(FLSHM_GetReprogStat() == FLSHM_REPROG_REQ)
		{
			ISOUDS_Init(1);
			FLSHM_ClrReprogReq();

			// START_FIX Enrico: removed
			/*SBC driver init */
			//UJA1075A_vInit();
			//SBC_InitStat = TRUE;
			// END_FIX
		}
		else
		{
			ISOUDS_Init(0);
		}

		// start other mainfunctions
		Coding_StartupFinished = 1;
	}

	if( coding_counter > 0 )
	{
		coding_counter--;
	}
}


int main(void)
{
	/* Initialize Low Level Driver */

	Mcu_Init();

	/* Initialize 32Mhz clock */
	GPT_init();

	// START_FIX Enrico: jump to appl if valid and no request
	#if 0 // This is now done is startup_S32K144.s
		if( (FLSHM_REPROG_REQ != FLSHM_GetReprogStat()) && ( r0,0xA5A5A5A5 !=  *((uint32 *)FLSHM_APP_VALID_FLAG)) )
		{
			/* Clear Application Update Request */
			FLSHM_ClrReprogReq();

			/* Directly Jump to Application (Since Application Validation was already performed in the Application) */
			FLSHM_JumpToApp();
		}
	#endif
	// END_FIX

	/* Initialize Flash */
	FLASH_DRV_Init();

	/* Initialize Flash Manager */
	FLSHM_Init();
#if 0
	/* Check if Application Update Request is present */
	if( FLSHM_REPROG_REQ == FLSHM_GetReprogStat() )
	{
		/* Erase the Application Partition */
		FlashStatus = FLASH_DRV_EraseSector(FLSHM_APP_VALID_ADDR, (FLSHM_APP_END_ADDRS - FLSHM_APP_VALID_ADDR + 1U));

		if(STATUS_SUCCESS == FlashStatus)
		{
			/* Set the Source Address to the Start of Data Loader Partition */
			AppSrcAddr = (uint8 *)FLSHM_DL_VALID_ADDR;

			/* Copy data from Data Loader to Application Partition */
			FlashStatus |= FLASH_DRV_Program( FLSHM_APP_VALID_ADDR,
							   	   	   	     (FLSHM_APP_END_ADDRS - FLSHM_APP_VALID_ADDR + 1U),
											 AppSrcAddr);

			if(STATUS_SUCCESS == FlashStatus)
			{
				/* Clear Application Update Request */
				FLSHM_ClrReprogReq();

				/* Directly Jump to Application (Since Application Validation was already performed in the Application) */
				FLSHM_JumpToApp();
			}
			else
			{
				/* Problem in copying data to Application Partition, so stay in Bootloader */
			}
		}
		else
		{
			/* Problem in erasing Application Partition, so stay in Bootloader */
		}

		/* Clear Application Update Request */
		FLSHM_ClrReprogReq();
	}
	else
	{
		/* Do nothing */
	}
}
#endif


	// START_FIX Enrico: added
	 /*SBC driver init */
	UJA1075A_vInit();
	// activate CAN
	//UJA1075A_CMD_setNormal(); // move to after coding
	SBC_InitStat = TRUE;
	// END_FIX


    /*___init IOs_____________________________________________________________*/
//    IO_vInit();
    MCU_24V0_ENABLE_doENABLE();
    MCU_24V0_ENABLE_toOUT();

    //MCU_24V0_SYNC_toOUT();
    //MCU_24V0_SYNC_toHI();

    MCU_24V0_PGOOD_toIN();

    //>>> done via PWM
    //MCU_LEDA_ENA_doENABLE(); //Turn LED ON/OFF
    //MCU_LEDA_ENA_doDISABLE(); //Turn LED ON/OFF
    //MCU_LEDA_ENA_toOUT();

    //MCU_LEDB_ENA_doENABLE(); //Turn LED ON/OFF
    //MCU_LEDB_ENA_doDISABLE(); //Turn LED ON/OFF
    //MCU_LEDB_ENA_toOUT();

    //MCU_LEDC_ENA_doENABLE(); //Turn LED ON/OFF
    //MCU_LEDC_ENA_doDISABLE(); //Turn LED ON/OFF
    //MCU_LEDC_ENA_toOUT();

    //MCU_LEDD_ENA_doENABLE(); //Turn LED ON/OFF
    //MCU_LEDD_ENA_doDISABLE(); //Turn LED ON/OFF
    //MCU_LEDD_ENA_toOUT();
    //<<<< done via PWM

    MCU_KL30_PS_ENA_doENABLE();
    MCU_KL30_PS_ENA_toOUT();

    MCU_LWC_ENA_doDISABLE();
    MCU_LWC_ENA_toOUT();

    MCU_LWC_ST_toIN();

    SPI_CS_POTI_doDEACTIVATE();
    SPI_CS_POTI_toOUT();

    /*** analog pins ***/
    KL30_MEAS_toANALOG();
    TEMP_MEAS_toANALOG();
    MCU_LEDC_NTC_toANALOG();
    MCU_LEDC_BIN_toANALOG();
    MCU_LEDA_BIN_toANALOG();
    MCU_LEDA_NTC_toANALOG();
    SYS_CODE_toANALOG();

    ADC0_vInit();

	/* Enable global interrupts */
	ENABLE_INTERRUPTS();

	/* Initialize Scheduler module*/
	SchmInit();

	/* Run the scheduler */
	SchM_Main();

	for(;;)
	{}

    /* to avoid the warning message for GHS and IAR: statement is unreachable*/
#if defined (__ghs__)
#pragma ghs nowarning 111
#endif
#if defined (__ICCARM__)
#pragma diag_suppress=Pe111
#endif

	return 0;
}



