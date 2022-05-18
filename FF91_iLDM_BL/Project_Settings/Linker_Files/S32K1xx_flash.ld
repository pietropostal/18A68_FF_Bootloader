/*
** ###################################################################
**     Processor:           S32K144 with 64 KB SRAM
**     Compiler:            GNU C Compiler
**
**     Abstract:
**         Linker file for the GNU C Compiler
**
**     Copyright (c) 2015-2016 Freescale Semiconductor, Inc.
**     Copyright 2017 NXP
**     All rights reserved.
**
**     THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
**     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
**     OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
**     IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
**     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**     SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
**     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
**     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
**     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
**     THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
** ###################################################################
*/

/* Entry Point */
ENTRY(Reset_Handler)

HEAP_SIZE  = DEFINED(__heap_size__)  ? __heap_size__  : 0x00000400;
STACK_SIZE = DEFINED(__stack_size__) ? __stack_size__ : 0x00000400;

/* If symbol __flash_vector_table__=1 is defined at link time
 * the interrupt vector will not be copied to RAM.
 * Warning: Using the interrupt vector from Flash will not allow
 * INT_SYS_InstallHandler because the section is Read Only.
 */
M_VECTOR_RAM_SIZE = DEFINED(__flash_vector_table__) ? 0x0 : 0x0400;

/* Specify the memory areas */
MEMORY
{
  /* Flash */
  /* Flash using full chip (all memory) */
/*  m_interrupts          (RX)  : ORIGIN = 0x00000000, LENGTH = 0x00000400 */
/*  m_flash_config        (RX)  : ORIGIN = 0x00000400, LENGTH = 0x00000010 */
/*  m_text                (RX)  : ORIGIN = 0x00000410, LENGTH = 0x00080000-0x410 */  /* 512k (full memory) */
  
  /* Flash for Bootloader (standalone) */
  m_interrupts          (RX)  : ORIGIN = 0x00000000, LENGTH = 0x00000400 
  m_flash_config        (RX)  : ORIGIN = 0x00000400, LENGTH = 0x00000010 
  m_text                (RX)  : ORIGIN = 0x00000410, LENGTH = 0x7F00-0x410
  
  /* Flash for Application (standalone) */
/*  m_interrupts          (RX)  : ORIGIN = 0x00000000, LENGTH = 0x00000400       */  
/*  m_flash_config        (RX)  : ORIGIN = 0x00000400, LENGTH = 0x00000010       */
/*  m_text                (RX)  : ORIGIN = 0x00008000, LENGTH = 0x20000-0x8000-4 *//* 96k - 4Byte starting from 0x8000 */
  
  /* Flash for Application (for Bootloader) */
/*  m_interrupts          (RX)  : ORIGIN = 0x00008000, LENGTH = 0x00000400 */
/*  m_flash_config        (RX)  : ORIGIN = 0x00008400, LENGTH = 0x00000010 */
/*  m_text                (RX)  : ORIGIN = 0x00008410, LENGTH = 0x20000-0x8410-4 */ /* 95k - 4Byte starting from 0x8410 */
   
  m_crc32               (RX)  : ORIGIN = 0x20000-4,  LENGTH = 0x4               /* 4 Byte CRC */
  m_applvalidflags      (RX)  : ORIGIN = 0x20000,    LENGTH = 0x1000            /* 4k */

  /* Flex-RAM */
  m_flexram             (RW)  : ORIGIN = 0x14000000, LENGTH = 0x00001000
  
  /* SRAM_L */
  m_data                (RW)  : ORIGIN = 0x1FFF8000, LENGTH = 0x00008000

  /* SRAM_U */
  m_data_2              (RW)  : ORIGIN = 0x20000000, LENGTH = 0x00006FF0 /* enrico changed */
  m_bootflags           (RW)  : ORIGIN = 0x20006FF0, LENGTH = 0x10 /* SRAM_U: Re-Programming request data */
}

