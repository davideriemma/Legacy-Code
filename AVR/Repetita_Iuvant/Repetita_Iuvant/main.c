#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include "utility.h"

ISR(PCINT0_vect){

	cli();		/*anche se si rilascia il bottone, non ce ne frega*/

	if (bit_is_set(PINB, PINB1))
	{
		_delay_ms(50);

		if (bit_is_set(PINB, PINB1))
		{
			SET_BIT(PORTB, PINB0);
			_delay_ms(1000);
			CLEAR_BIT(PORTB, PINB0);
		}
	}

	sei();	/*da ora in poi però si*/
	sleep_cpu();
}

int main(void)
{
	
	SET_OUTPUT_DIR(DDRB, PB0);
	SET_INPUT_DIR(DDRB, PB1);	/*imposta pb1 come input.. */
	SET_BIT(PORTB, PB1);	/*...pullup!*/

	setPCINTinterrupt();

	set_sleep_mode(SLEEP_MODE_EXT_STANDBY);
	
	sleep_enable();
	sleep_cpu();    

    while (1) 
    {
		TOGGLE_BIT(PORTB, PB0);
		_delay_ms(100);
    }
}

