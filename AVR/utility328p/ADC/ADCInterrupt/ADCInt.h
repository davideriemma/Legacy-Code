#ifndef ADCINT_H_
#define ADCINT_H_

#include <avr/io.h>
#include "../../bitmacro.h"

/*------------------------adc interrupt enable define------------------------------------*/

#define ADC_INTERRUPUT_REG ADCSRA

#define ADC_INTERRUPUT_BIT ADIE
#define ADC_INTERRUPUT_FLAG ADIF

/*----------------------------------------functions-------------------------------------*/



#endif /* ADCINT_H_ */