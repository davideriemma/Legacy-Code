#ifndef SERIALPRINT_H_
#define SERIALPRINT_H_

#include <avr/io.h>
#include <avr/pgmspace.h>

#define	USART_DATA UDR

#define USART_DATA_REG UCSRA
#define USART_DATA_REG_EMPTY_BIT UDRE

void printString(const char * string);
void printStringfromPgmem(const char * stringFromPgmem);
void transmitByte(uint8_t data);

#endif /* SERIALPRINT_H_ */