#ifndef DAVID_O_H_
#define DAVID_O_H_

/*LA LIBRERIA DEFINITIVA PER UTILIZZARE PRINTF E TRASMISSIONE UART TRAMITE INTERRUPT!!
  ver: 1.0
  */

#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define BUFFSIZE 500

typedef struct
{
	char Buffer[BUFFSIZE];	/*buffer di immagazzinamento caratteri*/
	size_t taken_space;	/*spazio occupato*/
	size_t current_char;	/*indice del carattere correntemente sottoposto ad invio*/
	size_t to_send;		/*caratteri da inviare*/
	bool owf;	/*segnalatore di overflow*/
	
}outBuffer;

int transmit(char c, FILE * f);
void david_o_init(void);

#endif /* DAVID_O_H_ */