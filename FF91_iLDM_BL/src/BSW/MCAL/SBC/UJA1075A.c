/*
 *    JANI HOVAN, COPYRIGHT (c) 2020
 *    ALL RIGHTS RESERVED
 */

/**
* \file UJA1075A.h
* \ingroup grpXXX
* \brief Driver for NXP UJA1075A CAN/LIN-SBC.
* \version 1.0.1
* \author Jani Hovan
* \date 2020-11-18
*/

/* === INCLUDES ============================================================= */
#include "board.h"        /* MCU registers */
#include "Globals.h"
#include "LPSPI0.h"
#include "LPSPI.h"

#include "UJA1075A.h"     /* Module header */

/* === TYPEDEFS ============================================================= */
typedef enum
{
     UJA1075A_STATE_DRIVEUP = 0U
    ,UJA1075A_STATE_STANDBY
    ,UJA1075A_STATE_NORMAL
    ,UJA1075A_STATE_SLEEP

    ,UJA1075A_STATE_AMOUNT
} eUJA1075AState_t;

typedef struct strUJA1075AFsm
{
    eUJA1075AState_t  stateAct;
    eUJA1075AState_t  stateOld;
    eUJA1075AState_t  stateNext;
}strUJA1075AFsm_t;

typedef enum
{
     UJA1075A_CMD_NONE = 0U
    ,UJA1075A_CMD_NORMAL
    ,UJA1075A_CMD_STANDBY
    ,UJA1075A_CMD_SLEEP

    ,UJA1075A_CMD_AMOUNT
} eUJA1075A_CMD_t;

typedef struct strUJA1075A
{
    uUJA1075A_REG_WD_And_Status_Register_t WD_And_Status_Register;
    uUJA1075A_REG_Mode_Control_Register_t  Mode_Control_Register;
    uUJA1075A_REG_Int_Control_Register_t   Int_Control_Register;
    uUJA1075A_REG_Int_Status_Register_t    Int_Status_Register;
    uint16_t  watchdogCnt;
    uint16_t  watchdogTriggerTime;
    uint8_t   newCommandCnt;
    uint8_t   newCommandCnt_old;
    eUJA1075A_CMD_t cmd;
}strUJA1075A_t;

/* === FORWARD DECLARATIONS ================================================= */
static uint8_t UJA1075Aloc_CheckNewCommand(void);
static void UJA1075Aloc_CMD_triggerWatchdogTimeout(eUJA1075A_WatchdogPeriod argPeriod);
#if 0
static void UJA1075Aloc_CMD_triggerWatchdogWindow(eUJA1075A_WatchdogPeriod argPeriod);
#endif
static void UJA1075Aloc_CMD_setStandby(void);
static void UJA1075Aloc_CMD_setNormal(void);
static void UJA1075Aloc_CMD_setSleep(void);
static void UJA1075Aloc_CMD_read_WD_And_Status_Register(void);
static void UJA1075Aloc_CMD_read_Mode_Control_Register(void);
static void UJA1075Aloc_CMD_read_Int_Control_Register(void);
static void UJA1075Aloc_CMD_read_Int_Status_Register(void);
static void UJA1075Aloc_CMD_clearAllPendingInterrupts(void);
static void UJA1075Aloc_CMD_setCanWakeup(void);
static void UJA1075Aloc_CMD_clearAllWakeupSources(void);
static void UJA1075Aloc_CMD_doSoftwareReset(void);

/* === SYMBOLIC CONSTANTS =================================================== */
/* none */
/* === MACROS =============================================================== */
#define UJA1075A_FSM_SET_NEW_STATE(x)        (strUJA1075AFsm.stateNext = ( x ))
#define UJA1075A_FSM_CHECK_ENTRY()           (strUJA1075AFsm.stateAct != strUJA1075AFsm.stateOld)
#define UJA1075A_FSM_CHECK_EXIT()            (strUJA1075AFsm.stateAct != strUJA1075AFsm.stateNext)
#define UJA1075A_FSM_SWITCH_STATE()          {strUJA1075AFsm.stateOld = strUJA1075AFsm.stateAct; strUJA1075AFsm.stateAct = strUJA1075AFsm.stateNext;}

