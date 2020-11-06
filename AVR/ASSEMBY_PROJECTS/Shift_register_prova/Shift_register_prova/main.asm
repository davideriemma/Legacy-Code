;
; Shift_register_prova.asm
;
; Created: 14/04/2018 15:48:36
; Author : david
;

;prova per il funzionamento corretto dell'algoritmo di shift register

;il programma utilizza DDRC come control register

;il programma non gestisce master reclear

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

	clr counter

main:

	;immette il dato nel buffer

	ldi buffer, data
	ldi counter, data_size

	;invia il dato nello shift register

loop:
	
	;verifica se il bit corrente (MSB) è 1 o 0
	sbrc buffer, 0
	;se non è zero, quindi 1, shifta un 1
	call shift_one
	;per evitare che, dopo shiftone di shifti anche uno zero, skippo testando
	sbrs buffer, 0
	;Se è zero, shifta uno zero
	call shift_zero
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
	rjmp main	;fine dei giochi

;----------------------------------------------routines-------------------------------------------------

shift_one:
	
	;mette sul bus controller_shreg il dato
	sbi control_port, data_portout
	;alza il clock (low to high transition)
	sbi control_port, clock_portout
	;aspetta che il segnale sia ricevuto
	nop
	;riabbassa il clock
	cbi control_port, clock_portout
	;ritorna dalla subroutine
	ret

shift_zero:

	;mette sul bus controller_shreg il dato
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

.def buffer = r16
.def counter = r17

/*.equ control_register = DDRC
.equ control_port = PORTC
.equ data_portout = A1
.equ clock_portout = A2
.equ latch_portout = A3
.equ output_enable = A4*/

.equ control_register = DDRB
.equ control_port = PORTB
.equ data_portout = PB4
.equ clock_portout = PB1
.equ latch_portout = PB2
.equ output_enable = PB3

.equ data = 0xF0
.equ data_size = 0x08


