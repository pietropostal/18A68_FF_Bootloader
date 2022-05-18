
/* To avoid multi-inclusions */
#ifndef ISOUDS_SEEDKEY_H
#define ISOUDS_SEEDKEY_H
#include "Platform_Types.h"

#define KEYSIZE (uint8)32u
extern uint8 generateKeyLevel1(uint64 seed, uint8  *p_key);
extern uint64 GetSeedLevel1(void);
#endif /* ISOUDS_SEEDKEY_H */
