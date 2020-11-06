/*
 * main.asm
 *
 *  Created: 29/04/2018 09:15:33
 *   Author: david
 */ 

 .nolist
 .include "..\mc68008pinDef.inc"
 .list

 .org 0x0000
 rjmp reset
 .org 0x000A
 rjmp as_interrupt

 main:
	;legge l'indirizzo dal bus
	in r16,address_control_port
	;e lo sposta in gpioreg
	out GPIOREG,r16
	;se il primo bit è alzato, allora si sta accedendo alle periferiche
if:	sbic GPIOREG,7
	rjmp else
	;se il primo bit non è alzato, allora si sta accedendo alla eeprom
	;imposta l'indirizzo di lettura della eeprom
	in r16,GPIOREG
	out EEPROM_address_low_reg, r16
	;avvia la lettura del dato
	sbi EEPROM_control_reg, EEPROM_read
	;invia il dato al motorola
	in r16, EEPROM_data_reg
	;invia il dato richiesto
	push r16
	call write
	pop r16

	;chiama l'array di funzioni all'offset indicato dalle ultime 3 cifre

else:

continue:

	sleep

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
	ldi r16, (1 << sleep_enable) | (1 << sleep_bit_1)
	out sleep_mode_reg, r16

	;abilito gli interrupt
	sei
	;metto in idle la cpu
	sleep

 write:

 	;salva i registri che dovrà usare
	push r17
	;imposta le linee dati come output
	ser r17
	out data_ddr, r17
	;ottiene il dato dallo stack
	in YL,SPL
	in YH,SPH

	ldd	r17, Y + 4
	;aspetta che il dato sulle linee sia valido
wait:
	sbic data_control_pin, _DS_
	rjmp wait
	;invia il dato
	out data_port,r17
	;conferma il dato
	cbi data_control_port, _DTACK_
wait_2:
	;aspetta che il dato sia stato ricevuto (aspetta che AS diventi high)
	sbic data_control_pin, _AS_
	rjmp wait_2
	;rimuove il dato dal bus
	clr r17
	out data_port, r17
	;nega dtack
	sbi data_control_port, _DTACK_
	;la scrittura del dato è ultimata
	;ripristino dei registri
	pop r17
	ret

as_interrupt:
	
	;verifica se il bit _AS_ è low
	;se lo è, salta al main
	lds r16, as_interrupt_mask
	sbrc r16,(1 << _AS_)
	call main
	sleep

	
