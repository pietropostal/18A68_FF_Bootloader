/** Copyright (c) 2019 EMBITEL
**
** This software is the property of Embitel.
** It can not be used or duplicated without Embitel authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : Flash.h
** Module name  : FLASH DRIVER
** -------------------------------------------------------------------------------------------------
** Description : Include file of component flash.c
**
** -------------------------------------------------------------------------------------------------
**
****************************************************************************************************
** R E V I S I O N  H I S T O R Y
****************************************************************************************************
** V01.00
** - First release
*/

#ifndef FLASH_DRIVER_H
#define FLASH_DRIVER_H

/**************************************** Inclusion files *****************************************/
#include <stdbool.h>
#include <stddef.h>
#include "device_registers.h"
#include "Flash_Cfg.h"

/*!
 * @defgroup flash_driver Flash Memory (Flash)
 * @ingroup flash
 * @details This section describes the programming interface of the Flash Peripheral Driver.
 * @{
 */

/*! @brief Status return codes.
 * Common error codes will be a unified enumeration (C enum) that will contain all error codes
 * (common and specific). There will be separate "error values spaces" (or slots), each of 256
 * positions, allocated per functionality.
 */
typedef enum
{
    /* Generic error codes */
    STATUS_SUCCESS                         = 0x000U,    /*!< Generic operation success status */
    STATUS_ERROR                           = 0x001U,    /*!< Generic operation failure status */
    STATUS_BUSY                            = 0x002U,    /*!< Generic operation busy status */
    STATUS_TIMEOUT                         = 0x003U,    /*!< Generic operation timeout status */
    STATUS_UNSUPPORTED                     = 0x004U,    /*!< Generic operation unsupported status */

    /* FLASH specific error codes */
    STATUS_FLASH_ERROR_ENABLE              = 0x901U, /*!< It's impossible to enable an operation */
    STATUS_FLASH_ERROR_NO_BLOCK            = 0x902U, /*!< No blocks have been enabled for Array Integrity check */
    STATUS_FLASH_INPROGRESS                = 0x903U, /*!< InProgress status */

} status_t;

/*******************************************************************************
 * FTFx - Register instance definitions
 *******************************************************************************/
/*******************************************************************************
 * FTFE
 *******************************************************************************/
