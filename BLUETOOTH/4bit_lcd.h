#include<lpc21xx.h>
#define lcd_pin 0xf<<4
#define RS  	1<<10
#define E		1<<11
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_str(unsigned char *);
void delay_ms(unsigned int ms)
{
	T0PR  = 15000-1;
	T0TCR =	0X01;
	while(T0TC<ms);
	T0TCR = 0X03;
	T0TCR = 0X00;
}
void lcd_init(void)
{
	IODIR0 |= lcd_pin|RS|E;
	lcd_cmd(0x01); //clear the lcd
	lcd_cmd(0x02);
	lcd_cmd(0x0c); 
	lcd_cmd(0x28);
	lcd_cmd(0x80);
}
void lcd_cmd(unsigned char cmd)
{
	IOCLR0 = lcd_pin;
	IOSET0 = (cmd&0xf0)<<0;
	IOCLR0 = RS;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E;

	IOCLR0 = lcd_pin;
	IOSET0 = (cmd&0x0f)<<4;
	IOCLR0 = RS;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E;
}
void lcd_data(unsigned char d)
{
	IOCLR0 = lcd_pin;
	IOSET0 = (d&0xf0)<<0;
	IOSET0 = RS;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E;

	IOCLR0 = lcd_pin;
	IOSET0 = (d&0x0f)<<4;
	IOSET0 = RS;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E;
}
void lcd_str(unsigned char *s)
{
	while(*s)
	{
		lcd_data(*s++);
	}
}
