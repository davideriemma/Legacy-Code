;
; testAtm.asm
;
; Created: 01/06/2018 14:35:40
; Author : david
;


; Replace with your application code
start:

	sbi DDRD, PD5
	ldi r16, (1 << COM1A0)
	out TCCR1A, r16
	ldi r16, (1 << WGM12) | (1 << CS11) | (1 << CS10)
	out TCCR1B, r16
	ldi r16, high(15624)
	ldi r17, low(15624)
	out OCR1AH, r16
	out OCR1AL, r17

loop: rjmp loop