#ifdef FTFE
#define FTFx_BASE                               FTFE_BASE
#define FTFx_FSTAT                              FTFE->FSTAT
#define FTFx_FCNFG                              FTFE->FCNFG
#define FTFx_FSEC                               FTFE->FSEC
#define FTFx_FOPT                               FTFE->FOPT
#define FTFx_FCCOB3                             FTFE->FCCOB[0]
#define FTFx_FCCOB2                             FTFE->FCCOB[1]
#define FTFx_FCCOB1                             FTFE->FCCOB[2]
#define FTFx_FCCOB0                             FTFE->FCCOB[3]
#define FTFx_FCCOB7                             FTFE->FCCOB[4]
#define FTFx_FCCOB6                             FTFE->FCCOB[5]
#define FTFx_FCCOB5                             FTFE->FCCOB[6]
#define FTFx_FCCOB4                             FTFE->FCCOB[7]
#define FTFx_FCCOBB                             FTFE->FCCOB[8]
#define FTFx_FCCOBA                             FTFE->FCCOB[9]
#define FTFx_FCCOB9                             FTFE->FCCOB[10]
#define FTFx_FCCOB8                             FTFE->FCCOB[11]
#define FTFx_FPROT3                             FTFE->FPROT[0]
#define FTFx_FPROT2                             FTFE->FPROT[1]
#define FTFx_FPROT1                             FTFE->FPROT[2]
#define FTFx_FPROT0                             FTFE->FPROT[3]
#define FTFx_FEPROT                             FTFE->FEPROT
#define FTFx_FDPROT                             FTFE->FDPROT
#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
#define FTFx_FERSTAT                            FTFE->FERSTAT
#define FTFx_FERCNFG                            FTFE->FERCNFG
#endif
/* FSTAT Bit Fields */
#define FTFx_FSTAT_MGSTAT0_MASK                 FTFE_FSTAT_MGSTAT0_MASK
#define FTFx_FSTAT_MGSTAT0_SHIFT                FTFE_FSTAT_MGSTAT0_SHIFT
#define FTFx_FSTAT_MGSTAT0_WIDTH                FTFE_FSTAT_MGSTAT0_WIDTH
#define FTFx_FSTAT_MGSTAT0(x)                   FTFE_FSTAT_MGSTAT0(x)
#define FTFx_FSTAT_FPVIOL_MASK                  FTFE_FSTAT_FPVIOL_MASK
#define FTFx_FSTAT_FPVIOL_SHIFT                 FTFE_FSTAT_FPVIOL_SHIFT
#define FTFx_FSTAT_FPVIOL_WIDTH                 FTFE_FSTAT_FPVIOL_WIDTH
#define FTFx_FSTAT_FPVIOL(x)                    FTFE_FSTAT_FPVIOL(x)
#define FTFx_FSTAT_ACCERR_MASK                  FTFE_FSTAT_ACCERR_MASK
#define FTFx_FSTAT_ACCERR_SHIFT                 FTFE_FSTAT_ACCERR_SHIFT
#define FTFx_FSTAT_ACCERR_WIDTH                 FTFE_FSTAT_ACCERR_WIDTH
#define FTFx_FSTAT_ACCERR(x)                    FTFE_FSTAT_ACCERR(x)
#define FTFx_FSTAT_RDCOLERR_MASK                FTFE_FSTAT_RDCOLERR_MASK
#define FTFx_FSTAT_RDCOLERR_SHIFT               FTFE_FSTAT_RDCOLERR_SHIFT
#define FTFx_FSTAT_RDCOLERR_WIDTH               FTFE_FSTAT_RDCOLERR_WIDTH
#define FTFx_FSTAT_RDCOLERR(x)                  FTFE_FSTAT_RDCOLERR(x)
#define FTFx_FSTAT_CCIF_MASK                    FTFE_FSTAT_CCIF_MASK
#define FTFx_FSTAT_CCIF_SHIFT                   FTFE_FSTAT_CCIF_SHIFT
#define FTFx_FSTAT_CCIF_WIDTH                   FTFE_FSTAT_CCIF_WIDTH
#define FTFx_FSTAT_CCIF(x)                      FTFE_FSTAT_CCIF(x)
/* FCNFG Bit Fields */
#define FTFx_FCNFG_EEERDY_MASK                  FTFE_FCNFG_EEERDY_MASK
#define FTFx_FCNFG_EEERDY_SHIFT                 FTFE_FCNFG_EEERDY_SHIFT
#define FTFx_FCNFG_EEERDY_WIDTH                 FTFE_FCNFG_EEERDY_WIDTH
#define FTFx_FCNFG_EEERDY(x)                    FTFE_FCNFG_EEERDY(x)
#define FTFx_FCNFG_RAMRDY_MASK                  FTFE_FCNFG_RAMRDY_MASK
#define FTFx_FCNFG_RAMRDY_SHIFT                 FTFE_FCNFG_RAMRDY_SHIFT
#define FTFx_FCNFG_RAMRDY_WIDTH                 FTFE_FCNFG_RAMRDY_WIDTH
#define FTFx_FCNFG_RAMRDY(x)                    FTFE_FCNFG_RAMRDY(x)
#define FTFx_FCNFG_PFLSH_MASK                   FTFE_FCNFG_PFLSH_MASK
#define FTFx_FCNFG_PFLSH_SHIFT                  FTFE_FCNFG_PFLSH_SHIFT
#define FTFx_FCNFG_PFLSH_WIDTH                  FTFE_FCNFG_PFLSH_WIDTH
#define FTFx_FCNFG_PFLSH(x)                     FTFE_FCNFG_PFLSH(x)
#define FTFx_FCNFG_ERSSUSP_MASK                 FTFE_FCNFG_ERSSUSP_MASK
#define FTFx_FCNFG_ERSSUSP_SHIFT                FTFE_FCNFG_ERSSUSP_SHIFT
#define FTFx_FCNFG_ERSSUSP_WIDTH                FTFE_FCNFG_ERSSUSP_WIDTH
#define FTFx_FCNFG_ERSSUSP(x)                   FTFE_FCNFG_ERSSUSP(x)
#define FTFx_FCNFG_ERSAREQ_MASK                 FTFE_FCNFG_ERSAREQ_MASK
#define FTFx_FCNFG_ERSAREQ_SHIFT                FTFE_FCNFG_ERSAREQ_SHIFT
#define FTFx_FCNFG_ERSAREQ_WIDTH                FTFE_FCNFG_ERSAREQ_WIDTH
#define FTFx_FCNFG_ERSAREQ(x)                   FTFE_FCNFG_ERSAREQ(x)
#define FTFx_FCNFG_RDCOLLIE_MASK                FTFE_FCNFG_RDCOLLIE_MASK
#define FTFx_FCNFG_RDCOLLIE_SHIFT               FTFE_FCNFG_RDCOLLIE_SHIFT
#define FTFx_FCNFG_RDCOLLIE_WIDTH               FTFE_FCNFG_RDCOLLIE_WIDTH
#define FTFx_FCNFG_RDCOLLIE(x)                  FTFE_FCNFG_RDCOLLIE(x)
#define FTFx_FCNFG_CCIE_MASK                    FTFE_FCNFG_CCIE_MASK
#define FTFx_FCNFG_CCIE_SHIFT                   FTFE_FCNFG_CCIE_SHIFT
#define FTFx_FCNFG_CCIE_WIDTH                   FTFE_FCNFG_CCIE_WIDTH
#define FTFx_FCNFG_CCIE(x)                      FTFE_FCNFG_CCIE(x)
/* FSEC Bit Fields */
#define FTFx_FSEC_SEC_MASK                      FTFE_FSEC_SEC_MASK
#define FTFx_FSEC_SEC_SHIFT                     FTFE_FSEC_SEC_SHIFT
#define FTFx_FSEC_SEC_WIDTH                     FTFE_FSEC_SEC_WIDTH
#define FTFx_FSEC_SEC(x)                        FTFE_FSEC_SEC(x)
#define FTFx_FSEC_FSLACC_MASK                   FTFE_FSEC_FSLACC_MASK
#define FTFx_FSEC_FSLACC_SHIFT                  FTFE_FSEC_FSLACC_SHIFT
#define FTFx_FSEC_FSLACC_WIDTH                  FTFE_FSEC_FSLACC_WIDTH
#define FTFx_FSEC_FSLACC(x)                     FTFE_FSEC_FSLACC(x)
#define FTFx_FSEC_MEEN_MASK                     FTFE_FSEC_MEEN_MASK
#define FTFx_FSEC_MEEN_SHIFT                    FTFE_FSEC_MEEN_SHIFT
#define FTFx_FSEC_MEEN_WIDTH                    FTFE_FSEC_MEEN_WIDTH
#define FTFx_FSEC_MEEN(x)                       FTFE_FSEC_MEEN(x)
#define FTFx_FSEC_KEYEN_MASK                    FTFE_FSEC_KEYEN_MASK
#define FTFx_FSEC_KEYEN_SHIFT                   FTFE_FSEC_KEYEN_SHIFT
#define FTFx_FSEC_KEYEN_WIDTH                   FTFE_FSEC_KEYEN_WIDTH
#define FTFx_FSEC_KEYEN(x)                      FTFE_FSEC_KEYEN(x)
/* FOPT Bit Fields */
#define FTFx_FOPT_OPT_MASK                      FTFE_FOPT_OPT_MASK
#define FTFx_FOPT_OPT_SHIFT                     FTFE_FOPT_OPT_SHIFT
#define FTFx_FOPT_OPT_WIDTH                     FTFE_FOPT_OPT_WIDTH
#define FTFx_FOPT_OPT(x)                        FTFE_FOPT_OPT(x)
/* FCCOB Bit Fields */
#define FTFx_FCCOB_CCOBn_MASK                   FTFE_FCCOB_CCOBn_MASK
#define FTFx_FCCOB_CCOBn_SHIFT                  FTFE_FCCOB_CCOBn_SHIFT
#define FTFx_FCCOB_CCOBn_WIDTH                  FTFE_FCCOB_CCOBn_WIDTH
#define FTFx_FCCOB_CCOBn(x)                     FTFE_FCCOB_CCOBn(x)
/* FPROT Bit Fields */
#define FTFx_FPROT_PROT_MASK                    FTFE_FPROT_PROT_MASK
#define FTFx_FPROT_PROT_SHIFT                   FTFE_FPROT_PROT_SHIFT
#define FTFx_FPROT_PROT_WIDTH                   FTFE_FPROT_PROT_WIDTH
#define FTFx_FPROT_PROT(x)                      FTFE_FPROT_PROT(x)
/* FEPROT Bit Fields */
#define FTFx_FEPROT_EPROT_MASK                  FTFE_FEPROT_EPROT_MASK
#define FTFx_FEPROT_EPROT_SHIFT                 FTFE_FEPROT_EPROT_SHIFT
#define FTFx_FEPROT_EPROT_WIDTH                 FTFE_FEPROT_EPROT_WIDTH
#define FTFx_FEPROT_EPROT(x)                    FTFE_FEPROT_EPROT(x)
/* FDPROT Bit Fields */
#define FTFx_FDPROT_DPROT_MASK                  FTFE_FDPROT_DPROT_MASK
#define FTFx_FDPROT_DPROT_SHIFT                 FTFE_FDPROT_DPROT_SHIFT
#define FTFx_FDPROT_DPROT_WIDTH                 FTFE_FDPROT_DPROT_WIDTH
#define FTFx_FDPROT_DPROT(x)                    FTFE_FDPROT_DPROT(x)
#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
/* FERSTAT Bit Fields */
#define FTFx_FERSTAT_DFDIF_MASK                 FTFE_FERSTAT_DFDIF_MASK
#define FTFx_FERSTAT_DFDIF_SHIFT                FTFE_FERSTAT_DFDIF_SHIFT
#define FTFx_FERSTAT_DFDIF_WIDTH                FTFE_FERSTAT_DFDIF_WIDTH
#define FTFx_FERSTAT_DFDIF(x)                   FTFE_FERSTAT_DFDIF(x)
/* FERCNFG Bit Fields */
#define FTFx_FERCNFG_DFDIE_MASK                 FTFE_FERCNFG_DFDIE_MASK
#define FTFx_FERCNFG_DFDIE_SHIFT                FTFE_FERCNFG_DFDIE_SHIFT
#define FTFx_FERCNFG_DFDIE_WIDTH                FTFE_FERCNFG_DFDIE_WIDTH
#define FTFx_FERCNFG_DFDIE(x)                   FTFE_FERCNFG_DFDIE(x)
#define FTFx_FERCNFG_FDFD_MASK                  FTFE_FERCNFG_FDFD_MASK
#define FTFx_FERCNFG_FDFD_SHIFT                 FTFE_FERCNFG_FDFD_SHIFT
#define FTFx_FERCNFG_FDFD_WIDTH                 FTFE_FERCNFG_FDFD_WIDTH
#define FTFx_FERCNFG_FDFD(x)                    FTFE_FERCNFG_FDFD(x)
#endif
/*******************************************************************************
 * FTFC
 *******************************************************************************/
