/*
 * sdk2027.c
 *
 * Created: 9/21/2026 4:22:01 PM
 * Author : josel
 */ 
#include "ports.h"
#include "leds.h"

int main(void)
{
    /* Replace with your application code */
    init_ports();
	while (1) 
    {
		led_on_off();
    }
}

