/*
 * david_o_m32A_prova.c
 *
 * Created: 12/06/2018 18:37:13
 * Author : david
 */ 

#include <avr/io.h>
#include "../../libs/david_o_m32/david_o_m32/david_o.h"
#define F_CPU 1000000
#define BAUD 9600
#include <util/delay.h>
#include <util/setbaud.h>

void serial_init(void);

int main(void)
{
    david_o_init();
	serial_init();
	
    while (1) 
    {
		printf("CIAO!!\nLow level buffering executing shalalalala maria ti amoaaaakadhfdsjahfadshl afdjcfashdfshjadshfkjadhhadfkslaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\nghghghjgjghjg\niscliscliscliscliscliscliscliscliscliscliscl\n");
		_delay_ms(1000);
    }
}

void serial_init(void){
	
	UBRRL = UBRRL_VALUE;
	UCSRC &= ~(1 << URSEL);
	UBRRH = UBRRH_VALUE;
	
	UCSRC |= (1 << URSEL) | (1 << UPM1) | (1 << UCSZ0) | (1 << UCSZ1);
	UCSRA |= (1 << U2X);
	UCSRB |= (1 << TXEN);
	
	return;
}
