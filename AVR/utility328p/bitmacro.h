#ifndef UTILITY_H_
#define UTILITY_H_

#define SET_BIT(PORT, PIN)	PORT |= _BV(PIN)
#define CLEAR_BIT(PORT, PIN)	PORT &= ~(_BV(PIN))
#define SET_OUTPUT_DIR(DIR, PIN)	SET_BIT(DIR, PIN)
#define SET_INPUT_DIR(DIR, PIN)	CLEAR_BIT(DIR, PIN)
#define TOGGLE_BIT(PORT, PIN)	PORT ^= _BV(PIN)


#endif /* UTILITY_H_ */