/* === EXPORTED VARIABLES =================================================== */
/* none */
/* === LOCAL VARIABLES ====================================================== */
static strUJA1075AFsm_t   strUJA1075AFsm;
static strUJA1075A_t      strUJA1075A;

const strLPSPI_config_t LPSPI0_config =
{
        .PCC_Clocksource     = LPSPI_CLKSOURCE_SPLLDIV2,
        .CFGR1_MasterSlave   = LPSPI_MASTER,

        .IER_Interrupt       = LPSPI_INTERRUPT_NONE,
//      .IER_Interrupt       = LPSPI_INTERRUPT_DATA,

        .DER_DMA_Rx          = LPSPI_DMA_DISABLE,
        .DER_DMA_Tx          = LPSPI_DMA_DISABLE,
        .CFGR1_SAMPLE        = LPSPI_SAMPLE_EDGE,
        .CFGR1_NOSTALL       = LPSPI_NOSTALL_NOSTALL,

        .CFGR1_PCSPOL        = LPSPI_PCSPOL_ACTIVE_LO, /* PCS[n] pin is active low */
//      .CFGR1_PCSPOL        = LPSPI_PCSPOL_ACTIVE_HI, /* PCS[n] pin is active high */

        .CFGR1_PINCFG        = LPSPI_PINCFG_SIN_IN_SOUT_OUT,
//      .CFGR1_PINCFG        = LPSPI_PINCFG_SIN_OUT_SOUT_IN,
//      .CFGR1_OUTCFG        = LPSPI_OUTCFG_RETAINED, /* Output data retains last value when chip-select is negated */
        .CFGR1_OUTCFG        = LPSPI_OUTCFG_TRISTATE, /* Output data is tristated when chip-select is negated */
        .CFGR1_PCSCFG        = LPSPI_PCSCFG_PCS_USED, /* PCS[3:2] are configured for chip-select function */

//      .TCR_FRAMESZ         = LPSPI_FRAMESZ_8bit,
        .TCR_FRAMESZ         = LPSPI_FRAMESZ_16bit,
//      .TCR_FRAMESZ         = LPSPI_FRAMESZ_32bit,

        .TCR_WIDTH           = LPSPI_WIDTH_1bit,  /* 1bit transfer */
        .TCR_TXMSK           = LPSPI_TXMSK_TRANSFER_NORMAL,
        .TCR_RXMSK           = LPSPI_RXMSK_TRANSFER_NORMAL,
        .TCR_CONT            = LPSPI_CONT_DISABLED,
        .TCR_BYSW            = LPSPI_BYSW_DISABLED,
        .TCR_LSBF            = LPSPI_LSBF_MSB_FIRST,
//      .TCR_LSBF            = LPSPI_LSBF_LSB_FIRST,
//      .TCR_PCS             = LPSPI_PCS_PCS0,       /* PCS0 used */
        .TCR_PCS             = LPSPI_PCS_PCS1,       /* PCS1 used */
        .TCR_PRESCALE        = LPSPI_PRESCALE_DIV_8, /* 80MHz / 8 = 10MHz */
//      .TCR_PRESCALE        = LPSPI_PRESCALE_DIV_64, /* 80MHz / 64 = 1,25MHz */

//      .TCR_CPHA            = LPSPI_CPHA_CAPTURE_1ST_EDGE,
        .TCR_CPHA            = LPSPI_CPHA_CAPTURE_2ND_EDGE,

        .TCR_CPOL            = LPSPI_CPOL_INACTIVE_LO,
//      .TCR_CPOL            = LPSPI_CPOL_INACTIVE_HI,

//      .CCR_SCKDIV          = LPSPI_SCKDIV_DIV_10, /* 10MHz / 10 = 1MHz */
        .CCR_SCKDIV          = LPSPI_SCKDIV_DIV_100, /* 10MHz / 100 = 100kHz */
//      .CCR_SCKDIV          = LPSPI_SCKDIV_DIV_200, /* 10MHz / 200 = 50kHz */

        .CCR_DBT             = LPSPI_DBT_10CYCLES, /* Delay between transfers */
        .CCR_PCSSCK          = LPSPI_PCSSCK_20CYCLES, /* PCS-to-SCK Delay */
        .CCR_SCKPCS          = LPSPI_SCKPCS_20CYCLES, /* SCK-to-PCS Delay */

        .FCR_TXWATER         = LPSPI_TXWATER_0WORDS, /* Transmit FIFO Watermark 0Words */
//      .FCR_TXWATER         = LPSPI_TXWATER_1WORDS, /* Transmit FIFO Watermark 1Words */
//      .FCR_TXWATER         = LPSPI_TXWATER_2WORDS, /* Transmit FIFO Watermark 2Words */

        .FCR_RXWATER         = LPSPI_RXWATER_0WORDS, /* Receive FIFO Watermark 0Words */
//      .FCR_RXWATER         = LPSPI_RXWATER_1WORDS, /* Receive FIFO Watermark 1Words */

        .CR_DBGEN            = LPSPI_DBGEN_YES,      /* Enable during debug */
};

