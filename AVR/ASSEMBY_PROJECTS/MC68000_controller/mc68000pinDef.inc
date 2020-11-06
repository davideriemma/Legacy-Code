;il seguente file contiene alias per i nomi dei pin ai quali sono collegati i segnali indicati

 .include "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\avrasm\inc\m32def.inc"

 ;pin per il bus di  controllo dati

.equ data_control_ddr = DDRB	
.equ data_control_port = PORTB
.equ data_control_pin = PINB

.equ _AS_ =	PB2
.equ RW_ = PB3
.equ _DTACK_ = PB4
.equ _UDS_ = PB0
.equ _LDS_ = PB1
.equ LED = PB6
.equ PHEN = PB5

;pin per il bus indirizzi

.equ address_ddr = DDRD
.equ address_port= PORTD
.equ address_pin = PIND

;pin per il bus dati

.equ upper_data_ddr = DDRC
.equ upper_data_port = PORTC
.equ upper_data_pin = PINC

.equ lower_data_ddr = DDRA
.equ lower_data_port = PORTA
.equ lower_data_pin = PINA

;buffer per l'indirizzo

.equ GPIOREG = RAMEND

;pin per il controllo dell'interrupt di waking su _AS_

.equ as_interrupt_reg = MCUCSR
.equ as_interrupt_enable = GICR
.equ as_interrupt_mask = GIFR

.equ as_int_en = INT2
.equ as_mode_bit = ISC2	;va settato a 0, dimodochè un falling edge gneri un interrupt

;alias per il controllo della modalità di risparmio energetico

.equ sleep_mode_reg = MCUCR
.equ sleep_enable_reg = MCUCR

.equ sleep_enable = SE

.equ sleep_bit_0 = SM0
.equ sleep_bit_1 = SM1
.equ sleep_bit_2 = SM2

;alias per il controllo della eeprom

.equ EEPROM_address_low_reg = EEARL
.equ EEPROM_address_high_reg = EEARH
.equ EEPROM_control_reg = EECR
.equ EEPROM_read_bit = EERE
.equ EEPROM_write_enable = EEMWE
.equ EEPROM_write_bit = EEWE
.equ EEPROM_data_reg = EEDR

