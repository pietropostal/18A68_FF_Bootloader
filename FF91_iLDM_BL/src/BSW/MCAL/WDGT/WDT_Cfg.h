/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name     : WDT.Cfg.h
** Module Name   : WDT
** -------------------------------------------------------------------------------------------------
**
** Description : Watchdog Target
**
** -------------------------------------------------------------------------------------------------
**
** Documentation reference :
**
****************************************************************************************************
** R E V I S I O N H I S T O R Y
****************************************************************************************************
** V01.00 10/08/2018
** - Baseline Created
** -------------------------------------------------------------------------------------------------
***************************************************************************************************/
/* To avoid multi-inclusions */
#ifndef WDT_CFG_H_
#define WDT_CFG_H_
/********************************** Declaration of global macros **********************************/
#define WDT_TIMEOUT_VAL_MS				500U

#define WDT_CLK_FROM_LPO_FREQ			128000U

#define WDT_SCALING_HZ					1000U

/*Formula to for WDT timeout*/
#define WDT_CFG_TIMEOUT					((WDT_CLK_FROM_LPO_FREQ/WDT_SCALING_HZ) * WDT_TIMEOUT_VAL_MS)

#endif /* WDT_CFG_H_ */