/* Define output sections */
SECTIONS
{
  .crc32 : /* application code CRC32 */
  {
    __CRC32 = .;
  } > m_crc32
  
  .bootflags : /* enrico added */
  {
    __BOOTFLAGS = .;
  } > m_bootflags
  
  .applvalid : /* application valid flags */
  {
    __APPLVALIDFLAGS = .;
  } > m_applvalidflags  
  
  /*___DID0xF180______________________________________________________________*/
  .segmentDID0xF180 0x00007F00 : /* inside bootloader */
  /* .segmentDID0xF180 0x00027F00 : */ /* fake bootloader */
  {
    KEEP(*(.sectionDID0xF180))
  }
  
  /*___DID0xF181______________________________________________________________*/
  .segmentDID0xF181 0x0001FC00 :
  {
    KEEP(*(.sectionDID0xF181))
  }
  
  /*___DID0xF182______________________________________________________________*/
  .segmentDID0xF182 0x0001FC10 :
  {
    KEEP(*(.sectionDID0xF182))
  }
 
  /*___DID0xF188 Bootloader___________________________________________________*/
  .segmentDID0xF188BOOT 0x00007F10 :  /* inside bootloader */
  /*.segmentDID0xF188BOOT 0x00027F10 : */ /* fake bootloader */
  {
    KEEP(*(.sectionDID0xF188BOOT))
  }

  /*___DID0xF188 Application__________________________________________________*/
  .segmentDID0xF188APP 0x0001FC20 :
  {
    KEEP(*(.sectionDID0xF188APP))
  }
  
  /*___DID0xF188 Calibration__________________________________________________*/
  .segmentDID0xF188CAL 0x0001FC30 :
  {
    KEEP(*(.sectionDID0xF188CAL))
  }
  
  /*___DID0xF18B______________________________________________________________*/
  .segmentDID0xF18B 0x00070000 :
  {
    KEEP(*(.sectionDID0xF18B))
  }

  /*___DID0xF18C______________________________________________________________*/
  .segmentDID0xF18C 0x00071000 :
  {
    KEEP(*(.sectionDID0xF18C))
  }
  
  /*___DID0xF193______________________________________________________________*/
  .segmentDID0xF193 0x00072000 :
  {
    KEEP(*(.sectionDID0xF193))
  }  

  /*___DID0xF200______________________________________________________________*/
  .segmentDID0xF200 0x00073000 :
  {
    KEEP(*(.sectionDID0xF200))
  }

  /*___DID0xF191______________________________________________________________*/
  .segmentDID0xF191 0x00074000 :
  {
    KEEP(*(.sectionDID0xF191))
  }

  /*___DID0xF198 Bootloader___________________________________________________*/
  .segmentDID0xF198BOOT 0x00075000 :
  {
    KEEP(*(.sectionDID0xF198BOOT))
  }

  /*___DID0xF198 Application__________________________________________________*/
  .segmentDID0xF198BOOT 0x00076000 :
  {
    KEEP(*(.sectionDID0xF198APP))
  }

  /*___DID0xF198 Calibration__________________________________________________*/
  .segmentDID0xF198CAL 0x00077000 :
  {
    KEEP(*(.sectionDID0xF198CAL))
  }

  /*___DID0xF190______________________________________________________________*/
  .segmentDID0xF190 0x00078000 :
  {
    KEEP(*(.sectionDID0xF190))
  }


  /*___Bootloader Data (production mode; reprogramming cnt; ...)______________*/
  .segmentBOOTDATA 0x0007F000 :
  {
    KEEP(*(.sectionBOOTDATA))
  }


  
  /*___eeprom via FlexRAM_____________________________________________________*/
  .eeprom (NOLOAD):
  {
     *(.eeprom)
  } > m_flexram
  
  
  /* The startup code goes first into internal flash */
  .interrupts :
  {
    __VECTOR_TABLE = .;
    . = ALIGN(4);
    KEEP(*(.isr_vector))     /* Startup code */
    . = ALIGN(4);
  } > m_interrupts

  .flash_config :
  {
    . = ALIGN(4);
    KEEP(*(.FlashConfig))    /* Flash Configuration Field (FCF) */
    . = ALIGN(4);
  } > m_flash_config

  /* The program code and other data goes into internal flash */
  .text :
  {
    . = ALIGN(4);
    *(.text)                 /* .text sections (code) */
    *(.text*)                /* .text* sections (code) */
    *(.rodata)               /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)              /* .rodata* sections (constants, strings, etc.) */
    *(.glue_7)               /* glue arm to thumb code */
    *(.glue_7t)              /* glue thumb to arm code */
    *(.eh_frame)
    KEEP (*(.init))
    KEEP (*(.fini))
    . = ALIGN(4);
  } > m_text

  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > m_text

  .ARM :
  {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } > m_text

 .ctors :
  {
    __CTOR_LIST__ = .;
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
       from the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    __CTOR_END__ = .;
  } > m_text

  .dtors :
  {
    __DTOR_LIST__ = .;
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    __DTOR_END__ = .;
  } > m_text

  .preinit_array :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } > m_text

  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } > m_text

  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } > m_text

  __etext = .;    /* Define a global symbol at end of code. */
  __DATA_ROM = .; /* Symbol is used by startup for data initialization. */
  .interrupts_ram :
  {
    . = ALIGN(4);
    __VECTOR_RAM__ = .;
    __interrupts_ram_start__ = .; /* Create a global symbol at data start. */
    *(.m_interrupts_ram)          /* This is a user defined section. */
    . += M_VECTOR_RAM_SIZE;
    . = ALIGN(4);
    __interrupts_ram_end__ = .;   /* Define a global symbol at data end. */
  } > m_data

  __VECTOR_RAM = DEFINED(__flash_vector_table__) ? ORIGIN(m_interrupts) : __VECTOR_RAM__ ;
  __RAM_VECTOR_TABLE_SIZE = DEFINED(__flash_vector_table__) ? 0x0 : (__interrupts_ram_end__ - __interrupts_ram_start__) ;

  .data : AT(__DATA_ROM)
  {
    . = ALIGN(4);
    __DATA_RAM = .;
    __data_start__ = .;      /* Create a global symbol at data start. */
    *(.data)                 /* .data sections */
    *(.data*)                /* .data* sections */
    KEEP(*(.jcr*))
    . = ALIGN(4);
    __data_end__ = .;        /* Define a global symbol at data end. */
  } > m_data

  __DATA_END = __DATA_ROM + (__data_end__ - __data_start__);
  __CODE_ROM = __DATA_END; /* Symbol is used by code initialization. */
  .code : AT(__CODE_ROM)
  {
    . = ALIGN(4);
    __CODE_RAM = .;
    __code_start__ = .;      /* Create a global symbol at code start. */
    *(.code_ram)             /* Custom section for storing code in RAM */
    . = ALIGN(4);
    __code_end__ = .;        /* Define a global symbol at code end. */
  } > m_data

  __CODE_END = __CODE_ROM + (__code_end__ - __code_start__);

  /* Custom Section Block that can be used to place data at absolute address. */
  /* Use __attribute__((section (".customSection"))) to place data here. */
  .customSectionBlock  ORIGIN(m_data_2) :
  {
    KEEP(*(.customSection))  /* Keep section even if not referenced. */
  } > m_data_2

  /* Uninitialized data section. */
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section. */
    . = ALIGN(4);
    __BSS_START = .;
    __bss_start__ = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
    __BSS_END = .;
  } > m_data_2

  .heap :
  {
    . = ALIGN(8);
    __end__ = .;
    PROVIDE(end = .);
    PROVIDE(_end = .);
    PROVIDE(__end = .);
    __HeapBase = .;
    . += HEAP_SIZE;
    __HeapLimit = .;
    __heap_limit = .;
  } > m_data_2

  .stack :
  {
    . = ALIGN(8);
    . += STACK_SIZE;
  } > m_data_2

  /* Initializes stack on the end of block */
  __StackTop   = ORIGIN(m_data_2) + LENGTH(m_data_2);
  __StackLimit = __StackTop - STACK_SIZE;
  PROVIDE(__stack = __StackTop);

  .ARM.attributes 0 : { *(.ARM.attributes) }

  ASSERT(__StackLimit >= __HeapLimit, "region m_data_2 overflowed with stack and heap")
}