#elif defined(FTFC)
#define FTFx_BASE                               FTFC_BASE
#define FTFx_FSTAT                              FTFC->FSTAT
#define FTFx_FCNFG                              FTFC->FCNFG
#define FTFx_FSEC                               FTFC->FSEC
#define FTFx_FOPT                               FTFC->FOPT
#define FTFx_FCCOB3                             FTFC->FCCOB[0]
#define FTFx_FCCOB2                             FTFC->FCCOB[1]
#define FTFx_FCCOB1                             FTFC->FCCOB[2]
#define FTFx_FCCOB0                             FTFC->FCCOB[3]
#define FTFx_FCCOB7                             FTFC->FCCOB[4]
#define FTFx_FCCOB6                             FTFC->FCCOB[5]
#define FTFx_FCCOB5                             FTFC->FCCOB[6]
#define FTFx_FCCOB4                             FTFC->FCCOB[7]
#define FTFx_FCCOBB                             FTFC->FCCOB[8]
#define FTFx_FCCOBA                             FTFC->FCCOB[9]
#define FTFx_FCCOB9                             FTFC->FCCOB[10]
#define FTFx_FCCOB8                             FTFC->FCCOB[11]
#define FTFx_FPROT3                             FTFC->FPROT[0]
#define FTFx_FPROT2                             FTFC->FPROT[1]
#define FTFx_FPROT1                             FTFC->FPROT[2]
#define FTFx_FPROT0                             FTFC->FPROT[3]
#define FTFx_FEPROT                             FTFC->FEPROT
#define FTFx_FDPROT                             FTFC->FDPROT
#define FTFx_FCSESTAT                           FTFC->FCSESTAT
#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
#define FTFx_FERSTAT                            FTFC->FERSTAT
#define FTFx_FERCNFG                            FTFC->FERCNFG
#endif
/* FSTAT Bit Fields */
#define FTFx_FSTAT_MGSTAT0_MASK                 FTFC_FSTAT_MGSTAT0_MASK
#define FTFx_FSTAT_MGSTAT0_SHIFT                FTFC_FSTAT_MGSTAT0_SHIFT
#define FTFx_FSTAT_MGSTAT0_WIDTH                FTFC_FSTAT_MGSTAT0_WIDTH
#define FTFx_FSTAT_MGSTAT0(x)                   FTFC_FSTAT_MGSTAT0(x)
#define FTFx_FSTAT_FPVIOL_MASK                  FTFC_FSTAT_FPVIOL_MASK
#define FTFx_FSTAT_FPVIOL_SHIFT                 FTFC_FSTAT_FPVIOL_SHIFT
#define FTFx_FSTAT_FPVIOL_WIDTH                 FTFC_FSTAT_FPVIOL_WIDTH
#define FTFx_FSTAT_FPVIOL(x)                    FTFC_FSTAT_FPVIOL(x)
#define FTFx_FSTAT_ACCERR_MASK                  FTFC_FSTAT_ACCERR_MASK
#define FTFx_FSTAT_ACCERR_SHIFT                 FTFC_FSTAT_ACCERR_SHIFT
#define FTFx_FSTAT_ACCERR_WIDTH                 FTFC_FSTAT_ACCERR_WIDTH
#define FTFx_FSTAT_ACCERR(x)                    FTFC_FSTAT_ACCERR(x)
#define FTFx_FSTAT_RDCOLERR_MASK                FTFC_FSTAT_RDCOLERR_MASK
#define FTFx_FSTAT_RDCOLERR_SHIFT               FTFC_FSTAT_RDCOLERR_SHIFT
#define FTFx_FSTAT_RDCOLERR_WIDTH               FTFC_FSTAT_RDCOLERR_WIDTH
#define FTFx_FSTAT_RDCOLERR(x)                  FTFC_FSTAT_RDCOLERR(x)
#define FTFx_FSTAT_CCIF_MASK                    FTFC_FSTAT_CCIF_MASK
#define FTFx_FSTAT_CCIF_SHIFT                   FTFC_FSTAT_CCIF_SHIFT
#define FTFx_FSTAT_CCIF_WIDTH                   FTFC_FSTAT_CCIF_WIDTH
#define FTFx_FSTAT_CCIF(x)                      FTFC_FSTAT_CCIF(x)
/* FCNFG Bit Fields */
#define FTFx_FCNFG_EEERDY_MASK                  FTFC_FCNFG_EEERDY_MASK
#define FTFx_FCNFG_EEERDY_SHIFT                 FTFC_FCNFG_EEERDY_SHIFT
#define FTFx_FCNFG_EEERDY_WIDTH                 FTFC_FCNFG_EEERDY_WIDTH
#define FTFx_FCNFG_EEERDY(x)                    FTFC_FCNFG_EEERDY(x)
#define FTFx_FCNFG_RAMRDY_MASK                  FTFC_FCNFG_RAMRDY_MASK
#define FTFx_FCNFG_RAMRDY_SHIFT                 FTFC_FCNFG_RAMRDY_SHIFT
#define FTFx_FCNFG_RAMRDY_WIDTH                 FTFC_FCNFG_RAMRDY_WIDTH
#define FTFx_FCNFG_RAMRDY(x)                    FTFC_FCNFG_RAMRDY(x)
#define FTFx_FCNFG_ERSSUSP_MASK                 FTFC_FCNFG_ERSSUSP_MASK
#define FTFx_FCNFG_ERSSUSP_SHIFT                FTFC_FCNFG_ERSSUSP_SHIFT
#define FTFx_FCNFG_ERSSUSP_WIDTH                FTFC_FCNFG_ERSSUSP_WIDTH
#define FTFx_FCNFG_ERSSUSP(x)                   FTFC_FCNFG_ERSSUSP(x)
#define FTFx_FCNFG_ERSAREQ_MASK                 FTFC_FCNFG_ERSAREQ_MASK
#define FTFx_FCNFG_ERSAREQ_SHIFT                FTFC_FCNFG_ERSAREQ_SHIFT
#define FTFx_FCNFG_ERSAREQ_WIDTH                FTFC_FCNFG_ERSAREQ_WIDTH
#define FTFx_FCNFG_ERSAREQ(x)                   FTFC_FCNFG_ERSAREQ(x)
#define FTFx_FCNFG_RDCOLLIE_MASK                FTFC_FCNFG_RDCOLLIE_MASK
#define FTFx_FCNFG_RDCOLLIE_SHIFT               FTFC_FCNFG_RDCOLLIE_SHIFT
#define FTFx_FCNFG_RDCOLLIE_WIDTH               FTFC_FCNFG_RDCOLLIE_WIDTH
#define FTFx_FCNFG_RDCOLLIE(x)                  FTFC_FCNFG_RDCOLLIE(x)
#define FTFx_FCNFG_CCIE_MASK                    FTFC_FCNFG_CCIE_MASK
#define FTFx_FCNFG_CCIE_SHIFT                   FTFC_FCNFG_CCIE_SHIFT
#define FTFx_FCNFG_CCIE_WIDTH                   FTFC_FCNFG_CCIE_WIDTH
#define FTFx_FCNFG_CCIE(x)                      FTFC_FCNFG_CCIE(x)
/* FSEC Bit Fields */
#define FTFx_FSEC_SEC_MASK                      FTFC_FSEC_SEC_MASK
#define FTFx_FSEC_SEC_SHIFT                     FTFC_FSEC_SEC_SHIFT
#define FTFx_FSEC_SEC_WIDTH                     FTFC_FSEC_SEC_WIDTH
#define FTFx_FSEC_SEC(x)                        FTFC_FSEC_SEC(x)
#define FTFx_FSEC_FSLACC_MASK                   FTFC_FSEC_FSLACC_MASK
#define FTFx_FSEC_FSLACC_SHIFT                  FTFC_FSEC_FSLACC_SHIFT
#define FTFx_FSEC_FSLACC_WIDTH                  FTFC_FSEC_FSLACC_WIDTH
#define FTFx_FSEC_FSLACC(x)                     FTFC_FSEC_FSLACC(x)
#define FTFx_FSEC_MEEN_MASK                     FTFC_FSEC_MEEN_MASK
#define FTFx_FSEC_MEEN_SHIFT                    FTFC_FSEC_MEEN_SHIFT
#define FTFx_FSEC_MEEN_WIDTH                    FTFC_FSEC_MEEN_WIDTH
#define FTFx_FSEC_MEEN(x)                       FTFC_FSEC_MEEN(x)
#define FTFx_FSEC_KEYEN_MASK                    FTFC_FSEC_KEYEN_MASK
#define FTFx_FSEC_KEYEN_SHIFT                   FTFC_FSEC_KEYEN_SHIFT
#define FTFx_FSEC_KEYEN_WIDTH                   FTFC_FSEC_KEYEN_WIDTH
#define FTFx_FSEC_KEYEN(x)                      FTFC_FSEC_KEYEN(x)
/* FOPT Bit Fields */
#define FTFx_FOPT_OPT_MASK                      FTFC_FOPT_OPT_MASK
#define FTFx_FOPT_OPT_SHIFT                     FTFC_FOPT_OPT_SHIFT
#define FTFx_FOPT_OPT_WIDTH                     FTFC_FOPT_OPT_WIDTH
#define FTFx_FOPT_OPT(x)                        FTFC_FOPT_OPT(x)
/* FCCOB Bit Fields */
#define FTFx_FCCOB_CCOBn_MASK                   FTFC_FCCOB_CCOBn_MASK
#define FTFx_FCCOB_CCOBn_SHIFT                  FTFC_FCCOB_CCOBn_SHIFT
#define FTFx_FCCOB_CCOBn_WIDTH                  FTFC_FCCOB_CCOBn_WIDTH
#define FTFx_FCCOB_CCOBn(x)                     FTFC_FCCOB_CCOBn(x)
/* FPROT Bit Fields */
#define FTFx_FPROT_PROT_MASK                    FTFC_FPROT_PROT_MASK
#define FTFx_FPROT_PROT_SHIFT                   FTFC_FPROT_PROT_SHIFT
#define FTFx_FPROT_PROT_WIDTH                   FTFC_FPROT_PROT_WIDTH
#define FTFx_FPROT_PROT(x)                      FTFC_FPROT_PROT(x)
/* FEPROT Bit Fields */
#define FTFx_FEPROT_EPROT_MASK                  FTFC_FEPROT_EPROT_MASK
#define FTFx_FEPROT_EPROT_SHIFT                 FTFC_FEPROT_EPROT_SHIFT
#define FTFx_FEPROT_EPROT_WIDTH                 FTFC_FEPROT_EPROT_WIDTH
#define FTFx_FEPROT_EPROT(x)                    FTFC_FEPROT_EPROT(x)
/* FDPROT Bit Fields */
#define FTFx_FDPROT_DPROT_MASK                  FTFC_FDPROT_DPROT_MASK
#define FTFx_FDPROT_DPROT_SHIFT                 FTFC_FDPROT_DPROT_SHIFT
#define FTFx_FDPROT_DPROT_WIDTH                 FTFC_FDPROT_DPROT_WIDTH
#define FTFx_FDPROT_DPROT(x)                    FTFC_FDPROT_DPROT(x)
/* FCSESTAT Bit Fields */
#define FTFx_FCSESTAT_IDB_MASK                  FTFC_FCSESTAT_IDB_MASK
#define FTFx_FCSESTAT_IDB_SHIFT                 FTFC_FCSESTAT_IDB_SHIFT
#define FTFx_FCSESTAT_IDB_WIDTH                 FTFC_FCSESTAT_IDB_WIDTH
#define FTFx_FCSESTAT_IDB(x)                    FTFC_FCSESTAT_IDB(x)
#define FTFx_FCSESTAT_EDB_MASK                  FTFC_FCSESTAT_EDB_MASK
#define FTFx_FCSESTAT_EDB_SHIFT                 FTFC_FCSESTAT_EDB_SHIFT
#define FTFx_FCSESTAT_EDB_WIDTH                 FTFC_FCSESTAT_EDB_WIDTH
#define FTFx_FCSESTAT_EDB(x)                    FTFC_FCSESTAT_EDB(x)
#define FTFx_FCSESTAT_RIN_MASK                  FTFC_FCSESTAT_RIN_MASK
#define FTFx_FCSESTAT_RIN_SHIFT                 FTFC_FCSESTAT_RIN_SHIFT
#define FTFx_FCSESTAT_RIN_WIDTH                 FTFC_FCSESTAT_RIN_WIDTH
#define FTFx_FCSESTAT_RIN(x)                    FTFC_FCSESTAT_RIN(x)
#define FTFx_FCSESTAT_BOK_MASK                  FTFC_FCSESTAT_BOK_MASK
#define FTFx_FCSESTAT_BOK_SHIFT                 FTFC_FCSESTAT_BOK_SHIFT
#define FTFx_FCSESTAT_BOK_WIDTH                 FTFC_FCSESTAT_BOK_WIDTH
#define FTFx_FCSESTAT_BOK(x)                    FTFC_FCSESTAT_BOK(x)
#define FTFx_FCSESTAT_BFN_MASK                  FTFC_FCSESTAT_BFN_MASK
#define FTFx_FCSESTAT_BFN_SHIFT                 FTFC_FCSESTAT_BFN_SHIFT
#define FTFx_FCSESTAT_BFN_WIDTH                 FTFC_FCSESTAT_BFN_WIDTH
#define FTFx_FCSESTAT_BFN(x)                    FTFC_FCSESTAT_BFN(x)
#define FTFx_FCSESTAT_BIN_MASK                  FTFC_FCSESTAT_BIN_MASK
#define FTFx_FCSESTAT_BIN_SHIFT                 FTFC_FCSESTAT_BIN_SHIFT
#define FTFx_FCSESTAT_BIN_WIDTH                 FTFC_FCSESTAT_BIN_WIDTH
#define FTFx_FCSESTAT_BIN(x)                    FTFC_FCSESTAT_BIN(x)
#define FTFx_FCSESTAT_SB_MASK                   FTFC_FCSESTAT_SB_MASK
#define FTFx_FCSESTAT_SB_SHIFT                  FTFC_FCSESTAT_SB_SHIFT
#define FTFx_FCSESTAT_SB_WIDTH                  FTFC_FCSESTAT_SB_WIDTH
#define FTFx_FCSESTAT_SB(x)                     FTFC_FCSESTAT_SB(x)
#define FTFx_FCSESTAT_BSY_MASK                  FTFC_FCSESTAT_BSY_MASK
#define FTFx_FCSESTAT_BSY_SHIFT                 FTFC_FCSESTAT_BSY_SHIFT
#define FTFx_FCSESTAT_BSY_WIDTH                 FTFC_FCSESTAT_BSY_WIDTH
#define FTFx_FCSESTAT_BSY(x)                    FTFC_FCSESTAT_BSY(x)
#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
/* FERSTAT Bit Fields */
#define FTFx_FERSTAT_DFDIF_MASK                 FTFC_FERSTAT_DFDIF_MASK
#define FTFx_FERSTAT_DFDIF_SHIFT                FTFC_FERSTAT_DFDIF_SHIFT
#define FTFxFERSTAT_DFDIF_WIDTH                 FTFC_FERSTAT_DFDIF_WIDTH
#define FTFx_FERSTAT_DFDIF(x)                   FTFC_FERSTAT_DFDIF(x)
/* FERCNFG Bit Fields */
#define FTFx_FERCNFG_DFDIE_MASK                 FTFC_FERCNFG_DFDIE_MASK
#define FTFx_FERCNFG_DFDIE_SHIFT                FTFC_FERCNFG_DFDIE_SHIFT
#define FTFx_FERCNFG_DFDIE_WIDTH                FTFC_FERCNFG_DFDIE_WIDTH
#define FTFx_FERCNFG_DFDIE(x)                   FTFC_FERCNFG_DFDIE(x)
#define FTFx_FERCNFG_FDFD_MASK                  FTFC_FERCNFG_FDFD_MASK
#define FTFx_FERCNFG_FDFD_SHIFT                 FTFC_FERCNFG_FDFD_SHIFT
#define FTFx_FERCNFG_FDFD_WIDTH                 FTFC_FERCNFG_FDFD_WIDTH
#define FTFx_FERCNFG_FDFD(x)                    FTFC_FERCNFG_FDFD(x)
#endif

