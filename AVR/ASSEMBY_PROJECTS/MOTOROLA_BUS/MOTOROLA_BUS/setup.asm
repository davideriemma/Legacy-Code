;
; MOTOROLA_BUS.asm
;
; Created: 17/04/2018 13:36:42
; Author : david
;
;CONTROLLER DEL BUS PER IL MOTOROLA 68000

.nolist
.include "..\mc68008pinDef.inc"
.list

.org 0x000

rjmp reset

.org 0x000A

rjmp as_interrupt

reset:	
	
	;inizializza lo stack pointer
	ldi r16, low(RAMEND)
	ldi r17, high(RAMEND)
	out SPL, r16
	out SPH, r17

	;inizializza i registri del bus indirizzi
	;imposta tutti i bit a 0
	clr r16
	;per impostare address_control_ddr come input
	out address_control_ddr, r16
	;ci si assicura che le resistenze di pull-up non siano attive
	out address_control_port, r16

	;inizializza i registri del bus controlli
	;il registro r16 è già impostato a 0, quindi imposto come output DTACK
	ldi r16, (1 << _DTACK_)
	out data_control_ddr, r16
	;imposto le resistende di pullup per i pin in imput e alzo DATCK
	;nego r16
	com r16
	;e lo metto in data control port: le necessarie resistenze di pullup sono attive e DTACK è high.
	out data_control_port, r16

	;inizializzo l'interrupt per avviare il controller all'attivazione di _AS_
	;imposta l'interrupt triggered sul 3° banco di pin
	ldi r16, (1 << as_mode_bit_2)
	sts as_interrupt_reg, r16

	;inizializzo la modalità di sleep del mcu

	;imposto la modalità di idle
	clr r16
	ldi r16, (1 << sleep_enable)
	out sleep_mode_reg, r16

	;abilito gli interrupt
	sei
	;metto in idle la cpu
	sleep

as_interrupt:
	
	;verifica se il bit _AS_ è low
	;se lo è, salta al main
	lds r16, as_interrupt_mask
	sbrc r16,(1 << _AS_)
;	call main
	sleep
	