/* === EXPORTED FUNCTIONS =================================================== */

/**
 * \brief Init this module.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
void UJA1075A_vInit(void)
{
    LPSPI0_vInit( &LPSPI0_config );

    /* set state-machine */
    strUJA1075AFsm.stateAct = UJA1075A_STATE_DRIVEUP;
    strUJA1075AFsm.stateNext = UJA1075A_STATE_DRIVEUP;
    strUJA1075AFsm.stateOld = UJA1075A_STATE_AMOUNT;

    strUJA1075A.watchdogCnt = 0U;
    strUJA1075A.watchdogTriggerTime = 50U; //[ms] => default is 128ms
    strUJA1075A.newCommandCnt = 0U;
    strUJA1075A.newCommandCnt_old = 0U;
    strUJA1075A.cmd = UJA1075A_CMD_NONE;

    /* read register default values */
    UJA1075Aloc_CMD_read_WD_And_Status_Register();
    NOP();
    UJA1075Aloc_CMD_read_Mode_Control_Register();
    NOP();
    UJA1075Aloc_CMD_read_Int_Control_Register();
    NOP();
    UJA1075Aloc_CMD_read_Int_Status_Register();
} /* END UJA1075A_vInit() */

/******************************************************************************/

/**
 * \brief Cyclic function of this module.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
void UJA1075A_vMain(void)
{
    static uint16_t  stateCnt = 0U;


    //TODO: remove this later !!
    //just dummy for test here !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    strGlobals.SBC_mode         = strUJA1075A.Mode_Control_Register.bits.MC;
    strGlobals.watchdogDisabled = strUJA1075A.WD_And_Status_Register.bits.WOS_SWR;
    strGlobals.SBC_LimpHome     = strUJA1075A.Mode_Control_Register.bits.LHC;



    switch( strUJA1075AFsm.stateAct )
    {
        /*___DRIVEUP__________________________________________________________*/
        case UJA1075A_STATE_DRIVEUP:
            if (UJA1075A_FSM_CHECK_ENTRY())
            {
                /* entry code */
                stateCnt = 0U;
            }

            UJA1075Aloc_CMD_triggerWatchdogTimeout(UJA1075A_WDPERIOD_4096ms);
            UJA1075A_FSM_SET_NEW_STATE(UJA1075A_STATE_STANDBY);

            if (UJA1075A_FSM_CHECK_EXIT())
            {
                /* exit code */
            }
            break;
        /*___STANDBY__________________________________________________________*/
        case UJA1075A_STATE_STANDBY:
            if (UJA1075A_FSM_CHECK_ENTRY())
            {
            	// Enrico added switch to Standby mode
                UJA1075Aloc_CMD_setStandby();

                /* entry code */
                stateCnt = 0U;
            }

#if 0
            UJA1075Aloc_CMD_read_WD_And_Status_Register();

            if (strUJA1075A.WD_And_Status_Register.bits.V2S == 0U)
            {
                //V2-Supply is stable
                strGlobals.CANphyIsReady = TRUE;
                UJA1075Aloc_CMD_triggerWatchdogWindow(UJA1075A_WDPERIOD_32ms);
                NOP();
                UJA1075Aloc_CMD_setNormal();
                UJA1075A_FSM_SET_NEW_STATE(UJA1075A_STATE_NORMAL);
            }
            else
            {
                //V2-Supply is not stable
                strGlobals.CANphyIsReady = FALSE;
                UJA1075Aloc_CMD_triggerWatchdogTimeout(UJA1075A_WDPERIOD_32ms);
            }
