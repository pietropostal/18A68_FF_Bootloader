/*******************************************************************************
** Copyright (c) 2018 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -----------------------------------------------------------------------------
** File Name    : SchM.h
** Module name  : Schedule Manager
** -----------------------------------------------------------------------------
** Description  : This module Schedules tasks periodically and file is header 
**                file for Schm.c.
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
#ifndef SCHM_H
#define SCHM_H
/**************************************** Inclusion files *********************/
#include "Platform_Types.h"
#include  "GPT.h"
#include  "CANT.h"
#include  "Wdt.h"
#include  "FLSHM.h"
/********************************* Declaration of global types ****************/

/************************** Declaration of global symbol and constants ********/

/********************************* Declaration of global macros ***************/

/*******************************************************************************
**                              FUNCTIONS                                     **
*******************************************************************************/
extern void SchM_Main(void);
extern void SchmInit(void);
extern boolean SchM_GetStatus(void);
#endif /* SCHM_H */
