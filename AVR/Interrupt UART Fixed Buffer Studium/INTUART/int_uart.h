/*
 * int_uart.h
 *
 * Created: 12/06/2018 10:52:23
 *  Author: david
 */ 

//do not redefine ISR USART_TX_vect
//the buffer size shall be defined before using 

#ifndef INT_UART_H_
#define INT_UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdbool.h>

#ifndef BUFFSIZE

#warning "No Output Buffer Size defined, using default."
#define BUFFSIZE 100

#endif

typedef struct
{
	char Buffer[BUFFSIZE];
	size_t currentChar;
	size_t taken_space;
	bool owf;
	
} outBuffer;


#endif /* INT_UART_H_ */