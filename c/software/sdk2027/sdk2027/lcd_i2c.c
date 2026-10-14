/*
 * lcd_i2c.c
 *
 * Created: 
 *  Author: jlbPacheco
 */
#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "lcd_i2c.h"

char column1 [2] = {0 , 64}; //first column address	


// 4bit initialization Hitachi 44780 data sheet pag.46
void lcd_i2c_reset(void)
{
	start();	// START to I2C
	write_i2c(PCF8574_ADDR);
	
	write_i2c(0xFF); //wait at least 15 ms
	_delay_ms(20);
	
	write_i2c(0x30+LCD_EN); //write Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 & E=1
	write_i2c(0x30);		//write Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 & E=0
	_delay_ms(10);			//wait at least 4.1 ms
	
	write_i2c(0x30+LCD_EN); //write Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 & E=1
	write_i2c(0x30);		//write Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 & E=0
	_delay_ms(1);			//wait at least 100 us
	
	write_i2c(0x30+LCD_EN); //write Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 & E=1
	write_i2c(0x30);		//write Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 & E=0
	_delay_ms(1);			//wait at least 100 us
	
	write_i2c(0x20+LCD_EN); //write Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=0 & E=1
	write_i2c(0x20);		//write Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=0 & E=0
	_delay_ms(1);			//wait at least 100 us
	
	stop();	// STOP to I2C
}

// write command to LCD
void lcd_i2c_cmd (char cmd)
{
	unsigned char data;
	start();	//START to I2C
	write_i2c(PCF8574_ADDR);
	
	data=(cmd & 0xF0)|LCD_EN|BACKLIGHT;
	write_i2c(data);

	data=(cmd & 0xF0)|BACKLIGHT;
	write_i2c(data);

	data=((cmd << 4) & 0xF0)|LCD_EN|BACKLIGHT;
	write_i2c(data);

	data=((cmd << 4) & (0xF0|BACKLIGHT));
	write_i2c(data);
	
	stop();	//STOP to I2C
	_delay_ms(2);
	_delay_ms(2);
}

//	LCD initialization trought I2C
void lcd_i2c_init (void)
{
	init_i2c();				//i2c initialization
	lcd_i2c_reset();		//LCD reset 
	lcd_i2c_cmd(0x2C);		//Function Set: 4 bits, 2 lines, 5×10 resolution
	//lcd_i2c_cmd(0x0F);	//Display control: LCD on, cursor on, blinking
	lcd_i2c_cmd(0x0C);		//Cursor off
	lcd_i2c_cmd(0x06);		//Entry mode: Increment
	lcd_i2c_cmd(0x80);		//Points to DDRAM address
}

// write char data
void lcd_i2c_data (unsigned char dat)
{
	unsigned char data;
	start();	//START to I2C
	write_i2c(PCF8574_ADDR);

	data=((dat & 0xF0)|LCD_EN|LCD_RS|BACKLIGHT);
	write_i2c(data);

	data=((dat & 0xF0)|LCD_RS|BACKLIGHT);
	write_i2c(data);

	data=(((dat << 4) & 0xF0)|LCD_EN|LCD_RS|BACKLIGHT);
	write_i2c(data);

	data=(((dat << 4) & 0xF0)|LCD_RS|BACKLIGHT);
	write_i2c(data);

	stop();	//STOP to I2C
	_delay_ms(2);
	_delay_ms(2);
}

//position the cursor to column & row
void lcd_i2c_col_row(uint8_t x, uint8_t y)
{
	lcd_i2c_cmd(0x80 + column1[y-1]+(x-1));
}

//clear screen
void lcd_i2c_clr(void)
{
	lcd_i2c_cmd(0x01); 
	_delay_ms(2);
}

//write string
void lcd_i2c_write_string(char *a)
{
	unsigned int i;
	for(i=0;a[i]!=0;i++)
	lcd_i2c_data(a[i]);
}

//write integer value
void lcd_i2c_write_int(int value,unsigned int field_length)
{
	char str[5]={0,0,0,0,0};
	int i=4,j=0;
	while(value)
		{
			str[i]=value%10;
			value=value/10;
			i--;
		}
	if(field_length==-1)
	while(str[j]==0) j++;
	else  
		j=5-field_length;
	if(value<0) lcd_i2c_data('-');
	for(i=j;i<5;i++)
		{
			lcd_i2c_data(48+str[i]);
		}
}