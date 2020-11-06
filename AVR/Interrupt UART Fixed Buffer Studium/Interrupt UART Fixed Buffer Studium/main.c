#include <avr/io.h>
#define F_CPU 16000000
#define BAUD 9600
#include <util/setbaud.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdbool.h>

#define BUFFSIZE 500

void transmit(char * string);
void serial_init(void);

typedef struct
{
	char Buffer[BUFFSIZE];
	size_t currentChar;
	size_t taken_space;
	bool owf;
} outBuffer;

outBuffer out = {{0}, 0, 0, false};

ISR(USART_TX_vect)
{
	if (out.Buffer[out.currentChar])
	{
		UDR0 = out.Buffer[out.currentChar++];
	}
	else   /*siamo giunti al carattere nullo di terminazione*/
	{
		out.currentChar = 0;
		out.taken_space = 0;
		out.owf = false;
		UCSR0B &= ~(1 << TXCIE0);
	}
}

int main(void)
{ 
	serial_init();
	transmit("Ciaoooooooooooooooooooooooooooooooooooo!\n");	
    while (1) 
    {
		transmit("Maria ");
		transmit("e Davide!\n");
		if (out.owf)
		{
			transmit("OWF\n");
		}
		
		_delay_ms(1000);
    }
}

void serial_init(void){
	
	UBRR0L = UBRRL_VALUE;
	UBRR0H = UBRRH_VALUE;
	
	UCSR0C |= (1 << UPM01) | (1 << UCSZ00) | (1 << UCSZ01);
	UCSR0A |= (1 << U2X0);
	UCSR0B |= (1 << TXEN0);
	
	return;
}

void transmit(char * string)
{
	if (!out.currentChar)
	{
		strncpy(out.Buffer, string, BUFFSIZE);
		
		if(strlen(string) + 1 > BUFFSIZE)	/*se si verifica overflow fin dalla prima stringa, lo handla*/
		{
			out.taken_space = BUFFSIZE;
			out.owf = true;
			out.Buffer[BUFFSIZE - 1] = 0;	/*appende il null terminating char per far si che il buffer venga svuotato appena finisce l'invio della stringa*/
		}
		
		else
		{
			out.taken_space = strlen(string) + 1; /*il +1 è il null char*/	
		}
		
		UCSR0B |= (1 << TXCIE0);
		UDR0 = out.Buffer[out.currentChar++];
		sei();
	}
	else	/*handle overflow -> mi basta fare tutto come strNcat limitandolo alla dimensione restante del buffer :/*/
	{
		strncat(out.Buffer, string, BUFFSIZE - out.taken_space);
		
		if (strlen(string) + out.taken_space > BUFFSIZE)	//lo spazio out.tknspc è gia comprensivo del carattere nullo che sarà sovrascritto
		{
			out.owf = true;
			out.taken_space = BUFFSIZE;
			out.Buffer[BUFFSIZE - 1] = 0;	/*appende il null terminating char per far si che il buffer venga svuotato appena finisce l'invio della stringa*/
		}
		else
		{
			out.owf = false;
			out.taken_space += strlen(string) + 1;
		}
	}
}

