#ifndef SERIALREAD_H_
#define SERIALREAD_H_

#include <avr/io.h>

#define MAX_LINE_LENGTH 50

uint8_t receiveByte(void);
char * readString(void);


#endif /* SERIALREAD_H_ */