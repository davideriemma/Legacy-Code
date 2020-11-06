/*
 * david_o.c
 *
 * Created: 12/06/2018 16:40:24
 * Author : david
 */ 

#include "david_o.h"

static outBuffer out = {{0}, 0, 0, 0, false};

static FILE output = FDEV_SETUP_STREAM(transmit, NULL, _FDEV_SETUP_WRITE);

void david_o_init(void)
{
	stdout = &output;
	return;
}

ISR(USART_UDRE_vect)
{
	if (out.to_send)
	{
		UDR0 = out.Buffer[out.current_char++];
		out.to_send--;
	}
	else
	{
		out.current_char = 0;
		out.owf = false;
		out.taken_space = 0;
		/*out.to_send è già a zero, altrimenti non saremmo arrivati quì!*/
		
		UCSR0B &= ~(1 << UDRIE0);
	}
}

int transmit(char c, FILE * f)
{
	if (out.taken_space == BUFFSIZE)
	{
		out.owf = true;
		return -1;
	}
	
	out.Buffer[out.taken_space] = c;
	out.to_send++;
	
	if (out.taken_space++ == 0)
	{
		UCSR0B |= (1 << UDRIE0);
		sei();
	}
	
	return 0;
}
