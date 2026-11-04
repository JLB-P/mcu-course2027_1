/*
 * i2c.c
 *
 * Created: 
 *  Author: jlbPacheco
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"

void init_i2c(void){
	TWSR = ((0 << TWPS1) & (0 << TWPS0)); //Prescaler = 1
	TWBR = 0X14;	/*define Bit rate SCL_frec=CPU_frec/(16+2(TWBR)x(prescalerValue))
					* TWBR = Value of the TWI Bit Rate Register
					* SCL_Frec=(16000000/(16+2(72)(1)))=100Khz	*/
	TWCR = (1<<TWEN); //enable TWI
}

void start(void){
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //START condition
	while((TWCR & (1<<TWINT))==0);			//wait until flag is TWINT=0
}

void write_i2c(uint8_t data){
	TWDR = data; //byte to write
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA); //write with acknowledge (TWEA=1)
	while((TWCR & (1<<TWINT))==0); //wait until flag is TWINT=0
}

uint8_t read_i2c(){
	TWCR = (1<<TWINT)|(1<<TWEN); //read with acknowledge (TWEA=0)
	while((TWCR & (1<<TWINT))==0); //wait until flag is TWINT=0
	return TWDR; //return read byte in the function
}

void stop(void){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //STOP condition
	_delay_ms(1);
}

