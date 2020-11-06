#include "ADCDisable.h"

void inline ADCDisable(void){
	
	CLEAR_BIT(ADC_ENABLE_REG, ADC_ENABLE_BIT);
	
	return;
}