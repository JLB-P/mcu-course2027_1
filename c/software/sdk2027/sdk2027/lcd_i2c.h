/*
 * lcd_i2c.h
 *
 * Created: 
 *  Author: jlbPacheco
 */ 
#include <avr/io.h>

#ifndef LCD_I2C_H_
#define LCD_I2C_H_

#define PCF8574_ADDR	0x70	//I2C device address (Protesus sim.)
//#define PCF8574_ADDR	0x4E	//I2C device address
// PCF8574 address=0x20, shift to left 0x40
// PCF8574A address=0x38, shift to left 0x70

#define LCD_RS			0x01		//RS=0000 0001
#define LCD_RW			0x02		//RW=0000 0010
#define LCD_EN			0x04		//E= 0000 0100
#define BACKLIGHT		0x08		//turn on/off backlight

void lcd_i2c_init (void);
void lcd_i2c_data (unsigned char dat);
void lcd_i2c_write_string(char *a);
void lcd_i2c_clr(void);
void lcd_i2c_col_row(uint8_t x, uint8_t y);
void lcd_i2c_write_int(int value,unsigned int field_length);

#endif /* LCD_I2C_H_ */