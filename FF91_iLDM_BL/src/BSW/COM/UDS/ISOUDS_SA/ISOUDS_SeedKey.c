
/****************************************************/
/*Headers                                            */
/****************************************************/

#include "ISOUDS_SeedKey.h"
#include "Platform_Types.h"
#include "stdlib.h"
#include "TIME.h"
#include "FLSHM.h"

/****************************************************/
/*Constants                                            */
/****************************************************/



/****************************************************/
/*Structures                            */
/****************************************************/
sha256_control SA_256;
uint8 SA_Signature[32];

/****************************************************/
/*Function Declarations                                */
/****************************************************/



/****************************************************/
/*Functions                                        */
/****************************************************/

uint8 generateKeyLevel1(uint64 seed, uint8  *p_key)
{

	uint8 *KeyPtr2Seed;
	uint8 seed_pntr[5];
	uint32 total_seed_len;

	KeyPtr2Seed = (uint8*)&seed;


	seed_pntr[0] =KeyPtr2Seed[4];
	seed_pntr[1] =KeyPtr2Seed[3];
	seed_pntr[2] =KeyPtr2Seed[2];
	seed_pntr[3] =KeyPtr2Seed[1];
	seed_pntr[4] =KeyPtr2Seed[0];
    
	/* Initialise the SHA algorithm for seed and key */
    FLASHM_sha256_init(&SA_256);

    /* Set SHA algorithm parameters */
    total_seed_len=5;

    /* Create the signature */
    FLSHM_CreateSignature((uint32) seed_pntr, total_seed_len, &SA_256,total_seed_len);

    /* Get the hash signature for seed */
    FLSHM_GetAppFP(p_key,&SA_256);

    return 0;
}

uint64 GetSeedLevel1(void)
{
	uint64 Seed;
  
	uint64 next = 0;
  
	while (0 == next)
	{
		next = rand();
		next = next * 1103515245UL + 12345;
	}

	/* Passing the timer value as seed */
	Seed = next;
  
    return(Seed);
}
