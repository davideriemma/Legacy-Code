#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../utility328p/bitmacro.h"

#define INT0_INTREN_REG EIMSK
#define INT0_INTREN_BIT INT0

#define INT0_INTFLAG_REG EICRA
#define INT0_MODE_1 ISC01

ISR(INT0_vect){
	
	TOGGLE_BIT(PORTA, PORTA5);
}

void inline initINT0interrupt(void){
	
	SET_BIT(INT0_INTREN_REG, INT0_INTREN_BIT);
	SET_BIT(INT0_INTFLAG_REG, INT0_MODE_1);
	
	sei();
}


int main(void)
{
    SET_BIT(DDRA, PORTA5);
	initINT0interrupt();
	
    while (1) 
    {
    }
}

