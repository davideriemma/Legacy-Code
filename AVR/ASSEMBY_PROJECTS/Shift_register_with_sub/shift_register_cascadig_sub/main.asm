;
; shift_register_cascadig_sub.asm
;
; Created: 15/04/2018 12:31:11
; Author : david
;
;il progrmma utilizza il passaggio di parametri tramite stack per mandare 16 bit su due shift register in cascading

.include "..\..\arduino.inc"

.cseg
.org 0x000

	rjmp reset

reset: 

	;inizializza lo stack pointer

	ldi r16, high(RAMEND)
	ldi r17, low(RAMEND)

	out SPL, r17
	out SPH, r16
	
	;imposta come output PORTB
	ldi r16, (1 << data_portout) | (1 << clock_portout) | (1 << latch_portout) | (1 << output_enable)
	out control_register, r16

	;nega r16, così da mettere low tutte le linee di controllo e di data
	neg	r16
	out control_port, r16
	
	;imposta la sleep mode

	ldi r17, (1 << SM1) | (1 << SE)
	out SMCR, r17 


main:

	ldi data_reg, data1
	push data_reg
	call shift_data
	pop data_reg
	ldi data_reg, data2
	push data_reg
	call shift_data
	pop data_reg

	call latch_data

	sleep

shift_data:

	;prende l'indirizzo dello stack pointer, così da poterci muovere con facilità nello stack
	in YL, SPL
	in YH, SPH
	
	;immette il dato nel buffer
	ldd buffer, Y + 3
	;inizializza il counter
	clr counter
	ldi counter, data_size

	;invia il dato nello shift register

loop:
	
	;passa il buffer come parametro
	push buffer
	;chiama la funzione per passare i dati <---
	call shift
	;pulisce lo Stack
	pop buffer
	;shifta il dato nel buffer a sinistra, in maniera da passare al successivo msbit
	lsr buffer
	;decrementa il contatore, che tiene traccia dei bit immessi
	dec counter
	;verifica se è zero
	tst counter
	;se è zero, esce dal loop (vede se il bit Z nello SREG è stato settato da tst)
	brbc 1, loop

	;finito l'invio, si ritorna dalla funzione
	ret
	

;----------------------------------------------routines-------------------------------------------------

shift:
	
	;prende l'indirizzo dello stack pointer, così da poterci muovere con facilità nello stack
	in YL, SPL
	in YH, SPH
	;ricava il buffer dallo stack
	ldd temp, Y + 3
	;esegue il testper vedere se il bit di interesse è 0 1
	sbrc temp, testing_bit
	;mette sul bus controller_shreg il dato
	sbi control_port, data_portout
	;per evitare che, dopo shiftone di shifti anche uno zero, skippo testando-------- è necessario, previo il mal funzionamento dell'algoritmo.
	sbrs temp, testing_bit
	;Se è zero, shifta uno zero
	cbi control_port, data_portout
	;alza il clock (low to high transition)
	sbi control_port, clock_portout
	;aspetta che il segnale sia ricevuto
	nop
	;riabbassa il clock
	cbi control_port, clock_portout
	;ritorna dalla subroutine
	ret

latch_data:

	;alza il latch pin
	sbi control_port, latch_portout
	;aspetta che il segnale sia ricevuto
	nop
	;riabbassa il latch_pin
	cbi control_port, latch_portout
	;ritorna dalla subroutine
	ret

;---------------------------------------------------------------data and constant section----------------------------------------------------------

.def data_reg = r16
.def buffer = r17
.def counter = r18
.def temp = r19

.equ control_register = DDRB
.equ control_port = PORTB
.equ data_portout = PB3
.equ clock_portout = PB1
.equ latch_portout = PB4
.equ output_enable = PB2

.equ data1 = 0x30
.equ data2 = 0x10
.equ data_size = 0x08

.equ testing_bit = 0