#endif

#if 1
            stateCnt ++;
            if (stateCnt > 30U)
            {
                stateCnt = 0U;
                UJA1075Aloc_CMD_triggerWatchdogTimeout(UJA1075A_WDPERIOD_4096ms);
            }

            if (UJA1075Aloc_CheckNewCommand())
            {
                if (strUJA1075A.cmd == UJA1075A_CMD_NORMAL)
                {
                    UJA1075A_FSM_SET_NEW_STATE(UJA1075A_STATE_NORMAL);
                }
            }
#endif

            if (UJA1075A_FSM_CHECK_EXIT())
            {
                /* exit code */
            }
            break;
        /*___NORMAL___________________________________________________________*/
        case UJA1075A_STATE_NORMAL:
            if (UJA1075A_FSM_CHECK_ENTRY())
            {
                /* entry code */
                strUJA1075A.watchdogCnt = 0U;
                // Enrico, adapt for BL
                UJA1075Aloc_CMD_triggerWatchdogTimeout(UJA1075A_WDPERIOD_4096ms);
                //UJA1075Aloc_CMD_triggerWatchdogWindow(UJA1075A_WDPERIOD_32ms);
                NOP();
                NOP();
                UJA1075Aloc_CMD_setNormal();
                NOP();
                NOP();
                UJA1075Aloc_CMD_clearAllWakeupSources();
            }

            strUJA1075A.watchdogCnt ++;
            if (strUJA1075A.watchdogCnt >= strUJA1075A.watchdogTriggerTime)
            {
            	UJA1075Aloc_CMD_triggerWatchdogTimeout(UJA1075A_WDPERIOD_4096ms);
                //UJA1075Aloc_CMD_triggerWatchdogWindow(UJA1075A_WDPERIOD_32ms);
                NOP();
                UJA1075Aloc_CMD_read_WD_And_Status_Register();
                NOP();
                UJA1075Aloc_CMD_read_Mode_Control_Register();
                NOP();
                UJA1075Aloc_CMD_read_Int_Control_Register();
                NOP();
                UJA1075Aloc_CMD_read_Int_Status_Register();

                /* check for sleep-mode - synchronized with WD-tiggering */
                if (UJA1075Aloc_CheckNewCommand())
                {
                    if (strUJA1075A.cmd == UJA1075A_CMD_SLEEP)
                    {
                        UJA1075A_FSM_SET_NEW_STATE(UJA1075A_STATE_SLEEP);
                    }
                	// Enrico: added switch to StandbyMode
                    else if (strUJA1075A.cmd == UJA1075A_CMD_STANDBY)
                    {
                        UJA1075A_FSM_SET_NEW_STATE(UJA1075A_STATE_STANDBY);
                    }
                }
            }

            if (0U == strUJA1075A.WD_And_Status_Register.bits.V2S)
            {
                //V2-Supply is stable
                strGlobals.CAN0phyIsReady = TRUE;
            }
            else
            {
                //V2-Supply is not stable
                strGlobals.CAN0phyIsReady = FALSE;
            }

#if 0
            if (1U == strUJA1075A.Mode_Control_Register.bits.LHWC) //versuch aus LimpHome wieder rauszukommen
            {
                /* "Limp Home Warning Control" is set */
                strUJA1075A.Mode_Control_Register.bits.ADDR = UJA1075A__REGADDR__MODE_CONTROL_REG;
                strUJA1075A.Mode_Control_Register.bits.RO = UJA1075A__RO_ReadWrite;
                strUJA1075A.Mode_Control_Register.bits.LHWC = 0U;
                LPSPI0_vSendReceive16bitBlocking( strUJA1075A.Mode_Control_Register.reg, &strUJA1075A.Mode_Control_Register.reg );
            }
