#include "SerialDisable.h"
#include <avr/io.h>

void inline SerialDisable(void){
	
	CLEAR_BIT(COMU_REG, RX_ENABLED);
	CLEAR_BIT(COMU_REG, TX_ENABLED);
	
	return;
}
