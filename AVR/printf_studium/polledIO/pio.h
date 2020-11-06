/*
 * pio.h
 *
 * Created: 09/06/2018 23:31:58
 *  Author: david
 */ 

/*la libreria inizializza la comunicazione tramite due puntatori a funzione rispettivamente per trasmettere e inviare, oltre che 
  un modo per indicare come viene utilizzato il file di i/o che è unico, sia per stdin che stdout, in modo tale da risparmiale memoria*/


#ifndef PIO_H_
#define PIO_H_

#include <avr/io.h>
#include <stdio.h>

unsigned char init_pio((int * )(char, FILE *), (int *)(char));

#endif /* PIO_H_ */