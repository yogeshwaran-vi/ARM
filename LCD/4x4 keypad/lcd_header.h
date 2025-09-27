#include <lpc21xx.h>
#include "delay_ms.h"

#define lcd_pin 0xFF<<0
#define RS		1<<8
#define E		1<<9

void lcd_cmd(unsigned char CMD);
void lcd_init(void)
{
	IODIR0=lcd_pin|RS|E;
	lcd_cmd(0x01);		//to clear a lcd
	lcd_cmd(0x02);		//return to home position
	lcd_cmd(0x0c);      //display on cursor off
	lcd_cmd(0x38);      //8 bit interface mode
	lcd_cmd(0x80);		//starting address
}
void lcd_cmd(unsigned char CMD)
{
	IOCLR0=lcd_pin;
	IOSET0=CMD;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
void lcd_data(unsigned char D)
{
	IOCLR0=lcd_pin;
	IOSET0=D;
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
