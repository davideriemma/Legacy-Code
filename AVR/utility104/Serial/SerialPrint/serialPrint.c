#include "serialPrint.h"
#include "..\..\bitmacro.h"
#include <avr/io.h>
#include <avr/pgmspace.h>

void printString(const char * string){

  uint8_t i = 0;

  while (string[i]) {

	transmitByte(string[i]);
	i++;
  }

	return;
}

void transmitByte(uint8_t data) {
	/* Wait for empty transmit buffer */
	loop_until_bit_is_set(USART_DATA_REG, USART_DATA_REG_EMPTY_BIT);
	
	USART_DATA = data;                                            /* send data */
}

void printStringfromPgmem(const char * stringFromPgmem){

	uint8_t i = 0;

	while (pgm_read_byte(&stringFromPgmem[i])) {

		transmitByte(pgm_read_byte(&stringFromPgmem[i]));
		i++;
	}

	return;
}
