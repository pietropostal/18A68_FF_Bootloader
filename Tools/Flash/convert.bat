@ECHO OFF

srec_cat.exe FF91_iLDM.srec -crop 0x8000 0x20000 -o FF91_iLDM_CANFlash.hex -Intel
srec_cat.exe FF91_iLDM_CANFlash.hex -Intel -fill 0xFF -over FF91_iLDM_CANFlash.hex -Intel -o FF91_iLDM_CANFlash.hex -Intel
srec_cat.exe FF91_iLDM_BL.srec -crop 0x0000 0x8000 -o tmp_Bootloader.srec
srec_cat.exe FF91_iLDM_BL.srec -crop 0x20000 0x80000 -E 0x20000 0x20004 -GEN 0x20000 0x20004 -CONSTLE 0xA5A5A5A5 4 -o Data.srec

srec_cat.exe tmp_Bootloader.srec FF91_iLDM_CANFlash.hex -Intel Data.srec -o FF91_iLDM_Production.hex -Intel
del tmp_Bootloader.srec
pause
