#ifndef ADRSTART_H_
#define ADRSTART_H_

#include <avr/io.h>
#include "../../bitmacro.h"

/*-------------------------------------multiplexer defines-----------------------------------------*/

#define ADC_CHANNEL_REG ADMUX

#define ADC_MUX_BIT_0 MUX0
#define ADC_MUX_BIT_1 MUX1
#define ADC_MUX_BIT_2 MUX2

#define ADC0 0
#define ADC1 _BV(ADC_MUX_BIT_0)
#define ADC2 _BV(ADC_MUX_BIT_1)
#define ADC3 _BV(ADC_MUX_BIT_0) | _BV(ADC_MUX_BIT_1)
#define ADC4 _BV(ADC_MUX_BIT_2) 
#define ADC5 _BV(ADC_MUX_BIT_0) | _BV(ADC_MUX_BIT_2)
#define ADC6 _BV(ADC_MUX_BIT_1) | _BV(ADC_MUX_BIT_2)
#define ADC7 _BV(ADC_MUX_BIT_0) | _BV(ADC_MUX_BIT_1) | _BV(ADC_MUX_BIT_2)

/*------------------------------------------adc conversion start-------------------------------------*/

#define ADC_START_REG ADCSRA

#define ADC_START_BIT ADSC

/*------------------------------------------------adc result-----------------------------------------*/

#define ADC_RESULT_HIGH ADCH
#define ADC_RESULT_LOW ADCL

/*------------------------------------------functions------------------------------------------------*/

uint16_t adc_convert(uint8_t channel);	/*esegue la conversione sul canale selezionato*/

#endif /* ADRSTART_H_ */