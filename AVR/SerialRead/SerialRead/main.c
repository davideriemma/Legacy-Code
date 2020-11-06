#include <avr/io.h>
#include <avr/pgmspace.h>
#include "../../utility328p/Serial/Serial.h"
#include <stdlib.h>

#undef F_CPU
#define F_CPU 16000000L


int main(void)
{
	
	SerialEnable(EIGHT_BIT_FRAME, ONE_BIT_STOP, NO_PARITY, TX_ENABLED | RX_ENABLED, ASYNC_SERIAL);
	
	static const char string[] PROGMEM = "stringa letta ";
	
	char * c;
	
    while (1) 
	{
		c = readString();
		printStringfromPgmem(string);
		printString(c);
		transmitByte('\n');
		
		free(c);
    }
}

