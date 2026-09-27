/*
 * ports.c
 *
 * Created: 9/21/2026 4:28:27 PM
 *  Author: josel
 */ 
#include <avr/io.h>

void init_ports(void){
	DDRB |= (1 << PB5);	//define pin para LED de la tarjeta
	//define pin para interrupciones
	DDRD &= ~(1 << PD2 | 1 << PD3); //PD2 y PD3 como entrada
	PORTD |= (1 << PD2 | 1 << PD3); //activa Rp
}