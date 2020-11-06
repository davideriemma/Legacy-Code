;
; Subroutine_Parameters_studium.asm
;
; Created: 16/04/2018 16:44:59
; Author : david
;
;il programma approfondisce lo studio del passaggio di parametri tramite stack
;il programma immagazzina in SRAM i valori presi dallo stack

.cseg
.org 0x000

rjmp reset

reset:
	
	;inizializza lo stack pointer

	ldi r16, low(RAMEND)
	ldi r17, high(RAMEND)

	out SPL, r16
	out SPH, r17

main:

	ldi r16, 0x18
	ldi r17, 0x24

	push r16
	push r17

	call function

	pop r17
	pop r16

loop:	rjmp loop

function:
	
	in YL, SPL
	in YH, SPH

	ldd r18, Y + 3
	ldd r19, Y + 4

	sts data1, r18
	sts data2, r19

	ret

.dseg

data1: .byte 1
data2: .byte 1
