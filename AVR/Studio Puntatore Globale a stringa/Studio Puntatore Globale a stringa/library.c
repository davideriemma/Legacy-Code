/*
 * Studio Puntatore Globale a stringa.c
 *
 * Created: 11/06/2018 14:46:41
 * Author : david
 * 
 * il seguente studio si pone l'obbiettivo di osservare in che modo viene gestita una stringa globale
 
   quando si tratta di recuperare una stringa si utilizza come puntatore Z
 */ 

#include <avr/io.h>
#include <stdlib.h>

char * string;

int main()
{
	string = "Ciao";
	
	char a;
	
	while(1)
	{
		a = *string ++;
		a = a - 1;
	}
	
	return 0;
}
