/***************************************************************************************************
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_SA.h
**
** Description  : Include file of component ISOUDS_SA.c
**
** -------------------------------------------------------------------------------------------------
**
***************************************************************************************************/

/* To avoid multi-inclusions */
#ifndef ISOUDS_SA_H
#define ISOUDS_SA_H

/************************************* Inclusion files ********************************************/
#include "ISOUDS.h"


/************************** Declaration of global symbol and constants ****************************/
/* SID of Security Access */
#define     ISOUDS_SIDSA                (0x27)

/********************************* Declaration of global macros ***********************************/
/* ISOUDS_SAState machine states */
/* State A :- All levels locked,No Active Seed Send */
#define ISOUDS_SA_STATE_A            ((uint8)1)
/* State B :- All levels locked,Seed Send waiting for key */
#define ISOUDS_SA_STATE_B            ((uint8)2)
/* State C:- One level Unlocked ,No Active Seed */
#define ISOUDS_SA_STATE_C            ((uint8)3)
/* State D:- One level Unlocked, Seed Send for another level waiting for key */
#define ISOUDS_SA_STATE_D            ((uint8)4)

/* Session timer max value-after this time current security session will expire */
#define ISOUDS_SASESSIONTIMERMAX    (120000)/* 60 minutes for Firmware Download*/

/* maximum time waiting for key */
#define ISOUDS_SAWAITKEYMAX            (5000)/* 5s */

/* maximum time for att_cnt banning */
//#define ISOUDS_SAATTCNTMAXWAIT        (60000)/* 60s */

/* Maximum attempts count for wrong key Take 1 here */
#define ISOUDS_MAXATTEMTCOUNT        ((uint8)5)

/* Lock time Secuirty Access. */
#define ISOUDS_SALOCKPERIOD             (180000)/* 60s */

// Enrico: temp fix?
//#define ISOUDS_SAPOWERON_DELAY	        (10000)
#define ISOUDS_SAPOWERON_DELAY	        (1000)

#define SA_MANUFACTURING_MODE 0x01
//#define SA_PRODUNCTION_MODE  0x02

/********************************* Declaration of global types ************************************/

/****************************** External links of global variables ********************************/
/* Status to indicate whether ECU is unlocked or not */
extern uint8 ISOUDS_StECUUnLock;

/* Is seed Static or to be generated each time when Unlock request comes is decided by this variable */
/* ISOUDS_TRUE = Same seed everytime for same level 
   ISOUDS_FALSE = Random seed is generated every time */
extern uint8 ISOUDS_SAStatic_Seed;

/* Status to indicate which security Access level is currently there */
extern uint8 ISOUDS_SALevel;
/* Attempt counts if Exceeds limit ECU is locked for some time and
will not accept any request for unlocking */
extern uint8 ISOUDS_SAAttCnt;

/* Timers */
/* Security Access Delay timer for session.
After this time particular session will time out and ECU will lock again */
extern uint32 ISOUDS_SATimerSession;
/* Security Access Delay timer for Recevie key 
Under this time the key should be Received for send seed.otherwise it will be count as ISOUDS_FALSE attempt*/
extern uint32 ISOUDS_SATimerWaitingForKey;
/* Security Access delay timer to lock ECU if attempt count exceeds limit */
extern uint32 ISOUDS_SATimerAttCntExceeded;

/* Requested Current Security levels */
extern uint8 ISOUDS_SACurrentRequestedLevel;


/* To start stop the timers */
extern uint32 ISOUDS_SATimerSessionRunning;
extern uint32 ISOUDS_SATimerWaitingForKeyRunning;
extern uint32 ISOUDS_SATimerAttCntExceededRunning;

/* Variable to Check ISOUDS Session change */
extern uint8 ISOUDS_OldSess;
/****************************** External links of global constants ********************************/

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/********************************** Function definitions ******************************************/
extern void ISOUDS_SAInit (uint8 bootFlag);
extern void ISOUDS_SA (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[]);
extern uint8 ISOUDS_GetSASt (void);
extern void ISOUDS_SAChkTimer (void);
extern void ISOUDS_SAReset (void);
extern uint8 ISOUDS_GetSAStLevel (uint8 SALevel);

#endif  /* ISOUDS_SA_H */
