/*
 * ports.c
 *
 * Created: 9/21/2026 4:28:27 PM
 *  Author: josel
 */ 
#include <avr/io.h>

void init_ports(void){
	DDRB |= (1 << PB5);
}