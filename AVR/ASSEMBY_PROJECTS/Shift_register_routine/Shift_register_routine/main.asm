;
; Shift_register_with_sub.asm
;
; Created: 15/04/2018 11:53:19
; Author : david
;
;il programma esegue la routine di shifting utilizzando lo stack per passare i valori, risparmiando scrittura di codice
;il programma è scritto per uno shreg che viene impostato msb4321 lsb4321, qundi non per il motorola

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
	
	;imposta come output DDRB
	ldi r16, (1 << data_portout) | (1 << clock_portout) | (1 << latch_portout) | (1 << output_enable)
	out control_register, r16

	;nega r16, così da mettere low tutte le linee di controllo e di data
	com	r16
	out control_port, r16

	clr counter

main:

	;immette il dato nel buffer

	ldi buffer, data
	ldi counter, data_size

	;invia il dato nello shift register

loop:
	
	;passa il buffer come parametro
	push buffer
	;chiama la funzione per shiftare i dati <---
	call shift_data
	pop buffer
	;shifta il dato nel buffer a sinistra, in maniera da passare al successivo msbit
	lsr buffer
	;decrementa il contatore, che tiene traccia dei bit immessi
	dec counter
	;verifica se è zero
	tst counter
	;se è zero, esce dal loop (vede se il bit Z nello SREG è stato settato da tst)
	brbc 1, loop

	;finito l'invio, si procede all'output
	call latch_data
	;fine dei giochi

;----------------------------------------------routines-------------------------------------------------

shift_data:
	
	in YL, SPL
	in YH, SPH

	ldd temp, Y + 3

	;esegue il test per vedere se il bit di interesse è 0 1
	sbrc temp, testing_bit
	;mette sul bus controller_shreg il dato
	sbi control_port, data_portout
	;se il dato è zero, manda semplicemente un colpo di clock, in quanto il pin data è di defautl tenuto a massa	
	;alza il clock (low to high transition)
	sbi control_port, clock_portout
	;aspetta che il segnale sia ricevuto
	nop
	;riabbassa il clock
	cbi control_port, clock_portout
	;resetta la condizione del pin DATA a quella di default (a massa)
	cbi control_port, data_portout
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

.def buffer = r16
.def counter = r17
.def temp = r18

.equ control_register = DDRB
.equ control_port = PORTB
.equ data_portout = PB4
.equ clock_portout = PB1
.equ latch_portout = PB2
.equ output_enable = PB3

.equ data = 0xFF
.equ data_size = 0x08

.equ testing_bit = 0

