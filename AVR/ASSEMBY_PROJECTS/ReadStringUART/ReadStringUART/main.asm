;
; ReadStringUART.asm
;
; Created: 14/05/2018 18:03:46
; Author : david
;
;il programma immagazzina le stringhe ricevute in una coda nella ram

	.org 0x000
	rjmp reset
	.org 0x024
	call receive
	.org 0x028
	call transmit

reset:
	
	;settaggio del baud rate
	lds r0, low(ubrr)
	lds r1, high(ubrr)

	sts UBRR0L, r0
	sts UBRR0H, r1

	lds r0, (1 << UPM01) | (1 << UCSZ01) | (1 << UCSZ00) 
	sts UCSR0C, r0
	lds r0, (1 << TXCIE0) | (1 << RXCIE0) | (1 << TXEN0) | (1 << RXEN0)
	sts UCSR0B, r0

	ldi ZL, low(string * 2)
	ldi ZH, high(string * 2)

	ldi

	lpm r0,Z+
	sei
	sts UDRR0, r0

loop rjmp loop

transmit:
	
	cli
	push r0
	lpm r0, Z+
	tst r0
	brne else_1
	rjmp continue_1
else_1:
	sts UDRR0, r0
continue_1:
	pop r0
	reti

receive:

	cli
	lds r0, UDRR0
	st 
	reti

	.cseg

string: .db "ATMEGA READY TO RECEIVE INSTRUCTIONS:",'\n'

	.dseg 

buffer: .byte 100

.equ ubrr = 103