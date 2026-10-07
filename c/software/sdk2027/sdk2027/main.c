/*
 * sdk2027.c
 *
 * Created: 9/21/2026 4:22:01 PM
 * Author : josel
 */ 
#include <avr/interrupt.h>
#include "ports.h"
#include "leds.h"
#include "ext_int.h"
#include "a_comp.h"
#include "lcd_4b.h"

int main(void)
{
    /* Replace with your application code */
    init_ports();
	init_ext_int();
	init_analog_comp();
	lcd_init();
	lcd_col_row(1,2);
	lcd_write_string("todos reprobados");
	sei();
	while (1) 
    {
		led_on_off();
    }
}

