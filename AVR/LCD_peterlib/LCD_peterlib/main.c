#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>
#include "src/lcd.h"
#include <avr/sleep.h>
#include <avr/power.h>

void inline startSleep(void){
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	
	return;
}

void inline houseOS_LCD_welcome(void){
	
	lcd_clrscr();
	lcd_home();
	lcd_puts_P("Welcome Davide!");
	_delay_ms(3000);
	
	lcd_clrscr();
	lcd_puts_P("Loading HouseOS");
	
	_delay_ms(3000);
		
	return;
}

int main(void)
{
	
	lcd_init(LCD_DISP_ON);
	houseOS_LCD_welcome();
	
	startSleep();
    while (1) 
    {
		lcd_clrscr();
		lcd_puts_P("Sleeping MCU");
		sleep_cpu();
    }
}

