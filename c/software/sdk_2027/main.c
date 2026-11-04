/*
 * sdk2027.c
 *
 * Created: 9/21/2026 4:22:01 PM
 * Author : jlbPacheco
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "ports.h"
#include "leds.h"
#include "ext_int.h"
#include "a_comp.h"
#include "adc.h"
#include "lcd_i2c.h" 


//declare a shared flag as volatile
volatile uint8_t comp_event_flag = 0; 
ISR(ANALOG_COMP_vect){
	//set the flag in the ISR
	comp_event_flag = 1;
}


int main(void)
{
    init_ports();
//	init_ext_int();
//	init_analog_comp();
//	init_adc_withINT();
	lcd_i2c_init();
	lcd_i2c_clr();
	lcd_i2c_col_row(1,1);
	lcd_i2c_write_string("reprobados..");
	//sei();
	while (1) 
    {
		
//		if (comp_event_flag) {
//			lcd_i2c_clr();
//			lcd_i2c_write_string("Vin < Vref");
//			_delay_ms(1000);	//stay visible text for 1 second
//          // Clear the flag for the next event
//            comp_event_flag = 0; 
//    	}
	}
}

