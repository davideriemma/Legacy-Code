;
; reset testing.asm
;
; Created: 23/05/2018 21:37:11
; Author : david
;
;test del pulsante di reset

	.org 0x00
	rjmp reset

reset:
	
	ser r16
	out DDRD, r16
	ldi r16, (1 << COM21) | (1 << COM20)
	com r16
	in r17, TCCR2
	and r17, r16
	out TCCR2, r17
	ldi r16, (1 << PD7)
	out PORTD, r16

	loop: rjmp loop
