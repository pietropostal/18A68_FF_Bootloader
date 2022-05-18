/***************************************************************************************************
** Copyright (c) 2019 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -------------------------------------------------------------------------------------------------
** File Name    : ISOUDS_RdDaByID.c
** Module Name  : ISOUDS_RdDaByID
** -------------------------------------------------------------------------------------------------
**
** Description : Read Data by Identifier
**
** -------------------------------------------------------------------------------------------------
**
** Documentation reference : EME-17ST013-12211.01(SWLLD CanSrv_RdDaByID)
**
****************************************************************************************************
** R E V I S I O N H I S T O R Y
****************************************************************************************************
** V01.00 16/07/2019
** - Baseline Created
**
***************************************************************************************************/

/**************************************** Inclusion files *****************************************/
#include "ISOUDS_RdDaByID.h"
#include "ISOUDS_RdCfg.h"
#include "ISOUDS_SA.h"

/********************** Declaration of local symbol and constants *********************************/

/********************************* Declaration of local macros ************************************/

/********************************* Declaration of local types *************************************/

/******************************* Declaration of local variables ***********************************/
/* Holds the configuration table index */
static VAR(uint8, AUTOMATIC) ISOUDS_RdTabIdx;
/* Holds the Negative response code */
static VAR(uint8, AUTOMATIC) ISOUDS_RdNRC;

/******************************* Declaration of local constants ***********************************/

/****************************** Declaration of exported variables *********************************/

/****************************** Declaration of exported constants *********************************/

/***************************************************************************************************
**                                      FUNCTIONS                                                 **
***************************************************************************************************/

/**************************** Internal functions declarations *************************************/
static VAR(uint8, AUTOMATIC) ISOUDS_RdDidData (uint16 rdDid,uint8 buff[], uint16 *buffPos);
static VAR(uint8, AUTOMATIC) ISOUDS_RdLookUp (uint16 recvDid);

/******************************** Function definitions ********************************************/

