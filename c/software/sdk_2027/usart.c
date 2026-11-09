/*
 * usart.c
 *
 * Created: 3/22/2022 6:49:28 PM
 *  Author: jlb
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart.h"

//Global variables
volatile char usart_received_char;

ISR (USART_RX_vect)
{
	usart_transmit_string("\n\rHola BLE\n\r");
	usart_received_char=UDR0;
	usart_transmit(0x2D); //transmit "-"
	usart_transmit(0x3E); //then ">" symbol
	usart_transmit(usart_received_char); //char from terminal
}


unsigned char usart_receive( void )
{
  while ((UCSR0A & 0x80) == 0x00); // Espera por un dato (RXC=1)
  return UDR0;
}

void usart_transmit( uint8_t data )
{
  while ((UCSR0A & 0x20) == 0x00);  // Espera hasta que el buffer del transmisor est� vac�o (UDRE=1)
  UDR0 = data; // Cuando el buffer est� vac�o, coloca el dato en el registro UDR
}

void usart_transmit_string( char s[] )
{	
	int i = 0;
  while (i < 64)
  {
	  if (s[i] == '\0') break;
	  usart_transmit(s[i++]);
  }
}

void init_usart(unsigned int baudrate)
{
	UCSR0C &= (~(1<<UMSEL00) & ~(1<<UMSEL01)); // bit UMSEL = 0 asyncronous mode
	UCSR0A = (1<<U2X0); // bit U2X = 1 double speed mode
	//from table 20-7 (pag.199) fosc = 16 Mhz, U2Xn= 1, BaudRate = 9600, then UBRR= 207
	UBRR0H = (unsigned char) (baudrate>>8); // write(MSB)
	UBRR0L = (unsigned char) (baudrate); //write(LSB)
	UCSR0C = ((1<<UCSZ00) | (1<<UCSZ01)); //8 bits data lenght
	UCSR0B = (1<<RXEN0) | (1<<TXEN0); //enable transmitter & receiver
	//UCSRC = (1<<USBS); //2 stop bits
	UCSR0B |= (1<<RXCIE0);	//enable reception complete (RXCIE0=1) interrupt
}