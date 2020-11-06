/*
 * printf_studium.c
 *
 * Created: 09/06/2018 22:18:52
 * Author : david
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#define BAUD 9600
#include <util/setbaud.h>
#include <avr/pgmspace.h>
#include <stdio.h>

void init_uart();	//non generica, solo per lo studio

static int transmit(char data, FILE * file);
static int receive(FILE * data);

int main(){
	
	init_uart();
	
	static FILE out = FDEV_SETUP_STREAM(transmit, receive, _FDEV_SETUP_RW);
	
	stdin = &out;
	stdout = &out;
	
	int a;
	
	while(1)
	{
		printf_P(PSTR("Ciao, immetti un numero! -> "));
		scanf("%d", &a);
		printf_P(PSTR("Hai immesso %i!\n"), a);		
	}
		
	return 0;
}

void init_uart()
{
	UBRR0L = UBRRL_VALUE;
	UBRR0H = UBRRH_VALUE;
	
	UCSR0C |= (1 << UPM01) | (1 << UCSZ00) | (1 << UCSZ01);
	UCSR0A |= (1 << U2X0);
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
	
	return;
}

static int transmit(char data, FILE * file){
	
	if (data == '\n')
	{
		transmit('\r', file);
	}
	
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = data;
	
	return 0;
}

static int receive(FILE * data)
{
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}
