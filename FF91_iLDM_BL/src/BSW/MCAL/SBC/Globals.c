/*
 *    JANI HOVAN, COPYRIGHT (c) 2020
 *    ALL RIGHTS RESERVED
 */

/**
* \file Globals.c
* \ingroup grpXXX
* \brief Global Variables
* \version 1.0.0
* \author Jani Hovan
* \date 2020-10-04
*/

/* === INCLUDES ============================================================= */
#include "board.h"
//#include "CANDiag.h"

#include "Globals.h"      /* Module header */

/* === TYPEDEFS ============================================================= */
/* none */
/* === FORWARD DECLARATIONS ================================================= */
/* none */
/* === SYMBOLIC CONSTANTS =================================================== */
/* none */
/* === MACROS =============================================================== */
/* none */
/* === EXPORTED VARIABLES =================================================== */
volatile strGlobals_t strGlobals;
volatile strUID_t     strUID;
//eCodingType_t         eCodingType;



/* === LOCAL VARIABLES ====================================================== */
/* none */
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
void Globals_vInit(void)
{
    //uint8_t  ii;


    strGlobals.CAN0phyIsReady = FALSE;
    strGlobals.SWresetCnt = 0;
    strGlobals.HWresetCnt = 0;
    strGlobals.LEDdriverInitDone = FALSE;
    strGlobals.LEDdriverUpdatePossible = FALSE;
    strGlobals.VboostOK = FALSE;
    strGlobals.PCBtemp_degC = 25;
    strGlobals.LEDAtemp_degC = 25;
    strGlobals.LEDCtemp_degC = 25;

    // Enrico fix
#if 0
    for (ii = 0; ii < LightFunc_Amount; ii ++)
    {
        strGlobals.strLightFunc[ ii ].in = LIGHTVAL_SNA;
        strGlobals.strLightFunc[ ii ].out = LIGHTVAL_OFF;
        strGlobals.strLightFunc[ ii ].outOld = LIGHTVAL_OFF;
        strGlobals.strLightFunc[ ii ].actPWM = 0U;
        strGlobals.strLightFunc[ ii ].diagControlCurrent.cmd = 0U;
        strGlobals.strLightFunc[ ii ].diagControlCurrent.cmdOld = 0U;
        strGlobals.strLightFunc[ ii ].diagControlCurrent.InputOutputControlById = CANDIAG_UDS_INPUTOUTPUT_CONTROL_BY_ID_RETURN_TO_ECU;
        strGlobals.strLightFunc[ ii ].diagControlCurrent.RoutineControl = CANDIAG_UDS_INPUTOUTPUT_CONTROL_BY_ID_RETURN_TO_ECU;
        strGlobals.strLightFunc[ ii ].diagControlPwm.cmd = 0U;
        strGlobals.strLightFunc[ ii ].diagControlPwm.cmdOld = 0U;
        strGlobals.strLightFunc[ ii ].diagControlPwm.InputOutputControlById = CANDIAG_UDS_INPUTOUTPUT_CONTROL_BY_ID_RETURN_TO_ECU;
        strGlobals.strLightFunc[ ii ].diagControlPwm.RoutineControl = CANDIAG_UDS_INPUTOUTPUT_CONTROL_BY_ID_RETURN_TO_ECU;
        strGlobals.strLightFunc[ ii ].status = LampStatus_Undef;
    }/* for() */
#endif

    strGlobals.DiagApplMsgDisable = FALSE;
    //strGlobals.DiagRxId = 0; //set during start-up
    //strGlobals.DiagTxId = 0; //set during start-up

    strGlobals.Voltage_KL30raw = 0U;
    strGlobals.Voltage_KL30filtered = 0U;


    /* unique identification */
    strUID.UID127_96 = SIM->UIDH;
    strUID.UID95_64  = SIM->UIDMH;
    strUID.UID63_32  = SIM->UIDML;
    strUID.UID31_0   = SIM->UIDL;

    //eCodingType = Coding_None;

} /* END Globals_vInit() */

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
void Globals_vMain(void)
{

} /* END Globals_vMain() */

/* === LOCAL FUNCTIONS ====================================================== */
/* none */

