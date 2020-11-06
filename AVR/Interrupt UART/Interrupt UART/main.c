#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#define BAUD 9600
#include <util/setbaud.h>
#include <util/delay.h>

#define MAX_BUFFER 250

char * outBuffer;	/*puntatore al buffer*/
unsigned int outBufferDim = 0;

void transmit(char * string);
void serial_init(void);

ISR(USART_TX_vect)
{
	if (*outBuffer)
	{
		UDR0 = *outBuffer++;
		
	}
	else
	{
		UCSR0B &= ~(1 << TXCIE0);
		outBufferDim = 0;
	}
}

int main(void)
{
	serial_init();
	
    while (1) 
    {
		transmit("Mary\n");
		transmit("e Davide!\n");
		_delay_ms(1000);
    }
}

void serial_init(void){
	
	UBRR0L = UBRRL_VALUE;
	UBRR0H = UBRRH_VALUE;
	
	UCSR0C |= (1 << UPM01) | (1 << UCSZ00) | (1 << UCSZ01);
	UCSR0A |= (1 << U2X0);
	UCSR0B |= (1 << TXEN0);
	
	return;
}

void transmit(char * string)
{
	if (!outBufferDim)
	{
		outBuffer = string;
		outBufferDim = strlen(string) + 1;
		UCSR0B |= (1 << TXCIE0);
		UDR0 = *outBuffer++;
		sei();
	} 
	else
	{
		cli();
		outBufferDim += strlen(string) + 1;
		
		if (outBufferDim > MAX_BUFFER)
		{
			return;
		}
		
		char * temp = malloc(outBufferDim);
		
		if (temp)
		{
			strcat(temp, outBuffer);
			strcat(outBuffer, string);
			
		} 
		else
		{
			return;
		}
		
		sei();
	}
	
	return;	
}
