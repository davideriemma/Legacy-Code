/*
 * david_o test.c
 *
 * Created: 12/06/2018 16:47:59
 * Author : david
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#define BAUD 9600
#include <util/setbaud.h>
#include <util/delay.h>
#include "../../libs/david_o/david_o.h"

void serial_init(void);

int main(void)
{
    david_o_init();
	serial_init();
	printf("Welcome to David_o Library!\n");
    while (1) 
    {
		printf("Maria ti amo!\n");
		_delay_ms(1000);
    }
}


void serial_init(void)
{
	UBRR0L = UBRRL_VALUE;
	UBRR0H = UBRRH_VALUE;
	
	UCSR0A |= (1 << U2X0);
	UCSR0C |= (1 << UPM01) | (1 << UCSZ00) | (1 << UCSZ01);
	UCSR0B |= (1 << TXEN0);
	
	return;
}
