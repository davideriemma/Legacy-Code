#include "David.h"

int byteToInt(uint16_t byte){
	
	int power(int base, int exponent);

	int integer = 0;	/*Contatore dove viene immagazzinato il numero*/

	uint16_t bitmask = 1;	/*bitmask per il confronto*/

	for (int i = 0; i < 10; i++)
	{
		if(byte & (bitmask << i))	/*Se il confronto tra il byte binario e il bitmask con un 1 shiftato man mano verso destra ritorna vero*/
		{
			integer += (int) power(2, i);
		}
	}

	return integer;
}

int power(int base, int exponent){

    int power = 1;  /*conviene dichiararla extern? non credo, poichè questa deve essere richiamata più volte e rieseguire daccapo il suo compito*/

    for(; exponent > 0; exponent--){

        power *= base;  /*moltiplica power per l'esponente e assegna il risultato a power:
                          se power è uguale a 0, ritorna 1 */
    }

    return power;

}
