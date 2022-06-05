/***************************************************************************************************
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_RtnCfg.c
**
** Description  : Routine Control Service configuration
**
** -------------------------------------------------------------------------------------------------
**
***************************************************************************************************/

/**************************************** Inclusion files *****************************************/
#include "ISOUDS_RtnCfg.h"

/********************************* Declaration of local macros ************************************/

/********************************* Declaration of local types *************************************/

/******************************* Declaration of local variables ***********************************/

/******************************* Declaration of local constants ***********************************/

/****************************** Declaration of exported variables *********************************/

/****************************** Declaration of exported constants *********************************/

const ISOUDS_RtnIdType ISOUDS_RtnConfTab[ISOUDS_RTNCONFTABSIZE] =
{
    {
        (uint16)ISOUDS_RTNID_ERASE,
        &ISOUDS_EraseFlash,
		ISOUDS_DIDSS_F_T_F_F,
        ISOUDS_TRUE
    },
    {
        (uint16)ISOUDS_RTNID_CHECKMEMORY,
        &ISOUDS_CheckMemory,
		ISOUDS_DIDSS_F_T_F_F,
        ISOUDS_TRUE
    },

    {
        (uint16)ISOUDS_RTNID_VALIDATION,
        &ISOUDS_CheckAppValidation,
        ISOUDS_DIDSS_F_T_F_F,
        ISOUDS_TRUE
    },
    
    {
        (uint16)ISOUDS_RTNID_AUTHORIZATION,
        &ISOUDS_CheckAppAuthorization,
        ISOUDS_DIDSS_F_T_F_F,
        ISOUDS_TRUE
    },
	{
	    (uint16)ISOUDS_RTNID_ECUMODE,
	    &ISOUDS_CheckECUMode,
	    ISOUDS_DIDSS_F_T_F_F,
	    ISOUDS_TRUE
	}
};

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/
/******************************** Function definitions ********************************************/

/**************************** Internal functions declarations *************************************/