#endif

            if (1U == strUJA1075A.Mode_Control_Register.bits.LHC) //versuch aus LimpHome wieder rauszukommen
            {
                /* "Limp Home Control" is set */
                strUJA1075A.Mode_Control_Register.bits.ADDR = UJA1075A__REGADDR__MODE_CONTROL_REG;
                strUJA1075A.Mode_Control_Register.bits.RO = UJA1075A__RO_ReadWrite;
                strUJA1075A.Mode_Control_Register.bits.LHC = 0u;
                LPSPI0_vSendReceive16bitBlocking( strUJA1075A.Mode_Control_Register.reg, &strUJA1075A.Mode_Control_Register.reg );
            }


            if (UJA1075A_FSM_CHECK_EXIT())
            {
                /* exit code */
            }
            break;
        /*___SLEEP____________________________________________________________*/
        case UJA1075A_STATE_SLEEP:
            if (UJA1075A_FSM_CHECK_ENTRY())
            {
                /* entry code */
                stateCnt = 0U;
                UJA1075Aloc_CMD_clearAllPendingInterrupts();
                NOP();
                UJA1075Aloc_CMD_setCanWakeup();
                NOP();
                UJA1075Aloc_CMD_setSleep();
            }

            /* timeout check */
            stateCnt ++;
            if (stateCnt > 1000U)
            {
                UJA1075Aloc_CMD_doSoftwareReset();
            }

            if (UJA1075A_FSM_CHECK_EXIT())
            {
                /* exit code */
            }
            break;
        /*___DEFAULT__________________________________________________________*/
        default:
            break;
    } /* switch( strUJA1075AFsm.stateAct ) */
    UJA1075A_FSM_SWITCH_STATE();

} /* END UJA1075A_vMain() */

/******************************************************************************/

/**
 * \brief Set the mode to "normal" from outside this module.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
void UJA1075A_CMD_setNormal(void)
{
    strUJA1075A.cmd = UJA1075A_CMD_NORMAL;
    strUJA1075A.newCommandCnt ++;
} /* END UJA1075A_CMD_setNormal() */

/******************************************************************************/

/**
 * \brief Set the mode to "sleep" from outside this module.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
void UJA1075A_CMD_setSleep(void)
{
    strUJA1075A.cmd = UJA1075A_CMD_SLEEP;
    strUJA1075A.newCommandCnt ++;
} /* END UJA1075A_CMD_setSleep() */

/******************************************************************************/

/**
 * \brief Set the mode to "standby" from outside this module.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
void UJA1075A_CMD_setStandby(void)
{
    strUJA1075A.cmd = UJA1075A_CMD_STANDBY;
    strUJA1075A.newCommandCnt ++;
} /* END UJA1075A_CMD_setStandby() */

/******************************************************************************/

/**
 * \brief Perform a Watchdog-Reset from outside this module.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/

void UJA1075A_CMD_performWatchdogReset(void)
{
    UJA1075Aloc_CMD_doSoftwareReset();
} /* END UJA1075A_CMD_performWatchdogReset() */

/* === LOCAL FUNCTIONS ====================================================== */

static uint8_t UJA1075Aloc_CheckNewCommand(void)
{
    uint8_t  retVal;

    if (strUJA1075A.newCommandCnt != strUJA1075A.newCommandCnt_old)
    {
        retVal = TRUE;
    }
    else
    {
        retVal = FALSE;
    }

    strUJA1075A.newCommandCnt_old = strUJA1075A.newCommandCnt;

    return retVal;
} /* END UJA1075Aloc_CheckNewCommand() */

/******************************************************************************/

