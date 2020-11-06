#ifndef SERIALINTERRUPT_H_
#define SERIALINTERRUPT_H_

#include <avr/io.h>
#include <avr/interrupt.h>

/*--------------tipi di interrupt------------*/

#define SERIAL_INTERRUPT_PORT UCSR0B

#define TX_COMPLETED_INTERRUPT _BV(TXCIE0)
#define RX_COMPLETED_INTERRUPT _BV(RXCIE0)
#define DATA_REG_EMPTY_INTERRUPT _BV(UDRIE0)

/*NOTA: è possibile abilitare più interrupt contemporaneamente passando alla 
  funzione "SerialInterruptEnable" molteplici valori di cui sopra tramite or logico
  
  ex: SerialInterruptEnable(TX_COMPLETED_INTERRUPT | RX_COMPLETED_INTERRUPT);
  
  */

/*------------------Registro flag interrupt--*/

#define SERIAL_INTERRUPT_FLAG_REG UCSR0A

/*--------------------funzioni---------------*/

void SerialInterruptInit(uint8_t interrupt_type);	/*inizializza gli interrupt desiderati*/
void TriggerInterrupt(uint8_t interrupt_type);	/*simula interrupt via software*/

#endif /* SERIALINTERRUPT_H_ */