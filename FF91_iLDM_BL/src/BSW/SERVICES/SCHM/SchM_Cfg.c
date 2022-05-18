/*******************************************************************************
** Copyright (c) 2018 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -----------------------------------------------------------------------------
** File Name    : SchM_Cfg.c
** Module name  : Schedule Manager
** -----------------------------------------------------------------------------
** Description  : This module Schedules tasks periodically and file is used to
**                configure the tasks, that needs to be scheduled.
**
** -----------------------------------------------------------------------------
**
** Documentation reference : 
**
********************************************************************************
** R E V I S I O N  H I S T O R Y
********************************************************************************
** V01.00
** - Baseline for SCHEDULER module
*******************************************************************************/

/**************************************** Inclusion files *********************/
#include "SchM_Cfg.h"
#include "CanTp.h"
#include "ISOUDS.h"
#include "FLSHM.h"
#include "CANT_Cfg.h"
#include "ADC0.h"
#include "ProjectCfg.h"

//uint32 ID = CANT_TX_ID;
uint8 Buffer[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
uint32 Reset;

/******************************* Declaration of local constants ***************/
/******************** Functions declarations **********************************/
void Task1(void);
void Task2(void);
void Task3(void);
void Task4(void);
void Task10000ms(void);
/****************************  Variable declarations **************************/

#ifdef SCHM_TASKBLK2MSSIZE
const SchM_SchBlkType SchM_icTaskBlk2ms[SCHM_TASKBLK2MSSIZE] =
{
  {(uint8)0,     &Task1},
};
#endif

#ifdef SCHM_TASKBLK3MSSIZE
const SchM_SchBlkType SchM_icTaskBlk3ms[SCHM_TASKBLK3MSSIZE] =
{
		 {(uint8)0,     &Task2},
};
#endif

#ifdef SCHM_TASKBLK10000MSSIZE
const SchM_SchBlkType SchM_icTaskBlk10000ms[SCHM_TASKBLK10000MSSIZE] =
{
  {(uint8)0,      &Task10000ms}
};
#endif

extern void Coding_Startup(void);
extern uint8 Coding_StartupFinished;

/*  To be filled with Application code */
void Task1(void) 
{
	ADC0_vMain();
	Coding_Startup();

	// Enrico added if
	if( Coding_StartupFinished )
	{
		FLSHM_AppValdnStateMnger();
	}
}


void Task2(void) 
{
	// Enrico added if
	if( Coding_StartupFinished )
	{
		CANT_MainLoop();
		ISOTP_Main();
		FLSHM_FblTask();
		ISOUDS_Main();
	}
}

void Task10000ms(void)
{
	if( Coding_StartupFinished )
	{
		CANIF_VERSION_MESSAGE_TRANSMIT();
	}
}

