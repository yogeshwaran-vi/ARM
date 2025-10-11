#include <lpc21xx.h>
#include "lcd_header.h"

void heart_symbol(void);
void lcd_string(unsigned char *);

unsigned char i = 0x80,j;
unsigned char heart_lut[]={0x00,0x0a,0x15,0x11,0x0a,0x04,0x00,0x00};

int main()
{
	lcd_init();
	heart_symbol();
		
	while(1)
	{
		lcd_cmd(0xc7);
		lcd_data(0);
		delay_ms(500);
		lcd_cmd(0x01);
		lcd_string("YOGESH MARI");
		lcd_cmd(i++);
		if(i==0x90)
			i=0x80;
	}

}
void heart_symbol(void)
{
	char i;
	lcd_cmd(0x40);
	for(i=0;i<8;i++)
	{
		lcd_data(heart_lut[i]);
	}
}
void lcd_string(unsigned char *s)
{
	j=i;	
	while(*s)
	{	
		lcd_cmd(j++);
		if(j==0x90)
			j=0x80;
			lcd_data(*s++);
	}	
	delay_ms(500);
}

