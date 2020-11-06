#include "ADCStart.h"
#include <avr/io.h>

uint16_t adc_convert(uint8_t channel){
	
	uint16_t adc_result = 0;
	
	ADC_CHANNEL_REG |= channel;
	
	SET_BIT(ADC_START_REG, ADC_START_BIT);
	
	loop_until_bit_is_clear(ADC_START_REG, ADC_START_BIT);	/*attende che la convesione sia finita*/
	
	/*formatta il risultato in un intero da 10 bit a seconda che il risulato lo si preferisca allineato a destra o a sinistra*/

#ifdef ADC_LEFT_ADJUSTED

	adc_result |= ADC_RESULT_HIGH;
	adc_result <<= 2;
	adc_result |= ADC_RESULT_LOW;

#else
	adc_result |= ADC_RESULT_HIGH;
	adc_result <<= 8;
	adc_result |= ADC_RESULT_LOW;
	
#endif
	
	return adc_result;
}