#else  /* ifndef FTFE */
#endif /* ifdef FTFE */


#define CLEAR_FTFx_FSTAT_ERROR_BITS FTFx_FSTAT = (uint8_t)(FTFx_FSTAT_FPVIOL_MASK | FTFx_FSTAT_ACCERR_MASK | FTFx_FSTAT_RDCOLERR_MASK)

/* Word size 2 bytes */
#define FTFx_WORD_SIZE     0x0002U
/* Long word size 4 bytes */
#define FTFx_LONGWORD_SIZE 0x0004U
/* Phrase size 8 bytes */
#define FTFx_PHRASE_SIZE   0x0008U
/* Double-phrase size 16 bytes */
#define FTFx_DPHRASE_SIZE  0x0010U

/* FCCOB offset address to store resource code */
#if (FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE == FTFx_PHRASE_SIZE)
#define FTFx_RSRC_CODE_REG FTFx_FCCOB4
#else
#define FTFx_RSRC_CODE_REG FTFx_FCCOB8
#endif

/*******************************************************************************
* Flash hardware algorithm operation commands
*******************************************************************************/
#define FTFx_VERIFY_BLOCK             0x00U
#define FTFx_VERIFY_SECTION           0x01U
#define FTFx_PROGRAM_CHECK            0x02U
#define FTFx_READ_RESOURCE            0x03U
#define FTFx_PROGRAM_LONGWORD         0x06U
#define FTFx_PROGRAM_PHRASE           0x07U
#define FTFx_ERASE_BLOCK              0x08U
#define FTFx_ERASE_SECTOR             0x09U
#define FTFx_PROGRAM_SECTION          0x0BU
#define FTFx_VERIFY_ALL_BLOCK         0x40U
#define FTFx_READ_ONCE                0x41U
#define FTFx_PROGRAM_ONCE             0x43U
#define FTFx_ERASE_ALL_BLOCK          0x44U
#define FTFx_SECURITY_BY_PASS         0x45U
#define FTFx_PFLASH_SWAP              0x46U
#define FTFx_ERASE_ALL_BLOCK_UNSECURE 0x49U
#define FTFx_PROGRAM_PARTITION        0x80U
#define FTFx_SET_EERAM                0x81U


