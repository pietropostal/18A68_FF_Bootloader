/*******************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL.
**
** -----------------------------------------------------------------------------
** File Name   : SchM.c
** Module Name : Schedule Manager
** -----------------------------------------------------------------------------
**
** Description : This module Schedules tasks periodically and file contains 
**                the code for schedule management of Task.
**
** -----------------------------------------------------------------------------
**
** Documentation reference : 
**
********************************************************************************
** R E V I S I O N H I S T O R Y
********************************************************************************
** V01.00
** - Baseline for SCHEDULER module
*******************************************************************************/

/**************************************** Inclusion files *********************/
#include "SchM_Cfg.h"
#include "FLSHM.h"
#include "UJA1075A.h"

/****************************** Declaration of exported variables *************/
static boolean SchM_OverLd;
/****************************** Declaration of exported constants *************/
/**************************** Internal functions declarations *****************/
/*******************************************************************************
**                                      FUNCTIONS                             **
*******************************************************************************/

/******************************** Function definitions ************************/

/*******************************************************************************
** Function                 : SchMInit

** Description              : Initializes module parameters

** Parameter                : None

** Return value             : None
*******************************************************************************/
void SchmInit(void)
{
    /* reset overload flag*/
    SchM_OverLd = (boolean)FALSE;
}

/*******************************************************************************
** Function                 : SchM_Main

** Description              : Schedules tasks

** Parameter                : None

** Return value             : None
*******************************************************************************/

void SchM_Main(void)
{
    uint16 idxTaskBlk;
    uint32 currDly;
    uint32 timer1;
    uint32 timer2;
    boolean schm1msTrig;

    while (1)
    {
        /* MISRA does not permit direct read of volatile variable */
        schm1msTrig = GPT_Get1msTrig();
		
        if (schm1msTrig == (boolean)TRUE)
        {

        	// Call SBC
        	if (TRUE == SBC_InitStat)
        	{
        		/*SBC Driver Main function */
        		UJA1075A_vMain();
        	}


            /* get the current time */
            timer1 = GPT_Get1ms();

            /* reset trigger flag */
            GPT_Reset1msTrig();
            
           #ifdef SCHM_TASKBLK2MSSIZE
           /* invoke 2ms task */
           /* current delay for 2ms period */
           currDly = (uint32)(timer1 % SCHM_2MSTASK);
           for(idxTaskBlk = (uint16)0; idxTaskBlk < SCHM_TASKBLK2MSSIZE;
                                                                  idxTaskBlk++)
           {
               if(currDly == SchM_icTaskBlk2ms[idxTaskBlk].delay)
               {
                   (*(SchM_icTaskBlk2ms[idxTaskBlk].fptr))();
               }
           }
           #endif

          #ifdef SCHM_TASKBLK3MSSIZE
           /* invoke 3ms task */
           /* current delay for 3ms period */
           currDly = (uint32)(timer1 % SCHM_3MSTASK);
           for(idxTaskBlk = (uint16)0; idxTaskBlk < SCHM_TASKBLK3MSSIZE;
                                                                  idxTaskBlk++)
           {
               if(currDly == SchM_icTaskBlk3ms[idxTaskBlk].delay)
               {
                   (*(SchM_icTaskBlk3ms[idxTaskBlk].fptr))();
               }
           }
           #endif
			#ifdef SCHM_TASKBLK500MSSIZE
           /* invoke 100ms task */
           /* current delay for 500ms period */
           currDly = (uint32)(timer1 % SCHM_500MSTASK);
           for(idxTaskBlk = (uint16)0; idxTaskBlk < SCHM_TASKBLK500MSSIZE;
                                                                  idxTaskBlk++)
           {
               if(currDly == SchM_icTaskBlk500ms[idxTaskBlk].delay)
               {
                   (*(SchM_icTaskBlk500ms[idxTaskBlk].fptr))();
               }
           }
           #endif

           #ifdef SCHM_TASKBLK10000MSSIZE
           /* invoke 100ms task */
           /* current delay for 10000ms period */
           currDly = (uint32)(timer1 % SCHM_10000MSTASK);
           for(idxTaskBlk = (uint16)0; idxTaskBlk < SCHM_TASKBLK10000MSSIZE;
                                                                  idxTaskBlk++)
           {
               if(currDly == SchM_icTaskBlk10000ms[idxTaskBlk].delay)
               {
                   (*(SchM_icTaskBlk10000ms[idxTaskBlk].fptr))();
               }
           }
           #endif

            timer2 = GPT_Get1ms();
            /* if execution time is more than 1ms */
            if ((timer2 - timer1) > (uint32)1)
            {
                SchM_OverLd = (boolean)TRUE;
            }          
        }
    }
}

/*******************************************************************************
** Function                 : SchM_GetStatus

** Description              : Returns the status of MCU module.

** Parameter                : None

** Return value             : None
*******************************************************************************/
boolean SchM_GetStatus(void)
{
    /* return overload flag status */
    return(SchM_OverLd);
}
