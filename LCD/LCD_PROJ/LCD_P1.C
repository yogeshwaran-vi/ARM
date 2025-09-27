#include<lpc21xx.h>
#include"delay_ms.h"
#define LCD_DP 0xff<<0
#define RS 1<<8
#define E 1<<9

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);

void LCD_INIT(void)
{
	 IODIR0=LCD_DP|RS|E;
	 LCD_CMD(0x01);
	 LCD_CMD(0x02);
	 LCD_CMD(0X0C);
	 LCD_CMD(0X38);
	 LCD_CMD(0X80);
}
void LCD_CMD(unsigned char cmd)
{
	IOCLR0=LCD_DP;
	IOSET0=cmd;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(1);
	IOCLR0=E;
	
}
void LCD_DATA(unsigned char d)
{
	IOCLR0=LCD_DP;
	IOSET0=d;
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
	delay_ms(500);
}