/*!
 * @name PFlash swap control codes
 * @{
 */
/*! @brief Initialize Swap System control code */
#define FTFx_SWAP_SET_INDICATOR_ADDR 0x01U
/*! @brief Set Swap in Update State */
#define FTFx_SWAP_SET_IN_PREPARE     0x02U
/*! @brief Set Swap in Complete State */
#define FTFx_SWAP_SET_IN_COMPLETE    0x04U
/*! @brief  Report Swap Status */
#define FTFx_SWAP_REPORT_STATUS      0x08U
/*@}*/

/*!
 * @name PFlash swap states
 * @{
 */
/*! @brief  Uninitialized swap mode */
#define FTFx_SWAP_UNINIT        0x00U
/*! @brief  Ready swap mode */
#define FTFx_SWAP_READY         0x01U
/*! @brief  Update swap mode */
#define FTFx_SWAP_UPDATE        0x02U
/*! @brief  Update-Erased swap mode */
#define FTFx_SWAP_UPDATE_ERASED 0x03U
/*! @brief  Complete swap mode */
#define FTFx_SWAP_COMPLETE      0x04U
/*@}*/

/*! @brief Resume wait count used in FLASH_DRV_EraseResume function */
#define RESUME_WAIT_CNT         0x20U
/*! @brief Suspend wait count used in FLASH_DRV_EraseSuspend function */
#define SUSPEND_WAIT_CNT        0x40U

