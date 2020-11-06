;
; vettore di funzioni.asm
;
; Created: 02/05/2018 11:43:36
; Author : david
;
;studio sulla chiamata di funzioni in un vettore

.cseg
main:

	ldi r16,low(RAMEND)
	ldi r17,high(RAMEND)

	out SPL, r16
	out SPH, r17

function:

	ldi r16,0x18

	ret

function_1:

	ldi r17, 0x19

	ret

.cseg
vector: .dw function, function_1