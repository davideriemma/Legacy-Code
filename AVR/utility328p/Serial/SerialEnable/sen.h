#ifndef USART_H_
#define USART_H_

#include <stdbool.h>
#include "..\..\bitmacro.h"
#include <avr/io.h>

/*-----------------------------baudrate settings----------------*/

#define LBAUD_REG_SIZE 8

/*-----------------------------mode-----------------------------*/

#define USART_MODE_REG UCSR0C

#define SYNC_SERIAL 1
#define ASYNC_SERIAL 0

#define SYNC_MODE_BIT UMSEL00

#define RISING_EDGE_CLOCK 0
#define FALLING_EDGE_CLOCK 1

#define FALLING_CLOCK_BIT UCPOL0

/*-----------------------------dataFrame------------------------*/

#define DATA_FRAME_REG	UCSR0C
#define DATA_FRAME_REG_9 UCSR0B

#define BIT_FRAME_ZERO UCSZ00
#define BIT_FRAME_ONE UCSZ01
#define BIT_FRAME_TWO UCSZ02

#define FIVE_BIT_FRAME 0
#define SIX_BIT_FRAME	_BV(BIT_FRAME_ZERO)
#define SEVEN_BIT_FRAME	_BV(BIT_FRAME_ONE)
#define EIGHT_BIT_FRAME	_BV(BIT_FRAME_ZERO) | _BV(BIT_FRAME_ONE)
#define NINE_BIT_FRAME	1	/*richiede la manipolazione di due registri*/

#define BIT_STOP_REG UCSR0C

#define BIT_STOP_BIT USBS0

#define ONE_BIT_STOP 0
#define TWO_STOP_BIT _BV(BIT_STOP_BIT)

#define BIT_CONTROL_REG UCSR0C

#define BIT_PARITY_MODE_ZERO UPM00
#define BIT_PARITY_MODE_ONE UPM01

#define NO_PARITY 0
#define EVEN_PARITY _BV(BIT_PARITY_MODE_ONE)
#define ODD_PARITY	_BV(BIT_PARITY_MODE_ONE) | _BV(BIT_PARITY_MODE_ZERO)

/*-------------abilitazioni delle linee di trasmissione----------*/

#define COMU_REG UCSR0B

#define RX_ENABLED _BV(RXEN0)
#define TX_ENABLED _BV(TXEN0)
#define RX_TX_ENABLED RX_ENABLED | TX_ENABLED

/*----------------------------funzioni--------------------------*/

void SerialEnable(unsigned int baudRate, const uint8_t dataFrame, const uint8_t stop_bit, const uint8_t partity_bit, const uint8_t xline, const bool mode, ... );

#endif /* USART_H_ */