/***************************************************************************************************
** Function                 : ISOUDS_RdDaByID

** Description              : Sends response to Read Data by ID service request

** Parameter ISOUDSConfPtr  : Pointer to service configuration structure

** Parameter dataBuff       : Data array

** Return value             : None
***************************************************************************************************/
void ISOUDS_RdDaByID (ISOUDS_ConfType *ISOUDSConfPtr, uint8 dataBuff[])
{
	VAR(uint16, AUTOMATIC)  locDID;
	VAR(uint16, AUTOMATIC)   numOfDids;
    VAR(uint8, AUTOMATIC)   txData[ISOUDS_BUFFSIZE];
    VAR(uint16, AUTOMATIC)    txPos;
    VAR(uint16, AUTOMATIC)    idx;
    VAR(uint8, AUTOMATIC)   rdFirstNRC;
    VAR(uint8, AUTOMATIC) rdNoError;
    VAR(uint8, AUTOMATIC) posResp;


    // Enrico
    // Update active session
    ISOUDS_ActiveDiag_session[0] = ISOUDS_Sess;

    /* Initialize the tx position to 0 */
    txPos = (uint16)0;

    /* Initialize to (uint8)ISOUDS_FALSE - Negative response */
    posResp = (uint8)(uint8)ISOUDS_FALSE;

    /* Initialize the first negative response to 0 (invalid/ non-updated value) */
    rdFirstNRC = (uint8)0;


    /* Check if received length is valid */
    if ((ISOUDSConfPtr->srvLen > (uint16)1) &&
        (((ISOUDSConfPtr->srvLen - (uint16)1) % (uint8)2) == (uint8)0))
    {
        /* Number of DIDs received in request.*/
        numOfDids = ((ISOUDSConfPtr->srvLen - (uint8)1) / ((uint8)2));

        for (idx = (uint16)0; idx < numOfDids; idx++)
        {
            /* get the data identifier value */
            locDID = ((uint16)(((uint16)dataBuff[idx * (uint8)2]) << (uint8)8) +
                                            dataBuff[(uint8)1 + (idx * (uint8)2)]);

            /* Check if DID is configured for read purpose */
            if ((uint8)ISOUDS_TRUE == ISOUDS_RdLookUp (locDID))
            {

                    /* Check if DID is configured to be read in active session */
                    if ((((ISOUDS_RdConfTab[ISOUDS_RdTabIdx].rdDidSess) >> ISOUDS_Sess) & (uint8)1)
                                                                                        == (uint8)1)
                    {
                       /* MISRA RULE 1.2 VIOLATION: Taking address of near auto variable: 
					   The address- is passed as a function paramter and is sucessfully tested */
                        /* function call to get the data record value of the DID */
                        rdNoError = ISOUDS_RdDidData (locDID, txData, &txPos);

                        /* Check if data record value is fetched */
                        if (rdNoError == (uint8)ISOUDS_TRUE)
                        {
                            /* Send positive response */
                            posResp = (uint8)ISOUDS_TRUE;
                        }
                        /* Check if Negative response is due insufficient buffer space */
                        else if (ISOUDS_RdNRC == (uint8)ISOUDS_ROOR)
                        {
                            /* Send negative response - buffer size exceeded */
                            posResp = (uint8)ISOUDS_FALSE;
                        }
                        else
                        {
                            /* Do Nothing */
                        }
                    }
                    else
                    {
                        /* NRC - Request Out Of Range */
                        ISOUDS_RdNRC = (uint8)ISOUDS_ROOR;

                        /* Error - DID not supported in active session */
                        rdNoError = (uint8)ISOUDS_FALSE;
                    }

            }
            else
            {
                /* NRC - Request Out Of Range */
                ISOUDS_RdNRC = (uint8)ISOUDS_ROOR;

                /* Error - DID not configured for read */
                rdNoError = (uint8)ISOUDS_FALSE;
            }

            /* Check for negative response and the NRC has not been previously updated */
            if ((rdFirstNRC == (uint8)0) && (rdNoError == (uint8)ISOUDS_FALSE))
            {
                /* Update the First NRC variable with the NRC code */
                rdFirstNRC = ISOUDS_RdNRC;
            }
        }
    }
    /* invalid message length */
    else
    {
        /* Negative response */
        /* Invalid Message Length Or Invalid Format */
        rdFirstNRC = (uint8)ISOUDS_IMLOIF;
    }

    /* Check if positive response is to be sent */
    if (posResp == (uint8)ISOUDS_TRUE)
    {
        /* prepare the response */
        for (idx = (uint16)0; idx < txPos; idx++)
        {
            /* MISRA RULE 9.1 VIOLATION: The initialization of txData[] is not necessary -
                - as data is copied only when necessary conditions are satisfied */
            dataBuff[idx] = txData[idx];
        }

        /* Response length for the current Service - including SID */
        ISOUDSConfPtr->srvLen = (txPos + (uint16)1);

        /* Send positive response */
        ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESP;
    }
    /* Negative response to be sent */
    else
    {
        /* Negative response */
        ISOUDSConfPtr->srvSt = (uint8)ISOUDS_RESPNEG;

        /* Invalid Message Length Or Invalid Format */
        ISOUDSConfPtr->srvNegResp = rdFirstNRC;
    }
}

/**************************************************************************************************
** Function                 : ISOUDS_RdArrData

** Description              : Reads the data record value of an array

** Parameter srcBuff        : data array

** Parameter len            : Length - Number of Bytes to read

** Return value             : 0  -> Read operation successful
                              1  -> Read Operation unsuccessful

** Remarks                  : None
***************************************************************************************************/
VAR(uint8, AUTOMATIC)  ISOUDS_RdArrData ( VAR(uint8, AUTOMATIC)  srcBuff[], \
						VAR(uint8, AUTOMATIC)  len)
{
    uint8 retVal;
    uint8 idx;

    /* read directly from address */
    for (idx = (uint8)0; idx < len; idx++)
    {
        /* MISRA RULE 17.4 VIOLATION: Performing pointer arithmetic
        -Pointer arithmetic is more efficient
        */
        /* Copy the value */
        srcBuff[idx] = *(ISOUDS_RdConfTab[ISOUDS_RdTabIdx].rdDidAddr + (uint8)idx);
    }

    /* Read operation success */
    retVal = (uint8)0;

    return (retVal);
}

/**************************** Internal Function definitions ***************************************/

