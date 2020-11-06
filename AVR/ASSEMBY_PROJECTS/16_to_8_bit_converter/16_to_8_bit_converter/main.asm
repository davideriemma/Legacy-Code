;
; 16_to_8_bit_converter.asm
;
; Created: 10/05/2018 22:43:04
; Author : david
;
;il seguente codice è firmware di un convertitore di un bus a 16 bit ad uno ad 8 bit (2 byte in sequenza)

	.org 0x000
	rjmp reset

reset:
	
	ldi r16, low(ramend)
	ldi r17, high(ramend)
	out SPL,r16
	out SPH,r17

	ldi r16, (1 << _USD_) | (1 << _LDS_) | (1 << _RD_) | (1 << _WR_)
	out DDRD, r16	;0 0 1 1 1 1
	;disattivo le resistenze di pullup per UDS e LDS e alzo DTACK e STATUS
	neg r16	;1 1 0 0 0 0
	;attivo le resistenze di pullup per rd e wr
	ori r16, (1 << _RD_) | (1 << _WR_)	;1 1 1 1 0 0
	out PORTB,r16

main:

while:	in r16,PINB
		andi r16, (1 << _RD_)
		breq rd_low
		in r16,PINB
		andi r16, (1 << _WR_)
		breq wr_low

		;da mgliorare.

.equ _DTACK_ = PB5
.equ _STATUS_ = PB4
.equ _RD_ = PB2
.equ _WR_ = PB3
.equ _UDS_ = PB0
.equ _LDS_ = PB1
