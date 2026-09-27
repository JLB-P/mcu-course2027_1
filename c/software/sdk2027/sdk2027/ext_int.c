/*
 * ext_int.c
 *
 * Created: 9/23/2026 4:29:41 PM
 *  Author: josel
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "leds.h"

ISR(INT0_vect){
	for(int i=0; i < 10;i++){
		led_on_off_int0();	
	}
}

ISR(INT1_vect){
	
}

void init_ext_int(void){
	EICRA |=(1 << ISC01) | ~(1 << ISC00); //int0 activa en pulso de bajada
	EICRA |=(1 << ISC11) | ~(1 << ISC10); //int1 activa en pulso de bajada
	EIMSK |=(1 << INT0) | (1 << INT1);
	sei();
}