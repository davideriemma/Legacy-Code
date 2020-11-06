
#define F_CPU 8000000UL

#include <avr/io.h>
#include "header/utility.h"
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/delay.h>

ISR(INT1_vect){

	cli();		/*anche se si rilascia il bottone, non ce ne frega*/
	
	TOGGLE_BIT(PORTB, PINB1);

	sei();	/*da ora in poi però si*/
	sleep_cpu();
}

int main(){

	SET_OUTPUT_DIR(DDRB, PB1);	/*imposta pb1 come output*/
	SET_INPUT_DIR(DDRB, PB0);	/*imposta pb0 come input*/
	SET_INPUT_DIR(DDRD, PD3);	/*imposta pd3 come input*/
	
	CLEAR_BIT(PORTD, PD3);
		
	_delay_ms(1000);
	
	setPCINTinterrupt();
	setPower();
	
	sleep_cpu();

	while(1){

	}

	return 0;
}
