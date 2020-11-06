
.cseg
.org 0x000

rjmp reset_handler

.org 0x001

rjmp int0_handler

reset_handler:

	sbi EIMSK, INT0	;abilita l'interrupt del pulsante
	ldi r16, 0x03
	out EICRA, r16	;le due istruzioni settano il modo dell'interrupt a "rising edge"

	sbi DDRA, PORTA5	;imposta il led come output
	clr r18
	out PORTA, r18

	ldi r16, 0x02
	out SMCR, r16	;abilita power down mode

	sei ;abilita gli interrupt

	rjmp main

int0_handler:

	cli

	ldi r16, (1 << PORTA5)
	in r17, PORTA
	eor r16, r17
	out PORTA, r16

	sei

.org 0x014

main:

	sleep

	rjmp main
