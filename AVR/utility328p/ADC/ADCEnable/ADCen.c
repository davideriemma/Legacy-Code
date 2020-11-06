#include "ADCen.h"
#include <avr/io.h>
#include <stdarg.h>

void ADCEnable(const uint8_t source, const uint8_t prescaler, uint8_t mode, ...){
	
	SET_BIT(ADC_ENABLE_REG, ADC_ENABLE_BIT);	/*ABILITA ADC*/
	
	ADC_SOURCE_REG |= source;	/*imposta la fonte di comparazione*/
	
	ADC_PRESCALER_REG |= prescaler;	/*imposta il prescaler dal clock*/
	
	if (mode)
	{
		SET_BIT(ADC_MODE_REG, ADC_MODE_ENABLE_BIT);	/*imposta la modalità continua (necessaria per le modalità definite nell'header)*/
		
		va_list modes;
		
		va_start(modes, mode);
		
		ADC_MODE_REG |= va_arg(modes, unsigned int);	/*imposta la modalità dall'argomento passato dopo mode*/
		
		va_end(modes);
	}
	
	return;
}

void changeModeADC(uint8_t mode){
	
	SET_BIT(ADC_MODE_REG, ADC_MODE_ENABLE_BIT);	/*imposta la modalità continua (necessaria per le modalità definite nell'header)*/
	ADC_MODE_REG |= mode;
	
	return;
}