#if (FEATURE_FLS_IS_FTFE == 1U)
#define DFLASH_IFR_READRESOURCE_ADDRESS 0x8003F8U
#else /* FEATURE_FLASH_IS_FTFL == 1 or FEATURE_FLASH_IS_FTFA == 1 */
#define DFLASH_IFR_READRESOURCE_ADDRESS 0x8000FCU
#endif

#define GET_BIT_0_7(value)   ((uint8_t)(((uint32_t)(value)) & 0xFFU))
#define GET_BIT_8_15(value)  ((uint8_t)((((uint32_t)(value)) >> 8) & 0xFFU))
#define GET_BIT_16_23(value) ((uint8_t)((((uint32_t)(value)) >> 16) & 0xFFU))
#define GET_BIT_24_31(value) ((uint8_t)(((uint32_t)(value)) >> 24))

/* Flash security status */
#define FLASH_SECURITY_STATE_KEYEN     0x80U
#define FLASH_SECURITY_STATE_UNSECURED 0x02U

/* CSEc user key size */
#define CSE_KEY_SIZE_CODE_MAX 0x03U

/*!
 * @addtogroup flash_driver
 * @{
 */

/*!
 * @brief FlexRAM Function control Code
 *
 * Implements : flash_flexRAM_function_control_code_t_Class
 */
