/** Copyright (c) 2019 EMBITEL
**
** This software is the property of Embitel.
** It can not be used or duplicated without Embitel authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : Flash.c
** Module name  : FLASH DRIVER
** -------------------------------------------------------------------------------------------------
** Description : Flash driver with functionality of Read/Write
**
** -------------------------------------------------------------------------------------------------
**
****************************************************************************************************
** R E V I S I O N  H I S T O R Y
****************************************************************************************************
** V01.00
** - First release
*/

/**************************************** Inclusion files *****************************************/
#include "Flash.h"

START_FUNCTION_DECLARATION_RAMSECTION
static status_t FLASH_DRV_CommandSequence(const flash_ssd_config_t * pSSDConfig)
END_FUNCTION_DECLARATION_RAMSECTION

/*******************************************************************************
 * Code
 ******************************************************************************/
static flash_ssd_config_t flashSSDConfig;

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_Init
 * Description   : Initializes Flash module by clearing status error bit
 * and reporting the memory configuration via SSD configuration structure.
 *
 * Implements    : FLASH_DRV_Init_Activity
 *END**************************************************************************/
status_t FLASH_DRV_Init(void)
{
    status_t ret = STATUS_SUCCESS;

    flash_callback_t pCallBack;

    /* Set callback function before a long time consuming flash operation
     * (ex: erasing) to let the application code do other tasks while flash
     * in operation. In this case we use it to enable interrupt for
     * Flash Command Complete event */
    pCallBack = (flash_callback_t)CCIF_Callback;
    flashSSDConfig.CallBack = pCallBack;

	flashSSDConfig.PFlashBase  = FLASH_PRG_FLASH_BASE;
	flashSSDConfig.PFlashSize  = FLASH_PRG_FLASH_SIZE;
	flashSSDConfig.DFlashBase  = FLASH_DATA_FLASH_BASE;
	flashSSDConfig.DFlashSize  = FEATURE_FLS_DF_SIZE_0011;
	flashSSDConfig.EERAMBase   = FLASH_EEE_BASE;
	flashSSDConfig.EEESize     = FEATURE_FLS_EE_SIZE_0010;
/* If using callback, any code reachable from this function must not be placed in a Flash block targeted for a program/erase operation.*/
	flashSSDConfig.CallBack    = NULL_CALLBACK;

	/*FLASH_DRV_DEFlashPartition( &flashSSDConfig,
								0x02U,
								0x03U,
								0x00U,
								0U,
								0U );*/

   ret = STATUS_SUCCESS;

    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_CommandSequence
 * Description   : Perform command write sequence on Flash.
 * It is internal function, called by driver APIs only.
 *
 *END**************************************************************************/
START_FUNCTION_DEFINITION_RAMSECTION
static status_t FLASH_DRV_CommandSequence(const flash_ssd_config_t * pSSDConfig)
{
    status_t ret = STATUS_SUCCESS;    /* Return code variable */

    /* Clear CCIF to launch command */
    FTFx_FSTAT |= FTFx_FSTAT_CCIF_MASK;

    while (0U == (FTFx_FSTAT & FTFx_FSTAT_CCIF_MASK))
    {
        /* Wait till CCIF bit is set
         * Serve callback function as often as possible
         */
        if (NULL_CALLBACK != pSSDConfig->CallBack)
        {
            /* Temporarily disable compiler's check for ROM access call from within a ram function.
             * The use of a function pointer type makes this check irrelevant.
             * Nevertheless, it is imperative that the user-provided callback be defined in RAMSECTION */
            DISABLE_CHECK_RAMSECTION_FUNCTION_CALL
            (pSSDConfig->CallBack)();
            ENABLE_CHECK_RAMSECTION_FUNCTION_CALL
        }
    }

    /* Check if an error is occurred */
    if ((FTFx_FSTAT & (FTFx_FSTAT_MGSTAT0_MASK | FTFx_FSTAT_FPVIOL_MASK | FTFx_FSTAT_ACCERR_MASK | FTFx_FSTAT_RDCOLERR_MASK)) != 0U)
    {
        ret = STATUS_ERROR;
    }

    return ret;
}
END_FUNCTION_DEFINITION_RAMSECTION

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_EraseSector
 * Description   : Erases one or more sectors in P-Flash or D-Flash memory.
 * This API always returns STATUS_SUCCESS if size provided by the user is
 * zero regardless of the input validation.
 *
 * Implements    : FLASH_DRV_EraseSector_Activity
 *END**************************************************************************/
status_t FLASH_DRV_EraseSector( uint32_t dest,
        						uint32_t size )
{
    status_t ret = STATUS_SUCCESS;       /* Return code variable */
    uint32_t sectorSize;                 /* Size of one sector   */
    uint32_t temp;                       /* Temporary variable   */
    uint32_t tempSize = size;            /* Temporary of size variation */

    DISABLE_INTERRUPTS()

#if FEATURE_FLS_HAS_FLEX_NVM
    temp = flashSSDConfig.DFlashBase;
    if ((dest >= temp) && (dest < (temp + flashSSDConfig.DFlashSize)))
    {
        dest += 0x800000U - temp;
        sectorSize = (uint32_t)FEATURE_FLS_DF_BLOCK_SECTOR_SIZE;
    }
    else
#endif
    {
        temp = flashSSDConfig.PFlashBase;
        if ((dest >= temp) && (dest < (temp + flashSSDConfig.PFlashSize)))
        {
            dest -= temp;
            sectorSize = (uint32_t)FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;
        }
        else
        {
            ret = STATUS_ERROR;
            tempSize = 0U;
            sectorSize = 0U;
        }
    }

    /* Check if the size is sector alignment or not */
    if ((tempSize & (sectorSize - 1U)) != 0U)
    {
        /* Return an error code */
        ret = STATUS_UNSUPPORTED;
    }

    while ((tempSize > 0U) && (STATUS_SUCCESS == ret))
    {
        /* Check CCIF to verify the previous command is completed */
        if (0U == (FTFx_FSTAT & FTFx_FSTAT_CCIF_MASK))
        {
            ret = STATUS_BUSY;
        }
        else
        {
            /* Clear RDCOLERR & ACCERR & FPVIOL flag in flash status register. Write 1 to clear */
            CLEAR_FTFx_FSTAT_ERROR_BITS;

            /* Passing parameter to the command */
            FTFx_FCCOB0 = FTFx_ERASE_SECTOR;
            FTFx_FCCOB1 = GET_BIT_16_23(dest);
            FTFx_FCCOB2 = GET_BIT_8_15(dest);
            FTFx_FCCOB3 = GET_BIT_0_7(dest);

            /* Calling flash command sequence function to execute the command */
            ret = FLASH_DRV_CommandSequence(&flashSSDConfig);

            /* Update size and destination address */
            tempSize -= sectorSize;
            dest += sectorSize;
        }
    }

	ENABLE_INTERRUPTS()

    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_Program
 * Description   : Program 4 consecutive bytes (for program long word command)
 * and 8 consecutive bytes (for program phrase command) on P-Flash or D-Flash block.
 * This API always returns STATUS_SUCCESS if size provided by user is
 * zero regardless of the input validation.
 *
 * Implements    : FLASH_DRV_Program_Activity
 *END**************************************************************************/
status_t FLASH_DRV_Program(uint32_t dest,uint32_t size,const uint8_t * pData)
{
    DEV_ASSERT(pSSDConfig != NULL);
    DEV_ASSERT(pData != NULL);
    status_t ret = STATUS_SUCCESS;    /* Return code variable */
    uint32_t temp;
    uint8_t i;

	DISABLE_INTERRUPTS()

    if ((size & (FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE - 1U)) != 0U)
    {
        ret = STATUS_UNSUPPORTED;
    }
    else
    {
    #if FEATURE_FLS_HAS_FLEX_NVM
        temp = flashSSDConfig.DFlashBase;
        if ((dest >= temp) && (dest < (temp + flashSSDConfig.DFlashSize)))
        {
            dest += 0x800000U - temp;
        }
        else
    #endif
        {
            temp = flashSSDConfig.PFlashBase;
            if ((dest >= temp) && (dest < (temp + flashSSDConfig.PFlashSize)))
            {
                dest -= temp;
            }
            else
            {
                ret = STATUS_ERROR;
            }
        }

        while ((size > 0U) && (STATUS_SUCCESS == ret))
        {
            /* Check CCIF to verify the previous command is completed */
            if (0U == (FTFx_FSTAT & FTFx_FSTAT_CCIF_MASK))
            {
                ret = STATUS_BUSY;
            }
            else
            {
                /* Clear RDCOLERR & ACCERR & FPVIOL flag in flash status register. Write 1 to clear */
                CLEAR_FTFx_FSTAT_ERROR_BITS;

                /* Passing parameter to the command */
                #if (FEATURE_FLS_DF_BLOCK_WRITE_UNIT_SIZE == FTFx_PHRASE_SIZE)
                FTFx_FCCOB0 = FTFx_PROGRAM_PHRASE;
                #else
                FTFx_FCCOB0 = FTFx_PROGRAM_LONGWORD;
                #endif
                FTFx_FCCOB1 = GET_BIT_16_23(dest);
                FTFx_FCCOB2 = GET_BIT_8_15(dest);
                FTFx_FCCOB3 = GET_BIT_0_7(dest);

                for (i = 0U; i < FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE; i++)
                {
                    temp = FTFx_BASE + i + 0x08U;
                    *(uint8_t *)(temp) = pData[i];
                }

                /* Calling flash command sequence function to execute the command */
                ret = FLASH_DRV_CommandSequence(&flashSSDConfig);

                /* Update destination address for next iteration */
                dest += FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE;
                /* Update size for next iteration */
                size -= FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE;
                /* Increment the source address by 1 */
                pData += FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE;
            }
        }
    }
    ENABLE_INTERRUPTS()
    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_EnableCmdCompleteInterupt
 * Description   : Enable the command complete interrupt is generated when
 * an FTFC command completes.
 *
 * Implements    : FLASH_DRV_EnableCmdCompleteInterupt_Activity
 *END**************************************************************************/
status_t FLASH_DRV_EnableCmdCompleteInterupt(void)
{
    const IRQn_Type flashIrqId = FTFC_COMMAND_COMPLETE_IRQS;

    /* Enable the command complete interrupt */
    FTFx_FCNFG |= FTFx_FCNFG_CCIE_MASK;
    INT_SYS_EnableIRQ(flashIrqId);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_DisableCmdCompleteInterupt
 * Description   : Disable the command complete interrupt.
 *
 * Implements    : FLASH_DRV_DisableCmdCompleteInterupt_Activity
 *END**************************************************************************/
void FLASH_DRV_DisableCmdCompleteInterupt(void)
{
    const IRQn_Type flashIrqId = FTFC_COMMAND_COMPLETE_IRQS;

    /* Disable the command complete interrupt */
    FTFx_FCNFG &= (uint8_t)(~FTFx_FCNFG_CCIE_MASK);
    INT_SYS_DisableIRQ(flashIrqId);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_EnableReadColisionInterupt
 * Description   : Enable the read collision error interrupt generation when an
 * FTFC read collision error occurs.
 *
 * Implements    : FLASH_DRV_EnableReadColisionInterupt_Activity
 *END**************************************************************************/
status_t FLASH_DRV_EnableReadColisionInterupt(void)
{
    const IRQn_Type flashIrqId = FTFC_READ_COLLISION_IRQS;

    /* Enable the read collision error interrupt */
    FTFx_FCNFG |= FTFx_FCNFG_RDCOLLIE_MASK;
    INT_SYS_EnableIRQ(flashIrqId);

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_DisableReadColisionInterupt
 * Description   : Disable the read collision error interrupt
 *
 * Implements    : FLASH_DRV_DisableReadColisionInterupt_Activity
 *END**************************************************************************/
void FLASH_DRV_DisableReadColisionInterupt(void)
{
    const IRQn_Type flashIrqId = FTFC_READ_COLLISION_IRQS;

    /* Disable the read collision error interrupt */
    FTFx_FCNFG &= (uint8_t)(~FTFx_FCNFG_RDCOLLIE_MASK);
    INT_SYS_DisableIRQ(flashIrqId);
}

#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_EnableDoubleBitFaultInterupt
 * Description   : Enable the double bit fault detect interrupt generation when
 * an uncorrectable ECC fault is detected during a valid flash read access from
 * the platform flash controller.
 *
 * Implements    : FLASH_DRV_EnableDoubleBitFaultInterupt_Activity
 *END**************************************************************************/
status_t FLASH_DRV_EnableDoubleBitFaultInterupt(void)
{
    /* Enable the double bit fault detect interrupt */
    FTFx_FERCNFG |= FTFx_FERCNFG_DFDIE_MASK;
#if FEATURE_FLS_HAS_INTERRUPT_DOUBLE_BIT_FAULT_IRQ
    INT_SYS_EnableIRQ(FTFC_Fault_IRQn);
#else
    INT_SYS_EnableIRQ(FTFC_IRQn);
#endif
    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_DisableDoubleBitFaultInterupt
 * Description   : Disable the double bit fault detect interrupt
 *
 * Implements    : FLASH_DRV_DisableDoubleBitFaultInterupt_Activity
 *END**************************************************************************/
void FLASH_DRV_DisableDoubleBitFaultInterupt(void)
{
    /* Disable the double bit fault detect interrupt */
    FTFx_FERCNFG &= (uint8_t)(~FTFx_FERCNFG_DFDIE_MASK);
#if FEATURE_FLS_HAS_INTERRUPT_DOUBLE_BIT_FAULT_IRQ
    INT_SYS_DisableIRQ(FTFC_Fault_IRQn);
#else
    INT_SYS_DisableIRQ(FTFC_IRQn);
#endif
}
#endif

/*!
  \brief Callback function for Flash operations
*/
START_FUNCTION_DEFINITION_RAMSECTION
void CCIF_Callback(void)
{
    /* Enable interrupt for Flash Command Complete */
    if ((FTFx_FCNFG & FTFx_FCNFG_CCIE_MASK) == 0u)
    {
        FTFx_FCNFG |= FTFx_FCNFG_CCIE_MASK;
    }
}
END_FUNCTION_DEFINITION_RAMSECTION

/*********************************************************************************
** Function : Flash_GetMemSec

** Description : Get Memory Sec No

** Parameters : Address

** Return value : Sector No

** Remarks : None
**********************************************************************************/
uint8_t Flash_GetMemSec(uint32_t Flash_Erase_Add)
{
uint32_t temp_FlashStart=0;
uint8_t FlashBlock=0,SearchFound=0;

	while(SearchFound!=1){
		if( (temp_FlashStart<=Flash_Erase_Add) && (Flash_Erase_Add<(temp_FlashStart + FEATURE_FLS_PF_BLOCK_SECTOR_SIZE)) ){
			SearchFound =1;
			break;
		}else{
			temp_FlashStart +=FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;
			FlashBlock++;
		}
	}

return FlashBlock;
}

#if 0 // enrico removed

/*FUNCTION**********************************************************************
 *
 * Function Name : FLASH_DRV_DEFlashPartition
 * Description   : Prepares the FlexNVM block for use as D-Flash, EEPROM backup, or a combination
 * of both and initializes the FlexRAM.
 * The single partition choice should be used through entire life time of a given
 * application to guarantee the Flash endurance and data retention of Flash module.
 *
 * Implements    : FLASH_DRV_DEFlashPartition_Activity
 *END**************************************************************************/
status_t FLASH_DRV_DEFlashPartition(const flash_ssd_config_t * pSSDConfig,
                                    uint8_t uEEEDataSizeCode,
                                    uint8_t uDEPartitionCode,
                                    uint8_t uCSEcKeySize,
                                    bool uSFE,
                                    bool flexRamEnableLoadEEEData)
{
    DEV_ASSERT(pSSDConfig != NULL);
    DEV_ASSERT(uCSEcKeySize <= CSE_KEY_SIZE_CODE_MAX);
    status_t ret;    /* Return code variable */

    DISABLE_INTERRUPTS()

    /* Check CCIF to verify the previous command is completed */
    if (0U == (FTFx_FSTAT & FTFx_FSTAT_CCIF_MASK))
    {
        ret = STATUS_BUSY;
    }
    else
    {
        /* Clear RDCOLERR & ACCERR & FPVIOL & MGSTAT0 flag in flash status register. Write 1 to clear */
        CLEAR_FTFx_FSTAT_ERROR_BITS;

        /* Passing parameter to the command */
        FTFx_FCCOB0 = FTFx_PROGRAM_PARTITION;
        FTFx_FCCOB1 = uCSEcKeySize;
        FTFx_FCCOB2 = (uint8_t)(uSFE ? 1U : 0U);
        FTFx_FCCOB3 = (uint8_t)(flexRamEnableLoadEEEData ? 0U : 1U);
        FTFx_FCCOB4 = uEEEDataSizeCode;
        FTFx_FCCOB5 = uDEPartitionCode;

        /* Calling flash command sequence function to execute the command */
        ret = FLASH_DRV_CommandSequence(pSSDConfig);
    }

    ENABLE_INTERRUPTS()

    return ret;
}

#endif

/*******************************************************************************
* EOF
*******************************************************************************/
