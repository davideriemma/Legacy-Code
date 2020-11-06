#include <avr/io.h>
#include "../../utility104/Serial/Serial.h"
#include <avr/pgmspace.h>

#define F_CPU 1000000L

#include <util/delay.h>
#include <avr/interrupt.h>

#include <avr/sleep.h>
#include <avr/power.h>

#define INT0_INTREN_REG EIMSK
#define INT0_INTREN_BIT INT0

#define INT0_MODE_REG EICRA
#define INT0_MODE_1 ISC01

#define INT0_INTFLAG_REG EIFR
#define INT0_INTFLAG_BIT INTF0

#define string(name) static const char name[] PROGMEM


void inline initINT0interrupt(void){
	
	SET_BIT(INT0_INTREN_REG, INT0_INTREN_BIT);
	SET_BIT(INT0_MODE_REG, INT0_MODE_1);
	
	sei();
}

void inline setSleep(void){
	
	set_sleep_mode(SLEEP_MODE_IDLE);
		
	sleep_enable();
}

int main(void)
{
    
	SerialEnable(9600, EIGHT_BIT_FRAME, ONE_BIT_STOP, NO_PARITY, TX_ENABLED | RX_ENABLED, ASYNC_SERIAL);
	
	SET_OUTPUT_DIR(DDRA, PORTA5);
	
    while (1) 
    {
		TOGGLE_BIT(DDRA, PORTA5);
		printString("Immettere Codice di attivazione\n");
		_delay_ms(1000);
    }
}

