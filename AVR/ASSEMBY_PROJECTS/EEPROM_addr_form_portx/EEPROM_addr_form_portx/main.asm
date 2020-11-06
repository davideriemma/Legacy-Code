;
; EEPROM_addr_form_portx.asm
;
; Created: 10/04/2018 19:55:08
; Author : david
;
;il programma legge un indirizzo parallelo su PORTD e lo immagazzina nella memoria SRAM

;si suppone il segnale AS già acquisito e il R/W impostato su R

.cseg
.org 0x000

rjmp reset

reset:
	
	;imposto entrambi i registri come input
	clr r16
	out address_reg, r16
	out control_reg, r16

;adesso sposto l'indirizzo ricevuto i PIND in EEARL

in r16, address_portin
out EEPROM_address_low_reg, r16

;e abilito la lettura

sbi EEPROM_control_reg, EEPROM_read

;sposto poi il dato nella ram

in r16, EEPROM_data_reg
sts data, r16

.dseg

data: .byte 1	;risultato della lettura in SRAM

.equ address_portin = PIND
.equ address_reg = DDRD

.equ control_reg = DDRC
.equ control_pin = PINC
.equ UDS = PC2
.equ LWDS = PC3
.equ EEPROM_address_low_reg = EEARL
.equ EEPROM_control_reg = EECR
.equ EEPROM_read = EERE
.equ EEPROM_data_reg = EEDR
