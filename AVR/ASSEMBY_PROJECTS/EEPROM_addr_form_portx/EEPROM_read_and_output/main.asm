;
; EEPROM_read_and_output.asm
;
; Created: 10/04/2018 20:24:22
; Author : david
;
;il programma legge l'indirizzo parallelo da PIND e scrive il risutato in parallelo su PINB

.cseg
.org 0x000

	rjmp reset

reset:
	
	;imposta come input DDRD e DDRC

	clr r16
	out address_reg, r16
	
	;e come output DDRB

	ser r16
	out data_reg, r16

start:

	;legge gli indirizzi da PIND e lo mette in EEARL
	in r16, address_portin
	out EEPROM_address_low_reg, r16

	;avvia la lettura del dato

	sbi EEPROM_control_reg, EEPROM_read

	;sposta il dato in EEDR sul bus (spostandolo in PORTB)
	
	in r16, EEPROM_data_reg
	out data_portout, r16

	;esegue poi la routine endcycle [...]

.equ address_portin = PIND
.equ address_reg = DDRD

.equ data_portout = PORTB
.equ data_reg = DDRB

.equ EEPROM_address_low_reg = EEARL
.equ EEPROM_control_reg = EECR
.equ EEPROM_read = EERE
.equ EEPROM_data_reg = EEDR
