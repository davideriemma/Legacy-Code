.cseg
.org 0x0000

main:
	
	ldi xl, low(charvector)
	ldi xh, high(charvector)

	rjmp initialize_vector

initialize_vector:

	ldi r16, 0x18
	st x+, r16
	ldi r16, 0x06
	st x+, r16
	ldi r16, 0x20
	st x+, r16
	ldi r16, 0xff
	st x+, r16

	rjmp sum

sum:

.def sum_reg = r16
.def temp_reg = r17
.def cmp_temp_reg = r18

	clr xl
	clr xh

	ldi xl, low(charvector)
	ldi xh, high(charvector)	;rewind del puntatore

	ld sum_reg, x+
	ld temp_reg, x+

	add_elements:

		add sum_reg, temp_reg
		ld temp_reg, x+

		ldi cmp_temp_reg, low(charvector) + 5
		
		cp xl, cmp_temp_reg	;se il contatore è arrivato alla fine del vettore (l'inizio più la dimensione - 1)
		breq main	;finito di aggiungere, ritorna al main

		rjmp add_elements


.dseg
.org 0x0040

charvector: .byte 4

 