#include<lpc21xx.h>

#define LCD_DP 0Xf<<4
#define RS 1<<8
//#define RW 1<<17
#define E  1<<9

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);

void delay_ms(unsigned int ms)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<ms);
	T0TCR=0X03;
	T0TCR=0X00;
}

void LCD_INIT(void)
{
	 IODIR0|=LCD_DP|RS|E;
	 LCD_CMD(0x01);
	 LCD_CMD(0x02);
	 LCD_CMD(0X0C);
	 LCD_CMD(0X28);
	 LCD_CMD(0X80);
}
void LCD_CMD(unsigned char cmd)
{
	IOCLR0=LCD_DP;
	IOSET0=(cmd&0XF0)<<0;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;

	IOCLR0=LCD_DP;
	IOSET0=(cmd&0X0F)<<4;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
	
}
void LCD_DATA(unsigned char d)
{
	IOCLR0=LCD_DP;
	IOSET0=(d&0XF0)<<0;
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;

	IOCLR0=LCD_DP;
	IOSET0=(d&0X0F)<<4;
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
LCD_STR(unsigned char *str)
{
	while(*str)
		LCD_DATA(*str++);
}
