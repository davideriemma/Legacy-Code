#include "ADCInt.h"

void ADCinterruptEnable(void){
	
	SET_BIT(ADC_INTERRUPUT_REG, ADC_INTERRUPUT_BIT);
	
	return;
}

void ADCTrigInterrupt(void){
	
	SET_BIT(ADC_INTERRUPUT_REG, ADC_INTERRUPUT_FLAG);
}
