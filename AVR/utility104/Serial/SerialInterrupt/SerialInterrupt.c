#include "serialInterrupt.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void SerialInterruptInit(uint8_t interrupt_type){
	
	SERIAL_INTERRUPT_PORT |= interrupt_type;
	
	return;
}

void TriggerInterrupt(uint8_t interrupt_type){
	
	SERIAL_INTERRUPT_FLAG_REG |= interrupt_type;
	
	return;
}

void SerialInterruptDisable(uint8_t interrupt_type){
	
	SERIAL_INTERRUPT_PORT &= ~(interrupt_type);
	
	return;
}
