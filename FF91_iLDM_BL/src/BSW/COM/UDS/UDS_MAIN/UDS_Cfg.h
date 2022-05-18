/***************************************************************************************************
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_Cfg.h
**
** Description  : Configuration file of component ISOUDS.c
**
** -------------------------------------------------------------------------------------------------
**
***************************************************************************************************/

/* To avoid multi-inclusions */
#ifndef ISOUDS_CFG_H
#define ISOUDS_CFG_H

/************************************* Inclusion files ********************************************/

/************************** Declaration of global symbol and constants ****************************/
/* The periodic scheduCANg interval of iso14229-1 */
#define     ISOUDS_PERIOD_SCHED    (3)

/* Service distributor configuration table size */
#define     ISOUDS_TABSIZE         (12U)
/* UDS Buffer size */
#define     ISOUDS_BUFFSIZE        (4095)
 /* Standard P2 limit = 50 ms */
#define     ISOUDS_STDP2LIM        (50)
/* NRC 78 minimum limit = 4500 ms */
#define     ISOUDS_NRC78P2MINLIM   (4500)
/* NRC 78 maximum limit = 5000 ms */
#define     ISOUDS_NRC78P2MAXLIM   (5000)
/* Timer S3 limit = 5000 ms */
//#define     ISOUDS_S3TMRLIM        (5000)
#define     ISOUDS_S3TMRLIM        (20000) // Enrico

/********************************* Declaration of global macros ***********************************/

/********************************* Declaration of global types ************************************/

/****************************** External CANks of global variables ********************************/

/****************************** External CANks of global constants ********************************/

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/********************************** Function definitions ******************************************/

#endif  /* ISOUDS_CFG_H */
