;
; Stack_parameters_studium.asm
;
; Created: 15/04/2018 11:27:12
; Author : david
;
;il programma mostra come utilizzare lo stack per passare parametri alle subroutines
;la subroutines riceve due numeri e li somma

.cseg
.org 0x000	
	
	rjmp reset

reset:
	
	;si inizializza lo stack pointer

	ldi r16, low(RAMEND)
	ldi r17, high(RAMEND)

	out SPL, r16
	out SPH, r17

	;setta lo sleep del processore a power down

	ldi r18, (1 << SM1) | (1 << SE)
	out SMCR, r18

main:	
	
	;spostamento dei parametri nei registri
	ldi r16, 0x18
	ldi r17, 0x18

	;spostamento dei registri nello stack
	push r16
	push r17

	rcall sum
	;toglie i dati dallo stack
	pop r17
	pop r16
	sleep

sum:
	
	;ottiene il primo operando
	in	YL, SPL
	in	YH, SPH
	ldd r18, Y + 4
	;ottiene il secondo operando immesso
	ldd r19, Y + 3
	;esegue la somma	
	add r18, r19
	;conserva il dato in memoria
	sts data, r18

	ret

.dseg

data:	.byte 2
