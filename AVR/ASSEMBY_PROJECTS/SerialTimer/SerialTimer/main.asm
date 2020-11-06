;
; SerialTimer.asm
;
; Created: 20/05/2018 13:15:34
; Author : david
;
;il seguente studio utilizza il t/c come timer
;le equazioni individuate verficheranno se usare il timer a 8 o a 16 bit
;l'equazione determina che serve un timer a 16 bit

	.org 0x00
	rjmp reset
	.org 0x0016
	rjmp timer1_compA

reset:

	;inizializza lo SP
	ldi r16, low(RAMEND)
	ldi r17, high(RAMEND)
	out SPL, r16
	out SPH, r17

	;inizializza la porta seriale
	ldi r16, low(16)
	ldi r17, high(16)
	sts UBRR0L, r16
	sts UBRR0H, r17
	ldi r16, (1 << UPM00) | (1 << UCSZ01) | (1 << UCSZ00)
	sts UCSR0C, r16
	ldi r16, (1 << TXEN0)
	sts UCSR0B, r16

	;inizializza la sleep mode

	ldi r16, (1 << SE)
	sts SMCR, r16
	
	;inizializza la modalità di timer come CTC
	ldi r16, (1 << WGM12)
	sts TCCR1A, r16
	ldi r16, (1 << CS12)
	sts TCCR1B, r16
	ldi r16, high(31249)
	ldi r17, low(31249)
	ldi r16, (1 << OCIE1A)
	sts TIMSK1, r16
	sts OCR1AH, r16
	sts OCR1AL, r17

	sei
loop: rjmp loop

timer1_compA:
	ldi r16, 'T'
	sts UDR0, r16
	reti