#if 0 // enrico
/**
 * \brief Trigger the Watchdog in Window-Mode.
 *
 * \param [in] argPeriod The period of watchdog to be set
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
static void UJA1075Aloc_CMD_triggerWatchdogWindow(eUJA1075A_WatchdogPeriod argPeriod)
{
    if (argPeriod < UJA1075A_WDPERIOD_AMOUNT)
    {
        switch (argPeriod)
        {
            case UJA1075A_WDPERIOD_8ms:
                strUJA1075A.watchdogTriggerTime = 6U;
                break;
            case UJA1075A_WDPERIOD_16ms:
                strUJA1075A.watchdogTriggerTime = 12U;
                break;
            case UJA1075A_WDPERIOD_32ms:
                strUJA1075A.watchdogTriggerTime = 24U;
                break;
            case UJA1075A_WDPERIOD_64ms:
                strUJA1075A.watchdogTriggerTime = 48U;
                break;
            case UJA1075A_WDPERIOD_128ms:
                strUJA1075A.watchdogTriggerTime = 96U;
                break;
            case UJA1075A_WDPERIOD_256ms:
                strUJA1075A.watchdogTriggerTime = 192U;
                break;
            case UJA1075A_WDPERIOD_1024ms:
                strUJA1075A.watchdogTriggerTime = 768U;
                break;
            case UJA1075A_WDPERIOD_4096ms:
                strUJA1075A.watchdogTriggerTime = 3072U;
                break;
            default:
                break;
        }//switch (argPeriod)

        strUJA1075A.WD_And_Status_Register.bits.ADDR = UJA1075A__REGADDR__WATCHDOG_AND_STATUS_REG;
        strUJA1075A.WD_And_Status_Register.bits.RO = UJA1075A__RO_ReadWrite;
        strUJA1075A.WD_And_Status_Register.bits.NWP = argPeriod;
        strUJA1075A.WD_And_Status_Register.bits.WOS_SWR = 0U;
        strUJA1075A.WD_And_Status_Register.bits.WMC = 0; // Enrico: Bugfix Window mode
        LPSPI0_vSendReceive16bitBlocking( strUJA1075A.WD_And_Status_Register.reg, &strUJA1075A.WD_And_Status_Register.reg );

        strUJA1075A.watchdogCnt = 0U;
    }//if (argPeriod < UJA1075A_WDPERIOD_AMOUNT)
} /* END UJA1075Aloc_CMD_triggerWatchdogWindow() */
#endif

/******************************************************************************/

/**
 * \brief Trigger the Watchdog in Timeout-Mode.
 *
 * \param [in] argPeriod The period of watchdog to be set
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
static void UJA1075Aloc_CMD_triggerWatchdogTimeout(eUJA1075A_WatchdogPeriod argPeriod)
{
    if (argPeriod < UJA1075A_WDPERIOD_AMOUNT)
    {
        switch (argPeriod)
        {
            case UJA1075A_WDPERIOD_8ms:
                strUJA1075A.watchdogTriggerTime = 4U;
                break;
            case UJA1075A_WDPERIOD_16ms:
                strUJA1075A.watchdogTriggerTime = 8U;
                break;
            case UJA1075A_WDPERIOD_32ms:
                strUJA1075A.watchdogTriggerTime = 16U;
                break;
            case UJA1075A_WDPERIOD_64ms:
                strUJA1075A.watchdogTriggerTime = 32U;
                break;
            case UJA1075A_WDPERIOD_128ms:
                strUJA1075A.watchdogTriggerTime = 64U;
                break;
            case UJA1075A_WDPERIOD_256ms:
                strUJA1075A.watchdogTriggerTime = 128U;
                break;
            case UJA1075A_WDPERIOD_1024ms:
                strUJA1075A.watchdogTriggerTime = 512U;
                break;
            case UJA1075A_WDPERIOD_4096ms:
                strUJA1075A.watchdogTriggerTime = 3072U; // Enrico: bugfix "window" time, before = 2048U;
                break;
            default:
                break;
        }//switch (argPeriod)

        strUJA1075A.WD_And_Status_Register.bits.ADDR = UJA1075A__REGADDR__WATCHDOG_AND_STATUS_REG;
        strUJA1075A.WD_And_Status_Register.bits.RO = UJA1075A__RO_ReadWrite;
        strUJA1075A.WD_And_Status_Register.bits.NWP = argPeriod;
        strUJA1075A.WD_And_Status_Register.bits.WOS_SWR = 0U;
        //strUJA1075A.WD_And_Status_Register.bits.WMC = 1; // Enrico: Bugfix Timeout mode??
        LPSPI0_vSendReceive16bitBlocking( strUJA1075A.WD_And_Status_Register.reg, &strUJA1075A.WD_And_Status_Register.reg );

        strUJA1075A.watchdogCnt = 0U;
    }//if (argPeriod < UJA1075A_WDPERIOD_AMOUNT)
} /* END UJA1075Aloc_CMD_triggerWatchdogTimeout() */

