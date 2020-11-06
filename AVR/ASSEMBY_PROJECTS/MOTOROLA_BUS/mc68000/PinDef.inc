;
;
;IL FILE CONTIENE ALIAS PER I PIN AI QUALI SONO COLLEGATI I SEGNALI

;pin per il bus di  controllo dati

.equ data_control_ddr = DDRD
.equ data_control_port = PORTD
.equ data_control_pin = PIND

.equ _AS_ = PD2
.equ RW_ = PD3
.equ _DTACK_ = PD4
.equ _UDS_ = PD5
.equ _LDS_ = PD6

;pin per il bus indirizzi

.equ address_control_ddr = DDRB
.equ address_control_port = PORTB
.equ address_control_pin = PINB

;pin per il controllo degli shift registers di output dei dati

.equ shreg_control_register = DDRC
.equ shreg_control_port = PORTC

.equ shreg_data = PC0
.equ shreg_clock = PC3
.equ shreg_latch= PC2
.equ shreg_output_enable = PC1
.equ shreg_master_reclear = PC4

.equ shreg_data_size = 0x08

.equ shreg_testing_bit = 7

;pin per il controllo dell'interrupt di waking su _AS_

.equ as_interrupt_mode_reg = EICRA
.equ as_interrupt_mode_reg_addr = 0x69
.equ as_interrupt_enable_reg = EIMSK
.equ as_interrupt_flag_reg = EIFR

.equ as_mode_bit_0 = ISC10
.equ as_mode_bit_1 = ISC11

.equ as_interrupt_en_bit_1 = INT1

;alias per il controllo della modalità di risparmio energetico

.equ sleep_mode_reg = SMCR
.equ sleep_enable_reg = SMCR

.equ sleep_enable = SE

.equ sleep_bit_0 = SM0
.equ sleep_bit_1 = SM1
.equ sleep_bit_2 = SM2
