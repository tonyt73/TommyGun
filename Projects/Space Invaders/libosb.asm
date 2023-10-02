;---------------------------------------------------------------;
;                                                               ;
;  OSB.ASM                                                      ;
;                                                               ;
;  This file includes the definition of an off screen buffer    ;
;                                                               ;
;---------------------------------------------------------------;

USE_OSB     equ     0                   ; Compile flag: Use Off Screen Buffer

IF USE_OSB
MemScr:     defs 5632                   ; off screen memory aligned to 4 byte boundary
MemAttr:    defs 705
ENDIF ; USE_OSB
