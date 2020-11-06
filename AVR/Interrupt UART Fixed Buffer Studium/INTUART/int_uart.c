/*
 * INTUART.c
 *
 * Created: 12/06/2018 10:51:47
 * Author : david
 */ 

#include "int_uart.h"

outBuffer out = {{0}, 0, 0, false};

ISR(USART_TX_vect)
{
	if (out.Buffer[out.currentChar])
	{
		UDR0 = out.Buffer[out.currentChar++];
	}
	else   /*siamo giunti al carattere nullo di terminazione*/
	{
		out.currentChar = 0;
		out.taken_space = 0;
		out.owf = false;
		UCSR0B &= ~(1 << TXCIE0);
	}
}

void transmit(char * string)
{
	if (!out.currentChar)
	{
		strncpy(out.Buffer, string, BUFFSIZE);
		
		if(strlen(string) + 1 > BUFFSIZE)	/*se si verifica overflow fin dalla prima stringa, lo handla*/
		{
			out.taken_space = BUFFSIZE;
			out.owf = true;
			out.Buffer[BUFFSIZE - 2] = '\n';
			out.Buffer[BUFFSIZE - 3] = '\r';	/*aggiunti per permettere la comunicazione con i terminali, che si aspettano la sequenza \r \n*/
			out.Buffer[BUFFSIZE - 1] = 0;	/*appende il null terminating char per far si che il buffer venga svuotato appena finisce l'invio della stringa*/
		}
		
		else
		{
			out.taken_space = strlen(string) + 1; /*il +1 è il null char*/	
		}
		
		UCSR0B |= (1 << TXCIE0);
		UDR0 = out.Buffer[out.currentChar++];
		sei();
	}
	else	/*handle overflow -> mi basta fare tutto come strNcat limitandolo alla dimensione restante del buffer :/*/
	{
		strncat(out.Buffer, string, BUFFSIZE - out.taken_space);
		
		if (strlen(string) + out.taken_space > BUFFSIZE)	//lo spazio out.tknspc è gia comprensivo del carattere nullo che sarà sovrascritto
		{
			out.owf = true;
			out.taken_space = BUFFSIZE;
			out.Buffer[BUFFSIZE - 1] = 0;	/*appende il null terminating char per far si che il buffer venga svuotato appena finisce l'invio della stringa*/
		}
		else
		{
			out.owf = false;
			out.taken_space += strlen(string) + 1;
		}
	}
}