typedef enum
{
    EEE_ENABLE                              = 0x00U,    /*!< Make FlexRAM available for emulated EEPROM */
    EEE_QUICK_WRITE                         = 0x55U,    /*!< Make FlexRAM available for EEPROM quick writes */
    EEE_STATUS_QUERY                        = 0x77U,    /*!< EEPROM quick write status query */
    EEE_COMPLETE_INTERRUPT_QUICK_WRITE      = 0xAAU,    /*!< Complete interrupted EEPROM quick write process */
    EEE_DISABLE                             = 0xFFU,    /*!< Make FlexRAM available as RAM */
} flash_flexRam_function_control_code_t;

/*!
 * @name Flash security status
 * @{
 */
/*! @brief  Flash currently not in secure state */
#define FLASH_NOT_SECURE               0x01U
/*! @brief  Flash is secured and backdoor key access enabled */
#define FLASH_SECURE_BACKDOOR_ENABLED  0x02U
/*! @brief  Flash is secured and backdoor key access disabled */
#define FLASH_SECURE_BACKDOOR_DISABLED 0x04U
/*@}*/

/*******************************************************************************
* CallBack function period
*******************************************************************************/
#ifndef FLASH_CALLBACK_CS
/*! @brief  Callback period count for FlashCheckSum
 *
 * This value is only relevant for FlashCheckSum operation, where a high rate of calling back can impair performance.
 * The rest of the flash operations invoke the callback as often as possible while waiting for the flash controller
 * to finish the requested operation.
 */
#define FLASH_CALLBACK_CS 0x0AU
#endif

/*******************************************************************************
* Null Callback function definition
*******************************************************************************/
/*!
 * @name Null Callback function definition
 * @{
 */
/*! @brief  Null callback */
#define NULL_CALLBACK      ((flash_callback_t)0xFFFFFFFFU)

#if FEATURE_FLS_HAS_PF_BLOCK_SWAP
/*! @brief  Null swap callback */
#define NULL_SWAP_CALLBACK ((flash_swap_callback_t)0xFFFFFFFFU)
#endif
/*@}*/

/*******************************************************************************
* Callback function prototype
*******************************************************************************/
/*! @brief Call back function pointer data type
 *
 *   If using callback in the application, any code reachable from this function
 *   must not be placed in a Flash block targeted for a program/erase operation.
 *   Functions can be placed in RAM section by using the START/END_FUNCTION_DEFINITION/DECLARATION_RAMSECTION macros.
 */
typedef void (* flash_callback_t)(void);
#if FEATURE_FLS_HAS_PF_BLOCK_SWAP
/*! @brief Swap call back function pointer data type */
typedef bool (* flash_swap_callback_t)(uint8_t function);
#endif

/*******************************************************************************
* Flash SSD Configuration Structure
*******************************************************************************/
/*!
 * @brief Flash SSD Configuration Structure
 *
 * The structure includes the static parameters for C90TFS/FTFx which are
 * device-dependent. The fields including
 * PFlashBlockBase, PFlashBlockSize, DFlashBlockBase, EERAMBlockBase,
 * and CallBack are passed via flash_user_config_t.
 * The rest of parameters such as DFlashBlockSize, and EEEBlockSize will be
 * initialized in FLASH_DRV_Init() automatically.
 *
 * Implements : flash_ssd_config_t_Class
 */
typedef struct
{
    uint32_t PFlashBase;          /*!< The base address of P-Flash memory */
    uint32_t PFlashSize;          /*!< The size in byte of P-Flash memory */
    uint32_t DFlashBase;          /*!< For FlexNVM device, this is the base address of D-Flash memory (FlexNVM memory);
                                   *    For non-FlexNVM device, this field is unused */
    uint32_t DFlashSize;          /*!< For FlexNVM device, this is the size in byte of area
                                   *    which is used as D-Flash from FlexNVM memory;
                                   *    For non-FlexNVM device, this field is unused */
    uint32_t EERAMBase;           /*!< The base address of FlexRAM (for FlexNVM device)
                                   *    or acceleration RAM memory (for non-FlexNVM device) */
    uint32_t EEESize;             /*!< For FlexNVM device, this is the size in byte of EEPROM area which was partitioned
                                   *    from FlexRAM; For non-FlexNVM device, this field is unused */
    flash_callback_t CallBack;    /*!< Call back function to service the time critical events. Any code reachable from this function
                                   *   must not be placed in a Flash block targeted for a program/erase operation */
} flash_ssd_config_t;

/*******************************************************************************
* Function Prototypes for Flash SSD
*******************************************************************************/
/*!
 * @name Flash driver APIs
 * @{
 */

/*!
 * @brief Initializes Flash.
 *
 * This API initializes Flash module by clearing status error
 * bit and reporting the memory configuration via SSD configuration structure.
 *
 * @param[in] pSSDConfig The SSD configuration structure pointer.
 * @return operation status
 *        - STATUS_SUCCESS:    Operation was successful.
 */
status_t FLASH_DRV_Init(void);

/*!
 * @brief Flash erase sector.
 *
 * This API erases one or more sectors in P-Flash or D-Flash memory.
 * This API always returns FTFx_OK if size provided by the user is
 * zero regardless of the input validation.
 *
 * @param[in] dest Address in the first sector to be erased.
 *
 * @return operation status
 *        - STATUS_SUCCESS:         Operation was successful.
 *        - STATUS_ERROR:           Operation failure was occurred.
 *        - STATUS_UNSUPPORTED:     Operation was unsupported.
 *        - STATUS_BUSY:            Operation was busy.
 */
