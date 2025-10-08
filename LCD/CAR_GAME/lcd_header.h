#include "delay_ms.h"

#define lcd_pin 0xFF<<0
#define RS      1<<8
#define E		1<<9

void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_init(void)
{
	IODIR0 = lcd_pin|RS|E;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0c);
	lcd_cmd(0x38);
	lcd_cmd(0x80);
}
void lcd_cmd(unsigned char cmd)
{
	IOCLR0 = lcd_pin;
	IOSET0 = cmd;
	IOCLR0 = RS;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E;
}
void lcd_data(unsigned char d)
{
	IOCLR0 = lcd_pin;
	IOSET0 = d;
	IOSET0 = RS;
	IOSET0 = E;
	delay_ms(2);
	IOSET0 = E;
}

