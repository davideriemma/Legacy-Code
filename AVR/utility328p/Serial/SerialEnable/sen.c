#include <avr/io.h>
#include <stdbool.h>
#include <stdarg.h>
#include "sen.h"
#include "..\..\bitmacro.h"

#ifndef F_CPU

	#define F_CPU 1000000L

#endif

void SerialEnable(unsigned int baudRate, const uint8_t dataFrame, const uint8_t stop_bit, const uint8_t partity_bit, const uint8_t xline, const bool mode, ... ){
	
	unsigned int Rate = F_CPU / 16 / (baudRate - 1);
	
	UBRR0H = (unsigned int) Rate >> LBAUD_REG_SIZE;
	UBRR0L = (unsigned int) Rate;
	
	/*imposta la modalità operativa (sincrona o asincrona)*/
	
	if (mode)
	{
		SET_BIT(USART_MODE_REG, SYNC_MODE_BIT);	/*abilita la modalità sincrona*/
		
		va_list clock_mode;	/*se viene richiesta una modalità sincrona, tramite l'ellissi è possibile impostare il fronte di clock*/
		va_start(clock_mode, mode);
		
		if (va_arg(clock_mode, bool))
		{
			SET_BIT(USART_MODE_REG, FALLING_CLOCK_BIT);	/*clock on falling edge*/			
		}
	}
	
	/*imposta la lunghezza del frame*/
	
	if (dataFrame == NINE_BIT_FRAME)
	{
		SET_BIT(DATA_FRAME_REG, BIT_FRAME_ZERO);	/*111 - 9-bit frame*/
		SET_BIT(DATA_FRAME_REG, BIT_FRAME_ONE);
		SET_BIT(DATA_FRAME_REG_9, BIT_FRAME_TWO);
	}
	else
	{
			DATA_FRAME_REG |= dataFrame;		
	}
	
	/*imposta il bit di stop, specificato dalle macro passate per argomento*/
	BIT_STOP_REG |= stop_bit;
	
	/*imposta il controllo di parità del frame ricevuto*/
	
	BIT_CONTROL_REG |= partity_bit;
	
	/*inizializza le linee di comunicazione*/
	
	COMU_REG |= xline;
		
	return;
}

