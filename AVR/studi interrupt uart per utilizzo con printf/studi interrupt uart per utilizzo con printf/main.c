/*
 * studi interrupt uart per utilizzo con printf.c
 *
 * Created: 12/06/2018 14:33:11
 * Author : david
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#define BAUD 9600
#include <util/setbaud.h>
#include <util/delay.h>

#define BUFFSIZE 500

typedef struct  
{
	char Buffer[BUFFSIZE];	/*buffer di immagazzinamento caratteri*/
	size_t taken_space;	/*spazio occupato*/
	size_t current_char;	/*indice del carattere correntemente sottoposto ad invio*/
	size_t to_send;		/*caratteri da inviare*/
	bool owf;	/*segnalatore di overflow*/
	
}outBuffer;

static outBuffer out = {{0}, 0, 0, 0, false};
	
int transmit(char c, FILE * f);
void serial_init(void);

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

int main(void)
{
	serial_init();
    
	static FILE output = FDEV_SETUP_STREAM(transmit, NULL, _FDEV_SETUP_WRITE);
	stdout = &output;
	
    while (1) 
    {
		printf("Maria %s\n", "Ti amo Tanto");
		_delay_ms(1000);
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

void serial_init(void){
	
	UBRR0L = UBRRL_VALUE;
	UBRR0H = UBRRH_VALUE;
	
	UCSR0C |= (1 << UPM01) | (1 << UCSZ00) | (1 << UCSZ01);
	UCSR0A |= (1 << U2X0);
	UCSR0B |= (1 << TXEN0);
	
	return;
}
