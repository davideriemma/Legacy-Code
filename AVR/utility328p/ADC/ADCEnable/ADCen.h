#ifndef ADCEN_H_
#define ADCEN_H_

#include <avr/io.h>
#include "../../bitmacro.h"

/*------------------------------------------adc enable-------------------------------------------*/

#define ADC_ENABLE_REG ADCSRA
#define ADC_ENABLE_BIT ADEN

/*---------------------------------------comparation source---------------------------------------*/

#define ADC_SOURCE_REG ADMUX

#define ADC_SOURCE_BIT_0 REFS0
#define ADC_SOURCE_BIT_1 REFS1

#define AREF_PIN 0
#define INTERNAL_AVCC _BV(ADC_SOURCE_BIT_0)
#define INTERNAL_1_1V _BV(ADC_SOURCE_BIT_0) | _BV(ADC_SOURCE_BIT_0)

/*---------------------------------------prescaler settings--------------------------------------*/

#define ADC_PRESCALER_REG ADCSRA

#define PRESCALER_BIT_0 ADPS0
#define PRESCALER_BIT_1 ADPS1
#define PRESCALER_BIT_2 ADPS2

#define TWO_DIV_CLCK 0
#define FOUR_DIV_CLCK _BV(PRESCALER_BIT_1)
#define EIGHT_DIV_CLCK _BV(PRESCALER_BIT_0) | _BV(PRESCALER_BIT_1)
#define SIXTEEN_DIV_CLCK _BV(PRESCALER_BIT_2)
#define THIRTYTWO_DIV_CLCK _BV(PRESCALER_BIT_0) | _BV(PRESCALER_BIT_2)
#define SIXYFOUR_DIV_CLCK _BV(PRESCALER_BIT_1) | _BV(PRESCALER_BIT_2)
#define ONEHUN28_DIV_CLCK _BV(PRESCALER_BIT_0) | _BV(PRESCALER_BIT_1) | _BV(PRESCALER_BIT_2)

/*--------------------------------------operation mode-------------------------------------------*/

#define ADC_MODE_REG ADCSRB

#define ADC_MODE_ENABLE_REG ADCSRA
#define ADC_MODE_ENABLE_BIT ADATE

#define ADC_MODE_BIT_0 ADTS0
#define ADC_MODE_BIT_1 ADTS1
#define ADC_MODE_BIT_2 ADTS2

#define ADC_SINGLE_CONV 0	/*permette una sola conversione, tuttavia "accende" l'adc, che può essere successivamente modificato*/
#define ADC_MODE_SELECT 1

#define FREE_RUNNING_MODE 0
#define ANALOG_COMP_MODE _BV(ADC_MODE_BIT_0)
#define EXTERNAL_INT_REQ_MODE _BV(ADC_MODE_BIT_1)
#define TC0_COMPARE_MODE _BV(ADC_MODE_BIT_0) | _BV(ADC_MODE_BIT_1)
#define TC0_OVERFLOW_MODE _BV(ADC_MODE_BIT_2)
#define TC1_COMPARE_MODE _BV(ADC_MODE_BIT_0) | _BV(ADC_MODE_BIT_2)
#define TC1_OVERFLOW_MODE _BV(ADC_MODE_BIT_1) | _BV(ADC_MODE_BIT_2)
#define TC1_CAPUTREV_MODE _BV(ADC_MODE_BIT_0) | _BV(ADC_MODE_BIT_1) | _BV(ADC_MODE_BIT_2)

/*------------------------------------------functions---------------------------------------------*/

#endif /* ADCEN_H_ */