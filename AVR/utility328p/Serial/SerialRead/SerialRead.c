/*
 * SerialRead.c
 *
 * Created: 27/02/2018 10:47:25
 *  Author: davide
 */ 

#include "../SerialPrint/serialPrint.h"
#include "SerialRead.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

uint8_t receiveByte(void) {
	loop_until_bit_is_set(UCSR0A, RXC0);       /* Wait for incoming data */
	return UDR0;                                /* return register value */
}

char * readString(void){
	
	static const char message[] PROGMEM = "No Memory available\n";;
	
	char * string = (char * ) malloc(MAX_LINE_LENGTH * sizeof(char));
	
	if(string == NULL){
		
		printStringfromPgmem(message);
		return NULL;
	}
	
	char byte;

	int i = 0;

	while((byte = receiveByte()) != '\n' && i < MAX_LINE_LENGTH){

		string = realloc(string, sizeof(string) + 1);
		
		if (string == NULL)
		{
			printStringfromPgmem(message);
			return NULL;
		}
		string[i] = byte;
		i++;
	}
	
	string[i] = 0;

	return string;
}