status_t FLASH_DRV_EraseSector( uint32_t dest,
        						uint32_t size );

/*!
 * @brief Flash program
 *
 * This API is used to program 4 consecutive bytes (for program long
 * word command) and 8 consecutive bytes (for program phrase command) on
 * P-Flash or D-Flash block. This API always returns FTFx_OK if size
 * provided by user is zero regardless of the input validation
 *
 * @param[in] dest Start address for the intended program operation.
 * @param[in] size Size in byte to be programmed
 * @param[in] pData Pointer of source address from which data has to
 *                  be taken for program operation.
 * @return operation status
 *        - STATUS_SUCCESS:         Operation was successful.
 *        - STATUS_ERROR:           Operation failure was occurred.
 *        - STATUS_UNSUPPORTED:     Operation was unsupported.
 *        - STATUS_BUSY:            Operation was busy.
 */
status_t FLASH_DRV_Program(uint32_t dest,
                           uint32_t size,
                           const uint8_t * pData);

/*!
 * @brief Enable the command complete interrupt.
 *
 * This function will enable the command complete interrupt is generated when
 * an FTFC command completes.
 *
 * @return operation status
 *        - STATUS_SUCCESS:         Operation was successful.
 */
status_t FLASH_DRV_EnableCmdCompleteInterupt(void);

/*!
 * @brief Disable the command complete interrupt.
 *
 */
void FLASH_DRV_DisableCmdCompleteInterupt(void);

/*!
 * @brief Enable the read collision error interrupt.
 *
 * This function will enable the read collision error interrupt generation when an
 * FTFC read collision error occurs.
 *
 * @return operation status
 *        - STATUS_SUCCESS:         Operation was successful.
 */
status_t FLASH_DRV_EnableReadColisionInterupt(void);

/*!
 * @brief Disable the read collision error interrupt.
 *
 */
void FLASH_DRV_DisableReadColisionInterupt(void);

#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
/*!
 * @brief Enable the double bit fault detect interrupt.
 *
 * This function will enable the double bit fault detect interrupt generation when
 * an uncorrectable ECC fault is detected during a valid flash read access from
 * the platform flash controller.
 *
 * @return operation status
 *        - STATUS_SUCCESS:         Operation was successful.
 */
status_t FLASH_DRV_EnableDoubleBitFaultInterupt(void);

/*!
 * @brief Disable the double bit fault detect interrupt.
 *
 */
void FLASH_DRV_DisableDoubleBitFaultInterupt(void);
#endif /* End of FEATURE_FLS_HAS_DETECT_ECC_ERROR */
/*!
 * @brief Disables an interrupt for a given IRQ number.
 *
 * This function disables the individual interrupt for a specified IRQ number.
 *
 * @param irqNumber IRQ number
 */
void INT_SYS_DisableIRQ(IRQn_Type irqNumber);

/*!
 * @brief Enables an interrupt for a given IRQ number.
 *
 * This function  enables the individual interrupt for a specified IRQ number.
 *
 * @param irqNumber IRQ number
 */
void INT_SYS_EnableIRQ(IRQn_Type irqNumber);

/*! @brief Interrupt handler type */
typedef void (* isr_t)(void);

/* If target is flash, insert this macro to locate callback function into RAM */
START_FUNCTION_DECLARATION_RAMSECTION
void CCIF_Callback(void)
END_FUNCTION_DECLARATION_RAMSECTION

/*!
 * @brief Returns the Sector num for specified address.
 *
 * This function get the flash address and returns the corresponding setor number.
 *
 * @param Address Address of the Flash to erase
 */
uint8_t Flash_GetMemSec(uint32_t Flash_Erase_Add);


/*!
 * @brief Flash D/E-Flash Partition.
 *
 * This API prepares the FlexNVM block for use as D-Flash, EEPROM backup, or a combination
 * of both and initializes the FlexRAM.
 * In addition, this function is used to configure number of user keys and user key 'Verify Only' attribute if
 * CSEc is enabled.
 *
 * The single partition choice should be used through entire life time of a given
 * application to guarantee the Flash endurance and data retention of Flash module.
 *
 * @param[in] pSSDConfig The SSD configuration structure pointer
 * @param[in] uEEEDataSizeCode EEPROM Data Size Code
 * @param[in] uDEPartitionCode FlexNVM Partition Code
 * @param[in] uCSEcKeySize CSEc Key Size Code, it should be 0 if the function is not used for configuring CSEc part.
 *             It can be:
 *             - 0x00U: Number of User Keys is Zero
 *                      Number of Bytes (subtracts from the total 4K EEERAM space) is 0
 *             - 0x01U: Number of User Keys is 1 to 6 keys
 *                      Number of Bytes (subtracts from the total 4K EEERAM space) is 128 bytes
 *             - 0x02U: Number of User Keys is 1 to 12 keys
 *                      Number of Bytes (subtracts from the total 4K EEERAM space) is 256 bytes
 *             - 0x03U: Number of User Keys is 1 to 24 keys
 *                      Number of Bytes (subtracts from the total 4K EEERAM space) is 512 bytes
 * @param[in] uSFE Security Flag Extension, it should be false if the function is not used for configuring CSEc part.
 * @param[in] flexRamEnableLoadEEEData FlexRAM load during reset option.
 *            - true : FlexRAM loaded with valid EEPROM data during reset sequence
 *            - false : FlexRAM not loaded during reset sequence
 * @return operation status
 *        - STATUS_SUCCESS:         Operation was successful.
 *        - STATUS_ERROR:           Operation failure was occurred.
 *        - STATUS_BUSY:            Operation was busy.
 */
status_t FLASH_DRV_DEFlashPartition(const flash_ssd_config_t * pSSDConfig,
                                    uint8_t uEEEDataSizeCode,
                                    uint8_t uDEPartitionCode,
                                    uint8_t uCSEcKeySize,
                                    bool uSFE,
                                    bool flexRamEnableLoadEEEData);

/*@}*/ /* End of Flash driver APIs*/
/*! @}*/ /* End of addtogroup flash_driver */

#endif /* FLASH_DRIVER_H */
