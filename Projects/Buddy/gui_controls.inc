;------------------------------------------------------------------------------;
;  Controls.inc                                                                ;
;  Contains control graphic/drawing data                                       ;
;------------------------------------------------------------------------------;


; Controls
ButtonActiveLeftInfo:
defw ButtonActiveLeft
defb 1, 14, 0
ButtonActiveMiddleInfo:
defw ButtonActiveMiddle
defb 1, 14, 0
ButtonActiveRightInfo:
defw ButtonActiveRight
defb 1, 14, 0
ButtonLeftInfo:
defw ButtonLeft
defb 1, 14, 0
ButtonMiddleInfo:
defw ButtonMiddle
defb 1, 14, 0
ButtonRightInfo:
defw ButtonRight
defb 1, 14, 0
CheckboxCheckedInfo:
defw CheckboxChecked
defb 1, 7, 0
CheckboxUncheckedInfo:
defw CheckboxUnchecked
defb 1, 7, 0
RadioCheckedInfo:
defw RadioChecked
defb 1, 7, 0
RadioUncheckedInfo:
defw RadioUnchecked
defb 1, 7, 0


ButtonActiveLeft:
DEFB $01
DEFB $02
DEFB $04
DEFB $05
DEFB $05
DEFB $05
DEFB $05
DEFB $05
DEFB $05
DEFB $05
DEFB $05
DEFB $04
DEFB $02
DEFB $01

ButtonActiveMiddle:
DEFB $FF
DEFB $00
DEFB $FF
DEFB $00
DEFB $00
DEFB $00
DEFB $00
DEFB $00
DEFB $00
DEFB $00
DEFB $00
DEFB $FF
DEFB $00
DEFB $FF

ButtonActiveRight:
DEFB $80
DEFB $40
DEFB $20
DEFB $A0
DEFB $A0
DEFB $A0
DEFB $A0
DEFB $A0
DEFB $A0
DEFB $A0
DEFB $A0
DEFB $20
DEFB $40
DEFB $80

ButtonLeft:
DEFB $00
DEFB $00
DEFB $00
DEFB $01
DEFB $01
DEFB $01
DEFB $01
DEFB $01
DEFB $01
DEFB $01
DEFB $01
DEFB $00
DEFB $00
DEFB $00

ButtonMiddle:
DEFB $00
DEFB $00
DEFB $FF
DEFB $00
DEFB $00
DEFB $00
DEFB $00
DEFB $00
DEFB $00
DEFB $00
DEFB $00
DEFB $FF
DEFB $00
DEFB $00
DEFB $00

ButtonRight:
DEFB $00
DEFB $00
DEFB $00
DEFB $80
DEFB $80
DEFB $80
DEFB $80
DEFB $80
DEFB $80
DEFB $80
DEFB $80
DEFB $00
DEFB $00
DEFB $00
DEFB $00

CheckboxChecked:
DEFB $FE
DEFB $82
DEFB $86
DEFB $8A
DEFB $D2
DEFB $A2
DEFB $FE

CheckboxUnchecked:
DEFB $FE
DEFB $82
DEFB $82
DEFB $82
DEFB $82
DEFB $82
DEFB $FE

RadioChecked:
DEFB $38
DEFB $44
DEFB $BA
DEFB $BA
DEFB $BA
DEFB $44
DEFB $38

RadioUnchecked:
DEFB $38
DEFB $44
DEFB $82
DEFB $82
DEFB $82
DEFB $44
DEFB $38

