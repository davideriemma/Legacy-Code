;
; leggere PINx quando DDRx è input.asm
;
; Created: 11/05/2018 15:48:28
; Author : david
;
;il porgramma verifica se è possibile leggere correttamente PINx se DDRx è impostato come output

start:
    ser r16
	out DDRB,r16
	in r17,PINB
