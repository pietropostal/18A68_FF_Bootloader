/*******************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -----------------------------------------------------------------------------
** File Name    : SchM.h
** Module name  : Schedule Manager
** -----------------------------------------------------------------------------
** Description  : This module Schedules tasks periodically and this file is  
**                header file for Schm_Cfg.c.
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
/* To avoid multi-inclusions */
#ifndef	SCHM_CFG_H
#define	SCHM_CFG_H

/**************************************** Inclusion files *********************/
#include "SchM.h"
/************************* Declaration of local symbol and constants **********/

#define SCHM_TASKBLK2MSSIZE     (uint8)1
#define SCHM_TASKBLK3MSSIZE     (uint8)1


/* MISRA RULE 11.1 WARNING: Conversions shall not be performed between a 
pointer to a function and any other type
commented the below code used(uncomment if required)  
*/
#define SCHM_TASKBLK10000MSSIZE (uint8)1


#define SCHM_2MSTASK            (uint8)2
#define SCHM_3MSTASK            (uint8)3
#define SCHM_10000MSTASK        (uint16)10000
//#define SCHM_500MSTASK          (uint16)500

/********************************* Declaration of local types *****************/
typedef struct
{
  uint8 delay;
	void (*fptr)(void);
}SchM_SchBlkType;

/*******************************************************************************
**                              FUNCTIONS                                     **
*******************************************************************************/
/****************************** External links of global constants ************/
/* MISRA RULE 8.7 VIOLATION: could define variable at block scope
   External links of global constants are purposefully declared at this location
   to follow file structure.
*/
extern const SchM_SchBlkType SchM_icTaskBlk2ms[SCHM_TASKBLK2MSSIZE];
extern const SchM_SchBlkType SchM_icTaskBlk3ms[SCHM_TASKBLK3MSSIZE];
extern const SchM_SchBlkType SchM_icTaskBlk10000ms[SCHM_TASKBLK10000MSSIZE]; // enrico modified

#endif	/* SchM_CFG_H */
