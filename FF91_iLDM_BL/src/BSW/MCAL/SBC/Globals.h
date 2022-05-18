/*
 *    JANI HOVAN, COPYRIGHT (c) 2020
 *    ALL RIGHTS RESERVED
 */

/**
* \file Globals.h
* \ingroup grpXXX
* \brief Global Variables
* \version 1.0.0
* \author Jani Hovan
* \date 2020-10-04
*/


#ifndef GLOBALS_H_
#define GLOBALS_H_

/* === INCLUDES ============================================================= */
#include "myTypes.h"

/* === TYPEDEFS ============================================================= */
enum
{
     LightFunc_LowBeam = 0U
    ,LightFunc_HighBeam
    ,LightFunc_PositionLight
    ,LightFunc_DayDrivingLight
    ,LightFunc_SideMarkerLight
    ,LightFunc_TurnLight
    ,LightFunc_Sync
    ,LightFunc_StopLight
    ,LightFunc_TurnLightRear
    ,LightFunc_PositionLightRear
    ,LightFunc_LevelCmd

    ,LightFunc_Amount
};

typedef enum
{
     Coding_None = 0U
	,Coding_ACCL
    ,Coding_HLL
    ,Coding_HLR
    ,Coding_RCLL
	,Coding_RCLR
	,Coding_LGL
    ,Coding_Amount
}eCodingType_t;

typedef enum /* should meet the CAN-signals XXLM_Status */
{
     LampStatus_OK_OFF = 0U
    ,LampStatus_OK_ON  = 1U
    ,LampStatus_Short  = 2U
    ,LampStatus_OpenLoad = 2U
    ,LampStatus_Undef  = 3U  //SNA

    ,LampStatus_Amount
}eLampStatus_t;

typedef struct
{
    uint8_t  cmd;
    uint8_t  cmdOld;
    uint8_t  InputOutputControlById; /* Sub-functions */
    uint8_t  RoutineControl; /* Sub-functions */
    uint8_t  Pwm; /* PWM for light */
}strDiagControlPwm_t;

typedef struct
{
    uint8_t  cmd;
    uint8_t  cmdOld;
    uint8_t  InputOutputControlById; /* Sub-functions */
    uint8_t  RoutineControl; /* Sub-functions */
    uint16_t Current; /* current for light */
}strDiagControlCurrent_t;

typedef struct
{
    uint8_t                  in;
    uint8_t                  out;
    uint8_t                  outOld;
    uint8_t                  actPWM;
    eLampStatus_t            status;
    strDiagControlPwm_t      diagControlPwm;
    strDiagControlCurrent_t  diagControlCurrent;
}strLightFunc_t;

typedef struct
{
    strLightFunc_t  strLightFunc[ LightFunc_Amount ];

    uint8_t   CAN0phyIsReady;
    uint16_t  SWresetCnt;
    uint16_t  HWresetCnt;

    uint16_t  DiagRxId;
    uint16_t  DiagTxId;
    uint8_t   DiagApplMsgDisable;

    uint8_t   VboostOK;

    sint16_t  PCBtemp_degC;
    sint16_t  LEDCtemp_degC;
    sint16_t  LEDAtemp_degC;

    uint8_t   LEDdriverInitDone;
    uint8_t   LEDdriverUpdatePossible;

    uint16_t  Voltage_KL30raw;
    uint16_t  Voltage_KL30filtered;


    //TODO: später alles weg !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    uint8_t   SBC_mode;
    uint8_t   watchdogDisabled;
    uint8_t   SBC_LimpHome;
    uint16_t  CodingVoltage;
}strGlobals_t;

typedef struct
{
    uint32_t  UID127_96;
    uint32_t  UID95_64;
    uint32_t  UID63_32;
    uint32_t  UID31_0;
}strUID_t;


/* === SYMBOLIC CONSTANTS =================================================== */
/*___CAN-Signals___*/
#define LIGHTVAL_OFF              0x00U
#define LIGHTVAL_ON               0x01U
#define LIGHTVAL_SNA              0x03U

/* CAN-Signals */
//#define XXX_STATUS_OFF      0x00U
//#define XXX_STATUS_ON       0x01U
//#define XXX_STATUS_FAULT    0x02U
//#define XXX_STATUS_SNA      0x03U

#define CAN_INACTIVITY_THRESH     4000U //[ms]

/*___PWM/Current for the Lamps___*/
#define PWM_HIBEAM                100U  /* [%] */
#define PWM_LOBEAM                100U  /* [%] */
#define PWM_POSLIGHT              50U   /* [%] */
#define PWM_DRL                   100U  /* [%] */
#define PWM_REAR_TURN             100U  /* [%] */
#define PWM_REAR_POSLIGHT         20U   /* [%] */
#define PWM_REAR_STOPLIGHT        100U  /* [%] */
#define I_HIBEAM_mA               900U  /* [mA] */
#define I_LOBEAM_mA               900U  /* [mA] */
#define I_FRONT_DRL_PO_mA         800U  /* [mA] */
#define I_FRONT_TURN_mA           1200U /* [mA] */
#define I_REAR_POS_mA             400U  /* [mA] */
#define I_REAR_STOP_mA            400U  /* [mA] */
#define I_REAR_TURN_mA            400U  /* [mA] */

/*___Thresholds for Lamp-Check___*/
#define LAMP_THRESH_SHORT         3U
#define LAMP_THRESH_OPEN          80U
#define LAMP_THRESH_OFF_LO        7U
#define LAMP_THRESH_OFF_HI        12U
#define LAMP_THRESH_ON_LO         15U
#define LAMP_THRESH_ON_HI         79U

/*___Coding Thresholds___*/
#define CODING_THRESH_FL_HI       5000U /* [mA] */
#define CODING_THRESH_FL_LO       3800U /* [mA] */
#define CODING_THRESH_FR_HI       3700U /* [mA] */
#define CODING_THRESH_FR_LO       2600U /* [mA] */
#define CODING_THRESH_RL_HI       2400U /* [mA] */
#define CODING_THRESH_RL_LO       1300U /* [mA] */
#define CODING_THRESH_RR_HI       1200U /* [mA] */
#define CODING_THRESH_RR_LO       0000U /* [mA] */

/*___Diag Constants___________________________________________________________*/
#define DIAG_USAGE_ID             0x00U
#define DIAG_ASSEMBLY_ID          0x00U




extern volatile strGlobals_t  strGlobals;
extern volatile strUID_t      strUID;
extern eCodingType_t          eCodingType;

/* === EXPORTED FUNCTIONS =================================================== */
extern void Globals_vInit( void );
extern void Globals_vMain( void );

#endif /* GLOBALS_H_ */
