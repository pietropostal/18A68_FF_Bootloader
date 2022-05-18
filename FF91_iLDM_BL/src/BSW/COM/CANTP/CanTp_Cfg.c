/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name : CanTp_cfg.c
** Module Name : CanTp
** -------------------------------------------------------------------------------------------------
**
** Description : Configuration file of component CanTp.c
** This file must exclusively contain informations needed to
** use this component.
**
** -------------------------------------------------------------------------------------------------
**
** Documentation reference : EME-17ST013-12070.01 (SWLLD CanTp)
**
****************************************************************************************************
** R E V I S I O N H I S T O R Y
****************************************************************************************************
** V01.00 13/07/2019
** - Baseline Created
**
***************************************************************************************************/
/**************************************** Inclusion files *****************************************/
#include "CanTp.h"

/********************** Declaration of local symbol and constants *********************************/
/****************************** Declaration of exported variables *********************************/
/****************************** Declaration of exported constants *********************************/
/********************************* Declaration of local macros ************************************/
/********************************* Declaration of local types *************************************/
/******************************* Declaration of local variables ***********************************/
/******************************* Declaration of local constants ***********************************/

/* ISO15765 timeout configuration */
CONST(ISOTP_TimeoutT, CanSrv_VAR) ISOTP_iTimeOut[ISOTP_TIMEOUT_TAB] =
{
     /* Transmission timeout values */
    {
        (uint32)ISOTP_NAS_TIMEOUT_MS,       /* N_As timeout in ms */
        (uint32)ISOTP_NBS_TIMEOUT_MS,       /* N_Bs timeout in ms */
        (uint32)ISOTP_NCS_TIMEOUT_MS        /* N_Cs timeout in ms */
    },
    /* Reception timeout values */
    {
        (uint32)ISOTP_NAR_TIMEOUT_MS,       /* N_Ar timeout in ms */
        (uint32)ISOTP_NBR_TIMEOUT_MS,       /* N_Br timeout in ms */
        (uint32)ISOTP_NCR_TIMEOUT_MS        /* N_Cr timeout in ms */
    }
};

