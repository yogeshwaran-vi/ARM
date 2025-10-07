#include <lpc21xx.h>
#include "DELAY_MS.H"

#define lcd_pin 0xFF<<0
#define RS		1<<8
#define E 		1<<9

void lcd_init(void);
void lcd_cmd(unsigned char );
void lcd_data(unsigned char );
void lcd_integer(unsigned int);

void lcd_init()
{
		IODIR0 |= lcd_pin|RS|E;
		lcd_cmd(0x01);        //  clear a display
		lcd_cmd(0x02);       //   home position
		lcd_cmd(0x0c);      //    diplay on,cursor off
		lcd_cmd(0x38);	   //	  8 bit interface mode
		lcd_cmd(0x80);	  // 	  select starting address of DDRAM
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
		IOCLR0 = E;
}
void lcd_integer(unsigned int n)
{
	char arr[5];
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