/******************************************************************************/

/**
 * \brief Set the mode to "normal".
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
static void UJA1075Aloc_CMD_setNormal(void)
{
    strUJA1075A.Mode_Control_Register.bits.ADDR = UJA1075A__REGADDR__MODE_CONTROL_REG;
    strUJA1075A.Mode_Control_Register.bits.RO = UJA1075A__RO_ReadWrite;
    strUJA1075A.Mode_Control_Register.bits.MC = UJA1075A__MC_NormalModeV2on;
    LPSPI0_vSendReceive16bitBlocking( strUJA1075A.Mode_Control_Register.reg, &strUJA1075A.Mode_Control_Register.reg );
} /* END UJA1075Aloc_CMD_setNormal() */

/******************************************************************************/

/**
 * \brief Set the mode to "sleep".
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
static void UJA1075Aloc_CMD_setSleep(void)
{
    strUJA1075A.Mode_Control_Register.bits.ADDR = UJA1075A__REGADDR__MODE_CONTROL_REG;
    strUJA1075A.Mode_Control_Register.bits.RO = UJA1075A__RO_ReadWrite;
    strUJA1075A.Mode_Control_Register.bits.MC = UJA1075A__MC_SleepMode;
    strUJA1075A.Mode_Control_Register.bits.LHWC = 0U; //no limp-home warning
    LPSPI0_vSendReceive16bitBlocking( strUJA1075A.Mode_Control_Register.reg, &strUJA1075A.Mode_Control_Register.reg );
} /* END UJA1075Aloc_CMD_setSleep() */

/******************************************************************************/

/**
 * \brief Set the mode to "standby".
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
static void UJA1075Aloc_CMD_setStandby(void)
{
    strUJA1075A.Mode_Control_Register.bits.ADDR = UJA1075A__REGADDR__MODE_CONTROL_REG;
    strUJA1075A.Mode_Control_Register.bits.RO = UJA1075A__RO_ReadWrite;
    strUJA1075A.Mode_Control_Register.bits.MC = UJA1075A__MC_StandbyMode;
    LPSPI0_vSendReceive16bitBlocking( strUJA1075A.Mode_Control_Register.reg, &strUJA1075A.Mode_Control_Register.reg );
} /* END UJA1075Aloc_CMD_setStandby() */

/******************************************************************************/

/**
 * \brief Read the WD_AND_STATUS_REGISTER values.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
static void UJA1075Aloc_CMD_read_WD_And_Status_Register(void)
{
    strUJA1075A.WD_And_Status_Register.bits.ADDR = UJA1075A__REGADDR__WATCHDOG_AND_STATUS_REG;
    strUJA1075A.WD_And_Status_Register.bits.RO = UJA1075A__RO_ReadOnly;
    LPSPI0_vSendReceive16bitBlocking( strUJA1075A.WD_And_Status_Register.reg, &strUJA1075A.WD_And_Status_Register.reg );
} /* END UJA1075Aloc_CMD_read_WD_And_Status_Register() */

/******************************************************************************/

/**
 * \brief Read the MODE_CONTROL_REGISTER values.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
static void UJA1075Aloc_CMD_read_Mode_Control_Register(void)
{
    strUJA1075A.Mode_Control_Register.bits.ADDR = UJA1075A__REGADDR__MODE_CONTROL_REG;
    strUJA1075A.Mode_Control_Register.bits.RO = UJA1075A__RO_ReadOnly;
    LPSPI0_vSendReceive16bitBlocking( strUJA1075A.Mode_Control_Register.reg, &strUJA1075A.Mode_Control_Register.reg );
} /* END UJA1075A_CMD_read_Mode_Control_Register() */

/******************************************************************************/

