#ifndef UTILITY_H_
#define UTILITY_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>

#define SET_BIT(PORT, PIN)	PORT |= _BV(PIN)
#define CLEAR_BIT(PORT, PIN)	PORT &= ~(_BV(PIN))
#define SET_OUTPUT_DIR(DIR, PIN)	SET_BIT(DIR, PIN)
#define SET_INPUT_DIR(DIR, PIN)	CLEAR_BIT(DIR, PIN)
#define TOGGLE_BIT(PORT, PIN)	PORT ^= _BV(PIN)

void inline setPCINTinterrupt(void){
	
	SET_BIT(EICRA, ISC10);
	SET_BIT(EICRA, ISC11);

	SET_BIT(EIMSK, INT1);

	sei();

	return;
}

void inline setPower(void){
	
	set_sleep_mode(SLEEP_MODE_EXT_STANDBY);
	
	sleep_enable();
	
	return;
}

#endif /* UTILITY_H_ */
