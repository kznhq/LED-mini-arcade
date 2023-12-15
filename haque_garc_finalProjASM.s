.include "xc.inc"

.text                       ;BP (put the following data in ROM(program memory))

; This is a library, thus it can *not* contain a _main function: the C file will
; define main().  However, we will need a .global statement to make available ASM
; functions to C code.
; All functions utilized outside of this file will need to have a leading 
; underscore (_) and be included in a comment delimited list below.
.global  _write_0, _write_1, _haque_garc_delay_1ms

_write_0:    ;7 cycles high, 13 cycles low
    inc LATA
    repeat #4
    nop
    clr LATA
    repeat #5
    nop
    return
    
_write_1:	;10 cycles high, 10 cycles low
    inc LATA
    repeat #7
    nop
    clr LATA
    repeat #2
    nop
    return  

_haque_garc_delay_1ms:
    repeat #15993
    nop
    return