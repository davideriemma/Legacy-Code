#include <avr/io.h>
#include "../../utility328p/Serial/Serial.h"
#undef DEFAULT
#define F_CPU 16000000L
#define BAUD 9600L
#include <util/delay.h>
#include <avr/pgmspace.h>

#define string(name) static const char name[] PROGMEM

int main(void)
{
	SerialEnable(EIGHT_BIT_FRAME, ONE_BIT_STOP, NO_PARITY, TX_ENABLED, ASYNC_SERIAL);
	
	string(cptr) = "Transmitting from memory: No buffer.\n";

    while (1) 
    {
		printStringfromPgmem(cptr);
		_delay_ms(1000);
    }
}
