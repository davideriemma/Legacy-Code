.nolist
#inclue <avr/io.h>
.list
.global USART_TX_vect

#define __SFR_OFFSET 0

USART_TX_vect:
	
	push YL
	push YH
	push r16

	ldi YL, 0x19
	ldi YH, 0x01
	tst r16
	breq exit

	out UDR0, r16

exit:
	
	pop r16
	pop YH
	pop YL
	reti
