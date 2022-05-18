/*
 *    JANI HOVAN, COPYRIGHT (c) 2020
 *    ALL RIGHTS RESERVED
 *
 */

/**
* \file myTypes.h
* \ingroup grpXXX
* \brief Type definitions.
*/

#ifndef __MYTYPES_H
#define __MYTYPES_H

/* === INCLUDES ============================================================= */
/* none */
/* === TYPEDEFS ============================================================= */

typedef unsigned char        uint8_t;
typedef unsigned char        uint8;
typedef signed char          sint8_t;
typedef signed char          sint8;

typedef unsigned short       uint16_t;
typedef unsigned short       uint16;
typedef signed short         sint16_t;
typedef signed short         sint16;

#if 1 //32bit as long
typedef unsigned long        uint32_t;
typedef uint32_t             uint32;
typedef signed long          sint32_t;
typedef sint32_t             sint32;
#else //32bit as int
typedef unsigned int         uint32_t;
typedef uint32_t             uint32;
typedef signed int           sint32_t;
typedef sint32_t             sint32;
#endif

typedef unsigned long long   uint64_t;
typedef uint64_t             uint64;
typedef signed long long     sint64_t;
typedef sint64_t             sint64;

typedef double               double64_t;
typedef float                float32_t;


/* Only for Target-Link functions: */
typedef void                 Void;
typedef float                Float32;

typedef volatile unsigned char  vuint8_t;
typedef volatile unsigned short vuint16_t;
typedef volatile unsigned long  vuint32_t;

typedef unsigned char        bool_t;
typedef unsigned char        boolean_t;

/** Enumerated type definition for boolean values */
typedef enum enumBool
{
    E_FALSE   = 0,  ///< 0: Boolean expression False
    E_TRUE    = 1,  ///< 1: Boolean expression True
    E_NOT_OK  = 0,  ///< 0: NOT OK or ERROR
    E_OK      = 1,  ///< 1: OK state or no error
    E_LOW     = 0,  ///< 0: Logical LOW signal
    E_HIGH    = 1,  ///< 1: Logical HIGH signal
    E_OFF     = 0,  ///< 0: Switch OFF
    E_ON      = 1,  ///< 1: Switch ON
    E_STOP    = 0,  ///< 0: Stop routine
    E_START   = 1   ///< 1: Start routine
} eBool_t;

typedef unsigned int         bitfield_t;

typedef union
{
  uint16_t u16;
  uint8_t  u8[2];
} word2byte_t;

typedef union l2c
{
  uint32_t u32;
  uint16_t u16[2];
  uint8_t  u8[4];
} long2byte_t;

typedef union 
{
    uint8_t byte;
    struct
    {
        uint8_t b0:1;
        uint8_t b1:1;
        uint8_t b2:1;
        uint8_t b3:1;
        uint8_t b4:1;
        uint8_t b5:1;
        uint8_t b6:1;
        uint8_t b7:1;
    } bits;
} flags8_t;

typedef union 
{
    uint16_t word;
    struct
    {
        uint16_t b0:1;
        uint16_t b1:1;
        uint16_t b2:1;
        uint16_t b3:1;
        uint16_t b4:1;
        uint16_t b5:1;
        uint16_t b6:1;
        uint16_t b7:1;
        uint16_t b8:1;
        uint16_t b9:1;
        uint16_t b10:1;
        uint16_t b11:1;
        uint16_t b12:1;
        uint16_t b13:1;
        uint16_t b14:1;
        uint16_t b15:1;
    } bits;
} flags16_t;

typedef union
{
    uint32_t u32;
    uint16_t u16[2];
    uint8_t  u8[4];
    struct
    {
        uint16_t b0:1;
        uint16_t b1:1;
        uint16_t b2:1;
        uint16_t b3:1;
        uint16_t b4:1;
        uint16_t b5:1;
        uint16_t b6:1;
        uint16_t b7:1;
        uint16_t b8:1;
        uint16_t b9:1;
        uint16_t b10:1;
        uint16_t b11:1;
        uint16_t b12:1;
        uint16_t b13:1;
        uint16_t b14:1;
        uint16_t b15:1;
        uint16_t b16:1;
        uint16_t b17:1;
        uint16_t b18:1;
        uint16_t b19:1;
        uint16_t b20:1;
        uint16_t b21:1;
        uint16_t b22:1;
        uint16_t b23:1;
        uint16_t b24:1;
        uint16_t b25:1;
        uint16_t b26:1;
        uint16_t b27:1;
        uint16_t b28:1;
        uint16_t b29:1;
        uint16_t b30:1;
        uint16_t b31:1;
    } bits;
} flags32_t;

/* === SYMBOLIC CONSTANTS =================================================== */
/* none */
/* === EXPORTED MACROS ====================================================== */
#ifndef TRUE
  #define TRUE  (1U)
#endif
#ifndef FALSE
  #define FALSE (0U)
#endif

#define BIT_0    0x01
#define BIT_1    0x02
#define BIT_2    0x04
#define BIT_3    0x08
#define BIT_4    0x10
#define BIT_5    0x20
#define BIT_6    0x40
#define BIT_7    0x80
#define BIT_8    0x100
#define BIT_9    0x200
#define BIT_10   0x400
#define BIT_11   0x800
#define BIT_12   0x1000
#define BIT_13   0x2000
#define BIT_14   0x4000
#define BIT_15   0x8000
#define BIT_16   0x10000

/* === GLOBAL MACRO DEFINITIONS ============================================ */

/* TYPE CONVERSIONS */

/** Convert a value \a x of any type to unsigned 8-bit. */
#define UINT8(x)        ((uint8_t)(x))

/** Convert a value \a x of any type to unsigned 16-bit. */
#define UINT16(x)       ((uint16_t)(x))

/** Convert a value \a x of any type to double_t. */
#define DOUBLE(x)       ((double_t)(x))

/** Type definition for 24-bit unsigned value (range 0 to 16777215) */
typedef struct uint24_s
{
#if CPU_BYTE_ORDER == HIGH_BYTE_FIRST
    // HIGH BYTE FIRST: this is standard for the C51 compiler
    uint8_t     bHi;    /**< high-byte (bits 16-23) */
    uint16_t    wLo;    /**< low-word (bits 0-15), byte order h/l */
#else
    // LOW BYTE FIRST
    uint16_t    wLo;    /**< low-word (bits 0-15), byte order l/h */
    uint8_t     bHi;    /**< high-byte (bits 16-23) */
#endif
}
sUint24_t;

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef NULL_PTR
#define NULL_PTR ((void*)0)
#endif

/* === EXPORTED VARIABLES =================================================== */
/* none */
/* === EXPORTED FUNCTIONS =================================================== */
/* none */

#endif /* __MYTYPES_H */


/* === HISTORY ============================================================== */
/* $Log:   $
 * 
*/
