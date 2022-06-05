Enrico 26.09.2021:


MemoryMap
============

ROM: 512KB

 *  |
 *  |__________________S32K144 Memory Architecture__________________________
 *  |
 *  |
 *  |   S32K144         ==> 512 KB Program memory
 *  |
 *  |   1 Sector        ==> 4096 Bytes
 *  |
 *  |   Total sector    ==> 128 Sector (0 to 127)
 *  |
 *  |   Start Address   ==> 0x00000000
 *  |
 *  |   End Address     ==> 0x0007FFFF
 *  |
 *  |__________________Boot loader Memory Mapping____________________________
 *  |
 *  |
 *  |   Boot loader Memory Size ==> 32 KB
 *  |
 *  |   Assigned Sector         ==> 0 to 8
 *  |
 *  |   Start Address           ==> 0x00000000
 *  |
 *  |   End Address             ==> 0x00007FFF
 *  |
 *  |_________________Application Memory Mapping_____________________________
 *  |
 *  |
 *  |   Application Memory Size ==> 240 KB
 *  |
 *  |   Assigned Sector         ==> 8 to 60
 *  |
 *  |Header Information         ==> 44 Byte
 *  |
 *  |           Start Address   ==> 0x00043000
 *  |           End Address     ==> 0x00043FFF
 *  |
 *  |Application Information
 *  |
 *  |           Start Address   ==> 0x00008000U
 *  |           End Address     ==> 0x00043FFFU
 *  |
 *  |_________________Calibration Memory Mapping_____________________________
 *  |
 *  |
 *  |   Calibration Memory Size ==> 240 KB
 *  |
 *  |   Assigned Sector         ==> 8 to 60
 *  |
 *  |Header Information         ==> 44 Byte
 *  |
 *  |           Start Address   ==> 0x0007F000
 *  |           End Address     ==> 0x0007FFFF
 *  |
 *  |Calibration Information
 *  |
 *  |           Start Address   ==> 0x00044000
 *  |           End Address     ==> 0x0007FFFF
 *  |_______________________________________________________________________
 *


RAM: 64KB
===========

0x1fff8000 - Interrupts
0x1fff8400 - data
0x20000000 - bss

Dataflash: 4kKB/64KB FlexRAM etc. 
==========
0x10000000 - not touched!

======================================================
======================================================

Diag-Services


