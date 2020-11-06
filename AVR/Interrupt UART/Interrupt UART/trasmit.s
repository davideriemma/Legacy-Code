
.global USART_TX_vect
.extern outBuffer
.extern outBufferDim

USART_TX_vect:
	
	push r16
	push r17
	ld r16, outBuffer
	ld r17, outBufferDim
	tst r16
	breq else

	out r16, UDR0
	dec r17
	;decrementa il numero di caratteri rimanenti
	;incrementa l'indirizzo

	rjmp exit
else:
	;disabilita l'interrupt di invio
	;ritorna

exit:
	
	pop r16
	reti
