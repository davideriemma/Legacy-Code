#ifndef SERIALPRINT_H_
#define SERIALPRINT_H_

#include <avr/io.h>
#include <avr/pgmspace.h>

void printString(const char * string);
void printStringfromPgmem(const char * stringFromPgmem);
void transmitByte(uint8_t data);

#endif /* SERIALPRINT_H_ */