/***************************************************************************************************
** Function                 : ISOUDS_RdDidData

** Description              : Reads the data record value

** Parameter rdDid          : Read data identifier

** Parameter buff           : data array

** Parameter buffPos        : pointer to buffer position

** Return value             : (uint8)ISOUDS_TRUE  -> If read operation was successful
                              (uint8)ISOUDS_FALSE -> If read operation was unsuccessful
***************************************************************************************************/
static  VAR(uint8, AUTOMATIC)  ISOUDS_RdDidData (VAR(uint16, AUTOMATIC) rdDid,\
                                                  VAR(uint8, AUTOMATIC) buff[], \
                                                  P2VAR(uint16, AUTOMATIC,CAN_CODE) buffPos)
{
    uint8   readSt;
    uint8 readOK;
    uint8   idx;

    /* Initialize the read success to (uint8)ISOUDS_FALSE */
    readOK = (uint8)ISOUDS_FALSE;

    /* Check if sufficient bytes are available for reading the data record */
    if (((uint16)(*buffPos) + (uint16)(ISOUDS_RdConfTab[ISOUDS_RdTabIdx].rdDidLen) + (uint16)2)
                                                            < ((uint16)ISOUDS_BUFFSIZE))
    {
        /* Store the DID value and increment the buffer position */
        buff[*buffPos] = (uint8)(rdDid >> 8);
        *buffPos += (uint16)1;
        buff[*buffPos] = (uint8)rdDid;
        *buffPos += (uint16)1;

        /* Check if read function is configured for the corresponding DID */
        if (ISOUDS_RdConfTab[ISOUDS_RdTabIdx].rdDid_funPtr != ISOUDS_RDFUNCNULLPTR)
        {
            /* dedicated function to read */
            readSt = (ISOUDS_RdConfTab[ISOUDS_RdTabIdx].rdDid_funPtr)(&buff[*buffPos],
                                            ISOUDS_RdConfTab[ISOUDS_RdTabIdx].rdDidLen);
            *buffPos += (uint16)(ISOUDS_RdConfTab[ISOUDS_RdTabIdx].rdDidLen);

            /* If Reading of data bytes successful */
            if (readSt == (uint8)0x00)
            {
                /* Read Success */
                readOK = (uint8)ISOUDS_TRUE;
            }
            /* Read Unsuccessful */
            else if (readSt == (uint8)0x01)
            {
                /* NRC - Conditions not correct */
                ISOUDS_RdNRC = (uint8)ISOUDS_CNC;
            }
            else
            {
                /* Do Nothing */
            }
        }
        /* Check if read address is configured for the corresponding DID */
        else if (ISOUDS_RdConfTab[ISOUDS_RdTabIdx].rdDidAddr != NULL_PTR)
        {
            for (idx = (uint8)0; idx < ISOUDS_RdConfTab[ISOUDS_RdTabIdx].rdDidLen; idx++)
            {
               /* MISRA RULE 17.4 VIOLATION: pointer arithmetic used to read 
                  data from a address location with offset */
               /* Copy the value */
               buff[*buffPos] = *(ISOUDS_RdConfTab[ISOUDS_RdTabIdx].rdDidAddr + 
                                                                   (uint8)idx);
               *buffPos += (uint16)1;
            }
            
            /* Reading of data bytes successful */
            readOK = (uint8)ISOUDS_TRUE;
        }
        else
        {
            /* Do nothing */
        }
    }
    else
    {
        /* NRC - Request out of range */
        ISOUDS_RdNRC = (uint8)ISOUDS_ROOR;
    }

    return (readOK);
}

/***************************************************************************************************
** Function                 : ISOUDS_RdLookUp

** Description              : Checks whether the DID is configured for reading

** Parameter recvDid        : DID received in the request

** Return value             : (uint8)ISOUDS_TRUE  -> DID configured for reading
                              (uint8)ISOUDS_FALSE -> DID not configured for reading
***************************************************************************************************/
static  VAR(uint8, AUTOMATIC)  ISOUDS_RdLookUp (uint16 recvDid)
{
	uint8 rdDidFound;
    uint8   idx;

    /* Initialize to (uint8)ISOUDS_FALSE */
    rdDidFound = (uint8)ISOUDS_FALSE;

    /* Search in the Write configuration table whether the DID is configured */
    for(idx = (uint8)0; ((idx < ((uint8)ISOUDS_RDCONFTABSIZE)) && \
								(rdDidFound != (uint8)ISOUDS_TRUE));idx++)
    {
        /* Check for a DID match */
        if (ISOUDS_RdConfTab[idx].rdDid == recvDid)
        {
            /* DID is configured for writing */
            rdDidFound = (uint8)ISOUDS_TRUE;

            /* Save the index of the corresponding DID */
            ISOUDS_RdTabIdx = idx;
        }
    }

    return (rdDidFound);
}
