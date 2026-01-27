#include<lpc21xx.h>
#define lcd_pin 0x0f<<23
#define RS		1<<18
#define E		1<<19
void lcd_float(float val);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char d);
void lcd_integer(unsigned int val);
void lcd_init()
{
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0c);
	lcd_cmd(0x28);
	lcd_cmd(0x80);
}
void lcd_cmd(unsigned char cmd)
{
	IOCLR1= lcd_pin;
	IOSET1 = (cmd&0xf0)<<19;
	IOCLR1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;

	IOCLR1 = lcd_pin;
	IOSET1 = (cmd&0x0f)<<23;
	IOCLR1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
}
void lcd_data(unsigned char d)
{
	IOCLR1 = lcd_pin;
	IOSET1 = (d&0xf0)<<19;
	IOSET1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;

	IOCLR1 = lcd_pin;
	IOSET1 = (d&0x0f)<<23;
	IOSET1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
}
void lcd_str(unsigned char *s)
{
	while(*s)
	{
		lcd_data(*s++);
	}
}
void lcd_integer(unsigned int num)
{
	signed char arr[5],i=0;
	if(num==0)
		lcd_data('0');
	else
	{
		if(num<0)
		{
			lcd_data('-');
			num=-num;
		} 
		while(num>0)
		{
			arr[i++]=num%10;
			num=num/10;
		}
		for(--i;i>=0;i--)
		{
			lcd_data(arr[i]+48);
		}
	}
}
void lcd_float(float val)
{
	unsigned int num=val;
	lcd_integer(num);
	lcd_data('.');
	num=(val-num)*10;
	lcd_integer(num);
}


