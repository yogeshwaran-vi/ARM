#include <lpc21xx.h>
#include "DELAY_MS.H"

#define lcd_pin 0xFF
#define RS 			1<<8
#define E				1<<9

void lcd_integer(unsigned int );
void lcd_data(unsigned char );
void lcd_cmd(unsigned char );

void lcd_init(void)
{
	IODIR0=lcd_pin|RS|E;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0c);
	lcd_cmd(0x38);
	lcd_cmd(0x80);
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
void lcd_integer(unsigned int n)
{
	char arr[20];
	int i=0;
		if(n==0)
			{
				lcd_data('0');
				return;
			}
		else
			{
				while(n)
				{
					arr[i++]=n%10;
					n=n/10;
				}
				for(i=i-1;i>=0;i--)
				{
					lcd_data(arr[i]+48);
				}
			}
}
