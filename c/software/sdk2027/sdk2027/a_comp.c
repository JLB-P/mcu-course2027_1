/*
 * a_comp.c
 *
 * Created: 9/28/2026 5:18:03 PM
 *  Author: josel
 */ 
ISR(ANALOG_COMP_vect){
	
}

void init_analog_comp(void){
	ACSR |= ((1 << ACIS0)|(1 << ACIS1)); //activa comparador en pulso de subida
	ACSR |= (1 << ACIE); //activa interupciones
}