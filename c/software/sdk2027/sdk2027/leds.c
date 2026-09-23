/*
 * leds.c
 *
 * Created: 9/21/2026 4:47:09 PM
 *  Author: josel
 */ 
#include <avr/io.h>
#include <util/delay.h>

void led_on_off(void){
	PORTB |= (1 << PB5);
	_delay_ms(1000);
	PORTB &= ~(1 << PB5);
	_delay_ms(1000);
}