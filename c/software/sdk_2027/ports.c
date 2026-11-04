/*
 * ports.c
 *
 * Created: 
 *  Author: jlbPacheco
 */ 
#include <avr/io.h>

void init_ports(void){
	DDRB |= (1 << PB5);	//define pin para LED de la tarjeta
	//define pin para interrupciones
	DDRD &= ~(1 << PD2 | 1 << PD3); //PD2 y PD3 como entrada
	PORTD |= (1 << PD2 | 1 << PD3); //activa Rp
	//define salidas para I2C
	DDRC |= (1 << PC4 | 1 << PC5); //PC4 y PC5 como salida
	PORTC |= (1 << PC4 | 1 << PC5); //activa Rp	
}