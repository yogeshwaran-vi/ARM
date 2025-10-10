#include <lpc21xx.h>
#include "delay_ms.h"

#define lcd_pin 0xFF<<0
#define RS      1<<8
#define E		1<<9

void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(unsigned char *);
void lcd_integer(int );
void lcd_init(void)
{
	IODIR0 = lcd_pin|RS|E;  //INPUT DIR OF LCD P0.0 TO P0.7 
							//RS P0.8 AND ENABLE P0.9	
	lcd_cmd(0x01);			//TO CLEAR THE DISPLAY
	lcd_cmd(0x02);			//RETURN TO CURSOR HOME POSITION 
	lcd_cmd(0x0c);			//DISPLAY ON CURSOR OFF
	lcd_cmd(0x38);			//8-BIT INTERFACE MODE
	lcd_cmd(0x80);			//STARTING ADDRESS OF DDRAM
}
void lcd_cmd(unsigned char cmd)
{
	IOCLR0 = lcd_pin;       //TO CLEAR THE DATA PINS
	IOSET0 = cmd;			//ASSIGN COMMAND TO THE DATA PINS
	IOCLR0 = RS;			//TO SELECT COMMEND REGISTER 0
	IOSET0 = E;				//TO LATCH THE DATA TO THE LCD
	delay_ms(2);			//WAITING FOR 2-MILLISECOND
	IOCLR0 = E;				//TO RE-LATCH THE NEXT BYTE
}
void lcd_data(unsigned char d)
{
	IOCLR0 = lcd_pin;       //TO CLEAR THE DATA PINS	
	IOSET0 = d;				//ASSIGN THE DATA TO DATA PINS
	IOSET0 = RS;			//TO SELECT THE DATA REGISTER 1
	IOSET0 = E;				//TO LATCH THE DATA TO LCD
	delay_ms(2);			//WAIT FOR 2-MILLISECOND
	IOCLR0 = E;				//TO RE-LATCH THE NEXT BYTE
}
void lcd_string(unsigned char *s)
{
	while(*s)
	{
		lcd_data(*s++);
	}
}
void lcd_integer(int n)
{
	lcd_data((n/100)+48);
	lcd_data((n/10)+48);
	lcd_data((n%10)+48);
}

