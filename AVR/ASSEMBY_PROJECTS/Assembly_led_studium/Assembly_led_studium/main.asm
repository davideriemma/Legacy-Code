.dseg
.org 0x0040

var1 : .byte 2

.cseg
.org 0000

initVar:

	ldi r16, 0x18	;immagazina nel registro il valore di sopra salvare
	ldi r17, 0x13	;immagazzina nel registro il valore di sotto da salvare
	ldi Xl, low(var1)	;immagazzina l'indirizzo nel lsbyte del registro X
	ldi Xh, high(var1)	;immagazzina l'indirizzo della parte di sopra

	st X+, r16	;immagazzina in var il valore di r16
	st X, r17	;immagazzina il var il valore di r17
	

start:

	ldi XL, 0x40
	ld r16, X+	;legge il valore del primo elemento di var1
	ld r17, X

rjmp start