/**
 * \brief Read the INT_CONTROL_REGISTER values.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
static void UJA1075Aloc_CMD_read_Int_Control_Register(void)
{
    strUJA1075A.Int_Control_Register.bits.ADDR = UJA1075A__REGADDR__INTERRUPT_CONTROL_REG;
    strUJA1075A.Int_Control_Register.bits.RO = UJA1075A__RO_ReadOnly;
    LPSPI0_vSendReceive16bitBlocking( strUJA1075A.Int_Control_Register.reg, &strUJA1075A.Int_Control_Register.reg );
} /* END UJA1075A_CMD_read_Int_Control_Register() */

/******************************************************************************/

/**
 * \brief Read the INT_STATUS_REGISTER values.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
static void UJA1075Aloc_CMD_read_Int_Status_Register(void)
{
    strUJA1075A.Int_Status_Register.bits.ADDR = UJA1075A__REGADDR__INTERRUPT_STATUS_REG;
    strUJA1075A.Int_Status_Register.bits.RO = UJA1075A__RO_ReadOnly;
    LPSPI0_vSendReceive16bitBlocking( strUJA1075A.Int_Status_Register.reg, &strUJA1075A.Int_Status_Register.reg );
} /* END UJA1075A_CMD_read_Int_Status_Register() */

/******************************************************************************/

/**
 * \brief Clear all pending interrupts.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
static void UJA1075Aloc_CMD_clearAllPendingInterrupts(void)
{
    UJA1075Aloc_CMD_read_Int_Status_Register(); //read the actual register values

    strUJA1075A.Int_Status_Register.bits.ADDR = UJA1075A__REGADDR__INTERRUPT_STATUS_REG;
    strUJA1075A.Int_Status_Register.bits.RO = UJA1075A__RO_ReadWrite;
    LPSPI0_vSendReceive16bitBlocking( strUJA1075A.Int_Status_Register.reg, &strUJA1075A.Int_Status_Register.reg );
} /* END UJA1075Aloc_CMD_clearAllPendingInterrupts() */

/******************************************************************************/

/**
 * \brief Set CAN wake-up.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
static void UJA1075Aloc_CMD_setCanWakeup(void)
{
    strUJA1075A.Int_Control_Register.bits.ADDR = UJA1075A__REGADDR__INTERRUPT_CONTROL_REG;
    strUJA1075A.Int_Control_Register.bits.RO = UJA1075A__RO_ReadWrite;
    strUJA1075A.Int_Control_Register.bits.STBCC = 1U;
    LPSPI0_vSendReceive16bitBlocking( strUJA1075A.Int_Control_Register.reg, &strUJA1075A.Int_Control_Register.reg );
} /* END UJA1075Aloc_CMD_setCanWakeup() */

/******************************************************************************/

/**
 * \brief Disable (clear) all wake-up sources.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
static void UJA1075Aloc_CMD_clearAllWakeupSources(void)
{
    strUJA1075A.Int_Control_Register.reg = 0U; //clear all wake-up sources
    strUJA1075A.Int_Control_Register.bits.ADDR = UJA1075A__REGADDR__INTERRUPT_CONTROL_REG;
    strUJA1075A.Int_Control_Register.bits.RO = UJA1075A__RO_ReadWrite;
    LPSPI0_vSendReceive16bitBlocking( strUJA1075A.Int_Control_Register.reg, &strUJA1075A.Int_Control_Register.reg );
} /* END UJA1075Aloc_CMD_clearAllWakeupSources() */

/******************************************************************************/

/**
 * \brief Perform a software-reset.
 *
 * \param [in] -
 * \param [out] -
 * \return -
 *
 * \par Used global resources
 * - \ref x - x
*/
static void UJA1075Aloc_CMD_doSoftwareReset(void)
{
    strUJA1075A.WD_And_Status_Register.bits.ADDR = UJA1075A__REGADDR__WATCHDOG_AND_STATUS_REG;
    strUJA1075A.WD_And_Status_Register.bits.RO = UJA1075A__RO_ReadWrite;
    strUJA1075A.WD_And_Status_Register.bits.WOS_SWR = 1U;
    LPSPI0_vSendReceive16bitBlocking( strUJA1075A.WD_And_Status_Register.reg, &strUJA1075A.WD_And_Status_Register.reg );
} /* END UJA1075Aloc_CMD_doSoftwareReset() */

