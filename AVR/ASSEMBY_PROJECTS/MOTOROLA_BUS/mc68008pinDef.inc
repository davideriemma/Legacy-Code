/*
 * mc68008pinDef.inc
 *
 *  Created: 29/04/2018 06:42:18
 *   Author: david
 */ 

 ;IL FILE CONTIENE ALIAS PER I PIN AI QUALI SONO COLLEGATI I SEGNALI

 .include "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\avrasm\inc\m328pdef.inc"

 ;pin per il bus di  controllo dati

.equ data_control_ddr = DDRC
.equ data_control_port = PORTC
.equ data_control_pin = PINC

.equ _AS_ =	PC0
.equ RW_ = PC1
.equ _DTACK_ = PC3
.equ _DS_ = PC2

;pin per il bus indirizzi

.equ address_control_ddr =	DDRD
.equ address_control_port = PORTD
.equ address_control_pin = PIND

;registro di buffer per l'indirizzo

.equ GPIOREG = 0x1E	;GPIOR0

;pin per il bus dati

.equ data_ddr = DDRB
.equ data_port = PORTB
.equ data_pin = PINB

;pin per il controllo dell'interrupt di waking su _AS_

.equ as_interrupt_reg = PCICR
.equ as_interrupt_flag_reg = PCIFR
.equ as_interrupt_mask = PCMSK2

.equ as_mode_bit_2 = PCIE2
.equ as_mode_bit_1 = PCIE1
.equ as_mode_bit_0 = PCIE0

;alias per il controllo della modalità di risparmio energetico

.equ sleep_mode_reg = SMCR
.equ sleep_enable_reg = SMCR

.equ sleep_enable = SE

.equ sleep_bit_0 = SM0
.equ sleep_bit_1 = SM1
.equ sleep_bit_2 = SM2

;alias per il controllo della eeprom

.equ EEPROM_address_low_reg = EEARL
.equ EEPROM_address_high_reg = EEARH
.equ EEPROM_control_reg = EECR
.equ EEPROM_read = EERE
.equ EEPROM_data_reg = EEDR
